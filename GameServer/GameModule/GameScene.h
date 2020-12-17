#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_
#include "../ServerData/BattleData.h"
#include "../stdafx.h"

class GameScene
{
private:
	//场景uid
	unsigned long long m_uid;
public:
	GameScene();
	virtual ~GameScene();
	void RegisterMessageHanler();
	//初始化场景对象
	bool Init();
	//处理战斗状态
	bool BATTLECommand();
	//战斗结束
	bool BATTLEFinish();
	//战斗是否超时检测
	bool BATTLETimeOutCheck();
	//是否进入下一回合检测
	bool BATTLENextRoundCheck();
	//执行战斗指令
	bool ExecBATTLECommand();
public:
	//获取场景uid
	inline int GetUid() { return m_uid; }
	//设置场景uid
	inline void SetUid(int uid) { m_uid = uid; }
public:
	//*******************消息处理定义**************************
	bool OnMsgCommandSkillReq(NetPacket* pack);         //释放技能请求
	bool OnMsgCommandDefineReq(NetPacket* pack);        //防御请求
	bool OnMsgCommandUsingReq(NetPacket* pack);         //使用道具请求
	bool OnMsgCommandChangeCardReq(NetPacket* pack);    //切换卡牌请求
	bool OnMsgCommandEscapeReq(NetPacket* pack);        //逃跑请求
	//*********************************************************
public:
	//当前的模式
	int Mode;
	//场上阵营
	BattleSide Side[BATTLE_SIDE_COUNT];
	//当前战斗回合数
	int RoundCount;
	//当前回合指令的操作结束时间戳
	unsigned long long RoundEndTime;
	//战斗持续的最大时间(结束时间戳)
	unsigned long long EndTime;
};

#endif
