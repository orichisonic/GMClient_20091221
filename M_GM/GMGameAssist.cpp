// GMGameAssist.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_GM.h"
#include "GMGameAssist.h"
#include ".\gmgameassist.h"

// GMGameAssist �Ի���

IMPLEMENT_DYNAMIC(GMGameAssist, CDialog)
GMGameAssist::GMGameAssist(CWnd* pParent /*=NULL*/)
	: CDialog(GMGameAssist::IDD, pParent)
	, exportFilePath(_T(""))
	, importFilePath(_T(""))
{
}

GMGameAssist::~GMGameAssist()
{
}

void GMGameAssist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBGAMENAME, cmbGame);
	DDX_Control(pDX, IDC_CMBASSIST, cmbAssit);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_CMBTYPE, cmbType);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Text(pDX, IDC_EDITEXPORT, exportFilePath);
	DDX_Text(pDX, IDC_EDITIMPORT, importFilePath);
	DDX_Control(pDX, IDC_LISTBANBATCH, listAccountImport);
	DDX_Control(pDX, IDC_LISTVIP, listVIPAccount);
}


BEGIN_MESSAGE_MAP(GMGameAssist, CDialog)
	ON_CBN_SELCHANGE(IDC_CMBGAMENAME, OnCbnSelchangeCmbgamename)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)	
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_BN_CLICKED(IDC_BTNBAN, OnBnClickedBtnban)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDC_BTNSTART, OnBnClickedBtnstart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTNEXPORT, &GMGameAssist::OnBnClickedBtnExport)
	ON_BN_CLICKED(IDC_BTNIMPORT, &GMGameAssist::OnBnClickedBtnImport)
	ON_BN_CLICKED(IDC_BTNBANBATCH, &GMGameAssist::OnBnClickedBtnBanBatch)
	ON_BN_CLICKED(IDC_CHECKVIP, &GMGameAssist::OnBnClickedCheckVip)
	ON_BN_CLICKED(IDC_BTNCHECKACCOUNTALL, &GMGameAssist::OnBnClickedBtnCheckAccountAll)
END_MESSAGE_MAP()


// GMGameAssist ��Ϣ�������

// ��ʼ���Ի���
BOOL GMGameAssist::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// ��ʼ����ʾ�ַ�
	ShowBanPlayer(SW_HIDE);
	ShowExcelBanPlayer(SW_HIDE);

	GameName = "";
	AssitType = 0;
	iIndex = 0;
	iPageSize = 0 ;
	refreshTime = 5;
	iRefresh = false;
	
	CRect rs;
	GetClientRect(rs);; //��ȡ�Ի���Ĵ�С��Ϣ

	CRect srcRect;
	CRect newRect;

	if(GrpSearch.m_hWnd != NULL)
	{
		GrpSearch.GetWindowRect(srcRect);//��ȡGrpSearch�Ĵ�С��Ϣ
		grpHeight = srcRect.bottom - srcRect.top;//�õ�GrpSearch�ĸ߶���Ϣ

		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + grpHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpSearch.MoveWindow(newRect);//���ú�GrpSearch��λ��
	}

	if(tbcResult.m_hWnd != NULL)
	{
		tbcResult.GetWindowRect(srcRect);//��ȡtbcResult�Ĵ�С��Ϣ
		tbcHeight = srcRect.bottom - srcRect.top;//�õ�tbcResult�ĸ߶���Ϣ

		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + tbcHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		tbcResult.MoveWindow(newRect);//���ú�tbcResult��λ��
	}

	if(GrpPage.m_hWnd != NULL)
	{
		GrpPage.GetWindowRect(srcRect);//��ȡGrpPage�Ĵ�С��Ϣ
		grpPHeight = srcRect.bottom - srcRect.top;//�õ�GrpPage�ĸ߶���Ϣ

		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}
	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//���ú�listResult��λ��
	}
	if(listAccountImport.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = (rs.right + rs.left)/2 -10;
		
		listAccountImport.MoveWindow(newRect);//���ú�listAccountImport��λ��
	}
	if(listVIPAccount.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = (rs.right + rs.left)/2;
		newRect.right = rs.right - 10;

		listVIPAccount.MoveWindow(newRect);//���ú�listVIPAccount��λ��
	}

	

	dlgStatus = theApp.operGM.ReadIntValue("MGM","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	QueryGameList();


	//�趨clistctrl���
	//////////////////////////////////////////////////////////////////////
	LONG lStyle;
	lStyle = GetWindowLong(listAccountImport.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(listAccountImport.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = listAccountImport.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	listAccountImport.SetExtendedStyle(dwStyle); //������չ���
	//////////////////////////////////////////////////////////////////////
	lStyle;
	lStyle = GetWindowLong(listVIPAccount.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(listVIPAccount.m_hWnd, GWL_STYLE, lStyle);//����style

	dwStyle = listVIPAccount.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	listVIPAccount.SetExtendedStyle(dwStyle); //������չ���

	listVIPAccount.InsertColumn(0, "����ʺ�", LVCFMT_LEFT, 160);
	///////////////////////////////////////////////////////////////////////

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void GMGameAssist::InitUI()
{
	SetWindowText(theApp.operGM.ReadValue("MGM","GA_UI_GameAssist"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operGM.ReadValue("MGM","OL_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLGAMENAME,theApp.operGM.ReadValue("MGM","OL_UI_LblGame"));
	SetDlgItemText(IDC_LBLASSIST,theApp.operGM.ReadValue("MGM","GA_UI_LBLASSIST"));
	SetDlgItemText(IDC_LBLSERVERNAME,theApp.operGM.ReadValue("MGM","GA_UI_Server"));
	SetDlgItemText(IDSEARCH,theApp.operGM.ReadValue("MGM","Search"));
	SetDlgItemText(IDCANCEL,theApp.operGM.ReadValue("MGM","Close"));
	SetDlgItemText(IDSEARCH,theApp.operGM.ReadValue("MGM","Search"));
	SetDlgItemText(IDC_LBLCIRCLE,theApp.operGM.ReadValue("MGM","GA_UI_LBLCircle"));
	SetDlgItemText(IDC_EDITMINUTE,"5");
	SetDlgItemText(IDC_LBLMINUTE,theApp.operGM.ReadValue("MGM","GA_UI_LblMinute"));
	SetDlgItemText(IDC_BTNSTART,theApp.operGM.ReadValue("MGM","GA_UI_BTNSTART"));

	cmbAssit.AddString(theApp.operGM.ReadValue("MGM","GA_UI_AllType"));
	cmbAssit.AddString(theApp.operGM.ReadValue("MGM","GA_UI_MemoryTool"));
	cmbAssit.AddString(theApp.operGM.ReadValue("MGM","GA_UI_SpeedTool"));
	cmbAssit.AddString(theApp.operGM.ReadValue("MGM","GA_UI_KeyTool"));
	cmbAssit.AddString(theApp.operGM.ReadValue("MGM","GA_UI_PackTool"));
	cmbAssit.AddString(theApp.operGM.ReadValue("MGM","GA_UI_ProcessTool"));
	cmbAssit.AddString(theApp.operGM.ReadValue("MGM","GA_UI_MasmTool"));
	cmbAssit.AddString(theApp.operGM.ReadValue("MGM","GA_UI_TestTool"));
	cmbAssit.AddString(theApp.operGM.ReadValue("MGM","GA_UI_PrayayaTool"));
	cmbAssit.AddString(theApp.operGM.ReadValue("MGM","GA_UI_OtherTool"));

	cmbAssit.SetCurSel(0);

	tbcResult.InsertItem(0,theApp.operGM.ReadValue("MGM","GA_UI_tpgGameAssist"));
	tbcResult.InsertItem(1,theApp.operGM.ReadValue("MGM","GA_UI_tpgBanAccount"));
	tbcResult.InsertItem(2,theApp.operGM.ReadValue("MGM","GA_UI_tpgBanAccountFromExcel"));

	SetDlgItemText(IDC_LBLGAME,theApp.operGM.ReadValue("MGM","OL_UI_LblGame"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operGM.ReadValue("MGM","GA_UI_Server"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operGM.ReadValue("MGM","GA_UI_Account"));
	SetDlgItemText(IDC_LBLTIME,theApp.operGM.ReadValue("MGM","GA_UI_BanTime"));
	SetDlgItemText(IDC_LBLDATE,theApp.operGM.ReadValue("MGM","GA_UI_LblDate"));
	SetDlgItemText(IDC_LBLREASON,theApp.operGM.ReadValue("MGM","GA_UI_LBLREASON"));
	SetDlgItemText(IDC_LBLTYPE,theApp.operGM.ReadValue("MGM","GA_UI_LBLTYPE"));
	SetDlgItemText(IDC_BTNBAN,theApp.operGM.ReadValue("MGM","GA_UI_BTNBAN"));
	SetDlgItemText(IDC_BTNRESET,theApp.operGM.ReadValue("MGM","Reset"));

	cmbType.AddString(theApp.operGM.ReadValue("MGM","R_SYSTEM"));
	cmbType.AddString(theApp.operGM.ReadValue("MGM","R_SYSTEM_TEMP"));
	cmbType.AddString(theApp.operGM.ReadValue("MGM","R_USERCUSTOM"));
	cmbType.AddString(theApp.operGM.ReadValue("MGM","R_USERCUSTOM_TEMP"));

	cmbType.SetCurSel(0);
}

//�����ݼ���Ӧ����
BOOL GMGameAssist::PreTranslateMessage(MSG* pMsg)
{
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operGM.CopyListInfo(&listResult);
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listResult.m_hWnd)
				{
					for(int i=0; i<listResult.GetItemCount(); i++)
					{
					    listResult.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listResult.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

// �Զ��ı��С
void GMGameAssist::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rs;
	GetClientRect(rs);

	CRect newRect;

	if(GrpSearch.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4;		
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;
		newRect.bottom = newRect.top + grpHeight;

		GrpSearch.MoveWindow(newRect);//���ú�GrpSearch��λ��
	}

	if(tbcResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + tbcHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		tbcResult.MoveWindow(newRect);//���ú�tbcResult��λ��
	}

	if(GrpPage.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//���ú�listResult��λ��
	}

	if(listAccountImport.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = (rs.right + rs.left)/2 -10;

		listAccountImport.MoveWindow(newRect);//���ú�listAccountImport��λ��
	}
	if(listVIPAccount.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = (rs.right + rs.left)/2;
		newRect.right = rs.right - 10;

		listVIPAccount.MoveWindow(newRect);//���ú�listVIPAccount��λ��
	}

}

//���ñ�����ɫ
HBRUSH GMGameAssist::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

void GMGameAssist::OnTimer(UINT nIDEvent)
{
    GameAssist();	
	CDialog::OnTimer(nIDEvent);
}

//��ȡ���е���Ϸ����
void GMGameAssist::QueryGameList()
{
	try
	{		
		CIni mIni;

		int index = theApp.operGM.ReadIntValue("MGM","index");
		int iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");

		cmbGame.ResetContent();
		
		CSocketData socketdata;	
		socketdata.InitCreate(1,3);//����3��������ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::GAME_ADMIN,CEnumCore::ServiceKey::GAME_QUERY))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","GA_WARN_SEARCHGAME"),theApp.operGM.ReadValue("MGM","Error"),0);
	}	
}

//ͨ����Ϸ���Ʋ�ѯ��Ӧ����Ϸ������IP
void GMGameAssist::OnCbnSelchangeCmbgamename()
{
	try
	{
		CIni mIni;

		int index = theApp.operGM.ReadIntValue("MGM","index");
		int iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");

		cmbServer.ResetContent();

		GetDlgItemText(IDC_CMBGAMENAME,GameName);//��ȡ��Ϸ����
		if(GameName == "")//��Ϸ���Ʋ���Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","OL_Warn_GameNameNull"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		GameList.Lookup(cmbGame.GetCurSel()+1,GameID);//��CMap��Ķ���GameList�л�ȡ��ϷID

		CSocketData socketdata;	
		socketdata.InitCreate(1,5);//��������������������IP��������Name������ǳơ���������,ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(GameID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ϷID
		_itoa(1,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameDBID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ϷID

		socketdata.AddTFLV(CEnumCore::TagName::GameName,CEnumCore::TagFormat::TLV_STRING,strlen(GameName),(unsigned char *)mIni.wcharToChar(GameName));//��Ϸ����

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::SERVERINFO_IP_QUERY))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","GA_WARN_SEARCHSERVER"),theApp.operGM.ReadValue("MGM","Error"),0);
	}	
}

// ��ѯ��Ӧ��Ϸ�������Ϣ
void GMGameAssist::OnBnClickedSearch()
{
	try
	{
		iIndex = theApp.operGM.ReadIntValue("MGM","index");//��ѯ��һҳ����Ϣ
		iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");//ÿҳ��ʾ50����¼

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}//�����������б��е���������

		tbcResult.SetCurSel(0);
		ShowBanPlayer(SW_HIDE);
		ShowUserInfo(SW_SHOW);
		ShowExcelBanPlayer(SW_HIDE);

		UpdateData(true);

		GetDlgItemText(IDC_CMBGAMENAME,GameName);//��ȡ��Ϸ��
		if(GameName == "")//��Ϸ������Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UIC_Warn_SelectServer"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		GameList.Lookup(cmbGame.GetCurSel()+1,GameID);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ����������
		if(ServerName == "")//���������Ʋ���Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UIC_Warn_SelectServer"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		//else if(ServerName == theApp.operGM.ReadValue("MGM", "GA_UI_AREADEFAULT"))
		//{
			//ServerIP = "";
		//}
		else
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��ȡ������IP

		AssitType=cmbAssit.GetCurSel();//��ȡ�������
		if(AssitType < 0)//������Ͳ���Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","OL_Warn_InputNotNull"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		
		KillTimer(1);
		GameAssist();		
		SetTimer(1,refreshTime * 60000,NULL);
	}
	catch(...)
	{
	}
}

// ��ҳ���в�ѯ
void GMGameAssist::OnCbnSelchangeCmbpage()
{
	try
	{	
		if(pageInfo)//������Է�ҳ�Ļ�
		{
			iIndex = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			KillTimer(1);
			GameAssist();
			SetTimer(1,refreshTime * 60000,NULL);
		}
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","UIC_Error_Page"),theApp.operGM.ReadValue("MGM","Error"),0);
	}
}

//�޸�ѭ����ѯ��ʱ����
void GMGameAssist::OnBnClickedBtnstart()
{
	try
	{	
		CString iTime="";
		GetDlgItemText(IDC_EDITMINUTE,iTime);
		if(atoi(iTime)<5)
		{
			MessageBox(theApp.operGM.ReadValue("MGM","GA_WARN_EDITTIMEEDGE"),theApp.operGM.ReadValue("MGM","Error"),0);
			SetDlgItemText(IDC_EDITMINUTE,"5");
			return;
		}
		refreshTime=atoi(iTime);

		KillTimer(1);// �����������
		GameAssist();
		SetTimer(1,refreshTime * 60000,NULL);
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","GA_WARN_EDITTIM"),theApp.operGM.ReadValue("MGM","Error"),0);
	}
}

//��ѯ��Ϸ�����Ϣ
void GMGameAssist::GameAssist()
{
	try
	{
		CIni mIni;

		int midlength = 0;
		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		_itoa(GameID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GameID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID
		socketdata.AddTFLV(CEnumCore::TagName::GameName,CEnumCore::TagFormat::TLV_STRING,strlen(GameName),(unsigned char *)mIni.wcharToChar(GameName));//��Ϸ����
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_City,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//��������
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_IP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//����IP

		_itoa(AssitType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::ToolProcTypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID

		_itoa(iIndex,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		midlength=socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::HARMFUL_PROC_QUERY))//���Ͳ�ѯ��Ϸ�����Ϣ������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","GA_WARN_SEARCHGA"),theApp.operGM.ReadValue("MGM","Error"),0);
	}
}

// ������ͣ�ʺ��б��浱ǰ�к�
void GMGameAssist::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listResult.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
			listResult.ScreenToClient(&point);
			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;
			mItem = listResult.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�
		}
		else
		{
			mItem = -1;
		}
	}
	*pResult = 0;
}

// ˫����ͣ�ʺ��б����������
void GMGameAssist::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{		
		if(listResult.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
			listResult.ScreenToClient(&point);
			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;
			mItem = listResult.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�
			if(mItem >= 0)
			{
				if(!strcmp(GameName,theApp.operGM.ReadValue("MGM","WA_Name")))
				{
					KillTimer(1);
					CIni mIni;
					UserAccount = theApp.operGM.GetValueByColName(&listResult, mItem, theApp.operGM.ReadValue("MGM","PlayerAccount"));
					UserName = theApp.operGM.GetValueByColName(&listResult, mItem, theApp.operGM.ReadValue("MGM","PlayerName"));

					if (AfxMessageBox(theApp.operGM.ReadValue("MGM","KP_Hint_KickPlayer"), MB_YESNO) == IDNO) 
					{
						return;
					}

					int userbyID = theApp.UserByID;

					CSocketData socketdata;
					socketdata.InitCreate(1,10);//�����ĸ�������������IP������ǳơ�����ʺš�����ԱID
					char strInt[10];

					socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
					socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
					socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

					_itoa(userbyID,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

					int midlength = socketdata.EnBody();
					if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::WA_ADMIN,CEnumCore::ServiceKey::WA_KickPlayer))//����ǿ��������ߵ�����
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);
						dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
					socketdata.Destroy();
				}
			}
		}
		else
		{
			mItem = 0;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// �л�ѡ����в���
void GMGameAssist::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{

	CIni mIni;

	if(tbcResult.GetCurSel()==0)//���ѡ�е��������Ϣ�б��ҳ��
	{		
		ShowBanPlayer(SW_HIDE);
		ShowUserInfo(SW_SHOW);
		ShowExcelBanPlayer(SW_HIDE);
	}
	else if(tbcResult.GetCurSel()==1)//���ѡ�е��Ƿ�ͣ�ʺŵ�ҳ��
	{
		KillTimer(1);

		ShowUserInfo(SW_HIDE);
		ShowBanPlayer(SW_SHOW);
		ShowExcelBanPlayer(SW_HIDE);
		OnBnClickedBtnreset();
		iRefresh = false;

		UpdateData(false);

		if(!strcmp(GameName,theApp.operGM.ReadValue("MGM","WA_Name")))
		{
			if((listResult.GetItemCount() > 0) && (mItem >= 0))
			{
				UserAccount = theApp.operGM.GetValueByColName(&listResult, mItem, theApp.operGM.ReadValue("MGM","PlayerAccount"));
				UserName = theApp.operGM.GetValueByColName(&listResult, mItem, theApp.operGM.ReadValue("MGM","PlayerName"));

				SetDlgItemText(IDC_EDITGAME,GameName);
				SetDlgItemText(IDC_EDITSERVER,ServerName);
				SetDlgItemText(IDC_EDITACCOUNT,UserAccount);
			}
		}		
	}
	else if(tbcResult.GetCurSel()==2) //������ͣ�ʺ�
	{
		ShowUserInfo(SW_HIDE);
		ShowBanPlayer(SW_HIDE);
		ShowExcelBanPlayer(SW_SHOW);
	}
	*pResult = 0;
}

// ��ͣ�ʺ�
void GMGameAssist::OnBnClickedBtnban()
{
	try
	{		
		CIni mIni;			
		CString BanAccount = "";
		CString BanTime="";///////////////////////////////��¼��ͣʱ��
		GetDlgItemText(IDC_EDITTIME,BanTime);
		int RealTime = atoi(BanTime)*24*60;

		GetDlgItemText(IDC_EDITACCOUNT,BanAccount);//��ȡ����ʺ�
		if(BanAccount == "")//����ͣ������ʺŲ���Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","BU_UI_AccountNull"),theApp.operGM.ReadValue("MGM","Warn"),0);
			return;
		}				

		CString BanReason = "";
		GetDlgItemText(IDC_EDITREASON, BanReason);
		if(strlen(BanReason) >= 256 || strlen(BanReason)==0||BanTime=="")//��ͣ����ԭ����Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","BU_Warn_ContentNull"),theApp.operGM.ReadValue("MGM","Warn"),0);
			return;
		}

		int userbyID = theApp.UserByID;//����ԱID

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�����ĸ�������������IP������ʺš���ͣ����ԭ�򡢲���ԱID
		char strInt[10];
		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(BanAccount),(unsigned char *)mIni.wcharToChar(BanAccount));//����ʺ�

		_itoa(cmbType.GetCurSel()+1, strInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::WA_Reason,CEnumCore::TagFormat::TLV_STRING,sizeof(int),(unsigned char *)&strInt);//��ͣ����

		_itoa(RealTime, strInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::WA_Time,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ͣʱ��
		socketdata.AddTFLV(CEnumCore::TagName::WA_Description, CEnumCore::TagFormat::TLV_STRING,strlen(BanReason),(unsigned char *)mIni.wcharToChar(BanReason));//��ͣԭ��

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		int midlength = socketdata.EnBody();

		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::WA_ADMIN,CEnumCore::ServiceKey::WA_ClosePlayer))//���ͷ�ͣ����ʺŵ�����
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}

		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

// ������Ϣ
void GMGameAssist::OnBnClickedBtnreset()
{	
	SetDlgItemText(IDC_EDITGAME,"");
	SetDlgItemText(IDC_EDITSERVER,"");
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITTIME,"");
	SetDlgItemText(IDC_EDITREASON,"");
	cmbType.SetCurSel(0);
}

// ���շ�����Ϣ
LRESULT GMGameAssist::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;

	dlgStatus = theApp.operGM.ReadIntValue("MGM","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	int pageCount = 0;

	switch(theApp.m_tag_id)
	{
	case CEnumCore::Message_Tag_ID::GAME_QUERY_RESP://��ѯ��Ϸ��Ϣ�Ļ�Ӧ
		{
			if(!GameList.IsEmpty())
			{
				GameList.RemoveAll();
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int GameID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::GameID).lpdata);//�õ���ϷID
				GameList.SetAt(i-1,GameID);//����ϷID������CMap��Ķ���UserList��
			}

			theApp.operGM.BuildComboxs(&socketdata,&cmbGame,2,CEnumCore::TagName::GameName);//������Ϸ�����б���Ϣ	

			OnCbnSelchangeCmbgamename();
		}
		break;
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��ѯ��Ϸ������IP�Ļ�Ӧ
		{
			//AfxMessageBox("������IP��ѯ");
			if(!ServerList.IsEmpty())
			{
				ServerList.RemoveAll();
				ServerCityToServerIP.clear();
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ���Ϸ������IP
				ServerList.SetAt(i,ServerIP);//����Ϸ������IP������CMap��Ķ���ServerList��
				CString ServerCity = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_City).lpdata;//�õ���Ϸ��������
				ServerCityToServerIP.insert(pair<CString, CString>(ServerCity, ServerIP));
			}
			/*
			CString str;
			map<CString, CString>::iterator it;
			for(it = ServerCityToServerIP.begin(); it != ServerCityToServerIP.end(); it++)
				str += it->second;
			AfxMessageBox(str);
			*/
			theApp.operGM.BuildComboxs(&socketdata,&cmbServer,1,CEnumCore::TagName::ServerInfo_City);//������Ϸ�������б���Ϣ
			
			//cmbServer.InsertString(0, (LPCSTR)theApp.operGM.ReadValue("MGM", "GA_UI_AREADEFAULT"));//�����б�����Ӹ�����ΪĬ�ϲ�ѯѡ�� Added by yanfei_qin 2010-9-14
			//cmbServer.SetCurSel(0);
		}
		break;
	case CEnumCore::Message_Tag_ID::HARMFUL_PROC_QUERY_RESP://��ҽ��̹��߰�
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operGM.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operGM.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					pageInfo = false;//���ܷ�ҳ		
					cmbPage.ResetContent();
				}
				else
				{
					cmbPage.ResetContent();
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbPage.AddString(str);
					}
					cmbPage.SetCurSel(0);
					if(pageCount == 1)
					{
						pageInfo = false;
					}
					else
					{
						pageInfo = true;
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GM_AccountInfo_Resp://��ѯvip�û�����˷�����Ϣ
		{			
			//AfxMessageBox("���ղ�ѯ��Ϣ");
			char* isVip = (char*)&socketdata.getTLVByName(1,CEnumCore::TagName::GM_AccountInfo_Vip).lpdata;  //�����Ƿ�vip
			if(atoi(isVip)==TRUE)
			{
				m_isVipAccount = TRUE;
				theApp.operGM.ShowVIP(&socketdata, &listVIPAccount);
			}
			else
				m_isVipAccount = FALSE;
			SetEvent(m_hCheckVipEvent);
		}
		break;
	case CEnumCore::Message_Tag_ID::GM_ClosePlayerGroup_Resp_WA:
		{
			//AfxMessageBox("������ͣ��������Ӧ");
			char* ban = (char*)&socketdata.getTLVByName(1,CEnumCore::TagName::MESSAGE).lpdata; 

			if(strcmp(ban, "��ͣ�ɹ�"))   //����ͣ���ɹ�
				listVIPAccount.InsertItem(0, m_curAccount);   //��¼���ɹ��ʺ�
			SetEvent(m_hBanAccountEvent);
		}
		break;
	default:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operGM.ShowResult(result);//��ʾ�������
			
			OnBnClickedBtnreset();
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	return false;
}

// �رնԻ���
void GMGameAssist::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	cmbAssit.SetCurSel(0);
}

// �رնԻ���
void GMGameAssist::OnClose()
{
	if(!GameList.IsEmpty())
	{
		GameList.RemoveAll();
	}
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	KillTimer(1);
	DestroyWindow();
	CDialog::OnClose();
}

//��ʾ���������Ϣ
void GMGameAssist::ShowUserInfo(int m_cmdShow)
{
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(m_cmdShow);
}

//��ʾ��ͣ�ʺ�
void GMGameAssist::ShowBanPlayer(int m_cmdShow)
{
	GetDlgItem(IDC_LBLGAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITGAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLHINT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSERVER)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSERVER)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLTIME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITTIME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLDATE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLREASON)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITREASON)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(m_cmdShow);
}

//��ʾ��������
void GMGameAssist::ShowExcelBanPlayer(int m_cmdShow)
{
	GetDlgItem(IDC_BTNBANBATCH)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTBANBATCH)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTVIP)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CHECKVIP)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITIMPORT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNIMPORT)->ShowWindow(m_cmdShow);

}

//�򿪵������ܵ��ļ��Ի���
/*
void GMGameAssist::OnBnClickedOpenFileExport()
{
	CString szFilters = "xls Files (*.xls)|*.xls||";
	CFileDialog exportDlg (TRUE, "xls", "*.xls",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
	exportDlg.DoModal();

	SetDlgItemText(IDC_EDITEXPORT, exportDlg.GetPathName());
	GetDlgItemText(IDC_EDITEXPORT, exportFilePath);

	if (exportFilePath.IsEmpty())
	{
		MessageBox(NULL, "��ָ���ļ�",  MB_OK | MB_TOPMOST);
		return;
	}
}
*/
//�������ݵ�xls�ļ�
void GMGameAssist::OnBnClickedBtnExport()
{
	CString szFilters = "xls Files (*.xls)|*.xls||";
	CFileDialog exportDlg (TRUE, "xls", "*.xls",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
	
	if(exportDlg.DoModal() != IDOK)
		return;

	CString path;

	SetDlgItemText(IDC_EDITEXPORT, exportDlg.GetPathName());
	//GetDlgItemText(IDC_EDITEXPORT, exportFilePath);
	GetDlgItemText(IDC_EDITEXPORT, path);

	if (path.IsEmpty())
	{
		MessageBox(NULL, "��ָ���ļ�", MB_OK | MB_TOPMOST);
		return;
	}
	
	CString str;
	str.Format("ѡ��<%s>��Ϊsheet�����������?\n", GameName);
	if(MessageBox(str,  NULL, MB_YESNO | MB_TOPMOST) == IDNO)
		return;

	CListCtrl* list;
	if (tbcResult.GetCurSel()==0)
		list = &listResult;
	else if(tbcResult.GetCurSel()==2)
		list = &listVIPAccount;

	theApp.operGM.ExportCListCtrlToExcel(list, path, GameName);
}



//�򿪵��빦�ܵ��ļ��Ի���
/*
void GMGameAssist::OnBnClickedOpenFileImport()
{
	CString szFilters = "xls Files (*.xls)|*.xls||";
	CFileDialog importDlg (TRUE, "xls", "*.xls",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
	importDlg.DoModal();

	SetDlgItemText(IDC_EDITIMPORT, importDlg.GetPathName());
	GetDlgItemText(IDC_EDITIMPORT, importFilePath);

	if (importFilePath.IsEmpty())
	{
		MessageBox(NULL, "��ָ���ļ�",  MB_OK | MB_TOPMOST);
		return;
	}
}


*/
//�������ݵ�CListCtrl
void GMGameAssist::OnBnClickedBtnImport()
{
	CString szFilters = "xls Files (*.xls)|*.xls||";
	CFileDialog importDlg (TRUE, "xls", "*.xls",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
	
	if(importDlg.DoModal() != IDOK)
		return;

	CString path;

	SetDlgItemText(IDC_EDITIMPORT, importDlg.GetPathName());
	//GetDlgItemText(IDC_EDITIMPORT, importFilePath);
	GetDlgItemText(IDC_EDITIMPORT, path);

	if (path.IsEmpty())
	{
		MessageBox(NULL, "��ָ���ļ�",  MB_OK | MB_TOPMOST);
		return;
	}

	CString str;
	str.Format("��ȷ��xls�д�����Ϊ%s��sheet��", GameName);
	if (MessageBox(str,  NULL, MB_YESNO | MB_TOPMOST) == IDNO)
		return;

	//while(listAccountImport.DeleteColumn(0)){}	//���CListCtrl������
	listVIPAccount.DeleteAllItems();
	listAccountImport.DeleteAllItems();

	theApp.operGM.ImportCListCtrlFromExcel(&listAccountImport, path, GameName);
}


//���Ͳ�ѯvip�ʺ���Ϣ
DWORD WINAPI GMGameAssist::sendVIPAccountRequest(LPVOID pClsParam)
{
	try
	{
		GMGameAssist* pCls = (GMGameAssist*)pClsParam;

		pCls->listVIPAccount.DeleteAllItems();

		::EnableWindow(pCls->GetParent()->m_hWnd,false);

		LVCOLUMN columnData;
		CString columnName;
		columnData.mask = LVCF_TEXT;
		columnData.pszText = columnName.GetBuffer(128);
		columnData.cchTextMax = 128;

		HDITEM hdi;
		CString itemName;
		hdi.mask = HDI_TEXT;
		hdi.pszText = itemName.GetBuffer(128);
		hdi.cchTextMax = 128;

		//DWORD eventResult;
		int colCount, rowCount;
		CString account;

		for (rowCount = 0; rowCount < pCls->listAccountImport.GetItemCount(); rowCount++)
		{
			for (colCount = 0; colCount < pCls->listAccountImport.GetHeaderCtrl()->GetItemCount(); colCount ++)
			{
				pCls->listAccountImport.GetHeaderCtrl()->GetItem(colCount, &hdi);
				//�������ѯ���ʺ�
				if (!strcmp(hdi.pszText, "�����ʺ�")) 
				{
					account = pCls->listAccountImport.GetItemText(rowCount, colCount);

					CSocketData socketdata;
					socketdata.InitCreate(1,2);//����2������������ʺš�����ԱID

					socketdata.AddTFLV(CEnumCore::TagName::PlayerAccount,CEnumCore::TagFormat::TLV_STRING,strlen(account),(unsigned char *)(LPCTSTR)(account));//����ʺ�

					int userbyID = theApp.UserByID;//����ԱID
					char strInt[10];
					_itoa(userbyID,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

					int midlength = socketdata.EnBody();

					if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::GM_AccountInfo_Vip))//���Ͳ�ѯ����ʺ��Ƿ�Ϊvip������
					{
						pCls->dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
					socketdata.Destroy();
					WaitForSingleObject(pCls->m_hCheckVipEvent, INFINITE);
					//ResetEvent(pCls->m_hCheckVipEvent);
					if(pCls->m_isVipAccount)
					{
						pCls->listAccountImport.DeleteItem(rowCount);
						rowCount -= 1;   //����һ�к�, �����кŵ�˳�����, ��Ҫ�ָ�
					}
					pCls->m_isVipAccount = FALSE;
				}
			}		
		}

		//ɾ��clistctrl�е�vip�ʺ�
		/*
		if(pCls->listVIPAccount.GetItemCount() > 0)
		{
			int i, index;
			for(i=0;i < pCls->listVIPAccount.GetItemCount(); i++)
			{
				LVFINDINFO info;
				info.flags = LVFI_PARTIAL|LVFI_STRING;
				info.psz = (LPCTSTR)pCls->listVIPAccount.GetItemText(i,0);  
				AfxMessageBox(info.psz);
				index = pCls->listAccountImport.FindItem(&info);
				if(index != -1)
					pCls->listAccountImport.DeleteItem(index);
			}
		}
		*/
		::EnableWindow(pCls->GetParent()->m_hWnd,true);
		return 1; 
	}
	catch(...)
	{
		return 0;
	}
}



//����������ͣ�ʺ���Ϣ
DWORD WINAPI GMGameAssist::sendBanAccountList(LPVOID pClsParam)
{
	
	try
	{
		GMGameAssist* pCls = (GMGameAssist*)pClsParam;

		::EnableWindow(pCls->GetParent()->m_hWnd,false);

		pCls->listVIPAccount.DeleteAllItems();

		CIni mIni;	

		LVCOLUMN columnData;
		CString columnName;
		columnData.mask = LVCF_TEXT;
		columnData.pszText = columnName.GetBuffer(128);
		columnData.cchTextMax = 128;

		HDITEM hdi;
		CString itemName;
		hdi.mask = HDI_TEXT;
		hdi.pszText = itemName.GetBuffer(128);
		hdi.cchTextMax = 128;


		CString accounts;
		CString resons;
		CString banTimes;
		CString types;
		CString serverIPs;
		CString city;

		int typeID=0;

		if(strcmp(pCls->listAccountImport.GetItemText(0, 0), pCls->GameName))    //�Ƿ��Ѿ�ѡ���Ӧ����Ϸ
		{
			AfxMessageBox("��ȷ�����Ѿ�ѡ���˶�Ӧ����Ϸ,�ұ������д����Ϸ������ȷ");
			::EnableWindow(pCls->GetParent()->m_hWnd,true);
			return 0;
		}

		DWORD eventResult;
		int colCount, rowCount;
		map<CString, CString>::iterator it;
		for (rowCount = 0; rowCount < pCls->listAccountImport.GetItemCount(); rowCount++)
		{
			for (colCount = 0; colCount < pCls->listAccountImport.GetHeaderCtrl()->GetItemCount(); colCount ++)
			{
				pCls->listAccountImport.GetHeaderCtrl()->GetItem(colCount, &hdi);
				if (!strcmp(hdi.pszText, "�����ʺ�"))  //�����ʺ�
				{
					//accounts += pCls->listAccountImport.GetItemText(rowCount, colCount) + token;
					accounts = pCls->listAccountImport.GetItemText(rowCount, colCount);
					pCls->m_curAccount = accounts;
				}
				if (!strcmp(hdi.pszText, "��Ϸ����"))   //��Ϸ����
				{
					city = pCls->listAccountImport.GetItemText(rowCount, colCount);
					it = pCls->ServerCityToServerIP.find(city);
					//if (it != pCls->ServerCityToServerIP.end())
					serverIPs = it->second;
					//AfxMessageBox((LPCTSTR)(city + serverIPs));
				}
				if(!strcmp(hdi.pszText, "��ͣʱ��"))    //��ͣʱ��
				{
					//banTimes += pCls->listAccountImport.GetItemText(rowCount, colCount) + token;
					banTimes = pCls->listAccountImport.GetItemText(rowCount, colCount);
				}
				if(!strcmp(hdi.pszText, "��ͣԭ��"))       //��ͣԭ��
				{
					//resons = pCls->listAccountImport.GetItemText(rowCount, colCount) + token;
					resons = pCls->listAccountImport.GetItemText(rowCount, colCount);
				}
				if(!strcmp(hdi.pszText, "��ͣ����"))      //��ͣ����
				{
					//types = pCls->listAccountImport.GetItemText(rowCount, colCount) + token;
					types = pCls->listAccountImport.GetItemText(rowCount, colCount);
					if(!strcmp((LPCTSTR)types, "ϵͳ��ͣ"))
						typeID = 1;
					else if(!strcmp((LPCTSTR)types, "ϵͳ��ʱ��ͣ"))
						typeID = 2;
					else if(!strcmp((LPCTSTR)types, "�û�����"))
						typeID = 3;
					else if(!strcmp((LPCTSTR)types, "�û���ʱ����"))
						typeID = 4;
				}					
			}

			//����������ͣ�ʺ�
			int userbyID = theApp.UserByID;//����ԱID
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�����ĸ�������������IP������ʺš���ͣ����ԭ�򡢲���ԱID
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(serverIPs),(unsigned char *)mIni.wcharToChar(serverIPs));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(accounts),(unsigned char *)mIni.wcharToChar(accounts));//����ʺ�

			_itoa(typeID, strInt, 10);
			socketdata.AddTFLV(CEnumCore::TagName::WA_Reason,CEnumCore::TagFormat::TLV_STRING,sizeof(types),(unsigned char *)&strInt);//��ͣ����

			//_itoa(RealTime, strInt, 10);
			char itime[10];
			sprintf(itime, "%s", (LPCTSTR)banTimes);
			socketdata.AddTFLV(CEnumCore::TagName::WA_Time,CEnumCore::TagFormat::TLV_INTEGER,sizeof(banTimes),(unsigned char *)&itime);//��ͣʱ��
			socketdata.AddTFLV(CEnumCore::TagName::WA_Description, CEnumCore::TagFormat::TLV_STRING,strlen(resons),(unsigned char *)mIni.wcharToChar(resons));//��ͣԭ��

			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

			int midlength = socketdata.EnBody();

			if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::WA_ADMIN,CEnumCore::ServiceKey::WA_ClosePlayerGroup))//���ͷ�ͣ����ʺŵ�����
			{
				pCls->dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
			socketdata.Destroy();	
			WaitForSingleObject(pCls->m_hBanAccountEvent, INFINITE);
			//ResetEvent(pCls->m_hBanAccountEvent);
		}
		::EnableWindow(pCls->GetParent()->m_hWnd,true);
	}
	catch (...)
	{
		return 0;
	}
}
//��ѯvip�ʻ���ť��Ӧ
void GMGameAssist::OnBnClickedCheckVip()
{
	// TODO: Add your control notification handler code here
	
	m_hCheckVipEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	ResetEvent(m_hCheckVipEvent);

	DWORD IDThread;
	m_hCheckVipThread = CreateThread(NULL, 0, 
		&GMGameAssist::sendVIPAccountRequest, 
		this,  // pass event handle
		0, &IDThread);
	
	if(m_hCheckVipThread == NULL) 
	{
		MessageBox(NULL, "������ѯvip�ʺ��߳�ʧ��", MB_OK | MB_TOPMOST);
	}
	
}
//������ͣ�ʺŰ�ť��Ӧ
void GMGameAssist::OnBnClickedBtnBanBatch()
{
	if(MessageBox("��ȷ���Ѿ���ѯ��VIP�ʺ�����?", NULL,  MB_YESNO | MB_TOPMOST)==IDNO)
		return;

	m_hBanAccountEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	//SetEvent(m_hBanAccountEvent);

	DWORD IDThread;
	m_hBanAccountThread = CreateThread(NULL, 0, 
		&GMGameAssist::sendBanAccountList, 
		this,  // pass event handle
		0, &IDThread);

	if(m_hBanAccountThread == NULL) 
	{
		MessageBox(NULL, "����������ͣ�ʺ��߳�ʧ��", MB_OK | MB_TOPMOST);
	}
}

//��ѯ��������ʺ�
void GMGameAssist::OnBnClickedBtnCheckAccountAll()
{
	// TODO: Add your control notification handler code here

	try
	{
		iIndex = theApp.operGM.ReadIntValue("MGM","index");//��ѯ��һҳ����Ϣ
		iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");//ÿҳ��ʾ50����¼

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}//�����������б��е���������

		tbcResult.SetCurSel(0);
		ShowBanPlayer(SW_HIDE);
		ShowUserInfo(SW_SHOW);

		UpdateData(true);

		GetDlgItemText(IDC_CMBGAMENAME,GameName);//��ȡ��Ϸ��
		if(GameName == "")//��Ϸ������Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UIC_Warn_SelectServer"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		GameList.Lookup(cmbGame.GetCurSel()+1,GameID);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ����������
		if(ServerName == "")//���������Ʋ���Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UIC_Warn_SelectServer"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		ServerIP = "";


		AssitType=cmbAssit.GetCurSel();//��ȡ�������
		if(AssitType < 0)//������Ͳ���Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","OL_Warn_InputNotNull"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		KillTimer(1);		
		SetTimer(1,refreshTime * 60000,NULL);
	}
	catch(...)
	{
	}


	try
	{
		//QueryGameList();

		CIni mIni;

		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		_itoa(GameID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GameID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID
		socketdata.AddTFLV(CEnumCore::TagName::GameName,CEnumCore::TagFormat::TLV_STRING,strlen(GameName),(unsigned char *)mIni.wcharToChar(GameName));//��Ϸ����
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_City,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//��������
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_IP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//����IP

		_itoa(AssitType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::ToolProcTypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID

		_itoa(iIndex,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = 0;
		midlength=socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::HARMFUL_PROC_QUERY))//���Ͳ�ѯ��Ϸ�����Ϣ������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}
}


