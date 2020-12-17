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
	//��ǰ��Ƶ���ŵ�pts
	long long pts = 0;
	//�򿪣����ܳɹ��������
	virtual bool Open(AVCodecParameters *para,int sampleRate,int channels);

	bool init(AVCodecID codeID, int format, int sampleRate, int channels);

	//ֹͣ�̣߳�������Դ
	virtual void Close();

	virtual void Clear();
	void run();

	//bufΪ��Ҫ������������Ƶ���ݿ��׵�ַָ�룬sizeΪ���ȣ�uRepeatΪ�ظ�������ͨ����Ϊ1��volΪ���汶��,����С��1  
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

