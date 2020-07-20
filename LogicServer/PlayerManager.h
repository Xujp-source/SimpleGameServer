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
	//获取玩家对象
	CPlayerObject* GetPlayer(unsigned long long uid);
	//获取所有在线玩家
	std::map<unsigned long long, CPlayerObject*> GetOnlinePlayer();
	//创建玩家对象
	CPlayerObject* CreatePlayer();

public:
	//定时器管理
	bool OnUpdate();
	//每秒触发操作
	bool OnSecondTimer();

private:
	std::map<unsigned long long, CPlayerObject*> m_playermap;

};

#endif 