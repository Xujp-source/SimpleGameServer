#include "AgentManager.h"
#include "Agent.h"

AgentManager::AgentManager()
{
}

AgentManager::~AgentManager()
{
}

AgentManager * AgentManager::GetInstancePtr()
{
	static AgentManager _Instance;
	return &_Instance;
}


bool AgentManager::RelayComm(Agent * comm, Agent * tocomm)
{
	int fd = comm->GetFd();
	std::map<int, Agent*>::iterator it = m_Agents.find(fd);
	if (it != m_Agents.end())
	{
		it->second = tocomm;
		delete comm;
		return true;
	}
	return false;
}

bool AgentManager::SetPortToAgent(int fd, Agent * agent)
{
	std::map<int, Agent*>::iterator it = m_Agents.find(fd);
	if (it == m_Agents.end())
	{
		m_Agents.insert(std::make_pair(fd, agent));
		return true;
	}
	return false;
}

bool AgentManager::RemovePortToAgent(int fd)
{
	std::map<int, Agent*>::iterator it = m_Agents.find(fd);
	if (it != m_Agents.end())
	{
		m_Agents.erase(it);
		return true;
	}
	return false;
}

Agent * AgentManager::FindAgentByPort(int fd)
{
	std::map<int, Agent*>::iterator it = m_Agents.find(fd);
	if (it != m_Agents.end())
	{
		return it->second;
	}
	return nullptr;
}
