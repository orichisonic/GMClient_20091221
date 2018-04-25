// GTOWNItemManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_GTOWN.h"
#include "GTOWNItemManage.h"
#include ".\GTOWNItemManage.h"


// CGTOWNItemManage 对话框

IMPLEMENT_DYNAMIC(CGTOWNItemManage, CDialog)
CGTOWNItemManage::CGTOWNItemManage(CWnd* pParent /*=NULL*/)
: CDialog(CGTOWNItemManage::IDD, pParent)
{
}

CGTOWNItemManage::~CGTOWNItemManage()
{
}

void CGTOWNItemManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_LISTITEM, listItem);
	DDX_Control(pDX, IDC_COMBO1, cmbBigType);
	DDX_Control(pDX, IDC_COMBO2, cmbSmallType);
}


BEGIN_MESSAGE_MAP(CGTOWNItemManage, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
	ON_BN_CLICKED(IDC_BTNBLURSEARCH, OnBnClickedBtnblursearch)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_BN_CLICKED(IDC_BTNADD, OnBnClickedBtnadd)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTITEM, OnLvnColumnclickListitem)
	ON_NOTIFY(NM_CLICK, IDC_LISTITEM, OnNMClickListitem)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTITEM, OnNMDblclkListitem)
	ON_BN_CLICKED(IDC_BTNDELETE, OnBnClickedBtndelete)
	ON_BN_CLICKED(IDC_BTNSEND, OnBnClickedBtnsend)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
END_MESSAGE_MAP()


// CGTOWNItemManage 消息处理程序

//初始化对话框
BOOL CGTOWNItemManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// 初始化显示字符	

	nItem = 0;
	addItem = 0;
	delItem = 0;
	pageInfo = false;
	ServerIP = "";
	ServerName = "";
	UserAccount = "";
	UserName = "";
	UserID=0;//初始化一些私有变量

	ShowUserInfo(SW_SHOW);//显示用户资料信息
	ShowItemInfo(SW_HIDE);//不显示添加道具信息

	SetProp(listUser.GetSafeHwnd(),"排序列号",(HANDLE)0);
	SetProp(listUser.GetSafeHwnd(),"排序顺序",(HANDLE)1);

	SetProp(listResult.GetSafeHwnd(),"排序列号",(HANDLE)0);
	SetProp(listResult.GetSafeHwnd(),"排序顺序",(HANDLE)1);

	SetProp(listItem.GetSafeHwnd(),"排序列号",(HANDLE)0);
	SetProp(listItem.GetSafeHwnd(),"排序顺序",(HANDLE)1);

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
		listResult.GetWindowRect(srcRect);//获取listResult的大小信息
		listWidth = srcRect.right - srcRect.left;//得到listResult的宽度信息

		newRect.top = rs.top + grpHeight + tbcHeight + 4;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = newRect.left + listWidth;

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

// 初始化显示字符
void CGTOWNItemManage::InitUI()
{
	SetWindowText(theApp.operGTOWN.ReadValue("MGTOWN","TM_UI_ItemManager"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operGTOWN.ReadValue("MGTOWN","Search"));
	SetDlgItemText(IDCANCEL,theApp.operGTOWN.ReadValue("MGTOWN","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLADDNAME,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_lblNick"));
	SetDlgItemText(IDC_LBLITEM,theApp.operGTOWN.ReadValue("MGTOWN","IM_UI_lblBlurSearch"));
	SetDlgItemText(IDC_BTNBLURSEARCH,theApp.operGTOWN.ReadValue("MGTOWN","Search"));

	SetDlgItemText(IDC_LBLITEMNUM,theApp.operGTOWN.ReadValue("MGTOWN","IM_UI_lblItemNum"));
	SetDlgItemText(IDC_LBLTOADDITEM,theApp.operGTOWN.ReadValue("MGTOWN","IM_UI_lblItemList"));

	SetDlgItemText(IDC_LBLMAILSUBJECT,theApp.operGTOWN.ReadValue("MGTOWN","IM_UI_LBLMAILSUBJECT"));
	SetDlgItemText(IDC_LBLMAILCONTENT,theApp.operGTOWN.ReadValue("MGTOWN","IM_UI_LBLMAILCONTENT"));

	SetDlgItemText(IDC_BTNSEND,theApp.operGTOWN.ReadValue("MGTOWN","IM_UI_BTNSEND"));
	SetDlgItemText(IDC_BTNRESET,theApp.operGTOWN.ReadValue("MGTOWN","Reset"));

	tbcResult.InsertItem(0,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_tpgUserInfo"));//玩家基本信息
	tbcResult.InsertItem(1,theApp.operGTOWN.ReadValue("MGTOWN","TM_UI_tpgAddItem"));//添加道具
//	tbcResult.InsertItem(2,theApp.operGTOWN.ReadValue("MGTOWN","TM_UI_tpgAddItem"));//删除道具
}

//处理快捷键响应函数
BOOL CGTOWNItemManage::PreTranslateMessage(MSG* pMsg)
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
				else if(pMsg->hwnd == listItem.m_hWnd)
				{
					theApp.operGTOWN.CopyListInfo(&listItem);
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
				else if(pMsg->hwnd == listItem.m_hWnd)
				{
					for(int i=0; i<listItem.GetItemCount(); i++)
					{
						listItem.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listItem.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

//自动改变大小
void CGTOWNItemManage::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rs;
	GetClientRect(rs);

	CRect newRect;
	CRect srcRect;

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
		newRect.top = rs.top + grpHeight + tbcHeight + 4;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = newRect.left + listWidth;

		listResult.MoveWindow(newRect);//设置好listResult的位置
	}
}

//设置背景颜色
HBRUSH CGTOWNItemManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}



//查询玩家资料信息
void CGTOWNItemManage::OnBnClickedSearch()
{
	try
	{
		CIni mIni;

		tbcResult.SetCurSel(0);
		ShowUserInfo(SW_SHOW);
		ShowItemInfo(SW_HIDE);

		int index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");//查询第一页的信息
		int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//每页显示50条记录

		nItem = 0;//玩家资料列表没有选定项
		bool pageInfo = false;//刚开始不能翻页
		cmbPage.ResetContent();//清空翻页复选框
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Warn_SelectServer"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITACCOUNT,Account);//获取玩家帐号//IDC_EDITACCOUNT
		GetDlgItemText(IDC_EDITNAME,Name);//获取玩家角色名//IDC_EDITNAME
		if((Name == "") && (Account == ""))//玩家帐号和玩家角色名不能同时为空
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Warn_InputAccount"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

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
	catch(...)
	{
	}
}

//切换翻页组合框
void CGTOWNItemManage::OnCbnSelchangeCmbpage()
{
	try
	{	
		if(pageInfo)//如果可以翻页的话
		{
			CIni mIni;

			int index = cmbPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
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

// 单击用户列表保存当前行号
void CGTOWNItemManage::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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

			nItem = listUser.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// 双击玩家资料信息进行查询
void CGTOWNItemManage::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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

			nItem = listUser.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

			if(nItem >= 0)
			{
				tbcResult.SetCurSel(1);
				ShowUserInfo(SW_HIDE);
				ShowItemInfo(SW_SHOW);				
				while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

				UserAccount = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Account"));//玩家帐号
				UserName = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserNick"));//玩家昵称
				UserID= atoi(theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserID")));//玩家ID

				SetDlgItemText(IDC_EDITADDNAME, UserName);//设置要添加道具的玩家昵称
				OnBnClickedBtnreset();
			}
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// 切换选项卡进行查询
void CGTOWNItemManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)//显示用户资料信息
	{
		tbcResult.SetCurSel(0);
		ShowUserInfo(SW_SHOW);
		ShowItemInfo(SW_HIDE);
	}
	else
	{
		ShowUserInfo(SW_HIDE);
		ShowItemInfo(SW_SHOW);
		OnBnClickedBtnreset();

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			UserAccount = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Account"));//玩家帐号
			UserName = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserNick"));//玩家昵称
			UserID= atoi(theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserID")));//玩家ID

			if(tbcResult.GetCurSel()==1)
			{
				SetDlgItemText(IDC_EDITADDNAME, UserName);//设置要添加道具的玩家昵称		
			}
		}
		else
		{
			UserAccount = "";
			UserName = "";
			UserID = 0;
			SetDlgItemText(IDC_EDITADDNAME, "");//设置要添加道具的玩家昵称
		}
	}
	*pResult = 0;
}

//模糊查询可以进行添加的道具信息
void CGTOWNItemManage::OnBnClickedBtnblursearch()
{
	try
	{		
		CIni mIni;

		int index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");
		int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");

		while(listResult.DeleteColumn(0)){};

		UpdateData(true);			

		if(UserName == "")//要添加道具的玩家昵称不能为空
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","IM_Warn_UserNickNull"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString tmpName = "";//用于模糊查询的道具名称
		GetDlgItemText(IDC_EDITITEM,tmpName);//获取用于模糊查询的道具名称
		if(tmpName == "")//用于模糊查询的道具名称不能为空
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","IM_WARN_BlurItemNameNull"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

		//用于模糊查询的道具名称
		socketdata.AddTFLV(CEnumCore::TagName::GT_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(tmpName),(unsigned char *)mIni.wcharToChar(tmpName));

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数


		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_Select_Item))//模糊查询道具信息
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_TreasureBox"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}
}


//单击可以添加的道具列表，保存行号
void CGTOWNItemManage::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listResult.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		addItem = listResult.SubItemHitTest(&lvinfo);//保存在可以添加的道具列表中选中的行号
	}
	else
	{
		addItem = -1;
	}
	*pResult = 0;
}

//双击可以添加的道具列表，进行添加
void CGTOWNItemManage::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listResult.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		addItem = listResult.SubItemHitTest(&lvinfo);//保存在可以添加的道具列表中选中的行号

		if(addItem >= 0)
		{
			OnBnClickedBtnadd();
		}
	}
	else
	{
		addItem = -1;
	}
	*pResult = 0;
}


//添加道具信息到赠送道具列表中
void CGTOWNItemManage::OnBnClickedBtnadd()
{
	try
	{
		CIni mIni;

		if((listResult.GetItemCount() == 0)||(addItem < 0))//如果要添加的道具列表为空则返回
		{
			return;
		}

		CString tmpItemID = listResult.GetItemText(addItem, 0);
		int ItemID = atoi(mIni.wcharToChar(tmpItemID));//获取要添加的道具ID
		CString ItemName = listResult.GetItemText(addItem, 1);//获取要添加的道具名称

		int itemNum = GetDlgItemInt(IDC_EDITITEMNUM);
		if(itemNum == 0)
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","IM_Warn_ItemNumNull"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		//if(itemNum>5)
		//{
		//	MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","IM_Warn_ItemNum"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
		//	return;
		//}

		int nRow = 0;
		char strInt[10];
		ZeroMemory(strInt,10);
		if(listItem.GetItemCount() == 0)
		{
			DWORD dwStyle = listItem.GetExtendedStyle();
			dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
			listItem.SetExtendedStyle(dwStyle); //设置扩展风格

			listItem.InsertColumn(0,theApp.operGTOWN.ReadValue("MGTOWN","IM_ITEM_ITEMID"),LVCFMT_CENTER,80,-1);
			listItem.InsertColumn(1,theApp.operGTOWN.ReadValue("MGTOWN","IM_ITEM_ITEMNAME"),LVCFMT_CENTER,100,-1);
			listItem.InsertColumn(2,theApp.operGTOWN.ReadValue("MGTOWN","IM_ITEM_ITEMNUM"),LVCFMT_CENTER,80,-1);

			_itoa(ItemID,strInt,10);
			int nRow=listItem.InsertItem(0,strInt);
			listItem.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItem.SetItemText(nRow,2,strInt);
		}
		else
		{
			_itoa(ItemID,strInt,10);
			int nRow=listItem.InsertItem(0,strInt);
			listItem.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItem.SetItemText(nRow,2,strInt);
		}
	}
	catch(...)
	{
	}
}

//单击赠送道具列表，保存行号
void CGTOWNItemManage::OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listItem.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		delItem = listItem.SubItemHitTest(&lvinfo);//保存在可以添加的道具列表中选中的行号
	}
	else
	{
		delItem = -1;
	}
	*pResult = 0;
}

//双击赠送道具列表，进行删除
void CGTOWNItemManage::OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listItem.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		delItem = listItem.SubItemHitTest(&lvinfo);//保存在可以添加的道具列表中选中的行号

		if(delItem >= 0)
		{
			OnBnClickedBtndelete();
		}
	}
	else
	{
		delItem = -1;
	}
	*pResult = 0;
}

//从赠送道具列表中删除相应的道具
void CGTOWNItemManage::OnBnClickedBtndelete()
{
	if((listItem.GetItemCount() != 0) && (delItem >= 0))
	{
		listItem.DeleteItem(delItem);
	}
	if(listItem.GetItemCount() == 0)
	{
		while(listItem.DeleteColumn(0)){};
	}
}


//添加道具
void CGTOWNItemManage::OnBnClickedBtnsend()
{
	try
	{		
		CIni mIni;

		int index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");
		int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");

		GetDlgItemText(IDC_EDITADDNAME,UserName);//获取角色名
		if(UserName == "")
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","RM_Warn_RoleNameNull"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		///////////////////取邮件内容///////////////////////

		CString m_strSubject;
		GetDlgItemText(IDC_EDMAILSUBJECT,m_strSubject);
		if(m_strSubject == "")
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","IM_Warn_MailSubject"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		CString m_strContent;
		GetDlgItemText(IDC_EDMAILCONTENT,m_strContent);
		if(m_strContent == "")
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","IM_Warn_MailContent"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		char ItemData[2048];
		ZeroMemory(ItemData, 2048);//初始化要发送的道具信息
		char tmpItemData[2048];
		ZeroMemory(tmpItemData, 2048);//保存临时的道具信息

		int itemCount = listItem.GetItemCount();//要添加道具的行数
		int mid = 0;//要添加的道具商品号
		int itemNum = 0;//要添加的道具数量
		for(int i=0;i<itemCount;i++)
		{
			mid = atoi(mIni.wcharToChar(listItem.GetItemText(i,0)));
			itemNum = atoi(mIni.wcharToChar(listItem.GetItemText(i,2)));
			sprintf(tmpItemData, "%i*%i", mid, itemNum);
			if(i == 0)
			{
				sprintf(ItemData, "%s", tmpItemData);
			}
			else
			{
				sprintf(ItemData, "%s|%s", ItemData, tmpItemData);
			}
		}		

		int iUserByID=theApp.UserByID;

		CSocketData socketdata;	
		socketdata.InitCreate(1,25);
		char strInt[10];
		ZeroMemory(strInt, 10);

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号


		//邮件主题
		socketdata.AddTFLV(CEnumCore::TagName::GT_MailTitle,CEnumCore::TagFormat::TLV_STRING,strlen(m_strSubject),(unsigned char *)mIni.wcharToChar(m_strSubject));
		//邮件内容
		socketdata.AddTFLV(CEnumCore::TagName::GT_MailContent,CEnumCore::TagFormat::TLV_STRING,strlen(m_strContent),(unsigned char *)mIni.wcharToChar(m_strContent));

		//添加的道具内容
		socketdata.AddTFLV(CEnumCore::TagName::GT_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemData),(unsigned char *)ItemData);

		_itoa(itemCount,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageCount,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//添加数量

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		_itoa(iUserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID


		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_ADD_ITEM))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","IM_Error_ADDITEM"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}	
}

//重置添加道具中的信息
void CGTOWNItemManage::OnBnClickedBtnreset()
{
	SetDlgItemText(IDC_EDITITEM,"");//模糊查询道具名称为空
	SetDlgItemInt(IDC_EDITITEMNUM,1);//道具数量为1
	SetDlgItemText(IDC_EDMAILSUBJECT,"");//邮件主题为空
	SetDlgItemText(IDC_EDMAILCONTENT,"");//邮件内容为空
	listResult.DeleteAllItems();
	while(listResult.DeleteColumn(0)){}//道具列表为空
	listItem.DeleteAllItems();
	while(listItem.DeleteColumn(0)){}//赠送道具列表为空
}


// 接收返回信息
LRESULT CGTOWNItemManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::GT_UserInfo_Query_Resp://查询玩家资料信息的回应
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
					pageInfo = false;//不能翻页		
					cmbPage.ResetContent();
					while(listUser.DeleteColumn(0)){}
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
	case CEnumCore::Message_Tag_ID::GT_ITEM_SELECT_ACK://模糊查询道具信息的回应
	case CEnumCore::Message_Tag_ID::GT_Select_Item_Resp:
		{
			theApp.operGTOWN.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_ADD_ITEM_ACK://给玩家添加道具的回应
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operGTOWN.ShowResult(result);//显示操作结果

			OnBnClickedBtnreset();//重置信息
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

//显示玩家信息
void CGTOWNItemManage::ShowUserInfo(int nCmdShow)
{
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(nCmdShow);
}

//显示其他信息
void CGTOWNItemManage::ShowItemInfo(int nCmdShow)
{
	GetDlgItem(IDC_LBLADDNAME)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDITADDNAME)->ShowWindow(nCmdShow);
	//GetDlgItem(IDC_LBLITEM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDITITEM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_BTNBLURSEARCH)->ShowWindow(nCmdShow);

	GetDlgItem(IDC_LISTRESULT)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_LBLITEMNUM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDITITEMNUM)->ShowWindow(nCmdShow);

	GetDlgItem(IDC_BTNADD)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_BTNDELETE)->ShowWindow(nCmdShow);

	GetDlgItem(IDC_LBLTOADDITEM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(nCmdShow);

	GetDlgItem(IDC_LBLMAILSUBJECT)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDMAILSUBJECT)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_LBLMAILCONTENT)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDMAILCONTENT)->ShowWindow(nCmdShow);

	GetDlgItem(IDC_BTNSEND)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(nCmdShow);
}

//单击用户资料信息的列名进行排序
void CGTOWNItemManage::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operGTOWN.SortListInfo(&listUser,pNMHDR,pResult);
}

//单击结果信息的列名进行排序
void CGTOWNItemManage::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operGTOWN.SortListInfo(&listResult,pNMHDR,pResult);
}

//单击添加道具列表进行排序
void CGTOWNItemManage::OnLvnColumnclickListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operGTOWN.SortListInfo(&listItem,pNMHDR,pResult);
}

//使用关闭按钮
void CGTOWNItemManage::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	tbcResult.SetCurSel(0);
	ShowUserInfo(SW_SHOW);
	ShowItemInfo(SW_HIDE);
}

// 关闭对话框
void CGTOWNItemManage::OnClose()
{
	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Close");//关闭窗体	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}