#include "LoginMsgHandler.h"
#include "MsgHandlerManager.hpp"
#include "GameService.h"
#include "./protoc/Login.pb.h"
#include "./protoc/DBExcute.pb.h"

LoginMsgHandler::LoginMsgHandler(void)
{
}

LoginMsgHandler::~LoginMsgHandler(void)
{
}

LoginMsgHandler * LoginMsgHandler::GetInstancePtr()
{
	static LoginMsgHandler Instance;
	return &Instance;
}

bool LoginMsgHandler::Init()
{
	RegisterMessageHanler();
	return true;
}

void LoginMsgHandler::RegisterMessageHanler()
{
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_LOGICSVR_HEART_ACK, &LoginMsgHandler::OnMsgLogicSvrHeartAck, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_DBSVR_HEART_ACK, &LoginMsgHandler::OnMsgDBSvrHeartAck, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_LOST_CONNECT_REQ, &LoginMsgHandler::OnMsgLostConnectReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_ACCOUNT_REG_REQ, &LoginMsgHandler::OnMsgAccountRegReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_ACCOUNT_LOGIN_REQ, &LoginMsgHandler::OnMsgAccountLoginReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_SERVER_LIST_REQ, &LoginMsgHandler::OnMsgLoadLogicSvrListReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_ACCOUNT_LOGIN_VERIFY_ACK, &LoginMsgHandler::OnMsgAccountLoginFromDBAck, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_ACCOUNT_REG_TO_DBSVR_ACK, &LoginMsgHandler::OnMsgAccountRegFromDBAck, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_LOAD_LOGICSVR_LIST_FROM_DBSVR_ACK, &LoginMsgHandler::OnMsgLoadLogicSvrListFromDBAck, this);
}

//逻辑服的心跳确认
bool LoginMsgHandler::OnMsgLogicSvrHeartAck(NetPacket * pack)
{
	return true;
}

//DB操作服的心跳确认
bool LoginMsgHandler::OnMsgDBSvrHeartAck(NetPacket * pack)
{
	return true;
}

//登录账号请求
bool LoginMsgHandler::OnMsgAccountLoginReq(NetPacket * pack)
{
	//反序列化
	AccountLoginReq req;
	req.ParsePartialFromArray(pack->m_pDataBuffer->buff, 1024);

	//条件验证
	unsigned long long account = req.account();
	ERROR_RETURN_TRUE(account != 0);
	std::string password = req.password();
	ERROR_RETURN_TRUE(password.length() != 0);

	//构造sql语句
	char szSql[128] = { 0 };
	snprintf(szSql, 128, "select * from account where id = %d and password = %s", account, password.c_str());
	DBExeSqlReq dbReq;
	dbReq.set_exectype(SQL_EXECUTE);
	dbReq.set_sqlcmd(szSql);
	dbReq.set_sockfd(pack->m_dwConnID);

	//推给DBServer验证账号
	int m_DBConnID = CGameService::GetInstancePtr()->GetDBConnID();
	CGameService::GetInstancePtr()->SendData(m_DBConnID, MSG_ACCOUNT_LOGIN_VERIFY_REQ, dbReq);

	return true;
}

//登录账号结果来自DBServer
bool LoginMsgHandler::OnMsgAccountLoginFromDBAck(NetPacket * pack)
{
	//反序列化
	AccountLoginAck ack;
	ack.ParsePartialFromArray(pack->m_pDataBuffer->buff, 1024);

	//条件验证
	int m_dwConnID = ack.sockfd();
	ERROR_RETURN_TRUE(m_dwConnID != 0);
	CGameService::GetInstancePtr()->SendData(m_dwConnID, MSG_ACCOUNT_LOGIN_ACK, ack);

	return true;
}

//注册账号请求
bool LoginMsgHandler::OnMsgAccountRegReq(NetPacket * pack)
{
	//反序列化
	AccountRegisterReq req;
	req.ParsePartialFromArray(pack->m_pDataBuffer->buff, 1024);

	//条件验证
	unsigned long long account = req.account();
	ERROR_RETURN_TRUE(account != 0);
	std::string password = req.password();
	ERROR_RETURN_TRUE(password.length() != 0);
	std::string name = req.name();
	ERROR_RETURN_TRUE(name.length() != 0);

	//构造sql语句
	char szSql[128] = { 0 };
	snprintf(szSql, 128, "insert into account values(%d, %s, %s)", account, password.c_str(), name.c_str());
	DBExeSqlReq dbReq;
	dbReq.set_exectype(SQL_EXECUTE);
	dbReq.set_sqlcmd(szSql);
	dbReq.set_sockfd(pack->m_dwConnID);

	//推给DBServer注册账号
	int m_DBConnID = CGameService::GetInstancePtr()->GetDBConnID();
	CGameService::GetInstancePtr()->SendData(m_DBConnID, MSG_ACCOUNT_REG_TO_DBSVR_REQ, dbReq);

	return true;
}

//注册账号结果来自DBServer
bool LoginMsgHandler::OnMsgAccountRegFromDBAck(NetPacket * pack)
{
	//反序列化
	AccountRegisterAck ack;
	ack.ParsePartialFromArray(pack->m_pDataBuffer->buff, 1024);

	//条件验证
	int m_dwConnID = ack.sockfd();
	ERROR_RETURN_TRUE(m_dwConnID != 0);
	CGameService::GetInstancePtr()->SendData(m_dwConnID, MSG_ACCOUNT_REG_ACK, ack);
	return true;
}

//加载逻辑服的列表
bool LoginMsgHandler::OnMsgLoadLogicSvrListReq(NetPacket * pack)
{
	//构造sql语句
	char szSql[128] = { 0 };
	snprintf(szSql, 128, "select * from server_list");
	DBExeSqlReq dbReq;
	dbReq.set_exectype(SQL_READ);
	dbReq.set_sqlcmd(szSql);

	//推给DBServer获取服务器列表
	int m_DBConnID = CGameService::GetInstancePtr()->GetDBConnID();
	CGameService::GetInstancePtr()->SendData(m_DBConnID, MSG_LOAD_LOGICSVR_LIST_FROM_DBSVR_REQ, dbReq);

	return true;
}

//加载逻辑服的列表结果来自DBServer
bool LoginMsgHandler::OnMsgLoadLogicSvrListFromDBAck(NetPacket * pack)
{
	return false;
}

//选择进入哪个逻辑服
bool LoginMsgHandler::OnMsgSelectEnterLogicSvrReq(NetPacket * pack)
{
	//反序列化
	SelectEnterLogicSvrReq req;
	req.ParsePartialFromArray(pack->m_pDataBuffer->buff, 1024);

	//条件验证
	unsigned long long account = req.account();
	ERROR_RETURN_TRUE(account != 0);
	int serverid = req.serverid();
	ERROR_RETURN_TRUE(serverid != 0);

	//这里暂时只考虑单服情况
	int m_LogicConnID = CGameService::GetInstancePtr()->GetLogicConnID();
	CGameService::GetInstancePtr()->SendData(m_LogicConnID, MSG_SELECT_ENTER_LOGICSVR_REQ, req);
	
	return true;
}

//选择进入哪个逻辑服结果来自LogicServer
bool LoginMsgHandler::OnMsgSelectEnterLogicSvrFromLogicAck(NetPacket * pack)
{
	return true;
}

//主动断开连接请求
bool LoginMsgHandler::OnMsgLostConnectReq(NetPacket * pack)
{
	return true;
}
