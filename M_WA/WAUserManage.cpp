// WAUserManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_WA.h"
#include "WAUserManage.h"
#include ".\wausermanage.h"

/*1、玩家账号管理：
可执行操作：
①、角色技能修改（添加/删除技能、修改技能等级）
②、游戏密码管理（可修改/恢复游戏账号临时密码和角色背包临时密码/其他密码）(角色背包密码,暂无此功能)
③、用户角色管理（恢复/删除角色）
④、角色信息管理（可对角色名、角色等级进行修改）*/

// CWAUserManage 对话框

IMPLEMENT_DYNAMIC(CWAUserManage, CDialog)
CWAUserManage::CWAUserManage(CWnd* pParent /*=NULL*/)
	: CDialog(CWAUserManage::IDD, pParent)
{
}

CWAUserManage::~CWAUserManage()
{
}

void CWAUserManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);

	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listResult);

	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_LISTCHARACTER, listUser);

	DDX_Control(pDX, IDC_CMBUSERPAGE, cmbUPage);
	DDX_Control(pDX, IDC_CMBSKILL, cmbList);
	DDX_Control(pDX, IDC_EDITNEW, CEditNew);
	DDX_Control(pDX, IDC_EDITOLD, CEditOld);
}


BEGIN_MESSAGE_MAP(CWAUserManage, CDialog)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabuiresult)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbuipage)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_LISTCHARACTER, OnNMClickListcharacter)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTCHARACTER, OnNMDblclkListcharacter)
	ON_CBN_SELCHANGE(IDC_CMBUSERPAGE, OnCbnSelchangeCmbuserpage)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTNEDIT, OnBnClickedBtnedit)
	ON_BN_CLICKED(IDC_BTNRECOVER, OnBnClickedBtnrecover)
	ON_BN_CLICKED(IDC_BTNEDITLVL, OnBnClickedBtneditlvl)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_BN_CLICKED(IDC_BTNDELSKILL, OnBnClickedBtndelskill)
	ON_CBN_SELCHANGE(IDC_CMBSKILL, OnCbnSelchangeCmbskill)	
END_MESSAGE_MAP()


// CWAUserManage 消息处理程序

// 初始化对话框
BOOL CWAUserManage::OnInitDialog()
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

	//maple add/////日志查询输入内容隐藏

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Create");//当前的状态为初始建立对话框

	if(theApp.operWA.GetServerList())//请求所有的游戏服务器列表
	{
		//MessageBox("t");
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
	}

	return TRUE;
}

// 初始化显示字符
void CWAUserManage::InitUI()
{
	SetWindowText(theApp.operWA.ReadValue("MWA","AM_UI_UserManage"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operWA.ReadValue("MWA","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operWA.ReadValue("MWA","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operWA.ReadValue("MWA","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operWA.ReadValue("MWA","Search"));
	SetDlgItemText(IDCANCEL,theApp.operWA.ReadValue("MWA","Reset"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operWA.ReadValue("MWA","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operWA.ReadValue("MWA","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operWA.ReadValue("MWA","AM_UI_SkillInfo"));	
	tbcResult.InsertItem(2,theApp.operWA.ReadValue("MWA","AM_UI_PwdEdit"));
	tbcResult.InsertItem(3,theApp.operWA.ReadValue("MWA","AM_UI_UserEdit"));
	tbcResult.InsertItem(4,theApp.operWA.ReadValue("MWA","AM_UI_InfoEdit"));
	tbcResult.InsertItem(5,theApp.operWA.ReadValue("MWA","AM_UI_RoleAttr"));
	//tbcResult.InsertItem(5,theApp.operWA.ReadValue("MWA","AM_UI_SkillEdit"));

	SetDlgItemText(IDC_LBLACCOUNT,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNICK,theApp.operWA.ReadValue("MWA","UIC_UI_lblNick"));
	SetDlgItemText(IDC_LBLSKILL,theApp.operWA.ReadValue("MWA","AM_UI_SkillName"));
	SetDlgItemText(IDC_LBLLEVEL,theApp.operWA.ReadValue("MWA","AM_UI_SkillLevel"));
	SetDlgItemText(IDC_BTNEDITLVL,theApp.operWA.ReadValue("MWA","AM_UI_EditLevel"));
	SetDlgItemText(IDC_BTNDELSKILL,theApp.operWA.ReadValue("MWA","AM_UI_DelSkill"));
}

// 自动改变大小
void CWAUserManage::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CWAUserManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询玩家资料信息
void CWAUserManage::OnBnClickedSearch()
{
	try
	{
		CIni mIni;

		tbcResult.SetCurSel(0);

		nItem = -1;//玩家资料列表没有选定项
		pageUInfo = false;//玩家资料列表不能翻页	
		cmbUPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		ShowSkillInfo(SW_HIDE);
		ShowPwdInfo(SW_HIDE);
		ShowNewSkill(SW_HIDE);
		ShowUserInfo(SW_SHOW);

		UpdateData(true);

		CString m_ServerName;
		GetDlgItemText(IDC_CMBSERVER,m_ServerName);//获取游戏服务器的名称
		if(m_ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_SelectServer"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//获取玩家帐号
		GetDlgItemText(IDC_EDITUINICK,UserNick);//获取玩家昵称
		if((UserName == "") && (UserNick == ""))//玩家帐号和玩家昵称不能同时为空
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_InputAccount"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		UserInfo();// 查询玩家资料信息
	}
	catch(...)
	{
	}
}

// 查询玩家资料信息
void CWAUserManage::UserInfo()
{	
	try
	{		
		CIni mIni;		

		int index = theApp.operWA.ReadIntValue("MWA","index");//查询第一页的信息
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//每页显示50条记录

		nItem = -1;//玩家资料列表没有选定项
		pageUInfo = false;//玩家资料列表不能翻页	
		cmbUPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query);//发送查询玩家资料信息的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_UserInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// 翻页查询玩家资料信息
void CWAUserManage::OnCbnSelchangeCmbuserpage()
{	
	try
	{	
		if(pageUInfo)//如果可以翻页的话
		{
			CIni mIni;	

			int index = cmbUPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//每页显示50条记录

			while(listUser.DeleteColumn(0)){}//清除页面内容

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query );//发送查询玩家资料信息的请求

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// 单击用户列表保存当前行号
void CWAUserManage::OnNMClickListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
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
void CWAUserManage::OnNMDblclkListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
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
				CIni mIni;
				pageInfo = false;
				cmbPage.ResetContent();
				while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

				ShowUserInfo(SW_HIDE);
				ShowPwdInfo(SW_HIDE);
				ShowNewSkill(SW_HIDE);				
				ShowSkillInfo(SW_SHOW);				

				if((listUser.GetItemCount() > 0) && (nItem >= 0))
				{
					UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// 保存选中的玩家帐号
					UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_NickID"));// 保存选中的玩家ID
					UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// 保存选中的玩家昵称
					
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

// 切换选项卡进行查询
void CWAUserManage::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// 保存选中的玩家帐号
	UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_NickID"));// 保存选中的玩家ID
	UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// 保存选中的玩家昵称

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

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
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

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
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

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
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
			ShowSkillInfo(SW_HIDE);
			ShowNewSkill(SW_HIDE);
			ShowPwdInfo(SW_HIDE);

			GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLNICK)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDITNICK)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTNEDIT)->ShowWindow(SW_SHOW);
			SetDlgItemText(IDC_BTNEDIT,theApp.operWA.ReadValue("MWA","AM_UI_RecoverAttr"));

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);
			}
		}
		break;
	//case 5:
	//	{
	//		ShowPwdInfo(SW_HIDE);		
	//		ShowUserInfo(SW_HIDE);
	//		ShowSkillInfo(SW_HIDE);
	//		ShowNewSkill(SW_SHOW);

	//		if((listUser.GetItemCount() > 0) && (nItem >= 0))
	//		{
	//			SetDlgItemText(IDC_EDITACCOUNT,UserName);
	//			SetDlgItemText(IDC_EDITNICK,UserNick);

	//			SearchSkill();
	//		}
	//	}
	//	break;
	default:
		break;
	}
	*pResult = 0;
}

// 查询角色技能信息
void CWAUserManage::SkillInfo()
{	
	try
	{		
		CIni mIni;
		pageInfo = false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_RoleSkill_Query );//查询角色技能信息

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Skill"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// 翻页进行查询
void CWAUserManage::OnCbnSelchangeCmbuipage()
{	
	try
	{
		if(pageInfo)
		{
			CIni mIni;

			int index = cmbPage.GetCurSel() + 1;
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

			while(listResult.DeleteColumn(0)){}

			if((listUser.GetItemCount() > 0) && (nItem>=0))
			{
				CSocketData socketdata;
				socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
				socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
				socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
				socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//玩家IDKEY

				_itoa(index,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

				_itoa(iPageSize,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

				int midlength = socketdata.EnBody();				
				theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_RoleSkill_Query);// 查询角色技能信息

				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
				socketdata.Destroy();
			}
		}		
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Page"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

//选择相应的技能信息进行修改
void CWAUserManage::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
				SkillID = atoi(theApp.operWA.GetValueByColName(&listResult, nListItem, theApp.operWA.ReadValue("MWA","WA_SkillID")));// 保存选中的技能ID
				SkillName = theApp.operWA.GetValueByColName(&listResult, nListItem, theApp.operWA.ReadValue("MWA","WA_SkillName"));// 保存选中的技能名称
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
void CWAUserManage::OnBnClickedBtneditlvl()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listResult.GetItemCount() > 0) && (nListItem>=0))
		{		
			GetDlgItemText(IDC_EDITSKILL,SkillName);//获取技能名称
			if(SkillName == "")//要修改的技能名称不能为空
			{
				MessageBox(theApp.operWA.ReadValue("MWA","AM_Warn_EditSkillNone"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}

			CString newValue; //修改后的技能等级
			GetDlgItemText(IDC_EDITLEVEL,newValue);//获取技能等级
			if(newValue == "")//要修改的技能等级不能为空
			{
				MessageBox(theApp.operWA.ReadValue("MWA","AM_Warn_NewSkillLevel"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// 保存选中的玩家帐号
			UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_NickID"));// 保存选中的玩家ID
			UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// 保存选中的玩家昵称

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY

			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员id

			_itoa(SkillID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::WA_SkillID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//技能ID

			socketdata.AddTFLV(CEnumCore::TagName::WA_SkillName,CEnumCore::TagFormat::TLV_STRING,strlen(SkillName),(unsigned char *)mIni.wcharToChar(SkillName));//技能名称
			socketdata.AddTFLV(CEnumCore::TagName::WA_SkillLvl,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//技能等级

			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_ModifyCharacterSkill);//修改技能等级

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_EditSkill"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

//删除选中的角色技能信息
void CWAUserManage::OnBnClickedBtndelskill()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listResult.GetItemCount() > 0) && (nListItem>=0))
		{		
			GetDlgItemText(IDC_EDITSKILL,SkillName);//获取技能名称
			if(SkillName == "")//要删除的技能名称不能为空
			{
				MessageBox(theApp.operWA.ReadValue("MWA","AM_Warn_DelSkillNone"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// 保存选中的玩家帐号
			UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_NickID"));// 保存选中的玩家ID
			UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// 保存选中的玩家昵称

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY

			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员id

			socketdata.AddTFLV(CEnumCore::TagName::WA_SkillName,CEnumCore::TagFormat::TLV_STRING,strlen(SkillName),(unsigned char *)mIni.wcharToChar(SkillName));//技能名称
			
			int midlength = socketdata.EnBody();
			//theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_ModifyCharacterSkill);//删除角色技能

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_EditSkill"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

//查询所有可以添加的技能信息
void CWAUserManage::SearchSkill()
{
	try
	{		
		CIni mIni;

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// 保存选中的玩家帐号
			UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_NickID"));// 保存选中的玩家ID
			UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// 保存选中的玩家昵称

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY

			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_SkillList_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_SearchSkill"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

//修改或添加信息
void CWAUserManage::OnBnClickedBtnedit()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{			
			CString newValue; //修改后的值
			//if(tbcResult.GetCurSel()==5)//添加新技能时
			//{
			//	GetDlgItemText(IDC_CMBSKILL,SkillName);//获取技能名称
			//	if(SkillName == "")//添加技能不能为空
			//	{
			//		MessageBox(theApp.operWA.ReadValue("MWA","AM_Warn_SkillNone"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			//		return;
			//	}
			//}
			if(tbcResult.GetCurSel()==2)//修改用户密码时
			{
				GetDlgItemText(IDC_EDITOLD,newValue);	
				if(newValue=="") //新密码不能为空
				{
					MessageBox(theApp.operWA.ReadValue("MWA","AM_Warn_InputNPwd"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
				CString newPassAG; //重复新密码
				GetDlgItemText(IDC_EDITNEW,newPassAG);	
				if(newPassAG=="") //重复新密码不能为空
				{
					MessageBox(theApp.operWA.ReadValue("MWA","AM_Warn_InputNPwdAG"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
				if(newPassAG!=newValue) //密码前后要相同
				{
					MessageBox(theApp.operWA.ReadValue("MWA","AM_Warn_PwdNotSame"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}		
			}
			else if(tbcResult.GetCurSel()==4)//角色信息管理
			{
				GetDlgItemText(IDC_EDITNEW,newValue);	
				if(newValue=="") //修改后的值不能为空
				{
					MessageBox(theApp.operWA.ReadValue("MWA","AM_Warn_NewValue"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
			}

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// 保存选中的玩家帐号
			UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_NickID"));// 保存选中的玩家ID
			UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// 保存选中的玩家昵称

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY

			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员id

			switch(tbcResult.GetCurSel())
			{
			//case 5:
			//	socketdata.AddTFLV(CEnumCore::TagName::WA_SkillName,CEnumCore::TagFormat::TLV_STRING,strlen(SkillName),(unsigned char *)mIni.wcharToChar(SkillName));//技能名称
			//	break;
			case 2:
				socketdata.AddTFLV(CEnumCore::TagName::WA_NewPasswd,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//新密码
				break;
			case 4:
				{
					//int iType=cmbList.GetCurSel();
					_itoa(1,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::WA_TYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//类型
					socketdata.AddTFLV(CEnumCore::TagName::WA_Level,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//新等级

					//if(cmbList.GetCurSel()==0)
					//	socketdata.AddTFLV(CEnumCore::TagName::WA_NewRole,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//新角色名
					//else if(cmbList.GetCurSel()==1)					
					//	socketdata.AddTFLV(CEnumCore::TagName::WA_Level,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//新等级
					//else if(cmbList.GetCurSel()==2)					
					//  socketdata.AddTFLV(CEnumCore::TagName::WA_Money,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//新金钱	
				}
				break;
			}

			int midlength = socketdata.EnBody();
			switch(tbcResult.GetCurSel())
			{
			//case 5:
			//	//theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_ModifyCharacterSkill);//添加角色技能
			//	break;
			case 2:
				theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_ModifyAccountPassw);//修改密码
				break;
			case 3:
				theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_RecoverCharacter);//恢复角色
				break;
			case 4:
				{
					//if(cmbList.GetCurSel()==0)
						//theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_PlayerRole_Modfiy);//修改角色名
					//else if(cmbList.GetCurSel()==1)
						theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_RoleInfo_Modfiy);//修改角色属性值(改钱,改名,改等级)
				}
				break;
			case 5:
				theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_ResumeAttribute_Op);//修改密码
				break;
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Edit"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

//删除或恢复信息
void CWAUserManage::OnBnClickedBtnrecover()
{
	try
	{		
		cmbList.SetCurSel(0);
		SetDlgItemText(IDC_EDITOLD,"");
		SetDlgItemText(IDC_EDITNEW,"");	

		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// 保存选中的玩家帐号
			UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_NickID"));// 保存选中的玩家ID
			UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// 保存选中的玩家昵称

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY

			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员id

			int midlength = socketdata.EnBody();
			switch(tbcResult.GetCurSel())
			{
			case 2:
				theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Query_ResumePassw);//恢复密码
				break;
			case 4:
				//theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_RecoverCharacter);//删除角色
				break;
			}

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Item"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// 接收返回信息
LRESULT CWAUserManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{	
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Receive");//当前的状态为接收到了返回信息

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
			theApp.operWA.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Account_Query_Resp://查询玩家资料信息的回应
		{
			if(pageUInfo)//如果已经能够翻页
			{
				theApp.operWA.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象

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
	case CEnumCore::Message_Tag_ID::WA_RoleSkill_Query_Resp://查询玩家身上技能信息
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

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
	case CEnumCore::Message_Tag_ID::WA_SkillList_Query_Resp://查询所有的技能信息
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int SkillID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::WA_SkillID).lpdata);//得到技能ID
				SkillList.SetAt(i,SkillID);//将技能ID保存在CMap类的对象SkillList中
			}
			theApp.operWA.BuildCombox(&socketdata,&cmbList,2);//构造技能信息
		}
		break;
	default:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//显示返回结果

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
void CWAUserManage::OnBnClickedCancel()
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
void CWAUserManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//处理快捷键响应函数
BOOL CWAUserManage::PreTranslateMessage(MSG* pMsg)
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
					theApp.operWA.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listResult);
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

void CWAUserManage::OnCbnSelchangeCmbskill()
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


void CWAUserManage::ShowUserInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);
}

void CWAUserManage::ShowSkillInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSKILL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSKILL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLLEVEL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITLEVEL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDITLVL)->ShowWindow(m_cmdShow);
	//GetDlgItem(IDC_BTNDELSKILL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_EDITSKILL,"");
	SetDlgItemText(IDC_EDITLEVEL,"");
}

void CWAUserManage::ShowNewSkill(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operWA.ReadValue("MWA","AM_UI_NewSkill"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operWA.ReadValue("MWA","AM_UI_Add"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operWA.ReadValue("MWA","AM_UI_Reset"));

	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	cmbList.ResetContent();

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLOLD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBSKILL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

void CWAUserManage::ShowPwdInfo(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operWA.ReadValue("MWA","AM_UI_NewPwd"));
	SetDlgItemText(IDC_LBLNEW,theApp.operWA.ReadValue("MWA","AM_UI_ReNewPwd"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operWA.ReadValue("MWA","AM_UI_EditPwd"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operWA.ReadValue("MWA","AM_UI_RecoverPwd"));
	//SetDlgItemText(IDC_BTNRECOVER,theApp.operWA.ReadValue("MWA","AM_UI_Reset"));

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

void CWAUserManage::ShowManageInfo(int m_cmdShow)
{
	SetDlgItemText(IDC_BTNEDIT,theApp.operWA.ReadValue("MWA","AM_UI_RecoverRole"));
	//SetDlgItemText(IDC_BTNRECOVER,theApp.operWA.ReadValue("MWA","AM_UI_DelRole"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operWA.ReadValue("MWA","AM_UI_Reset"));

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

void CWAUserManage::ShowAccountInfo(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operWA.ReadValue("MWA","AM_UI_Type"));
	SetDlgItemText(IDC_LBLNEW,theApp.operWA.ReadValue("MWA","AM_UI_NewValue"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operWA.ReadValue("MWA","AM_UI_Edit"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operWA.ReadValue("MWA","AM_UI_Reset"));

	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITNEW,"");
	cmbList.ResetContent();
	//cmbList.AddString(theApp.operWA.ReadValue("MWA","AM_UI_RoleName"));
	cmbList.AddString(theApp.operWA.ReadValue("MWA","AM_UI_Level"));
	//cmbList.AddString(theApp.operWA.ReadValue("MWA","AM_UI_Money"));
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
