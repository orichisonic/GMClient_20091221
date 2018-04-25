#include "StdAfx.h"
#include "IniFile.h"

CIniFile::CIniFile()
{
	memset(m_szIniFileFullPath, 0, sizeof(m_szIniFileFullPath));
}

CIniFile::CIniFile(LPCTSTR lpFullFilePath)
{
	ASSERT(NULL != lpFullFilePath);
//	strcpy_s(m_szIniFileFullPath, sizeof(m_szIniFileFullPath), lpFullFilePath);	
	strcpy(m_szIniFileFullPath, lpFullFilePath);	
}

CIniFile::~CIniFile(void)
{

}

void CIniFile::SetFile(LPCTSTR lpFullFilePath)
{
	ASSERT(NULL != lpFullFilePath);
	//strcpy_s(m_szIniFileFullPath, sizeof(m_szIniFileFullPath), lpFullFilePath);	
	strcpy(m_szIniFileFullPath, lpFullFilePath);	
}

UINT CIniFile::ReadIntegrityValue(LPCTSTR lpSection, LPCTSTR lpKey) const
{
	ASSERT(NULL != lpSection);
	ASSERT(NULL != lpKey);


	UINT uValue = ::GetPrivateProfileInt(lpSection, lpKey, -1, m_szIniFileFullPath);
	ASSERT((int)uValue > -1);

	return uValue;
}

CString CIniFile::ReadStringValue(LPCTSTR lpSection, LPCTSTR lpKey) const
{
	ASSERT(NULL != lpSection);
	ASSERT(NULL != lpKey);

	char szBuff[MAX_PATH] = {0};
	DWORD dwRet = ::GetPrivateProfileString(lpSection, lpKey, "", szBuff, sizeof(szBuff), m_szIniFileFullPath);
	ASSERT(0<dwRet && dwRet<=MAX_PATH);

	CString strRet(szBuff);

	return strRet;
}
