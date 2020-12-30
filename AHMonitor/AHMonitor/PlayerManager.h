#ifndef _PLAYER_MANAGER_H_
#define _PLAYER_MANAGER_H_
#pragma once

#include "HeadFile.h"
#include <map>
#include "videopanel.h"
//���Ź���
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
	//����panel
	void setPanelWidget(VideoPanel* pWidget) {
		pVideoWidget_ = pWidget;
	}

	//��������
	std::map<int, CPlaybackEngine*> playerEngineMap_;
	//�½�index
	int newPlayerIndex();
	int playerIndex_;
public:
	//�������
	int addPlayerEngine(/*int playerIndex,*/ int nsession);
	
	void insertPlayerEngine(int EngineIndex, CPlaybackEngine* playerEngine);
	//�ͷ�����
	void erasePlayerEngine(int EngineIndex);
	//��ʼ����
	int startPlayer(int serverid,int nSession);
	//ֹͣ����
	int stopPlayer(int nSession);
	//��ȡindex
	int getPlayerIndex() { return playerIndex_; }
	//����index
	void setPlayerIndex(int index) { playerIndex_ = index; }
	//����mic������
	void setMicmute(int session, bool mute);
};

#endif