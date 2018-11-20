LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libvideo_processing

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					
LOCAL_SRC_FILES := brighten.cc \
				   brightness_detection.cc \
				   color_enhancement.cc \
				   content_analysis.cc \
				   deflickering.cc \
				   frame_preprocessor.cc \
				   spatial_resampler.cc \
				   video_decimator.cc \
				   video_processing_impl.cc


include $(BUILD_STATIC_LIBRARY)