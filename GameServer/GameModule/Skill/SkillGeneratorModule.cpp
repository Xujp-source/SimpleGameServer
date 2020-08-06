#include "SKillGeneratorModule.h"

SKillGenerator::SKillGenerator()
{
}

SKillGenerator::~SKillGenerator()
{
}

bool SKillGenerator::CreateSkill(BattleSide & ack, BattleSide & def, int skill_id)
{
	return false;
}

SKillGenerator * SKillGenerator::GetInstancePtr()
{
	static SKillGenerator _Instance;
	return &_Instance;
}
