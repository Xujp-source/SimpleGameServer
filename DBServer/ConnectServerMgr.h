#ifndef __CONNECT_SERVER_MGR_H__
#define __CONNECT_SERVER_MGR_H__
#include "stdafx.h"

// 其他服连接GameServer后的对象管理
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

	//推送网络消息
	bool SendData(int ServerID, int MsgID, const google::protobuf::Message& pdata);

public:
	//*******************消息处理定义**************************
	
	//*********************************************************

private:
	//server_id to socketfd
	std::map<int, int> m_connServerMap;
};

#endif
