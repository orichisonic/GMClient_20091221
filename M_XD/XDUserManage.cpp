// XDUserManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_XD.h"
#include "XDUserManage.h"
#include ".\xdusermanage.h"


// CXDUserManage 对话框

IMPLEMENT_DYNAMIC(CXDUserManage, CDialog)
CXDUserManage::CXDUserManage(CWnd* pParent /*=NULL*/)
	: CDialog(CXDUserManage::IDD, pParent)
{
}

CXDUserManage::~CXDUserManage()
{
}

void CXDUserManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);

	DDX_Control(pDX, IDC_TABRESULT, tbcResult);

	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBBASIC, cmbBasic);
	DDX_Control(pDX, IDC_CMBRESULT, cmbResult);

	DDX_Control(pDX, IDC_LISTBASIC, listBasic);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);	
		
	DDX_Control(pDX, IDC_CMBSKILL, cmbList);
	DDX_Control(pDX, IDC_EDITNEW, CEditNew);
	DDX_Control(pDX, IDC_EDITOLD, CEditOld);
}


BEGIN_MESSAGE_MAP(CXDUserManage, CDialog)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_CMBBASIC, OnCbnSelchangeCmbbasic)
	ON_CBN_SELCHANGE(IDC_CMBRESULT, OnCbnSelchangeCmbresult)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTBASIC, OnNMClickListbasic)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTBASIC, OnNMDblclkListbasic)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)

	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	
	ON_BN_CLICKED(IDC_BTNEDIT, OnBnClickedBtnedit)
	ON_BN_CLICKED(IDC_BTNRECOVER, OnBnClickedBtnrecover)
	ON_BN_CLICKED(IDC_BTNEDITLVL, OnBnClickedBtneditlvl)
	ON_BN_CLICKED(IDC_BTNDELSKILL, OnBnClickedBtndelskill)
	ON_CBN_SELCHANGE(IDC_CMBSKILL, OnCbnSelchangeCmbskill)	
	
END_MESSAGE_MAP()


// CXDUserManage 消息处理程序

// 初始化对话框
BOOL CXDUserManage::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// 初始化显示字符

	nItem = -1;
	pageResult = false;
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

		if(listResult.m_hWnd != NULL)
		{
			listResult.MoveWindow(newRect);//设置好listResult的位置，listResult和listBasic的位置完全重叠
		}
	}

	//maple add/////日志查询输入内容隐藏

	dlgStatus = theApp.operXD.ReadIntValue("MXD","Create");//当前的状态为初始建立对话框

	if(theApp.operXD.GetServerList())//请求所有的游戏服务器列表
	{
		//MessageBox("t");
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
	}

	return TRUE;
}

// 初始化显示字符
void CXDUserManage::InitUI()
{
	SetWindowText(theApp.operXD.ReadValue("MXD","UM_UI_UserManage"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operXD.ReadValue("MXD","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operXD.ReadValue("MXD","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operXD.ReadValue("MXD","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operXD.ReadValue("MXD","Search"));
	SetDlgItemText(IDCANCEL,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operXD.ReadValue("MXD","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operXD.ReadValue("MXD","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operXD.ReadValue("MXD","UM_UI_SkillInfo"));	
	tbcResult.InsertItem(2,theApp.operXD.ReadValue("MXD","UM_UI_PwdEdit"));
	tbcResult.InsertItem(3,theApp.operXD.ReadValue("MXD","UM_UI_UserEdit"));
	tbcResult.InsertItem(4,theApp.operXD.ReadValue("MXD","UM_UI_InfoEdit"));
	tbcResult.InsertItem(5,theApp.operXD.ReadValue("MXD","UM_UI_SkillEdit"));
	//tbcResult.InsertItem(6,theApp.operXD.ReadValue("MXD","UM_UI_TitleEdit"));

	SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNICK,theApp.operXD.ReadValue("MXD","UIC_UI_lblNick"));
	SetDlgItemText(IDC_LBLSKILL,theApp.operXD.ReadValue("MXD","UM_UI_SkillName"));
	SetDlgItemText(IDC_LBLLEVEL,theApp.operXD.ReadValue("MXD","UM_UI_SkillLevel"));
	SetDlgItemText(IDC_BTNEDITLVL,theApp.operXD.ReadValue("MXD","UM_UI_EditLevel"));
	SetDlgItemText(IDC_BTNDELSKILL,theApp.operXD.ReadValue("MXD","UM_UI_DelSkill"));
}

// 自动改变大小
void CXDUserManage::OnSize(UINT nType, int cx, int cy)
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

		if(listResult.m_hWnd != NULL)
		{
			listResult.MoveWindow(newRect);//设置好listResult的位置
		}
	}
}

//设置背景颜色
HBRUSH CXDUserManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询玩家资料信息
void CXDUserManage::OnBnClickedSearch()
{
	try
	{
		CIni mIni;

		tbcResult.SetCurSel(0);

		nItem = -1;//玩家资料列表没有选定项
		pageBasic = false;//玩家资料列表不能翻页	
		cmbBasic.ResetContent();//清除玩家资料列表翻页的复选框
		while(listBasic.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		ShowSkillInfo(SW_HIDE);
		ShowPwdInfo(SW_HIDE);
		ShowNewSkill(SW_HIDE);
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
void CXDUserManage::UserInfo()
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
void CXDUserManage::OnCbnSelchangeCmbbasic()
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
void CXDUserManage::OnNMClickListbasic(NMHDR *pNMHDR, LRESULT *pResult)
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
void CXDUserManage::OnNMDblclkListbasic(NMHDR *pNMHDR, LRESULT *pResult)
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
				CIni mIni;
				pageResult = false;
				cmbResult.ResetContent();
				while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

				ShowUserInfo(SW_HIDE);
				ShowPwdInfo(SW_HIDE);
				ShowNewSkill(SW_HIDE);
				ShowSkillInfo(SW_SHOW);

				if((listBasic.GetItemCount() > 0) && (nItem >= 0))
				{
					UserName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// 保存选中的玩家帐号
					//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","WA_NickID"));// 保存选中的玩家ID
					UserNick = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// 保存选中的玩家昵称
						
					tbcResult.SetCurSel(1);
					SkillInfo();
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
void CXDUserManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	UserName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// 保存选中的玩家帐号
	//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_AccountID"));// 保存选中的玩家ID
	UserNick = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// 保存选中的玩家昵称

	switch(tbcResult.GetCurSel())
	{
	case 0:
		{
			ShowSkillInfo(SW_HIDE);
			ShowPwdInfo(SW_HIDE);
			ShowNewSkill(SW_HIDE);
			ShowUserInfo(SW_SHOW);
		}
		break;
	case 1:
		{
			ShowPwdInfo(SW_HIDE);
			ShowNewSkill(SW_HIDE);
			ShowUserInfo(SW_HIDE);
			ShowSkillInfo(SW_SHOW);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SkillInfo();
			}
		}
		break;
	case 2:
		{				
			ShowUserInfo(SW_HIDE);
			ShowSkillInfo(SW_HIDE);
			ShowNewSkill(SW_HIDE);
			ShowPwdInfo(SW_SHOW);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);
			}	
		}
		break;
	case 3:
		{
			ShowUserInfo(SW_HIDE);
			ShowSkillInfo(SW_HIDE);
			ShowNewSkill(SW_HIDE);
			ShowPwdInfo(SW_HIDE);
			ShowManageInfo(SW_SHOW);

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
			ShowSkillInfo(SW_HIDE);
			ShowNewSkill(SW_HIDE);
			ShowPwdInfo(SW_HIDE);
			ShowAccountInfo(SW_SHOW);

			CEditNew.ModifyStyle(0,ES_NUMBER);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);
			}
		}
		break;
	case 5:
		{
			ShowPwdInfo(SW_HIDE);		
			ShowUserInfo(SW_HIDE);
			ShowSkillInfo(SW_HIDE);
			ShowNewSkill(SW_SHOW);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);

				SearchSkill();
			}
		}
		break;
	case 6:
		{
			ShowPwdInfo(SW_HIDE);		
			ShowUserInfo(SW_HIDE);
			ShowSkillInfo(SW_HIDE);
			ShowEditTitle(SW_SHOW);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);

				SearchTitle();
			}
		}
		break;
	default:
		break;
	}
	*pResult = 0;
}

// 查询相关资料信息
void CXDUserManage::SkillInfo()
{	
	try
	{		
		CIni mIni;
		pageResult = false;
		cmbResult.ResetContent();
		while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listBasic.GetItemCount() > 0) && (nItem>=0))
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
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_RoleSkills_Query );//查询角色技能信息

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_Skill"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

// 翻页进行查询
void CXDUserManage::OnCbnSelchangeCmbresult()
{	
	try
	{
		if(pageResult)
		{
			CIni mIni;

			int index = cmbResult.GetCurSel() + 1;
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

			while(listResult.DeleteColumn(0)){}

			if((listBasic.GetItemCount() > 0) && (nItem>=0))
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
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_RoleSkills_Query);// 查询角色技能信息

				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
				socketdata.Destroy();
			}
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_Page"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//单击相关资料信息列表进行选择
void CXDUserManage::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 1)
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
				SkillID = atoi(theApp.operXD.GetValueByColName(&listResult, nListItem, theApp.operXD.ReadValue("MXD","XDJG_SkillID")));// 保存选中的技能ID
				SkillName = theApp.operXD.GetValueByColName(&listResult, nListItem, theApp.operXD.ReadValue("MXD","XDJG_SkillName"));// 保存选中的技能名称
				SetDlgItemText(IDC_EDITSKILL,SkillName);
			}
		}
		else
		{
			nListItem = -1;
		}
	}
	*pResult = 0;
}

//修改选中的角色技能信息
void CXDUserManage::OnBnClickedBtneditlvl()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listResult.GetItemCount() > 0) && (nListItem>=0))
		{		
			GetDlgItemText(IDC_EDITSKILL,SkillName);//获取技能名称
			if(SkillName == "")//要修改的技能名称不能为空
			{
				MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_EditSkillNone"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}

			CString newValue; //修改后的技能等级
			GetDlgItemText(IDC_EDITLEVEL,newValue);//获取技能等级
			if(newValue == "")//要修改的技能等级不能为空
			{
				MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_NewSkillLevel"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
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

			_itoa(SkillID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_SkillID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//技能ID

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_SkillName,CEnumCore::TagFormat::TLV_STRING,strlen(SkillName),(unsigned char *)mIni.wcharToChar(SkillName));//技能名称
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Level,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//技能等级

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ModifyLevel_operate);//修改技能等级

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_EditSkill"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//删除选中的角色技能信息
void CXDUserManage::OnBnClickedBtndelskill()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listResult.GetItemCount() > 0) && (nListItem>=0))
		{		
			GetDlgItemText(IDC_EDITSKILL,SkillName);//获取技能名称
			if(SkillName == "")//要删除的技能名称不能为空
			{
				MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_DelSkillNone"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
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

			_itoa(SkillID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_SkillID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//技能ID
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_SkillName,CEnumCore::TagFormat::TLV_STRING,strlen(SkillName),(unsigned char *)mIni.wcharToChar(SkillName));//技能名称
			
			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_RoleSkillDel);//删除角色技能

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_EditSkill"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//查询所有可以添加的技能信息
void CXDUserManage::SearchSkill()
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
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_SkillList_Query);

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

//查询所有称号信息
void CXDUserManage::SearchTitle()
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
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_TitleList_Query);

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

//修改或添加信息
void CXDUserManage::OnBnClickedBtnedit()
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

			CString newValue; //修改后的值
			if(tbcResult.GetCurSel()==2)//修改用户密码时
			{
				GetDlgItemText(IDC_EDITOLD,newValue);	
				if(newValue=="") //新密码不能为空
				{
					MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_InputNPwd"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
				CString newPassAG; //重复新密码
				GetDlgItemText(IDC_EDITNEW,newPassAG);	
				if(newPassAG=="") //重复新密码不能为空
				{
					MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_InputNPwdAG"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
				if(newPassAG!=newValue) //密码前后要相同
				{
					MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_PwdNotSame"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}		
			}
			else if(tbcResult.GetCurSel()==4)//角色信息管理
			{
				GetDlgItemText(IDC_EDITNEW,newValue);	
				if(newValue=="") //修改后的值不能为空
				{
					MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_NewValue"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
			}
			else if(tbcResult.GetCurSel()==5)//添加新技能时
			{
				GetDlgItemText(IDC_CMBSKILL,SkillName);//获取技能名称
				if(SkillName == "")//添加技能不能为空
				{
					MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_SkillNone"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
				SkillList.Lookup(cmbList.GetCurSel()+1,SkillID);//从CMap类的对象SkillList中获取SkillID

				GetDlgItemText(IDC_EDITNEW,newValue);	
				//if(newValue=="") //技能等级不能为空
				//{
				//	MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_SkillLevel"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				//	return;
				//}
			}
			else if(tbcResult.GetCurSel()==6)//添加新称号时
			{
				GetDlgItemText(IDC_CMBSKILL,TitleName);//获取称号名称
				if(TitleName == "")//添加称号不能为空
				{
					return;
				}
				TitleList.Lookup(cmbList.GetCurSel()+1,TitleID);//从CMap类的对象TitleList中获取TitleID
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
			case 5:
				{
					_itoa(SkillID,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_SkillID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//技能ID
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_SkillName,CEnumCore::TagFormat::TLV_STRING,strlen(SkillName),(unsigned char *)mIni.wcharToChar(SkillName));//技能名称
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_Level,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//技能等级
				}
				break;
			case 2:
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_Pwd,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//新密码
				break;
			case 4:
				{
					if(cmbList.GetCurSel()==0)
					{
						_itoa(1,strInt,10);
						socketdata.AddTFLV(CEnumCore::TagName::XDJG_UpdateType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//类型：1、等级
						socketdata.AddTFLV(CEnumCore::TagName::XDJG_Level,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//新等级
					}
					else if(cmbList.GetCurSel()==1)
					{
						_itoa(2,strInt,10);
						socketdata.AddTFLV(CEnumCore::TagName::XDJG_UpdateType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//类型：2、经验
						socketdata.AddTFLV(CEnumCore::TagName::XDJG_Exp,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//新金钱
					}
					//else if(cmbList.GetCurSel()==2)
						//socketdata.AddTFLV(CEnumCore::TagName::WA_NewRole,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//新角色名
				}
				break;
			case 6:
				{
					_itoa(TitleID,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_TitleID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//称号ID
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_TitleName,CEnumCore::TagFormat::TLV_STRING,strlen(TitleName),(unsigned char *)mIni.wcharToChar(TitleName));//称号名称
				}
				break;
			}

			int midlength = socketdata.EnBody();
			switch(tbcResult.GetCurSel())
			{			
			case 2:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ModifyPwd_operate);//修改密码
				break;
			case 3:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_DeleteRole_operate);//删除角色
				break;
			case 4:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ModifyLevel_operate);//修改等级
				break;
			case 5:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_RoleSkillAdd);//添加角色技能
				break;
			case 6:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_AddTitle_Query);//添加称号
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

//删除或恢复信息
void CXDUserManage::OnBnClickedBtnrecover()
{
	try
	{		
		cmbList.SetCurSel(0);
		SetDlgItemText(IDC_EDITOLD,"");
		SetDlgItemText(IDC_EDITNEW,"");	

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

			switch(tbcResult.GetCurSel())
			{
			case 6:
				{
					_itoa(TitleID,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_TitleID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//称号ID
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_TitleName,CEnumCore::TagFormat::TLV_STRING,strlen(TitleName),(unsigned char *)mIni.wcharToChar(TitleName));//称号名称
				}
				break;
			}

			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员id

			int midlength = socketdata.EnBody();
			switch(tbcResult.GetCurSel())
			{
			case 2:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ResumePwd_operate);//恢复密码
				break;
			case 3:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ResumeRole_operate);//恢复角色
				break;
			case 6:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_RemoveTitle_Query);//移除称号
				break;
			}

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

// 接收返回信息
LRESULT CXDUserManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::XDJG_RoleSkills_Query_Resp://查询玩家身上技能信息
		{
			if(pageResult)//如果已经能够翻页
			{
				theApp.operXD.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operXD.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

				if(pageCount<0)//页数<=0，说明没有数据返回
				{
					pageResult = false;//不能翻页		
					cmbResult.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					cmbResult.ResetContent();
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbResult.AddString(str);
					}
					cmbResult.SetCurSel(0);
					if(pageCount == 1)
					{
						pageResult = false;
					}
					else
					{
						pageResult = true;
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_SkillList_Query_Resp://查询所有的技能信息
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int SkillID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::XDJG_SkillID).lpdata);//得到技能ID
				SkillList.SetAt(i,SkillID);//将技能ID保存在CMap类的对象SkillList中
			}
			theApp.operXD.BuildComboxs(&socketdata,&cmbList,CEnumCore::TagName::XDJG_SkillName);//构造技能信息
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_TitleList_Query_Resp://称号列表查询
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int TitleID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::XDJG_TitleID).lpdata);//得到称号ID
				TitleList.SetAt(i,TitleID);//将称号ID保存在CMap类的对象TitleList中
			}
			theApp.operXD.BuildComboxs(&socketdata,&cmbList,CEnumCore::TagName::XDJG_TitleName);//构造称号信息
		}
		break;
	default:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operXD.ShowResult(result);//显示返回结果

			cmbList.SetCurSel(0);
			SetDlgItemText(IDC_EDITOLD,"");
			SetDlgItemText(IDC_EDITNEW,"");
			SetDlgItemText(IDC_EDITLEVEL,"");
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

// 关闭对话框
void CXDUserManage::OnBnClickedCancel()
{
	ShowSkillInfo(SW_HIDE);
	ShowPwdInfo(SW_HIDE);
	GetDlgItem(IDC_CMBSKILL)->ShowWindow(SW_HIDE);		
	ShowUserInfo(SW_SHOW);

	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// 关闭对话框
void CXDUserManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!SkillList.IsEmpty())
	{
		SkillList.RemoveAll();
	}
	if(!TitleList.IsEmpty())
	{
		TitleList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//处理快捷键响应函数
BOOL CXDUserManage::PreTranslateMessage(MSG* pMsg)
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
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operXD.CopyListInfo(&listResult);
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

void CXDUserManage::OnCbnSelchangeCmbskill()
{
	SetDlgItemText(IDC_EDITNEW,"");
	if(tbcResult.GetCurSel()==4)
	{
		//if(cmbList.GetCurSel()==0)
		//    CEditNew.ModifyStyle(ES_NUMBER,0);
		//else
		CEditNew.ModifyStyle(0,ES_NUMBER);
	}
}

//用户基本资料信息页面
void CXDUserManage::ShowUserInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);
}

//用户技能信息页面
void CXDUserManage::ShowSkillInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBRESULT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSKILL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSKILL)->ShowWindow(m_cmdShow);
	//GetDlgItem(IDC_LBLLEVEL)->ShowWindow(m_cmdShow);
	//GetDlgItem(IDC_EDITLEVEL)->ShowWindow(m_cmdShow);
	//GetDlgItem(IDC_BTNEDITLVL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNDELSKILL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_EDITSKILL,"");
	SetDlgItemText(IDC_EDITLEVEL,"");
}

//修改/恢复用户密码页面
void CXDUserManage::ShowPwdInfo(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operXD.ReadValue("MXD","UM_UI_NewPwd"));
	SetDlgItemText(IDC_LBLNEW,theApp.operXD.ReadValue("MXD","UM_UI_ReNewPwd"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","UM_UI_EditPwd"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","UM_UI_RecoverPwd"));

	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITOLD,"");
	SetDlgItemText(IDC_EDITNEW,"");

	CEditOld.SetPasswordChar('*');
	CEditOld.ModifyStyle(0,ES_PASSWORD,0);
	CEditNew.SetPasswordChar('*');
	CEditNew.ModifyStyle(0,ES_PASSWORD,0);

	CEditNew.ModifyStyle(ES_NUMBER,0);

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLOLD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITOLD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

//删除/恢复用户页面
void CXDUserManage::ShowManageInfo(int m_cmdShow)
{
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","UM_UI_DelRole"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","UM_UI_RecoverRole"));

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

//修改用户角色名/等级/金钱页面
void CXDUserManage::ShowAccountInfo(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operXD.ReadValue("MXD","UM_UI_Type"));
	SetDlgItemText(IDC_LBLNEW,theApp.operXD.ReadValue("MXD","UM_UI_NewValue"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","UM_UI_Edit"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","UM_UI_Reset"));

	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITNEW,"");
	cmbList.ResetContent();
	//cmbList.AddString(theApp.operXD.ReadValue("MXD","UM_UI_RoleName"));
	cmbList.AddString(theApp.operXD.ReadValue("MXD","UM_UI_Level"));	
	//cmbList.AddString(theApp.operXD.ReadValue("MXD","UM_UI_Money"));
	cmbList.AddString(theApp.operXD.ReadValue("MXD","UM_UI_Exp"));
	cmbList.SetCurSel(0);

	CEditNew.SetPasswordChar(NULL);
	CEditNew.ModifyStyle(ES_PASSWORD,0);
	CEditNew.ModifyStyle(ES_NUMBER,0);

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLOLD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBSKILL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

//添加新技能页面
void CXDUserManage::ShowNewSkill(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operXD.ReadValue("MXD","UM_UI_NewSkill"));
	//SetDlgItemText(IDC_LBLNEW,theApp.operXD.ReadValue("MXD","UM_UI_SkillLevel"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","UM_UI_Add"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","UM_UI_Reset"));

	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	cmbList.ResetContent();

	//CEditNew.SetPasswordChar(NULL);
	//CEditNew.ModifyStyle(ES_PASSWORD,0);
	//SetDlgItemText(IDC_EDITNEW,"0");
	//CEditNew.ModifyStyle(0,ES_NUMBER);

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLOLD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBSKILL)->ShowWindow(m_cmdShow);
	//GetDlgItem(IDC_LBLNEW)->ShowWindow(m_cmdShow);
	//GetDlgItem(IDC_EDITNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

//添加/移除称号页面
void CXDUserManage::ShowEditTitle(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operXD.ReadValue("MXD","UM_UI_TitleList"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","Add"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","Remove"));

	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	cmbList.ResetContent();

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLOLD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBSKILL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}
