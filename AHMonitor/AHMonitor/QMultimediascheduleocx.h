#ifndef _QMULTIMEDIASHEDULE_OCX_H_
#define _QMULTIMEDIASHEDULE_OCX_H_


#pragma once
#include "qaxwidget.h"
class QMultimediascheduleocx :
	public QObject
{
	Q_OBJECT
public:
	QMultimediascheduleocx();
	virtual ~QMultimediascheduleocx();
	//登录sip
	int LogonSip(QString user, QString pasd, QString server, QString port);
	//发送消息
	int sendSMS(QString callNumber,QString Msg);
	//获取设备
	long getPhysicsHandCount();
	//拨打语音
	int makeAudioCall(QString dsNumber, long nHand);
	//拨打视频
	int makeVideoCall(QString dsNumber, long Hwnd, long nHand);
	//终止会话
	int hangUpCall(long callid);

private:
	QAxWidget* pMulAxWidget_;

	long nhwnd;
public slots:
	void onMulEventRegistered(int code);

	void onMulEventConnected(int callId);
};

#endif