#include "QPTZAction.h"

#include <QMessageBox>
#pragma execution_character_set("utf-8")
QPTZAction::QPTZAction(QWidget *parent) : QWidget(parent)
{
	QGridLayout* gLayout = new QGridLayout;
	pScanlabel_ = new QLabel("扫描", this);
	pCruiselabel_ = new QLabel("巡航", this);
	pInfraredlabel_ = new QLabel("红外", this);
	pWiperlabel_ = new QLabel("雨刷", this);

	pScanlabel_->setWordWrap(true);
	pScanlabel_->setAlignment(Qt::AlignCenter);
	pCruiselabel_->setWordWrap(true);
	pCruiselabel_->setAlignment(Qt::AlignCenter);
	pInfraredlabel_->setWordWrap(true);
	pInfraredlabel_->setAlignment(Qt::AlignCenter);
	pWiperlabel_->setWordWrap(true);
	pWiperlabel_->setAlignment(Qt::AlignCenter);

	//QHBoxLayout* hLayout = new QHBoxLayout;
	gLayout->addWidget(pScanlabel_,0,0);
	gLayout->addWidget(pCruiselabel_,0,1);
	gLayout->addWidget(pInfraredlabel_,0,2);
	gLayout->addWidget(pWiperlabel_,0,3);

	QList<QString> btns;
	btns << "启" << "启" << "启" << "启" << "停" << "停" << "停" << "停";
	QList<QString> btnObjects;
	btnObjects << "ss" << "xs" << "hs" << "ys" << "sp" << "xp" << "hp" << "yp";
	//循环添加顶部按钮
	for (int i = 0; i < btns.count(); i++) {
		QPushButton *btn = new QPushButton;
		//绑定按钮单击事件,用来发出信号通知
		connect(btn, SIGNAL(clicked(bool)), this, SLOT(btnClicked()));
		//设置标识,用来区别按钮
		btn->setObjectName(btnObjects.at(i));
		//设置文字内容
		btn->setText(btns.at(i));
		//设置固定宽度
		btn->setFixedWidth(30);
		//设置固定宽度
		btn->setFixedHeight(30);
		//设置焦点策略为无焦点,避免单击后焦点跑到按钮上
		btn->setFocusPolicy(Qt::NoFocus);

		if (i < 4)
		{
			gLayout->addWidget(btn, 1, i);
		}
		else
		{
			gLayout->addWidget(btn, 2, i - 4);
		}

		//btnList.push_back(btn);
	}

	//gLayout->addLayout(hLayout, 0, 0);
	
	this->setLayout(gLayout);
}


QPTZAction::~QPTZAction()
{
}

void QPTZAction::btnClicked()
{
	QPushButton *btn = (QPushButton *)sender();

	QMessageBox::information(NULL, "Error", btn->objectName(),
		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

}