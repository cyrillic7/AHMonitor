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
	//��¼�ؼ�
	QLogonDialog* pLogonDialog_;
	//����������
	QServerTreeWidget* pTreeWidget_;
	//���ſؼ�
	VideoPanel* pVidoePanel_Widget_;
	ZXCmtPlayer* pZXCmtPlayer_;
	//�Ͽ����Ӵ���
	QSDisConWidget* pSDisConWidget_;
	//����tab
	QTabWidget*		pTabWidget_;
	//�ն˿���
	QTerminalControl* pTerminalCtl_;
	//ptz����
	QPTZControl* pPTZControl_;
	//�����ؼ�
	QAlarmWidget* pAlarmWidget_;

	QMultimediascheduleocx* mul;
private:
	Ui::AHMonitorClass ui;
	//ע��dll
	bool av_register = false;

	//CCameraMngr* cameraManager;
private:
	//QAxWidget* pAxWidgetPlayer_;
	QTabWidget* pPanelTab_;
	bool bPanelFull = false;
	//�ַ���
	QStringList rtString;
	//��Ϣ����
	Widget*		MsgShowWidget_;
	//������
	QWidget*	QMainWidget;
	//�˵���
	QMenu *  LinkMenu_;
	//�˵���action
	QAction* LinkAction_;
	QAction* unLinkAction_;
	QAction* ExitAction_;
	QAction* SaveVideoAction_;
	QAction* ScreenFull_;
	QAction* makeVideoTest_;
	QAction* makeAudioText_;

	QToolBar* LinkTool_; //������
	//�϶���
	QToolsSplit* pToolsSplit_;
	//����������
	ServerManager* m_pServerManager;
	//����������
	CPlayerManager* m_pPlayerManager;
	//����������
	CCameraMngr* getCamMnr();
	//FrameStreamManager* m_pFrameStreamManager;
	/*struct AVCodecContext *pAVCodecCtx_decoder = NULL;
	struct AVCodec *pAVCodec_decoder;
	struct AVPacket mAVPacket_decoder;
	struct AVFrame *pAVFrame_decoder = NULL;
	struct SwsContext* pImageConvertCtx_decoder = NULL;
	struct AVFrame *pFrameYUV_decoder = NULL;*/
signals:
	//��Ϣ�ź�
	void showMsg(QString title, QString content, QString url);
public:
	//�����б�
	void updateTreeWidget();
	//���¶Ͽ����Ӵ���
	void updateDisConWidget();
	//���������豸
	void updateCamOnLine(int nSession, bool bOnline);
	//���ӷ�����
	int serverConnection(QString szAccounts, QString szPassword, QString szAddress, QString szPort);
	//�����ַ���
	void decodeACKString(QString AckString);
private:
	void createActions();
	void createMenus();
	void createToolBars();
	//����gps
	void gpsParse(QByteArray GPSBuffer);

public slots:
void makeVideo();
void makeAudio();
	//���ӷ�����
	void onServerConnect();
	//�Ͽ�����������
	void onServerDisConnect();
	void serverDisCon(const QString & servername);
	//������Ƶ
	void saveVideo();
	//ȫ��
	void screenfull();
	//
	void clickTerDefault();
	//������Ƶ����
	void clickTerSet();
	//�����豸
	void clickTerRestart();
	//���ò���
	void SetVideoParamCommand(int camChannel, VideoSize size, int KeySpacing, int KeyFrame, int CodeMode, int CodeLevel,int QuaStep,int CodeRate, char * command);
	//����serverid��sessionid
	void setItemSession(int serverID,int session);
	//��̨����
	void cloudCicked(int nPosition);

	void zoomPlus();
	void zoomReduce();
	void apertureBig();
	void apertureSmall();
	void focusingNear();
	void focusingFar();

	void FerPosition(int position);
	void CAction(QString & action);
	//����
	void clickAlarm(QString & action);
};
