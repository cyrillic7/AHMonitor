#ifndef _ZX_CMT_PLAYER_H_
#define _ZX_CMT_PLAYER_H_
#pragma once
#include "qaxwidget.h"
//#include "cmtvideoplayerlib.h"
class ZXCmtPlayer :
	public QAxWidget
{
	Q_OBJECT
public:
	ZXCmtPlayer(QWidget *parent=0);
	virtual ~ZXCmtPlayer();

	void setVideoIndex(long index);
	long getHwnd();
};

#endif