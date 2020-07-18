#ifndef _PLAYER_OBJECT_H_
#define _PLAYER_OBJECT_H_
#include"Object.h"
#include"Agent.h"

class CBaseModule;
class CPlayerObject : public CObject, public Agent
{
public:
	CPlayerObject();

	virtual ~CPlayerObject();

	//初始化玩家对象
	bool Init(unsigned long long u64ID);

	//注册所有玩家相关的模块
	bool RegisterAllMoudle();

public:
	//获取玩家uid
	inline int GetUid() { return m_uid; }

	//设置玩家uid
	inline void SetUid(int uid) { m_uid = uid; }

	//设置缓存数据
	void SetTemp(std::string key, int value);

	//获取玩家缓存
	int  GetTemp(std::string key);

	//保存改变的数据
	bool SaveData();

	//是否是玩家对象
	virtual bool IsUser() { return true; }

public:
	//模块注册表
	std::vector<CBaseModule*> m_MoudleList;
	//玩家缓存
	std::map<std::string, int> m_TempList;

	CTimerManager m_Timer;

private:
	unsigned long long m_uid;

};

#endif 