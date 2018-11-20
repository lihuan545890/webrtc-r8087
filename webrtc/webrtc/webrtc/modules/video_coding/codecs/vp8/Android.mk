LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libwebrtc_vp8

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(JNI_PATH)/webrtc/webrtc/third_party/libvpx/jni/libvpx \
					$(JNI_PATH)/webrtc/webrtc/third_party/libyuv/include

					
LOCAL_SRC_FILES := default_temporal_layers.cc \
				   realtime_temporal_layers.cc \
				   reference_picture_selection.cc \
				   screenshare_layers.cc \
				   simulcast_encoder_adapter.cc \
				   vp8_factory.cc \
				   vp8_impl.cc

				   
				   
include $(BUILD_STATIC_LIBRARY)