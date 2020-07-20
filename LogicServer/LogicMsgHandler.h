#ifndef _LOGIC_MSG_HANDLER_H_
#define _LOGIC_MSG_HANDLER_H_
#include "stdafx.h"
//杂项消息处理

class LogicMsgHandler
{
private:
	LogicMsgHandler(void);
	~LogicMsgHandler(void);

public:
	static LogicMsgHandler* GetInstancePtr();

public:
	bool Init();

	void RegisterMessageHanler();

public:
	//*******************消息处理定义**************************
	bool OnMsgLoginSvrHeartAck(NetPacket* pack);  //登录服的心跳确认
	bool OnMsgGateSvrHeartAck(NetPacket* pack);   //网关服的心跳确认
	//*********************************************************
};

#endif