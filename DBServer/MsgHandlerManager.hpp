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

		std::vector<CHandlerBase*>* pMsgVector = NULL;
		std::map<int, std::vector<CHandlerBase* >* >::iterator it = m_mapHandler.find(nMsgID);
		if (it == m_mapHandler.end())
		{
			pMsgVector = new std::vector<CHandlerBase*>;
			pMsgVector->push_back(pSlot);
			m_mapHandler.insert(std::make_pair(nMsgID, pMsgVector));
		}
		else
		{
			pMsgVector = it->second;
			pMsgVector->push_back(pSlot);
		}

		return true;
	}

	// 找到并执行对应模块的函数
	template<typename TParam>
	bool ExecuteMessage(int nMsgID, TParam* pData)
	{
		std::map<int, std::vector<CHandlerBase* >* >::iterator itor = m_mapHandler.find(nMsgID);
		if (itor == m_mapHandler.end())
		{
			return false;
		}

		std::vector<CHandlerBase* >* vtHandler = itor->second;
		for (std::vector<CHandlerBase* >::iterator itorHandler = vtHandler->begin(); itorHandler != vtHandler->end(); itorHandler++)
		{
			(**itorHandler)((void*)pData);
		}
		return true;
	}

	bool ClearAll()
	{
		for (std::map<int, std::vector<CHandlerBase*>*>::iterator itor = m_mapHandler.begin(); itor != m_mapHandler.end(); itor++)
		{
			std::vector<CHandlerBase* >* pVtHandler = itor->second;
			for (std::vector<CHandlerBase* >::iterator itor2 = pVtHandler->begin(); itor2 != pVtHandler->end(); itor2++)
			{
				delete *itor2;
			}

			pVtHandler->clear();
			delete pVtHandler;
		}

		m_mapHandler.clear();

		return true;
	}

protected:
	std::map<int, std::vector<CHandlerBase* >* > m_mapHandler;
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