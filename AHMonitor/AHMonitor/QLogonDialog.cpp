#include "QLogonDialog.h"
#include "ServerManager.h"
#include <QGridLayout>
#include <QDesktopWidget>
#include <QApplication>
#include "AHMonitor.h"
#include "INI_File.h"
#pragma execution_character_set("utf-8")
QLogonDialog::QLogonDialog(QWidget *parent):QDialog(parent)
{
	this->setWindowTitle("用户登录");


	QGridLayout* pMainLayout = new QGridLayout;

	pAccountEdit_ = new QLineEdit;
	pPasswordEdit_ = new QLineEdit;
	pAddressEdit_ = new QLineEdit;
	pPortEdit_ = new QLineEdit;

	INI_File inifile;
	inifile.OpenFile(NULL, "config.ini");
	pAccountEdit_->setText(inifile.GetUsername());
	pPasswordEdit_->setText(inifile.GetPassword());
	pAddressEdit_->setText(inifile.GetIp());
	pPortEdit_->setText(inifile.GetPort());

	QHBoxLayout* pBtnLayout = new QHBoxLayout;
	pBtnLogon_ = new QPushButton("登录");
	pBtnCancel_ = new QPushButton("取消");
	pBtnLayout->addWidget(pBtnLogon_);
	pBtnLayout->addWidget(pBtnCancel_);

	pMainLayout->addWidget(new QLabel("用戶名:"),0,0);
	pMainLayout->addWidget(pAccountEdit_, 0, 1);
	pMainLayout->addWidget(new QLabel("密码:"),1, 0);
	pMainLayout->addWidget(pPasswordEdit_, 1, 1);
	pMainLayout->addWidget(new QLabel("路劲:"), 2, 0);
	pMainLayout->addWidget(pAddressEdit_, 2, 1);
	pMainLayout->addWidget(new QLabel("端口号:"), 3, 0);
	pMainLayout->addWidget(pPortEdit_,3, 1);
	pMainLayout->addLayout(pBtnLayout, 4, 1,Qt::AlignRight);

	pMainLayout->addWidget(new QLabel(QString::fromStdString(AH_VERSION)), 5, 0, Qt::AlignLeft);

	connect(pBtnLogon_, SIGNAL(clicked()), this, SLOT(onLogonClicked()));
	connect(pBtnCancel_, SIGNAL(clicked()), this, SLOT(onCancelClicked()));

	this->setLayout(pMainLayout);

	/*this->move((qApp->desktop()->availableGeometry().width() - width()) / 2 + qApp->desktop()->availableGeometry().x(),
		(qApp->desktop()->availableGeometry().height() - height()) / 2 + qApp->desktop()->availableGeometry().y());*/
	/*QDesktopWidget *desk = QApplication::desktop();
	int wd = desk->width();
	int ht = desk->height();
	this->move((wd - this->width()) / 2, (ht - this->height()) / 2);*/

}


QLogonDialog::~QLogonDialog()
{
}

void QLogonDialog::onLogonClicked()
{
	 szAccounts = pAccountEdit_->text();
	 szPassword = pPasswordEdit_->text();
	 szAddress = pAddressEdit_->text();
	 szPort = pPortEdit_->text();

	 INI_File inifile;
	 inifile.OpenFile(NULL, "config.ini");
	 inifile.SetIp(szAddress);
	 inifile.SetUserName(szAccounts);
	 inifile.SetPassword(szPassword);
	 inifile.SetPort(szPort);
	/*CCameraMngr* cameraManager = CCameraMngr::getInstance();
	cameraManager->SetCallbackFunc(UIEventCallBackHandler,AHMonitor::getInstance());

	CAM_SERVER_INFO serverInfo;
	if (cameraManager->ConnectServer(szAddress.toStdString().c_str(), szPort.toInt(), szAccounts.toStdString().c_str(), szPassword.toStdString().c_str(), &serverInfo) != MP_ENG_OK)
	{
		QMessageBox::information(NULL, "Error", "链接失败",
			QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}

	ServerManager* pServerManger = ServerManager::getInstance();
	pServerManger->addServerNode(serverInfo.nCamServerID, cameraManager, &serverInfo);*/

	//int connectedServerID = serverInfo.nCamServerID;

	//retrieve all cameras in all groups
	//CAM_INFO *pCamInfos;
	//CAM_GROUP_INFO *pCamGroup;

	//int nGroupNum = cameraManager->RetrieveCamGroupArrayFromServer(connectedServerID, &pCamGroup);

	//list<CAM_GROUP_INFO>::const_iterator groupIter;
	//for (int i = 0; i < nGroupNum; i++)
	//{
	//	pServerManger->addServerCamGroup(connectedServerID,pCamGroup);
	//	int nCameraNum = cameraManager->RetrieveCamArrayFromServer(connectedServerID, pCamGroup[i].nCamGroupID, &pCamInfos);

	//	for (int j = 0; j < nCameraNum; j++)
	//	{
	//		pServerManger->addServerCamTerminal(connectedServerID, pCamInfos);
	//		//if (pCamInfos[j].state == MP_CAM_StateOnline)
	//		{
	//			
	//		}
	//	}

	//	cameraManager->FreeCamArray(pCamInfos);
	//}

	//cameraManager->FreeCamGroupArray(pCamGroup);



	QDialog::accept();
}

void QLogonDialog::onCancelClicked()
{
	QDialog::reject();
}