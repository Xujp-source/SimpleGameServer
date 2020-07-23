#ifndef _DB_MSG_HANDLER_H_
#define _DB_MSG_HANDLER_H_
#include "stdafx.h"
//杂项消息处理

class DBMsgHandler
{
private:
	DBMsgHandler(void);
	~DBMsgHandler(void);

public:
	static DBMsgHandler* GetInstancePtr();

public:
	bool Init();

	void RegisterMessageHanler();

public:
	//*******************消息处理定义**************************
	bool OnMsgGateSvrHeartAck(NetPacket* pack);   //网关服的心跳确认
	bool OnMsgDBExeSqlReq(NetPacket* pack);		  //处理数据库操作请求
	//*********************************************************
};

#endif