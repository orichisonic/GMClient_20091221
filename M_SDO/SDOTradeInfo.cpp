// SDOTradeInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOTradeInfo.h"
#include ".\sdotradeinfo.h"


// CSDOTradeInfo �Ի���
#include "OperationSDO.h"

static LPCSTR INI_WNDTEXT_SECTION ="MSDO"; //"WNDTEXT";

CSDOTradeInfo::CSDOTradeInfo(CWnd* pParent /*=NULL*/)
	: CSDOBaseDlg(pParent)
{
}

CSDOTradeInfo::~CSDOTradeInfo(void)
{
}


BEGIN_MESSAGE_MAP(CSDOTradeInfo, CSDOBaseDlg)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST_ACCOUNT_INFO, OnLvnColumnclickListAccountInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_ACCOUNT_INFO, OnCbnSelchangeCmbAccountInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ACCOUNT_INFO, OnNMRclickListAccountInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_TRADE, OnCbnSelchangeCmbTradeInfo)
	ON_COMMAND(IDM_QUERY_TRADE, OnMenuCmdQueryTrade)
END_MESSAGE_MAP()


// CSDOTradeInfo ��Ϣ�������

// ��ʼ���Ի���

BOOL CSDOTradeInfo::OnInitDialog()
{
	CSDOBaseDlg::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(theApp.operSDO.ReadValue("MCG2","UIC_UI_TradeInfo"));

	// .ini�ļ��вˆ��ı���key.
	const char const *pMenuTextKey[] =
	{
		"",								// ��ԃ��̖�Ľ�ɫ��Ϣ������Ҫ�ˆ�.
		"MenuText_QueryTrade",		// ��ԃ������Ϣ.

	};
	CString strMenuText;

	// ��ԃ��̖�Ľ�ɫ��Ϣ�б��.
	CreateCtrlList(m_listAccountInfo, IDC_LIST_ACCOUNT_INFO);

	// �����.
	CreateCtrlComCmb(m_cmbAccountInfoPage, IDC_CMB_PAGE_ACCOUNT_INFO);
	m_menuAccount.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_TRADE-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuAccount.AppendMenu(MF_STRING, IDM_QUERY_TRADE, (LPCTSTR)strMenuText);


	// ��ԃ������Ϣ
	CreateCtrlList(m_listTradeInfo, IDC_LIST_TRADE_INFO);

	// �����.
	CreateCtrlComCmb(m_cmbTradeInfoPage, IDC_CMB_PAGE_TRADE);

	// Tab�ؼ���ǩ������Ŀؼ�id������ǩ�������Щ�ؼ�����ʾ.
	DWORD dwTabItemCtrlID[][TAB_ITEM_CTRL_MAX_NUM] = 
	{
		IDC_LIST_ACCOUNT_INFO, IDC_CMB_PAGE_ACCOUNT_INFO, IDOK,IDC_STATICMENUPROMPT,IDC_STATICBASEGRPPAGE,IDD_STATICBASEPAGE,
		IDC_LIST_TRADE_INFO, IDC_CMB_PAGE_TRADE, IDC_STATICBASEGRPPAGE,IDD_STATICBASEPAGE,0,0,
	};

	// Tab�ؼ���ǩ�ı���.ini�ļ��е�key.
	const char const *pTabTextKey[] = 
	{
		"UIC_UI_tpgCharacterInfo",
		"UIC_UI_tpgTradeInfo",
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
	GetDlgItem(IDC_STATICTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBTYPE)->ShowWindow(SW_SHOW);
	TradeType();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSDOTradeInfo::QueryOperation(int nTabCurSel)//�̳�BaseDlg
{
	ASSERT(nTabCurSel == TII_QUERY_ACCOUNT);

	ResetCmbCtrl(m_cmbAccountInfoPage);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryCharInfo(strPageIndex);
}


void CSDOTradeInfo::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//�̳�BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_CHARACTERINFO_QUERY_RESP:			// ��ѯ��ɫ��Ϣ
		SetDataForListCtrl(m_listAccountInfo, socketData, m_cmbAccountInfoPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_ITEMSHOP_TRADE_QUERY_RESP://������Ϣ
		SetDataForListCtrl(m_listTradeInfo, socketData, m_cmbTradeInfoPage);
		break;
	default:
		break;
	}
}

BOOL CSDOTradeInfo::ClearDataForCtrl()//�̳�BaseDlg
{
	m_menuAccount.DestroyMenu();
	return TRUE;
}

void CSDOTradeInfo::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//�̳�BaseDlg
{
}

void CSDOTradeInfo::ImplementUpdateOperation(int nTabCurSel)//�̳�BaseDlg
{
}

void CSDOTradeInfo::OnLvnColumnclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listAccountInfo,pNMHDR,pResult);
	*pResult = 0;
}

void CSDOTradeInfo::OnCbnSelchangeCmbAccountInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryCharInfo(strPageIndex);
}

void CSDOTradeInfo::OnMenuCmdQueryTrade()
{
	SetTabCtrlItemCurSel(TII_QUERY_TRADE);
	/*CString strPageIndex = GetCmbCurSelText(m_cmbTradeInfoPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_ITEMSHOP_BYOWNER_QUERY,strPageIndex,m_listAccountInfo);
	*/
	TradeInfo(CEnumCore::ServiceKey::SDO_ITEMSHOP_TRADE_QUERY);
}

void CSDOTradeInfo::TradeInfo(CEnumCore::ServiceKey eServiceKey)
{
	CComboBox* pComboBox = NULL;
	switch (eServiceKey)
	{
	case CEnumCore::ServiceKey::SDO_ITEMSHOP_TRADE_QUERY:
		pComboBox = &m_cmbTradeInfoPage;
		break;
	default:
		ASSERT(FALSE);
		break;
	}

	CString strServerIP = GetGameServerIP();
	CString strAccount = GetDataFromListCtrl(m_listAccountInfo, CEnumCore::TagName::SDO_Account);
	CString strCharID = GetDataFromListCtrl(m_listAccountInfo, CEnumCore::TagName::SDO_UserIndexID);
	CString strPageIndex = GetCmbCurSelText(*pComboBox);

	int TradeType=cmbTradeType.GetCurSel()+1;
	char strInt[10];

	try
	{
		CSocketData socketdata;	
		socketdata.InitCreate(1, 10);

		// ������IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);

		// ����ʺ�.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account, CEnumCore::TagFormat::TLV_STRING,
			strAccount.GetLength(), (unsigned char *)(LPCTSTR)strAccount);

		// ��ɫID.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID, CEnumCore::TagFormat::TLV_STRING,
			strCharID.GetLength(), (unsigned char *)(LPCTSTR)strCharID);

		// ��ʼҳ.
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,
			strPageIndex.GetLength(), (unsigned char *)(LPCTSTR)strPageIndex);

		// ÿҳ��¼��.
		socketdata.AddTFLV(CEnumCore::TagName::PageSize, CEnumCore::TagFormat::TLV_INTEGER,
			m_strPageSize.GetLength(), (unsigned char *)(LPCTSTR)m_strPageSize);

		_itoa(TradeType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Type,
			CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����

		int nDataLen = socketdata.EnBody();
		theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, eServiceKey);

		EnableWindow(FALSE);
	}
	catch(...)
	{
	}
}

//���뽻������
void CSDOTradeInfo::TradeType()
{
	cmbTradeType.ResetContent();
	cmbTradeType.AddString(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"LI_UI_SENDER"));
	cmbTradeType.AddString(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"LI_UI_RECEIVER"));
	cmbTradeType.SetCurSel(0);
}

void CSDOTradeInfo::OnCbnSelchangeCmbTradeInfo()
{
	TradeInfo(CEnumCore::ServiceKey::SDO_ITEMSHOP_TRADE_QUERY);
}

BOOL CSDOTradeInfo::PreTranslateMessage(MSG* pMsg)
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
				if(pMsg->hwnd == m_listTradeInfo.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listTradeInfo);				
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
				if(pMsg->hwnd == m_listTradeInfo.m_hWnd)
				{
					for(int i=0; i<m_listTradeInfo.GetItemCount(); i++)
					{
					    m_listTradeInfo.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						m_listTradeInfo.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

void CSDOTradeInfo::OnNMRclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItemActive = (LPNMITEMACTIVATE)pNMHDR;
	if (lpItemActive->iItem < 0)
		return;

	PopupMenuForListCtrlRClick(m_listAccountInfo, m_menuAccount, lpItemActive->ptAction);
}
