#ifndef _MessageHeader_hpp_
#define _MessageHeader_hpp_
#include "./Common/stdafx.h"
enum CMD
{
	CMD_LOGIN,
	CMD_LOGIN_RESULT,
	CMD_LOGOUT,
	CMD_LOGOUT_RESULT,
	CMD_NEW_USER_JOIN,
	CMD_C2S_HEART,
	CMD_S2C_HEART,
	CMD_ERROR
};

struct netmsg_DataHeader
{
	netmsg_DataHeader()
	{
		dataLength = sizeof(netmsg_DataHeader);
		cmd = CMD_ERROR;
		memset(buff, 0, sizeof(buff));
	}
	unsigned short dataLength;
	unsigned short cmd;
	char buff[1024];
};

struct NetPacket
{
	NetPacket(UINT32 dwConnID = 0, netmsg_DataHeader* pBuffer = NULL)
	{
		m_dwConnID = dwConnID;
		m_pDataBuffer = pBuffer;
	}

	UINT32       m_dwConnID;
	netmsg_DataHeader* m_pDataBuffer;
};


#endif // !_MessageHeader_hpp_