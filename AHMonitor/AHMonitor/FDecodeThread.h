#ifndef _FDECODE_THREAD_H_
#define _FDECODE_THREAD_H_
#pragma once

#include "HeadFile.h"
#include "qthread.h"
#include <QImage>
#include <QMutex>

class  AVCodec;
class AVCodecContext;
class AVFrame;

class FDecodeThread :
	public QThread
{
	Q_OBJECT
public:
	FDecodeThread(QObject *parent = 0);
	virtual ~FDecodeThread();

private:
	BOOL _av_register = FALSE;
	int  AlgorithmFlag;

	BOOL _init = FALSE;
	AVCodec * _pH264VideoDecoder = NULL;
	AVCodecContext *_pCodecContext = NULL;
	AVFrame *_pFrameYuv = NULL;
	struct SwsContext   *_img_convert_ctx = NULL;

	int _rgbWidth = 0;
	int _rgbHeight = 0;
	int _out_rgb_buffer_len = 0;
	int _dst_linesize[4];
	uint8_t *_dst_dataTmp[4];

	QMutex mutex;
	QList<MP_DATA_INFO *> pkts;
public:
	BOOL Init();

	void putpacket(MP_DATA_INFO *p);

	MP_DATA_INFO *getpacket();

	void freepacket(MP_DATA_INFO *p);

	INT32 PutVideoStream(char* buffer, INT32 bufferLen);

	INT32 SetAlgorithm(INT32 flag);
	INT32 GetVideoParam(INT32& width, INT32& height);
	INT32 GetVideoFrameSize();
	INT32 GetVideoFrameFormate();

	INT32 GetNextVideoFrame(char* buffer, INT32 bufferLen, INT32 yuFormate);

	INT32 GetVideoFrameCurSize_Rgb();
	INT32 GetNextVideoFrame_Rgb(char* buffer, INT32 bufferLen);

	INT32 GetVideoFrameSize_Rgb2(INT32 width, INT32 height);
	INT32 GetNextVideoFrame_Rgb(char* buffer, INT32 bufferLen, INT32 width, INT32 height);

	bool ResetRgbScale(INT32 width, INT32 height);

	void getVideoResolution(int nResolution, int * width, int * height);

protected:
	volatile bool stopped;          //线程停止标志位
	volatile bool isPlay;           //播放视频标志位

	void run();
public:
	void play();

	void stop();
signals:
	//收到图片信号
	void receiveImage(const QImage &image);
};

#endif