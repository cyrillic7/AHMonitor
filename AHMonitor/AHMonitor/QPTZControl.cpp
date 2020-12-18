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

	pPositionCtl_ = new QPTZPosition(this);
	pPositionCtl_->setMinimumSize(100, 100);
	pActionCtl_ = new QPTZAction(this);
	pActionCtl_->setMinimumSize(100, 100);
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


void QPTZControl::mouseClick(int position)
{
	/*QMessageBox::information(NULL, "Error", QString::number(position),
		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);*/

	emit gauCloudClicked(position);
}