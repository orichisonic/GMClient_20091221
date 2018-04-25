// SDOShopInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOShopInfo.h"
#include ".\sdoshopinfo.h"


// CSDOShopInfo �Ի���
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


// CSDOShopInfo ��Ϣ�������

// ��ʼ���Ի���

BOOL CSDOShopInfo::OnInitDialog()
{
	CSDOBaseDlg::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(theApp.operSDO.ReadValue("MCG2","UIC_UI_ShopInfo"));

	// .ini�ļ��вˆ��ı���key.
	const char const *pMenuTextKey[] =
	{
		"",								// ��ԃ��̖�Ľ�ɫ��Ϣ������Ҫ�ˆ�.
		"MenuText_QueryShop",		// ��ԃ������Ϣ.

	};
	CString strMenuText;

	// ��ԃ��̖�Ľ�ɫ��Ϣ�б��.
	CreateCtrlList(m_listAccountInfo, IDC_LIST_ACCOUNT_INFO);

	// �����.
	CreateCtrlComCmb(m_cmbAccountInfoPage, IDC_CMB_PAGE_ACCOUNT_INFO);
	m_menuAccount.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_SHOP-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuAccount.AppendMenu(MF_STRING, IDM_QUERY_SHOP, (LPCTSTR)strMenuText);


	// ��ԃ������Ϣ
	CreateCtrlList(m_listShopInfo, IDC_LIST_SHOP_INFO);

	// �����.
	CreateCtrlComCmb(m_cmbShopInfoPage, IDC_CMB_PAGE_SHOP);

	// Tab�ؼ���ǩ������Ŀؼ�id������ǩ�������Щ�ؼ�����ʾ.
	DWORD dwTabItemCtrlID[][TAB_ITEM_CTRL_MAX_NUM] = 
	{
		IDC_LIST_ACCOUNT_INFO, IDC_CMB_PAGE_ACCOUNT_INFO, IDOK,IDC_STATICMENUPROMPT,IDC_STATICBASEGRPPAGE,IDD_STATICBASEPAGE,
		IDC_LIST_SHOP_INFO, IDC_CMB_PAGE_SHOP, IDC_STATICBASEGRPPAGE,IDD_STATICBASEPAGE,0,0,
	};

	// Tab�ؼ���ǩ�ı���.ini�ļ��е�key.
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
	GetDlgItem(IDC_STATICITEM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITITEM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATICBASEBEGIN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DTPBEGIN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATICBASEEND)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DTPEND)->ShowWindow(SW_SHOW);
	ShopType();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSDOShopInfo::QueryOperation(int nTabCurSel)//�̳�BaseDlg
{
	ASSERT(nTabCurSel == TII_QUERY_ACCOUNT);

	ResetCmbCtrl(m_cmbAccountInfoPage);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryCharInfo(strPageIndex);
}


void CSDOShopInfo::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//�̳�BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_CHARACTERINFO_QUERY_RESP:			// ��ѯ��ɫ��Ϣ
		SetDataForListCtrl(m_listAccountInfo, socketData, m_cmbAccountInfoPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_CONSUME_QUERY_RESP:
		SetDataForListCtrl(m_listShopInfo, socketData, m_cmbShopInfoPage);
		break;
	default:
		break;
	}
}

BOOL CSDOShopInfo::ClearDataForCtrl()//�̳�BaseDlg
{
	m_menuAccount.DestroyMenu();
	return TRUE;
}

void CSDOShopInfo::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//�̳�BaseDlg
{
}

void CSDOShopInfo::ImplementUpdateOperation(int nTabCurSel)//�̳�BaseDlg
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

	CString strStartTime = "";//��ʼʱ��
	CString strEndTime = "";//����ʱ��

	CTime curTime = CTime::GetCurrentTime();

	CTime StartTime;
	dtcLoginDate.GetTime(StartTime);//��ȡ��ʼʱ��

	CTime EndTime;
	dtcLogoutDate.GetTime(EndTime);//��ȡ����ʱ��

	if(StartTime >= curTime)//��ʼʱ�䲻�ܴ��ڵ�ǰʱ��
	{
		MessageBox(theApp.operSDO.ReadValue("MSDO","LI_Warn_StartTime"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
		return;
	}

	if(EndTime <= StartTime)//����ʱ�䲻��С�ڿ�ʼʱ��
	{
		MessageBox(theApp.operSDO.ReadValue("MSDO","LI_Warn_TimeSpan"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
		return;
	}
	strStartTime = StartTime.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��
	strEndTime = EndTime.Format("%Y-%m-%d %H:%M:%S");//���ý���ʱ��

	CString strMoney("");
	GetDlgItemText(IDC_CMBTYPE,strMoney);//��������
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

		_itoa(iMoney,strInt,10);///��������
		socketdata.AddTFLV(CEnumCore::TagName::SDO_MoneyType,
			CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����

		//��������
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName, CEnumCore::TagFormat::TLV_STRING, 
			strItem.GetLength(), (unsigned char *)(LPCTSTR)strItem);

		socketdata.AddTFLV(CEnumCore::TagName::SDO_BeginTime,CEnumCore::TagFormat::TLV_STRING,
			strStartTime.GetLength(),(unsigned char *)(LPCTSTR)strStartTime);//��ʼʱ��

		socketdata.AddTFLV(CEnumCore::TagName::SDO_EndTime,CEnumCore::TagFormat::TLV_STRING,
			strEndTime.GetLength(),(unsigned char *)(LPCTSTR)strEndTime);//����ʱ��


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
