#pragma once
#include "SDOBaseDlg.h"

// 角色道具管理类.
class CSDOUserInfo :public CSDOBaseDlg
{
public:
	CSDOUserInfo(CWnd* pParent = NULL);
	~CSDOUserInfo(void);

	virtual BOOL OnInitDialog();

	//enum{IDD = 12108};
	enum{IDD = 12008};////maple update

protected:

	DECLARE_MESSAGE_MAP()


	// Operation.
protected:

	void QueryOperation(int nTabCurSel);
	void ImplementUpdateOperation(int nTabCurSel);
	void ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID);
	void OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel);
////	BOOL IsDataShownInListCtrl(const CEnumCore::TagName eTagName);
	BOOL ClearDataForCtrl();
////	CString GetListCtrlTitle(const CEnumCore::TagName eTagName);

	// 菜单命令函数.
	////afx_msg void OnMenuCmdQueryRefresh();
	afx_msg void OnMenuCmdQueryCharItem();
	afx_msg void OnMenuCmdQueryCharTempItem();
	afx_msg void OnMenuCmdQueryCharEquip();
	afx_msg void OnMenuCmdDelCharItem();
	afx_msg void OnMenuCmdDelCharTempItem();
	afx_msg void OnMenuCmdDelCharEquip();

	// 右击列表框显示操作菜单.
	afx_msg void OnNMRclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickListCharItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickListCharTempItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickListCharEquip(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnCbnSelchangeCmbAccountInfo();
	afx_msg void OnCbnSelchangeCmbCharItem();
	afx_msg void OnCbnSelchangeCmbCharTempItem();
	afx_msg void OnCbnSelchangeCmbCharEquip();
	// Structure.

	afx_msg void OnLvnColumnclickListchartemp(NMHDR *pNMHDR, LRESULT *pResult);////单击列表框头排序
private:

	// Control ID.
	enum ECtrlID
	{
		CID_CHAR_ITEM_MNR = 22100,

		// 查询帐号的角色.
		IDC_LIST_ACCOUNT_INFO,
		IDC_CMB_PAGE_ACCOUNT_INFO,

		// 查询角色道具栏道具.
		IDC_LIST_CHAR_ITEM,
		IDC_CMB_PAGE_CHAR_ITEM,

		// 查询角色临时道具栏道具.
		IDC_LIST_CHAR_TEMP_ITEM,
		IDC_CMB_PAGE_CHAR_TEMP_ITEM,

		// 查询角色随身装备道具.
		IDC_LIST_CHAR_EQUIP,
		IDC_CMB_PAGE_CHAR_EQUIP
	};

	// Menu ID.
	enum EMenuID
	{
		IDM_QUERY_ACCOUNT_CHAR = 34100,

		/////IDM_QUERY_REFESH,
		IDM_QUERY_CHAR_ITEM,
		IDM_QUERY_CHAR_TEMP_ITEM,
		IDM_QUERY_CHAR_EQUIP,
		
		IDM_ITEM_COUNT
	};

	// Tab item index.
	enum ETabItemIndex
	{
		TII_QUERY_ACCOUNT = 0,		// 查询帐号的角色.
		TII_QUERY_CHAR_ITEM,		// 查询角色道具栏道具.
		TII_QUERY_CHAR_TEMP_ITEM,	// 查询角色临时道具栏道具.
		TII_QUERY_CHAR_EQUIP,		// 查询角色随身装备道具.
//		TII_DEL_CHAR_ITEM,			// 删除角色道具栏道具.
//		TII_DEL_CHAR_TEMP_ITEM,		// 删除临时角色道具栏道具.
//		TII_DEL_CHAR_EQUIP,			// 删除随身装备道具.
		TII_ITEM_COUNT
	};
	enum{TAB_ITEM_CTRL_MAX_NUM = 6};//同tab标签关联的最大控件数.

	// Control.
private:
	
	// 查询帐号的角色.
	CListCtrl	m_listAccountInfo;
	CMenu		m_menuAccountInfoList;
	CComboBox	m_cmbAccountInfoPage;

	// 查询物品信息.
	CListCtrl	m_listQueryCharItem;
	CMenu		m_menuCharItemList;
	CComboBox	m_cmbCharItemPage;

	// 查询宠物信息
	CListCtrl	m_listQueryCharTempItem;
	CMenu		m_menuCharTempItemList;
	CComboBox	m_cmbCharTempItemPage;

	// 查询宠物删除信息
	CListCtrl	m_listQueryCharEquip;
	CMenu		m_menuCharEquipList;
	CComboBox	m_cmbCharEquipPage;

	// Operation.
private:

	// 查询角色物品(道具/装备)信息.
	void QueryCharResInfo(CEnumCore::ServiceKey eServiceKey);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);////处理快捷键响应函数


};
