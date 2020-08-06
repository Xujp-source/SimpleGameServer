#ifndef __SERVER_DEFINE_H__
#define __SERVER_DEFINE_H__


enum 
{
	SQL_BEGIN,
	//读取
	SQL_READ,
	//执行
	SQL_EXECUTE,
	//事务
	SQL_TRANSACTION,
	//replace
	SQL_REPLACE
};

enum BATTLE_MODE
{
	//未战斗
	BATTLE_MODE_NONE,
	//战斗初始化
	BATTLE_MODE_INIT,
	//处在战斗中
	BATTLE_MODE_BATTLE,
	//战斗结束
	BATTLE_MODE_FINISH
};

enum BATTLE_TARGET
{
	//攻击方
	ATK_TARGET,
	//防守方
	DEFINE_TARGET
};

enum BATTLE_COMMAND
{
	//初始化空命令
	BATTLE_COMMAND_NONE,
	//发起释放技能命令
	BATTLE_COMMAND_SKILL,
	//发起防御命令
	BATTLE_COMMAND_DEFINE,
	//发起使用道具命令
	BATTLE_COMMAND_USING,
	//发起切换卡牌命令
	BATTLE_COMMAND_CHANGECARD,
	//发起逃跑命令
	BATTLE_COMMAND_ESCAPE

};

enum BATTLE_ROUND_LOCK
{
	//下一回合指令解锁标记
	COMMAND_UNLOCK,
	//当前回合收到指令后的加锁标记
	COMMAND_LOCK
};


//阵营数
#define BATTLE_SIDE_COUNT 2
//当前回合选择操作指令的时间限制
#define ROUND_TIME 20
//一场战斗持续的最大时间
#define BATTLE_MAX_TIME 60*60

#endif