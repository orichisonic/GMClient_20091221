// PALPuzzleMapManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_PAL.h"
#include "PALPuzzleMapManage.h"
#include ".\PALPuzzleMapManage.h"


// CPALPuzzleMapManage 对话框

IMPLEMENT_DYNAMIC(CPALPuzzleMapManage, CDialog)
CPALPuzzleMapManage::CPALPuzzleMapManage(CWnd* pParent /*=NULL*/)
	: CDialog(CPALPuzzleMapManage::IDD, pParent)
{
}

CPALPuzzleMapManage::~CPALPuzzleMapManage()
{
}

void CPALPuzzleMapManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_CB1, m_CB1);
	DDX_Control(pDX, IDC_CB2, m_CB2);
	DDX_Control(pDX, IDC_CB6, m_CB6);
	DDX_Control(pDX, IDC_CB9, m_CB9);
	DDX_Control(pDX, IDC_CB4, m_CB4);
	DDX_Control(pDX, IDC_CB3, m_CB3);
	DDX_Control(pDX, IDC_CB5, m_CB5);
	DDX_Control(pDX, IDC_CB7, m_CB7);
	DDX_Control(pDX, IDC_CB8, m_CB8);
}


BEGIN_MESSAGE_MAP(CPALPuzzleMapManage, CDialog)
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
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
	ON_BN_CLICKED(IDC_BTN1, OnBnClickedBtn1)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_BN_CLICKED(IDC_BTN2, OnBnClickedBtn2)
END_MESSAGE_MAP()


// 初始化对话框
BOOL CPALPuzzleMapManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// 初始化显示字符

	nItem = 0;
	nListItem = 0;
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
void CPALPuzzleMapManage::InitUI()
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

	SetDlgItemText(IDC_LBL0,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP"));
	SetDlgItemText(IDC_LBL1,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP1"));
	SetDlgItemText(IDC_LBL2,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP2"));
	SetDlgItemText(IDC_LBL3,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP3"));
	SetDlgItemText(IDC_LBL4,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP4"));
	SetDlgItemText(IDC_LBL5,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP5"));
	SetDlgItemText(IDC_LBL6,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP6"));
	SetDlgItemText(IDC_LBL7,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP7"));
	SetDlgItemText(IDC_LBL8,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP8"));
	SetDlgItemText(IDC_LBL9,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP9"));

	SetDlgItemText(IDC_BTN1,theApp.operPAL.ReadValue("MPAL","MakeSure"));
	SetDlgItemText(IDC_BTN2,theApp.operPAL.ReadValue("MPAL","Close"));

	tbcResult.InsertItem(0,theApp.operPAL.ReadValue("MPAL","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operPAL.ReadValue("MPAL","PMI_UI_tpgPuzzleMapInfo"));
	tbcResult.InsertItem(2,theApp.operPAL.ReadValue("MPAL","MPM_UI_tpgModifyPuzzleMap"));
	
}

//处理快捷键响应函数
BOOL CPALPuzzleMapManage::PreTranslateMessage(MSG* pMsg)
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
void CPALPuzzleMapManage::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CPALPuzzleMapManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询玩家资料信息
void CPALPuzzleMapManage::OnBnClickedSearch()
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
void CPALPuzzleMapManage::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
void CPALPuzzleMapManage::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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

				PuzzleMap();// 查询玩家背包信息
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
void CPALPuzzleMapManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	switch(tbcResult.GetCurSel())
	{
	case 0:
			ShowUserInfo();//显示用户资料信息
		break;
	case 1:

		ShowBagType();
		pageInfo = false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			//OperationPAL operPAL;
			UserAccount = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// 保存选中的玩家帐号
			UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// 保存选中的玩家角色名
			PuzzleMap();//查询玩家背包信息
		}			
		break;
	case 2:
		ShowModifyPuzzleMap();
		if((listResult.GetItemCount() > 0) && (nListItem >= 0))
		{
			InitComBox();
			strPuzzleMap = theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMap"));
			iPuzzleMapID[0]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID1")));
			iPuzzleMapID[1]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID2")));
			iPuzzleMapID[2]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID3")));
			iPuzzleMapID[3]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID4")));
			iPuzzleMapID[4]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID5")));
			iPuzzleMapID[5]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID6")));
			iPuzzleMapID[6]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID7")));
			iPuzzleMapID[7]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID8")));
			iPuzzleMapID[8]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID9")));

			SetDlgItemText(IDC_PUZZLEMAP,strPuzzleMap);
			m_CB1.SetCurSel(iPuzzleMapID[0]);
			m_CB2.SetCurSel(iPuzzleMapID[1]);
			m_CB3.SetCurSel(iPuzzleMapID[2]);
			m_CB4.SetCurSel(iPuzzleMapID[3]);
			m_CB5.SetCurSel(iPuzzleMapID[4]);
			m_CB6.SetCurSel(iPuzzleMapID[5]);
			m_CB7.SetCurSel(iPuzzleMapID[6]);
			m_CB8.SetCurSel(iPuzzleMapID[7]);
			m_CB9.SetCurSel(iPuzzleMapID[8]);

		}		
		break;
	}
	*pResult = 0;
}
//查询玩家图鉴
void CPALPuzzleMapManage::PuzzleMap()
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
		socketdata.InitCreate(1,7);//共有六个参数，服务器IP、服务器Name、玩家昵称、背包类型,页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数


		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERPUZZLEMAP))
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
void CPALPuzzleMapManage::OnCbnSelchangeCmbpage()
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
					if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERPUZZLEMAP))//发送查询玩家资料信息的请求
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
void CPALPuzzleMapManage::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
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

			nListItem = listResult.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

			if((listResult.GetItemCount() > 0) && (nListItem >= 0))
			{
				ShowModifyPuzzleMap();
				InitComBox();
				strPuzzleMap = theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMap"));
				iPuzzleMapID[0]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID1")));
				iPuzzleMapID[1]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID2")));
				iPuzzleMapID[2]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID3")));
				iPuzzleMapID[3]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID4")));
				iPuzzleMapID[4]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID5")));
				iPuzzleMapID[5]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID6")));
				iPuzzleMapID[6]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID7")));
				iPuzzleMapID[7]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID8")));
				iPuzzleMapID[8]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID9")));

				SetDlgItemText(IDC_PUZZLEMAP,strPuzzleMap);
				m_CB1.SetCurSel(iPuzzleMapID[0]);
				m_CB2.SetCurSel(iPuzzleMapID[1]);
				m_CB3.SetCurSel(iPuzzleMapID[2]);
				m_CB4.SetCurSel(iPuzzleMapID[3]);
				m_CB5.SetCurSel(iPuzzleMapID[4]);
				m_CB6.SetCurSel(iPuzzleMapID[5]);
				m_CB7.SetCurSel(iPuzzleMapID[6]);
				m_CB8.SetCurSel(iPuzzleMapID[7]);
				m_CB9.SetCurSel(iPuzzleMapID[8]);

			}	
		}
		else
		{
	    	nListItem = 0;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// 接收返回信息
LRESULT CPALPuzzleMapManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERPUZZLEMAP_RESP://查询玩家背包的回应
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
	case CEnumCore::Message_Tag_ID::PAL_MODIFYPUZZLEMAP_RESP:
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

//单击用户资料信息的列名进行排序
void CPALPuzzleMapManage::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listUser,pNMHDR,pResult);
}

//单击结果信息的列名进行排序
void CPALPuzzleMapManage::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listResult,pNMHDR,pResult);
}

// 关闭对话框
void CPALPuzzleMapManage::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	ShowUserInfo();
}

// 关闭对话框
void CPALPuzzleMapManage::OnClose()
{
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Close");//关闭窗体	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

// 显示角色资料信息
void CPALPuzzleMapManage::ShowUserInfo(void)
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBL0)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PUZZLEMAP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN2)->ShowWindow(SW_HIDE);
}

// 显示背包信息
void CPALPuzzleMapManage::ShowBagType(void)
{
	tbcResult.SetCurSel(1);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);


	GetDlgItem(IDC_LBL0)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PUZZLEMAP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN2)->ShowWindow(SW_HIDE);
}

// 显示修改图鉴
void CPALPuzzleMapManage::ShowModifyPuzzleMap(void)
{
	tbcResult.SetCurSel(2);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);


	GetDlgItem(IDC_LBL0)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL5)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL6)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL7)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL8)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL9)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_PUZZLEMAP)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB5)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB6)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB7)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB8)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB9)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN2)->ShowWindow(SW_SHOW);

}


void CPALPuzzleMapManage::OnBnClickedBtn1()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,30);//共有六个参数，服务器IP、服务器Name、玩家昵称、背包类型,页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

		CString PuzzleMap;
		GetDlgItemText(IDC_PUZZLEMAP,PuzzleMap);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMap,CEnumCore::TagFormat::TLV_STRING,strlen(PuzzleMap),(unsigned char *)mIni.wcharToChar(PuzzleMap));//玩家帐号

		_itoa(m_CB1.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID1,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(m_CB2.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID2,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(m_CB3.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID3,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(m_CB4.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID4,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(m_CB5.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID5,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(m_CB6.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID6,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(m_CB7.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID7,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(m_CB8.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID8,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(m_CB9.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID9,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数


		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYPUZZLEMAP))
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

void CPALPuzzleMapManage::InitComBox(void)
{
	m_CB1.ResetContent();
	m_CB2.ResetContent();
	m_CB3.ResetContent();
	m_CB4.ResetContent();
	m_CB5.ResetContent();
	m_CB6.ResetContent();
	m_CB7.ResetContent();
	m_CB8.ResetContent();
	m_CB9.ResetContent();

	m_CB1.AddString("关");
	m_CB1.AddString("开");
	m_CB1.SetCurSel(0);
	m_CB2.AddString("关");
	m_CB2.AddString("开");
	m_CB2.SetCurSel(0);
	m_CB3.AddString("关");
	m_CB3.AddString("开");
	m_CB3.SetCurSel(0);
	m_CB4.AddString("关");
	m_CB4.AddString("开");
	m_CB4.SetCurSel(0);
	m_CB5.AddString("关");
	m_CB5.AddString("开");
	m_CB5.SetCurSel(0);
	m_CB6.AddString("关");
	m_CB6.AddString("开");
	m_CB6.SetCurSel(0);
	m_CB7.AddString("关");
	m_CB7.AddString("开");
	m_CB7.SetCurSel(0);
	m_CB8.AddString("关");
	m_CB8.AddString("开");
	m_CB8.SetCurSel(0);
	m_CB9.AddString("关");
	m_CB9.AddString("开");
	m_CB9.SetCurSel(0);

}




void CPALPuzzleMapManage::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
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

			nListItem = listUser.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号
		}
		else
		{
			nListItem = 0;
		}
	}
	*pResult = 0;
}

void CPALPuzzleMapManage::OnBnClickedBtn2()
{
	// TODO: 在此添加控件通知处理程序代码
	InitComBox();
	strPuzzleMap = theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMap"));
	iPuzzleMapID[0]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID1")));
	iPuzzleMapID[1]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID2")));
	iPuzzleMapID[2]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID3")));
	iPuzzleMapID[3]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID4")));
	iPuzzleMapID[4]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID5")));
	iPuzzleMapID[5]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID6")));
	iPuzzleMapID[6]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID7")));
	iPuzzleMapID[7]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID8")));
	iPuzzleMapID[8]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID9")));

	SetDlgItemText(IDC_PUZZLEMAP,strPuzzleMap);
	m_CB1.SetCurSel(iPuzzleMapID[0]);
	m_CB2.SetCurSel(iPuzzleMapID[1]);
	m_CB3.SetCurSel(iPuzzleMapID[2]);
	m_CB4.SetCurSel(iPuzzleMapID[3]);
	m_CB5.SetCurSel(iPuzzleMapID[4]);
	m_CB6.SetCurSel(iPuzzleMapID[5]);
	m_CB7.SetCurSel(iPuzzleMapID[6]);
	m_CB8.SetCurSel(iPuzzleMapID[7]);
	m_CB9.SetCurSel(iPuzzleMapID[8]);
}
