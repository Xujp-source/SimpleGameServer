#ifndef __SERVER_DEFINE_H__
#define __SERVER_DEFINE_H__


enum EMouduleType
{
	MT_STORE,
	MT_BAG,
	MT_END
};


enum
{
	SQL_BEGIN,
	//��ȡ
	SQL_READ,
	//ִ��
	SQL_EXECUTE,
	//����
	SQL_TRANSACTION,
	//replace
	SQL_REPLACE,
	SQL_END
};

#endif