LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libvideo_coding_utility

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \

					
LOCAL_SRC_FILES := frame_dropper.cc \
				   quality_scaler.cc

				   
				   
include $(BUILD_STATIC_LIBRARY)