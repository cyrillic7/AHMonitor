#ifndef _QLOGON_DIALOG_
#define _QLOGON_DIALOG_

#pragma once
#include "HeadFile.h"
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>

class QLogonDialog :
	public QDialog
{
	Q_OBJECT
public:
	QLogonDialog(QWidget *parent = 0);
	virtual ~QLogonDialog();

protected:
	QLineEdit* pAccountEdit_;
	QLineEdit* pPasswordEdit_;
	QLineEdit* pAddressEdit_;
	QLineEdit* pPortEdit_;

	QPushButton* pBtnLogon_;
	QPushButton* pBtnCancel_;

public slots:
	void onLogonClicked();
	void onCancelClicked();
	
};

#endif