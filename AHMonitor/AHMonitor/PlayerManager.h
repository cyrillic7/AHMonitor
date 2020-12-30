#ifndef _PLAYER_MANAGER_H_
#define _PLAYER_MANAGER_H_
#pragma once

#include "HeadFile.h"
#include <map>
#include "videopanel.h"
//播放管理
class CPlayerManager
{
public:
	CPlayerManager();
	virtual ~CPlayerManager();

	static CPlayerManager *getInstance() {
		return m_Instance;
	}

	static CPlayerManager *m_Instance;

	VideoPanel* pVideoWidget_;
	//设置panel
	void setPanelWidget(VideoPanel* pWidget) {
		pVideoWidget_ = pWidget;
	}

	//播放引擎
	std::map<int, CPlaybackEngine*> playerEngineMap_;
	//新建index
	int newPlayerIndex();
	int playerIndex_;
public:
	//添加引擎
	int addPlayerEngine(/*int playerIndex,*/ int nsession);
	
	void insertPlayerEngine(int EngineIndex, CPlaybackEngine* playerEngine);
	//释放引擎
	void erasePlayerEngine(int EngineIndex);
	//开始播放
	int startPlayer(int serverid,int nSession);
	//停止播放
	int stopPlayer(int nSession);
	//获取index
	int getPlayerIndex() { return playerIndex_; }
	//设置index
	void setPlayerIndex(int index) { playerIndex_ = index; }
	//设置mic输出输出
	void setMicmute(int session, bool mute);
};

#endif