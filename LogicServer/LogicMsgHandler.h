#ifndef _LOGIC_MSG_HANDLER_H_
#define _LOGIC_MSG_HANDLER_H_
#include "stdafx.h"
//������Ϣ����

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
	//*******************��Ϣ������**************************
	bool OnMsgLoginSvrHeartAck(NetPacket* pack);  //��¼��������ȷ��
	bool OnMsgGateSvrHeartAck(NetPacket* pack);   //���ط�������ȷ��
	//*********************************************************
};

#endif