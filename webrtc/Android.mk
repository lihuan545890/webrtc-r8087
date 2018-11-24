LOCAL_PATH := $(call my-dir)
MY_WEBRTC_ROOT_PATH := $(LOCAL_PATH)/webrtc/webrtc

LOCAL_MODULE    := libvpx
LOCAL_SRC_FILES := webrtc/webrtc/third_party/libvpx/obj/local/armeabi-v7a/libvpx.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := libx264
LOCAL_SRC_FILES := webrtc/webrtc/third_party/ffmpeg/libx264/lib/libx264.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := libavcodec
LOCAL_SRC_FILES := webrtc/webrtc/third_party/ffmpeg/android/arm-v7a/lib/libavcodec.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := libavfilter
LOCAL_SRC_FILES := webrtc/webrtc/third_party/ffmpeg/android/arm-v7a/lib/libavfilter.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := libavformat
LOCAL_SRC_FILES := webrtc/webrtc/third_party/ffmpeg/android/arm-v7a/lib/libavformat.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := libavutil
LOCAL_SRC_FILES := webrtc/webrtc/third_party/ffmpeg/android/arm-v7a/lib/libavutil.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := libswresample
LOCAL_SRC_FILES := webrtc/webrtc/third_party/ffmpeg/android/arm-v7a/lib/libswresample.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := libswscale
LOCAL_SRC_FILES := webrtc/webrtc/third_party/ffmpeg/android/arm-v7a/lib/libswscale.a
include $(PREBUILT_STATIC_LIBRARY)

#LOCAL_CPPFLAGS += -std=c++11
LOCAL_CFLAGS += -DWEBRTC_POSIX

include $(MY_WEBRTC_ROOT_PATH)/base/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/system_wrappers/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/media_file/source/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/utility/source/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/video_capture/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/audio_coding/codecs/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/audio_coding/codecs/cng/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/audio_coding/codecs/g711/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/audio_coding/codecs/g722/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/audio_coding/codecs/ilbc/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/audio_coding/codecs/isac/main/source/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/audio_coding/codecs/opus/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/audio_coding/codecs/pcm16b/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/audio_coding/codecs/red/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/audio_coding/neteq/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/audio_coding/main/acm2/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/pacing/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/remote_bitrate_estimator/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/rtp_rtcp/source/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/bitrate_controller/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/video_render/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/video_coding/utility/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/video_coding/codecs/vp8/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/video_coding/codecs/vp9/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/video_coding/codecs/h264/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/video_coding/codecs/i420/main/source/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/video_coding/main/source/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/video_processing/main/source/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/audio_device/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/audio_conference_mixer/source/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/modules/audio_processing/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/test/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/common_audio/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/common_video/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/video_engine/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/voice_engine/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/third_party/libyuv/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/third_party/openssl/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/third_party/jsoncpp/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/third_party/icu/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/third_party/opus/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/sound/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/p2p/Android.mk

include $(CLEAR_VARS)

LOCAL_MODULE := libwebrtcdemo-jni

LOCAL_MODULE_TAGS := optional

LOCAL_LDLIBS += -llog -lGLESv2 -lOpenSLES -lz

LOCAL_CPPFLAGS += -std=c++11   -lcrystax_static -lgnustl_static -frtti -DWEBRTC_ANDROID
LOCAL_CFLAGS += -DWEBRTC_ANDROID
LOCAL_CFLAGS += -DWEBRTC_POSIX
LOCAL_CPP_FEATURES := rtti

LOCAL_CPP_EXTENSION := .cc

PROJECT_PATH :=/project/mnt/webrtc-r8087/webrtc/webrtc
LOCAL_C_INCLUDES := $(PROJECT_PATH) \
					$(PROJECT_PATH)/webrtc \
					$(PROJECT_PATH)/webrtc/third_party/icu/source/common \
					$(PROJECT_PATH)/webrtc/third_party/ffmpeg/android/arm-v7a/include

LOCAL_SRC_FILES :=   $(PROJECT_PATH)/webrtc/examples/android/media_demo/jni/jni_helpers.cc \
					 $(PROJECT_PATH)/webrtc/examples/android/media_demo/jni/on_load.cc \
					 $(PROJECT_PATH)/webrtc/examples/android/media_demo/jni/video_engine_jni.cc \
					 $(PROJECT_PATH)/webrtc/examples/android/media_demo/jni/voice_engine_jni.cc \
					 $(PROJECT_PATH)/webrtc/examples/android/media_demo/jni/media_codec_video_decoder.cc

LOCAL_WHOLE_STATIC_LIBRARIES := libmedia_file \
								libwebrtc_utility \
								libssl \
								libopenssl \
								libopus \
								librtc_base_approved \
								libwebrtc_base \
								libsystem_wrappers \
								libcommon_audio \
								libcommon_audio_neon \
								libyuv_static \
								libjsoncpp \
								libi18n \
								libicudata \
								libicuuc \
								libcommon_video \
								librtc_sound \
								librtc_p2p \
								libaudio_decoder_interface \
								libaudio_encoder_interface \
								libcng \
								libg711 \
								libg722 \
								libilbc \
								libisac \
								libred \
								libwebrtc_opus \
								libpcm16b \
								libvpx \
								libx264 \
								libavformat \
								libavcodec \
								libavutil \
								libavfilter \
								libswresample \
								libswscale \
								libneteq \
								libvideo_capture_module \
								libvideo_capture_module_internal_impl \
                                librtc_sound \
								libpaced_sender \
								libremote_bitrate_estimator \
								librtp_rtcp \
								libbitrate_controller \
								libchannel_transport \
								libvideo_render_module \
								libvideo_render_module_internal_impl \
								libvideo_coding_utility \
								libwebrtc_vp8 \
								libwebrtc_vp9 \
								libwebrtc_i420 \
								libwebrtc_h264 \
								libwebrtc_video_coding \
								libvideo_engine_core \
								libvideo_processing \
								libaudio_coding_module \
								libaudio_device \
								libaudio_conference_mixer \
								libaudio_processing \
								libvoice_engine



LOCAL_PRELINK_MODULE := false

include $(BUILD_SHARED_LIBRARY)