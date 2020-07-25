#ifndef _DB_MSG_HANDLER_H_
#define _DB_MSG_HANDLER_H_
#include "stdafx.h"
//������Ϣ����

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
	//*******************��Ϣ������**************************
	bool OnMsgGateSvrHeartAck(NetPacket* pack);   //���ط�������ȷ��
	bool OnMsgDBExeSqlReq(NetPacket* pack);		  //�������ݿ��������
	bool OnMsgAccountLoginVerifyReq(NetPacket * pack);
	bool OnMsgAccountRegToDBsvrReq(NetPacket * pack);
	bool OnMsgLoadLogicsvrListFromDBsvrReq(NetPacket * pack);
	//*********************************************************
};

#endif