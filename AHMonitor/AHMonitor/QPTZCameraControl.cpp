#include "QPTZCameraControl.h"
#include <QGridLayout>

#pragma execution_character_set("utf-8")
QPTZCameraControl::QPTZCameraControl(QWidget *parent) : QWidget(parent)
{
	zoomPlus = new QPushButton("+", this);
	zoomReduce = new QPushButton("-", this);

	apertureBig = new QPushButton("大", this);
	apertureSmall = new QPushButton("小", this);

	focusingNear = new QPushButton("近", this);
	focusingFar = new QPushButton("远", this);

	pSpeedSlider = new QSlider(this);
	pSpeedSlider->setOrientation(Qt::Horizontal);  // 水平方向
	pSpeedSlider->setMinimum(0);  // 最小值
	pSpeedSlider->setMaximum(100);  // 最大值
	pSpeedSlider->setSingleStep(1);
	pSpeedSlider->setValue(33);

	QGridLayout* lLayout = new QGridLayout;

	lLayout->addWidget(new QLabel("缩放"), 0, 0);
	lLayout->addWidget(zoomPlus, 0, 1);
	lLayout->addWidget(zoomReduce, 0, 2);

	lLayout->addWidget(new QLabel("光圈"), 1, 0);
	lLayout->addWidget(apertureBig, 1, 1);
	lLayout->addWidget(apertureSmall, 1, 2);

	lLayout->addWidget(new QLabel("聚焦"), 2, 0);
	lLayout->addWidget(focusingNear, 2, 1);
	lLayout->addWidget(focusingFar, 2, 2);

	lLayout->addWidget(new QLabel("速度"), 3, 0);
	lLayout->addWidget(pSpeedSlider, 3, 1, 1, 2);

	this->setLayout(lLayout);
}


QPTZCameraControl::~QPTZCameraControl()
{
}

int QPTZCameraControl::getSpeed()
{
	return pSpeedSlider->value();
}
