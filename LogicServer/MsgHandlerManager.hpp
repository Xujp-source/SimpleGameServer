#ifndef _MSG_HANDLER_MANAGER_H__
#define _MSG_HANDLER_MANAGER_H__
#include<map>
//消息分发框架

class CHandlerBase
{
public:
	virtual ~CHandlerBase() {}

	virtual bool operator()(void* pdata) = 0;

};

template<typename TClass, typename TParam>
class CHandlerSlot : public CHandlerBase
{
	typedef bool(TClass::*FuncType)(TParam*);
public:
	CHandlerSlot(FuncType funcPtr, TClass* pObj) :m_pFuncPtr(funcPtr), m_pThis(pObj)
	{
	}

	virtual ~CHandlerSlot()
	{
	}

	virtual bool operator() (void* pData)
	{
		if (m_pFuncPtr != NULL)
		{
			(m_pThis->*m_pFuncPtr)(static_cast<TParam*>(pData));
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	FuncType m_pFuncPtr;
	TClass*  m_pThis;
};

class CHandlerManager
{
	
public:
	CHandlerManager()
	{

	}

	virtual ~CHandlerManager()
	{
		ClearAll();
	}

	template<typename TClass, typename TParam>
	bool RegisterMessageHandle(int nMsgID, bool(TClass::*FuncPtr)(TParam*), TClass* pObj)
	{
		CHandlerBase* pSlot = new CHandlerSlot<TClass, TParam>(FuncPtr, pObj);
		if (pSlot == NULL)
		{
			return false;
		}

		std::map<int, CHandlerBase*>::iterator it = m_mapHandler.find(nMsgID);
		if (it == m_mapHandler.end())
		{
			m_mapHandler.insert(std::make_pair(nMsgID, pSlot));
			return true;
		}
		return false;
	}

	// 找到并执行对应模块的函数
	template<typename TParam>
	bool ExecuteMessage(int nMsgID, TParam* pData)
	{
		std::map<int, CHandlerBase*>::iterator itor = m_mapHandler.find(nMsgID);
		if(itor != m_mapHandler.end())
		{
			(*(itor->second))((void*)pData);
			return true;
		}
		return false;
	}

	bool ClearAll()
	{
		for (std::map<int, CHandlerBase* > ::iterator itor = m_mapHandler.begin(); itor != m_mapHandler.end(); itor++)
		{
			delete itor->second;
			itor->second = nullptr;
		}
		m_mapHandler.clear();
		return true;
	}

protected:
	std::map<int, CHandlerBase*> m_mapHandler;
};

class CMsgHandlerManager : public CHandlerManager
{
private:
	CMsgHandlerManager(void) {};
	virtual ~CMsgHandlerManager(void) {};

public:
	static CMsgHandlerManager* GetInstancePtr()
	{
		static CMsgHandlerManager _Instance;
		return &_Instance;
	}
};

#endif