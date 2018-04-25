// SDORewardItemInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDORewardItemInfo.h"
#include ".\sdorewarditeminfo.h"


// CSDORewardItemInfo 对话框

static LPCSTR INI_WNDTEXT_SECTION ="MSDO"; //"WNDTEXT";
CSDORewardItemInfo::CSDORewardItemInfo(CWnd* pParent /*=NULL*/)
	:  CSDOBaseDlg(pParent)
{
}

CSDORewardItemInfo::~CSDORewardItemInfo()
{
}

BEGIN_MESSAGE_MAP(CSDORewardItemInfo, CSDOBaseDlg)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST_ACCOUNT_INFO, OnLvnColumnclickListAccountInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_ACCOUNT_INFO, OnCbnSelchangeCmbAccountInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ACCOUNT_INFO, OnNMRclickListAccountInfo)
	ON_COMMAND(IDM_QUERY_REWARD, OnMenuCmdQueryReward)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_REWARD, OnCbnSelchangeCmbRewardInfo)
END_MESSAGE_MAP()


// CSDORewardItemInfo 消息处理程序


BOOL CSDORewardItemInfo::OnInitDialog()
{
	CSDOBaseDlg::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(theApp.operSDO.ReadValue("MCG2","UIC_UI_RewardItemInfo"));

	// .ini文件中菜單文本字key.
	const char const *pMenuTextKey[] =
	{
		"",								// 查詢帳號的角色信息，不需要菜單.
		"MenuText_QueryReward",		// 查詢摇摇乐获奖信息

	};
	CString strMenuText;

	// 查詢帳號的角色信息列表框.
	CreateCtrlList(m_listAccountInfo, IDC_LIST_ACCOUNT_INFO);

	// 頁索引.
	CreateCtrlComCmb(m_cmbAccountInfoPage, IDC_CMB_PAGE_ACCOUNT_INFO);
	m_menuAccount.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_REWARD-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuAccount.AppendMenu(MF_STRING, IDM_QUERY_REWARD, (LPCTSTR)strMenuText);


	// 查詢婚姻信息
	CreateCtrlList(m_listRewardInfo, IDC_LIST_REWARD_INFO);

	// 頁索引.
	CreateCtrlComCmb(m_cmbRewardPage, IDC_CMB_PAGE_REWARD);

	// Tab控件标签相关联的控件id，当标签被激活，这些控件将显示.
	DWORD dwTabItemCtrlID[][TAB_ITEM_CTRL_MAX_NUM] = 
	{
		IDC_LIST_ACCOUNT_INFO, IDC_CMB_PAGE_ACCOUNT_INFO, IDOK,IDC_STATICMENUPROMPT,IDC_STATICBASEGRPPAGE,IDD_STATICBASEPAGE,
		IDC_LIST_REWARD_INFO, IDC_CMB_PAGE_REWARD, IDC_STATICBASEGRPPAGE,IDD_STATICBASEPAGE,0,0,
	};

	// Tab控件标签文本在.ini文件中的key.
	const char const *pTabTextKey[] = 
	{
		"UIC_UI_tpgCharacterInfo",
		"UIC_UI_tpgRewardItem",
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

void CSDORewardItemInfo::QueryOperation(int nTabCurSel)//继承BaseDlg
{
	ASSERT(nTabCurSel == TII_QUERY_ACCOUNT);

	ResetCmbCtrl(m_cmbAccountInfoPage);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryCharInfo(strPageIndex);
}


void CSDORewardItemInfo::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//继承BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_CHARACTERINFO_QUERY_RESP:			// 查询角色信息
		SetDataForListCtrl(m_listAccountInfo, socketData, m_cmbAccountInfoPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_RewardItem_QUERY_RESP://
		SetDataForListCtrl(m_listRewardInfo, socketData, m_cmbRewardPage);
		break;
	default:
		break;
	}
}

BOOL CSDORewardItemInfo::ClearDataForCtrl()//继承BaseDlg
{
	m_menuAccount.DestroyMenu();
	return TRUE;
}

void CSDORewardItemInfo::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//继承BaseDlg
{
}

void CSDORewardItemInfo::ImplementUpdateOperation(int nTabCurSel)//继承BaseDlg
{
}

void CSDORewardItemInfo::OnLvnColumnclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listAccountInfo,pNMHDR,pResult);
	*pResult = 0;
}

void CSDORewardItemInfo::OnCbnSelchangeCmbAccountInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	QueryCharInfo(strPageIndex);
}

void CSDORewardItemInfo::OnNMRclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItemActive = (LPNMITEMACTIVATE)pNMHDR;
	if (lpItemActive->iItem < 0)
		return;

	PopupMenuForListCtrlRClick(m_listAccountInfo, m_menuAccount, lpItemActive->ptAction);
}

void CSDORewardItemInfo::OnMenuCmdQueryReward()
{
	SetTabCtrlItemCurSel(TII_QUERY_REWARD);
	CString strPageIndex = GetCmbCurSelText(m_cmbRewardPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_RewardItem_QUERY, strPageIndex, m_listAccountInfo);
}

void CSDORewardItemInfo::OnCbnSelchangeCmbRewardInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbRewardPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_RewardItem_QUERY, strPageIndex, m_listAccountInfo);
}

BOOL CSDORewardItemInfo::PreTranslateMessage(MSG* pMsg)
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
				if(pMsg->hwnd == m_listRewardInfo.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&m_listRewardInfo);				
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
				if(pMsg->hwnd == m_listRewardInfo.m_hWnd)
				{
					for(int i=0; i<m_listRewardInfo.GetItemCount(); i++)
					{
					    m_listRewardInfo.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						m_listRewardInfo.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}
