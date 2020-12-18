#include "widget.h"
#include "titlewidget.h"
#include <QVBoxLayout>
#include "mypushbutton.h"
#include <QLabel>
#include <QPainter>
#include <QBitmap>
#include <QDesktopWidget>
#include <QApplication>
#include <QTimer>
#include <QDesktopServices>
#include <QUrl>
#include <iostream>
#include <QDateTime>
using namespace std;
#pragma execution_character_set("utf-8")
Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    titleW=new titleWidget;
    connect(titleW,SIGNAL(myClose()),this,SLOT(close()));

	msgTime = new QLabel;
	msgTime->setWordWrap(true);
	msgTime->setAlignment(Qt::AlignTop);
	msgTime->setFixedSize(300, 50);

    content=new QLabel;
    content->setWordWrap(true);
    content->setAlignment(Qt::AlignTop);
    content->setFixedSize(300,50);
   /* btnLook=new myPushButton("look.png");
    connect(btnLook,SIGNAL(clicked()),this,SLOT(openWeb()));*/

    QVBoxLayout*mainLayout=new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(titleW);
	mainLayout->addWidget(msgTime);
    mainLayout->addWidget(content);
	mainLayout->addStretch();
   // content->setMargin(5);
   // mainLayout->addWidget(btnLook,0,Qt::AlignRight);
    setLayout(mainLayout);

    setFixedSize(sizeHint().width(),sizeHint().height());

    timerShow=new QTimer(this);
    connect(timerShow,SIGNAL(timeout()),this,SLOT(myMove()));
    timerStay=new QTimer(this);
    connect(timerStay,SIGNAL(timeout()),this,SLOT(myStay()));
    timerClose=new QTimer(this);
    connect(timerClose,SIGNAL(timeout()),this,SLOT(myClose()));
}

Widget::~Widget()
{
}

void Widget::setMsg(QString title, QString content, QString url)
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm::ss.zzz");
	msgTime->setText(current_date);
    titleW->setTitleText("  "+title);
    this->content->setText(content);
    this->url=url;
	showAsQQ();
}

void Widget::paintEvent(QPaintEvent *)
{
    QBitmap bitmap(this->size());
    bitmap.fill(Qt::white);
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(250,240,230)));
    painter.setPen(QPen(QBrush(QColor(255,222,173)),4));
    painter.drawRoundedRect(bitmap.rect(),5,5);
    setMask(bitmap);
}
void Widget::showAsQQ()
{
	setWindowOpacity(1.0);
    QDesktopWidget *deskTop=QApplication::desktop();
    deskRect=deskTop->availableGeometry();
	beginY = QApplication::desktop()->height();
	timeCount = 0;
    normalPoint.setX(deskRect.width()-rect().width());
    normalPoint.setY(deskRect.height()-rect().height());
    move(normalPoint.x(),768-1);
    show();
    timerShow->start(5);
	cout << "showAsQQ" << endl;
}
//平滑显示出来
void Widget::myMove()
{
	//static int beginy = beginY;
	beginY--;
    move(normalPoint.x(), beginY);
    if(beginY <=normalPoint.y())
    {
        timerShow->stop();
        timerStay->start(200);
    }
}
//停留显示
void Widget::myStay()
{
   // static int timeCount=0;
    timeCount++;
    if(timeCount>=9)
    {
        timerStay->stop();
        timerClose->start(200);
    }
}
//自动关闭时实现淡出效果
void Widget::myClose()
{
    static double tran=0.0;
    tran-=0.1;
    if(tran<=0.0)
    {
        timerClose->stop();
        emit close();
		//hide();
    }
    else
        setWindowOpacity(tran);
}
void Widget::openWeb()
{
    QDesktopServices::openUrl(QUrl(url));
}
