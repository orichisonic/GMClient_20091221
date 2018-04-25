// SDOBanPlayer.cpp : 实现文件
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOBanPlayer.h"
#include ".\sdobanplayer.h"


// CSDOBanPlayer 对话框
static LPCSTR INI_WNDTEXT_SECTION ="MSDO"; //"WNDTEXT";
CSDOBanPlayer::CSDOBanPlayer(CWnd* pParent /*=NULL*/)
	: CSDOBaseDlg(pParent)
{
}

CSDOBanPlayer::~CSDOBanPlayer()
{
}


BEGIN_MESSAGE_MAP(CSDOBanPlayer, CSDOBaseDlg)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST_ACCOUNT_INFO, OnLvnColumnclickListAccountInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_ACCOUNT_INFO, OnCbnSelchangeCmbAccountInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ACCOUNT_INFO, OnNMRclickListAccountInfo)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST_BANPLAYER, OnLvnColumnclickListBanPlayer)
	ON_COMMAND(IDM_BANPLAYER, OnMenuCmdBanPlayer)
	ON_COMMAND(IDM_UNBANPLAYER, OnMenuCmdUnBanPlayer)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_BANPLAYER, OnCbnSelchangeCmbBanPlayer)
	ON_NOTIFY(NM_RCLICK,IDC_LIST_BANPLAYER, OnNMRclickListBanPlayer)
	ON_BN_CLICKED(IDC_BTN_QUERY,OnBnClickedQuery)
END_MESSAGE_MAP()


// CSDOBanPlayer 消息处理程序



BOOL CSDOBanPlayer::OnInitDialog()
{
	CSDOBaseDlg::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(theApp.operSDO.ReadValue("MCG2","UIC_UI_BanPlayer"));

	// .ini文件中菜單文本字key.
	const char const *pMenuTextKey[] =
	{
		"",								// 查詢帳號的角色信息，不需要菜單.
		"MenuText_BanPlayer",		// 封停玩家帐号
		"MenuText_UnBanPlayer",		//解封玩家帐号

	};
	CString strMenuText;

	// 查詢帳號的角色信息列表框.
	CreateCtrlList(m_listAccountInfo, IDC_LIST_ACCOUNT_INFO);

	// 頁索引.
	CreateCtrlComCmb(m_cmbAccountInfoPage, IDC_CMB_PAGE_ACCOUNT_INFO);
	m_menuAccount.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_BANPLAYER-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuAccount.AppendMenu(MF_STRING, IDM_BANPLAYER, (LPCTSTR)strMenuText);


	//封停玩家帐号
	CreateCtrlStatic(m_staticAccount, IDC_STATICBASEREF, IDC_STATIC_ACCOUNT);
	CreateCtrlEdit(m_editAccount, IDC_EDITBASEREF, IDC_EDIT_ACCOUNT);
	CreateCtrlStatic(m_staticReason, IDC_STATIC_ACCOUNT, IDC_STATIC_REASON);
	CreateCtrlEdit(m_editReason, IDC_EDIT_ACCOUNT, IDC_EDIT_REASON);
	MoveImpButton(IDC_EDIT_REASON, IDC_BTNBASEIMP);

	//封停玩家列表
	CreateCtrlList(m_listBanPlayer, IDC_LIST_BANPLAYER);
	CreateCtrlComCmb(m_cmbBanPlayer, IDC_CMB_PAGE_BANPLAYER);
	m_menuBanPlayer.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_UNBANPLAYER-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuBanPlayer.AppendMenu(MF_STRING, IDM_UNBANPLAYER, (LPCTSTR)strMenuText);

	//解封玩家帐号

	//查询此帐号是否被封停
	CreateCtrlStatic(m_staticAccount1, IDC_STATICBASEREF,IDC_STATIC_ACCOUNT1);
	CreateCtrlEdit(m_editAccount1, IDC_EDITBASEREF, IDC_EDIT_ACCOUNT1);
	CreateCtrlButton(m_btnQuery,IDC_EDIT_ACCOUNT1,IDC_BTN_QUERY);

	// Tab控件标签相关联的控件id，当标签被激活，这些控件将显示.
	DWORD dwTabItemCtrlID[][TAB_ITEM_CTRL_MAX_NUM] = 
	{
		{IDC_LIST_ACCOUNT_INFO, IDC_CMB_PAGE_ACCOUNT_INFO, IDOK,IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE, IDC_STATICMENUPROMPT},////
		{IDC_STATIC_ACCOUNT, IDC_EDIT_ACCOUNT, IDC_STATIC_REASON, IDC_EDIT_REASON, IDC_BTNBASEIMP ,0},
		{IDC_LIST_BANPLAYER, IDC_CMB_PAGE_BANPLAYER,IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE, IDC_STATICMENUPROMPT, IDOK},
		{IDC_STATIC_ACCOUNT, IDC_EDIT_ACCOUNT, IDC_STATIC_REASON, IDC_EDIT_REASON, IDC_BTNBASEIMP ,0},
		{IDC_STATIC_ACCOUNT1, IDC_EDIT_ACCOUNT1, IDC_BTN_QUERY, 0,0,0}
	};

	// Tab控件标签文本在.ini文件中的key.
	const char const *pTabTextKey[] = 
	{
		"UIC_UI_tpgCharacterInfo",
		"UIC_UI_tpgBanPlayer",
		"UIC_UI_tpgBanPlayerList",
		"UIC_UI_tpgUnBanPlayer",
		"BU_UI_Tpgquary",
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
		IDC_STATICMENUPROMPT,	"ListCtrlMenuPrompt",
		IDC_STATIC_ACCOUNT,		"UIC_UI_lblAccount",
		IDC_STATIC_REASON,		"BU_UI_reason",
		IDC_STATIC_ACCOUNT1,	"UIC_UI_lblAccount"
	};
	for (int i=0; i<sizeof(cik)/sizeof(CTRLID_INI_KEY); i++)
	{
		CWnd* pWnd = GetDlgItem(cik[i].dwCtrlID);
		ASSERT(pWnd != NULL);
		//pWnd->ShowWindow(SW_SHOW);
		CString strText=theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, CString(cik[i].lpKey));
		pWnd->SetWindowText(strText);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSDOBanPlayer::QueryOperation(int nTabCurSel)//继承BaseDlg
{
	////ASSERT(nTabCurSel == TII_QUERY_ACCOUNT);

	ResetCmbCtrl(m_cmbAccountInfoPage);
	ResetCmbCtrl(m_cmbBanPlayer);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryCharInfo(strPageIndex);
}


void CSDOBanPlayer::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//继承BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_CHARACTERINFO_QUERY_RESP:			// 查询角色信息
		SetDataForListCtrl(m_listAccountInfo, socketData, m_cmbAccountInfoPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_MEMBERBANISHMENT_QUERY_RESP://查询所有停封帐号
		SetDataForListCtrl(m_listBanPlayer, socketData, m_cmbBanPlayer);
		break;
	case CEnumCore::Message_Tag_ID::SDO_ACCOUNT_CLOSE_RESP://封停帐号
	case CEnumCore::Message_Tag_ID::SDO_ACCOUNT_OPEN_RESP://解封帐号
	case CEnumCore::Message_Tag_ID::SDO_MEMBERSTOPSTATUS_QUERY_RESP:
		{
			CGlobalStruct::TFLV tflvErr = socketData.getTLVBynIndex(1);
			if ((unsigned short)tflvErr.m_tagName == CEnumCore::TagName::MESSAGE)
			{
				///////AfxMessageBox("此帐号未被封停!");//(LPTSTR)tflvErr.lpdata);
			}
			else
			{
				AfxMessageBox("此帐号已被封停!");
			}
		}
		break;
	default:
		break;
	}
}

BOOL CSDOBanPlayer::ClearDataForCtrl()//继承BaseDlg
{
	m_menuAccount.DestroyMenu();
	m_menuBanPlayer.DestroyMenu();
	return TRUE;
}

void CSDOBanPlayer::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//继承BaseDlg
{
}

void CSDOBanPlayer::ImplementUpdateOperation(int nTabCurSel)//继承BaseDlg
{
	CEnumCore::ServiceKey eServiceKey=NULL;
	CString strReason("");
	CString strAccount("");
	CString strCharID("");
	switch(nTabCurSel)
	{
	case TII_BANPLAYER:
		{
			strAccount = GetDataFromListCtrl(m_listAccountInfo, CEnumCore::TagName::SDO_Account);
			strCharID = GetDataFromListCtrl(m_listAccountInfo, CEnumCore::TagName::SDO_UserIndexID);
			GetDlgItemText(IDC_EDIT_REASON, strReason);
			eServiceKey = CEnumCore::ServiceKey::SDO_ACCOUNT_CLOSE;
		}
		break;
	case TII_UNBANPLAYER:
		{
			strAccount = GetDataFromListCtrl(m_listBanPlayer, CEnumCore::TagName::SDO_Account);
			////strCharID = GetDataFromListCtrl(m_listBanPlayer, CEnumCore::TagName::SDO_UserIndexID);
			GetDlgItemText(IDC_EDIT_REASON, strReason);
			eServiceKey = CEnumCore::ServiceKey::SDO_ACCOUNT_OPEN;
		}
		break;
	case TII_QUERY_ACCOUNTSTATUS:
		{
			GetDlgItemText(IDC_EDIT_ACCOUNT1, strAccount);
			eServiceKey = CEnumCore::ServiceKey::SDO_MEMBERSTOPSTATUS_QUERY;
		}
		break;
	default:
		break;
	}

	CString strServerIP = GetGameServerIP();
	CString strServerName = GetGameServerName();

	int userbyID = theApp.UserByID;//操作员ID
	char strInt[10];

	try
	{
		CSocketData socketdata;	
		socketdata.InitCreate(1, 6);

		// 服务器IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);

		//服务器名
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName, CEnumCore::TagFormat::TLV_STRING, 
			strServerName.GetLength(), (unsigned char *)(LPCTSTR)strServerName);

		// 玩家帐号.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account, CEnumCore::TagFormat::TLV_STRING,
			strAccount.GetLength(), (unsigned char *)(LPCTSTR)strAccount);

		// 角色ID.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID, CEnumCore::TagFormat::TLV_STRING,
			strCharID.GetLength(), (unsigned char *)(LPCTSTR)strCharID);

		//原因
		socketdata.AddTFLV(CEnumCore::TagName::SDO_REASON,CEnumCore::TagFormat::TLV_STRING,
			strReason.GetLength(),(unsigned char *)(LPCTSTR)strReason);//封停或解封原因

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,
			sizeof(int),(unsigned char *)&strInt);//操作员ID

		int nDataLen = socketdata.EnBody();
		theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, eServiceKey);

		EnableWindow(FALSE);
	}
	catch(...)
	{
	}

}

void CSDOBanPlayer::OnLvnColumnclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listAccountInfo,pNMHDR,pResult);
	*pResult = 0;
}

void CSDOBanPlayer::OnCbnSelchangeCmbAccountInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryCharInfo(strPageIndex);
}

void CSDOBanPlayer::OnNMRclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItemActive = (LPNMITEMACTIVATE)pNMHDR;
	if (lpItemActive->iItem < 0)
		return;

	PopupMenuForListCtrlRClick(m_listAccountInfo, m_menuAccount, lpItemActive->ptAction);
}

void CSDOBanPlayer::OnNMRclickListBanPlayer(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItemActive = (LPNMITEMACTIVATE)pNMHDR;
	if (lpItemActive->iItem < 0)
		return;

	PopupMenuForListCtrlRClick(m_listBanPlayer, m_menuBanPlayer, lpItemActive->ptAction);
}

void CSDOBanPlayer::OnLvnColumnclickListBanPlayer(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listBanPlayer,pNMHDR,pResult);
	*pResult = 0;
}

void CSDOBanPlayer::OnMenuCmdBanPlayer()
{
	SetTabCtrlItemCurSel(TII_BANPLAYER);
	CString strAccount = GetDataFromListCtrl(m_listAccountInfo, CEnumCore::TagName::SDO_Account);
	SetDlgItemText(IDC_EDIT_ACCOUNT, strAccount);
}

void CSDOBanPlayer::OnMenuCmdUnBanPlayer()
{
	SetTabCtrlItemCurSel(TII_UNBANPLAYER);
	CString strAccount = GetDataFromListCtrl(m_listBanPlayer, CEnumCore::TagName::SDO_Account);
	SetDlgItemText(IDC_EDIT_ACCOUNT, strAccount);
}

void CSDOBanPlayer::OnCbnSelchangeCmbBanPlayer()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbBanPlayer);
	QueryCharInfo(strPageIndex);
}

void CSDOBanPlayer::OnBnClickedQuery()
{
	CString strServerIP = GetGameServerIP();
	CString strServerName = GetGameServerName();
	CString strAccount("");
	GetDlgItemText(IDC_EDIT_ACCOUNT1, strAccount);

	try
	{
		CSocketData socketdata;	
		socketdata.InitCreate(1, 6);

		// 服务器IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);

		//服务器名
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName, CEnumCore::TagFormat::TLV_STRING, 
			strServerName.GetLength(), (unsigned char *)(LPCTSTR)strServerName);

		// 玩家帐号.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account, CEnumCore::TagFormat::TLV_STRING,
			strAccount.GetLength(), (unsigned char *)(LPCTSTR)strAccount);

		int nDataLen = socketdata.EnBody();
		theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, CEnumCore::ServiceKey::SDO_MEMBERSTOPSTATUS_QUERY);

		EnableWindow(FALSE);
	}
	catch(...)
	{
	}
}

BOOL CSDOBanPlayer::PreTranslateMessage(MSG* pMsg)
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
				if(pMsg->hwnd == m_listBanPlayer.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listBanPlayer);				
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
				if(pMsg->hwnd == m_listBanPlayer.m_hWnd)
				{
					for(int i=0; i<m_listBanPlayer.GetItemCount(); i++)
					{
					    m_listBanPlayer.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						m_listBanPlayer.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}
