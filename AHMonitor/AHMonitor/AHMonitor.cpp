#include "AHMonitor.h"
#include "QLogonDialog.h"
#include <QGridLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QSplitter>
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
		pMonitor->updateCamOnLine(nIndex, true);
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
	{
		/*QMessageBox::information(NULL, "Error", "MP_EVENT_USER_LOGIN",
			QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);*/
	}
		break;
	case MP_EVENT_USER_LOGOUT:
	{
		/*QMessageBox::information(NULL, "Error", "MP_EVENT_USER_LOGOUT",
			QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);*/
	}
		break;
	case MP_EVENT_USER_PWD_ERROR:
	{
		/*QMessageBox::information(NULL, "Error", "MP_EVENT_USER_PWD_ERROR",
			QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);*/
	}
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
	MsgShowWidget_ = new Widget;
	connect(this, SIGNAL(showMsg(QString, QString, QString)), MsgShowWidget_,SLOT(setMsg(QString, QString, QString)));
	//pLogonDialog_->move((qApp->desktop()->availableGeometry().width() - width()) / 2 + qApp->desktop()->availableGeometry().x(),
	//	(qApp->desktop()->availableGeometry().height() - height()) / 2 + qApp->desktop()->availableGeometry().y());

	pVidoePanel_Widget_ = new VideoPanel(this);
	pToolsSplit_ = new QToolsSplit(this);
	pToolsSplit_->setVideoPanelWidget(pVidoePanel_Widget_);
	
	//m_pFrameStreamManager = new FrameStreamManager;
	m_pServerManager = new ServerManager;
	m_pPlayerManager = new CPlayerManager;
	m_pPlayerManager->setPanelWidget(pVidoePanel_Widget_);

	QSplitter *splitterMain = new QSplitter(Qt::Horizontal, this);
	splitterMain->setOpaqueResize(true);
	splitterMain->setChildrenCollapsible(false);


	QMainWidget = new QWidget;
	this->setCentralWidget(QMainWidget);

	pTreeWidget_ = new QServerTreeWidget(this);
	pTreeWidget_->setMinimumWidth(250);
	pTreeWidget_->setMaximumWidth(350);

	QGridLayout* pMainLayout = new QGridLayout;
	QVBoxLayout* pControlLayout = new QVBoxLayout;
	/*pControlLayout->addWidget(pTreeWidget_);

	pMainLayout->addLayout(pControlLayout, 0, 0);

	pMainLayout->addWidget(pVidoePanel_Widget_, 0, 1);

	pMainLayout->addWidget(pToolsSplit_, 0, 2);*/

	splitterMain->addWidget(pTreeWidget_);
	splitterMain->addWidget(pVidoePanel_Widget_);
	splitterMain->addWidget(pToolsSplit_);

	pMainLayout->addWidget(splitterMain);
	QMainWidget->setLayout(pMainLayout);

	//updateCamOnLine(1, true);
	//�����������˵���������
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

	QString strTitle;
	if (bOnline == true)
	{
		strTitle = "��Ƶ����";
	}
	else
	{
		strTitle = "��Ƶ����";
	}
	emit showMsg(strTitle, QString::number(nSession),NULL);
	/*QMessageBox::information(NULL, "Error", "��Ƶ",
		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);*/
	//Widget w;

	/*if (bOnline == true)
	{
		QString strInfo = "��ƵID:" + QString::number(nSession);
		MsgShowWidget_->setMsg("��Ƶ����", strInfo, NULL);
	}
	else
	{
		QString strInfo = "��ƵID:" + QString::number(nSession);
		MsgShowWidget_->setMsg("��Ƶ����", strInfo, NULL);
	}
	MsgShowWidget_->showAsQQ();*/
}

int AHMonitor::serverConnection(QString szAccounts, QString szPassword, QString szAddress, QString szPort)
{
	CCameraMngr* cameraManager = CCameraMngr::getInstance();
	cameraManager->SetCallbackFunc(UIEventCallBackHandler, this);

	CAM_SERVER_INFO serverInfo;
	if (cameraManager->ConnectServer(szAddress.toStdString().c_str(), szPort.toInt(), szAccounts.toStdString().c_str(), szPassword.toStdString().c_str(), &serverInfo) != MP_ENG_OK)
	{
		QMessageBox::information(NULL, "Error", "����ʧ��",
			QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return -1;
	}

	ServerManager* pServerManger = ServerManager::getInstance();
	pServerManger->addServerNode(serverInfo.nCamServerID, cameraManager, &serverInfo);

	return 0;
}

void AHMonitor::createActions()
{
	LinkAction_ = new QAction(tr("����վ��"), this);
	connect(LinkAction_, SIGNAL(triggered()), this, SLOT(onServerConnect()));

	unLinkAction_ = new QAction(tr("�Ͽ�վ��"), this);
	connect(unLinkAction_, SIGNAL(triggered()), this, SLOT(onServerDisConnect()));

	ExitAction_ = new QAction(tr("�˳�"), this);
	connect(ExitAction_, SIGNAL(triggered()), this, SLOT(close()));
}

void AHMonitor::createMenus()
{
	LinkMenu_ = menuBar()->addMenu(tr("·��"));
	LinkMenu_->addAction(LinkAction_);
	LinkMenu_->addAction(unLinkAction_);
	LinkMenu_->addAction(ExitAction_);


}

void AHMonitor::createToolBars()
{
	LinkTool_ = addToolBar("����վ��");
	LinkTool_->addAction(LinkAction_);
}

void AHMonitor::onServerConnect()
{
	if (pLogonDialog_->exec() == QDialog::Accepted)
	{
		if (serverConnection(pLogonDialog_->szAccounts, pLogonDialog_->szPassword, pLogonDialog_->szAddress, pLogonDialog_->szPort) == -1)
			return;

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
			//�Ͽ�����
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
