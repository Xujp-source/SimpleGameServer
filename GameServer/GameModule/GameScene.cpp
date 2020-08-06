#include "GameScene.h"
#include "./Skill/SkillModule.h"
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
	//��������ͽ���������
	for (int i = 0; i < BATTLE_SIDE_COUNT; i++)
	{
		ERROR_RETURN_TRUE(Side[i].cmd_lock != COMMAND_UNLOCK);
		Side[i].cmd_lock = COMMAND_UNLOCK;

		std::map<unsigned long long, Card*>::iterator itor = Side[i].card_map.find(Side[i].card_uid);
		itor->second->cur_cmd = BATTLE_COMMAND_NONE;
	}
	//״̬ͬ����GameScene����������

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
	for (int i = 0; i < BATTLE_SIDE_COUNT; i++)
	{
		std::map<unsigned long long, Card*>::iterator itor = Side[i].card_map.find(Side[i].card_uid);
		switch (itor->second->cur_cmd)
		{
		case BATTLE_COMMAND_SKILL:
			SKillModule::GetInstancePtr()->CastSkill(Side[ATK_TARGET], Side[DEFINE_TARGET], itor->second->skill_id);
			break;
		default:
			break;

		}
	}
	return true;
}

bool GameScene::OnMsgCommandSkillReq(NetPacket * pack)
{
	ERROR_RETURN_TRUE(Mode == BATTLE_MODE_BATTLE);
	//�����л�
	CommandSkillReq req;
	char *str = pack->m_pDataBuffer->buff;
	req.ParsePartialFromArray(pack->m_pDataBuffer->buff, 1024);

	//������֤
	unsigned long long uid = req.uid();
	ERROR_RETURN_TRUE(uid != 0);
	int command = req.cmd();
	ERROR_RETURN_TRUE(command != BATTLE_COMMAND_SKILL);

	for (int i = 0; i < BATTLE_SIDE_COUNT; i++)
	{
		if (uid == Side[i].player_uid)
		{
			//����ǰ�غ���ָ�����������ף�
			ERROR_RETURN_TRUE(Side[i].cmd_lock != COMMAND_LOCK);
			Side[i].cmd_lock = COMMAND_LOCK;
			//��ǰ�غϵ�ָ��
			std::map<unsigned long long, Card*>::iterator itor = Side[i].card_map.find(Side[i].card_uid);
			itor->second->cur_cmd = BATTLE_COMMAND_SKILL;
			break;
		}
	}

	return true;
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
