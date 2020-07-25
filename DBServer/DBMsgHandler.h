#ifndef _DB_MSG_HANDLER_H_
#define _DB_MSG_HANDLER_H_
#include "stdafx.h"
//杂项消息处理

class CppMySQLQuery;
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

	CppMySQLQuery* querySQL(const char* sqlcmd);

	int execSQL(const char* sqlcmd);

public:
	//*******************消息处理定义**************************
	bool OnMsgGateSvrHeartAck(NetPacket* pack);   //网关服的心跳确认
	bool OnMsgDBExeSqlReq(NetPacket* pack);		  //处理数据库操作请求
	bool OnMsgAccountLoginVerifyReq(NetPacket * pack);
	bool OnMsgAccountRegToDBsvrReq(NetPacket * pack);
	bool OnMsgLoadLogicsvrListFromDBsvrReq(NetPacket * pack);
	//*********************************************************
};

#endif