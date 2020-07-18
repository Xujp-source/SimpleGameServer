#include"BagModule.h"
#include"../ServerData/BagData.h"
#include "../protoc/Bag.pb.h"

CBagModule::CBagModule(CPlayerObject * pOwner):CBaseModule(pOwner)
{	
	RegisterMessageHanler();
}

CBagModule::~CBagModule()
{
}

void CBagModule::RegisterMessageHanler()
{
	m_pOwnPlayer->m_NetMessagePump.RegisterMessageHandle(MSG_BAG_UNLOCK_REQ, &CBagModule::OnMsgBagUnLockReq, this);
}

//BOOL CBagModule::ReadFromDBLoginData(DBRoleLoginAck& Ack)
//{
//
//}
//
//BOOL CBagModule::SaveToClientLoginData(RoleLoginAck& Ack)
//{
//
//}

bool CBagModule::SaveChangeData()
{
	return true;
}

bool CBagModule::AddItem(int itemID, unsigned long long itemGuid, int count)
{
	return true;
}

bool CBagModule::DeleteItem(int itemID, unsigned long long itemGuid)
{
	return true;
}

bool CBagModule::UpdateItem(unsigned long long itemGuid, int count)
{
	return true;
}

//背包格子解锁请求
bool CBagModule::OnMsgBagUnLockReq(NetPacket* pack)
{

	//netmsg_DataHeader header;
	//header.cmd = 
	BagUnLockReq ack;
	m_pOwnPlayer->SendData(MSG_BAG_UNLOCK_ACK, ack);

	CGameService::GetInstancePtr()->SendData(pack->m_dwConnID, MSG_BAG_UNLOCK_ACK, ack);
	return true;
}