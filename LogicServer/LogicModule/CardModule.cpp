#include "CardModule.h"
#include "../ServerData/CardData.h"
#include "../protoc/DBExcute.pb.h"

CardModule::CardModule(CPlayerObject * pOwner) :CBaseModule(pOwner)
{
}

CardModule::~CardModule()
{
	ClearCard();
}

void CardModule::RegisterMessageHanler()
{
}

void CardModule::RegisterEventHanler()
{
}

bool CardModule::ReadFromDBLoginData()
{
	return false;
}

bool CardModule::SaveChangeData()
{
	return false;
}

bool CardModule::NotifyChange(char* sqlcmd)
{
	DBExeSqlReq dbReq;
	dbReq.set_exectype(SQL_READ);
	dbReq.set_sqlcmd(sqlcmd);

	//推给DBServer操作库
	int m_DBConnID = CGameService::GetInstancePtr()->GetDBConnID();
	CGameService::GetInstancePtr()->SendData(m_DBConnID, MSG_LOAD_LOGICSVR_LIST_FROM_DBSVR_REQ, dbReq);
	return true;
}

bool CardModule::AddCard(int cardID, int count)
{
	for (int i = 0; i <= count; i++)
	{
		CardObject* card = new CardObject();
		card->m_uCardId = cardID;
		card->m_uLevel = 0;
		card->m_uGuid = Uuid::GetInstancePtr()->NewGuid();

		m_mapCardData.insert(std::make_pair(card->m_uGuid, card));
	}
	//执行事务


	//同步给客户端
	DBExeSqlReq req;
	m_pOwnPlayer->SendData(MSG_LOAD_LOGICSVR_LIST_FROM_DBSVR_REQ, req);
	return true;
}

bool CardModule::DeleteCard(unsigned long long cardGuid)
{
	std::map<unsigned long long, CardObject*>::iterator itor = m_mapCardData.find(cardGuid);
	if (itor != m_mapCardData.end())
	{
		delete itor->second;
		itor->second = nullptr;
		m_mapCardData.erase(itor);
	}
	//构造sql语句
	char szSql[128] = { 0 };
	snprintf(szSql, 128, "delete form card where id = %lld", cardGuid);
	NotifyChange(szSql);
	//同步给客户端
	DBExeSqlReq req;
	m_pOwnPlayer->SendData(MSG_LOAD_LOGICSVR_LIST_FROM_DBSVR_REQ, req);

	return true;
}

bool CardModule::ClearCard()
{
	//玩家析构下线 清除内存数据
	std::map<unsigned long long, CardObject*>::iterator itor = m_mapCardData.begin();
	for (; itor != m_mapCardData.end();)
	{
		delete itor->second;
		itor->second = nullptr;
	}
	m_mapCardData.clear();

	return true;
}

