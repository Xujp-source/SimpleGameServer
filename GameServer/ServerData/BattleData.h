#ifndef __BATTLE_DATA_H__
#define __BATTLE_DATA_H__
#include<map>

//每张参战卡牌的信息
struct Card
{
	int cur_hp;        //当前hp
	int cur_hp_rec;    //当前hp回复速度
	int cur_mp;        //当前mp
	int cur_mp_rec;    //当前mp回复速度
	int cur_atk;       //当前攻击力
	int cur_def;       //当前护甲
	int cur_matk;      //当前智力
	int cur_mdef;      //当前魔抗
	int cur_acc;       //当前命中
	int cur_eva;       //当前闪避
	int cur_cri;       //当前暴击
	int cur_cdef;      //当前抗暴

	int cur_cmd;
	int skill_id;
	int card_id;
	unsigned long long uid;
	std::map<int, int> cd_map; //技能id - 技能cd

};

//一个阵营的信息
struct BattleSide
{
	unsigned long long player_uid;
	int is_robot;
	unsigned long long card_uid; //当前参战的唯一卡牌id
	std::map<unsigned long long, Card*> card_map;
};

#endif