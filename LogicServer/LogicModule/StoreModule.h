#ifndef __STORE_MODULE_H__
#define __STORE_MODULE_H__
#include "BaseModule.h"

struct StoreDataObject;
class CStoreModule  : public CBaseModule
{
public:
	CStoreModule(CPlayerObject* pOwner);

	virtual ~CStoreModule();

public:
	virtual void RegisterMessageHanler();
	virtual void RegisterEventHanler();
	virtual bool ReadFromDBLoginData();
	virtual bool SaveChangeData();

public:
	//*********************消息处理定义*************************
	bool OnMsgStoreBuyReq(NetPacket* pack);  //购买请求
	//**********************************************************
};

#endif //__STORE_MODULE_H__
