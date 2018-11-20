LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libwebrtc_video_coding

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					
LOCAL_SRC_FILES := codec_database.cc \
				   codec_timer.cc \
				   content_metrics_processing.cc \
				   decoding_state.cc \
				   encoded_frame.cc \
				   frame_buffer.cc \
				   generic_decoder.cc \
				   generic_encoder.cc \
				   inter_frame_delay.cc \
				   jitter_buffer.cc \
				   jitter_estimator.cc \
				   media_opt_util.cc \
				   media_optimization.cc \
				   packet.cc \
				   qm_select.cc \
				   receiver.cc \
				   rtt_filter.cc \
				   session_info.cc \
				   timestamp_map.cc \
				   timing.cc \
				   video_coding_impl.cc \
				   video_sender.cc \
				   video_receiver.cc

include $(BUILD_STATIC_LIBRARY)