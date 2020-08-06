#ifndef _SKILL_GENERATOR_H_
#define _SKILL_GENERATOR_H_
#include "../../ServerData/BattleData.h"

//技能生成器
class SKillGenerator
{
private:
	SKillGenerator();
	virtual ~SKillGenerator();

public:
	static SKillGenerator* GetInstancePtr();

public:
	//生成技能算法相关
	bool CreateSkill(BattleSide& ack, BattleSide& def, int skill_id);
	
};

#endif

