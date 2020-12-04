#ifndef _QSDIS_CON_WIDGET_H_
#define _QSDIS_CON_WIDGET_H_
#pragma once
#include "qwidget.h"
#include <QListWidget>
#include <QPushButton>
#include <QDialog>
class QSDisConWidget :
	public QDialog
{
	Q_OBJECT
public:
	QSDisConWidget(QWidget *parent = 0);
	virtual ~QSDisConWidget();

	void additem(QString strItem);
private:
	QListWidget* pListWidget_;
	QPushButton* pBtDisCon_;
	QPushButton* pBtCancel_;
	QPushButton* pBtNewCon_;

signals:
	void serverConnect();

	void serverDisConnect(const QString& servername);

public slots:
	void serverDisConnect();
	void onCancel();
	void newConnect();
};

#endif // !_QSDIS_CON_WIDGET_H_