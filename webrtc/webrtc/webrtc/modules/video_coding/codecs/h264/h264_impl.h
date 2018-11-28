#ifndef WEBRTC_MODULES_VIDEO_CODING_CODECS_H264_IMPL_H_
#define WEBRTC_MODULES_VIDEO_CODING_CODECS_H264_IMPL_H_

#include "webrtc/modules/video_coding/codecs/h264/include/h264.h"

extern "C"{
	#include "libavcodec/avcodec.h"
	#include "libavformat/avformat.h"
	#include "libavutil/opt.h"
	#include "libswscale/swscale.h"
}
namespace webrtc {

class H264EncoderImpl : public H264Encoder {
	public:
		H264EncoderImpl();
		virtual  ~H264EncoderImpl();
	    virtual int Release();
	    virtual int InitEncode(const VideoCodec* codec_settings, int number_of_cores, size_t max_payload_size);
	    virtual int Encode(const I420VideoFrame& input_image, const CodecSpecificInfo* codec_specific_info, const std::vector<VideoFrameType>* frame_types);
	    virtual int RegisterEncodeCompleteCallback(EncodedImageCallback* callback);
	    virtual int SetChannelParameters(uint32_t packet_loss, int64_t rtt);
	    virtual int SetRates(uint32_t new_bitrate_kbit, uint32_t frame_rate);

	private:
		int UpdateCodecFrameSize(const I420VideoFrame& input_image);
		EncodedImage encoded_image_;
		EncodedImageCallback* encoded_complete_callback_;

		VideoCodec codec_;
		bool inited_;

// ffmpeg avcodec
		AVCodec* pCodec;
		AVCodecContext* pCodecCtx;
		AVPacket enc_pkt;
		AVFrame *pFrameYUV;
		
};

class H264DecoderImpl : public H264Decoder {
 public:
	  H264DecoderImpl();
	  ~H264DecoderImpl();

	  int InitDecode(const VideoCodec* inst, int number_of_cores);

	  int Decode(const EncodedImage& input_image,
	                     bool missing_frames,
	                     const RTPFragmentationHeader* fragmentation,
	                     const CodecSpecificInfo* codec_specific_info,
	                     int64_t /*render_time_ms*/);

	  int RegisterDecodeCompleteCallback(DecodedImageCallback* callback);

	  int Release();

	  int Reset();

	  VideoDecoder* Copy();

	private:
	  // Copy reference image from this _decoder to the _decoder in copyTo. Set
	  // which frame type to copy in _refFrame->frame_type before the call to
	  // this function.
	  int CopyReference(H264DecoderImpl* copy);

	  int DecodePartitions(const EncodedImage& input_image,
	                       const RTPFragmentationHeader* fragmentation);

	  int ReturnFrame(const void* img,
	                  uint32_t timeStamp,
	                  int64_t ntp_time_ms);

	  I420VideoFrame decoded_image_;
	  DecodedImageCallback* decode_complete_callback_;
	  bool inited_;
  	  VideoCodec codec_;	  
	  bool feedback_mode_;

// ffmpeg avcodec
		AVCodec* pCodec;
		AVCodecContext* pCodecCtx;
		AVPacket enc_pkt;
		AVFrame *pFrameYUV;	  

};  // end of H264DecoderImpl class

}

#endif  // WEBRTC_MODULES_VIDEO_CODING_CODECS_H264_IMPL_H_
