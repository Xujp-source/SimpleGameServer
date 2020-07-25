#ifndef __COMMON_CONVERT__
#define __COMMON_CONVERT__
#include "stdafx.h"

namespace CommonConvert
{
int StringToInt(char* pStr);

int StringToInt(const char* pStr);

long long StringToInt64(char* pStr);

long long StringToInt64(const char* pStr);

float StringToFloat(char* pStr);

float StringToFloat(const char* pStr);

double StringToDouble(char* pStr);

std::string DoubleToString(double dValue);

std::string IntToString(unsigned int nValue);

std::string IntToString(int nValue);

std::string IntToString(unsigned long long nValue);

std::string IntToString(long long nValue);

bool  StringToPos(char* pStr, float& x, float& y, float& z);

bool  StringToBox(char* pStr, float& left, float& top, float& right, float& bottom);

//浮点到字符串， nPrecision 保留的最大小数的位数， bRound 是否四舍五入
std::string FloatToString(float fValue, int nPrecision = -1, bool bRound = false);

// std::wstring Utf8_To_Unicode(std::string strValue);
//
// std::string  Unicode_To_Uft8(std::wstring wstrValue);
//
// std::wstring Ansi_To_Unicode(std::string strValue);
//
// std::string Unicode_To_Ansi(std::wstring strValue);
//
// std::string Utf8_To_Ansi(std::string strValue);
//
// std::string Ansi_To_Uft8(std::string wstrValue);
//
// bool IsTextUTF8(const char* str, UINT32 length);

bool SpliteString(std::string strSrc,  std::string strDelim, std::vector<std::string>& vtStr);

bool SpliteString(std::string strSrc, char cDelim, std::vector<std::string>& vtStr);

bool ReplaceString(std::string& str, const std::string& pattern, const std::string& newpat);

bool StringToVector(const char* pStrValue, int IntVector[], int nSize, char cDelim = ',');

bool StringToVector(const char* pStrValue, float FloatVector[], int nSize, char cDelim = ',');

unsigned int VersionToInt(const std::string& strVersion);

int  CountSymbol(char* pStr, char cSymbol);

bool StringTrim(std::string& strValue);

}


#endif /* __COMMON_CONVERT__ */
