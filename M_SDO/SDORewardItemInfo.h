#pragma once
#include "SDOBaseDlg.h"

class CSDORewardItemInfo : public CSDOBaseDlg
{
public:
	CSDORewardItemInfo(CWnd* pParent = NULL);
	~CSDORewardItemInfo(void);

	enum{IDD = 12008};////maple update

protected:

	DECLARE_MESSAGE_MAP()


	// Operation.
protected:

	void QueryOperation(int nTabCurSel);
	void ImplementUpdateOperation(int nTabCurSel);
	void ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID);
	void OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel);
	BOOL ClearDataForCtrl();

	afx_msg void OnLvnColumnclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCmbAccountInfo();
	afx_msg void OnNMRclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuCmdQueryReward();
	afx_msg void OnCbnSelchangeCmbRewardInfo();

private:

	// Control ID.
	enum ECtrlID
	{
		CID_CHAR_ITEM_MNR = 22100,

		// 查询帐号的角色.
		IDC_LIST_ACCOUNT_INFO,
		IDC_CMB_PAGE_ACCOUNT_INFO,

		//查询摇摇乐获奖信息
		IDC_LIST_REWARD_INFO,
		IDC_CMB_PAGE_REWARD,

	};

	// Menu ID.
	enum EMenuID
	{
		IDM_QUERY_ACCOUNT_CHAR = 34100,
		IDM_QUERY_REWARD,

		IDM_ITEM_COUNT
	};

	// Tab item index.
	enum ETabItemIndex
	{
		TII_QUERY_ACCOUNT = 0,		// 查询帐号的角色.
		TII_QUERY_REWARD,
		TII_ITEM_COUNT
	};
	enum{TAB_ITEM_CTRL_MAX_NUM = 6};//同tab标签关联的最大控件数.

	// Control.
private:
	
	// 查询帐号的角色.
	CListCtrl	m_listAccountInfo;
	CMenu		m_menuAccount;
	CComboBox	m_cmbAccountInfoPage;

	CListCtrl	m_listRewardInfo;
	CComboBox	m_cmbRewardPage;
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
