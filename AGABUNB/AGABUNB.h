// AGABUNB.h : main header file for the AGABUNB DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "IniFile.h"

// CAGABUNBApp
// See AGABUNB.cpp for the implementation of this class
//

class CAGABUNBApp : public CWinApp
{
public:
	CAGABUNBApp();

	HWND m_ParentHwnd;

	//使用GMClient工具的操作员ID，登录的时候已经确定
	int m_nGMTUserID;

	//使用GMClient工具的操作员名称，登录的时候已经确定
	CString m_strgGMTUserName;

	CDataOper m_dataOper;

	CIniFile m_iniFile;

	//CAccountDlg是否已被创建.
	BOOL m_bCreatingAccountDlg;

	//CAccountQuery是否已被创建
	BOOL m_bCreatingAccountQuery;
	//CBanQuery是否已被创建
	BOOL m_bCreatingBanQuery;

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

};

extern CAGABUNBApp theApp;
