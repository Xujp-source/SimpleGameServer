#include "MailModule.h"

CMailModule::CMailModule(CPlayerObject * pOwner) :CBaseModule(pOwner)
{
}

CMailModule::~CMailModule()
{
}

void CMailModule::RegisterMessageHanler()
{
}

void CMailModule::RegisterEventHanler()
{
}

bool CMailModule::ReadFromDBLoginData()
{
	return false;
}

bool CMailModule::SaveChangeData()
{
	return false;
}

bool CMailModule::SendMail(int descid, int itemid)
{
	return false;
}

bool CMailModule::OnMsgLoadMailReq(NetPacket * pNetPacket)
{
	return false;
}

bool CMailModule::OnMsgReadMailReq(NetPacket * pNetPacket)
{
	return false;
}

bool CMailModule::OnMsgAcquireMailReq(NetPacket * pNetPacket)
{
	return false;
}

bool CMailModule::OnMsgDeleteMailReq(NetPacket * pNetPacket)
{
	return false;
}
