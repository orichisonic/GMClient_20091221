// SDOBaseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOBaseDlg.h"


// CSDOBaseDlg 对话框

#include <stack>
// CCG2BaseDlg 对话框

static LPCSTR INI_ERRORPROMPT_SECTION = "MSDO";//"ERRORPROMPT";

IMPLEMENT_DYNAMIC(CSDOBaseDlg, CDialog)
CSDOBaseDlg::CSDOBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSDOBaseDlg::IDD, pParent)
{
	m_strPageSize = theApp.operSDO.ReadValue(INI_ERRORPROMPT_SECTION, "pageSize");
}

CSDOBaseDlg::~CSDOBaseDlg()
{
}

void CSDOBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBBASESERVER, m_cmbGameServer);
	DDX_Control(pDX, IDC_LISTBASELIST, m_listBaseCtrl);
	DDX_Control(pDX, IDC_CMBBASEPAGE, m_cmbPage);
	DDX_Control(pDX, IDC_TABBASE, m_tcbBase);
	DDX_Control(pDX, IDC_DTPBEGIN, dtcLoginDate);
	DDX_Control(pDX, IDC_DTPEND, dtcLogoutDate);
	DDX_Control(pDX, IDC_CMBTYPE, cmbTradeType);
}


BEGIN_MESSAGE_MAP(CSDOBaseDlg, CDialog)
	ON_BN_CLICKED(IDC_BTNBASEIMP, OnBnClickedBtnbaseimp)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABBASE, OnTcnSelchangeTabbase)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSDOBaseDlg 消息处理程序
// CCG2BaseDlg 消息处理程序
BOOL CSDOBaseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	RECT rctDlg;
	GetWindowRect(&rctDlg);

	RECT rctGroup;
	CWnd* pWnd = GetDlgItem(IDC_STATICBASEGRPPAGE);
	pWnd->GetWindowRect(&rctGroup);
	ScreenToClient(&rctGroup);

	RECT rctList;
	rctList.top = rctGroup.bottom + 10;
	rctList.left = rctGroup.left;
	rctList.right = rctGroup.left + (rctDlg.right - rctDlg.left);
	rctList.bottom = rctList.top + (rctDlg.bottom - rctDlg.top);

	m_listBaseCtrl.MoveWindow(CRect(rctList));
	m_listBaseCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	// 获取游戏服务器列表.
	theApp.operSDO.GetServerList();
	EnableWindow(FALSE);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Set data for Ctrl.

void CSDOBaseDlg::InitTableCtrl(TCB_ITEM tidArray[], DWORD dwCount, CString& strSection)
{
	for (int i=0; i<dwCount; i++)
	{
		CString strText = theApp.operSDO.ReadValue(strSection,tidArray[i].strKey);//m_operCG2.ReadValue(strSection, tidArray[i].strKey);
		
		if (tidArray[i].lptid == NULL)
		{
			m_tcbBase.InsertItem(TCIF_TEXT, strText);
		}
		else
		{
			m_tcbBase.InsertItem(TCIF_TEXT | TCIF_PARAM, i, strText, 0, (LPARAM)(tidArray[i].lptid));
			tidArray[i].lptid = NULL;
		}
	}

	m_nCurrentSelIndex = 0;
	m_tcbBase.SetCurSel(m_nCurrentSelIndex);
	LRESULT lres;
	OnTcnSelchangeTabbase(NULL, &lres);
}

void CSDOBaseDlg::ResetCmbCtrl(CComboBox& cmbCtrl)
{
	cmbCtrl.ResetContent();
	cmbCtrl.AddString("1");
	cmbCtrl.SetCurSel(0);
}

// Set recving data to list ctrl.
void CSDOBaseDlg::SetDataForListCtrl(CListCtrl &listCtrl, CSocketData& socketdata, CComboBox& cmbCtrl)
{
	listCtrl.DeleteAllItems();

	int nTFLVColNum = socketdata.getColTFLVNum();
	if (nTFLVColNum <= 1)
		return;

	CHeaderCtrl* pListCtrlHeader = listCtrl.GetHeaderCtrl();
	ASSERT(NULL != pListCtrlHeader);
	int nListColNum = pListCtrlHeader->GetItemCount();

	// Set header for list ctrl.
	HDITEM headerData;
	headerData.mask = HDI_LPARAM;
	if (0 == nListColNum)
	{
		for (int i=0; i<nListColNum; i++)
			listCtrl.DeleteColumn(i);

		// List column number.
		nListColNum = nTFLVColNum-1;

		// Construct columns again.
		for (int i=0; i<nListColNum; i++)
		{
			// Get column title name from config file.
			// The first effective TLFV is from 1.
			CGlobalStruct::TFLV tflv= socketdata.getTLV(1, i+1);
			//if (!IsDataShownInListCtrl(tflv.m_tagName))
			//	continue;

			///CString strTitle = GetListCtrlTitle(tflv.m_tagName);
			CString strTitle=theApp.operSDO.ReadValue(INI_ERRORPROMPT_SECTION,theApp.operSDO.tagToStr(tflv.m_tagName));
			int nIndex = listCtrl.InsertColumn(i, (LPCTSTR)strTitle, LVCFMT_CENTER, LIST_CTRL_COL_WIDTH);

			headerData.lParam = (LPARAM)(unsigned short)tflv.m_tagName;
			pListCtrlHeader->SetItem(nIndex, &headerData);
		}
	}

	// Total page count.
	CGlobalStruct::TFLV tflvPageCount = socketdata.getTLVByTag(CEnumCore::TagName::PageCount, 1);
	char szPageNum[MAX_PATH] = {0};
	strncpy(szPageNum, (char *)tflvPageCount.lpdata, tflvPageCount.m_tvlength);
	int nPageNum = atoi((char *)szPageNum);

	// Current Max Page number shown in page-commboBox.
	CString strMaxPageNum;
	cmbCtrl.GetLBText(cmbCtrl.GetCount()-1, strMaxPageNum);
	int MaxPageNum = atoi(LPCTSTR(strMaxPageNum));

	// Set page number for page-combobox.
	if (nPageNum != MaxPageNum)
	{
		cmbCtrl.ResetContent();
		for (int i=1; i<=nPageNum; i++)
		{
			CString strText;
			strText.Format("%d", i);
			cmbCtrl.AddString((LPCTSTR)strText);
		}
		cmbCtrl.SetCurSel(0);
	}

	// Insert data to ListCtrl.
	headerData.mask = HDI_LPARAM;
	int nTFLVRowNum = socketdata.getQueryNum();
	for (int i=0; i<nTFLVRowNum; i++)
	{
		listCtrl.InsertItem(i, "");
		for (int j=0; j<nListColNum; j++)
		{
			// The first effective TLFV is from 1.
			CGlobalStruct::TFLV tflv= socketdata.getTLV(i+1, j+1);
			//if (!IsDataShownInListCtrl(tflv.m_tagName))
			///	continue;

			//pListCtrlHeader->GetItem(j, &headerData);
			//LPARAM lpData = (LPARAM)(unsigned short)tflv.m_tagName;
			//if (headerData.lParam != lpData)
			//{
			//	ASSERT(FALSE);
			//	continue;
			//}

			char szBuff[MAX_PATH] = {0};
			strncpy(szBuff, (LPCTSTR)tflv.lpdata, tflv.m_tvlength);
			///listCtrl.SetItemText(i, j, szBuff);
			//maple add
			unsigned short tmpTagName=tflv.m_tagName;
			/*if(tmpTagName == CEnumCore::TagName::CG2_Sex)//性别需要用文字显示
			{
				if(!strcmp("1", szBuff))//性别为1的话
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_male"));//显示为男
				}
				else//性别不为1的话
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_female"));//显示为女
				}
			}


			else if(tmpTagName == CEnumCore::TagName::CG2_IsOnline)
			{
				if(!strcmp("1", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIA_Code_isOnline"));
				}
				else if(!strcmp("0", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIA_Code_notOnline"));
				}

			}
			else if(tmpTagName == CEnumCore::TagName::CG2_Ip)
			{
				if(!strcmp("", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIA_Code_noIP"));
				}
			}

			else if(tmpTagName == CEnumCore::TagName::CG2_InPrison)
			{
				if(!strcmp("0", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_NotInPrison"));
				}
				else
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_InPrison"));
				}
			}
			else if(tmpTagName == CEnumCore::TagName::CG2_isUse)
			{
				if(!strcmp("0", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","SL_Hint_isUse"));
				}
			}
			else if(tmpTagName == CEnumCore::TagName::CG2_isChairman)
			{
				if(!strcmp("1", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_IsChairman"));
				}
				if(!strcmp("0", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_NoChairman"));
				}
			}
			else if(tmpTagName == CEnumCore::TagName::CG2_tempRank)
			{
				if(!strcmp("NULL", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_NoRank"));
				}
				if(!strcmp("0", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_NoRank"));
				}
			}

			else if(tmpTagName == CEnumCore::TagName::CG2_PetNewName)
			{
				if(!strcmp("", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_NoPetNewName"));
				}
			}
			else if(tmpTagName == CEnumCore::TagName::CG2_OwnName)
			{
				if(!strcmp("", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_NoOwnName"));
				}
			}
			else if(tmpTagName == CEnumCore::TagName::CG2_category)
			{
				if(!strcmp("pet", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_CatePet"));
				}
				else if(!strcmp("item", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_CateItem"));
				}
				else if(!strcmp("skill", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_CateSkill"));
				}
				else if(!strcmp("char", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_CateChar"));
				}
				else if(!strcmp("account", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_CateAccount"));
				}
				else if(!strcmp("gold", szBuff))
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","UIC_Code_CateGold"));
				}
			}
			else if(tmpTagName == CEnumCore::TagName::CG2_TypeName)
			{
				if(!strcmp("0", szBuff))//typename为0
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","BU_UI_STRBANTYPEROLE"));
				}
				else
				{
					listCtrl.SetItemText(i,j,theApp.operCG2.ReadValue("MCG2","BU_UI_STRBANTYPEACCOUNT"));
				}
			}
			else*/
				listCtrl.SetItemText(i,j,szBuff);
		}
	}

	RECT rctDlg;
	GetWindowRect(&rctDlg);
	ScreenToClient(&rctDlg);

	RECT rctGroup;
	CWnd* pWnd = GetDlgItem(IDC_STATICBASEGRPPAGE);
	pWnd->GetWindowRect(&rctGroup);
	ScreenToClient(&rctGroup);

	// Set list ctrl.
	RECT rctList;
	rctList.left = rctGroup.left;
	rctList.top = rctGroup.bottom + 10;
	rctList.right = rctDlg.right - 20;
	rctList.bottom = rctDlg.bottom - 10;
	listCtrl.MoveWindow(CRect(rctList));
}

CString CSDOBaseDlg::GetDataFromListCtrl(CListCtrl &listCtrl, CEnumCore::TagName tagName, int nRowIndex/* = -1*/)
{
	CHeaderCtrl* pListCtrlHeader = listCtrl.GetHeaderCtrl();
	ASSERT(NULL != pListCtrlHeader);
	int nListColNum = pListCtrlHeader->GetItemCount();

	if( -1 == nRowIndex)
	{
		nRowIndex = listCtrl.GetNextItem(-1, LVNI_SELECTED);
	}

	CString strPetData("");

	HDITEM headerData;
	headerData.mask = HDI_LPARAM;
	for (int i=0; i<nListColNum; i++)
	{
		pListCtrlHeader->GetItem(i, &headerData);
		if (headerData.lParam == (LPARAM)(unsigned short)tagName)
		{
			strPetData = listCtrl.GetItemText(nRowIndex, i);
			break;
		}
	}

	/////////ASSERT(!strPetData.IsEmpty());

	return strPetData;
}

//////////////////////////////////////////////////////////////////////
// Clear data for ctrl.

void CSDOBaseDlg::ClearTabCtrlData()
{
	std::stack<LPTCB_ITEM_DATA> stackTabItemData;
	int nItemCount = m_tcbBase.GetItemCount();
	for (int i=0; i<nItemCount; i++)
	{
		TCITEM tabItem;
		tabItem.mask = TCIF_PARAM;
		m_tcbBase.GetItem(i, &tabItem);

		LPTCB_ITEM_DATA lptid = (LPTCB_ITEM_DATA)tabItem.lParam;
		while (lptid != NULL)
		{
			stackTabItemData.push(lptid);
			lptid = lptid->pNext;
		}
	}

	while (!stackTabItemData.empty())
	{
		LPTCB_ITEM_DATA lptid = stackTabItemData.top();
		stackTabItemData.pop();
		delete lptid;
	}
}

//////////////////////////////////////////////////////////////////
// Create child ctrl.

void CSDOBaseDlg::CreateCtrlEdit(CEdit& editCtrl, DWORD dwAboveCtrlID, DWORD dwEditID)
{
	RECT rct;
	CWnd* pWnd = GetDlgItem(dwAboveCtrlID);
	ASSERT(pWnd != NULL);

	pWnd->GetWindowRect(&rct);
	ScreenToClient(&rct);

	DWORD dwHight = rct.bottom - rct.top;
	rct.top = rct.bottom + 10;
	rct.bottom = rct.top + dwHight;

	//	DWORD dwExStyle = WS_EX_STATICEDGE | WS_EX_CLIENTEDGE;
	pWnd = GetDlgItem(IDC_EDITBASEREF);
	ASSERT(pWnd != NULL);
	DWORD dwStyle = pWnd->GetStyle();
	DWORD dwExStyle = pWnd->GetExStyle();

	editCtrl.CreateEx(dwExStyle, "Edit", NULL, dwStyle, rct, this, dwEditID);

	CFont* pRefFont = pWnd->GetFont();
	LOGFONT lf;
	pRefFont->GetLogFont(&lf);

	CFont* pFont = editCtrl.GetFont();
	ASSERT(pFont == NULL);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	editCtrl.SetFont(pFont);
}

void CSDOBaseDlg::CreateCtrlStatic(CStatic& staticCtrl, DWORD dwAboveStaticCtrlID, DWORD dwStaticID)
{
	RECT rct;
	CWnd* pWnd = GetDlgItem(dwAboveStaticCtrlID);
	ASSERT(NULL != pWnd);

	pWnd->GetWindowRect(&rct);
	ScreenToClient(&rct);
	DWORD dwHight = rct.bottom - rct.top;
	rct.top = rct.bottom + 20;
	rct.bottom = rct.top + dwHight;

	DWORD dwStyle = pWnd->GetStyle();
	DWORD dwExStyle = pWnd->GetExStyle();

	staticCtrl.CreateEx(dwExStyle, "Static", "静态控件：", dwStyle, rct, this, dwStaticID);

	CFont* pRefFont = pWnd->GetFont();
	LOGFONT lf;
	pRefFont->GetLogFont(&lf);

	CFont* pFont = staticCtrl.GetFont();
	ASSERT(pFont == NULL);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	staticCtrl.SetFont(pFont);
}

void CSDOBaseDlg::CreateCtrlComCmb(CComboBox& cmbCtrl, DWORD dwCmbID, DWORD dwAboveCtrlID/* = 0*/)
{	
/*	RECT rct;
	DWORD dwStyle;
	DWORD dwExStyle;
	CWnd* pWnd = NULL;
	if (dwAboveCtrlID != 0)
	{
		pWnd = GetDlgItem(dwAboveCtrlID);
		ASSERT(NULL != pWnd);
		pWnd->GetWindowRect(&rct);
		ScreenToClient(&rct);
		DWORD dwHight = rct.bottom - rct.top;
		rct.top = rct.bottom + 10;
		rct.bottom = rct.top + dwHight + 100;
	}
	else
	{
		pWnd = &m_cmbPage;
		pWnd->GetWindowRect(&rct);
		rct.bottom += 100;
		ScreenToClient(&rct);
	}

	dwStyle = pWnd->GetStyle();
	dwExStyle = pWnd->GetExStyle();

	dwStyle |= WS_VSCROLL;
	cmbCtrl.CreateEx(dwExStyle, "ComboBox", NULL, dwStyle, rct, this, dwCmbID);

	CFont* pRefFont = pWnd->GetFont();
	LOGFONT lf;
	pRefFont->GetLogFont(&lf);

	CFont* pFont = cmbCtrl.GetFont();
	ASSERT(pFont == NULL);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	cmbCtrl.SetFont(pFont);

	// 默认页索引为1.
	if (dwAboveCtrlID == 0)
	{
		cmbCtrl.AddString("1");
		cmbCtrl.SetCurSel(0);
	}*/

	RECT rct,ComRct;
	DWORD dwStyle;
	DWORD dwExStyle;
	CWnd* pWnd = NULL;
	CWnd* pComWnd = GetDlgItem(IDC_CMBBASEPAGE);
	if (dwAboveCtrlID != 0)////////不是翻页的ComboBox
	{
		pWnd = GetDlgItem(dwAboveCtrlID);
		ASSERT(NULL != pWnd);
		pWnd->GetWindowRect(&rct);
		DWORD dwHight = rct.bottom - rct.top;
		DWORD dwWidth = rct.right - rct.left;//宽度
		rct.top = rct.bottom + 10;
		rct.bottom = rct.top + dwHight + 100;
		rct.right = rct.left + 110 +30;
		ScreenToClient(&rct);

		dwStyle = pComWnd->GetStyle();
		dwExStyle = pComWnd->GetExStyle();

		dwStyle |= WS_VSCROLL;
		cmbCtrl.CreateEx(dwExStyle, "ComboBox", NULL, dwStyle, rct, this, dwCmbID);

	}
	else
	{
		pWnd = &m_cmbPage;
		pWnd->GetWindowRect(&rct);
		rct.bottom += 100;
		ScreenToClient(&rct);

		dwStyle = pWnd->GetStyle();
		dwExStyle = pWnd->GetExStyle();

		dwStyle |= WS_VSCROLL;
		cmbCtrl.CreateEx(dwExStyle, "ComboBox", NULL, dwStyle, rct, this, dwCmbID);
	}

	

	CFont* pRefFont = pWnd->GetFont();
	LOGFONT lf;
	pRefFont->GetLogFont(&lf);

	CFont* pFont = cmbCtrl.GetFont();
	ASSERT(pFont == NULL);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	cmbCtrl.SetFont(pFont);

	// 默认页索引为1.
	if (dwAboveCtrlID == 0)
	{
		cmbCtrl.AddString("1");
		cmbCtrl.SetCurSel(0);
	}
}

void CSDOBaseDlg::CreateCtrlList(CListCtrl& listCtrl, DWORD dwListID)
{
	RECT rctList;
	m_listBaseCtrl.GetWindowRect(&rctList);
	ScreenToClient(&rctList);

	DWORD dwExStyle = m_listBaseCtrl.GetExStyle();
	DWORD dwStyle = m_listBaseCtrl.GetStyle();

	listCtrl.CWnd::CreateEx(dwExStyle, "SysListView32", NULL, dwStyle, rctList, this, dwListID);

	DWORD dwListExStyle = m_listBaseCtrl.GetExtendedStyle();
	listCtrl.SetExtendedStyle(dwListExStyle);
}

void CSDOBaseDlg::MoveImpButton(DWORD dwAboveCtrlID, DWORD dwButtonID)
{

	RECT rct;
	CWnd* pWnd=NULL;
	
	if(dwAboveCtrlID != 0)
	{
		pWnd = GetDlgItem(dwAboveCtrlID);
		ASSERT(NULL != pWnd);
		pWnd->GetWindowRect(&rct);
		ScreenToClient(&rct);

		RECT rctBtn;
		pWnd = GetDlgItem(IDC_BTNBASEIMP);
		ASSERT(NULL != pWnd);
		pWnd->GetWindowRect(&rctBtn);
		
		int x = rct.left;
		int y = rct.bottom + 15;
		int nWidth = rctBtn.right - rctBtn.left;
		int nHeight = rctBtn.bottom - rctBtn.top;
		pWnd->MoveWindow(x, y, nWidth, nHeight);
	}
	else
	{
		pWnd = GetDlgItem(IDC_TABBASE);
		ASSERT(NULL != pWnd);
		pWnd->GetWindowRect(&rct);
		ScreenToClient(&rct);

		RECT rctBtn;
		pWnd = GetDlgItem(IDC_BTNBASEIMP);
		ASSERT(NULL != pWnd);
		pWnd->GetWindowRect(&rctBtn);
		
		DWORD dwHight=rctBtn.bottom-rctBtn.top;
		DWORD dwWidth=rctBtn.right-rctBtn.left;

		rct.left = rct.right - dwWidth - 40;
		rct.right = rct.left + dwWidth;
		rct.top = rct.bottom + 20;
		rct.bottom = rct.top + dwHight;
		pWnd->MoveWindow(&rct);
	}
}

//创建button
void CSDOBaseDlg::CreateCtrlButton(CButton& buttonCtrl, DWORD dwAboveCtrlID, DWORD dwButtonID)
{

	RECT rct;
	CWnd* pWnd = GetDlgItem(dwAboveCtrlID);
	ASSERT(NULL != pWnd);
	CWnd* pBtnWnd = GetDlgItem(IDC_BTNBASEIMP);
	ASSERT(NULL != pBtnWnd);

	pWnd->GetWindowRect(&rct);
	ScreenToClient(&rct);
	DWORD dwHight = rct.bottom - rct.top;
	rct.top = rct.bottom + 20;
	rct.bottom = rct.top + dwHight;
	rct.right = rct.left + 60;

	//DWORD dwStyle = pWnd->GetStyle();
	//DWORD dwExStyle = pWnd->GetExStyle();//pWnd = GetDlgItem(IDC_BTNBASEIMP);

	DWORD dwStyle = pBtnWnd->GetStyle();
	DWORD dwExStyle = pBtnWnd->GetExStyle();

	buttonCtrl.CreateEx(dwExStyle,"Button",_TEXT("确定"),dwStyle,rct,this,dwButtonID);
	
	CFont* pRefFont = pWnd->GetFont();
	LOGFONT lf;
	pRefFont->GetLogFont(&lf);
	CFont* pFont = buttonCtrl.GetFont();
	ASSERT(pFont == NULL);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	buttonCtrl.SetFont(pFont);
}

//创建DataTimePicker控件
void CSDOBaseDlg::CreateCtrlDateTime(CDateTimeCtrl& datatimeCtrl, DWORD dwAboveCtrlID, DWORD dwDateTimeID)//CDateTimeCtrl
{
	RECT rct;
	CWnd* pWnd = GetDlgItem(dwAboveCtrlID);
	ASSERT(NULL != pWnd);

	pWnd->GetWindowRect(&rct);
	ScreenToClient(&rct);
	DWORD dwHight = rct.bottom - rct.top;
	rct.top = rct.bottom + 10;
	rct.bottom = rct.top + dwHight;

	CWnd* pDTPWnd = GetDlgItem(IDC_DTPBEGIN);
	ASSERT(NULL != pDTPWnd);

	DWORD dwStyle = pDTPWnd->GetStyle();//pWnd->GetStyle();
	//DWORD dwExStyle = pDTPWnd->GetExStyle();//pWnd->GetExStyle();

	datatimeCtrl.Create(dwStyle, rct, this, dwDateTimeID);
	//CDateTimeCtrl* pCtrl=NULL;
	//pCtrl = new CDateTimeCtrl;
	//pCtrl->Create(dwStyle, rct, this, dwDateTimeID);
}

void CSDOBaseDlg::OnBnClickedBtnbaseimp()
{
	ImplementUpdateOperation(m_nCurrentSelIndex);
}

void CSDOBaseDlg::OnBnClickedOk()
{
	QueryOperation(m_nCurrentSelIndex);
}

//查询玩家的角色信息
void CSDOBaseDlg::QueryCharInfo(CString &curPage)
{
	int nTFLVNum = 1;

	// Server IP.
	nTFLVNum++;
	CString strServerIP = GetGameServerIP();
	ASSERT(!strServerIP.IsEmpty());

	//Server Name
	nTFLVNum++;
	CString strServerName = GetGameServerName();

	// Account.
	nTFLVNum++;
	CString strAccount = GetAccount();

	// Nick.
	nTFLVNum++;
	CString strNick = GetNick();

	if (strAccount.IsEmpty() && strNick.IsEmpty() && m_nCurrentSelIndex == 0)
	{
		CString strError = theApp.operSDO.ReadValue(INI_ERRORPROMPT_SECTION, "AccountOrNickInput");
		AfxMessageBox(strError);
		return;
	}

	// Page index.
	nTFLVNum++;
	///CString strPageIndex = GetCmbCurSelText(m_cmbAccountInfoPage);
	CString strPageIndex = curPage;

	try
	{
		CSocketData socketdata;	
		ASSERT(5<=nTFLVNum && nTFLVNum<=6);
		socketdata.InitCreate(1, nTFLVNum);

		// 服务器IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);
		
		//服务器名
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName, CEnumCore::TagFormat::TLV_STRING, 
			strServerName.GetLength(), (unsigned char *)(LPCTSTR)strServerName);

		//玩家帐号.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account, CEnumCore::TagFormat::TLV_STRING,
			strAccount.GetLength(), (unsigned char *)(LPCTSTR)strAccount);

		//玩家昵称.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName, CEnumCore::TagFormat::TLV_STRING, 
			strNick.GetLength(), (unsigned char *)(LPCTSTR)strNick);

		// 开始页.
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,
			strPageIndex.GetLength(), (unsigned char *)(LPCTSTR)strPageIndex);

		// 每页记录数.
		socketdata.AddTFLV(CEnumCore::TagName::PageSize, CEnumCore::TagFormat::TLV_INTEGER,
			m_strPageSize.GetLength(), (unsigned char *)(LPCTSTR)m_strPageSize);

		int nDataLen = socketdata.EnBody();
		//m_operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, CEnumCore::ServiceKey::CG2_Account_Query);
		if(m_nCurrentSelIndex == 0)
			theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, CEnumCore::ServiceKey::SDO_CHARACTERINFO_QUERY);
		else if(m_nCurrentSelIndex == 2)
			theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, CEnumCore::ServiceKey::SDO_MEMBERBANISHMENT_QUERY);//封停列表

		EnableWindow(FALSE);
	}
	catch(...)
	{
	}
}

//查询玩家的其他信息
void CSDOBaseDlg::QueryOtherInfo(CEnumCore::ServiceKey eServiceKey, CString& curPage, CListCtrl& listCtrl)
{

	CString strServerIP = GetGameServerIP();
	CString strServerName = GetGameServerName();
	CString strAccount = GetDataFromListCtrl(listCtrl, CEnumCore::TagName::SDO_Account);
	CString strCharID = GetDataFromListCtrl(listCtrl, CEnumCore::TagName::SDO_UserIndexID);
	CString strPageIndex = curPage;//GetCmbCurSelText(*pComboBox);

	try
	{
		CSocketData socketdata;	
		socketdata.InitCreate(1, 6);

		// 服务器IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);

		//服务器名
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName, CEnumCore::TagFormat::TLV_STRING, 
			strServerName.GetLength(), (unsigned char *)(LPCTSTR)strServerName);

		// 玩家帐号.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account, CEnumCore::TagFormat::TLV_STRING,
			strAccount.GetLength(), (unsigned char *)(LPCTSTR)strAccount);

		// 角色ID.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID, CEnumCore::TagFormat::TLV_STRING,
			strCharID.GetLength(), (unsigned char *)(LPCTSTR)strCharID);

		// 开始页.
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,
			strPageIndex.GetLength(), (unsigned char *)(LPCTSTR)strPageIndex);

		// 每页记录数.
		socketdata.AddTFLV(CEnumCore::TagName::PageSize, CEnumCore::TagFormat::TLV_INTEGER,
			m_strPageSize.GetLength(), (unsigned char *)(LPCTSTR)m_strPageSize);

		int nDataLen = socketdata.EnBody();
		theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, eServiceKey);

		EnableWindow(FALSE);
	}
	catch(...)
	{
	}
}

void CSDOBaseDlg::OnBnClickedCancel()
{
//	ClearTabCtrlData();
//	ClearDataForCtrl();

//	CDialog::OnCancel();

///	ShowWindow(SW_HIDE);

	//maple add
	CWnd *pWnd=GetDlgItem(IDOK);
	pWnd->ShowWindow(SW_SHOW);


	m_tcbBase.SetCurSel(0);
	LRESULT lres;
	OnTcnSelchangeTabbase(NULL, &lres);
	m_cmbGameServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITBASEACCOUNT,"");
	SetDlgItemText(IDC_EDITBASENICK,"");
}

/////////////////////////////////////////////////////
// Receiving data.

void CSDOBaseDlg::SetRecvData(unsigned char * lpRecvbuf, int nLen, CEnumCore::Message_Tag_ID msgTagID)
{
	ASSERT(NULL != lpRecvbuf);
	
	EnableWindow(TRUE);

	CSocketData socketdata;
	socketdata.Create(nLen/8);
	socketdata.DeBody(lpRecvbuf, nLen);

	int nTFLVCount = socketdata.getAllTFLV();
	if (0 == nTFLVCount)
		return;

	CGlobalStruct::TFLV tflvErr = socketdata.getTLVBynIndex(1);
	if ((unsigned short)tflvErr.m_tagName == CEnumCore::TagName::MESSAGE)
	{
		AfxMessageBox((LPTSTR)tflvErr.lpdata);
	}

	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP:		// 游戏服务器名称/IP.
		InitGameServerComboBox(socketdata);
		break;
	default:
		ProcessRecvData(socketdata, msgTagID);
		break;
	}
}

// Game server information.
void CSDOBaseDlg::InitGameServerComboBox(CSocketData& socketdata)
{
	int nTFLVNum = socketdata.getAllTFLV();
	for (int i=1; i<nTFLVNum; i++)
	{
		CGlobalStruct::TFLV tflvServerCity = socketdata.getTLVBynIndex(i);
		if ((unsigned short)tflvServerCity.m_tagName == CEnumCore::TagName::ServerInfo_City)
		{
			//大区名.
			char szServerCity[MAX_PATH] = {0};
			ASSERT((unsigned short)tflvServerCity.m_tagFormat == CEnumCore::TagFormat::TLV_STRING);
			strncpy(szServerCity, (const char *)tflvServerCity.lpdata, tflvServerCity.m_tvlength);
			int nIndex = m_cmbGameServer.AddString((LPCTSTR)szServerCity);

			// 服务器IP.
			CGlobalStruct::TFLV tflvServerIP = socketdata.getTLVBynIndex(i-1);
			ASSERT((unsigned short)tflvServerIP.m_tagName == CEnumCore::TagName::ServerInfo_IP);
			ASSERT((unsigned short)tflvServerIP.m_tagFormat == CEnumCore::TagFormat::TLV_STRING);
			char* pszIP = new char[tflvServerIP.m_tvlength+1];
			memset(pszIP, 0, tflvServerIP.m_tvlength+1);
			strncpy(pszIP, (const char *)tflvServerIP.lpdata, tflvServerIP.m_tvlength);
			m_cmbGameServer.SetItemData(nIndex, (DWORD_PTR)pszIP);
		}
	}

	m_cmbGameServer.SetCurSel(0);
}

//////////////////////////////////////////////////////////////////////

void CSDOBaseDlg::OnTcnSelchangeTabbase(NMHDR *pNMHDR, LRESULT *pResult)
{
	TCITEM tcItem;

	// 隐藏控件.
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	BOOL bRet = m_tcbBase.GetItem(m_nCurrentSelIndex, &tcItem);
	ASSERT(bRet);
	LPTCB_ITEM_DATA lptid = (LPTCB_ITEM_DATA)tcItem.lParam;
	while (NULL != lptid)
	{
		if (lptid->dwCtrlID != 0)
			GetDlgItem(lptid->dwCtrlID)->ShowWindow(SW_HIDE);

		lptid = lptid->pNext;
	}
	lptid = NULL;


	// 显示控件.
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	int nSel = m_tcbBase.GetCurSel();
	bRet = m_tcbBase.GetItem(nSel, &tcItem);
	ASSERT(bRet);
	lptid = (LPTCB_ITEM_DATA)tcItem.lParam;
	while (NULL != lptid)	
	{
		if (lptid->dwCtrlID != 0)
			GetDlgItem(lptid->dwCtrlID)->ShowWindow(SW_SHOW);

		lptid = lptid->pNext;
	}
	lptid = NULL;


	OnSelectTabCtrlItem(m_nCurrentSelIndex, nSel);

	m_nCurrentSelIndex = nSel;

	*pResult = 0;
}

void CSDOBaseDlg::SetTabCtrlItemCurSel(int nCurSel)
{
	ASSERT(nCurSel <= m_tcbBase.GetItemCount());

	// 模拟选择tab标签.
	m_tcbBase.SetCurSel(nCurSel);

	LRESULT lres;
	OnTcnSelchangeTabbase(NULL, &lres);
}

int CSDOBaseDlg::GetTabCtrlItemCurSel()
{
	return m_tcbBase.GetCurSel();	
}

////////////////////////////////////////
// 指定列表框彈出菜單.
void CSDOBaseDlg::PopupMenuForListCtrlRClick(CListCtrl& listCtrl, CMenu& menu, POINT& point)
{
	if (0 == listCtrl.GetItemCount())
		return;

	POINT pointMenu;
	pointMenu.x = point.x;
	pointMenu.y = point.y;
	listCtrl.ClientToScreen(&pointMenu);
	menu.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, pointMenu.x, pointMenu.y, this);
}
/////////////////////////////////////////////////////////
// Get data from control.

CString CSDOBaseDlg::GetGameServerIP()
{
	// Game Server IP.
	int nSel = m_cmbGameServer.GetCurSel();
	DWORD_PTR dwIP = m_cmbGameServer.GetItemData(nSel);
	ASSERT(dwIP !=  CB_ERR );

	return CString((LPCSTR)dwIP);
}

CString CSDOBaseDlg::GetGameServerName()
{
	CString strGameName;
	GetDlgItemText(IDC_CMBBASESERVER,strGameName);
	
	return strGameName;
}

CString CSDOBaseDlg::GetAccount()
{
	CString Account;
	GetDlgItem(IDC_EDITBASEACCOUNT)->GetWindowText(Account);

	return Account;
}

CString CSDOBaseDlg::GetNick()
{
	CString strNick;
	GetDlgItem(IDC_EDITBASENICK)->GetWindowText(strNick);

	return strNick;
}

CString CSDOBaseDlg::GetCmbCurSelText(CComboBox& cmbPage)
{
	CString strCurText;
	int nSel = cmbPage.GetCurSel();
	cmbPage.GetLBText(nSel, strCurText);

	return strCurText;
}
void CSDOBaseDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DestroyWindow();
	ClearDataForCtrl();

	CDialog::OnClose();
}

HBRUSH CSDOBaseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}
