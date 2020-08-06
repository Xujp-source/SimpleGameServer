#ifndef __BATTLE_DATA_H__
#define __BATTLE_DATA_H__
#include<map>

//ÿ�Ų�ս���Ƶ���Ϣ
struct Card
{
	int cur_hp;        //��ǰhp
	int cur_hp_rec;    //��ǰhp�ظ��ٶ�
	int cur_mp;        //��ǰmp
	int cur_mp_rec;    //��ǰmp�ظ��ٶ�
	int cur_atk;       //��ǰ������
	int cur_def;       //��ǰ����
	int cur_matk;      //��ǰ����
	int cur_mdef;      //��ǰħ��
	int cur_acc;       //��ǰ����
	int cur_eva;       //��ǰ����
	int cur_cri;       //��ǰ����
	int cur_cdef;      //��ǰ����

	int cur_cmd;
	int skill_id;
	int card_id;
	unsigned long long uid;
	std::map<int, int> cd_map; //����id - ����cd

};

//һ����Ӫ����Ϣ
struct BattleSide
{
	unsigned long long player_uid;
	int is_robot;
	unsigned long long card_uid; //��ǰ��ս��Ψһ����id
	std::map<unsigned long long, Card*> card_map;
};

#endif