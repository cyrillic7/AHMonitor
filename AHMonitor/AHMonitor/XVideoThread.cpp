#include "XVideoThread.h"
#include "XDecode.h"
#include <iostream>
extern "C" {
#include <libavformat/avformat.h>
}
using namespace std;
static double r2d(AVRational r)
{
	return r.den == 0 ? 0 : (double)r.num / (double)r.den;
}
//打开，不管成功与否都清理
bool XVideoThread::Open(AVCodecParameters *para, IVideoCall *call,int width,int height)
{
	if (!para)return false;
	Clear();

	vmux.lock();
	synpts = 0;
	//初始化显示窗口
	this->call = call;
	if (call)
	{
		call->Init(width, height);
	}
	vmux.unlock();
	int re = true;
	//para->codec_id = AV_CODEC_ID_HEVC;
	if (!decode->Open(para))
	{
		cout << "audio XDecode open failed!" << endl;
		re = false;
	}
	
	cout << "XAudioThread::Open :" << re << endl;
	return re;
}
bool XVideoThread::init(AVCodecID codeID, IVideoCall *call, int width, int height)
{
	vmux.lock();
	synpts = 0;
	//初始化显示窗口
	this->call = (IVideoCall *)call;
	if (call)
	{
		this->call->Init(width, height);
	}
	vmux.unlock();
	int re = true;
	if (!decode->init(codeID,0,0))
	{
		cout << "video XDecode init failed!" << endl;
		re = false;
	}

	cout << "XVideoThread::init :" << re << endl;
	return re;
}
bool XVideoThread::initOStream(const char* ofile, AVStream * iStream)
{
	vmux.lock();
	// 初始化一个用于输出的AVFormatContext结构体
	if (avformat_alloc_output_context2(&o_fmt_ctx, NULL, NULL, ofile) < 0)
	{
		vmux.unlock();
		return false;
	}

	o_video_stream = avformat_new_stream(o_fmt_ctx, NULL);

	AVCodecContext *c;
	//avcodec_copy_context(o_video_stream->codec, iStream->codec);
	avcodec_parameters_from_context(o_video_stream->codecpar, iStream->codec);
	o_video_stream->time_base.num = iStream->time_base.num;
	o_video_stream->time_base.den = iStream->time_base.den;
	c = o_video_stream->codec;
	//c = o_video_stream->codec;
	c->bit_rate = 400000;
	c->codec_id = iStream->codec->codec_id;
	c->codec_type = iStream->codec->codec_type;
	c->time_base.num = iStream->time_base.num;
	c->time_base.den = iStream->time_base.den;
	fprintf(stderr, "time_base.num = %d time_base.den = %d\n", c->time_base.num, c->time_base.den);
	cout << "time_base.num :" << c->time_base.num << "time_base.den :" << c->time_base.den << endl;
	c->width = iStream->codec->width;
	c->height = iStream->codec->height;
	c->pix_fmt = iStream->codec->pix_fmt;
	printf("%d %d %d", c->width, c->height, c->pix_fmt);
	cout << "c->width:" << c->width << "c->height:" << c->height << "c->pix_fmt:" << c->pix_fmt << endl;

	c->flags = iStream->codec->flags;
	c->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;// CODEC_FLAG_GLOBAL_HEADER;
	c->me_range = iStream->codec->me_range;
	c->max_qdiff = iStream->codec->max_qdiff;

	c->qmin = iStream->codec->qmin;
	c->qmax = iStream->codec->qmax;

	c->qcompress = iStream->codec->qcompress;

	int ret = avio_open(&o_fmt_ctx->pb, ofile, AVIO_FLAG_WRITE);
	if (ret < 0)
	{
		cout << "avio_open failed!" << endl;
	}

	ret = avformat_write_header(o_fmt_ctx, NULL);
	if (ret != AVSTREAM_INIT_IN_WRITE_HEADER)
	{
		cout << "avformat_write_header failed!" << endl;
	}
	vmux.unlock();
	return true;
}
void XVideoThread::SetPause(bool isPause)
{
	vmux.lock();
	this->isPause = isPause;
	vmux.unlock();
}

void XVideoThread::setisRecord(bool record)
{
	vmux.lock();
	this->isRecord = record;
	vmux.unlock();
}
void XVideoThread::run()
{
	while (!isExit)
	{
		vmux.lock();
		if (this->isPause)
		{
			vmux.unlock();
			msleep(5);
			continue;
		}
		//cout << "synpts = " << synpts << " dpts =" << decode->pts << endl;
		//音视频同步
		/*if (synpts > 0 && synpts < decode->pts)
		{
			vmux.unlock();
			msleep(1);
			continue;
		}*/
		AVPacket *pkt = Pop();
		/*	AVPacket *Recordpkt = av_packet_alloc();
			av_init_packet(Recordpkt);
			if (pkt)
			{
				av_copy_packet(Recordpkt, pkt);
			}*/
		
		bool re = decode->Send(pkt);
		
		if (!re)
		{
			vmux.unlock();
			msleep(1);
			continue;
		}
		//一次send 多次recv
		while (!isExit)
		{
			AVFrame * frame = decode->Recv();
			if (!frame)break;
// 			if (frame->pict_type == AV_PICTURE_TYPE_I)
// 			{
// 				//cout << "frame->pict_type:" << frame->pict_type << endl;
// 				//break;
// 			}
// 			if (frame->pict_type == AV_PICTURE_TYPE_P)
// 			{
// 				//cout << "frame->pict_type:" << frame->pict_type << endl;
// 				//break;
// 			}
// 			if (frame->pict_type != AV_PICTURE_TYPE_I && frame->pict_type != AV_PICTURE_TYPE_P)
// 			{
// 				
// 				cout << "frame->pict_type:" << frame->pict_type << endl;
// 				//break;
// 			}
// 			if (frame->pict_type == AV_PICTURE_TYPE_B)
// 			{
// 				cout << "frame->pict_type:" << frame->pict_type << endl;
// 			}
			//显示视频
			if (call)
			{
				//emit RepatintImage(frame);
				this->call->Repaint(frame);
				//cout << "XVideoThread::Repaint :" << isExit << endl;
			}

		}
		vmux.unlock();
		//msleep(10);
	}
}
//解码pts，如果接收到的解码数据pts >= seekpts return true 并且显示画面
bool XVideoThread::RepaintPts(AVPacket *pkt, long long seekpts)
{
	vmux.lock();
	bool re = decode->Send(pkt);
	if (!re)
	{
		vmux.unlock();
		return true; //表示结束解码
	}
	AVFrame *frame = decode->Recv();
	if (!frame)
	{
		vmux.unlock();
		return false;
	}
	//到达位置
	if (decode->pts >= seekpts)
	{
		if(call)
			call->Repaint(frame);
		vmux.unlock();
		return true;
	}
	XFreeFrame(&frame);
	vmux.unlock();
	return false;
}
XVideoThread::XVideoThread()
{
}


XVideoThread::~XVideoThread()
{
	isExit = true;
	wait();
}
