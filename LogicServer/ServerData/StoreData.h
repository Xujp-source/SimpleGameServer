#ifndef __STORE_DATA_H__
#define __STORE_DATA_H__

struct StoreDataObject
{
	StoreDataObject()
	{
		m_UserID = 0;
	}

	unsigned long long	m_UserID;		//玩家uID

};

#endif