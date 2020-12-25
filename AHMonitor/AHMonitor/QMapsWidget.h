#ifndef _QMAPS_WIDGET_H_
#define _QMAPS_WIDGET_H_

#pragma once
#include "qwidget.h"
#include "bridge.h"
#include <QWebEngineView>
class QMapsWidget :
	public QWidget
{
	Q_OBJECT
public:
	QMapsWidget(QWidget *parent = 0);
	virtual ~QMapsWidget();

public:
	void loadMap();
public:
	QWebEngineView* pWebView;
};

#endif