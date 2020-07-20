#ifndef _AGENT_H_
#define _AGENT_H_
#include "google/protobuf/message.h"
#include "MsgHandlerManager.hpp"
#include "./ServerEngine/MessageHeader.hpp"
#include <map>

// 连接对象基类
class Agent
{
private:
	int fd;

public:
	Agent();
	virtual ~Agent();

public:
	//推送网络消息
	bool SendData(int MsgID, const google::protobuf::Message& pdata);

	//设置sockfd
	inline void SetFd(int sockfd) { fd = sockfd; }

	//获得sockfd
	inline int GetFd() { return fd; }

	//是否是玩家对象
	virtual bool IsUser() { return false; }

	//是否是连接其他服后新生成的连接对象
	bool isConnect() { return isConFlag; }

	void SetConnect(bool res) { isConFlag = res; }

public:
	//*******************消息处理定义**************************
	bool OnMsgUserHeartReq(NetPacket* pack);	  //Client(玩家)的心跳请求
	//*********************************************************
	
public:
	//网络消息泵
	CHandlerManager m_NetMessagePump;

	bool isConFlag = false;

};

#endif