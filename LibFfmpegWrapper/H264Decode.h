#pragma once
#include <list>

class  AVCodec;
class AVCodecContext;
class AVFrame;

struct DecodeData
{
	unsigned char *pData = NULL;
	int dataLen;

	~DecodeData()
	{
		//delete []pData;
	}

};


class H264Decode
{
public:
	H264Decode();
	~H264Decode();

	BOOL Init();

	int DecodeH264(char* buffer, int bufferLen,std::list<DecodeData>& listOutData);

	INT32 H264_PutVideoStream(char* buffer, INT32 bufferLen);
	INT32 H264_SetAlgorithm(INT32 flag);
	INT32 H264_GetVideoParam(INT32& width, INT32& height);
	INT32 H264_GetVideoFrameSize();
	INT32 H264_GetVideoFrameFormate();

	INT32 H264_GetNextVideoFrame(char* buffer, INT32 bufferLen, INT32 yuFormate);

	INT32 H264_GetVideoFrameCurSize_Rgb();
	INT32 H264_GetNextVideoFrame_Rgb(char* buffer, INT32 bufferLen);

	INT32 H264_GetVideoFrameSize_Rgb2(INT32 width, INT32 height);
	INT32 H264_GetNextVideoFrame_Rgb(char* buffer, INT32 bufferLen,INT32 width, INT32 height);

	bool ResetRgbScale(INT32 width, INT32 height);

private:
	BOOL _av_register = FALSE;
	int  AlgorithmFlag;

	BOOL _init = FALSE;
	AVCodec * _pH264VideoDecoder = NULL;
	AVCodecContext *_pCodecContext = NULL;
	AVFrame *_pFrameYuv = NULL;
	struct SwsContext   *_img_convert_ctx = NULL;

	int _rgbWidth = 0;
	int _rgbHeight = 0;
	int _out_rgb_buffer_len = 0;
	int _dst_linesize[4];
	uint8_t *_dst_dataTmp[4];
};

