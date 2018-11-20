LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libmedia_file

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc

LOCAL_SRC_FILES := avi_file.cc \
				   media_file_impl.cc \
				   media_file_utility.cc

include $(BUILD_STATIC_LIBRARY)