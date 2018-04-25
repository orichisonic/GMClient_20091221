// XDGMManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_XD.h"
#include "XDGMManage.h"


// CXDGMManage 对话框

IMPLEMENT_DYNAMIC(CXDGMManage, CDialog)
CXDGMManage::CXDGMManage(CWnd* pParent /*=NULL*/)
	: CDialog(CXDGMManage::IDD, pParent)
{
}

CXDGMManage::~CXDGMManage()
{
}

void CXDGMManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);

	DDX_Control(pDX, IDC_TABRESULT, tbcResult);

	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBBASIC, cmbBasic);
	DDX_Control(pDX, IDC_LISTBASIC, listBasic);
	DDX_Control(pDX, IDC_CMBLIST, cmbList);
}


BEGIN_MESSAGE_MAP(CXDGMManage, CDialog)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_CMBBASIC, OnCbnSelchangeCmbbasic)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTBASIC, OnNMClickListbasic)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTBASIC, OnNMDblclkListbasic)

	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	
	ON_BN_CLICKED(IDC_BTNEDIT, OnBnClickedBtnedit)
	ON_BN_CLICKED(IDC_BTNRECOVER, OnBnClickedBtnrecover)
END_MESSAGE_MAP()


// CXDGMManage 消息处理程序

// 初始化对话框
BOOL CXDGMManage::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// 初始化显示字符

	nItem = -1;
	pageBasic = false;
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

	if(listBasic.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listBasic.MoveWindow(newRect);//设置好listBasic的位置
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
void CXDGMManage::InitUI()
{
	SetWindowText(theApp.operXD.ReadValue("MXD","GMM_UI_GMManage"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operXD.ReadValue("MXD","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operXD.ReadValue("MXD","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operXD.ReadValue("MXD","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operXD.ReadValue("MXD","Search"));
	SetDlgItemText(IDCANCEL,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operXD.ReadValue("MXD","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operXD.ReadValue("MXD","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operXD.ReadValue("MXD","GMM_UI_TransferXYZ"));	
	tbcResult.InsertItem(2,theApp.operXD.ReadValue("MXD","GMM_UI_TransferGM"));
	tbcResult.InsertItem(3,theApp.operXD.ReadValue("MXD","GMM_UI_GMTransfer"));
	tbcResult.InsertItem(4,theApp.operXD.ReadValue("MXD","GMM_UI_BuffEdit"));

	SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNICK,theApp.operXD.ReadValue("MXD","UIC_UI_lblNick"));
	SetDlgItemText(IDC_LBLGMNAME,theApp.operXD.ReadValue("MXD","GMM_UI_GMName"));
	SetDlgItemText(IDC_LBLCOORDINATE,theApp.operXD.ReadValue("MXD","GMM_UI_Coordinate"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","Move"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_EDITX,"0");
	SetDlgItemText(IDC_EDITY,"0");
	SetDlgItemText(IDC_EDITZ,"0");
}

// 自动改变大小
void CXDGMManage::OnSize(UINT nType, int cx, int cy)
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

	if(listBasic.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listBasic.MoveWindow(newRect);//设置好listBasic的位置
	}
}

//设置背景颜色
HBRUSH CXDGMManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询玩家资料信息
void CXDGMManage::OnBnClickedSearch()
{
	try
	{
		CIni mIni;

		tbcResult.SetCurSel(0);

		nItem = -1;//玩家资料列表没有选定项
		pageBasic = false;//玩家资料列表不能翻页	
		cmbBasic.ResetContent();//清除玩家资料列表翻页的复选框
		while(listBasic.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		ShowCoordinate(SW_HIDE);
		ShowTransferGM(SW_HIDE);
		ShowEditBuff(SW_HIDE);
		ShowUserInfo(SW_SHOW);

		UpdateData(true);

		CString m_ServerName;
		GetDlgItemText(IDC_CMBSERVER,m_ServerName);//获取游戏服务器的名称
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
void CXDGMManage::UserInfo()
{	
	try
	{		
		CIni mIni;		

		int index = theApp.operXD.ReadIntValue("MXD","index");//查询第一页的信息
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//每页显示50条记录

		nItem = -1;//玩家资料列表没有选定项
		pageBasic = false;//玩家资料列表不能翻页	
		cmbBasic.ResetContent();//清除玩家资料列表翻页的复选框
		while(listBasic.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

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
		theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Account_Query);//发送查询玩家资料信息的请求

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
void CXDGMManage::OnCbnSelchangeCmbbasic()
{	
	try
	{	
		if(pageBasic)//如果可以翻页的话
		{
			CIni mIni;	

			int index = cmbBasic.GetCurSel() + 1;//页数为cmbBasic当前的索引值加1，也就是cmbBasic中当前显示的值
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//每页显示50条记录

			while(listBasic.DeleteColumn(0)){}//清除页面内容

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
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Account_Query);//发送查询玩家资料信息的请求

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// 单击基本资料信息保存当前行号
void CXDGMManage::OnNMClickListbasic(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listBasic.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listBasic.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listBasic.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

// 双击基本资料信息进行查询
void CXDGMManage::OnNMDblclkListbasic(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listBasic.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listBasic.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listBasic.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

			if(nItem >= 0)
			{
				ShowUserInfo(SW_HIDE);
				ShowTransferGM(SW_HIDE);
				ShowEditBuff(SW_HIDE);
				ShowCoordinate(SW_SHOW);

				if((listBasic.GetItemCount() > 0) && (nItem >= 0))
				{
					UserName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// 保存选中的玩家帐号
					//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","WA_NickID"));// 保存选中的玩家ID
					UserNick = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// 保存选中的玩家昵称
						
					tbcResult.SetCurSel(1);
					SetDlgItemText(IDC_EDITACCOUNT,UserName);
					SetDlgItemText(IDC_EDITNICK,UserNick);
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

// 切换选项卡进行操作
void CXDGMManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	UserName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// 保存选中的玩家帐号
	//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_AccountID"));// 保存选中的玩家ID
	UserNick = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// 保存选中的玩家昵称

	switch(tbcResult.GetCurSel())
	{
	case 0:
		{
			ShowCoordinate(SW_HIDE);
			ShowTransferGM(SW_HIDE);
			ShowEditBuff(SW_HIDE);
			ShowUserInfo(SW_SHOW);
		}
		break;
	case 1:
		{
			ShowUserInfo(SW_HIDE);
			ShowTransferGM(SW_HIDE);
			ShowEditBuff(SW_HIDE);
			ShowCoordinate(SW_SHOW);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);
			}
		}
		break;
	case 4:
		{
			ShowUserInfo(SW_HIDE);
			ShowCoordinate(SW_HIDE);
			ShowTransferGM(SW_HIDE);			
			ShowEditBuff(SW_SHOW);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);

				SearchBuff();
			}
		}
		break;
	default:
		{	
			ShowUserInfo(SW_HIDE);
			ShowCoordinate(SW_HIDE);
			ShowEditBuff(SW_HIDE);
			ShowTransferGM(SW_SHOW);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);
			}	
		}
		break;
	}
	*pResult = 0;
}

//查询所有BUFF信息
void CXDGMManage::SearchBuff()
{
	try
	{		
		CIni mIni;

		if((listBasic.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			CString Profession = "";
			Profession = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Profession"));// 保存选中的职业名称

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Profession,CEnumCore::TagFormat::TLV_STRING,strlen(Profession),(unsigned char *)mIni.wcharToChar(Profession));//职业名称

			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_BuffList_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_SearchSkill"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//移动角色位置
void CXDGMManage::OnBnClickedBtnedit()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listBasic.GetItemCount() > 0) && (nItem>=0))
		{			
			GetDlgItemText(IDC_EDITACCOUNT,UserName);
			GetDlgItemText(IDC_EDITNICK,UserNick);

			CString m_Name = ""; //GM角色名
			CString xPos = "";//x坐标
			CString yPos = "";//y坐标
			CString zPos = "";//z坐标
			if(tbcResult.GetCurSel()==1)//传送至指定位置
			{
				GetDlgItemText(IDC_EDITX,xPos);
				GetDlgItemText(IDC_EDITY,yPos);
				GetDlgItemText(IDC_EDITZ,zPos);	
			}
			else if(tbcResult.GetCurSel()==4)//添加BUFF
			{
				GetDlgItemText(IDC_CMBLIST,BuffName);//获取Buff名称
				if(BuffName == "")//添加Buff不能为空
				{
					return;
				}
				BuffList.Lookup(cmbList.GetCurSel()+1,BuffID);//从CMap类的对象BuffList中获取BuffID
			}
			else//和GM互相传送时
			{
				GetDlgItemText(IDC_EDITGMNAME,m_Name);
				if(m_Name=="") //GM角色名不能为空
				{
					MessageBox(theApp.operXD.ReadValue("MXD","GMM_Warn_GMNameNull"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
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

			switch(tbcResult.GetCurSel())
			{
			case 1:
				{
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_PositionX,CEnumCore::TagFormat::TLV_STRING,strlen(xPos),(unsigned char *)mIni.wcharToChar(xPos));//x坐标
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_PositionY,CEnumCore::TagFormat::TLV_STRING,strlen(yPos),(unsigned char *)mIni.wcharToChar(yPos));//y坐标
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_PositionZ,CEnumCore::TagFormat::TLV_STRING,strlen(zPos),(unsigned char *)mIni.wcharToChar(zPos));//z坐标
				}
				break;
			case 4:
				{
					_itoa(BuffID,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_BuffID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//BuffID
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_BuffName,CEnumCore::TagFormat::TLV_STRING,strlen(BuffName),(unsigned char *)mIni.wcharToChar(BuffName));//Buff名称
				}
				break;
			default:
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_TargetCharacter,CEnumCore::TagFormat::TLV_STRING,strlen(m_Name),(unsigned char *)mIni.wcharToChar(m_Name));//GM角色名
				break;
			}

			int midlength = socketdata.EnBody();
			switch(tbcResult.GetCurSel())
			{			
			case 1:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_MoveToPosition_Query);//传送玩家至指定位置
				break;
			case 2:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_MoveToRole_Query);//传送玩家至GM身边
				break;
			case 3:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_MoveToTargetRole_Query);//GM移动至指定角色身边
				break;
			case 4:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_AddBuff_Query);//添加BUFF
				break;
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_Edit"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//重置信息
void CXDGMManage::OnBnClickedBtnrecover()
{
	SetDlgItemText(IDC_EDITX,"0");
	SetDlgItemText(IDC_EDITY,"0");
	SetDlgItemText(IDC_EDITZ,"0");
	SetDlgItemText(IDC_EDITGMNAME,"");
	if(tbcResult.GetCurSel() == 4)
	{
		try
		{
			CIni mIni;

			int index = theApp.operXD.ReadIntValue("MXD","index");
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

			if((listBasic.GetItemCount() > 0) && (nItem>=0))
			{
				GetDlgItemText(IDC_EDITACCOUNT,UserName);
				GetDlgItemText(IDC_EDITNICK,UserNick);

				CSocketData socketdata;
				socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名

				_itoa(BuffID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_BuffID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//BuffID
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_BuffName,CEnumCore::TagFormat::TLV_STRING,strlen(BuffName),(unsigned char *)mIni.wcharToChar(BuffName));//Buff名称
			

				int userbyID = theApp.UserByID;
				_itoa(userbyID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员id

				int midlength = socketdata.EnBody();
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_RemoveBuff_Query_Resp);//移除BUFF
				
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

				socketdata.Destroy();
			}
		}
		catch(...)
		{
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_Item"),theApp.operXD.ReadValue("MXD","Error"),0);
		}	
	}
}

// 接收返回信息
LRESULT CXDGMManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{	
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);	
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
			if(pageBasic)//如果已经能够翻页
			{
				theApp.operXD.BuildDataTable(&socketdata,&listBasic,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operXD.BuildDataTable(&socketdata,&listBasic,&pageCount);//构造CListCtrl对象

				if(pageCount<0)//页数<=0，说明没有数据返回
				{
					nItem = -1;//不能选中某一行
					pageBasic = false;//不能翻页					
					cmbBasic.ResetContent();//清空页数复选框
					while(listBasic.DeleteColumn(0)){}//清空CListCtrl内容
				}
				else
				{
					nItem = 0;
					cmbBasic.ResetContent();//清空页数复选框，以便重新构造
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbBasic.AddString(str);//在复选框中构造页数信息
					}
					cmbBasic.SetCurSel(0);//在复选框中选中第一页
					if(pageCount == 1)
					{
						pageBasic = false;//只有一页数据，不能翻页
					}
					else
					{
						pageBasic = true;//有多页数据，可以翻页
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_BuffList_Query_Resp://BUFF列表查询
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int BuffID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::XDJG_BuffID).lpdata);//得到BuffID
				BuffList.SetAt(i,BuffID);//将BuffID保存在CMap类的对象BuffList中
			}
			theApp.operXD.BuildComboxs(&socketdata,&cmbList,CEnumCore::TagName::XDJG_BuffName);//构造Buff信息
		}
		break;
	default:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operXD.ShowResult(result);//显示返回结果

			SetDlgItemText(IDC_EDITX,"0");
			SetDlgItemText(IDC_EDITY,"0");
			SetDlgItemText(IDC_EDITZ,"0");
			SetDlgItemText(IDC_EDITGMNAME,"");
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

// 关闭对话框
void CXDGMManage::OnBnClickedCancel()
{
	ShowCoordinate(SW_HIDE);
	ShowTransferGM(SW_HIDE);
	ShowUserInfo(SW_SHOW);

	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// 关闭对话框
void CXDGMManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!BuffList.IsEmpty())
	{
		BuffList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//处理快捷键响应函数
BOOL CXDGMManage::PreTranslateMessage(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listBasic.m_hWnd)
				{
					theApp.operXD.CopyListInfo(&listBasic);				
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listBasic.m_hWnd)
				{
					for(int i=0; i<listBasic.GetItemCount(); i++)
					{
						listBasic.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listBasic.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

//用户基本资料信息页面
void CXDGMManage::ShowUserInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);
}

//传送至指定坐标页面
void CXDGMManage::ShowCoordinate(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLCOORDINATE,theApp.operXD.ReadValue("MXD","GMM_UI_Coordinate"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","Move"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITX,"0");
	SetDlgItemText(IDC_EDITY,"0");
	SetDlgItemText(IDC_EDITZ,"0");

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLCOORDINATE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLX)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITX)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLY)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITY)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLZ)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITZ)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

//玩家和GM互相传送至对方位置
void CXDGMManage::ShowTransferGM(int m_cmdShow)
{
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","Move"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITGMNAME,"");

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLGMNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITGMNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

//添加/移除BUFF页面
void CXDGMManage::ShowEditBuff(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLCOORDINATE,theApp.operXD.ReadValue("MXD","GMM_UI_BuffList"));
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITGMNAME,"");
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","Add"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","Remove"));

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLCOORDINATE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBLIST)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

