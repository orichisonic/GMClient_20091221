// AccountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataOper.h"
#include "AGABUNB.h"
#include "BanQuery.h"
#include <stack>
#include <iostream>

// Game DB id section in ini file.
LPCTSTR INI_GAME_DB_SECTIONNew = "GAMEDB";
LPCTSTR INI_TAG_NAME_SECTIONNew = "TAGNAME";
LPCTSTR INI_ERROR_PROMPT_SECTIONNew = "ERRORPROMPT";
LPCTSTR INI_UI_TEXT_SECTIONNew = "UITEXT";

#define IDC_BANTIMEHINT 5022

// ID of ctrl with text.
DWORD g_dwCtrlIDWithTextNew[] = 
{
	// Static contrl.
	IDC_STATICUBANTIME,
		IDC_STATICBANTIME,
		IDC_STATICREASON,
		IDC_STATICGAMENAME,
		IDC_STATICPLAYERACCOUNT,
		IDC_STATICPLAYERNICK,
		IDC_STATICPROMPT,

		//maple add
		IDC_BANTIMEHINT,

		// Group ctrl.
		IDC_GRPSEARCH,

		// Button
		IDOK,
		IDC_BTNIMPLEMENT,
};
//////////////////////////////////////

// Column width of list ctrl.
#define LIST_CTRL_COL_WIDTH	160

/////////////////////////////////////////////

///////////////////////////////////////

typedef struct _GAME_OPER_INFO_
{
	UINT uGameID;			// Game ID.
	BOOL bOperByNick;		// FALSE, operation by Account; operation by Nick.
	LPCTSTR lpGameDBIDKey;	// KeyName in the ini-file, the value is GameDBid.
} GAME_OPER_INFO;

// GameName's key int ini file.
GAME_OPER_INFO g_sGameOperInfoNew[] = 
{
	///////////////////////////////////////////////////
	//	GameID		GameDB ID key name.
	//////////////////////////////////////////////////////
	{3,		FALSE,	"SDODB"},		// ��������
	{18,	FALSE,	"FJDB"},		// ���֮��
	{19,	FALSE,	"LIGHTCARDB"},	// ���߷ɳ�
	{22,	FALSE,	"PETFORESTDB"},	// ����ɭ��
	{25,	TRUE,	"CG2DB"},		// ħ������2
	{27,	TRUE,	"BASKETBALLDB"},// ��������
	{31,	FALSE,	"PALDB"},		// �ɽ�online
	{34,	FALSE,	"GTDB"},		// ����ONLINE
	{6,		FALSE,	"AUDB"},		//������
	{35,	FALSE,	"JW2DB"},		// ������II
	{36,	FALSE,	"SDGANDA"}		// SDganda
};

//////////////////////////////////////////

// Tab ctrl item index.
typedef enum
{
	TCII_QUERY_RESULT = 0,
	TCII_BAN_ACCOUNT,
	TCII_UNBAN_ACCOUNT,
	TCII_SET_BAN_TIME,
	TCII_SET_UNBAN_TIME,
	TCII_TAB_ITEM_COUNT=2
} TAB_CTRL_ITEM_INDEX;

// Num of ctrl associate with tab-ctrl-item.
#define MAX_TCN_ASSO_WND	13//12

// Ctrl windows associate with tab ctrl items.
// These ctrl would be shown if according tab-ctrl-item is Selected.
DWORD g_dwTabCtrlIDMapCtrlWndIDNew[][MAX_TCN_ASSO_WND] = 
{
	// TCII_QUERY_RESULT TAB��ǩ: ��ѯ���
	{IDC_LISTACCOUNTINFO, IDOK, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0},
		// TCII_BAN_ACCOUNT TAB��ǩ: ��ͣ�ʺ�
	{
		0,
			IDC_STATICUBANTIME,
			0,
			0,
			IDC_UNBANDATE,
			IDC_UNBANTIME,
			0,
			0,
			IDC_REASON,
			IDC_OPTIONUBANTIME,
			//maple add
			IDC_BANTIMEHINT,
			IDC_BTNIMPLEMENT,
			IDC_STATICREASON,
	},
	// TCII_UNBAN_ACCOUNT TAB��ǩ: ����ʺ�
	{
		0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			IDC_REASON,
			0,
			0,
			IDC_STATICREASON,
			IDC_BTNIMPLEMENT,
	},
	// TCII_SET_BAN_TIME TAB��ǩ: ���÷�ͣʱ��
		{
			0,
				0,
				IDC_STATICUBANTIME,
				IDC_STATICBANTIME,
				IDC_UNBANDATE,
				IDC_UNBANTIME,
				IDC_BANDATE,
				IDC_BANTIME,
				IDC_REASON,
				IDC_OPTIONUBANTIME,
				//maple add
				IDC_BANTIMEHINT,
				IDC_STATICREASON,
				IDC_BTNIMPLEMENT,
		},
		// TCII_SET_UNBAN_TIME TAB��ǩ: ���ý��ͣʱ��
		{
			0,
				0,
				IDC_STATICUBANTIME,
				0,
				IDC_UNBANDATE,
				IDC_UNBANTIME,
				0,
				0,
				IDC_REASON,
				IDC_OPTIONUBANTIME,
				//maple add
				IDC_BANTIMEHINT,
				IDC_STATICREASON,
				IDC_BTNIMPLEMENT,
		}
};

///////////////////////////////////////
// CBanQuery dialog

IMPLEMENT_DYNAMIC(CBanQuery, CDialog)

CBanQuery::CBanQuery(CWnd* pParent /*=NULL*/)
: CDialog(CBanQuery::IDD, pParent)
{
	m_nTabCtrlSelectItem = 0;
	m_listColumnNum = 0;
}

CBanQuery::~CBanQuery()
{
}

void CBanQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAMENAME, m_cmbGameName);
	DDX_Control(pDX, IDC_GAMESERVER, m_cmbGameServerIp);
	DDX_Control(pDX, IDC_PLAYERNAME, m_editPlayerAccount);
	DDX_Control(pDX, IDC_NICKNAME, m_editPlayerNickName);
	DDX_Control(pDX, IDC_LISTACCOUNTINFO, m_listAccountInfo);
	DDX_Control(pDX, IDC_TAB, m_tabCtrl);
	DDX_Control(pDX,IDC_UNBANDATE,m_timeCtrlUnBanDate);
	DDX_Control(pDX, IDC_UNBANTIME, m_timeCtrlUnBanTime);
	DDX_Control(pDX,IDC_BANDATE,m_timeCtrlBanDate);
	DDX_Control(pDX, IDC_BANTIME, m_timeCtrlBanTime);
	DDX_Control(pDX, IDC_REASON, m_editReason);
	DDX_Control(pDX, IDC_OPTIONUBANTIME, m_chkBtnUnbanTimeOption);
	DDX_Control(pDX, IDC_BEGINTIME, dtcBeginTime);
	DDX_Control(pDX, IDC_ENDTIME, dtcEndTime);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
}


BEGIN_MESSAGE_MAP(CBanQuery, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CBanQuery::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_GAMENAME, &CBanQuery::OnCbnSelChangeGameName)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, &CBanQuery::OnCbnSelChangePage)
	ON_BN_CLICKED(IDCANCEL, &CBanQuery::OnBnClickedCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CBanQuery::OnTcnSelchangeTab)
	ON_BN_CLICKED(IDC_BTNIMPLEMENT, &CBanQuery::OnBnClickedImplement)
	//maple add
	ON_BN_CLICKED(IDC_OPTIONUBANTIME,&CBanQuery::OnBnClickBanTimeOption)
END_MESSAGE_MAP()


// CBanQuery message handlers

BOOL CBanQuery::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	// ��󻯴���
	ShowWindow(SW_SHOWMAXIMIZED);

	InitTabCtrl();
	LayoutChildWnd();

	m_listAccountInfo.SetExtendedStyle(LVS_EX_GRIDLINES);

	m_timeCtrlUnBanDate.ShowWindow(SW_HIDE);
	m_timeCtrlUnBanTime.ShowWindow(SW_HIDE);
	m_timeCtrlBanDate.ShowWindow(SW_HIDE);
	m_timeCtrlBanTime.ShowWindow(SW_HIDE);
	m_chkBtnUnbanTimeOption.ShowWindow(SW_HIDE);
	m_editReason.ShowWindow(SW_HIDE);

	m_timeCtrlUnBanDate.SetFormat("yyyy-MM-dd");
	m_timeCtrlBanDate.SetFormat("yyyy-MM-dd");
	int iGameID=0;

	int i=0;
	int nIndex =0;
	// Set ctrl text.
	for (i=0; i<sizeof(g_dwCtrlIDWithTextNew)/sizeof(DWORD); i++)
	{
		if (i != IDC_TAB)
		{
			char szKey[MAX_PATH] = {0};
			_itoa(g_dwCtrlIDWithTextNew[i], szKey, 10);
			CString strText = theApp.m_iniFile.ReadStringValue(INI_UI_TEXT_SECTIONNew, szKey);
			CWnd* pCtrl = GetDlgItem(g_dwCtrlIDWithTextNew[i]);
			ASSERT(NULL != pCtrl);
			pCtrl->SetWindowText((LPCTSTR)strText);
		}
	}
	char path[256];
	GetCurrentDirectory(256,path);//��ȡ��ǰĿ¼
	char filepath[256];
	sprintf(filepath,"%s%s",path,"\\config\\AGABUNB.ini");//��ȡAGABUNB.ini�ļ�·��

	for (i=0; i<sizeof(g_sGameOperInfoNew)/sizeof(GAME_OPER_INFO); i++)
	{

		iGameID=GetPrivateProfileInt("GAMEID",g_sGameOperInfoNew[i].lpGameDBIDKey,0,filepath);//�õ������˿ں�
		if(iGameID!=0)
			g_sGameOperInfoNew[i].uGameID=iGameID;
	}


	for (i=0; i<sizeof(g_sGameOperInfoNew)/sizeof(GAME_OPER_INFO); i++)
	{

		iGameID=GetPrivateProfileInt("GAMEID",g_sGameOperInfoNew[i].lpGameDBIDKey,0,filepath);//�õ������˿ں�
		if(iGameID!=0)
		{
			LPGAME_INFO_NEW lpgi = new GAME_INFO_NEW;
			if(g_sGameOperInfoNew[i].lpGameDBIDKey=="SDODB")
			{
				lpgi->nGameID = iGameID;
				nIndex = m_cmbGameName.AddString((LPCTSTR)"��������");
				m_cmbGameName.SetItemData(nIndex, (DWORD_PTR)lpgi);
			}
			else if(g_sGameOperInfoNew[i].lpGameDBIDKey=="FJDB")
			{
				lpgi->nGameID = iGameID;
				nIndex = m_cmbGameName.AddString((LPCTSTR)"���֮��");
				m_cmbGameName.SetItemData(nIndex, (DWORD_PTR)lpgi);
			}
			else if(g_sGameOperInfoNew[i].lpGameDBIDKey=="LIGHTCARDB")
			{
				lpgi->nGameID = iGameID;
				nIndex = m_cmbGameName.AddString((LPCTSTR)"���߷ɳ�");
				m_cmbGameName.SetItemData(nIndex, (DWORD_PTR)lpgi);
			}
			else if(g_sGameOperInfoNew[i].lpGameDBIDKey=="PETFORESTDB")
			{
				lpgi->nGameID = iGameID;
				nIndex = m_cmbGameName.AddString((LPCTSTR)"����ɭ��");
				m_cmbGameName.SetItemData(nIndex, (DWORD_PTR)lpgi);
			}
			else if(g_sGameOperInfoNew[i].lpGameDBIDKey=="CG2DB")
			{
				lpgi->nGameID = iGameID;
				nIndex = m_cmbGameName.AddString((LPCTSTR)"ħ������2");
				m_cmbGameName.SetItemData(nIndex, (DWORD_PTR)lpgi);
			}
			else if(g_sGameOperInfoNew[i].lpGameDBIDKey=="BASKETBALLDB")
			{
				lpgi->nGameID = iGameID;
				nIndex = m_cmbGameName.AddString((LPCTSTR)"��������");
				m_cmbGameName.SetItemData(nIndex, (DWORD_PTR)lpgi);
			}
			else if(g_sGameOperInfoNew[i].lpGameDBIDKey=="PALDB")
			{
				lpgi->nGameID = iGameID;
				nIndex = m_cmbGameName.AddString((LPCTSTR)"�ɽ�online");
				m_cmbGameName.SetItemData(nIndex, (DWORD_PTR)lpgi);
			}
			else if(g_sGameOperInfoNew[i].lpGameDBIDKey=="GTDB")
			{
				lpgi->nGameID = iGameID;
				nIndex = m_cmbGameName.AddString((LPCTSTR)"����ONLINE");
				m_cmbGameName.SetItemData(nIndex, (DWORD_PTR)lpgi);
			}
			else if(g_sGameOperInfoNew[i].lpGameDBIDKey=="AUDB")
			{
				lpgi->nGameID = iGameID;
				nIndex= m_cmbGameName.AddString((LPCTSTR)"������");
				m_cmbGameName.SetItemData(nIndex, (DWORD_PTR)lpgi);
			}
			else if(g_sGameOperInfoNew[i].lpGameDBIDKey=="JW2DB")
			{
				lpgi->nGameID = iGameID;
				nIndex = m_cmbGameName.AddString((LPCTSTR)"������II");
				m_cmbGameName.SetItemData(nIndex, (DWORD_PTR)lpgi);
			}
			else if(g_sGameOperInfoNew[i].lpGameDBIDKey=="SDGANDA")
			{
				lpgi->nGameID = iGameID;
				nIndex = m_cmbGameName.AddString((LPCTSTR)"SD�Ҵ�");
				m_cmbGameName.SetItemData(nIndex, (DWORD_PTR)lpgi);
			}

		}
	}
	m_cmbGameName.SetCurSel(0);
	OnCbnSelChangeGameName();
	//QueryGameName();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// Initialize tabCtrl and associate windows to tab ctrl item.
// These windows would be shown if the tab ctrl item is Selected.
void CBanQuery::InitTabCtrl()
{
	for (int i=0; i<TCII_TAB_ITEM_COUNT; i++)
	{
		char szKey[MAX_PATH] = {0};
		//	sprintf_s(szKey, "%d_%d", IDC_TAB, i);
		sprintf(szKey, "%d_%d", IDC_TAB, i);
		CString strTxt = theApp.m_iniFile.ReadStringValue(INI_UI_TEXT_SECTIONNew, szKey);
		
		m_tabCtrl.InsertItem(i, strTxt);
	}

	m_nTabCtrlSelectItem = TCII_QUERY_RESULT;
	m_tabCtrl.SetCurSel(m_nTabCtrlSelectItem);
}

void CBanQuery::LayoutChildWnd()
{
	RECT rctDlg;
	GetClientRect(&rctDlg);

	RECT rctGroup;
	CWnd* pWnd = GetDlgItem(IDC_GRPSEARCH);
	pWnd->GetClientRect(&rctGroup);

	// Set tab ctrl.
	RECT rctTab;
	rctTab.left = rctDlg.left;
	rctTab.top = rctGroup.bottom + 15;
	rctTab.right  = rctDlg.right;  
	rctTab.bottom = rctTab.top + 25;
	m_tabCtrl.MoveWindow(CRect(rctTab));

	// Set list ctrl.
	RECT rctList;
	rctList.left = rctDlg.left;
	rctList.top = rctTab.bottom + 5;
	rctList.right  = rctDlg.right;  
	rctList.bottom = rctDlg.bottom;
	m_listAccountInfo.MoveWindow(CRect(rctList));
}

void CBanQuery::SetGameDBServerComboBox(LPGAME_INFO_NEW lpgi)
{
	ASSERT(NULL != lpgi);

	try
	{
		ClearGameDBServerCombBoxAssociateData();

		int nIndex = 0;
		LPGAME_DB_SERVER_NEW lpgds = lpgi->lplistDBServer;
		while(NULL != lpgds)
		{
			nIndex = m_cmbGameServerIp.AddString((LPCTSTR)lpgds->strDBServerName);
			char* pszIP = new char[lpgds->strDBServerIP.GetLength()+1];
			//	strcpy_s(pszIP, lpgds->strDBServerIP.GetLength()+1, (LPCTSTR)lpgds->strDBServerIP);
			strcpy(pszIP,(LPCTSTR)lpgds->strDBServerIP);
			m_cmbGameServerIp.SetItemData(nIndex, (DWORD_PTR)pszIP);
			lpgds = lpgds->lpNext;
		}

		m_cmbGameServerIp.SetCurSel(0);
	}
	catch(...)
	{

	}
}
// Initialize m_cmbGameName.
void CBanQuery::QueryGameName()
{
	m_cmbGameName.ResetContent();

	try
	{
		CSocketData socketdata;
		socketdata.InitCreate(1,3);//����3��������ҳ����ÿҳ�ļ�¼����

		// 
		// ����TFLV
		//

		// GMTOOLS' userID.
		char szInt[MAX_PATH] = {0};
		_itoa(theApp.m_nGMTUserID, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char *)szInt);

		// ҳ����, 0��ʾȫ��.
		memset(szInt, 0, sizeof(szInt));
		_itoa(0, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER, sizeof(int),(unsigned char *)szInt);

		// ÿҳ�ļ�¼����, 0��ʾȫ��.
		memset(szInt, 0, sizeof(szInt));
		_itoa(0, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER, sizeof(int),(unsigned char *)szInt);

		EnableWindow(FALSE);
		theApp.m_dataOper.SendQuery(socketdata, CEnumCore::Msg_Category::GAME_ADMIN, CEnumCore::ServiceKey::GAME_QUERY);

		socketdata.Destroy();
	}
	catch(...)
	{

	}
}

// Initialize m_cmbGameServerIp.
void CBanQuery::QueryGameServerIp(int nGameID, int nGameDBID)
{
	try
	{
		CSocketData socketdata;
		socketdata.InitCreate(1,2);

		// Game ID.
		char szInt[MAX_PATH] = {0};
		_itoa(nGameID, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameID, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char *)szInt);

		// Game DB ID.
		memset(szInt, 0, sizeof(szInt));
		_itoa(nGameDBID, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameDBID, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char *)szInt);

		// ҳ����, 0��ʾȫ��.
		memset(szInt, 0, sizeof(szInt));
		_itoa(0, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER, sizeof(int),(unsigned char *)szInt);

		// ÿҳ�ļ�¼����, 0��ʾȫ��.
		memset(szInt, 0, sizeof(szInt));
		_itoa(0, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER, sizeof(int),(unsigned char *)szInt);

		EnableWindow(FALSE);

		// Check all DBServerIP of game.
		theApp.m_dataOper.SendQuery(socketdata, CEnumCore::Msg_Category::COMMON, CEnumCore::ServiceKey::SERVERINFO_IP_QUERY);

		socketdata.Destroy();
	}
	catch(...)
	{

	}
}

void CBanQuery::SetRecvData(CSocketData &socketdata, CEnumCore::Message_Tag_ID eMsgTagID)
{
	EnableWindow(TRUE);

	int nTFLVCount = socketdata.getAllTFLV();
	if (0 == nTFLVCount)
		return;

	CGlobalStruct::TFLV tflvErr = socketdata.getTLVBynIndex(1);
	if ((unsigned short)tflvErr.m_tagName == CEnumCore::TagName::MESSAGE)
	{
		AfxMessageBox((LPTSTR)tflvErr.lpdata);
	}

	try
	{
		switch(eMsgTagID)
		{
		case CEnumCore::Message_Tag_ID::GAME_QUERY_RESP:	// ��Ϸ�б�.
			{
				// ����Ϸ����ӵ�m_cmbGameName��Ͽ�.
				m_cmbGameName.ResetContent();
				int nTFLVNum = socketdata.getAllTFLV();
				for (int i=1; i<nTFLVNum; i++)
				{
					CGlobalStruct::TFLV tflvGameID = socketdata.getTLVBynIndex(i);
					if ((unsigned short)tflvGameID.m_tagName == CEnumCore::TagName::GameID)
					{
						// Set game id.
						UINT format = tflvGameID.m_tagFormat;
						ASSERT((unsigned short)tflvGameID.m_tagFormat == CEnumCore::TagFormat::TLV_STRING);
						LPGAME_INFO_NEW lpgi = new GAME_INFO_NEW;
						int nModuleID = atoi((const char *)tflvGameID.lpdata);
						if (1 == nModuleID)
							continue;
						lpgi->nGameID = nModuleID;

						// Set game name.
						CGlobalStruct::TFLV tflvGameName = socketdata.getTLVBynIndex(i+1);
						ASSERT((unsigned short)tflvGameName.m_tagName == CEnumCore::TagName::GameName);
						ASSERT((unsigned short)tflvGameName.m_tagFormat == CEnumCore::TagFormat::TLV_STRING);
						char szGameName[MAX_PATH] = {0};
						//						strncpy_s(szGameName, sizeof(szGameName), (const char *)tflvGameName.lpdata, tflvGameName.m_tvlength);
						strncpy(szGameName, (const char *)tflvGameName.lpdata, tflvGameName.m_tvlength);

						int nIndex = m_cmbGameName.AddString((LPCTSTR)szGameName);
						m_cmbGameName.SetItemData(nIndex, (DWORD_PTR)lpgi);
					}
				}
				m_cmbGameName.SetCurSel(0);
				OnCbnSelChangeGameName();
			}
			break;
		case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP:	// ��ϷDB�б�.
			{
				// Make gameDB list.

				// Pointer to gameDB list.
				int nIndex = m_cmbGameName.GetCurSel();
				void* pvgi = m_cmbGameName.GetItemDataPtr(nIndex);
				ASSERT(NULL != pvgi);
				LPGAME_INFO_NEW lpgi = (LPGAME_INFO_NEW)pvgi;

				// make GameDB list.
				int nTFLVNum = socketdata.getAllTFLV();
				LPGAME_DB_SERVER_NEW lpLastDBServer = NULL;
				for (int i=1; i<nTFLVNum; i++)
				{
					CGlobalStruct::TFLV tflvServerCity = socketdata.getTLVBynIndex(i);
					if ((unsigned short)tflvServerCity.m_tagName == CEnumCore::TagName::ServerInfo_City)
					{
						ASSERT(i > 1);

						if (NULL == lpgi->lplistDBServer)
						{
							lpgi->lplistDBServer = new GAME_DB_SERVER_NEW;
							lpLastDBServer = lpgi->lplistDBServer;						
						}
						else
						{
							lpLastDBServer->lpNext = new GAME_DB_SERVER_NEW;
							lpLastDBServer = lpLastDBServer->lpNext;
						}

						ASSERT(NULL != lpLastDBServer);
						lpLastDBServer->nGameID = lpgi->nGameID;

						//������.
						char szServerCity[MAX_PATH] = {0};
						ASSERT((unsigned short)tflvServerCity.m_tagFormat == CEnumCore::TagFormat::TLV_STRING);
						strncpy(szServerCity, (const char *)tflvServerCity.lpdata, tflvServerCity.m_tvlength);
						//						strncpy_s(szServerCity, sizeof(szServerCity), (const char *)tflvServerCity.lpdata, tflvServerCity.m_tvlength);
						lpLastDBServer->strDBServerName = szServerCity;

						// ������IP.
						char szServerIP[MAX_PATH] = {0};
						CGlobalStruct::TFLV tflvServerIP = socketdata.getTLVBynIndex(i-1);
						ASSERT((unsigned short)tflvServerIP.m_tagName == CEnumCore::TagName::ServerInfo_IP);
						ASSERT((unsigned short)tflvServerIP.m_tagFormat == CEnumCore::TagFormat::TLV_STRING);
						strncpy(szServerIP, (const char *)tflvServerIP.lpdata, tflvServerIP.m_tvlength);
						//						strncpy_s(szServerIP, sizeof(szServerIP), (const char *)tflvServerIP.lpdata, tflvServerIP.m_tvlength);
						lpLastDBServer->strDBServerIP =	szServerIP;
					}
				}

				SetGameDBServerComboBox(lpgi);
			}
			break;
		case CEnumCore::Message_Tag_ID::Ban_AccountList_Query_Resp:	// ��ѯ��ͣ�ʺŵ��б��Ӧ.
		case CEnumCore::Message_Tag_ID::Ban_Account_Query_Resp:		// ��ѯ�����ʺŵķ�ͣ��Ϣ��Ӧ.
			{



				m_listAccountInfo.DeleteAllItems();
				if ((unsigned short)tflvErr.m_tagName == CEnumCore::TagName::MESSAGE)
					break;

				///////����cmbBox///////////
				int iPageCount=atoi((char *)&(socketdata.getTLVByTag(CEnumCore::TagName::PageCount,0).lpdata));
				CString iIndex;
				if(pageInfo)
				{
					cmbPage.ResetContent();
					for(int i=0;i<iPageCount;i++)
					{
						iIndex.Format("%i",i+1);
						cmbPage.AddString(iIndex);
					}
					cmbPage.SetCurSel(0);
				}

				int nTFLVColNum = socketdata.getColTFLVNum();
				if (nTFLVColNum-1 != m_listColumnNum)
				{
					for (int i=0; i<m_listColumnNum; i++)
						m_listAccountInfo.DeleteColumn(i);

					// Column number.
					m_listColumnNum = nTFLVColNum-1;

					// Construct columns again.
					for (int i=0; i<m_listColumnNum; i++)
					{
						// Get column title name from config file.
						CGlobalStruct::TFLV tflv= socketdata.getTLV(1, i+1);
						CString strKey;
						strKey.Format("%u", (unsigned short)tflv.m_tagName);
						CString strTitle = theApp.m_iniFile.ReadStringValue(INI_TAG_NAME_SECTIONNew, (LPCTSTR)strKey);

						m_listAccountInfo.InsertColumn(i, (LPCTSTR)strTitle, LVCFMT_CENTER, LIST_CTRL_COL_WIDTH);
					}
				}

				// Insert account information.
				int nTFLVRowNum = socketdata.getQueryNum();
				for (int i=0; i<nTFLVRowNum; i++)
				{
					m_listAccountInfo.InsertItem(i, "");
					for (int j=0; j<m_listColumnNum; j++)
					{
						CGlobalStruct::TFLV tflv= socketdata.getTLV(i+1, j+1);
						char szBuff[MAX_PATH] = {0};
						//						strncpy_s(szBuff, sizeof(szBuff), (LPCTSTR)tflv.lpdata, tflv.m_tvlength);
						strncpy(szBuff, (LPCTSTR)tflv.lpdata, tflv.m_tvlength);

						// �ǳ�
						if ((unsigned short)tflv.m_tagName == CEnumCore::TagName::Ban_UserNick)
							if(0 == strcmp(szBuff, "NULL"))
								strcpy(szBuff,"");
						//strcpy_s(szBuff, sizeof(szBuff), "");

						// ���ʱ��
						if ((unsigned short)tflv.m_tagName == CEnumCore::TagName::Ban_EndTime)
							if(0 == strcmp(szBuff, "NULL"))
								strcpy(szBuff,"���÷�ͣ");
						//strcpy_s(szBuff, sizeof(szBuff), "���÷�ͣ");

						// ��ͣʱ��
						if ((unsigned short)tflv.m_tagName == CEnumCore::TagName::Ban_StartTime)
							if(0 == strcmp(szBuff, "NULL"))
								strcpy(szBuff, "�ѷ�ͣ");
						//	strcpy_s(szBuff, sizeof(szBuff), "�ѷ�ͣ");*/

						m_listAccountInfo.SetItemText(i, j, szBuff);
					}
				}
			}
			break;
		case CEnumCore::Message_Tag_ID::Ban_Open_Query_Resp:		// ����˺Ż�Ӧ & ���ý��ʱ���Ӧ
		case CEnumCore::Message_Tag_ID::Ban_Close_Query_Resp:		// ��ͣ�˺Ż�Ӧ & ���÷�ͣʱ���Ӧ
			{
				int nTFLVNum = socketdata.getAllTFLV();
				ASSERT(1 == nTFLVNum);
			}
			break;
		default:
			break;
		}
	}
	catch(...)
	{

	}
}


// ��ͣ�ʺ��б��ѯ & ��ѯָ���ʺŷ�ͣ��Ϣ.
void CBanQuery::OnBnClickedOk()
{
	int nSel = 0;

	int nTFLVNum = 5;

	// Get game name.
	nTFLVNum++;
	nSel = m_cmbGameName.GetCurSel();
	CString strGameName;
	m_cmbGameName.GetLBText(nSel, strGameName);

	// Get game id.
	nTFLVNum++;
	LPGAME_INFO_NEW lpgi = (LPGAME_INFO_NEW)m_cmbGameName.GetItemDataPtr(nSel);
	ASSERT(NULL != lpgi);
	int nGameID = lpgi->nGameID;

	// Get game DBServer city.
	nTFLVNum++;
	nSel = m_cmbGameServerIp.GetCurSel();
	CString strGameDBServerCity;
	m_cmbGameServerIp.GetLBText(nSel, strGameDBServerCity);

	// Get game DBServer ip.
	nTFLVNum++;
	DWORD_PTR dwIP = m_cmbGameServerIp.GetItemData(nSel);
	CString strServerIP((LPCSTR)dwIP);


	// PlayerAccount.
	CString strPlayerAccount;
	m_editPlayerAccount.GetWindowText(strPlayerAccount);
	int nAccountLen = strPlayerAccount.GetLength();

	// PlayerNickName.
	CString strPlayerNickName;
	m_editPlayerNickName.GetWindowText(strPlayerNickName);
	int nNickNameLen = strPlayerNickName.GetLength();

	if (nNickNameLen>0 || nAccountLen>0)
		nTFLVNum++;


	try
	{
		CSocketData socketdata;
		//ASSERT(nTFLVNum>=6 && nTFLVNum<=7);
		socketdata.InitCreate(1, nTFLVNum);
		char szInt[MAX_PATH] = {0};

		// Game ID.
		_itoa(nGameID, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameID, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char *)szInt);

		// Game name.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameName, CEnumCore::TagFormat::TLV_STRING, 
			strGameName.GetLength(), (unsigned char*)(LPCTSTR)strGameName);

		// Game DB Server city.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_City, CEnumCore::TagFormat::TLV_STRING, 
			strGameDBServerCity.GetLength(), (unsigned char*)(LPCTSTR)strGameDBServerCity);

		// Game DB Server IP.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_IP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char*)(LPCTSTR)strServerIP); 

		if (0<nAccountLen)
		{
			// Player Account.
			socketdata.AddTFLV(CEnumCore::TagName::Ban_UserName, CEnumCore::TagFormat::TLV_STRING,
				strPlayerAccount.GetLength(), (unsigned char*)(LPCTSTR)strPlayerAccount);
		}
		else
		{
			// PlayerNickName.
			CString strPlayerNickName;
			m_editPlayerNickName.GetWindowText(strPlayerNickName);
			int nNickNameLen = strPlayerNickName.GetLength();

			if (0<nNickNameLen)
				socketdata.AddTFLV(CEnumCore::TagName::Ban_UserNick, CEnumCore::TagFormat::TLV_STRING, 
				strPlayerNickName.GetLength(), (unsigned char*)(LPCTSTR)strPlayerNickName);				
		}

		CIni mIni;

		CTime beginTime,endTime;
		dtcBeginTime.GetTime(beginTime);
		dtcEndTime.GetTime(endTime);

		CTime beginDT=CTime::CTime(beginTime.GetYear(),beginTime.GetMonth(),beginTime.GetDay(),0,0,0);
		CTime endDT=CTime::CTime(endTime.GetYear(),endTime.GetMonth(),endTime.GetDay(),0,0,0);

		if(beginDT>=endDT)
		{
			MessageBox("��ʼʱ�䲻�ܴ��ڵ��ڽ���ʱ��");
			return;
		}

		CString strBeginTime,strEndTime;
		strBeginTime=beginDT.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��
		strEndTime=endDT.Format("%Y-%m-%d %H:%M:%S");//���ý���ʱ��

		socketdata.AddTFLV(CEnumCore::TagName::BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char *)mIni.wcharToChar(strBeginTime));

		socketdata.AddTFLV(CEnumCore::TagName::EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));


		int iIndex=cmbPage.GetCurSel()+1;
		if(iIndex<=0)
			iIndex=1;
		pageInfo=true;

		// ҳ����, 0��ʾȫ��.
		memset(szInt, 0, sizeof(szInt));
		_itoa(iIndex, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER, sizeof(int),(unsigned char *)szInt);

		// ÿҳ�ļ�¼����, 0��ʾȫ��.
		int iPageSize=theApp.m_iniFile.ReadIntegrityValue("QUERY","PageSize");
		memset(szInt, 0, sizeof(szInt));
		_itoa(iPageSize, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER, sizeof(int),(unsigned char *)szInt);

		EnableWindow(FALSE);

		if (nNickNameLen>0 || nAccountLen>0)
		{
			// ��ѯָ���ʺŷ�ͣ��Ϣ.
			theApp.m_dataOper.SendQuery(socketdata, CEnumCore::Msg_Category::Ban_ADMIN, CEnumCore::ServiceKey::Ban_Account_Query);
		}	
		else
		{
			// ��ѯ��ͣ�ʺŵ��б�.
			theApp.m_dataOper.SendQuery(socketdata, CEnumCore::Msg_Category::Ban_ADMIN, CEnumCore::ServiceKey::Ban_AccountList_Query);
		}

		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

// Set m_cmbGameServerIp comboBox.
void CBanQuery::OnCbnSelChangeGameName()
{
	// Get gameDBID-Key.
	int nIndex = m_cmbGameName.GetCurSel();
	LPGAME_INFO_NEW lpgi = (LPGAME_INFO_NEW)m_cmbGameName.GetItemData(nIndex);
	ASSERT(NULL != lpgi);

	if (NULL == lpgi->lplistDBServer)
	{
		CString strKey("");
		for (int i=0; i<sizeof(g_sGameOperInfoNew)/sizeof(GAME_OPER_INFO); i++)
		{
			if (g_sGameOperInfoNew[i].uGameID == lpgi->nGameID)
			{
				strKey = g_sGameOperInfoNew[i].lpGameDBIDKey;
				break;
			}
		}
		ASSERT(0 < strKey.GetLength());

		// Get GameDBID.
		int nGameDBID = theApp.m_iniFile.ReadIntegrityValue(INI_GAME_DB_SECTIONNew, strKey);

		QueryGameServerIp(lpgi->nGameID, nGameDBID);
	}
	else
	{
		SetGameDBServerComboBox(lpgi);
	}
}
void CBanQuery::OnCbnSelChangePage()
{
	pageInfo=false;
	int nSel = 0;

	int nTFLVNum = 5;

	// Get game name.
	nTFLVNum++;
	nSel = m_cmbGameName.GetCurSel();
	CString strGameName;
	m_cmbGameName.GetLBText(nSel, strGameName);

	// Get game id.
	nTFLVNum++;
	LPGAME_INFO_NEW lpgi = (LPGAME_INFO_NEW)m_cmbGameName.GetItemDataPtr(nSel);
	ASSERT(NULL != lpgi);
	int nGameID = lpgi->nGameID;

	// Get game DBServer city.
	nTFLVNum++;
	nSel = m_cmbGameServerIp.GetCurSel();
	CString strGameDBServerCity;
	m_cmbGameServerIp.GetLBText(nSel, strGameDBServerCity);

	// Get game DBServer ip.
	nTFLVNum++;
	DWORD_PTR dwIP = m_cmbGameServerIp.GetItemData(nSel);
	CString strServerIP((LPCSTR)dwIP);


	// PlayerAccount.
	CString strPlayerAccount;
	m_editPlayerAccount.GetWindowText(strPlayerAccount);
	int nAccountLen = strPlayerAccount.GetLength();

	// PlayerNickName.
	CString strPlayerNickName;
	m_editPlayerNickName.GetWindowText(strPlayerNickName);
	int nNickNameLen = strPlayerNickName.GetLength();

	if (nNickNameLen>0 || nAccountLen>0)
		nTFLVNum++;


	try
	{
		CSocketData socketdata;
		//ASSERT(nTFLVNum>=6 && nTFLVNum<=7);
		socketdata.InitCreate(1, nTFLVNum);
		char szInt[MAX_PATH] = {0};

		// Game ID.
		_itoa(nGameID, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameID, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char *)szInt);

		// Game name.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameName, CEnumCore::TagFormat::TLV_STRING, 
			strGameName.GetLength(), (unsigned char*)(LPCTSTR)strGameName);

		// Game DB Server city.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_City, CEnumCore::TagFormat::TLV_STRING, 
			strGameDBServerCity.GetLength(), (unsigned char*)(LPCTSTR)strGameDBServerCity);

		// Game DB Server IP.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_IP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char*)(LPCTSTR)strServerIP); 

		if (0<nAccountLen)
		{
			// Player Account.
			socketdata.AddTFLV(CEnumCore::TagName::Ban_UserName, CEnumCore::TagFormat::TLV_STRING,
				strPlayerAccount.GetLength(), (unsigned char*)(LPCTSTR)strPlayerAccount);
		}
		else
		{
			// PlayerNickName.
			CString strPlayerNickName;
			m_editPlayerNickName.GetWindowText(strPlayerNickName);
			int nNickNameLen = strPlayerNickName.GetLength();

			if (0<nNickNameLen)
				socketdata.AddTFLV(CEnumCore::TagName::Ban_UserNick, CEnumCore::TagFormat::TLV_STRING, 
				strPlayerNickName.GetLength(), (unsigned char*)(LPCTSTR)strPlayerNickName);				
		}

		CIni mIni;

		CTime beginTime,endTime;
		dtcBeginTime.GetTime(beginTime);
		dtcEndTime.GetTime(endTime);

		CTime beginDT=CTime::CTime(beginTime.GetYear(),beginTime.GetMonth(),beginTime.GetDay(),0,0,0);
		CTime endDT=CTime::CTime(endTime.GetYear(),endTime.GetMonth(),endTime.GetDay(),0,0,0);

		if(beginDT>=endDT)
		{
			MessageBox("��ʼʱ�䲻�ܴ��ڵ��ڽ���ʱ��");
			return;
		}

		CString strBeginTime,strEndTime;
		strBeginTime=beginDT.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��
		strEndTime=endDT.Format("%Y-%m-%d %H:%M:%S");//���ý���ʱ��

		socketdata.AddTFLV(CEnumCore::TagName::BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char *)mIni.wcharToChar(strBeginTime));

		socketdata.AddTFLV(CEnumCore::TagName::EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));


		int iIndex=cmbPage.GetCurSel()+1;
		if(iIndex<=0)
			iIndex=1;

		// ҳ����, 0��ʾȫ��.
		memset(szInt, 0, sizeof(szInt));
		_itoa(iIndex, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER, sizeof(int),(unsigned char *)szInt);

		// ÿҳ�ļ�¼����, 0��ʾȫ��.
		int iPageSize=theApp.m_iniFile.ReadIntegrityValue("QUERY","PageSize");
		memset(szInt, 0, sizeof(szInt));
		_itoa(iPageSize, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER, sizeof(int),(unsigned char *)szInt);

		EnableWindow(FALSE);

		if (nNickNameLen>0 || nAccountLen>0)
		{
			// ��ѯָ���ʺŷ�ͣ��Ϣ.
			theApp.m_dataOper.SendQuery(socketdata, CEnumCore::Msg_Category::Ban_ADMIN, CEnumCore::ServiceKey::Ban_Account_Query);
		}	
		else
		{
			// ��ѯ��ͣ�ʺŵ��б�.
			theApp.m_dataOper.SendQuery(socketdata, CEnumCore::Msg_Category::Ban_ADMIN, CEnumCore::ServiceKey::Ban_AccountList_Query);
		}

		socketdata.Destroy();
	}
	catch(...)
	{
	}
}
void CBanQuery::OnBnClickedCancel()
{
	//ClearGameNameCombBoxAssociateData();
	//ClearGameDBServerCombBoxAssociateData();

	//theApp.m_bCreatingAccountDlg = FALSE;

	ShowWindow(SW_HIDE);
}

void CBanQuery::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Last showing ctrl-window, these window is about to hide.
	ASSERT(m_nTabCtrlSelectItem < MAX_TCN_ASSO_WND);
	for (int i=0; i<MAX_TCN_ASSO_WND; i++)
	{
		if (0 == g_dwTabCtrlIDMapCtrlWndIDNew[m_nTabCtrlSelectItem][i])
			continue;

		CWnd* pCtrlHide = GetDlgItem(g_dwTabCtrlIDMapCtrlWndIDNew[m_nTabCtrlSelectItem][i]);
		ASSERT(NULL != pCtrlHide);
		pCtrlHide->ShowWindow(SW_HIDE);
	}

	// Ctrl-window is about to show.
	int nSel = m_tabCtrl.GetCurSel();
	for (int i=0; i<MAX_TCN_ASSO_WND; i++)
	{
		if (0 == g_dwTabCtrlIDMapCtrlWndIDNew[nSel][i])
			continue;

		ASSERT(nSel < MAX_TCN_ASSO_WND);
		CWnd* pCtrlHide = GetDlgItem(g_dwTabCtrlIDMapCtrlWndIDNew[nSel][i]);
		ASSERT(NULL != pCtrlHide);
		pCtrlHide->ShowWindow(SW_SHOW);
	}
	if(nSel==0)
	{
		GetDlgItem(IDC_LPLPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_LPLPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	}
	m_nTabCtrlSelectItem = nSel;

	*pResult = 0;
}

void CBanQuery::OnBnClickedImplement()
{
	int nSel = m_tabCtrl.GetCurSel();
	switch (nSel)
	{
	case TCII_BAN_ACCOUNT:		// ��ͣ�ʺ�.
		BanAccount();
		break;
	case TCII_UNBAN_ACCOUNT:	// ����ʺ�.
		UnBanAccount();
		break;
	case TCII_SET_BAN_TIME:		// ���÷�ͣʱ��.
		SetBanTime();
		break;
	case TCII_SET_UNBAN_TIME:	// ���ý��ʱ��.
		SetUnBanTime();
		break;
	case TCII_QUERY_RESULT:
	default:
		break;
	}	
}

// ��ͣ�ʺ�.
void CBanQuery::BanAccount()
{
	ASSERT(1 == m_tabCtrl.GetCurSel());

	int nTFLVNum = 3;

	// Get GameName.
	nTFLVNum++;
	int nSel = m_cmbGameName.GetCurSel();
	CString strGameName;
	m_cmbGameName.GetLBText(nSel, strGameName);

	// Get Game ID.
	nTFLVNum++;
	LPGAME_INFO_NEW lpgi = (LPGAME_INFO_NEW)m_cmbGameName.GetItemDataPtr(nSel);
	ASSERT(NULL != lpgi);
	int nGameID = lpgi->nGameID;

	// Get Game DBServer city.
	nTFLVNum++;
	nSel = m_cmbGameServerIp.GetCurSel();
	CString strGameDBServerCity;
	m_cmbGameServerIp.GetLBText(nSel, strGameDBServerCity);

	// Get game DBServer ip.
	nTFLVNum++;
	DWORD_PTR dwIP = m_cmbGameServerIp.GetItemData(nSel);
	CString strServerIP((LPCSTR)dwIP);

	// PlayerAccount.
	CString strPlayerAccount;
	m_editPlayerAccount.GetWindowText(strPlayerAccount);
	int nAccountLen = strPlayerAccount.GetLength();
	if (0 < nAccountLen)
		nTFLVNum++;

	// PlayerNickName.
	CString strPlayerNickName;
	m_editPlayerNickName.GetWindowText(strPlayerNickName);
	int nNickNameLen = strPlayerNickName.GetLength();
	if (0 < nNickNameLen)
		nTFLVNum++;

	BOOL bBanNick = FALSE;
	if (0==nAccountLen && 0==nNickNameLen)
	{
		CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "AccountNickNameInput");
		AfxMessageBox(strErr);
		return;
	}
	else if (nNickNameLen>0 && nAccountLen>0)
	{
		int i;
		for (i=0; i<sizeof(g_sGameOperInfoNew)/sizeof(GAME_OPER_INFO); i++)
		{
			if (g_sGameOperInfoNew[i].uGameID == nGameID)
			{
				bBanNick = g_sGameOperInfoNew[i].bOperByNick;
				break;
			}
		}
		ASSERT(i<sizeof(g_sGameOperInfoNew)/sizeof(GAME_OPER_INFO));
	}

	// UnBan Time. (option)
	BOOL bAddUnBanTime = FALSE;
	CString strUnBanTime;

	//maple add
	CString strCurTime;
	CTime curTime = CTime::GetCurrentTime();
	if (BST_CHECKED != m_chkBtnUnbanTimeOption.GetCheck())////�Ƿ����÷�ͣ
	{
		CTime UnBanDate;
		m_timeCtrlUnBanDate.GetTime(UnBanDate);
		CTime UnBanTime;
		m_timeCtrlUnBanTime.GetTime(UnBanTime);

		//CTime curTime = CTime::GetCurrentTime();
		CTime UnBanAllTime = CTime::CTime(UnBanDate.GetYear(),UnBanDate.GetMonth(),UnBanDate.GetDay(),UnBanTime.GetHour(),UnBanTime.GetMinute(),UnBanTime.GetSecond());

		if (UnBanAllTime <= curTime)
		{
			CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "TimeErr");
			AfxMessageBox(strErr);
			return;
		}

		strUnBanTime = UnBanAllTime.Format("%Y-%m-%d %H:%M:%S");
		bAddUnBanTime = TRUE;
		nTFLVNum++;
		strCurTime = curTime.Format("%Y-%m-%d %H:%M:%S");
	}
	else
	{
		strUnBanTime = "2050-11-11 11:11:11";
		nTFLVNum++;
		bAddUnBanTime = FALSE;
		strCurTime = curTime.Format("%Y-%m-%d %H:%M:%S");
	}

	// Ban reason.
	nTFLVNum++;
	CString strBanReason;
	m_editReason.GetWindowText(strBanReason);
	if (0 == strBanReason.GetLength())
	{
		CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "ReasonInput");
		AfxMessageBox(strErr);
		return;
	}

	//
	// Construct sending packet.
	// 

	try
	{
		CSocketData socketdata;
		ASSERT(nTFLVNum>=9 && nTFLVNum<=11);
		socketdata.InitCreate(1, nTFLVNum); // 1��nTFLVNum��.
		char szInt[MAX_PATH] = {0};

		// 
		// ����TFLV
		//

		// GMTOOLS' userID.
		_itoa(theApp.m_nGMTUserID, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char *)szInt);

		// Player Account.
		if (0 != nAccountLen)
			socketdata.AddTFLV(CEnumCore::TagName::Ban_UserName, CEnumCore::TagFormat::TLV_STRING, 
			strPlayerAccount.GetLength(), (unsigned char*)(LPCTSTR)strPlayerAccount);

		// Player NickName.
		if (0 != nNickNameLen)
			socketdata.AddTFLV(CEnumCore::TagName::Ban_UserNick, CEnumCore::TagFormat::TLV_STRING, 
			strPlayerNickName.GetLength(), (unsigned char*)(LPCTSTR)strPlayerNickName);

		if (bBanNick)
		{
			ASSERT(nAccountLen>0 && nNickNameLen>0);

			// Indicate banning NickName.
			socketdata.AddTFLV(CEnumCore::TagName::Ban_Memo, CEnumCore::TagFormat::TLV_STRING, 1, (unsigned char*)(LPCTSTR)"0");
		}
		else
		{
			// Indicate banning Account.
			socketdata.AddTFLV(CEnumCore::TagName::Ban_Memo, CEnumCore::TagFormat::TLV_STRING, 1, (unsigned char*)(LPCTSTR)"1");
		}

		// Game name.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameName, CEnumCore::TagFormat::TLV_STRING, 
			strGameName.GetLength(), (unsigned char*)(LPCTSTR)strGameName);

		// Game ID.
		_itoa(nGameID, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameID, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char *)szInt);

		// Game DB Server city.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_City, CEnumCore::TagFormat::TLV_STRING, 
			strGameDBServerCity.GetLength(), (unsigned char*)(LPCTSTR)strGameDBServerCity);

		// Game DB Server IP.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_IP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char*)(LPCTSTR)strServerIP);

		// UnBan Time. (option)
		//		if (bAddUnBanTime)//maple add
		//		{
		socketdata.AddTFLV(CEnumCore::TagName::Ban_EndTime, CEnumCore::TagFormat::TLV_STRING, 
			strUnBanTime.GetLength(), (unsigned char*)(LPCTSTR)strUnBanTime);//��ͣʱ��
		//		}
		socketdata.AddTFLV(CEnumCore::TagName::Ban_StartTime, CEnumCore::TagFormat::TLV_STRING,
			strCurTime.GetLength(), (unsigned char*)(LPCTSTR)strCurTime);//��ʼʱ��

		// Ban reason.
		socketdata.AddTFLV(CEnumCore::TagName::Ban_Reason, CEnumCore::TagFormat::TLV_STRING,
			strBanReason.GetLength(), (unsigned char*)(LPCTSTR)strBanReason);

		// Ban immediately.
		socketdata.AddTFLV(CEnumCore::TagName::Ban_Type, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char*)"0");

		EnableWindow(FALSE);

		theApp.m_dataOper.SendQuery(socketdata, CEnumCore::Msg_Category::Ban_ADMIN, CEnumCore::ServiceKey::Ban_Close_Query);

		socketdata.Destroy();
	}
	catch(...)
	{
		CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "ConstructTFLV");
		AfxMessageBox(strErr);
	}
}

// ����ʺ�.
void CBanQuery::UnBanAccount()
{
	ASSERT(2 == m_tabCtrl.GetCurSel());

	int nTFLVNum = 3;

	// Get GameName.
	nTFLVNum++;
	int nSel = m_cmbGameName.GetCurSel();
	CString strGameName;
	m_cmbGameName.GetLBText(nSel, strGameName);

	// Get Game ID.
	nTFLVNum++;
	LPGAME_INFO_NEW lpgi = (LPGAME_INFO_NEW)m_cmbGameName.GetItemDataPtr(nSel);
	ASSERT(NULL != lpgi);
	int nGameID = lpgi->nGameID;

	// Get Game DBServer city.
	nTFLVNum++;
	nSel = m_cmbGameServerIp.GetCurSel();
	CString strGameDBServerCity;
	m_cmbGameServerIp.GetLBText(nSel, strGameDBServerCity);

	// Get game DBServer ip.
	nTFLVNum++;
	DWORD_PTR dwIP = m_cmbGameServerIp.GetItemData(nSel);
	CString strServerIP((LPCSTR)dwIP);


	// PlayerAccount.
	CString strPlayerAccount;
	m_editPlayerAccount.GetWindowText(strPlayerAccount);
	int nAccountLen = strPlayerAccount.GetLength();
	if (0 < nAccountLen)
		nTFLVNum++;

	// PlayerNickName.
	CString strPlayerNickName;
	m_editPlayerNickName.GetWindowText(strPlayerNickName);
	int nNickNameLen = strPlayerNickName.GetLength();
	if (0 < nNickNameLen)
		nTFLVNum++;

	BOOL bUnBanNick = FALSE;
	if (0==nAccountLen && 0==nNickNameLen)
	{
		CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "AccountNickNameInput");
		AfxMessageBox(strErr);
		return;
	}
	else if (nNickNameLen>0 && nAccountLen>0)
	{
		int i;
		for (i=0; i<sizeof(g_sGameOperInfoNew)/sizeof(GAME_OPER_INFO); i++)
		{
			if (g_sGameOperInfoNew[i].uGameID == nGameID)
			{
				bUnBanNick = g_sGameOperInfoNew[i].bOperByNick;
				break;
			}
		}
		ASSERT(i<sizeof(g_sGameOperInfoNew)/sizeof(GAME_OPER_INFO));
	}

	// UnBan reason.
	nTFLVNum++;
	CString strUnBanReason;
	m_editReason.GetWindowText(strUnBanReason);
	if (0 == strUnBanReason.GetLength())
	{
		CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "ReasonInput");
		AfxMessageBox(strErr);
		return;
	}

	//
	// Construct sending packet.
	// 

	try
	{
		CSocketData socketdata;
		ASSERT(nTFLVNum>=9 && nTFLVNum<=10);
		socketdata.InitCreate(1, nTFLVNum); // 1��nTFLVNum��.
		char szInt[MAX_PATH] = {0};

		// 
		// ����TFLV
		//

		// GMTOOLS' userID.
		_itoa(theApp.m_nGMTUserID, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char *)szInt);

		// Player Account.
		if (0 != nAccountLen)
			socketdata.AddTFLV(CEnumCore::TagName::Ban_UserName, CEnumCore::TagFormat::TLV_STRING, 
			strPlayerAccount.GetLength(), (unsigned char*)(LPCTSTR)strPlayerAccount);

		// Player NickName.
		if (0 != nNickNameLen)
			socketdata.AddTFLV(CEnumCore::TagName::Ban_UserNick, CEnumCore::TagFormat::TLV_STRING, 
			strPlayerNickName.GetLength(), (unsigned char*)(LPCTSTR)strPlayerNickName);

		if (bUnBanNick)
		{
			ASSERT(nAccountLen>0 && nNickNameLen>0);			

			// Indicate Unbanning NickName.
			socketdata.AddTFLV(CEnumCore::TagName::Ban_Memo, CEnumCore::TagFormat::TLV_STRING, 1, (unsigned char*)(LPCTSTR)"0");
		}
		else
		{
			// Indicate Unbanning Account.
			socketdata.AddTFLV(CEnumCore::TagName::Ban_Memo, CEnumCore::TagFormat::TLV_STRING, 1, (unsigned char*)(LPCTSTR)"1");
		}

		// Game name.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameName, CEnumCore::TagFormat::TLV_STRING, 
			strGameName.GetLength(), (unsigned char*)(LPCTSTR)strGameName);

		// Game ID.
		_itoa(nGameID, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameID, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char *)szInt);

		// Game DB Server city.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_City, CEnumCore::TagFormat::TLV_STRING, 
			strGameDBServerCity.GetLength(), (unsigned char*)(LPCTSTR)strGameDBServerCity);

		// Game DB Server IP.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_IP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char*)(LPCTSTR)strServerIP); 

		// UnBan reason.
		socketdata.AddTFLV(CEnumCore::TagName::Ban_Reason, CEnumCore::TagFormat::TLV_STRING,
			strUnBanReason.GetLength(), (unsigned char*)(LPCTSTR)strUnBanReason);

		// UnBan immediately.
		socketdata.AddTFLV(CEnumCore::TagName::Ban_Type, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char*)"0");

		EnableWindow(FALSE);

		theApp.m_dataOper.SendQuery(socketdata, CEnumCore::Msg_Category::Ban_ADMIN, CEnumCore::ServiceKey::Ban_Open_Query);

		socketdata.Destroy();
	}
	catch(...)
	{
		CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "ConstructTFLV");
		AfxMessageBox(strErr);
	}
}

// ���÷�ͣʱ��.
void CBanQuery::SetBanTime()
{
	ASSERT(3 == m_tabCtrl.GetCurSel());

	int nTFLVNum = 5;

	// Get GameName.
	nTFLVNum++;
	int nSel = m_cmbGameName.GetCurSel();
	CString strGameName;
	m_cmbGameName.GetLBText(nSel, strGameName);

	// Get Game ID.
	nTFLVNum++;
	LPGAME_INFO_NEW lpgi = (LPGAME_INFO_NEW)m_cmbGameName.GetItemDataPtr(nSel);
	ASSERT(NULL != lpgi);
	int nGameID = lpgi->nGameID;

	// Get Game DBServer city.
	nTFLVNum++;
	nSel = m_cmbGameServerIp.GetCurSel();
	CString strGameDBServerCity;
	m_cmbGameServerIp.GetLBText(nSel, strGameDBServerCity);

	// Get game DBServer ip.
	nTFLVNum++;
	DWORD_PTR dwIP = m_cmbGameServerIp.GetItemData(nSel);
	CString strServerIP((LPCSTR)dwIP);


	// PlayerAccount.
	CString strPlayerAccount;
	m_editPlayerAccount.GetWindowText(strPlayerAccount);
	int nAccountLen = strPlayerAccount.GetLength();
	if (0 < nAccountLen)
		nTFLVNum++;

	// PlayerNickName.
	CString strPlayerNickName;
	m_editPlayerNickName.GetWindowText(strPlayerNickName);
	int nNickNameLen = strPlayerNickName.GetLength();
	if (0 < nNickNameLen)
		nTFLVNum++;

	BOOL bOperByNick = FALSE;
	if (0==nAccountLen && 0==nNickNameLen)
	{
		CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "AccountNickNameInput");
		AfxMessageBox(strErr);
		return;
	}
	else if (nNickNameLen>0 && nAccountLen>0)
	{
		int i;
		for (i=0; i<sizeof(g_sGameOperInfoNew)/sizeof(GAME_OPER_INFO); i++)
		{
			if (g_sGameOperInfoNew[i].uGameID == nGameID)
			{
				bOperByNick = g_sGameOperInfoNew[i].bOperByNick;
				break;
			}
		}
		ASSERT(i<sizeof(g_sGameOperInfoNew)/sizeof(GAME_OPER_INFO));
	}

	// Ban Time.//��ͣʱ��
	nTFLVNum++;
	CString strBanTime;
	CTime BanDate;
	m_timeCtrlBanDate.GetTime(BanDate);
	CTime BanTime;
	m_timeCtrlBanTime.GetTime(BanTime);

	CTime curTime = CTime::GetCurrentTime();
	CTime BanAllTime = CTime::CTime(BanDate.GetYear(),BanDate.GetMonth(),BanDate.GetDay(),BanTime.GetHour(),BanTime.GetMinute(),BanTime.GetSecond());


	if (BanAllTime <= curTime)
	{
		CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "TimeErr");
		AfxMessageBox(strErr);
		return;
	}
	strBanTime = BanAllTime.Format("%Y-%m-%d %H:%M:%S");


	// UnBan Time. (option)//���ʱ��
	BOOL bAddUnBanTime = FALSE;
	CString strUnBanTime;
	if (BST_CHECKED != m_chkBtnUnbanTimeOption.GetCheck())////�Ƿ����÷�ͣ
	{
		CTime UnBanDate;
		m_timeCtrlUnBanDate.GetTime(UnBanDate);
		CTime UnBanTime;
		m_timeCtrlUnBanTime.GetTime(UnBanTime);

		CTime curTime = CTime::GetCurrentTime();
		CTime UnBanAllTime = CTime::CTime(UnBanDate.GetYear(),UnBanDate.GetMonth(),UnBanDate.GetDay(),UnBanTime.GetHour(),UnBanTime.GetMinute(),UnBanTime.GetSecond());

		if (UnBanAllTime <= curTime)
		{
			CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "TimeErr");
			AfxMessageBox(strErr);
			return;
		}		

		strUnBanTime = UnBanAllTime.Format("%Y-%m-%d %H:%M:%S");
		bAddUnBanTime = TRUE;
		nTFLVNum++;
	}
	else///���÷�ͣ
	{
		strUnBanTime = "2050-11-11 11:11:11";
		bAddUnBanTime = FALSE;
		nTFLVNum++;
	}

	// Ban reason.
	nTFLVNum++;
	CString strBanReason;
	m_editReason.GetWindowText(strBanReason);
	if (0 == strBanReason.GetLength())
	{
		CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "ReasonInput");
		AfxMessageBox(strErr);
		return;
	}

	//
	// Construct sending packet.
	// 

	try
	{
		CSocketData socketdata;
		ASSERT(nTFLVNum>=10 && nTFLVNum<=15);
		socketdata.InitCreate(1, nTFLVNum); // 1��nTFLVNum��.
		char szInt[MAX_PATH] = {0};

		// 
		// ����TFLV
		//

		// GMTOOLS' userID.
		_itoa(theApp.m_nGMTUserID, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char *)szInt);

		// Player Account.
		if (0 != nAccountLen)
			socketdata.AddTFLV(CEnumCore::TagName::Ban_UserName, CEnumCore::TagFormat::TLV_STRING, 
			strPlayerAccount.GetLength(), (unsigned char*)(LPCTSTR)strPlayerAccount);

		// Player NickName.
		if (0 != nNickNameLen)
			socketdata.AddTFLV(CEnumCore::TagName::Ban_UserNick, CEnumCore::TagFormat::TLV_STRING, 
			strPlayerNickName.GetLength(), (unsigned char*)(LPCTSTR)strPlayerNickName);

		if (bOperByNick)
		{
			ASSERT(nAccountLen>0 && nNickNameLen>0);

			// Indicate banning NickName.
			socketdata.AddTFLV(CEnumCore::TagName::Ban_Memo, CEnumCore::TagFormat::TLV_STRING, 1, (unsigned char*)(LPCTSTR)"0");
		}
		else
		{
			// Indicate banning Account.
			socketdata.AddTFLV(CEnumCore::TagName::Ban_Memo, CEnumCore::TagFormat::TLV_STRING, 1, (unsigned char*)(LPCTSTR)"1");
		}

		// Game name.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameName, CEnumCore::TagFormat::TLV_STRING, 
			strGameName.GetLength(), (unsigned char*)(LPCTSTR)strGameName);

		// Game ID.
		_itoa(nGameID, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameID, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char *)szInt);

		// Game DB Server city.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_City, CEnumCore::TagFormat::TLV_STRING, 
			strGameDBServerCity.GetLength(), (unsigned char*)(LPCTSTR)strGameDBServerCity);

		// Game DB Server IP.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_IP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char*)(LPCTSTR)strServerIP);

		// Ban time.
		socketdata.AddTFLV(CEnumCore::TagName::Ban_StartTime, CEnumCore::TagFormat::TLV_STRING, 
			strBanTime.GetLength(), (unsigned char*)(LPCTSTR)strBanTime);

		// UnBan Time. (option)
		//		if (bAddUnBanTime)
		//		{
		socketdata.AddTFLV(CEnumCore::TagName::Ban_EndTime, CEnumCore::TagFormat::TLV_STRING, 
			strUnBanTime.GetLength(), (unsigned char*)(LPCTSTR)strUnBanTime);
		//		}
		socketdata.AddTFLV(CEnumCore::TagName::Ban_StartTime, CEnumCore::TagFormat::TLV_STRING,
			strBanTime.GetLength(), (unsigned char*)(LPCTSTR)strBanTime);

		// Ban reason.
		socketdata.AddTFLV(CEnumCore::TagName::Ban_Reason, CEnumCore::TagFormat::TLV_STRING,
			strBanReason.GetLength(), (unsigned char*)(LPCTSTR)strBanReason);

		// Set Ban time.
		CString sType="1";
		socketdata.AddTFLV(CEnumCore::TagName::Ban_Type, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char*)(LPCTSTR)sType);//"1");

		EnableWindow(FALSE);

		theApp.m_dataOper.SendQuery(socketdata, CEnumCore::Msg_Category::Ban_ADMIN, CEnumCore::ServiceKey::Ban_Close_Query);

		socketdata.Destroy();
	}
	catch(...)
	{
		CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "ConstructTFLV");
		AfxMessageBox(strErr);
	}
}

// ���ý��ʱ��.
void CBanQuery::SetUnBanTime()
{
	ASSERT(4 == m_tabCtrl.GetCurSel());

	int nTFLVNum = 3;

	// Get GameName.
	nTFLVNum++;
	int nSel = m_cmbGameName.GetCurSel();
	CString strGameName;
	m_cmbGameName.GetLBText(nSel, strGameName);

	// Get Game ID.
	nTFLVNum++;
	LPGAME_INFO_NEW lpgi = (LPGAME_INFO_NEW)m_cmbGameName.GetItemDataPtr(nSel);
	ASSERT(NULL != lpgi);
	int nGameID = lpgi->nGameID;

	// Get Game DBServer city.
	nTFLVNum++;
	nSel = m_cmbGameServerIp.GetCurSel();
	CString strGameDBServerCity;
	m_cmbGameServerIp.GetLBText(nSel, strGameDBServerCity);

	// Get game DBServer ip.
	nTFLVNum++;
	DWORD_PTR dwIP = m_cmbGameServerIp.GetItemData(nSel);
	CString strServerIP((LPCSTR)dwIP);

	// PlayerAccount.
	CString strPlayerAccount;
	m_editPlayerAccount.GetWindowText(strPlayerAccount);
	int nAccountLen = strPlayerAccount.GetLength();
	if (0 < nAccountLen)
		nTFLVNum++;

	// PlayerNickName.
	CString strPlayerNickName;
	m_editPlayerNickName.GetWindowText(strPlayerNickName);
	int nNickNameLen = strPlayerNickName.GetLength();
	if (0 < nNickNameLen)
		nTFLVNum++;

	BOOL bOperByNick = FALSE;
	if (0==nAccountLen && 0==nNickNameLen)
	{
		CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "AccountNickNameInput");
		AfxMessageBox(strErr);
		return;
	}
	else if (nNickNameLen>0 && nAccountLen>0)
	{
		int i;
		for (i=0; i<sizeof(g_sGameOperInfoNew)/sizeof(GAME_OPER_INFO); i++)
		{
			if (g_sGameOperInfoNew[i].uGameID == nGameID)
			{
				bOperByNick = g_sGameOperInfoNew[i].bOperByNick;
				break;
			}
		}
		ASSERT(i<sizeof(g_sGameOperInfoNew)/sizeof(GAME_OPER_INFO));
	}

	// UnBan Time.
	nTFLVNum++;
	CString strUnBanTime;
	CTime UnBanDate;
	m_timeCtrlUnBanDate.GetTime(UnBanDate);
	CTime UnBanTime;
	m_timeCtrlUnBanTime.GetTime(UnBanTime);

	CTime curTime = CTime::GetCurrentTime();
	CTime UnBanAllTime = CTime::CTime(UnBanDate.GetYear(),UnBanDate.GetMonth(),UnBanDate.GetDay(),UnBanTime.GetHour(),UnBanTime.GetMinute(),UnBanTime.GetSecond());

	if (UnBanAllTime <= curTime)
	{
		CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "TimeErr");
		AfxMessageBox(strErr);
		return;
	}
	strUnBanTime = UnBanAllTime.Format("%Y-%m-%d %H:%M:%S");

	// UnBan reason.
	nTFLVNum++;
	CString strUnBanReason;
	m_editReason.GetWindowText(strUnBanReason);
	if (0 == strUnBanReason.GetLength())
	{
		CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "ReasonInput");
		AfxMessageBox(strErr);
		return;
	}

	//
	// Construct sending packet.
	// 

	try
	{
		CSocketData socketdata;
		ASSERT(nTFLVNum>=9 && nTFLVNum<=11);
		socketdata.InitCreate(1, nTFLVNum); // 1��nTFLVNum��.
		char szInt[MAX_PATH] = {0};

		// 
		// ����TFLV
		//

		// GMTOOLS' userID.
		_itoa(theApp.m_nGMTUserID, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char *)szInt);

		// Player Account.
		if (0 != nAccountLen)
			socketdata.AddTFLV(CEnumCore::TagName::Ban_UserName, CEnumCore::TagFormat::TLV_STRING, 
			strPlayerAccount.GetLength(), (unsigned char*)(LPCTSTR)strPlayerAccount);

		// Player NickName.
		if (0 != nNickNameLen)
			socketdata.AddTFLV(CEnumCore::TagName::Ban_UserNick, CEnumCore::TagFormat::TLV_STRING, 
			strPlayerNickName.GetLength(), (unsigned char*)(LPCTSTR)strPlayerNickName);

		if (bOperByNick)
		{
			ASSERT(nAccountLen>0 && nNickNameLen>0);

			// Indicate Unbanning NickName.
			socketdata.AddTFLV(CEnumCore::TagName::Ban_Memo, CEnumCore::TagFormat::TLV_STRING, 1, (unsigned char*)(LPCTSTR)"0");
		}
		else
		{
			// Indicate Unbanning Account.
			socketdata.AddTFLV(CEnumCore::TagName::Ban_Memo, CEnumCore::TagFormat::TLV_STRING, 1, (unsigned char*)(LPCTSTR)"1");
		}

		// Game name.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameName, CEnumCore::TagFormat::TLV_STRING, 
			strGameName.GetLength(), (unsigned char*)(LPCTSTR)strGameName);

		// Game ID.
		_itoa(nGameID, szInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameID, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char *)szInt);

		// Game DB Server city.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_City, CEnumCore::TagFormat::TLV_STRING, 
			strGameDBServerCity.GetLength(), (unsigned char*)(LPCTSTR)strGameDBServerCity);

		// Game DB Server IP.
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_IP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char*)(LPCTSTR)strServerIP); 

		// UnBan time.
		socketdata.AddTFLV(CEnumCore::TagName::Ban_EndTime, CEnumCore::TagFormat::TLV_STRING, 
			strUnBanTime.GetLength(), (unsigned char*)(LPCTSTR)strUnBanTime);

		// UnBan reason.
		socketdata.AddTFLV(CEnumCore::TagName::Ban_Reason, CEnumCore::TagFormat::TLV_STRING,
			strUnBanReason.GetLength(), (unsigned char*)(LPCTSTR)strUnBanReason);

		// Set UnBan time.
		socketdata.AddTFLV(CEnumCore::TagName::Ban_Type, CEnumCore::TagFormat::TLV_INTEGER, sizeof(int), (unsigned char*)"1");

		EnableWindow(FALSE);

		theApp.m_dataOper.SendQuery(socketdata, CEnumCore::Msg_Category::Ban_ADMIN, CEnumCore::ServiceKey::Ban_Open_Query);

		socketdata.Destroy();
	}
	catch(...)
	{
		CString strErr = theApp.m_iniFile.ReadStringValue(INI_ERROR_PROMPT_SECTIONNew, "ConstructTFLV");
		AfxMessageBox(strErr);
	}
}

void CBanQuery::ClearGameNameCombBoxAssociateData()
{
	// Clear.
	std::stack<LPGAME_DB_SERVER_NEW> stackData;
	int nCount = m_cmbGameName.GetCount();
	for (int i=0; i<nCount; i++)
	{
		LPVOID lpData = m_cmbGameName.GetItemDataPtr(i);
		if (-1 == (int)lpData)
			continue;
		LPGAME_INFO_NEW lpgi = (LPGAME_INFO_NEW)lpData;
		ASSERT(NULL != lpgi);

		LPGAME_DB_SERVER_NEW lpgds = lpgi->lplistDBServer;
		while(NULL != lpgds)
		{
			stackData.push(lpgds);
			lpgds = lpgds->lpNext;
		}
		delete lpgi;
	}

	while(!stackData.empty())
	{
		LPGAME_DB_SERVER_NEW lpgds = (LPGAME_DB_SERVER_NEW)stackData.top();
		ASSERT(NULL != lpgds);
		delete lpgds;
		stackData.pop();
	}

	m_cmbGameName.ResetContent();
}

void CBanQuery::ClearGameDBServerCombBoxAssociateData()
{
	int nCount = m_cmbGameServerIp.GetCount();
	for (int i=0; i<nCount; i++)
	{
		DWORD_PTR dwPtr = m_cmbGameServerIp.GetItemData(i);
		if (CB_ERR != dwPtr)
		{
			char* pszIP = (char*)dwPtr;
			delete[] pszIP; 
		}
	}

	m_cmbGameServerIp.ResetContent();
}

//maple add
void CBanQuery::OnBnClickBanTimeOption()
{
	if (BST_CHECKED != m_chkBtnUnbanTimeOption.GetCheck())
	{
		GetDlgItem(IDC_UNBANDATE)->EnableWindow(true);
		GetDlgItem(IDC_UNBANTIME)->EnableWindow(true);
	}
	else
	{
		GetDlgItem(IDC_UNBANDATE)->EnableWindow(false);
		GetDlgItem(IDC_UNBANTIME)->EnableWindow(false);
	}
}
HBRUSH CBanQuery::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);
	return CreateSolidBrush(backColor);
}