#ifndef _PTZ_CONTROL_H_
#define _PTZ_CONTROL_H_
#pragma once
#include "qwidget.h"
#include <gaugecloud.h>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include "QPTZCameraControl.h"
#include "QPTZPosition.h"
#include "QPTZAction.h"

class QPTZControl :
	public QWidget
{
	Q_OBJECT
public:
	QPTZControl(QWidget *parent);
	virtual ~QPTZControl();

	GaugeCloud* pGauCloude_;
	QPTZCameraControl* pCameraCtl_;
	QPTZPosition* pPositionCtl_;
	QPTZAction* pActionCtl_;
public slots:
	void mouseClick(int position);
};

#endif