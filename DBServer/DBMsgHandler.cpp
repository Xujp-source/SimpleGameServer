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
	//CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_BAG_UNLOCK_REQ, &DBMsgHandler::OnMsgGateSvrHeartAck, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_DB_EXE_SQL_REQ, &DBMsgHandler::OnMsgDBExeSqlReq, this);

}

bool DBMsgHandler::OnMsgGateSvrHeartAck(NetPacket * pack)
{
	return false;
}

bool DBMsgHandler::OnMsgDBExeSqlReq(NetPacket * pack)
{
	DBExeSqlReq req;
	char *str = pack->m_pDataBuffer->buff;
	req.ParsePartialFromArray(pack->m_pDataBuffer->buff, 1024);
	int exectype = req.exectype();
	if (exectype == SQL_READ)
	{
		CppMySQLQuery res = CGameService::GetInstancePtr()->tDBConnection.querySQL(req.sqlcmd().c_str());
		CELLLog::Info("copyid = %d, roleid = %d\n", res.getIntField("copyid"), res.getIntField("roleid"));
	}
	else
	{
		int res = CGameService::GetInstancePtr()->tDBConnection.execSQL(req.sqlcmd().c_str());
		if (res != -1)
		{
			CELLLog::Info("sql falied !!!!!!!!!!!!!!!!!!\n");
			//CGameService::GetInstancePtr()->SendData(pack->m_dwConnID, MSG_DB_EXE_SQL_ACK, req);
		}
	}
	
	return false;
}
