// CG2UserShoppingInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2UserShoppingInfo.h"
#include ".\CG2UserShoppingInfo.h"


// CCG2UserShoppingInfo 对话框

IMPLEMENT_DYNAMIC(CCG2UserShoppingInfo, CDialog)
CCG2UserShoppingInfo::CCG2UserShoppingInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2UserShoppingInfo::IDD, pParent)
{
}

CCG2UserShoppingInfo::~CCG2UserShoppingInfo()
{
}

void CCG2UserShoppingInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBKPPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listResult);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPKPPAGE, GrpPage);
	DDX_Control(pDX, IDC_BEGINTIME, dtcBeginDate);
	DDX_Control(pDX, IDC_ENDTIME, dtcEndDate);
	DDX_Control(pDX, IDC_CK1, ck_Send);
	DDX_Control(pDX, IDC_CK2, ck_Recv);
}


BEGIN_MESSAGE_MAP(CCG2UserShoppingInfo, CDialog)
	ON_CBN_SELCHANGE(IDC_CMBKPPAGE, OnCbnSelchangeCmbkppage)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CK1, OnBnClickedCk1)
	ON_BN_CLICKED(IDC_CK2, OnBnClickedCk2)
END_MESSAGE_MAP()

// 初始化对话框
BOOL CCG2UserShoppingInfo::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// 初始化显示字符	

	nItem = -1;
	pageInfo = false;//初始化一些私有变量

	CRect rs;
	GetClientRect(rs);//获取对话框的大小信息

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

	if(GrpPage.m_hWnd != NULL)
	{
		GrpPage.GetWindowRect(srcRect);//获取GrpPage的大小信息
		grpPHeight = srcRect.bottom - srcRect.top;//得到GrpPage的高度信息

		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listUser的位置
	}

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//初始建立对话框


	return TRUE;
}

// 初始化显示字符
void CCG2UserShoppingInfo::InitUI()
{
	//OperationCG2 theApp.operCG2;

	SetWindowText(theApp.operCG2.ReadValue("MCG2","KP_UI_KickPlayer"));
	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));
	SetDlgItemText(IDC_LBLBEGINTIME,theApp.operCG2.ReadValue("MCG2","NI_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operCG2.ReadValue("MCG2","NI_UI_EndTime"));
	SetDlgItemText(IDC_CK1,theApp.operCG2.ReadValue("MCG2","BU_UI_SENDLOG"));
	SetDlgItemText(IDC_CK2,theApp.operCG2.ReadValue("MCG2","BU_UI_RECVLOG"));
	ck_Send.SetCheck(1);

	
	

}

// 自动改变大小
void CCG2UserShoppingInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rs;
	GetClientRect(rs);

	CRect newRect;
	
	if(GrpSearch.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + grpHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpSearch.MoveWindow(newRect);//设置好GrpSearch的位置
	}

	if(GrpPage.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listResult的位置
	}
}

//设置背景颜色
HBRUSH CCG2UserShoppingInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询玩家资料信息
void CCG2UserShoppingInfo::OnBnClickedUisearch()
{
	try
	{
		//OperationCG2 theApp.operCG2;

		nItem = -1;//玩家资料列表没有选定项
		pageInfo = false;//玩家资料列表不能翻页	
		cmbPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listResult.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		UpdateData(true);			



		GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//获取玩家帐号
		if(UserName == "")//玩家帐号不能同时为空
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_InputUserName"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

	    UserInfo();
	}
	catch(...)
	{
	}
}

// 查询玩家资料信息
void CCG2UserShoppingInfo::UserInfo()
{
	//OperationCG2 theApp.operCG2;
	try
	{
		CIni mIni;	

		int index = theApp.operCG2.ReadIntValue("MCG2","index");//查询第一页的信息
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//每页显示50条记录

		nItem = -1;//玩家资料列表没有选定项
		pageInfo = false;//玩家资料列表不能翻页		
		cmbPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listResult.DeleteColumn(0)){}//清除玩家资料列表中的所有内容		

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];


		CTime BeginDate,EndDate;
		dtcBeginDate.GetTime(BeginDate);
		dtcEndDate.GetTime(EndDate);



		CTime LoginDT=CTime::CTime(BeginDate.GetYear(),BeginDate.GetMonth(),BeginDate.GetDay(),0,0,0);
		CTime LogoutDT=CTime::CTime(EndDate.GetYear(),EndDate.GetMonth(),EndDate.GetDay(),0,0,0);

		CString strLoginTime,strLogoutTime;
		strLoginTime=LoginDT.Format("%Y-%m-%d %H:%M:%S");//设置开始时间
		strLogoutTime=LogoutDT.Format("%Y-%m-%d %H:%M:%S");//设置结束时间

		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

		socketdata.AddTFLV(CEnumCore::TagName::CG2_StartTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLoginTime),(unsigned char *)mIni.wcharToChar(strLoginTime));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLogoutTime),(unsigned char *)mIni.wcharToChar(strLogoutTime));//玩家昵称


		int iTypeID=0;
		switch(ck_Send.GetCheck())
		{
		case 0:
			iTypeID=2;
			break;
		case 1:
			iTypeID=1;
			break;
		}
		_itoa(iTypeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_TypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//类型

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_UserShoppingInfo_Query);//发送查询玩家资料信息的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// 翻页进行查询
void CCG2UserShoppingInfo::OnCbnSelchangeCmbkppage()
{	
	try
	{
		if(pageInfo)//如果可以翻页的话
		{	
			CIni mIni;
			//OperationCG2 theApp.operCG2;
			
			char strInt[10];
			int index = cmbPage.GetCurSel() + 1;//页数为cmbPage当前的索引值加1，也就是cmbPage中当前显示的值
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//每页显示50条记录

			while(listResult.DeleteColumn(0)){}//清除页面内容

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数


			CTime BeginDate,EndDate;
			dtcBeginDate.GetTime(BeginDate);
			dtcEndDate.GetTime(EndDate);



			CTime LoginDT=CTime::CTime(BeginDate.GetYear(),BeginDate.GetMonth(),BeginDate.GetDay(),0,0,0);
			CTime LogoutDT=CTime::CTime(EndDate.GetYear(),EndDate.GetMonth(),EndDate.GetDay(),0,0,0);

			CString strLoginTime,strLogoutTime;
			strLoginTime=LoginDT.Format("%Y-%m-%d %H:%M:%S");//设置开始时间
			strLogoutTime=LogoutDT.Format("%Y-%m-%d %H:%M:%S");//设置结束时间

			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称


			socketdata.AddTFLV(CEnumCore::TagName::CG2_StartTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLoginTime),(unsigned char *)mIni.wcharToChar(strLoginTime));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLogoutTime),(unsigned char *)mIni.wcharToChar(strLogoutTime));//玩家昵称
			int iTypeID=0;
			switch(ck_Send.GetCheck())
			{
			case 0:
				iTypeID=2;
				break;
			case 1:
				iTypeID=1;
				break;
			}
			_itoa(iTypeID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::CG2_TypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//类型

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_UserShoppingInfo_Query);//当前的状态为发送查询请求

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// 接收返回信息
LRESULT CCG2UserShoppingInfo::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::CG2_UserShoppingInfo_Query_Resp ://查询玩家资料信息的回应
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{					
					nItem = -1;//不能选中某一行
					pageInfo = false;//不能翻页
					cmbPage.ResetContent();//清空页数复选框
					while(listResult.DeleteColumn(0)){}//清空CListCtrl内容
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
						pageInfo = false;//只有一页数据，不能翻页
					}
					else
					{
						pageInfo = true;//有多页数据，可以翻页
					}
				}				
			}
		}
		break;
	default:
		break;
	}
	socketdata.Destroy();
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	return false;
}

// 关闭对话框
void CCG2UserShoppingInfo::OnBnClickedUicancel()
{
	//OperationCG2 theApp.operCG2;
	/*dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Close");//关闭窗体
	OnClose();*/
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	ck_Send.SetCheck(1);
	ck_Recv.SetCheck(0);
	SYSTEMTIME sys; 
	GetLocalTime( &sys );
	dtcBeginDate.SetTime(sys);
	dtcEndDate.SetTime(sys);
	nItem = -1;//玩家资料列表没有选定项
	pageInfo = false;//玩家资料列表不能翻页	
	cmbPage.ResetContent();//清除玩家资料列表翻页的复选框
	while(listResult.DeleteColumn(0)){}//清除玩家资料列表中的所有内容


}

// 关闭对话框
void CCG2UserShoppingInfo::OnClose()
{
	DestroyWindow();
	CDialog::OnClose();
}



void CCG2UserShoppingInfo::OnBnClickedCk1()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(ck_Send.GetCheck())
	{
	case 0:
		{
			ck_Recv.SetCheck(1);

		}
		break;
	case 1:
		{
			ck_Recv.SetCheck(0);
		}	
		break;
	}
}

void CCG2UserShoppingInfo::OnBnClickedCk2()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(ck_Recv.GetCheck())
	{
	case 0:
		{
			ck_Send.SetCheck(1);

		}
		break;
	case 1:
		{
			ck_Send.SetCheck(0);
		}	
		break;
	}
}
