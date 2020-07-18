#ifndef _TIMER_H__
#define _TIMER_H__
#include"stdafx.h"

//定时器管理模块
class CTimerBase
{
public:
	CTimerBase(){}
	virtual ~CTimerBase() {}

	virtual bool operator()(UINT32 pData) = 0;

};

template<typename TClass>
class CTimerSlot : public CTimerBase
{
	typedef bool(TClass::*FuncType)(UINT32);
public:
	CTimerSlot(FuncType funcPtr, TClass* pObj) :m_pFuncPtr(funcPtr), m_pThis(pObj)
	{
	}

	virtual ~CTimerSlot()
	{
	}

	virtual bool operator()(UINT32 pData)
	{
		if (m_pFuncPtr != NULL)
		{
			(m_pThis->*m_pFuncPtr)(pData);
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

struct TimeEvent
{
public:
	TimeEvent()
	{
		m_dwFireTime	 = 0;
		m_dwSec			 = 0;
		m_dwData		 = 0;
		m_Repeat		 = false;
		m_pTimerFuncSlot = nullptr;
	}

	~TimeEvent()
	{
		Reset();
	}

	void Reset()
	{
		m_dwFireTime = 0;
		m_dwSec      = 0;
		m_dwData     = 0;
		m_Repeat     = false;
		if (m_pTimerFuncSlot != nullptr)
		{
			delete m_pTimerFuncSlot;
			m_pTimerFuncSlot = nullptr;
		}
	}

	UINT64 m_dwFireTime;  //触发时间
	UINT32 m_dwSec;
	UINT32 m_dwData;
	bool   m_Repeat;
	CTimerBase* m_pTimerFuncSlot;
};

class CTimerManager
{
public:
	CTimerManager(void);
	virtual ~CTimerManager(void);

	template<typename TClass>
	bool AddTimer(UINT32 dwSec, UINT32 dwData, bool(TClass::* FuncPtr)(UINT32), TClass* pObj, bool isRepeat)
	{
		TimeEvent* event = new TimeEvent;
		event->m_dwFireTime = CELLTime::getNowInMilliSec() + dwSec;
		event->m_dwSec = dwSec;
		event->m_dwData = dwData;
		event->m_Repeat = isRepeat;
		event->m_pTimerFuncSlot = new CTimerSlot<TClass>(FuncPtr, pObj);
		m_TimerList.push_back(event);
		return false;
	}

	bool DelTimer(UINT32 dwSec, UINT32 dwData);

	void UpdateTimer();

	bool Clear();

private:
	std::list<TimeEvent*> m_TimerList;
};

class CSysTimerManager : public CTimerManager
{
private:
	CSysTimerManager(void) {};
	virtual ~CSysTimerManager(void) {};

public:
	static CSysTimerManager* GetInstancePtr()
	{
		static CSysTimerManager _Instance;
		return &_Instance;
	}
};

#endif

