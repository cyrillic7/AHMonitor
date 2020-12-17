#ifndef _TERMINAL_CONTROL_H_
#define _TERMINAL_CONTROL_H_
#pragma once

#include "qwidget.h"
#include <QComboBox>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>

class QTerminalControl :
	public QWidget
{
	Q_OBJECT
public:
	QTerminalControl(QWidget *parent);
	virtual ~QTerminalControl();

	void setSession(int session) { nSession_ = session; }
	int getSession() { return nSession_; }

	void setServer(int serverId) { nServer_ = serverId; }
	int getServerId() { return nServer_; }

	void setVideoParam(int size, int keyspace, int keyfps , int cmode, int clevel, int qstep, int crate);

	int getVideoSize();
	int getmaxFPS();
	int getquality();
	int getKeySpacing();
	int getCodeMode();
private:
	int nSession_ = 0;
	int nServer_ = 0;
	QComboBox* pCombResolution_;
	QSpinBox* pKeySpacing_;
	QSpinBox* pKeyFrame_;
	QComboBox* pCombCodeMode_;
	QComboBox* pCombCodeLevel_;
	QSpinBox*  pQuaStep_;
	QSpinBox* pCodeRate_;
public:
	QPushButton* pDefault_;
	QPushButton* pSet_;
	QPushButton* pRestart_;
};

#endif