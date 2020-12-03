#include "stdafx.h"
#include "H264Decode.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavformat/avformat.h"
#include "libavutil/dict.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
};

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "swscale.lib")

AVPixelFormat videoFmt_RGB24 = AV_PIX_FMT_RGB24;
int Buffer_Align = 4; //如果不4字节对齐，缩放可能会出问题。

int DefaultAlgorithmFlag = SWS_BICUBIC;

H264Decode::H264Decode()
{
	AlgorithmFlag = DefaultAlgorithmFlag;
}


H264Decode::~H264Decode()
{
	if (_pCodecContext != NULL)
	{
		avcodec_free_context(&_pCodecContext);
		_pCodecContext = NULL;
	}

	if (_pFrameYuv != NULL)
	{
		av_frame_free(&_pFrameYuv);
		_pFrameYuv = NULL;
	}

	if (_img_convert_ctx != NULL)
	{
		sws_freeContext(_img_convert_ctx);
		_img_convert_ctx = NULL;
	}
}

//BOOL _av_register = FALSE;
BOOL H264Decode::Init()
{
	if (_init)
		return TRUE;

	_init = TRUE;
	if (!_av_register)
	{
		_av_register = TRUE;
		av_register_all();
	}

	_pCodecContext = avcodec_alloc_context3(NULL);
	_pH264VideoDecoder = avcodec_find_decoder(AV_CODEC_ID_H265);
	if (_pH264VideoDecoder == NULL)
	{
		return FALSE;
	}	

	//初始化参数，下面的参数应该由具体的业务决定  AV_PIX_FMT_YUV420P;
	_pCodecContext->flags |= AV_CODEC_FLAG_LOW_DELAY;
	_pCodecContext->time_base.num = 1;
	_pCodecContext->frame_number = 1; //每包一个视频帧  
	_pCodecContext->codec_type = AVMEDIA_TYPE_VIDEO;
	_pCodecContext->bit_rate = 400000;
	//_pCodecContext->bit_rate_tolerance = 4000000;
	_pCodecContext->time_base.den = 25;//帧率  
	//_pCodecContext->time_base = {1,25};
	_pCodecContext->width = 0;//视频宽  
	_pCodecContext->height = 0;//视频高 
	_pCodecContext->pix_fmt = AV_PIX_FMT_YUV420P;
	_pCodecContext->color_range = AVCOL_RANGE_MPEG;
	_pCodecContext->max_b_frames = 0;
	_pCodecContext->thread_count = 8;
	/*AVDictionary *optionsDict = NULL;
	av_dict_set(&optionsDict, "rtsp_transport", "tdp", 0);
	av_dict_set(&optionsDict, "buffer_size", "1024000", 0);
	av_dict_set(&optionsDict, "max_delay", "500000", 0);
	av_dict_set(&optionsDict, "fflags", "nobuffer", 0);
	av_dict_set(&optionsDict, "probsize", "4096", 0);
	av_dict_set(&optionsDict, "packet - buffering", "0", 0);
	av_dict_set(&optionsDict, "fps", "30", 0);*/


	AVDictionary *param = 0;
	av_dict_set(&param, "fflags", "nobuffer", 0);
	av_dict_set(&param, "preset", "ultrafast", 0); // av_opt_set(pCodecCtx->priv_data,"preset","fast",0);
	//av_dict_set(&param, "tune", "zerolatency", 0);
	av_dict_set(&param, "probesize", "4096", 0);
	av_dict_set(&param, "buffer_size", "8192000", 0);//设置缓存大小，1080p可将值调大，比如1MB; 524288=512KB  1048576=1MB
	//av_dict_set(&param, "max_delay", "10", 0);
	//av_dict_set(&param, "max_delay", "5000000", 0);
	av_dict_set(&param, "threads", "auto", 0);

	if (avcodec_open2(_pCodecContext, _pH264VideoDecoder, &param) >= 0)
		_pFrameYuv = av_frame_alloc();
	else
		return FALSE;

	return TRUE;
}

INT32 H264Decode::H264_PutVideoStream(char* buffer, INT32 bufferLen)
{
	/*if (buffer == NULL)
		return -1;*/
	//avcodec_flush_buffers(_pCodecContext);
	AVPacket packet = { 0 };
	packet.data = (uint8_t*)buffer;	//这里填入一个指向完整H264数据帧的指针  
	packet.size = bufferLen;		//这个填入H264数据帧的大小  
	//packet.stream_index = AVMEDIA_TYPE_VIDEO;

	int ret = avcodec_send_packet(_pCodecContext, &packet);
	return ret;
}

INT32 H264Decode::H264_SetAlgorithm(INT32 flag)
{
	if (flag == SWS_FAST_BILINEAR
		|| flag == SWS_BILINEAR
		|| flag == SWS_BICUBIC
		|| flag == SWS_X
		|| flag == SWS_POINT
		|| flag == SWS_AREA
		|| flag == SWS_BICUBLIN
		|| flag == SWS_GAUSS
		|| flag == SWS_SINC
		|| flag == SWS_LANCZOS
		|| flag == SWS_SPLINE
		)
	{

	}
	else
	{
		flag = DefaultAlgorithmFlag;
	}

	AlgorithmFlag = flag;
	_rgbWidth = 0;
	_rgbHeight = 0;
	return 0;
}


INT32 H264Decode::H264_GetVideoParam(INT32& width, INT32& height)
{
	height = _pCodecContext->height;
	width = _pCodecContext->width;
	if (height > 0 && width > 0)
		return  0;
	return -1;
}


INT32 H264Decode::H264_GetVideoFrameSize()
{
	int picSize = _pCodecContext->height * _pCodecContext->width;
	int newSize = picSize * 1.5;
	return newSize;
}

INT32 H264Decode::H264_GetVideoFrameFormate()
{
	return _pFrameYuv->format;
}

INT32 H264Decode::H264_GetNextVideoFrame(char* buffer, INT32 bufferLen, INT32 yuFormate)
{
	if (avcodec_receive_frame(_pCodecContext, _pFrameYuv) == 0)
	{
		int height = _pCodecContext->height;
		int width = _pCodecContext->width;

		if (yuFormate == 1)
		{
			////写入数据  
			int yLen = height * width;
			memcpy(buffer, _pFrameYuv->data[0], yLen);

			int uLen = yLen / 4;
			memcpy(buffer + yLen, _pFrameYuv->data[1], uLen);

			int vLen = uLen;
			memcpy(buffer + yLen + uLen, _pFrameYuv->data[2], vLen);
			return 0;
		}
		else
		{
			////写入数据  
			int yLen = height * width;
			memcpy(buffer, _pFrameYuv->data[0], yLen);

			int uLen = yLen / 4;
			memcpy(buffer + yLen, _pFrameYuv->data[2], uLen);

			int vLen = uLen;
			memcpy(buffer + yLen + uLen, _pFrameYuv->data[1], vLen);
			return 0;
		}
	}
	return -1;
}

INT32 H264Decode::H264_GetVideoFrameCurSize_Rgb()
{
	return H264_GetVideoFrameSize_Rgb2(_pCodecContext->width, _pCodecContext->height);
}

int GetLineSize(INT32 width)
{
	int n = width * 3;
	int m = n % Buffer_Align;
	if (m != 0)
	{
		n += Buffer_Align - m;
	}
	return  n;
}

INT32 H264Decode::H264_GetVideoFrameSize_Rgb2(INT32 width, INT32 height)
{
	int picSize = GetLineSize(width) * height;
	return picSize;
}


INT32 H264Decode::H264_GetNextVideoFrame_Rgb(char* buffer, INT32 bufferLen)
{
	if (avcodec_receive_frame(_pCodecContext, _pFrameYuv) == 0)
	{
		ResetRgbScale(_pCodecContext->width, _pCodecContext->height);

		uint8_t * data[3];
		data[0] = _pFrameYuv->data[0];
		data[1] = _pFrameYuv->data[2]; //u v 向量互换
		data[2] = _pFrameYuv->data[1];

		_dst_dataTmp[0] = (uint8_t *)buffer; //少一次复制
		sws_scale(_img_convert_ctx, (const unsigned char* const*)data, _pFrameYuv->linesize, 0, _pCodecContext->height,
			_dst_dataTmp, _dst_linesize);
		return 0;
	}
	return -1;
}

INT32 H264Decode::H264_GetNextVideoFrame_Rgb(char* buffer, INT32 bufferLen, INT32 width, INT32 height)
{
	//av_frame_unref(_pFrameYuv);
	//avcodec_flush_buffers(_pCodecContext);
	if (avcodec_receive_frame(_pCodecContext, _pFrameYuv) == 0)
	{
		ResetRgbScale(width, height);

		int n = (_out_rgb_buffer_len == bufferLen);

		uint8_t * data[3];
		data[0] = _pFrameYuv->data[0];
		data[1] = _pFrameYuv->data[2]; //u v 向量互换
		data[2] = _pFrameYuv->data[1];

		_dst_dataTmp[0] = (uint8_t *)buffer; //少一次复制
		int ret = sws_scale(_img_convert_ctx, (const unsigned char* const*)data, _pFrameYuv->linesize, 0, _pCodecContext->height,
			_dst_dataTmp, _dst_linesize);
		return 0;
	}
	return -1;
}

bool H264Decode::ResetRgbScale(INT32 width, INT32 height)
{
	if (_rgbWidth == width && height == _rgbHeight)
		return false;

	if (_img_convert_ctx != NULL)
	{
		sws_freeContext(_img_convert_ctx);
		_img_convert_ctx = NULL;
	}


	_rgbWidth = width;
	_rgbHeight = height;

	//int dst_bpp = av_get_bits_per_pixel(av_pix_fmt_desc_get(videoFmt_RGB24));
	//int ret = av_image_alloc(_dst_data, _dst_linesize, _rgbWidth, _rgbHeight, videoFmt_RGB24, Buffer_Align);

	_dst_linesize[0]= GetLineSize(width);
	_out_rgb_buffer_len = H264_GetVideoFrameSize_Rgb2(width, height);

	_img_convert_ctx = sws_getContext(_pCodecContext->width, _pCodecContext->height, _pCodecContext->pix_fmt,
		_rgbWidth, _rgbHeight, videoFmt_RGB24, AlgorithmFlag, NULL, NULL, NULL);
	return true;
}

int H264Decode::DecodeH264(char * buffer, int bufferLen, std::list<DecodeData>& listOutData)
{
	AVPacket packet = { 0 };

	packet.data = (uint8_t*)buffer;//这里填入一个指向完整H264数据帧的指针  
	packet.size = bufferLen;//这个填入H264数据帧的大小  

	int ret = avcodec_send_packet(_pCodecContext, &packet);
	if (ret != 0)
	{
		return -1;
	}

	while (avcodec_receive_frame(_pCodecContext, _pFrameYuv) == 0)
	{
		int picSize = _pCodecContext->height * _pCodecContext->width;
		int newSize = picSize * 1.5;

		//申请内存  
		unsigned char *buf = new unsigned char[newSize];
		DecodeData data;
		data.pData = buf;
		data.dataLen = newSize;
		listOutData.push_back(data);

		int height = _pCodecContext->height;
		int width = _pCodecContext->width;
		_pFrameYuv->qscale_table;

		//写入数据  
		int a = 0, i;
		for (i = 0; i < height; i++)
		{
			memcpy(buf + a, _pFrameYuv->data[0] + i * _pFrameYuv->linesize[0], width);
			a += width;
		}
		for (i = 0; i < height / 2; i++)
		{
			memcpy(buf + a, _pFrameYuv->data[1] + i * _pFrameYuv->linesize[1], width / 2);
			a += width / 2;
		}
		for (i = 0; i < height / 2; i++)
		{
			memcpy(buf + a, _pFrameYuv->data[2] + i * _pFrameYuv->linesize[2], width / 2);
			a += width / 2;
		}
	}

	return 0;
}

//int H264Decode::DecodeH264(char * buffer, int bufferLen, std::list<DecodeData>& listOutData)
//{
//	AVPacket packet = { 0 };
//	int frameFinished = 0;//这个是随便填入数字，没什么作用  
//
//	packet.data = (uint8_t*)buffer;//这里填入一个指向完整H264数据帧的指针  
//	packet.size = bufferLen;//这个填入H264数据帧的大小  
//
//	int ret = avcodec_send_packet(_pCodecContext, &packet);
//	if (ret != 0)
//	{
//		return -1;
//	}
//
//	while (avcodec_receive_frame(_pCodecContext, _pFrame) == 0)
//	{
//		int picSize = _pCodecContext->height * _pCodecContext->width;
//		int newSize = picSize * 1.5;
//
//		//申请内存  
//		unsigned char *buf = new unsigned char[newSize];
//		DecodeData data;
//		data.pData = buf;
//		data.dataLen = newSize;
//		listOutData.push_back(data);
//
//		int height = _pCodecContext->height;
//		int width = _pCodecContext->width;
//
//
//		//写入数据  
//		int a = 0, i;
//		for (i = 0; i<height; i++)
//		{
//			memcpy(buf + a, _pFrame->data[0] + i * _pFrame->linesize[0], width);
//			a += width;
//		}
//		for (i = 0; i<height / 2; i++)
//		{
//			memcpy(buf + a, _pFrame->data[1] + i * _pFrame->linesize[1], width / 2);
//			a += width / 2;
//		}
//		for (i = 0; i<height / 2; i++)
//		{
//			memcpy(buf + a, _pFrame->data[2] + i * _pFrame->linesize[2], width / 2);
//			a += width / 2;
//		}
//	}
//
//	return 0;
//}
