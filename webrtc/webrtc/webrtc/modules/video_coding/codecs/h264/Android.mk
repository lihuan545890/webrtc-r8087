LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libwebrtc_h264

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(JNI_PATH)/webrtc/webrtc/third_party/ffmpeg/android/arm-v7a/include
					
LOCAL_SRC_FILES := h264_impl.cc
				   
include $(BUILD_STATIC_LIBRARY)