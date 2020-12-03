#include "stdafx.h"
#include "FfmpegWrapper.h"
#include "H264Decode.h"


extern "C"
{
#include "libswscale/swscale.h"
};


INT64 H264_CreateHandle()
{
	H264Decode *pDecode = new  H264Decode();
	if (!pDecode->Init())
		return 0;

	return (INT64)pDecode;
}

INT32 H264_CloseHandle(INT64 handle)
{
	H264Decode *pDecode = (H264Decode*)handle;
	delete pDecode;
	return 0;
}

extern int DefaultAlgorithmFlag;
INT32 H264_SetDefaultAlgorithm(INT32 flag)
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
		flag = SWS_BICUBIC;
	}
	DefaultAlgorithmFlag = flag;
	return 0;
}

INT32 H264_SetAlgorithm(INT64 handle, INT32 flag)
{
	H264Decode *pDecode = (H264Decode*)handle;
	return pDecode->H264_SetAlgorithm(flag);
}


INT32 H264_PutVideoStream(INT64 handle, char* buffer, INT32 bufferLen/*,char* rgb,INT32 rgblen, INT32 width, INT32 height*/)
{
	H264Decode *pDecode = (H264Decode*)handle;
	int ret = pDecode->H264_PutVideoStream(buffer, bufferLen);
	/*int ret;
	while (true)
	{
		ret = pDecode->H264_PutVideoStream(buffer, bufferLen);
		if (ret != 0)
			return -2;

		ret = pDecode->H264_GetNextVideoFrame_Rgb(rgb, bufferLen, width, height);
		if (ret == 0)
		{
			break;
		}

	}*/
	//ret = pDecode->H264_GetNextVideoFrame_Rgb(rgb, bufferLen, width, height);
	return ret;
}

INT32 H264_GetVideoParam(INT64 handle, INT32& width, INT32& height)
{
	H264Decode *pDecode = (H264Decode*)handle;
	return pDecode->H264_GetVideoParam(width, height);
}

INT32 H264_GetVideoFrameSize(INT64 handle)
{
	H264Decode *pDecode = (H264Decode*)handle;
	return pDecode->H264_GetVideoFrameSize();
}

INT32 H264_GetNextVideoFrame(INT64 handle, char* buffer, INT32 bufferLen, INT32 yuFormate)
{
	H264Decode *pDecode = (H264Decode*)handle;
	return pDecode->H264_GetNextVideoFrame(buffer, bufferLen, yuFormate);
}

INT32 H264_GetVideoFrameFormate(INT64 handle)
{
	H264Decode *pDecode = (H264Decode*)handle;
	return pDecode->H264_GetVideoFrameFormate();
}

INT32 H264_GetVideoFrameSize_Rgb(INT64 handle)
{
	H264Decode *pDecode = (H264Decode*)handle;
	return pDecode->H264_GetVideoFrameCurSize_Rgb();
}

INT32 H264_GetNextVideoFrame_Rgb(INT64 handle, char* buffer, INT32 bufferLen)
{
	H264Decode *pDecode = (H264Decode*)handle;
	return pDecode->H264_GetNextVideoFrame_Rgb(buffer, bufferLen);
}

INT32 H264_GetVideoFrameSize_Rgb2(INT64 handle, INT32 width, INT32 height)
{
	H264Decode *pDecode = (H264Decode*)handle;
	return pDecode->H264_GetVideoFrameSize_Rgb2(width, height);
}


INT32 H264_GetNextVideoFrame_Rgb2(INT64 handle, char* buffer, INT32 bufferLen, INT32 width, INT32 height)
{
	H264Decode *pDecode = (H264Decode*)handle;
	return pDecode->H264_GetNextVideoFrame_Rgb(buffer, bufferLen, width, height);
}
