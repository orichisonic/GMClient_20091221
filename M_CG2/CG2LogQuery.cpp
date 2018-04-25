// CG2LogQuery.cpp : 实现文件
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2LogQuery.h"
#include ".\cg2logquery.h"


// CCG2LogQuery 对话框

IMPLEMENT_DYNAMIC(CCG2LogQuery, CDialog)
CCG2LogQuery::CCG2LogQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2LogQuery::IDD, pParent)
	, ServerIP(_T(""))
{
}

CCG2LogQuery::~CCG2LogQuery()
{
}

void CCG2LogQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBKPPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTCHARACTER, listResult);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_CBString(pDX, IDC_CMBUISERVER, ServerIP);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBCATEGORY, cmbCategory);
	DDX_Control(pDX, IDC_CMBACTION, cmbAction);
	DDX_Control(pDX, IDC_DATESTART, dtcStartDate);
	DDX_Control(pDX, IDC_TIMESTART, dtcStartTime);
	DDX_Control(pDX, IDC_DATEEND, dtcEndDate);
	DDX_Control(pDX, IDC_TIMEEND, dtcEndTime);
}


BEGIN_MESSAGE_MAP(CCG2LogQuery, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_CBN_SELCHANGE(IDC_CMBCATEGORY, OnCbnSelchangeCmbcategory)
	ON_BN_CLICKED(IDC_BTSEARCH, OnBnClickedBtsearch)
END_MESSAGE_MAP()


// CCG2LogQuery 消息处理程序

BOOL CCG2LogQuery::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUI();

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
			listResult.MoveWindow(newRect);//设置好listResult的位置
		}

	}

	GetDlgItem(IDC_STATICCATEGORY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBCATEGORY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICACTION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBACTION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICSTARTTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATESTART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TIMESTART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICENDTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATEEND)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TIMEEND)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTSEARCH)->ShowWindow(SW_HIDE);



	//OperationCG2 theApp.operCG2;
	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//当前的状态为初始建立对话框

	theApp.operCG2.GetServerList();//请求所有的游戏服务器列表
	::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 初始化显示字符
void CCG2LogQuery::InitUI()//
{
	//OperationCG2 theApp.operCG2;

	SetWindowText(theApp.operCG2.ReadValue("MCG2","CG2_UI_LogQuery"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operCG2.ReadValue("MCG2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));

	SetDlgItemText(IDC_STATICCATEGORY,theApp.operCG2.ReadValue("MCG2","UIC_UI_CATEGORY"));
	SetDlgItemText(IDC_STATICACTION,theApp.operCG2.ReadValue("MCG2","UIC_UI_ACTION"));
	SetDlgItemText(IDC_STATICSTARTTIME,theApp.operCG2.ReadValue("MCG2","UIC_UI_STARTTIME"));
	SetDlgItemText(IDC_STATICENDTIME,theApp.operCG2.ReadValue("MCG2","UIC_UI_ENDTIME"));

	SetDlgItemText(IDC_BTSEARCH,theApp.operCG2.ReadValue("MCG2","Search"));

	tbcResult.InsertItem(0,theApp.operCG2.ReadValue("MCG2","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operCG2.ReadValue("MCG2","CG2_UI_tpgLogInfo"));

}

//自动改变大小
void CCG2LogQuery::OnSize(UINT nType, int cx, int cy)
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

		if(listResult.m_hWnd != NULL)
		{
			listResult.MoveWindow(newRect);//设置好listResult的位置
		}

	}
}

//设置背景颜色
HBRUSH CCG2LogQuery::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//查询玩家信息
void CCG2LogQuery::OnBnClickedUisearch()
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

		//GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);

		//GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
		//GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
		//UpdateData(true);
		

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


void CCG2LogQuery::UserInfo()
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

//切换选项卡
void CCG2LogQuery::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//OperationCG2 theApp.operCG2;
	if(tbcResult.GetCurSel() == 0)//选中的是玩家资料信息选项卡
	{
		GetDlgItem(IDC_STATICCATEGORY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBCATEGORY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICACTION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBACTION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICSTARTTIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DATESTART)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TIMESTART)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICENDTIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DATEEND)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TIMEEND)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTSEARCH)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);

		UpdateData(true);
		cmbCategory.ResetContent();
	}
	else if(tbcResult.GetCurSel() == 1)//选中的是日志查询
	{
		CIni mIni;
		pageInfo = false;
		cmbPage.ResetContent();
		//cmbCategory.ResetContent();
		//cmbAction.ResetContent();
		while(listUser.DeleteColumn(0)){}// 清除结果列表中的所有内容

		GetDlgItem(IDC_STATICCATEGORY)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBCATEGORY)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICACTION)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBACTION)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICSTARTTIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DATESTART)->ShowWindow(SW_SHOW);
////		GetDlgItem(IDC_TIMESTART)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICENDTIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DATEEND)->ShowWindow(SW_SHOW);
////		GetDlgItem(IDC_TIMEEND)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTSEARCH)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

		//日志大类显示
		cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR"));//人物
		cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM"));//道具
		cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_MAIL"));//邮件
		cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET"));//宠物
		cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_SKILL"));//技能
		cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD"));//金钱

//		cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ACCOUNT"));//帐号

		UpdateData(true);
	}
	*pResult = 0;
}

//日志大类组合框改变
void CCG2LogQuery::OnCbnSelchangeCmbcategory()
{
	// TODO: 在此添加控件通知处理程序代码
	//OperationCG2 theApp.operCG2;
	CString strCategory="";
	GetDlgItemText(IDC_CMBCATEGORY,strCategory);//获得大类信息
	int index=cmbCategory.GetCurSel();

	if(index==4)//strCategory==theApp.operCG2.ReadValue("MCG2","UIC_CHAR"))//人物
	{
		cmbAction.ResetContent();
		//UpdateData(true);
		cmbAction.SetCurSel(0);

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_LOGIN"));//人物登陆
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_LOGOUT"));//人物登出
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_LEVELUP"));//人物升级

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_QUESTERROR"));//回答问题出错被踢下线
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_CREATE"));//人物创建
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_DELETE"));//人物删除
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_QUESTCLEAR"));//完成任务
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GHONORUP"));//工会荣誉增加
		
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GRANKUP"));//工会等级增加
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GCREATE"));//创建公会
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GCLOSE"));//解散工会
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GJOIN"));//加入工会
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GLEFT"));//离开工会

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GKICK"));//将别人踢出工会
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GCHANGEM"));//更换工会会长
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GEXTEND"));//工会延期
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_MARRY"));//结婚
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_DIVORCE"));//离婚
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GETGD"));//工会战
		
	}
	else if(index==5)//strCategory==theApp.operCG2.ReadValue("MCG2","UIC_MAIL"))//邮件
	{
		cmbAction.ResetContent();
		//UpdateData(true);
		cmbAction.SetCurSel(0);

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_MAIL_NORMAL"));

	}
/*	else if(index==6)//strCategory==theApp.operCG2.ReadVlaue("MCG2","UIC_ACCOUNT")
	{
		cmbAction.ResetContent();
		cmbAction.SetCurSel(0);

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ACCOUNT_LOGIN"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ACCOUNT_XTRAPERROR"));
	}*/
	else if(index==0)//strCategory==theApp.operCG2.ReadValue("MCG2","UIC_PET"))//宠物
	{
		cmbAction.ResetContent();
		//UpdateData(true);
		cmbAction.SetCurSel(0);

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_LEVELUP"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_GAIN"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_DELETESKILL"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_RELEASE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_TRADE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_SELL"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_GRADEUPSKILL"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_PUTBANK"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_GETBANK"));
		
	}
	else if(index==2)//strCategory==theApp.operCG2.ReadValue("MCG2","UIC_SKILL"))//技能
	{
		cmbAction.ResetContent();
		//UpdateData(true);
		cmbAction.SetCurSel(0);

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_SKILL_DELETE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_SKILL_GAIN"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_SKILL_GRADEUP"));

		
	}
	else if(index==1)////strCategory==theApp.operCG2.ReadValue("MCG2","UIC_ITEM"))///道具
	{
		cmbAction.ResetContent();
		cmbAction.SetCurSel(0);

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BUY"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_USE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GAIN_BATTLE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_DROP"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_DROPCHARGEITEM"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_DROP_DELETE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_SELL"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_USECHARGEITEM"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_TRADE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GETCHARGEITEM"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GAIN"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BREAK"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_PUTBANK"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GETBANK"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_MERGE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_ITEMCOLOR"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BREAKCHARGEITEM"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BUYCHARGEITEM"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GAINSKILLITEM"));//UIC_ITEM_GAINSKILLITEM
	}
	else if(index=3)//strCategory==theApp.operCG2.ReadValue("MCG2","UIC_GOLD"))
	{
		cmbAction.ResetContent();
		cmbAction.SetCurSel(0);
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD_TRADELOST"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD_PUTBANK"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD_GETBANK"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD_GAIN"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD_DROP"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD_SPENDMONEY"));
	}
}

// 单击用户列表保存当前行号
void CCG2LogQuery::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
void CCG2LogQuery::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
				while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容
				

				GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
				///GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				///GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);

				UpdateData(true);

				//OperationCG2 theApp.operCG2;
				UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
				UserID = theApp.operCG2.GetValueByColName(&listUser, nItem,theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
				UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称



				GetDlgItem(IDC_STATICCATEGORY)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBCATEGORY)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICACTION)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBACTION)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICSTARTTIME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_DATESTART)->ShowWindow(SW_SHOW);
///				GetDlgItem(IDC_TIMESTART)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICENDTIME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_DATEEND)->ShowWindow(SW_SHOW);
///				GetDlgItem(IDC_TIMEEND)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTSEARCH)->ShowWindow(SW_SHOW);


				//日志大类显示
				cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR"));//人物
				cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM"));//道具
				cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_MAIL"));//邮件
				cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET"));//宠物
				cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_SKILL"));//技能
				cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD"));//金钱

//				cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ACCOUNT"));//帐号

				UpdateData(true);



				//DetailInfo();// 查询角色详细资料
				tbcResult.SetCurSel(1);
			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}


///点击玩家日志查询button
void CCG2LogQuery::OnBnClickedBtsearch()
{
	// TODO: 在此添加控件通知处理程序代码
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
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、角色IDKey、日志大类、日志小类、开始时间、结束时间、页数、每页的记录条数
		char strInt[10];

		//获取开始时间和结束时间
		CTime startDate,endDate;
		dtcStartDate.GetTime(startDate);
		dtcEndDate.GetTime(endDate);

		CTime startTime,endTime;
		dtcStartTime.GetTime(startTime);
		dtcEndTime.GetTime(endTime);

		CTime startDT=CTime::CTime(startDate.GetYear(),startDate.GetMonth(),startDate.GetDay(),startTime.GetHour(),startTime.GetMinute(),startTime.GetSecond());
		CTime endDT=CTime::CTime(endDate.GetYear(),endDate.GetMonth(),endDate.GetDay(),endTime.GetHour(),endTime.GetMinute(),endTime.GetSecond());

		CString strStartTime,strEndTime;
		strStartTime=startDT.Format("%Y-%m-%d %H:%M:%S");//设置开始时间
		strEndTime=endDT.Format("%Y-%m-%d %H:%M:%S");//设置结束时间

		//获得日志大类，日志小类
		CString strCategory="";
		CString strAction="";
		CString str="";

		GetDlgItemText(IDC_CMBCATEGORY,str);//获得大类信息
		if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR"))//人物
		{
			strCategory="char";
			GetDlgItemText(IDC_CMBACTION,str);//获得小类信息
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_LEVELUP"))//人物升级
				strAction="levelup";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_LOGIN"))//人物登陆
				strAction="login";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_LOGOUT"))//人物登出
				strAction="logout";



			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_QUESTERROR"))//回答问题出错被踢下线
				strAction="questerror";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_CREATE"))//人物创建
				strAction="create";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_DELETE"))//人物删除
				strAction="delete";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_QUESTCLEAR"))//完成任务
				strAction="questclear";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GHONORUP"))//工会荣誉增加
				strAction="ghonorup";
		
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GRANKUP"))//工会等级增加
				strAction="grankup";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GCREATE"))//创建公会
				strAction="gcreate";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GCLOSE"))//解散工会
				strAction="gclose";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GJOIN"))//加入工会
				strAction="gjoin";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GLEFT"))//离开工会
				strAction="gleft";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GKICK"))//将别人踢出工会
				strAction="gkick";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GCHANGEM"))//更换工会会长
				strAction="gchangem";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GEXTEND"))//工会延期
				strAction="gextend";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_MARRY"))//结婚
				strAction="marry";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_DIVORCE"))//离婚
				strAction="divorce";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GETGD"))//工会战
				strAction="getgd";
		}
		if(str==theApp.operCG2.ReadValue("MCG2","UIC_SKILL"))//技能
		{
			strCategory="skill";
			GetDlgItemText(IDC_CMBACTION,str);//获得小类信息
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_SKILL_GRADEUP"))//技能升级
				strAction="gradeup";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_SKILL_DELETE"))//删除技能
				strAction="delete";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_SKILL_GAIN"))//获得技能
				strAction="gain";
		}
		if(str==theApp.operCG2.ReadValue("MCG2","UIC_MAIL"))//邮件
		{
			strCategory="mail";
			GetDlgItemText(IDC_CMBACTION,str);//获得小类信息
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_MAIL_NORMAL"))//正常
				strAction="normal";
		}
		if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM"))//道具
		{
			strCategory="item";
			GetDlgItemText(IDC_CMBACTION,str);//获得小类信息
			

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GAIN_BATTLE"))//战斗获得
				strAction="gain_battle";
				
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BUY"))//购买
				strAction="buy";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_USE"))//使用
				strAction="use";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_DROP"))//丢弃
				strAction="drop";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_DROPCHARGEITEM"))//丢弃合成道具
				strAction="dropchargeitem";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_DROP_DELETE"))//丢弃删除
				strAction="drop_delete";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_SELL"))//出售
				strAction="sell";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_USECHARGEITEM"))//使用合成道具
				strAction="usechargeitem";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_TRADE"))//交易
				strAction="trade";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GETCHARGEITEM"))//获得合成道具
				strAction="getchargeitem";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GAIN"))//获得
				strAction="gain";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BREAK"))//损坏
				strAction="break";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_PUTBANK"))//道具放到银行
				strAction="putbank";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GETBANK"))//从银行取出道具
				strAction="getbank";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_MERGE"))//合成道具
				strAction="merge";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_ITEMCOLOR"))//装备染色
				strAction="itemcolor";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BREAKCHARGEITEM"))//收费道具损坏
				strAction="breakchargeitem";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BUYCHARGEITEM"))//用M币购买道具
				strAction="buychargeitem";//UIC_ITEM_GAINSKILLITEM

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GAINSKILLITEM"))//获得技能道具
				strAction="gainskillitem";

		}
		if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET"))//宠物
		{
			strCategory="pet";
			GetDlgItemText(IDC_CMBACTION,str);//获得小类信息
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_LEVELUP"))//宠物升级
				strAction="levelup";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_GAIN"))//获得宠物
				strAction="gain";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_DELETESKILL"))//删除技能
				strAction="deleteskill";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_RELEASE"))//释放
				strAction="release";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_TRADE"))//交易宠物
				strAction="trade";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_SELL"))//出售宠物
				strAction="sell";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_GRADEUPSKILL"))//宠物技能升级
				strAction="gradeupskill";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_PUTBANK"))//把宠物放到银行
				strAction="putbank";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_GETBANK"))//从银行取出宠物
				strAction="getbank";
		}
		if(str==theApp.operCG2.ReadValue("MCG2","UIC_GOLD"))//金钱
		{
			strCategory="gold";
			GetDlgItemText(IDC_CMBACTION,str);//获得小类信息
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_GOLD_TRADELOST"))//交易金钱
				strAction="tradeLost";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_GOLD_PUTBANK"))//把金钱放到银行
				strAction="putbank";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_GOLD_GETBANK"))//从银行取出金钱
				strAction="getbank";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_GOLD_GAIN"))//获得金钱
				strAction="gain";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_GOLD_DROP"))//丢弃金钱
				strAction="drop";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_GOLD_SPENDMONEY"))//其他消耗M币
				strAction="spendmoney";
		}
/*		if(str==theApp.operCG2.ReadValue("MCG2","UIC_ACCOUNT"))//帐号
		{
			strCategory="account";
			GetDlgItemText(IDC_CMBACTION,str);//获得小类信息
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ACCOUNT_LOGIN"))//帐号登陆
				strAction="accountlogin";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ACCOUNT_XTRAPERROR"))//xtrap服务器端发现外挂断开连接
				strAction="xtraperror";
		}
*/
		

		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP


		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//角色IDKey
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Log_StartTime,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//日志开始时间
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Log_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//日志结束时间
		socketdata.AddTFLV(CEnumCore::TagName::CG2_category,CEnumCore::TagFormat::TLV_STRING,strlen(strCategory),(unsigned char *)mIni.wcharToChar(strCategory));//日志大类
		socketdata.AddTFLV(CEnumCore::TagName::CG2_action,CEnumCore::TagFormat::TLV_STRING,strlen(strAction),(unsigned char *)mIni.wcharToChar(strAction));//日志小类


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Log_Query);//发送查询玩家资料信息的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_LogQuery"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

//接受返回信息
LRESULT CCG2LogQuery::OnMessageReceive(WPARAM wParam,LPARAM lParam)
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
///	case CEnumCore::Message_Tag_ID::CG2_Log_Query_Resp://玩家日志查询
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

	default:
		{
			if(pageUInfo)//如果已经能够翻页
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

				if(pageCount<0)//页数<=0，说明没有数据返回
				{
					nItem = -1;//不能选中某一行
					pageUInfo = false;//不能翻页					
					cmbPage.ResetContent();//清空页数复选框
					//cmbCategory.ResetContent();
					while(listResult.DeleteColumn(0)){}//清空CListCtrl内容
				}
				else
				{
					nItem = 0;
					cmbPage.ResetContent();//清空页数复选框，以便重新构造
					//cmbCategory.ResetContent();
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
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}


//关闭对话框
void CCG2LogQuery::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CCG2LogQuery::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");

}




