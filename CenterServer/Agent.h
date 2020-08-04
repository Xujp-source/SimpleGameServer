#ifndef _AGENT_H_
#define _AGENT_H_
#include "google/protobuf/message.h"
#include "EventHandlerManager.hpp"
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

	void RegisterMessageHanler();

public:
	//推送网络消息
	bool SendData(int MsgID, const google::protobuf::Message& pdata);

	//设置sockfd
	inline void SetFd(int sockfd) { fd = sockfd; }

	//获得sockfd
	inline int GetFd() { return fd; }

	//是否是玩家对象
	virtual bool IsUser() { return false; }

public:
	//*******************消息处理定义**************************
	bool OnMsgClientHeartReq(NetPacket* pack);	  //来自Client的心跳请求
	//*********************************************************
	
public:
	//网络消息泵
	CHandlerManager m_NetMessagePump;
	//回调事件
	CEventHandler m_EventPump;

};

#endif