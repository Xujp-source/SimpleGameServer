#ifndef __CMODULE_BASE_H__
#define __CMODULE_BASE_H__
#include "../stdafx.h"
#include "../GameService.h"
#include "../Player.h"

class CBaseModule
{
public:
	CBaseModule(CPlayerObject* pOwner);

	virtual ~CBaseModule();

public:
	virtual void RegisterMessageHanler() = 0;
	/*virtual bool ReadFromDBLoginData(DBRoleLoginAck& Ack) = 0;
	virtual bool SaveToClientLoginData(RoleLoginAck& Ack) = 0;*/
	virtual bool SaveChangeData() = 0;

protected:
	CPlayerObject* m_pOwnPlayer;
};


#endif //__CMODULE_BASE_H__
