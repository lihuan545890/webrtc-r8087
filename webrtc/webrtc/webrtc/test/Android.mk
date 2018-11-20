LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libchannel_transport

#LOCAL_CPPFLAGS += -DJSON_USE_EXCEPTION=0
LOCAL_CPPFLAGS += -DWEBRTC_ANDROID -DWEBRTC_LINUX


LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(JNI_PATH)/webrtc/webrtc 

					
					
LOCAL_SRC_FILES := channel_transport/channel_transport.cc \
				   channel_transport/udp_socket_manager_posix.cc \
				   channel_transport/udp_socket_manager_wrapper.cc \
				   channel_transport/udp_socket_posix.cc \
				   channel_transport/udp_socket_wrapper.cc \
				   channel_transport/udp_transport_impl.cc
				   
include $(BUILD_STATIC_LIBRARY)				   