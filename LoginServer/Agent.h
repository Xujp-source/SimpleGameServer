#ifndef _AGENT_H_
#define _AGENT_H_
#include "google/protobuf/message.h"
#include "EventHandlerManager.hpp"
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

	void RegisterMessageHanler();

public:
	//����������Ϣ
	bool SendData(int MsgID, const google::protobuf::Message& pdata);

	//����sockfd
	inline void SetFd(int sockfd) { fd = sockfd; }

	//���sockfd
	inline int GetFd() { return fd; }

	//�Ƿ�����Ҷ���
	virtual bool IsUser() { return false; }

public:
	//*******************��Ϣ������**************************
	bool OnMsgClientHeartReq(NetPacket* pack);	  //����Client����������
	//*********************************************************
	
public:
	//������Ϣ��
	CHandlerManager m_NetMessagePump;
	//�ص��¼�
	CEventHandler m_EventPump;

};

#endif