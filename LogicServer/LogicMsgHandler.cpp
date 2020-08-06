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

//���ؽ�ɫ�б�
bool LogicMsgHandler::OnMsgLoadPlayerListReq(NetPacket * pack)
{
	//�����л� 
	LoadPlayerListReq req;
	req.ParsePartialFromArray(pack->m_pDataBuffer->buff, 1024);

	//������֤
	unsigned long long account = req.account();
	ERROR_RETURN_TRUE(account != 0);
	int logincode = req.logincode();
	ERROR_RETURN_TRUE(logincode != 0);

	//��֤�˺ź�rand��ӳ����Ϣ
	std::map<unsigned long long, int>::iterator itor = account_map.find(account);
	ERROR_RETURN_TRUE(itor != account_map.end());
	ERROR_RETURN_TRUE(itor->second != logincode);
	//��֤�ɹ���ɾ��
	account_map.erase(itor);

	//����sql���
	char szSql[128] = { 0 };
	snprintf(szSql, 128, "select * from player where account_id = %lld");
	DBExeSqlReq dbReq;
	dbReq.set_exectype(SQL_READ);
	dbReq.set_sqlcmd(szSql);

	//�Ƹ�DBServer��ȡ����б�
	int m_DBConnID = CGameService::GetInstancePtr()->GetDBConnID();
	CGameService::GetInstancePtr()->SendData(m_DBConnID, MSG_LOAD_LOGICSVR_LIST_FROM_DBSVR_REQ, dbReq);

	return false;
}

//��ɫ�б�������DB
bool LogicMsgHandler::OnMsgLoadPlayerListAck(NetPacket * pack)
{
	return false;
}

//������ɫ
bool LogicMsgHandler::OnMsgCreatePlayerReq(NetPacket * pack)
{
	//�����л� 

	//����sql���

	//�Ƹ�DBServer�������

	//�����ͻ��� ��Ҵ������
	return false;
}

//������ɫ�������DB
bool LogicMsgHandler::OnMsgCreatePlayerAck(NetPacket * pack)
{
	return false;
}

//ѡ���ɫ������Ϸ
bool LogicMsgHandler::OnMsgSelectPlayerEnterReq(NetPacket * pack)
{
	//�����л� 

	//Create Player

	//�����ͻ��� �����player����
	return false;
}

//ѡ�������߼�������loginserver����¼��������accountid������֤��
bool LogicMsgHandler::OnMsgSelectEnterLogicSvrReq(NetPacket * pack)
{
	//�����л� 
	SelectEnterLogicSvrReq req;
	req.ParsePartialFromArray(pack->m_pDataBuffer->buff, 1024);

	//������֤
	unsigned long long account = req.account();
	ERROR_RETURN_TRUE(account != 0);
	int serverid = req.serverid();
	ERROR_RETURN_TRUE(serverid != 0);
	int sockfd = req.sockfd();
	ERROR_RETURN_TRUE(sockfd != 0);

	//����account�����ֵ��ӳ����֤
	std::map<unsigned long long, int>::iterator itor = account_map.find(account);
	ERROR_RETURN_TRUE(itor != account_map.end());
	srand((int)time(0));
	int logincode = rand();
	account_map.insert(std::make_pair(account, logincode));

	//�ش���LoginServer���
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

//�����Ͽ���������
bool LogicMsgHandler::OnMsgLostConnectReq(NetPacket * pack)
{
	return false;
}

//�ǳ�����
bool LogicMsgHandler::OnMsgLogoutReq(NetPacket * pack)
{
	return false;
}


