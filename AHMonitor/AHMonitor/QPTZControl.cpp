#include "QPTZControl.h"
#include <QGridLayout>
#include <QMessageBox>

#pragma execution_character_set("utf-8")
QPTZControl::QPTZControl(QWidget *parent) : QWidget(parent)
{
	QGridLayout* mainlayout = new QGridLayout;

	pGauCloude_ = new GaugeCloud(this);
	pGauCloude_->setMinimumSize(130, 130);
	connect(pGauCloude_, SIGNAL(mouseReleased(int)),this,SLOT(mouseClick(int)));

	pCameraCtl_ = new QPTZCameraControl(this);
	connect(pCameraCtl_->zoomPlus, SIGNAL(clicked()), this, SLOT(zoomPlusClick()));
	connect(pCameraCtl_->zoomReduce, SIGNAL(clicked()), this, SLOT(zoomReduceClick()));
	connect(pCameraCtl_->apertureBig, SIGNAL(clicked()), this, SLOT(apertureBigClick()));
	connect(pCameraCtl_->apertureSmall, SIGNAL(clicked()), this, SLOT(apertureSmallClick()));
	connect(pCameraCtl_->focusingNear, SIGNAL(clicked()), this, SLOT(focusingNearClick()));
	connect(pCameraCtl_->focusingFar, SIGNAL(clicked()), this, SLOT(focusingFarClick()));

	pPositionCtl_ = new QPTZPosition(this);
	pPositionCtl_->setMinimumSize(100, 100);
	connect(pPositionCtl_, SIGNAL(QPositionClicked(QString &)), this, SLOT(positionClick(QString &)));

	pActionCtl_ = new QPTZAction(this);
	pActionCtl_->setMinimumSize(100, 100);
	connect(pActionCtl_, SIGNAL(QActionClicked(QString &)), this, SLOT(actionClick(QString &)));

	mainlayout->addWidget(pGauCloude_,0,0,2,1);
	mainlayout->addWidget(pCameraCtl_, 0, 1,2,1);
	mainlayout->addWidget(pPositionCtl_, 3, 0);
	mainlayout->addWidget(pActionCtl_, 3, 1);

	this->setLayout(mainlayout);
}


QPTZControl::~QPTZControl()
{
}

int QPTZControl::getSpeed()
{
	return pCameraCtl_->getSpeed();
}

void QPTZControl::zoomPlusClick()
{
	emit CloudzoomPlus();
}

void QPTZControl::zoomReduceClick()
{
	emit CloudzoomReduce();
}

void QPTZControl::apertureBigClick()
{
	emit CloudapertureBig();
}

void QPTZControl::apertureSmallClick()
{
	emit CloudapertureSmall();
}

void QPTZControl::focusingNearClick()
{
	emit CloudfocusingNear();
}

void QPTZControl::focusingFarClick()
{
	emit CloudfocusingFar();
}

void QPTZControl::positionClick(QString & objectName)
{
	emit CloudFerPosition(objectName.toInt());
}

void QPTZControl::actionClick(QString & objectName)
{

}


void QPTZControl::mouseClick(int position)
{
	/*QMessageBox::information(NULL, "Error", QString::number(position),
		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);*/

	emit gauCloudClicked(position);
}