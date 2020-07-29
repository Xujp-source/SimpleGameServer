#include "GameScene.h"
#include "../ServerDefine.h"
#include "../ServerEngine/CELLTimestamp.hpp"

GameScene::GameScene()
{
	RegisterMessageHanler();
}

GameScene::~GameScene()
{
}

void GameScene::RegisterMessageHanler()
{

	BATTLETimeOutCheck();
}

bool GameScene::Init()
{
	Mode = BATTLE_MODE_BATTLE;
	RoundCount = 1;
	RoundEndTime = RoundEndTime + 20;
	EndTime = EndTime + 60 * 60;
	CmdLock = BATTLE_COMMAND_UNLOCK;
	return true;
}

bool GameScene::BATTLECommand()
{
	//判断是否超过游戏最大时间
	if (BATTLETimeOutCheck() == true)
	{
		return false;
	}
	//判断是否有资格进入下一回合
	if (BATTLENextRoundCheck() == false)
	{
		return false;
	}
	//执行当前命令操作
	ExecBATTLECommand();

	//回合数加一
	RoundCount = RoundCount + 1;
	//增加下一回合的结束时间戳
	RoundEndTime = CELLTime::getNowInSec() + 20;
	//解锁命令操作
	CmdLock = BATTLE_COMMAND_UNLOCK;
	//重置命令
	for (int i = 0; i < BATTLE_SIDE_COUNT; i++)
	{
		Side[i].Entry[Side[i].sequence].cmd = BATTLE_COMMAND_NONE;
	}

	return true;
}

bool GameScene::BATTLEFinish()
{

	return true;
}

bool GameScene::BATTLETimeOutCheck()
{
	if (CELLTime::getNowInSec() >= EndTime)
	{
		//ERROR_RETURN_TRUE(Mode == BATTLE_MODE_BATTLE);
		Mode = BATTLE_MODE_FINISH;
	}
	
	return false;
}

bool GameScene::BATTLENextRoundCheck()
{
	return false;
}

bool GameScene::ExecBATTLECommand()
{
	return false;
}

bool GameScene::OnMsgCommandAtkReq(NetPacket * pack)
{
	//ERROR_RETURN_TRUE(Mode == BATTLE_MODE_BATTLE);
	//ERROR_RETURN_TRUE(CmdLock != BATTLE_COMMAND_UNLOCK);
	////反序列化
	//CommandAtkReq req;
	//char *str = pack->m_pDataBuffer->buff;
	//req.ParsePartialFromArray(pack->m_pDataBuffer->buff, 1024);

	////条件验证
	//unsigned long long uid = req.uid();
	//ERROR_RETURN_TRUE(uid != 0);
	//int command = req.command();
	//ERROR_RETURN_TRUE(command != BATTLE_COMMAND_ATK);

	//for (int i = 0; i < BATTLE_SIDE_COUNT; i++)
	//{
	//	if (uid == Side[i].usr_id)
	//	{
	//		CmdLock = BATTLE_COMMAND_LOCK;
	//		Side[i].Entry[Side[i].sequence].cmd = BATTLE_COMMAND_ATK;
	//		break;
	//	}
	//}

	return true;
}
