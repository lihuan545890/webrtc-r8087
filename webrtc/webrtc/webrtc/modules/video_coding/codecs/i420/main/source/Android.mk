LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libwebrtc_i420

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc 
					
LOCAL_SRC_FILES := i420.cc
				   
include $(BUILD_STATIC_LIBRARY)