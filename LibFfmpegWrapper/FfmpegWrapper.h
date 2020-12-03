#pragma once
// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 IOCPNETLIB_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// IOCPNETLIB_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
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