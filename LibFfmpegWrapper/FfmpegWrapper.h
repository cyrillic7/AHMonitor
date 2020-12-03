#pragma once
// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� IOCPNETLIB_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// IOCPNETLIB_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef LIBFFMPEGWRAPPER_EXPORTS
#define LibFfmpegWrapper_API __declspec(dllexport)
#else
#define LibFfmpegWrapper_API __declspec(dllimport)
#endif

extern "C"
{
	LibFfmpegWrapper_API INT64 H264_CreateHandle();
	LibFfmpegWrapper_API INT32 H264_CloseHandle(INT64 handle);

	LibFfmpegWrapper_API INT32 H264_SetDefaultAlgorithm(INT32 flag);
	LibFfmpegWrapper_API INT32 H264_SetAlgorithm(INT64 handle, INT32 flag);

	LibFfmpegWrapper_API INT32 H264_PutVideoStream(INT64 handle, char* buffer, INT32 bufferLen/*, char* rgb, INT32 rgblen, INT32 width, INT32 height*/);
	LibFfmpegWrapper_API INT32 H264_GetVideoParam(INT64 handle, INT32& width, INT32& height);

	LibFfmpegWrapper_API INT32 H264_GetVideoFrameSize(INT64 handle);
	LibFfmpegWrapper_API INT32 H264_GetVideoFrameFormate(INT64 handle);

	LibFfmpegWrapper_API INT32 H264_GetNextVideoFrame(INT64 handle, char* buffer, INT32 bufferLen, INT32 yuFormate);

	LibFfmpegWrapper_API INT32 H264_GetVideoFrameSize_Rgb(INT64 handle);
	LibFfmpegWrapper_API INT32 H264_GetNextVideoFrame_Rgb(INT64 handle, char* buffer, INT32 bufferLen);

	LibFfmpegWrapper_API INT32 H264_GetVideoFrameSize_Rgb2(INT64 handle,INT32 width, INT32 height);
	LibFfmpegWrapper_API INT32 H264_GetNextVideoFrame_Rgb2(INT64 handle, char* buffer, INT32 bufferLen, INT32 width, INT32 height);
}