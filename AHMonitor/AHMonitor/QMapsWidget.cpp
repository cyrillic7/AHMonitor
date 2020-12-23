#include "QMapsWidget.h"
#include <QDir>
#include <QGridLayout>

QMapsWidget::QMapsWidget(QWidget *parent) : QWidget(parent)
{
	//qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--single-process");
	pWebView = new QWebEngineView(this);
	QGridLayout* glayout = new QGridLayout;
	glayout->addWidget(pWebView, 0, 0);

	this->setLayout(glayout);
}


QMapsWidget::~QMapsWidget()
{
}

void QMapsWidget::loadMap()
{
	QDir temDir("D:/Map/mapabc/lmap.html");
	QString absDir = temDir.absolutePath();
	QString filePath = "file:///" + absDir;
//	qDebug() << filePath;
	pWebView->load(QUrl(filePath));
}
