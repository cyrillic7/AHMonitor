#ifndef _PLAYER_MANAGER_H_
#define _PLAYER_MANAGER_H_
#pragma once

#include "HeadFile.h"
#include <map>
#include "videopanel.h"

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

	void setPanelWidget(VideoPanel* pWidget) {
		pVideoWidget_ = pWidget;
	}

	std::map<int, CPlaybackEngine*> playerEngineMap_;

	int playerIndex_;
public:
	int addPlayerEngine(/*int playerIndex,*/ int nsession);

	void insertPlayerEngine(int EngineIndex, CPlaybackEngine* playerEngine);

	void erasePlayerEngine(int EngineIndex);

	int startPlayer(int nSession);

	int getPlayerIndex() { return playerIndex_; }

	void setPlayerIndex(int index) { playerIndex_ = index; }
};

#endif