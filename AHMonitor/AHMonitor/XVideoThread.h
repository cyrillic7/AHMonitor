#ifndef XVIDEOTHREAD
#define XVIDEOTHREAD

///解码和显示视频
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
	Q_OBJECT
public:

	//解码pts，如果接收到的解码数据pts >= seekpts return true 并且显示画面
	virtual bool RepaintPts(AVPacket *pkt, long long seekpts);
	//打开，不管成功与否都清理
	virtual bool Open(AVCodecParameters *para,IVideoCall *call,int width,int height);
	virtual bool init(AVCodecID codeID, IVideoCall *call, int width, int height);
	void run();
	XVideoThread();
	virtual ~XVideoThread();
	//同步时间，由外部传入
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


 signals:
 	//收到图片信号
 	void RepatintImage(AVFrame *frame);
};

#endif
