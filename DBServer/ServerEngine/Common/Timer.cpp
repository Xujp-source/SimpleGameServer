#include "Timer.h"
#include "../CELLTimestamp.hpp"


CTimerManager::CTimerManager(void)
{

}

CTimerManager:: ~CTimerManager(void)
{
	Clear();
}

bool CTimerManager::DelTimer(UINT32 dwSec, UINT32 dwData)
{
	for (std::list<TimeEvent*>::iterator itor = m_TimerList.begin(); itor != m_TimerList.end();)
	{
		if ((*itor)->m_dwSec == dwSec && (*itor)->m_dwData == dwData)
		{
			delete *itor;
			*itor = nullptr;
			m_TimerList.erase(itor++);
			return true;
		}
	}
	return false;
}

void CTimerManager::UpdateTimer()
{
	for (std::list<TimeEvent*>::iterator itor = m_TimerList.begin(); itor != m_TimerList.end(); itor++)
	{
		if (CELLTime::getNowInMilliSec() >= (*itor)->m_dwFireTime)
		{
			//如果是循环定时器
			if ((*itor)->m_Repeat)
			{
				//执行回调方法
				(*((*itor)->m_pTimerFuncSlot))((*itor)->m_dwFireTime);
				//更新下一次触发时间
				(*itor)->m_dwFireTime = (*itor)->m_dwFireTime + (*itor)->m_dwSec;
			}
			else
			{
				//执行回调方法
				(*((*itor)->m_pTimerFuncSlot))((*itor)->m_dwFireTime);
				//调用完删除定时器
				DelTimer((*itor)->m_dwSec, (*itor)->m_dwData);
			}
		}
	}
}

bool CTimerManager::Clear()
{
	for (std::list<TimeEvent*>::iterator itor = m_TimerList.begin(); itor != m_TimerList.end(); itor++)
	{
		delete *itor;
		*itor = nullptr;
	}
	m_TimerList.clear();
	return true;
}
