// CG2UpdateSkill.cpp : 实现文件
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2UpdateSkill.h"
#include ".\cg2updateskill.h"


// CCG2UpdateSkill 对话框


IMPLEMENT_DYNCREATE(CCG2UpdateSkill, CDialog)

CCG2UpdateSkill::CCG2UpdateSkill(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2UpdateSkill::IDD, pParent)
{
}

CCG2UpdateSkill::~CCG2UpdateSkill()
{
}

void CCG2UpdateSkill::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBNEWLEVEL, cmbNewLevel);
	DDX_Control(pDX, IDC_LISTSKILLINFO, listSkill);
	DDX_Control(pDX, IDC_CMBSKILLPAGE, cmbSkillPage);
	DDX_Control(pDX, IDC_CMBNEWLEVEL, cmbNewLevel);
	DDX_Control(pDX, IDC_CMBSKILLTYPE, cmbSkillType);
	DDX_Control(pDX, IDC_CMBSKILLNAME, cmbSkillName);
}

BEGIN_MESSAGE_MAP(CCG2UpdateSkill, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_NOTIFY(NM_CLICK, IDC_LISTSKILLINFO, OnNMClickListskillinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTSKILLINFO, OnNMDblclkListskillinfo)
	ON_BN_CLICKED(IDC_BTUPDATE, OnBnClickedBtupdate)
	ON_BN_CLICKED(IDC_BTRESET, OnBnClickedBtreset)
	ON_BN_CLICKED(IDC_BTADDSKILL, OnBnClickedBtaddskill)
	ON_BN_CLICKED(IDC_BTRESETSKILL, OnBnClickedBtresetskill)


ON_CBN_SELCHANGE(IDC_CMBSKILLTYPE, OnCbnSelchangeCmbskilltype)

END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CCG2UpdateSkill)

END_DHTML_EVENT_MAP()





// 初始化显示字符
void CCG2UpdateSkill::InitUI()
{
	//OperationCG2 theApp.operCG2;

	SetWindowText(theApp.operCG2.ReadValue("MCG2","CG2_UI_UpdateSkill"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operCG2.ReadValue("MCG2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));
	SetDlgItemText(IDC_BTUPDATE,theApp.operCG2.ReadValue("MCG2","Update"));
	SetDlgItemText(IDC_BTRESET,theApp.operCG2.ReadValue("MCG2","Reset"));

	SetDlgItemText(IDC_BTSEARCH,theApp.operCG2.ReadValue("MCG2","Search"));


	SetDlgItemText(IDC_STATICSKILL,theApp.operCG2.ReadValue("MCG2","US_UI_Skill"));
	SetDlgItemText(IDC_STATICCURLEVEL,theApp.operCG2.ReadValue("MCG2","US_UI_CurrentLevel"));
	SetDlgItemText(IDC_STATICNEWLEVEL,theApp.operCG2.ReadValue("MCG2","US_UI_NewLevel"));
	SetDlgItemText(IDC_STATICSKILLTYPE,theApp.operCG2.ReadValue("MCG2","US_UI_SkillType"));
	SetDlgItemText(IDC_STATICSKILLNAME,theApp.operCG2.ReadValue("MCG2","US_UI_Skill"));
	SetDlgItemText(IDC_STATICSKILLLEVEL,theApp.operCG2.ReadValue("MCG2","US_UI_SkillLevel"));
	SetDlgItemText(IDC_BTUPDATE,theApp.operCG2.ReadValue("MCG2","MakeSure"));
	SetDlgItemText(IDC_BTRESET,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_BTADDSKILL,theApp.operCG2.ReadValue("MCG2","MakeSure"));
	SetDlgItemText(IDC_BTRESETSKILL,theApp.operCG2.ReadValue("MCG2","Reset"));



	tbcResult.InsertItem(0,theApp.operCG2.ReadValue("MCG2","UIC_UI_tpgUserInfo"));//玩家基本信息
	tbcResult.InsertItem(1,theApp.operCG2.ReadValue("MCG2","CG2_UI_tpgSkillInfo"));//技能信息
	tbcResult.InsertItem(2,theApp.operCG2.ReadValue("MCG2","CG2_UI_tpgSkillLevel"));//修改角色技能等级
	tbcResult.InsertItem(3,theApp.operCG2.ReadValue("MCG2","CG2_UI_tpgAddSkill"));//添加角色技能


	GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

}



BOOL CCG2UpdateSkill::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: 在此处添加消息处理程序代码
	InitUI();

	nItem = -1;
	pageInfo = false;
	pageUInfo = false;
	ServerIP = "";
	UserID = "";
	UserName = "";
	UserNick = "";//初始化一些私有变量
	iCharNo=0;

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

		if(listSkill.m_hWnd != NULL)
		{
			listSkill.MoveWindow(newRect);//设置好listResult的位置
		}
		
	}

	//OperationCG2 theApp.operCG2;
	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//当前的状态为初始建立对话框

	theApp.operCG2.GetServerList();//请求所有的游戏服务器列表
	::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

	return TRUE;
}

void CCG2UpdateSkill::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CCG2UpdateSkill::OnBnClickedUicancel()
{
	// TODO: 在此添加控件通知处理程序代码
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");

}

void CCG2UpdateSkill::OnSize(UINT nType, int cx, int cy)
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

		if(listSkill.m_hWnd != NULL)
		{
			listSkill.MoveWindow(newRect);//设置好listResult的位置
		}

		
	}
}

HBRUSH CCG2UpdateSkill::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

void CCG2UpdateSkill::OnBnClickedUisearch()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;
		//OperationCG2 theApp.operCG2;

		tbcResult.SetCurSel(0);//玩家信息

		nItem = -1;//玩家资料列表没有选定项
		pageUInfo = false;//玩家资料列表不能翻页	
		cmbPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容


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

void CCG2UpdateSkill::UserInfo()
{
	//OperationCG2 theApp.operCG2;
	try
	{		
		CIni mIni;		
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");//查询第一页的信息
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//每页显示50条记录

		nItem = -1;//玩家资料列表没有选定项
		pageUInfo = false;//玩家资料列表不能翻页	
		cmbPage.ResetContent();//清除玩家资料列表翻页的复选框
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

//技能信息查询
void CCG2UpdateSkill::SkillInfo()
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
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//玩家IDKEY

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Skill_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
	    }
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Skill"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
}

//切换tabCtrl
void CCG2UpdateSkill::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//OperationCG2 theApp.operCG2;
	if(tbcResult.GetCurSel()==0)//选中的是玩家资料信息选项卡
	{
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

		UpdateData(true);
	}
	else if(tbcResult.GetCurSel()==1)
	{
		GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

		//GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);
		UpdateData(true);

		SkillInfo();
	}
	else if(tbcResult.GetCurSel()==2)//选中的是修改角色技能等级
	{
		CIni mIni;
		pageInfo = false;
		cmbPage.ResetContent();

		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTRESET)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

		UpdateData(true);
		//OperationCG2 theApp.operCG2;

		UserSkill = theApp.operCG2.GetValueByColName(&listSkill,nItem,theApp.operCG2.ReadValue("MCG2","CG2_SkillName"));//保存选中的技能名称
		UserSkillLevel = atoi(theApp.operCG2.GetValueByColName(&listSkill,nItem,theApp.operCG2.ReadValue("MCG2","CG2_SkillLevel")));//保存选中的技能等级

		char strInt[10];
		_itoa(UserSkillLevel,strInt,10);
		SetDlgItemText(IDC_ETSKILL,UserSkill);
		SetDlgItemText(IDC_ETCURLEVEL,strInt);
	}
	else if(tbcResult.GetCurSel()==3)//选中的是添加技能信息
	{
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_SHOW);

		SetDlgItemText(IDC_ETSKILLLEVEL,"1");

		GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_SHOW);

		UpdateData(true);

		SkillType();
	}
	*pResult = 0;
}

//查询技能类别
void CCG2UpdateSkill::SkillType()
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
			socketdata.InitCreate(1,2);//共有五个参数，服务器IP、玩家帐号、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			//socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

			//socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY

			//_itoa(index,strInt,10);
			//socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			//_itoa(iPageSize,strInt,10);
			//socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_GetSkill_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_AddSkill"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
}
// 单击用户列表保存当前行号
void CCG2UpdateSkill::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
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
void CCG2UpdateSkill::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//OperationCG2 theApp.operCG2;

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
				//while(listUser.DeleteColumn(0)){}// 清除结果列表中的所有内容

				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

				UpdateData(true);

				//OperationCG2 theApp.operCG2;
				UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
				UserID = theApp.operCG2.GetValueByColName(&listUser, nItem,theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
				UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称
				iCharNo =atoi(theApp.operCG2.GetValueByColName(&listUser,nItem,theApp.operCG2.ReadValue("MCG2","CG2_CharacterNum")));//保存选中的玩家角色号

				SkillInfo();

			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

//单击技能信息列表框
void CCG2UpdateSkill::OnNMClickListskillinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(tbcResult.GetCurSel() == 1)
	{
		if(listSkill.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listSkill.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listSkill.SubItemHitTest(&lvinfo);//保存在技能信息列表中选中的行号
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}
//双击技能信息列表框
void CCG2UpdateSkill::OnNMDblclkListskillinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//OperationCG2 theApp.operCG2;

	if(tbcResult.GetCurSel() == 1)
	{
		if(listSkill.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listSkill.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listSkill.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

			if(nItem >= 0)
			{
				tbcResult.SetCurSel(2);

				CIni mIni;
				pageInfo = false;
				cmbPage.ResetContent();
				//while(listUser.DeleteColumn(0)){}// 清除结果列表中的所有内容

				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTRESET)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

				UpdateData(true);

				//OperationCG2 theApp.operCG2;


				UserSkill = theApp.operCG2.GetValueByColName(&listSkill,nItem,theApp.operCG2.ReadValue("MCG2","CG2_SkillName"));//保存选中的技能名称
				SkillID =theApp.operCG2.GetValueByColName(&listSkill,nItem,theApp.operCG2.ReadValue("MCG2","CG2_SkillID"));//保存选中的技能id
				UserSkillLevel = atoi(theApp.operCG2.GetValueByColName(&listSkill,nItem,theApp.operCG2.ReadValue("MCG2","CG2_SkillLevel")));//保存选中的技能等级

				char strInt[10];
				_itoa(UserSkillLevel,strInt,10);
				SetDlgItemText(IDC_ETSKILL,UserSkill);
				SetDlgItemText(IDC_ETCURLEVEL,strInt);
				cmbNewLevel.ResetContent();
				SetLevel();

			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}
///修改玩家角色技能等级
void CCG2UpdateSkill::OnBnClickedBtupdate()
{
	// TODO: 在此添加控件通知处理程序代码
	//OperationCG2 theApp.operCG2;
	try
	{
		CIni mIni;
		CSocketData socketdata;
		socketdata.InitCreate(1,7);//共有五个参数，服务器IP、玩家帐号、角色IDKEY、角色号、备注、技能等级、技能ID

		char strInt[10];
		_itoa(iCharNo,strInt,10);
		CString remark="Update Skill Level";
		CString SkillLevel="";

		cmbNewLevel.GetWindowText(SkillLevel);

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//角色号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Remark,CEnumCore::TagFormat::TLV_STRING,strlen(remark),(unsigned char *)mIni.wcharToChar(remark));//备注
		socketdata.AddTFLV(CEnumCore::TagName::CG2_SkillLevel,CEnumCore::TagFormat::TLV_STRING,strlen(SkillLevel),(unsigned char *)mIni.wcharToChar(SkillLevel));//技能等级

		socketdata.AddTFLV(CEnumCore::TagName::CG2_SkillID,CEnumCore::TagFormat::TLV_STRING,strlen(SkillID),(unsigned char *)mIni.wcharToChar(SkillID));//技能id
		//_itoa(index,strInt,10);
		//socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		//_itoa(iPageSize,strInt,10);
		//socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Update_Account_Skill_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UpdateSkillLevel"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
}
//重置修改角色技能等级
void CCG2UpdateSkill::OnBnClickedBtreset()
{
	// TODO: 在此添加控件通知处理程序代码
	tbcResult.SetCurSel(1);



	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

	cmbNewLevel.ResetContent();
	SetLevel();

	UpdateData(true);

	SkillInfo();
}

//切换职业类别组合框,技能名称查询
void CCG2UpdateSkill::OnCbnSelchangeCmbskilltype()
{
	// TODO: 在此添加控件通知处理程序代码

	int iPos=((CComboBox*)GetDlgItem(IDC_CMBSKILLTYPE))->GetCurSel();//当前选中的行
	CString SkillType="";
	//cmbSkillType.GetWindowText(SkillType);
	//GetDlgItemText(IDC_CMBSKILLTYPE,SkillType);
	((CComboBox*)GetDlgItem(IDC_CMBSKILLTYPE))->GetLBText(iPos,SkillType); //其中n为从0开始的索引值
	CString m_ServerName="";
	GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//获取游戏服务器的名称

	ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

	//OperationCG2 theApp.operCG2;	
	try
	{		
		CIni mIni;
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		//if((listUser.GetItemCount() > 0) && (nItem>=0))
		//{
			CSocketData socketdata;
			socketdata.InitCreate(1,5);//共有五个参数，服务器IP、玩家帐号、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_SkillType,CEnumCore::TagFormat::TLV_STRING,strlen(SkillType),(unsigned char *)mIni.wcharToChar(SkillType));//技能类别

			//socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SkillList_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
	//	}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_AddSkill"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}

}




//添加技能信息
void CCG2UpdateSkill::OnBnClickedBtaddskill()
{
	// TODO: 在此添加控件通知处理程序代码
	//OperationCG2 theApp.operCG2;
	try
	{
		CIni mIni;
		CSocketData socketdata;
		socketdata.InitCreate(1,6);//共有五个参数，服务器IP、玩家帐号、角色IDKEY、角色号、新职业、备注

		char strInt[10];
		_itoa(iCharNo,strInt,10);
		CString remark="Add Skill";
		CString SkillName="";

		//cmbNewLevel.GetWindowText(SkillLevel);
		GetDlgItemText(IDC_CMBSKILLNAME,SkillName);

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//角色号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色唯一IDKEY
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Remark,CEnumCore::TagFormat::TLV_STRING,strlen(remark),(unsigned char *)mIni.wcharToChar(remark));//角色唯一IDKEY
		socketdata.AddTFLV(CEnumCore::TagName::CG2_SkillName,CEnumCore::TagFormat::TLV_STRING,strlen(SkillName),(unsigned char *)mIni.wcharToChar(SkillName));//技能名称

		//_itoa(index,strInt,10);
		//socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		//_itoa(iPageSize,strInt,10);
		//socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Insert_Account_Skill_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_AddSkill"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
}
//重置添加技能信息
void CCG2UpdateSkill::OnBnClickedBtresetskill()
{
	// TODO: 在此添加控件通知处理程序代码
	tbcResult.SetCurSel(1);



	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

	cmbNewLevel.ResetContent();
	SetLevel();

	UpdateData(true);

	SkillInfo();
}

void CCG2UpdateSkill::SetLevel()
{
	cmbNewLevel.ResetContent();
	cmbNewLevel.AddString("0");
	cmbNewLevel.AddString("1");
	cmbNewLevel.AddString("2");
	cmbNewLevel.AddString("3");
	cmbNewLevel.AddString("4");
	cmbNewLevel.AddString("5");
	cmbNewLevel.AddString("6");
	cmbNewLevel.AddString("7");
	cmbNewLevel.AddString("8");
	cmbNewLevel.AddString("9");
	cmbNewLevel.SetCurSel(0);
	
}

LRESULT CCG2UpdateSkill::OnMessageReceive(WPARAM wParam,LPARAM lParam)
{
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
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
					cmbPage.ResetContent();//清空页数复选框
					while(listUser.DeleteColumn(0)){}//清空CListCtrl内容
				}
				else
				{
					nItem = 0;
					cmbPage.ResetContent();//清空页数复选框，以便重新构造
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbPage.AddString(str);//在复选框中构造页数信息
					}
					cmbPage.SetCurSel(0);//在复选框中选中第一页
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
	case CEnumCore::Message_Tag_ID::CG2_Account_Skill_Query_Resp://查询玩家技能信息
		{
			if(pageUInfo)//如果已经能够翻页
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listSkill,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listSkill,&pageCount);//构造CListCtrl对象

				if(pageCount<0)//页数<=0，说明没有数据返回
				{
					nItem = -1;//不能选中某一行
					pageUInfo = false;//不能翻页					
					cmbSkillPage.ResetContent();//清空页数复选框
					while(listSkill.DeleteColumn(0)){}//清空CListCtrl内容
				}
				else
				{
					nItem = 0;
					cmbSkillPage.ResetContent();//清空页数复选框，以便重新构造
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbSkillPage.AddString(str);//在复选框中构造页数信息
					}
					cmbSkillPage.SetCurSel(0);//在复选框中选中第一页
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
		//修改玩家角色技能等级
	case CEnumCore::Message_Tag_ID::CG2_Update_Account_Skill_Query_Resp:
		//添加技能信息
	case CEnumCore::Message_Tag_ID::CG2_Insert_Account_Skill_Query_Resp:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//显示操作结果
			tbcResult.SetCurSel(1);

			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

			cmbNewLevel.ResetContent();
			SetLevel();

			UpdateData(true);

			SkillInfo();
		}
		break;

		
		//查询技能类别
	case CEnumCore::Message_Tag_ID::CG2_GerSkill_Query_Resp:
		{
			theApp.operCG2.BuildJobCombox(&socketdata,&cmbSkillType);//构造技能类别组合框
		}
		break;
		//技能名称查询
	case CEnumCore::Message_Tag_ID::CG2_SkillList_Query_Resp:
		{
			theApp.operCG2.BuildJobCombox(&socketdata,&cmbSkillName);//构造技能名称组合框
		}
		break;
	}


	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}


















