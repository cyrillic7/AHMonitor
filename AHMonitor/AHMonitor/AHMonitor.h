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
#include "widget.h"
#include <QTabWidget>
#include "QTerminalControl.h"
#include "QPTZControl.h"
#include "QAlarmWidget.h"

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
	QTabWidget*		pTabWidget_;
	QTerminalControl* pTerminalCtl_;
	QPTZControl* pPTZControl_;
	QAlarmWidget* pAlarmWidget_;
private:
	Ui::AHMonitorClass ui;

	bool av_register = false;

	//CCameraMngr* cameraManager;
private:
	QStringList rtString;
	Widget*		MsgShowWidget_;
	QWidget*	QMainWidget;

	QMenu *  LinkMenu_;

	QAction* LinkAction_;
	QAction* unLinkAction_;
	QAction* ExitAction_;

	QToolBar* LinkTool_; //¹¤¾ßÀ¸

	QToolsSplit* pToolsSplit_;

	ServerManager* m_pServerManager;
	CPlayerManager* m_pPlayerManager;

	CCameraMngr* getCamMnr();
	//FrameStreamManager* m_pFrameStreamManager;
	/*struct AVCodecContext *pAVCodecCtx_decoder = NULL;
	struct AVCodec *pAVCodec_decoder;
	struct AVPacket mAVPacket_decoder;
	struct AVFrame *pAVFrame_decoder = NULL;
	struct SwsContext* pImageConvertCtx_decoder = NULL;
	struct AVFrame *pFrameYUV_decoder = NULL;*/
signals:
	void showMsg(QString title, QString content, QString url);
public:
	void updateTreeWidget();

	void updateDisConWidget();

	void updateCamOnLine(int nSession, bool bOnline);

	int serverConnection(QString szAccounts, QString szPassword, QString szAddress, QString szPort);

	void decodeACKString(QString AckString);
private:
	void createActions();
	void createMenus();
	void createToolBars();

public slots:
	void onServerConnect();
	void onServerDisConnect();
	void serverDisCon(const QString & servername);

	void clickTerDefault();
	void clickTerSet();
	void clickTerRestart();

	void SetVideoParamCommand(int camChannel, VideoSize size, int KeySpacing, int KeyFrame, int CodeMode, int CodeLevel,int QuaStep,int CodeRate, char * command);

	void setItemSession(int serverID,int session);

	void cloudCicked(int nPosition);

	void zoomPlus();
	void zoomReduce();
	void apertureBig();
	void apertureSmall();
	void focusingNear();
	void focusingFar();

	void FerPosition(int position);
	void CAction(QString & action);
};
