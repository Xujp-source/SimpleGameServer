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
	bool OnMsgGateSvrHeartAck(NetPacket* pack);				//网关服的心跳确认

	bool OnMsgAccountLoginReq(NetPacket* pack);				//登录请求
	bool OnMsgAccountLoginFromDBAck(NetPacket* pack);		//登录结果来自DBServer
	bool OnMsgAccountRegReq(NetPacket* pack);				//注册请求
	bool OnMsgAccountRegFromDBAck(NetPacket* pack);			//注册结果来自DBServer

	bool OnMsgLoadLogicSvrListReq(NetPacket* pack);			//加载逻辑服的列表
	bool OnMsgLoadLogicSvrListFromDBAck(NetPacket* pack);   //加载逻辑服的列表结果来自DBServer

	bool OnMsgSelectEnterLogicSvrReq(NetPacket* pack);	//选择进入哪个逻辑服
	bool OnMsgSelectEnterLogicSvrFromLogicAck(NetPacket* pack);	//选择进入哪个逻辑服结果来自LogicServer
	//***************************************************************************************************
};

#endif