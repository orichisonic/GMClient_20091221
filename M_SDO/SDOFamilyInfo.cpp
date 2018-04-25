// SDOFamilyInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOFamilyInfo.h"
#include ".\sdofamilyinfo.h"


// CSDOFamilyInfo 对话框

static LPCSTR INI_WNDTEXT_SECTION ="MSDO"; //"WNDTEXT";
CSDOFamilyInfo::CSDOFamilyInfo(CWnd* pParent /*=NULL*/)
	: CSDOFamilyBaseDlg(pParent)
{
}

CSDOFamilyInfo::~CSDOFamilyInfo(void)
{
}

BEGIN_MESSAGE_MAP(CSDOFamilyInfo, CSDOFamilyBaseDlg)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST_FAMILY_INFO, OnLvnColumnclickListFamilyInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_FAMILY_INFO, OnCbnSelchangeCmbFamilyInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_FAMILY_INFO, OnNMRclickListFamilyInfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_MEMEBER_INFO, OnLvnColumnclickListMemberInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_MEMBER, OnCbnSelchangeCmbMemberInfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_REPLY_INFO, OnLvnColumnclickReplyInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_REPLY, OnCbnSelchangeCmbReplyInfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_BRAND_INFO, OnLvnColumnclickBrandInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_BRAND, OnCbnSelchangeCmbBrandInfo)
	ON_COMMAND(IDM_QUERY_MEMBER, OnMenuCmdQueryMember)
	ON_COMMAND(IDM_QUERY_REPLY, OnMenuCmdQueryReply)
	ON_COMMAND(IDM_QUERY_BRAND, OnMenuCmdQueryBrand)
END_MESSAGE_MAP()

BOOL CSDOFamilyInfo::OnInitDialog()
{
	CSDOFamilyBaseDlg::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(theApp.operSDO.ReadValue("MCG2","FI_UI_FamilyInfo"));
	// .ini文件中菜單文本字key.
	const char const *pMenuTextKey[] =
	{
		"",								// 查詢帳號的角色信息，不需要菜單.
		"MenuText_QueryMember",		// 查询成员信息
		"MenuText_QueryReply",		//查询申请中成员信息
		"MenuText_QueryBrand",		//申请徽章信息

	};
	CString strMenuText;

	//查询家族基本信息
	CreateCtrlList(m_listFamilyInfo, IDC_LIST_FAMILY_INFO);
	CreateCtrlComCmb(m_cmbFamilyPage, IDC_CMB_PAGE_FAMILY_INFO);

	m_menuFamily.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_MEMBER-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuFamily.AppendMenu(MF_STRING, IDM_QUERY_MEMBER, (LPCTSTR)strMenuText);

	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_REPLY-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuFamily.AppendMenu(MF_STRING, IDM_QUERY_REPLY, (LPCTSTR)strMenuText);

	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_BRAND-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuFamily.AppendMenu(MF_STRING, IDM_QUERY_BRAND, (LPCTSTR)strMenuText);

	//家族成员信息
	CreateCtrlList(m_listMemberInfo, IDC_LIST_MEMEBER_INFO);
	CreateCtrlComCmb(m_cmbMemberPage, IDC_CMB_PAGE_MEMBER);

	//家族申请中成员信息
	CreateCtrlList(m_listReplyInfo, IDC_LIST_REPLY_INFO);
	CreateCtrlComCmb(m_cmbReplyPage, IDC_CMB_PAGE_REPLY);

	//家族徽章信息
	CreateCtrlList(m_listBrandInfo, IDC_LIST_BRAND_INFO);
	CreateCtrlComCmb(m_cmbBrandPage, IDC_CMB_PAGE_BRAND);

	// Tab控件标签相关联的控件id，当标签被激活，这些控件将显示.
	DWORD dwTabItemCtrlID[][TAB_ITEM_CTRL_MAX_NUM] = 
	{
		{IDC_LIST_FAMILY_INFO, IDC_CMB_PAGE_FAMILY_INFO, IDOK,IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE, IDC_STATICMENUPROMPT},
		{IDC_LIST_MEMEBER_INFO, IDC_CMB_PAGE_MEMBER, IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE,0,0},
		{IDC_LIST_REPLY_INFO, IDC_CMB_PAGE_REPLY,IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE,0,0},
		{IDC_LIST_BRAND_INFO, IDC_CMB_PAGE_BRAND,IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE,0,0},
	};

	// Tab控件标签文本在.ini文件中的key.
	const char const *pTabTextKey[] = 
	{
		"FI_UI_tpgBasicInfo",
		"FI_UI_tpgMemberInfo",
		"FI_UI_tpgReplyInfo",
		"FI_UI_tpgBrandInfo",
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

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSDOFamilyInfo::QueryOperation(int nTabCurSel)//继承BaseDlg
{
	ASSERT(nTabCurSel == TII_QUERY_FAMILY);

	ResetCmbCtrl(m_cmbFamilyPage);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbFamilyPage);
	QueryFamilyInfo(strPageIndex);
}


void CSDOFamilyInfo::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//继承BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_Family_Info_QUERY_RESP://家族基本信息
		SetDataForListCtrl(m_listFamilyInfo, socketData, m_cmbFamilyPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_FamilyMember_Query_RESP://家族成员
		SetDataForListCtrl(m_listMemberInfo, socketData, m_cmbMemberPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_FamilyFormal_Query_RESP://申请中成员
		SetDataForListCtrl(m_listReplyInfo, socketData, m_cmbReplyPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_Personal_Emblem_Query_RESP://家族徽章
		SetDataForListCtrl(m_listBrandInfo, socketData, m_cmbBrandPage);
		break;
	default:
		break;
	}
}

BOOL CSDOFamilyInfo::ClearDataForCtrl()//继承BaseDlg
{
	m_menuFamily.DestroyMenu();
	return TRUE;
}

void CSDOFamilyInfo::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//继承BaseDlg
{
}

void CSDOFamilyInfo::ImplementUpdateOperation(int nTabCurSel)//继承BaseDlg
{
}

void CSDOFamilyInfo::OnLvnColumnclickListFamilyInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listFamilyInfo,pNMHDR,pResult);
	*pResult = 0;
}

void CSDOFamilyInfo::OnCbnSelchangeCmbFamilyInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbFamilyPage);
	QueryFamilyInfo(strPageIndex);
}

void CSDOFamilyInfo::OnNMRclickListFamilyInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItemActive = (LPNMITEMACTIVATE)pNMHDR;
	if (lpItemActive->iItem < 0)
		return;

	PopupMenuForListCtrlRClick(m_listFamilyInfo, m_menuFamily, lpItemActive->ptAction);
}

void CSDOFamilyInfo::OnMenuCmdQueryMember()
{
	SetTabCtrlItemCurSel(TII_QUERY_MEMBER);
	CString strPageIndex = GetCmbCurSelText(m_cmbMemberPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_FamilyMember_Query, strPageIndex, m_listFamilyInfo);
}

void CSDOFamilyInfo::OnMenuCmdQueryReply()
{
	SetTabCtrlItemCurSel(TII_QUERY_REPLY);
	CString strPageIndex = GetCmbCurSelText(m_cmbReplyPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_FamilyFormal_Query, strPageIndex, m_listFamilyInfo);
}

void CSDOFamilyInfo::OnMenuCmdQueryBrand()
{
	SetTabCtrlItemCurSel(TII_QUERY_BRAND);
	CString strPageIndex = GetCmbCurSelText(m_cmbBrandPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_Personal_Emblem_Query, strPageIndex, m_listFamilyInfo);
}

void CSDOFamilyInfo::OnLvnColumnclickListMemberInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listMemberInfo,pNMHDR,pResult);
	*pResult = 0;
}

void CSDOFamilyInfo::OnCbnSelchangeCmbMemberInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbMemberPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_FamilyMember_Query, strPageIndex, m_listFamilyInfo);
}

void CSDOFamilyInfo::OnLvnColumnclickReplyInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listReplyInfo,pNMHDR,pResult);
	*pResult = 0;
}

void CSDOFamilyInfo::OnCbnSelchangeCmbReplyInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbReplyPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_FamilyFormal_Query, strPageIndex, m_listFamilyInfo);
}

void CSDOFamilyInfo::OnLvnColumnclickBrandInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listBrandInfo,pNMHDR,pResult);
	*pResult = 0;
}
void CSDOFamilyInfo::OnCbnSelchangeCmbBrandInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbBrandPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_Personal_Emblem_Query, strPageIndex, m_listFamilyInfo);
}



BOOL CSDOFamilyInfo::PreTranslateMessage(MSG* pMsg)
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
				if(pMsg->hwnd == m_listMemberInfo.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listMemberInfo);				
				}
				if(pMsg->hwnd == m_listReplyInfo.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listReplyInfo);				
				}
				if(pMsg->hwnd == m_listBrandInfo.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listBrandInfo);				
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
				if(pMsg->hwnd == m_listMemberInfo.m_hWnd)
				{
					for(int i=0; i<m_listMemberInfo.GetItemCount(); i++)
					{
						m_listMemberInfo.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						m_listMemberInfo.EnsureVisible(i,false);
					}
				}
				if(pMsg->hwnd == m_listReplyInfo.m_hWnd)
				{
					for(int i=0; i<m_listReplyInfo.GetItemCount(); i++)
					{
						m_listReplyInfo.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						m_listReplyInfo.EnsureVisible(i,false);
					}
				}
				if(pMsg->hwnd == m_listBrandInfo.m_hWnd)
				{
					for(int i=0; i<m_listBrandInfo.GetItemCount(); i++)
					{
						m_listBrandInfo.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						m_listBrandInfo.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}
