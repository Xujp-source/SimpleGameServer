#include "CommonConvert.h"


int CommonConvert::StringToInt(char* pStr)
{
	if(pStr == NULL)
	{
		return 0;
	}

	return atoi(pStr);
}

long long CommonConvert::StringToInt64(char* pStr)
{
	if(pStr == NULL)
	{
		return 0;
	}

#ifdef WIN32
	return _atoi64(pStr);
#else
	return atoll(pStr);
#endif
}

long long CommonConvert::StringToInt64(const char* pStr)
{
	if(pStr == NULL)
	{
		return 0;
	}


#ifdef WIN32
	return _atoi64(pStr);
#else
	return atoll(pStr);
#endif
}

int CommonConvert::StringToInt(const char* pStr)
{
	if(pStr == NULL)
	{
		return 0;
	}

	return atoi(pStr);
}

float CommonConvert::StringToFloat(char* pStr)
{
	if(pStr == NULL)
	{
		return 0;
	}

	return (float)atof(pStr);
}

double CommonConvert::StringToDouble(char* pStr)
{
	if (pStr == NULL)
	{
		return 0;
	}

	return strtod(pStr, NULL);
}

std::string CommonConvert::DoubleToString(double dValue)
{
	char szValue[64] = { 0 };

	snprintf(szValue, 64, "%f", dValue);

	return std::string(szValue);
}

float  CommonConvert::StringToFloat(const char* pStr)
{
	if(pStr == NULL)
	{
		return 0;
	}

	return (float)atof(pStr);
}

std::string CommonConvert::IntToString(int nValue)
{
	char szValue[64] = {0};

	snprintf(szValue, 64, "%d", nValue);

	return std::string(szValue);
}

std::string CommonConvert::IntToString(long long uValue)
{
	char szValue[64] = { 0 };

	snprintf(szValue, 64, "%lld", uValue);

	return std::string(szValue);
}

std::string CommonConvert::IntToString(unsigned int nValue)
{
	char szValue[64] = { 0 };

	snprintf(szValue, 64, "%d", nValue);

	return std::string(szValue);
}

std::string CommonConvert::IntToString(unsigned long long uValue)
{
	char szValue[64] = { 0 };

	snprintf(szValue, 64, "%lld", uValue);

	return std::string(szValue);
}

bool CommonConvert::StringToPos(char* pStr, float& x, float& y, float& z)
{
	if(pStr == NULL)
	{
		return false;
	}

	char szTempBuf[256] = { 0 };
	strncpy(szTempBuf, pStr, strlen(pStr));

	char* pPos = strchr(szTempBuf, ',');
	if(pPos == NULL)
	{
		return false;
	}
	*pPos = 0;
	x = CommonConvert::StringToFloat(szTempBuf + 1);

	char* pOldPos = pPos + 1;
	pPos = strchr(pPos + 1, ',');
	if(pPos == NULL)
	{
		return false;
	}
	*pPos = 0;
	y = CommonConvert::StringToFloat(pOldPos);

	pOldPos = pPos + 1;
	pPos = strchr(pPos + 1, ')');
	if(pPos == NULL)
	{
		return false;
	}
	*pPos = 0;
	z = CommonConvert::StringToFloat(pOldPos);

	return true;
}

bool CommonConvert::StringToBox(char* pStr, float& left, float& top, float& right, float& bottom)
{
	if (pStr == NULL)
	{
		return false;
	}

	char szTempBuf[256] = { 0 };
	strncpy(szTempBuf, pStr, strlen(pStr));

	char* pPos = strchr(szTempBuf, ',');
	if (pPos == NULL)
	{
		return false;
	}
	*pPos = 0;
	left = CommonConvert::StringToFloat(szTempBuf + 1);

	char* pOldPos = pPos + 1;
	pPos = strchr(pPos + 1, ',');
	if (pPos == NULL)
	{
		return false;
	}
	*pPos = 0;
	top = CommonConvert::StringToFloat(pOldPos);

	pOldPos = pPos + 1;
	pPos = strchr(pPos + 1, ',');
	if (pPos == NULL)
	{
		return false;
	}
	*pPos = 0;
	right = CommonConvert::StringToFloat(pOldPos);

	pOldPos = pPos + 1;
	pPos = strchr(pPos + 1, ')');
	if (pPos == NULL)
	{
		return false;
	}
	*pPos = 0;
	bottom = CommonConvert::StringToFloat(pOldPos);

	return true;
}

std::string CommonConvert::FloatToString(float fValue, int nPrecision, bool bRound)
{
	char szValue[64] = {0};

	if((bRound) && (nPrecision > 0) && (nPrecision < 6))
	{
		float fRoundValue = 5;

		for(int i = 0; i < nPrecision + 1; i++)
		{
			fRoundValue *= 0.1f;
		}

		fValue += fRoundValue;
	}

	snprintf(szValue, 64, "%f", fValue);

	char* pChar = strchr(szValue, '.');
	if(pChar == NULL)
	{
		return std::string(szValue);
	}

	*(pChar + nPrecision + 1) = '\0';

	return std::string(szValue);
}

bool CommonConvert::SpliteString(std::string strSrc, std::string strDelim, std::vector<std::string>& vtStr)
{
	vtStr.clear();
	if (strDelim.empty())
	{
		vtStr.push_back(strSrc);
		return true;
	}

	std::string::iterator subStart, subEnd;
	subStart = strSrc.begin();
	while (true)
	{
		subEnd = std::search(subStart, strSrc.end(), strDelim.begin(), strDelim.end());
		std::string temp(subStart, subEnd);
		if (!temp.empty())
		{
			vtStr.push_back(temp);
		}
		if (subEnd == strSrc.end())
		{
			break;
		}
		subStart = subEnd + strDelim.size();
	}

	return true;
}

bool CommonConvert::ReplaceString(std::string& str, const std::string& pattern, const std::string& newpat)
{
	const size_t nsize = newpat.size();
	const size_t psize = pattern.size();

	for (size_t pos = str.find(pattern, 0); pos != std::string::npos; pos = str.find(pattern, pos + nsize))
	{
		str.replace(pos, psize, newpat);
	}

	return true;
}

bool CommonConvert::StringToVector(const char* pStrValue, int IntVector[], int nSize, char cDelim)
{
	if (pStrValue == NULL)
	{
		return false;
	}

	char szBuf[1024] = { 0 };
	strncpy(szBuf, pStrValue, 1024);

	char* pBeginPos = szBuf;
	char* pEndPos = strchr(pBeginPos, cDelim);

	if (pBeginPos == pEndPos)
	{
		pBeginPos += 1;
		pEndPos = strchr(pBeginPos, cDelim);
	}

	int nIndex = 0;
	while (pEndPos != NULL)
	{
		//*pEndPos = 0;
		IntVector[nIndex++] = StringToInt(pBeginPos);
		if (nIndex >= nSize)
		{
			return true;
		}

		pBeginPos = pEndPos + 1;
		pEndPos = strchr(pBeginPos, cDelim);
	}

	if (*pBeginPos != 0 && nIndex < nSize)
	{
		IntVector[nIndex++] = StringToInt(pBeginPos);
	}

	return true;
}

bool CommonConvert::StringToVector(const char* pStrValue, float FloatVector[], int nSize, char cDelim /*= ','*/)
{
	if (pStrValue == NULL)
	{
		return false;
	}

	char szBuf[1024] = { 0 };
	strncpy(szBuf, pStrValue, 1024);

	char* pBeginPos = szBuf;
	char* pEndPos = strchr(pBeginPos, cDelim);

	if (pBeginPos == pEndPos)
	{
		pBeginPos += 1;
		pEndPos = strchr(pBeginPos, cDelim);
	}

	int nIndex = 0;
	while (pEndPos != NULL)
	{
		FloatVector[nIndex++] = StringToFloat(pBeginPos);
		if (nIndex >= nSize)
		{
			return true;
		}

		pBeginPos = pEndPos + 1;
		pEndPos = strchr(pBeginPos, cDelim);
	}

	if (*pBeginPos != 0 && nIndex < nSize)
	{
		FloatVector[nIndex++] = StringToFloat(pBeginPos);
	}

	return true;
}

bool CommonConvert::SpliteString(std::string strSrc,  char cDelim, std::vector<std::string>& vtStr)
{
	vtStr.clear();

	std::string::size_type posStart, posEnd;
	posEnd = strSrc.find(cDelim);
	posStart = 0;
	while(std::string::npos != posEnd)
	{
		vtStr.emplace_back(strSrc.substr(posStart, posEnd - posStart));

		posStart = posEnd + 1;
		posEnd = strSrc.find(cDelim, posStart);
	}

	if(posStart != strSrc.length())
	{
		vtStr.emplace_back(strSrc.substr(posStart));
	}

	return true;
}


unsigned int CommonConvert::VersionToInt(const std::string& strVersion )
{
	int nValue[3] = { 0 };
	StringToVector(strVersion.c_str(), nValue, 3, '.');
	return nValue[0] * 1000000 + nValue[1] * 1000 + nValue[2];
}

int CommonConvert::CountSymbol(char* pStr, char cSymbol )
{
	if(pStr == NULL)
	{
		return 0;
	}

	int nCount = 0;

	char* pTemp = pStr;
	while(*pTemp != '\0')
	{
		if(*pTemp == cSymbol)
		{
			nCount += 1;
		}

		pTemp += 1;
	}

	return nCount;
}

bool CommonConvert::StringTrim(std::string& strValue)
{
	if(!strValue.empty())
	{
		strValue.erase(0, strValue.find_first_not_of((" \n\r\t")));
		strValue.erase(strValue.find_last_not_of((" \n\r\t")) + 1);
	}
	return true;
}
