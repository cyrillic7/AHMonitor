#include "AHMonitor.h"
#include "QLogonDialog.h"
#include <QGridLayout>
#include <QDesktopWidget>
#include <QApplication>
extern "C"
{
#include "libavformat/avformat.h"
};
#pragma execution_character_set("utf-8")

//INT64 _h264Handle = 0;
void UIEventCallBackHandler(MP_ENG_EVENT event, int nIndex, void *pParam, void *pAppData)
{
	switch (event)
	{
	case MP_EVENT_FPS:
		break;
	case MP_EVENT_BINDWIDTH:
		break;
	case MP_EVENT_PLR:
		break;
	case MP_EVENT_ERROR:
		break;
	case MP_EVENT_ACK:
		break;
	case MP_EVENT_CAMJOIN:
	{
		AHMonitor* pMonitor = (AHMonitor*)pAppData;
		pMonitor->updateCamOnLine(nIndex,true);
	}
	break;
	case MP_EVENT_CAMEXIT:
	{
		AHMonitor* pMonitor = (AHMonitor*)pAppData;
		pMonitor->updateCamOnLine(nIndex, false);
	}
		break;
	case MP_EVENT_WATERMARK_LOW:
		break;
	case MP_EVENT_WATERMARK_HIGH:
		break;
	case MP_EVENT_USER_LOGIN:
		break;
	case MP_EVENT_USER_LOGOUT:
		break;
	case MP_EVENT_USER_PWD_ERROR:
		break;
	case MP_EVENT_SERVER_DISCONNECT:
		break;
	case MP_EVENT_SERVER_CONNECT:
		break;
	case MP_EVENT_MOVE_DETECTION:
		break;
	case MP_EVENT_MOVE_STOP:
		break;
	case MP_EVENT_ALARM:
		break;
	case MP_EVENT_DISK_LOW:
		break;
	case MP_EVENT_DISK_FULL:
		break;
	case MP_EVENT_DATA_READY:
	{
	
	}

	break;
	}
}


AHMonitor::AHMonitor(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);

	pSDisConWidget_ = new QSDisConWidget(this);
	pSDisConWidget_->hide();
	connect(pSDisConWidget_, SIGNAL(serverConnect()), this, SLOT(onServerConnect()));
	connect(pSDisConWidget_, SIGNAL(serverDisConnect(const QString&)), this, SLOT(serverDisCon(const QString&)));

	pLogonDialog_ = new QLogonDialog(this);
	//pLogonDialog_->move((qApp->desktop()->availableGeometry().width() - width()) / 2 + qApp->desktop()->availableGeometry().x(),
	//	(qApp->desktop()->availableGeometry().height() - height()) / 2 + qApp->desktop()->availableGeometry().y());

	pVidoePanel_Widget_ = new VideoPanel(this);
	pToolsSplit_ = new QToolsSplit(this);
	pToolsSplit_->setVideoPanelWidget(pVidoePanel_Widget_);
	
	//m_pFrameStreamManager = new FrameStreamManager;
	m_pServerManager = new ServerManager;
	m_pPlayerManager = new CPlayerManager;
	m_pPlayerManager->setPanelWidget(pVidoePanel_Widget_);

	QMainWidget = new QWidget;
	this->setCentralWidget(QMainWidget);

	pTreeWidget_ = new QServerTreeWidget(this);
	pTreeWidget_->setMaximumWidth(280);

	QGridLayout* pMainLayout = new QGridLayout;
	QVBoxLayout* pControlLayout = new QVBoxLayout;
	pControlLayout->addWidget(pTreeWidget_);
	pMainLayout->addLayout(pControlLayout, 0, 0);

	pMainLayout->addWidget(pVidoePanel_Widget_, 0, 1);

	pMainLayout->addWidget(pToolsSplit_, 0, 2);

	QMainWidget->setLayout(pMainLayout);


	//创建动作、菜单、工具栏
	createActions();
	createMenus();
	createToolBars();

	CPlaybackEngine::Initialize("{D79399DA-2F36-4f7d-846A-292C90BA9E8D}");

	if (av_register == false)
	{
		av_register_all();

		avformat_network_init();
		av_register = true;

	}
}

AHMonitor::~AHMonitor()
{
	
}

void AHMonitor::updateTreeWidget()
{
	pTreeWidget_->updateServerTreeItem();
}

void AHMonitor::updateDisConWidget()
{
	ServerManager* pServerMng = ServerManager::getInstance();
	for (int i = 0; i < pServerMng->getServerCount(); i++)
	{
		CServerNode* pServerNode = pServerMng->getServerNode(i);
		QString strServerName;
		char *pTest = pServerNode->getCamServerInfo()->szCamServerName;
		strServerName = QString::fromLocal8Bit(pTest);

		pSDisConWidget_->additem(strServerName);
	}
}

void AHMonitor::updateCamOnLine(int nSession, bool bOnline)
{
	pTreeWidget_->updateCamLine(nSession, bOnline);
	pVidoePanel_Widget_->setVideoOffLine(nSession);
}

void AHMonitor::createActions()
{
	LinkAction_ = new QAction(tr("链接站点"), this);
	connect(LinkAction_, SIGNAL(triggered()), this, SLOT(onServerConnect()));

	unLinkAction_ = new QAction(tr("断开站点"), this);
	connect(unLinkAction_, SIGNAL(triggered()), this, SLOT(onServerDisConnect()));

	ExitAction_ = new QAction(tr("退出"), this);
	connect(ExitAction_, SIGNAL(triggered()), this, SLOT(close()));
}

void AHMonitor::createMenus()
{
	LinkMenu_ = menuBar()->addMenu(tr("路径"));
	LinkMenu_->addAction(LinkAction_);
	LinkMenu_->addAction(unLinkAction_);
	LinkMenu_->addAction(ExitAction_);


}

void AHMonitor::createToolBars()
{
	LinkTool_ = addToolBar("链接站点");
	LinkTool_->addAction(LinkAction_);
}

void AHMonitor::onServerConnect()
{
	if (pLogonDialog_->exec() == QDialog::Accepted)
	{
		updateDisConWidget();
		//updateDisConWidget();
		pTreeWidget_->updateServerTreeItem();
	}
}


void AHMonitor::onServerDisConnect()
{
	//if (pSDisConWidget_->exec() == QDialog::Accepted)
	//{
	//	
	//}
	pSDisConWidget_->exec();
}

void AHMonitor::serverDisCon(const QString & servername)
{
	/*QMessageBox::information(NULL, "Error", servername,
		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);*/

	ServerManager* pServerMng = ServerManager::getInstance();
	for (int i = 0; i < pServerMng->getServerCount(); i++)
	{
		CServerNode* pServerNode = pServerMng->getServerNode(i);
		QString strServerName;
		char *pServer = pServerNode->getCamServerInfo()->szCamServerName;
		strServerName = QString::fromLocal8Bit(pServer);
		if (servername == strServerName)
		{
			//断开连接
			int serverId = pServerNode->getCamerServerID();
			pVidoePanel_Widget_->CloseAllVideo();
			pTreeWidget_->deleteServerItem(servername);
			pServerNode->DisConnectServer(serverId);
			pServerMng->removeServerNode(serverId);

			pSDisConWidget_->removeItem(strServerName);
			CPlayerManager::getInstance()->setPlayerIndex(0);
			return;
		}

	}
}
