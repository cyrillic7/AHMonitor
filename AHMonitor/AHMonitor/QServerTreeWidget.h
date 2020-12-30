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
	//更新item
	void updateServerTreeItem();
	//设备上下线
	void updateCamLine(int nSession,bool bOnline);
	//删除item
	void deleteServerItem(QString server);

signals:
	void recItemSession(int serverId,int session);

public slots:
//双击
	void TerminalItemDoubleClicked(QTreeWidgetItem* WidgetItem, int column);
	//单击
	void TerminalItemClicked(QTreeWidgetItem* WidgetItem, int column);
};

#endif