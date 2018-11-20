LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libbitrate_controller

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(LOCAL_PATH)/include 
					
LOCAL_SRC_FILES := bitrate_controller_impl.cc \
				   remb_suppressor.cc \
				   send_side_bandwidth_estimation.cc
				  
include $(BUILD_STATIC_LIBRARY)				   