// SDOBanPlayer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOBanPlayer.h"
#include ".\sdobanplayer.h"


// CSDOBanPlayer �Ի���
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


// CSDOBanPlayer ��Ϣ�������



BOOL CSDOBanPlayer::OnInitDialog()
{
	CSDOBaseDlg::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(theApp.operSDO.ReadValue("MCG2","UIC_UI_BanPlayer"));

	// .ini�ļ��вˆ��ı���key.
	const char const *pMenuTextKey[] =
	{
		"",								// ��ԃ��̖�Ľ�ɫ��Ϣ������Ҫ�ˆ�.
		"MenuText_BanPlayer",		// ��ͣ����ʺ�
		"MenuText_UnBanPlayer",		//�������ʺ�

	};
	CString strMenuText;

	// ��ԃ��̖�Ľ�ɫ��Ϣ�б��.
	CreateCtrlList(m_listAccountInfo, IDC_LIST_ACCOUNT_INFO);

	// �����.
	CreateCtrlComCmb(m_cmbAccountInfoPage, IDC_CMB_PAGE_ACCOUNT_INFO);
	m_menuAccount.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_BANPLAYER-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuAccount.AppendMenu(MF_STRING, IDM_BANPLAYER, (LPCTSTR)strMenuText);


	//��ͣ����ʺ�
	CreateCtrlStatic(m_staticAccount, IDC_STATICBASEREF, IDC_STATIC_ACCOUNT);
	CreateCtrlEdit(m_editAccount, IDC_EDITBASEREF, IDC_EDIT_ACCOUNT);
	CreateCtrlStatic(m_staticReason, IDC_STATIC_ACCOUNT, IDC_STATIC_REASON);
	CreateCtrlEdit(m_editReason, IDC_EDIT_ACCOUNT, IDC_EDIT_REASON);
	MoveImpButton(IDC_EDIT_REASON, IDC_BTNBASEIMP);

	//��ͣ����б�
	CreateCtrlList(m_listBanPlayer, IDC_LIST_BANPLAYER);
	CreateCtrlComCmb(m_cmbBanPlayer, IDC_CMB_PAGE_BANPLAYER);
	m_menuBanPlayer.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_UNBANPLAYER-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuBanPlayer.AppendMenu(MF_STRING, IDM_UNBANPLAYER, (LPCTSTR)strMenuText);

	//�������ʺ�

	//��ѯ���ʺ��Ƿ񱻷�ͣ
	CreateCtrlStatic(m_staticAccount1, IDC_STATICBASEREF,IDC_STATIC_ACCOUNT1);
	CreateCtrlEdit(m_editAccount1, IDC_EDITBASEREF, IDC_EDIT_ACCOUNT1);
	CreateCtrlButton(m_btnQuery,IDC_EDIT_ACCOUNT1,IDC_BTN_QUERY);

	// Tab�ؼ���ǩ������Ŀؼ�id������ǩ�������Щ�ؼ�����ʾ.
	DWORD dwTabItemCtrlID[][TAB_ITEM_CTRL_MAX_NUM] = 
	{
		{IDC_LIST_ACCOUNT_INFO, IDC_CMB_PAGE_ACCOUNT_INFO, IDOK,IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE, IDC_STATICMENUPROMPT},////
		{IDC_STATIC_ACCOUNT, IDC_EDIT_ACCOUNT, IDC_STATIC_REASON, IDC_EDIT_REASON, IDC_BTNBASEIMP ,0},
		{IDC_LIST_BANPLAYER, IDC_CMB_PAGE_BANPLAYER,IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE, IDC_STATICMENUPROMPT, IDOK},
		{IDC_STATIC_ACCOUNT, IDC_EDIT_ACCOUNT, IDC_STATIC_REASON, IDC_EDIT_REASON, IDC_BTNBASEIMP ,0},
		{IDC_STATIC_ACCOUNT1, IDC_EDIT_ACCOUNT1, IDC_BTN_QUERY, 0,0,0}
	};

	// Tab�ؼ���ǩ�ı���.ini�ļ��е�key.
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


	// ���¿ؼ�������ʾ.
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
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSDOBanPlayer::QueryOperation(int nTabCurSel)//�̳�BaseDlg
{
	////ASSERT(nTabCurSel == TII_QUERY_ACCOUNT);

	ResetCmbCtrl(m_cmbAccountInfoPage);
	ResetCmbCtrl(m_cmbBanPlayer);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryCharInfo(strPageIndex);
}


void CSDOBanPlayer::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//�̳�BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_CHARACTERINFO_QUERY_RESP:			// ��ѯ��ɫ��Ϣ
		SetDataForListCtrl(m_listAccountInfo, socketData, m_cmbAccountInfoPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_MEMBERBANISHMENT_QUERY_RESP://��ѯ����ͣ���ʺ�
		SetDataForListCtrl(m_listBanPlayer, socketData, m_cmbBanPlayer);
		break;
	case CEnumCore::Message_Tag_ID::SDO_ACCOUNT_CLOSE_RESP://��ͣ�ʺ�
	case CEnumCore::Message_Tag_ID::SDO_ACCOUNT_OPEN_RESP://����ʺ�
	case CEnumCore::Message_Tag_ID::SDO_MEMBERSTOPSTATUS_QUERY_RESP:
		{
			CGlobalStruct::TFLV tflvErr = socketData.getTLVBynIndex(1);
			if ((unsigned short)tflvErr.m_tagName == CEnumCore::TagName::MESSAGE)
			{
				///////AfxMessageBox("���ʺ�δ����ͣ!");//(LPTSTR)tflvErr.lpdata);
			}
			else
			{
				AfxMessageBox("���ʺ��ѱ���ͣ!");
			}
		}
		break;
	default:
		break;
	}
}

BOOL CSDOBanPlayer::ClearDataForCtrl()//�̳�BaseDlg
{
	m_menuAccount.DestroyMenu();
	m_menuBanPlayer.DestroyMenu();
	return TRUE;
}

void CSDOBanPlayer::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//�̳�BaseDlg
{
}

void CSDOBanPlayer::ImplementUpdateOperation(int nTabCurSel)//�̳�BaseDlg
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

	int userbyID = theApp.UserByID;//����ԱID
	char strInt[10];

	try
	{
		CSocketData socketdata;	
		socketdata.InitCreate(1, 6);

		// ������IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);

		//��������
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName, CEnumCore::TagFormat::TLV_STRING, 
			strServerName.GetLength(), (unsigned char *)(LPCTSTR)strServerName);

		// ����ʺ�.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account, CEnumCore::TagFormat::TLV_STRING,
			strAccount.GetLength(), (unsigned char *)(LPCTSTR)strAccount);

		// ��ɫID.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID, CEnumCore::TagFormat::TLV_STRING,
			strCharID.GetLength(), (unsigned char *)(LPCTSTR)strCharID);

		//ԭ��
		socketdata.AddTFLV(CEnumCore::TagName::SDO_REASON,CEnumCore::TagFormat::TLV_STRING,
			strReason.GetLength(),(unsigned char *)(LPCTSTR)strReason);//��ͣ����ԭ��

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,
			sizeof(int),(unsigned char *)&strInt);//����ԱID

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

		// ������IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);

		//��������
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName, CEnumCore::TagFormat::TLV_STRING, 
			strServerName.GetLength(), (unsigned char *)(LPCTSTR)strServerName);

		// ����ʺ�.
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
