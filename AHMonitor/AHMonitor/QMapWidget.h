#ifndef _QMAP_WIDGET_H_
#define _QMAP_WIDGET_H_
#pragma once
#include "qwidget.h"
#include <QWebEngineView>
#include <QWebChannel>
#include <QGridLayout>
#include "jscontext.h"
class QMapWidget :
	public QWidget
{
	Q_OBJECT
public:
	QMapWidget(QWidget *parent);
	virtual ~QMapWidget();

	void loadMap();
private:
	QWebEngineView *m_webView;    // QWebView对象
	JsContext *m_jsContext;
	QWebChannel *m_webChannel;
//private slots:
//	void onPageLoadFinished(bool);    // 地图加载完毕槽函数
//
//	public slots:
//	void onMapClickCallback();    // 点击地图时槽函数，必须是public的
};

#endif