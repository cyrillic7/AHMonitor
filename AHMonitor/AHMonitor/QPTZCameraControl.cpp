#include "QPTZCameraControl.h"
#include <QGridLayout>

#pragma execution_character_set("utf-8")
QPTZCameraControl::QPTZCameraControl(QWidget *parent) : QWidget(parent)
{
	zoomPlus = new QPushButton("+", this);
	zoomReduce = new QPushButton("-", this);

	apertureBig = new QPushButton("��", this);
	apertureSmall = new QPushButton("С", this);

	focusingNear = new QPushButton("��", this);
	focusingFar = new QPushButton("Զ", this);

	pSpeedSlider = new QSlider(this);
	pSpeedSlider->setOrientation(Qt::Horizontal);  // ˮƽ����
	pSpeedSlider->setMinimum(0);  // ��Сֵ
	pSpeedSlider->setMaximum(100);  // ���ֵ
	pSpeedSlider->setSingleStep(1);
	pSpeedSlider->setValue(33);

	QGridLayout* lLayout = new QGridLayout;

	lLayout->addWidget(new QLabel("����"), 0, 0);
	lLayout->addWidget(zoomPlus, 0, 1);
	lLayout->addWidget(zoomReduce, 0, 2);

	lLayout->addWidget(new QLabel("��Ȧ"), 1, 0);
	lLayout->addWidget(apertureBig, 1, 1);
	lLayout->addWidget(apertureSmall, 1, 2);

	lLayout->addWidget(new QLabel("�۽�"), 2, 0);
	lLayout->addWidget(focusingNear, 2, 1);
	lLayout->addWidget(focusingFar, 2, 2);

	lLayout->addWidget(new QLabel("�ٶ�"), 3, 0);
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
