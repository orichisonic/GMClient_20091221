// XDItemManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_XD.h"
#include "XDItemManage.h"


// CXDItemManage 对话框

IMPLEMENT_DYNAMIC(CXDItemManage, CDialog)
CXDItemManage::CXDItemManage(CWnd* pParent /*=NULL*/)
	: CDialog(CXDItemManage::IDD, pParent)
{
}

CXDItemManage::~CXDItemManage()
{
}

void CXDItemManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listResult);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_LISTCHARACTER, listUser);
	DDX_Control(pDX, IDC_CMBUSERPAGE, cmbUPage);
	DDX_Control(pDX, IDC_CMBITEM, cmbList);
	DDX_Control(pDX, IDC_LISTITEM, listItem);
	DDX_Control(pDX, IDC_CMBTYPE, cmbType);
	DDX_Control(pDX, IDC_CHECKBATCH, checkSelect);
	DDX_Control(pDX, IDC_EDITNEW, CEditNew);
	DDX_Control(pDX, IDC_CHECKGROUP, checkGroup);
	DDX_Control(pDX, IDC_PROGRESSMAIL, progMail);
	DDX_Control(pDX, IDC_CMBQUALITY, cmbQuality);
}


BEGIN_MESSAGE_MAP(CXDItemManage, CDialog)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_CBN_SELCHANGE(IDC_CMBUIPAGE, OnCbnSelchangeCmbuipage)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_LISTCHARACTER, OnNMClickListcharacter)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTCHARACTER, OnNMDblclkListcharacter)
	ON_CBN_SELCHANGE(IDC_CMBUSERPAGE, OnCbnSelchangeCmbuserpage)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTNEDIT, OnBnClickedBtnedit)
	ON_BN_CLICKED(IDC_BTNRECOVER, OnBnClickedBtnrecover)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_BN_CLICKED(IDC_BTNDELITEM, OnBnClickedBtndelitem)
	ON_BN_CLICKED(IDC_BTNITEMLIST, OnBnClickedBtnitemlist)
	ON_BN_CLICKED(IDC_BTNADD, OnBnClickedBtnadd)
	ON_NOTIFY(NM_CLICK, IDC_LISTITEM, OnNMClickListitem)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTITEM, OnNMDblclkListitem)
	ON_BN_CLICKED(IDC_BTNDELETE, OnBnClickedBtndelete)
	ON_BN_CLICKED(IDC_CHECKBATCH, OnBnClickedCheckselect)
	ON_BN_CLICKED(IDC_BTNBROWSE, OnBnClickedBtnbrowse)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTCHARACTER, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListresult)
	ON_BN_CLICKED(IDC_CHECKGROUP, OnBnClickedCheckgroup)
	ON_CBN_SELCHANGE(IDC_CMBUISERVER, OnCbnSelchangeCmbuiserver)
END_MESSAGE_MAP()


// CXDItemManage 消息处理程序

// 初始化对话框
BOOL CXDItemManage::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// 初始化显示字符

	nItem = -1;
	pageInfo = false;
	pageUInfo = false;
	ServerIP = "";
	UserID = "";
	UserName = "";
	UserNick = "";//初始化一些私有变量
	nFirst = 0;
	nListItem = 0;
	nSelectItem = 0;
	ZeroMemory(ItemResult, 2048);//初始化添加道具的最终结果
	ZeroMemory(tmpItemResult, 2048);//临时的添加道具信息
	multStatus=0;//不批量添加

	SetProp(listUser.GetSafeHwnd(),"排序列号",(HANDLE)0);
    SetProp(listUser.GetSafeHwnd(),"排序顺序",(HANDLE)1);

	SetProp(listResult.GetSafeHwnd(),"排序列号",(HANDLE)0);
    SetProp(listResult.GetSafeHwnd(),"排序顺序",(HANDLE)1);

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

		if(listResult.m_hWnd != NULL)
		{
			listResult.MoveWindow(newRect);//设置好listResult的位置，listResult和listUser的位置完全重叠
		}
	}

	dlgStatus = theApp.operXD.ReadIntValue("MXD","Create");//当前的状态为初始建立对话框

	if(theApp.operXD.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
	}

	return TRUE;
}

// 初始化显示字符
void CXDItemManage::InitUI()
{
	SetWindowText(theApp.operXD.ReadValue("MXD","IM_UI_ITEMMANAGE"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operXD.ReadValue("MXD","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operXD.ReadValue("MXD","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operXD.ReadValue("MXD","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operXD.ReadValue("MXD","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operXD.ReadValue("MXD","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operXD.ReadValue("MXD","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operXD.ReadValue("MXD","IC_UI_Avatar"));
	tbcResult.InsertItem(2,theApp.operXD.ReadValue("MXD","IC_UI_PackItem"));
	tbcResult.InsertItem(3,theApp.operXD.ReadValue("MXD","IC_UI_BankItem"));
	tbcResult.InsertItem(4,theApp.operXD.ReadValue("MXD","IM_UI_tpgAddItem"));
	tbcResult.InsertItem(5,theApp.operXD.ReadValue("MXD","IM_UI_tpgEditMoney"));

	SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNICK,theApp.operXD.ReadValue("MXD","UIC_UI_lblNick"));
	SetDlgItemText(IDC_LBLITEM,theApp.operXD.ReadValue("MXD","IM_UI_lblItemName"));
	SetDlgItemText(IDC_LBLNUM,theApp.operXD.ReadValue("MXD","IM_UI_lblItemNum"));
	SetDlgItemText(IDC_BTNDELITEM,theApp.operXD.ReadValue("MXD","IM_UI_DELITEM"));

	SetDlgItemText(IDC_CHECKBATCH,theApp.operXD.ReadValue("MXD","IM_UI_CHECKMULT"));
	SetDlgItemText(IDC_CHECKGROUP,theApp.operXD.ReadValue("MXD","IM_UI_CHECKGROUP"));
	SetDlgItemText(IDC_BTNBROWSE,theApp.operXD.ReadValue("MXD","IM_UI_BTNBROWSE"));

	SetDlgItemText(IDC_LBLSENDER,theApp.operXD.ReadValue("MXD","IM_UI_Sender"));
	SetDlgItemText(IDC_LBLQUALITY,theApp.operXD.ReadValue("MXD","IM_UI_ITEMQUALITY"));
	SetDlgItemText(IDC_LBLMAILSUBJECT2,theApp.operXD.ReadValue("MXD","IM_UI_LBLMAILSUBJECT"));
	SetDlgItemText(IDC_LBLMAILCONTENT2,theApp.operXD.ReadValue("MXD","IM_UI_LBLMAILCONTENT"));
	SetDlgItemText(IDC_LBLMAILMONEY,theApp.operXD.ReadValue("MXD","IM_UI_MONEY"));

	SetDlgItemText(IDC_LBLDELNUM,theApp.operXD.ReadValue("MXD","IM_UI_lblItemNum"));

	SetDlgItemText(IDC_LBLATTRID,theApp.operXD.ReadValue("MXD","IM_UI_ATTRID"));
	SetDlgItemText(IDC_LBLATTRVALUE,theApp.operXD.ReadValue("MXD","IM_UI_ATTRVALUE"));
	SetDlgItemText(IDC_LBLADDLEVEL,theApp.operXD.ReadValue("MXD","IM_UI_ADDLEVEL"));
	SetDlgItemText(IDC_LBLADDTYPE,theApp.operXD.ReadValue("MXD","IM_UI_ADDTYPE"));
	SetDlgItemText(IDC_LBLADDVALUE,theApp.operXD.ReadValue("MXD","IM_UI_ADDVALUE"));
	SetDlgItemText(IDC_LBLADDVALUELAST,theApp.operXD.ReadValue("MXD","IM_UI_ADDVALUELAST"));
	SetDlgItemText(IDC_LBLSTAR,theApp.operXD.ReadValue("MXD","IM_UI_STAR"));
	SetDlgItemText(IDC_LBLPLUGIN,theApp.operXD.ReadValue("MXD","IM_UI_PLUGIN"));
	SetDlgItemText(IDC_LBLSLOTNUM,theApp.operXD.ReadValue("MXD","IM_UI_SLOTNUM"));
	SetDlgItemText(IDC_LBLSLOT1,theApp.operXD.ReadValue("MXD","IM_UI_SLOT1"));
	SetDlgItemText(IDC_LBLSLOT2,theApp.operXD.ReadValue("MXD","IM_UI_SLOT2"));
	SetDlgItemText(IDC_LBLSLOT3,theApp.operXD.ReadValue("MXD","IM_UI_SLOT3"));
	SetDlgItemText(IDC_LBLAPTITUDE,theApp.operXD.ReadValue("MXD","IM_UI_APTITUDE"));
	SetDlgItemText(IDC_LBLBIND,theApp.operXD.ReadValue("MXD","IM_UI_BIND"));

	SetDlgItemText(IDC_EDITATTRID,"-1");
	SetDlgItemText(IDC_EDITATTRVALUE,"-1");
	SetDlgItemText(IDC_EDITADDLEVEL,"-1");
	SetDlgItemText(IDC_EDITADDTYPE,"-1");
	SetDlgItemText(IDC_EDITADDVALUE,"-1");
	SetDlgItemText(IDC_EDITADDVALUELAST,"-1");
	SetDlgItemText(IDC_EDITSTAR,"-1");
	SetDlgItemText(IDC_EDITPLUGIN,"-1");
	SetDlgItemText(IDC_EDITSLOTNUM,"-1");
	SetDlgItemText(IDC_EDITSLOT1,"-1");
	SetDlgItemText(IDC_EDITSLOT2,"-1");
	SetDlgItemText(IDC_EDITSLOT3,"-1");
	SetDlgItemText(IDC_EDITAPTITUDE,"-1");
	SetDlgItemText(IDC_EDITBIND,"-1");

	//cmbQuality.AddString(theApp.operXD.ReadValue("MXD","IM_UI_WHITE"));
	//cmbQuality.AddString(theApp.operXD.ReadValue("MXD","IM_UI_BLUE"));
	//cmbQuality.AddString(theApp.operXD.ReadValue("MXD","IM_UI_PURPLE"));
	//cmbQuality.AddString(theApp.operXD.ReadValue("MXD","IM_UI_ORANGE"));
	//cmbQuality.SetCurSel(0);

	SetDlgItemText(IDC_LBLMAIN,theApp.operXD.ReadValue("MXD","IM_UI_LblMain"));
	SetDlgItemText(IDC_LBLPROG,theApp.operXD.ReadValue("MXD","IM_UI_LblMailFirst")+theApp.operXD.ReadValue("MXD","IM_UI_LblMailSecond")+theApp.operXD.ReadValue("MXD","IM_UI_LblMailThird")+theApp.operXD.ReadValue("MXD","IM_UI_LblMailFourth"));
}

// 自动改变大小
void CXDItemManage::OnSize(UINT nType, int cx, int cy)
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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置

		if(listResult.m_hWnd != NULL)
		{
			listResult.MoveWindow(newRect);//设置好listResult的位置
		}
	}
}

//设置背景颜色
HBRUSH CXDItemManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//获取选择的ServerIP
void CXDItemManage::OnCbnSelchangeCmbuiserver()
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

// 查询玩家资料信息
void CXDItemManage::OnBnClickedUisearch()
{
	try
	{
		CIni mIni;

		tbcResult.SetCurSel(0);

		nItem = -1;//玩家资料列表没有选定项
		pageUInfo = false;//玩家资料列表不能翻页	
		cmbUPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		ShowItemInfo(SW_HIDE);
		ShowNewItem(SW_HIDE);
		ShowUserInfo(SW_SHOW);

		UpdateData(true);

		CString m_ServerName;
		GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//获取游戏服务器的名称
		if(m_ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_SelectServer"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//获取玩家帐号
		GetDlgItemText(IDC_EDITUINICK,UserNick);//获取玩家昵称
		if((UserName == "") && (UserNick == ""))//玩家帐号和玩家昵称不能同时为空
		{
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_InputAccount"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		UserInfo();// 查询玩家资料信息
	}
	catch(...)
	{
	}
}

// 查询玩家资料信息
void CXDItemManage::UserInfo()
{	
	try
	{		
		CIni mIni;		

		int index = theApp.operXD.ReadIntValue("MXD","index");//查询第一页的信息
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//每页显示50条记录

		nItem = -1;//玩家资料列表没有选定项
		pageUInfo = false;//玩家资料列表不能翻页	
		cmbUPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_SEARCHTYPE,CEnumCore::TagFormat::TLV_STRING,strlen("1"),(unsigned char *)mIni.wcharToChar("1"));//查找类型

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query);//发送查询玩家资料信息的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_UserInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

// 翻页查询玩家资料信息
void CXDItemManage::OnCbnSelchangeCmbuserpage()
{	
	try
	{	
		if(pageUInfo)//如果可以翻页的话
		{
			CIni mIni;
			//OperationWA theApp.operXD;	

			int index = cmbUPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//每页显示50条记录

			while(listUser.DeleteColumn(0)){}//清除页面内容

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_SEARCHTYPE,CEnumCore::TagFormat::TLV_STRING,strlen("1"),(unsigned char *)mIni.wcharToChar("1"));//查找类型

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query );//发送查询玩家资料信息的请求

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// 单击用户列表保存当前行号
void CXDItemManage::OnNMClickListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
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
void CXDItemManage::OnNMDblclkListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
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
				pageInfo = false;
				cmbPage.ResetContent();
				while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

				ShowNewItem(SW_HIDE);
				ShowUserInfo(SW_HIDE);
				ShowItemInfo(SW_SHOW);

				GetDlgItem(IDC_LBLITEM)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDITITEM)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTNDELITEM)->ShowWindow(SW_HIDE);

				if((listUser.GetItemCount() > 0) && (nItem >= 0))
				{
					UserName = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// 保存选中的玩家帐号
					//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","WA_NickID"));// 保存选中的玩家ID
					UserNick = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// 保存选中的玩家昵称

					tbcResult.SetCurSel(1);
					ItemInfo();
				}
			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

// 切换选项卡进行查询
void CXDItemManage::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	pageInfo = false;
	cmbPage.ResetContent();
	while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

	UserName = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// 保存选中的玩家帐号
	//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","WA_NickID"));// 保存选中的玩家ID
	UserNick = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// 保存选中的玩家昵称

	switch(tbcResult.GetCurSel())
	{
	case 0:
		{
			ShowItemInfo(SW_HIDE);
			ShowNewItem(SW_HIDE);
			ShowUserInfo(SW_SHOW);
		}
		break;
	case 1:
		{
			ShowUserInfo(SW_HIDE);
			ShowNewItem(SW_HIDE);
			ShowItemInfo(SW_SHOW);

			GetDlgItem(IDC_LBLITEM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITITEM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLDELNUM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITDELNUM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNDELITEM)->ShowWindow(SW_HIDE);

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				ItemInfo();
			}	
		}
		break;
	case 2:
		{
			ShowUserInfo(SW_HIDE);
			ShowNewItem(SW_HIDE);
			ShowItemInfo(SW_SHOW);

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				ItemInfo();
			}	
		}
		break;
	case 3:
		{
			ShowUserInfo(SW_HIDE);
			ShowNewItem(SW_HIDE);
			ShowItemInfo(SW_SHOW);

			GetDlgItem(IDC_LBLITEM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITITEM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLDELNUM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITDELNUM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNDELITEM)->ShowWindow(SW_HIDE);

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				ItemInfo();
			}	
		}
		break;
	case 4:
		{
			ShowUserInfo(SW_HIDE);
			ShowItemInfo(SW_HIDE);
			ShowMoneyInfo(SW_HIDE);
			ShowNewItem(SW_SHOW);
			NewItemValue();

			SearchItemType();

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);				
			}
		}
		break;
	case 5:
		{
			ShowUserInfo(SW_HIDE);
			ShowItemInfo(SW_HIDE);
			ShowNewItem(SW_HIDE);
			ShowMoneyInfo(SW_SHOW);

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);
			}
		}
		break;
	default:
		{				
			ShowUserInfo(SW_HIDE);
			ShowNewItem(SW_HIDE);
			ShowItemInfo(SW_SHOW);

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				ItemInfo();
			}	
		}
		break;
	}
	*pResult = 0;
}

// 查询角色道具信息
void CXDItemManage::ItemInfo()
{	
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名
			
			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			if(tbcResult.GetCurSel()==1)
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemBody_Query);//身上物品信息
			else if(tbcResult.GetCurSel()==2)	
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Itembackpack_Query);//背包物品信息
			else if(tbcResult.GetCurSel()==3)	
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemStorage_Query);//仓库物品信息

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_ResultInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

// 翻页进行查询
void CXDItemManage::OnCbnSelchangeCmbuipage()
{	
	try
	{
		if(pageInfo)
		{
			CIni mIni;

			int index = cmbPage.GetCurSel() + 1;
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

			while(listResult.DeleteColumn(0)){}

			if((listUser.GetItemCount() > 0) && (nItem>=0))
			{
				CSocketData socketdata;
				socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名
				
				_itoa(index,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

				_itoa(iPageSize,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

				int midlength = socketdata.EnBody();
				if(tbcResult.GetCurSel()==1)
					theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemBody_Query);//身上物品信息
				else if(tbcResult.GetCurSel()==2)	
					theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Itembackpack_Query);//背包物品信息
				else if(tbcResult.GetCurSel()==3)	
					theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemStorage_Query);//仓库物品信息

				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
				socketdata.Destroy();
			}
		}		
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_ResultInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

//选择相应的道具信息进行删除
void CXDItemManage::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listResult.GetItemCount() != 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nListItem = listResult.SubItemHitTest(&lvinfo);//保存在玩家技能信息列表中选中的行号

		if(nListItem >= 0)
		{			
			ItemName = theApp.operXD.GetValueByColName(&listResult, nListItem, theApp.operXD.ReadValue("MXD","XDJG_ItemName"));// 保存选中的道具名称
			SetDlgItemText(IDC_EDITITEM,ItemName);
		}
	}
	else
	{
		nListItem = -1;
	}
	*pResult = 0;
}

//删除选中的道具信息
void CXDItemManage::OnBnClickedBtndelitem()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listResult.GetItemCount() > 0) && (nListItem>=0))
		{		
			GetDlgItemText(IDC_EDITITEM,ItemName);//获取道具名称
			if(ItemName == "")//要删除的道具名称不能为空
			{
				MessageBox(theApp.operXD.ReadValue("MXD","IM_HINT_DELETEITEM"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			int ItemIndex = atoi(theApp.operXD.GetValueByColName(&listResult, nListItem, theApp.operXD.ReadValue("MXD","XDJG_ItemID")));// 保存选中的道具序号

			int ItemNum = -1;
			ItemNum = GetDlgItemInt(IDC_EDITDELNUM);

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名
			
			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员id

			_itoa(tbcResult.GetCurSel()-1,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//类型：0、身上；1、背包；2、银行

			_itoa(ItemIndex,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//道具索引

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//道具名称

			_itoa(ItemNum,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemNum,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//要删除的道具数量

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemDel);//删除道具信息

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","IM_Error_DELETEITEM"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//选择是否批量添加道具
void CXDItemManage::OnBnClickedCheckselect()
{
	if(checkSelect.GetCheck()==1)
	{
		checkGroup.SetCheck(0);

		GetDlgItem(IDC_EDITPATH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNBROWSE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLNICK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITNICK)->ShowWindow(SW_HIDE);

		SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","IM_UI_LBLPATH"));
		multStatus=1;
	}
	else
	{
		GetDlgItem(IDC_EDITPATH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNBROWSE)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLNICK)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITNICK)->ShowWindow(SW_SHOW);

		SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
		multStatus=0;
	}
}

//选择是否需要群发道具
void CXDItemManage::OnBnClickedCheckgroup()
{
	if(checkGroup.GetCheck()==1)
	{
		checkSelect.SetCheck(0);

		GetDlgItem(IDC_EDITPATH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNBROWSE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLNICK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITNICK)->ShowWindow(SW_HIDE);

		multStatus=2;
	}
	else
	{
		GetDlgItem(IDC_EDITPATH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNBROWSE)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLNICK)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITNICK)->ShowWindow(SW_SHOW);

		SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
		multStatus=0;
	}
}

//选择批量添加道具的角色文件名
void CXDItemManage::OnBnClickedBtnbrowse()
{
	char path[256];
	GetCurrentDirectory(256,path);
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象

	lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,"文件类型(*.txt)|*.txt||");

	if(lpszOpenFile->DoModal()==IDOK)//假如点击对话框确定按钮
	{
		CString szGetName;
		szGetName=lpszOpenFile->GetPathName();
		SetDlgItemText(IDC_EDITPATH,szGetName);
		SetCurrentDirectory(path);
	}
	delete lpszOpenFile;
}

//查询道具类型信息
void CXDItemManage::SearchItemType()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名
		
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的条数

		int midlength = socketdata.EnBody();
		theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemType_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","IM_Error_SearchItemType"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//查询相应类型的道具信息
void CXDItemManage::OnBnClickedBtnitemlist()
{
	try
	{
		CIni mIni;

		//int index = theApp.operXD.ReadIntValue("MXD","index");
		//int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");
		cmbList.ResetContent();

		CString ItemType;
		GetDlgItemText(IDC_CMBTYPE,ItemType);//获取道具类型
		if(ItemType == "")//道具类型不能为空
		{
			MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ItemTypeNull"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		ItemName="";
		GetDlgItemText(IDC_EDITNEW,ItemName);//获取模糊道具名
		
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名
		
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemType,CEnumCore::TagFormat::TLV_STRING,strlen(ItemType),(unsigned char *)mIni.wcharToChar(ItemType));//道具类型
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//模糊道具名

		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的条数

		int midlength = socketdata.EnBody();
		theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemNameLst_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","IM_Error_SearchItemName"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//向道具列表中添加道具
void CXDItemManage::OnBnClickedBtnadd()
{
	try
	{
		CString ItemName = "";		
		GetDlgItemText(IDC_CMBITEM,ItemName);//获取道具名称
		if(ItemName == "")//道具名称不能为空
		{
			MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ItemNameNull"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ItemList.Lookup(cmbList.GetCurSel()+1,ItemID);//从CMap类的对象ItemList中获取道具ID

		//CString ItemQuality = "";
		//GetDlgItemText(IDC_CMBQUALITY,ItemQuality);//获取道具品质

		int itemNum = GetDlgItemInt(IDC_EDITITEMNUM);
		if(itemNum == 0)
		{
			MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ItemNumNull"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		/*if(itemNum>5)
		{
			MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ItemNum"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}*/

		CString ATTRID = "";
		GetDlgItemText(IDC_EDITATTRID,ATTRID);//附加属性ID
		CString ATTRVALUE = "";
		GetDlgItemText(IDC_EDITATTRVALUE,ATTRVALUE);//附加属性值
		CString ADDLEVEL = "";
		GetDlgItemText(IDC_EDITADDLEVEL,ADDLEVEL);//增幅等级
		CString ADDTYPE = "";
		GetDlgItemText(IDC_EDITADDTYPE,ADDTYPE);//增幅属性
		CString ADDVALUE = "";
		GetDlgItemText(IDC_EDITADDVALUE,ADDVALUE);//增幅值
		CString ADDVALUELAST = "";
		GetDlgItemText(IDC_EDITADDLEVEL,ADDVALUELAST);//上次增幅值
		CString STAR = "";
		GetDlgItemText(IDC_EDITSTAR,STAR);//星数
		CString PLUGIN = "";
		GetDlgItemText(IDC_EDITPLUGIN,PLUGIN);//组装ID
		CString SLOTNUM = "";
		GetDlgItemText(IDC_EDITSLOTNUM,SLOTNUM);//插孔数量
		CString SLOT1 = "";
		GetDlgItemText(IDC_EDITSLOT1,SLOT1);//插孔1
		CString SLOT2 = "";
		GetDlgItemText(IDC_EDITSLOT2,SLOT2);//插孔2
		CString SLOT3 = "";
		GetDlgItemText(IDC_EDITSLOT3,SLOT3);//插孔3
		CString APTITUDE = "";
		GetDlgItemText(IDC_EDITAPTITUDE,APTITUDE);//资质
		CString BIND = "";
		GetDlgItemText(IDC_EDITBIND,BIND);//绑定

		int nRow = 0;
		char strInt[10];
		ZeroMemory(strInt,10);
		if(nFirst == 0)
		{
			nFirst = 1;

			DWORD dwStyle = listItem.GetExtendedStyle();
			dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
			listItem.SetExtendedStyle(dwStyle); //设置扩展风格

			listItem.InsertColumn(0,theApp.operXD.ReadValue("MXD","IM_ITEM_ITEMID"),LVCFMT_CENTER,65,-1);
			listItem.InsertColumn(1,theApp.operXD.ReadValue("MXD","IM_ITEM_ITEMNAME"),LVCFMT_CENTER,120,-1);
		    listItem.InsertColumn(2,theApp.operXD.ReadValue("MXD","IM_ITEM_ITEMNUM"),LVCFMT_CENTER,65,-1);
			//listItem.InsertColumn(3,theApp.operXD.ReadValue("MXD","IM_ITEM_ITEMQULITY"),LVCFMT_CENTER,80,-1);
			listItem.InsertColumn(3,theApp.operXD.ReadValue("MXD","IM_UI_ATTRID"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(4,theApp.operXD.ReadValue("MXD","IM_UI_ATTRVALUE"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(5,theApp.operXD.ReadValue("MXD","IM_UI_ADDLEVEL"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(6,theApp.operXD.ReadValue("MXD","IM_UI_ADDTYPE"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(7,theApp.operXD.ReadValue("MXD","IM_UI_ADDVALUE"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(8,theApp.operXD.ReadValue("MXD","IM_UI_ADDVALUELAST"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(9,theApp.operXD.ReadValue("MXD","IM_UI_STAR"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(10,theApp.operXD.ReadValue("MXD","IM_UI_PLUGIN"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(11,theApp.operXD.ReadValue("MXD","IM_UI_SLOTNUM"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(12,theApp.operXD.ReadValue("MXD","IM_UI_SLOT1"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(13,theApp.operXD.ReadValue("MXD","IM_UI_SLOT2"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(14,theApp.operXD.ReadValue("MXD","IM_UI_SLOT3"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(15,theApp.operXD.ReadValue("MXD","IM_UI_APTITUDE"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(16,theApp.operXD.ReadValue("MXD","IM_UI_BIND"),LVCFMT_CENTER,40,-1);

			nRow=listItem.InsertItem(0,ItemID);
			listItem.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItem.SetItemText(nRow,2,strInt);			
			//listItem.SetItemText(nRow,3,ItemQuality);
			listItem.SetItemText(nRow,3,ATTRID);
			listItem.SetItemText(nRow,4,ATTRVALUE);
			listItem.SetItemText(nRow,5,ADDLEVEL);
			listItem.SetItemText(nRow,6,ADDTYPE);
			listItem.SetItemText(nRow,7,ADDVALUE);
			listItem.SetItemText(nRow,8,ADDVALUELAST);
			listItem.SetItemText(nRow,9,STAR);
			listItem.SetItemText(nRow,10,PLUGIN);
			listItem.SetItemText(nRow,11,SLOTNUM);
			listItem.SetItemText(nRow,12,SLOT1);
			listItem.SetItemText(nRow,13,SLOT2);
			listItem.SetItemText(nRow,14,SLOT3);
			listItem.SetItemText(nRow,15,APTITUDE);
			listItem.SetItemText(nRow,16,BIND);
		}
		else
		{
			/*int itemCount = 0;
			for(int i=0;i<listItem.GetItemCount();i++)
			{
				itemCount += atoi((LPCSTR)mIni.wcharToChar(listItem.GetItemText(i,2)));
			}
			if((itemCount + itemNum)>5)
			{
				MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ItemNum"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}*/
			int itemCount = listItem.GetItemCount();
			if(itemCount >= 5)
			{
				MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ItemType"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			nRow=listItem.InsertItem(0,ItemID);
			listItem.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItem.SetItemText(nRow,2,strInt);
			//listItem.SetItemText(nRow,3,ItemQuality);
			listItem.SetItemText(nRow,3,ATTRID);
			listItem.SetItemText(nRow,4,ATTRVALUE);
			listItem.SetItemText(nRow,5,ADDLEVEL);
			listItem.SetItemText(nRow,6,ADDTYPE);
			listItem.SetItemText(nRow,7,ADDVALUE);
			listItem.SetItemText(nRow,8,ADDVALUELAST);
			listItem.SetItemText(nRow,9,STAR);
			listItem.SetItemText(nRow,10,PLUGIN);
			listItem.SetItemText(nRow,11,SLOTNUM);
			listItem.SetItemText(nRow,12,SLOT1);
			listItem.SetItemText(nRow,13,SLOT2);
			listItem.SetItemText(nRow,14,SLOT3);
			listItem.SetItemText(nRow,15,APTITUDE);
			listItem.SetItemText(nRow,16,BIND);
		}
	}
	catch(...)
	{
	}
}

//单击道具列表保存行号
void CXDItemManage::OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listItem.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nSelectItem = listItem.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号
	}
	else
	{
		nSelectItem = 0;
	}
	*pResult = 0;
}

//双击道具列表进行删除
void CXDItemManage::OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listItem.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nSelectItem = listItem.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

		if(nSelectItem >= 0)
		{
			listItem.DeleteItem(nSelectItem);
		}
	}
	else
	{
		nSelectItem = 0;
	}
	*pResult = 0;
}

//从道具列表中进行删除
void CXDItemManage::OnBnClickedBtndelete()
{
	if((listItem.GetItemCount() != 0) && (nSelectItem >= 0))
	{
		listItem.DeleteItem(nSelectItem);
	}
}

//修改或添加信息
void CXDItemManage::OnBnClickedBtnedit()
{
	switch(tbcResult.GetCurSel())
	{
	case 4:
		//{
		//	nItemCount = listItem.GetItemCount();
		//	if(nItemCount == 0)
		//	{
		//		MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ItemNumNull"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
		//		return;
		//	}
		//	nSelectItem=0;
		//	AddItem();
		//}
		{
			nSelectItem=0;
			if(multStatus > 0) 
			{
				CString m_ServerName;
				GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//获取游戏服务器的名称
				if(m_ServerName == "")//游戏服务器为空
				{
					return;
				}
				ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
			}
			if(multStatus == 1) 
			{
				//读取要批量添加的角色名txt文件				
				CString filename="";				
				GetDlgItemText(IDC_EDITPATH,filename);	

				CStdioFile nFile;
				if(!nFile.Open(filename,CFile::typeBinary))
				{
					MessageBox(theApp.operXD.ReadValue("MXD","IM_Error_ReadFile"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}				
				UserNum = 0;
				UserNick = "";
				nFile.ReadString(UserNick);
				while(nFile.ReadString(UserNick) != false && UserNick.GetLength() != 0)
				{
					UserNick = UserNick.TrimLeft();
					UserNick = UserNick.TrimRight();
					UserNum++;
					UserList.SetAt(UserNum,UserNick);//将角色名保存在CMap类的对象UserList中
				}
				nFile.Close();

				if(UserNum == 0)
					return;

				ShowNewItem(SW_HIDE);				
				GetDlgItem(IDUISEARCH)->ShowWindow(SW_HIDE);
				GetDlgItem(IDUICANCEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TABUIRESULT)->ShowWindow(SW_HIDE);

				multStatus=1;
				GetDlgItem(IDC_BTNRECOVER)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_LBLMAIN)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_PROGRESSMAIL)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LBLPROG)->ShowWindow(SW_SHOW);
				
				CString tmpNum = "";
				tmpNum.Format("%i",UserNum);
				SetDlgItemText(IDC_LBLMAIN,theApp.operXD.ReadValue("MXD","IM_UI_LblMain")+tmpNum);
				SetDlgItemText(IDC_LBLPROG,"");	

				progMail.SetPos(0);
				progMail.SetRange(0,UserNum);
				progMail.SetStep(1);

				mCurNum = 1;
				UserNick = "";
				UserList.Lookup(mCurNum,UserNick);//从CMap类的对象UserList中获取角色名
				AddItem();
			}
			else
			{
				UserNick = "";
				if(multStatus==0)//给指定玩家添加道具
				{
					GetDlgItemText(IDC_EDITNICK,UserNick);//获取角色名
					if(UserNick == "")
					{
						MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_RoleNameNull"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
						return;
					}
				}
				AddItem();
			}
		}
		break;
	case 5:
		EditMoney();
		break;
	default:
		break;
	}	
}

//添加新道具
void CXDItemManage::AddItem()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		CString SenderNick = "";
		GetDlgItemText(IDC_EDITSENDER,SenderNick);
		
		///////////////////取邮件内容///////////////////////

		CString m_strSubject;
		GetDlgItemText(IDC_EDMAILSUBJECT2,m_strSubject);
		//if(m_strSubject == "")
		//{
		//	MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_MailSubject"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
		//	return;
		//}
		//if(strlen(m_strSubject) > 20)//邮件标题不能超过20个字符
		//{
		//	MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_SubjectTooLong"),theApp.operXD.ReadValue("MXD","Warn"),0);
		//	return;
		//}

		CString m_strContent;
		GetDlgItemText(IDC_EDMAILCONTENT2,m_strContent);
		//if(m_strContent == "")
		//{
		//	MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_MailContent"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
		//	return;
		//}
		//if(strlen(m_strContent) > 200)//邮件内容不能超过200个字符
		//{
		//	MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ContentTooLong"),theApp.operXD.ReadValue("MXD","Warn"),0);
		//	return;
		//}

		int iMoney=0;
		iMoney=GetDlgItemInt(IDC_EDMAILMONEY);

		int itemCount = listItem.GetItemCount();//要添加道具的行数
		if(itemCount == 0)//要添加的道具不能为空
		{
			MessageBox(theApp.operXD.ReadValue("MXD","IM_HINT_ADDITEM"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		ItemID="";
		ItemName="";
		CString ItemNum="";
		//CString ItemQuality="";
		CString ATTRID = "";
		CString ATTRVALUE = "";
		CString ADDLEVEL = "";
		CString ADDTYPE = "";
		CString ADDVALUE = "";
		CString ADDVALUELAST = "";
		CString STAR = "";
		CString PLUGIN = "";
		CString SLOTNUM = "";
		CString SLOT1 = "";
		CString SLOT2 = "";
		CString SLOT3 = "";
		CString APTITUDE = "";
		CString BIND = "";

		for(int i=0;i<itemCount;i++)
		{
			ItemID += listItem.GetItemText(i,0);
			ItemID += ";";
			ItemName += listItem.GetItemText(i,1);
			ItemName += ";";
			ItemNum += listItem.GetItemText(i,2);
			ItemNum += ";";
			ATTRID += listItem.GetItemText(i,3);
			ATTRID += ";";
			ATTRVALUE += listItem.GetItemText(i,4);
			ATTRVALUE += ";";
			ADDLEVEL += listItem.GetItemText(i,5);
			ADDLEVEL += ";";
			ADDTYPE += listItem.GetItemText(i,6);
			ADDTYPE += ";";
			ADDVALUE += listItem.GetItemText(i,7);
			ADDVALUE += ";";
			ADDVALUELAST += listItem.GetItemText(i,8);
			ADDVALUELAST += ";";
			STAR += listItem.GetItemText(i,9);
			STAR += ";";
			PLUGIN += listItem.GetItemText(i,10);
			PLUGIN += ";";
			SLOTNUM += listItem.GetItemText(i,11);
			SLOTNUM += ";";
			SLOT1 += listItem.GetItemText(i,12);
			SLOT1 += ";";
			SLOT2 += listItem.GetItemText(i,13);
			SLOT2 += ";";
			SLOT3 += listItem.GetItemText(i,14);
			SLOT3 += ";";
			APTITUDE += listItem.GetItemText(i,15);
			APTITUDE += ";";
			BIND += listItem.GetItemText(i,16);
			BIND += ";";
			//if(listItem.GetItemText(i,3) == theApp.operXD.ReadValue("MXD","IM_UI_WHITE"))
			//{
			//	ItemQuality += "0;";
			//}
			//else if(listItem.GetItemText(i,3) == theApp.operXD.ReadValue("MXD","IM_UI_BLUE"))
			//{
			//	ItemQuality += "1;";
			//}
			//else if(listItem.GetItemText(i,3) == theApp.operXD.ReadValue("MXD","IM_UI_PURPLE"))
			//{
			//	ItemQuality += "2;";
			//}
			//else if(listItem.GetItemText(i,3) == theApp.operXD.ReadValue("MXD","IM_UI_ORANGE"))
			//{
			//	ItemQuality += "3;";
			//}
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,30);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名
		
		int userbyID = theApp.UserByID;
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员id

		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的条数

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemID,CEnumCore::TagFormat::TLV_STRING,strlen(ItemID),(unsigned char *)mIni.wcharToChar(ItemID));//道具ID
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//道具名称
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemNum,CEnumCore::TagFormat::TLV_STRING,strlen(ItemNum),(unsigned char *)mIni.wcharToChar(ItemNum));//道具数量

		//if(multStatus == 2)
		//	_itoa(1,strInt,10);//群发邮件
		//else
		//	_itoa(0,strInt,10);//给指定玩家发送邮件
		//socketdata.AddTFLV(CEnumCore::TagName::WA_MailTag,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//是否群发邮件
		//socketdata.AddTFLV(CEnumCore::TagName::WA_ItemGen,CEnumCore::TagFormat::TLV_STRING,strlen(ItemQuality),(unsigned char *)mIni.wcharToChar(ItemQuality));//道具品质

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_SendCharacter,CEnumCore::TagFormat::TLV_STRING,strlen(SenderNick),(unsigned char *)mIni.wcharToChar(SenderNick));//发件人昵称
		
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_MailTitle,CEnumCore::TagFormat::TLV_STRING,strlen(m_strSubject),(unsigned char *)mIni.wcharToChar(m_strSubject));//邮件主题
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_MailContent,CEnumCore::TagFormat::TLV_STRING,strlen(m_strContent),(unsigned char *)mIni.wcharToChar(m_strContent));//邮件内容
		
		_itoa(iMoney,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Money,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//发送金钱

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_PropertyId,CEnumCore::TagFormat::TLV_STRING,strlen(ATTRID),(unsigned char *)mIni.wcharToChar(ATTRID));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_PropertyValue,CEnumCore::TagFormat::TLV_STRING,strlen(ATTRVALUE),(unsigned char *)mIni.wcharToChar(ATTRVALUE));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_IncreaseNum,CEnumCore::TagFormat::TLV_STRING,strlen(ADDLEVEL),(unsigned char *)mIni.wcharToChar(ADDLEVEL));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_IncreaseType,CEnumCore::TagFormat::TLV_STRING,strlen(ADDTYPE),(unsigned char *)mIni.wcharToChar(ADDTYPE));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_IncreaseValue,CEnumCore::TagFormat::TLV_STRING,strlen(ADDVALUE),(unsigned char *)mIni.wcharToChar(ADDVALUE));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_IncreaseEndValue,CEnumCore::TagFormat::TLV_STRING,strlen(ADDVALUELAST),(unsigned char *)mIni.wcharToChar(ADDVALUELAST));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_StarsLevel,CEnumCore::TagFormat::TLV_STRING,strlen(STAR),(unsigned char *)mIni.wcharToChar(STAR));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_AssemblyID,CEnumCore::TagFormat::TLV_STRING,strlen(PLUGIN),(unsigned char *)mIni.wcharToChar(PLUGIN));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_SlotNum,CEnumCore::TagFormat::TLV_STRING,strlen(SLOTNUM),(unsigned char *)mIni.wcharToChar(SLOTNUM));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_EquipSlotID1,CEnumCore::TagFormat::TLV_STRING,strlen(SLOT1),(unsigned char *)mIni.wcharToChar(SLOT1));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_EquipSlotID2,CEnumCore::TagFormat::TLV_STRING,strlen(SLOT2),(unsigned char *)mIni.wcharToChar(SLOT2));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_EquipSlotID3,CEnumCore::TagFormat::TLV_STRING,strlen(SLOT3),(unsigned char *)mIni.wcharToChar(SLOT3));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_QualityEquip,CEnumCore::TagFormat::TLV_STRING,strlen(APTITUDE),(unsigned char *)mIni.wcharToChar(APTITUDE));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_IsBind,CEnumCore::TagFormat::TLV_STRING,strlen(BIND),(unsigned char *)mIni.wcharToChar(BIND));		

		int midlength = socketdata.EnBody();
		theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemAdd);//添加新道具

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_AddItem"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

//修改金钱数量
void CXDItemManage::EditMoney()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CString newMoney;
			GetDlgItemText(IDC_EDITNEW,newMoney);//修改后的金钱数量
			if(newMoney == "")//修改后的金钱数量不能为空
			{
				MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_MoneyNum"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名
			
			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员id

			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的条数

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Money,CEnumCore::TagFormat::TLV_STRING,strlen(newMoney),(unsigned char *)mIni.wcharToChar(newMoney));//金钱数量

			int midlength = socketdata.EnBody();
			if(cmbType.GetCurSel() == 0)
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_AddRoleBind_operate);//添加角色身上金钱数量(绑定币)
			else if(cmbType.GetCurSel() == 1)
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_AddRoleNonBind_operate);//添加角色身上金钱数量(非绑定币)
			else if(cmbType.GetCurSel() == 2)
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_UpRoleBind_operate);//修改角色身上金钱数量(绑定币)
			else if(cmbType.GetCurSel() == 3)
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_UpRoleNonBind_operate);//修改角色身上金钱数量(非绑定币)
			else if(cmbType.GetCurSel() == 4)
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_MoneyAdd);//添加游戏币
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_EditMoney"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

//重置信息
void CXDItemManage::OnBnClickedBtnrecover()
{
	listItem.DeleteAllItems();
	while(listItem.DeleteColumn(0)){}
	nFirst = 0;
	SetDlgItemText(IDC_EDITNEW,"");
	cmbQuality.SetCurSel(0);
	SetDlgItemText(IDC_EDITITEMNUM,"1");
	//SetDlgItemText(IDC_EDITTIME,"0");
	SetDlgItemText(IDC_EDMAILSUBJECT2,"");
	SetDlgItemText(IDC_EDMAILCONTENT2,"");
	SetDlgItemText(IDC_EDMAILMONEY,"0");

	mCurNum = UserNum;
	progMail.SetPos(mCurNum-1);
}

// 接收返回信息
LRESULT CXDItemManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;

	dlgStatus = theApp.operXD.ReadIntValue("MXD","Receive");//当前的状态为接收到了返回信息

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
			theApp.operXD.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_Account_Query_Resp://查询玩家资料信息的回应
		{
			if(pageUInfo)//如果已经能够翻页
			{
				theApp.operXD.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operXD.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象

				if(pageCount<0)//页数<=0，说明没有数据返回
				{
					nItem = -1;//不能选中某一行
					pageUInfo = false;//不能翻页					
					cmbUPage.ResetContent();//清空页数复选框
					while(listUser.DeleteColumn(0)){}//清空CListCtrl内容
				}
				else
				{
					nItem = 0;
					cmbUPage.ResetContent();//清空页数复选框，以便重新构造
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbUPage.AddString(str);//在复选框中构造页数信息
					}
					cmbUPage.SetCurSel(0);//在复选框中选中第一页
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
	case CEnumCore::Message_Tag_ID::XDJG_ItemType_Query_Resp://查询道具类型信息
		{
			theApp.operXD.BuildCombox(&socketdata,&cmbType,1);//构造道具类型信息
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ItemNameLst_Query_Resp://查询所有的道具信息
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ItemID = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::XDJG_ItemID).lpdata;//得到道具ID
				ItemList.SetAt(i,ItemID);//将道具ID保存在CMap类的对象ItemList中
			}
			theApp.operXD.BuildComboxs(&socketdata,&cmbList,CEnumCore::TagName::XDJG_ItemName);//构造道具信息
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ItemAdd_Resp://添加道具信息
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString Result = (LPCTSTR)&m_tflv.lpdata;
			if(multStatus == 1) 
			{
				CString tmpNum="";
				if(mCurNum<UserNum)
				{					
					tmpNum.Format("%i",mCurNum);
					SetDlgItemText(IDC_LBLPROG,theApp.operXD.ReadValue("MXD","IM_UI_LblMailFirst")+tmpNum+theApp.operXD.ReadValue("MXD","IM_UI_LblMailSecond")+UserNick+theApp.operXD.ReadValue("MXD","IM_UI_LblMailThird")+Result+theApp.operXD.ReadValue("MXD","IM_UI_LblMailFourth"));	
					progMail.StepIt();

					mCurNum++;
					UserList.Lookup(mCurNum,UserNick);//从CMap类的对象UserList中获取角色名					

					AddItem();
					return false;					
				}
				if(!UserList.IsEmpty())
				{
					UserList.RemoveAll();
				}
				tmpNum.Format("%i",mCurNum);
				SetDlgItemText(IDC_LBLPROG,theApp.operXD.ReadValue("MXD","IM_UI_LblMailFirst")+tmpNum+theApp.operXD.ReadValue("MXD","IM_UI_LblMailSecond")+UserNick+theApp.operXD.ReadValue("MXD","IM_UI_LblMailThird")+Result+theApp.operXD.ReadValue("MXD","IM_UI_LblMailFourth"));	
				progMail.StepIt();

				theApp.operXD.ShowResult(Result);//显示返回结果
				OnBnClickedBtnrecover();

				GetDlgItem(IDC_LBLMAIN)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_PROGRESSMAIL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLPROG)->ShowWindow(SW_HIDE);

				ShowNewItem(SW_SHOW);
				checkSelect.SetCheck(0);
				checkGroup.SetCheck(0);				
				multStatus=0;

				GetDlgItem(IDC_TABUIRESULT)->ShowWindow(SW_SHOW);
				GetDlgItem(IDUISEARCH)->ShowWindow(SW_SHOW);
				GetDlgItem(IDUICANCEL)->ShowWindow(SW_SHOW);
			}
			else
			{
				theApp.operXD.ShowResult(Result);//显示返回结果
				OnBnClickedBtnrecover();
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ItemDel_Resp://道具删除
	case CEnumCore::Message_Tag_ID::XDJG_MoneyAdd_Resp://添加游戏币
	case CEnumCore::Message_Tag_ID::XDJG_AddRoleBind_operate_Resp://添加角色身上金钱数量(绑定币)
	case CEnumCore::Message_Tag_ID::XDJG_AddRoleNonBind_operate_Resp://添加角色身上金钱数量(非绑定币)
	case CEnumCore::Message_Tag_ID::XDJG_UpRoleBind_operate_Resp://修改角色身上金钱数量(绑定币)
	case CEnumCore::Message_Tag_ID::XDJG_UpRoleNonBind_operate_Resp://修改角色身上金钱数量(非绑定币)
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operXD.ShowResult(result);//显示返回结果
		}
		break;
	default:
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operXD.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operXD.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

				if(pageCount<0)//页数<=0，说明没有数据返回
				{
					pageInfo = false;//不能翻页		
					cmbPage.ResetContent();
					while(listResult.DeleteColumn(0)){}
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
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

//单击用户资料信息的列名进行排序
void CXDItemManage::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operXD.SortListInfo(&listUser,pNMHDR,pResult);
}

//单击结果信息的列名进行排序
void CXDItemManage::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operXD.SortListInfo(&listResult,pNMHDR,pResult);
}

// 关闭对话框
void CXDItemManage::OnBnClickedUicancel()
{
	ShowItemInfo(SW_HIDE);
	ShowNewItem(SW_HIDE);		
	ShowUserInfo(SW_SHOW);

	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// 关闭对话框
void CXDItemManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!ItemList.IsEmpty())
	{
		ItemList.RemoveAll();
	}
	if(!UserList.IsEmpty())
	{
		UserList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//处理快捷键响应函数
BOOL CXDItemManage::PreTranslateMessage(MSG* pMsg)
{
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

void CXDItemManage::ShowUserInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(m_cmdShow);
}

void CXDItemManage::ShowItemInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLDELNUM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITDELNUM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNDELITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_EDITITEM,"");
	SetDlgItemText(IDC_EDITDELNUM,"1");
}

void CXDItemManage::ShowNewItem(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operXD.ReadValue("MXD","IM_UI_lblItemType"));
	SetDlgItemText(IDC_LBLNEW,theApp.operXD.ReadValue("MXD","IM_UI_lblBIItem"));
	SetDlgItemText(IDC_LBLITEMNAME,theApp.operXD.ReadValue("MXD","IM_UI_lblItemInfo"));	
	SetDlgItemText(IDC_LBLTOADDITEM,theApp.operXD.ReadValue("MXD","IM_UI_lblItemList"));
	SetDlgItemText(IDC_BTNITEMLIST,theApp.operXD.ReadValue("MXD","IM_UI_btnItemList"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","IM_UI_BTNSEND"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","Reset"));

	SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITNEW,"");

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLOLD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLITEMNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNUM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITITEMNUM)->ShowWindow(m_cmdShow);
	CEditNew.ModifyStyle(ES_NUMBER,0);
	SetDlgItemText(IDC_EDITITEMNUM,"1");

	GetDlgItem(IDC_LBLSENDER)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSENDER)->ShowWindow(m_cmdShow);
	SetDlgItemText(IDC_EDITSENDER,theApp.operXD.ReadValue("MXD","IM_UI_SysMail"));
	//GetDlgItem(IDC_LBLQUALITY)->ShowWindow(m_cmdShow);
	//GetDlgItem(IDC_CMBQUALITY)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMAILSUBJECT2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILSUBJECT2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMAILCONTENT2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILCONTENT2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMAILMONEY)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILMONEY)->ShowWindow(m_cmdShow);	
	SetDlgItemText(IDC_EDMAILMONEY,"0");

	GetDlgItem(IDC_LBLATTRID)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLATTRVALUE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLADDLEVEL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLADDTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLADDVALUE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLADDVALUELAST)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSTAR)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPLUGIN)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSLOTNUM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSLOT1)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSLOT2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSLOT3)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLAPTITUDE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLBIND)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_EDITATTRID)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITATTRVALUE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITADDLEVEL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITADDTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITADDVALUE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITADDVALUELAST)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSTAR)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITPLUGIN)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSLOTNUM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSLOT1)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSLOT2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSLOT3)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITAPTITUDE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITBIND)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_EDITPATH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKBATCH)->ShowWindow(m_cmdShow);
	//GetDlgItem(IDC_CHECKGROUP)->ShowWindow(m_cmdShow);
	multStatus=0;

	GetDlgItem(IDC_LBLTOADDITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNADD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNDELETE)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_BTNITEMLIST)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

//给新道具页面的相关参数赋值
void CXDItemManage::NewItemValue()
{
	cmbType.ResetContent();
	cmbList.ResetContent();

	checkSelect.SetCheck(0);
	checkGroup.SetCheck(0);
}	

void CXDItemManage::ShowMoneyInfo(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operXD.ReadValue("MXD","UM_UI_Type"));
	SetDlgItemText(IDC_LBLNEW,theApp.operXD.ReadValue("MXD","IM_UI_NewValue"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","Modify"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","Reset"));

	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITNEW,"");
	cmbType.ResetContent();
	cmbType.AddString(theApp.operXD.ReadValue("MXD","IM_UI_ADDBIND"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","IM_UI_ADDNONBIND"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","IM_UI_EDITBIND"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","IM_UI_EDITNONBIND"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","IM_UI_PLAYMONEY"));
	cmbType.SetCurSel(0);

	CEditNew.ModifyStyle(0,ES_NUMBER);
	
	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLOLD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

