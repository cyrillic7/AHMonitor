#ifndef _QPTZ_POSITION_H_
#define _QPTZ_POSITION_H_
#pragma once
#include "qwidget.h"
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
using namespace std;
class QPTZPosition :
	public QWidget
{
	Q_OBJECT
public:
	QPTZPosition(QWidget *parent);
	virtual ~QPTZPosition();

private:
	std::list<QPushButton*> btnList;
	QGridLayout* btGridlayout;
	QPushButton* btRight;
	QPushButton* btLeft;
	int currentPage = 0;
public slots:
	//处理按钮单击
	void btnClicked();

	void btnleft();
	void btnright();
};

#endif