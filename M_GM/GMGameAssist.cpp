// GMGameAssist.cpp : 实现文件
//

#include "stdafx.h"
#include "M_GM.h"
#include "GMGameAssist.h"
#include ".\gmgameassist.h"

// GMGameAssist 对话框

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


// GMGameAssist 消息处理程序

// 初始化对话框
BOOL GMGameAssist::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// 初始化显示字符
	ShowBanPlayer(SW_HIDE);
	ShowExcelBanPlayer(SW_HIDE);

	GameName = "";
	AssitType = 0;
	iIndex = 0;
	iPageSize = 0 ;
	refreshTime = 5;
	iRefresh = false;
	
	CRect rs;
	GetClientRect(rs);; //获取对话框的大小信息

	CRect srcRect;
	CRect newRect;

	if(GrpSearch.m_hWnd != NULL)
	{
		GrpSearch.GetWindowRect(srcRect);//获取GrpSearch的大小信息
		grpHeight = srcRect.bottom - srcRect.top;//得到GrpSearch的高度信息

		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + grpHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpSearch.MoveWindow(newRect);//设置好GrpSearch的位置
	}

	if(tbcResult.m_hWnd != NULL)
	{
		tbcResult.GetWindowRect(srcRect);//获取tbcResult的大小信息
		tbcHeight = srcRect.bottom - srcRect.top;//得到tbcResult的高度信息

		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + tbcHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		tbcResult.MoveWindow(newRect);//设置好tbcResult的位置
	}

	if(GrpPage.m_hWnd != NULL)
	{
		GrpPage.GetWindowRect(srcRect);//获取GrpPage的大小信息
		grpPHeight = srcRect.bottom - srcRect.top;//得到GrpPage的高度信息

		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}
	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listResult的位置
	}
	if(listAccountImport.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = (rs.right + rs.left)/2 -10;
		
		listAccountImport.MoveWindow(newRect);//设置好listAccountImport的位置
	}
	if(listVIPAccount.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = (rs.right + rs.left)/2;
		newRect.right = rs.right - 10;

		listVIPAccount.MoveWindow(newRect);//设置好listVIPAccount的位置
	}

	

	dlgStatus = theApp.operGM.ReadIntValue("MGM","Create");//当前的状态为初始建立对话框

	QueryGameList();


	//设定clistctrl风格
	//////////////////////////////////////////////////////////////////////
	LONG lStyle;
	lStyle = GetWindowLong(listAccountImport.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(listAccountImport.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = listAccountImport.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	listAccountImport.SetExtendedStyle(dwStyle); //设置扩展风格
	//////////////////////////////////////////////////////////////////////
	lStyle;
	lStyle = GetWindowLong(listVIPAccount.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(listVIPAccount.m_hWnd, GWL_STYLE, lStyle);//设置style

	dwStyle = listVIPAccount.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	listVIPAccount.SetExtendedStyle(dwStyle); //设置扩展风格

	listVIPAccount.InsertColumn(0, "玩家帐号", LVCFMT_LEFT, 160);
	///////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 初始化显示字符
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

//处理快捷键响应函数
BOOL GMGameAssist::PreTranslateMessage(MSG* pMsg)
{
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
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

// 自动改变大小
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

		GrpSearch.MoveWindow(newRect);//设置好GrpSearch的位置
	}

	if(tbcResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + tbcHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		tbcResult.MoveWindow(newRect);//设置好tbcResult的位置
	}

	if(GrpPage.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listResult的位置
	}

	if(listAccountImport.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = (rs.right + rs.left)/2 -10;

		listAccountImport.MoveWindow(newRect);//设置好listAccountImport的位置
	}
	if(listVIPAccount.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = (rs.right + rs.left)/2;
		newRect.right = rs.right - 10;

		listVIPAccount.MoveWindow(newRect);//设置好listVIPAccount的位置
	}

}

//设置背景颜色
HBRUSH GMGameAssist::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

void GMGameAssist::OnTimer(UINT nIDEvent)
{
    GameAssist();	
	CDialog::OnTimer(nIDEvent);
}

//获取所有的游戏名称
void GMGameAssist::QueryGameList()
{
	try
	{		
		CIni mIni;

		int index = theApp.operGM.ReadIntValue("MGM","index");
		int iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");

		cmbGame.ResetContent();
		
		CSocketData socketdata;	
		socketdata.InitCreate(1,3);//共有3个参数，页数、每页的记录条数
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::GAME_ADMIN,CEnumCore::ServiceKey::GAME_QUERY))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","GA_WARN_SEARCHGAME"),theApp.operGM.ReadValue("MGM","Error"),0);
	}	
}

//通过游戏名称查询相应的游戏服务器IP
void GMGameAssist::OnCbnSelchangeCmbgamename()
{
	try
	{
		CIni mIni;

		int index = theApp.operGM.ReadIntValue("MGM","index");
		int iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");

		cmbServer.ResetContent();

		GetDlgItemText(IDC_CMBGAMENAME,GameName);//获取游戏名称
		if(GameName == "")//游戏名称不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","OL_Warn_GameNameNull"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		GameList.Lookup(cmbGame.GetCurSel()+1,GameID);//从CMap类的对象GameList中获取游戏ID

		CSocketData socketdata;	
		socketdata.InitCreate(1,5);//共有六个参数，服务器IP、服务器Name、玩家昵称、背包类型,页数、每页的记录条数
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(GameID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//游戏ID
		_itoa(1,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameDBID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//游戏ID

		socketdata.AddTFLV(CEnumCore::TagName::GameName,CEnumCore::TagFormat::TLV_STRING,strlen(GameName),(unsigned char *)mIni.wcharToChar(GameName));//游戏名称

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::SERVERINFO_IP_QUERY))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","GA_WARN_SEARCHSERVER"),theApp.operGM.ReadValue("MGM","Error"),0);
	}	
}

// 查询相应游戏的外挂信息
void GMGameAssist::OnBnClickedSearch()
{
	try
	{
		iIndex = theApp.operGM.ReadIntValue("MGM","index");//查询第一页的信息
		iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");//每页显示50条记录

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		tbcResult.SetCurSel(0);
		ShowBanPlayer(SW_HIDE);
		ShowUserInfo(SW_SHOW);
		ShowExcelBanPlayer(SW_HIDE);

		UpdateData(true);

		GetDlgItemText(IDC_CMBGAMENAME,GameName);//获取游戏名
		if(GameName == "")//游戏名不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UIC_Warn_SelectServer"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		GameList.Lookup(cmbGame.GetCurSel()+1,GameID);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取服务器名称
		if(ServerName == "")//服务器名称不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UIC_Warn_SelectServer"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		//else if(ServerName == theApp.operGM.ReadValue("MGM", "GA_UI_AREADEFAULT"))
		//{
			//ServerIP = "";
		//}
		else
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//获取服务器IP

		AssitType=cmbAssit.GetCurSel();//获取外挂类型
		if(AssitType < 0)//外挂类型不能为空
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

// 翻页进行查询
void GMGameAssist::OnCbnSelchangeCmbpage()
{
	try
	{	
		if(pageInfo)//如果可以翻页的话
		{
			iIndex = cmbPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
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

//修改循环查询的时间间隔
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

		KillTimer(1);// 根据情况而定
		GameAssist();
		SetTimer(1,refreshTime * 60000,NULL);
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","GA_WARN_EDITTIM"),theApp.operGM.ReadValue("MGM","Error"),0);
	}
}

//查询游戏外挂信息
void GMGameAssist::GameAssist()
{
	try
	{
		CIni mIni;

		int midlength = 0;
		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
		char strInt[10];

		_itoa(GameID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GameID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID
		socketdata.AddTFLV(CEnumCore::TagName::GameName,CEnumCore::TagFormat::TLV_STRING,strlen(GameName),(unsigned char *)mIni.wcharToChar(GameName));//游戏名称
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_City,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//大区名称
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_IP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//大区IP

		_itoa(AssitType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::ToolProcTypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//类型ID

		_itoa(iIndex,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		midlength=socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::HARMFUL_PROC_QUERY))//发送查询游戏外挂信息的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","GA_WARN_SEARCHGA"),theApp.operGM.ReadValue("MGM","Error"),0);
	}
}

// 单击封停帐号列表保存当前行号
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
			mItem = listResult.SubItemHitTest(&lvinfo);//保存在列表中选中的行号
		}
		else
		{
			mItem = -1;
		}
	}
	*pResult = 0;
}

// 双击封停帐号列表踢玩家下线
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
			mItem = listResult.SubItemHitTest(&lvinfo);//保存在列表中选中的行号
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
					socketdata.InitCreate(1,10);//共有四个参数，服务器IP、玩家昵称、玩家帐号、操作员ID
					char strInt[10];

					socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
					socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
					socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

					_itoa(userbyID,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

					int midlength = socketdata.EnBody();
					if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::WA_ADMIN,CEnumCore::ServiceKey::WA_KickPlayer))//发送强制玩家下线的请求
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);
						dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
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

// 切换选项卡进行操作
void GMGameAssist::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{

	CIni mIni;

	if(tbcResult.GetCurSel()==0)//如果选中的是外挂信息列表的页面
	{		
		ShowBanPlayer(SW_HIDE);
		ShowUserInfo(SW_SHOW);
		ShowExcelBanPlayer(SW_HIDE);
	}
	else if(tbcResult.GetCurSel()==1)//如果选中的是封停帐号的页面
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
	else if(tbcResult.GetCurSel()==2) //批量封停帐号
	{
		ShowUserInfo(SW_HIDE);
		ShowBanPlayer(SW_HIDE);
		ShowExcelBanPlayer(SW_SHOW);
	}
	*pResult = 0;
}

// 封停帐号
void GMGameAssist::OnBnClickedBtnban()
{
	try
	{		
		CIni mIni;			
		CString BanAccount = "";
		CString BanTime="";///////////////////////////////记录封停时间
		GetDlgItemText(IDC_EDITTIME,BanTime);
		int RealTime = atoi(BanTime)*24*60;

		GetDlgItemText(IDC_EDITACCOUNT,BanAccount);//获取玩家帐号
		if(BanAccount == "")//待封停的玩家帐号不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","BU_UI_AccountNull"),theApp.operGM.ReadValue("MGM","Warn"),0);
			return;
		}				

		CString BanReason = "";
		GetDlgItemText(IDC_EDITREASON, BanReason);
		if(strlen(BanReason) >= 256 || strlen(BanReason)==0||BanTime=="")//封停或解封原因不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","BU_Warn_ContentNull"),theApp.operGM.ReadValue("MGM","Warn"),0);
			return;
		}

		int userbyID = theApp.UserByID;//操作员ID

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有四个参数，服务器IP、玩家帐号、封停或解封原因、操作员ID
		char strInt[10];
		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(BanAccount),(unsigned char *)mIni.wcharToChar(BanAccount));//玩家帐号

		_itoa(cmbType.GetCurSel()+1, strInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::WA_Reason,CEnumCore::TagFormat::TLV_STRING,sizeof(int),(unsigned char *)&strInt);//封停类型

		_itoa(RealTime, strInt, 10);
		socketdata.AddTFLV(CEnumCore::TagName::WA_Time,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//封停时间
		socketdata.AddTFLV(CEnumCore::TagName::WA_Description, CEnumCore::TagFormat::TLV_STRING,strlen(BanReason),(unsigned char *)mIni.wcharToChar(BanReason));//封停原因

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		int midlength = socketdata.EnBody();

		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::WA_ADMIN,CEnumCore::ServiceKey::WA_ClosePlayer))//发送封停玩家帐号的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}

		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

// 重置信息
void GMGameAssist::OnBnClickedBtnreset()
{	
	SetDlgItemText(IDC_EDITGAME,"");
	SetDlgItemText(IDC_EDITSERVER,"");
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITTIME,"");
	SetDlgItemText(IDC_EDITREASON,"");
	cmbType.SetCurSel(0);
}

// 接收返回信息
LRESULT GMGameAssist::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;

	dlgStatus = theApp.operGM.ReadIntValue("MGM","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	int pageCount = 0;

	switch(theApp.m_tag_id)
	{
	case CEnumCore::Message_Tag_ID::GAME_QUERY_RESP://查询游戏信息的回应
		{
			if(!GameList.IsEmpty())
			{
				GameList.RemoveAll();
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int GameID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::GameID).lpdata);//得到游戏ID
				GameList.SetAt(i-1,GameID);//将游戏ID保存在CMap类的对象UserList中
			}

			theApp.operGM.BuildComboxs(&socketdata,&cmbGame,2,CEnumCore::TagName::GameName);//构造游戏名称列表信息	

			OnCbnSelchangeCmbgamename();
		}
		break;
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://查询游戏服务器IP的回应
		{
			//AfxMessageBox("服务器IP查询");
			if(!ServerList.IsEmpty())
			{
				ServerList.RemoveAll();
				ServerCityToServerIP.clear();
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到游戏服务器IP
				ServerList.SetAt(i,ServerIP);//将游戏服务器IP保存在CMap类的对象ServerList中
				CString ServerCity = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_City).lpdata;//得到游戏大区名字
				ServerCityToServerIP.insert(pair<CString, CString>(ServerCity, ServerIP));
			}
			/*
			CString str;
			map<CString, CString>::iterator it;
			for(it = ServerCityToServerIP.begin(); it != ServerCityToServerIP.end(); it++)
				str += it->second;
			AfxMessageBox(str);
			*/
			theApp.operGM.BuildComboxs(&socketdata,&cmbServer,1,CEnumCore::TagName::ServerInfo_City);//构造游戏服务器列表信息
			
			//cmbServer.InsertString(0, (LPCSTR)theApp.operGM.ReadValue("MGM", "GA_UI_AREADEFAULT"));//大区列表中添加该条作为默认查询选项 Added by yanfei_qin 2010-9-14
			//cmbServer.SetCurSel(0);
		}
		break;
	case CEnumCore::Message_Tag_ID::HARMFUL_PROC_QUERY_RESP://外挂进程工具包
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operGM.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operGM.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					pageInfo = false;//不能翻页		
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
	case CEnumCore::Message_Tag_ID::GM_AccountInfo_Resp://查询vip用户服务端返回消息
		{			
			//AfxMessageBox("接收查询信息");
			char* isVip = (char*)&socketdata.getTLVByName(1,CEnumCore::TagName::GM_AccountInfo_Vip).lpdata;  //测试是否vip
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
			//AfxMessageBox("批量封停服务器回应");
			char* ban = (char*)&socketdata.getTLVByName(1,CEnumCore::TagName::MESSAGE).lpdata; 

			if(strcmp(ban, "封停成功"))   //若封停不成功
				listVIPAccount.InsertItem(0, m_curAccount);   //记录不成功帐号
			SetEvent(m_hBanAccountEvent);
		}
		break;
	default:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operGM.ShowResult(result);//显示操作结果
			
			OnBnClickedBtnreset();
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	return false;
}

// 关闭对话框
void GMGameAssist::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	cmbAssit.SetCurSel(0);
}

// 关闭对话框
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

//显示玩家资料信息
void GMGameAssist::ShowUserInfo(int m_cmdShow)
{
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(m_cmdShow);
}

//显示封停帐号
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

//显示导入数据
void GMGameAssist::ShowExcelBanPlayer(int m_cmdShow)
{
	GetDlgItem(IDC_BTNBANBATCH)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTBANBATCH)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTVIP)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CHECKVIP)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITIMPORT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNIMPORT)->ShowWindow(m_cmdShow);

}

//打开导出功能的文件对话框
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
		MessageBox(NULL, "请指定文件",  MB_OK | MB_TOPMOST);
		return;
	}
}
*/
//导出数据到xls文件
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
		MessageBox(NULL, "请指定文件", MB_OK | MB_TOPMOST);
		return;
	}
	
	CString str;
	str.Format("选择<%s>作为sheet表的名称是吗?\n", GameName);
	if(MessageBox(str,  NULL, MB_YESNO | MB_TOPMOST) == IDNO)
		return;

	CListCtrl* list;
	if (tbcResult.GetCurSel()==0)
		list = &listResult;
	else if(tbcResult.GetCurSel()==2)
		list = &listVIPAccount;

	theApp.operGM.ExportCListCtrlToExcel(list, path, GameName);
}



//打开导入功能的文件对话框
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
		MessageBox(NULL, "请指定文件",  MB_OK | MB_TOPMOST);
		return;
	}
}


*/
//导入数据到CListCtrl
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
		MessageBox(NULL, "请指定文件",  MB_OK | MB_TOPMOST);
		return;
	}

	CString str;
	str.Format("请确定xls中存在名为%s的sheet表", GameName);
	if (MessageBox(str,  NULL, MB_YESNO | MB_TOPMOST) == IDNO)
		return;

	//while(listAccountImport.DeleteColumn(0)){}	//清空CListCtrl的内容
	listVIPAccount.DeleteAllItems();
	listAccountImport.DeleteAllItems();

	theApp.operGM.ImportCListCtrlFromExcel(&listAccountImport, path, GameName);
}


//发送查询vip帐号消息
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
				//发送需查询的帐号
				if (!strcmp(hdi.pszText, "久游帐号")) 
				{
					account = pCls->listAccountImport.GetItemText(rowCount, colCount);

					CSocketData socketdata;
					socketdata.InitCreate(1,2);//共有2个参数，玩家帐号、操作员ID

					socketdata.AddTFLV(CEnumCore::TagName::PlayerAccount,CEnumCore::TagFormat::TLV_STRING,strlen(account),(unsigned char *)(LPCTSTR)(account));//玩家帐号

					int userbyID = theApp.UserByID;//操作员ID
					char strInt[10];
					_itoa(userbyID,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

					int midlength = socketdata.EnBody();

					if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::GM_AccountInfo_Vip))//发送查询玩家帐号是否为vip的请求
					{
						pCls->dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
					}
					socketdata.Destroy();
					WaitForSingleObject(pCls->m_hCheckVipEvent, INFINITE);
					//ResetEvent(pCls->m_hCheckVipEvent);
					if(pCls->m_isVipAccount)
					{
						pCls->listAccountImport.DeleteItem(rowCount);
						rowCount -= 1;   //减少一行后, 各个行号的顺序变了, 需要恢复
					}
					pCls->m_isVipAccount = FALSE;
				}
			}		
		}

		//删除clistctrl中的vip帐号
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



//发送批量封停帐号信息
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

		if(strcmp(pCls->listAccountImport.GetItemText(0, 0), pCls->GameName))    //是否已经选择对应的游戏
		{
			AfxMessageBox("请确认你已经选择了对应的游戏,且表格中填写的游戏名称正确");
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
				if (!strcmp(hdi.pszText, "久游帐号"))  //久游帐号
				{
					//accounts += pCls->listAccountImport.GetItemText(rowCount, colCount) + token;
					accounts = pCls->listAccountImport.GetItemText(rowCount, colCount);
					pCls->m_curAccount = accounts;
				}
				if (!strcmp(hdi.pszText, "游戏大区"))   //游戏大区
				{
					city = pCls->listAccountImport.GetItemText(rowCount, colCount);
					it = pCls->ServerCityToServerIP.find(city);
					//if (it != pCls->ServerCityToServerIP.end())
					serverIPs = it->second;
					//AfxMessageBox((LPCTSTR)(city + serverIPs));
				}
				if(!strcmp(hdi.pszText, "封停时间"))    //封停时间
				{
					//banTimes += pCls->listAccountImport.GetItemText(rowCount, colCount) + token;
					banTimes = pCls->listAccountImport.GetItemText(rowCount, colCount);
				}
				if(!strcmp(hdi.pszText, "封停原因"))       //封停原因
				{
					//resons = pCls->listAccountImport.GetItemText(rowCount, colCount) + token;
					resons = pCls->listAccountImport.GetItemText(rowCount, colCount);
				}
				if(!strcmp(hdi.pszText, "封停类型"))      //封停类型
				{
					//types = pCls->listAccountImport.GetItemText(rowCount, colCount) + token;
					types = pCls->listAccountImport.GetItemText(rowCount, colCount);
					if(!strcmp((LPCTSTR)types, "系统封停"))
						typeID = 1;
					else if(!strcmp((LPCTSTR)types, "系统临时封停"))
						typeID = 2;
					else if(!strcmp((LPCTSTR)types, "用户自助"))
						typeID = 3;
					else if(!strcmp((LPCTSTR)types, "用户临时自助"))
						typeID = 4;
				}					
			}

			//发送批量封停帐号
			int userbyID = theApp.UserByID;//操作员ID
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有四个参数，服务器IP、玩家帐号、封停或解封原因、操作员ID
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(serverIPs),(unsigned char *)mIni.wcharToChar(serverIPs));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(accounts),(unsigned char *)mIni.wcharToChar(accounts));//玩家帐号

			_itoa(typeID, strInt, 10);
			socketdata.AddTFLV(CEnumCore::TagName::WA_Reason,CEnumCore::TagFormat::TLV_STRING,sizeof(types),(unsigned char *)&strInt);//封停类型

			//_itoa(RealTime, strInt, 10);
			char itime[10];
			sprintf(itime, "%s", (LPCTSTR)banTimes);
			socketdata.AddTFLV(CEnumCore::TagName::WA_Time,CEnumCore::TagFormat::TLV_INTEGER,sizeof(banTimes),(unsigned char *)&itime);//封停时间
			socketdata.AddTFLV(CEnumCore::TagName::WA_Description, CEnumCore::TagFormat::TLV_STRING,strlen(resons),(unsigned char *)mIni.wcharToChar(resons));//封停原因

			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

			int midlength = socketdata.EnBody();

			if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::WA_ADMIN,CEnumCore::ServiceKey::WA_ClosePlayerGroup))//发送封停玩家帐号的请求
			{
				pCls->dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
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
//查询vip帐户按钮响应
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
		MessageBox(NULL, "创建查询vip帐号线程失败", MB_OK | MB_TOPMOST);
	}
	
}
//批量封停帐号按钮响应
void GMGameAssist::OnBnClickedBtnBanBatch()
{
	if(MessageBox("你确定已经查询过VIP帐号了吗?", NULL,  MB_YESNO | MB_TOPMOST)==IDNO)
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
		MessageBox(NULL, "创建批量封停帐号线程失败", MB_OK | MB_TOPMOST);
	}
}

//查询所有外挂帐号
void GMGameAssist::OnBnClickedBtnCheckAccountAll()
{
	// TODO: Add your control notification handler code here

	try
	{
		iIndex = theApp.operGM.ReadIntValue("MGM","index");//查询第一页的信息
		iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");//每页显示50条记录

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		tbcResult.SetCurSel(0);
		ShowBanPlayer(SW_HIDE);
		ShowUserInfo(SW_SHOW);

		UpdateData(true);

		GetDlgItemText(IDC_CMBGAMENAME,GameName);//获取游戏名
		if(GameName == "")//游戏名不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UIC_Warn_SelectServer"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		GameList.Lookup(cmbGame.GetCurSel()+1,GameID);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取服务器名称
		if(ServerName == "")//服务器名称不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UIC_Warn_SelectServer"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		ServerIP = "";


		AssitType=cmbAssit.GetCurSel();//获取外挂类型
		if(AssitType < 0)//外挂类型不能为空
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
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
		char strInt[10];

		_itoa(GameID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GameID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID
		socketdata.AddTFLV(CEnumCore::TagName::GameName,CEnumCore::TagFormat::TLV_STRING,strlen(GameName),(unsigned char *)mIni.wcharToChar(GameName));//游戏名称
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_City,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//大区名称
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_IP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//大区IP

		_itoa(AssitType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::ToolProcTypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//类型ID

		_itoa(iIndex,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = 0;
		midlength=socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::HARMFUL_PROC_QUERY))//发送查询游戏外挂信息的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}
}


