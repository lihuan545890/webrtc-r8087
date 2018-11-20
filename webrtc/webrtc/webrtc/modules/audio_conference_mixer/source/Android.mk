LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libaudio_conference_mixer

LOCAL_CFLAGS += -DWEBRTC_POSIX

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(LOCAL_PATH)/include 
					
LOCAL_SRC_FILES := audio_frame_manipulator.cc \
				   level_indicator.cc \
				   audio_conference_mixer_impl.cc \
				   time_scheduler.cc
				  
include $(BUILD_STATIC_LIBRARY)				   