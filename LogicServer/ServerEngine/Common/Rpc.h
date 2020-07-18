#ifndef __RPC__H__
#define __RPC__H__

class Rpc
{
private:
	Rpc();

	~Rpc();

public:
	static Rpc* GetInstancePtr();
};

#endif