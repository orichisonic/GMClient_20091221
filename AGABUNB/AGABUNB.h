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

	//ʹ��GMClient���ߵĲ���ԱID����¼��ʱ���Ѿ�ȷ��
	int m_nGMTUserID;

	//ʹ��GMClient���ߵĲ���Ա���ƣ���¼��ʱ���Ѿ�ȷ��
	CString m_strgGMTUserName;

	CDataOper m_dataOper;

	CIniFile m_iniFile;

	//CAccountDlg�Ƿ��ѱ�����.
	BOOL m_bCreatingAccountDlg;

	//CAccountQuery�Ƿ��ѱ�����
	BOOL m_bCreatingAccountQuery;
	//CBanQuery�Ƿ��ѱ�����
	BOOL m_bCreatingBanQuery;

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

};

extern CAGABUNBApp theApp;
