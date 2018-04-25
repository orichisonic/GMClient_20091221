#pragma once
#include "SDOBaseDlg.h"

// ��ɫ���߹�����.
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

	// �˵������.
	////afx_msg void OnMenuCmdQueryRefresh();
	afx_msg void OnMenuCmdQueryCharItem();
	afx_msg void OnMenuCmdQueryCharTempItem();
	afx_msg void OnMenuCmdQueryCharEquip();
	afx_msg void OnMenuCmdDelCharItem();
	afx_msg void OnMenuCmdDelCharTempItem();
	afx_msg void OnMenuCmdDelCharEquip();

	// �һ��б����ʾ�����˵�.
	afx_msg void OnNMRclickListAccountInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickListCharItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickListCharTempItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickListCharEquip(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnCbnSelchangeCmbAccountInfo();
	afx_msg void OnCbnSelchangeCmbCharItem();
	afx_msg void OnCbnSelchangeCmbCharTempItem();
	afx_msg void OnCbnSelchangeCmbCharEquip();
	// Structure.

	afx_msg void OnLvnColumnclickListchartemp(NMHDR *pNMHDR, LRESULT *pResult);////�����б��ͷ����
private:

	// Control ID.
	enum ECtrlID
	{
		CID_CHAR_ITEM_MNR = 22100,

		// ��ѯ�ʺŵĽ�ɫ.
		IDC_LIST_ACCOUNT_INFO,
		IDC_CMB_PAGE_ACCOUNT_INFO,

		// ��ѯ��ɫ����������.
		IDC_LIST_CHAR_ITEM,
		IDC_CMB_PAGE_CHAR_ITEM,

		// ��ѯ��ɫ��ʱ����������.
		IDC_LIST_CHAR_TEMP_ITEM,
		IDC_CMB_PAGE_CHAR_TEMP_ITEM,

		// ��ѯ��ɫ����װ������.
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
		TII_QUERY_ACCOUNT = 0,		// ��ѯ�ʺŵĽ�ɫ.
		TII_QUERY_CHAR_ITEM,		// ��ѯ��ɫ����������.
		TII_QUERY_CHAR_TEMP_ITEM,	// ��ѯ��ɫ��ʱ����������.
		TII_QUERY_CHAR_EQUIP,		// ��ѯ��ɫ����װ������.
//		TII_DEL_CHAR_ITEM,			// ɾ����ɫ����������.
//		TII_DEL_CHAR_TEMP_ITEM,		// ɾ����ʱ��ɫ����������.
//		TII_DEL_CHAR_EQUIP,			// ɾ������װ������.
		TII_ITEM_COUNT
	};
	enum{TAB_ITEM_CTRL_MAX_NUM = 6};//ͬtab��ǩ���������ؼ���.

	// Control.
private:
	
	// ��ѯ�ʺŵĽ�ɫ.
	CListCtrl	m_listAccountInfo;
	CMenu		m_menuAccountInfoList;
	CComboBox	m_cmbAccountInfoPage;

	// ��ѯ��Ʒ��Ϣ.
	CListCtrl	m_listQueryCharItem;
	CMenu		m_menuCharItemList;
	CComboBox	m_cmbCharItemPage;

	// ��ѯ������Ϣ
	CListCtrl	m_listQueryCharTempItem;
	CMenu		m_menuCharTempItemList;
	CComboBox	m_cmbCharTempItemPage;

	// ��ѯ����ɾ����Ϣ
	CListCtrl	m_listQueryCharEquip;
	CMenu		m_menuCharEquipList;
	CComboBox	m_cmbCharEquipPage;

	// Operation.
private:

	// ��ѯ��ɫ��Ʒ(����/װ��)��Ϣ.
	void QueryCharResInfo(CEnumCore::ServiceKey eServiceKey);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);////�����ݼ���Ӧ����


};
