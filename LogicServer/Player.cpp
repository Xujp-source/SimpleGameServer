#include"Player.h"
#include"./LogicMoudle/BaseModule.h"
#include"./LogicMoudle/StoreModule.h"
#include"./LogicMoudle/BagModule.h"

CPlayerObject::CPlayerObject(void)
{
}

CPlayerObject::~CPlayerObject(void)
{
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
