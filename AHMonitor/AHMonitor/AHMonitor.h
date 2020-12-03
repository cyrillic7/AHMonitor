#pragma once

#include "HeadFile.h"
#include <QtWidgets/QMainWindow>
#include <QMenubar>
#include <QMenu>
#include <QTreeWidget>
#include "ui_AHMonitor.h"
#include "videopanel.h"
#include "ServerManager.h"
#include "PlayerManager.h"
#include "QServerTreeWidget.h"
#include "QLogonDialog.h"
#include "QToolsSplit.h"


class AHMonitor : public QMainWindow
{
	Q_OBJECT

public:
	AHMonitor(QWidget *parent = Q_NULLPTR);
	virtual ~AHMonitor();

	QLogonDialog* pLogonDialog_;
	QServerTreeWidget* pTreeWidget_;
	VideoPanel* pVidoePanel_Widget_;
private:
	Ui::AHMonitorClass ui;

	bool av_register = false;
private:
	QWidget*	QMainWidget;

	QMenu *  LinkMenu_;

	QAction* LinkAction_;
	QAction* unLinkAction_;
	QAction* ExitAction_;

	QToolBar* LinkTool_; //¹¤¾ßÀ¸

	QToolsSplit* pToolsSplit_;

	ServerManager* m_pServerManager;
	CPlayerManager* m_pPlayerManager;
	//FrameStreamManager* m_pFrameStreamManager;
	/*struct AVCodecContext *pAVCodecCtx_decoder = NULL;
	struct AVCodec *pAVCodec_decoder;
	struct AVPacket mAVPacket_decoder;
	struct AVFrame *pAVFrame_decoder = NULL;
	struct SwsContext* pImageConvertCtx_decoder = NULL;
	struct AVFrame *pFrameYUV_decoder = NULL;*/

public:
	void updateTreeWidget();

	void updateCamOnLine(int nSession, bool bOnline);

	void showh264toImage(unsigned char* pData, int iLen,int nResolution);

	bool GetVideoFrameResolution(void *pParam, int *width, int *height);

	void Yuv420p2Rgb32(unsigned char * pBufy, unsigned char * pBufu, unsigned char * pBufv, const BYTE * rgbBuffer_out, int width, int height);
	void YUV420_2_RGB(unsigned char * pBufy, unsigned char * pBufu, unsigned char * pBufv, unsigned char * pRGB, int width, int height);
	bool yuv420ToRgb(unsigned char * pBufy, unsigned char * pBufu, unsigned char * pBufv, int w, int h, char * rgb);

	void RGB2Image(char * srcBuf, int w, int h, QImage * pDistImage);
private:
	void createActions();
	void createMenus();
	void createToolBars();

public slots:
	void onServerConnect();
	void onServerDisConnect();
};
