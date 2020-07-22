#include"Player.h"
#include"./LogicModule/BaseModule.h"
#include"./LogicModule/StoreModule.h"
#include"./LogicModule/BagModule.h"

CPlayerObject::CPlayerObject(void)
{
}

CPlayerObject::~CPlayerObject(void)
{
	UnRegisterAllMoudle();
}

bool CPlayerObject::Init(unsigned long long u64ID)
{
	RegisterAllMoudle();
	return true;
}

bool CPlayerObject::RegisterAllMoudle()
{
	m_MoudleList[MT_STORE] = new CStoreModule(this);
	m_MoudleList[MT_BAG]   = new CBagModule(this);
	return true;
}

bool CPlayerObject::UnRegisterAllMoudle()
{
	std::vector<CBaseModule*>::iterator itor = m_MoudleList.begin();
	for (; itor != m_MoudleList.end();)
	{
		delete *itor;
		*itor = nullptr;
		m_MoudleList.erase(itor++);
	}
	return true;
}

void CPlayerObject::SetTemp(std::string key, int value)
{
	std::map<std::string, int>::iterator it = m_TempList.find(key);
	if (it == m_TempList.end())
	{
		m_TempList.insert(std::make_pair(key, value));
	}
}

int CPlayerObject::GetTemp(std::string key)
{
	std::map<std::string, int>::iterator it = m_TempList.find(key);
	if (it != m_TempList.end())
	{
		return it->second;
	}
}

bool CPlayerObject::SaveData()
{
	for (int i = MT_STORE; i < MT_END; i++)
	{
		m_MoudleList[i]->SaveChangeData();
	}
	return true;
}
