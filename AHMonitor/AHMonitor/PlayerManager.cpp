#include "PlayerManager.h"

CPlayerManager* CPlayerManager::m_Instance = NULL;

CPlayerManager::CPlayerManager()
{
	m_Instance = this;
	playerIndex_ = -1;
	pVideoWidget_ = NULL;
}


CPlayerManager::~CPlayerManager()
{
}

int CPlayerManager::newPlayerIndex()
{
	for (int i=0;i<64;i++)
	{
		if (CPlaybackEngine::getInstance(i)->GetCameraSession() == -1)
		{
			playerIndex_ = i;
			return i;
		}
	}

	return -1;
}

int CPlayerManager::addPlayerEngine(/*int playerIndex, */int nsession)
{
	if (playerIndex_ > 0)
	{
		if (CPlaybackEngine::getInstance(playerIndex_ - 1)->GetCameraSession() == nsession)
		{
			return -1;
		}
	}
	/*playerIndex_++;*/
	int playerIndex = newPlayerIndex();
	if (CPlaybackEngine::getInstance(playerIndex)->GetCameraSession() == nsession)
	{
		return -1;
	}
	CPlaybackEngine* player = CPlaybackEngine::getInstance(playerIndex);

	insertPlayerEngine(playerIndex, player);

	return playerIndex;
}

void CPlayerManager::insertPlayerEngine(int EngineIndex, CPlaybackEngine * playerEngine)
{
	playerEngineMap_[EngineIndex] = playerEngine;
}

void CPlayerManager::erasePlayerEngine(int EngineIndex)
{
	playerEngineMap_.erase(EngineIndex);
}

int CPlayerManager::startPlayer(int serverid, int nSession)
{
	if (nSession == -1)
		return -1;

	for (std::map<int, CPlaybackEngine*>::iterator it = playerEngineMap_.begin(); it != playerEngineMap_.end(); /*i++*/)
	{
		if (it->second->GetCameraSession() == nSession)
		{
			it->second->SetMode(MP_MODE_SERV_PROXY);
			it->second->SetCallbackFunc(UIPlayerEventCallBackHandler, pVideoWidget_->getVideoWidget(serverid,nSession));
			if (it->second->Load() == MP_ENG_OK) {
				if (it->second->Start() == MP_ENG_OK)
				{
					return 0;
				}
			}

		}
		else
		{
			it++;
		}
	}
	return -1;
}

int CPlayerManager::stopPlayer(int nSession)
{
	if (nSession == -1)
		return -1;

	for (std::map<int, CPlaybackEngine*>::iterator it = playerEngineMap_.begin(); it != playerEngineMap_.end(); /*i++*/)
	{
		if (it->second->GetCameraSession() == nSession)
		{
			if (it->second->Stop() == MP_ENG_OK)
			{
				it->second->Unload();
				playerEngineMap_.erase(it);
				return 0;
			}
		}
		else
		{
			it++;
		}

	}
}

void CPlayerManager::setMicmute(int session,bool mute)
{
	if (session == -1)
		return;

	for (std::map<int, CPlaybackEngine*>::iterator it = playerEngineMap_.begin(); it != playerEngineMap_.end(); /*i++*/)
	{
		if (it->second->GetCameraSession() == session)
		{
			if (mute == false)
			{
				it->second->Mic_UnMute();
				return;
			}
			else
			{
				it->second->Mic_Mute();
				return;
			}
		}
		else
		{
			it++;
		}

	}
}
