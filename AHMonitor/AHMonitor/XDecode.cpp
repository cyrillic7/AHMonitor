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
bool XDecode::init(AVCodecID codeID)
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

		codec->codec_id = AV_CODEC_ID_H265;
		codec->flags |= AV_CODEC_FLAG_LOW_DELAY;
		codec->time_base.num = 1;
		codec->time_base.den = 25;//֡��
		codec->frame_number = 1; //ÿ��һ����Ƶ֡  
		codec->codec_type = AVMEDIA_TYPE_VIDEO;
		codec->bit_rate = 400000;
		//_pCodecContext->bit_rate_tolerance = 4000000;  
						
		codec->width = 0;//��Ƶ��  
		codec->height = 0;//��Ƶ�� 
		codec->pix_fmt = AV_PIX_FMT_YUV420P;
		codec->color_range = AVCOL_RANGE_MPEG;
		codec->max_b_frames = 0;
		codec->thread_count = 8;
		//���߳̽���
		//codec->codec_id = AV_CODEC_ID_H265;
		//codec->flags |= AV_CODEC_FLAG_LOW_DELAY;
		//codec->time_base.num = 1;
		//codec->frame_number = 1; //ÿ��һ����Ƶ֡  
		//codec->codec_type = AVMEDIA_TYPE_VIDEO;
		//codec->bit_rate = 400000;
		////_pCodecContext->bit_rate_tolerance = 4000000;
		//codec->time_base.den = 25;//֡��  
		//								   //_pCodecContext->time_base = {1,25};
		//codec->width = 0;//��Ƶ��  
		//codec->height = 0;//��Ƶ�� 
		//codec->pix_fmt = AV_PIX_FMT_YUV420P;
		//codec->color_range = AVCOL_RANGE_MPEG;
		//codec->max_b_frames = 0;

		//codec->thread_count = 8;
		//codec->lowres = vcodec->max_lowres;
		//codec->flags2 |= AV_CODEC_FLAG2_FAST;
		/*codec->sample_aspect_ratio.num = 4;
		codec->sample_aspect_ratio.den = 3;*/
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
