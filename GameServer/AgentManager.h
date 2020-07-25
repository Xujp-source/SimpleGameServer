#ifndef _AGENT_MANAGER_H_
#define _AGENT_MANAGER_H_
#include <map>

class Agent;
class AgentManager
{
private:
	AgentManager();

	~AgentManager();

public:
	static AgentManager* GetInstancePtr();

public:
	// ת��port_no����һ��������
	bool RelayComm(Agent* comm, Agent* tocomm);

	// ����port_no - agent��ӳ��
	bool SetPortToAgent(int fd, Agent* agent);

	// �Ƴ�port_no - agent��ӳ��
	bool RemovePortToAgent(int fd);

	// ����port_no �� agent����
	Agent* FindAgentByPort(int fd);

private:
	std::map<int, Agent*> m_Agents;
};

#endif