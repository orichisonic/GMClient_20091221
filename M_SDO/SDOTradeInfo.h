#pragma once
#include "SDOBaseDlg.h"

class CSDOTradeInfo : public CSDOBaseDlg
{
public:
	CSDOTradeInfo(CWnd* pParent = NULL);
	~CSDOTradeInfo(void);

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
	afx_msg void OnMenuCmdQueryTrade();
	afx_msg void OnCbnSelchangeCmbTradeInfo();

private:

	// Control ID.
	enum ECtrlID
	{
		CID_CHAR_ITEM_MNR = 22100,

		// 查询帐号的角色.
		IDC_LIST_ACCOUNT_INFO,
		IDC_CMB_PAGE_ACCOUNT_INFO,

		//查询交易信息
		IDC_LIST_TRADE_INFO,
		IDC_CMB_PAGE_TRADE,

	};

	// Menu ID.
	enum EMenuID
	{
		IDM_QUERY_ACCOUNT_CHAR = 34100,
		IDM_QUERY_TRADE,

		IDM_ITEM_COUNT
	};

	// Tab item index.
	enum ETabItemIndex
	{
		TII_QUERY_ACCOUNT = 0,		// 查询帐号的角色.
		TII_QUERY_TRADE,
		TII_ITEM_COUNT
	};
	enum{TAB_ITEM_CTRL_MAX_NUM = 6};//同tab标签关联的最大控件数.

	// Control.
private:
	
	// 查询帐号的角色.
	CListCtrl	m_listAccountInfo;
	CMenu		m_menuAccount;
	CComboBox	m_cmbAccountInfoPage;

	CListCtrl	m_listTradeInfo;
	CComboBox	m_cmbTradeInfoPage;
public:
	virtual BOOL OnInitDialog();

	//玩家交易信息查询
	void TradeInfo(CEnumCore::ServiceKey eServiceKey);
	void TradeType();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};