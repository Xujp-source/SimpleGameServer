﻿#include "../Common/stdafx.h"
#include "../Common/CommonConvert.h"
#include "CppMysql.h"
#include <stdlib.h>
#include <errmsg.h>

CppMySQLQuery::CppMySQLQuery()
{
	m_MysqlRes = NULL;
	_field = NULL;
	_row = NULL;
	_row_count = 0;
	_field_count = 0;
}

CppMySQLQuery::CppMySQLQuery(CppMySQLQuery& rQuery)
{
	*this = rQuery;
}

CppMySQLQuery& CppMySQLQuery::operator=(CppMySQLQuery& rQuery)
{
	if (this == &rQuery)
	{
		return *this;
	}

	m_MysqlRes = rQuery.m_MysqlRes;
	_row = NULL;
	_row_count = 0;
	_field_count = 0;
	_field = NULL;
	if (m_MysqlRes != NULL)
	{
		//定位游标位置到第一个位置
		mysql_data_seek(m_MysqlRes, 0);
		_row = mysql_fetch_row(m_MysqlRes);
		_row_count = (int)mysql_num_rows(m_MysqlRes);
		//得到字段数量
		_field_count = mysql_num_fields(m_MysqlRes);
	}
	rQuery.m_MysqlRes = NULL;
	rQuery._field = NULL;
	rQuery._row = NULL;
	rQuery._row_count = 0;
	rQuery._field_count = 0;
	return *this;
}

CppMySQLQuery::~CppMySQLQuery()
{
	freeRes();
}

void CppMySQLQuery::freeRes()
{
	if (m_MysqlRes != NULL)
	{
		mysql_free_result(m_MysqlRes);
		m_MysqlRes = NULL;
	}
}

int CppMySQLQuery::numRow()
{
	return _row_count;
}

int CppMySQLQuery::numFields()
{
	return _field_count;
}

int CppMySQLQuery::seekRow(int offerset)
{
	if (offerset < 0)
	{
		offerset = 0;
	}

	if (offerset >= _row_count)
	{
		offerset = _row_count - 1;
	}

	mysql_data_seek(m_MysqlRes, offerset);

	_row = mysql_fetch_row(m_MysqlRes);

	return offerset;
}

int CppMySQLQuery::fieldIndex(const char* szField)
{
	if (NULL == m_MysqlRes)
	{
		return -1;
	}

	if (NULL == szField)
	{
		return -1;
	}

	mysql_field_seek(m_MysqlRes, 0);//定位到第0列
	int i = 0;
	while (i < _field_count)
	{
		_field = mysql_fetch_field(m_MysqlRes);
		if (_field != NULL && strcmp(_field->name, szField) == 0)//找到
		{
			return i;
		}

		i++;
	}

	return -1;
}

const char* CppMySQLQuery::fieldName(int nCol)
{
	if (m_MysqlRes == NULL)
	{
		return NULL;
	}

	mysql_field_seek(m_MysqlRes, nCol);

	_field = mysql_fetch_field(m_MysqlRes);
	if (_field != NULL)
	{
		return _field->name;
	}

	return  NULL;
}

int CppMySQLQuery::getIntField(int nField, int nNullValue/*=0*/)
{
	if (NULL == m_MysqlRes)
	{
		return nNullValue;
	}

	if (nField + 1 > (int)_field_count)
	{
		return nNullValue;
	}

	if (NULL == _row)
	{
		return nNullValue;
	}

	return atoi(_row[nField]);
}

int CppMySQLQuery::getIntField(const char* szField, int nNullValue/*=0*/)
{
	if (NULL == m_MysqlRes || NULL == szField)
	{
		return nNullValue;
	}

	if (NULL == _row)
	{
		return nNullValue;
	}

	const char* filed = getStringField(szField);
	if (NULL == filed)
	{
		return nNullValue;
	}

	return atoi(filed);
}

const char* CppMySQLQuery::getStringField(int nField, const char* szNullValue/*=""*/)
{
	if (NULL == m_MysqlRes)
	{
		return szNullValue;
	}

	if (nField + 1 > (int)_field_count)
	{
		return szNullValue;
	}

	if (NULL == _row)
	{
		return szNullValue;
	}

	if (_row[nField] == NULL)
	{
		return szNullValue;
	}

	return _row[nField];
}

const char* CppMySQLQuery::getStringField(const char* szField, const char* szNullValue/*=""*/)
{
	if (NULL == m_MysqlRes)
	{
		return szNullValue;
	}

	int nField = fieldIndex(szField);
	if (nField == -1)
	{
		return szNullValue;
	}

	return getStringField(nField, szNullValue);
}

INT64 CppMySQLQuery::getInt64Field(int nField, INT64 nNullValue /*= 0*/)
{
	if (NULL == m_MysqlRes)
	{
		return nNullValue;
	}

	if (nField + 1 > (int)_field_count)
	{
		return nNullValue;
	}

	if (NULL == _row)
	{
		return nNullValue;
	}

	return CommonConvert::StringToInt64(_row[nField]);
}

INT64 CppMySQLQuery::getInt64Field(const char* szField, INT64 nNullValue /*= 0*/)
{
	if (NULL == m_MysqlRes || NULL == szField)
	{
		return nNullValue;
	}

	if (NULL == _row)
	{
		return nNullValue;
	}

	const char* filed = getStringField(szField);
	if (NULL == filed)
	{
		return nNullValue;
	}

	return CommonConvert::StringToInt64(filed);
}

double CppMySQLQuery::getFloatField(int nField, double fNullValue/*=0.0*/)
{
	const char* field = getStringField(nField);
	if (NULL == field)
	{
		return fNullValue;
	}

	return atof(field);
}

double CppMySQLQuery::getFloatField(const char* szField, double fNullValue/*=0.0*/)
{
	const char* field = getStringField(szField);
	if (NULL == field)
	{
		return fNullValue;
	}

	return atof(field);
}

void CppMySQLQuery::nextRow()
{
	if (NULL == m_MysqlRes)
	{
		return;
	}

	_row = mysql_fetch_row(m_MysqlRes);
}

bool CppMySQLQuery::hasResult()
{
	return m_MysqlRes != NULL;
}

const unsigned char* CppMySQLQuery::getBlobField(int nField, int& nLen)
{
	const unsigned char* pData = (const unsigned char*)getStringField(nField);
	if (NULL == pData)
	{
		return NULL;
	}

	unsigned   long*   FieldLength = mysql_fetch_lengths(m_MysqlRes);
	nLen = (int)FieldLength[nField];

	return pData;
}

const unsigned char* CppMySQLQuery::getBlobField(const char* szField, int& nLen)
{
	if (NULL == m_MysqlRes)
	{
		return NULL;
	}

	int nField = fieldIndex(szField);
	if (nField == -1)
	{
		return NULL;
	}

	const unsigned char* pData = (const unsigned char*)getStringField(nField);
	if (NULL == pData)
	{
		return NULL;
	}

	unsigned   long*   FieldLength = mysql_fetch_lengths(m_MysqlRes);
	nLen = (int)FieldLength[nField];

	return pData;
}

bool CppMySQLQuery::fieldIsNull(int nField)
{
	if (NULL == m_MysqlRes)
	{
		return NULL;
	}

	const unsigned char* pData = (const unsigned char*)getStringField(nField);
	if (NULL == pData)
	{
		return TRUE;
	}

	return FALSE;
}

bool CppMySQLQuery::fieldIsNull(const char* szField)
{
	if (NULL == m_MysqlRes)
	{
		return NULL;
	}

	const unsigned char* pData = (const unsigned char*)getStringField(szField);
	if (NULL == pData)
	{
		return TRUE;
	}

	return FALSE;
}

bool CppMySQLQuery::eof()
{
	return (_row == NULL);
}

CppMySQL3DB::CppMySQL3DB()
{
	m_pMySqlDB = NULL;
}

CppMySQL3DB::~CppMySQL3DB()
{
	if (m_pMySqlDB != NULL)
	{
		close();
	}
}

bool CppMySQL3DB::open(const char* host, const char* user, const char* passwd, const char* db,
	unsigned int port, const char* charSetName, unsigned long client_flag /*= 0*/)
{
	bool ret = false;
	m_pMySqlDB = mysql_init(NULL);
	if (NULL == m_pMySqlDB)
	{
		goto EXT;
	}

	if (0 != mysql_options(m_pMySqlDB, MYSQL_SET_CHARSET_NAME, charSetName))
	{
		m_nErrno = mysql_errno(m_pMySqlDB);
		m_strError = mysql_error(m_pMySqlDB);
		goto EXT;
	}

	//如果连接失败，返回NULL。对于成功的连接，返回值与第1个参数的值相同。
	if (NULL == mysql_real_connect(m_pMySqlDB, host, user, passwd, db, port, NULL, client_flag))
	{
		m_nErrno = mysql_errno(m_pMySqlDB);
		m_strError = mysql_error(m_pMySqlDB);
		goto EXT;
	}

	m_strHost = host;
	m_strUser = user;
	m_strPwd = passwd;
	m_strDB = db;
	m_nPort = port;
	m_strCharSet = charSetName;

	//选择制定的数据库失败
	//0表示成功，非0值表示出现错误。
	if (mysql_select_db(m_pMySqlDB, db) != 0)
	{
		m_nErrno = mysql_errno(m_pMySqlDB);
		m_strError = mysql_error(m_pMySqlDB);
		mysql_close(m_pMySqlDB);
		m_pMySqlDB = NULL;
		goto EXT;
	}
	ret = true;
EXT:
	//初始化mysql结构失败
	if (ret == false && m_pMySqlDB != NULL)
	{
		mysql_close(m_pMySqlDB);
		m_pMySqlDB = NULL;
	}
	return ret;
}

bool CppMySQL3DB::setOpenParam(const char* host, const char* user, const char* passwd, const char* db, unsigned int port, const char* charSetName /*= "utf8"*/, unsigned long client_flag /*= 0*/)
{
	m_strHost = host;
	m_strUser = user;
	m_strPwd = passwd;
	m_strDB = db;
	m_nPort = port;
	m_strCharSet = charSetName;
	return true;
}

void CppMySQL3DB::close()
{
	if (m_pMySqlDB != NULL)
	{
		mysql_close(m_pMySqlDB);
		m_pMySqlDB = NULL;
	}
}

MYSQL* CppMySQL3DB::getMysql()
{
	return m_pMySqlDB;
}

/* 处理返回多行的查询，返回影响的行数 */
CppMySQLQuery& CppMySQL3DB::querySQL(const char* sql)
{
	int nRet = mysql_real_query(m_pMySqlDB, sql, (unsigned long)strlen(sql));
	if (nRet != 0)
	{
		m_nErrno = mysql_errno(m_pMySqlDB);
		m_strError = mysql_error(m_pMySqlDB);
		if (m_nErrno == CR_SERVER_GONE_ERROR || m_nErrno == CR_SERVER_LOST)
		{
			reconnect();
			nRet = mysql_real_query(m_pMySqlDB, sql, (unsigned long)strlen(sql));
		}
	}

	if (0 == nRet)
	{
		m_dbQuery.m_MysqlRes = mysql_store_result(m_pMySqlDB);
	}
	return m_dbQuery;
}

/* 执行非返回结果查询 */
int CppMySQL3DB::execSQL(const char* sql)
{
	int nRet = mysql_real_query(m_pMySqlDB, sql, (unsigned long)strlen(sql));
	if (nRet == 0)
	{
		//得到受影响的行数
		return (int)mysql_affected_rows(m_pMySqlDB);
	}

	m_nErrno = mysql_errno(m_pMySqlDB);
	m_strError = mysql_error(m_pMySqlDB);
	if (m_nErrno == CR_SERVER_GONE_ERROR || m_nErrno == CR_SERVER_LOST)
	{
		reconnect();
		nRet = mysql_real_query(m_pMySqlDB, sql, (unsigned long)strlen(sql));
		if (0 == nRet)
		{
			//得到受影响的行数
			return (int)mysql_affected_rows(m_pMySqlDB);
		}
	}


	return -1;
}

/* 测试mysql服务器是否存活 */
bool CppMySQL3DB::ping()
{
	if (mysql_ping(m_pMySqlDB) == 0)
	{
		return true;
	}

	return false;
}

/* 关闭mysql 服务器 */
bool CppMySQL3DB::shutDown()
{
	if (mysql_shutdown(m_pMySqlDB, SHUTDOWN_DEFAULT) == 0)
	{
		return true;
	}

	return false;
}

/* 主要功能:重新启动mysql 服务器 */
bool CppMySQL3DB::reboot()
{
	if (!mysql_reload(m_pMySqlDB))
	{
		return true;
	}

	return false;
}

bool CppMySQL3DB::reconnect()
{
	if (m_pMySqlDB != NULL && ping())
	{
		return true;
	}

	close();
	bool ret = false;
	m_pMySqlDB = mysql_init(NULL);
	if (NULL == m_pMySqlDB)
	{
		goto EXT;
	}

	if (0 != mysql_options(m_pMySqlDB, MYSQL_SET_CHARSET_NAME, m_strCharSet.c_str()))
	{
		goto EXT;
	}

	//如果连接失败，返回NULL。对于成功的连接，返回值与第1个参数的值相同。
	if (NULL == mysql_real_connect(m_pMySqlDB, m_strHost.c_str(), m_strUser.c_str(), m_strPwd.c_str(), m_strDB.c_str(), m_nPort, NULL, 0))
	{
		goto EXT;
	}
	//选择制定的数据库失败
	//0表示成功，非0值表示出现错误。
	if (mysql_select_db(m_pMySqlDB, m_strDB.c_str()) != 0)
	{
		mysql_close(m_pMySqlDB);
		m_pMySqlDB = NULL;
		goto EXT;
	}
	ret = true;
EXT:
	//初始化mysql结构失败
	if (ret == false && m_pMySqlDB != NULL)
	{
		mysql_close(m_pMySqlDB);
		m_pMySqlDB = NULL;
	}
	return ret;
}

/*
* 说明:事务支持InnoDB or BDB表类型
*/
/* 主要功能:开始事务 */
bool CppMySQL3DB::startTransaction()
{
	if (!mysql_real_query(m_pMySqlDB, "START TRANSACTION", (unsigned long)strlen("START TRANSACTION")))
	{
		return true;
	}

	m_nErrno = mysql_errno(m_pMySqlDB);
	m_strError = mysql_error(m_pMySqlDB);

	return false;
}

/* 主要功能:提交事务 */
bool CppMySQL3DB::commit()
{
	if (!mysql_real_query(m_pMySqlDB, "COMMIT", (unsigned long)strlen("COMMIT")))
	{
		return true;
	}

	m_nErrno = mysql_errno(m_pMySqlDB);
	m_strError = mysql_error(m_pMySqlDB);

	return false;
}

/* 主要功能:回滚事务 */
bool CppMySQL3DB::rollback()
{
	if (!mysql_real_query(m_pMySqlDB, "ROLLBACK", (unsigned long)strlen("ROLLBACK")))
	{
		return true;
	}

	return false;
}

/* 得到客户信息 */
const char* CppMySQL3DB::getClientInfo()
{
	return mysql_get_client_info();
}

/* 主要功能:得到客户版本信息 */
const unsigned long  CppMySQL3DB::getClientVersion()
{
	return mysql_get_client_version();
}

/* 主要功能:得到主机信息 */
const char* CppMySQL3DB::getHostInfo()
{
	return mysql_get_host_info(m_pMySqlDB);
}

/* 主要功能:得到服务器信息 */
const char* CppMySQL3DB::GetServerInfo()
{
	return mysql_get_server_info(m_pMySqlDB);
}

const char* CppMySQL3DB::GetErrorMsg()
{
	return m_strError.c_str();
}

/*主要功能:得到服务器版本信息*/
const unsigned long  CppMySQL3DB::GetDBVersion()
{
	return mysql_get_server_version(m_pMySqlDB);
}

/*主要功能:得到 当前连接的默认字符集*/
const char*   CppMySQL3DB::getCharacterSetName()
{
	return mysql_character_set_name(m_pMySqlDB);
}

/* 建立新数据库 */
int CppMySQL3DB::createDB(const char* name)
{
	char temp[1024];
	snprintf(temp, 1024, "CREATE DATABASE %s", name);
	if (!mysql_real_query(m_pMySqlDB, temp, (unsigned long)strlen(temp)))
	{
		return 0;
	}

	return -1;
}

/* 删除制定的数据库*/
int CppMySQL3DB::dropDB(const char*  name)
{
	char temp[1024];

	snprintf(temp, 1024, "DROP DATABASE %s", name);
	if (!mysql_real_query(m_pMySqlDB, temp, (unsigned long)strlen(temp)))
	{
		return 0;
	}

	return -1;
}

bool CppMySQL3DB::changeCurDB(const char* name)
{
	if (m_pMySqlDB == NULL)
	{
		return false;
	}

	if (0 == mysql_select_db(m_pMySqlDB, name))
	{
		return true;
	}

	return false;
}

INT64 CppMySQL3DB::getAutoIncrementID(const char* szTableName, const char* szDBName)
{
	if ((szTableName == NULL) || (szDBName == NULL))
	{
		return 0;
	}

	char strSql[1024];
	snprintf(strSql, 1024, "SELECT auto_increment FROM information_schema.tables where table_schema=\"%s\" and table_name=\"%s\"", szDBName, szTableName);

	CppMySQLQuery tQuery;

	int nRet = mysql_real_query(m_pMySqlDB, strSql, (unsigned long)strlen(strSql));
	if (nRet != 0)
	{
		int nError = mysql_errno(m_pMySqlDB);
		if (nError == CR_SERVER_GONE_ERROR || nError == CR_SERVER_LOST)
		{
			reconnect();
			nRet = mysql_real_query(m_pMySqlDB, strSql, (unsigned long)strlen(strSql));
		}
	}

	if (0 == nRet)
	{
		tQuery.m_MysqlRes = mysql_store_result(m_pMySqlDB);
	}

	INT64 tId = tQuery.getInt64Field(0);
	return tId;
}

bool CppMySQL3DB::setAutoIncrementID(INT64 nId, const char* szTableName, const char* szDBName)
{
	if ((szTableName == NULL) || (szDBName == NULL))
	{
		return 0;
	}

	char strSql[1024];
	snprintf(strSql, 1024, "alter table %s.%s AUTO_INCREMENT=%lld;", szDBName, szTableName, nId);

	if (!mysql_real_query(m_pMySqlDB, strSql, (unsigned long)strlen(strSql)))
	{
		return true;
	}

	return false;
}

//int CppMySQL3DB::execSQLWithReconnect(const char* sql)
//{
//	int nRet = execSQL(sql);
//	if (nRet >= 0)
//	{
//		return nRet;
//	}
//
//	if (ping())
//	{
//		return execSQL(sql);
//	}
//
//	static int nCount = 0;
//
//	while (nCount < 3)
//	{
//		reconnect();
//
//		if (ping())
//		{
//			return execSQL(sql);
//		}
//
//		nCount++;
//
//		CommonFunc::Sleep(1000);
//	}
//
//	return -1;
//}
