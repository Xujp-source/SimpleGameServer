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
	// 转接port_no到另一个对象上
	bool RelayComm(Agent* comm, Agent* tocomm);

	// 设置port_no - agent的映射
	bool SetPortToAgent(int fd, Agent* agent);

	// 移除port_no - agent的映射
	bool RemovePortToAgent(int fd);

	// 根据port_no 找 agent对象
	Agent* FindAgentByPort(int fd);

private:
	std::map<int, Agent*> m_Agents;
};

#endif