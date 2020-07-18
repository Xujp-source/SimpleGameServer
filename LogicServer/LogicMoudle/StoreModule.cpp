#include"StoreModule.h"
#include"../ServerData/StoreData.h"
#include "../protoc/Store.pb.h"

CStoreModule::CStoreModule(CPlayerObject* pOwner): CBaseModule(pOwner)
{
	RegisterMessageHanler();
}

CStoreModule::~CStoreModule()
{

}

void CStoreModule::RegisterMessageHanler()
{
	m_pOwnPlayer->m_NetMessagePump.RegisterMessageHandle(MSG_STORE_BUY_REQ, &CStoreModule::OnMsgStoreBuyReq, this);
}

//bool CStoreModule::ReadFromDBLoginData(DBRoleLoginAck& Ack)
//{
//
//}
//
//bool CStoreModule::SaveToClientLoginData(RoleLoginAck& Ack)
//{
//
//}

bool CStoreModule::SaveChangeData()
{
	return true;
}

//购买请求
bool CStoreModule::OnMsgStoreBuyReq(NetPacket* pack)
{

	StoreBuyReq req;
	CGameService::GetInstancePtr()->SendData(m_pOwnPlayer->GetFd(), MSG_STORE_BUY_ACK, req);
	return true;
}