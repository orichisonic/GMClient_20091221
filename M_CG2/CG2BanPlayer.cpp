// CG2BanPlayer.cpp : 实现文件
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2BanPlayer.h"
#include ".\CG2banplayer.h"


// CCG2BanPlayer 对话框

IMPLEMENT_DYNAMIC(CCG2BanPlayer, CDialog)
CCG2BanPlayer::CCG2BanPlayer(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2BanPlayer::IDD, pParent)
{
}

CCG2BanPlayer::~CCG2BanPlayer()
{
}

void CCG2BanPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbUPage);
	DDX_Control(pDX, IDC_LISTUSERINFO,listUser);
	DDX_Control(pDX, IDC_EDITBANACCOUNT, txtAccount);
	DDX_Control(pDX, IDC_EDITBANREASON, txtReason);
	DDX_Control(pDX, IDC_DTPBANENDDATE, dtcBanEndDate);
	DDX_Control(pDX, IDC_DTPBANENDTIME, dtcBanEndTime);
	DDX_Control(pDX, IDC_CMBBANTYPE, cmbBanType);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
}


BEGIN_MESSAGE_MAP(CCG2BanPlayer, CDialog)
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
	ON_CBN_SELCHANGE(IDC_CMBBANTYPE, OnCbnSelchangeCmbbantype)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
END_MESSAGE_MAP()

// 初始化对话框
BOOL CCG2BanPlayer::OnInitDialog()
{
	CDialog::OnInitDialog();	
	InitUI();// 初始化显示字符	
	InitBanType();

	nItem = -1;// 单击用户列表得到行号
	mItem = -1;
	pageInfo = false;// 判断是否需要翻页
	pageUInfo = false;
	ServerIP = "";// 游戏服务器IP	
	UserName = "";//玩家帐号
	UserNick = "";//玩家昵称
	UserID = "";//玩家ID

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

	dtcBanEndTime.SetFormat("HH:mm:ss");
	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
	GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
	GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
	GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//

	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//初始建立对话框

	theApp.operCG2.GetServerList();//请求所有的游戏服务器列表

	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//发送查询请求	

	return TRUE;
}

// 初始化显示字符
void CCG2BanPlayer::InitUI()
{

	SetWindowText(theApp.operCG2.ReadValue("MCG2","BU_UI_BanPlayer"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operCG2.ReadValue("MCG2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLHINT,theApp.operCG2.ReadValue("MCG2","BU_UI_LblHint"));	
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLBANACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLBANENDTIME,theApp.operCG2.ReadValue("MCG2","BU_UI_LblBanEndTime"));
	SetDlgItemText(IDC_LBLBANTYPE,theApp.operCG2.ReadValue("MCG2","BU_UI_LblBanType"));
	SetDlgItemText(IDC_LBLBANREASON,theApp.operCG2.ReadValue("MCG2","BU_UI_reason"));
	SetDlgItemText(IDC_BTNBAN,theApp.operCG2.ReadValue("MCG2","BU_UI_TpgOpen"));
	SetDlgItemText(IDC_BTNRESET,theApp.operCG2.ReadValue("MCG2","Reset"));

	tbcResult.InsertItem(0,theApp.operCG2.ReadValue("MCG2","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operCG2.ReadValue("MCG2","BU_UI_TpgOpen"));
	tbcResult.InsertItem(2,theApp.operCG2.ReadValue("MCG2","BU_UI_TpgList"));
	tbcResult.InsertItem(3,theApp.operCG2.ReadValue("MCG2","BU_UI_BtnSave"));
	tbcResult.InsertItem(4,theApp.operCG2.ReadValue("MCG2","BU_UI_Tpgquary"));
}

// 自动改变大小
void CCG2BanPlayer::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CCG2BanPlayer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询资料信息
void CCG2BanPlayer::OnBnClickedUisearch()
{
	try
	{

		nItem = -1;//列表没有选定项
		mItem = -1;
		pageInfo = false;//列表不能翻页	
		pageUInfo = false;
		cmbPage.ResetContent();//清除列表翻页的复选框
		cmbUPage.ResetContent();
		while(listUser.DeleteColumn(0)){}
		while(listResult.DeleteColumn(0)){}//清除列表中的所有内容

		UpdateData(true);			

		CString m_ServerName;
		GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//获取游戏服务器的名称
		if(m_ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_SelectServer"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
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
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);//SW_SHOW);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);


			GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);//SW_HIDE);
	        GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//
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

			GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//
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
void CCG2BanPlayer::UserInfo()
{
	try
	{		
		CIni mIni;	

		nItem = -1;
		pageUInfo = false;		
		cmbUPage.ResetContent();
		while(listUser.DeleteColumn(0)){}
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");//查询第一页的信息
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//每页显示50条记录

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Query);//发送查询玩家资料信息的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// 查询所有被封停帐号列表信息
void CCG2BanPlayer::AllBanUserList()
{
	try
	{				
		CIni mIni;
		
		mItem = -1;
		pageInfo = false;		
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}

		char strInt[10];
		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_BanAccount_Query);
		
		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// 翻页进行查询
void CCG2BanPlayer::OnCbnSelchangeCmbuipage()
{	
	////OperationCG2 operCG2;
	try
	{		
		if(pageUInfo)
		{	
			CIni mIni;

			while(listUser.DeleteColumn(0)){}
			
			int index = cmbUPage.GetCurSel() + 1;//页数为cmbPage当前的索引值加1，也就是cmbPage中当前显示的值
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//每页显示50条记录
			
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
		
			if(tbcResult.GetCurSel() == 0)
			{
				theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Query);
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Page"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// 翻页查询封停账号列表
void CCG2BanPlayer::OnCbnSelchangeCmbpage()
{
	//OperationCG2 operCG2;
	try
	{		
		if(pageInfo)
		{	
			CIni mIni;

			while(listResult.DeleteColumn(0)){}
			
			int index = cmbPage.GetCurSel() + 1;//页数为cmbPage当前的索引值加1，也就是cmbPage中当前显示的值
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//每页显示50条记录
			
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
		
			if(tbcResult.GetCurSel() == 2)
			{				
				theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_BanAccount_Query);				
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Page"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// 单击资料信息保存当前行号
void CCG2BanPlayer::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listUser.GetItemCount() > 0)
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
void CCG2BanPlayer::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		if(listUser.GetItemCount() > 0)
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
				//////OperationCG2 operCG2;
				CIni mIni;
				if(tbcResult.GetCurSel() == 0)//如果当前是在玩家资料信息的页面
				{
					tbcResult.SetCurSel(1);//跳转到进行帐号封停的页面

					GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_SHOW);//
					GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_SHOW);//
					GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_SHOW);//
					GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_SHOW);//
					GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_SHOW);//

					CTime curTime = CTime::GetCurrentTime();//重置时间
					dtcBanEndDate.SetTime(&curTime);
					dtcBanEndTime.SetTime(&curTime);

					GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

					UpdateData(false);

					SetDlgItemText(IDC_LBLBANREASON,theApp.operCG2.ReadValue("MCG2","BU_UI_reason"));//封停原因
					SetDlgItemText(IDC_BTNBAN,theApp.operCG2.ReadValue("MCG2","BU_UI_TpgOpen"));//帐号封停

					txtAccount.SetReadOnly(true);//玩家帐号的CEdit对象设置为只读属性

					UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
				    UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
			        UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称
					iCharNo = atoi(theApp.operCG2.GetValueByColName(&listResult, nItem, theApp.operCG2.ReadValue("MCG2","CG2_CharacterNum")));//获取角色号

					SetDlgItemText(IDC_EDITBANACCOUNT,UserName);//设置要封停的玩家帐号
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

// 单击资料信息保存当前行号
void CCG2BanPlayer::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
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

// 双击资料信息进行操作
void CCG2BanPlayer::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
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
				//OperationCG2 operCG2;
				CIni mIni;
				if(tbcResult.GetCurSel() == 2)//如果当前是在封停账号列表的界面
				{
					tbcResult.SetCurSel(3);//跳转到进行帐号解封的页面
					GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
					GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
					GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
					GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
					GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//

					GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

					UpdateData(false);

					SetDlgItemText(IDC_LBLBANREASON,theApp.operCG2.ReadValue("MCG2","BU_UI_UnBind"));//解封原因
					SetDlgItemText(IDC_BTNBAN,theApp.operCG2.ReadValue("MCG2","BU_UI_BtnSave"));//解封帐号

					txtAccount.SetReadOnly(true);//玩家帐号的CEdit对象设置为只读属性

					UserName = theApp.operCG2.GetValueByColName(&listResult,mItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 获取要解封的玩家帐号
				    UserID = theApp.operCG2.GetValueByColName(&listResult, mItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 获取要解封的玩家ID

					SetDlgItemText(IDC_EDITBANACCOUNT,UserName);//设置要解封的玩家帐号
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

// 切换选项卡进行查询
void CCG2BanPlayer::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{	
	CIni mIni;
	//OperationCG2 operCG2;

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
		GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//
		
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

		GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//
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
		GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_SHOW);//
		GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_SHOW);//
		GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_SHOW);//
		GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_SHOW);//
		GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_SHOW);//
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

		SetDlgItemText(IDC_LBLBANREASON,theApp.operCG2.ReadValue("MCG2","BU_UI_reason"));//封停原因
		SetDlgItemText(IDC_BTNBAN,theApp.operCG2.ReadValue("MCG2","BU_UI_TpgOpen"));//帐号封停

		txtAccount.SetReadOnly(true);//玩家帐号的CEdit对象设置为只读属性
		CTime curTime = CTime::GetCurrentTime();//重置时间
		dtcBanEndDate.SetTime(&curTime);
		dtcBanEndTime.SetTime(&curTime);

		UpdateData(false);

		if((listUser.GetItemCount() > 0) && (nItem >= 0))//如果玩家帐号和昵称不同时为空，nItem>=0，说明已经查询过玩家资料信息，并且已经选中了要封停的帐号，可以进行封停操作
		{
			UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
			UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
			UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称
			iCharNo = atoi(theApp.operCG2.GetValueByColName(&listResult, nItem, theApp.operCG2.ReadValue("MCG2","CG2_CharacterNum")));//获取角色号

			SetDlgItemText(IDC_EDITBANACCOUNT,UserName);
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

		GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

		SetDlgItemText(IDC_LBLBANREASON,theApp.operCG2.ReadValue("MCG2","BU_UI_UnBind"));
		SetDlgItemText(IDC_BTNBAN,theApp.operCG2.ReadValue("MCG2","BU_UI_BtnSave"));

		txtAccount.SetReadOnly(true);//玩家帐号的CEdit对象设置为只读属性
		UpdateData(false);

		if((listResult.GetItemCount()) > 0 && (mItem >= 0))//如果玩家帐号和昵称同时为空，nItem>=0，说明已经查询过封停帐号列表，并且已经选中了要解封的帐号，可以进行解封操作
		{
			UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
			UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
			UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称
			iCharNo = atoi(theApp.operCG2.GetValueByColName(&listResult, nItem, theApp.operCG2.ReadValue("MCG2","CG2_CharacterNum")));//获取角色号

			SetDlgItemText(IDC_EDITBANACCOUNT,UserName);
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

		GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//

		GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

		UpdateData(false);

		SetDlgItemText(IDC_BTNBAN,theApp.operCG2.ReadValue("MCG2","Search"));
		UserID = "";
		txtAccount.SetReadOnly(false);//玩家帐号的CEdit对象取消只读属性

		SetDlgItemText(IDC_EDITBANACCOUNT,"");
		SetDlgItemText(IDC_EDITBANREASON,"");
	}
	*pResult = 0;
}

// 封停或解封帐号
void CCG2BanPlayer::OnBnClickedBtnban()
{
	try
	{
		CIni mIni;
		//OperationCG2 theApp.operCG2;	

		int iBanType=0;

		CString strBanType;
		CString BanAccount = "";
		txtAccount.GetWindowText(BanAccount);//获取玩家帐号
		if(BanAccount == "")//玩家帐号不能为空
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","BU_UI_AccountNull"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
			return;
		}				

		CString BanReason = "";
		txtReason.GetWindowText(BanReason);//获取封停或解封原因
		if((tbcResult.GetCurSel() == 1) || (tbcResult.GetCurSel() == 3))// 选择的是封停或解封帐号
		{			
			if(strlen(BanReason) >= 256)//封停或解封原因不能为空
			{
				MessageBox(theApp.operCG2.ReadValue("MCG2","BU_UI_ReasonTooLong"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
				return;
			}
			else if(strlen(BanReason)<=0)
			{
				MessageBox(theApp.operCG2.ReadValue("MCG2","BU_UI_ReasonNotNull"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
				return;
			}
			UserID=listResult.GetItemText(nItem,1);
			strBanType=listResult.GetItemText(nItem,5);
			if(!strcmp(strBanType,theApp.operCG2.ReadValue("MCG2","BU_UI_STRBANTYPEROLE")))
			{
				iBanType=0;
			}
			//else///////maple add
			else if(!strcmp(strBanType,theApp.operCG2.ReadValue("MCG2","BU_UI_STRBANTYPEACCOUNT")))
			{
				iBanType=1;
			}

		}
		else if(tbcResult.GetCurSel() == 4)// 选择的是查询帐号有没有被封停
		{
			CString m_ServerName;
			GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//获取服务器名称
			if(m_ServerName == "")//服务器名称不能为空
			{
				MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_SelectServer"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//获取服务器IP
			GetDlgItemText(IDC_EDITBANACCOUNT,UserName);
			
			


		}
		CString strBanEndTime;
	

		if(tbcResult.GetCurSel()==1)
		{
			CTime curTime = CTime::GetCurrentTime();

			CTime StartDate;
			dtcBanEndDate.GetTime(StartDate);
			CTime StartTime;
			dtcBanEndTime.GetTime(StartTime);//获取时间

			CTime BanEndTime = CTime::CTime(StartDate.GetYear(),StartDate.GetMonth(),StartDate.GetDay(),StartTime.GetHour(),StartTime.GetMinute(),StartTime.GetSecond());

			strBanEndTime = BanEndTime.Format("%Y-%m-%d %H:%M:%S");//设置开始时间


		
			if(BanEndTime <= curTime)//结束时间不能小于当前时间
			{
				MessageBox(theApp.operCG2.ReadValue("MCG2","BU_Warn_BanTime"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
				return;
			}
			iBanType=cmbBanType.GetCurSel();

		}
		

		int userbyID = theApp.UserByID;//操作员ID

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、封停或解封原因、操作员ID、玩家ID
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//玩家ID


		if(tbcResult.GetCurSel()==1)
		{
			socketdata.AddTFLV(CEnumCore::TagName::CG2_BanTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBanEndTime),(unsigned char *)mIni.wcharToChar(strBanEndTime));

		}
		
		_itoa(iBanType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_TypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//封停类型

		_itoa(iCharNo,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//角色号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Content,CEnumCore::TagFormat::TLV_STRING,strlen(BanReason),(unsigned char *)mIni.wcharToChar(BanReason));//封停或解封原因

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID


		int midlength = socketdata.EnBody();
		
		if(tbcResult.GetCurSel() == 1)
		{
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Close);//发送封停玩家帐号的请求
		}
		else if(tbcResult.GetCurSel() == 3)
		{
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Open);//发送解封玩家帐号的请求
		}
		else if(tbcResult.GetCurSel() == 4)
		{
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_BANISHMENT_QUERY);//发送查询玩家帐号有没有被封停的请求
		}
		
		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

// 重置信息
void CCG2BanPlayer::OnBnClickedBtnreset()
{
	SetDlgItemText(IDC_EDITBANREASON,"");
	if(tbcResult.GetCurSel() == 4)
	{
		SetDlgItemText(IDC_EDITBANACCOUNT,"");
	}		
}

// 接收返回信息
LRESULT CCG2BanPlayer::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	//OperationCG2 theApp.operCG2;
	CIni mIni;

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Receive");//当前的状态为接收到了返回信息

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

			theApp.operCG2.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Query_Resp://查询玩家资料信息的回应
		{
			if(pageInfo)
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					nItem = -1;//不能选中某一行
					pageInfo = false;//不能翻页				
					cmbPage.ResetContent();//清空页数复选框
					while(listResult.DeleteColumn(0)){}//清空CListCtrl内容
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
	case CEnumCore::Message_Tag_ID::CG2_BanAccount_Query_Resp://查询所有被封停帐号列表的回应
		{
			if(pageInfo)
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					nItem = -1;
					pageInfo = false;					
					cmbPage.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					nItem = 0;
					cmbPage.ResetContent();//清空复选框
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
	case CEnumCore::Message_Tag_ID::CG2_Account_Close_RESP://封停玩家帐号的回应
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//显示操作结果

			tbcResult.SetCurSel(0);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
			UserInfo();//查询玩家帐号信息
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Open_RESP://解封玩家帐号的回应
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//显示操作结果

			tbcResult.SetCurSel(2);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
			AllBanUserList();//查询所有被封停帐号列表
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_BANISHMENT_QUERY_RESP://查询帐号有没有被封停的回应
		{

			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			if(!strcmp(result,UserName))
			{
				theApp.operCG2.ShowResult(theApp.operCG2.ReadValue("MCG2","BU_Warn_Result"));
			}
			else
			{
					theApp.operCG2.ShowResult(result);//显示返回结果
			}
			
		}
		break;
	default:
		break;
	}
	//socketdata.Destroy();
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	return false;
}

// 关闭对话框
void CCG2BanPlayer::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// 关闭对话框
void CCG2BanPlayer::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
void CCG2BanPlayer::InitBanType(void)
{
	//OperationCG2 operCG2;
	cmbBanType.ResetContent();
	cmbBanType.AddString(theApp.operCG2.ReadValue("MCG2","BU_UI_CMBBANTYPEROLE"));
	cmbBanType.AddString(theApp.operCG2.ReadValue("MCG2","BU_UI_CMBBANTYPEACCOUNT"));
	cmbBanType.SetCurSel(0);
}

void CCG2BanPlayer::OnCbnSelchangeCmbbantype()
{
	// TODO: 在此添加控件通知处理程序代码
}


