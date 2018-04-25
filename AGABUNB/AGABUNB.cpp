// AGABUNB.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "DataOper.h"
#include "AGABUNB.h"
#include "AccountDlg.h"
#include "AccountQuery.h"
#include "BanQuery.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

const LPCTSTR INI_FILE_NAME	= "Config\\AGABUNB.ini";

// CAGABUNBApp

BEGIN_MESSAGE_MAP(CAGABUNBApp, CWinApp)
END_MESSAGE_MAP()


// CAGABUNBApp construction

CAGABUNBApp::CAGABUNBApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_bCreatingAccountDlg = FALSE;
	m_bCreatingBanQuery=FALSE;
}


// The one and only CAGABUNBApp object

CAGABUNBApp theApp;

CAccountDlg g_accountDlg;
CAccountQuery g_accountQuery;
CBanQuery g_banquery;
// CAGABUNBApp initialization

BOOL CAGABUNBApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Set ini file.
	char szFile[MAX_PATH] = {0};
	if( 0 == ::GetModuleFileName( NULL, szFile, sizeof(szFile)))
	{
		AfxMessageBox("CAGABUNBApp::InitInstance(): ::GetModuleFileName failed!");
		return FALSE;
	}

	char* lpTemp = strrchr(szFile, '\\');
	lpTemp++;
	memset(lpTemp, 0, strlen(lpTemp));
	int nSurplusBuffLen = sizeof(szFile)-strlen(szFile);
//	strcpy_s(lpTemp, nSurplusBuffLen, INI_FILE_NAME);
	strcpy(lpTemp, INI_FILE_NAME);

	m_iniFile.SetFile(szFile);

	return TRUE;
}

GMT_EXT_API void Initialize(SOCKET sock, int nUserID, CString strUserName, HWND hParent, int* nSelectDll)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ASSERT(0 < nUserID);
	ASSERT(0 < strUserName.GetLength());
	ASSERT(NULL != hParent);

	theApp.m_nGMTUserID = nUserID;			// 操作员ID.
	theApp.m_strgGMTUserName = strUserName;	// 操作员名称.
	theApp.m_dataOper.SetSocket(sock);// 用于收/发数据.
	theApp.m_ParentHwnd = hParent;
}

GMT_EXT_API void ShowGABUNBDlg(CString DlgName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CIni mIni;

	if(!strcmp(DlgName, mIni.ReadValue("Global","AGABUNB")))
	{
		if(g_accountDlg.m_hWnd!=NULL)
		{
			DWORD i = (g_accountDlg.GetStyle() & SW_HIDE);
		//		if (theApp.m_bCreatingAccountDlg && (g_accountDlg.GetStyle() & SW_HIDE) != 0)
			if (theApp.m_bCreatingAccountDlg)
				g_accountDlg.SetWindowPos(&CWnd::wndTop, 0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		}
	}
	else if(!strcmp(DlgName, mIni.ReadValue("Global","AccountQuery")))
	{
		if(g_accountQuery.m_hWnd!=NULL)
		{
			DWORD i = (g_accountQuery.GetStyle() & SW_HIDE);
			//		if (theApp.m_bCreatingAccountDlg && (g_accountDlg.GetStyle() & SW_HIDE) != 0)
			if (theApp.m_bCreatingAccountQuery)
				g_accountQuery.SetWindowPos(&CWnd::wndTop, 0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		}
	}
	else if(!strcmp(DlgName, mIni.ReadValue("Global","BanQuery")))
	{
		if(g_banquery.m_hWnd!=NULL)
		{
			DWORD i = (g_banquery.GetStyle() & SW_HIDE);
			//		if (theApp.m_bCreatingAccountDlg && (g_accountDlg.GetStyle() & SW_HIDE) != 0)
			if (theApp.m_bCreatingBanQuery)
				g_banquery.SetWindowPos(&CWnd::wndTop, 0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		}
	}
	
	
}

GMT_EXT_API void CloseDialog(LPCTSTR lpDlgName)// = NULL)//maple update
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CIni mIni;
	if(!strcmp(lpDlgName, mIni.ReadValue("Global","AGABUNB")))
	{
		if(g_accountDlg.m_hWnd!=NULL)
		{
			g_accountDlg.SendMessage(WM_CLOSE,0,0);
		}
	}
	else if(!strcmp(lpDlgName, mIni.ReadValue("Global","AccountQuery")))
	{
		if(g_accountQuery.m_hWnd!=NULL)
		{
			g_accountQuery.SendMessage(WM_CLOSE,0,0);
		}
	}
	else if(!strcmp(lpDlgName, mIni.ReadValue("Global","BanQuery")))
	{
		if(g_banquery.m_hWnd!=NULL)
		{
			g_banquery.SendMessage(WM_CLOSE,0,0);
		}
	}
	else
	{
		if(g_accountDlg.m_hWnd!=NULL)
		{
			g_accountDlg.SendMessage(WM_CLOSE,0,0);
		}
		if(g_accountQuery.m_hWnd!=NULL)
		{
			g_accountQuery.SendMessage(WM_CLOSE,0,0);
		}
		if(g_banquery.m_hWnd!=NULL)
		{
			g_banquery.SendMessage(WM_CLOSE,0,0);
		}
	}
	
	/*DWORD dwParam = BN_CLICKED;
	dwParam<<16;
	dwParam += IDCANCEL;
	g_accountDlg.SendMessage(WM_COMMAND, (WPARAM)dwParam, NULL);*/
}

GMT_EXT_API BOOL OpenCAGABUNBDlg(CString m_MenuName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CIni mIni;
//MessageBox(NULL,m_MenuName,"",0);
	ASSERT(NULL != theApp.m_ParentHwnd);
	if(!strcmp(m_MenuName, mIni.ReadValue("Global","AGABUNB")))
	{
		if(!theApp.m_bCreatingAccountDlg)
		{
			g_accountDlg.Create(CAccountDlg::IDD);
			::SetParent(g_accountDlg.m_hWnd, theApp.m_ParentHwnd);
			g_accountDlg.ShowWindow(SW_SHOWMAXIMIZED);
			theApp.m_bCreatingAccountDlg = TRUE;

		}
		else
		{
			g_accountDlg.ShowWindow(SW_SHOWMAXIMIZED);
		}
	}
	else if(!strcmp(m_MenuName, mIni.ReadValue("Global","AccountQuery")))
	{
		if(!theApp.m_bCreatingAccountQuery)
		{
			g_accountQuery.Create(CAccountDlg::IDD);
			::SetParent(g_accountQuery.m_hWnd, theApp.m_ParentHwnd);
			g_accountQuery.ShowWindow(SW_SHOWMAXIMIZED);
			theApp.m_bCreatingAccountQuery = TRUE;

		}
		else
		{
			g_accountQuery.ShowWindow(SW_SHOWMAXIMIZED);
		}
	}
	else if(!strcmp(m_MenuName, mIni.ReadValue("Global","BanQuery")))
	{
		if(!theApp.m_bCreatingBanQuery)
		{
			g_banquery.Create(CAccountDlg::IDD);
			::SetParent(g_banquery.m_hWnd, theApp.m_ParentHwnd);
			g_banquery.ShowWindow(SW_SHOWMAXIMIZED);
			theApp.m_bCreatingBanQuery = TRUE;

		}
		else
		{
			g_banquery.ShowWindow(SW_SHOWMAXIMIZED);
		}
	}
	
	


	return TRUE;
}

GMT_EXT_API void SetRecvData(unsigned char * lpRecvbuf, int nDataLen, CEnumCore::Message_Tag_ID m_message_tag_id)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (theApp.m_bCreatingAccountDlg && !g_accountDlg.IsWindowEnabled())
	{
		CSocketData socketdata;
		socketdata.Create(nDataLen/8);
		if(!socketdata.DeBody(lpRecvbuf, nDataLen))
		{
			CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTION, "DeBodyErr");
			AfxMessageBox(strErr);
			socketdata.Destroy();
			return;
		}

		g_accountDlg.SetRecvData(socketdata, m_message_tag_id);

		socketdata.Destroy();		
	}
	if (theApp.m_bCreatingAccountQuery&& !g_accountQuery.IsWindowEnabled())
	{
		CSocketData socketdata;
		socketdata.Create(nDataLen/8);
		if(!socketdata.DeBody(lpRecvbuf, nDataLen))
		{
			CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTION, "DeBodyErr");
			AfxMessageBox(strErr);
			socketdata.Destroy();
			return;
		}

		g_accountQuery.SetRecvData(socketdata, m_message_tag_id);

		socketdata.Destroy();		
	}
	if (theApp.m_bCreatingBanQuery&& !g_banquery.IsWindowEnabled())
	{
		CSocketData socketdata;
		socketdata.Create(nDataLen/8);
		if(!socketdata.DeBody(lpRecvbuf, nDataLen))
		{
			CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTION, "DeBodyErr");
			AfxMessageBox(strErr);
			socketdata.Destroy();
			return;
		}

		g_banquery.SetRecvData(socketdata, m_message_tag_id);

		socketdata.Destroy();		
	}
}