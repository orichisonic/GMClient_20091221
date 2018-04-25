// SDOAccountInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOAccountInfo.h"
#include ".\sdoaccountinfo.h"


// CSDOAccountInfo �Ի���
#include "OperationSDO.h"

static LPCSTR INI_WNDTEXT_SECTION ="MSDO"; //"WNDTEXT";

// Error prompt.
static LPCSTR INI_ERRORPROMPT_SECTION = "ERRORPROMPT";

static LPCSTR INI_MCG2_SECTION = "MSDO";


CSDOAccountInfo::CSDOAccountInfo(CWnd* pParent /*=NULL*/)
	: CSDOBaseDlg(pParent)
{
}

CSDOAccountInfo::~CSDOAccountInfo(void)
{
}




BEGIN_MESSAGE_MAP(CSDOAccountInfo, CSDOBaseDlg)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST_ACCOUNT_INFO, OnLvnColumnclickListAccountInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_ACCOUNT_INFO, OnCbnSelchangeCmbAccountInfo)
END_MESSAGE_MAP()



BOOL CSDOAccountInfo::OnInitDialog()
{
	CSDOBaseDlg::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"UIC_UI_AccountInfo"));

	// ��ԃ��̖�Ľ�ɫ��Ϣ�б��.
	CreateCtrlList(m_listAccountInfo, IDC_LIST_ACCOUNT_INFO);

	// �����.
	CreateCtrlComCmb(m_cmbAccountInfoPage, IDC_CMB_PAGE_ACCOUNT_INFO);

	// Tab�ؼ���ǩ������Ŀؼ�id������ǩ�������Щ�ؼ�����ʾ.
	DWORD dwTabItemCtrlID[][TAB_ITEM_CTRL_MAX_NUM] = 
	{
		IDC_LIST_ACCOUNT_INFO, IDC_CMB_PAGE_ACCOUNT_INFO, IDOK,

	};

	// Tab�ؼ���ǩ�ı���.ini�ļ��е�key.
	const char const *pTabTextKey[] = 
	{
		"UIC_UI_tpgAccountInfo",
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
		pWnd->ShowWindow(SW_SHOW);
		CString strText=theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, CString(cik[i].lpKey));
		pWnd->SetWindowText(strText);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSDOAccountInfo::QueryOperation(int nTabCurSel)//�̳�BaseDlg
{
	ASSERT(nTabCurSel == TII_QUERY_ACCOUNT);

	ResetCmbCtrl(m_cmbAccountInfoPage);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	//QueryOtherInfo(CEnumCore::ServiceKey::SDO_ACCOUNT_QUERY,strPageIndex,m_listAccountInfo);
	QueryAccount(strPageIndex);
}
//��ѯ����ʺ���Ϣ
void CSDOAccountInfo::QueryAccount(CString& curPage)
{
	CString strServerIP = GetGameServerIP();
	CString strServerName = GetGameServerName();
	CString strAccount = GetAccount();
	CString strNick = GetNick();
	CString strPageIndex = curPage;

	if (strAccount.IsEmpty() && strNick.IsEmpty())
	{
		CString strError = theApp.operSDO.ReadValue(INI_ERRORPROMPT_SECTION, "AccountOrNickInput");
		AfxMessageBox(strError);
		return;
	}


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

		//����ʺ�.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account, CEnumCore::TagFormat::TLV_STRING,
			strAccount.GetLength(), (unsigned char *)(LPCTSTR)strAccount);

		//����ǳ�.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName, CEnumCore::TagFormat::TLV_STRING, 
			strNick.GetLength(), (unsigned char *)(LPCTSTR)strNick);

		// ��ʼҳ.
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,
			strPageIndex.GetLength(), (unsigned char *)(LPCTSTR)strPageIndex);

		// ÿҳ��¼��.
		socketdata.AddTFLV(CEnumCore::TagName::PageSize, CEnumCore::TagFormat::TLV_INTEGER,
			m_strPageSize.GetLength(), (unsigned char *)(LPCTSTR)m_strPageSize);

		int nDataLen = socketdata.EnBody();
		//m_operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, CEnumCore::ServiceKey::CG2_Account_Query);
		theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, CEnumCore::ServiceKey::SDO_ACCOUNT_QUERY);

		EnableWindow(FALSE);
	}
	catch(...)
	{
	}
}


void CSDOAccountInfo::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//�̳�BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_ACCOUNT_QUERY_RESP://CG2_Account_Query_Resp:			// ��ѯ�ʺŽ�ɫ.
		SetDataForListCtrl(m_listAccountInfo, socketData, m_cmbAccountInfoPage);
		break;
	default:
		break;
	}
}

BOOL CSDOAccountInfo::ClearDataForCtrl()//�̳�BaseDlg
{
	return TRUE;
}

void CSDOAccountInfo::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//�̳�BaseDlg
{
}

void CSDOAccountInfo::ImplementUpdateOperation(int nTabCurSel)//�̳�BaseDlg
{
}

BOOL CSDOAccountInfo::PreTranslateMessage(MSG* pMsg)
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

void CSDOAccountInfo::OnLvnColumnclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listAccountInfo,pNMHDR,pResult);
	*pResult = 0;
}

void CSDOAccountInfo::OnCbnSelchangeCmbAccountInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_ACCOUNT_QUERY,strPageIndex,m_listAccountInfo);
}
