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
#include "ZXCmtPlayer.h"
#include "QMultimediascheduleocx.h"

class AHMonitor : public QMainWindow
{
	Q_OBJECT

public:
	AHMonitor(QWidget *parent = Q_NULLPTR);
	virtual ~AHMonitor();
	//登录控件
	QLogonDialog* pLogonDialog_;
	//服务器队列
	QServerTreeWidget* pTreeWidget_;
	//播放控件
	VideoPanel* pVidoePanel_Widget_;
	ZXCmtPlayer* pZXCmtPlayer_;
	//断开连接窗口
	QSDisConWidget* pSDisConWidget_;
	//控制tab
	QTabWidget*		pTabWidget_;
	//终端控制
	QTerminalControl* pTerminalCtl_;
	//ptz控制
	QPTZControl* pPTZControl_;
	//报警控件
	QAlarmWidget* pAlarmWidget_;

	QMultimediascheduleocx* mul;
private:
	Ui::AHMonitorClass ui;
	//注册dll
	bool av_register = false;

	//CCameraMngr* cameraManager;
private:
	//QAxWidget* pAxWidgetPlayer_;
	QTabWidget* pPanelTab_;
	bool bPanelFull = false;
	//字符串
	QStringList rtString;
	//消息窗口
	Widget*		MsgShowWidget_;
	//主窗口
	QWidget*	QMainWidget;
	//菜单栏
	QMenu *  LinkMenu_;
	//菜单栏action
	QAction* LinkAction_;
	QAction* unLinkAction_;
	QAction* ExitAction_;
	QAction* SaveVideoAction_;
	QAction* ScreenFull_;
	QAction* makeVideoTest_;
	QAction* makeAudioText_;

	QToolBar* LinkTool_; //工具栏
	//拖动条
	QToolsSplit* pToolsSplit_;
	//服务器管理
	ServerManager* m_pServerManager;
	//播放器管理
	CPlayerManager* m_pPlayerManager;
	//播放器对象
	CCameraMngr* getCamMnr();
	//FrameStreamManager* m_pFrameStreamManager;
	/*struct AVCodecContext *pAVCodecCtx_decoder = NULL;
	struct AVCodec *pAVCodec_decoder;
	struct AVPacket mAVPacket_decoder;
	struct AVFrame *pAVFrame_decoder = NULL;
	struct SwsContext* pImageConvertCtx_decoder = NULL;
	struct AVFrame *pFrameYUV_decoder = NULL;*/
signals:
	//消息信号
	void showMsg(QString title, QString content, QString url);
public:
	//更新列表
	void updateTreeWidget();
	//更新断开连接窗口
	void updateDisConWidget();
	//更新在线设备
	void updateCamOnLine(int nSession, bool bOnline);
	//连接服务器
	int serverConnection(QString szAccounts, QString szPassword, QString szAddress, QString szPort);
	//解析字符串
	void decodeACKString(QString AckString);
private:
	void createActions();
	void createMenus();
	void createToolBars();
	//解析gps
	void gpsParse(QByteArray GPSBuffer);

public slots:
void makeVideo();
void makeAudio();
	//连接服务器
	void onServerConnect();
	//断开服务器窗口
	void onServerDisConnect();
	void serverDisCon(const QString & servername);
	//保存视频
	void saveVideo();
	//全屏
	void screenfull();
	//
	void clickTerDefault();
	//设置视频参数
	void clickTerSet();
	//重启设备
	void clickTerRestart();
	//设置参数
	void SetVideoParamCommand(int camChannel, VideoSize size, int KeySpacing, int KeyFrame, int CodeMode, int CodeLevel,int QuaStep,int CodeRate, char * command);
	//设置serverid，sessionid
	void setItemSession(int serverID,int session);
	//云台控制
	void cloudCicked(int nPosition);

	void zoomPlus();
	void zoomReduce();
	void apertureBig();
	void apertureSmall();
	void focusingNear();
	void focusingFar();

	void FerPosition(int position);
	void CAction(QString & action);
	//报警
	void clickAlarm(QString & action);
};
