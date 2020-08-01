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
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_DBSVR_HEART_ACK, &LogicMsgHandler::OnMsgDBSvrHeartAck, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_LOAD_PLAYER_LIST_REQ, &LogicMsgHandler::OnMsgLoadPlayerListReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_CREATE_PLAYER_REQ, &LogicMsgHandler::OnMsgCreatePlayerReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_SELECT_PLAYER_ENTER_REQ, &LogicMsgHandler::OnMsgSelectPlayerEnterReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_SELECT_ENTER_LOGICSVR_REQ, &LogicMsgHandler::OnMsgSelectEnterLogicSvrReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_LOST_CONNECT_REQ, &LogicMsgHandler::OnMsgLostConnectReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_LOGOUT_REQ, &LogicMsgHandler::OnMsgLogoutReq, this);
}

bool LogicMsgHandler::OnMsgDBSvrHeartAck(NetPacket * pack)
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

bool LogicMsgHandler::OnMsgLostConnectReq(NetPacket * pack)
{
	return false;
}

bool LogicMsgHandler::OnMsgLogoutReq(NetPacket * pack)
{
	return false;
}


