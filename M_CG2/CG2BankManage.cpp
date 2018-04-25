// CG2BankManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2BankManage.h"
#include ".\CG2BankManage.h"


// CCG2BankManage 对话框

IMPLEMENT_DYNAMIC(CCG2BankManage, CDialog)
CCG2BankManage::CCG2BankManage(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2BankManage::IDD, pParent)
{
}

CCG2BankManage::~CCG2BankManage()
{
}

void CCG2BankManage::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_CKITEMTYPE, ckItemType);
	//DDX_Control(pDX, IDC_LISTITEM, listItem);
	DDX_Control(pDX, IDC_CMB2, cmbItemName);
	DDX_Control(pDX, IDC_CMB1, cmbItemType);
}


BEGIN_MESSAGE_MAP(CCG2BankManage, CDialog)
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
	ON_BN_CLICKED(IDC_CKITEMTYPE, OnBnClickedCkitemtype)
	ON_BN_CLICKED(IDC_BTN1, OnBnClickedBtn1)
	ON_BN_CLICKED(IDC_BTN2, OnBnClickedBtn2)
	ON_BN_CLICKED(IDC_BTRIGHT, OnBnClickedBtright)
	ON_BN_CLICKED(IDC_BTLEFT, OnBnClickedBtleft)
	ON_NOTIFY(NM_CLICK, IDC_LISTITEM, OnNMClickListitem)
	ON_CBN_SELCHANGE(IDC_CMB1, OnCbnSelchangeCmb1)
END_MESSAGE_MAP()

// 初始化对话框
BOOL CCG2BankManage::OnInitDialog()
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
	

	ShowAddBankItem(SW_HIDE);
	ShowBankMoney(SW_HIDE);

	//maple add/////日志查询输入内容隐藏

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//当前的状态为初始建立对话框

	theApp.operCG2.GetServerList();//请求所有的游戏服务器列表
	::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

	return TRUE;
}

// 初始化显示字符
void CCG2BankManage::InitUI()
{
	//OperationCG2 theApp.operCG2;

	SetWindowText(theApp.operCG2.ReadValue("MCG2","UIC_UI_UserInfo"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operCG2.ReadValue("MCG2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));


	tbcResult.InsertItem(0,theApp.operCG2.ReadValue("MCG2","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgBankItem"));
	tbcResult.InsertItem(2,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgAddBankItem"));
	tbcResult.InsertItem(3,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgModiBankMoney"));
	//tbcResult.InsertItem(4,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgMultiAddBankItem"));


}

// 自动改变大小
void CCG2BankManage::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CCG2BankManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询玩家资料信息
void CCG2BankManage::OnBnClickedUisearch()
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

	    UserInfo();// 查询玩家资料信息
	}
	catch(...)
	{
	}
}

// 查询玩家资料信息
void CCG2BankManage::UserInfo()
{	
	try
	{		
		CIni mIni;		
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");//查询第一页的信息
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//每页显示50条记录

		nItem = -1;//玩家资料列表没有选定项
		pageUInfo = false;//玩家资料列表不能翻页	
		cmbUPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
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

// 翻页查询玩家资料信息
void CCG2BankManage::OnCbnSelchangeCmbuserpage()
{	
	try
	{	
		if(pageUInfo)//如果可以翻页的话
		{
			CIni mIni;
			//OperationCG2 theApp.operCG2;	
			
			int index = cmbUPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//每页显示50条记录

			while(listUser.DeleteColumn(0)){}//清除页面内容

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Query );//发送查询玩家资料信息的请求

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// 单击用户列表保存当前行号
void CCG2BankManage::OnNMClickListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
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
void CCG2BankManage::OnNMDblclkListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
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

				CIni mIni;
				pageInfo = false;
				cmbPage.ResetContent();
				while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容
				

				GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);

				UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
				UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
			    UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称

				BankItem();// 查询银行物品
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
void CCG2BankManage::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{		
	switch(tbcResult.GetCurSel())
	{
	case 0:
		{
			ShowAddBankItem(SW_HIDE);
			ShowBankMoney(SW_HIDE);
			ShowMultiAdd(SW_HIDE);
			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);

		
		}
		break;
	case 1:
		{
			CIni mIni;
			pageInfo = false;
			cmbPage.ResetContent();
			while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);

			ShowAddBankItem(SW_HIDE);
			ShowMultiAdd(SW_HIDE);
			ShowBankMoney(SW_HIDE);

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
				UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
				UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称

				BankItem();// 查询角色属性资料
			}
		}
		break;
	case 2:
		{
			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			ShowMultiAdd(SW_HIDE);
			ShowBankMoney(SW_HIDE);
			ShowAddBankItem(SW_SHOW);
			
			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
				UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
				UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称

				SetDlgItemText(IDC_ED1,UserName);

				ItemType();

			}
		}
		break;
	case 3:
		{
			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			ShowMultiAdd(SW_HIDE);
			ShowAddBankItem(SW_HIDE);
			ShowBankMoney(SW_SHOW);
			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
				UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
				UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称

				SetDlgItemText(IDC_ED1,UserName);

				BankInfo();

			}	
		}
		break;
	case 4:
		{
			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			ShowAddBankItem(SW_HIDE);
			ShowBankMoney(SW_HIDE);
			ShowMultiAdd(SW_SHOW);

		}
		break;
	default:
		break;
	}
	*pResult = 0;
}

// 银行存款信息
void CCG2BankManage::BankInfo()
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
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_BankInfo_Query );

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_LEVELEXP"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// 查询银行物品信息
void CCG2BankManage::BankItem()
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
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_BankItem_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Story"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}


// 翻页进行查询
void CCG2BankManage::OnCbnSelchangeCmbuipage()
{
	//OperationCG2 theApp.operCG2;	
	try
	{
		if(pageInfo)
		{
			CIni mIni;
			
			int index = cmbPage.GetCurSel() + 1;
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

			while(listResult.DeleteColumn(0)){}

			if((listUser.GetItemCount() > 0) && (nItem>=0))
			{
				CSocketData socketdata;
				socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
				socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
				socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
				socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//玩家IDKEY

				_itoa(index,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

				_itoa(iPageSize,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

				
				int midlength = socketdata.EnBody();				
				if(tbcResult.GetCurSel() == 1)
				{
					theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_BankInfo_Query);// 查询角色详细资料
				}
				else if(tbcResult.GetCurSel() == 2)
				{
					theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_BankItem_Query);// 查询角色属性资料
				}
				else if(tbcResult.GetCurSel() == 3)
				{
					theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_BankPet_Query);// 查询角色工会资料
				}
				
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求
				socketdata.Destroy();
			}
		}		
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Page"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// 接收返回信息
LRESULT CCG2BankManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{	
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
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
	case CEnumCore::Message_Tag_ID::CG2_InsertBankItem_Query_Resp:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//显示操作结果
			tbcResult.SetCurSel(1);
			CIni mIni;
			pageInfo = false;
			cmbPage.ResetContent();
			while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容
			ShowAddBankItem(SW_HIDE);
			ShowBankMoney(SW_HIDE);
			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);

			
			BankItem();// 查询角色属性资料
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_BankInfo_Query_Resp:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			if(m_tflv.m_tagName==CEnumCore::TagName::MESSAGE)
			{
				
				theApp.operCG2.ShowResult(result);//显示操作结果
			}
			else
			{
				CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(2);
				result = (LPCTSTR)&m_tflv.lpdata;
				SetDlgItemText(IDC_ED7,result);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_SetBankMoney_Query_Resp:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//显示操作结果
			SetDlgItemText(IDC_ED3,"");
			BankInfo();
		}
		break;
	default:
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

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

// 关闭对话框
void CCG2BankManage::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// 关闭对话框
void CCG2BankManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}




void CCG2BankManage::ShowAddBankItem(int n_cmdShow)
{
	GetDlgItem(IDC_ED1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ED2)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ED3)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ED4)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ED5)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL2)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL3)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL4)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL5)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL6)->ShowWindow(n_cmdShow);
	//GetDlgItem(IDC_LBL7)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_CKITEMTYPE)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_CMB1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_CMB2)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTN1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTN2)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTN3)->ShowWindow(n_cmdShow);
	//GetDlgItem(IDC_BTRIGHT)->ShowWindow(n_cmdShow);
	//GetDlgItem(IDC_BTLEFT)->ShowWindow(n_cmdShow);
	//GetDlgItem(IDC_LISTITEM)->ShowWindow(n_cmdShow);
	


	SetDlgItemText(IDC_LBL1,theApp.operCG2.ReadValue("MCG2","BU_UI_USERNAME"));
	SetDlgItemText(IDC_LBL2,theApp.operCG2.ReadValue("MCG2","UIC_ItemType"));
	SetDlgItemText(IDC_LBL3,theApp.operCG2.ReadValue("MCG2","UIC_ItemName"));
	SetDlgItemText(IDC_LBL4,theApp.operCG2.ReadValue("MCG2","UIC_ItemNumber"));
	SetDlgItemText(IDC_LBL5,theApp.operCG2.ReadValue("MCG2","UIC_Title"));
	SetDlgItemText(IDC_LBL6,theApp.operCG2.ReadValue("MCG2","UIC_Context"));

	SetDlgItemText(IDC_BTN1,theApp.operCG2.ReadValue("MCG2","BU_UI_btnSearch"));
	SetDlgItemText(IDC_BTN2,theApp.operCG2.ReadValue("MCG2","CG2_UI_tpgAddItem"));
	SetDlgItemText(IDC_BTN3,theApp.operCG2.ReadValue("MCG2","BU_UI_RESET"));

	SetDlgItemText(IDC_CKITEMTYPE,theApp.operCG2.ReadValue("MCG2","BU_UI_LBLSearchItemType"));
	//SetDlgItemText(IDC_LISTITEM,theApp.operCG2.ReadValue("MCG2","UIC_PresentItemList"));

	ckItemType.SetCheck(0);

	GetDlgItem(IDC_BTN1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ED4)->ShowWindow(SW_HIDE);



}
void CCG2BankManage::ShowBankMoney(int m_cmdShow)
{
	GetDlgItem(IDC_LBL1)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBL2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBL4)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_ED1)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_ED7)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_ED3)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_BTN2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTN3)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_LBL1,theApp.operCG2.ReadValue("MCG2","BU_UI_USERNAME"));
	SetDlgItemText(IDC_LBL2,theApp.operCG2.ReadValue("MCG2","BU_UI_OLDBANKMONEY"));
	SetDlgItemText(IDC_LBL4,theApp.operCG2.ReadValue("MCG2","BU_UI_NEWBANKMONEY"));
	SetDlgItemText(IDC_BTN2,theApp.operCG2.ReadValue("MCG2","BU_UI_SETBANKMONEY"));
}

void CCG2BankManage::ShowMultiAdd(int m_cmdShow)
{
	GetDlgItem(IDC_LBL2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_ED4)->ShowWindow(m_cmdShow);


	GetDlgItem(IDC_BTN1)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTN2)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_LBL2,theApp.operCG2.ReadValue("MCG2","BU_UI_FILEPATH"));
	SetDlgItemText(IDC_BTN1,theApp.operCG2.ReadValue("MCG2","BU_UI_BROWSE"));
	SetDlgItemText(IDC_BTN2,theApp.operCG2.ReadValue("MCG2","BU_UI_MULTIADD"));
}



void CCG2BankManage::OnBnClickedCkitemtype()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(ckItemType.GetCheck())
	{
	case 0:
		{
			GetDlgItem(IDC_BTN1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ED4)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMB1)->ShowWindow(SW_SHOW);
			SetDlgItemText(IDC_CKITEMTYPE,theApp.operCG2.ReadValue("MCG2","BU_UI_LBLSearchItemType"));

		}
		break;
	case 1:
		{
			GetDlgItem(IDC_BTN1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_ED4)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMB1)->ShowWindow(SW_HIDE);
			SetDlgItemText(IDC_CKITEMTYPE,theApp.operCG2.ReadValue("MCG2","BU_UI_LBLItemType"));
		}	
		break;
	}
}
//查询模糊道具
void CCG2BankManage::OnBnClickedBtn1()
{
	switch(tbcResult.GetCurSel())
	{
	case 2:
		SearchItem();
		break;
	case 4:
		{
			char path[256];
			GetCurrentDirectory(256,path);
			CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象

			lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,"文件类型(*.xls)|*.xls||");


			if(lpszOpenFile->DoModal()==IDOK)//假如点击对话框确定按钮
			{
				CString szGetName;
				szGetName=lpszOpenFile->GetPathName();
				SetDlgItemText(IDC_ED4,szGetName);
				SetCurrentDirectory(path);

			}
			delete lpszOpenFile;
		}
		break;
	default:
		break;
	}
	// TODO: 在此添加控件通知处理程序代码
	

}
//查询道具
void CCG2BankManage::SearchItem()
{
	try
	{		
		CIni mIni;

		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
			UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
			UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称



			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY

			_itoa(1,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::CG2_TypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数


			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SearchItem_Query );

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_LEVELEXP"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	

}
//添加道具,修改银行金钱
void CCG2BankManage::OnBnClickedBtn2()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(tbcResult.GetCurSel())
	{
	case 2:
		AddBankItem();
		break;
	case 3:
		ModifyBankMoney();
		break;
	case 4:
		MultiAddBankItem();
		break;
	}
}

//添加银行道具
void CCG2BankManage::AddBankItem()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;
		CSocketData socketdata;
		socketdata.InitCreate(1,20);//共有7个参数，服务器IP、玩家帐号、角色IDKEY、角色号、备注、道具名称、道具数量

		CString ItemName="";
		CString ItemNumber="";
		char strInt[10];

		/*int itemCount = 0;
		CString rItemName = "";
		CString rItemNum = "";
		for(int i=0;i<listItem.GetItemCount();i++)
		{
			rItemName=listItem.GetItemText(i,0);
			rItemNum=listItem.GetItemText(i,1);
			ItemName += rItemName;
			ItemName += "|";
			ItemNumber+=rItemNum;
			ItemNumber+="|";
		}*/

		GetDlgItemText(IDC_CMB2,ItemName);
		GetDlgItemText(IDC_ED3,ItemNumber);
		UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
		UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
		UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称
		int iCharNo=atoi(theApp.operCG2.GetValueByColName(&listUser,nItem,theApp.operCG2.ReadValue("MCG2","CG2_CharNo")));
	
		_itoa(iCharNo,strInt,10);



		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//角色号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY
		socketdata.AddTFLV(CEnumCore::TagName::CG2_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//道具名称
		socketdata.AddTFLV(CEnumCore::TagName::CG2_ItemNum,CEnumCore::TagFormat::TLV_STRING,strlen(ItemNumber),(unsigned char *)mIni.wcharToChar(ItemNumber));//道具数量

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_InsertBankItem_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
	}

}

//修改银行金钱
void CCG2BankManage::ModifyBankMoney()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;
		CSocketData socketdata;
		socketdata.InitCreate(1,20);//共有7个参数，服务器IP、玩家帐号、角色IDKEY、角色号、备注、道具名称、道具数量

		CString BankMoney="";

		char strInt[10];

		GetDlgItemText(IDC_ED3,BankMoney);
		UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
		UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
		UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称
		int iCharNo=atoi(theApp.operCG2.GetValueByColName(&listUser,nItem,theApp.operCG2.ReadValue("MCG2","CG2_CharNo")));

		_itoa(iCharNo,strInt,10);



		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//角色号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Money,CEnumCore::TagFormat::TLV_STRING,strlen(BankMoney),(unsigned char *)mIni.wcharToChar(BankMoney));//道具数量

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SetBankMoney_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
	}

}
//批量添加银行道具
void CCG2BankManage::MultiAddBankItem()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;
		CSocketData socketdata;
		socketdata.InitCreate(1,20);//共有7个参数，服务器IP、玩家帐号、角色IDKEY、角色号、备注、道具名称、道具数量
	
		CString strFilePath="";
        CString strUserName="";
		CString strUserID="";
		CString strItemName="";
		CString strItemNum="";


		/////////读数据库获取内容////////////
		GetDlgItemText(IDC_ED4,strFilePath);
		ReadXls(strFilePath,&strUserName,&strUserID,&strItemName,&strItemNum);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(strUserName),(unsigned char *)mIni.wcharToChar(strUserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(strUserID),(unsigned char *)mIni.wcharToChar(strUserID));//角色唯一IDKEY
		socketdata.AddTFLV(CEnumCore::TagName::CG2_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(strItemName),(unsigned char *)mIni.wcharToChar(strItemName));//道具名称
		socketdata.AddTFLV(CEnumCore::TagName::CG2_ItemNum,CEnumCore::TagFormat::TLV_STRING,strlen(strItemNum),(unsigned char *)mIni.wcharToChar(strItemNum));//道具数量

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_InsertBankItemALL_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
	}

}
void CCG2BankManage::OnBnClickedBtright()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	//获取道具名称
	int iPos=((CComboBox*)GetDlgItem(IDC_CMB2))->GetCurSel();//当前选中的行
	CString ItemName="";
	((CComboBox*)GetDlgItem(IDC_CMB2))->GetLBText(iPos,ItemName); //其中n为从0开始的索引值

	//获取道具数量
	CString ItemNumber;
	GetDlgItemText(IDC_ED3,ItemNumber);
	if(StrToInt(ItemNumber)<1)
	{
		MessageBox("请输入数字");
		return;

	}

	listItem.InsertItem(0,ItemName);
	listItem.SetItemText(0,1,ItemNumber);
}

void CCG2BankManage::OnBnClickedBtleft()
{
	// TODO: 在此添加控件通知处理程序代码
	listItem.DeleteItem(nListItem);
}

void CCG2BankManage::OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult)
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

		nListItem = listItem.SubItemHitTest(&lvinfo);//保存在赠送道具列表中选中的行号
	}
	else
	{
		nListItem = -1;
	}
	*pResult = 0;
}


//道具类别查询
void CCG2BankManage::ItemType()
{
	try
	{		
		CIni mIni;

		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,5);//共有2个参数，服务器IP、玩家帐号
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			
			_itoa(1,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::CG2_TypeID,CEnumCore::TagFormat::TLV_STRING,sizeof(int),(unsigned char *)&strInt);//玩家帐号

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

void CCG2BankManage::OnCbnSelchangeCmb1()
{
	// TODO: 在此添加控件通知处理程序代码

	
	try
	{		
		CIni mIni;

		int iPos=((CComboBox*)GetDlgItem(IDC_CMB1))->GetCurSel();//当前选中的行
		CString ItemType="";
		((CComboBox*)GetDlgItem(IDC_CMB1))->GetLBText(iPos,ItemType); //其中n为从0开始的索引值

		CSocketData socketdata;
		socketdata.InitCreate(1,3);//共有3个参数，服务器IP、玩家帐号、道具类别


		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_ItemType,CEnumCore::TagFormat::TLV_STRING,strlen(ItemType),(unsigned char *)mIni.wcharToChar(ItemType));//道具类别

	
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

void CCG2BankManage::GetListItem(CString m_ItemName, CString m_ItemNum)
{
	int itemCount = 0;
	CString rItemName = "";
	CString rItemNum = "";
	for(int i=0;i<listItem.GetItemCount();i++)
	{
		rItemName=listItem.GetItemText(i,0);
		rItemNum=listItem.GetItemText(i,1);
		m_ItemName += rItemName;
		m_ItemName += "|";
		m_ItemNum+=rItemNum;
		m_ItemNum+="|";
	}
	
}


bool CCG2BankManage::ReadXls(CString strFilePath,CString* strUserName, CString* strUserID, CString* strItemName, CString* strItemNum)
{
	try
	{
		CoInitialize(NULL);
		_ConnectionPtr m_pConnection;
		_RecordsetPtr	m_pRecordset;
		CString ConnectionString="";
		CString UserName="";
		CString UserID="";
		CString ItemName="";
		CString ItemNum="";
		ConnectionString = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=");   
		ConnectionString += strFilePath;   //excel   file   name   
		ConnectionString += _T(";Extended Properties=\"Excel 8.0;HDR=Yes;IMEX=1\""); 


		BSTR resultsString = ConnectionString.AllocSysString();



		m_pConnection.CreateInstance(__uuidof(Connection));

		m_pConnection->Open(resultsString,"","",adModeUnknown);
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open("select * from [Sheet1$]",
			m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);

		if(m_pRecordset->adoEOF) AfxMessageBox("该文档没有内容");
		while(!m_pRecordset->adoEOF)
		{
			if(m_pRecordset->GetFields()->GetItem(long(0))->Value.vt==VT_NULL) break;
			UserName=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem((long)0)->GetValue());
			UserID=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem((long)1)->GetValue());
			ItemName=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem((long)2)->GetValue());
			ItemNum=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem((long)3)->GetValue());

			*strUserName += UserName;
			*strUserName += "|";
			*strUserID+=UserID;
			*strUserID+="|";
			*strItemName += ItemName;
			*strItemName += "|";
			*strItemNum+=ItemNum;
			*strItemNum+="|";

			m_pRecordset->MoveNext();
		}
		m_pRecordset->Close();
		if(m_pRecordset) m_pRecordset.Release();
		m_pConnection->Close();
		if(m_pConnection) m_pConnection.Release();
		CoUninitialize();

	}
	catch(...)
	{
		return false;
	}
	
	return true;
}
