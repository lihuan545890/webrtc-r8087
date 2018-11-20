LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libcommon_video

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc $(JNI_PATH)/webrtc/webrtc/third_party/libyuv/include

#$(warning $(LOCAL_C_INCLUDES))


LOCAL_SRC_FILES := i420_video_frame.cc libyuv/webrtc_libyuv.cc libyuv/scaler.cc plane.cc texture_video_frame.cc

include $(BUILD_STATIC_LIBRARY)