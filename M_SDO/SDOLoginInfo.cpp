// SDOLoginInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOLoginInfo.h"
#include ".\sdologininfo.h"


// CSDOLoginInfo 对话框
#include "OperationSDO.h"

static LPCSTR INI_WNDTEXT_SECTION ="MSDO"; //"WNDTEXT";


CSDOLoginInfo::CSDOLoginInfo(CWnd* pParent /*=NULL*/)
	: CSDOBaseDlg(pParent)
{
}

CSDOLoginInfo::~CSDOLoginInfo(void)
{
}


BEGIN_MESSAGE_MAP(CSDOLoginInfo, CSDOBaseDlg)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST_ACCOUNT_INFO, OnLvnColumnclickListAccountInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_ACCOUNT_INFO, OnCbnSelchangeCmbAccountInfo)	
END_MESSAGE_MAP()


// CSDOLoginInfo 消息处理程序

// 初始化对话框

BOOL CSDOLoginInfo::OnInitDialog()
{
	CSDOBaseDlg::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"UIC_UI_LoginInfo"));

	// 查詢帳號的角色信息列表框.
	CreateCtrlList(m_listAccountInfo, IDC_LIST_ACCOUNT_INFO);

	// 頁索引.
	CreateCtrlComCmb(m_cmbAccountInfoPage, IDC_CMB_PAGE_ACCOUNT_INFO);

	// Tab控件标签相关联的控件id，当标签被激活，这些控件将显示.
	DWORD dwTabItemCtrlID[][TAB_ITEM_CTRL_MAX_NUM] = 
	{
		IDC_LIST_ACCOUNT_INFO, IDC_CMB_PAGE_ACCOUNT_INFO, IDOK,

	};

	// Tab控件标签文本在.ini文件中的key.
	const char const *pTabTextKey[] = 
	{
		"UIC_UI_tpgLoginInfo",
	};

	TCB_ITEM ti[TII_ITEM_COUNT];
	for (int i=0; i<TII_ITEM_COUNT; i++)
	{
		LPTCB_ITEM_DATA lptid = NULL;
		for (int j=0; j<TAB_ITEM_CTRL_MAX_NUM; j++)
		{
			if (lptid == NULL)
			{
				lptid = new TCB_ITEM_DATA;
				ti[i].lptid = lptid;
			}
			else
			{
				lptid->pNext = new TCB_ITEM_DATA;
				lptid = lptid->pNext;
			}
			lptid->dwCtrlID = dwTabItemCtrlID[i][j];
		}

		ti[i].strKey = pTabTextKey[i];
	}

	CString strSec(INI_WNDTEXT_SECTION);
	InitTableCtrl(ti, TII_ITEM_COUNT, strSec);


	// 以下控件总是显示.
	CTRLID_INI_KEY cik[] = 
	{
		IDC_STATICBASEGRPPAGE,	"PageGroupText",
		IDD_STATICBASEPAGE,		"PleaseSelPageCount",
		IDC_STATICMENUPROMPT,	"ListCtrlMenuPrompt"
	};
	for (int i=0; i<sizeof(cik)/sizeof(CTRLID_INI_KEY); i++)
	{
		CWnd* pWnd = GetDlgItem(cik[i].dwCtrlID);
		ASSERT(pWnd != NULL);
		pWnd->ShowWindow(SW_SHOW);
		CString strText=theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, CString(cik[i].lpKey));
		pWnd->SetWindowText(strText);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSDOLoginInfo::QueryOperation(int nTabCurSel)//继承BaseDlg
{
	ASSERT(nTabCurSel == TII_QUERY_ACCOUNT);

	ResetCmbCtrl(m_cmbAccountInfoPage);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	///QueryOtherInfo(CEnumCore::ServiceKey::SDO_USERONLINE_QUERY,strPageIndex,m_listAccountInfo);
	QueryLogin(strPageIndex);
}

//查询玩家登录信息
void CSDOLoginInfo::QueryLogin(CString& curPage)
{
	CString strServerIP = GetGameServerIP();
	CString strServerName = GetGameServerName();
	CString strAccount = GetAccount();
	CString strNick = GetNick();
	CString strPageIndex = curPage;

	try
	{
		CSocketData socketdata;	
		socketdata.InitCreate(1, 10);

		// 服务器IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);
		
		//服务器名
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName, CEnumCore::TagFormat::TLV_STRING, 
			strServerName.GetLength(), (unsigned char *)(LPCTSTR)strServerName);

		//玩家帐号.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account, CEnumCore::TagFormat::TLV_STRING,
			strAccount.GetLength(), (unsigned char *)(LPCTSTR)strAccount);

		//玩家昵称.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName, CEnumCore::TagFormat::TLV_STRING, 
			strNick.GetLength(), (unsigned char *)(LPCTSTR)strNick);

		// 开始页.
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,
			strPageIndex.GetLength(), (unsigned char *)(LPCTSTR)strPageIndex);

		// 每页记录数.
		socketdata.AddTFLV(CEnumCore::TagName::PageSize, CEnumCore::TagFormat::TLV_INTEGER,
			m_strPageSize.GetLength(), (unsigned char *)(LPCTSTR)m_strPageSize);

		int nDataLen = socketdata.EnBody();
		theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, CEnumCore::ServiceKey::SDO_USERONLINE_QUERY);

		EnableWindow(FALSE);
	}
	catch(...)
	{
	}
}


void CSDOLoginInfo::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//继承BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_USERONLINE_QUERY_RESP:			// 查询登陆信息
		SetDataForListCtrl(m_listAccountInfo, socketData, m_cmbAccountInfoPage);
		break;
	default:
		break;
	}
}

BOOL CSDOLoginInfo::ClearDataForCtrl()//继承BaseDlg
{
	return TRUE;
}

void CSDOLoginInfo::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//继承BaseDlg
{
}

void CSDOLoginInfo::ImplementUpdateOperation(int nTabCurSel)//继承BaseDlg
{
}

BOOL CSDOLoginInfo::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == m_listAccountInfo.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listAccountInfo);				
				}
				
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == m_listAccountInfo.m_hWnd)
				{
					for(int i=0; i<m_listAccountInfo.GetItemCount(); i++)
					{
					    m_listAccountInfo.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						m_listAccountInfo.EnsureVisible(i,false);
					}
				}

			}
		}		
	}
	return FALSE;
}

void CSDOLoginInfo::OnLvnColumnclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listAccountInfo,pNMHDR,pResult);
	*pResult = 0;
}

void CSDOLoginInfo::OnCbnSelchangeCmbAccountInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_USERONLINE_QUERY,strPageIndex,m_listAccountInfo);
}
