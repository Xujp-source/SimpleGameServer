#ifndef _MessageHeader_hpp_
#define _MessageHeader_hpp_
#include "./Common/stdafx.h"
enum CMD
{
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
	unsigned int dataLength;
	unsigned int cmd;
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