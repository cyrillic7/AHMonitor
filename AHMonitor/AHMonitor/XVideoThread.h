#ifndef XVIDEOTHREAD
#define XVIDEOTHREAD

///�������ʾ��Ƶ
struct AVPacket;
struct AVCodecParameters;
struct AVStream;
struct AVFormatContext;
class XDecode;
#include <list>
#include <mutex>
#include <QThread>
#include "IVideoCall.h"
#include "XDecodeThread.h"
extern "C" {
#include <libavcodec/avcodec.h>
}
class XVideoThread:public XDecodeThread
{
public:

	//����pts��������յ��Ľ�������pts >= seekpts return true ������ʾ����
	virtual bool RepaintPts(AVPacket *pkt, long long seekpts);
	//�򿪣����ܳɹ��������
	virtual bool Open(AVCodecParameters *para,IVideoCall *call,int width,int height);
	virtual bool init(AVCodecID codeID, void *call, int width, int height);
	void run();
	XVideoThread();
	virtual ~XVideoThread();
	//ͬ��ʱ�䣬���ⲿ����
	long long synpts = 0;

	void SetPause(bool isPause);
	bool isPause = false;

	bool initOStream(const char* ofile, AVStream * iStream);
	void setisRecord(bool record);
	bool isRecord = false;
protected:
	IVideoCall *call = 0;
	std::mutex vmux;

	const char* ot_file_path = NULL;

	AVFormatContext *o_fmt_ctx = NULL;
	AVStream *o_video_stream = NULL;

};

#endif
