#include "QServerTreeWidget.h"
#include "PlayerManager.h"
#include <QMessageBox>

QServerTreeWidget::QServerTreeWidget(QWidget *parent) : QTreeWidget(parent)
{

	connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(TerminalItemDoubleClicked(QTreeWidgetItem*, int)));
	connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(TerminalItemClicked(QTreeWidgetItem*, int)));
}


QServerTreeWidget::~QServerTreeWidget()
{
}

void QServerTreeWidget::updateServerTreeItem()
{
	ServerManager* pServerMng = ServerManager::getInstance();
	for (int i = 0; i < pServerMng->getServerCount(); i++)
	{
		CServerNode* pServerNode = pServerMng->getServerNode(i);
		if (pServerMng == NULL)
			continue;

		int connectServerID = pServerNode->getCamerServerID();
		CCameraMngr* pCameraMngr = pServerNode->m_pCameraMngr;

		this->setHeaderLabel("视频列表");
		QTreeWidgetItem *ServerItem = new QTreeWidgetItem(this);

		ServerItem->setText(0, GlobalFun::charToqstirng(pServerNode->m_pCamServerInfo->szCamServerName));
		//ServerItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);

		//retrieve all cameras in all groups
		CAM_INFO *pCamInfos;
		CAM_GROUP_INFO *pCamGroup;

		int nGroupNum = pCameraMngr->RetrieveCamGroupArrayFromServer(connectServerID, &pCamGroup);

		/*list<CAM_GROUP_INFO>::const_iterator groupIter;*/
		for (int k = 0; k < nGroupNum; k++)
		{
			QTreeWidgetItem *ServerGroupItem = new QTreeWidgetItem(ServerItem);
			ServerGroupItem->setText(0, GlobalFun::charToqstirng(pCamGroup[k].szGroupName));

			pServerMng->addServerCamGroup(connectServerID, &pCamGroup[k]);
			int nCameraNum = pCameraMngr->RetrieveCamArrayFromServer(connectServerID, pCamGroup[k].nCamGroupID, &pCamInfos);

			for (int j = 0; j < nCameraNum; j++)
			{
				QString CamDisc;
				pServerMng->addServerCamTerminal(connectServerID, &pCamInfos[j]);
				if (pCamInfos[j].state == MP_CAM_StateOnline)
				{
					CamDisc = GlobalFun::charToqstirng(pCamInfos[j].szLocation) + "(在线)";
				}
				else if (pCamInfos[j].state == MP_CAM_StateOffline)
				{
					CamDisc = GlobalFun::charToqstirng(pCamInfos[j].szLocation) + "(离线)";
				}
				QTreeWidgetItem *ServerTerminalItem = new QTreeWidgetItem(ServerGroupItem);
				ServerTerminalItem->setText(0, CamDisc);

				////绑定设备
				//pServerNode->m_pCameraMngr->AssignPlayer(j, pCamInfos[j].nSession);
				//CPlayerManager::getInstance()->addPlayerEngine(j);
			}

			//pCameraMngr->FreeCamArray(pCamInfos);
		}

		//pCameraMngr->FreeCamGroupArray(pCamGroup);
	}

	this->expandAll();
}

void QServerTreeWidget::updateCamLine(int nSession, bool bOnline)
{
	ServerManager* pServerMng = ServerManager::getInstance();
	for (int i = 0; i < pServerMng->getServerCount(); i++)
	{
		CServerNode* pServerNode = pServerMng->getServerNode(i);
		if (pServerMng == NULL)
			continue;

		CAM_INFO* pCamInfo = pServerNode->getCamTerminalInfo(nSession);
		if(pCamInfo == NULL)
			continue;

		QTreeWidgetItemIterator it(this);
		while (*it) {
			//do something like
			QString CamDisc;
			QString strItem = GlobalFun::charToqstirng(pCamInfo->szLocation);
			if (pCamInfo->state == MP_CAM_StateOffline)
			{
				strItem += "(离线)";
			}
			else
			{
				strItem += "(在线)";
			}
			if ((*it)->text(0) == strItem)
			{
				if (bOnline == true)
				{
					CamDisc = GlobalFun::charToqstirng(pCamInfo->szLocation) + "(在线)";
					(*it)->setText(0, CamDisc);
					pCamInfo->state = MP_CAM_StateOnline;
					this->update();
					return;
				}else if (bOnline == false)
				{
					CamDisc = GlobalFun::charToqstirng(pCamInfo->szLocation) + "(离线)";
					(*it)->setText(0, CamDisc);
					pCamInfo->state = MP_CAM_StateOffline;
					this->update();
					return;
				}
			}
			++it;
		}
	}
}

void QServerTreeWidget::deleteServerItem(QString server)
{
	for (int i = 0; i < this->topLevelItemCount(); ++i)
	{
		QTreeWidgetItem *item = this->topLevelItem(i);

		QString strItem = item->text(0);
		if (strItem == server)
		{
			delete item;
		}
	}
}

void QServerTreeWidget::TerminalItemClicked(QTreeWidgetItem * WidgetItem, int column)
{
	if (WidgetItem->parent()->parent())
	{
		QString strParentItem = WidgetItem->parent()->parent()->text(column);
		int connectServerID;
		ServerManager* pServerMng = ServerManager::getInstance();
		if (pServerMng == NULL)
			return;
		for (int i = 0; i < pServerMng->getServerCount(); i++)
		{
			CServerNode* pServerNode = pServerMng->getServerNode(i);
			QString strItem = WidgetItem->text(column);
			int nSession = pServerNode->getSessionID(strItem);
			if (nSession == -1)
				continue;
			if (strParentItem == GlobalFun::charToqstirng(pServerNode->m_pCamServerInfo->szCamServerName))
			{
				connectServerID = pServerNode->getCamerServerID();
			}

			emit recItemSession(connectServerID,nSession);
			return;
		}
	}
}


void QServerTreeWidget::TerminalItemDoubleClicked(QTreeWidgetItem* WidgetItem, int column)
{
	if (WidgetItem->parent()->parent())
	{
		QString strParentItem = WidgetItem->parent()->parent()->text(column);

		ServerManager* pServerMng = ServerManager::getInstance();
		if (pServerMng == NULL)
			return;
		for (int i = 0; i < pServerMng->getServerCount(); i++)
		{
			CServerNode* pServerNode = pServerMng->getServerNode(i);
			QString strItem = WidgetItem->text(column);
			int nSession = pServerNode->getSessionID(strItem);
			if (nSession == -1)
				continue;
			if (strParentItem == GlobalFun::charToqstirng(pServerNode->m_pCamServerInfo->szCamServerName))
			{
				int connectServerID = pServerNode->getCamerServerID();

				//绑定设备
				int playerindex = CPlayerManager::getInstance()->addPlayerEngine(/*playerindex,*/ nSession);// CPlayerManager::getInstance()->getPlayerIndex();
				if (playerindex == -1)
					continue;

				pServerNode->m_pCameraMngr->AssignPlayer(playerindex, nSession);

				CPlayerManager::getInstance()->startPlayer(connectServerID,nSession);

			}
		}
	}
}