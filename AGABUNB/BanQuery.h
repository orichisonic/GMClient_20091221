#pragma once
#include "afxwin.h"
#include <list>
#include <iostream>
#include "afxcmn.h"
#include "afxdtctl.h"

typedef struct _GAME_DB_SERVER_NEW
{
	int nGameID;
	CString strDBServerIP;
	CString strDBServerName;
	_GAME_DB_SERVER_NEW* lpNext;
	_GAME_DB_SERVER_NEW()
	{
		nGameID = -1;
		lpNext = NULL;
	}
} GAME_DB_SERVER_NEW, *LPGAME_DB_SERVER_NEW;

typedef struct _GAME_INFO_NEW
{
	int nGameID;
	LPGAME_DB_SERVER_NEW lplistDBServer;
	_GAME_INFO_NEW()
	{
		nGameID = -1;
		lplistDBServer = NULL;
	}
} GAME_INFO_NEW, *LPGAME_INFO_NEW;

// CBanQuery dialog

class CBanQuery : public CDialog
{
	DECLARE_DYNAMIC(CBanQuery)

public:
	CBanQuery(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBanQuery();

	// Dialog Data
	enum { IDD = IDD_SHOWVIEW };

	void SetRecvData(CSocketData &socketdata,  CEnumCore::Message_Tag_ID eMsgTagID);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelChangeGameName();
	afx_msg void OnCbnSelChangePage();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedImplement();
   virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//maple add
	afx_msg void OnBnClickBanTimeOption();

	DECLARE_MESSAGE_MAP()

	// Attribute.
private:
	CEdit m_editPlayerAccount;	// Player's account.
	CEdit m_editPlayerNickName;	// Player's nick name.

	CComboBox m_cmbGameName;	// List all game name.
	CComboBox m_cmbGameServerIp;// List one game's server ip.

	CTabCtrl m_tabCtrl;			// Tab ctrl.
	int m_nTabCtrlSelectItem;	// Current Select tab ctrl item.

	int m_listColumnNum;
	CListCtrl m_listAccountInfo;// List Account information.

	CButton m_chkBtnUnbanTimeOption;	// Unban time Option.
	CDateTimeCtrl m_timeCtrlUnBanDate;
	CDateTimeCtrl m_timeCtrlUnBanTime;	// Unban time.
	CDateTimeCtrl m_timeCtrlBanDate;
	CDateTimeCtrl m_timeCtrlBanTime;	// Ban time.



	CEdit m_editReason;	// UnBan/Ban reason.

	// Operation.
private:
	void SetGameDBServerComboBox(LPGAME_INFO_NEW lpgi);

	void InitTabCtrl();
	void LayoutChildWnd();

	void QueryGameName();
	void QueryGameServerIp(int nGameID, int nGameDBID);

	void BanAccount();
	void UnBanAccount();
	void SetBanTime();
	void SetUnBanTime();

	void ClearGameNameCombBoxAssociateData();
	void ClearGameDBServerCombBoxAssociateData();

public:
	CDateTimeCtrl dtcBeginTime;
	CDateTimeCtrl dtcEndTime;
	CComboBox cmbPage;
	// ≈–∂œ «∑Ò–Ë“™∑≠“≥
	bool pageInfo;
};
extern LPCTSTR INI_ERROR_PROMPT_SECTION;