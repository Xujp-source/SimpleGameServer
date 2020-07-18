#include"PlayerManager.h"
#include"Player.h"

CPlayerManager::CPlayerManager()
{

}

CPlayerManager::~CPlayerManager()
{

}

CPlayerManager* CPlayerManager::GetInstancePtr()
{
	static CPlayerManager _Instance;

	return &_Instance;
}

CPlayerObject * CPlayerManager::GetPlayer(unsigned long long uid)
{
	std::map<unsigned long long, CPlayerObject*>::iterator itor = m_playermap.find(uid);
	if (itor != m_playermap.end())
	{
		return itor->second;
	}
	return nullptr;
}

std::map<unsigned long long, CPlayerObject*> CPlayerManager::GetOnlinePlayer()
{
	return m_playermap;
}

CPlayerObject * CPlayerManager::CreatePlayer()
{
	return nullptr;
}

bool CPlayerManager::OnUpdate()
{
	for (std::map<unsigned long long, CPlayerObject*>::iterator itor = m_playermap.begin(); itor != m_playermap.end(); itor++)
	{
		CPlayerObject* player = itor->second;
		player->m_Timer.UpdateTimer();
	}
	return true;
}

bool CPlayerManager::OnSecondTimer()
{
	for (std::map<unsigned long long, CPlayerObject*>::iterator itor = m_playermap.begin(); itor != m_playermap.end(); itor++)
	{
		CPlayerObject* player = itor->second;
		unsigned long long cur_time = CELLTime::getNowInSec();
		unsigned long long last_time = player->GetTemp("last_autosave_time");
		if (!last_time)
		{
			player->SetTemp("last_autosave_time", cur_time);
			return true;
		}

		if (cur_time - last_time >= 10.0)
		{
			player->SaveData();
			player->SetTemp("last_autosave_time", cur_time);
		}
	}
	return true;
}

