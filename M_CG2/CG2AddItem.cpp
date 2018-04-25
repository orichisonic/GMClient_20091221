// CG2AddItem.cpp : 实现文件
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2AddItem.h"
#include ".\cg2additem.h"


// CCG2AddItem 对话框

IMPLEMENT_DYNAMIC(CCG2AddItem, CDialog)
CCG2AddItem::CCG2AddItem(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2AddItem::IDD, pParent)
{
}

CCG2AddItem::~CCG2AddItem()
{
}

void CCG2AddItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBITEMTYPE, cmbItemType);
	DDX_Control(pDX, IDC_CMBITEMNAME, cmbItemName);
	DDX_Control(pDX, IDC_CMBITEMNUMBER, cmbItemNumber);
	DDX_Control(pDX, IDC_LISTITEM, listItem);
}


BEGIN_MESSAGE_MAP(CCG2AddItem, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_CBN_SELCHANGE(IDC_CMBITEMTYPE, OnCbnSelchangeCmbitemtype)
	ON_BN_CLICKED(IDC_BTRIGHT, OnBnClickedBtright)
	ON_BN_CLICKED(IDC_BTLEFT, OnBnClickedBtleft)
	ON_NOTIFY(NM_CLICK, IDC_LISTITEM, OnNMClickListitem)
	ON_BN_CLICKED(IDC_BTADD, OnBnClickedBtadd)
	ON_BN_CLICKED(IDC_BTRESET, OnBnClickedBtreset)
END_MESSAGE_MAP()


// CCG2AddItem 消息处理程序
//初始化显示字符
void CCG2AddItem::InitUI()
{
	//OperationCG2 theApp.operCG2;

	SetWindowText(theApp.operCG2.ReadValue("MCG2","CG2_UI_AddItem"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operCG2.ReadValue("MCG2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));
	SetDlgItemText(IDC_BTUPDATE,theApp.operCG2.ReadValue("MCG2","Update"));
	SetDlgItemText(IDC_BTRESET,theApp.operCG2.ReadValue("MCG2","Reset"));

	SetDlgItemText(IDC_BTSEARCH,theApp.operCG2.ReadValue("MCG2","Search"));

	SetDlgItemText(IDC_STATICCHARNICK,theApp.operCG2.ReadValue("MCG2","UIC_CharNick"));
	SetDlgItemText(IDC_CHECKUNSUREQUERY,theApp.operCG2.ReadValue("MCG2","UIC_UnsureQuery"));
	SetDlgItemText(IDC_STATICITEMTYPE,theApp.operCG2.ReadValue("MCG2","UIC_ItemType"));
	SetDlgItemText(IDC_STATICITEMNAME,theApp.operCG2.ReadValue("MCG2","UIC_ItemName"));
	SetDlgItemText(IDC_STATICITEMNUMBER,theApp.operCG2.ReadValue("MCG2","UIC_ItemNumber"));
	SetDlgItemText(IDC_STATICITEMLIST,theApp.operCG2.ReadValue("MCG2","UIC_PresentItemList"));
	SetDlgItemText(IDC_STATICTITLE,theApp.operCG2.ReadValue("MCG2","UIC_Title"));
	SetDlgItemText(IDC_STATICCONTEXT,theApp.operCG2.ReadValue("MCG2","UIC_Context"));
	SetDlgItemText(IDC_BTADD,theApp.operCG2.ReadValue("MCG2","MakeSure"));
	SetDlgItemText(IDC_BTRESET,theApp.operCG2.ReadValue("MCG2","UIC_Reset"));


	tbcResult.InsertItem(0,theApp.operCG2.ReadValue("MCG2","UIC_UI_tpgUserInfo"));//玩家基本信息//
	tbcResult.InsertItem(1,theApp.operCG2.ReadValue("MCG2","CG2_UI_tpgAddItem"));

	GetDlgItem(IDC_STATICCHARNICK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCHARNICK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKUNSUREQUERY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMNUMBER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBITEMTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBITEMNUMBER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTLEFT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRIGHT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMLIST)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICTITLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETTITLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICCONTEXT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCONTEXT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTADD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

	UpdateData(true);
}
//初始化对话框
BOOL CCG2AddItem::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUI();

	nItem = -1;
	pageInfo = false;
	pageUInfo = false;
	ServerIP = "";
	UserID = "";
	UserName = "";
	UserNick = "";//初始化一些私有变量
	iCharNo=0;

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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置

		
	}

	////OperationCG2 theApp.operCG2;
	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//当前的状态为初始建立对话框

	theApp.operCG2.GetServerList();//请求所有的游戏服务器列表
	::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//自动调节大小
void CCG2AddItem::OnSize(UINT nType, int cx, int cy)
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

		listUser.MoveWindow(newRect);//设置好listUser的位置

			
	}
}


//设置背景颜色
HBRUSH CCG2AddItem::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//关闭对话框
void CCG2AddItem::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CCG2AddItem::OnBnClickedUicancel()
{
	// TODO: 在此添加控件通知处理程序代码
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

//玩家基本信息


void CCG2AddItem::OnBnClickedUisearch()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;
		//OperationCG2 theApp.operCG2;

		tbcResult.SetCurSel(0);//玩家信息

		nItem = -1;//玩家资料列表没有选定项
		pageUInfo = false;//玩家资料列表不能翻页	
		cmbPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容


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
		if((UserName == "") && (UserNick == ""))//玩家帐号和玩家昵称不能同时为空
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_InputAccount"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

	    //UserInfo();// 查询玩家资料信息
		UserInfo();
	}
	catch(...)
	{
	}
}

void CCG2AddItem::UserInfo()
{
	//OperationCG2 theApp.operCG2;
	try
	{		
		CIni mIni;		
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");//查询第一页的信息
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//每页显示50条记录

		nItem = -1;//玩家资料列表没有选定项
		pageUInfo = false;//玩家资料列表不能翻页	
		cmbPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		CSocketData socketdata;		
		socketdata.InitCreate(1,5);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
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


//切换tabctrl
void CCG2AddItem::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//OperationCG2 theApp.operCG2;
	if(tbcResult.GetCurSel()==0)//选中的是玩家资料信息选项卡
	{
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATICCHARNICK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETCHARNICK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECKUNSUREQUERY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICITEMTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICITEMNUMBER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBITEMTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBITEMNUMBER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTLEFT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICITEMLIST)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICTITLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETTITLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICCONTEXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETCONTEXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTADD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

		UpdateData(true);
	}
	else if(tbcResult.GetCurSel()==1)//选中的是添加道具
	{
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICCHARNICK)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ETCHARNICK)->ShowWindow(SW_SHOW);
		////GetDlgItem(IDC_CHECKUNSUREQUERY)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICITEMTYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICITEMNUMBER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBITEMTYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBITEMNUMBER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTLEFT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTRIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICITEMLIST)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_SHOW);
		////GetDlgItem(IDC_STATICTITLE)->ShowWindow(SW_SHOW);
		////GetDlgItem(IDC_ETTITLE)->ShowWindow(SW_SHOW);
		////GetDlgItem(IDC_STATICCONTEXT)->ShowWindow(SW_SHOW);
		////GetDlgItem(IDC_ETCONTEXT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTADD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTRESET)->ShowWindow(SW_SHOW);

		while(listItem.DeleteColumn(0)){}// 清除结果列表中的所有内容

		UpdateData(true);
	}
	*pResult = 0;
}

// 单击用户列表保存当前行号
void CCG2AddItem::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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

			nItem = listUser.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

// 双击玩家资料信息进行查询
void CCG2AddItem::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//OperationCG2 theApp.operCG2;

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

			nItem = listUser.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

			if(nItem >= 0)
			{
				tbcResult.SetCurSel(1);

				CIni mIni;
				pageInfo = false;
				cmbPage.ResetContent();
				while(listItem.DeleteColumn(0)){}// 清除结果列表中的所有内容

				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_STATICCHARNICK)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_ETCHARNICK)->ShowWindow(SW_SHOW);
				////GetDlgItem(IDC_CHECKUNSUREQUERY)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICITEMTYPE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICITEMNUMBER)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBITEMTYPE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBITEMNUMBER)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTLEFT)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTRIGHT)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICITEMLIST)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_SHOW);
				////GetDlgItem(IDC_STATICTITLE)->ShowWindow(SW_SHOW);
				////GetDlgItem(IDC_ETTITLE)->ShowWindow(SW_SHOW);
				///GetDlgItem(IDC_STATICCONTEXT)->ShowWindow(SW_SHOW);
				///GetDlgItem(IDC_ETCONTEXT)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTADD)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTRESET)->ShowWindow(SW_SHOW);

				UpdateData(true);

				UpdateData(true);

				//OperationCG2 theApp.operCG2;
				UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
				UserID = theApp.operCG2.GetValueByColName(&listUser, nItem,theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
				UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称
				iCharNo =atoi(theApp.operCG2.GetValueByColName(&listUser,nItem,theApp.operCG2.ReadValue("MCG2","CG2_CharacterNum")));//保存选中的玩家角色号

				SetDlgItemText(IDC_ETCHARNICK,UserNick);
				ItemType();
				SetNumber();
			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

//道具类别查询
void CCG2AddItem::ItemType()
{
	//OperationCG2 theApp.operCG2;	
	try
	{		
		CIni mIni;
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,2);//共有2个参数，服务器IP、玩家帐号
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			//socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

			//socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY

			//_itoa(index,strInt,10);
			//socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			//_itoa(iPageSize,strInt,10);
			//socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Get_Item_Query );

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_AddItem"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
}

//切换技能类别组合框进行技能名称查询
void CCG2AddItem::OnCbnSelchangeCmbitemtype()
{
	// TODO: 在此添加控件通知处理程序代码
	int iPos=((CComboBox*)GetDlgItem(IDC_CMBITEMTYPE))->GetCurSel();//当前选中的行
	CString ItemType="";
	((CComboBox*)GetDlgItem(IDC_CMBITEMTYPE))->GetLBText(iPos,ItemType); //其中n为从0开始的索引值
	//((CComboBox*)GetDlgItem(IDC_CMBSKILLTYPE))->GetLBText(iPos,SkillType); //其中n为从0开始的索引值

	//OperationCG2 theApp.operCG2;	
	try
	{		
		CIni mIni;
		
		//int index = theApp.operCG2.ReadIntValue("MCG2","index");
		//int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		//if((listUser.GetItemCount() > 0) && (nItem>=0))
		//{
			CSocketData socketdata;
			socketdata.InitCreate(1,3);//共有3个参数，服务器IP、玩家帐号、道具类别
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_ItemType,CEnumCore::TagFormat::TLV_STRING,strlen(ItemType),(unsigned char *)mIni.wcharToChar(ItemType));//道具类别

			//socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY

			//_itoa(index,strInt,10);
			//socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			//_itoa(iPageSize,strInt,10);
			//socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Get_Item_Detail_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
	//	}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_AddItem"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
	
}
//设置道具数量
void CCG2AddItem::SetNumber()
{
	cmbItemNumber.ResetContent();
	cmbItemNumber.AddString("1");
	cmbItemNumber.AddString("2");
	cmbItemNumber.AddString("3");
	cmbItemNumber.AddString("4");
	cmbItemNumber.AddString("5");
	cmbItemNumber.AddString("6");
	cmbItemNumber.AddString("7");
	cmbItemNumber.AddString("8");
	cmbItemNumber.AddString("9");
	cmbItemNumber.AddString("10");
	cmbItemNumber.AddString("11");
	cmbItemNumber.AddString("12");
	cmbItemNumber.SetCurSel(0);

	//初始化添加道具列表框
	//OperationCG2 theApp.operCG2;
	listItem.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);//0,"用户名",LVCFMT_LEFT,70);
	CString ItemName="";
	ItemName=theApp.operCG2.ReadValue("MCG2","UIC_ItemName");
	CString ItemNumber="";
	ItemNumber=theApp.operCG2.ReadValue("MCG2","UIC_ItemNumber");
	listItem.InsertColumn(0,ItemName,LVCFMT_LEFT,170);//(LPCTSTR)theApp.operCG2.ReadValue("MCG2","UIC_ItemName"),LVCFMT_LEFT,120);
	listItem.InsertColumn(1,ItemNumber,LVCFMT_LEFT,70);
	//SetDlgItemText(IDC_BTRESET,theApp.operCG2.ReadValue("MCG2","Reset"));
}

//添加赠送道具列表
void CCG2AddItem::OnBnClickedBtright()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取道具名称
	int iPos=((CComboBox*)GetDlgItem(IDC_CMBITEMNAME))->GetCurSel();//当前选中的行
	CString ItemName="";
	((CComboBox*)GetDlgItem(IDC_CMBITEMNAME))->GetLBText(iPos,ItemName); //其中n为从0开始的索引值

	//获取道具数量
	iPos=((CComboBox*)GetDlgItem(IDC_CMBITEMNUMBER))->GetCurSel();//当前选中的行
	CString ItemNumber="";
	((CComboBox*)GetDlgItem(IDC_CMBITEMNUMBER))->GetLBText(iPos,ItemNumber); //其中n为从0开始的索引值

	listItem.InsertItem(0,ItemName);
	listItem.SetItemText(0,1,ItemNumber);
}

//单击道具列表保存当前行号
void CCG2AddItem::OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(listItem.GetItemCount() != 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nItem = listItem.SubItemHitTest(&lvinfo);//保存在赠送道具列表中选中的行号
	}
	else
	{
		nItem = -1;
	}
	*pResult = 0;
}

//删除赠送道具列表
void CCG2AddItem::OnBnClickedBtleft()
{
	// TODO: 在此添加控件通知处理程序代码
	listItem.DeleteItem(nItem);
	
}

//添加道具
void CCG2AddItem::OnBnClickedBtadd()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有7个参数，服务器IP、玩家帐号、角色IDKEY、角色号、备注、道具名称、道具数量

		CString ItemName="";
		CString ItemNumber="";
		//OperationCG2 theApp.operCG2;
		//UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
		ItemName=theApp.operCG2.GetValueByColName(&listItem,nItem,theApp.operCG2.ReadValue("MCG2","CG2_ItemName"));//保存选中的道具名称
		ItemNumber=theApp.operCG2.GetValueByColName(&listItem,nItem,theApp.operCG2.ReadValue("MCG2","CG2_ItemNum"));//保存选中的道具数量

		CString remark="add item";
		//GetDlgItemText(IDC_ETTITLE,remark);
		char strInt[10];
		_itoa(iCharNo,strInt,10);

		

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//角色号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Remark,CEnumCore::TagFormat::TLV_STRING,strlen(remark),(unsigned char *)mIni.wcharToChar(remark));//备注remark
		socketdata.AddTFLV(CEnumCore::TagName::CG2_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//道具名称
		socketdata.AddTFLV(CEnumCore::TagName::CG2_ItemNum,CEnumCore::TagFormat::TLV_STRING,strlen(ItemNumber),(unsigned char *)mIni.wcharToChar(ItemNumber));//道具数量

		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_TypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//类型

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Insert_Item_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
	}

}


//点击重置按钮
void CCG2AddItem::OnBnClickedBtreset()
{
	// TODO: 在此添加控件通知处理程序代码
	//listItem.DeleteAllItems();
	//SetDlgItemText(IDC_ETTITLE,"");
	//SetDlgItemText(IDC_ETCONTEXT,"");
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICCHARNICK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCHARNICK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKUNSUREQUERY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMNUMBER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBITEMTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBITEMNUMBER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTLEFT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRIGHT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMLIST)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICTITLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETTITLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICCONTEXT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCONTEXT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTADD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

	UpdateData(true);
	UserInfo();
}

//接受返回信息
LRESULT CCG2AddItem::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
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
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到服务器IP
				ServerList.SetAt(i,ServerIP);//将服务器IP保存在CMap类的对象ServerList中
			}

			theApp.operCG2.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Query_Resp://查询玩家资料信息的回应
		{
			if(pageUInfo)//如果已经能够翻页
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象

				if(pageCount<0)//页数<=0，说明没有数据返回
				{
					nItem = -1;//不能选中某一行
					pageUInfo = false;//不能翻页					
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
	case CEnumCore::Message_Tag_ID::CG2_Get_Item_Query_Resp://查询道具类别
		{
			theApp.operCG2.BuildPetCombox(&socketdata,&cmbItemType);
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Get_Item_Detail_Query_Resp ://道具名称查询
		{
			theApp.operCG2.BuildJobCombox(&socketdata,&cmbItemName);
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Insert_Item_Query_Resp://添加道具
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//显示操作结果

			tbcResult.SetCurSel(0);
			cmbPage.ResetContent();

			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_STATICCHARNICK)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ETCHARNICK)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKUNSUREQUERY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICITEMTYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICITEMNUMBER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBITEMTYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBITEMNUMBER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTLEFT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTRIGHT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICITEMLIST)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICTITLE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ETTITLE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICCONTEXT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ETCONTEXT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTADD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

			UpdateData(true);

			UserInfo();
		}
		break;
	}


	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}












