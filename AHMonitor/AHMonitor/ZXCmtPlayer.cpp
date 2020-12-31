#include "ZXCmtPlayer.h"
#include <QDebug>


ZXCmtPlayer::ZXCmtPlayer(QWidget *parent)
{
	this->setControl(QString::fromUtf8("{790B714B-552A-4C40-AA78-4FC72C8F7AF8}"));
	//this->dynamicCall("setVpIndex(long)", 0);
	//QString sUrl = "www.baidu.com";
	//this->dynamicCall("Navigate(const QString&)", sUrl);
	int hwnd = this->dynamicCall("GetHWnd()").toLongLong();
	qDebug() << "hwnd" << hwnd;
	/*qDebug() << this->generateDocumentation();*/

	/*CmtVideoPlayerLib::CmtVideoPlayer player;
	int hwnd = player.GetHWnd();
	qDebug() << "hwnd" << hwnd; */
}


ZXCmtPlayer::~ZXCmtPlayer()
{
}


void ZXCmtPlayer::setVideoIndex(long index)
{
	this->dynamicCall("setVpIndex(long)", index).toLongLong();
}

long ZXCmtPlayer::getHwnd()
{
	return this->dynamicCall("GetHWnd()").toLongLong();
}
