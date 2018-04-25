// UserManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_GM.h"
#include "UserManage.h"
#include ".\usermanage.h"


// CUserManage 对话框

IMPLEMENT_DYNAMIC(CUserManage, CDialog)
CUserManage::CUserManage(CWnd* pParent /*=NULL*/)
	: CDialog(CUserManage::IDD, pParent)
{
}

CUserManage::~CUserManage()
{
}

void CUserManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABUSERMANAGE, tbcResult);
	DDX_Control(pDX, IDC_LISTUSER, listUser);
	DDX_Control(pDX, IDC_CHECKEXIT, cBtnExit);
	DDX_Control(pDX, IDC_CHECKUSERONLINE, cBtnOnline);
	DDX_Control(pDX, IDC_CHECKSYSMANAGE, cBtnSysAdmin);
	DDX_Control(pDX, IDC_CHECKDEPART, cBtnDepartAdmin);
	DDX_Control(pDX, IDC_DTPENDTIME, dtpEndTime);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_STATPAGE, GrpSearch);
	DDX_Control(pDX, IDC_CMBDEPART, cmbDepart);
}


BEGIN_MESSAGE_MAP(CUserManage, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUSERMANAGE, OnTcnSelchangeTabusermanage)
	ON_BN_CLICKED(IDADDUSER, OnBnClickedAdduser)
	ON_BN_CLICKED(IDRESET, OnBnClickedReset)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSER, OnNMDblclkListuser)
	ON_BN_CLICKED(IDC_CHECKSYSMANAGE, OnBnClickedChecksysmanage)
	ON_BN_CLICKED(IDC_CHECKDEPART, OnBnClickedCheckdepart)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSER, OnNMClickListuser)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID__PPPEDOMMANAGE, OnPopedomManage)
	ON_NOTIFY(NM_RCLICK, IDC_LISTUSER, OnNMRclickListuser)
	ON_COMMAND(ID__MODIUSERPWD, OnModiUserPwd)
	ON_COMMAND(ID__UPDATEUSERMAC, OnUpdateUserMAC)
END_MESSAGE_MAP()

// 初始化对话框
BOOL CUserManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	nItem = -1;
	pageInfo = false;//初始化一些私有变量

	InitUI();// 初始化显示字符

	CRect rs;
	GetClientRect(rs); //获取对话框的大小信息

	CRect srcRect;
	CRect newRect;

	if(tbcResult.m_hWnd != NULL)
	{
		tbcResult.GetWindowRect(srcRect);//获取tbcResult的大小信息
		tbcHeight = srcRect.bottom - srcRect.top;//得到tbcResult的高度信息

		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + tbcHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		tbcResult.MoveWindow(newRect);//设置tbcResult的位置
	}
	
	if(GrpSearch.m_hWnd != NULL)
	{
		GrpSearch.GetWindowRect(srcRect);//获取GrpSearch的大小信息
		grpHeight = srcRect.bottom - srcRect.top;//得到GrpSearch的高度信息

		newRect.top = rs.top + 4 + tbcHeight;
		newRect.bottom = newRect.top + grpHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpSearch.MoveWindow(newRect);//设置好GrpSearch的位置
	}	

	if(listUser.m_hWnd != NULL)
	{
		listUser.GetWindowRect(srcRect);//获取listUser的大小信息

		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置
	}

	GetDlgItem(IDC_LISTUSER)->ShowWindow(SW_SHOW);//刚开始需要显示用户列表信息
	GetDlgItem(IDC_STATPAGE)->ShowWindow(SW_SHOW);//显示翻页信息
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATNAME)->ShowWindow(SW_HIDE);//操作的内容都被隐藏了
	GetDlgItem(IDC_TXTUSER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATUPWD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TXTPWD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATPWDAG)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TXTPWDAG)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATREALNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TXTREALNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATDEPART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBDEPART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATENDTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DTPENDTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKEXIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKUSERONLINE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKSYSMANAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKDEPART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDADDUSER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDRESET)->ShowWindow(SW_HIDE);

	InitUserList();//初始化用户列表
	::EnableWindow(this->GetParent()->m_hWnd,false);

	return TRUE;
}

// 初始化显示字符
void CUserManage::InitUI()
{
	//OperationGM operGM;

	SetWindowText(theApp.operGM.ReadValue("MGM","UM_UI_UserManage"));
	tbcResult.InsertItem(0,theApp.operGM.ReadValue("MGM","UM_UI_UserList"));
	tbcResult.InsertItem(1,theApp.operGM.ReadValue("MGM","UM_UI_AddUser"));
	tbcResult.InsertItem(2,theApp.operGM.ReadValue("MGM","UM_UI_EditUser"));

	SetDlgItemText(IDC_LBLPAGE,theApp.operGM.ReadValue("MGM","UM_UI_Page"));
	SetDlgItemText(IDC_STATNAME,theApp.operGM.ReadValue("MGM","UM_UI_UserName"));
	SetDlgItemText(IDC_STATUPWD,theApp.operGM.ReadValue("MGM","UM_UI_UserPwd"));
	SetDlgItemText(IDC_STATPWDAG,theApp.operGM.ReadValue("MGM","UM_UI_UserPwdAG"));
	SetDlgItemText(IDC_STATREALNAME,theApp.operGM.ReadValue("MGM","UM_UI_RealName"));
	SetDlgItemText(IDC_STATDEPART,theApp.operGM.ReadValue("MGM","UM_UI_UserDepart"));
	SetDlgItemText(IDC_STATENDTIME,theApp.operGM.ReadValue("MGM","UM_UI_EndTime"));
	SetDlgItemText(IDC_CHECKEXIT,theApp.operGM.ReadValue("MGM","UM_UI_CheckExit"));
	SetDlgItemText(IDC_CHECKUSERONLINE,theApp.operGM.ReadValue("MGM","UM_UI_CheckOnline"));
	SetDlgItemText(IDC_CHECKSYSMANAGE,theApp.operGM.ReadValue("MGM","UM_UI_CheckSys"));
	SetDlgItemText(IDC_CHECKDEPART,theApp.operGM.ReadValue("MGM","UM_UI_CheckDepart"));
	SetDlgItemText(IDADDUSER,theApp.operGM.ReadValue("MGM","UM_UI_AddUser"));
	SetDlgItemText(IDRESET,theApp.operGM.ReadValue("MGM","Reset"));

	SetDlgItemText(ID__PPPEDOMMANAGE,theApp.operGM.ReadValue("MGM","PM_UI_PopedomManage"));
}

//处理快捷键响应函数
BOOL CUserManage::PreTranslateMessage(MSG* pMsg)
{
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operGM.CopyListInfo(&listUser);
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
			}
		}		
	}
	return FALSE;
}

/// <summary>
/// 自动改变大小
/// </summary>
void CUserManage::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rs;
	GetClientRect(rs);

	CRect srcRect;
	CRect newRect;
	
	if(tbcResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + tbcHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		tbcResult.MoveWindow(newRect);//设置好tbcResult的位置
	}
	
	if(GrpSearch.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + tbcHeight;
		newRect.bottom = newRect.top + grpHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpSearch.MoveWindow(newRect);//设置好GrpSearch的位置
	}	

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置
	}
}

//设置背景颜色
HBRUSH CUserManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

/// <summary>
/// 请求所有用户信息列表
/// </summary>
void CUserManage::InitUserList()
{
	try
	{
		//OperationGM operGM;

		nItem = -1;//用户列表没有选定项
		pageInfo = false;//用户列表不能翻页	
		cmbPage.ResetContent();//清除翻页的复选框
		while(listUser.DeleteColumn(0)){}//清除用户列表中的所有内容

		int userByID=theApp.UserByID;
		int index=1;//查询第一页的信息
		int iPageSize=50;//每页显示50条记录

		CSocketData socketdata;
		socketdata.InitCreate(1,3);//共有三个参数，操作者ID、页数、每页的记录条数
		char strInt[10];		

		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_QUERY_ALL))//发送查询用户列表的请求
		{
		    ::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}
}

/// <summary>
/// 翻页请求所有用户信息列表
/// </summary>
void CUserManage::OnCbnSelchangeCmbpage()
{
	try
	{			
		if(pageInfo)//如果可以翻页的话
		{
			//OperationGM operGM;
			nItem = -1;
			while(listUser.DeleteColumn(0)){}//清除页面内容

			CSocketData socketdata;
			socketdata.InitCreate(1,3);
			char strInt[10];

			int userByID=theApp.UserByID;
			int index = cmbPage.GetCurSel() + 1;//页数为cmbPage当前的索引值加1，也就是cmbPage中当前显示的值
			int iPageSize=50;//每页显示50条记录

			_itoa(userByID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
			if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_QUERY_ALL))//发送查询用户列表的请求
			{
			    ::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
				dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

/// <summary>
/// 单击用户列表保存当前行号
/// </summary>
void CUserManage::OnNMClickListuser(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listUser.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nItem = listUser.SubItemHitTest(&lvinfo);//保存在用户列表中选中的行号

		*pResult = 0;
	}
	catch(...)
	{
	}
}

/// <summary>
/// 双击用户列表进行删除
/// </summary>
void CUserManage::OnNMDblclkListuser(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{		
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listUser.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nItem = listUser.SubItemHitTest(&lvinfo);//保存在用户列表中选中的行号

		if(nItem >= 0)
		{
			CIni mIni;
			//OperationGM operGM;					

			UpdateData(true);

			int userID=0;
			userID = atoi(mIni.wcharToChar(theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","User_ID"))));//获取要删除的用户ID

			CString userName = theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","UserName"));//获取要删除的用户名称

			if(userID == 0)//用户ID不能为0
			{
				return;
			}

			if (AfxMessageBox(theApp.operGM.ReadValue("MGM","UM_Hint_DeleteSelectUser"), MB_YESNO) != IDYES) //是否确定要删除
			{
				return;
			} 

			CSocketData socketdata;
			socketdata.InitCreate(1,3);//共有三个参数，操作者ID、要删除的用户名称、要删除的用户ID
			char strInt[10];
			
			int userByID=theApp.UserByID;

			_itoa(userByID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作者ID

			socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(userName),(unsigned char*)mIni.wcharToChar(userName));//要删除的用户名称

			_itoa(userID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//要删除的用户ID

			int midlength = socketdata.EnBody();
			if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_DELETE))//发送删除用户的请求
			{
			    ::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
				dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();
		}
		*pResult = 0;
	}
	catch(...)
	{
	}
}

/// <summary>
/// 切换选项卡进行操作
/// </summary>
void CUserManage::OnTcnSelchangeTabusermanage(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		CIni mIni;
		//OperationGM operGM;
		if(tbcResult.GetCurSel()==0)//查看用户列表时，只要将用户列表显示出来就可以了，不需要做其它操作
		{
			GetDlgItem(IDC_LISTUSER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_STATNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTUSER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATUPWD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTPWD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATPWDAG)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTPWDAG)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATREALNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTREALNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATDEPART)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBDEPART)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATENDTIME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_DTPENDTIME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKEXIT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKUSERONLINE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKSYSMANAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKDEPART)->ShowWindow(SW_HIDE);
			GetDlgItem(IDADDUSER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDRESET)->ShowWindow(SW_HIDE);
		}
		else if(tbcResult.GetCurSel()==1)//添加新的用户信息时，除了显示相应的界面信息，还要获得所有的部门列表
		{
			GetDlgItem(IDC_LISTUSER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TXTUSER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TXTUSER)->EnableWindow(true);

			GetDlgItem(IDC_STATUPWD)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TXTPWD)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATPWDAG)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TXTPWDAG)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATREALNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TXTREALNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATDEPART)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBDEPART)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATENDTIME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_DTPENDTIME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECKEXIT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECKUSERONLINE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKSYSMANAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECKDEPART)->ShowWindow(SW_SHOW);
			GetDlgItem(IDADDUSER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDRESET)->ShowWindow(SW_SHOW);

			SetDlgItemText(IDC_TXTUSER,"");
			SetDlgItemText(IDC_TXTPWD,"");
			SetDlgItemText(IDC_TXTPWDAG,"");
			SetDlgItemText(IDC_TXTREALNAME,"");
			SetDlgItemText(IDC_TXTREALNAME,"");

			CTime curTime = CTime::GetCurrentTime();
			dtpEndTime.SetTime(&curTime);//设置要编辑的用户名使用时效

			cBtnExit.SetCheck(false);
			cBtnSysAdmin.SetCheck(false);
			cBtnDepartAdmin.SetCheck(false);

			SetDlgItemText(IDADDUSER,theApp.operGM.ReadValue("MGM","UM_UI_AddUser"));
			DepartList();//获取所有的部门信息
		}
		else if(tbcResult.GetCurSel()==2)//编辑已有的用户信息时，要将已有的信息都显示在界面中，还要获得所有的用户部门信息
		{
			if(nItem < 0)
			{
				MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_SelectModiUser"),theApp.operGM.ReadValue("MGM","Warn"),0);

				tbcResult.SetCurSel(0);
				GetDlgItem(IDC_LISTUSER)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATPAGE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_STATNAME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TXTUSER)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATUPWD)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TXTPWD)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATPWDAG)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TXTPWDAG)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATREALNAME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TXTREALNAME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATDEPART)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBDEPART)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATENDTIME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_DTPENDTIME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CHECKEXIT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CHECKUSERONLINE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CHECKSYSMANAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CHECKDEPART)->ShowWindow(SW_HIDE);
				GetDlgItem(IDADDUSER)->ShowWindow(SW_HIDE);
				GetDlgItem(IDRESET)->ShowWindow(SW_HIDE);

				return;
			}
			GetDlgItem(IDC_LISTUSER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TXTUSER)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_TXTUSER)->EnableWindow(false);//要编辑的用户名称是固定的
			CString userName = theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","UserName"));
			SetDlgItemText(IDC_TXTUSER,userName);//设置要编辑的用户名称

			CString realName = theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","RealName"));
			SetDlgItemText(IDC_TXTREALNAME,realName);//设置要编辑的用户真实姓名

			CString limitTime = theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","Limit"));
			CTime curTime = mIni.StrToTime(limitTime);
			dtpEndTime.SetTime(&curTime);

			GetDlgItem(IDC_STATUPWD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTPWD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATPWDAG)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTPWDAG)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATREALNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TXTREALNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATDEPART)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBDEPART)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATENDTIME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_DTPENDTIME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECKEXIT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECKUSERONLINE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECKSYSMANAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECKDEPART)->ShowWindow(SW_SHOW);
			GetDlgItem(IDADDUSER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDRESET)->ShowWindow(SW_SHOW);

			cBtnExit.SetCheck(false);
			cBtnOnline.SetCheck(false);
			cBtnSysAdmin.SetCheck(false);
			cBtnDepartAdmin.SetCheck(false);

			SetDlgItemText(IDADDUSER,theApp.operGM.ReadValue("MGM","UM_UI_EditUser"));
			DepartList();//获取所有的部门信息
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

/// <summary>
/// 请求所有部门列表
/// </summary>
void CUserManage::DepartList()
{
	try
	{			
		//OperationGM operGM;

		cmbDepart.ResetContent();//清除已有的部门列表

		CSocketData socketdata;
		socketdata.InitCreate(1,1);
		
		int userByID=theApp.UserByID;

		char strInt[10];
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::DEPART_QUERY))//发送查询部门列表的请求
		{
		    ::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}


/// <summary>
/// 添加或修改用户信息
/// </summary>
void CUserManage::OnBnClickedAdduser()
{
	try
	{
		if(tbcResult.GetCurSel()==1)//如果是在添加用户信息的界面
		{
			AddUser();//添加用户信息
		}
		else if(tbcResult.GetCurSel()==2)//如果是在编辑用户信息的界面
		{
			EditUser();//编辑用户信息
		}
	}
	catch(...)
	{
	}
}

/// <summary>
/// 添加用户信息
/// </summary>
void CUserManage::AddUser()
{
	try
	{			
		//OperationGM operGM;
		CIni mIni;

		UpdateData(true);

		CString m_strAccount;	
		GetDlgItemText(IDC_TXTUSER,m_strAccount);//要添加的用户名
		if(m_strAccount=="")//用户名不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_InputName"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString m_strPwd;
		GetDlgItemText(IDC_TXTPWD,m_strPwd);//用户的密码
		if(m_strPwd=="")//密码不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_InputPwd"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString m_strPwdAG;
		GetDlgItemText(IDC_TXTPWDAG,m_strPwdAG);//重复用户密码
		if(m_strPwdAG=="")//重复密码不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","MP_Warn_InputNPwdAG"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		if(m_strPwd!=m_strPwdAG)//密码前后要相同
		{
			MessageBox(theApp.operGM.ReadValue("MGM","MP_Warn_PwdNotSame"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString realName;
		GetDlgItemText(IDC_TXTREALNAME,realName);//用户的真实姓名
		if(realName=="")//用户的真实姓名不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_InputRealName"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString DepartName;
		GetDlgItemText(IDC_CMBDEPART,DepartName);//用户所在的部门名称
		if(DepartName=="")//用户的部门名称不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_SelectDepart"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CTime mTime;		
		dtpEndTime.GetTime(mTime);//获取设置的使用时效
		CTime curTime = CTime::GetCurrentTime();//获取系统当前时间
		if(mTime <= curTime)//使用时效不能小于当前时间
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_TimeLimit"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		CString strLimitTime = "";
		strLimitTime.Format("%i/%i/%i 00:00:00",mTime.GetYear(),mTime.GetMonth(),mTime.GetDay());//将使用时效格式化成CString类型

		int status = cBtnExit.GetCheck() ? 0 : 1;//是否停用该帐号
		int sysAdmin = cBtnSysAdmin.GetCheck() ? 1 : cBtnDepartAdmin.GetCheck() ? 2 : 0;//是系统管理员还是部门管理员

		int departID = 0;
		POSITION pos = DepartData.GetStartPosition(); //部门ID和部门名称保存在一个CMap类的对象中
		int nKey;
		CString pt;
		while (pos != NULL)//循环遍历CMap类的对象
		{
			DepartData.GetNextAssoc(pos, nKey, pt);//获取CMap类的对象中下面一项的内容，pos为位置，nkey为键值，pt为保存的内容
			if(pt == DepartName)//如果内容和当前选中的部门名称相同的话
			{
				departID = nKey;//键值就是要获取的部门ID
			}
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,8);//共有8个参数，操作员ID、要添加的用户名、密码、真实姓名、使用时效、用户状态（是否停用）、是不是系统管理员、部门ID
		char strInt[10];
		
		int userByID=theApp.UserByID;
		
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID
		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(m_strAccount),(unsigned char *)mIni.wcharToChar(m_strAccount));//要添加的用户名
		socketdata.AddTFLV(CEnumCore::TagName::PassWord,CEnumCore::TagFormat::TLV_STRING,strlen(m_strPwd),(unsigned char *)mIni.wcharToChar(m_strPwd));//密码
		socketdata.AddTFLV(CEnumCore::TagName::RealName,CEnumCore::TagFormat::TLV_STRING,strlen(realName),(unsigned char *)mIni.wcharToChar(realName));	//	真实姓名
		socketdata.AddTFLV(CEnumCore::TagName::Limit,CEnumCore::TagFormat::TLV_STRING,strlen(strLimitTime),(unsigned char *)mIni.wcharToChar(strLimitTime));//使用时效
		
		_itoa(status,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_Status,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户状态（是否停用）
		
		_itoa(sysAdmin,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SysAdmin,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//是不是系统管理员
		
		_itoa(departID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::DepartID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//部门ID

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_CREATE))//发送添加用户的请求
		{
		    ::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

/// <summary>
/// 修改用户信息
/// </summary>
void CUserManage::EditUser()
{
	try
	{			
		CIni mIni;
		//OperationGM operGM;

		CString m_strAccount;//用户名，不能修改
		GetDlgItemText(IDC_TXTUSER,m_strAccount);
		if(m_strAccount=="")//用户名不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_SelectModiUser"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString realName;//要编辑的用户真实姓名
		GetDlgItemText(IDC_TXTREALNAME,realName);
		if(realName=="")//用户的真实姓名不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_InputRealName"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString DepartName;
		GetDlgItemText(IDC_CMBDEPART,DepartName);//用户所在的部门名称
		if(DepartName=="")//用户的部门名称不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_SelectDepart"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CTime mTime;		
		dtpEndTime.GetTime(mTime);//获取设置的使用时效
		CTime curTime = CTime::GetCurrentTime();//获取系统当前时间
		if(mTime <= curTime)//使用时效不能小于当前时间
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_TimeLimit"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		CString strLimitTime = "";
		strLimitTime.Format("%i-%i-%i 00:00:00",mTime.GetYear(),mTime.GetMonth(),mTime.GetDay());//将使用时效格式化成CString类型

		int departID = 0;
		POSITION pos = DepartData.GetStartPosition(); //部门ID和部门名称保存在一个CMap类的对象中
		int nKey;
		CString pt;
		while (pos != NULL)//循环遍历CMap类的对象
		{
			DepartData.GetNextAssoc(pos, nKey, pt);//获取CMap类的对象中下面一项的内容，pos为位置，nkey为键值，pt为保存的内容
			if(pt == DepartName)//如果内容和当前选中的部门名称相同的话
			{
				departID = nKey;//键值就是要获取的部门ID
			}
		}

		int userID = atoi(mIni.wcharToChar(theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","User_ID"))));//获取要编辑的用户ID
		int status = cBtnExit.GetCheck() ? 0 : 1;//是否停用该帐号
		int onlineActive = cBtnOnline.GetCheck() ? 1:0; //是否设置用户为在线状态
		int sysAdmin = cBtnSysAdmin.GetCheck() ? 1 : cBtnDepartAdmin.GetCheck() ? 2 : 0;//是系统管理员还是部门管理员

		CSocketData socketdata;
		socketdata.InitCreate(1,9);//共有9个参数，操作员ID、要编辑的用户ID、要编辑的用户名、真实姓名、使用时效、用户状态（是否停用）、用户是否在线、是不是系统管理员、部门ID
		char strInt[10];
		
		int userByID=theApp.UserByID;
		
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID
		
		_itoa(userID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//要编辑的用户ID

		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(m_strAccount),(unsigned char *)mIni.wcharToChar(m_strAccount));//要编辑的用户名
		socketdata.AddTFLV(CEnumCore::TagName::RealName,CEnumCore::TagFormat::TLV_STRING,strlen(realName),(unsigned char *)mIni.wcharToChar(realName));//真实姓名

		socketdata.AddTFLV(CEnumCore::TagName::Limit,CEnumCore::TagFormat::TLV_DATE,strlen(strLimitTime),(unsigned char *)mIni.wcharToChar(strLimitTime));//使用时效
		
		_itoa(status,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_Status,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户状态（是否停用）
		
		_itoa(onlineActive,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::OnlineActive,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户是否在线
		
		_itoa(sysAdmin,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SysAdmin,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//是不是系统管理员

		_itoa(departID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::DepartID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//部门ID

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_UPDATE))//发送编辑用户信息的请求
		{
		    ::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

/// <summary>
/// 重置信息
/// </summary>
void CUserManage::OnBnClickedReset()
{
	SetDlgItemText(IDC_TXTPWD,"");
	SetDlgItemText(IDC_TXTPWDAG,"");
	SetDlgItemText(IDC_TXTREALNAME,"");
	DepartList();//获取部门列表
	
	CTime curTime = CTime::GetCurrentTime();
	dtpEndTime.SetTime(&curTime);//使用时效设置为当前时间

	cBtnExit.SetCheck(0);
	cBtnOnline.SetCheck(0);
	cBtnSysAdmin.SetCheck(0);
	cBtnDepartAdmin.SetCheck(0);
}

// 右键点击用户列表分配权限
void CUserManage::OnNMRclickListuser(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
    {
        DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
		CPoint mPoint(LOWORD(dwPos), HIWORD(dwPos));

		listUser.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nItem = listUser.SubItemHitTest(&lvinfo);//保存在用户列表中选中的行号
		if(nItem >= 0)
		{
			CMenu menu;
			VERIFY( menu.LoadMenu(IDR_MENUMANAGE));
			CMenu* popup = menu.GetSubMenu(0);
			ASSERT( popup != NULL );
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, mPoint.x, mPoint.y, this );
			popup->DestroyMenu();
			popup=NULL;
			menu.DestroyMenu();
		}
    } 
	catch(...)
	{
	}
	*pResult = 0;
}

//重置用户MAC
void CUserManage::OnUpdateUserMAC()
{
	try
	{
		CIni mIni;
		//OperationGM operGM;
		CString uName = theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","UserName"));//获取要分配权限的用户名
		int uID = atoi(mIni.wcharToChar(theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","User_ID"))));//获取要分配权限的用户ID
		
		::EnableWindow(this->m_hWnd,false);//让父句柄为Disable的状态
		::EnableWindow(this->GetParent()->m_hWnd,false);//让父句柄为Disable的状态

		theApp.updateUserMac.initVar(uName,uID);		
		theApp.updateUserMac.DoModal();		
		::SetParent(theApp.updateUserMac.m_hWnd,this->m_hWnd);//进行句柄的设置
	}
	catch(...)
	{
	}
}

//修改用户密码
void CUserManage::OnModiUserPwd()
{
	try
	{
		CIni mIni;
		//OperationGM operGM;
		CString uName = theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","UserName"));//获取要分配权限的用户名
		int uID = atoi(mIni.wcharToChar(theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","User_ID"))));//获取要分配权限的用户ID
		
		::EnableWindow(this->m_hWnd,false);//让父句柄为Disable的状态
		::EnableWindow(this->GetParent()->m_hWnd,false);//让父句柄为Disable的状态

		theApp.modiUserPwd.initVar(uName,uID);		
		theApp.modiUserPwd.DoModal();		
		::SetParent(theApp.modiUserPwd.m_hWnd,this->m_hWnd);//进行句柄的设置
	}
	catch(...)
	{
	}
}

// 给选中用户分配权限
void CUserManage::OnPopedomManage()
{
	try
	{
		CIni mIni;
		//OperationGM operGM;
		CString uName = theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","UserName"));//获取要分配权限的用户名
		int uID = atoi(mIni.wcharToChar(theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","User_ID"))));//获取要分配权限的用户ID
		
		::EnableWindow(this->m_hWnd,false);//让父句柄为Disable的状态
		::EnableWindow(this->GetParent()->m_hWnd,false);//让父句柄为Disable的状态

		theApp.popedomManage.initVar(uName,uID);		
		theApp.popedomManage.DoModal();
		::SetParent(theApp.popedomManage.m_hWnd,this->m_hWnd);//进行句柄的设置
	}
	catch(...)
	{
	}
}

/// <summary>
/// 设置帐号为系统管理员
/// </summary>
void CUserManage::OnBnClickedChecksysmanage()
{
	if(cBtnSysAdmin.GetCheck())
	{
		cBtnDepartAdmin.SetCheck(0);
	}
}

/// <summary>
/// 设置帐号为部门管理员
/// </summary>
void CUserManage::OnBnClickedCheckdepart()
{
	if(cBtnDepartAdmin.GetCheck())
	{
		cBtnSysAdmin.SetCheck(0);
	}
}

/// <summary>
/// 接收返回信息
/// </summary>
LRESULT CUserManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的长度
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Receive");//当前的状态为接收到了返回信息

	CIni mIni;
	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	//OperationGM operGM;

	int pageCount = 0;//保存页数信息

	switch(theApp.m_tag_id)
	{
	case CEnumCore::Message_Tag_ID::USER_QUERY_ALL_RESP://如果返回的是对请求用户列表的响应
		{			
			if(pageInfo)//如果已经有了翻页信息
			{
				theApp.operGM.BuildDataTable(&socketdata,&listUser,&pageCount);//在CListCtrl中构造得到的内容
			}
			else
			{
				theApp.operGM.BuildDataTable(&socketdata,&listUser,&pageCount);

				if(pageCount<=0)//如果返回值为空
				{
					pageInfo = false;//翻页信息为false,不能翻页
					cmbPage.ResetContent();//储存页数的CComboBox也为空
					while(listUser.DeleteColumn(0)){}//CListCtrl为空
				}
				else
				{
					cmbPage.ResetContent();//储存页数的CComboBox也为空
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbPage.AddString(str);//添加所有的页数
					}
					cmbPage.SetCurSel(0);//最开始显示第一页
					if(pageCount == 1)
					{
						pageInfo = false;//如果只有一页，翻页信息也为false，不需要翻页
					}
					else
					{
						pageInfo = true;//翻页信息为true，可以翻页进行查询
					}
				}
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::DEPART_QUERY_RESP://如果返回的是对请求部门列表的响应
		{
			if(!DepartData.IsEmpty())
			{
				DepartData.RemoveAll();
			}
			for(int i=0;i<socketdata.getQueryNum();i++)
			{
				int departID = atoi((char*)&socketdata.getTLVByName(i+1,CEnumCore::TagName::DepartID).lpdata);//从得到的数据中获取所有的部门ID信息
				CString departName = (LPCSTR)&socketdata.getTLVByName(i+1,CEnumCore::TagName::DepartName).lpdata;//获取部门名称信息
				DepartData.SetAt(departID,departName);//将部门ID和部门名称以键-值对的形式保存在CMap类的对象中
			}
			theApp.operGM.BuildCombox(&socketdata,&cmbDepart);	//构造保存部门名称信息的CComboBox
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_CREATE_RESP://如果返回的是操作类请求的响应
	case CEnumCore::Message_Tag_ID::USER_UPDATE_RESP:
	case CEnumCore::Message_Tag_ID::USER_DELETE_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operGM.ShowResult(result);//显示操作结果

			tbcResult.SetCurSel(0);
			GetDlgItem(IDC_LISTUSER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_STATNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTUSER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATUPWD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTPWD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATPWDAG)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTPWDAG)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATREALNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTREALNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATDEPART)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBDEPART)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATENDTIME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_DTPENDTIME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKEXIT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKUSERONLINE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKSYSMANAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKDEPART)->ShowWindow(SW_HIDE);
			GetDlgItem(IDADDUSER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDRESET)->ShowWindow(SW_HIDE);

			InitUserList();//再次查询用户列表信息
		}
		break;
	default:
		{
			MessageBox("Error","Error",0);
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return true;
}

// 关闭对话框
void CUserManage::OnClose()
{
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Close");//关闭窗体
	if(!DepartData.IsEmpty())
	{
		DepartData.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
