LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libwebrtc_vp9

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(JNI_PATH)/webrtc/webrtc/third_party/libvpx/jni/libvpx \
					$(JNI_PATH)/webrtc/webrtc/third_party/libyuv/include

					
LOCAL_SRC_FILES := vp9_impl.cc


				   
				   
include $(BUILD_STATIC_LIBRARY)