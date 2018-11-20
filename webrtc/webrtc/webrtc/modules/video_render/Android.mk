LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libvideo_render_module

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(LOCAL_PATH)/include 
					
LOCAL_SRC_FILES := external/video_render_external_impl.cc \
				   incoming_video_stream.cc \
				   video_render_frames.cc \

				   
				   
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := libvideo_render_module_impl

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(LOCAL_PATH)/include 
					
LOCAL_SRC_FILES := video_render_impl.cc

				   				   
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := libvideo_render_module_internal_impl

LOCAL_CPPFLAGS += -DWEBRTC_ANDROID

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(LOCAL_PATH)/include 
					
LOCAL_SRC_FILES := video_render_internal_impl.cc \
				   android/video_render_android_impl.cc \
				   android/video_render_android_native_opengl2.cc \
				   android/video_render_android_surface_view.cc \
				   android/video_render_opengles20.cc

				   				   
include $(BUILD_STATIC_LIBRARY)