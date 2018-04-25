#include "stdafx.h"
#include "M_SDO.h"
#include ".\SDOUserInfo.h"

#include "OperationSDO.h"

static LPCSTR INI_WNDTEXT_SECTION ="MSDO"; //"WNDTEXT";

// Error prompt.
static LPCSTR INI_ERRORPROMPT_SECTION = "ERRORPROMPT";

static LPCSTR INI_MCG2_SECTION = "MSDO";

CSDOUserInfo::CSDOUserInfo(CWnd* pParent/* = NULL*/)
	: CSDOBaseDlg(pParent)
{
}

CSDOUserInfo::~CSDOUserInfo(void)
{
}


/////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CSDOUserInfo, CSDOBaseDlg)
///	ON_COMMAND(IDM_QUERY_REFESH, OnMenuCmdQueryRefresh)
	ON_COMMAND(IDM_QUERY_CHAR_ITEM, OnMenuCmdQueryCharItem)
	ON_COMMAND(IDM_QUERY_CHAR_TEMP_ITEM, OnMenuCmdQueryCharTempItem)
	ON_COMMAND(IDM_QUERY_CHAR_EQUIP, OnMenuCmdQueryCharEquip)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ACCOUNT_INFO, OnNMRclickListAccountInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CHAR_ITEM, OnNMRclickListCharItem)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CHAR_TEMP_ITEM, OnNMRclickListCharTempItem)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CHAR_EQUIP, OnNMRclickListCharEquip)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_ACCOUNT_INFO, OnCbnSelchangeCmbAccountInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_CHAR_ITEM, OnCbnSelchangeCmbCharItem)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_CHAR_TEMP_ITEM, OnCbnSelchangeCmbCharTempItem)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_CHAR_EQUIP, OnCbnSelchangeCmbCharEquip)

	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST_CHAR_TEMP_ITEM,OnLvnColumnclickListchartemp)

END_MESSAGE_MAP()

BOOL CSDOUserInfo::OnInitDialog()
{
	CSDOBaseDlg::OnInitDialog();

	//SetWindowText("角色道具管理");
	
	//OperationSDO operSDO;////maple add
	SetWindowText(theApp.operSDO.ReadValue("MCG2","CG2_UI_CharItemManager"));
	//
	// 初始化列表框及相應的頁所引組合框/菜單.
	//

	// .ini文件中菜單文本字key.
	const char const *pMenuTextKey[] =
	{
		"",								// 查詢帳號的角色信息，不需要菜單.
		"MenuText_QueryCharItem",		// 查詢物品信息.
		"MenuText_QueryCharPet",		// 查詢宠物信息
		"MenuText_QueryCharPetDel",			// 宠物删除信息

	};
	CString strMenuText;

	// 查詢帳號的角色信息列表框.
	CreateCtrlList(m_listAccountInfo, IDC_LIST_ACCOUNT_INFO);

	// 頁索引.
	CreateCtrlComCmb(m_cmbAccountInfoPage, IDC_CMB_PAGE_ACCOUNT_INFO);

	// 列表框m_listAccountInfo的鼠標右鍵菜單(查詢功能).
	m_menuAccountInfoList.CreatePopupMenu();
	for (int i=IDM_QUERY_CHAR_ITEM; i<=IDM_QUERY_CHAR_EQUIP; i++)
	{
		strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[i-IDM_QUERY_ACCOUNT_CHAR]);
		m_menuAccountInfoList.AppendMenu(MF_STRING, i, (LPCTSTR)strMenuText);
	}

	// 查詢物品信息列表框.
	CreateCtrlList(m_listQueryCharItem, IDC_LIST_CHAR_ITEM);

	// 頁索引.
	CreateCtrlComCmb(m_cmbCharItemPage, IDC_CMB_PAGE_CHAR_ITEM);

	// 列表框m_listQueryCharItem的鼠標右鍵菜單(刪除功能).
	m_menuCharItemList.CreatePopupMenu();
	//strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_CHAR_ITEM-IDM_QUERY_ACCOUNT_CHAR]);
	//m_menuCharItemList.AppendMenu(MF_STRING, IDM_QUERY_REFESH, (LPCTSTR)strMenuText);

	// 查询宠物信息列表框.
	CreateCtrlList(m_listQueryCharTempItem, IDC_LIST_CHAR_TEMP_ITEM);

	// 頁索引.
	CreateCtrlComCmb(m_cmbCharTempItemPage, IDC_CMB_PAGE_CHAR_TEMP_ITEM);
	
	// 列表框m_listQueryCharTempItem的鼠標右鍵菜單(刪除功能).
	m_menuCharTempItemList.CreatePopupMenu();

//	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_REFESH-IDM_QUERY_ACCOUNT_CHAR]);
//	m_menuCharTempItemList.AppendMenu(MF_STRING, IDM_QUERY_REFESH, (LPCTSTR)strMenuText);


	// 查询宠物删除信息列表框.
	CreateCtrlList(m_listQueryCharEquip, IDC_LIST_CHAR_EQUIP);

	// 頁索引.
	CreateCtrlComCmb(m_cmbCharEquipPage, IDC_CMB_PAGE_CHAR_EQUIP);

	// 列表框m_listQueryCharEquip的鼠標右鍵菜單(刪除功能).
	m_menuCharEquipList.CreatePopupMenu();

//	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_REFESH-IDM_QUERY_ACCOUNT_CHAR]);
//	m_menuCharEquipList.AppendMenu(MF_STRING, IDM_QUERY_REFESH, (LPCTSTR)strMenuText);


	//
	// 初始化Tab控件.
	//

	// Tab控件标签相关联的控件id，当标签被激活，这些控件将显示.
	DWORD dwTabItemCtrlID[][TAB_ITEM_CTRL_MAX_NUM] = 
	{
		IDC_LIST_ACCOUNT_INFO, IDC_CMB_PAGE_ACCOUNT_INFO, IDOK,IDC_STATICMENUPROMPT,IDC_STATICBASEGRPPAGE,IDD_STATICBASEPAGE,
		IDC_LIST_CHAR_ITEM, IDC_CMB_PAGE_CHAR_ITEM, 0,0,IDC_STATICBASEGRPPAGE,IDD_STATICBASEPAGE,
		IDC_LIST_CHAR_TEMP_ITEM, IDC_CMB_PAGE_CHAR_TEMP_ITEM,0,0,IDC_STATICBASEGRPPAGE,IDD_STATICBASEPAGE,
		IDC_LIST_CHAR_EQUIP, IDC_CMB_PAGE_CHAR_EQUIP, 0,0,IDC_STATICBASEGRPPAGE,IDD_STATICBASEPAGE,
	};

	// Tab控件标签文本在.ini文件中的key.
	const char const *pTabTextKey[] = 
	{
		"UIC_UI_tpgCharacterInfo",//"TabItemText_QueryCharForAccount",
		"UIC_UI_tpgItemInfo",//"TabItemText_QueryCharItem",
		"UIC_UI_tpgPetInfo",//"TabItemText_QueryCharTempItem",
		"UIC_UI_tpgPetDelInfo",//"TabItemText_QueryCharEquip"
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

	return TRUE;
}

void CSDOUserInfo::QueryOperation(int nTabCurSel)//继承BaseDlg
{
	ASSERT(nTabCurSel == TII_QUERY_ACCOUNT);

	ResetCmbCtrl(m_cmbAccountInfoPage);
	ResetCmbCtrl(m_cmbCharItemPage);
	ResetCmbCtrl(m_cmbCharTempItemPage);
	ResetCmbCtrl(m_cmbCharEquipPage);

//	QueryCharsOfAccount(nTabCurSel);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryCharInfo(strPageIndex);
}


void CSDOUserInfo::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//继承BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_CHARACTERINFO_QUERY_RESP://CG2_Account_Query_Resp:			// 查询帐号角色.
		SetDataForListCtrl(m_listAccountInfo, socketData, m_cmbAccountInfoPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_ITEMSHOP_BYOWNER_QUERY_RESP://CG2_ItemCote_Query_Resp:		// 查询物品信息.
		SetDataForListCtrl(m_listQueryCharItem, socketData, m_cmbCharItemPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_PetInfo_Query_RESP://CG2_ItemTemporary_Query_Resp:	// 查询宠物信息.
		SetDataForListCtrl(m_listQueryCharTempItem, socketData, m_cmbCharTempItemPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_PetDrop_Query_RESP://CG2_ItemEquipment_Query_Resp:	// 查询宠物删除信息.
		SetDataForListCtrl(m_listQueryCharEquip, socketData, m_cmbCharEquipPage);
		break;

	default:
		break;
	}
}


// 查询角色物品信息
void CSDOUserInfo::OnMenuCmdQueryCharItem()
{
	//////QueryCharResInfo(CEnumCore::ServiceKey::SDO_ITEMSHOP_BYOWNER_QUERY);
	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbCharItemPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_ITEMSHOP_BYOWNER_QUERY,strPageIndex,m_listAccountInfo);
	SetTabCtrlItemCurSel(TII_QUERY_CHAR_ITEM);
}

//查询角色宠物信息
void CSDOUserInfo::OnMenuCmdQueryCharTempItem()
{
	//////QueryCharResInfo(CEnumCore::ServiceKey::SDO_PetInfo_Query);

	///maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbCharTempItemPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_PetInfo_Query, strPageIndex, m_listAccountInfo);
	SetTabCtrlItemCurSel(TII_QUERY_CHAR_TEMP_ITEM);
}

//查询角色宠物删除信息
void CSDOUserInfo::OnMenuCmdQueryCharEquip()
{
	/////QueryCharResInfo(CEnumCore::ServiceKey::SDO_PetDrop_Query);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbCharEquipPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_PetDrop_Query,strPageIndex,m_listAccountInfo);
	SetTabCtrlItemCurSel(TII_QUERY_CHAR_EQUIP);
}

void CSDOUserInfo::OnMenuCmdDelCharItem()
{

}

void CSDOUserInfo::OnMenuCmdDelCharTempItem()
{

}

void CSDOUserInfo::OnMenuCmdDelCharEquip()
{

}

// 查询角色物品(道具/装备)信息.
void CSDOUserInfo::QueryCharResInfo(CEnumCore::ServiceKey eServiceKey)
{	
	CComboBox* pComboBox = NULL;
	switch (eServiceKey)
	{
	case CEnumCore::ServiceKey::SDO_ITEMSHOP_BYOWNER_QUERY:
		pComboBox = &m_cmbCharItemPage;
		break;
	case CEnumCore::ServiceKey::SDO_PetInfo_Query:
		pComboBox = &m_cmbCharTempItemPage;
		break;
	case CEnumCore::ServiceKey::SDO_PetDrop_Query:
		pComboBox = &m_cmbCharEquipPage;
		break;
	default:
		ASSERT(FALSE);
		break;
	}

	CString strServerIP = GetGameServerIP();
	CString strAccount = GetDataFromListCtrl(m_listAccountInfo, CEnumCore::TagName::SDO_Account);
	CString strCharID = GetDataFromListCtrl(m_listAccountInfo, CEnumCore::TagName::SDO_UserIndexID);
	CString strPageIndex = GetCmbCurSelText(*pComboBox);

	try
	{
		CSocketData socketdata;	
		socketdata.InitCreate(1, 5);

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

		int nDataLen = socketdata.EnBody();
		theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, eServiceKey);

		EnableWindow(FALSE);
	}
	catch(...)
	{
	}
}


/////////////////////////////////////////////////
// 右击列表框显示操作菜单.

void CSDOUserInfo::OnNMRclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItemActive = (LPNMITEMACTIVATE)pNMHDR;
	if (lpItemActive->iItem < 0)
		return;

	PopupMenuForListCtrlRClick(m_listAccountInfo, m_menuAccountInfoList, lpItemActive->ptAction);
}

void CSDOUserInfo::OnNMRclickListCharItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItemActive = (LPNMITEMACTIVATE)pNMHDR;
	if (lpItemActive->iItem < 0)
		return;

	PopupMenuForListCtrlRClick(m_listQueryCharItem, m_menuCharItemList, lpItemActive->ptAction);
}

void CSDOUserInfo::OnNMRclickListCharTempItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItemActive = (LPNMITEMACTIVATE)pNMHDR;
	if (lpItemActive->iItem < 0)
		return;

	PopupMenuForListCtrlRClick(m_listQueryCharTempItem, m_menuCharTempItemList, lpItemActive->ptAction);
}

void CSDOUserInfo::OnNMRclickListCharEquip(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItemActive = (LPNMITEMACTIVATE)pNMHDR;
	if (lpItemActive->iItem < 0)
		return;

	PopupMenuForListCtrlRClick(m_listQueryCharEquip, m_menuCharEquipList, lpItemActive->ptAction);
}

/////////////////////////////////////////////
// 页组合框

void CSDOUserInfo::OnCbnSelchangeCmbAccountInfo()
{
	///QueryCharsOfAccount(GetTabCtrlItemCurSel());
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryCharInfo(strPageIndex);
}

void CSDOUserInfo::OnCbnSelchangeCmbCharItem()
{
	QueryCharResInfo(CEnumCore::ServiceKey::SDO_ITEMSHOP_BYOWNER_QUERY);
}

void CSDOUserInfo::OnCbnSelchangeCmbCharTempItem()
{
	QueryCharResInfo(CEnumCore::ServiceKey::SDO_PetInfo_Query);
}

void CSDOUserInfo::OnCbnSelchangeCmbCharEquip()
{
	QueryCharResInfo(CEnumCore::ServiceKey::SDO_PetDrop_Query);
}

/////////////////////////////////////////////////////

BOOL CSDOUserInfo::ClearDataForCtrl()//继承BaseDlg
{
	m_menuAccountInfoList.DestroyMenu();
	m_menuCharItemList.DestroyMenu();
	m_menuCharTempItemList.DestroyMenu();
	m_menuCharEquipList.DestroyMenu();

	return TRUE;
}

void CSDOUserInfo::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//继承BaseDlg
{
}

void CSDOUserInfo::ImplementUpdateOperation(int nTabCurSel)//继承BaseDlg
{
}

////处理快捷键响应函数
BOOL CSDOUserInfo::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == m_listQueryCharTempItem.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listQueryCharTempItem);				
				}
				if(pMsg->hwnd == m_listAccountInfo.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listAccountInfo);				
				}
				if(pMsg->hwnd == m_listQueryCharItem.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listQueryCharItem);				
				}
				if(pMsg->hwnd == m_listQueryCharEquip.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listQueryCharEquip);				
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == m_listQueryCharTempItem.m_hWnd)
				{
					for(int i=0; i<m_listQueryCharTempItem.GetItemCount(); i++)
					{
					    m_listQueryCharTempItem.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						m_listQueryCharTempItem.EnsureVisible(i,false);
					}
				}
				if(pMsg->hwnd == m_listAccountInfo.m_hWnd)
				{
					for(int i=0; i<m_listAccountInfo.GetItemCount(); i++)
					{
					    m_listAccountInfo.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						m_listAccountInfo.EnsureVisible(i,false);
					}
				}
				if(pMsg->hwnd == m_listQueryCharItem.m_hWnd)
				{
					for(int i=0; i<m_listQueryCharItem.GetItemCount(); i++)
					{
					    m_listQueryCharItem.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						m_listQueryCharItem.EnsureVisible(i,false);
					}
				}
				if(pMsg->hwnd == m_listQueryCharEquip.m_hWnd)
				{
					for(int i=0; i<m_listQueryCharEquip.GetItemCount(); i++)
					{
					    m_listQueryCharEquip.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						m_listQueryCharEquip.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

void CSDOUserInfo::OnLvnColumnclickListchartemp(NMHDR *pNMHDR,LRESULT *pResult)
{

	theApp.operSDO.SortListInfo(&m_listQueryCharTempItem,pNMHDR,pResult);

	*pResult = 0;
}

