#include "QMapWidget.h"
#include <QFile>
#include <QCoreApplication>
#include <QNetworkProxyFactory>
#pragma execution_character_set("utf-8")
QMapWidget::QMapWidget(QWidget *parent) : QWidget(parent)
{
	QNetworkProxyFactory::setUseSystemConfiguration(false);
	m_webView = new QWebEngineView(this);
	//connect(m_webView, SIGNAL(loadFinished(bool)), this, SLOT(onPageLoadFinished(bool)));
	m_jsContext = new JsContext(this);
	m_webChannel = new QWebChannel(this);
	m_webChannel->registerObject("context", (QObject*)m_jsContext);
	m_webView->page()->setWebChannel(m_webChannel);

	//QString htmlPath = QCoreApplication::applicationDirPath() + "/map.html";
	//QFile file(htmlPath);//直接加载本地html文件，外部对象由本地文件的相对路径查找，因此不需要设置
	//if (!file.exists())
	//{
	//	return;
	//}
	//m_webView->load(QUrl("file:///" + htmlPath));
	/*connect(m_jsContext, &JsContext::recvdMsg, this, [this](const QString& msg) {
		ui->statusBar->showMessage(QString("Received message：%1").arg(msg), 3000);
	});*/

	/*connect(ui->btnSend, &QPushButton::clicked, this, [this]() {
		QString msg = ui->msgEdit->text();
		if (!msg.isEmpty())
		{
			m_jsContext->sendMsg(m_webView->page(), msg);
		}
	});*/
	QGridLayout* glayout = new QGridLayout;
	glayout->addWidget(m_webView, 0, 0);

	this->setLayout(glayout);
}


QMapWidget::~QMapWidget()
{
}

void QMapWidget::loadMap()
{
	QString htmlPath = QCoreApplication::applicationDirPath() + "/gaode_Map.html";
	QFile file(htmlPath);//直接加载本地html文件，外部对象由本地文件的相对路径查找，因此不需要设置
	if (!file.exists())
	{
		return;
	}
	m_webView->load(QUrl("file:///" + htmlPath));
}
