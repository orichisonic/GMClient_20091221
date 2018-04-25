// SDOStatusInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOStatusInfo.h"
#include ".\sdostatusinfo.h"


// CSDOStatusInfo �Ի���
static LPCSTR INI_WNDTEXT_SECTION ="MSDO"; //"WNDTEXT";
CSDOStatusInfo::CSDOStatusInfo(CWnd* pParent /*=NULL*/)
	: CSDOBaseDlg(pParent)
{
}

CSDOStatusInfo::~CSDOStatusInfo()
{
}


BEGIN_MESSAGE_MAP(CSDOStatusInfo, CSDOBaseDlg)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST_ACCOUNT_INFO, OnLvnColumnclickListAccountInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_ACCOUNT_INFO, OnCbnSelchangeCmbAccountInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ACCOUNT_INFO, OnNMRclickListAccountInfo)
	ON_COMMAND(IDM_QUERY_STATUS, OnMenuCmdQueryStatus)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_STATUS, OnCbnSelchangeCmbStatusInfo)
END_MESSAGE_MAP()


// CSDOStatusInfo ��Ϣ�������

BOOL CSDOStatusInfo::OnInitDialog()
{
	CSDOBaseDlg::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(theApp.operSDO.ReadValue("MCG2","UIC_UI_StatusInfo"));

	// .ini�ļ��вˆ��ı���key.
	const char const *pMenuTextKey[] =
	{
		"",								// ��ԃ��̖�Ľ�ɫ��Ϣ������Ҫ�ˆ�.
		"MenuText_QueryStatus",		// ��ԃ״̬��Ϣ.

	};
	CString strMenuText;

	// ��ԃ��̖�Ľ�ɫ��Ϣ�б��.
	CreateCtrlList(m_listAccountInfo, IDC_LIST_ACCOUNT_INFO);

	// �����.
	CreateCtrlComCmb(m_cmbAccountInfoPage, IDC_CMB_PAGE_ACCOUNT_INFO);
	m_menuAccount.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_STATUS-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuAccount.AppendMenu(MF_STRING, IDM_QUERY_STATUS, (LPCTSTR)strMenuText);


	// ��ԃ״̬��Ϣ
	CreateCtrlList(m_listStatusInfo, IDC_LIST_STATUS_INFO);

	// �����.
	CreateCtrlComCmb(m_cmbStatusPage, IDC_CMB_PAGE_STATUS);

	// Tab�ؼ���ǩ������Ŀؼ�id������ǩ�������Щ�ؼ�����ʾ.
	DWORD dwTabItemCtrlID[][TAB_ITEM_CTRL_MAX_NUM] = 
	{
		IDC_LIST_ACCOUNT_INFO, IDC_CMB_PAGE_ACCOUNT_INFO, IDOK,IDC_STATICMENUPROMPT,IDC_STATICBASEGRPPAGE,IDD_STATICBASEPAGE,
		IDC_LIST_STATUS_INFO, IDC_CMB_PAGE_STATUS, IDC_STATICBASEGRPPAGE,IDD_STATICBASEPAGE,0,0,
	};

	// Tab�ؼ���ǩ�ı���.ini�ļ��е�key.
	const char const *pTabTextKey[] = 
	{
		"UIC_UI_tpgCharacterInfo",
		"UIC_UI_tpgStatusInfo",
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

void CSDOStatusInfo::QueryOperation(int nTabCurSel)//�̳�BaseDlg
{
	ASSERT(nTabCurSel == TII_QUERY_ACCOUNT);

	ResetCmbCtrl(m_cmbAccountInfoPage);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryCharInfo(strPageIndex);
}


void CSDOStatusInfo::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//�̳�BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_CHARACTERINFO_QUERY_RESP:			// ��ѯ��ɫ��Ϣ
		SetDataForListCtrl(m_listAccountInfo, socketData, m_cmbAccountInfoPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_USERLOGIN_STATUS_QUERY_RESP://״̬��Ϣ
		SetDataForListCtrl(m_listStatusInfo, socketData, m_cmbStatusPage);
		break;
	default:
		break;
	}
}

BOOL CSDOStatusInfo::ClearDataForCtrl()//�̳�BaseDlg
{
	m_menuAccount.DestroyMenu();
	return TRUE;
}

void CSDOStatusInfo::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//�̳�BaseDlg
{
}

void CSDOStatusInfo::ImplementUpdateOperation(int nTabCurSel)//�̳�BaseDlg
{
}

void CSDOStatusInfo::OnLvnColumnclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listAccountInfo,pNMHDR,pResult);
	*pResult = 0;
}

void CSDOStatusInfo::OnCbnSelchangeCmbAccountInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryCharInfo(strPageIndex);
}

void CSDOStatusInfo::OnNMRclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItemActive = (LPNMITEMACTIVATE)pNMHDR;
	if (lpItemActive->iItem < 0)
		return;

	PopupMenuForListCtrlRClick(m_listAccountInfo, m_menuAccount, lpItemActive->ptAction);
}

void CSDOStatusInfo::OnMenuCmdQueryStatus()
{
	SetTabCtrlItemCurSel(TII_QUERY_STATUS);
	CString strPageIndex = GetCmbCurSelText(m_cmbStatusPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_USERLOGIN_STATUS_QUERY, strPageIndex, m_listAccountInfo);
}

void CSDOStatusInfo::OnCbnSelchangeCmbStatusInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbStatusPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_USERLOGIN_STATUS_QUERY, strPageIndex, m_listAccountInfo);
}

BOOL CSDOStatusInfo::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == m_listAccountInfo.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listAccountInfo);				
				}
				if(pMsg->hwnd == m_listStatusInfo.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listStatusInfo);				
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
				if(pMsg->hwnd == m_listStatusInfo.m_hWnd)
				{
					for(int i=0; i<m_listStatusInfo.GetItemCount(); i++)
					{
					    m_listStatusInfo.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						m_listStatusInfo.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}
