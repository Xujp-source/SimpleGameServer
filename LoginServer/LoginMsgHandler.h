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
	bool OnMsgGateSvrHeartAck(NetPacket* pack);				//���ط�������ȷ��

	bool OnMsgAccountLoginReq(NetPacket* pack);				//��¼����
	bool OnMsgAccountLoginFromDBAck(NetPacket* pack);		//��¼�������DBServer
	bool OnMsgAccountRegReq(NetPacket* pack);				//ע������
	bool OnMsgAccountRegFromDBAck(NetPacket* pack);			//ע��������DBServer

	bool OnMsgLoadLogicSvrListReq(NetPacket* pack);			//�����߼������б�
	bool OnMsgLoadLogicSvrListFromDBAck(NetPacket* pack);   //�����߼������б�������DBServer

	bool OnMsgSelectEnterLogicSvrReq(NetPacket* pack);	//ѡ������ĸ��߼���
	bool OnMsgSelectEnterLogicSvrFromLogicAck(NetPacket* pack);	//ѡ������ĸ��߼����������LogicServer
	//***************************************************************************************************
};

#endif