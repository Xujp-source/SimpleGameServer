#ifndef __BATTLE_DATA_H__
#define __BATTLE_DATA_H__

//ÿ�Ų�ս���Ƶ���Ϣ
struct Card
{
	int hp;
	int mp;
	int id;
	int cmd;
	unsigned long long uid;

};

//һ����Ӫ����Ϣ
struct BattleSide
{
	unsigned long long usr_id;
	int is_robot;
	int sequence;  //��ս�ĵڼ�ֻ
	Card Entry[5];
};

#endif