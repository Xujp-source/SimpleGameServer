#ifndef _PLAYER_MANAGER_H_
#define _PLAYER_MANAGER_H_
#include"stdafx.h"

class CPlayerObject;
class CPlayerManager
{
private:
	CPlayerManager();

	virtual ~CPlayerManager();

public:
	static CPlayerManager* GetInstancePtr();

public:
	CPlayerObject* GetPlayer(unsigned long long uid);

	std::map<unsigned long long, CPlayerObject*> GetOnlinePlayer();

	CPlayerObject* CreatePlayer();

public:
	bool OnUpdate();

	bool OnSecondTimer();

private:
	std::map<unsigned long long, CPlayerObject*> m_playermap;

public:
	//*********************消息处理定义*************************

	//**********************************************************
};

#endif 