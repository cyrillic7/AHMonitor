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

int CPlayerManager::addPlayerEngine(/*int playerIndex, */int nsession)
{
	/*if (playerIndex_ > 0)
	{
		if (CPlaybackEngine::getInstance(playerIndex - 1)->GetCameraSession() == nsession)
		{
			return -1;
		}
	}
	playerIndex_++;*/
	playerIndex_++;
	if (CPlaybackEngine::getInstance(playerIndex_)->GetCameraSession() == nsession)
	{
		return -1;
	}
	CPlaybackEngine* player = CPlaybackEngine::getInstance(playerIndex_);

	insertPlayerEngine(playerIndex_, player);

	return playerIndex_;
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
