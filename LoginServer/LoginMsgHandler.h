#ifndef _LOGIN_MSG_HANDLER_H_
#define _LOGIN_MSG_HANDLER_H_
#include "stdafx.h"
//杂项消息处理

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
	//****************************************消息处理定义***********************************************
	bool OnMsgLogicSvrHeartAck(NetPacket* pack);			    //逻辑服的心跳确认
	bool OnMsgDBSvrHeartAck(NetPacket* pack);					//DB操作服的心跳确认

	bool OnMsgAccountLoginReq(NetPacket* pack);					//登录账号请求
	bool OnMsgAccountLoginFromDBAck(NetPacket* pack);			//登录账号结果来自DBServer
	bool OnMsgAccountRegReq(NetPacket* pack);					//注册账号请求
	bool OnMsgAccountRegFromDBAck(NetPacket* pack);				//注册账号结果来自DBServer

	bool OnMsgLoadLogicSvrListReq(NetPacket* pack);				//加载逻辑服的列表
	bool OnMsgLoadLogicSvrListFromDBAck(NetPacket* pack);		//加载逻辑服的列表结果来自DBServer

	bool OnMsgSelectEnterLogicSvrReq(NetPacket* pack);			//选择进入哪个逻辑服
	bool OnMsgSelectEnterLogicSvrFromLogicAck(NetPacket* pack);	//选择进入哪个逻辑服结果来自LogicServer

	bool OnMsgLostConnectReq(NetPacket* pack);					//主动断开连接请求
	//***************************************************************************************************
};

#endif