// SDOPurchaseInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOPurchaseInfo.h"
#include ".\sdopurchaseinfo.h"


// CSDOPurchaseInfo 对话框
#include "OperationSDO.h"

// CSDOFamilyDonate 对话框
static LPCSTR INI_WNDTEXT_SECTION ="MSDO"; //"WNDTEXT";
CSDOPurchaseInfo::CSDOPurchaseInfo(CWnd* pParent /*=NULL*/)
	: CSDOFamilyBaseDlg(pParent)
{
}

CSDOPurchaseInfo::~CSDOPurchaseInfo()
{
}

BEGIN_MESSAGE_MAP(CSDOPurchaseInfo, CSDOFamilyBaseDlg)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST_FAMILY_INFO, OnLvnColumnclickListFamilyInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_FAMILY_INFO, OnCbnSelchangeCmbFamilyInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_FAMILY_INFO, OnNMRclickListFamilyInfo)
	ON_COMMAND(IDM_QUERY_PURCHASE, OnMenuCmdQueryPurchase)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_PURCHASE_INFO, OnLvnColumnclickListPurchaseInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_PURCHASE, OnCbnSelchangeCmbPurchaseInfo)
END_MESSAGE_MAP()


// CSDOPurchaseInfo 消息处理程序

// 初始化对话框

BOOL CSDOPurchaseInfo::OnInitDialog()
{
	CSDOFamilyBaseDlg::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"PI_UI_PurchaseInfo"));
	const char const *pMenuTextKey[] =
	{
		"",								// 查詢帳號的角色信息，不需要菜單.
		"MenuText_QueryPurchase",		// 查询家族购买信息
	};
	CString strMenuText;
	//查询家族基本信息
	CreateCtrlList(m_listFamilyInfo, IDC_LIST_FAMILY_INFO);
	CreateCtrlComCmb(m_cmbFamilyPage, IDC_CMB_PAGE_FAMILY_INFO);

	m_menuFamily.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_PURCHASE-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuFamily.AppendMenu(MF_STRING, IDM_QUERY_PURCHASE, (LPCTSTR)strMenuText);

	//家族购买信息
	CreateCtrlList(m_listFamilyPurchase, IDC_LIST_PURCHASE_INFO);
	CreateCtrlComCmb(m_cmbFamilyPurchase, IDC_CMB_PAGE_PURCHASE);

	DWORD dwTabItemCtrlID[][TAB_ITEM_CTRL_MAX_NUM] = 
	{
		{IDC_LIST_FAMILY_INFO, IDC_CMB_PAGE_FAMILY_INFO, IDOK,IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE, IDC_STATICMENUPROMPT},
		{IDC_LIST_PURCHASE_INFO, IDC_CMB_PAGE_PURCHASE, IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE,0,0},
	};

	// Tab控件标签文本在.ini文件中的key.
	const char const *pTabTextKey[] = 
	{
		"FI_UI_tpgBasicInfo",
		"PI_UI_tpgPurchase",
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
		////pWnd->ShowWindow(SW_SHOW);
		CString strText=theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, CString(cik[i].lpKey));
		pWnd->SetWindowText(strText);
	}
	GetDlgItem(IDC_STATICBASEBEGIN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATICBASEEND)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DTPBEGIN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DTPEND)->ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSDOPurchaseInfo::QueryOperation(int nTabCurSel)//继承BaseDlg
{
	ASSERT(nTabCurSel == TII_QUERY_FAMILY);

	ResetCmbCtrl(m_cmbFamilyPage);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbFamilyPage);
	QueryFamilyInfo(strPageIndex);
}


void CSDOPurchaseInfo::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//继承BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_Family_Info_QUERY_RESP://家族基本信息
		SetDataForListCtrl(m_listFamilyInfo, socketData, m_cmbFamilyPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_Family_CONSUME_QUERY_RESP:
		SetDataForListCtrl(m_listFamilyPurchase, socketData, m_cmbFamilyPurchase);
		break;
	default:
		break;
	}
}

BOOL CSDOPurchaseInfo::ClearDataForCtrl()//继承BaseDlg
{
	m_menuFamily.DestroyMenu();
	return TRUE;
}

void CSDOPurchaseInfo::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//继承BaseDlg
{
}

void CSDOPurchaseInfo::ImplementUpdateOperation(int nTabCurSel)//继承BaseDlg
{
}

void CSDOPurchaseInfo::OnLvnColumnclickListFamilyInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listFamilyInfo,pNMHDR,pResult);
	*pResult = 0;
}

void CSDOPurchaseInfo::OnCbnSelchangeCmbFamilyInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbFamilyPage);
	QueryFamilyInfo(strPageIndex);
}

void CSDOPurchaseInfo::OnNMRclickListFamilyInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItemActive = (LPNMITEMACTIVATE)pNMHDR;
	if (lpItemActive->iItem < 0)
		return;

	PopupMenuForListCtrlRClick(m_listFamilyInfo, m_menuFamily, lpItemActive->ptAction);
}

//查询购买信息
void CSDOPurchaseInfo::OnMenuCmdQueryPurchase()
{
	SetTabCtrlItemCurSel(TII_QUERY_PURCHASE);
	CString strPageIndex = GetCmbCurSelText(m_cmbFamilyPurchase);
	QueryPurchase(strPageIndex);
}

void CSDOPurchaseInfo::QueryPurchase(CString& curPage)
{
	CString strServerIP = GetGameServerIP();
	CString strServerName = GetGameServerName();
	CString strFamilyName = GetDataFromListCtrl(m_listFamilyInfo, CEnumCore::TagName::SDO_FamilyName);
	CString strFamilyID = GetDataFromListCtrl(m_listFamilyInfo, CEnumCore::TagName::SDO_FamilyID);
	CString strPageIndex = curPage;

	CString strStartTime = "";//开始时间
	CString strEndTime = "";//结束时间

	CTime curTime = CTime::GetCurrentTime();

	CTime StartTime;
	dtcLoginDate.GetTime(StartTime);//获取开始时间

	CTime EndTime;
	dtcLogoutDate.GetTime(EndTime);//获取结束时间

	if(StartTime >= curTime)//开始时间不能大于当前时间
	{
		MessageBox(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"LI_Warn_StartTime"),theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"Warn"),0);
		return;
	}

	if(EndTime <= StartTime)//结束时间不能小于开始时间
	{
		MessageBox(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"LI_Warn_TimeSpan"),theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"Warn"),0);
		return;
	}
	strStartTime = StartTime.Format("%Y-%m-%d %H:%M:%S");//设置开始时间
	strEndTime = EndTime.Format("%Y-%m-%d %H:%M:%S");//设置结束时间

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

		// 家族名称
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyName, CEnumCore::TagFormat::TLV_STRING,
			strFamilyName.GetLength(), (unsigned char *)(LPCTSTR)strFamilyName);

		// 家族ID.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyID, CEnumCore::TagFormat::TLV_STRING,
			strFamilyID.GetLength(), (unsigned char *)(LPCTSTR)strFamilyID);

		// 开始页.
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,
			strPageIndex.GetLength(), (unsigned char *)(LPCTSTR)strPageIndex);

		// 每页记录数.
		socketdata.AddTFLV(CEnumCore::TagName::PageSize, CEnumCore::TagFormat::TLV_INTEGER,
			m_strPageSize.GetLength(), (unsigned char *)(LPCTSTR)m_strPageSize);

		socketdata.AddTFLV(CEnumCore::TagName::SDO_BeginTime,CEnumCore::TagFormat::TLV_STRING,
			strStartTime.GetLength(),(unsigned char *)(LPCTSTR)strStartTime);//开始时间

		socketdata.AddTFLV(CEnumCore::TagName::SDO_EndTime,CEnumCore::TagFormat::TLV_STRING,
			strEndTime.GetLength(),(unsigned char *)(LPCTSTR)strEndTime);//结束时间

		int nDataLen = socketdata.EnBody();
		theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, CEnumCore::ServiceKey::SDO_Family_CONSUME_QUERY);

		EnableWindow(FALSE);
	}
	catch(...)
	{
	}
}

void CSDOPurchaseInfo::OnLvnColumnclickListPurchaseInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listFamilyPurchase,pNMHDR,pResult);
	*pResult = 0;
}
void CSDOPurchaseInfo::OnCbnSelchangeCmbPurchaseInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbFamilyPurchase);
	QueryPurchase(strPageIndex);
}

BOOL CSDOPurchaseInfo::PreTranslateMessage(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == m_listFamilyInfo.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listFamilyInfo);				
				}
				if(pMsg->hwnd == m_listFamilyPurchase.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listFamilyPurchase);				
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == m_listFamilyInfo.m_hWnd)
				{
					for(int i=0; i<m_listFamilyInfo.GetItemCount(); i++)
					{
						m_listFamilyInfo.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						m_listFamilyInfo.EnsureVisible(i,false);
					}
				}
				if(pMsg->hwnd == m_listFamilyPurchase.m_hWnd)
				{
					for(int i=0; i<m_listFamilyPurchase.GetItemCount(); i++)
					{
						m_listFamilyPurchase.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						m_listFamilyPurchase.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}
