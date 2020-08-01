#include"GameService.h"
#include"MsgHandlerManager.hpp"
#include"EventHandlerManager.hpp"
#include"Player.h"
#include"PlayerManager.h"
#include"AgentManager.h"
#include"ConnectServerMgr.h"
#include"LogicMsgHandler.h"
#include"./protoc/DBExcute.pb.h"

CGameService::CGameService()
{
	m_dwDBConnID = -1;
}

CGameService::~CGameService()
{
}

CGameService* CGameService::GetInstancePtr()
{
	static CGameService _GameService;
	return &_GameService;
}

//服务初始化
bool CGameService::Init()
{
	if(!CConfigFile::GetInstancePtr()->Load("./ServerEngine/servercfg.ini"))
	{
		CELLLog::Info("加载 servercfg.ini文件失败!\n");
		return false;
	}

	//连接本服的其他服管理类初始化
	ConnectServerMgr::GetInstancePtr()->Init();

	//杂项消息处理类初始化
	LogicMsgHandler::GetInstancePtr()->Init();

	//增加心跳定时器
	CSysTimerManager::GetInstancePtr()->AddTimer(3000, 1, &CGameService::HeartBeat, this, true);

	//test sql
	CSysTimerManager::GetInstancePtr()->AddTimer(8000, 1, &CGameService::TestSql, this, true);

	return true;
}

//定时操作
bool CGameService::OnSecondTimer()
{
	//连接数据库操作服
	ConnectToDBServer();

	//玩家每秒定时操作
	CPlayerManager::GetInstancePtr()->OnSecondTimer();

	return true;
}

//Update
void CGameService::OnUpdate()
{
	//刷新系统定时器
	CSysTimerManager::GetInstancePtr()->UpdateTimer();
	//刷新玩家定时器
	CPlayerManager::GetInstancePtr()->OnUpdate();
}

//给其他服发送心跳包
bool CGameService::HeartBeat(unsigned int msec)
{
	if (m_dwDBConnID != -1)
	{
		EmptyReq req;
		SendData(m_dwDBConnID, MSG_DBSVR_HEART_REQ, req);
	}
	return true;
}

//test
bool CGameService::TestSql(unsigned int msec)
{
	if (m_dwDBConnID != -1)
	{
		DBExeSqlReq req;
		req.set_exectype(SQL_READ);
		req.set_sqlcmd("select * from copy");
		SendData(m_dwDBConnID, MSG_DB_EXE_SQL_REQ, req);
	}
	return true;
}

//连接数据库操作服
bool CGameService::ConnectToDBServer()
{
	if (m_dwDBConnID != -1)
	{
		return true;
	}

	UINT32 nDBPort = CConfigFile::GetInstancePtr()->GetIntValue("db_svr_port");
	std::string strDBIp = CConfigFile::GetInstancePtr()->GetStringValue("db_svr_ip");
	m_dwDBConnID = Connect(strDBIp.c_str(), nDBPort);
	ERROR_RETURN_FALSE(m_dwDBConnID != -1);
	return true;
}

//客户端加入事件
void CGameService::OnNetJoin(CELLClient * pClient)
{
	//调用基类方法
	EasyTcpServer::OnNetJoin(pClient);
	//新建agent对象
	int fd = pClient->sockfd();
	Agent* agent = new Agent();
	agent->SetFd(fd);
	//设置fd和agent的映射关系
	AgentManager::GetInstancePtr()->SetPortToAgent(fd, agent);
}

//客户端异常离开事件
void CGameService::OnNetLeave(CELLClient * pClient)
{
	//调用基类方法
	EasyTcpServer::OnNetLeave(pClient);
	//获取agent对象
	int fd = pClient->sockfd();
	Agent* agent = AgentManager::GetInstancePtr()->FindAgentByPort(fd);
	//抛出客户端离开事件
	//EmptyReq req;
	//NotifyEvent(agent, EVENT_LOGOUT, req);
	//删除agent对象
	delete agent;
	agent = nullptr;
	//移除fd和agent的映射关系
	AgentManager::GetInstancePtr()->RemovePortToAgent(fd);

	//当数据库服异常，未收到数据库服的心跳定时ack，移除pClient，重置connID
	if (fd == m_dwDBConnID)
	{
		m_dwDBConnID = -1;
	}
}

//处理网络消息
void CGameService::OnNetMsg(CELLServer* pServer, CELLClient* pClient, netmsg_DataHeader* package)
{
	//调用基类方法
	EasyTcpServer::OnNetMsg(pServer, pClient, package);
	//通过fd找到agent
	int fd = pClient->sockfd();
	Agent* agent = AgentManager::GetInstancePtr()->FindAgentByPort(fd);
	if (agent == nullptr)
	{
		CELLLog::Info("CGameService::OnNetMsg Error Invalid sockfd:%d, MessageID:%d\n", pClient->sockfd(), package->cmd);
		return;
	}
	//打包成业务层用的消息buffer
	NetPacket pack(fd, package);
	// system or other message
	if (CMsgHandlerManager::GetInstancePtr()->ExecuteMessage(package->cmd, &pack))
	{
		return;
	}
	// agent message
	if (agent->m_NetMessagePump.ExecuteMessage(package->cmd, &pack))
	{
		return;
	}
	CELLLog::Info("ERROR:CGameService::OnNetMsg Not Find Message sockfd:%d, MessageID:%d\n", pClient->sockfd(), package->cmd);
}

//推送网络消息
bool CGameService::SendData(int fd, int MsgID, const google::protobuf::Message& pdata)
{
	//通过fd找到client
	CELLClient* pClient = GetClientByFD(fd);
	if(pClient == nullptr)
	{
		CELLLog::Info("Error: pClient is nullptr!!!!!!\n");
		return false;
	}
	//google::protobuf::Message Serializer
	char szBuff[1023] = { 0 };
	ERROR_RETURN_FALSE(pdata.ByteSizeLong() < 1023);
	pdata.SerializePartialToArray(szBuff, pdata.GetCachedSize());
	//打包给消息传输层用的消息buffer
	netmsg_DataHeader data;
	data.cmd = MsgID;
	memcpy(data.buff, szBuff, strlen(szBuff)+1);
	//推送消息
	pClient->SendData(&data);
	return true;
}

//推送事件
bool CGameService::NotifyEvent(Agent* agent, int EventID, const google::protobuf::Message & pdata)
{
	if (!agent->m_EventPump.NotifyEventHandle(EventID, &pdata))
	{
		CELLLog::Info("ERROR:CGameService::OnEventMsg Not Find EventMessage EventID:%d\n", EventID);
		return false;
	}
	return true;
}

