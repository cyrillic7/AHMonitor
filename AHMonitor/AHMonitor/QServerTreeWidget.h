#ifndef _SERVER_TREE_WIDGET_
#define _SERVER_TREE_WIDGET_
#pragma once

#include "qtreewidget.h"
#include "HeadFile.h";
#include "ServerManager.h"
class QServerTreeWidget :
	public QTreeWidget
{
	Q_OBJECT
public:
	QServerTreeWidget(QWidget *parent = 0);
	virtual ~QServerTreeWidget();

public:
	void updateServerTreeItem();

	void updateCamLine(int nSession,bool bOnline);

public slots:
	void TerminalItemDoubleClicked(QTreeWidgetItem* WidgetItem, int column);
};

#endif