#include "DBMsgHandler.h"
#include "MsgHandlerManager.hpp"
#include "GameService.h"
#include "./protoc/DBExcute.pb.h"

DBMsgHandler::DBMsgHandler(void)
{
}

DBMsgHandler::~DBMsgHandler(void)
{
}

DBMsgHandler * DBMsgHandler::GetInstancePtr()
{
	static DBMsgHandler Instance;
	return &Instance;
}

bool DBMsgHandler::Init()
{
	RegisterMessageHanler();
	return true;
}

void DBMsgHandler::RegisterMessageHanler()
{
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_DB_EXE_SQL_REQ, &DBMsgHandler::OnMsgDBExeSqlReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_ACCOUNT_LOGIN_VERIFY_REQ, &DBMsgHandler::OnMsgAccountLoginVerifyReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_ACCOUNT_REG_TO_DBSVR_REQ, &DBMsgHandler::OnMsgAccountRegToDBsvrReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_LOAD_LOGICSVR_LIST_FROM_DBSVR_REQ, &DBMsgHandler::OnMsgLoadLogicsvrListFromDBsvrReq, this);
}

CppMySQLQuery * DBMsgHandler::querySQL(const char * sqlcmd)
{
	CppMySQL3DB tDBConnection;
	CppMySQLQuery res = tDBConnection.querySQL(sqlcmd);
	return &res;
}

int DBMsgHandler::execSQL(const char * sqlcmd)
{
	CppMySQL3DB tDBConnection;
	int res = tDBConnection.execSQL(sqlcmd);
	return res;
}

bool DBMsgHandler::OnMsgGateSvrHeartAck(NetPacket * pack)
{
	return false;
}

bool DBMsgHandler::OnMsgDBExeSqlReq(NetPacket * pack)
{
	DBExeSqlReq req;
	char *str = pack->m_pDataBuffer->buff;
	int length = sizeof(*str);
	int length2 = sizeof(str);
	req.ParsePartialFromArray(pack->m_pDataBuffer->buff, 1024);
	int exectype = req.exectype();
	if (exectype == SQL_READ)
	{
		CppMySQLQuery* res = querySQL(req.sqlcmd().c_str());
		CELLLog::Info("copyid = %d, roleid = %d\n", res->getIntField("copyid"), res->getIntField("roleid"));
		return true;
	}
	else
	{
		int res = CGameService::GetInstancePtr()->tDBConnection.execSQL(req.sqlcmd().c_str());
		if (res == -1)
		{
			CELLLog::Info("sql execute falied ........\n");
			CGameService::GetInstancePtr()->SendData(pack->m_dwConnID, MSG_DB_EXE_SQL_ACK, req);
			return false;
			//CGameService::GetInstancePtr()->SendData(pack->m_dwConnID, MSG_DB_EXE_SQL_ACK, req);
		}
		else
		{

		}
	}
	
	return false;
}

bool DBMsgHandler::OnMsgAccountLoginVerifyReq(NetPacket* pack)
{
	DBExeSqlReq req;
	req.ParsePartialFromArray(pack->m_pDataBuffer->buff, sizeof(pack->m_pDataBuffer->buff));

	int exectype = req.exectype();
	ERROR_RETURN_TRUE(exectype != SQL_EXECUTE);
	int sockfd = req.sockfd();
	ERROR_RETURN_TRUE(sockfd != 0);
	
	int res = execSQL(req.sqlcmd().c_str());
	AccountLoginAck ack;
	ack.set_res(res);
	ack.set_sockfd(sockfd);
	CGameService::GetInstancePtr()->SendData(pack->m_dwConnID, MSG_ACCOUNT_LOGIN_VERIFY_ACK, ack);

	return true;
}

bool DBMsgHandler::OnMsgAccountRegToDBsvrReq(NetPacket* pack)
{
	DBExeSqlReq req;
	req.ParsePartialFromArray(pack->m_pDataBuffer->buff, sizeof(pack->m_pDataBuffer->buff));

	int exectype = req.exectype();
	ERROR_RETURN_TRUE(exectype != SQL_EXECUTE);
	int sockfd = req.sockfd();
	ERROR_RETURN_TRUE(sockfd != 0);

	int res = execSQL(req.sqlcmd().c_str());
	AccountRegisterAck ack;
	ack.set_res(res);
	ack.set_sockfd(sockfd);
	CGameService::GetInstancePtr()->SendData(pack->m_dwConnID, MSG_ACCOUNT_REG_TO_DBSVR_ACK, ack);
	return true;
}

bool DBMsgHandler::OnMsgLoadLogicsvrListFromDBsvrReq(NetPacket* pack)
{
	return true;
}