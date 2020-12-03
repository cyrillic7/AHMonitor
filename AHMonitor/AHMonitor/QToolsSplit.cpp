#include "QToolsSplit.h"
#include <QMessageBox>

QToolsSplit::QToolsSplit(QWidget *parent) : QWidget(parent)
{
	pButtonGroup_ = new QButtonGroup;
	scrollArea_ = new QScrollArea(this);
	pModeFrame_ = new QFrame(scrollArea_);
	scrollArea_->setWidget(pModeFrame_);
	scrollArea_->setWidgetResizable(true);
	pGridLayout_ = new QGridLayout(pModeFrame_);
	pGridLayout_->setMargin(0);
	pGridLayout_->setSpacing(30);
	pModeFrame_->setLayout(pGridLayout_);
	InitButton();
	//pGridLayout_->addWidget(pButtonGroup_, 0, 0);
	mainlayout_.addWidget(scrollArea_);

	connect(pButtonGroup_, SIGNAL(buttonClicked(int)), this, SLOT(GroupbuttonClick(int)));

	this->setMinimumWidth(180);
	this->setMaximumWidth(200);
	this->setLayout(&mainlayout_);
}


QToolsSplit::~QToolsSplit()
{
}

void QToolsSplit::InitButton()
{
	for (int i = 0; i < 17; i++)
	{
		QPushButton *toolbutton = new QPushButton;

		toolbutton->setFixedSize(80,80);

		//toolbutton->setText("state 1");
		//pGridLayout_->addWidget(toolbutton, i, 0, 1, 1);

		toolbutton->setIconSize(QSize(79, 79));
		QString strIcon;
		strIcon = QString(":/Resources/Resources/icon/icon%1.png").arg(i);
		toolbutton->setIcon(QIcon(strIcon));

		pGridLayout_->addWidget(toolbutton, i, 0, 1, 1);
		pButtonGroup_->addButton(toolbutton, i);
	}
}

void QToolsSplit::setVideoPanelWidget(VideoPanel * pWidget)
{
	pVideoPanel_ = pWidget;
}


void QToolsSplit::GroupbuttonClick(int btTag)
{
	/*QMessageBox::information(NULL, "Error", QString::number(btTag),
		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);*/

	pVideoPanel_->hide_video_all();
	switch (btTag)
	{
	case 0:
	{
		pVideoPanel_->change_video(0, 1);
	}
	break;
	case 1:
	{
		pVideoPanel_->change_video(0, 2);
	}
	break;
	case 2:
	{
		pVideoPanel_->change_video(0, 3);
	}
	break;
	case 3:
	{
		pVideoPanel_->change_video(0, 4);
	}
	break;
	case 4:
	{
		pVideoPanel_->change_video_6(0);
	}
	break;
	case 5:
	{
		pVideoPanel_->change_video_8(0);
	}
	break;
	case 6:
	{
		pVideoPanel_->change_video_8(0);
	}
	break;
	case 7:
	{
		pVideoPanel_->change_video_4(0);
	}
	break;
	case 8:
	{
		pVideoPanel_->change_video_4(0);
	}
	break;
	case 9:
	{
		pVideoPanel_->change_video_13(0);
	}
	break;
	case 10:
	{
		pVideoPanel_->change_video_16(0);
	}
	break;
	case 11:
	{
		pVideoPanel_->change_video_25(0);
	}
	break;
	case 12:
	{
		pVideoPanel_->change_video_25(0);
	}
	break;
	case 13:
	{
		pVideoPanel_->change_video_25(0);
	}
	break;
	case 14:
	{
		pVideoPanel_->change_video_36(0);
	}
	break;
	case 15:
	{
		pVideoPanel_->change_video_36(0);
	}
	break;
	case 16:
	{
		pVideoPanel_->change_video_64(0);
	}
	break;
	default:
		break;
	}
}