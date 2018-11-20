LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libremote_bitrate_estimator

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(LOCAL_PATH)/include 
					
LOCAL_SRC_FILES := aimd_rate_control.cc \
				   inter_arrival.cc \
				   mimd_rate_control.cc \
				   overuse_detector.cc \
				   overuse_estimator.cc \
				   rate_statistics.cc \
				   remote_bitrate_estimator_abs_send_time.cc \
				   remote_bitrate_estimator_single_stream.cc \
				   remote_rate_control.cc \
				   test/bwe_test_logging.cc
				   
				   
				   
				  
include $(BUILD_STATIC_LIBRARY)				   