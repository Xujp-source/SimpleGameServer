#include "Agent.h"
#include "GameService.h"

Agent::Agent()
{
}

Agent::~Agent()
{
}

bool Agent::SendData(int MsgID, const google::protobuf::Message & pdata)
{
	CGameService::GetInstancePtr()->SendData(fd, MsgID, pdata);
	return false;
}

bool Agent::OnMsgUserHeartReq(NetPacket * pack)
{
	return false;
}


