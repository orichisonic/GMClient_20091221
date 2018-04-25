// JW2UserManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_JW2.h"
#include "JW2UserManage.h"
#include ".\JW2UserManage.h"


// CJW2UserManage 对话框

IMPLEMENT_DYNAMIC(CJW2UserManage, CDialog)
CJW2UserManage::CJW2UserManage(CWnd* pParent /*=NULL*/)
	: CDialog(CJW2UserManage::IDD, pParent)
{
}

CJW2UserManage::~CJW2UserManage()
{
}

void CJW2UserManage::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_CB1, cmbModifyType);
}


BEGIN_MESSAGE_MAP(CJW2UserManage, CDialog)
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
	ON_CBN_SELCHANGE(IDC_CB1, OnCbnSelchangeCb1)
	ON_BN_CLICKED(IDC_BTN1, OnBnClickedBtn1)
	ON_BN_CLICKED(IDC_BTN2, OnBnClickedBtn2)
END_MESSAGE_MAP()

// 初始化对话框
BOOL CJW2UserManage::OnInitDialog()
{
	CDialog::OnInitDialog();
	ShowModifyUser(SW_HIDE);
	ShowModifyPWD(SW_HIDE);
	InitUI();// 初始化显示字符	

	nItem = -1;
	pageInfo = false;
	pageUInfo = false;
	ServerIP = "";
	UserAccount = "";
	UserID = 0;
	UserName = "";
	UserNick = "";//初始化一些私有变量

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

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Create");//当前的状态为初始建立对话框

	theApp.operJW2.GetServerList();//请求所有的游戏服务器列表
	::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

	return TRUE;
}

// 初始化显示字符
void CJW2UserManage::InitUI()
{


	SetWindowText(theApp.operJW2.ReadValue("MJW2","UIC_UI_UserInfo"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operJW2.ReadValue("MJW2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operJW2.ReadValue("MJW2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operJW2.ReadValue("MJW2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operJW2.ReadValue("MJW2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operJW2.ReadValue("MJW2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operJW2.ReadValue("MJW2","Cancel"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operJW2.ReadValue("MJW2","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operJW2.ReadValue("MJW2","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operJW2.ReadValue("MJW2","UM_UI_tpgModifyUser"));
	tbcResult.InsertItem(2,theApp.operJW2.ReadValue("MJW2","UM_UI_tpgModifyPWD"));

	InitModifyType();

}

//处理快捷键响应函数
BOOL CJW2UserManage::PreTranslateMessage(MSG* pMsg)
{
	OperationJW2 operJW2;
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					operJW2.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					operJW2.CopyListInfo(&listResult);
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
void CJW2UserManage::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CJW2UserManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询玩家资料信息
void CJW2UserManage::OnBnClickedUisearch()
{
	try
	{
		CIni mIni;


		tbcResult.SetCurSel(0);

		nItem = -1;//玩家资料列表没有选定项
		pageUInfo = false;//玩家资料列表不能翻页	
		cmbUPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容
		
		GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);

		UpdateData(true);			


		GetDlgItemText(IDC_CMBUISERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Warn_SelectServer"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//获取玩家帐号
		GetDlgItemText(IDC_EDITUINICK,UserNick);//获取玩家昵称
		if((UserName == "") && (UserNick == ""))//玩家帐号和玩家昵称不能同时为空
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Warn_InputAccount"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

	    UserInfo();// 查询玩家资料信息
	}
	catch(...)
	{
	}
}

// 查询玩家资料信息
void CJW2UserManage::UserInfo()
{	

	try
	{		
		CIni mIni;		
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");//查询第一页的信息
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//每页显示50条记录

		nItem = -1;//玩家资料列表没有选定项
		pageUInfo = false;//玩家资料列表不能翻页	
		cmbUPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNT_QUERY);//发送查询玩家资料信息的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_UserInfo"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 翻页查询玩家资料信息
void CJW2UserManage::OnCbnSelchangeCmbuserpage()
{	
	try
	{	
		if(pageUInfo)//如果可以翻页的话
		{
			CIni mIni;
			
			int index = cmbUPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//每页显示50条记录

			while(listUser.DeleteColumn(0)){}//清除页面内容

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称


			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNT_QUERY);//发送查询玩家资料信息的请求

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// 单击用户列表保存当前行号
void CJW2UserManage::OnNMClickListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
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
void CJW2UserManage::OnNMDblclkListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
{
	CIni mIni;
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

			if(nItem >= 0)
			{
				tbcResult.SetCurSel(1);

				GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
				ShowModifyPWD(SW_HIDE);
				ShowModifyUser(SW_SHOW);

				if(nItem >= 0)
				{
					UserNick = theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserNick"));
					UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));
					int iUserLevel= atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_Level"))));
					SetDlgItemText(IDC_ED1,UserNick);
					SetDlgItemInt(IDC_ED2,iUserLevel);
				}
				else
				{
					cmbModifyType.ResetContent();
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
void CJW2UserManage::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{		
	CIni mIni;
	switch(tbcResult.GetCurSel())
	{
	case 0:
		ShowModifyUser(SW_HIDE);
		ShowModifyPWD(SW_HIDE);
		GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

		break;
	case 1:
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		ShowModifyPWD(SW_HIDE);
		ShowModifyUser(SW_SHOW);

		if(nItem >= 0)
		{
			UserNick = theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserNick"));
			UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));
			int iUserLevel= atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_Level"))));
			SetDlgItemText(IDC_ED1,UserNick);
			SetDlgItemInt(IDC_ED2,iUserLevel);
		}
		else
		{
			cmbModifyType.ResetContent();
		}
		break;
	case 2:
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		ShowModifyUser(SW_HIDE);
		ShowModifyPWD(SW_SHOW);
		if(nItem >= 0)
		{
			UserName = theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_ACCOUNT"));
			UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));
			SetDlgItemText(IDC_ED1,UserName);
		}
		break;
	default:
		break;
	}
	*pResult = 0;
}

// 修改等级
void CJW2UserManage::ModifyLevel()
{
	try
	{		
		CIni mIni;
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,20);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称


		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		int iLevel=GetDlgItemInt(IDC_ED3);
		_itoa(iLevel,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_Level,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_MODIFYLEVEL_QUERY);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_LEVELEXP"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 修改经验
void CJW2UserManage::ModifyExp()
{
	try
	{		
	    CIni mIni;
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,20);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称


		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		CString strExp;
		GetDlgItemText(IDC_ED3,strExp);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_Exp,CEnumCore::TagFormat::TLV_STRING,strlen(strExp),(unsigned char *)mIni.wcharToChar(strExp));//玩家昵称

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_MODIFYEXP_QUERY);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Story"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 修改密码
void CJW2UserManage::ModifyPwd()
{
	
	try
	{		
		CIni mIni;
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		CString firstpwd,secondpwd;
		GetDlgItemText(IDC_ED4,firstpwd);
		GetDlgItemText(IDC_ED5,secondpwd);
		if(strcmp(firstpwd,secondpwd))
		{
			MessageBox("密码重复不一致");
			SetDlgItemText(IDC_ED4,"");
			SetDlgItemText(IDC_ED5,"");
			return;
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,20);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称


		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID
		
		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		socketdata.AddTFLV(CEnumCore::TagName::JW2_PWD,CEnumCore::TagFormat::TLV_STRING,strlen(firstpwd),(unsigned char *)mIni.wcharToChar(firstpwd));//密码
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_MODIFY_PWD);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Item"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 重置密码
void CJW2UserManage::RecallPwd()
{
	
	try
	{
		CIni mIni;
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");


		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称


		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID

		_itoa(iType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_GOODSTYPE, CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//类型

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_RECALL_PWD);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Present"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 重置对话框
void CJW2UserManage::ResetDialog()
{
	SetDlgItemText(IDC_ED3,"");	

}



// 翻页进行查询
void CJW2UserManage::OnCbnSelchangeCmbuipage()
{
	
	try
	{
		if(pageInfo)
		{
			CIni mIni;
			
			int index = cmbPage.GetCurSel() + 1;
			int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

			while(listResult.DeleteColumn(0)){}

			CSocketData socketdata;
			socketdata.InitCreate(1,6);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

			_itoa(UserID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID

			_itoa(iType,strInt,10);
		    socketdata.AddTFLV(CEnumCore::TagName::JW2_GOODSTYPE, CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//类型

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数
			
			int midlength = socketdata.EnBody();				
			if(tbcResult.GetCurSel() == 1)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_RPG_QUERY);// 查询玩家故事情节信息
			}
			else if(tbcResult.GetCurSel() == 2)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ITEMSHOP_BYOWNER_QUERY);// 查询玩家身上道具信息
			}
			else if(tbcResult.GetCurSel() == 3)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_HOME_ITEM_QUERY);// 查询玩家房间道具信息
			}
			else if(tbcResult.GetCurSel() == 4)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_SMALL_PRESENT_QUERY);// 查询玩家购物送礼记录
			}
			else if(tbcResult.GetCurSel() == 5)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_WASTE_ITEM_QUERY);// 查询玩家消耗性道具使用
			}
			else if(tbcResult.GetCurSel() == 6)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_SMALL_BUGLE_QUERY);// 查询玩家小喇叭发送记录
			}	

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求
			socketdata.Destroy();
		}		
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Page"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 接收返回信息
LRESULT CJW2UserManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{	
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度


	CIni mIni;

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Receive");//当前的状态为接收到了返回信息

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

			theApp.operJW2.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_QUERY_RESP://查询玩家资料信息的回应
		{
			if(pageUInfo)//如果已经能够翻页
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
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
	case CEnumCore::Message_Tag_ID::JW2_MODIFYEXP_QUERY_RESP:
	case CEnumCore::Message_Tag_ID::JW2_MODIFYLEVEL_QUERY_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//显示操作结果
			SetDlgItemText(IDC_ED3,"");
			{
				tbcResult.SetCurSel(0);
				ShowModifyUser(SW_HIDE);
				ShowModifyPWD(SW_HIDE);
				GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
				UserInfo();

			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_MODIFY_PWD_RESP:
	case CEnumCore::Message_Tag_ID::JW2_RECALL_PWD_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//显示操作结果
			SetDlgItemText(IDC_ED4,"");
			SetDlgItemText(IDC_ED5,"");
		}
		break;
	default:
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

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
	}

	socketdata.Destroy();
	return false;
}

//单击用户资料信息的列名进行排序
void CJW2UserManage::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{

	theApp.operJW2.SortListInfo(&listUser,pNMHDR,pResult);
}

//单击结果信息的列名进行排序
void CJW2UserManage::OnLvnColumnclickListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
{

	theApp.operJW2.SortListInfo(&listResult,pNMHDR,pResult);
}

// 关闭对话框
void CJW2UserManage::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// 关闭对话框
void CJW2UserManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
//显示修改用户
void CJW2UserManage::ShowModifyUser(int n_cmdShow)
{
	GetDlgItem(IDC_LBL1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL2)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL3)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL4)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ED1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ED2)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ED3)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_CB1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTN1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTN2)->ShowWindow(n_cmdShow);
	
	SetDlgItemText(IDC_LBL1,theApp.operJW2.ReadValue("MJW2","UM_UI_UserNick"));
	SetDlgItemText(IDC_LBL2,theApp.operJW2.ReadValue("MJW2","UM_UI_ModifyType"));
	SetDlgItemText(IDC_LBL3,theApp.operJW2.ReadValue("MJW2","UM_UI_NowLevel"));
	SetDlgItemText(IDC_LBL4,theApp.operJW2.ReadValue("MJW2","UM_UI_NewLevel"));
	SetDlgItemText(IDC_BTN1,theApp.operJW2.ReadValue("MJW2","MakeSure"));
	SetDlgItemText(IDC_BTN2,theApp.operJW2.ReadValue("MJW2","Reset"));

	InitModifyType();



}

//显示修改密码
void CJW2UserManage::ShowModifyPWD(int n_cmdShow)
{
	GetDlgItem(IDC_LBL1)->ShowWindow(n_cmdShow);
	//GetDlgItem(IDC_LBL2)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL3)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL4)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ED1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ED4)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ED5)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTN1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTN2)->ShowWindow(n_cmdShow);

	SetDlgItemText(IDC_LBL1,theApp.operJW2.ReadValue("MJW2","UM_UI_UserName"));
	SetDlgItemText(IDC_LBL3,theApp.operJW2.ReadValue("MJW2","UM_UI_NewPasswd"));
	SetDlgItemText(IDC_LBL4,theApp.operJW2.ReadValue("MJW2","UM_UI_RENewPasswd"));
	SetDlgItemText(IDC_BTN1,theApp.operJW2.ReadValue("MJW2","UM_UI_ModifyPwd"));
	SetDlgItemText(IDC_BTN2,theApp.operJW2.ReadValue("MJW2","UM_UI_RecallPwd"));



}

void CJW2UserManage::InitModifyType(void)
{
	cmbModifyType.ResetContent();
	cmbModifyType.AddString(theApp.operJW2.ReadValue("MJW2","UM_UI_ModifyLevel"));
	cmbModifyType.AddString(theApp.operJW2.ReadValue("MJW2","UM_UI_ModifyExp"));
	cmbModifyType.SetCurSel(0);
}

void CJW2UserManage::OnCbnSelchangeCb1()
{
	// TODO: 在此添加控件通知处理程序代码
	int iResult=0;
	CIni mIni;
	switch(cmbModifyType.GetCurSel())
	{
	case 0:
		iResult= atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_Level"))));
		SetDlgItemText(IDC_LBL3,theApp.operJW2.ReadValue("MJW2","UM_UI_NowLevel"));
		SetDlgItemText(IDC_LBL4,theApp.operJW2.ReadValue("MJW2","UM_UI_NewLevel"));
		break;
	case 1:
		iResult= atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_Exp"))));
		SetDlgItemText(IDC_LBL3,theApp.operJW2.ReadValue("MJW2","UM_UI_NowExp"));
		SetDlgItemText(IDC_LBL4,theApp.operJW2.ReadValue("MJW2","UM_UI_NewExp"));
		break;
	default:
		break;
	}
	SetDlgItemInt(IDC_ED2,iResult);
}

void CJW2UserManage::OnBnClickedBtn1()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(tbcResult.GetCurSel())
	{
	case 1:
		{
			switch(cmbModifyType.GetCurSel())
			{
			case 0:
				ModifyLevel();
				break;
			case 1:
				ModifyExp();
				break;
			default:
				break;
			}
		}
		break;
	case 2:
		{
			ModifyPwd();
		}
		break;
	default:
		break;
	}
}

void CJW2UserManage::OnBnClickedBtn2()
{
	switch(tbcResult.GetCurSel())
	{
	case 1:
		{
			ResetDialog();
		}
		break;
	case 2:
		{
			RecallPwd();
		}
		break;
	default:
		break;
	}
}
