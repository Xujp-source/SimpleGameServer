#include "LogicMsgHandler.h"
#include "GameService.h"
#include "MsgHandlerManager.hpp"
#include "./protoc/Login.pb.h"
#include "./protoc/DBExcute.pb.h"

LogicMsgHandler::LogicMsgHandler(void)
{
}

LogicMsgHandler::~LogicMsgHandler(void)
{
}

LogicMsgHandler * LogicMsgHandler::GetInstancePtr()
{
	static LogicMsgHandler Instance;
	return &Instance;
}

bool LogicMsgHandler::Init()
{
	RegisterMessageHanler();
	return true;
}

void LogicMsgHandler::RegisterMessageHanler()
{
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_DBSVR_HEART_ACK, &LogicMsgHandler::OnMsgDBSvrHeartAck, this);

	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_LOAD_PLAYER_LIST_REQ, &LogicMsgHandler::OnMsgLoadPlayerListReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_LOAD_PLAYER_LIST_ACK, &LogicMsgHandler::OnMsgLoadPlayerListAck, this);

	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_CREATE_PLAYER_REQ, &LogicMsgHandler::OnMsgCreatePlayerReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_CREATE_PLAYER_ACK, &LogicMsgHandler::OnMsgCreatePlayerAck, this);

	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_SELECT_PLAYER_ENTER_REQ, &LogicMsgHandler::OnMsgSelectPlayerEnterReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_SELECT_ENTER_LOGICSVR_REQ, &LogicMsgHandler::OnMsgSelectEnterLogicSvrReq, this);

	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_LOST_CONNECT_REQ, &LogicMsgHandler::OnMsgLostConnectReq, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_LOGOUT_REQ, &LogicMsgHandler::OnMsgLogoutReq, this);
}

bool LogicMsgHandler::OnMsgDBSvrHeartAck(NetPacket * pack)
{
	return true;
}

//加载角色列表
bool LogicMsgHandler::OnMsgLoadPlayerListReq(NetPacket * pack)
{
	//反序列化 
	LoadPlayerListReq req;
	req.ParsePartialFromArray(pack->m_pDataBuffer->buff, 1024);

	//条件验证
	unsigned long long account = req.account();
	ERROR_RETURN_TRUE(account != 0);
	int logincode = req.logincode();
	ERROR_RETURN_TRUE(logincode != 0);

	//验证账号和rand的映射信息
	std::map<unsigned long long, int>::iterator itor = account_map.find(account);
	ERROR_RETURN_TRUE(itor != account_map.end());
	ERROR_RETURN_TRUE(itor->second != logincode);
	//验证成功，删除
	account_map.erase(itor);

	//构造sql语句
	char szSql[128] = { 0 };
	snprintf(szSql, 128, "select * from player where account_id = %lld");
	DBExeSqlReq dbReq;
	dbReq.set_exectype(SQL_READ);
	dbReq.set_sqlcmd(szSql);

	//推给DBServer获取玩家列表
	int m_DBConnID = CGameService::GetInstancePtr()->GetDBConnID();
	CGameService::GetInstancePtr()->SendData(m_DBConnID, MSG_LOAD_LOGICSVR_LIST_FROM_DBSVR_REQ, dbReq);

	return false;
}

//角色列表结果来自DB
bool LogicMsgHandler::OnMsgLoadPlayerListAck(NetPacket * pack)
{
	return false;
}

//创建角色
bool LogicMsgHandler::OnMsgCreatePlayerReq(NetPacket * pack)
{
	//反序列化 

	//构造sql语句

	//推给DBServer创建玩家

	//返给客户端 玩家创建结果
	return false;
}

//创建角色结果来自DB
bool LogicMsgHandler::OnMsgCreatePlayerAck(NetPacket * pack)
{
	return false;
}

//选择角色进入游戏
bool LogicMsgHandler::OnMsgSelectPlayerEnterReq(NetPacket * pack)
{
	//反序列化 

	//Create Player

	//返给客户端 构造的player对象
	return false;
}

//选择进入的逻辑服来自loginserver（记录即将连接accountid用于验证）
bool LogicMsgHandler::OnMsgSelectEnterLogicSvrReq(NetPacket * pack)
{
	//反序列化 
	SelectEnterLogicSvrReq req;
	req.ParsePartialFromArray(pack->m_pDataBuffer->buff, 1024);

	//条件验证
	unsigned long long account = req.account();
	ERROR_RETURN_TRUE(account != 0);
	int serverid = req.serverid();
	ERROR_RETURN_TRUE(serverid != 0);
	int sockfd = req.sockfd();
	ERROR_RETURN_TRUE(sockfd != 0);

	//创建account和随机值的映射验证
	std::map<unsigned long long, int>::iterator itor = account_map.find(account);
	ERROR_RETURN_TRUE(itor != account_map.end());
	srand((int)time(0));
	int logincode = rand();
	account_map.insert(std::make_pair(account, logincode));

	//回传给LoginServer结果
	SelectEnterLogicSvrAck ack;
	ack.set_account(account);
	ack.set_logincode(logincode);
	ack.set_serveraddr(CConfigFile::GetInstancePtr()->GetStringValue("logic_svr_ip"));
	ack.set_serverid(serverid);
	ack.set_serverport(CConfigFile::GetInstancePtr()->GetIntValue("logic_svr_port"));
	ack.set_sockfd(sockfd);
	CGameService::GetInstancePtr()->SendData(pack->m_dwConnID, MSG_SELECT_ENTER_LOGICSVR_ACK, ack);

	return false;
}

//主动断开连接请求
bool LogicMsgHandler::OnMsgLostConnectReq(NetPacket * pack)
{
	return false;
}

//登出请求
bool LogicMsgHandler::OnMsgLogoutReq(NetPacket * pack)
{
	return false;
}


