#ifndef _DB_MSG_HANDLER_H_
#define _DB_MSG_HANDLER_H_
#include "stdafx.h"
//������Ϣ����

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
	//*******************��Ϣ������**************************
	bool OnMsgGateSvrHeartAck(NetPacket* pack);   //���ط�������ȷ��
	bool OnMsgDBExeSqlReq(NetPacket* pack);		  //�������ݿ��������
	//*********************************************************
};

#endif