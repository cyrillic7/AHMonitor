#include "XDecode.h"
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavformat/avformat.h"
#include "libavutil/dict.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
};
#include <iostream>
using namespace std;

void XFreePacket(AVPacket **pkt)
{
	if (!pkt || !(*pkt))return;
	av_packet_free(pkt);
}
void XFreeFrame(AVFrame **frame)
{
	if (!frame || !(*frame))return;
	av_frame_free(frame);
}
void XDecode::Close()
{
	mux.lock();
	if (codec)
	{
		avcodec_close(codec);
		avcodec_free_context(&codec);
	}
	pts = 0;
	mux.unlock();
}

void XDecode::Clear()
{
	mux.lock();
	//清理解码缓冲
	if (codec)
		avcodec_flush_buffers(codec);

	mux.unlock();
}

//打开解码器
bool XDecode::Open(AVCodecParameters *para)
{
	if (!para) return false;
	Close();
	//////////////////////////////////////////////////////////
	///解码器打开
	///找到解码器
	AVCodec *vcodec = avcodec_find_decoder(para->codec_id);
	if (!vcodec)
	{
		avcodec_parameters_free(&para);
		cout << "can't find the codec id " << para->codec_id << endl;
		return false;
	}
	cout << "find the AVCodec " << para->codec_id << endl;

	mux.lock();
	codec = avcodec_alloc_context3(vcodec);

	//AVCodecParserContext *pCodecParserCtx = av_parser_init(para->codec_id);  //初始化AVCodecParserContext。
	//if (!pCodecParserCtx) {
	//	printf("Could not allocate video parser context\n");
	//	return false;
	//}
	///配置解码器上下文参数
	avcodec_parameters_to_context(codec, para);
	avcodec_parameters_free(&para);

	//八线程解码
	codec->thread_count = 8;
	codec->lowres = vcodec->max_lowres;
	codec->flags2 |= AV_CODEC_FLAG2_FAST;
	codec->sample_aspect_ratio.num = 4;
	codec->sample_aspect_ratio.den = 3;
	///打开解码器上下文
	int re = avcodec_open2(codec, vcodec, 0);
	if (re != 0)
	{
		avcodec_free_context(&codec);
		mux.unlock();
		char buf[1024] = { 0 };
		av_strerror(re, buf, sizeof(buf) - 1);
		cout << "avcodec_open2  failed! :" << buf << endl;
		return false;
	}
	mux.unlock();
	cout << " avcodec_open2 success!" << endl;
	return true;
}
bool XDecode::init(AVCodecID codeID, int sampleRate, int channels)
{

	switch (codeID)
	{
	case AV_CODEC_ID_H265:
	{
		AVCodec *vcodec = avcodec_find_decoder(codeID);
		if (!vcodec)
		{
			//avcodec_parameters_free(&para);
			cout << "can't find the codec id " << codeID << endl;
			return false;
		}
		cout << "find the AVCodec " << codeID << endl;

		mux.lock();
		codec = avcodec_alloc_context3(NULL);

		//codec->global_quality = 2;
		// VBR
		//codec->flags |= CODEC_FLAG_QSCALE;
		//codec->rc_min_rate = 850000 - 400000;
		//codec->rc_max_rate = 850000 + 400000;
		codec->bit_rate = 800000;
		codec->bit_rate_tolerance = 400000;
		codec->rc_buffer_size = 800000;
		//codec->rc_initial_buffer_occupancy = codec->rc_buffer_size * 3 / 4;
		//codec->rc_buffer_aggressivity = (float)1.0;
		//codec->rc_initial_cplx = 0.5;
		//codec->spatial_cplx_masking = 1.0;
		//codec->rc_buffer_aggressivity = 1.0

		codec->codec_id = AV_CODEC_ID_H265;
		codec->flags |= AV_CODEC_FLAG_PASS2 | AV_CODEC_FLAG_LOW_DELAY;
		codec->time_base.num = 1;
		codec->time_base.den = 25;//帧率
		codec->frame_number = 1; //每包一个视频帧  
		codec->codec_type = AVMEDIA_TYPE_VIDEO;
		//codec->bit_rate = 800000;
		codec->gop_size = 1000;
		//codec->refs = 5;
		//codec->slices = 5;
		//codec->pre_me = 2;
		codec->width = 0;//视频宽  
		codec->height = 0;//视频高 
		codec->pix_fmt = AV_PIX_FMT_YUV420P;
		codec->color_range = AVCOL_RANGE_MPEG;
		codec->max_b_frames = 0;
		//codec->has_b_frames = 0;
		codec->keyint_min = 1;
		codec->scenechange_threshold = 0;
		codec->thread_count = 8;		//八线程解码
		codec->lowres = vcodec->max_lowres;
		codec->flags2 |=  AV_CODEC_FLAG2_FAST ;
		codec->sample_aspect_ratio.num = 4;
		codec->sample_aspect_ratio.den = 3;

		codec->profile = FF_PROFILE_HEVC_MAIN;
		codec->qmin = 2;
		codec->qmax = 51;
		//codec->qcompress = 0.5;

		AVDictionary *param = 0;
		av_dict_set(&param, "x265-params", "qp=20", 0);
		av_dict_set(&param, "preset", "ultrafast", 0);
		av_dict_set(&param, "tune", "zerolatency", 0);
		//av_dict_set(&param, "qmin", "0", 0);
		//av_dict_set(&param, "qmax", "69", 0);
		//av_dict_set(&param, "qdiff", "4", 0);
		av_dict_set(&param, "rtsp_transport", "tcp", 0); //以tcp的方式传送
		av_dict_set(&param, "fflags", "nobuffer", 0);
		//av_dict_set(&param, "preset", "fast", 0); // av_opt_set(pCodecCtx->priv_data,"preset","fast",0);
		//av_dict_set(&param, "tune", "zerolatency", 0);
		av_dict_set(&param, "probesize", "4096", 0);
		av_dict_set(&param, "buffer_size", "1024000", 0);//设置缓存大小，1080p可将值调大，比如1MB; 524288=512KB  1048576=1MB
		av_dict_set(&param, "max_delay", "300", 0);
							 //av_dict_set(&param, "max_delay", "5000000", 0);
		//av_dict_set(&param, "profile", "main", 0);
		//av_dict_set_int(&param, "qscale", 15, 0);
		av_dict_set_int(&param, "threads", 8, 0);
		///打开解码器上下文
		int re = avcodec_open2(codec, vcodec, &param);
		if (re != 0)
		{
			avcodec_free_context(&codec);
			mux.unlock();
			char buf[1024] = { 0 };
			av_strerror(re, buf, sizeof(buf) - 1);
			cout << "avcodec_open2  failed! :" << buf << endl;
			return false;
		}
		mux.unlock();
		cout << " avcodec_open2 success!" << endl;
	}
	break;
	case AV_CODEC_ID_AAC:
	{
		AVCodec *vcodec = avcodec_find_decoder(codeID);
		if (!vcodec)
		{
			//avcodec_parameters_free(&para);
			cout << "can't find the codec id " << codeID << endl;
			return false;
		}
		cout << "find the AVCodec " << codeID << endl;

		mux.lock();
		codec = avcodec_alloc_context3(NULL);

		codec->codec_id = AV_CODEC_ID_AAC;
		codec->flags |= AV_CODEC_FLAG_LOW_DELAY;
		codec->time_base.num = 1;
		codec->time_base.den = 25;//帧率
		//codec->frame_number = 1; //每包一个视频帧  
		codec->codec_type = AVMEDIA_TYPE_AUDIO;
		codec->bit_rate = 80000;

		codec->sample_rate = 44100;
		codec->sample_fmt = AV_SAMPLE_FMT_S16;
		codec->sample_rate = sampleRate;
		codec->channels = channels;		  
		codec->channel_layout = AV_CH_LAYOUT_STEREO;		//输入音频的channel layout

		codec->thread_count = 8;		//八线程解码
		/*codec->lowres = vcodec->max_lowres;
		codec->flags2 |= AV_CODEC_FLAG2_FAST;
		codec->sample_aspect_ratio.num = 4;
		codec->sample_aspect_ratio.den = 3;
		codec->sample_rate = sampleRate;
		codec->channels = channels;*/

		codec->profile = FF_PROFILE_AAC_MAIN;
		/*codec->qmin = 10;
		codec->qmax = 51;*/

		AVDictionary *param = 0;
		//av_dict_set(&param, "fflags", "nobuffer", 0);
		av_dict_set(&param, "preset", "ultrafast", 0); // av_opt_set(pCodecCtx->priv_data,"preset","fast",0);
		av_dict_set(&param, "tune", "zero-latency", 0);
		//av_dict_set(&param, "probesize", "4096", 0);
		//av_dict_set(&param, "buffer_size", "8192000", 0);//设置缓存大小，1080p可将值调大，比如1MB; 524288=512KB  1048576=1MB
		//av_dict_set(&param, "max_delay", "300", 0);
		//av_dict_set(&param, "max_delay", "5000000", 0);
		//av_dict_set(&param, "profile", "main", 0);
		//av_dict_set_int(&param, "qscale", 15, 0);
		av_dict_set_int(&param, "threads", 8, 0);
		///打开解码器上下文
		int re = avcodec_open2(codec, vcodec, &param);
		if (re != 0)
		{
			avcodec_free_context(&codec);
			mux.unlock();
			char buf[1024] = { 0 };
			av_strerror(re, buf, sizeof(buf) - 1);
			cout << "avcodec_open2  failed! :" << buf << endl;
			return false;
		}
		mux.unlock();
		cout << " avcodec_open2 success!" << endl;
	}
	break;
	}
	return true;
}
//发送到解码线程，不管成功与否都释放pkt空间（对象和媒体内容）
bool XDecode::Send(AVPacket *pkt)
{
	
	//容错处理
	if (!pkt || pkt->size <= 0 || !pkt->data)
	{
		av_packet_free(&pkt);
		return false;
	}
	mux.lock();
	if (!codec)
	{
		mux.unlock();
		av_packet_free(&pkt);
		return false;
	}
	int re = avcodec_send_packet(codec, pkt);
	mux.unlock();
	av_packet_free(&pkt);
	if (re != 0)return false;
	return true;
}

//获取解码数据，一次send可能需要多次Recv，获取缓冲中的数据Send NULL在Recv多次
//每次复制一份，由调用者释放 av_frame_free
AVFrame* XDecode::Recv()
{
	mux.lock();
	if (!codec)
	{
		mux.unlock();
		return NULL;
	}
	AVFrame *frame = av_frame_alloc();
	//frame->top_field_first = 1;
	//frame->interlaced_frame = 1;
	int re = avcodec_receive_frame(codec, frame);
	mux.unlock();
	if (re != 0)
	{
		av_frame_free(&frame);
		return NULL;
	}
	//cout << "["<<frame->linesize[0] << "] " << flush;
	pts = frame->pts;
	return frame;
}

XDecode::XDecode()
{
}


XDecode::~XDecode()
{
}
