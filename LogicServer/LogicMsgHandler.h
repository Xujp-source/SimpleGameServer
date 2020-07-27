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
	bool OnMsgLoginSvrHeartAck(NetPacket* pack);		//��¼��������ȷ��
	bool OnMsgGateSvrHeartAck(NetPacket* pack);			//���ط�������ȷ��

	bool OnMsgLoadPlayerListReq(NetPacket* pack);		//���ؽ�ɫ�б�
	bool OnMsgCreatePlayerReq(NetPacket* pack);			//������ɫ
	bool OnMsgSelectPlayerEnterReq(NetPacket* pack);	//ѡ���ɫ������Ϸ

	bool OnMsgSelectEnterLogicSvrReq(NetPacket* pack);	//ѡ�������߼�������¼��������accountid������֤��
	//*********************************************************
};

#endif