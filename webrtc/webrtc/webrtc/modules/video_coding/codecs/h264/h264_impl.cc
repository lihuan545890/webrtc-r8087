#include "webrtc/modules/video_coding/codecs/h264/h264_impl.h"
#include "webrtc/common_video/libyuv/include/webrtc_libyuv.h"
#include "webrtc/system_wrappers/interface/trace.h"

//FILE *fp=fopen("/sdcard/test.h264", "wb");
FILE *fp = fopen("/sdcard/test.yuv", "wb");
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

	av_opt_set(pCodecCtx->priv_data, "profile", "baseline", 0);
	av_opt_set(pCodecCtx->priv_data, "preset", "ultrafast", 0);

	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
   		WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "open h264 encoder failed"); 
		return WEBRTC_VIDEO_CODEC_ERROR;
	}

	inited_ = true;
    WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "H264Encoder InitEncode Success"); 
	return WEBRTC_VIDEO_CODEC_OK;

}


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
	: decoded_image_(),
	  decode_complete_callback_(NULL),
      inited_(false)
{
  	  memset(&codec_, 0, sizeof(codec_));
}

H264DecoderImpl::~H264DecoderImpl()
{
	Release();
}

int H264DecoderImpl::InitDecode(const VideoCodec * inst, int number_of_cores)
{

    if (inst == NULL) {
      return WEBRTC_VIDEO_CODEC_ERR_PARAMETER;
    }
    int ret_val = Release();
    if (ret_val < 0) {
      return ret_val;
    }

	if (&codec_ != inst) {	
		codec_ = *inst;
	}

    av_register_all();
	pCodec = avcodec_find_decoder(AV_CODEC_ID_H264);
	if(pCodec == NULL)
	{
   		WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "fine h264 encoder failed"); 
		return WEBRTC_VIDEO_CODEC_ERROR;
	}
	pCodecCtx = avcodec_alloc_context3(pCodec);
	pCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
	pCodecCtx->width = codec_.width;
	pCodecCtx->height = codec_.height;
	pCodecCtx->time_base.num = 1;
	pCodecCtx->time_base.den = codec_.maxFramerate;

	pFrameYUV = av_frame_alloc(); // 初始化的时候AVFrame中的元素data,linesize均为空。未指向任何内存数据，必须指向一块内存
	uint8_t * out_buffer = (uint8_t *)av_malloc(avpicture_get_size(AV_PIX_FMT_YUV420P, codec_.width, codec_.height));
	avpicture_fill((AVPicture *)pFrameYUV, out_buffer, AV_PIX_FMT_YUV420P, codec_.width, codec_.height);	

	if(avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
   		WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "open h264 encoder failed"); 
		return WEBRTC_VIDEO_CODEC_ERROR;
	}	

	av_init_packet(&enc_pkt);	
    WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "H264Decoder InitDecode success, width:%d, height:%d", codec_.width, codec_.height); 
	inited_ = true;
	return WEBRTC_VIDEO_CODEC_OK;
}

int H264DecoderImpl::Decode(const EncodedImage & input_image, bool missing_frames, const RTPFragmentationHeader * fragmentation, const CodecSpecificInfo * codec_specific_info, int64_t)
{
	if (!inited_) {
		WEBRTC_TRACE(webrtc::kTraceError, webrtc::kTraceVideoCoding, -1,
			"H264DecoderImpl::Decode, decoder is not initialized");
		return WEBRTC_VIDEO_CODEC_UNINITIALIZED;
	}

	if (decode_complete_callback_ == NULL) {
		WEBRTC_TRACE(webrtc::kTraceError, webrtc::kTraceVideoCoding, -1,
			"H264DecoderImpl::Decode, decode complete call back is not set");
		return WEBRTC_VIDEO_CODEC_UNINITIALIZED;
	}

	if (input_image._buffer == NULL) {
		WEBRTC_TRACE(webrtc::kTraceError, webrtc::kTraceVideoCoding, -1,
			"H264DecoderImpl::Decode, null buffer");
		return WEBRTC_VIDEO_CODEC_ERR_PARAMETER;
	}
	if (!codec_specific_info) {
		WEBRTC_TRACE(webrtc::kTraceError, webrtc::kTraceVideoCoding, -1,
			"H264EncoderImpl::Decode, no codec info");
		return WEBRTC_VIDEO_CODEC_ERROR;
	}
	if (codec_specific_info->codecType != kVideoCodecH264) {
		WEBRTC_TRACE(webrtc::kTraceError, webrtc::kTraceVideoCoding, -1,
			"H264EncoderImpl::Decode, non h264 codec %d", codec_specific_info->codecType);
		return WEBRTC_VIDEO_CODEC_ERROR;
	}

	int got_picture = 0;

	enc_pkt.data = input_image._buffer;
	enc_pkt.size = input_image._length;
	
	int ret = avcodec_decode_video2(pCodecCtx, pFrameYUV, &got_picture, &enc_pkt);
	if(got_picture < 0)
	{
   		WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "decode h264 data failed"); 
		return WEBRTC_VIDEO_CODEC_ERROR;		
	}

	int size_y = pFrameYUV->linesize[0] * pCodecCtx->height;
	int size_u = pFrameYUV->linesize[1] * pCodecCtx->height / 2;
	int size_v = pFrameYUV->linesize[2] * pCodecCtx->height / 2;
	decoded_image_.set_timestamp(input_image._timeStamp);  
	decoded_image_.CreateFrame(size_y, pFrameYUV->data[0], size_u, pFrameYUV->data[1], size_v, pFrameYUV->data[2], pCodecCtx->width, pCodecCtx->height, pFrameYUV->linesize[0], pFrameYUV->linesize[1], pFrameYUV->linesize[2]);
	decode_complete_callback_->Decoded(decoded_image_);
/*
	static int count = 0;
	if(count++<50)
	{
		fwrite(pFrameYUV->data[0], 1, size_y, fp);
		fwrite(pFrameYUV->data[1], 1, size_u, fp);
		fwrite(pFrameYUV->data[2], 1, size_v, fp);
	}
	else
	{
		fclose(fp);
	}
*/	
//    WEBRTC_TRACE(kTraceDebug, kTraceVideoCoding, -1, "H264Decoder Decode success, linesize[0]: %d, linesize[1]: %d, linesize[2]: %d",pFrameYUV->linesize[0],pFrameYUV->linesize[1],pFrameYUV->linesize[2] ); 
	return WEBRTC_VIDEO_CODEC_OK;
}

int H264DecoderImpl::RegisterDecodeCompleteCallback(DecodedImageCallback * callback)
{
 	decode_complete_callback_ = callback;
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


