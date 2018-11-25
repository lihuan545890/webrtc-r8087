#include "webrtc/modules/video_coding/codecs/h264/h264_impl.h"
#include "webrtc/common_video/libyuv/include/webrtc_libyuv.h"

#include <android/log.h>
#include <stdio.h>


#define WEBRTC_TRACE(a,b,c,...)  __android_log_print(ANDROID_LOG_DEBUG, "H264EncoderImpl", __VA_ARGS__)

namespace webrtc{

H264Encoder* H264Encoder::Create()
{
	return new H264EncoderImpl();
}

H264EncoderImpl::H264EncoderImpl()
	: encoded_image_(),
	  encoded_complete_callback_(NULL), 
	  inited_(false)
{
  	  memset(&codec_, 0, sizeof(codec_));
      WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "H264Encoder Create Success");   
}

H264EncoderImpl::~H264EncoderImpl()
{
	Release();
}

int H264EncoderImpl::Release()
{
	inited_ = false;
    if (encoded_image_._buffer != NULL) {
      delete [] encoded_image_._buffer;
      encoded_image_._buffer = NULL;
    }
	
	return WEBRTC_VIDEO_CODEC_OK;
}

int H264EncoderImpl::SetRates(uint32_t new_bitrate_kbit, uint32_t frame_rate)
{
    if (!inited_) {
      return WEBRTC_VIDEO_CODEC_UNINITIALIZED;
    }

	return WEBRTC_VIDEO_CODEC_OK;
}

int H264EncoderImpl::InitEncode(const VideoCodec * codec_settings, int number_of_cores, size_t max_payload_size)
{

    if (codec_settings == NULL) {
      return WEBRTC_VIDEO_CODEC_ERR_PARAMETER;
    }
    if (codec_settings->maxFramerate < 1) {
      return WEBRTC_VIDEO_CODEC_ERR_PARAMETER;
    }
    // Allow zero to represent an unspecified maxBitRate
    if (codec_settings->maxBitrate > 0 && codec_settings->startBitrate > codec_settings->maxBitrate) {
      return WEBRTC_VIDEO_CODEC_ERR_PARAMETER;
    }
    if (codec_settings->width < 1 || codec_settings->height < 1) {
      return WEBRTC_VIDEO_CODEC_ERR_PARAMETER;
    }

    if (&codec_ != codec_settings) {
      codec_ = *codec_settings;
    }

    if (encoded_image_._buffer != NULL) {
      delete [] encoded_image_._buffer;
    }

    encoded_image_._size = CalcBufferSize(kI420, codec_.width, codec_.height);
    encoded_image_._buffer = new uint8_t[encoded_image_._size];
    encoded_image_._completeFrame = true;

	av_register_all();
	pCodec = avcodec_find_encoder_by_name("libx264");

	if (!pCodec){
   		WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "fine h264 encoder failed"); 
		return WEBRTC_VIDEO_CODEC_ERROR;
	}
	pFrameYUV = av_frame_alloc(); // 初始化的时候AVFrame中的元素data,linesize均为空。未指向任何内存数据，必须指向一块内存
	uint8_t * out_buffer = (uint8_t *)av_malloc(avpicture_get_size(AV_PIX_FMT_YUV420P, codec_settings->width, codec_settings->height));
	avpicture_fill((AVPicture *)pFrameYUV, out_buffer, AV_PIX_FMT_YUV420P, codec_settings->width, codec_settings->height);	
	
	pCodecCtx = avcodec_alloc_context3(pCodec);
//	pCodecCtx->bit_rate = 400000 * 5;
	pCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
	pCodecCtx->width = codec_settings->width;
	pCodecCtx->height = codec_settings->height;
	pCodecCtx->time_base = (AVRational){1, codec_settings->maxFramerate};
	pCodecCtx->max_b_frames = 1;

	av_opt_set(pCodecCtx->priv_data, "profile", "main", 0);
	av_opt_set(pCodecCtx->priv_data, "preset", "ultrafast", 0);

	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
   		WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "open h264 encoder failed"); 
		return WEBRTC_VIDEO_CODEC_ERROR;
	}

	inited_ = true;
    WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "H264Encoder InitEncode Success"); 
	return WEBRTC_VIDEO_CODEC_OK;

}

//FILE *fp=fopen("/sdcard/test.h264", "wb");
int H264EncoderImpl::Encode(const I420VideoFrame & input_image, const CodecSpecificInfo * codec_specific_info, const std::vector <VideoFrameType>* frame_types)
{
	int enc_got_frame=0;
	static int count = 0;
    if (!inited_) {
      return WEBRTC_VIDEO_CODEC_UNINITIALIZED;
    }
    if (input_image.IsZeroSize()) {
      return WEBRTC_VIDEO_CODEC_ERR_PARAMETER;
    }

    if (encoded_complete_callback_ == NULL) {
      return WEBRTC_VIDEO_CODEC_UNINITIALIZED;
    }

    VideoFrameType frame_type = kDeltaFrame;  
    // We only support one stream at the moment.  
    if (frame_types && frame_types->size() > 0) {  
        frame_type = (*frame_types)[0];  
    }  
  

	av_init_packet(&enc_pkt);
	enc_pkt.data = NULL;
	enc_pkt.size = 0;

	int size = input_image.width() * input_image.height();
	memcpy(pFrameYUV->data[0], input_image.buffer(kYPlane), size);
	memcpy(pFrameYUV->data[1], input_image.buffer(kUPlane), size / 4);
	memcpy(pFrameYUV->data[2], input_image.buffer(kVPlane), size / 4);	

	pFrameYUV->format = AV_PIX_FMT_YUV420P;
	pFrameYUV->width = input_image.width();
	pFrameYUV->height = input_image.height();	

	if (avcodec_encode_video2(pCodecCtx, &enc_pkt, pFrameYUV, &enc_got_frame)) {
		return WEBRTC_VIDEO_CODEC_ERROR;
	}

    encoded_image_._length = 0;
    encoded_image_._frameType = kDeltaFrame;
    RTPFragmentationHeader frag_info;
	frag_info.VerifyAndAllocateFragmentationHeader(1);

	if(enc_got_frame)
	{
/*		if(count++<200)
		{
			fwrite(enc_pkt.data, 1, enc_pkt.size, fp);
		}
		else
		{
			fclose(fp);
		}
*/		uint32_t currentNaluSize = enc_pkt.size - 4;
		memcpy(encoded_image_._buffer, enc_pkt.data + 4, currentNaluSize);
		encoded_image_._length = currentNaluSize; 

        frag_info.fragmentationOffset[0] = 0;  
        frag_info.fragmentationLength[0] = currentNaluSize;  
        frag_info.fragmentationPlType[0] = pCodecCtx->coded_frame->pict_type;  
        frag_info.fragmentationTimeDiff[0] = 0;  
		frag_info.fragmentationTimeDiff[0] = 0;

        if (encoded_image_._length > 0) {  
            encoded_image_._timeStamp = input_image.timestamp();  
            encoded_image_.capture_time_ms_ = input_image.render_time_ms();  
            encoded_image_._encodedHeight = codec_.height;  
            encoded_image_._encodedWidth = codec_.width;  
            encoded_image_._frameType = frame_type;  
            // call back  
            encoded_complete_callback_->Encoded(encoded_image_, NULL, &frag_info);  
        } 

		av_free_packet(&enc_pkt);
	}
	
    WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "H264Encoder Encode Success kYPlane:%d, kUPlane:%d, encode size:%d", input_image.stride(kYPlane), input_image.stride(kUPlane), enc_pkt.size); 
	return WEBRTC_VIDEO_CODEC_OK;
}

int H264EncoderImpl::RegisterEncodeCompleteCallback(EncodedImageCallback * callback)
{
	encoded_complete_callback_ = callback;
    WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "H264Encoder RegisterEncodeCompleteCallback success"); 
	
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


