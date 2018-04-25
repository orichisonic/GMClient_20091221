#pragma once
#include "SDOFamilyBaseDlg.h"


// CSDOFamilyInfo 对话框
class CSDOFamilyInfo : public CSDOFamilyBaseDlg
{
public:
	CSDOFamilyInfo(CWnd* pParent = NULL);
	~CSDOFamilyInfo(void);

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
	afx_msg void OnLvnColumnclickListMemberInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCmbMemberInfo();
	afx_msg void OnLvnColumnclickReplyInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCmbReplyInfo();
	afx_msg void OnLvnColumnclickBrandInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCmbBrandInfo();
	afx_msg void OnMenuCmdQueryMember();
	afx_msg void OnMenuCmdQueryReply();
	afx_msg void OnMenuCmdQueryBrand();

private:

	// Control ID.
	enum ECtrlID
	{
		CID_CHAR_ITEM_MNR = 22100,

		// 查询家族基本信息
		IDC_LIST_FAMILY_INFO,
		IDC_CMB_PAGE_FAMILY_INFO,

		//查询家族成员信息
		IDC_LIST_MEMEBER_INFO,
		IDC_CMB_PAGE_MEMBER,

		//查询家族申请中成员信息
		IDC_LIST_REPLY_INFO,
		IDC_CMB_PAGE_REPLY,

		//查询家族徽章信息
		IDC_LIST_BRAND_INFO,
		IDC_CMB_PAGE_BRAND,

	};

	// Menu ID.
	enum EMenuID
	{
		IDM_QUERY_ACCOUNT_CHAR = 34100,
        IDM_QUERY_MEMBER,
		IDM_QUERY_REPLY,
		IDM_QUERY_BRAND,
		IDM_ITEM_COUNT
	};

	// Tab item index.
	enum ETabItemIndex
	{
		TII_QUERY_FAMILY = 0,		// 查询家族信息.
		TII_QUERY_MEMBER,
		TII_QUERY_REPLY,
		TII_QUERY_BRAND,
		TII_ITEM_COUNT
	};
	enum{TAB_ITEM_CTRL_MAX_NUM = 6};//同tab标签关联的最大控件数.

	// Control.
private:
	
	// 查询家族基本信息
	CListCtrl	m_listFamilyInfo;
	CMenu		m_menuFamily;
	CComboBox	m_cmbFamilyPage;

	//查询家族成员信息
	CListCtrl		m_listMemberInfo;
	CComboBox		m_cmbMemberPage;

	//查询家族申请中成员信息
	CListCtrl		m_listReplyInfo;
	CComboBox		m_cmbReplyPage;

	//查询家族徽章信息
	CListCtrl		m_listBrandInfo;
	CComboBox		m_cmbBrandPage;
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
