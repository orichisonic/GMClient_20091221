// SDOShopInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOShopInfo.h"
#include ".\sdoshopinfo.h"


// CSDOShopInfo 对话框
#include "OperationSDO.h"

static LPCSTR INI_WNDTEXT_SECTION ="MSDO"; //"WNDTEXT";

CSDOShopInfo::CSDOShopInfo(CWnd* pParent /*=NULL*/)
	: CSDOBaseDlg(pParent)
{
}

CSDOShopInfo::~CSDOShopInfo()
{
}


BEGIN_MESSAGE_MAP(CSDOShopInfo, CSDOBaseDlg)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST_ACCOUNT_INFO, OnLvnColumnclickListAccountInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_ACCOUNT_INFO, OnCbnSelchangeCmbAccountInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ACCOUNT_INFO, OnNMRclickListAccountInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_SHOP, OnCbnSelchangeCmbShopInfo)
	ON_COMMAND(IDM_QUERY_SHOP, OnMenuCmdQueryShop)
END_MESSAGE_MAP()


// CSDOShopInfo 消息处理程序

// 初始化对话框

BOOL CSDOShopInfo::OnInitDialog()
{
	CSDOBaseDlg::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(theApp.operSDO.ReadValue("MCG2","UIC_UI_ShopInfo"));

	// .ini文件中菜單文本字key.
	const char const *pMenuTextKey[] =
	{
		"",								// 查詢帳號的角色信息，不需要菜單.
		"MenuText_QueryShop",		// 查詢消费信息.

	};
	CString strMenuText;

	// 查詢帳號的角色信息列表框.
	CreateCtrlList(m_listAccountInfo, IDC_LIST_ACCOUNT_INFO);

	// 頁索引.
	CreateCtrlComCmb(m_cmbAccountInfoPage, IDC_CMB_PAGE_ACCOUNT_INFO);
	m_menuAccount.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_SHOP-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuAccount.AppendMenu(MF_STRING, IDM_QUERY_SHOP, (LPCTSTR)strMenuText);


	// 查詢消费信息
	CreateCtrlList(m_listShopInfo, IDC_LIST_SHOP_INFO);

	// 頁索引.
	CreateCtrlComCmb(m_cmbShopInfoPage, IDC_CMB_PAGE_SHOP);

	// Tab控件标签相关联的控件id，当标签被激活，这些控件将显示.
	DWORD dwTabItemCtrlID[][TAB_ITEM_CTRL_MAX_NUM] = 
	{
		IDC_LIST_ACCOUNT_INFO, IDC_CMB_PAGE_ACCOUNT_INFO, IDOK,IDC_STATICMENUPROMPT,IDC_STATICBASEGRPPAGE,IDD_STATICBASEPAGE,
		IDC_LIST_SHOP_INFO, IDC_CMB_PAGE_SHOP, IDC_STATICBASEGRPPAGE,IDD_STATICBASEPAGE,0,0,
	};

	// Tab控件标签文本在.ini文件中的key.
	const char const *pTabTextKey[] = 
	{
		"UIC_UI_tpgCharacterInfo",
		"UIC_UI_tpgShopInfo",
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
	GetDlgItem(IDC_STATICTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATICITEM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITITEM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATICBASEBEGIN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DTPBEGIN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATICBASEEND)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DTPEND)->ShowWindow(SW_SHOW);
	ShopType();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSDOShopInfo::QueryOperation(int nTabCurSel)//继承BaseDlg
{
	ASSERT(nTabCurSel == TII_QUERY_ACCOUNT);

	ResetCmbCtrl(m_cmbAccountInfoPage);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryCharInfo(strPageIndex);
}


void CSDOShopInfo::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//继承BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_CHARACTERINFO_QUERY_RESP:			// 查询角色信息
		SetDataForListCtrl(m_listAccountInfo, socketData, m_cmbAccountInfoPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_CONSUME_QUERY_RESP:
		SetDataForListCtrl(m_listShopInfo, socketData, m_cmbShopInfoPage);
		break;
	default:
		break;
	}
}

BOOL CSDOShopInfo::ClearDataForCtrl()//继承BaseDlg
{
	m_menuAccount.DestroyMenu();
	return TRUE;
}

void CSDOShopInfo::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//继承BaseDlg
{
}

void CSDOShopInfo::ImplementUpdateOperation(int nTabCurSel)//继承BaseDlg
{
}

void CSDOShopInfo::ShopType()
{
	cmbTradeType.ResetContent();
	cmbTradeType.AddString(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"UIC_UI_MB"));
	cmbTradeType.AddString(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"UIC_UI_GB"));
	cmbTradeType.AddString(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"UIC_UI_Jifen"));
	cmbTradeType.AddString(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"UIC_UI_AllType"));
	cmbTradeType.SetCurSel(0);
}

void CSDOShopInfo::OnLvnColumnclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listAccountInfo,pNMHDR,pResult);
	*pResult = 0;
}

void CSDOShopInfo::OnCbnSelchangeCmbAccountInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryCharInfo(strPageIndex);
}

void CSDOShopInfo::OnMenuCmdQueryShop()
{
	SetTabCtrlItemCurSel(TII_QUERY_SHOP);
	QueryShop(CEnumCore::ServiceKey::SDO_CONSUME_QUERY);
}

void CSDOShopInfo::QueryShop(CEnumCore::ServiceKey eServiceKey)
{
	CComboBox* pComboBox = NULL;
	switch (eServiceKey)
	{
	case CEnumCore::ServiceKey::SDO_CONSUME_QUERY:
		pComboBox = &m_cmbShopInfoPage;
		break;
	default:
		ASSERT(FALSE);
		break;
	}

	CString strServerIP = GetGameServerIP();
	CString strAccount = GetDataFromListCtrl(m_listAccountInfo, CEnumCore::TagName::SDO_Account);
	CString strCharID = GetDataFromListCtrl(m_listAccountInfo, CEnumCore::TagName::SDO_UserIndexID);
	CString strPageIndex = GetCmbCurSelText(*pComboBox);

	CString strStartTime = "";//开始时间
	CString strEndTime = "";//结束时间

	CTime curTime = CTime::GetCurrentTime();

	CTime StartTime;
	dtcLoginDate.GetTime(StartTime);//获取开始时间

	CTime EndTime;
	dtcLogoutDate.GetTime(EndTime);//获取结束时间

	if(StartTime >= curTime)//开始时间不能大于当前时间
	{
		MessageBox(theApp.operSDO.ReadValue("MSDO","LI_Warn_StartTime"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
		return;
	}

	if(EndTime <= StartTime)//结束时间不能小于开始时间
	{
		MessageBox(theApp.operSDO.ReadValue("MSDO","LI_Warn_TimeSpan"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
		return;
	}
	strStartTime = StartTime.Format("%Y-%m-%d %H:%M:%S");//设置开始时间
	strEndTime = EndTime.Format("%Y-%m-%d %H:%M:%S");//设置结束时间

	CString strMoney("");
	GetDlgItemText(IDC_CMBTYPE,strMoney);//货币类型
	int iMoney=0;
	if(strMoney==theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"UIC_UI_MB"))
		iMoney=1;
	else if(strMoney==theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"UIC_UI_GB"))
		iMoney=0;
	else if(strMoney==theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"UIC_UI_Jifen"))
		iMoney=4;
	else if(strMoney==theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"UIC_UI_AllType"))
		iMoney=2;

	CString strItem("");
	GetDlgItemText(IDC_EDITITEM,strItem);
	char strInt[10];

	try
	{
		CSocketData socketdata;	
		socketdata.InitCreate(1, 10);

		// 服务器IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);

		// 玩家帐号.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account, CEnumCore::TagFormat::TLV_STRING,
			strAccount.GetLength(), (unsigned char *)(LPCTSTR)strAccount);

		// 角色ID.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID, CEnumCore::TagFormat::TLV_STRING,
			strCharID.GetLength(), (unsigned char *)(LPCTSTR)strCharID);

		// 开始页.
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,
			strPageIndex.GetLength(), (unsigned char *)(LPCTSTR)strPageIndex);

		// 每页记录数.
		socketdata.AddTFLV(CEnumCore::TagName::PageSize, CEnumCore::TagFormat::TLV_INTEGER,
			m_strPageSize.GetLength(), (unsigned char *)(LPCTSTR)m_strPageSize);

		_itoa(iMoney,strInt,10);///货币类型
		socketdata.AddTFLV(CEnumCore::TagName::SDO_MoneyType,
			CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//类型

		//道具名称
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName, CEnumCore::TagFormat::TLV_STRING, 
			strItem.GetLength(), (unsigned char *)(LPCTSTR)strItem);

		socketdata.AddTFLV(CEnumCore::TagName::SDO_BeginTime,CEnumCore::TagFormat::TLV_STRING,
			strStartTime.GetLength(),(unsigned char *)(LPCTSTR)strStartTime);//开始时间

		socketdata.AddTFLV(CEnumCore::TagName::SDO_EndTime,CEnumCore::TagFormat::TLV_STRING,
			strEndTime.GetLength(),(unsigned char *)(LPCTSTR)strEndTime);//结束时间


		int nDataLen = socketdata.EnBody();
		theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, eServiceKey);

		EnableWindow(FALSE);
	}
	catch(...)
	{
	}
}

void CSDOShopInfo::OnCbnSelchangeCmbShopInfo()
{
	QueryShop(CEnumCore::ServiceKey::SDO_CONSUME_QUERY);
}

BOOL CSDOShopInfo::PreTranslateMessage(MSG* pMsg)
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
				if(pMsg->hwnd == m_listShopInfo.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listShopInfo);				
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
				if(pMsg->hwnd == m_listShopInfo.m_hWnd)
				{
					for(int i=0; i<m_listShopInfo.GetItemCount(); i++)
					{
					    m_listShopInfo.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						m_listShopInfo.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}
void CSDOShopInfo::OnNMRclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItemActive = (LPNMITEMACTIVATE)pNMHDR;
	if (lpItemActive->iItem < 0)
		return;

	PopupMenuForListCtrlRClick(m_listAccountInfo, m_menuAccount, lpItemActive->ptAction);
}
