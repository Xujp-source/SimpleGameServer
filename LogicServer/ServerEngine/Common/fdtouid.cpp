#include "fdtouid.h"
#include"../CELLLog.hpp"

FdToUid::FdToUid()
{

}

FdToUid::~FdToUid()
{

}

FdToUid* FdToUid::GetInstancePtr()
{
	static FdToUid _Instance;
	
	return &_Instance;
}

int FdToUid::GetFdByUid(unsigned long long uid)
{
	std::map<unsigned long long, int>::iterator itor = m_uidmap.find(uid);
	if(itor != m_uidmap.end())
	{
		return itor->second;
	}

	return -1;
}

bool FdToUid::SetFdToUid(unsigned long long uid, int fd)
{
	std::map<unsigned long long, int>::iterator itor = m_uidmap.find(uid);
	if(itor != m_uidmap.end())
	{
		CELLLog::Instance().Info("玩家uid和fdsock已成映射关系\n");
		return false;
	}

	m_uidmap.insert(std::make_pair(uid, fd));
	return true;
}

bool FdToUid::RemoveFdToUid(unsigned long long uid)
{
	std::map<unsigned long long, int>::iterator itor = m_uidmap.find(uid);
	if(itor == m_uidmap.end())
	{
		CELLLog::Instance().Info("玩家uid和fdsock的映射关系已移除\n");
		return false;
	}

	m_uidmap.erase(itor);
	return true;
}
