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
	//�ж��Ƿ񳬹���Ϸ���ʱ��
	if (BATTLETimeOutCheck() == true)
	{
		return false;
	}
	//�ж��Ƿ����ʸ������һ�غ�
	if (BATTLENextRoundCheck() == false)
	{
		return false;
	}
	//ִ�е�ǰ�������
	ExecBATTLECommand();

	//�غ�����һ
	RoundCount = RoundCount + 1;
	//������һ�غϵĽ���ʱ���
	RoundEndTime = CELLTime::getNowInSec() + 20;
	//�����������
	CmdLock = BATTLE_COMMAND_UNLOCK;
	//��������
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
	////�����л�
	//CommandAtkReq req;
	//char *str = pack->m_pDataBuffer->buff;
	//req.ParsePartialFromArray(pack->m_pDataBuffer->buff, 1024);

	////������֤
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
