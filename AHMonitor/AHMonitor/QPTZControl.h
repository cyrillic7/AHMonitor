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

	int getSpeed();
signals:
	void gauCloudClicked(int nPosition);

	void CloudzoomPlus();
	void CloudzoomReduce();

	void CloudapertureBig();
	void CloudapertureSmall();

	void CloudfocusingNear();
	void CloudfocusingFar();

	void CloudFerPosition(int position);
	void CloudAction(QString & action);
public slots:
	void mouseClick(int position);

	void zoomPlusClick();
	void zoomReduceClick();
	void apertureBigClick();
	void apertureSmallClick();
	void focusingNearClick();
	void focusingFarClick();

	void positionClick(QString & objectName);
	void actionClick(QString & objectName);
};

#endif