#include "uuid.h"

Uuid::Uuid()
{
}

Uuid::~Uuid()
{
}

Uuid * Uuid::GetInstancePtr()
{
	static Uuid _Instance;
	return &_Instance;
}

unsigned long long Uuid::NewGuid()
{
#ifdef _WIN32
	GUID guid;
	CoCreateGuid(&guid);
	char cBuffer[64] = { 0 };
	sprintf_s(cBuffer, sizeof(cBuffer),
		"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
		guid.Data1, guid.Data2,
		guid.Data3, guid.Data4[0],
		guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4],
		guid.Data4[5], guid.Data4[6],
		guid.Data4[7]);
	return atoi((std::string(cBuffer)).c_str());
#else
	// auto uidGen = boost::uuids::random_generator();
	// boost::uuids::uuid uid = uidGen();
	// std::stringstream sGuid;
	// sGuid << uid;
	// return atoi(sGuid.str());

#endif

}
