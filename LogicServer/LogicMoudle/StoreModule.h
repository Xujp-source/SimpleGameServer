#ifndef __STORE_MODULE_H__
#define __STORE_MODULE_H__
#include "BaseModule.h"

struct StoreDataObject;
class CStoreModule  : public CBaseModule
{
public:
	CStoreModule(CPlayerObject* pOwner);

	~CStoreModule();

public:

	virtual void RegisterMessageHanler();

	//virtual BOOL ReadFromDBLoginData(DBRoleLoginAck& Ack);

	//virtual BOOL SaveToClientLoginData(RoleLoginAck& Ack);

	virtual bool SaveChangeData();

public:
	//*********************消息处理定义*************************
	bool OnMsgStoreBuyReq(NetPacket* pack);  //购买请求
	//**********************************************************

public:


};

#endif //__STORE_MODULE_H__
