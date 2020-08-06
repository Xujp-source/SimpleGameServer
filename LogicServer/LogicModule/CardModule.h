#ifndef __MAIL_MODULE_H__
#define __MAIL_MODULE_H__
#include "BaseModule.h"

struct CardObject;
class CardModule : public CBaseModule
{
public:
	CardModule(CPlayerObject* pOwner);

	virtual ~CardModule();

public:
	//*********************ģ��ͨ�÷������忪ʼ*************************
	virtual void RegisterMessageHanler();
	virtual void RegisterEventHanler();
	virtual bool ReadFromDBLoginData();
	virtual bool SaveChangeData();
	//******************************************************************

public:
	//*********************ģ���Զ��巽������*******************
	bool NotifyChange(char* sqlcmd);
	bool AddCard(int cardID, int count = 1);
	bool DeleteCard(unsigned long long cardGuid);
	bool ClearCard();
	//**********************************************************

public:
	std::map<unsigned long long, CardObject*> m_mapCardData;

};

#endif


