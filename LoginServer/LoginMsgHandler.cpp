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
	//CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_BAG_UNLOCK_REQ, &DBMsgHandler::OnMsgGateSvrHeartAck, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_ACCOUNT_REG_REQ, &LoginMsgHandler::OnMsgAccountRegReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_ACCOUNT_LOGIN_REQ, &LoginMsgHandler::OnMsgAccountLoginReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_SERVER_LIST_REQ, &LoginMsgHandler::OnMsgLoadLogicSvrListReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_ACCOUNT_LOGIN_VERIFY_ACK, &LoginMsgHandler::OnMsgAccountRegFromDBAck, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_ACCOUNT_REG_TO_DBSVR_ACK, &LoginMsgHandler::OnMsgAccountLoginFromDBAck, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_LOAD_LOGICSVR_LIST_FROM_DBSVR_ACK, &LoginMsgHandler::OnMsgLoadLogicSvrListFromDBAck, this);
}

bool LoginMsgHandler::OnMsgGateSvrHeartAck(NetPacket * pack)
{
	return false;
}

bool LoginMsgHandler::OnMsgAccountLoginReq(NetPacket * pack)
{
	//反序列化
	AccountLoginReq req;
	char *str = pack->m_pDataBuffer->buff;
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

	//推给DBServer验证账号
	int m_DBConnID = CGameService::GetInstancePtr()->GetDBConnID();
	CGameService::GetInstancePtr()->SendData(m_DBConnID, MSG_ACCOUNT_LOGIN_VERIFY_REQ, dbReq);

	return true;
}

bool LoginMsgHandler::OnMsgAccountLoginFromDBAck(NetPacket * pack)
{
	return false;
}

bool LoginMsgHandler::OnMsgAccountRegReq(NetPacket * pack)
{
	//反序列化
	AccountRegisterReq req;
	char *str = pack->m_pDataBuffer->buff;
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

	//推给DBServer注册账号
	int m_DBConnID = CGameService::GetInstancePtr()->GetDBConnID();
	CGameService::GetInstancePtr()->SendData(m_DBConnID, MSG_ACCOUNT_REG_TO_DBSVR_REQ, dbReq);

	return true;
}

bool LoginMsgHandler::OnMsgAccountRegFromDBAck(NetPacket * pack)
{
	return false;
}

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

bool LoginMsgHandler::OnMsgLoadLogicSvrListFromDBAck(NetPacket * pack)
{
	return false;
}


