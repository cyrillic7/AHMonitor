#include "QPTZPosition.h"
#include <QMessageBox>
#pragma execution_character_set("utf-8")
QPTZPosition::QPTZPosition(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout* vLayout = new QVBoxLayout;
	QHBoxLayout* hLayout = new QHBoxLayout;
	btLeft = new QPushButton("<",this);
	btRight = new QPushButton(">", this);

	connect(btLeft, SIGNAL(clicked(bool)), this, SLOT(btnleft()));
	connect(btRight, SIGNAL(clicked(bool)), this, SLOT(btnright()));
	btLeft->setFixedWidth(20);
	btLeft->setFixedHeight(20);

	btRight->setFixedWidth(20);
	btRight->setFixedHeight(20);

	hLayout->addWidget(btLeft);
	hLayout->addWidget(new QLabel("预置位"));
	hLayout->addWidget(btRight);

	vLayout->addLayout(hLayout);

	btGridlayout = new QGridLayout;
	//按钮集合名称,如果需要新增按钮则在这里增加即可
	QList<QString> btns;
	btns << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8";
	//循环添加顶部按钮
	for (int i = 0; i < btns.count(); i++) {
		QPushButton *btn = new QPushButton;
		//绑定按钮单击事件,用来发出信号通知
		connect(btn, SIGNAL(clicked(bool)), this, SLOT(btnClicked()));
		//设置标识,用来区别按钮
		btn->setObjectName(btns.at(i));
		//
		btn->setText(btns.at(i));
		//设置固定宽度
		btn->setFixedWidth(35);
		//设置固定宽度
		btn->setFixedHeight(35);
		//设置焦点策略为无焦点,避免单击后焦点跑到按钮上
		btn->setFocusPolicy(Qt::NoFocus);

		if (i < 4)
		{
			btGridlayout->addWidget(btn, 0, i);
		}
		else
		{
			btGridlayout->addWidget(btn, 1, i-4);
		}

		btnList.push_back(btn);
	}

	vLayout->addLayout(btGridlayout);

	this->setLayout(vLayout);
}


QPTZPosition::~QPTZPosition()
{
	
}

void QPTZPosition::btnleft()
{
	currentPage--;
	if (currentPage < 0)
	{
		currentPage = 0;
		/*btLeft->hide();
		btRight->show();*/
		return;
	}

	int p = (currentPage * 8) + 1;

	for (auto it = btnList.begin(); it != btnList.end(); ++it)
	{
		(*it)->setObjectName(QString::number(p));
		(*it)->setText(QString::number(p++));
	}

}

void QPTZPosition::btnright()
{
	currentPage++;
	if (currentPage >= 32)
	{
		currentPage = 31;
		/*btLeft->show();
		btRight->hide();*/
		return;
	}

	int p = (currentPage * 8)+1;

	for (auto it = btnList.begin(); it != btnList.end(); ++it)
	{
		(*it)->setObjectName(QString::number(p));
		(*it)->setText(QString::number(p++));
	}
}

void QPTZPosition::btnClicked()
{
	QPushButton *btn = (QPushButton *)sender();
	
	QMessageBox::information(NULL, "Error", btn->objectName(),
		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	
}