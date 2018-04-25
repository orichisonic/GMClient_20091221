// PALItemManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_PAL.h"
#include "PALItemManage.h"
#include ".\palitemmanage.h"


// CPALItemManage 对话框

IMPLEMENT_DYNAMIC(CPALItemManage, CDialog)
CPALItemManage::CPALItemManage(CWnd* pParent /*=NULL*/)
	: CDialog(CPALItemManage::IDD, pParent)
{
}

CPALItemManage::~CPALItemManage()
{
}

void CPALItemManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_CMBBIGTYPE, cmbType);
	DDX_Control(pDX, IDC_CMBSMALLTYPE, cmbName);
	DDX_Control(pDX, IDC_LISTITEM, listItem);
}


BEGIN_MESSAGE_MAP(CPALItemManage, CDialog)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_BN_CLICKED(IDC_BTNSEND, OnBnClickedBtnsend)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_CBN_SELCHANGE(IDC_CMBBIGTYPE, OnCbnSelchangeCmbbigtype)
	ON_BN_CLICKED(IDC_BTNADD, OnBnClickedBtnadd)
	ON_NOTIFY(NM_CLICK, IDC_LISTITEM, OnNMClickListitem)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTITEM, OnNMDblclkListitem)
	ON_BN_CLICKED(IDC_BTNDELETE, OnBnClickedBtndelete)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
END_MESSAGE_MAP()


// 初始化对话框
BOOL CPALItemManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// 初始化显示字符

	nItem = 0;
	nSelectItem = 0;
	pageInfo = false;
	ServerIP = "";
	UserAccount = "";
	UserName = "";//初始化一些私有变量

	ShowUserInfo();//显示用户资料信息

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
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Create");//当前的状态为初始建立对话框

	if(theApp.operPAL.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
	}

	return TRUE;
}

// 初始化显示字符
void CPALItemManage::InitUI()
{
	//OperationPAL operPAL;

	SetWindowText(theApp.operPAL.ReadValue("MPAL","IM_UI_ITEMMANAGE"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operPAL.ReadValue("MPAL","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operPAL.ReadValue("MPAL","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblRole"));
	SetDlgItemText(IDSEARCH,theApp.operPAL.ReadValue("MPAL","Search"));
	SetDlgItemText(IDCANCEL,theApp.operPAL.ReadValue("MPAL","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operPAL.ReadValue("MPAL","UIC_UI_Page"));
	SetDlgItemText(IDC_LBLBAGTYPE,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblBAGTYPE"));

	SetDlgItemText(IDC_LBLADDNAME,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblRole"));
	SetDlgItemText(IDC_LBLBIGTYPE,theApp.operPAL.ReadValue("MPAL","IM_UI_lblItemType"));
	SetDlgItemText(IDC_LBLSMALLTYPE,theApp.operPAL.ReadValue("MPAL","IM_UI_lblItemName"));
	SetDlgItemText(IDC_LBLITEMNUM,theApp.operPAL.ReadValue("MPAL","IM_UI_lblItemNum"));
	SetDlgItemText(IDC_LBLMAILMONEY,theApp.operPAL.ReadValue("MPAL","IM_UI_LBLMAILMONEY"));
	SetDlgItemText(IDC_LBLTOADDITEM,theApp.operPAL.ReadValue("MPAL","IM_UI_lblItemList"));
	SetDlgItemText(IDC_LBLMAILSUBJECT,theApp.operPAL.ReadValue("MPAL","IM_UI_LBLMAILSUBJECT"));
	SetDlgItemText(IDC_LBLMAILCONTENT,theApp.operPAL.ReadValue("MPAL","IM_UI_LBLMAILCONTENT"));
	SetDlgItemText(IDC_LBLMAILREASON,theApp.operPAL.ReadValue("MPAL","IM_UI_LBLMAILREASON"));
	SetDlgItemText(IDC_BTNSEND,theApp.operPAL.ReadValue("MPAL","IM_UI_BTNSEND"));
	SetDlgItemText(IDC_BTNRESET,theApp.operPAL.ReadValue("MPAL","RESET"));

	tbcResult.InsertItem(0,theApp.operPAL.ReadValue("MPAL","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operPAL.ReadValue("MPAL","UIC_ITEM_tpgBody"));
	tbcResult.InsertItem(2,theApp.operPAL.ReadValue("MPAL","UIC_ITEM_tpgBank"));
	tbcResult.InsertItem(3,theApp.operPAL.ReadValue("MPAL","UIC_ITEM_tpgPK"));
	tbcResult.InsertItem(4,theApp.operPAL.ReadValue("MPAL","IM_UI_ADDITEM"));
}

//处理快捷键响应函数
BOOL CPALItemManage::PreTranslateMessage(MSG* pMsg)
{
	//OperationPAL operPAL;
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operPAL.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operPAL.CopyListInfo(&listResult);
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
void CPALItemManage::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CPALItemManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询玩家资料信息
void CPALItemManage::OnBnClickedSearch()
{
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
void CPALItemManage::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
void CPALItemManage::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
				ShowBagType();				

				pageInfo = false;
				cmbPage.ResetContent();
				while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

				//OperationPAL operPAL;
				UserAccount = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// 保存选中的玩家帐号
			    UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// 保存选中的玩家角色名

				BagInfo(0);// 查询玩家背包信息
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
void CPALItemManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		ShowUserInfo();//显示用户资料信息
	}
	else
	{
		ShowOtherInfo();

		pageInfo = false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			//OperationPAL operPAL;
			UserAccount = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// 保存选中的玩家帐号
			UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// 保存选中的玩家角色名

			if(tbcResult.GetCurSel()==1)
			{
				BagInfo(0);//查询玩家背包信息
			}
			else if(tbcResult.GetCurSel() == 2)
			{
				BagInfo(3);//查询玩家仓库信息
			}
			else if(tbcResult.GetCurSel() == 3)
			{
				BagInfo(2);//查询玩家藏宝袋信息
			}
			else if(tbcResult.GetCurSel() == 4)
			{
				SetDlgItemText(IDC_EDITADDNAME,UserName);
				ItemTypeInfo();
			}
		}
	}
	*pResult = 0;
}

//查询玩家背包信息
void CPALItemManage::BagInfo(int iBagType)
{
	//OperationPAL operPAL;	
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有六个参数，服务器IP、服务器Name、玩家昵称、背包类型,页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

		_itoa(iBagType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_BAGTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//背包类型

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数


		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERBAG))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_BagInfo"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}	
}

// 翻页进行查询
void CPALItemManage::OnCbnSelchangeCmbpage()
{
	//OperationPAL operPAL;
	try
	{	
		if(pageInfo)//如果可以翻页的话
		{
			CIni mIni;
		
			int index = cmbPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//每页显示50条记录

			int midlength = 0;
			while(listResult.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			
			switch(tbcResult.GetCurSel())
			{
			case 1:
				{
					_itoa(0,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::PAL_BAGTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
					midlength=socketdata.EnBody();
					if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERBAG))//发送查询玩家资料信息的请求
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
						dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
					}
				}
				break;
			case 2:
				{
					_itoa(3,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::PAL_BAGTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
					midlength=socketdata.EnBody();
					if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERBAG))//发送查询玩家资料信息的请求
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
						dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
					}
				}
				break;
			case 3:
				{
					_itoa(2,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::PAL_BAGTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
					midlength=socketdata.EnBody();
					if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERBAG))//发送查询玩家资料信息的请求
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
						dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
					}
				}
				break;
			}			
			socketdata.Destroy();//销毁CSocketData局部变量
		}
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_Page"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}
}

// 双击道具信息进行删除
void CPALItemManage::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
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

			int nSelectItem = listResult.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

			if(nSelectItem >= 0)
			{	
				CIni mIni;
				//OperationPAL operPAL;
				UserAccount = theApp.operPAL.GetValueByColName(&listResult, nSelectItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// 保存选中的玩家帐号
			    UserName = theApp.operPAL.GetValueByColName(&listResult, nSelectItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// 保存选中的玩家角色名

				int itemType = 0;
				CString strItemType = theApp.operPAL.GetValueByColName(&listResult, nSelectItem, theApp.operPAL.ReadValue("MPAL","PAL_ITEMTYPE"));// 保存物品类型
				CString ItemName = theApp.operPAL.GetValueByColName(&listResult, nSelectItem, theApp.operPAL.ReadValue("MPAL","PAL_ITEMNAME"));// 保存物品名称

				if(!strcmp(strItemType,theApp.operPAL.ReadValue("MPAL","UIC_ITEM_Body")))
				{
					itemType = 0;
				}
				else if(!strcmp(strItemType,theApp.operPAL.ReadValue("MPAL","UIC_ITEM_PetBag")))
				{
					itemType = 1;
				}
				else if(!strcmp(strItemType,theApp.operPAL.ReadValue("MPAL","UIC_ITEM_PK")))
				{
					itemType = 2;
				}
				else
				{
					itemType = 3;
				}

				int itemPosition = 0;
				CString strItemPosition = "";
				strItemPosition = theApp.operPAL.GetValueByColName(&listResult, nSelectItem, theApp.operPAL.ReadValue("MPAL","PAL_ITEMPOS"));// 保存物品位置

				itemPosition = atoi(strItemPosition);

				if (AfxMessageBox(theApp.operPAL.ReadValue("MPAL","IM_HINT_DELETEITEM"), MB_YESNO) == IDNO) 
				{
				    return;
				}

				int userbyID = theApp.UserByID;

				CSocketData socketdata;
				socketdata.InitCreate(1,10);//共有四个参数，服务器IP、服务器Name、玩家昵称、操作员ID
				int midlength = 0;
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
				socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
				socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
				socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

				_itoa(itemPosition,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PAL_ITEMPOS,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//物品位置
				socketdata.AddTFLV(CEnumCore::TagName::PAL_ITEMNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//物品名称

				_itoa(userbyID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

				switch(tbcResult.GetCurSel())
				{
				case 1:
					{
						_itoa(0,strInt,10);
						socketdata.AddTFLV(CEnumCore::TagName::PAL_BAGTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
						midlength=socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_DELCHARACTERITEM))//发送删除道具的请求
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
					    }
					}
					break;
				case 2:
					{
						_itoa(3,strInt,10);
						socketdata.AddTFLV(CEnumCore::TagName::PAL_BAGTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
						midlength=socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_DELCHARACTERITEM))//发送删除道具的请求
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
					    }
					}
					break;
				case 3:
					{
						_itoa(2,strInt,10);
						socketdata.AddTFLV(CEnumCore::TagName::PAL_BAGTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
						midlength=socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_DELCHARACTERITEM))//发送删除道具的请求
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
					    }
					}
					break;
				}
				socketdata.Destroy();
			}
		}
		else
		{
	    	nSelectItem = 0;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// 查询道具类别信息
void CPALItemManage::ItemTypeInfo()
{
	//OperationPAL operPAL;	
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		cmbType.ResetContent();
		cmbName.ResetContent();

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有六个参数，服务器IP、服务器Name、玩家昵称、背包类型,页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_ITEMTYPE_QUERY))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Error_SearchItemType"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}	
}

// 根据道具类别查询相应的道具名称
void CPALItemManage::OnCbnSelchangeCmbbigtype()
{
	//OperationPAL operPAL;	
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		cmbName.ResetContent();

		int ItemTypeID = 0;
		CString ItemTypeName = "";
		GetDlgItemText(IDC_CMBBIGTYPE,ItemTypeName);//获取道具类别的名称
		if(ItemTypeName == "")//道具类别不能为空
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_ItemTypeNull"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		BigTypeList.Lookup(cmbType.GetCurSel()+1,ItemTypeID);//从CMap类的对象BigTypeList中获取道具类别的ID

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有六个参数，服务器IP、服务器Name、玩家昵称、背包类型,页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称

		_itoa(ItemTypeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ITEMBIGTYPEID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//道具类别ID
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ITEMBIGTYPE,CEnumCore::TagFormat::TLV_STRING,strlen(ItemTypeName),(unsigned char *)mIni.wcharToChar(ItemTypeName));//道具类别

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_ITEMNAME_QUERY))
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

//向道具列表中添加道具
void CPALItemManage::OnBnClickedBtnadd()
{
	//OperationPAL operPAL;
	try
	{
		int ItemID = 0;
		CString ItemName = "";
		GetDlgItemText(IDC_CMBSMALLTYPE,ItemName);//获取道具名称
		if(ItemName == "")//道具名称不能为空
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_ItemNameNull"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		GiftList.Lookup(cmbName.GetCurSel()+1,ItemID);//从CMap类的对象GiftList中获取道具ID

		int itemNum = GetDlgItemInt(IDC_EDITITEMNUM);
		if(itemNum == 0)
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_ItemNumNull"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		if(itemNum>5)
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_ItemNum"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CIni mIni;

		int nRow = 0;
		char strInt[10];
		ZeroMemory(strInt,10);
		if(listItem.GetItemCount() == 0)
		{
			DWORD dwStyle = listItem.GetExtendedStyle();
			dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
			listItem.SetExtendedStyle(dwStyle); //设置扩展风格

			listItem.InsertColumn(0,theApp.operPAL.ReadValue("MPAL","IM_ITEM_ITEMID"),LVCFMT_CENTER,80,-1);
			listItem.InsertColumn(1,theApp.operPAL.ReadValue("MPAL","IM_ITEM_ITEMNAME"),LVCFMT_CENTER,100,-1);
			listItem.InsertColumn(2,theApp.operPAL.ReadValue("MPAL","IM_ITEM_ITEMNUM"),LVCFMT_CENTER,80,-1);

			_itoa(ItemID,strInt,10);
			int nRow=listItem.InsertItem(0,strInt);
			listItem.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItem.SetItemText(nRow,2,strInt);
		}
		else
		{
			int itemCount = 0;
			for(int i=0;i<listItem.GetItemCount();i++)
			{
				itemCount += atoi((LPCSTR)mIni.wcharToChar(listItem.GetItemText(i,2)));
			}
			if((itemCount + itemNum)>5)
			{
				MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_ItemNum"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			    return;
			}
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

//单击道具列表保存行号
void CPALItemManage::OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult)
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
void CPALItemManage::OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult)
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
void CPALItemManage::OnBnClickedBtndelete()
{
	if((listItem.GetItemCount() != 0) && (nSelectItem >= 0))
	{
		listItem.DeleteItem(nSelectItem);
	}
}

// 通过邮件添加道具
void CPALItemManage::OnBnClickedBtnsend()
{
	//OperationPAL operPAL;	
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		GetDlgItemText(IDC_EDITADDNAME,UserName);//获取角色名
		if(UserName == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","RM_Warn_RoleNameNull"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		///////////////////取邮件内容///////////////////////

		CString m_strSubject;
		GetDlgItemText(IDC_EDMAILSUBJECT,m_strSubject);
		if(m_strSubject == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_MailSubject"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		CString m_strContent;
		GetDlgItemText(IDC_EDMAILCONTENT,m_strContent);
		if(m_strContent == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_MailContent"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		CString m_strReason;
		GetDlgItemText(IDC_EDMAILREASON,m_strReason);
		if(m_strReason == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_MailReason"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		int iMoney=0;
		iMoney=GetDlgItemInt(IDC_EDMAILMONEY);
		int iGift[5]={-1,-1,-1,-1,-1};

		int itemCount = 0;
		int num = 0;
		for(int i=0;i<listItem.GetItemCount();i++)
		{
			itemCount = atoi((LPCSTR)mIni.wcharToChar(listItem.GetItemText(i,2)));
			for(int j=0;j<itemCount;j++)
			{
				iGift[num] = atoi((LPCSTR)mIni.wcharToChar(listItem.GetItemText(i,0)));
				num++;
			}
		}		

		int iUserByID=theApp.UserByID;

		CSocketData socketdata;	
		socketdata.InitCreate(1,25);//共有六个参数，服务器IP、服务器Name、玩家昵称、背包类型,页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号
	
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILSUBJECT,CEnumCore::TagFormat::TLV_STRING,strlen(m_strSubject),(unsigned char *)mIni.wcharToChar(m_strSubject));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILCONTENT,CEnumCore::TagFormat::TLV_STRING,strlen(m_strContent),(unsigned char *)mIni.wcharToChar(m_strContent));//玩家昵称

		_itoa(iMoney,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILMONEY,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//背包类型


		_itoa(iGift[0],strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILGIFTDBID0,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//背包类型

		_itoa(iGift[1],strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILGIFTDBID1,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//背包类型

		_itoa(iGift[2],strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILGIFTDBID2,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//背包类型

		_itoa(iGift[3],strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILGIFTDBID3,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//背包类型

		_itoa(iGift[4],strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILGIFTDBID4,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//背包类型
	
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILREASON,CEnumCore::TagFormat::TLV_STRING,strlen(m_strReason),(unsigned char *)mIni.wcharToChar(m_strReason));//玩家昵称


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		_itoa(iUserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//背包类型


		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_SENDGIFTMAIL))
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

// 重置信息
void CPALItemManage::OnBnClickedBtnreset()
{
	ResetMailInfo();//重置邮件信息
}


// 接收返回信息
LRESULT CPALItemManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::PAL_ITEMTYPE_QUERY_RESP://查询道具类别信息的回应
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int ItemTypeID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::PAL_ITEMBIGTYPEID).lpdata);//得到道具类别ID
				BigTypeList.SetAt(i,ItemTypeID);//将道具类别ID保存在CMap类的对象BigTypeList中
			}

			theApp.operPAL.BuildComboxs(&socketdata,&cmbType);//构造道具类别列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_ITEMNAME_QUERY_RESP://查询道具名称信息的回应
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int ItemNameID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::PAL_ITEMID).lpdata);//得到道具编号
				GiftList.SetAt(i,ItemNameID);//将道具编号保存在CMap类的对象GiftList中
			}

			theApp.operPAL.BuildComboxs(&socketdata,&cmbName);//构造道具名称列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERINFO_RESP://查询玩家资料信息的回应
		{
			theApp.operPAL.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERBAG_RESP://查询玩家背包的回应
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operPAL.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operPAL.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
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
	case CEnumCore::Message_Tag_ID::PAL_DELCHARACTERITEM_RESP:
	case CEnumCore::Message_Tag_ID::PAL_SENDGIFTMAIL_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operPAL.ShowResult(result);//显示返回结果
			ShowOtherInfo();
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

//单击用户资料信息的列名进行排序
void CPALItemManage::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listUser,pNMHDR,pResult);
}

//单击结果信息的列名进行排序
void CPALItemManage::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listResult,pNMHDR,pResult);
}

// 关闭对话框
void CPALItemManage::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	ShowUserInfo();
}

// 关闭对话框
void CPALItemManage::OnClose()
{
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Close");//关闭窗体	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!BigTypeList.IsEmpty())
	{
		BigTypeList.RemoveAll();
	}
	if(!GiftList.IsEmpty())
	{
		GiftList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

// 显示角色资料信息
void CPALItemManage::ShowUserInfo(void)
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
	ShowMailItem(SW_HIDE);
}

// 显示背包信息
void CPALItemManage::ShowBagType(void)
{
	tbcResult.SetCurSel(1);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
	ShowMailItem(SW_HIDE);
}

// 显示其它信息
void CPALItemManage::ShowOtherInfo(void)
{
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	if(tbcResult.GetCurSel()!=4)
	{
	    GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	    GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	    GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	    GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
		ShowMailItem(SW_HIDE);
	}
	else
	{
	    GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
		ShowMailItem(SW_SHOW);
	}
}

// 显示发送道具页面
void CPALItemManage::ShowMailItem(int m_cmdShow)
{
	GetDlgItem(IDC_LBLMAILSUBJECT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILSUBJECT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMAILCONTENT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILCONTENT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMAILMONEY)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILMONEY)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLADDNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITADDNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLBIGTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBBIGTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSMALLTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBSMALLTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLITEMNUM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITITEMNUM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNADD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNDELETE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLTOADDITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNSEND)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMAILREASON)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILREASON)->ShowWindow(m_cmdShow);

	ResetMailInfo();
}

//重置邮件信息
void CPALItemManage::ResetMailInfo(void)
{
	SetDlgItemText(IDC_EDMAILSUBJECT,"");
	SetDlgItemText(IDC_EDMAILCONTENT,"");
	SetDlgItemInt(IDC_EDMAILMONEY,0);
	SetDlgItemInt(IDC_EDITITEMNUM,0);
	listItem.DeleteAllItems();
	while(listItem.DeleteColumn(0)){}
	SetDlgItemText(IDC_EDMAILREASON,"");
}