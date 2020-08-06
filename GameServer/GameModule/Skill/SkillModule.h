#ifndef _SKILL_MODE_H_
#define _SKILL_MODE_H_
#include "../../ServerData/BattleData.h"

//�ͷ������������
class SKillModule
{
private:
	SKillModule();
	virtual ~SKillModule();

public:
	static SKillModule* GetInstancePtr();

public:
	//�ͷż���
	bool CastSkill(BattleSide& ack, BattleSide& def, int skill_id);

	//����HP
	bool CostHp(BattleSide& side, int skill_id);

	//����MP
	bool CostMp(BattleSide& side, int skill_id);

	//��������
	bool CostEnergy(BattleSide& side, int skill_id);

	//��ȴ�غ�
	bool AddCd(BattleSide& side, int skill_id);
};

#endif

