#ifndef __ACCOUNT_VERIFY_H__
#define __ACCOUNT_VERIFY_H__
#include<map>

struct CAccount
{
	unsigned long long uEndTime = 0;
	int nCode = 0;
};

class AccountVerify
{
	AccountVerify();
	~AccountVerify();
public:
	static AccountVerify* GetInstancePtr();

public:
	int CreateLoginCode(unsigned long long uAccountID);

	bool CheckLoginCode(unsigned long long uAccountID, int nCode);

private:
	std::map<unsigned long long, CAccount> verifyMap;
};

#endif
