#pragma once
#include "SDOFamilyBaseDlg.h"


// CSDOFamilyManager 对话框
class CSDOFamilyManager : public CSDOFamilyBaseDlg
{
public:
	CSDOFamilyManager(CWnd* pParent = NULL);
	~CSDOFamilyManager(void);

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
	afx_msg void OnMenuCmdQueryMember();
	afx_msg void OnLvnColumnclickListMemberInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCmbMemberInfo();
	afx_msg void OnNMRclickListMemberInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuCmdDelFamily();
	afx_msg void OnMenuCmdUpdateMember();
	afx_msg void OnMenuCmdQueryBrand();
	afx_msg void OnCbnSelchangeCmbBrandInfo();
	afx_msg void OnMenuCmdAddBrand();
	afx_msg void OnMenuCmdDelBrand();
	afx_msg void OnLvnColumnclickListBrandInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickListBrandInfo(NMHDR *pNMHDR, LRESULT *pResult);

private:

	// Control ID.
	enum ECtrlID
	{
		CID_CHAR_ITEM_MNR = 22100,

		// 查询家族基本信息
		IDC_LIST_FAMILY_INFO,
		IDC_CMB_PAGE_FAMILY_INFO,

		//查询成员信息
		IDC_LIST_MEMBER_INFO,
		IDC_CMB_PAGE_MEMBER,

		//家族成员修改
		IDC_STATIC_FAMILYID,
		IDC_EDIT_FAMILYID,
		IDC_STATIC_FAMILYNAME,
		IDC_EDIT_FAMILYNAME,
		IDC_STATIC_MEMBERTYPE,
		IDC_CMB_MEMBERTYPE,
		
		//家族徽章信息
		IDC_LIST_BRAND_INFO,
		IDC_CMB_PAGE_BRAND,

		//添加徽章
		//IDC_STATIC_FAMILYID,
		//IDC_EDIT_FAMILYID,
		IDC_STATIC_USERID,
		IDC_EDIT_USERID,
		IDC_STATIC_BRANDTYPE,
		IDC_CMB_BRANDTYPE,
		IDC_STATIC_BRANDNUM,
		IDC_EDIT_BRANDNUM,
	};

	// Menu ID.
	enum EMenuID
	{
		IDM_QUERY_ACCOUNT_CHAR = 34100,
        IDM_QUERY_MEMBER,	//查询家族成员信息
		IDM_QUERY_BRAND,	//查询徽章信息
		IDM_DEL_FAMILY,		//删除家族
		IDM_UPDATE_MEMBER,	//修改家族成员
		IDM_ADD_BRAND,		//添加徽章
		IDM_DEL_BRAND,		//删除徽章
		IDM_ITEM_COUNT
	};

	// Tab item index.
	enum ETabItemIndex
	{
		TII_QUERY_FAMILY = 0,		// 查询家族信息.
		TII_QUERY_MEMBER,
		TII_UPDATE_MEMBER,
		TII_QUERY_BRAND,
		TII_ADD_BRAND,
		TII_ITEM_COUNT
	};
	enum{TAB_ITEM_CTRL_MAX_NUM = 9};//同tab标签关联的最大控件数.

	// Control.
private:
	
	// 查询家族基本信息
	CListCtrl	m_listFamilyInfo;
	CMenu		m_menuFamily;
	CComboBox	m_cmbFamilyPage;

	//查询家族成员信息
	CListCtrl	m_listMemberInfo;
	CComboBox	m_cmbMemberPage;
	CMenu		m_menuMember;

	//家族成员修改
	CStatic		m_staticFamilyID;//家族ID
	CEdit		m_editFamilyID;
	CStatic		m_staticFamilyName;
	CEdit		m_editFamilyName;
	CStatic		m_staticMemberType;
	CComboBox	m_cmbMemberType;

	//查询家族徽章信息
	CListCtrl		m_listBrandInfo;
	CComboBox		m_cmbBrandPage;
	CMenu			m_menuBrand;

	//添加家族徽章
	//CStatic		m_staticFamilyID;//家族ID
	//CEdit		m_editFamilyID;
	CStatic		m_staticUserID;//用户ID
	CEdit		m_editUserID;
	CStatic		m_staticBrandType;//徽章类型
	CComboBox	m_cmbBrandType;
	CStatic		m_staticBrandNum;//徽章数量
	CEdit		m_editBrandNum;
public:
	virtual BOOL OnInitDialog();

	void MemberType();
	void BrandType();
};
