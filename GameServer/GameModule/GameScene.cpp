#include "GameScene.h"
#include "../MsgHandlerManager.hpp"
#include "../protoc/Battle.pb.h"

GameScene::GameScene()
{
	RegisterMessageHanler();
}

GameScene::~GameScene()
{
}

void GameScene::RegisterMessageHanler()
{
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_COMMAND_ATK_REQ, &GameScene::OnMsgCommandAtkReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_COMMAND_SKILL_REQ, &GameScene::OnMsgCommandSkillReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_COMMAND_DEFINE_REQ, &GameScene::OnMsgCommandDefineReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_COMMAND_USING_REQ, &GameScene::OnMsgCommandUsingReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_COMMAND_CHANGE_CARD_REQ, &GameScene::OnMsgCommandChangeCardReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_COMMAND_ESCAPE_REQ, &GameScene::OnMsgCommandEscapeReq, this);
}

bool GameScene::Init()
{
	Mode = BATTLE_MODE_BATTLE;
	RoundCount = 1;
	RoundEndTime = RoundEndTime + ROUND_TIME;
	EndTime = EndTime + BATTLE_MAX_TIME;
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
	RoundEndTime = CELLTime::getNowInSec() + ROUND_TIME;
	//�����������
	CmdLock = BATTLE_COMMAND_UNLOCK;
	//��������
	for (int i = 0; i < BATTLE_SIDE_COUNT; i++)
	{
		std::map<unsigned long long, Card>::iterator itor = Side[i].cardmap.find(Side[i].carduid);
		itor->second.cmd = BATTLE_COMMAND_ATK;
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
	ERROR_RETURN_TRUE(Mode == BATTLE_MODE_BATTLE);
	ERROR_RETURN_TRUE(CmdLock != BATTLE_COMMAND_UNLOCK);
	//�����л�
	CommandAtkReq req;
	char *str = pack->m_pDataBuffer->buff;
	req.ParsePartialFromArray(pack->m_pDataBuffer->buff, 1024);

	//������֤
	unsigned long long uid = req.uid();
	ERROR_RETURN_TRUE(uid != 0);
	int command = req.cmd();
	ERROR_RETURN_TRUE(command != BATTLE_COMMAND_ATK);

	for (int i = 0; i < BATTLE_SIDE_COUNT; i++)
	{
		if (uid == Side[i].playeruid)
		{
			std::map<unsigned long long, Card>::iterator itor = Side[i].cardmap.find(Side[i].carduid);
			itor->second.cmd = BATTLE_COMMAND_ATK;
			CmdLock = BATTLE_COMMAND_LOCK;
			break;
		}
	}

	return true;
}

bool GameScene::OnMsgCommandSkillReq(NetPacket * pack)
{
	return false;
}

bool GameScene::OnMsgCommandDefineReq(NetPacket * pack)
{
	return false;
}

bool GameScene::OnMsgCommandUsingReq(NetPacket * pack)
{
	return false;
}

bool GameScene::OnMsgCommandChangeCardReq(NetPacket * pack)
{
	return false;
}

bool GameScene::OnMsgCommandEscapeReq(NetPacket * pack)
{
	return false;
}
