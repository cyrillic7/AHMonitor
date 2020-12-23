#ifndef _QPTZ_ACTION_H_
#define _QPTZ_ACTION_H_
#pragma once
#include "qwidget.h"
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
class QPTZAction :
	public QWidget
{
	Q_OBJECT
public:
	QPTZAction(QWidget *parent);
	virtual ~QPTZAction();

private:
	QLabel* pScanlabel_;
	QLabel* pCruiselabel_;
	QLabel* pInfraredlabel_;
	QLabel* pWiperlabel_;

signals:
	void QActionClicked(QString & objectName);

public slots:
	//处理按钮单击
	void btnClicked();
};

#endif