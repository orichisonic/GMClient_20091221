// GTOWNPictureManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_GTOWN.h"
#include "GTOWNPictureManage.h"
#include ".\GTOWNPictureManage.h"


// CGTOWNPictureManage 对话框

IMPLEMENT_DYNAMIC(CGTOWNPictureManage, CDialog)
CGTOWNPictureManage::CGTOWNPictureManage(CWnd* pParent /*=NULL*/)
	: CDialog(CGTOWNPictureManage::IDD, pParent)
{
}

CGTOWNPictureManage::~CGTOWNPictureManage()
{
}

void CGTOWNPictureManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_EDITBANACCOUNT, txtAccount);
	DDX_Control(pDX, IDC_EDITBANREASON, txtReason);
	DDX_Control(pDX, IDC_CMBUPAGE, cmbUPage);
}


BEGIN_MESSAGE_MAP(CGTOWNPictureManage, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_BN_CLICKED(IDC_BTNBAN, OnBnClickedBtnban)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_CBN_SELCHANGE(IDC_CMBUPAGE, OnCbnSelchangeCmbupage)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
END_MESSAGE_MAP()


// CGTOWNPictureManage 消息处理程序

BOOL CGTOWNPictureManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// 初始化显示字符		
	showUserInfo();

	nItem = 0;// 单击用户列表得到行号
	mItem = 0;// 单击帐号封停列表得到行号
	pageUInfo = false;
	pageInfo = false;// 判断是否需要翻页
	ServerIP = "";// 游戏服务器IP	
	ServerName = "";//游戏服务器名称
	UserAccount = "";// 玩家帐号	
	UserName = "";//玩家帐号和昵称
	UserState=0;

	SetProp(listUser.GetSafeHwnd(),"排序列号",(HANDLE)0);
	SetProp(listUser.GetSafeHwnd(),"排序顺序",(HANDLE)1);

	SetProp(listResult.GetSafeHwnd(),"排序列号",(HANDLE)0);
    SetProp(listResult.GetSafeHwnd(),"排序顺序",(HANDLE)1);

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

		newRect.top = rs.top + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listResult的位置
	}


	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Create");//当前的状态为初始建立对话框

	if(theApp.operGTOWN.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//当前的状态为发送查询请求
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CGTOWNPictureManage::InitUI()
{
	SetWindowText(theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_BanPlayer"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operGTOWN.ReadValue("MGTOWN","Search"));
	SetDlgItemText(IDCANCEL,theApp.operGTOWN.ReadValue("MGTOWN","Close"));

	SetDlgItemText(IDC_LBLHINT,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_LblHint"));	
	SetDlgItemText(IDC_LBLPAGE,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLBANACCOUNT,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLBANREASON,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_reason"));
	SetDlgItemText(IDC_BTNBAN,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_TpgOpen"));
	SetDlgItemText(IDC_BTNRESET,theApp.operGTOWN.ReadValue("MGTOWN","Reset"));

	tbcResult.InsertItem(0,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_tpgPictureStop"));//禁止图片
	tbcResult.InsertItem(2,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_TpgStopList"));//禁止图片列表
	tbcResult.InsertItem(3,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_tpgPictureStart"));//解禁图片
}

//处理快捷键响应
BOOL CGTOWNPictureManage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operGTOWN.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operGTOWN.CopyListInfo(&listResult);
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

//自动调节大小
void CGTOWNPictureManage::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
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
	    newRect.top = rs.top + grpHeight + tbcHeight;
	    newRect.bottom = newRect.top + grpPHeight;
	    newRect.left = rs.left +10;
	    newRect.right = rs.right - 10;
  
	    GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listResult的位置
	}
}

//设置背景颜色
HBRUSH CGTOWNPictureManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//查询玩家资料信息
void CGTOWNPictureManage::OnBnClickedOk()
{
	try
	{
		CIni mIni;

		nItem = 0;//玩家资料列表没有选定项
		mItem = 0;// 单击帐号封停列表得到行号
		pageUInfo = false;//列表不能翻页	
		pageInfo = false;//列表不能翻页		
		cmbUPage.ResetContent();//清除列表翻页的复选框
		cmbPage.ResetContent();//清除列表翻页的复选框
		while(listResult.DeleteColumn(0)){}//清除列表中的所有内容
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Warn_SelectServer"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITACCOUNT,Account);//获取玩家帐号
		GetDlgItemText(IDC_EDITNAME,Name);//获取玩家角色名
		if((Name == "") && (Account == ""))//玩家帐号和玩家角色名同时为空
		{
			showBanList();
			AllStopUserList();//查询所有被封停帐号列表信息
		}
		else
		{
			showUserInfo();
			UserInfo();//查询玩家资料信息
		}
	}
	catch(...)
	{
	}
}

// 查询玩家资料信息
void CGTOWNPictureManage::UserInfo()
{
	try
	{		
		CIni mIni;	

		nItem = 0;
		pageUInfo = false;
		cmbUPage.ResetContent();
		while(listUser.DeleteColumn(0)){}

		int index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");//查询第一页的信息
		int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//每页显示50条记录

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(Name));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(Account),(unsigned char *)mIni.wcharToChar(Account));//玩家帐号

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_UserInfo_Query))//发送查询玩家资料信息的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//当前的状态为发送查询请求
		}

		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_UserInfo"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}	
}

//翻页查询玩家资料信息
void CGTOWNPictureManage::OnCbnSelchangeCmbupage()
{
	try
	{	
		if(pageUInfo)//如果可以翻页的话
		{
			CIni mIni;

			int index = cmbUPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//每页显示50条记录

			while(listUser.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,6);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(Name));//玩家角色名
			socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(Account),(unsigned char *)mIni.wcharToChar(Account));//玩家帐号

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_UserInfo_Query))//发送查询玩家资料信息的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
				dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();//销毁CSocketData局部变量
		}
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_Page"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}
}

// 查询所有被封停帐号列表信息
void CGTOWNPictureManage::AllStopUserList()
{
	try
	{				
		CIni mIni;
		
		mItem = -1;
		pageInfo = false;		
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}

		char strInt[10];
		int index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");
		int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家角色名、页数、每页的记录条数

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(Name));
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(Account),(unsigned char *)mIni.wcharToChar(Account));//玩家帐号

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_AllStopUser_Query))
		{		
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//发送查询请求
		}

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_UserInfo"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}
}

// 翻页进行查询//所有被封停的帐号
void CGTOWNPictureManage::OnCbnSelchangeCmbpage()
{
	try
	{		
		if(pageInfo)
		{	
			CIni mIni;

			while(listResult.DeleteColumn(0)){}

			int index = cmbPage.GetCurSel() + 1;//页数为cmbPage当前的索引值加1，也就是cmbPage中当前显示的值
			int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//每页显示50条记录

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
			if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_AllBanUser_Query))
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//发送查询请求
			}
			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_Page"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}
}

// 单击用户列表保存当前行号
void CGTOWNPictureManage::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
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
			nItem = 0;
		}
	}
	*pResult = 0;
}

// 双击用户列表切换界面
void CGTOWNPictureManage::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
				

			/*	showBanPlayer();*/

				UpdateData(false);

				UserAccount = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Account"));//获取要封停的玩家帐号
			    UserName = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserNick"));//获取要封停的玩家角色名
				userID= atoi(theApp.operGTOWN.GetValueByColName(&listUser, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserID")));//玩家ID

				ClearPicture();
				//SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);//设置要封停的玩家帐号
				//SetDlgItemText(IDC_EDITBANREASON,"");				
			}
		}
		else
		{
			nItem = 0;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}



// 单击封停帐号列表保存当前行号

void CGTOWNPictureManage::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 2)
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

// 双击封停帐号列表切换界面

void CGTOWNPictureManage::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
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
				CIni mIni;				
				showUnbindPlayer();

				UpdateData(false);

				UserAccount = theApp.operGTOWN.GetValueByColName(&listResult, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Account"));//获取要解封的玩家帐号
				UserName = theApp.operGTOWN.GetValueByColName(&listResult, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserNick"));//玩家昵称
				userID= atoi(theApp.operGTOWN.GetValueByColName(&listResult, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserID")));//玩家ID

				SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);//设置要封停的玩家帐号
				SetDlgItemText(IDC_EDITBANREASON,"");				
			}
		}
		else
		{
			nItem = 0;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

//切换tabCtrl选项卡
void CGTOWNPictureManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	CIni mIni;

	if(tbcResult.GetCurSel()==0)//如果选中的是玩家资料信息的页面
	{
		showUserInfo();
	}
	else if(tbcResult.GetCurSel()==2)//如果选中的是封停帐号列表的页面
	{
		showBanList();
	}
	else if(tbcResult.GetCurSel()==1)//如果选中的是封停帐号的页面
	{
		showBanPlayer();

		UpdateData(false);

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			UserAccount = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Account"));
			UserName = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserNick"));
			userID= atoi(theApp.operGTOWN.GetValueByColName(&listUser, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserID")));//玩家ID


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
		showUnbindPlayer();

		UpdateData(false);

		if((listResult.GetItemCount() > 0) && (mItem >= 0))
		{
			UserAccount = theApp.operGTOWN.GetValueByColName(&listResult, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Account"));
			UserName = theApp.operGTOWN.GetValueByColName(&listResult, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserNick"));
			userID= atoi(theApp.operGTOWN.GetValueByColName(&listResult, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserID")));//玩家ID


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
		showSearchPlayer();
		SetDlgItemText(IDC_EDITBANACCOUNT,"");
		SetDlgItemText(IDC_EDITBANREASON,"");
	}
	*pResult = 0;
}


//封停或解封帐号
void CGTOWNPictureManage::OnBnClickedBtnban()
{
	try
	{
		CIni mIni;		

		CString BanAccount = "";
		txtAccount.GetWindowText(BanAccount);//获取玩家帐号
		if(BanAccount == "")//玩家帐号不能为空
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_AccountNull"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
			return;
		}				

		CString BanReason = "";
		txtReason.GetWindowText(BanReason);//获取封停或解封原因
		if((tbcResult.GetCurSel() == 1) || (tbcResult.GetCurSel() == 3))// 选择的是封停或解封帐号
		{	

			if(strlen(BanReason) >= 256)//封停或解封原因不能为空
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_ReasonTooLong"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
				return;
			}
		}
		else if(tbcResult.GetCurSel() == 4)// 选择的是查询帐号有没有被封停
		{
			CString m_ServerName;
			GetDlgItemText(IDC_CMBSERVER,m_ServerName);//获取服务器名称
			if(m_ServerName == "")//服务器名称不能为空
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Warn_SelectServer"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//获取服务器IP
		}
		int userbyID = theApp.UserByID;//操作员ID

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有四个参数，服务器IP、玩家帐号、封停或解封原因、操作员ID
		char strInt[10];
		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char*)mIni.wcharToChar(ServerName));//服务器name
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(BanAccount),(unsigned char *)mIni.wcharToChar(BanAccount));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::GT_BanReason,CEnumCore::TagFormat::TLV_STRING,strlen(BanReason),(unsigned char *)mIni.wcharToChar(BanReason));//封停或解封原因

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		_itoa(userID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID

		if(tbcResult.GetCurSel() == 1)
		{

			UserState=0;
			_itoa(UserState,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::GT_UserState,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家状态
			int midlength = socketdata.EnBody();

			if(theApp.operGTOWN.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_Picture_Stop))//发送封停玩家帐号的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
		        dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//当前的状态为发送查询请求
			}
		}
		else if(tbcResult.GetCurSel() == 3)
		{
			UserState=1;
			_itoa(UserState,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::GT_UserState,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家状态
			int midlength = socketdata.EnBody();

			if(theApp.operGTOWN.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_Picture_Stop))//发送解封玩家帐号的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
		        dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//当前的状态为发送查询请求
			}
		}
		else if(tbcResult.GetCurSel() == 4)
		{
			int midlength = socketdata.EnBody();
			if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_AllBanUser_Query))//发送查询玩家帐号有没有被封停的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
		        dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//当前的状态为发送查询请求
			}
		}		
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//重置信息
void CGTOWNPictureManage::OnBnClickedBtnreset()
{
	SetDlgItemText(IDC_EDITBANREASON,"");
	if(tbcResult.GetCurSel() == 4)
	{
		SetDlgItemText(IDC_EDITBANACCOUNT,"");
	}
}


//接受返回信息
LRESULT CGTOWNPictureManage::OnMessageReceive(WPARAM wParam,LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;
	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","Main_UI_ParseData"),theApp.operGTOWN.ReadValue("MGTOWN","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	int pageCount = 0;

	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://查询服务器列表信息的回应
		{
			if(!ServerList.IsEmpty())
			{
				ServerList.RemoveAll();
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到服务器IP
				ServerList.SetAt(i,ServerIP);//将服务器IP保存在CMap类的对象ServerList中
			}

			theApp.operGTOWN.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_UserInfo_Query_Resp://玩家资料查询的反应
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					pageUInfo = false;//不能翻页		
					cmbUPage.ResetContent();
					while(listUser.DeleteColumn(0)){}
				}
				else
				{
					cmbUPage.ResetContent();
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbUPage.AddString(str);
					}
					cmbUPage.SetCurSel(0);
					if(pageCount == 1)
					{
						pageUInfo = false;
					}
					else
					{
						pageUInfo = true;
					}
				}				
			}
		}
		break;
		//封停玩家帐号的回应
	case CEnumCore::Message_Tag_ID::GT_Picture_Stop_Resp:
	case CEnumCore::Message_Tag_ID::GT_Picture_Clear_Resp:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operGTOWN.ShowResult(result);//显示操作结果

			//showUserInfo();
			//UserInfo();//查询玩家帐号信息
		}
		break;
		//查询所有被封停帐号的回应
	case CEnumCore::Message_Tag_ID::GT_AllStopUser_Query_Resp:
		{
			if(pageInfo)
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					mItem = -1;
					pageInfo = false;					
					cmbPage.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					mItem = 0;
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
	default:
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return FALSE;
}

//显示玩家资料信息
void CGTOWNPictureManage::showUserInfo()
{
	tbcResult.SetCurSel(0);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBUPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
}

//显示封停帐号
void CGTOWNPictureManage::showBanPlayer()
{
	tbcResult.SetCurSel(1);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBUPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

	SetDlgItemText(IDC_LBLBANREASON,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_reason"));//封停原因
	SetDlgItemText(IDC_BTNBAN,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_BtnPost"));//"PM_UI_TpgOpen"));//帐号封停
	txtAccount.SetReadOnly(true);//玩家帐号的CEdit对象设置为只读属性
}

//显示封停帐号列表
void CGTOWNPictureManage::showBanList()
{
	tbcResult.SetCurSel(2);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBUPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
}

//显示解封帐号
void CGTOWNPictureManage::showUnbindPlayer()
{
	tbcResult.SetCurSel(3);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBUPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

	SetDlgItemText(IDC_LBLBANREASON,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_UnBind"));//解封原因
	SetDlgItemText(IDC_BTNBAN,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_BtnSave"));//解封帐号

	txtAccount.SetReadOnly(true);//玩家帐号的CEdit对象设置为只读属性
}

//查询帐号有没有封停
void CGTOWNPictureManage::showSearchPlayer()
{
	tbcResult.SetCurSel(4);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBUPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

	SetDlgItemText(IDC_BTNBAN,theApp.operGTOWN.ReadValue("MGTOWN","Search"));

	txtAccount.SetReadOnly(false);//玩家帐号的CEdit对象取消只读属性
}

//单击用户资料信息的列名进行排序
void CGTOWNPictureManage::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operGTOWN.SortListInfo(&listUser,pNMHDR,pResult);
}

//单击结果信息的列名进行排序
void CGTOWNPictureManage::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operGTOWN.SortListInfo(&listResult,pNMHDR,pResult);
}

//使用关闭按钮
void CGTOWNPictureManage::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	showUserInfo();
}

//关闭对话框
void CGTOWNPictureManage::OnClose()
{
	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Close");//关闭窗体

	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CGTOWNPictureManage::ClearPicture()
{

	try
	{
		CIni mIni;


		if (AfxMessageBox("是否清除头像", MB_YESNO) == IDNO) 
		{
			return;
		}

		int userbyID = theApp.UserByID;

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有四个参数，服务器IP、服务器Name、玩家昵称、操作员ID
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_Picture_Clear))//发送重设玩家到出生状态的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}