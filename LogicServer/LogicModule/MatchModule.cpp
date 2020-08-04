#include"MatchModule.h"

CMatchModule::CMatchModule(CPlayerObject * pOwner):CBaseModule(pOwner)
{	
	RegisterMessageHanler();
	RegisterEventHanler();
}

CMatchModule::~CMatchModule()
{
}

void CMatchModule::RegisterMessageHanler()
{
	m_pOwnPlayer->m_NetMessagePump.RegisterMessageHandle(MSG_BAG_UNLOCK_REQ, &CMatchModule::OnMsgMatchReq, this);
}

void CMatchModule::RegisterEventHanler()
{
	m_pOwnPlayer->m_EventPump.RegisterEventHandle(EVENT_LOGOUT, &CMatchModule::LogoutCallback, this);
}

bool CMatchModule::ReadFromDBLoginData()
{
	return true;
}

bool CMatchModule::SaveChangeData()
{
	return true;
}

//匹配请求
bool CMatchModule::OnMsgMatchReq(NetPacket* pack)
{

	return true;
}

bool CMatchModule::OnMsgMatchAck(NetPacket * pack)
{
	return false;
}

bool CMatchModule::OnMsgCancelMatchReq(NetPacket * pack)
{
	return false;
}

bool CMatchModule::OnMsgCancelMatchAck(NetPacket * pack)
{
	return false;
}

//登出回调
bool CMatchModule::LogoutCallback(const google::protobuf::Message* pdata)
{

	return true;
}