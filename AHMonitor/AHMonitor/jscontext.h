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
	void recvdMsg(const QString& msg); //��mainwindow������Ϣ

public:
	// ��ҳ�淢����Ϣ
	void sendMsg(QWebEnginePage* page, const QString& msg);

	public slots:
	// ���յ�ҳ�淢��������Ϣ
	void onMsg(const QString& msg);
};

#endif // JSCONTEXT_H

