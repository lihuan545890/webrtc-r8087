LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libpaced_sender

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(LOCAL_PATH)/include 
					
LOCAL_SRC_FILES := bitrate_prober.cc \
				   paced_sender.cc 
				  
include $(BUILD_STATIC_LIBRARY)				   