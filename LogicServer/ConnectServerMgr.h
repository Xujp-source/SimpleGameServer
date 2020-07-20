#ifndef __CONNECT_SERVER_MGR_H__
#define __CONNECT_SERVER_MGR_H__
#include "stdafx.h"

// ����������LogicServer��Ķ������
class ConnectServerMgr
{
private:
	ConnectServerMgr(void);
	~ConnectServerMgr(void);

public:
	static ConnectServerMgr* GetInstancePtr();

public:
	bool Init();

	void RegisterMessageHanler();

	//����������Ϣ
	bool SendData(int ServerID, int MsgID, const google::protobuf::Message& pdata);

public:
	//*******************��Ϣ������**************************
	bool OnMsgGameSvrRegister(NetPacket* pack);  //��Ϸ���������Ӻ��ע������
	bool OnMsgGameSvrHeartReq(NetPacket* pack);	 //��Ϸ����������������
	//*********************************************************

private:
	//server_id to socketfd
	std::map<int, int> m_connServerMap;
};

#endif
