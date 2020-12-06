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
#include "QSDisConWidget.h"

class AHMonitor : public QMainWindow
{
	Q_OBJECT

public:
	AHMonitor(QWidget *parent = Q_NULLPTR);
	virtual ~AHMonitor();

	QLogonDialog* pLogonDialog_;
	QServerTreeWidget* pTreeWidget_;
	VideoPanel* pVidoePanel_Widget_;
	QSDisConWidget* pSDisConWidget_;
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

	void updateDisConWidget();

	void updateCamOnLine(int nSession, bool bOnline);

private:
	void createActions();
	void createMenus();
	void createToolBars();

public slots:
	void onServerConnect();
	void onServerDisConnect();
	void serverDisCon(const QString & servername);
};
