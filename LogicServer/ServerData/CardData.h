#ifndef __CARD_DATA_H__
#define __CARD_DATA_H__

struct CardObject
{
	CardObject()
	{
		m_uGuid		= 0;
		m_uCardId	= 0;
		m_uLevel    = 0;
	}

	unsigned long long m_uGuid;     //卡牌的guid（存库字段）
	unsigned long long m_uCardId;   //卡牌ID（存库字段）
	int m_uLevel;                   //等级（存库字段）
};

#endif