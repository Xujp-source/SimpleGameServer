#include "LogicMsgHandler.h"
#include "MsgHandlerManager.hpp"

LogicMsgHandler::LogicMsgHandler(void)
{
}

LogicMsgHandler::~LogicMsgHandler(void)
{
}

LogicMsgHandler * LogicMsgHandler::GetInstancePtr()
{
	static LogicMsgHandler Instance;
	return &Instance;
}

bool LogicMsgHandler::Init()
{
	RegisterMessageHanler();
	return true;
}

void LogicMsgHandler::RegisterMessageHanler()
{
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_BAG_UNLOCK_REQ, &LogicMsgHandler::OnMsgLoginSvrHeartAck, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_BAG_UNLOCK_REQ, &LogicMsgHandler::OnMsgGateSvrHeartAck, this);
}

bool LogicMsgHandler::OnMsgLoginSvrHeartAck(NetPacket * pack)
{
	return false;
}

bool LogicMsgHandler::OnMsgGateSvrHeartAck(NetPacket * pack)
{
	return false;
}

bool LogicMsgHandler::OnMsgLoadPlayerListReq(NetPacket * pack)
{
	//�����л� 

	//��֤�˺ź�rand��ӳ����Ϣ

	//����sql���

	//�Ƹ�DBServer��ȡ����б�

	//�����ͻ�������б���Ϣ

	return false;
}

bool LogicMsgHandler::OnMsgCreatePlayerReq(NetPacket * pack)
{
	//�����л� 

	//����sql���

	//�Ƹ�DBServer�������

	//�����ͻ��� ��Ҵ������
	return false;
}

bool LogicMsgHandler::OnMsgSelectPlayerEnterReq(NetPacket * pack)
{
	//�����л� 

	//Create Player

	//�����ͻ��� �����player����
	return false;
}

bool LogicMsgHandler::OnMsgSelectEnterLogicSvrReq(NetPacket * pack)
{
	//�����л� 

	//����account�����ֵ��ӳ����֤

	//�ش���LoginServer�������

	return false;
}


