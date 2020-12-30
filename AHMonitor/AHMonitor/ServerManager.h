#ifndef _SERVER_MANAGER_
#define _SERVER_MANAGER_
#pragma once
#include "HeadFile.h"
#include <map>
#include <vector>
//server node
class CServerNode
{
public:
	CServerNode(int serverid, CCameraMngr* pCameraMngr);
	virtual ~CServerNode();

	CCameraMngr* m_pCameraMngr;

	CAM_SERVER_INFO* m_pCamServerInfo;
protected:
	int m_CamServerID;//serverid

	int m_CamGroupCount;//������
	std::vector<CAM_GROUP_INFO*> m_pVCamGroup;

	int m_CamTerminalCount;//�ն�
	std::vector<CAM_INFO*> m_pVCamTerminal;
public:
	/*int ReConnectServer(int serverID);*/
	int DisConnectServer(int serverID);//�Ͽ�����
	int getCamerServerID() { return m_CamServerID; }

	void setCameraServerInfo(CAM_SERVER_INFO* pServerInfo);//���÷�����Ϣ
	CAM_SERVER_INFO* getCamServerInfo() { return m_pCamServerInfo; }

	CAM_GROUP_INFO* getCamGroupInfo(int nCamGroupID);//����Ϣ
	CAM_INFO* getCamTerminalInfo(int nSessionID);

	int getCamGroupCount() { return m_CamGroupCount; }
	int getCamTerminalCount() { return m_CamTerminalCount; }
	//�����
	void insertCamGroup(CAM_GROUP_INFO* pCamGroup);
	//����ն�
	void insertCamTerminal(CAM_INFO* pCamTerminal);
	//��ȡsessionid
	int getSessionID(const QString& szLocation);
	//��ȡ��������
	QString getServerName();
};
//server����
class ServerManager
{
public:
	ServerManager();
	virtual ~ServerManager();

	static ServerManager *getInstance() {
		return m_Instance;
	}

public:
	//���server node
	void addServerNode(int ServerId, CCameraMngr* pCameraMngr, CAM_SERVER_INFO* pCamServerInfo);
	//ɾ��server node
	void removeServerNode(int ServerId);
	//�����
	void addServerCamGroup(int ServerId, CAM_GROUP_INFO* pCamGroup);
	//����ն�
	void addServerCamTerminal(int ServerId, CAM_INFO* pCamTerminal);

	int getServerId(QString serverName);
	int getServerCount() { return m_CServerCount; }
	CServerNode* getServerNode(int index);
	//CServerNode* getServerNode(int serverId);
	//����
	void setCameraPlayerOff(int ServerId,int nSession);
private:
	static ServerManager *m_Instance;

	int m_CServerCount;
	std::vector<CServerNode*> m_pVServerNode;
};


#endif // !_SERVER_MANAGER_