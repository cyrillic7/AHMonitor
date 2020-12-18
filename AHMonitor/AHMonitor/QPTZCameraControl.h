#ifndef _QPTZ_CAMERA_CONTROL_H_
#define _QPTZ_CAMERA_CONTROL_H_
#pragma once
#include "qwidget.h"
#include <QPushButton>
#include <QLabel>
#include <QSlider>
class QPTZCameraControl :
	public QWidget
{
	Q_OBJECT
public:
	QPTZCameraControl(QWidget *parent);
	virtual ~QPTZCameraControl();

	int getSpeed();
private:
	QPushButton* zoomPlus;
	QPushButton* zoomReduce;

	QPushButton* apertureBig;
	QPushButton* apertureSmall;

	QPushButton* focusingNear;
	QPushButton* focusingFar;

	QSlider* pSpeedSlider;
};

#endif