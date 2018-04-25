// PALSendCustomerItem.cpp : 实现文件
//

#include "stdafx.h"
#include "M_PAL.h"
#include "PALSendCustomerItem.h"
#include ".\palsendcustomeritem.h"


// CPALSendCustomerItem 对话框

IMPLEMENT_DYNAMIC(CPALSendCustomerItem, CDialog)
CPALSendCustomerItem::CPALSendCustomerItem(CWnd* pParent /*=NULL*/)
	: CDialog(CPALSendCustomerItem::IDD, pParent)
{
}

CPALSendCustomerItem::~CPALSendCustomerItem()
{
}

void CPALSendCustomerItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	//DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	//DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_CMBITEMNAME, cmbItemName);
	DDX_Control(pDX, IDC_CHECKBIND, checkBind);
	DDX_Control(pDX, IDC_CHECKNOTBIND, checkNotBind);
	DDX_Control(pDX, IDC_CHECKSTONE, checkStone);
}


BEGIN_MESSAGE_MAP(CPALSendCustomerItem, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDC_CHECKBIND, OnBnClickedCheckbind)
	ON_BN_CLICKED(IDC_CHECKNOTBIND, OnBnClickedChecknotbind)
	ON_BN_CLICKED(IDC_CHECKSTONE, OnBnClickedCheckstone)
	ON_BN_CLICKED(IDC_BTNSEND, OnBnClickedBtnsend)
	ON_BN_CLICKED(IDC_BTQUEIRYITEM, OnBnClickedBtqueiryitem)
END_MESSAGE_MAP()


// CPALSendCustomerItem 消息处理程序

// 初始化对话框
BOOL CPALSendCustomerItem::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUI();
	nItem = 0;
	pageInfo = false;
	ServerIP = "";
	UserAccount = "";
	UserName = "";//初始化一些私有变量

	ShowUserInfo();//显示用户资料信息

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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置
	}

	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Create");//当前的状态为初始建立对话框

	if(theApp.operPAL.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//处理快捷键响应函数
BOOL CPALSendCustomerItem::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialog::PreTranslateMessage(pMsg);
}

// 初始化显示字符
void CPALSendCustomerItem::InitUI()
{
	SetWindowText(theApp.operPAL.ReadValue("MPAL","SCI_UI_SendCustomerItem"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operPAL.ReadValue("MPAL","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operPAL.ReadValue("MPAL","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblRole"));
	SetDlgItemText(IDSEARCH,theApp.operPAL.ReadValue("MPAL","Search"));
	SetDlgItemText(IDCANCEL,theApp.operPAL.ReadValue("MPAL","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operPAL.ReadValue("MPAL","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operPAL.ReadValue("MPAL","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operPAL.ReadValue("MPAL","SCI_UI_tpgSendCustomerItem"));
}
// 自动改变大小
void CPALSendCustomerItem::OnSize(UINT nType, int cx, int cy)
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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置
	}

	
}

//设置背景颜色
HBRUSH CPALSendCustomerItem::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询玩家资料信息
void CPALSendCustomerItem::OnBnClickedSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;
		//OperationPAL operPAL;

		ShowUserInfo();

		int index = theApp.operPAL.ReadIntValue("MPAL","index");//查询第一页的信息
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//每页显示50条记录

		nItem = 0;//玩家资料列表没有选定项
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Warn_SelectServer"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITACCOUNT,UserAccount);//获取玩家帐号
		GetDlgItemText(IDC_EDITNAME,UserName);//获取玩家角色名
		if((UserName == "") && (UserAccount == ""))//玩家帐号和玩家角色名不能同时为空
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Warn_InputAccount"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家角色名
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERINFO))//发送查询玩家资料信息的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}
}

// 单击用户列表保存当前行号
void CPALSendCustomerItem::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
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

			UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// 保存选中的玩家角色名
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// 切换选项卡进行查询
void CPALSendCustomerItem::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(tbcResult.GetCurSel() == 0)
	{
		ShowUserInfo();//显示用户资料信息
	}
	else
	{
		ShowOtherInfo();
		///ItemNameQuery();//装备查询

	}
	*pResult = 0;
}

//查询道具名
void CPALSendCustomerItem::OnBnClickedBtqueiryitem()
{
	// TODO: 在此添加控件通知处理程序代码
	ItemNameQuery();
}

//道具名称查询
void CPALSendCustomerItem::ItemNameQuery()
{
	try
	{		
		CIni mIni;


		cmbItemName.ResetContent();

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有六个参数，服务器IP、服务器Name、玩家昵称、背包类型,页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name

		//物品名称
		CString ItemName="";
		GetDlgItemText(IDC_ETITEM,ItemName);

		if(ItemName == "")//游戏服务器不能为空
		{
			MessageBox("请输入模糊道具名!",theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		socketdata.AddTFLV(CEnumCore::TagName::PAL_CustomIter,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_EQUIPMENT_QUERY))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Error_SearchItemName"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}	
}

// 接收返回信息
LRESULT CPALSendCustomerItem::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;
	//OperationPAL operPAL;	

	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operPAL.ReadValue("MPAL","Main_UI_ParseData"),theApp.operPAL.ReadValue("MPAL","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	int pageCount = 0;
	int ItemNameID =0;

	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://查询服务器列表信息的回应
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到服务器IP
				ServerList.SetAt(i,ServerIP);//将服务器IP保存在CMap类的对象ServerList中
			}

			theApp.operPAL.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_EQUIPMENT_QUERY_RESP://查询客制物品信息的回应
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				ItemNameID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::PAL_CustomIterID).lpdata);//得到道具编号
				ItemNameList.SetAt(i,ItemNameID);//将道具编号保存在CMap类的对象GiftList中
			}

			theApp.operPAL.BuildComboxs(&socketdata,&cmbItemName);//构造道具名称列表信息
			cmbItemName.SetCurSel(0);
			
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERINFO_RESP://查询玩家资料信息的回应
		{
			theApp.operPAL.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_SENDCUSTOMITEMMAIL_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operPAL.ShowResult(result);//显示返回结果
		}
		break;

	default:
		break;
	}	
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

// 关闭对话框
void CPALSendCustomerItem::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	SetDlgItemText(IDC_EDITNAME,"");
	ShowUserInfo();
}

void CPALSendCustomerItem::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Close");//关闭窗体	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!ItemNameList.IsEmpty())
	{
		ItemNameList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CPALSendCustomerItem::ShowUserInfo(void)
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICSUBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSUBJECT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICCONTENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCONTENT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICMONEY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETMONEY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICITEM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETITEM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTQUEIRYITEM)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTATUS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKBIND)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKNOTBIND)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSENDREASON)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_CHECKSTONE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE0)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE0)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE1)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE2)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE3)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE4)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE5)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE6)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE7)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE8)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE9)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTNSEND)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
}

void CPALSendCustomerItem::ShowOtherInfo(void)
{
	tbcResult.SetCurSel(1);
	checkStone.SetCheck(true);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSUBJECT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSUBJECT)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICCONTENT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETCONTENT)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICMONEY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETMONEY)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICITEM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETITEM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTQUEIRYITEM)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICSTATUS)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECKBIND)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECKNOTBIND)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSENDREASON)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_CHECKSTONE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICSTONE0)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE0)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE0,"-1");
	GetDlgItem(IDC_ETSTONE0)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE1)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE1,"-1");
	GetDlgItem(IDC_ETSTONE1)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE2)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE2,"-1");
	GetDlgItem(IDC_ETSTONE2)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE3)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE3,"-1");
	GetDlgItem(IDC_ETSTONE3)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE4)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE4,"-1");
	GetDlgItem(IDC_ETSTONE4)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE5)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE5)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE5,"-1");
	GetDlgItem(IDC_ETSTONE5)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE6)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE6)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE6,"-1");
	GetDlgItem(IDC_ETSTONE6)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE7)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE7)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE7,"-1");
	GetDlgItem(IDC_ETSTONE7)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE8)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE8)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE8,"-1");
	GetDlgItem(IDC_ETSTONE8)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE9)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE9)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE9,"-1");
	GetDlgItem(IDC_ETSTONE9)->EnableWindow(false);

	GetDlgItem(IDC_BTNSEND)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);
}

//设为绑定
void CPALSendCustomerItem::OnBnClickedCheckbind()
{
	// TODO: 在此添加控件通知处理程序代码
	if(checkBind.GetCheck() == 1)
		checkNotBind.SetCheck(false);
	else
		checkNotBind.SetCheck(true);
}
//维持原样版定
void CPALSendCustomerItem::OnBnClickedChecknotbind()
{
	// TODO: 在此添加控件通知处理程序代码
	if(checkNotBind.GetCheck() ==1)
		checkBind.SetCheck(false);
	else
		checkBind.SetCheck(true);
}

void CPALSendCustomerItem::OnBnClickedCheckstone()
{
	// TODO: 在此添加控件通知处理程序代码
	if(checkStone.GetCheck() == 1)
	{

		SetDlgItemText(IDC_ETSTONE0,"-1");
		SetDlgItemText(IDC_ETSTONE1,"-1");
		SetDlgItemText(IDC_ETSTONE2,"-1");
		SetDlgItemText(IDC_ETSTONE3,"-1");
		SetDlgItemText(IDC_ETSTONE4,"-1");
		SetDlgItemText(IDC_ETSTONE5,"-1");
		SetDlgItemText(IDC_ETSTONE6,"-1");
		SetDlgItemText(IDC_ETSTONE7,"-1");
		SetDlgItemText(IDC_ETSTONE8,"-1");
		SetDlgItemText(IDC_ETSTONE9,"-1");

		GetDlgItem(IDC_ETSTONE0)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE1)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE2)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE3)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE4)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE5)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE6)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE7)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE8)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE9)->EnableWindow(false);



	}
	else
	{
		GetDlgItem(IDC_ETSTONE0)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE1)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE2)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE3)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE4)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE5)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE6)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE7)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE8)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE9)->EnableWindow(true);

		SetDlgItemText(IDC_ETSTONE0,"");
		SetDlgItemText(IDC_ETSTONE1,"");
		SetDlgItemText(IDC_ETSTONE2,"");
		SetDlgItemText(IDC_ETSTONE3,"");
		SetDlgItemText(IDC_ETSTONE4,"");
		SetDlgItemText(IDC_ETSTONE5,"");
		SetDlgItemText(IDC_ETSTONE6,"");
		SetDlgItemText(IDC_ETSTONE7,"");
		SetDlgItemText(IDC_ETSTONE8,"");
		SetDlgItemText(IDC_ETSTONE9,"");
	}

}


//发送客制物品
void CPALSendCustomerItem::OnBnClickedBtnsend()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{		
		CIni mIni;

		///////////////////取邮件内容///////////////////////

		CString m_strSubject;
		GetDlgItemText(IDC_ETSUBJECT,m_strSubject);
		if(m_strSubject == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_MailSubject"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		CString m_strContent;
		GetDlgItemText(IDC_ETCONTENT,m_strContent);
		if(m_strContent == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_MailContent"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		CString m_strReason;
		GetDlgItemText(IDC_ETSENDREASON,m_strReason);
		if(m_strReason == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_MailReason"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		int iMoney=0;//邮件金钱
		iMoney=GetDlgItemInt(IDC_ETMONEY);
		//int iGift[5]={-1,-1,-1,-1,-1};


		//物品id
		int ItemID=0;
		ItemNameList.Lookup(cmbItemName.GetCurSel()+1,ItemID);//从CMap类的对象ItemNameList中获取

		//物品名称
		CString ItemName="";
		GetDlgItemText(IDC_CMBITEMNAME,ItemName);

		//是否绑定
		int bindornot=1;
		if(checkBind.GetCheck() == 1)
			bindornot=1;
		else
			bindornot=0;

		//是否使用玄石
		char szStone[512];
		ZeroMemory(szStone,512);
		if(checkStone.GetCheck() == 1)
			//strStone="-1,-1,-1,-1,-1,-1,-1,-1,-1,-1";
			sprintf(szStone,"%s","-1,-1,-1,-1,-1,-1,-1,-1,-1,-1");
		else
		{
			int iStone = 0,j;
			iStone=GetDlgItemInt(IDC_ETSTONE0);
			j = sprintf(szStone,"%d",iStone);
			j += sprintf(szStone + j,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE1);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE2);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE3);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE4);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE5);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE6);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE7);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE8);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE9);
			j += sprintf(szStone + j,"%d",iStone);
			//j += sprintf(szStone + j ,"%s",",");

		}




		int iUserByID=theApp.UserByID;

		CSocketData socketdata;	
		socketdata.InitCreate(1,15);//共有六个参数，服务器IP、服务器Name、玩家昵称、背包类型,页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
		//socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILSUBJECT,CEnumCore::TagFormat::TLV_STRING,strlen(m_strSubject),(unsigned char *)mIni.wcharToChar(m_strSubject));//主题
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILCONTENT,CEnumCore::TagFormat::TLV_STRING,strlen(m_strContent),(unsigned char *)mIni.wcharToChar(m_strContent));//内容

		_itoa(iMoney,strInt,10);//邮件金钱
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILMONEY,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//


		//物品id
		_itoa(ItemID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_CustomIterID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		//物品名称
		socketdata.AddTFLV(CEnumCore::TagName::PAL_CustomIter,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));

		//是否绑定
		_itoa(bindornot,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_BindSetup,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		//是否使用玄石//PAL_INHERITID0_NAME
		socketdata.AddTFLV(CEnumCore::TagName::PAL_INHERITID0_NAME,CEnumCore::TagFormat::TLV_STRING,strlen(szStone),(unsigned char *)szStone);//(unsigned char *)mIni.wcharToChar(strStone));//玄石参数
		
		//原因
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILREASON,CEnumCore::TagFormat::TLV_STRING,strlen(m_strReason),(unsigned char *)mIni.wcharToChar(m_strReason));//原因
		

		_itoa(iUserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员id


		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_SENDCUSTOMITEMMAIL))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Error_ADDITEM"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}	
}


