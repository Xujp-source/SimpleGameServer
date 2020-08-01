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
	//反序列化 

	//验证账号和rand的映射信息

	//构造sql语句

	//推给DBServer获取玩家列表

	//返给客户端玩家列表信息

	return false;
}

bool LogicMsgHandler::OnMsgCreatePlayerReq(NetPacket * pack)
{
	//反序列化 

	//构造sql语句

	//推给DBServer创建玩家

	//返给客户端 玩家创建结果
	return false;
}

bool LogicMsgHandler::OnMsgSelectPlayerEnterReq(NetPacket * pack)
{
	//反序列化 

	//Create Player

	//返给客户端 构造的player对象
	return false;
}

bool LogicMsgHandler::OnMsgSelectEnterLogicSvrReq(NetPacket * pack)
{
	//反序列化 

	//创建account和随机值的映射验证

	//回传给LoginServer创建结果

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


