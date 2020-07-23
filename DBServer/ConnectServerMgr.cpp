#include "ConnectServerMgr.h"
#include "GameService.h"
#include "MsgHandlerManager.hpp"
#include "AgentManager.h"
#include "Agent.h"


ConnectServerMgr::ConnectServerMgr(void)
{
}

ConnectServerMgr::~ConnectServerMgr(void)
{
}

ConnectServerMgr * ConnectServerMgr::GetInstancePtr()
{
	static ConnectServerMgr _Instance;
	return &_Instance;
}

bool ConnectServerMgr::Init()
{
	RegisterMessageHanler();
	return true;
}

void ConnectServerMgr::RegisterMessageHanler()
{
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_BAG_UNLOCK_REQ, &ConnectServerMgr::OnMsgLogicSvrRegister, this);
	CMsgHandlerManager::GetInstancePtr()->RegisterMessageHandle(MSG_HEART_BEAT_REQ, &ConnectServerMgr::OnMsgLogicSvrHeartReq, this);
}

bool ConnectServerMgr::SendData(int ServerID, int MsgID, const google::protobuf::Message & pdata)
{
	std::map<int, int>::iterator it = m_connServerMap.find(ServerID);
	if (it == m_connServerMap.end())
	{
		CELLLog::Info("Other Server Not Register, ServerID : %d, MsgID : %d\n", ServerID, MsgID);
		return false;
	}
	int fd = it->second;
	Agent* agent = AgentManager::GetInstancePtr()->FindAgentByPort(fd);
	//BagUnLockReq ack;
	//agent->SendData(MSG_BAG_UNLOCK_REQ, ack);

	return true;
}

bool ConnectServerMgr::OnMsgLogicSvrRegister(NetPacket* pack)
{
	int serverid;

	m_connServerMap.insert(std::make_pair(serverid, pack->m_dwConnID));
	return true;
}

bool ConnectServerMgr::OnMsgLogicSvrHeartReq(NetPacket * pack)
{
	CELLLog::Info("logic server heart beat!!!!!!!!!!!!!!!!!!\n");
	return false;
}

