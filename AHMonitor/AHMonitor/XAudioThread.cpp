#include "XAudioThread.h"
#include "XDecode.h"
#include "XAudioPlay.h"
#include "XResample.h"
#include <iostream>
#include <Windows.h> 
using namespace std;

void XAudioThread::Clear()
{
	XDecodeThread::Clear();
	mux.lock();
	if (ap) ap->Clear();
	mux.unlock();
}
//停止线程，清理资源
void XAudioThread::Close()
{
	XDecodeThread::Close();
	if (res)
	{
		res->Close();
		amux.lock();
		delete res;
		res = NULL;
		amux.unlock();
	}
	if (ap)
	{
		ap->Close();
		amux.lock();
		ap = NULL;
		amux.unlock();
	}
}
bool XAudioThread::Open(AVCodecParameters *para,int sampleRate, int channels)
{
	if (!para)return false;
	Clear();

	amux.lock();
	pts = 0;
	bool re = true;
	if (!res->Open(para, false))
	{
		cout << "XResample open failed!" << endl;
		re = false;
	}
	ap->sampleRate = sampleRate;
	ap->channels = channels;
	if (!ap->Open())
	{
		re = false;
		cout << "XAudioPlay open failed!" << endl;
	}
	if (!decode->Open(para))
	{
		cout << "audio XDecode open failed!" << endl;
		re = false;
	}
	amux.unlock();
	cout << "XAudioThread::Open :" << re << endl;
	return re;
}

void XAudioThread::SetPause(bool isPause)
{
	//amux.lock();
	this->isPause = isPause;
	if (ap)
		ap->SetPause(isPause);
	//amux.unlock();
}

void XAudioThread::run()
{
	unsigned char *pcm = new unsigned char[1024 * 1024 * 10];
	while (!isExit)
	{
		amux.lock();
		if (isPause)
		{
			amux.unlock();
			msleep(5);
			continue;
		}

		//没有数据
		//if (packs.empty() || !decode || !res || !ap)
		//{
		//	mux.unlock();
		//	msleep(1);
		//	continue;
		//}

		//AVPacket *pkt = packs.front();
		//packs.pop_front();
		AVPacket *pkt = Pop();
		bool re = decode->Send(pkt);
		if (!re)
		{
			amux.unlock();
			msleep(1);
			continue;
		}
		//一次send 多次recv
		while (!isExit)
		{
			AVFrame * frame = decode->Recv();
			if (!frame) break;

			//减去缓冲中未播放的时间
			pts = decode->pts - ap->GetNoPlayMs();

			//cout << "audio pts = " << pts << endl;

			//重采样 
			int size = res->Resample(frame, pcm);
			//播放音频
			while (!isExit)
			{
				if (size <= 0)break;
				//缓冲未播完，空间不够
				if (ap->GetFree() < size || isPause)
				{
					msleep(1);
					continue;
				}
				RaiseVolume((char*)pcm, size, 1, volumeValue);
				ap->Write(pcm, size);
				break;
			}
		}
		amux.unlock();
	}
	delete pcm;
}

void XAudioThread::RaiseVolume(char* buf, int size, int uRepeat, double vol)
{
	if (!size)
	{
		return;
	}
	for (int i = 0; i < size;)
	{
		signed long minData = -0x8000; //如果是8bit编码这里变成-0x80  
		signed long maxData = 0x7FFF;//如果是8bit编码这里变成0xFF  

		signed short wData = buf[i + 1];
		wData = MAKEWORD(buf[i], buf[i + 1]);
		signed long dwData = wData;

		for (int j = 0; j < uRepeat; j++)
		{
			dwData = dwData * vol;
			if (dwData < -0x8000)
			{
				dwData = -0x8000;
			}
			else if (dwData > 0x7FFF)
			{
				dwData = 0x7FFF;
			}
		}
		wData = LOWORD(dwData);
		buf[i] = LOBYTE(wData);
		buf[i + 1] = HIBYTE(wData);
		i += 2;
	}
}

void XAudioThread::setVolume(double vo)
{
	volumeValue = vo;
}

XAudioThread::XAudioThread()
{
	if (!res) res = new XResample();
	if (!ap) ap = XAudioPlay::Get();
}


XAudioThread::~XAudioThread()
{
	//等待线程退出
	isExit = true;
	wait();
}
