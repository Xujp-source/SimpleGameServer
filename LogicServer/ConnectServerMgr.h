#ifndef __CONNECT_SERVER_MGR_H__
#define __CONNECT_SERVER_MGR_H__
#include "stdafx.h"

// 其他服连接LogicServer后的对象管理
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
	bool OnMsgGameSvrRegister(NetPacket* pack);  //游戏服务器连接后的注册请求
	bool OnMsgGameSvrHeartReq(NetPacket* pack);	 //游戏服务器的心跳请求
	//*********************************************************

private:
	//server_id to socketfd
	std::map<int, int> m_connServerMap;
};

#endif
