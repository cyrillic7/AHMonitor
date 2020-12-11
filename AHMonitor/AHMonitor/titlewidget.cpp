#include "titlewidget.h"
#include <QLabel>
#include "mypushbutton.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QLinearGradient>
#include <QIcon>

titleWidget::titleWidget(QWidget *parent) :
    QWidget(parent)
{
    titleText=new QLabel;
    btnClose=new myPushButton("close.png");
    connect(btnClose,SIGNAL(clicked()),this,SIGNAL(myClose()));

    QHBoxLayout *layout=new QHBoxLayout;
    layout->addWidget(titleText,0,Qt::AlignLeft);
    layout->addStretch();
    layout->addWidget(btnClose,0,Qt::AlignRight);
    layout->setMargin(0);
    setLayout(layout);
    setFixedHeight(22);
}

void titleWidget::paintEvent(QPaintEvent *)
{
    QLinearGradient linear(rect().topLeft(),rect().bottomRight());
    linear.setColorAt(0,QColor(227,207,87));
    linear.setColorAt(0.5,QColor(245,222,179));
    linear.setColorAt(1,QColor(189,252,201));

    QPainter painter(this);
    painter.setBrush(QBrush(linear));
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());
}

void titleWidget::setTitleText(QString title)
{
    titleText->setText(title);
}
