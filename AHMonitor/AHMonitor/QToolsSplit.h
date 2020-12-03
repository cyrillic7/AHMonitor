#ifndef _TOOLS_SPLIT_
#define _TOOLS_SPLIT_

#pragma once
#include "qwidget.h"
#include <QScrollArea>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QButtonGroup>
#include "videopanel.h"

class QToolsSplit :
	public QWidget
{
	Q_OBJECT
public:
	QToolsSplit(QWidget *parent = 0);
	virtual ~QToolsSplit();

	VideoPanel* pVideoPanel_;

	QButtonGroup*   pButtonGroup_;
	QScrollArea*	scrollArea_;
	QFrame*			pModeFrame_;    //模块图标显示区域
	QGridLayout*	pGridLayout_;   //网格布局器
	QVBoxLayout		mainlayout_;   //竖向布局管理器

	void InitButton();


	void setVideoPanelWidget(VideoPanel* pWidget);
public slots:
	void GroupbuttonClick(int btTag);
};

#endif // !_TOOLS_SPLIT_