#include "XDecodeThread.h"
#include "XDecode.h"
#include <iostream>
using namespace std;
//清理资源，停止线程
void XDecodeThread::Close()
{
	Clear();
	
	//等待线程退出
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


//取出一帧数据，并出栈，如果没有返回NULL
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
	//阻塞
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
	//打开解码器
	if (!decode) decode = new XDecode();
}


XDecodeThread::~XDecodeThread()
{	//等待线程退出
	isExit = true;
	wait();
}
