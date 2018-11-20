LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := librtc_p2p

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc
LOCAL_CFLAGS += -DWEBRTC_POSIX
#$(warning $(LOCAL_C_INCLUDES))


LOCAL_SRC_FILES := base/asyncstuntcpsocket.cc \
                   base/basicpacketsocketfactory.cc \
				   base/constants.cc \
				   base/dtlstransportchannel.cc \
				   base/p2ptransport.cc \
				   base/p2ptransportchannel.cc \
				   base/port.cc \
				   base/portallocator.cc \
				   base/portallocatorsessionproxy.cc \
				   base/portproxy.cc \
				   base/pseudotcp.cc \
				   base/rawtransport.cc \
				   base/rawtransportchannel.cc \
				   base/relayport.cc \
				   base/relayserver.cc \
				   base/session.cc \
				   base/sessiondescription.cc \
				   base/stun.cc \
				   base/stunport.cc \
				   base/stunrequest.cc \
				   base/stunserver.cc \
				   base/tcpport.cc \
				   base/transport.cc \
				   base/transportchannel.cc \
				   base/transportchannelproxy.cc \
				   base/transportdescription.cc \
				   base/transportdescriptionfactory.cc \
				   base/turnport.cc \
				   base/turnserver.cc \
				   client/basicportallocator.cc \
				   client/connectivitychecker.cc \
				   client/httpportallocator.cc \
				   client/socketmonitor.cc
				   
				   

include $(BUILD_STATIC_LIBRARY)