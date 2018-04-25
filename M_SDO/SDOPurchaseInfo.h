#pragma once
#include "SDOFamilyBaseDlg.h"


// CSDOPurchaseInfo 对话框

class CSDOPurchaseInfo : public CSDOFamilyBaseDlg
{
public:
	CSDOPurchaseInfo(CWnd* pParent = NULL);
	~CSDOPurchaseInfo(void);

	enum{IDD = 12008};////maple update

protected:

	DECLARE_MESSAGE_MAP()

protected:

	void QueryOperation(int nTabCurSel);
	void ImplementUpdateOperation(int nTabCurSel);
	void ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID);
	void OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel);
	BOOL ClearDataForCtrl();

	afx_msg void OnLvnColumnclickListFamilyInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCmbFamilyInfo();
	afx_msg void OnNMRclickListFamilyInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuCmdQueryPurchase();
	afx_msg void OnLvnColumnclickListPurchaseInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCmbPurchaseInfo();

private:

	// Control ID.
	enum ECtrlID
	{
		CID_CHAR_ITEM_MNR = 22100,

		// 查询家族基本信息
		IDC_LIST_FAMILY_INFO,
		IDC_CMB_PAGE_FAMILY_INFO,

		//查询家族购买信息
		IDC_LIST_PURCHASE_INFO,
		IDC_CMB_PAGE_PURCHASE,

	};

	// Menu ID.
	enum EMenuID
	{
		IDM_QUERY_ACCOUNT_CHAR = 34100,
        IDM_QUERY_PURCHASE,
		IDM_ITEM_COUNT
	};

	// Tab item index.
	enum ETabItemIndex
	{
		TII_QUERY_FAMILY = 0,		// 查询家族信息.
		TII_QUERY_PURCHASE,
		TII_ITEM_COUNT
	};
	enum{TAB_ITEM_CTRL_MAX_NUM = 6};//同tab标签关联的最大控件数.

	// Control.
private:
	
	// 查询家族基本信息
	CListCtrl	m_listFamilyInfo;
	CMenu		m_menuFamily;
	CComboBox	m_cmbFamilyPage;

	//查询家族购买信息
	CListCtrl	m_listFamilyPurchase;
	CComboBox	m_cmbFamilyPurchase;
	
public:
	virtual BOOL OnInitDialog();
	//查询购买信息
	void QueryPurchase(CString& curPage);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
