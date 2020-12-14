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

private:
	QComboBox* pCombResolution_;
	QSpinBox* pKeySpacing_;
	QSpinBox* pKeyFrame_;
	QComboBox* pCombCodeMode_;
	QComboBox* pCombCodeLevel_;

	QPushButton* pDefault_;
	QPushButton* pSet_;
	QPushButton* pRestart_;
};

#endif