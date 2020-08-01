#include"GameService.h"
#include"MsgHandlerManager.hpp"
#include"Agent.h"
#include"AgentManager.h"
#include"ConnectServerMgr.h"
#include"./GameModule/GameSceneManager.h"

CGameService::CGameService()
{
	m_dwLogicConnID = -1;
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
	//初始化配置文件
	if (!CConfigFile::GetInstancePtr()->Load("./ServerEngine/servercfg.ini"))
	{
		CELLLog::Info("加载 servercfg.ini文件失败!\n");
		return false;
	}

	//连接本服的其他服管理类初始化
	ConnectServerMgr::GetInstancePtr()->Init();

	//增加心跳定时器
	CSysTimerManager::GetInstancePtr()->AddTimer(2000, 1, &CGameService::HeartBeat, this, true);

	return true;
}

//定时操作
bool CGameService::OnSecondTimer()
{
	//连接逻辑服
	ConnectToLogicServer();
	return true;
}

//Update
void CGameService::OnUpdate()
{
	//GameLoop
	GameSceneManager::GetInstancePtr()->GameLoop();

	//刷新系统定时器
	CSysTimerManager::GetInstancePtr()->UpdateTimer();
}

//给其他服发送心跳包
bool CGameService::HeartBeat(unsigned int msec)
{
	if (m_dwLogicConnID != -1)
	{
		EmptyReq req;
		SendData(m_dwLogicConnID, MSG_LOGICSVR_HEART_REQ, req);
	}
	return true;
}

//连接数据库操作服
bool CGameService::ConnectToLogicServer()
{
	if (m_dwLogicConnID != -1)
	{
		return true;
	}

	UINT32 nLogicPort = CConfigFile::GetInstancePtr()->GetIntValue("logic_svr_port");
	std::string strLogicIp = CConfigFile::GetInstancePtr()->GetStringValue("logic_svr_ip");
	m_dwLogicConnID = Connect(strLogicIp.c_str(), nLogicPort);
	ERROR_RETURN_FALSE(m_dwLogicConnID != -1);
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

//客户端离开事件
void CGameService::OnNetLeave(CELLClient * pClient)
{
	//调用基类方法
	EasyTcpServer::OnNetLeave(pClient);
	//删除agent对象
	int fd = pClient->sockfd();
	Agent* agent = AgentManager::GetInstancePtr()->FindAgentByPort(fd);
	delete agent;
	agent = nullptr;
	//移除fd和agent的映射关系
	AgentManager::GetInstancePtr()->RemovePortToAgent(fd);

	//当逻辑服异常，心跳定时未收到逻辑服的ack，移除pClient，重置connID
	if (fd == m_dwLogicConnID)
	{
		m_dwLogicConnID = -1;
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
	if (!agent->IsUser())
	{
		// system or other message
		if (!CMsgHandlerManager::GetInstancePtr()->ExecuteMessage(package->cmd, &pack))
		{
			CELLLog::Info("CGameService::OnNetMsg Not Find SystemMessage sockfd:%d, MessageID:%d\n", pClient->sockfd(), package->cmd);
			return;
		}
	}
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
	//protobuf序列化成szBuff
	char szBuff[1024] = { 0 };
	ERROR_RETURN_FALSE(pdata.ByteSizeLong() < 1024);
	pdata.SerializePartialToArray(szBuff, pdata.GetCachedSize());
	//打包给消息传输层用的消息buffer
	netmsg_DataHeader data;
	data.cmd = MsgID;
	memcpy(data.buff, "%s", sizeof(szBuff));
	//推送消息
	pClient->SendData(&data);
	return true;
}

