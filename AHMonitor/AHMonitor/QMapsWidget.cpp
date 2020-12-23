#include "QMapsWidget.h"
#include <QDir>
#include <QGridLayout>
#include <QCoreApplication>
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
	//QDir dir;
	//qDebug() << "currentPath : " + dir.currentPath();
	QDir temDir;// ("D:/AHMonitor/offmap/lmap.html");
	QString absDir = QCoreApplication::applicationDirPath() + "/lmap.html";
	QString filePath = "file:///" + absDir;
//	qDebug() << filePath;
	pWebView->load(QUrl(filePath));
}
