#pragma once
#include "SDOBaseDlg.h"

class CSDOKickPlayer : public CSDOBaseDlg
{
public:
	CSDOKickPlayer(CWnd* pParent = NULL);
	~CSDOKickPlayer(void);

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
	afx_msg void OnMenuCmdKickPlayer();

private:

	// Control ID.
	enum ECtrlID
	{
		CID_CHAR_ITEM_MNR = 22100,

		// ��ѯ�ʺŵĽ�ɫ.
		IDC_LIST_ACCOUNT_INFO,
		IDC_CMB_PAGE_ACCOUNT_INFO,

	};

	// Menu ID.
	enum EMenuID
	{
		IDM_QUERY_ACCOUNT_CHAR = 34100,
        IDM_KICKPLAYER,
		IDM_ITEM_COUNT
	};

	// Tab item index.
	enum ETabItemIndex
	{
		TII_QUERY_ACCOUNT = 0,		// ��ѯ�ʺŵĽ�ɫ.
		TII_ITEM_COUNT
	};
	enum{TAB_ITEM_CTRL_MAX_NUM = 3};//ͬtab��ǩ���������ؼ���.

	// Control.
private:
	
	// ��ѯ�ʺŵĽ�ɫ.
	CListCtrl	m_listAccountInfo;
	CMenu		m_menuAccount;
	CComboBox	m_cmbAccountInfoPage;

public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


