#ifndef __BAG_MODULE_H__
#define __BAG_MODULE_H__
#include "BaseModule.h"

struct BagDataObject;
class CBagModule : public CBaseModule
{
public:
	CBagModule(CPlayerObject* pOwner);

	virtual ~CBagModule();

public:
	//*********************模块通用方法定义*********************
	virtual void RegisterMessageHanler();
	virtual void RegisterEventHanler();
	virtual bool ReadFromDBLoginData();
	virtual bool SaveChangeData();
	//**********************************************************

public:
	//*********************模块自定义方法定义*******************
	bool AddItem(int itemID, unsigned long long itemGuid, int count);
	bool DeleteItem(int itemID, unsigned long long itemGuid);
	bool UpdateItem(unsigned long long itemGuid, int count);
	//**********************************************************

public:
	//*******************消息处理定义**************************
	bool OnMsgBagUnLockReq(NetPacket* pack);  //背包格子解锁请求
	//*********************************************************

public:
	std::map<unsigned long long, BagDataObject*> m_mapBagData;
};

#endif //__STORE_MODULE_H__