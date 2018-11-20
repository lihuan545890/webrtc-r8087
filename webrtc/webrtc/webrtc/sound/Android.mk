LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := librtc_sound

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc

#$(warning $(LOCAL_C_INCLUDES))
LOCAL_CFLAGS += -DWEBRTC_POSIX

LOCAL_SRC_FILES := nullsoundsystem.cc \
                   nullsoundsystemfactory.cc \
				   platformsoundsystem.cc \
				   platformsoundsystemfactory.cc \
				   soundsysteminterface.cc \
				   soundsystemproxy.cc
				   

include $(BUILD_STATIC_LIBRARY)