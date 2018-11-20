LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libwebrtc_utility

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc

LOCAL_SRC_FILES := audio_frame_operations.cc \
                   coder.cc \
				   file_player_impl.cc \
				   file_recorder_impl.cc \
				   helpers_android.cc \
				   process_thread_impl.cc \
				   rtp_dump_impl.cc 
				   

include $(BUILD_STATIC_LIBRARY)