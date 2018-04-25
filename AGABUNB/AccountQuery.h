#pragma once
#include "afxwin.h"
#include <list>
#include <iostream>
#include "afxcmn.h"
#include "afxdtctl.h"

// CAccountDlg dialog
typedef struct _GAME_SERVER_
{
	int nGameID;
	CString strDBServerIP;
	CString strDBServerName;
	_GAME_SERVER_* lpNext;
	_GAME_SERVER_()
	{
		nGameID = -1;
		lpNext = NULL;
	}
} GAME_SERVER, *LPGAME_SERVER;

typedef struct _GAME_
{
	int nGameID;
	LPGAME_SERVER lplistDBServer;
	_GAME_()
	{
		nGameID = -1;
		lplistDBServer = NULL;
	}
} GAME, *LPGAME;

class CAccountQuery : public CDialog
{
	DECLARE_DYNAMIC(CAccountQuery)

public:
	CAccountQuery(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAccountQuery();

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
	  virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
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

	CDateTimeCtrl dtcBeginTime;
	CDateTimeCtrl dtcEndTime;

	CComboBox cmbPage;
	// ≈–∂œ «∑Ò–Ë“™∑≠“≥
	bool pageInfo;
	// Operation.
private:
	void SetGameDBServerComboBox(LPGAME lpgi);

	void InitTabCtrl();
	void LayoutChildWnd();

	void QueryGameName();
	void QueryGameServerIp(int nGameID, int nGameDBID);


	void ClearGameNameCombBoxAssociateData();
	void ClearGameDBServerCombBoxAssociateData();
};

extern LPCTSTR INI_ERROR_PROMPT_SECTION;