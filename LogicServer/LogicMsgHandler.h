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
	bool OnMsgDBSvrHeartAck(NetPacket* pack);			//DB������������ȷ��

	bool OnMsgLoadPlayerListReq(NetPacket* pack);		//���ؽ�ɫ�б�
	bool OnMsgLoadPlayerListAck(NetPacket* pack);		//��ɫ�б�������DB
	bool OnMsgCreatePlayerReq(NetPacket* pack);			//������ɫ
	bool OnMsgCreatePlayerAck(NetPacket* pack);			//������ɫ�������DB
	bool OnMsgSelectPlayerEnterReq(NetPacket* pack);	//ѡ���ɫ������Ϸ

	bool OnMsgSelectEnterLogicSvrReq(NetPacket* pack);	//ѡ�������߼�������loginserver����¼��������accountid������֤��
	bool OnMsgLostConnectReq(NetPacket* pack);			//�����Ͽ���������
	bool OnMsgLogoutReq(NetPacket* pack);				//�ǳ�����
	//*********************************************************

private:
	std::map<unsigned long long, int> account_map;
};

#endif