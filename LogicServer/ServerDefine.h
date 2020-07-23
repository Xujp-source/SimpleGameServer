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
	//读取
	SQL_READ,
	//执行
	SQL_EXECUTE,
	//事务
	SQL_TRANSACTION,
	//replace
	SQL_REPLACE,
	SQL_END
};

#endif