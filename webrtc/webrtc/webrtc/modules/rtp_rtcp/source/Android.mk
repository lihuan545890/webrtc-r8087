LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := librtp_rtcp

LOCAL_CPPFLAGS += -DWEBRTC_LINUX

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc 
									
LOCAL_SRC_FILES := bitrate.cc \
				   fec_receiver_impl.cc \
				   receive_statistics_impl.cc \
				   remote_ntp_time_estimator.cc \
				   rtp_header_parser.cc \
				   rtp_rtcp_impl.cc \
				   rtcp_packet.cc \
				   rtcp_receiver.cc \
				   rtcp_receiver_help.cc \
				   rtcp_sender.cc \
				   rtcp_utility.cc \
				   rtp_header_extension.cc \
				   rtp_receiver_impl.cc \
				   rtp_sender.cc \
				   rtp_utility.cc \
				   ssrc_database.cc \
				   tmmbr_help.cc \
				   dtmf_queue.cc \
				   rtp_receiver_audio.cc \
				   rtp_sender_audio.cc \
				   forward_error_correction.cc \
				   forward_error_correction_internal.cc \
				   producer_fec.cc \
				   rtp_packet_history.cc \
				   rtp_payload_registry.cc \
				   rtp_receiver_strategy.cc \
				   rtp_receiver_video.cc \
				   rtp_sender_video.cc \
				   rtp_format.cc \
				   rtp_format_h264.cc \
				   rtp_format_vp8.cc \
				   rtp_format_video_generic.cc \
				   vp8_partition_aggregator.cc
				   
				   
				   
include $(BUILD_STATIC_LIBRARY)				   