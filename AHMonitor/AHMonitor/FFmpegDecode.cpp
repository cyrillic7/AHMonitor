//#include "FFmpegDecode.h"
//
//
//FFmpegDecode* FFmpegDecode::m_Instance = NULL;
//FFmpegDecode::FFmpegDecode(QObject *parent) : QObject(parent)
//{
//	m_Instance = this;
//	_h264Handle = 0;
//	if (_h264Handle == 0)
//	{
//		_h264Handle = H264_CreateHandle();
//	}
//}
//
//
//FFmpegDecode::~FFmpegDecode()
//{
//}
//
//int FFmpegDecode::PackDecode(MP_DATA_INFO * pData)
//{
//	if (pData->type == MP_DATA_H264)   //视频数据，也可能是h265，
//	{
//		/*QDateTime current_date_time = QDateTime::currentDateTime();
//		QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz");*/
//		/*if (b265Frame == false)
//		{
//			qDebug() << ("b265Frame == false!") << "time:" << current_date;
//		}
//		else
//		{
//			qDebug() << ("b265Frame == true!") << "time:" << current_date;;
//		}*/
//
//		int videoWidth;                 //视频宽度
//		int videoHeight;                //视频高度
//		int nResolution = ((pData->nTimestamp & 0xe000) >> 13);
//		getVideoResolution(nResolution, &videoWidth, &videoHeight);
//
//		if (_h264Handle == 0)
//		{
//			_h264Handle = H264_CreateHandle();
//		}
//
//		int pRet = H264_PutVideoStream(_h264Handle, (char*)pData->pData, pData->nLen/*, buffer, frameSize,picWidth, picHeight*/);
//		if (pRet != 0)
//		{
//			return pRet;
//		}
//
//		int picWidth = videoWidth;
//		int picHeight = videoHeight;
//		INT32 frameSize = H264_GetVideoFrameSize_Rgb2(_h264Handle, picWidth, picHeight);
//		if (frameSize == 0)
//			return -1;
//
//		char* buffer = new char[frameSize];
//		memset(buffer, 0, sizeof(buffer));
//
//		while (true)
//		{
//			INT32 ret = H264_GetNextVideoFrame_Rgb2(_h264Handle, buffer, frameSize, picWidth, picHeight);
//			if (ret != 0)
//				break;
//
//			QImage image((uchar*)buffer, picWidth, picHeight, QImage::Format_RGB888);
//			QImage imgs = image.rgbSwapped();
//
//			if (!imgs.isNull()) {
//				emit receiveImage(imgs);
//			}
//		}
//		delete buffer;
//	}
//
//	return 0;
//}
//
//void FFmpegDecode::getVideoResolution(int nResolution, int * width, int * height)
//{
//	if (nResolution == 0)
//	{
//		//should retieve from video streaming
//		*width = 0;
//		*height = 0;
//	}
//	else if (nResolution == 1)
//	{
//		*width = 176;
//		*height = 144;
//	}
//	else if (nResolution == 2)
//	{
//		*width = 320;
//		*height = 240;
//	}
//	else if (nResolution == 3)
//	{
//		*width = 352;
//		*height = 288;
//	}
//	else if (nResolution == 4)
//	{
//		*width = 704;
//		*height = 288;
//	}
//	else if (nResolution == 5)
//	{
//		*width = 704;
//		*height = 576;
//	}
//	else if (nResolution == 6)
//	{
//		*width = 1280;
//		*height = 720;
//	}
//	else if (nResolution == 7)
//	{
//		*width = 1920;
//		*height = 1080;
//	}
//}