#ifndef _EVENT_HANDLER_MANAGER_H__
#define _EVENT_HANDLER_MANAGER_H__
#include "MsgHandlerManager.hpp"
#include "google/protobuf/message.h"
//事件分发框架

class CEventHandler : public CHandlerManager
{
public:
	CEventHandler(void) {};
	virtual ~CEventHandler(void) {};

public:
	template<typename TClass>
	bool RegisterEventHandle(int nEventID, bool(TClass::*FuncPtr)(const google::protobuf::Message*), TClass* pObj)
	{
		return RegisterMessageHandle(nEventID, FuncPtr, pObj);
	}

	bool NotifyEventHandle(int nEventID, const google::protobuf::Message* pdata)
	{
		return ExecuteMessage(nEventID, pdata);
	}
};


class CEventHandlerManager : public CEventHandler
{
private:
	CEventHandlerManager(void) {};
	virtual ~CEventHandlerManager(void) {};

public:
	static CEventHandlerManager* GetInstancePtr()
	{
		static CEventHandlerManager _Instance;
		return &_Instance;
	}
};

#endif
