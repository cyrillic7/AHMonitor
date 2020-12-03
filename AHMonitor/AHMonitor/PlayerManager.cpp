#include "PlayerManager.h"

CPlayerManager* CPlayerManager::m_Instance = NULL;

CPlayerManager::CPlayerManager()
{
	m_Instance = this;
	playerIndex_ = 0;
	pVideoWidget_ = NULL;
}


CPlayerManager::~CPlayerManager()
{
}

int CPlayerManager::addPlayerEngine(int playerIndex, int nsession)
{
	if (playerIndex_ > 0)
	{
		if (CPlaybackEngine::getInstance(playerIndex - 1)->GetCameraSession() == nsession)
		{
			return -1;
		}
	}
	playerIndex_++;

	CPlaybackEngine* player = CPlaybackEngine::getInstance(playerIndex);

	insertPlayerEngine(playerIndex, player);

	return 0;
}

void CPlayerManager::insertPlayerEngine(int EngineIndex, CPlaybackEngine * playerEngine)
{
	playerEngineMap_[EngineIndex] = playerEngine;
}

void CPlayerManager::erasePlayerEngine(int EngineIndex)
{
	playerEngineMap_.erase(EngineIndex);
}

int CPlayerManager::startPlayer(int nSession)
{
	if (nSession == -1)
		return -1;

	for (std::map<int, CPlaybackEngine*>::iterator it = playerEngineMap_.begin(); it != playerEngineMap_.end(); /*i++*/)
	{
		if (it->second->GetCameraSession() == nSession)
		{
			it->second->SetMode(MP_MODE_SERV_PROXY);
			it->second->SetCallbackFunc(UIPlayerEventCallBackHandler, pVideoWidget_->getVideoWidget(nSession));
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
