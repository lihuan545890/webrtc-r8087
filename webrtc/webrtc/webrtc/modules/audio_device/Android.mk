LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libaudio_device

LOCAL_CFLAGS += -DWEBRTC_ANDROID  -DWEBRTC_LINUX

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(LOCAL_PATH)/android

LOCAL_SRC_FILES := audio_device_buffer.cc \
				   audio_device_generic.cc \
				   audio_device_utility.cc \
				   audio_device_impl.cc \
				   dummy/audio_device_dummy.cc \
				   dummy/audio_device_utility_dummy.cc \
				   dummy/file_audio_device.cc \
				   android/audio_device_utility_android.cc \
				   android/audio_manager_jni.cc \
				   android/audio_record_jni.cc \
				   android/audio_track_jni.cc \
				   android/fine_audio_buffer.cc \
				   android/low_latency_event_posix.cc \
				   android/opensles_common.cc \
				   android/opensles_input.cc \
				   android/opensles_output.cc \
				   android/single_rw_fifo.cc
				   

include $(BUILD_STATIC_LIBRARY)