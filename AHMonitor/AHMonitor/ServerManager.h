#ifndef _SERVER_MANAGER_
#define _SERVER_MANAGER_
#pragma once
#include "HeadFile.h"
#include <map>
#include <vector>

class CServerNode
{
public:
	CServerNode(int serverid, CCameraMngr* pCameraMngr);
	virtual ~CServerNode();

	CCameraMngr* m_pCameraMngr;

	CAM_SERVER_INFO* m_pCamServerInfo;
protected:
	int m_CamServerID;

	int m_CamGroupCount;
	std::vector<CAM_GROUP_INFO*> m_pVCamGroup;

	int m_CamTerminalCount;
	std::vector<CAM_INFO*> m_pVCamTerminal;
public:
	int getCamerServerID() { return m_CamServerID; }

	void setCameraServerInfo(CAM_SERVER_INFO* pServerInfo);
	CAM_SERVER_INFO* getCamServerInfo() { return m_pCamServerInfo; }

	CAM_GROUP_INFO* getCamGroupInfo(int nCamGroupID);
	CAM_INFO* getCamTerminalInfo(int nSessionID);

	int getCamGroupCount() { return m_CamGroupCount; }
	int getCamTerminalCount() { return m_CamTerminalCount; }

	void insertCamGroup(CAM_GROUP_INFO* pCamGroup);

	void insertCamTerminal(CAM_INFO* pCamTerminal);

	int getSessionID(const QString& szLocation);
};

class ServerManager
{
public:
	ServerManager();
	virtual ~ServerManager();

	static ServerManager *getInstance() {
		return m_Instance;
	}

public:
	void addServerNode(int ServerId, CCameraMngr* pCameraMngr, CAM_SERVER_INFO* pCamServerInfo);

	void addServerCamGroup(int ServerId, CAM_GROUP_INFO* pCamGroup);

	void addServerCamTerminal(int ServerId, CAM_INFO* pCamTerminal);

	int getServerCount() { return m_CServerCount; }
	CServerNode* getServerNode(int index);

private:
	static ServerManager *m_Instance;

	int m_CServerCount;
	std::vector<CServerNode*> m_pVServerNode;
};


#endif // !_SERVER_MANAGER_