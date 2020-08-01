#ifndef __TASK_MODULE_H__
#define __TASK_MODULE_H__
#include "BaseModule.h"

class CTaskModule : public CBaseModule
{
public:
	CTaskModule(CPlayerObject* pOwner);

	virtual ~CTaskModule();

public:
	virtual void RegisterMessageHanler();
	virtual void RegisterEventHanler();
	virtual bool ReadFromDBLoginData();
	virtual bool SaveChangeData();

public:
	//*********************消息处理定义*************************
	//**********************************************************
};

#endif //__STORE_MODULE_H__
