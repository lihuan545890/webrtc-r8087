/*
 *  Copyright 2014 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "webrtc/base/asyncinvoker.h"

namespace rtc {

AsyncInvoker::AsyncInvoker() : destroying_(false) {}

AsyncInvoker::~AsyncInvoker() {
  destroying_ = true;
  SignalInvokerDestroyed();
  // Messages for this need to be cleared *before* our destructor is complete.
  MessageQueueManager::Clear(this);
}

void AsyncInvoker::OnMessage(Message* msg) {
  // Get the AsyncClosure shared ptr from this message's data.
  ScopedRefMessageData<AsyncClosure>* data =
      static_cast<ScopedRefMessageData<AsyncClosure>*>(msg->pdata);
  scoped_refptr<AsyncClosure> closure = data->data();
  delete msg->pdata;
  msg->pdata = NULL;

  // Execute the closure and trigger the return message if needed.
  closure->Execute();
}

void AsyncInvoker::Flush(Thread* thread, uint32 id /*= MQID_ANY*/) {
  if (destroying_) return;

  // Run this on |thread| to reduce the number of context switches.
  if (Thread::Current() != thread) {
    thread->Invoke<void>(Bind(&AsyncInvoker::Flush, this, thread, id));
    return;
  }

  MessageList removed;
  thread->Clear(this, id, &removed);
  for (MessageList::iterator it = removed.begin(); it != removed.end(); ++it) {
    // This message was pending on this thread, so run it now.
    thread->Send(it->phandler,
                 it->message_id,
                 it->pdata);
  }
}

void AsyncInvoker::DoInvoke(Thread* thread, AsyncClosure* closure,
                            uint32 id) {
  if (destroying_) {
    LOG(LS_WARNING) << "Tried to invoke while destroying the invoker.";
    // Since this call transwers ownership of |closure|, we clean it up here.
    delete closure;
    return;
  }
  thread->Post(this, id, new ScopedRefMessageData<AsyncClosure>(closure));
}

NotifyingAsyncClosureBase::NotifyingAsyncClosureBase(AsyncInvoker* invoker,
                                                     Thread* calling_thread)
    : invoker_(invoker), calling_thread_(calling_thread) {
  calling_thread->SignalQueueDestroyed.connect(
      this, &NotifyingAsyncClosureBase::CancelCallback);
  invoker->SignalInvokerDestroyed.connect(
      this, &NotifyingAsyncClosureBase::CancelCallback);
}

void NotifyingAsyncClosureBase::TriggerCallback() {
  CritScope cs(&crit_);
  if (!CallbackCanceled() && !callback_.empty()) {
    invoker_->AsyncInvoke<void>(calling_thread_, callback_);
  }
}

void NotifyingAsyncClosureBase::CancelCallback() {
  // If the callback is triggering when this is called, block the
  // destructor of the dying object here by waiting until the callback
  // is done triggering.
  CritScope cs(&crit_);
  // calling_thread_ == NULL means do not trigger the callback.
  calling_thread_ = NULL;
}

}  // namespace rtc
