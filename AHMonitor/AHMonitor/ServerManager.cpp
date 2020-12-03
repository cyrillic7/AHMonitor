#include "ServerManager.h"

ServerManager* ServerManager::m_Instance = NULL;

ServerManager::ServerManager()
{
	m_Instance = this;
	m_CServerCount = 0;
}


ServerManager::~ServerManager()
{
}

void ServerManager::addServerNode(int ServerId, CCameraMngr * pCameraMngr, CAM_SERVER_INFO * pCamServerInfo)
{
	CServerNode* pServerNode = new CServerNode(ServerId, pCameraMngr);
	pServerNode->setCameraServerInfo(pCamServerInfo);

	m_pVServerNode.push_back(pServerNode);
	m_CServerCount = m_pVServerNode.size();
}

void ServerManager::addServerCamGroup(int ServerId, CAM_GROUP_INFO * pCamGroup)
{
	ServerManager* pServerMng = ServerManager::getInstance();
	for (int i = 0; i < pServerMng->getServerCount(); i++)
	{
		CServerNode* pServerNode = pServerMng->getServerNode(i);
		if (pServerMng == NULL)
			continue;

		if (pServerNode->getCamerServerID() == ServerId)
		{
			pServerNode->insertCamGroup(pCamGroup);
		}
	}
}

void ServerManager::addServerCamTerminal(int ServerId, CAM_INFO * pCamTerminal)
{
	ServerManager* pServerMng = ServerManager::getInstance();
	for (int i = 0; i < pServerMng->getServerCount(); i++)
	{
		CServerNode* pServerNode = pServerMng->getServerNode(i);
		if (pServerMng == NULL)
			continue;

		if (pServerNode->getCamerServerID() == ServerId)
		{
			pServerNode->insertCamTerminal(pCamTerminal);
		}
	}
}

CServerNode * ServerManager::getServerNode(int index)
{
	return m_pVServerNode[index];
}

CServerNode::CServerNode(int serverid, CCameraMngr* pCameraMngr)
{
	m_CamServerID = serverid;
	m_pCameraMngr = pCameraMngr;

	m_pCamServerInfo = new CAM_SERVER_INFO;
}

CServerNode::~CServerNode()
{
	m_pCameraMngr->Exit();
	if (m_pCamServerInfo != NULL )
	{
		delete m_pCamServerInfo;
	}
}

void CServerNode::setCameraServerInfo(CAM_SERVER_INFO * pServerInfo)
{
	if (pServerInfo == NULL)
	{
		return;
	}
	m_pCamServerInfo->nCamServerID = pServerInfo->nCamServerID;
	m_pCamServerInfo->nPort = pServerInfo->nPort;
	m_pCamServerInfo->state = pServerInfo->state;
	sprintf(m_pCamServerInfo->szCamServerName, pServerInfo->szCamServerName);
	sprintf(m_pCamServerInfo->szIPAddr, pServerInfo->szIPAddr);
}

CAM_GROUP_INFO * CServerNode::getCamGroupInfo(int nCamGroupID)
{
	if (m_CamGroupCount<=0)
		return NULL;

	std::vector<CAM_GROUP_INFO*>::iterator it = m_pVCamGroup.begin();
	for (it;it!=m_pVCamGroup.end();it++)
	{
		if ((*it)->nCamGroupID == nCamGroupID)
		{
			return *it;
		}
	}
}

CAM_INFO * CServerNode::getCamTerminalInfo(int nSessionID)
{
	if (m_CamTerminalCount <= 0)
		return NULL;
	
	std::vector<CAM_INFO*>::iterator it = m_pVCamTerminal.begin();
	for (it; it != m_pVCamTerminal.end(); it++)
	{
		if ((*it)->nSession == nSessionID)
		{
			return *it;
		}
	}
}

void CServerNode::insertCamGroup(CAM_GROUP_INFO * pCamGroup)
{
	m_pVCamGroup.push_back(pCamGroup);
	m_CamGroupCount = m_pVCamGroup.size();
}

void CServerNode::insertCamTerminal(CAM_INFO * pCamTerminal)
{
	m_pVCamTerminal.push_back(pCamTerminal);
	m_CamTerminalCount = m_pVCamTerminal.size();
}

int CServerNode::getSessionID(const QString & szLocation)
{
	if (szLocation.isEmpty() == true)
		return -1;

	std::vector<CAM_INFO*>::iterator it = m_pVCamTerminal.begin();
	for (it; it != m_pVCamTerminal.end(); it++)
	{
		QString szlocal = GlobalFun::charToqstirng((*it)->szLocation);
		if ((*it)->state == MP_CAM_StateOnline)
		{
			szlocal += "(ÔÚÏß)";
		}
		else
		{
			szlocal += "(ÀëÏß)";
			continue;
		}
		if (szlocal == szLocation)
		{
			return (*it)->nSession;
		}
	}
	return -1;
}
