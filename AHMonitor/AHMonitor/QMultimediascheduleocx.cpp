#include "QMultimediascheduleocx.h"
#include <QDebug>
#include <QMessageBox>
#include <Windows.h>

QMultimediascheduleocx::QMultimediascheduleocx()
{
	pMulAxWidget_ = new QAxWidget;
	pMulAxWidget_->setControl(QString::fromUtf8("{3184B8DF-4D45-4664-B6D0-D4232294B2B2}"));
	QObject::connect(pMulAxWidget_, SIGNAL(onEventRegistered(int)), this, SLOT(onMulEventRegistered(int)));
	QObject::connect(pMulAxWidget_, SIGNAL(onEventConnected(int)), this, SLOT(onMulEventConnected(int)));
	//qDebug() << pMulAxWidget_->generateDocumentation();
}


QMultimediascheduleocx::~QMultimediascheduleocx()
{
}

int QMultimediascheduleocx::LogonSip(QString user, QString pasd, QString server, QString port)
{
	int ret = pMulAxWidget_->dynamicCall("registerSip(QString,QString,QString,QString)", user, pasd, server, port).toInt();
	if (ret == 0)
	{
		/*QMessageBox::information(NULL, "LogonSip",QString::number(ret),
			QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);*/
	}
	
	return ret;
}

int QMultimediascheduleocx::sendSMS(QString callNumber, QString Msg)
{
	int ret = pMulAxWidget_->dynamicCall("sendSMS(QString,QString)", callNumber, Msg).toInt();
	return ret;
}

long QMultimediascheduleocx::getPhysicsHandCount()
{
	long handcount = pMulAxWidget_->dynamicCall("getPhysicsHandCount()").toLongLong();
	return handcount;
}

int QMultimediascheduleocx::makeAudioCall(QString dsNumber, long nHand)
{
	qDebug() << "makeAudioCall start dsNumber:" << dsNumber << "nhand:" << nHand;
	int ret = pMulAxWidget_->dynamicCall("makeAudioCall(QString,long)", dsNumber, nHand).toInt();
	return 0;
}

int QMultimediascheduleocx::makeVideoCall(QString dsNumber, long Hwnd, long nHand)
{
	nhwnd = Hwnd;
	//int re = pMulAxWidget_->dynamicCall("setVideoWnd(long,long)", dsNumber.toLong(), Hwnd).toInt();
	qDebug() <<  "makeVideoCall start dsNumber:" << dsNumber << "Hwnd:" << Hwnd << "nhand:" << nHand;
	long ret = pMulAxWidget_->dynamicCall("makeVideoCall(QString,long,long)", dsNumber, Hwnd, nHand).toLongLong();
	/*if (ret >= 0)
	{
		qDebug() << "makeVideoCall success ret:" << ret << "Hwnd:" << Hwnd;
		ret = pMulAxWidget_->dynamicCall("setVideoWnd(long,long)", ret, Hwnd).toLongLong();

		qDebug() << "setVideoWnd ret:" << ret;
	}*/
	
	return ret;
}

int QMultimediascheduleocx::hangUpCall(long callid)
{

	return 0;
}

void QMultimediascheduleocx::onMulEventConnected(int callId)
{
	//qDebug() << "onMulEventConnected callid:" << called;
	QMessageBox::information(NULL, "onEventReg", QString::number(callId),
		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	qDebug() << "onMulEventConnected callId:" << callId << "Hwnd:" << nhwnd;
	long ret = pMulAxWidget_->dynamicCall("setVideoWnd(long,long)", callId, nhwnd).toLongLong();
	if (ret < 0)
	{
		qDebug() << "setVideoWnd failed ret:" << ret << "Hwnd:" << nhwnd;

	}
	//qDebug() << "setVideoWnd ret:" << ret;
}



void QMultimediascheduleocx::onMulEventRegistered(int code)
{
	if (code == 200)
	{
		qDebug() << "registerSip success!";
// 		QMessageBox::information(NULL, "onEventReg", QString::number(code),
// 			QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	}
	else
	{
		qDebug() << "registerSip failed!";
// 		QMessageBox::information(NULL, "onEventReg", QString::number(code),
// 			QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	}
}