#include "QMapsWidget.h"
#include <QDir>
#include <QGridLayout>
#include <QCoreApplication>
#include <QWebChannel>
#include <QNetworkProxyFactory>
#define bridgeins bridge::instance()

QMapsWidget::QMapsWidget(QWidget *parent) : QWidget(parent)
{
	//QNetworkProxyFactory::setUseSystemConfiguration(false);
	//qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--single-process");

	//QWebChannel *channel = new QWebChannel(this);
	//channel->registerObject("bridge", (QObject*)bridgeins);
	//pWebView = new QWebEngineView(this);
	//pWebView->page()->setWebChannel(channel);

	//loadMap();
	//bridgeins->Init();
	//bridgeins->AddLight("33496", "111", 30.228742, 120.11787, 0);
	//bridgeins->AddLight("33496", "111", 30.229742, 120.11987, 0);
	//QGridLayout* glayout = new QGridLayout;
	//glayout->addWidget(pWebView, 0, 0);

	//this->setLayout(glayout);
}


QMapsWidget::~QMapsWidget()
{
}

void QMapsWidget::loadMap()
{
	QWebChannel *channel = new QWebChannel(this);
	channel->registerObject("bridge", (QObject*)bridgeins);
	pWebView = new QWebEngineView(this);
	pWebView->page()->setWebChannel(channel);

	QDir temDir;// ("D:/AHMonitor/offmap/lmap.html");
	QString absDir = QCoreApplication::applicationDirPath() + "/lmap.html";
	QString filePath = "file:///" + absDir;
	//	qDebug() << filePath;
	pWebView->load(QUrl(filePath));

	bridgeins->Init();
	bridgeins->AddLight("33496", "111", 30.228742, 120.11787, 0);
	bridgeins->AddLight("33496", "111", 30.239742, 120.11987, 0);
	QGridLayout* glayout = new QGridLayout;
	glayout->addWidget(pWebView, 0, 0);

	this->setLayout(glayout);
}
