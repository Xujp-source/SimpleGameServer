#ifndef __BATTLE_DATA_H__
#define __BATTLE_DATA_H__
#include<map>

//每张参战卡牌的信息
struct Card
{
	int hp;
	int mp;
	int id;
	int cmd;
	unsigned long long uid;

};

//一个阵营的信息
struct BattleSide
{
	unsigned long long playeruid;
	int is_robot;
	unsigned long long carduid; //当前参战的唯一卡牌id
	std::map<unsigned long long, Card> cardmap;
};

#endif