#ifndef _SKILL_MODE_H_
#define _SKILL_MODE_H_
#include "../../ServerData/BattleData.h"

//释放主动技能相关
class SKillModule
{
private:
	SKillModule();
	virtual ~SKillModule();

public:
	static SKillModule* GetInstancePtr();

public:
	//释放技能
	bool CastSkill(BattleSide& ack, BattleSide& def, int skill_id);

	//消耗HP
	bool CostHp(BattleSide& side, int skill_id);

	//消耗MP
	bool CostMp(BattleSide& side, int skill_id);

	//消耗能量
	bool CostEnergy(BattleSide& side, int skill_id);

	//冷却回合
	bool AddCd(BattleSide& side, int skill_id);
};

#endif

