#include "QTerminalControl.h"
#include <QGridLayout>

#pragma execution_character_set("utf-8")
QTerminalControl::QTerminalControl(QWidget *parent) : QWidget(parent)
{
	QGridLayout* MainLayout = new QGridLayout;

	pCombResolution_ = new QComboBox(this);
	pKeySpacing_ = new QSpinBox(this);
	pKeyFrame_ = new QSpinBox(this);
	pCombCodeMode_ = new QComboBox(this);
	pCombCodeLevel_ = new QComboBox(this);

	QHBoxLayout* Btlayout = new QHBoxLayout;
	pDefault_ = new QPushButton("�ָ�Ĭ��");
	pSet_ = new QPushButton("����");
	pRestart_ = new QPushButton("����");

	Btlayout->addWidget(pDefault_);
	Btlayout->addWidget(pSet_);
	Btlayout->addWidget(pRestart_);

	pCombResolution_->addItem("��");
	pCombResolution_->addItem("��");
	pCombResolution_->addItem("С");

	pCombCodeMode_->addItem("FIX_QP");
	pCombCodeMode_->addItem("VBR");
	pCombCodeMode_->addItem("CBR");
	pCombCodeMode_->setCurrentIndex(1);

	pCombCodeLevel_->addItem("1");
	pCombCodeLevel_->addItem("2");
	pCombCodeLevel_->addItem("3");
	pCombCodeLevel_->addItem("4");
	pCombCodeLevel_->addItem("5");
	pCombCodeLevel_->addItem("6");
	pCombCodeLevel_->addItem("7");
	pCombCodeLevel_->addItem("8");
	pCombCodeLevel_->setCurrentIndex(6);

	pKeySpacing_->setRange(1,1500);
	pKeySpacing_->setValue(1000);

	pKeyFrame_->setRange(1, 25);
	pKeyFrame_->setValue(25);

	MainLayout->addWidget(new QLabel("�ֱ���:"), 0, 0);
	MainLayout->addWidget(pCombResolution_, 0, 1);

	MainLayout->addWidget(new QLabel("�ؼ�֡���(1~1000):"), 1, 0);
	MainLayout->addWidget(pKeySpacing_, 1, 1);

	MainLayout->addWidget(new QLabel("֡��(1~25):"), 2, 0);
	MainLayout->addWidget(pKeyFrame_, 2, 1);

	MainLayout->addWidget(new QLabel("��������ģʽ:"), 3, 0);
	MainLayout->addWidget(pCombCodeMode_, 3, 1);

	MainLayout->addWidget(new QLabel("���������Ǽ�:"), 4, 0);
	MainLayout->addWidget(pCombCodeLevel_, 4, 1);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addLayout(MainLayout);
	vLayout->addLayout(Btlayout);

	this->setMaximumHeight(200);
	this->setLayout(vLayout);
}


QTerminalControl::~QTerminalControl()
{
}
