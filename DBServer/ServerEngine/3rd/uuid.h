#ifndef _UUID_H_
#define _UUID_H_

#ifdef _WIN32

#include <objbase.h>
#include <string>

#else

#include <iostream>
// #include <boost/uuid/uuid.hpp>
// #include <boost/uuid/uuid_generators.hpp>
// #include <boost/uuid/uuid_io.hpp>

#endif


class Uuid
{
private:
	Uuid();
	~Uuid();

public:
	static Uuid* GetInstancePtr();

	unsigned long long NewGuid();
};



#endif
