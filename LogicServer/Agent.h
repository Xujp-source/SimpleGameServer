#ifndef _AGENT_H_
#define _AGENT_H_
#include "google/protobuf/message.h"
#include "MsgHandlerManager.hpp"
#include "./ServerEngine/MessageHeader.hpp"
#include <map>

// ���Ӷ������
class Agent
{
private:
	int fd;

public:
	Agent();
	virtual ~Agent();

public:
	//����������Ϣ
	bool SendData(int MsgID, const google::protobuf::Message& pdata);

	//����sockfd
	inline void SetFd(int sockfd) { fd = sockfd; }

	//���sockfd
	inline int GetFd() { return fd; }

	//�Ƿ�����Ҷ���
	virtual bool IsUser() { return false; }

	//�Ƿ��������������������ɵ����Ӷ���
	bool isConnect() { return isConFlag; }

	void SetConnect(bool res) { isConFlag = res; }

public:
	//*******************��Ϣ������**************************
	bool OnMsgUserHeartReq(NetPacket* pack);	  //Client(���)����������
	//*********************************************************
	
public:
	//������Ϣ��
	CHandlerManager m_NetMessagePump;

	bool isConFlag = false;

};

#endif