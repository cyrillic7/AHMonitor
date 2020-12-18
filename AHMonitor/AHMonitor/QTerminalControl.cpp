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
	pQuaStep_ = new QSpinBox(this);
	pCodeRate_ = new QSpinBox(this);

	QHBoxLayout* Btlayout = new QHBoxLayout;
	pDefault_ = new QPushButton("恢复默认");
	pSet_ = new QPushButton("设置");
	pRestart_ = new QPushButton("重启");

	Btlayout->addWidget(pDefault_);
	Btlayout->addWidget(pSet_);
	Btlayout->addWidget(pRestart_);

	pCombResolution_->addItem("大");
	pCombResolution_->addItem("中");
	pCombResolution_->addItem("小");
	pCombResolution_->setCurrentIndex(1);

	//pCombCodeMode_->addItem("FIX_QP");
	pCombCodeMode_->addItem("CBR");
	pCombCodeMode_->addItem("VBR");
	pCombCodeMode_->setCurrentIndex(1);

	pCombCodeLevel_->addItem("1");
	pCombCodeLevel_->addItem("2");
	pCombCodeLevel_->addItem("3");
	pCombCodeLevel_->addItem("4");
	pCombCodeLevel_->addItem("5");
	pCombCodeLevel_->addItem("6");
	pCombCodeLevel_->addItem("7");
	pCombCodeLevel_->addItem("8");
	pCombCodeLevel_->setCurrentIndex(2);

	pKeySpacing_->setRange(1,1500);
	pKeySpacing_->setValue(25);

	pKeyFrame_->setRange(1, 25);
	pKeyFrame_->setValue(25);

	pQuaStep_->setRange(2, 31);
	pQuaStep_->setValue(10);
	pCodeRate_->setRange(1, 1500);
	pCodeRate_->setValue(300);

	MainLayout->addWidget(new QLabel("分辨率:"), 0, 0);
	MainLayout->addWidget(pCombResolution_, 0, 1);

	MainLayout->addWidget(new QLabel("关键帧间隔(1~1000):"), 1, 0);
	MainLayout->addWidget(pKeySpacing_, 1, 1);

	MainLayout->addWidget(new QLabel("帧率(1~25):"), 2, 0);
	MainLayout->addWidget(pKeyFrame_, 2, 1);

	MainLayout->addWidget(new QLabel("编码质量模式:"), 3, 0);
	MainLayout->addWidget(pCombCodeMode_, 3, 1);

	MainLayout->addWidget(new QLabel("编码质量登记:"), 4, 0);
	MainLayout->addWidget(pCombCodeLevel_, 4, 1);

	MainLayout->addWidget(new QLabel("量化步长(2~31)"), 5, 0);
	MainLayout->addWidget(pQuaStep_, 5, 1);

	MainLayout->addWidget(new QLabel("码率(10~1000)"), 6, 0);
	MainLayout->addWidget(pCodeRate_, 6, 1);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addLayout(MainLayout);
	vLayout->addLayout(Btlayout);

	this->setMaximumHeight(280);
	this->setLayout(vLayout);
}


QTerminalControl::~QTerminalControl()
{
}

void QTerminalControl::setVideoParam(int size, int keyspace, int keyfps, int cmode, int clevel, int qstep, int crate)
{
	pCombResolution_->setCurrentIndex(size-1);
	pKeySpacing_->setValue(keyspace);
	pKeyFrame_->setValue(keyfps);
	pCombCodeMode_->setCurrentIndex(cmode);
	pCombCodeLevel_->setCurrentIndex(clevel);
	pQuaStep_->setValue(qstep);
	pCodeRate_->setValue(crate);
}

int QTerminalControl::getVideoSize()
{
	int size = pCombResolution_->currentIndex()+1;
	return size;
}

int QTerminalControl::getmaxFPS()
{
	int fps = pKeyFrame_->text().toInt();
	return fps;
}

int QTerminalControl::getquality()
{
	int quality = pCombCodeLevel_->currentIndex();
	return quality;
}

int QTerminalControl::getKeySpacing()
{
	int keyS = pKeySpacing_->text().toInt();
	return keyS;
}

int QTerminalControl::getCodeMode()
{
	int modeIndex = pCombCodeMode_->currentIndex();
	return modeIndex;
}

int QTerminalControl::getQuaStep()
{
	int quaStep = pQuaStep_->text().toInt();
	return quaStep;
}

int QTerminalControl::getCodeRate()
{
	int codeRate = pCodeRate_->text().toInt();
	return codeRate;
}
