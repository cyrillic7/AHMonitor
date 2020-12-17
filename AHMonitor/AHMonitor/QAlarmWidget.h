#ifndef _QALARM_WIDGET_H_
#define _QALARM_WIDGET_H_
#pragma once
#include "qwidget.h"
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QTableWidget>

class QAlarmWidget :
	public QWidget
{
	Q_OBJECT
public:
	QAlarmWidget(QWidget *parent);
	virtual ~QAlarmWidget();

private:
	QTableWidget* pTableWidget_;
public slots:
	//处理按钮单击
	void btnClicked();
};

#endif