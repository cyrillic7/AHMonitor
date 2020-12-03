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
	QFrame*			pModeFrame_;    //ģ��ͼ����ʾ����
	QGridLayout*	pGridLayout_;   //���񲼾���
	QVBoxLayout		mainlayout_;   //���򲼾ֹ�����

	void InitButton();


	void setVideoPanelWidget(VideoPanel* pWidget);
public slots:
	void GroupbuttonClick(int btTag);
};

#endif // !_TOOLS_SPLIT_