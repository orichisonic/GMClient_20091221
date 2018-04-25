// JW2BanPlayer.cpp : 实现文件
//

#include "stdafx.h"
#include "M_JW2.h"
#include "JW2BanPlayer.h"
#include ".\JW2BanPlayer.h"


// CJW2BanPlayer 对话框

IMPLEMENT_DYNAMIC(CJW2BanPlayer, CDialog)
CJW2BanPlayer::CJW2BanPlayer(CWnd* pParent /*=NULL*/)
	: CDialog(CJW2BanPlayer::IDD, pParent)
{
}

CJW2BanPlayer::~CJW2BanPlayer()
{
}

void CJW2BanPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_EDITBANACCOUNT, txtAccount);
	DDX_Control(pDX, IDC_EDITBANREASON, txtReason);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_CMBPAGE, cmbLPage);
}


BEGIN_MESSAGE_MAP(CJW2BanPlayer, CDialog)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_CBN_SELCHANGE(IDC_CMBUIPAGE, OnCbnSelchangeCmbuipage)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_BN_CLICKED(IDC_BTNBAN, OnBnClickedBtnban)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
END_MESSAGE_MAP()

// 初始化对话框
BOOL CJW2BanPlayer::OnInitDialog()
{
	CDialog::OnInitDialog();	
	InitUI();// 初始化显示字符			

	nItem = -1;// 单击用户列表得到行号
	mItem = -1;
	pageInfo = false;// 判断是否需要翻页
	pageUInfo = false;
	ServerIP = "";// 游戏服务器IP	
	UserAccount = "";// 玩家帐号	
	UserName = "";//玩家帐号和昵称
	UserNick = "";
	UserID = 0;//玩家ID

	CRect rs;
	GetClientRect(rs);//获取对话框的大小信息

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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listResult的位置
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listResult的位置
	}

	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);


	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Create");//初始建立对话框

	theApp.operJW2.GetServerList();

	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//发送查询请求	

	return TRUE;
}

// 初始化显示字符
void CJW2BanPlayer::InitUI()
{

	SetWindowText(theApp.operJW2.ReadValue("MJW2","BU_UI_BanPlayer"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operJW2.ReadValue("MJW2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operJW2.ReadValue("MJW2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operJW2.ReadValue("MJW2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operJW2.ReadValue("MJW2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operJW2.ReadValue("MJW2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operJW2.ReadValue("MJW2","Cancel"));
	SetDlgItemText(IDC_LBLHINT,theApp.operJW2.ReadValue("MJW2","BU_UI_LblHint"));	
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operJW2.ReadValue("MJW2","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLBANACCOUNT,theApp.operJW2.ReadValue("MJW2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLBANREASON,theApp.operJW2.ReadValue("MJW2","BU_UI_reason"));
	SetDlgItemText(IDC_BTNBAN,theApp.operJW2.ReadValue("MJW2","BU_UI_TpgOpen"));
	SetDlgItemText(IDC_BTNRESET,theApp.operJW2.ReadValue("MJW2","Reset"));

	tbcResult.InsertItem(0,theApp.operJW2.ReadValue("MJW2","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operJW2.ReadValue("MJW2","BU_UI_TpgOpen"));
	tbcResult.InsertItem(2,theApp.operJW2.ReadValue("MJW2","BU_UI_TpgList"));
	tbcResult.InsertItem(3,theApp.operJW2.ReadValue("MJW2","BU_UI_BtnSave"));
	tbcResult.InsertItem(4,theApp.operJW2.ReadValue("MJW2","BU_UI_Tpgquary"));
}

//处理快捷键响应函数
BOOL CJW2BanPlayer::PreTranslateMessage(MSG* pMsg)
{
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operJW2.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operJW2.CopyListInfo(&listResult);
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					for(int i=0; i<listUser.GetItemCount(); i++)
					{
					    listUser.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listUser.EnsureVisible(i,false);
					}
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
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
void CJW2BanPlayer::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rs;
	GetClientRect(rs);

	CRect newRect;
	
	if(GrpSearch.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + grpHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listResult的位置
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listResult的位置
	}
}

//设置背景颜色
HBRUSH CJW2BanPlayer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询资料信息
void CJW2BanPlayer::OnBnClickedUisearch()
{
	try
	{

		nItem = -1;//列表没有选定项
		mItem = -1;
		pageInfo = false;//列表不能翻页	
		pageUInfo = false;
		cmbPage.ResetContent();//清除列表翻页的复选框
		cmbLPage.ResetContent();
		while(listUser.DeleteColumn(0)){}//清除列表中的所有内容
		while(listResult.DeleteColumn(0)){}//清除列表中的所有内容

		UpdateData(true);			

		GetDlgItemText(IDC_CMBUISERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Warn_SelectServer"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//获取玩家帐号
		GetDlgItemText(IDC_EDITUINICK,UserNick);//获取玩家昵称

		if((UserName != "") || (UserNick != ""))//玩家帐号和玩家昵称不同时为空时，查询玩家资料信息
		{
			tbcResult.SetCurSel(0);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	        GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
			UserInfo();//查询玩家资料信息
		}
		else//玩家帐号和玩家昵称同时为空时，查询所有被封停帐号列表信息
		{
			tbcResult.SetCurSel(2);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	        GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
			AllBanUserList();//查询所有被封停帐号列表信息
		}
	}
	catch(...)
	{
	}
}

// 查询玩家资料信息
void CJW2BanPlayer::UserInfo()
{
	try
	{		
		CIni mIni;	

		nItem = -1;
		pageInfo = false;		
		cmbPage.ResetContent();
		while(listUser.DeleteColumn(0)){}
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");//查询第一页的信息
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//每页显示50条记录

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNT_QUERY);//发送查询玩家资料信息的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_UserInfo"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 查询所有被封停帐号列表信息
void CJW2BanPlayer::AllBanUserList()
{
	try
	{				
		CIni mIni;
		
		mItem = -1;
		pageUInfo = false;		
		cmbLPage.ResetContent();
		while(listResult.DeleteColumn(0)){}

		char strInt[10];
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNTREMOTE_QUERY);
		
		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_UserInfo"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 翻页进行查询
void CJW2BanPlayer::OnCbnSelchangeCmbuipage()
{	
	try
	{		
		if(pageInfo)
		{	
			CIni mIni;

			while(listUser.DeleteColumn(0)){}
			
			int index = cmbPage.GetCurSel() + 1;//页数为cmbPage当前的索引值加1，也就是cmbPage中当前显示的值
			int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//每页显示50条记录
			
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
		
			if(tbcResult.GetCurSel() == 0)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNT_QUERY);
			}
			else if(tbcResult.GetCurSel() == 2)
			{				
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNTREMOTE_QUERY);
				
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Page"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 翻页进行查询玩家资料信息
void CJW2BanPlayer::OnCbnSelchangeCmbpage()
{
	try
	{		
		if(pageUInfo)
		{	
			CIni mIni;

			while(listResult.DeleteColumn(0)){}
			
			int index = cmbLPage.GetCurSel() + 1;//页数为cmbPage当前的索引值加1，也就是cmbPage中当前显示的值
			int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//每页显示50条记录
			
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
		
			if(tbcResult.GetCurSel() == 0)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNT_QUERY);
			}
			else if(tbcResult.GetCurSel() == 2)
			{				
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNTREMOTE_QUERY);
				
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Page"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 单击资料信息保存当前行号
void CJW2BanPlayer::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listUser.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listUser.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listUser.SubItemHitTest(&lvinfo);//保存在列表中选中的行号
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

// 双击资料信息进行操作
void CJW2BanPlayer::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		if(listUser.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listUser.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listUser.SubItemHitTest(&lvinfo);//保存在列表中选中的行号

			if(nItem >= 0)
			{
				CIni mIni;
				if(tbcResult.GetCurSel() == 0)//如果当前是在玩家资料信息的页面
				{
					tbcResult.SetCurSel(1);//跳转到进行帐号封停的页面

					GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

					UpdateData(false);

					SetDlgItemText(IDC_LBLBANREASON,theApp.operJW2.ReadValue("MJW2","BU_UI_reason"));//封停原因
					SetDlgItemText(IDC_BTNBAN,theApp.operJW2.ReadValue("MJW2","BU_UI_TpgOpen"));//帐号封停

					//txtAccount.SetReadOnly(true);//玩家帐号的CEdit对象设置为只读属性

					UserAccount = theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserID"));// 获取要封停的玩家帐号
				    UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));// 获取要封停的玩家ID

					SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);//设置要封停的玩家帐号
					SetDlgItemText(IDC_EDITBANREASON,"");
				}				
			}
		}
		else
		{
			nItem = -1;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// 单击封停账号列表信息保存当前行号
void CJW2BanPlayer::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 2)
	{
		if(listResult.GetItemCount() >0)
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

// 双击封停账号列表信息进行解封
void CJW2BanPlayer::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		if(listResult.GetItemCount() > 0)
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
				CIni mIni;
				if(tbcResult.GetCurSel() == 2)//如果当前是在封停账号列表的界面
				{
					tbcResult.SetCurSel(3);//跳转到进行帐号解封的页面
					GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

					UpdateData(false);

					SetDlgItemText(IDC_LBLBANREASON,theApp.operJW2.ReadValue("MJW2","BU_UI_UnBind"));//解封原因
					SetDlgItemText(IDC_BTNBAN,theApp.operJW2.ReadValue("MJW2","BU_UI_BtnSave"));//解封帐号

					//txtAccount.SetReadOnly(true);//玩家帐号的CEdit对象设置为只读属性

				    UserAccount = theApp.operJW2.GetValueByColName(&listResult, mItem, theApp.operJW2.ReadValue("MJW2","JW2_UserID"));// 获取要解封的玩家帐号
				    UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listResult, mItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));// 获取要解封的玩家ID

					SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);//设置要解封的玩家帐号
					SetDlgItemText(IDC_EDITBANREASON,"");
				}				
			}
		}
		else
		{
			mItem = -1;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}



// 切换选项卡进行查询
void CJW2BanPlayer::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{	
	CIni mIni;

	if(tbcResult.GetCurSel()==0)//如果选中的是玩家资料信息的页面
	{
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
	}
	else if(tbcResult.GetCurSel()==2)//如果选中的是封停帐号列表的页面
	{
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	    GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
	}
	else if(tbcResult.GetCurSel()==1)//如果选中的是封停帐号的页面
	{
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

		SetDlgItemText(IDC_LBLBANREASON,theApp.operJW2.ReadValue("MJW2","BU_UI_reason"));//封停原因
		SetDlgItemText(IDC_BTNBAN,theApp.operJW2.ReadValue("MJW2","BU_UI_TpgOpen"));//帐号封停

	//	txtAccount.SetReadOnly(true);//玩家帐号的CEdit对象设置为只读属性

		UpdateData(false);

		if((listUser.GetItemCount() > 0) && (nItem >= 0))//如果玩家帐号和昵称不同时为空，nItem>=0，说明已经查询过玩家资料信息，并且已经选中了要封停的帐号，可以进行封停操作
		{
			UserAccount = theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserID"));// 获取玩家帐号
			UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));// 获取玩家ID

			SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);
			SetDlgItemText(IDC_EDITBANREASON,"");
		}
		else
		{
			SetDlgItemText(IDC_EDITBANACCOUNT,"");
			SetDlgItemText(IDC_EDITBANREASON,"");
		}
	}
	else if(tbcResult.GetCurSel()==3)//如果选中的是解封帐号的页面
	{
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

		SetDlgItemText(IDC_LBLBANREASON,theApp.operJW2.ReadValue("MJW2","BU_UI_UnBind"));
		SetDlgItemText(IDC_BTNBAN,theApp.operJW2.ReadValue("MJW2","BU_UI_BtnSave"));

	//	txtAccount.SetReadOnly(true);//玩家帐号的CEdit对象设置为只读属性
		UpdateData(false);

		if((listResult.GetItemCount() > 0) && (mItem >= 0))//如果玩家帐号和昵称同时为空，nItem>=0，说明已经查询过封停帐号列表，并且已经选中了要解封的帐号，可以进行解封操作
		{
			UserAccount = theApp.operJW2.GetValueByColName(&listResult, mItem, theApp.operJW2.ReadValue("MJW2","JW2_UserID"));// 获取玩家帐号
			UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listResult, mItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));// 获取玩家ID

			SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);
			SetDlgItemText(IDC_EDITBANREASON,"");
		}
		else
		{
			SetDlgItemText(IDC_EDITBANACCOUNT,"");
			SetDlgItemText(IDC_EDITBANREASON,"");
		}
	}
	else if(tbcResult.GetCurSel()==4)//如果选中的是查询帐号有没有被封停的页面
	{
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

		UpdateData(false);

		SetDlgItemText(IDC_BTNBAN,theApp.operJW2.ReadValue("MJW2","Search"));
		UserID = 0;
		//txtAccount.SetReadOnly(false);//玩家帐号的CEdit对象取消只读属性

		SetDlgItemText(IDC_EDITBANACCOUNT,"");
		SetDlgItemText(IDC_EDITBANREASON,"");
	}
	*pResult = 0;
}

// 封停或解封帐号
void CJW2BanPlayer::OnBnClickedBtnban()
{
	try
	{
		CIni mIni;
	
		UpdateData(true);			

		GetDlgItemText(IDC_CMBUISERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Warn_SelectServer"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		CString BanAccount = "";
		txtAccount.GetWindowText(BanAccount);//获取玩家帐号
		if(BanAccount == "")//玩家帐号不能为空
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","BU_UI_AccountNull"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
			return;
		}				

		CString BanReason = "";
		txtReason.GetWindowText(BanReason);//获取封停或解封原因
		if((tbcResult.GetCurSel() == 1) || (tbcResult.GetCurSel() == 3))// 选择的是封停或解封帐号
		{			
			if(strlen(BanReason) >= 256)//封停或解封原因不能为空
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","BU_UI_ReasonTooLong"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}
			else if(strlen(BanReason)<10)
			{
				MessageBox("原因不能小于5个中文字",0);
				return;
			}
		}
		else if(tbcResult.GetCurSel() == 4)// 选择的是查询帐号有没有被封停
		{
			CString m_ServerName;
			GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//获取服务器名称
			if(m_ServerName == "")//服务器名称不能为空
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Warn_SelectServer"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//获取服务器IP
		}
		int userbyID = theApp.UserByID;//操作员ID
		GetDlgItemText(IDC_EDITBANACCOUNT,UserName);

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、封停或解封原因、操作员ID、玩家ID
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

	

		socketdata.AddTFLV(CEnumCore::TagName::JW2_Reason,CEnumCore::TagFormat::TLV_STRING,strlen(BanReason),(unsigned char *)mIni.wcharToChar(BanReason));//封停或解封原因

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID
		
		switch(tbcResult.GetCurSel())
		{
		case 1:
			UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));// 保存选中的玩家ID
			break;
		case 3:
			UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listResult, mItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));// 保存选中的玩家ID
			break;
		case 4:
			break;
		}
		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID

		int midlength = socketdata.EnBody();
		
		if(tbcResult.GetCurSel() == 1)
		{

			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNT_CLOSE);//发送封停玩家帐号的请求
		}
		else if(tbcResult.GetCurSel() == 3)
		{
			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNT_OPEN);//发送解封玩家帐号的请求
		}
		else if(tbcResult.GetCurSel() == 4)
		{
			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNT_BANISHMENT_QUERY);//发送查询玩家帐号有没有被封停的请求
		}
		
		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

// 重置信息
void CJW2BanPlayer::OnBnClickedBtnreset()
{
	SetDlgItemText(IDC_EDITBANREASON,"");
	if(tbcResult.GetCurSel() == 4)
	{
		SetDlgItemText(IDC_EDITBANACCOUNT,"");
	}		
}

// 接收返回信息
LRESULT CJW2BanPlayer::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度


	CIni mIni;

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	socketdata.DeBody(lpReceive,bodyLength);

	int pageCount = 0;

	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://查询服务器列表信息的回应
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString sIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到服务器IP
				ServerList.SetAt(i,sIP);//将服务器IP保存在CMap类的对象ServerList中
			}

			theApp.operJW2.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_QUERY_RESP://查询玩家资料信息的回应
		{
			if(pageInfo)
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					nItem = -1;//不能选中某一行
					pageInfo = false;//不能翻页				
					cmbPage.ResetContent();//清空页数复选框
					while(listUser.DeleteColumn(0)){}//清空CListCtrl内容
				}
				else
				{
					nItem = 0;
					cmbPage.ResetContent();//清空页数复选框，以便重新构造
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbPage.AddString(str);//在复选框中构造页数信息
					}
					cmbPage.SetCurSel(0);//在复选框中选中第一页
					if(pageCount == 1)
					{
						pageInfo = false;//只有一页数据，不能翻页
					}
					else
					{
						pageInfo = true;//有多页数据，可以翻页
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNTREMOTE_QUERY_RESP://查询所有被封停帐号列表的回应
		{
			if(pageInfo)
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					mItem = -1;
					pageUInfo = false;					
					cmbLPage.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					mItem = 0;
					cmbLPage.ResetContent();//清空复选框
					for(int i=1;i <= pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbLPage.AddString(str);//在复选框中构造页数信息
					}
					cmbLPage.SetCurSel(0);//在复选框中选中第一页
					if(pageCount == 1)
					{
						pageUInfo = false;//只有一页数据，不能翻页
					}
					else
					{
						pageUInfo = true;//有多页数据，可以翻页
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_CLOSE_RESP://封停玩家帐号的回应
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//显示操作结果

			/*tbcResult.SetCurSel(0);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);*/
			//UserInfo();//查询玩家帐号信息
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_OPEN_RESP://解封玩家帐号的回应
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//显示操作结果

			tbcResult.SetCurSel(2);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
			AllBanUserList();//查询所有被封停帐号列表
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_BANISHMENT_QUERY_RESP://查询帐号有没有被封停的回应
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			if(m_tflv.m_tagName==CEnumCore::TagName::MESSAGE)
			{
				CString result = (LPCTSTR)&m_tflv.lpdata;
				theApp.operJW2.ShowResult(result);//显示返回结果
			}
			else
			{
				theApp.operJW2.ShowResult("账号已经封停");//显示返回结果
			}
		}
		break;
	default:
		break;
	}

	socketdata.Destroy();
	return false;
}

//单击用户资料信息的列名进行排序
void CJW2BanPlayer::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operJW2.SortListInfo(&listUser,pNMHDR,pResult);
}

//单击结果信息的列名进行排序
void CJW2BanPlayer::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operJW2.SortListInfo(&listResult,pNMHDR,pResult);
}

// 关闭对话框
void CJW2BanPlayer::OnBnClickedUicancel()
{
	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Close");//关闭窗体
	OnClose();
}

// 关闭对话框
void CJW2BanPlayer::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}


