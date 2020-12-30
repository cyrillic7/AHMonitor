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

	int m_CamGroupCount;//组数量
	std::vector<CAM_GROUP_INFO*> m_pVCamGroup;

	int m_CamTerminalCount;//终端
	std::vector<CAM_INFO*> m_pVCamTerminal;
public:
	/*int ReConnectServer(int serverID);*/
	int DisConnectServer(int serverID);//断开服务
	int getCamerServerID() { return m_CamServerID; }

	void setCameraServerInfo(CAM_SERVER_INFO* pServerInfo);//设置服务信息
	CAM_SERVER_INFO* getCamServerInfo() { return m_pCamServerInfo; }

	CAM_GROUP_INFO* getCamGroupInfo(int nCamGroupID);//组信息
	CAM_INFO* getCamTerminalInfo(int nSessionID);

	int getCamGroupCount() { return m_CamGroupCount; }
	int getCamTerminalCount() { return m_CamTerminalCount; }
	//添加组
	void insertCamGroup(CAM_GROUP_INFO* pCamGroup);
	//添加终端
	void insertCamTerminal(CAM_INFO* pCamTerminal);
	//获取sessionid
	int getSessionID(const QString& szLocation);
	//获取服务名称
	QString getServerName();
};
//server管理
class ServerManager
{
public:
	ServerManager();
	virtual ~ServerManager();

	static ServerManager *getInstance() {
		return m_Instance;
	}

public:
	//添加server node
	void addServerNode(int ServerId, CCameraMngr* pCameraMngr, CAM_SERVER_INFO* pCamServerInfo);
	//删除server node
	void removeServerNode(int ServerId);
	//添加组
	void addServerCamGroup(int ServerId, CAM_GROUP_INFO* pCamGroup);
	//添加终端
	void addServerCamTerminal(int ServerId, CAM_INFO* pCamTerminal);

	int getServerId(QString serverName);
	int getServerCount() { return m_CServerCount; }
	CServerNode* getServerNode(int index);
	//CServerNode* getServerNode(int serverId);
	//离线
	void setCameraPlayerOff(int ServerId,int nSession);
private:
	static ServerManager *m_Instance;

	int m_CServerCount;
	std::vector<CServerNode*> m_pVServerNode;
};


#endif // !_SERVER_MANAGER_