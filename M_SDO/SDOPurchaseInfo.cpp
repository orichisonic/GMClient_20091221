// SDOPurchaseInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOPurchaseInfo.h"
#include ".\sdopurchaseinfo.h"


// CSDOPurchaseInfo �Ի���
#include "OperationSDO.h"

// CSDOFamilyDonate �Ի���
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


// CSDOPurchaseInfo ��Ϣ�������

// ��ʼ���Ի���

BOOL CSDOPurchaseInfo::OnInitDialog()
{
	CSDOFamilyBaseDlg::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"PI_UI_PurchaseInfo"));
	const char const *pMenuTextKey[] =
	{
		"",								// ��ԃ��̖�Ľ�ɫ��Ϣ������Ҫ�ˆ�.
		"MenuText_QueryPurchase",		// ��ѯ���幺����Ϣ
	};
	CString strMenuText;
	//��ѯ���������Ϣ
	CreateCtrlList(m_listFamilyInfo, IDC_LIST_FAMILY_INFO);
	CreateCtrlComCmb(m_cmbFamilyPage, IDC_CMB_PAGE_FAMILY_INFO);

	m_menuFamily.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_PURCHASE-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuFamily.AppendMenu(MF_STRING, IDM_QUERY_PURCHASE, (LPCTSTR)strMenuText);

	//���幺����Ϣ
	CreateCtrlList(m_listFamilyPurchase, IDC_LIST_PURCHASE_INFO);
	CreateCtrlComCmb(m_cmbFamilyPurchase, IDC_CMB_PAGE_PURCHASE);

	DWORD dwTabItemCtrlID[][TAB_ITEM_CTRL_MAX_NUM] = 
	{
		{IDC_LIST_FAMILY_INFO, IDC_CMB_PAGE_FAMILY_INFO, IDOK,IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE, IDC_STATICMENUPROMPT},
		{IDC_LIST_PURCHASE_INFO, IDC_CMB_PAGE_PURCHASE, IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE,0,0},
	};

	// Tab�ؼ���ǩ�ı���.ini�ļ��е�key.
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
	GetDlgItem(IDC_STATICBASEBEGIN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATICBASEEND)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DTPBEGIN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DTPEND)->ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSDOPurchaseInfo::QueryOperation(int nTabCurSel)//�̳�BaseDlg
{
	ASSERT(nTabCurSel == TII_QUERY_FAMILY);

	ResetCmbCtrl(m_cmbFamilyPage);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbFamilyPage);
	QueryFamilyInfo(strPageIndex);
}


void CSDOPurchaseInfo::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//�̳�BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_Family_Info_QUERY_RESP://���������Ϣ
		SetDataForListCtrl(m_listFamilyInfo, socketData, m_cmbFamilyPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_Family_CONSUME_QUERY_RESP:
		SetDataForListCtrl(m_listFamilyPurchase, socketData, m_cmbFamilyPurchase);
		break;
	default:
		break;
	}
}

BOOL CSDOPurchaseInfo::ClearDataForCtrl()//�̳�BaseDlg
{
	m_menuFamily.DestroyMenu();
	return TRUE;
}

void CSDOPurchaseInfo::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//�̳�BaseDlg
{
}

void CSDOPurchaseInfo::ImplementUpdateOperation(int nTabCurSel)//�̳�BaseDlg
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

//��ѯ������Ϣ
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

	CString strStartTime = "";//��ʼʱ��
	CString strEndTime = "";//����ʱ��

	CTime curTime = CTime::GetCurrentTime();

	CTime StartTime;
	dtcLoginDate.GetTime(StartTime);//��ȡ��ʼʱ��

	CTime EndTime;
	dtcLogoutDate.GetTime(EndTime);//��ȡ����ʱ��

	if(StartTime >= curTime)//��ʼʱ�䲻�ܴ��ڵ�ǰʱ��
	{
		MessageBox(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"LI_Warn_StartTime"),theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"Warn"),0);
		return;
	}

	if(EndTime <= StartTime)//����ʱ�䲻��С�ڿ�ʼʱ��
	{
		MessageBox(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"LI_Warn_TimeSpan"),theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"Warn"),0);
		return;
	}
	strStartTime = StartTime.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��
	strEndTime = EndTime.Format("%Y-%m-%d %H:%M:%S");//���ý���ʱ��

	try
	{
		CSocketData socketdata;	
		socketdata.InitCreate(1, 10);

		// ������IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);

		//��������
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName, CEnumCore::TagFormat::TLV_STRING, 
			strServerName.GetLength(), (unsigned char *)(LPCTSTR)strServerName);

		// ��������
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyName, CEnumCore::TagFormat::TLV_STRING,
			strFamilyName.GetLength(), (unsigned char *)(LPCTSTR)strFamilyName);

		// ����ID.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyID, CEnumCore::TagFormat::TLV_STRING,
			strFamilyID.GetLength(), (unsigned char *)(LPCTSTR)strFamilyID);

		// ��ʼҳ.
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,
			strPageIndex.GetLength(), (unsigned char *)(LPCTSTR)strPageIndex);

		// ÿҳ��¼��.
		socketdata.AddTFLV(CEnumCore::TagName::PageSize, CEnumCore::TagFormat::TLV_INTEGER,
			m_strPageSize.GetLength(), (unsigned char *)(LPCTSTR)m_strPageSize);

		socketdata.AddTFLV(CEnumCore::TagName::SDO_BeginTime,CEnumCore::TagFormat::TLV_STRING,
			strStartTime.GetLength(),(unsigned char *)(LPCTSTR)strStartTime);//��ʼʱ��

		socketdata.AddTFLV(CEnumCore::TagName::SDO_EndTime,CEnumCore::TagFormat::TLV_STRING,
			strEndTime.GetLength(),(unsigned char *)(LPCTSTR)strEndTime);//����ʱ��

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
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
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
