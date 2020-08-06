#ifndef _SKILL_GENERATOR_H_
#define _SKILL_GENERATOR_H_
#include "../../ServerData/BattleData.h"

//����������
class SKillGenerator
{
private:
	SKillGenerator();
	virtual ~SKillGenerator();

public:
	static SKillGenerator* GetInstancePtr();

public:
	//���ɼ����㷨���
	bool CreateSkill(BattleSide& ack, BattleSide& def, int skill_id);
	
};

#endif

