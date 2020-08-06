#include "SKillScript.h"

SKillScript::SKillScript()
{
}

SKillScript::~SKillScript()
{
}

SKillScript * SKillScript::GetInstancePtr()
{
	static SKillScript _Instance;
	return &_Instance;
}
