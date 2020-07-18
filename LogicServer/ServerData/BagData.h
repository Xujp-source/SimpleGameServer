#ifndef __BAG_DATA_H__
#define __BAG_DATA_H__

struct BagDataObject
{
	BagDataObject()
	{
		m_uGuid		= 0;
		m_UserID	= 0;
		m_ItemGuid	= 0;
		m_ItemID	= 0;
		m_nCount	= 0;
		m_bBind		= 0;
	}

	unsigned long long	m_uGuid;		//格子的guid
	unsigned long long	m_UserID;		//玩家UID
	unsigned long long	m_ItemGuid;		//物品guid
	unsigned int		m_ItemID;		//道具ID
	long long			m_nCount;		//个数
	bool				m_bBind;		//是否是邦定
};

#endif