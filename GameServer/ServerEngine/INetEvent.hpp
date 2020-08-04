#ifndef _I_NET_EVENT_HPP_
#define _I_NET_EVENT_HPP_

#include"CELL.hpp"
#include"CELLClient.hpp"
//自定义
class CELLServer;

//网络事件接口
class INetEvent
{
public:
	//客户端加入事件
	virtual void OnNetJoin(CELLClient* pClient) = 0;
	//客户端离开事件
	virtual void OnNetLeave(CELLClient* pClient) = 0;
	//客户端消息事件
	virtual void OnNetMsg(CELLServer* pServer, CELLClient* pClient, netmsg_DataHeader* header) = 0;
	//recv事件
	virtual void OnNetRecv(CELLClient* pClient) = 0;
	//每秒操作
	virtual void time4msg() = 0;
	//更新操作
	virtual void OnUpdate() = 0;

};

#endif // !_I_NET_EVENT_HPP_
