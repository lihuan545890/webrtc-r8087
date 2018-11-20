LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libvideo_engine_core

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc/
					
LOCAL_SRC_FILES := call_stats.cc \
				   encoder_state_feedback.cc \
				   overuse_frame_detector.cc \
				   report_block_stats.cc \
				   stream_synchronization.cc \
				   vie_base_impl.cc \
				   vie_capture_impl.cc \
				   vie_codec_impl.cc \
				   vie_external_codec_impl.cc \
				   vie_image_process_impl.cc \
				   vie_impl.cc \
				   vie_network_impl.cc \
				   vie_ref_count.cc \
				   vie_render_impl.cc \
				   vie_rtp_rtcp_impl.cc \
				   vie_shared_data.cc \
				   vie_capturer.cc \
				   vie_channel.cc \
				   vie_channel_group.cc \
				   vie_channel_manager.cc \
				   vie_encoder.cc \
				   vie_file_image.cc \
				   vie_frame_provider_base.cc \
				   vie_input_manager.cc \
				   vie_manager_base.cc \
				   vie_receiver.cc \
				   vie_remb.cc \
				   vie_renderer.cc \
				   vie_render_manager.cc \
				   vie_sender.cc \
				   vie_sync_module.cc
				   
include $(BUILD_STATIC_LIBRARY)				   