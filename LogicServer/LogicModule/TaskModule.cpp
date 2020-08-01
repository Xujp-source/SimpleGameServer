#include "TaskModule.h"

CTaskModule::CTaskModule(CPlayerObject* pOwner) : CBaseModule(pOwner)
{
	RegisterMessageHanler();
}


CTaskModule::~CTaskModule()
{
}

void CTaskModule::RegisterMessageHanler()
{
}

void CTaskModule::RegisterEventHanler()
{
}

bool CTaskModule::ReadFromDBLoginData()
{
	return false;
}

bool CTaskModule::SaveChangeData()
{
	return false;
}
