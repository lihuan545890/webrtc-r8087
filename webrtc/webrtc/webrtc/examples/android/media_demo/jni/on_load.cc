/*
 *  Copyright (c) 2013 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include <jni.h>

#include <assert.h>

#include "webrtc/examples/android/media_demo/jni/jni_helpers.h"
#include "webrtc/examples/android/media_demo/jni/video_engine_jni.h"
#include "webrtc/examples/android/media_demo/jni/voice_engine_jni.h"
#include "webrtc/modules/video_capture/video_capture_internal.h"
#include "webrtc/modules/video_render/video_render_internal.h"
#include "webrtc/voice_engine/include/voe_base.h"

// Macro for native functions that can be found by way of jni-auto discovery.
// Note extern "C" is needed for "discovery" of native methods to work.
extern "C"{
	#include "libavcodec/jni.h"	
	#include "libavutil/opt.h"
}

#define JOWW(rettype, name)                                             \
  extern "C" rettype JNIEXPORT JNICALL Java_org_webrtc_webrtcdemo_##name

static JavaVM* g_vm = NULL;

inline static int convert_to_android_log(int av_level)
{
    int level = ANDROID_LOG_VERBOSE;
    if      (av_level <= AV_LOG_PANIC)      level = ANDROID_LOG_FATAL;
    else if (av_level <= AV_LOG_FATAL)      level = ANDROID_LOG_FATAL;
    else if (av_level <= AV_LOG_ERROR)      level = ANDROID_LOG_ERROR;
    else if (av_level <= AV_LOG_WARNING)    level = ANDROID_LOG_WARN;
    else if (av_level <= AV_LOG_INFO)       level = ANDROID_LOG_INFO;
    // AV_LOG_VERBOSE means detailed info
    else if (av_level <= AV_LOG_VERBOSE)    level = ANDROID_LOG_INFO;
    else if (av_level <= AV_LOG_DEBUG)      level = ANDROID_LOG_DEBUG;
    else if (av_level <= AV_LOG_TRACE)      level = ANDROID_LOG_VERBOSE;
    else                                    level = ANDROID_LOG_VERBOSE;
    return level;
}

static void ff_log_callback_brief(void *ptr, int level, const char *fmt, va_list vl)
{
	if(level >48)
		return;

	int ffplv __unused = convert_to_android_log(level);
	 __android_log_vprint(ffplv, "ffmpeg-jni", fmt, vl); 
}


extern "C" jint JNIEXPORT JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
  // Only called once.
  CHECK(!g_vm, "OnLoad called more than once");
  g_vm = vm;
  av_log_set_callback(ff_log_callback_brief);
  av_jni_set_java_vm(vm, NULL);
  return JNI_VERSION_1_4;
}

JOWW(void, NativeWebRtcContextRegistry_register)(
    JNIEnv* jni,
    jclass,
    jobject context) {
  webrtc_examples::SetVoeDeviceObjects(g_vm);
  webrtc_examples::SetVieDeviceObjects(g_vm);
  CHECK(webrtc::SetCaptureAndroidVM(g_vm, context) == 0,
        "Failed to register android objects to video capture");
  CHECK(webrtc::SetRenderAndroidVM(g_vm) == 0,
        "Failed to register android objects to video render");
  CHECK(webrtc::VoiceEngine::SetAndroidObjects(g_vm, jni, context) == 0,
        "Failed to register android objects to voice engine");  
}

JOWW(void, NativeWebRtcContextRegistry_unRegister)(
    JNIEnv* jni,
    jclass) {
  CHECK(webrtc::SetCaptureAndroidVM(NULL, NULL) == 0,
        "Failed to unregister android objects from video capture");
  CHECK(webrtc::SetRenderAndroidVM(NULL) == 0,
        "Failed to unregister android objects from video render");
  CHECK(webrtc::VoiceEngine::SetAndroidObjects(NULL, NULL, NULL) == 0,
        "Failed to unregister android objects from voice engine");
  webrtc_examples::ClearVieDeviceObjects();
  webrtc_examples::ClearVoeDeviceObjects();
}
