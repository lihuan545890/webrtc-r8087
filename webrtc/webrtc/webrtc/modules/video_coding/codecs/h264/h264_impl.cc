#include "webrtc/modules/video_coding/codecs/h264/h264_impl.h"

#include <android/log.h>
#include <stdio.h>

#define WEBRTC_TRACE(a,b,c,...)  __android_log_print(ANDROID_LOG_DEBUG, "H264EncoderImpl", __VA_ARGS__)

namespace webrtc{

H264Encoder* H264Encoder::Create()
{
	return new H264EncoderImpl();
}

H264EncoderImpl::H264EncoderImpl()
{
      WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "H264Encoder Create Success");   
}

H264EncoderImpl::~H264EncoderImpl()
{
	Release();
}

int H264EncoderImpl::Release()
{
	return WEBRTC_VIDEO_CODEC_OK;
}

int H264EncoderImpl::SetRates(uint32_t new_bitrate_kbit, uint32_t frame_rate)
{
	return WEBRTC_VIDEO_CODEC_OK;
}

int H264EncoderImpl::InitEncode(const VideoCodec * codec_settings, int number_of_cores, size_t max_payload_size)
{

    WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "H264Encoder InitEncode Success"); 
	return WEBRTC_VIDEO_CODEC_OK;

}

int H264EncoderImpl::Encode(const I420VideoFrame & input_image, const CodecSpecificInfo * codec_specific_info, const std::vector <VideoFrameType>* frame_types)
{
    WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "H264Encoder Encode Success width:%d, height:%d", input_image.width(), input_image.height()); 
	return WEBRTC_VIDEO_CODEC_OK;
}

int H264EncoderImpl::RegisterEncodeCompleteCallback(EncodedImageCallback * callback)
{
	return WEBRTC_VIDEO_CODEC_OK;

}

int H264EncoderImpl::SetChannelParameters(uint32_t packet_loss, int64_t rtt)
{
	return WEBRTC_VIDEO_CODEC_OK;
}


H264Decoder* H264Decoder::Create()
{
	return new H264DecoderImpl();
}

H264DecoderImpl::H264DecoderImpl()
{

}

H264DecoderImpl::~H264DecoderImpl()
{

}

int H264DecoderImpl::InitDecode(const VideoCodec * inst, int number_of_cores)
{
	return WEBRTC_VIDEO_CODEC_OK;
}

int H264DecoderImpl::Decode(const EncodedImage & input_image, bool missing_frames, const RTPFragmentationHeader * fragmentation, const CodecSpecificInfo * codec_specific_info, int64_t)
{
	return WEBRTC_VIDEO_CODEC_OK;
}

int H264DecoderImpl::RegisterDecodeCompleteCallback(DecodedImageCallback * callback)
{
	return WEBRTC_VIDEO_CODEC_OK;
}

int H264DecoderImpl::Release()
{
	return WEBRTC_VIDEO_CODEC_OK;
}

int H264DecoderImpl::Reset()
{
	return WEBRTC_VIDEO_CODEC_OK;
}

VideoDecoder *H264DecoderImpl::Copy()
{
	return WEBRTC_VIDEO_CODEC_OK;
}

}


