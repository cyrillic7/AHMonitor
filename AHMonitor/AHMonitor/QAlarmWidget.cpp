#include "QAlarmWidget.h"


#include <QMessageBox>
#pragma execution_character_set("utf-8")
QAlarmWidget::QAlarmWidget(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout* vLayout = new QVBoxLayout;

	pTableWidget_ = new QTableWidget(this);
	pTableWidget_->setColumnCount(2); //设置列数
	pTableWidget_->setColumnWidth(0, 160);  //0 设置列宽
	pTableWidget_->setColumnWidth(1, 160); //1 设置列宽
	QStringList header;
	header << "ID号" << "安装位置";
	pTableWidget_->setHorizontalHeaderLabels(header);

	QGridLayout* gLayout = new QGridLayout;
	QHBoxLayout* hlayout = new QHBoxLayout;
	QLabel* alarmtitle = new QLabel;
	//alarmtitle->setMaximumWidth(20);
	alarmtitle->setWordWrap(true);
	alarmtitle->setAlignment(Qt::AlignCenter);
	QString s = "报警输出";
	alarmtitle->setText(s.split("", QString::SkipEmptyParts).join("\n"));

	gLayout->addWidget(alarmtitle,1,0,2,1);

	gLayout->addWidget(new QLabel("1"), 0, 1);
	gLayout->addWidget(new QLabel("2"), 0, 2);
	gLayout->addWidget(new QLabel("3"), 0, 3);
	gLayout->addWidget(new QLabel("4"), 0, 4);

	QList<QString> btns;
	btns << "通" << "通" << "通" << "通" << "断" << "断" << "断" << "断";
	QList<QString> btnObjects;
	btnObjects << "t1" << "t2" << "t3" << "t4" << "d1" << "d2" << "d3" << "d4";
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
		btn->setFixedWidth(70);
		//设置固定宽度
		btn->setFixedHeight(25);
		//设置焦点策略为无焦点,避免单击后焦点跑到按钮上
		btn->setFocusPolicy(Qt::NoFocus);

		if (i < 4)
		{
			gLayout->addWidget(btn, 1, i+1);
		}
		else
		{
			gLayout->addWidget(btn, 2, i - 3);
		}

		//btnList.push_back(btn);
	}
	//hlayout->addLayout(gLayout);
	vLayout->addWidget(pTableWidget_);
	vLayout->addLayout(gLayout);

	this->setLayout(vLayout);
}


QAlarmWidget::~QAlarmWidget()
{
}

void QAlarmWidget::btnClicked()
{
	QPushButton *btn = (QPushButton *)sender();

	QMessageBox::information(NULL, "Error", btn->objectName(),
		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

}