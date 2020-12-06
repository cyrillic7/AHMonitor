#include "QSDisConWidget.h"
#include <QGridLayout>

#pragma execution_character_set("utf-8")
QSDisConWidget::QSDisConWidget(QWidget *parent) :QDialog(parent)
{
	pListWidget_ = new QListWidget(this);
	pBtDisCon_ = new QPushButton("断开连接");
	pBtCancel_ = new QPushButton("关闭");
	pBtNewCon_ = new QPushButton("建立连接");

	connect(pBtDisCon_, SIGNAL(clicked()), this, SLOT(serverDisConnect()));
	connect(pBtCancel_, SIGNAL(clicked()), this, SLOT(onCancel()));
	connect(pBtNewCon_, SIGNAL(clicked()), this, SLOT(newConnect()));

	this->setWindowTitle("断开连接");

	QVBoxLayout* pVLayout = new QVBoxLayout;

	pVLayout->addWidget(pListWidget_);

	QHBoxLayout* pHLayout = new QHBoxLayout;
	pHLayout->addWidget(pBtNewCon_);
	pHLayout->addStretch();
	pHLayout->addWidget(pBtDisCon_);
	pHLayout->addWidget(pBtCancel_);

	pVLayout->addLayout(pHLayout);

	this->resize(QSize(360,360));
	this->setLayout(pVLayout);
}


QSDisConWidget::~QSDisConWidget()
{
}

void QSDisConWidget::serverDisConnect()
{
	QListWidgetItem* item = pListWidget_->currentItem();
	currentRow_ = pListWidget_->currentRow();
	emit serverDisConnect(item->text());
}

void QSDisConWidget::additem(QString strItem)
{
	pListWidget_->addItem(strItem);
}

void QSDisConWidget::removeItem(QString strItem)
{
	if (currentRow_ == -1)
	{
		return;
	}

	QListWidgetItem * pitem;

	pitem = pListWidget_->takeItem(currentRow_);
	pListWidget_->removeItemWidget(pitem);

	delete pitem;
}

void QSDisConWidget::onCancel()
{
	QDialog::reject();
}

void QSDisConWidget::newConnect()
{
	this->hide();
	emit serverConnect();
}
