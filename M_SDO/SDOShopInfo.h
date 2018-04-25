#pragma once
#include "SDOBaseDlg.h"

class CSDOShopInfo : public CSDOBaseDlg
{
public:
	CSDOShopInfo(CWnd* pParent = NULL);
	~CSDOShopInfo(void);

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
	afx_msg void OnMenuCmdQueryShop();
	afx_msg void OnCbnSelchangeCmbShopInfo();

private:

	// Control ID.
	enum ECtrlID
	{
		CID_CHAR_ITEM_MNR = 22100,

		// ��ѯ�ʺŵĽ�ɫ.
		IDC_LIST_ACCOUNT_INFO,
		IDC_CMB_PAGE_ACCOUNT_INFO,

		//��ѯ������Ϣ
		IDC_LIST_SHOP_INFO,
		IDC_CMB_PAGE_SHOP,

	};

	// Menu ID.
	enum EMenuID
	{
		IDM_QUERY_ACCOUNT_CHAR = 34100,
		IDM_QUERY_SHOP,

		IDM_ITEM_COUNT
	};

	// Tab item index.
	enum ETabItemIndex
	{
		TII_QUERY_ACCOUNT = 0,		// ��ѯ�ʺŵĽ�ɫ.
		TII_QUERY_SHOP,
		TII_ITEM_COUNT
	};
	enum{TAB_ITEM_CTRL_MAX_NUM = 6};//ͬtab��ǩ���������ؼ���.

	// Control.
private:
	
	// ��ѯ�ʺŵĽ�ɫ.
	CListCtrl	m_listAccountInfo;
	CMenu		m_menuAccount;
	CComboBox	m_cmbAccountInfoPage;

	CListCtrl	m_listShopInfo;
	CComboBox	m_cmbShopInfoPage;
public:
	virtual BOOL OnInitDialog();

	void ShopType();
	//��ѯ������Ϣ
	void QueryShop(CEnumCore::ServiceKey eServiceKey);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};



