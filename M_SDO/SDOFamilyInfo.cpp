// SDOFamilyInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOFamilyInfo.h"
#include ".\sdofamilyinfo.h"


// CSDOFamilyInfo �Ի���

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(theApp.operSDO.ReadValue("MCG2","FI_UI_FamilyInfo"));
	// .ini�ļ��вˆ��ı���key.
	const char const *pMenuTextKey[] =
	{
		"",								// ��ԃ��̖�Ľ�ɫ��Ϣ������Ҫ�ˆ�.
		"MenuText_QueryMember",		// ��ѯ��Ա��Ϣ
		"MenuText_QueryReply",		//��ѯ�����г�Ա��Ϣ
		"MenuText_QueryBrand",		//���������Ϣ

	};
	CString strMenuText;

	//��ѯ���������Ϣ
	CreateCtrlList(m_listFamilyInfo, IDC_LIST_FAMILY_INFO);
	CreateCtrlComCmb(m_cmbFamilyPage, IDC_CMB_PAGE_FAMILY_INFO);

	m_menuFamily.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_MEMBER-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuFamily.AppendMenu(MF_STRING, IDM_QUERY_MEMBER, (LPCTSTR)strMenuText);

	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_REPLY-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuFamily.AppendMenu(MF_STRING, IDM_QUERY_REPLY, (LPCTSTR)strMenuText);

	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_BRAND-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuFamily.AppendMenu(MF_STRING, IDM_QUERY_BRAND, (LPCTSTR)strMenuText);

	//�����Ա��Ϣ
	CreateCtrlList(m_listMemberInfo, IDC_LIST_MEMEBER_INFO);
	CreateCtrlComCmb(m_cmbMemberPage, IDC_CMB_PAGE_MEMBER);

	//���������г�Ա��Ϣ
	CreateCtrlList(m_listReplyInfo, IDC_LIST_REPLY_INFO);
	CreateCtrlComCmb(m_cmbReplyPage, IDC_CMB_PAGE_REPLY);

	//���������Ϣ
	CreateCtrlList(m_listBrandInfo, IDC_LIST_BRAND_INFO);
	CreateCtrlComCmb(m_cmbBrandPage, IDC_CMB_PAGE_BRAND);

	// Tab�ؼ���ǩ������Ŀؼ�id������ǩ�������Щ�ؼ�����ʾ.
	DWORD dwTabItemCtrlID[][TAB_ITEM_CTRL_MAX_NUM] = 
	{
		{IDC_LIST_FAMILY_INFO, IDC_CMB_PAGE_FAMILY_INFO, IDOK,IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE, IDC_STATICMENUPROMPT},
		{IDC_LIST_MEMEBER_INFO, IDC_CMB_PAGE_MEMBER, IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE,0,0},
		{IDC_LIST_REPLY_INFO, IDC_CMB_PAGE_REPLY,IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE,0,0},
		{IDC_LIST_BRAND_INFO, IDC_CMB_PAGE_BRAND,IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE,0,0},
	};

	// Tab�ؼ���ǩ�ı���.ini�ļ��е�key.
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


	// ���¿ؼ�������ʾ.
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSDOFamilyInfo::QueryOperation(int nTabCurSel)//�̳�BaseDlg
{
	ASSERT(nTabCurSel == TII_QUERY_FAMILY);

	ResetCmbCtrl(m_cmbFamilyPage);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbFamilyPage);
	QueryFamilyInfo(strPageIndex);
}


void CSDOFamilyInfo::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//�̳�BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_Family_Info_QUERY_RESP://���������Ϣ
		SetDataForListCtrl(m_listFamilyInfo, socketData, m_cmbFamilyPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_FamilyMember_Query_RESP://�����Ա
		SetDataForListCtrl(m_listMemberInfo, socketData, m_cmbMemberPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_FamilyFormal_Query_RESP://�����г�Ա
		SetDataForListCtrl(m_listReplyInfo, socketData, m_cmbReplyPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_Personal_Emblem_Query_RESP://�������
		SetDataForListCtrl(m_listBrandInfo, socketData, m_cmbBrandPage);
		break;
	default:
		break;
	}
}

BOOL CSDOFamilyInfo::ClearDataForCtrl()//�̳�BaseDlg
{
	m_menuFamily.DestroyMenu();
	return TRUE;
}

void CSDOFamilyInfo::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//�̳�BaseDlg
{
}

void CSDOFamilyInfo::ImplementUpdateOperation(int nTabCurSel)//�̳�BaseDlg
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
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
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
