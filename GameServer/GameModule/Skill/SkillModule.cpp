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
	//�ж��ͷ�����

	//�жϼ���CD��ȴʱ��

	//���ɼ���
	SKillGenerator::GetInstancePtr()->CreateSkill(ack, def, skill_id);

	//���Ĵ���

	//��ȴ����

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
