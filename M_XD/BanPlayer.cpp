// BanPlayer.cpp : 实现文件
//

#include "stdafx.h"
#include "M_XD.h"
#include "BanPlayer.h"
#include ".\banplayer.h"


// CBanPlayer 对话框

IMPLEMENT_DYNAMIC(CBanPlayer, CDialog)
CBanPlayer::CBanPlayer(CWnd* pParent /*=NULL*/)
	: CDialog(CBanPlayer::IDD, pParent)
{
}

CBanPlayer::~CBanPlayer()
{
}
void CBanPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_EDITBANACCOUNT, txtAccount);
	DDX_Control(pDX, IDC_EDITBANREASON, txtReason);
	DDX_Control(pDX, IDC_CMBBANTYPE, cmbType);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);	
}


BEGIN_MESSAGE_MAP(CBanPlayer, CDialog)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_BN_CLICKED(IDC_BTNBAN, OnBnClickedBtnban)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
	ON_BN_CLICKED(IDC_BTNSEARCH, OnBnClickedBtnsearch)
	ON_CBN_SELCHANGE(IDC_CMBSERVER, OnCbnSelchangeCmbserver)
	//ON_BN_CLICKED(IDC_BTBROWSE, OnBnClickedBtbrowse)
	//ON_BN_CLICKED(IDC_BTMULTICLOSE, OnBnClickedBtmulticlose)
	//ON_BN_CLICKED(IDC_BTBROWSE, OnBnClickedBtbrowse)	
END_MESSAGE_MAP()


// CBanPlayer 消息处理程序

// 初始化对话框
BOOL CBanPlayer::OnInitDialog()
{
	CDialog::OnInitDialog();	

	InitUI();// 初始化显示字符		
	showUserInfo();

	nItem = 0;// 单击用户列表得到行号
	mItem = 0;// 单击帐号封停列表得到行号
	pageInfo = false;// 判断是否需要翻页
	ServerIP = "";// 游戏服务器IP	
	ServerName = "";//游戏服务器名称
	UserAccount = "";// 玩家帐号	
	UserName = "";//玩家帐号和昵称

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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置
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
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listResult的位置
	}

	//OperationPAL operXD;
	dlgStatus = theApp.operXD.ReadIntValue("MXD","Create");//初始建立对话框

	if(theApp.operXD.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
	}

	return TRUE;
}

// 初始化显示字符
void CBanPlayer::InitUI()
{
	SetWindowText(theApp.operXD.ReadValue("MXD","BU_UI_BanPlayer"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operXD.ReadValue("MXD","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operXD.ReadValue("MXD","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operXD.ReadValue("MXD","UIC_UI_lblRole"));
	SetDlgItemText(IDSEARCH,theApp.operXD.ReadValue("MXD","Search"));
	SetDlgItemText(IDCANCEL,theApp.operXD.ReadValue("MXD","Close"));

	SetDlgItemText(IDC_LBLHINT,theApp.operXD.ReadValue("MXD","BU_UI_LblHint"));	
	SetDlgItemText(IDC_LBLPAGE,theApp.operXD.ReadValue("MXD","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLSACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_BTNSEARCH,theApp.operXD.ReadValue("MXD","BU_UI_SEARCHBAN"));

	SetDlgItemText(IDC_LBLBANACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLBANREASON,theApp.operXD.ReadValue("MXD","BU_UI_reason"));
	SetDlgItemText(IDC_LBLBANTYPE,theApp.operXD.ReadValue("MXD","BU_UI_TYPE"));
	SetDlgItemText(IDC_BTNRESET,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_BTNBAN,theApp.operXD.ReadValue("MXD","BU_UI_TpgOpen"));
	SetDlgItemText(IDC_LBBANTIME2,theApp.operXD.ReadValue("MXD","BU_UI_LblDate"));

	tbcResult.InsertItem(0,theApp.operXD.ReadValue("MXD","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operXD.ReadValue("MXD","BU_UI_TpgOpen"));
	tbcResult.InsertItem(2,theApp.operXD.ReadValue("MXD","BU_UI_TpgList"));
	tbcResult.InsertItem(3,theApp.operXD.ReadValue("MXD","BU_UI_BtnSave"));
	tbcResult.InsertItem(4,theApp.operXD.ReadValue("MXD","BU_UI_Tpgquary"));
	//tbcResult.InsertItem(4,theApp.operXD.ReadValue("MXD","BU_UI_TpgMultiClose"));
}

//处理快捷键响应函数
BOOL CBanPlayer::PreTranslateMessage(MSG* pMsg)
{
	//OperationPAL operXD;
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operXD.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operXD.CopyListInfo(&listResult);
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
void CBanPlayer::OnSize(UINT nType, int cx, int cy)
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
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listResult的位置
	}
}

//设置背景颜色
HBRUSH CBanPlayer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//获取选择的ServerIP
void CBanPlayer::OnCbnSelchangeCmbserver()
{
	try
	{
		CString m_ServerName;
		GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//获取游戏服务器的名称
		if(m_ServerName == "")//游戏服务器为空
		{
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
	}
	catch(...)
	{
	}
}

// 查询资料信息
void CBanPlayer::OnBnClickedOk()
{
	try
	{
		CIni mIni;
		//OperationPAL operXD;

		nItem = 0;//玩家资料列表没有选定项
		mItem = 0;// 单击帐号封停列表得到行号
		pageInfo = false;//列表不能翻页		
		cmbPage.ResetContent();//清除列表翻页的复选框
		while(listResult.DeleteColumn(0)){}//清除列表中的所有内容
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_SelectServer"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITACCOUNT,UserAccount);//获取玩家帐号
		GetDlgItemText(IDC_EDITNAME,UserName);//获取玩家角色名
		if((UserName == "") && (UserAccount == ""))//玩家帐号和玩家角色名同时为空
		{
			showBanList();
			AllBanUserList();//查询所有被封停帐号列表信息
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
void CBanPlayer::UserInfo()
{
	try
	{		
		CIni mIni;	

		nItem = 0;
		while(listUser.DeleteColumn(0)){}

		int index = theApp.operXD.ReadIntValue("MXD","index");//查询第一页的信息
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//每页显示50条记录
        CString SearchType="1";
		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家角色名、玩家帐号、查找类型、页数、每页的记录条数\\服务器Name、
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		//socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号
        socketdata.AddTFLV(CEnumCore::TagName::XDJG_SEARCHTYPE,CEnumCore::TagFormat::TLV_STRING,strlen(SearchType),(unsigned char *)mIni.wcharToChar(SearchType));//查找类型
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Account_Query))//发送查询玩家资料信息的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
		}

		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_UserInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

// 查询所有被封停帐号列表信息
void CBanPlayer::AllBanUserList()
{
	try
	{				
		CIni mIni;

		mItem = -1;
		pageInfo = false;		
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}

		char strInt[10];
		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家角色名、玩家帐号、页数、每页的记录条数
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_CloseList))
		{		
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//发送查询请求
		}

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_UserInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

// 单击用户列表保存当前行号
void CBanPlayer::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
			nItem = 0;
		}
	}
	*pResult = 0;
}

// 双击用户列表切换界面
void CBanPlayer::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
				showBanPlayer();

				UpdateData(false);

				UserAccount = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));//获取要封停的玩家帐号
				UserName = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));//获取要封停的玩家角色名

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

// 切换选项卡进行操作
void CBanPlayer::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	          
	CIni mIni;

	if(tbcResult.GetCurSel()==0)//如果选中的是玩家资料信息的页面
	{
		showUserInfo();
	}
	else if(tbcResult.GetCurSel()==2)//如果选中的是封停帐号列表的页面
	{
		showBanList();
		AllBanUserList();
	}
	else if(tbcResult.GetCurSel()==1)//如果选中的是封停帐号的页面
	{
		showBanPlayer();
		cmbType.SetCurSel(0);

		UpdateData(false);

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			UserAccount = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));
			UserName = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));

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
		cmbType.SetCurSel(0);

		UpdateData(false);
		if((listResult.GetItemCount() > 0) && (mItem >= 0))
		{
			
			UserAccount = theApp.operXD.GetValueByColName(&listResult, mItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));
			UserName = theApp.operXD.GetValueByColName(&listResult, mItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));
 
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
		ShowPlayerInfo();
		SetDlgItemText(IDC_EDITSACCOUNT,"");
		while(listResult.DeleteColumn(0)){}
	}
	//else if(tbcResult.GetCurSel()==4)//如果选中的是查询帐号有没有被封停的页面
	//{
	//	showSearchPlayer();
	//	SetDlgItemText(IDC_EDITBANACCOUNT,"");
	//	SetDlgItemText(IDC_EDITBANREASON,"");
	//	SetDlgItemText(IDC_ETFILE,"");
	//}
	*pResult = 0;
}

// 单击封停帐号列表保存当前行号
void CBanPlayer::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
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
void CBanPlayer::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
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
				CIni mIni;
				showUnbindPlayer();
				UpdateData(false);
				UserAccount = theApp.operXD.GetValueByColName(&listResult, mItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));//获取要解封的玩家帐号
				UserName = theApp.operXD.GetValueByColName(&listResult, mItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));
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

// 翻页进行查询
void CBanPlayer::OnCbnSelchangeCmbpage()
{
	try
	{		
		if(pageInfo)
		{	
			CIni mIni;
			while(listResult.DeleteColumn(0)){}

			int index = cmbPage.GetCurSel() + 1;//页数为cmbPage当前的索引值加1，也就是cmbPage中当前显示的值
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//每页显示50条记录

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			//socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
			if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_CloseList))
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//发送查询请求
			}

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_Page"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

// 封停或解封帐号
void CBanPlayer::OnBnClickedBtnban()
{
	try
	{
		CIni mIni;			
		CString BanAccount = "";
		CString BanTime="";///////////////////////////////记录封停时间
        GetDlgItemText(IDC_BANTIME,BanTime);
        //MessageBox(BanTime);
		txtAccount.GetWindowText(BanAccount);//获取玩家帐号
		if(BanAccount == "")//玩家帐号不能为空
		{
			MessageBox(theApp.operXD.ReadValue("MXD","BU_UI_AccountNull"),theApp.operXD.ReadValue("MXD","Warn"),0);
			return;
		}				

		CString BanReason = "";
		txtReason.GetWindowText(BanReason);//获取封停或解封原因
		if((tbcResult.GetCurSel() == 1) || (tbcResult.GetCurSel() == 3))// 选择的是封停或解封帐号
		{			
			if(strlen(BanReason) >= 256)//封停或解封原因不能为空
			{
				MessageBox(theApp.operXD.ReadValue("MXD","BU_UI_ReasonTooLong"),theApp.operXD.ReadValue("MXD","Warn"),0);
				return;
			}
		}
		else if(tbcResult.GetCurSel() == 4)// 选择的是查询帐号有没有被封停
		{
			CString m_ServerName;
			GetDlgItemText(IDC_CMBSERVER,m_ServerName);//获取服务器名称
			if(m_ServerName == "")//服务器名称不能为空
			{
				MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_SelectServer"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//获取服务器IP
		}
		int userbyID = theApp.UserByID;//操作员ID

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有四个参数，服务器IP、玩家帐号、封停或解封原因、操作员ID
		char strInt[10];
		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(BanAccount),(unsigned char *)mIni.wcharToChar(BanAccount));//玩家帐号
		//if(tbcResult.GetCurSel() == 1)
		//{
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_BANREASON,CEnumCore::TagFormat::TLV_STRING,strlen(BanReason),(unsigned char *)mIni.wcharToChar(BanReason));//封停原因
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_BANTIME,CEnumCore::TagFormat::TLV_STRING,strlen(BanTime),(unsigned char *)mIni.wcharToChar(BanTime));//封停时间
	//	}
		//else if(tbcResult.GetCurSel() == 3)
		//{
		//	socketdata.AddTFLV(CEnumCore::TagName::XDJG_UNBANREASON,CEnumCore::TagFormat::TLV_STRING,strlen(BanReason),(unsigned char *)mIni.wcharToChar(BanReason));//封停原因
		//}
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		int BanType=0;
		if(tbcResult.GetCurSel() == 1)
		{
			CString cmbBanType="";
			GetDlgItemText(IDC_CMBBANTYPE,cmbBanType);
			
			if(cmbBanType==theApp.operXD.ReadValue("MXD","BAN_NOACCOUNT"))
				BanType=BAN_NOACCOUNT;
			else if(cmbBanType==theApp.operXD.ReadValue("MXD","BAN_MAXCOUNT"))
				BanType=BAN_MAXCOUNT;
			else if(cmbBanType==theApp.operXD.ReadValue("MXD","BAN_BYGM"))
				BanType=BAN_BYGM;
			else if(cmbBanType==theApp.operXD.ReadValue("MXD","BAN_GAMEASSIST"))
				BanType=BAN_GAMEASSIST;
			else if(cmbBanType==theApp.operXD.ReadValue("MXD","BAN_FROZEN"))
				BanType=BAN_FROZEN;
			else if(cmbBanType==theApp.operXD.ReadValue("MXD","BAN_LOCK"))
				BanType=BAN_LOCK;
			else if(cmbBanType==theApp.operXD.ReadValue("MXD","BAN_NOCOND"))
				BanType=BAN_NOCOND;
		}
		_itoa(BanType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_BANTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//封停类型

		int midlength = socketdata.EnBody();
		if(tbcResult.GetCurSel() == 1)
		{
			if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ClosePlayer))//发送封停玩家帐号的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
			}
		}
		else if(tbcResult.GetCurSel() == 3)
		{
			if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_OpenPlayer))//发送解封玩家帐号的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
			}
		}
		/*else if(tbcResult.GetCurSel() == 4)
		{
		if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Account_BANISHMENT_QUERY))//发送查询玩家帐号有没有被封停的请求
		{
		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
		}
		}*/		
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//查询玩家账号有没有被封停
void CBanPlayer::OnBnClickedBtnsearch()
{
	try
	{				
		CIni mIni;

		CString BanAccount = "";
		GetDlgItemText(IDC_EDITSACCOUNT,BanAccount);

		while(listResult.DeleteColumn(0)){}

		char strInt[10];
		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家角色名、玩家帐号、页数、每页的记录条数
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		//socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(BanAccount),(unsigned char *)mIni.wcharToChar(BanAccount));//玩家帐号

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_AccountIsClose_Query))
		{		
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//发送查询请求
		}

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_UserInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

// 重置信息
void CBanPlayer::OnBnClickedBtnreset()
{
	SetDlgItemText(IDC_EDITBANREASON,"");
	if(tbcResult.GetCurSel() == 4)
	{
		SetDlgItemText(IDC_EDITBANACCOUNT,"");
	}		
}

// 接收返回信息
LRESULT CBanPlayer::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;

	dlgStatus = theApp.operXD.ReadIntValue("MXD","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operXD.ReadValue("MXD","Main_UI_ParseData"),theApp.operXD.ReadValue("MXD","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

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

			theApp.operXD.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息

			GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
			if(ServerName == "")//游戏服务器为空
				return false;
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_Account_Query_Resp://查询玩家资料信息的回应
		{
			nItem = 0;
			theApp.operXD.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ClosePlayer_Resp://封停玩家帐号的回应
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operXD.ShowResult(result);//显示操作结果

			showUserInfo();
			UserInfo();//查询玩家帐号信息
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_OpenPlayer_Resp://解封玩家帐号的回应
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operXD.ShowResult(result);//显示操作结果

			showBanList();
			AllBanUserList();//查询所有被封停帐号列表
		}
		break;
	//case CEnumCore::Message_Tag_ID::XDJG_Account_BANISHMENT_QUERY_RESP://查询帐号有没有被封停的回应
	//	{
	//		CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
	//		CString result = (LPCTSTR)&m_tflv.lpdata;
	//		theApp.operXD.ShowResult(result);//显示返回结果
	//	}
	//	break;
	//case CEnumCore::Message_Tag_ID::XDJG_CloseList_Resp://返回批量封停的结果//maple add
	//	{

	//		CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
	//		CString result = (LPCTSTR)&m_tflv.lpdata;
	//		theApp.operXD.ShowResult(result);//显示返回结果

	//		//showBanList();
	//		//AllBanUserList();//查询所有被封停帐号列表
	//	}
	default:
		{
			if(pageInfo)
			{
				theApp.operXD.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operXD.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

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
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

//单击用户资料信息的列名进行排序
void CBanPlayer::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationPAL operXD;
	theApp.operXD.SortListInfo(&listUser,pNMHDR,pResult);
}

//单击结果信息的列名进行排序
void CBanPlayer::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationPAL operXD;
	theApp.operXD.SortListInfo(&listResult,pNMHDR,pResult);
}

// 关闭对话框
void CBanPlayer::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
}

// 关闭对话框
void CBanPlayer::OnClose()
{
	dlgStatus = theApp.operXD.ReadIntValue("MXD","Close");//关闭窗体	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//显示玩家资料信息
void CBanPlayer::showUserInfo()
{
	tbcResult.SetCurSel(0);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNSEARCH)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBBANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBBANTIME2)->ShowWindow(SW_HIDE);
}

//显示封停帐号
void CBanPlayer::showBanPlayer()
{
	//OperationPAL operXD;
	tbcResult.SetCurSel(1);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNSEARCH)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

	cmbType.ResetContent();
	//cmbType.AddString(theApp.operXD.ReadValue("MXD","BAN_NOACCOUNT"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","BAN_MAXCOUNT"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","BAN_BYGM"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","BAN_GAMEASSIST"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","BAN_FROZEN"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","BAN_LOCK"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","BAN_NOCOND"));
	cmbType.SetCurSel(0);

	SetDlgItemText(IDC_LBLBANREASON,theApp.operXD.ReadValue("MXD","BU_UI_reason"));//封停原因
	SetDlgItemText(IDC_BTNBAN,theApp.operXD.ReadValue("MXD","BU_UI_TpgOpen"));//帐号封停
	//txtAccount.SetReadOnly(true);//玩家帐号的CEdit对象设置为只读属性

	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBBANTIME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BANTIME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBBANTIME2)->ShowWindow(SW_SHOW);
}

//显示封停帐号列表
void CBanPlayer::showBanList()
{
	tbcResult.SetCurSel(2);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNSEARCH)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBBANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBBANTIME2)->ShowWindow(SW_HIDE);
}

//显示解封帐号
void CBanPlayer::showUnbindPlayer()
{
	tbcResult.SetCurSel(3);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNSEARCH)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

	SetDlgItemText(IDC_LBLBANREASON,theApp.operXD.ReadValue("MXD","BU_UI_UnBind"));//解封原因
	SetDlgItemText(IDC_BTNBAN,theApp.operXD.ReadValue("MXD","BU_UI_BtnSave"));//解封帐号

	//txtAccount.SetReadOnly(true);//玩家帐号的CEdit对象设置为只读属性
	//txtAccount.SetReadOnly(false);
	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBBANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBBANTIME2)->ShowWindow(SW_HIDE);
}

//查询帐号有没有封停
void CBanPlayer::showSearchPlayer()
{
	tbcResult.SetCurSel(4);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_SHOW);


	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

	SetDlgItemText(IDC_BTNBAN,theApp.operXD.ReadValue("MXD","Search"));
}

//查询账号有没有被封停
void CBanPlayer::ShowPlayerInfo()
{
	tbcResult.SetCurSel(4);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLSACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITSACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNSEARCH)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBBANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBBANTIME2)->ShowWindow(SW_HIDE);
}

//bool CBanPlayer::ReadXls(CString m_filePath,CString* m_allUserAccount,CString* m_allUserChar)
//{
//	try
//	{
//		CoInitialize(NULL);
//		_ConnectionPtr m_pConnection;
//		_RecordsetPtr	m_pRecordset;
//		CString ConnectionString="";
//		//CString allusername="";
//		ConnectionString = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=");   
//		ConnectionString += m_filePath;   //excel   file   name   
//		ConnectionString += _T(";Extended Properties=\"Excel 8.0;HDR=Yes;IMEX=1\""); 
//
//
//		BSTR resultsString = ConnectionString.AllocSysString();
//
//
//
//		m_pConnection.CreateInstance(__uuidof(Connection));
//
//		m_pConnection->Open(resultsString,"","",adModeUnknown);
//		m_pRecordset.CreateInstance(__uuidof(Recordset));
//		m_pRecordset->Open("select * from [Sheet1$]",
//			m_pConnection.GetInterfacePtr(),
//			adOpenDynamic,
//			adLockOptimistic,
//			adCmdText);
//
//		if(m_pRecordset->adoEOF) AfxMessageBox("该文档没有内容");
//		//////第一行不读
//		while(!m_pRecordset->adoEOF)
//		{
//			if(m_pRecordset->GetFields()->GetItem("玩家帐号")->Value.vt==VT_NULL
//				||m_pRecordset->GetFields()->GetItem("角色名称")->Value.vt==VT_NULL) 
//			{
//				AfxMessageBox("格式错误");
//				break;
//			}
//			CString tmpUserName=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem("玩家帐号")->GetValue());
//			*m_allUserAccount += tmpUserName;
//			*m_allUserAccount += "|";
//
//			CString tmpChar=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem("角色名称")->GetValue());
//			*m_allUserChar += tmpChar;
//			*m_allUserChar += "|";
//
//
//			m_pRecordset->MoveNext();
//		}
//		m_pRecordset->Close();
//		if(m_pRecordset) m_pRecordset.Release();
//		m_pConnection->Close();
//		if(m_pConnection) m_pConnection.Release();
//		CoUninitialize();
//
//	}
//	catch(...)
//	{
//		return false;
//	}
//	return TRUE;
//}

//void CBanPlayer::OnBnClickedBtbrowse()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	char path[256];
//	GetCurrentDirectory(256,path);
//	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象
//
//	lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,"文件类型(*.xls)|*.xls||");
//
//
//	if(lpszOpenFile->DoModal()==IDOK)//假如点击对话框确定按钮
//	{
//		CString szGetName;
//		szGetName=lpszOpenFile->GetPathName();
//		SetDlgItemText(IDC_ETFILE,szGetName);
//		SetCurrentDirectory(path);
//
//	}
//	delete lpszOpenFile;
//}
//
//void CBanPlayer::OnBnClickedBtmulticlose()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	try
//	{
//		CIni mIni;
//		CString allUserName="";
//		CString allChar="";
//		CString filename="";
//		CString BanReason="";
//
//		GetDlgItemText(IDC_EDITBANREASON,BanReason);
//		if(strlen(BanReason)<1)
//		{
//			MessageBox("封停内容不能为空");
//			return;
//		}
//		GetDlgItemText(IDC_ETFILE,filename);
//		if(!ReadXls(filename,&allUserName,&allChar))
//		{
//			AfxMessageBox("格式错误");
//			return;
//		}
//		if(strlen(allUserName)>2000||strlen(allChar)>2000)
//		{
//			AfxMessageBox("超出最大批量数,请在分批");
//			return;
//		}
//		else
//		{
//			int userbyID = theApp.UserByID;//操作员ID
//
//			CSocketData socketdata;
//			socketdata.InitCreate(1,10);//共有四个参数，服务器IP、玩家帐号、封停或解封原因、操作员ID
//
//			CString m_ServerName;
//			GetDlgItemText(IDC_CMBSERVER,m_ServerName);//获取服务器名称
//			if(m_ServerName == "")//服务器名称不能为空
//			{
//				MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_SelectServer"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
//				return;
//			}
//			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//获取服务器IP
//
//			char strInt[10];
//
//			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
//			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(m_ServerName),(unsigned char*)mIni.wcharToChar(m_ServerName));//服务器name
//			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(allUserName),(unsigned char *)mIni.wcharToChar(allUserName));//批量玩家帐号
//			socketdata.AddTFLV(CEnumCore::TagName::PAL_REASON,CEnumCore::TagFormat::TLV_STRING,strlen(BanReason),(unsigned char *)mIni.wcharToChar(BanReason));//封停或解封原因
//
//			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(allChar),(unsigned char *)mIni.wcharToChar(allChar));//批量玩家角色名
//
//			_itoa(userbyID,strInt,10);
//			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID
//
//			int midlength = socketdata.EnBody();
//
//			if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_RELOADFUNCTIONSWITCH))
//			{
//				::EnableWindow(this->GetParent()->m_hWnd,false);
//				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//发送查询请求
//			}
//
//			socketdata.Destroy();
//		}
//
//	}
//	catch(...)
//	{
//
//	}
//}
