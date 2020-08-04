#ifndef __BATTLE_DATA_H__
#define __BATTLE_DATA_H__
#include<map>

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
	unsigned long long carduid; //��ǰ��ս��Ψһ����id
	std::map<unsigned long long, Card> cardmap;
};

#endif