#ifndef _LOGIN_MSG_HANDLER_H_
#define _LOGIN_MSG_HANDLER_H_
#include "stdafx.h"
//������Ϣ����

class LoginMsgHandler
{
private:
	LoginMsgHandler(void);
	~LoginMsgHandler(void);

public:
	static LoginMsgHandler* GetInstancePtr();

public:
	bool Init();

	void RegisterMessageHanler();

public:
	//****************************************��Ϣ������***********************************************
	bool OnMsgLogicSvrHeartAck(NetPacket* pack);			    //�߼���������ȷ��
	bool OnMsgDBSvrHeartAck(NetPacket* pack);					//DB������������ȷ��

	bool OnMsgAccountLoginReq(NetPacket* pack);					//��¼�˺�����
	bool OnMsgAccountLoginFromDBAck(NetPacket* pack);			//��¼�˺Ž������DBServer
	bool OnMsgAccountRegReq(NetPacket* pack);					//ע���˺�����
	bool OnMsgAccountRegFromDBAck(NetPacket* pack);				//ע���˺Ž������DBServer

	bool OnMsgLoadLogicSvrListReq(NetPacket* pack);				//�����߼������б�
	bool OnMsgLoadLogicSvrListFromDBAck(NetPacket* pack);		//�����߼������б�������DBServer

	bool OnMsgSelectEnterLogicSvrReq(NetPacket* pack);			//ѡ������ĸ��߼���
	bool OnMsgSelectEnterLogicSvrFromLogicAck(NetPacket* pack);	//ѡ������ĸ��߼����������LogicServer

	bool OnMsgLostConnectReq(NetPacket* pack);					//�����Ͽ���������
	//***************************************************************************************************
};

#endif