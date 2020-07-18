#ifndef _FD_TO_UID_H_
#define _FD_TO_UID_H_

#include<map>

// client fdsock map client uid
class FdToUid
{
private:
	FdToUid();

	virtual ~FdToUid();

public:
	static FdToUid* GetInstancePtr();

public:
	int GetFdByUid(unsigned long long uid);

	bool SetFdToUid(unsigned long long uid, int fd);

	bool RemoveFdToUid(unsigned long long uid);

private:
	std::map<unsigned long long, int> m_uidmap;
};


#endif