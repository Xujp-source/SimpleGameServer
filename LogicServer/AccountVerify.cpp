#include "AccountVerify.h"

AccountVerify::AccountVerify()
{
}

AccountVerify::~AccountVerify()
{
}

AccountVerify * AccountVerify::GetInstancePtr()
{
	return nullptr;
}

int AccountVerify::CreateLoginCode(unsigned long long uAccountID)
{
	return 0;
}

bool AccountVerify::CheckLoginCode(unsigned long long uAccountID, int nCode)
{
	return false;
}
