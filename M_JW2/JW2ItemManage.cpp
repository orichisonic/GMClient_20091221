// JW2ItemManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_JW2.h"
#include "JW2ItemManage.h"
#include ".\JW2ItemManage.h"


// CJW2ItemManage 对话框

IMPLEMENT_DYNAMIC(CJW2ItemManage, CDialog)
CJW2ItemManage::CJW2ItemManage(CWnd* pParent /*=NULL*/)
	: CDialog(CJW2ItemManage::IDD, pParent)
{
}

CJW2ItemManage::~CJW2ItemManage()
{
}

void CJW2ItemManage::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_CMBPOS, cmbPos);
	DDX_Control(pDX, IDC_LISTRESULT, listItem);
	DDX_Control(pDX, IDC_LISTITEM, listItemResult);
}


BEGIN_MESSAGE_MAP(CJW2ItemManage, CDialog)
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
	ON_CBN_SELCHANGE(IDC_CMBPOS, OnCbnSelchangeCmbpos)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_BN_CLICKED(IDC_BTNSEND, OnBnClickedBtnsend)
	ON_BN_CLICKED(IDC_BTNBLURSEARCH, OnBnClickedBtnblursearch)
	ON_BN_CLICKED(IDC_BTNADD, OnBnClickedBtnadd)
	ON_BN_CLICKED(IDC_BTNDELETE, OnBnClickedBtndelete)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTITEM, OnNMClickListitem)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTITEM, OnNMDblclkListitem)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
END_MESSAGE_MAP()

// 初始化对话框
BOOL CJW2ItemManage::OnInitDialog()
{
	CDialog::OnInitDialog();
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
void CJW2ItemManage::InitUI()
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

	tbcResult.InsertItem(1,theApp.operJW2.ReadValue("MJW2","IM_UI_tpgAddItem"));
	//tbcResult.InsertItem(1,theApp.operJW2.ReadValue("MJW2","IM_UI_tpgItemManage"));
	//tbcResult.InsertItem(2,theApp.operJW2.ReadValue("MJW2","IM_UI_tpgMoneyManage"));
	//tbcResult.InsertItem(3,theApp.operJW2.ReadValue("MJW2","IM_UI_tpgAddItem"));


	InitItemPos();

	GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_HIDE);

	ShowAddItem(SW_HIDE);

}

//处理快捷键响应函数
BOOL CJW2ItemManage::PreTranslateMessage(MSG* pMsg)
{
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operJW2.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operJW2.CopyListInfo(&listResult);
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
void CJW2ItemManage::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rs;
	GetClientRect(rs);

	CRect newRect;

	int iWidth=0;

	if(GrpSearch.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4;		
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;
		newRect.bottom = newRect.top + grpHeight;

		GrpSearch.MoveWindow(newRect);//设置好GrpSearch的位置

		iWidth = newRect.right - newRect.left;
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

	//maple add
/*	if(listItem.m_hWnd != NULL)///道具列表
	{
		//RECT rctGroup;
		//GrpPage.GetWindowRect(&rctGroup);
		//ScreenToClient(&rctGroup);

		newRect.top = rs.top + 4 +grpHeight + tbcHeight+ grpPHeight;
		newRect.bottom = rs.bottom - 100;
		newRect.left = rs.left + 10;
		newRect.right = rs.left + (iWidth/3.5);////380;

		listItem.MoveWindow(newRect);
	}
*/
}

//设置背景颜色
HBRUSH CJW2ItemManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询玩家资料信息
void CJW2ItemManage::OnBnClickedUisearch()
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
void CJW2ItemManage::UserInfo()
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
void CJW2ItemManage::OnCbnSelchangeCmbuserpage()
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
void CJW2ItemManage::OnNMClickListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
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
void CJW2ItemManage::OnNMDblclkListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
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

			/*if(nItem >= 0)
			{
				tbcResult.SetCurSel(1);

				CIni mIni;
				pageInfo = false;
				cmbPage.ResetContent();
				while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容
				

				GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_SHOW);

				UserAccount = theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserID"));
				UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));

			//	ItemInfo();// 道具信息查询
			}*/
			if(nItem >= 0)
			{
				tbcResult.SetCurSel(1);

				CIni mIni;
				pageInfo = false;
				cmbPage.ResetContent();
				while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容




				UserAccount = theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserID"));
				UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));

				GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
				ShowModifyMoney(SW_HIDE);
				ShowAddItem(SW_SHOW);

				if((listUser.GetItemCount() > 0) && (nItem >= 0))
				{
					UserAccount =theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_ACCOUNT"));
					SetDlgItemText(IDC_EDITADDNAME,UserAccount);

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
void CJW2ItemManage::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{		
	switch(tbcResult.GetCurSel())
	{
	case 0:
		{
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_HIDE);
			ShowAddItem(SW_HIDE);
			ShowModifyMoney(SW_HIDE);

			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

		
		}
		break;
	/*case 1:
		{
			CIni mIni;
			pageInfo = false;
			cmbPage.ResetContent();
			while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

			ShowAddItem(SW_HIDE);
			ShowModifyMoney(SW_HIDE);

			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				UserAccount = theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserID"));
				UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));
				ItemInfo();// 查询玩家故事情节信息

			}


		}
		break;
	case 2:
		{
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_HIDE);
			ShowAddItem(SW_HIDE);
			ShowModifyMoney(SW_SHOW);


			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				UserAccount =theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_ACCOUNT"));
				CString money=theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_Money"));
				SetDlgItemText(IDC_EDITADDNAME,UserAccount);
				SetDlgItemText(IDC_EDITITEM,money);
				

			}

			

		}
		

		break;
	case 3:
		{
			
			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			ShowModifyMoney(SW_HIDE);
			ShowAddItem(SW_SHOW);

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				UserAccount =theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_ACCOUNT"));
				SetDlgItemText(IDC_EDITADDNAME,UserAccount);

			}
			
		}
		break;*/
		case 1:
			{

				GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
				ShowModifyMoney(SW_HIDE);
				ShowAddItem(SW_SHOW);

				if((listUser.GetItemCount() > 0) && (nItem >= 0))
				{
					UserAccount =theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_ACCOUNT"));
					SetDlgItemText(IDC_EDITADDNAME,UserAccount);

				}

			}
			break;
	}

	*pResult = 0;
}

// 查询玩家道具信息
void CJW2ItemManage::ItemInfo()
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


		int iItemPos=cmbPos.GetCurSel();
		_itoa(iItemPos,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ItemPos,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//道具位置


		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ItemInfo_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Story"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 删除道具
void CJW2ItemManage::DelItem()
{
	
	try
	{		
		CIni mIni;
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");


		CString avatarItem;
		CString avatarItemName;
		avatarItem = theApp.operJW2.GetValueByColName(&listResult, nItemResult, theApp.operJW2.ReadValue("MJW2","JW2_AvatarItem"));
		avatarItemName = theApp.operJW2.GetValueByColName(&listResult, nItemResult, theApp.operJW2.ReadValue("MJW2","JW2_AvatarItemName"));
		int iItemNo=atoi(theApp.operJW2.GetValueByColName(&listResult, nItemResult, theApp.operJW2.ReadValue("MJW2","JW2_ItemNo")));
		if (AfxMessageBox("确实删除该道具", MB_YESNO) == IDNO) 
		{
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


		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItem,CEnumCore::TagFormat::TLV_STRING,strlen(avatarItem),(unsigned char *)mIni.wcharToChar(avatarItem));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItemName,CEnumCore::TagFormat::TLV_STRING,strlen(avatarItemName),(unsigned char *)mIni.wcharToChar(avatarItemName));//玩家昵称


		int iItemPos=cmbPos.GetCurSel();
		_itoa(iItemPos,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ItemPos,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//道具位置

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID


		_itoa(iItemNo,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ItemNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//道具位置


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ITEM_DEL);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Item"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 查询玩家购物送礼记录
void CJW2ItemManage::PresentInfo()
{
	
	try
	{
		CIni mIni;
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");
		iType = cmbType.GetCurSel() + 1;

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
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_SMALL_PRESENT_QUERY);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Present"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 选择不同类型查询玩家购物送礼记录
void CJW2ItemManage::OnCbnSelchangeCmbtype()
{
	
	try
	{
		CIni mIni;
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");
		iType = cmbType.GetCurSel() + 1;

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
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_SMALL_PRESENT_QUERY);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Present"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 查询玩家消耗性道具使用
void CJW2ItemManage::ConsumeItem()
{
	
	try
	{
		CIni mIni;
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,5);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_WASTE_ITEM_QUERY);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Consume"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 查询玩家小喇叭发送记录
void CJW2ItemManage::BugleSend()
{

	try
	{
		CIni mIni;
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,5);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_SMALL_BUGLE_QUERY);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Bugle"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}
//用户家族
void CJW2ItemManage::UserFamily()
{

	try
	{
		CIni mIni;

		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,5);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_User_Family_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Bugle"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}
// 翻页进行查询
void CJW2ItemManage::OnCbnSelchangeCmbuipage()
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
LRESULT CJW2ItemManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
			/*//////maple add
			char *pdest;
			int nPos;
			char strServer[128];
			ZeroMemory(strServer,128);
			char *split=",";
			char destServer[128];
			ZeroMemory(destServer,128);*/

			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到服务器IP

			/*	//maple add
				sprintf(strServer,"%s",ServerIP);
				pdest=strstr(strServer,split);
				nPos=pdest-strServer;
				strncpy(destServer,strServer,nPos);
				destServer[nPos]='\0';*/

				ServerList.SetAt(i,ServerIP);//将服务器IP保存在CMap类的对象ServerList中
				//ServerList.SetAt(i,(LPCSTR)&destServer);
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
	case CEnumCore::Message_Tag_ID::JW2_ITEM_DEL_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//显示操作结果
			pageInfo = false;
			cmbPage.ResetContent();
			while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容
			ItemInfo();
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_MODIFY_MONEY_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//显示操作结果
			tbcResult.SetCurSel(0);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_HIDE);
			ShowAddItem(SW_HIDE);
			ShowModifyMoney(SW_HIDE);

			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			UserInfo();

		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ITEM_SELECT_RESP:
		{
			theApp.operJW2.BuildDataTable(&socketdata,&listItem,&pageCount);//构造CListCtrl对象
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ADD_ITEM_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			/////theApp.operJW2.ShowResult(result);//显示操作结果
			
			if(result=="Add_Item_Success")
				DeductProductManage();
			else
				theApp.operJW2.ShowResult(result);//显示操作结果

		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Validate_Resp://验证权限
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			if(result=="1")
				AddItem();
			else
			{
				m_tflv=socketdata.getTLVBynIndex(2);
				result=(LPCTSTR)&m_tflv.lpdata;
				theApp.operJW2.ShowResult(result);//显示操作结果*/
			}


			//maple add
			/*char strResult[128];
			ZeroMemory(strResult,128);
			char *split=";";
			sprintf(strResult,"%s",result);
			char *pdest;
			pdest=strstr(strResult,split);
			pdest++;
			char strSuccess[30];
			ZeroMemory(strSuccess,30);
			strcpy(strSuccess,pdest);
			CString str1=(LPCSTR)&strSuccess;

			if("SUCCESS"==str1)
				AddItem();
			else
				theApp.operJW2.ShowResult(result);//显示操作结果*/

			
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Deduct_Resp://验证通过在权限表中减去
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//显示操作结果

			OnBnClickedBtnreset();
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
void CJW2ItemManage::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{

	theApp.operJW2.SortListInfo(&listUser,pNMHDR,pResult);
}

//单击结果信息的列名进行排序
void CJW2ItemManage::OnLvnColumnclickListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
{

	theApp.operJW2.SortListInfo(&listResult,pNMHDR,pResult);
}

// 关闭对话框
void CJW2ItemManage::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// 关闭对话框
void CJW2ItemManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//初始化物品位置
void CJW2ItemManage::InitItemPos()
{
	cmbPos.ResetContent();
	cmbPos.AddString(theApp.operJW2.ReadValue("MJW2","IM_Pos_Body"));
	cmbPos.AddString(theApp.operJW2.ReadValue("MJW2","IM_Pos_WuBin"));
	cmbPos.AddString(theApp.operJW2.ReadValue("MJW2","IM_Pos_liWu"));	
	cmbPos.SetCurSel(0);
}

void CJW2ItemManage::OnCbnSelchangeCmbpos()
{
	// TODO: 在此添加控件通知处理程序代码
	pageInfo = false;
	cmbPage.ResetContent();
	while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容
	ItemInfo();
}

void CJW2ItemManage::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)//删除道具
{
	// TODO: 在此添加控件通知处理程序代码
	if(listResult.GetItemCount() != 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nItemResult = listResult.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

		if(nItemResult >= 0)
		{
			DelItem();
		}
	}
	else
	{
		nItemResult = -1;
	}

	*pResult = 0;
}

//显示添加道具
void CJW2ItemManage::ShowAddItem(int nCmdShow)
{
	GetDlgItem(IDC_LBLADDNAME)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDITADDNAME)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_LBLITEM)->ShowWindow(nCmdShow);
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


	SetDlgItemText(IDC_LBLADDNAME,theApp.operJW2.ReadValue("MJW2","IM_UI_Account"));
	SetDlgItemText(IDC_LBLITEM,theApp.operJW2.ReadValue("MJW2","IM_UI_ItemName"));
	SetDlgItemText(IDC_BTNBLURSEARCH,theApp.operJW2.ReadValue("MJW2","IM_UI_Search"));
	SetDlgItemText(IDC_LBLITEMNUM,theApp.operJW2.ReadValue("MJW2","IM_UI_ItemNum"));
	SetDlgItemText(IDC_LBLTOADDITEM,theApp.operJW2.ReadValue("MJW2","IM_UI_ItemList"));
	SetDlgItemText(IDC_LBLMAILSUBJECT,theApp.operJW2.ReadValue("MJW2","IM_UI_MailSubject"));
	SetDlgItemText(IDC_LBLMAILCONTENT,theApp.operJW2.ReadValue("MJW2","IM_UI_MailBody"));
	SetDlgItemText(IDC_BTNSEND,theApp.operJW2.ReadValue("MJW2","IM_UI_Send"));
	SetDlgItemText(IDC_BTNRESET,theApp.operJW2.ReadValue("MJW2","IM_UI_Reset"));

	SetDlgItemText(IDC_EDITITEM,"");
	SetDlgItemInt(IDC_EDITITEMNUM,1);



}

//显示修改G币
void CJW2ItemManage::ShowModifyMoney(int nCmdShow)
{

	GetDlgItem(IDC_LBLADDNAME)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDITADDNAME)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_LBLITEM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDITITEM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_LBLITEMNUM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDITITEMNUM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_BTNSEND)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(nCmdShow);

	SetDlgItemText(IDC_LBLADDNAME,theApp.operJW2.ReadValue("MJW2","IM_UI_Account"));
	SetDlgItemText(IDC_LBLITEM,theApp.operJW2.ReadValue("MJW2","IM_UI_OldMoney"));
	SetDlgItemText(IDC_LBLITEMNUM,theApp.operJW2.ReadValue("MJW2","IM_UI_NewMoney"));
	SetDlgItemText(IDC_BTNSEND,theApp.operJW2.ReadValue("MJW2","IM_UI_Confirm"));
	SetDlgItemText(IDC_BTNRESET,theApp.operJW2.ReadValue("MJW2","IM_UI_Reset"));
}
//添加道具
void CJW2ItemManage::AddItem()
{
	try
	{		
		CIni mIni;

		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		GetDlgItemText(IDC_EDITADDNAME,UserName);//获取角色名
		if(UserName == "")
		{
			MessageBox(theApp.operJW2.ReadValue("MGTOWN","RM_Warn_RoleNameNull"),theApp.operJW2.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		///////////////////取邮件内容///////////////////////

		CString m_strSubject;
		GetDlgItemText(IDC_EDMAILSUBJECT,m_strSubject);
		if(m_strSubject == "")
		{
			MessageBox(theApp.operJW2.ReadValue("MGTOWN","IM_Warn_MailSubject"),theApp.operJW2.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		CString m_strContent;
		GetDlgItemText(IDC_EDMAILCONTENT,m_strContent);
		if(m_strContent == "")
		{
			MessageBox(theApp.operJW2.ReadValue("MGTOWN","IM_Warn_MailContent"),theApp.operJW2.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		char ItemData[2048];
		ZeroMemory(ItemData, 2048);//初始化要发送的道具信息
		char tmpItemData[2048];
		ZeroMemory(tmpItemData, 2048);//保存临时的道具信息

		int itemCount = listItemResult.GetItemCount();//要添加道具的行数
		int mid = 0;//要添加的道具商品号
		int itemNum = 0;//要添加的道具数量
		for(int i=0;i<itemCount;i++)
		{
			mid = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,0)));
			itemNum = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,2)));
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

	

		CSocketData socketdata;	
		socketdata.InitCreate(1,25);
		char strInt[10];
		ZeroMemory(strInt, 10);

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称


		//邮件主题
		socketdata.AddTFLV(CEnumCore::TagName::JW2_MailTitle,CEnumCore::TagFormat::TLV_STRING,strlen(m_strSubject),(unsigned char *)mIni.wcharToChar(m_strSubject));
		//邮件内容
		socketdata.AddTFLV(CEnumCore::TagName::JW2_MailContent,CEnumCore::TagFormat::TLV_STRING,strlen(m_strContent),(unsigned char *)mIni.wcharToChar(m_strContent));

		//添加的道具内容
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItem,CEnumCore::TagFormat::TLV_STRING,strlen(ItemData),(unsigned char *)ItemData);

		_itoa(itemCount,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageCount,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//添加数量

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));
		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID


		int midlength = socketdata.EnBody();
		if(theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ADD_ITEM))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","IM_Error_ADDITEM"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}
	// TODO: 在此添加控件通知处理程序代码
}

///验证权限
void CJW2ItemManage::ValidateProductManage()
{
	try
	{		
		CIni mIni;


		CSocketData socketdata;	
		socketdata.InitCreate(1,25);
		char strInt[10];
		ZeroMemory(strInt, 10);

		//GM帐号
		//UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));
		int userByID=theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员IDChar(GMName));

	
		//ServerIP = ReturnServerIP();
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
		//ServerIP="222.211.80.58";
		
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP

		char ItemData[2048];
		ZeroMemory(ItemData, 2048);//初始化要发送的道具信息
		char tmpItemData[2048];
		ZeroMemory(tmpItemData, 2048);//保存临时的道具信息


		//maple add
		//char tmpItemIDList[1024];
		//ZeroMemory(tmpItemIDList,1024);
		//char ItemIDList[1024];
		//ZeroMemory(ItemIDList,1024);

		int itemCount = listItemResult.GetItemCount();//要添加道具的行数
		int mid = 0;//要添加的道具商品号
		int itemNum = 0;//要添加的道具数量
		for(int i=0;i<itemCount;i++)
		{
			mid = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,0)));
			itemNum = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,2)));
			sprintf(tmpItemData, "%i*%i", mid, itemNum);
			if(i == 0)
			{
				sprintf(ItemData, "%s|", tmpItemData);
				////sprintf(ItemIDList,"<%s>",mid);
			}
			else
			{
				sprintf(ItemData, "%s%s|", ItemData, tmpItemData);
			}
		}		

		//添加的道具内容
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItem,CEnumCore::TagFormat::TLV_STRING,strlen(ItemData),(unsigned char *)ItemData);

/*		/////_itoa(itemCount,strInt,10);
		/////socketdata.AddTFLV(CEnumCore::TagName::PageCount,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//添加数量


		CTime StartDate;
		dtcStartDate.GetTime(StartDate);

		CTime EndDate;
		dtcEndDate.GetTime(EndDate);

		CTime beginTime = CTime::CTime(StartDate.GetYear(),StartDate.GetMonth(),StartDate.GetDay(),0,0,0);
		CTime toTime = CTime::CTime(EndDate.GetYear(),EndDate.GetMonth(),EndDate.GetDay(),0,0,0);

		CString strBeginTime = beginTime.Format("%Y/%m/%d %H:%M:%S");//设置开始时间
		CString strEndTime = toTime.Format("%Y/%m/%d %H:%M:%S");//设置结束时间


		socketdata.AddTFLV(CEnumCore::TagName::JW2_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//开始时间
		socketdata.AddTFLV(CEnumCore::TagName::JW2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//结束时间

		///_itoa(CountItemPrice,strInt,10);
		////socketdata.AddTFLV(CEnumCore::TagName::JW2_TotalPrice,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//总额
*/

		int midlength = socketdata.EnBody();
		if(theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ProductManage_Validate))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		/////MessageBox(theApp.operJW2.ReadValue("MJW2","IM_Error_ADDITEM"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}

}

//验证通过在权限中减去
void CJW2ItemManage::DeductProductManage()
{
	try
	{		
		CIni mIni;


		CSocketData socketdata;	
		socketdata.InitCreate(1,25);
		char strInt[10];
		ZeroMemory(strInt, 10);

		//GM帐号
		//UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));
		int userByID=theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员IDChar(GMName));


		//ServerIP = ReturnServerIP();
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
		//ServerIP="222.211.80.58";
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP

		char ItemData[2048];
		ZeroMemory(ItemData, 2048);//初始化要发送的道具信息
		char tmpItemData[2048];
		ZeroMemory(tmpItemData, 2048);//保存临时的道具信息

		int itemCount = listItemResult.GetItemCount();//要添加道具的行数
		int mid = 0;//要添加的道具商品号
		int itemNum = 0;//要添加的道具数量
		for(int i=0;i<itemCount;i++)
		{
			mid = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,0)));
			itemNum = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,2)));
			sprintf(tmpItemData, "%i*%i", mid, itemNum);
			if(i == 0)
			{
				sprintf(ItemData, "%s|", tmpItemData);
			}
			else
			{
				sprintf(ItemData, "%s%s|", ItemData, tmpItemData);
			}
		}		

		//添加的道具内容
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItem,CEnumCore::TagFormat::TLV_STRING,strlen(ItemData),(unsigned char *)ItemData);

		

		int midlength = socketdata.EnBody();
		if(theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ProductManage_Deduct))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		/////MessageBox(theApp.operJW2.ReadValue("MJW2","IM_Error_ADDITEM"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}

}


void CJW2ItemManage::ModifyMoney()
{
	try
	{		
		CIni mIni;

		int index = theApp.operJW2.ReadIntValue("MGTOWN","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MGTOWN","pageSize");


		UpdateData(true);			


		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

		UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));
		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID

		int iMoney=GetDlgItemInt(IDC_EDITITEMNUM);
		_itoa(iMoney,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_Money,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数


		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_MODIFY_MONEY);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询^请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MGTOWN","UIC_Error_TreasureBox"),theApp.operJW2.ReadValue("MGTOWN","Error"),0);
	}// TODO: 在此添加控件通知处理程序代码
}
//发送道具
void CJW2ItemManage::OnBnClickedBtnsend()
{

	switch(tbcResult.GetCurSel())
	{
	case 1:
		//maple add
		ValidateProductManage();
		//DeductProductManage();
		///AddItem();
		break;
	default:
		break;
	/*case 2:
		ModifyMoney();
		break;
	case 3:
		//maple add
		ValidateProductManage();
		//DeductProductManage();
		///AddItem();
		break;
	default:
		break;*/
	}
	

}

void CJW2ItemManage::OnBnClickedBtnblursearch()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{		
		CIni mIni;

		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		while(listItem.DeleteColumn(0)){};

		UpdateData(true);			

		CString tmpName = "";//用于模糊查询的道具名称
		GetDlgItemText(IDC_EDITITEM,tmpName);//获取用于模糊查询的道具名称
		if(tmpName == "")//用于模糊查询的道具名称不能为空
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","IM_WARN_BlurItemNameNull"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

		//用于模糊查询的道具名称
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItemName,CEnumCore::TagFormat::TLV_STRING,strlen(tmpName),(unsigned char *)mIni.wcharToChar(tmpName));

		UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));
		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数


		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ITEM_SELECT);//道具模糊查询

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询^请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_TreasureBox"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}

}

void CJW2ItemManage::OnBnClickedBtnadd()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;

		if((listItem.GetItemCount() == 0)||(addItem < 0))//如果要添加的道具列表为空则返回
		{
			return;
		}

		CString tmpItemID = listItem.GetItemText(addItem, 0);
		int ItemID = atoi(mIni.wcharToChar(tmpItemID));//获取要添加的道具ID
		CString ItemName = listItem.GetItemText(addItem, 1);//获取要添加的道具名称
		CString ItemLimit= listItem.GetItemText(addItem, 2);
		CString ItemRemain= listItem.GetItemText(addItem, 3);

		int itemNum = GetDlgItemInt(IDC_EDITITEMNUM);
		if(itemNum == 0)
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","IM_Warn_ItemNumNull"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
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
		if(listItemResult.GetItemCount() == 0)
		{
			DWORD dwStyle = listItemResult.GetExtendedStyle();
			dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
			listItemResult.SetExtendedStyle(dwStyle); //设置扩展风格

			listItemResult.InsertColumn(0,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMID"),LVCFMT_CENTER,40,-1);
			listItemResult.InsertColumn(1,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMNAME"),LVCFMT_CENTER,50,-1);
			listItemResult.InsertColumn(2,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMNUM"),LVCFMT_CENTER,40,-1);
			listItemResult.InsertColumn(3,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMEXPIREDATE"),LVCFMT_CENTER,50,-1);
			listItemResult.InsertColumn(4,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMREMAINCOUNT"),LVCFMT_CENTER,40,-1);

			_itoa(ItemID,strInt,10);
			int nRow=listItemResult.InsertItem(0,strInt);
			listItemResult.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItemResult.SetItemText(nRow,2,strInt);
			listItemResult.SetItemText(nRow,3,ItemLimit);
			listItemResult.SetItemText(nRow,4,ItemRemain);
		}
		else
		{
			_itoa(ItemID,strInt,10);
			int nRow=listItemResult.InsertItem(0,strInt);
			listItemResult.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItemResult.SetItemText(nRow,2,strInt);
			listItemResult.SetItemText(nRow,3,ItemLimit);
			listItemResult.SetItemText(nRow,4,ItemRemain);
		}
	}
	catch(...)
	{
	}
}

void CJW2ItemManage::OnBnClickedBtndelete()
{
	if((listItemResult.GetItemCount() != 0) && (delItem >= 0))
	{
		listItemResult.DeleteItem(delItem);
	}
	if(listItemResult.GetItemCount() == 0)
	{
		while(listItemResult.DeleteColumn(0)){};
	}

}

void CJW2ItemManage::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listItem.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		addItem = listItem.SubItemHitTest(&lvinfo);//保存在可以添加的道具列表中选中的行号
	}
	else
	{
		addItem = -1;
	}
	*pResult = 0;
}

void CJW2ItemManage::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listItem.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		addItem = listItem.SubItemHitTest(&lvinfo);//保存在可以添加的道具列表中选中的行号

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

void CJW2ItemManage::OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(listItemResult.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItemResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		delItem = listItemResult.SubItemHitTest(&lvinfo);//保存在可以添加的道具列表中选中的行号
	}
	else
	{
		delItem = -1;
	}
	*pResult = 0;
}

void CJW2ItemManage::OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listItemResult.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItemResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		delItem = listItemResult.SubItemHitTest(&lvinfo);//保存在可以添加的道具列表中选中的行号

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

void CJW2ItemManage::OnBnClickedBtnreset()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDITITEM,"");//模糊查询道具名称为空
	SetDlgItemInt(IDC_EDITITEMNUM,1);//道具数量为1
	SetDlgItemText(IDC_EDMAILSUBJECT,"");//邮件主题为空
	SetDlgItemText(IDC_EDMAILCONTENT,"");//邮件内容为空
	listItem.DeleteAllItems();
	while(listItem.DeleteColumn(0)){}//道具列表为空
	listItemResult.DeleteAllItems();
	while(listItemResult.DeleteColumn(0)){}//赠送道具列表为空
}
