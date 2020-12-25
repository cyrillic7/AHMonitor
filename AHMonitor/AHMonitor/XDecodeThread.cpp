#include "XDecodeThread.h"
#include "XDecode.h"
#include <iostream>
using namespace std;
//������Դ��ֹͣ�߳�
void XDecodeThread::Close()
{
	Clear();
	
	//�ȴ��߳��˳�
	isExit = true;
	wait();
	decode->Close();

	mux.lock();
	delete decode;
	decode = NULL;
	mux.unlock();
}
void XDecodeThread::Clear()
{
	mux.lock();
	decode->Clear();
	while (!packs.empty())
	{
		AVPacket *pkt = packs.front();
		XFreePacket(&pkt);
		packs.pop_front();
	}

	mux.unlock();
}


//ȡ��һ֡���ݣ�����ջ�����û�з���NULL
AVPacket *XDecodeThread::Pop()
{
	mux.lock();
	if (packs.empty())
	{
		mux.unlock();
		return NULL;
	}
	AVPacket *pkt = packs.front();
	packs.pop_front();
	mux.unlock();
	//msleep(1);
	return pkt;
}
void XDecodeThread::Push(AVPacket *pkt)
{
	if (!pkt)return;
	//����
	while (!isExit)
	{
		//cout << "packs.size:" << packs.size() << endl;
		mux.lock();
		if (packs.size() < maxList)
		{
			if (packs.size() > 0)
			{
				cout << "packs.size:" << packs.size() << endl;
			}
			packs.push_back(pkt);
			mux.unlock();
			//return;
			break;
		}
		
		//if (pkt->flags != AV_PKT_FLAG_KEY /*&& pkt->flags != AV_PKT_FLAG_CORRUPT*/)
		//{
		//	//packs.pop_front();
		//	//packs.push_back(pkt);
		//	//cout << "packs.sizesssssssssssssssssssssssss:" << packs.size() << endl;
		//	//AVPacket *pkts = packs.front();
		//	//if (pkts->flags != AV_PKT_FLAG_KEY/* && pkt->flags != AV_PKT_FLAG_CORRUPT*/)
		//	//{
		//	//	packs.pop_front();
		//	//	packs.push_back(pkt);
		//	//	//mux.unlock();
		//	//	//break;
		//	//}
		//	//else
		//	//{
		//	//	//packs.pop_back();
		//	//	//packs.push_back(pkt);
		//	//}
		//	//mux.unlock();
		//	//break;
		//}
		/*AVPacket *pkt = packs.front();
		packs.pop_front();*/

		mux.unlock();
		msleep(1);
	}
}


XDecodeThread::XDecodeThread()
{
	//�򿪽�����
	if (!decode) decode = new XDecode();
}


XDecodeThread::~XDecodeThread()
{	//�ȴ��߳��˳�
	isExit = true;
	wait();
}
