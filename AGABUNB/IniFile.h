/*
* File: IniFile.h
* @Des: read ini file.
* @author: yiyy.
*/

#pragma once

class CIniFile
{
public:
	CIniFile();
	CIniFile(LPCTSTR lpFullFilePath);
	virtual ~CIniFile(void);

	void SetFile(LPCTSTR lpFullFilePath);
	UINT ReadIntegrityValue(LPCTSTR lpSection, LPCTSTR lpKey) const;
	CString ReadStringValue(LPCTSTR lpSection, LPCTSTR lpKey) const;

private: 
	char m_szIniFileFullPath[MAX_PATH];
};
