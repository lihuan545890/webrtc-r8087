LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libaudio_processing

LOCAL_CFLAGS += -DWEBRTC_POSIX -DWEBRTC_NS_FLOAT

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \

LOCAL_SRC_FILES := aec/aec_core.c \
				   aec/aec_rdft.c \
				   aec/aec_resampler.c \
				   aec/echo_cancellation.c \
				   aecm/aecm_core.c \
				   aecm/aecm_core_c.c \
				   aecm/echo_control_mobile.c \
				   agc/agc.cc \
				   agc/agc_audio_proc.cc \
				   agc/agc_manager_direct.cc \
				   agc/circular_buffer.cc \
				   agc/gmm.cc \
				   agc/histogram.cc \
				   agc/legacy/analog_agc.c \
				   agc/legacy/digital_agc.c \
				   agc/pitch_based_vad.cc \
				   agc/pitch_internal.cc \
				   agc/pole_zero_filter.cc \
				   agc/standalone_vad.cc \
				   agc/utility.cc \
				   audio_buffer.cc \
				   audio_processing_impl.cc \
				   beamformer/covariance_matrix_generator.cc \
				   channel_buffer.cc \
				   echo_cancellation_impl.cc \
				   echo_control_mobile_impl.cc \
				   gain_control_impl.cc \
				   high_pass_filter_impl.cc \
				   level_estimator_impl.cc \
				   noise_suppression_impl.cc \
				   ns/noise_suppression.c \
				   ns/ns_core.c \
				   processing_component.cc \
				   rms_level.cc \
				   splitting_filter.cc \
				   transient/moving_moments.cc \
				   transient/transient_detector.cc \
				   transient/transient_suppressor.cc \
				   transient/wpd_node.cc \
				   transient/wpd_tree.cc \
				   typing_detection.cc \
				   utility/delay_estimator.c \
				   utility/delay_estimator_wrapper.c \
				   utility/fft4g.c \
				   voice_detection_impl.cc
				   

include $(BUILD_STATIC_LIBRARY)