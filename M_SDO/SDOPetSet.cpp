// SDOPetSet.cpp : 实现文件
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOPetSet.h"
#include ".\sdopetset.h"


// CSDOPetSet 对话框

IMPLEMENT_DYNAMIC(CSDOPetSet, CDialog)
CSDOPetSet::CSDOPetSet(CWnd* pParent /*=NULL*/)
	: CDialog(CSDOPetSet::IDD, pParent)
{
}

CSDOPetSet::~CSDOPetSet()
{
}

void CSDOPetSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbUPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
}


BEGIN_MESSAGE_MAP(CSDOPetSet, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_CBN_SELCHANGE(IDC_CMBUIPAGE, OnCbnSelchangeCmbuipage)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_BN_CLICKED(IDC_BTNOK, OnBnClickedBtnok)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
END_MESSAGE_MAP()


// CSDOPetSet 消息处理程序

// 初始化对话框
BOOL CSDOPetSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUI();// 初始化显示字符

	nItem = 0;
	pageInfo = false;
	ServerIP = "";
	UserAccount = "";
	UserName = "";//初始化一些私有变量
	UserID=0;
	mItem=0;

	nCurLevel=0;

	nCurExperience=0;

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
		newRect.top = rs.top + grpHeight + tbcHeight+ grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listResult的位置		
	}

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Create");//当前的状态为初始建立对话框

	if(theApp.operSDO.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 初始化显示字符
void CSDOPetSet::InitUI()
{
	SetWindowText(theApp.operSDO.ReadValue("MSDO","PS_UI_PetSet"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operSDO.ReadValue("MSDO","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operSDO.ReadValue("MSDO","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operSDO.ReadValue("MSDO","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operSDO.ReadValue("MSDO","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","Search"));
	SetDlgItemText(IDCANCEL,theApp.operSDO.ReadValue("MSDO","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operSDO.ReadValue("MSDO","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLNICKER,theApp.operSDO.ReadValue("MSDO","UIC_UI_lblNick"));//玩家昵称
	SetDlgItemText(IDC_LBLCURLEVEL,theApp.operSDO.ReadValue("MSDO","CurPetLevel"));//当前等级
	SetDlgItemText(IDC_LBLNEWLEVEL,theApp.operSDO.ReadValue("MSDO","NewPetLevel"));//新等级
	SetDlgItemText(IDC_LBLCUREXPERIENCE,theApp.operSDO.ReadValue("MSDO","CurPetExperience"));//当前经验值
	SetDlgItemText(IDC_LBLNEWEXPERIENCE,theApp.operSDO.ReadValue("MSDO","NewPetExperience"));//新经验值
	SetDlgItemText(IDC_BTNOK,theApp.operSDO.ReadValue("MSDO","MakeSure"));
	SetDlgItemText(IDC_BTNRESET,theApp.operSDO.ReadValue("MSDO","Reset"));


	tbcResult.InsertItem(0,theApp.operSDO.ReadValue("MSDO","UIC_UI_tpgCharacterInfo"));//角色信息
	tbcResult.InsertItem(1,theApp.operSDO.ReadValue("MSDO","UIC_UI_tpgPetInfo"));//宠物信息
	tbcResult.InsertItem(2,theApp.operSDO.ReadValue("MSDO","PS_UI_tpg"));//修改宠物信息
}

// 自动改变大小
void CSDOPetSet::OnSize(UINT nType, int cx, int cy)
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
		newRect.top = rs.top + grpHeight + tbcHeight+ grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listResult的位置
	}
}

//设置背景颜色
HBRUSH CSDOPetSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//处理快捷键响应函数
BOOL CSDOPetSet::PreTranslateMessage(MSG* pMsg)
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
					theApp.operSDO.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&listResult);
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

// 关闭对话框
void CSDOPetSet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Close");//关闭窗体	

	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CSDOPetSet::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	ShowUserInfo();
}

// 显示角色资料信息
void CSDOPetSet::ShowUserInfo(void)
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);//IDC_CMBUIBPAGE
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLNICKER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETNICKER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETNICKER)->EnableWindow(false);

	GetDlgItem(IDC_LBLCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCURLEVEL)->EnableWindow(false);

	GetDlgItem(IDC_LBLNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLCUREXPERIENCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCUREXPERIENCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCUREXPERIENCE)->EnableWindow(false);


	GetDlgItem(IDC_LBLNEWEXPERIENCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETNEWEXPERIENCE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTNOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
}

//显示玩家宠物信息
void CSDOPetSet::ShowPetInfo()
{
	tbcResult.SetCurSel(1);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);//IDC_CMBUIBPAGE
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLNICKER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETNICKER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLCUREXPERIENCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCUREXPERIENCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLNEWEXPERIENCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETNEWEXPERIENCE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTNOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
}

//显示修改宠物信息
void CSDOPetSet::ShowPetSet()
{
	tbcResult.SetCurSel(2);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);//IDC_CMBUIBPAGE
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLNICKER)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETNICKER)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLCURLEVEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLNEWLEVEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETNEWLEVEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLCUREXPERIENCE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETCUREXPERIENCE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLNEWEXPERIENCE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETNEWEXPERIENCE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_BTNOK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);
}

// 单击用户列表保存当前行号
void CSDOPetSet::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// 双击玩家资料信息进行查询
void CSDOPetSet::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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

			if(nItem >= 0)
			{
				tbcResult.SetCurSel(1);
				ShowPetInfo();				

				while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

				UserAccount = theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Account"));//玩家帐号
				UserName = theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_NickName"));//玩家昵称
				UserID= atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_UserIndexID")));//玩家ID

////////////////				ItemInfo();//物品信息
				PetInfo();//宠物信息
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
void CSDOPetSet::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(tbcResult.GetCurSel() == 0)
	{
		cmbUPage.ResetContent();
		pageInfo = false;
		ShowUserInfo();//显示用户资料信息
	}
	else if(tbcResult.GetCurSel()==1)
	{
		ShowPetInfo();

		while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			UserAccount = theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Account"));//玩家帐号
			UserName = theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_NickName"));//玩家昵称
			UserID= atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_UserIndexID")));//玩家ID

			PetInfo();//宠物信息

		}
	}
	else if(tbcResult.GetCurSel()==2)
	{
		ShowPetSet();


		if((listResult.GetItemCount() > 0) && (mItem >= 0))
		{
			UserAccount = theApp.operSDO.GetValueByColName(&listResult, mItem, theApp.operSDO.ReadValue("MSDO","SDO_Account"));//玩家帐号
			UserName = theApp.operSDO.GetValueByColName(&listResult, mItem, theApp.operSDO.ReadValue("MSDO","SDO_NickName"));//玩家昵称
			UserID= atoi(theApp.operSDO.GetValueByColName(&listResult, mItem, theApp.operSDO.ReadValue("MSDO","SDO_UserIndexID")));//玩家ID

			nCurLevel =atoi(theApp.operSDO.GetValueByColName(&listResult, mItem, theApp.operSDO.ReadValue("MSDO","SDO_PetLevel")));
			nCurExperience= atoi(theApp.operSDO.GetValueByColName(&listResult, mItem, theApp.operSDO.ReadValue("MSDO","SDO_PetExperience")));//SDO_PetExperience
		}

		SetDlgItemText(IDC_ETNICKER,UserName);
		SetDlgItemInt(IDC_ETCURLEVEL,nCurLevel);
		SetDlgItemInt(IDC_ETCUREXPERIENCE,nCurExperience);
	}
	*pResult = 0;
}

//查询玩家资料信息
void CSDOPetSet::OnBnClickedSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;

		int index = theApp.operSDO.ReadIntValue("MSDO","index");//查询第一页的信息
		int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");//每页显示50条记录

		nItem = 0;//玩家资料列表没有选定项
		pageInfo=false;
		cmbUPage.ResetContent();
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Warn_SelectServer"),theApp.operSDO.ReadValue("MSDO","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITACCOUNT,Account);//获取玩家帐号//IDC_EDITACCOUNT
		GetDlgItemText(IDC_EDITNAME,Name);//获取玩家角昵称//IDC_EDITNAME
		if((Account == "") && (Name == ""))//玩家帐号和玩家角昵称不能同时为空
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Warn_InputAccount"),theApp.operSDO.ReadValue("MSDO","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
	    
		CSocketData socketdata;	
		socketdata.InitCreate(1,6);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(Name));//玩家角色名
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(Account),(unsigned char *)mIni.wcharToChar(Account));//玩家帐号

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHARACTERINFO_QUERY))//发送查询玩家资料信息的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}
}

//宠物信息
void CSDOPetSet::PetInfo()
{
	try
	{		
		CIni mIni;

		int index = theApp.operSDO.ReadIntValue("MSDO","index");
		int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");

		while(listResult.DeleteColumn(0)){};
		cmbPage.ResetContent();
		pageInfo = false;

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数


		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_PetInfo_Query))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Error_PetInfoError"),theApp.operSDO.ReadValue("MSDO","Error"),0);
	}
}

//切换翻页组合框(角色信息)
void CSDOPetSet::OnCbnSelchangeCmbuipage()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{	
		if(pageInfo)//如果可以翻页的话
		{
			CIni mIni;

			int index = cmbUPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");//每页显示50条记录

			while(listUser.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,6);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(Name));//玩家角色名
			socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(Account),(unsigned char *)mIni.wcharToChar(Account));//玩家帐号

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHARACTERINFO_QUERY))//发送查询玩家资料信息的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
				dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();//销毁CSocketData局部变量
		}
	}
	catch(...)
	{
		MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Error_Page"),theApp.operSDO.ReadValue("MSDO","Error"),0);
	}
}

void CSDOPetSet::OnCbnSelchangeCmbpage()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{	
		if(pageInfo)//如果可以翻页的话
		{
			CIni mIni;

			int index = cmbPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");//每页显示50条记录

			while(listResult.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,6);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(UserName));//玩家角色名
			socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(Account),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_PetInfo_Query))//发送查询宠物信息请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
				dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
			}

			socketdata.Destroy();//销毁CSocketData局部变量
		}
	}
	catch(...)
	{
		MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Error_Page"),theApp.operSDO.ReadValue("MSDO","Error"),0);
	}
}

//单击用户资料信息的列名进行排序
void CSDOPetSet::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&listUser,pNMHDR,pResult);
}

//单击结果信息的列名进行排序
void CSDOPetSet::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&listResult,pNMHDR,pResult);
}

// 接收返回信息
LRESULT CSDOPetSet::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;
	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operSDO.ReadValue("MSDO","Main_UI_SENDDATAERROR"),theApp.operSDO.ReadValue("MSDO","ERROR"),0);//Main_UI_ParseData		
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

			theApp.operSDO.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHARACTERINFO_QUERY_RESP:
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					pageInfo = false;//不能翻页		
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
	case CEnumCore::Message_Tag_ID::SDO_PetInfo_Query_RESP://宠物信息
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

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
	case CEnumCore::Message_Tag_ID::SDO_Pet_Update_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operSDO.ShowResult(result);//显示操作结果
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

//单击宠物信息列表
void CSDOPetSet::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(tbcResult.GetCurSel() == 1)
	{
		if(listResult.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listResult.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			mItem = listResult.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号
		}
		else
		{
			mItem = 0;
		}
	}
	*pResult = 0;
}

//双击宠物信息列表
void CSDOPetSet::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(tbcResult.GetCurSel() == 1)
	{
		if(listResult.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listResult.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			mItem = listResult.SubItemHitTest(&lvinfo);

			if(mItem >= 0)
			{
				tbcResult.SetCurSel(2);
				ShowPetSet();				

				UserAccount = theApp.operSDO.GetValueByColName(&listResult, mItem, theApp.operSDO.ReadValue("MSDO","SDO_Account"));//玩家帐号
				UserName = theApp.operSDO.GetValueByColName(&listResult, mItem, theApp.operSDO.ReadValue("MSDO","SDO_NickName"));//玩家昵称
				UserID= atoi(theApp.operSDO.GetValueByColName(&listResult, mItem, theApp.operSDO.ReadValue("MSDO","SDO_UserIndexID")));//玩家ID

				nCurLevel =atoi(theApp.operSDO.GetValueByColName(&listResult, mItem, theApp.operSDO.ReadValue("MSDO","SDO_PetLevel")));
				nCurExperience= atoi(theApp.operSDO.GetValueByColName(&listResult, mItem, theApp.operSDO.ReadValue("MSDO","SDO_PetExperience")));//SDO_PetExperience

			}
			SetDlgItemText(IDC_ETNICKER,UserName);
			SetDlgItemInt(IDC_ETCURLEVEL,nCurLevel);
			SetDlgItemInt(IDC_ETCUREXPERIENCE,nCurExperience);
		}
		else
		{
			mItem = 0;
		}
	}
	*pResult = 0;
}

//单击确定按钮修改玩家宠物信息
void CSDOPetSet::OnBnClickedBtnok()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;

		int nNewLevel=GetDlgItemInt(IDC_ETNEWLEVEL);
		int nNewExperience=GetDlgItemInt(IDC_ETNEWEXPERIENCE);

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

		int userByID=theApp.UserByID;

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(nNewLevel,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_PetLevel,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(nNewExperience,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_PetExperience,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_Pet_Update))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//重置信息
void CSDOPetSet::OnBnClickedBtnreset()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemInt(IDC_ETNEWLEVEL,0);
	SetDlgItemInt(IDC_ETNEWEXPERIENCE,0);
}
