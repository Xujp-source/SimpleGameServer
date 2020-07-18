#include "ConfigFile.h"
#include "../CELLLog.hpp"
#include "CommonConvert.h"

CConfigFile::CConfigFile( void )
{

}

CConfigFile::~CConfigFile( void )
{

}

bool CConfigFile::Load( std::string strFileName )
{
	FILE* pFile = fopen(strFileName.c_str(), "r+");

	if(pFile == NULL)
	{
		return false;
	}

	char szBuff[256] = {0};

	do
	{
		fgets(szBuff, 256, pFile);

		if(szBuff[0] == ';')
		{
			continue;
		}

		char* pChar = strchr(szBuff, '=');
		if(pChar == NULL)
		{
			continue;
		}

		std::string strName;
		strName.assign(szBuff, pChar - szBuff);
		std::string strValue = pChar + 1;

		CommonConvert::StringTrim(strName);
		CommonConvert::StringTrim(strValue);

		m_Values.insert(std::make_pair(strName, strValue));

	}
	while(!feof(pFile));

	fclose(pFile);


	return true;
}


CConfigFile* CConfigFile::GetInstancePtr()
{
	static CConfigFile ConfigFile;

	return &ConfigFile;
}

std::string CConfigFile::GetStringValue( std::string strName )
{
	std::map<std::string, std::string>::iterator itor = m_Values.find(strName);
	if(itor != m_Values.end())
	{
		return itor->second;
	}

	CELLLog::Info("无效的配制选项: [%s]", strName.c_str());

	return "";
}

int CConfigFile::GetIntValue( std::string VarName )
{
	return atoi(GetStringValue(VarName).c_str());
}

float CConfigFile::GetFloatValue( std::string VarName )
{
	return (float)atof(GetStringValue(VarName).c_str());
}

double CConfigFile::GetDoubleValue( std::string VarName )
{
	return atof(GetStringValue(VarName).c_str());
}


