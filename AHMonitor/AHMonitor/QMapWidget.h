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
	QWebEngineView *m_webView;    // QWebView����
	JsContext *m_jsContext;
	QWebChannel *m_webChannel;
//private slots:
//	void onPageLoadFinished(bool);    // ��ͼ������ϲۺ���
//
//	public slots:
//	void onMapClickCallback();    // �����ͼʱ�ۺ�����������public��
};

#endif