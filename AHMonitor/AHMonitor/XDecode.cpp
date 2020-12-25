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
	//������뻺��
	if (codec)
		avcodec_flush_buffers(codec);

	mux.unlock();
}

//�򿪽�����
bool XDecode::Open(AVCodecParameters *para)
{
	if (!para) return false;
	Close();
	//////////////////////////////////////////////////////////
	///��������
	///�ҵ�������
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

	//AVCodecParserContext *pCodecParserCtx = av_parser_init(para->codec_id);  //��ʼ��AVCodecParserContext��
	//if (!pCodecParserCtx) {
	//	printf("Could not allocate video parser context\n");
	//	return false;
	//}
	///���ý����������Ĳ���
	avcodec_parameters_to_context(codec, para);
	avcodec_parameters_free(&para);

	//���߳̽���
	codec->thread_count = 8;
	codec->lowres = vcodec->max_lowres;
	codec->flags2 |= AV_CODEC_FLAG2_FAST;
	codec->sample_aspect_ratio.num = 4;
	codec->sample_aspect_ratio.den = 3;
	///�򿪽�����������
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
		//sps/pps
		codec->profile = FF_PROFILE_HEVC_MAIN;
		codec->level = 30;//��ʾlevel��5.0
		//					   //�ֱ���
		codec->width = 0;
		codec->height = 0;
		////gop
		codec->gop_size = 60;//i֡���
		codec->keyint_min = 4;//������С�Զ�����i֡�ļ��.OPTION
		codec->scenechange_threshold = 0;
		//							//B֡
		codec->max_b_frames = 0;//��ҪB֡
		codec->has_b_frames = 0;//
		//							 //�ο�֡
		codec->refs = 60;//OPTION
		//					 //���������yuv��ʽ
		codec->pix_fmt = AV_PIX_FMT_YUV420P;
		//// VBR
		////codec->flags |= CODEC_FLAG_QSCALE;
		codec->rc_min_rate = 400000;
		codec->rc_max_rate = 1200000;
		codec->bit_rate = 800000;
		//codec->bit_rate_tolerance = 400000;

		codec->codec_id = AV_CODEC_ID_H265;
		codec->flags |= /*AV_CODEC_FLAG_QSCALE |*/ AV_CODEC_FLAG_LOW_DELAY;
		codec->time_base.num = 1;
		codec->time_base.den = 25;//֡��
		////codec->framerate.num = 1;
		////codec->framerate.den = 25;
		codec->frame_number = 1; //ÿ��һ����Ƶ֡  
		codec->codec_type = AVMEDIA_TYPE_VIDEO;
		codec->color_range = AVCOL_RANGE_MPEG;
		codec->thread_count = 8;		//���߳̽���
		codec->lowres = vcodec->max_lowres;
		codec->flags2 |=  AV_CODEC_FLAG2_FAST ;
		codec->sample_aspect_ratio.num = 4;
		codec->sample_aspect_ratio.den = 3;
		//codec->qmin = 1;
		//codec->qmax = 51;
		////codec->qcompress = 0.5;

		AVDictionary *param = 0;
		av_dict_set(&param, "x265-params", "qp=20", 0);
		av_dict_set(&param, "preset", "ultrafast", 0);
		av_dict_set(&param, "tune", "zerolatency", 0);
		//////av_dict_set(&param, "qmin", "0", 0);
		//////av_dict_set(&param, "qmax", "69", 0);
		//av_dict_set(&param, "qdiff", "4", 0);
		av_dict_set(&param, "rtsp_transport", "tcp", 0); //��tcp�ķ�ʽ����
		av_dict_set(&param, "fflags", "nobuffer", 0);
		av_dict_set(&param, "probesize", "4096", 0);
		av_dict_set(&param, "buffer_size", "2048000", 0);//���û����С��1080p�ɽ�ֵ���󣬱���1MB; 524288=512KB  1048576=1MB
		av_dict_set(&param, "max_delay", "300", 0);
		//////av_dict_set_int(&param, "qscale", 15, 0);
		av_dict_set_int(&param, "threads", 8, 0);
		///�򿪽�����������
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
		codec->flags |= /*AV_CODEC_FLAG_PASS2 |*/ AV_CODEC_FLAG_LOW_DELAY;
		codec->time_base.num = 1;
		codec->time_base.den = 25;//֡��
		//codec->frame_number = 1; //ÿ��һ����Ƶ֡  
		codec->codec_type = AVMEDIA_TYPE_AUDIO;
		codec->rc_min_rate = 400000;
		codec->rc_max_rate = 1200000;
		codec->bit_rate = 800000;

		codec->sample_rate = 44100;
		codec->sample_fmt = AV_SAMPLE_FMT_S16;
		codec->sample_rate = sampleRate;
		codec->channels = channels;		  
		codec->channel_layout = AV_CH_LAYOUT_STEREO;		//������Ƶ��channel layout

		codec->thread_count = 8;		//���߳̽���
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
		av_dict_set(&param, "tune", "zerolatency", 0);
		//av_dict_set(&param, "probesize", "4096", 0);
		//av_dict_set(&param, "buffer_size", "8192000", 0);//���û����С��1080p�ɽ�ֵ���󣬱���1MB; 524288=512KB  1048576=1MB
		//av_dict_set(&param, "max_delay", "300", 0);
		//av_dict_set(&param, "max_delay", "5000000", 0);
		//av_dict_set(&param, "profile", "main", 0);
		//av_dict_set_int(&param, "qscale", 15, 0);
		av_dict_set_int(&param, "threads", 8, 0);
		///�򿪽�����������
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
//���͵������̣߳����ܳɹ�����ͷ�pkt�ռ䣨�����ý�����ݣ�
bool XDecode::Send(AVPacket *pkt)
{
	
	//�ݴ���
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

//��ȡ�������ݣ�һ��send������Ҫ���Recv����ȡ�����е�����Send NULL��Recv���
//ÿ�θ���һ�ݣ��ɵ������ͷ� av_frame_free
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
