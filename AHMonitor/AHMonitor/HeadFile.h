#ifndef _HEAD_FILE_
#define _HEAD_FILE_
#pragma once

#pragma execution_character_set("utf-8")

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes

#define MODE_NETWORK_SERVER
#define AH_VERSION  "1.0.0.0"

#include "../../WB_SDK/inc/ControlCommand.h"
#include "../../WB_SDK/inc/PlaybackEngine.h"

using namespace std;
//#ifdef debug
//#pragma commenct(lib,"../../WB_SDK/lib/release/ControlCommand.lib")
//#pragma commenct(lib,"../../WB_SDK/lib/release/PlaybackEngine.lib")
//#else
//#pragma commenct(lib,"../../WB_SDK/lib/debug/ControlCommand.lib")
//#pragma commenct(lib,"../../WB_SDK/lib/debug/PlaybackEngine.lib")
//#endif // !debug

void UIEventCallBackHandler(MP_ENG_EVENT event, int nIndex, void *pParam, void *pAppData);

void UIPlayerEventCallBackHandler(MP_ENG_EVENT event, int nIndex, void *pParam, void *pAppData);

#include "FfmpegWrapper.h"
#include <QString>
class GlobalFun
{
public:

	static QString charToqstirng(char* buff)
	{
		std::string str(buff);
		return QString::fromLocal8Bit(str.c_str());
	}

};

typedef  struct  RGB32 {
	BYTE     rgbBlue;       // 蓝色分量
	BYTE     rgbGreen;      // 绿色分量
	BYTE     rgbRed;        // 红色分量
	BYTE     rgbReserved;   // 保留字节（用作Alpha通道或忽略）
} RGB32;

#endif