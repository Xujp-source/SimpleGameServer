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
	unsigned long long playeruid;
	int is_robot;
	unsigned long long carduid; //��ս��Ψһ����id
	Card Entry[5];
};

#endif