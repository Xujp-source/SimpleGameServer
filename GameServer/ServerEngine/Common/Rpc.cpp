#include "Rpc.h"

Rpc::Rpc()
{
}

Rpc::~Rpc()
{
}

Rpc * Rpc::GetInstancePtr()
{
	static Rpc _Instance;
	return &_Instance;
}
