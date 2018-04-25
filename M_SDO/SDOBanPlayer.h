#pragma once
#include "SDOBaseDlg.h"

class CSDOBanPlayer : public CSDOBaseDlg
{
public:
	CSDOBanPlayer(CWnd* pParent = NULL);
	~CSDOBanPlayer(void);

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
	afx_msg void OnLvnColumnclickListBanPlayer(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuCmdBanPlayer();
	afx_msg void OnMenuCmdUnBanPlayer();
	afx_msg void OnCbnSelchangeCmbBanPlayer();
	afx_msg void OnNMRclickListBanPlayer(NMHDR *pNMHDR, LRESULT *pResult);

private:

	// Control ID.
	enum ECtrlID
	{
		CID_CHAR_ITEM_MNR = 22100,

		// ��ѯ�ʺŵĽ�ɫ.
		IDC_LIST_ACCOUNT_INFO,
		IDC_CMB_PAGE_ACCOUNT_INFO,

		//��ͣ����ʺ�
		IDC_STATIC_ACCOUNT,
		IDC_EDIT_ACCOUNT,
		IDC_STATIC_REASON,
		IDC_EDIT_REASON,

		//��ͣ�ʺ��б�
		IDC_LIST_BANPLAYER,
		IDC_CMB_PAGE_BANPLAYER,

		//�������ʺ�

		//���ʺ��Ƿ񱻷�ͣ
		IDC_STATIC_ACCOUNT1,
		IDC_EDIT_ACCOUNT1,
		IDC_BTN_QUERY,

	};

	// Menu ID.
	enum EMenuID
	{
		IDM_QUERY_ACCOUNT_CHAR = 34100,
        IDM_BANPLAYER,
		IDM_UNBANPLAYER,
		IDM_ITEM_COUNT
	};

	// Tab item index.
	enum ETabItemIndex
	{
		TII_QUERY_ACCOUNT = 0,		// ��ѯ�ʺŵĽ�ɫ.
		TII_BANPLAYER,
		TII_QUERY_BANPLAYER,
		TII_UNBANPLAYER,
		TII_QUERY_ACCOUNTSTATUS, //��ѯ���ʺ��Ƿ񱻷�ͣ
		TII_ITEM_COUNT
	};
	enum{TAB_ITEM_CTRL_MAX_NUM = 6};//ͬtab��ǩ���������ؼ���.

	// Control.
private:
	
	// ��ѯ�ʺŵĽ�ɫ.
	CListCtrl	m_listAccountInfo;
	CMenu		m_menuAccount;
	CComboBox	m_cmbAccountInfoPage;

	//��ͣ����ʺ�
	CStatic		m_staticAccount;
	CEdit		m_editAccount;
	CStatic		m_staticReason;
	CEdit		m_editReason;

	//��ͣ����б�
	CListCtrl		m_listBanPlayer;
	CMenu			m_menuBanPlayer;
	CComboBox		m_cmbBanPlayer;

	//�������ʺ�

	//��ѯ���ʺ��Ƿ񱻷�ͣ
	CStatic		m_staticAccount1;
	CEdit		m_editAccount1;
	CButton		m_btnQuery;
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void OnBnClickedQuery();
};



