#ifndef XAUDIOTHREAD
#define XAUDIOTHREAD

#pragma once
#include <QThread>
#include <mutex>
#include <list>
struct AVCodecParameters;
class XAudioPlay;
class XResample;
#include "XDecodeThread.h"
extern "C" {
#include <libavcodec/avcodec.h>
}
class XAudioThread:public XDecodeThread
{
public:
	//当前音频播放的pts
	long long pts = 0;
	//打开，不管成功与否都清理
	virtual bool Open(AVCodecParameters *para,int sampleRate,int channels);

	bool init(AVCodecID codeID, int format, int sampleRate, int channels);

	//停止线程，清理资源
	virtual void Close();

	virtual void Clear();
	void run();

	//buf为需要调节音量的音频数据块首地址指针，size为长度，uRepeat为重复次数，通常设为1，vol为增益倍数,可以小于1  
	void RaiseVolume(char * buf, int size, int uRepeat, double vol);

	void setVolume(double vo);
	XAudioThread();
	virtual ~XAudioThread();
	void SetPause(bool isPause);
	bool isPause = false;
	unsigned char *pcm;// = new unsigned char[1024 * 1024 * 10];
protected:
	double volumeValue = 1.00;
	std::mutex amux;
	XAudioPlay *ap = 0;
	XResample *res = 0;

};

#endif

