#include "SkillModule.h"
#include "SkillGeneratorModule.h"

SKillModule::SKillModule()
{
}

SKillModule::~SKillModule()
{
}

SKillModule * SKillModule::GetInstancePtr()
{
	static SKillModule _Instance;
	return &_Instance;
}

bool SKillModule::CastSkill(BattleSide& ack, BattleSide& def, int skill_id)
{
	//判断释放条件

	//判断技能CD冷却时间

	//生成技能
	SKillGenerator::GetInstancePtr()->CreateSkill(ack, def, skill_id);

	//消耗处理

	//冷却技能

	return true;
}

bool SKillModule::CostHp(BattleSide & side, int skill_id)
{
	return false;
}

bool SKillModule::CostMp(BattleSide & side, int skill_id)
{
	return false;
}

bool SKillModule::CostEnergy(BattleSide & side, int skill_id)
{
	return false;
}

bool SKillModule::AddCd(BattleSide & side, int skill_id)
{
	return false;
}
