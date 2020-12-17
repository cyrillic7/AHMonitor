//jscontext.h
#ifndef JSCONTEXT_H
#define JSCONTEXT_H

#include <QObject>
#include <QWebEnginePage>
#include <QJSEngine>
class JsContext : public QObject
{

	Q_OBJECT
public:
	explicit JsContext(QObject *parent = nullptr);

signals:
	void recvdMsg(const QString& msg); //向mainwindow传递消息

public:
	// 向页面发送消息
	void sendMsg(QWebEnginePage* page, const QString& msg);

	public slots:
	// 接收到页面发送来的消息
	void onMsg(const QString& msg);
};

#endif // JSCONTEXT_H

