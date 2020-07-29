#ifndef __BATTLE_DATA_H__
#define __BATTLE_DATA_H__

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
	unsigned long long usr_id;
	int is_robot;
	int sequence;  //参战的第几只
	Card Entry[5];
};

#endif