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
	{
		AHMonitor* pMonitor = (AHMonitor*)pAppData;
		//TRACE1("return: %s", (char*)pParam);
		QString ReturnStr = QString(QLatin1String((char*)pParam));
		cout << "MP_EVENT_ACK return :" << ReturnStr.toStdString() << endl;

		pMonitor->decodeACKString(ReturnStr);

		ControlCommandHelper helper;
		Return buffer[20];
		int len = helper.ParseReturnString((char*)pParam, buffer, sizeof(buffer));
		/*QString str = QString::fromStdString(pParam);*/
		//cout << "ParseReturnString :" << pParam << endl;
		for (int i = 0; i < len; i++)
		{
			TCHAR info[50];
			_stprintf_s(info, 50, _T("seq %d, val %d\n"), buffer[i].sequence, buffer[i].value);
			/*AfxMessageBox(info);*/
			cout << "MP_EVENT_ACK info:" << info << endl;
		}
	}
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

	QSplitter *splitterL = new QSplitter(Qt::Vertical, this);
	//splitterL->setMinimumHeight(300);
	splitterL->setMinimumWidth(280);
	splitterL->setMaximumWidth(350);

	pTabWidget_ = new QTabWidget(this);
	pTabWidget_->setMaximumHeight(330);
	pTabWidget_->setMinimumWidth(280);
	pTabWidget_->setMaximumWidth(350);

	pPTZControl_ = new QPTZControl(this);
	pTabWidget_->addTab(pPTZControl_, "PTZ控制");

	pTerminalCtl_ = new QTerminalControl(this);
	pTerminalCtl_->setEnabled(false);
	pTabWidget_->addTab(pTerminalCtl_, "终端控制");
	connect(pTerminalCtl_->pDefault_, SIGNAL(clicked()), this, SLOT(clickTerDefault()));
	connect(pTerminalCtl_->pSet_, SIGNAL(clicked()), this, SLOT(clickTerSet()));
	connect(pTerminalCtl_->pRestart_, SIGNAL(clicked()), this, SLOT(clickTerRestart()));

	pAlarmWidget_ = new QAlarmWidget(this);
	pTabWidget_->addTab(pAlarmWidget_, "报警输出");

	pTreeWidget_ = new QServerTreeWidget(this);
	pTreeWidget_->setMinimumWidth(250);
	pTreeWidget_->setMaximumWidth(350);
	connect(pTreeWidget_, SIGNAL(recItemSession(int,int)), this, SLOT(setItemSession(int,int)));

	splitterL->addWidget(pTabWidget_);
	splitterL->addWidget(pTreeWidget_);

	QGridLayout* pMainLayout = new QGridLayout;
	QVBoxLayout* pControlLayout = new QVBoxLayout;
	/*pControlLayout->addWidget(pTreeWidget_);

	pMainLayout->addLayout(pControlLayout, 0, 0);

	pMainLayout->addWidget(pVidoePanel_Widget_, 0, 1);

	pMainLayout->addWidget(pToolsSplit_, 0, 2);*/

	splitterMain->addWidget(splitterL);
	splitterMain->addWidget(pVidoePanel_Widget_);
	splitterMain->addWidget(pToolsSplit_);

	pMainLayout->addWidget(splitterMain);
	QMainWidget->setLayout(pMainLayout);

	//updateCamOnLine(1, true);
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

	QString strTitle;
	if (bOnline == true)
	{
		strTitle = "视频加入";
	}
	else
	{
		strTitle = "视频离线";
	}
	emit showMsg(strTitle, QString::number(nSession),NULL);
	/*QMessageBox::information(NULL, "Error", "视频",
		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);*/
	//Widget w;

	/*if (bOnline == true)
	{
		QString strInfo = "视频ID:" + QString::number(nSession);
		MsgShowWidget_->setMsg("视频加入", strInfo, NULL);
	}
	else
	{
		QString strInfo = "视频ID:" + QString::number(nSession);
		MsgShowWidget_->setMsg("视频离线", strInfo, NULL);
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
		QMessageBox::information(NULL, "Error", "链接失败",
			QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return -1;
	}

	ServerManager* pServerManger = ServerManager::getInstance();
	pServerManger->addServerNode(serverInfo.nCamServerID, cameraManager, &serverInfo);

	return 0;
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

void AHMonitor::decodeACKString(QString AckString)
{
	QStringList rtString;
	rtString = AckString.split(" ");
	for (int i=0;i<rtString.count();i++)
	{
		cout << rtString[i].toStdString() << endl;
	}

	if (rtString[2].toInt() == pTerminalCtl_->getSession())
	{
		pTerminalCtl_->setVideoParam(rtString[4].toInt(), rtString[5].toInt(), rtString[6].toInt(), rtString[7].toInt(), rtString[8].toInt(), rtString[9].toInt(), rtString[10].toInt());
	}
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

void AHMonitor::clickTerDefault()
{

}

void AHMonitor::clickTerSet()
{
	int session = pTerminalCtl_->getSession();
	int serverid = pTerminalCtl_->getServerId();
	if (session == -1 || serverid == -1)
		return;

	/*ControlCommandHelper helper;
	char command[100];
	helper.GenerateAutoScanCommand(session, true, command);
	TRACE1("command: %s", command);
	CCameraMngr::getInstance()->SendControlCmd(session, command);*/
	ControlCommandHelper helper;
	char command[100];
	//int res = helper.GenerateSetVideoParamCommand(session, Big, 15,5, command);
	SetVideoParamCommand(session, (VideoSize)pTerminalCtl_->getVideoSize(), pTerminalCtl_->getKeySpacing(), pTerminalCtl_->getmaxFPS(), pTerminalCtl_->getCodeMode(), pTerminalCtl_->getquality(), command);
	TRACE1("command: %s", command);
	ServerManager* pServerMng = ServerManager::getInstance();
	for (int i = 0; i < pServerMng->getServerCount(); i++)
	{
		CServerNode* pServerNode = pServerMng->getServerNode(i);
		if (pServerNode->getCamerServerID() == serverid)
		{
			int ret = pServerNode->m_pCameraMngr->SendControlCmd(session, command);

			cout << "SendControlCmdRET :" << ret << endl;
		}
	}

	//CCameraMngr::getInstance()->SendControlCmd(session, command);

}

void AHMonitor::clickTerRestart()
{

}

void AHMonitor::SetVideoParamCommand(int camChannel, VideoSize size, int KeySpacing, int KeyFrame, int CodeMode, int CodeLevel, char* command)
{
	int randnum = rand();
	sprintf(command, "TCONFIG %d,%d VideoParam %d %d %d %d %d 10 1000 55 55 50 50 1 0 0 0\r\n", randnum, camChannel, (int)size, KeySpacing, KeyFrame, CodeMode, CodeLevel);
}

void AHMonitor::setItemSession(int serverID,int session)
{
	pTerminalCtl_->setSession(session);
	pTerminalCtl_->setServer(serverID);
	if (session == -1)
	{
		pTerminalCtl_->setEnabled(false);
		return;
	}

	pTerminalCtl_->setEnabled(true);

	ServerManager* pServerMng = ServerManager::getInstance();
	for (int i = 0; i < pServerMng->getServerCount(); i++)
	{
		CServerNode* pServerNode = pServerMng->getServerNode(i);
		if (pServerNode->getCamerServerID() == serverID)
		{
			int randn = rand();
			char cmd[100];
			sprintf(cmd, "TREADCONFIG %d,%d VideoParam\r\n", randn, session);
			cout << "send: " << cmd << endl;
			pServerNode->m_pCameraMngr->SendControlCmd(session, cmd);
		}
	}
}

