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
	//��¼sip
	int LogonSip(QString user, QString pasd, QString server, QString port);
	//������Ϣ
	int sendSMS(QString callNumber,QString Msg);
	//��ȡ�豸
	long getPhysicsHandCount();
	//��������
	int makeAudioCall(QString dsNumber, long nHand);
	//������Ƶ
	int makeVideoCall(QString dsNumber, long Hwnd, long nHand);
	//��ֹ�Ự
	int hangUpCall(long callid);

private:
	QAxWidget* pMulAxWidget_;

	long nhwnd;
public slots:
	void onMulEventRegistered(int code);

	void onMulEventConnected(int callId);
};

#endif