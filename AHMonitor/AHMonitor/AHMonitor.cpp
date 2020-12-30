#include "AHMonitor.h"
#include "QLogonDialog.h"
#include <QGridLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QSplitter>
#include "INI_File.h"
extern "C"
{
#include "libavformat/avformat.h"
};
#pragma execution_character_set("utf-8")
//INT64 _h264Handle = 0;
void UIEventCallBackHandler(MP_ENG_EVENT event, int nIndex, void *pParam, void *pAppData)
{
	TCHAR buffer[256];
	_stprintf_s(buffer, 256, _T("UI event raised: event code %d, index %d, param 0x%X, application data 0x%X.\n"),
		event, nIndex, (DWORD)pParam, (DWORD)pAppData);
	OutputDebugString(buffer);
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

		QString ReturnStr = QString(QLatin1String((char*)pParam));//QString::fromLocal8Bit((char*)pParam);
		cout << "MP_EVENT_ACK return :" << ReturnStr.toStdString() << endl;

		ControlCommandHelper helper;
		Return buffer[10];
		int len = helper.ParseReturnString((char*)pParam, buffer, sizeof(buffer));
		//QString str = QString::fromStdString((char*)pParam);
		//cout << "ParseReturnString :" << str.toStdString().c_str() << endl;
		for (int i = 0; i < len; i++)
		{
			TCHAR info[50];
			_stprintf_s(info, 50, _T("seq %d, val %d\n"), buffer[i].sequence, buffer[i].value);
			QString s = QString::fromLocal8Bit((char*)info);
			cout << "MP_EVENT_ACK info:" << s.toStdString() << endl;
		}
		if(len == 0)
			pMonitor->decodeACKString(ReturnStr);
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
	{
		QString ReturnStr = QString(QLatin1String((char*)pParam));
		cout << "MP_EVENT_ALARM return :" << ReturnStr.toStdString() << endl;

		ControlCommandHelper helper;
		Return buffer[10];
		int len = helper.ParseReturnString((char*)pParam, buffer, sizeof(buffer));
		/*QString str = QString::fromStdString(pParam);*/
		//cout << "ParseReturnString :" << pParam << endl;
		for (int i = 0; i < len; i++)
		{
			TCHAR info[50];
			_stprintf_s(info, 50, _T("seq %d, val %d\n"), buffer[i].sequence, buffer[i].value);
			/*AfxMessageBox(info);*/
			cout << "MP_EVENT_ALARM info:" << info << endl;
		}
	}
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
	pPTZControl_->setEnabled(false);
	connect(pPTZControl_, SIGNAL(gauCloudClicked(int)), this, SLOT(cloudCicked(int)));
	connect(pPTZControl_, SIGNAL(CloudzoomPlus()), this, SLOT(zoomPlus()));
	connect(pPTZControl_, SIGNAL(CloudzoomReduce()), this, SLOT(zoomReduce()));
	connect(pPTZControl_, SIGNAL(CloudapertureBig()), this, SLOT(apertureBig()));
	connect(pPTZControl_, SIGNAL(CloudapertureSmall()), this, SLOT(apertureSmall()));
	connect(pPTZControl_, SIGNAL(CloudfocusingNear()), this, SLOT(focusingNear()));
	connect(pPTZControl_, SIGNAL(CloudfocusingFar()), this, SLOT(focusingFar()));
	connect(pPTZControl_, SIGNAL(CloudFerPosition(int)), this, SLOT(FerPosition(int)));
	connect(pPTZControl_, SIGNAL(CloudAction(QString &)), this, SLOT(CAction(QString &)));

	pTerminalCtl_ = new QTerminalControl(this);
	pTerminalCtl_->setEnabled(false);
	pTabWidget_->addTab(pTerminalCtl_, "终端控制");
	connect(pTerminalCtl_->pDefault_, SIGNAL(clicked()), this, SLOT(clickTerDefault()));
	connect(pTerminalCtl_->pSet_, SIGNAL(clicked()), this, SLOT(clickTerSet()));
	connect(pTerminalCtl_->pRestart_, SIGNAL(clicked()), this, SLOT(clickTerRestart()));

	pAlarmWidget_ = new QAlarmWidget(this);
	pTabWidget_->addTab(pAlarmWidget_, "报警输出");
	pAlarmWidget_->setEnabled(false);
	connect(pAlarmWidget_, SIGNAL(AlarmClicked(QString &)), this, SLOT(clickAlarm(QString &)));

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

CCameraMngr * AHMonitor::getCamMnr()
{
	int session = pTerminalCtl_->getSession();
	int serverid = pTerminalCtl_->getServerId();
	if (session == -1 || serverid == -1)
		return NULL;


	char command[100];
	int randnum = rand();
	int speeds = 33;// pPTZControl_->getSpeed();

	CCameraMngr* pCamGr;
	ServerManager* pServerMng = ServerManager::getInstance();
	for (int i = 0; i < pServerMng->getServerCount(); i++)
	{
		CServerNode* pServerNode = pServerMng->getServerNode(i);
		if (pServerNode->getCamerServerID() == serverid)
		{
			return pServerNode->m_pCameraMngr;
		}
	}

	return NULL;
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
	emit showMsg(strTitle, "视频ID:"+QString::number(nSession),NULL);
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

	SaveVideoAction_ = new QAction(tr("保存视频"),this);
	//SaveVideoAction_->setEnabled(false);
	connect(SaveVideoAction_, SIGNAL(triggered()), this, SLOT(saveVideo()));

	ScreenFull_ = new QAction(tr("全屏模式"), this);
	//connect(ScreenFull_, SIGNAL(triggered()), this, SLOT(screenfull()));
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

	LinkTool_->addAction(SaveVideoAction_);

//	LinkTool_->addAction(ScreenFull_);
}

void AHMonitor::gpsParse(QByteArray GPSBuffer)
{
  //    qDebug()<<GPSBuffer.size();

     if (GPSBuffer.contains("$GNRMC"))
     {

         QList<QByteArray> gpsByteArrays = GPSBuffer.split(',');
         int count = gpsByteArrays.count();

     int  gpsLat_1 = static_cast<int>(gpsByteArrays.at(3).toDouble() / 100);
     double gpsLat_2 = (gpsByteArrays.at(3).toDouble() - gpsLat_1 * 100) / 60;
     double gpslat = gpsLat_1 + gpsLat_2;

     int gpsLong_1 = static_cast<int>(gpsByteArrays.at(5).toDouble() / 100);
     double gpsLong_2 = (gpsByteArrays.at(5).toDouble() - gpsLong_1 * 100) / 60;
     double gpsLong = gpsLong_1 + gpsLong_2;

	 /*ui->timelineEdit->setText(gpsByteArrays.at(1));
	 ui->latlineEdit->setText(QString::number(gpslat, 'g', 9));
	 ui->longlineEdit->setText(QString::number(gpsLong, 'g', 10));

	 if (!gpsByteArrays.at(8).isEmpty())
		 ui->headlineEdit->setText(gpsByteArrays.at(8));*/


    }
}

void AHMonitor::decodeACKString(QString AckString)
{
	QStringList rtStrings;
	rtStrings = AckString.split(" ");
	for (int i=0;i<rtStrings.count();i++)
	{
		//cout << rtStrings[i].toStdString() << endl;
	}

	if (rtStrings[3] == "GPSINFO")
	{
		gpsParse(rtStrings[4].toUtf8());
		return;
	}

	if (rtStrings[3] == "VideoParam")
	{
		rtString.clear();
		rtString = AckString.split(" ");
		for (int i = 0; i < rtString.count(); i++)
		{
			cout << rtString[i].toStdString() << endl;
		}

		if (rtString[2].toInt() == pTerminalCtl_->getSession() && rtString[3] == "VideoParam")
		{
			pTerminalCtl_->setVideoParam(rtString[4].toInt(), rtString[5].toInt(), rtString[6].toInt(), rtString[7].toInt(), rtString[8].toInt(), rtString[9].toInt(), rtString[10].toInt());
		}
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

void AHMonitor::saveVideo()
{
	INI_File inifile;
	inifile.OpenFile(NULL, "saveVideo.ini");
	QString videoPath = inifile.readString("SavePath", "videoPath");

	if (!videoPath.isNull())
	{
		videoPath = inifile.GetDefaultSavePath() + "video";
	}

	qDebug() << "videoPath: " << videoPath;


}

void AHMonitor::screenfull()
{
	pVidoePanel_Widget_->full();
	/*if (bPanelFull == false)
	{
		pVidoePanel_Widget_->full();
		bPanelFull = true;
	}
	else
	{
		pVidoePanel_Widget_->setWindowFlags(Qt::SubWindow);
		pVidoePanel_Widget_->showNormal();
		bPanelFull = false;
	}*/
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
	//int res = helper.GenerateSetVideoParamCommand(session, (VideoSize)pTerminalCtl_->getVideoSize(), 15,pTerminalCtl_->getquality(), command);
	SetVideoParamCommand(session, (VideoSize)pTerminalCtl_->getVideoSize(), pTerminalCtl_->getKeySpacing(), pTerminalCtl_->getmaxFPS(), pTerminalCtl_->getCodeMode(), pTerminalCtl_->getquality(), pTerminalCtl_->getQuaStep(), pTerminalCtl_->getCodeRate(), command);
	//TRACE1("command: %s", QString::fromStdString(command));
	QString str = QString::fromStdString(command);
	cout << "command:" << str.toStdString() << endl;
	ServerManager* pServerMng = ServerManager::getInstance();
	for (int i = 0; i < pServerMng->getServerCount(); i++)
	{
		CServerNode* pServerNode = pServerMng->getServerNode(i);
		if (pServerNode->getCamerServerID() == serverid)
		{
			int ret = pServerNode->m_pCameraMngr->SendControlCmd(session, str.toStdString().c_str());

			//cout << "SendControlCmdRET :" << ret << endl;
			if (ret == 0)
			{
				emit showMsg("命令发送成功", "命令:设置视频参数", NULL);
			}else
				emit showMsg("命令发送失败", "命令:设置视频参数", NULL);
			
		}
	}

	//CCameraMngr::getInstance()->SendControlCmd(session, command);

}

void AHMonitor::clickTerRestart()
{
	int session = pTerminalCtl_->getSession();
	int serverid = pTerminalCtl_->getServerId();
	if (session == -1 || serverid == -1)
		return;

	ControlCommandHelper helper;
	char command[100];
	int res = helper.GenerateRebootCommand(session, command);
	QString strCmd = QString::fromStdString(command);
	if (res != -1)
	{
		ServerManager* pServerMng = ServerManager::getInstance();
		for (int i = 0; i < pServerMng->getServerCount(); i++)
		{
			CServerNode* pServerNode = pServerMng->getServerNode(i);
			if (pServerNode->getCamerServerID() == serverid)
			{
				int ret = pServerNode->m_pCameraMngr->SendControlCmd(session, strCmd.toStdString().c_str());

				//cout << "SendControlCmdRET :" << ret << endl;
				if (ret == 0)
				{
					emit showMsg("命令发送成功", "命令:设备重启", NULL);
				}
				else
					emit showMsg("命令发送失败", "命令:设备重启", NULL);
			}
		}
	}
}

void AHMonitor::SetVideoParamCommand(int camChannel, VideoSize size, int KeySpacing, int KeyFrame, int CodeMode, int CodeLevel, int QuaStep, int CodeRate, char* command)
{
	int randnum = rand();

	sprintf(command, "TCONFIG %d,%d VideoParam %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\r\n", randnum, camChannel, (int)size, KeySpacing, KeyFrame, CodeMode, CodeLevel, QuaStep, CodeRate
		,rtString[11].toInt(), rtString[12].toInt(),rtString[13].toInt(), rtString[14].toInt(), rtString[15].toInt(), rtString[16].toInt(), rtString[17].toInt(), rtString[18].toInt());
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

	pAlarmWidget_->setEnabled(true);
	pPTZControl_->setEnabled(true);
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

void AHMonitor::cloudCicked(int nPosition)
{
	/*QMessageBox::information(NULL, "Error", QString::number(nPosition),
		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);*/

	int session = pTerminalCtl_->getSession();
	int serverid = pTerminalCtl_->getServerId();
	if (session == -1 || serverid == -1)
		return;


	char command[100];
	int randnum = rand();
	int speeds = 33;// pPTZControl_->getSpeed();

	CCameraMngr* pCamGr;
	ServerManager* pServerMng = ServerManager::getInstance();
	for (int i = 0; i < pServerMng->getServerCount(); i++)
	{
		CServerNode* pServerNode = pServerMng->getServerNode(i);
		if (pServerNode->getCamerServerID() == serverid)
		{
			pCamGr = pServerNode->m_pCameraMngr;
		}
	}
	int ret = -1;
	switch (nPosition)
	{
	case 0://下
	{
		ControlCommandHelper helper;
		char command[100];
		int res = helper.GenerateGoDownCommand(session, speeds, command);
		//sprintf(command, "TCAMC %d,%d %s %d 0\r\n", randnum, session, "Down", speeds);
		QString strCmd = QString::fromStdString(command);
		ret = pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
		/*if (ret == 0)
		{
			emit showMsg("命令发送成功", "命令:向下移动", NULL);
		}else
			emit showMsg("命令发送失败", "命令:向下移动", NULL);*/
	}
	break;
	case 2://左
	{
		sprintf(command, "TCAMC %d,%d %s %d 0\r\n", randnum, session, "Left", speeds);
		ret = pCamGr->SendControlCmd(session, command);
		/*if (ret == 0)
		{
			emit showMsg("命令发送成功", "命令:向左移动", NULL);
		}
		else
			emit showMsg("命令发送失败", "命令:向左移动", NULL);*/
	}
	break;
	case 4://上
	{
		sprintf(command, "TCAMC %d,%d %s %d 0\r\n", randnum, session, "Up", speeds);
		ret = pCamGr->SendControlCmd(session, command);
		/*if(ret == 0)
		{
			emit showMsg("命令发送成功", "命令:向上移动", NULL);
		}
		else
			emit showMsg("命令发送失败", "命令:向上移动", NULL);*/
	}
	break;
	case 6://右
	{
		sprintf(command, "TCAMC %d,%d %s %d 0\r\n", randnum, session, "Right", speeds);
		ret = pCamGr->SendControlCmd(session, command);
		/*if (ret == 0)
		{
			emit showMsg("命令发送成功", "命令:向右移动", NULL);
		}
		else
			emit showMsg("命令发送失败", "命令:向右移动", NULL);*/
	}
	break;
	default:
		break;
	}

}

void AHMonitor::zoomPlus()
{
	int session = pTerminalCtl_->getSession();
	int serverid = pTerminalCtl_->getServerId();
	if (session == -1 || serverid == -1)
		return;


	char command[100];
	int randnum = rand();
	int speeds = 33;// pPTZControl_->getSpeed();

	CCameraMngr* pCamGr;
	pCamGr = getCamMnr();
	if (pCamGr == NULL)
		return;

	int ret = -1;

	ControlCommandHelper helper;
	int re = helper.GenerateZoomTeleCommand(session, speeds, command);
	//sprintf(command, "TCAMC %d,%d %s %d 0\r\n", randnum, session, "Down", speeds);
	QString strCmd = QString::fromStdString(command);
	ret = pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
}

void AHMonitor::zoomReduce()
{
	int session = pTerminalCtl_->getSession();
	int serverid = pTerminalCtl_->getServerId();
	if (session == -1 || serverid == -1)
		return;


	char command[100];
	int randnum = rand();
	int speeds = pPTZControl_->getSpeed();

	CCameraMngr* pCamGr;
	pCamGr = getCamMnr();
	if (pCamGr == NULL)
		return;

	int ret = -1;

	ControlCommandHelper helper;
	int re = helper.GenerateZoomWideCommand(session, speeds, command);
	//sprintf(command, "TCAMC %d,%d %s %d 0\r\n", randnum, session, "Down", speeds);
	QString strCmd = QString::fromStdString(command);
	ret = pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
}

void AHMonitor::apertureBig()
{
	int session = pTerminalCtl_->getSession();
	int serverid = pTerminalCtl_->getServerId();
	if (session == -1 || serverid == -1)
		return;


	char command[100];
	int randnum = rand();
	int speeds = pPTZControl_->getSpeed();

	CCameraMngr* pCamGr;
	pCamGr = getCamMnr();
	if (pCamGr == NULL)
		return;

	int ret = -1;

	ControlCommandHelper helper;
	int re = helper.GenerateIrisOpenCommand(session, speeds, command);
	//sprintf(command, "TCAMC %d,%d %s %d 0\r\n", randnum, session, "Down", speeds);
	QString strCmd = QString::fromStdString(command);
	ret = pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
}

void AHMonitor::apertureSmall()
{
	int session = pTerminalCtl_->getSession();
	int serverid = pTerminalCtl_->getServerId();
	if (session == -1 || serverid == -1)
		return;


	char command[100];
	int randnum = rand();
	int speeds = pPTZControl_->getSpeed();

	CCameraMngr* pCamGr;
	pCamGr = getCamMnr();
	if (pCamGr == NULL)
		return;

	int ret = -1;

	ControlCommandHelper helper;
	int re = helper.GenerateIrisCloseCommand(session, speeds, command);
	//sprintf(command, "TCAMC %d,%d %s %d 0\r\n", randnum, session, "Down", speeds);
	QString strCmd = QString::fromStdString(command);
	ret = pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
}

void AHMonitor::focusingNear()
{
	int session = pTerminalCtl_->getSession();
	int serverid = pTerminalCtl_->getServerId();
	if (session == -1 || serverid == -1)
		return;


	char command[100];
	int randnum = rand();
	int speeds = pPTZControl_->getSpeed();

	CCameraMngr* pCamGr;
	pCamGr = getCamMnr();
	if (pCamGr == NULL)
		return;

	int ret = -1;

	ControlCommandHelper helper;
	int re = helper.GenerateFocusNearCommand(session, speeds, command);
	//sprintf(command, "TCAMC %d,%d %s %d 0\r\n", randnum, session, "Down", speeds);
	QString strCmd = QString::fromStdString(command);
	ret = pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
}

void AHMonitor::focusingFar()
{
	int session = pTerminalCtl_->getSession();
	int serverid = pTerminalCtl_->getServerId();
	if (session == -1 || serverid == -1)
		return;


	char command[100];
	int randnum = rand();
	int speeds = pPTZControl_->getSpeed();

	CCameraMngr* pCamGr;
	pCamGr = getCamMnr();
	if (pCamGr == NULL)
		return;

	int ret = -1;

	ControlCommandHelper helper;
	int re = helper.GenerateFocusFarCommand(session, speeds, command);
	//sprintf(command, "TCAMC %d,%d %s %d 0\r\n", randnum, session, "Down", speeds);
	QString strCmd = QString::fromStdString(command);
	ret = pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
}

void AHMonitor::FerPosition(int position)
{
	int session = pTerminalCtl_->getSession();
	int serverid = pTerminalCtl_->getServerId();
	if (session == -1 || serverid == -1)
		return;


	char command[100];
	int randnum = rand();
	int speeds = pPTZControl_->getSpeed();

	CCameraMngr* pCamGr;
	pCamGr = getCamMnr();
	if (pCamGr == NULL)
		return;

	int ret = -1;

	ControlCommandHelper helper;
	int re = helper.GeneratePresetCommand(session, position, command);
	//sprintf(command, "TCAMC %d,%d %s %d 0\r\n", randnum, session, "Down", speeds);
	QString strCmd = QString::fromStdString(command);
	ret = pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
}

void AHMonitor::CAction(QString & action)
{
	int session = pTerminalCtl_->getSession();
	int serverid = pTerminalCtl_->getServerId();
	if (session == -1 || serverid == -1)
		return;


	char command[100];
	int randnum = rand();
	int speeds = pPTZControl_->getSpeed();

	CCameraMngr* pCamGr;
	pCamGr = getCamMnr();
	if (pCamGr == NULL)
		return;

	/*QMessageBox::information(NULL, "Error", action,
		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);*/

	if ("ss" == action)//启动扫描
	{
		ControlCommandHelper helper;
		int re = helper.GenerateAutoScanCommand(session, true, command);
		QString strCmd = QString::fromStdString(command);
		pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
	}
	else if ("sp" == action)//关闭扫描
	{
		ControlCommandHelper helper;
		int re = helper.GenerateAutoScanCommand(session, false, command);
		QString strCmd = QString::fromStdString(command);
		pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
	}
	else if ("xs" == action)//启动巡航
	{
		ControlCommandHelper helper;
		int re = helper.GenerateCruiseCommand(session, true, command);
		QString strCmd = QString::fromStdString(command);
		pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
	}
	else if ("xp" == action)//关闭巡航
	{
		ControlCommandHelper helper;
		int re = helper.GenerateCruiseCommand(session, false, command);
		QString strCmd = QString::fromStdString(command);
		pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
	}
	else if ("hs" == action)//启动红外
	{
		ControlCommandHelper helper;
		int re = helper.GenerateInfraredCommand(session, true, command);
		QString strCmd = QString::fromStdString(command);
		pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
	}
	else if ("hp" == action)//关闭红外
	{
		ControlCommandHelper helper;
		int re = helper.GenerateInfraredCommand(session, false, command);
		QString strCmd = QString::fromStdString(command);
		pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
	}
	else if ("ys" == action)//启动雨刷
	{
		ControlCommandHelper helper;
		int re = helper.GenerateRainStripCommand(session, true, command);
		QString strCmd = QString::fromStdString(command);
		pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
	}
	else if ("yp" == action)//关闭雨刷
	{
		ControlCommandHelper helper;
		int re = helper.GenerateRainStripCommand(session, false, command);
		QString strCmd = QString::fromStdString(command);
		pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
	}

}

void AHMonitor::clickAlarm(QString & action)
{
	int session = pTerminalCtl_->getSession();
	int serverid = pTerminalCtl_->getServerId();
	if (session == -1 || serverid == -1)
		return;


	char command[100];
	int randnum = rand();
	int speeds = pPTZControl_->getSpeed();

	CCameraMngr* pCamGr;
	pCamGr = getCamMnr();
	if (pCamGr == NULL)
		return;

	QMessageBox::information(NULL, "Error", action,
		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

	int ports = 0;
	bool bAlarm = false;
	if ("t1" == action)
	{
		ports = 1;
		bAlarm = true;
	}else if ("d1" == action)
	{
		ports = 1;
		bAlarm = false;
	}
	else if ("t2" == action)
	{
		ports = 2;
		bAlarm = true;
	}
	else if ("d2" == action)
	{
		ports = 2;
		bAlarm = false;
	}
	else if ("t3" == action)
	{
		ports = 3;
		bAlarm = true;
	}
	else if ("d3" == action)
	{
		ports = 3;
		bAlarm = false;
	}
	else if ("t4" == action)
	{
		ports = 4;
		bAlarm = true;
	}
	else if ("d4" == action)
	{
		ports = 4;
		bAlarm = false;
	}

	if (ports > 0 && ports < 5)
	{
		ControlCommandHelper helper;
		int re = helper.GenerateWarningOutputCommand(session, ports, bAlarm, command);
		QString strCmd = QString::fromStdString(command);
		pCamGr->SendControlCmd(session, strCmd.toStdString().c_str());
	}
}

