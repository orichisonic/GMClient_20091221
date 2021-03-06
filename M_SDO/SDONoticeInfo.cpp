// SDONoticeInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDONoticeInfo.h"
#include ".\sdonoticeinfo.h"


// CSDONoticeInfo 对话框

IMPLEMENT_DYNAMIC(CSDONoticeInfo, CDialog)
CSDONoticeInfo::CSDONoticeInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CSDONoticeInfo::IDD, pParent)
{
}

CSDONoticeInfo::~CSDONoticeInfo()
{
}

void CSDONoticeInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTSERVER, listServer);
	DDX_Control(pDX, IDC_LISTNOTICE, listNotice);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_DTPSTARTDATE, dtcStartDate);
	DDX_Control(pDX, IDC_DTPENDDATE, dtcEndDate);
	DDX_Control(pDX, IDC_DTPSTARTTIME, dtcStartTime);
	DDX_Control(pDX, IDC_DTPENDTIME, dtcEndTime);
	DDX_Control(pDX, IDC_CHECKIMME, checkSendImme);
	DDX_Control(pDX, IDC_CMBSTATUS, cmbStatus);
	DDX_Control(pDX, IDC_EDITINTERVAL, txtInterval);
}


BEGIN_MESSAGE_MAP(CSDONoticeInfo, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECKSELECTALL, OnBnClickedCheckselectall)
	ON_BN_CLICKED(IDC_BTNNOTICEINFO, OnBnClickedBtnnoticeinfo)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTNOTICE, OnNMDblclkListnotice)
	ON_BN_CLICKED(IDBTNNOTICE, OnBnClickedBtnnotice)
	ON_BN_CLICKED(IDC_CHECKIMME, OnBnClickedCheckimme)
	ON_BN_CLICKED(IDBTNRESET, OnBnClickedBtnreset)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTNOTICE, OnLvnColumnclickListnotice)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSDONoticeInfo 消息处理程序

//初始化对话框
BOOL CSDONoticeInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUI();

	dtcStartTime.SetFormat("HH:mm:ss");
	dtcEndTime.SetFormat("HH:mm:ss");
	
	nItem = 0;// 单击公告列表得到行号
	pageInfo = false;// 判断是否需要翻页
	addOrEdit = false;// 发送公告
	ServerIP = "";// 服务器IP
	NoticeID = 0;// 公告ID	
	AllServer = false;// 是否在所有大区发送公告
	NoticeType=0;
	strContent="";
	iInteval=0;

	//OperationPAL operPAL;

	cmbStatus.ResetContent();
	cmbStatus.AddString(theApp.operSDO.ReadValue("MSDO","NI_UI_UnSend"));//未发送
	cmbStatus.AddString(theApp.operSDO.ReadValue("MSDO","NI_UI_Sending"));
	cmbStatus.AddString(theApp.operSDO.ReadValue("MSDO","NI_UI_Sended"));//已发送
	cmbStatus.SetCurSel(0);

	GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//隐藏公告状态
	GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);

	listServer.SetExtendedStyle(listServer.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);//服务器列表中需要显示CheckBox
	listServer.InsertColumn(0,theApp.operSDO.ReadValue("MSDO","NI_UI_ServerList"),LVCFMT_CENTER,150,-1);

	SetProp(listNotice.GetSafeHwnd(),"排序列号",(HANDLE)0);
    SetProp(listNotice.GetSafeHwnd(),"排序顺序",(HANDLE)1);

	CRect rs;
	GetClientRect(rs);; //获取对话框的大小信息

	CRect srcRect;
	CRect newRect;

	if( listServer.m_hWnd != NULL )   
	{
		listServer.GetWindowRect(srcRect);//获取listResult的大小信息
		listRWidth = srcRect.right - srcRect.left;//得到listResult的宽度信息

		newRect.top = rs.top + 45;		
		newRect.left = rs.left + 10;
		newRect.right = newRect.left + listRWidth;
		newRect.bottom = rs.bottom - 8;

		listServer.MoveWindow(newRect);//设置listResult的位置
	}  

	CWnd* pWnd = GetDlgItem(IDC_EDITCONTENT);  
	if( pWnd )   
	{
		pWnd->GetWindowRect(srcRect);//获取公告内容CEdit的大小信息
		contentLength = srcRect.bottom - srcRect.top;//获取公告内容CEdit的高度信息

		newRect.top = rs.top + 117;		
		newRect.left = newRect.right + 110;
		newRect.right = rs.right - 8;
		newRect.bottom = newRect.top + contentLength;

		pWnd->MoveWindow(newRect);//设置公告内容CEdit的位置
	}   
	
	pWnd = GetDlgItem(IDC_GRPPAGE);  
	if( pWnd )   
	{
		pWnd->GetWindowRect(srcRect);//获取GrpPage的大小信息
		gPageLength = srcRect.bottom - srcRect.top;//获取GrpPage的高度信息

		newRect.top = newRect.bottom + 33;		
		newRect.left = rs.left + 10 + listRWidth;
		newRect.right = rs.right - 8;
		newRect.bottom = newRect.top + gPageLength;

		pWnd->MoveWindow(newRect);//设置GrpPage的位置
	}   

	if( listNotice.m_hWnd != NULL )   
	{
		listNotice.GetWindowRect(srcRect);//获取listNotice的大小信息

		newRect.top = newRect.bottom;
		newRect.left = rs.left + 10 + listRWidth;
		newRect.right = rs.right - 8;
		newRect.bottom = rs.bottom - 8;

		listNotice.MoveWindow(newRect);//设置listNotice的位置
	}

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Create");//当前的状态为初始建立对话框

	if(theApp.operSDO.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//处理快捷键响应函数
BOOL CSDONoticeInfo::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listServer.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&listServer);				
				}
				
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listServer.m_hWnd)
				{
					for(int i=0; i<listServer.GetItemCount(); i++)
					{
					    listServer.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listServer.EnsureVisible(i,false);
					}
				}
				
			}
		}		
	}
	return FALSE;
}

// 初始化显示字符
void CSDONoticeInfo::InitUI()
{
	SetWindowText(theApp.operSDO.ReadValue("MSDO","NI_UI_NoticeInfo"));

	SetDlgItemText(IDC_CHECKSELECTALL,theApp.operSDO.ReadValue("MSDO","NI_UI_SelectAll"));

	SetDlgItemText(IDC_BTNNOTICEINFO,theApp.operSDO.ReadValue("MSDO","NI_UI_NoticeCheck"));
	SetDlgItemText(IDC_LBLHINT,theApp.operSDO.ReadValue("MSDO","NI_UI_NoticeHint"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operSDO.ReadValue("MSDO","BU_UI_LblPage"));

	SetDlgItemText(IDC_LBLSTARTTIME,theApp.operSDO.ReadValue("MSDO","NI_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operSDO.ReadValue("MSDO","NI_UI_EndTime"));
	SetDlgItemText(IDC_LBLINTERVAL,theApp.operSDO.ReadValue("MSDO","NI_UI_TimeInterval"));
	SetDlgItemText(IDC_LBLTIME,theApp.operSDO.ReadValue("MSDO","NI_UI_Minite"));	
	SetDlgItemText(IDC_LBLCONTENT,theApp.operSDO.ReadValue("MSDO","NI_UI_SendContent"));
	SetDlgItemText(IDC_CHECKIMME,theApp.operSDO.ReadValue("MSDO","NI_UI_SendImme"));
	SetDlgItemText(IDC_LBLSTATUS,theApp.operSDO.ReadValue("MSDO","NI_UI_NoticeStatus"));
	SetDlgItemText(IDBTNNOTICE,theApp.operSDO.ReadValue("MSDO","NI_UI_AddNotice"));
	SetDlgItemText(IDBTNRESET,theApp.operSDO.ReadValue("MSDO","Reset"));
}

// 自动改变大小
void CSDONoticeInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rs;
	GetClientRect(rs);

	CRect newRect;

	if( listServer.m_hWnd != NULL )   
	{
		newRect.top = rs.top + 45;		
		newRect.left = rs.left + 10;
		newRect.right = newRect.left + listRWidth;
		newRect.bottom = rs.bottom - 10;

		listServer.MoveWindow(newRect);//设置listResult的位置
	}  

	CWnd* pWnd = GetDlgItem(IDC_EDITCONTENT);  
	if( pWnd )   
	{
		newRect.top = rs.top + 117;		
		newRect.left = newRect.right + 81;
		newRect.right = rs.right - 8;
		newRect.bottom = newRect.top + contentLength;

		pWnd->MoveWindow(newRect);//设置公告内容CEdit的位置
	}   
	
	pWnd = GetDlgItem(IDC_GRPPAGE);  
	if( pWnd )   
	{
		newRect.top = newRect.bottom + 33;		
		newRect.left = rs.left + 10 + listRWidth;
		newRect.right = rs.right - 8;
		newRect.bottom = newRect.top + gPageLength;

		pWnd->MoveWindow(newRect);//设置GrpPage的位置
	}   

	if( listNotice.m_hWnd != NULL )   
	{
		newRect.top = newRect.bottom;		
		newRect.left = rs.left + 10 + listRWidth;
		newRect.right = rs.right - 8;
		newRect.bottom = rs.bottom - 8;

		listNotice.MoveWindow(newRect);//设置listNotice的位置
	}
}

//设置背景颜色
HBRUSH CSDONoticeInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 选择所有游戏服务器进行发送
void CSDONoticeInfo::OnBnClickedCheckselectall()
{
	// TODO: 在此添加控件通知处理程序代码
	if(AllServer == false)
	{
		for(int i=0; i<listServer.GetItemCount(); i++)
		{
			listServer.SetCheck(i);//选中所有的游戏服务器
		}
		listServer.EnableWindow(true);//让游戏服务器列表变为Disable的状态
		AllServer = true;
	}
	else
	{
		for(int i=0; i<listServer.GetItemCount(); i++)
		{
			listServer.SetCheck(i,false);//取消选中所有的游戏服务器
		}
		//listResult.EnableWindow(true);//让游戏服务器列表变为Enable的状态
		AllServer = false;
	}
}

// 查看公告信息
void CSDONoticeInfo::NoticeInfo()
{
	nItem = 0;
	pageInfo = false;//公告信息不能翻页
	cmbPage.ResetContent();//公告信息翻页复选框为空
	while(listNotice.DeleteColumn(0)){}//删除所有公告列表信息
	
	//OperationPAL operPAL;	
	try
	{
		char strInt[10];
		int index = theApp.operSDO.ReadIntValue("MSDO","index");//查看第一页的记录
		int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");//每页有50条记录


        
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有两个参数，页数、每页的记录数

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录数

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_BOARDTASK_QUERY))//发送查询公告信息的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}
}

// 查看公告信息
void CSDONoticeInfo::OnBnClickedBtnnoticeinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	NoticeInfo();
}

// 翻页查看公告信息
void CSDONoticeInfo::OnCbnSelchangeCmbpage()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		if(pageInfo)
		{
			while(listNotice.DeleteColumn(0)){}//清除公告列表中的所有内容
			
			int index = cmbPage.GetCurSel() + 1;//翻页查看的页数
			int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");//每页有50条记录

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有两个参数，页数、每页的记录数
			char strInt[10];

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录数

			int midlength = socketdata.EnBody();
			if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_BOARDTASK_QUERY))//发送查询公告信息的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Error_NoticeInfo"),theApp.operSDO.ReadValue("MSDO","Error"),0);
	}
}

// 双击公告信息进行编辑公告
void CSDONoticeInfo::OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CIni mIni;
	//OperationPAL operPAL;	
	try
	{
		if(listNotice.GetItemCount() > 0)//如果公告列表中当前有记录
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listNotice.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listNotice.SubItemHitTest(&lvinfo);//获取要编辑的公告所处的行号

			if(nItem >= 0)
			{
				NoticeID = atoi(theApp.operSDO.GetValueByColName(&listNotice, nItem, theApp.operSDO.ReadValue("MSDO","SDO_TaskID")));//获取公告ID
				strContent =theApp.operSDO.GetValueByColName(&listNotice, nItem, theApp.operSDO.ReadValue("MSDO","SDO_BoardMessage"));//公告内容
				iInteval =atoi(theApp.operSDO.GetValueByColName(&listNotice, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Interval")));//间隔

				SetDlgItemText(IDC_EDITCONTENT,strContent);
				SetDlgItemInt(IDC_EDITINTERVAL,iInteval/60);
				for(int i=0;i<listServer.GetItemCount();i++)
				{
					listServer.SetCheck(i,false);
				}

				GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);//让服务器列表的状态变为Enable		
				SetDlgItemText(IDBTNNOTICE,theApp.operSDO.ReadValue("MSDO","NI_UI_EditNotice"));

				GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_SHOW);//隐藏公告状态
				GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_SHOW);

				//EditNotice();

/*				CSocketData socketdata;
				socketdata.InitCreate(1,10);//共有两个参数，页数、每页的记录数
				char strInt[10];

				_itoa(NoticeID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::SDO_TaskID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

				
				int midlength = socketdata.EnBody();
				if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_BOARDMESSAGE_REQ))//
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);
					dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
				}
				socketdata.Destroy();
*/
			}
		}
		else
		{
			nItem = 0;
			GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//不显示公告状态
			GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);//让服务器列表的状态变为Enable		
			SetDlgItemText(IDBTNNOTICE,theApp.operSDO.ReadValue("MSDO","NI_UI_AddNotice"));
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// 发送公告
void CSDONoticeInfo::AddNotice()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{		
		CIni mIni;

		UpdateData(true);

		int svrCheck = 0;
		for(int i=0;i<listServer.GetItemCount();i++)
		{
			if(listServer.GetCheck(i))//查看有没有选中当前的游戏服务器
			{
				svrCheck++;
			}
		}
		if(svrCheck == 0)//发送公告时，游戏服务器不能为空
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_ServerListNull"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
			return;
		}

		CString NoticeContent = "";
		GetDlgItemText(IDC_EDITCONTENT, NoticeContent);//获取公告内容

		if(NoticeContent == "")//公告内容不能为空
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_ContentNotNull"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
			return;
		}

		if(strlen(NoticeContent) >= 256)//公告内容不能超过256个字符
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_ContentTooLong"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
			return;
		}

		CTime curTime = CTime::GetCurrentTime();

		CTime StartDate;
		dtcStartDate.GetTime(StartDate);
		CTime StartTime;
		dtcStartTime.GetTime(StartTime);//获取开始时间

		CTime EndDate;
		dtcEndDate.GetTime(EndDate);
		CTime EndTime;
		dtcEndTime.GetTime(EndTime);//获取结束时间

		CTime beginTime = CTime::CTime(StartDate.GetYear(),StartDate.GetMonth(),StartDate.GetDay(),StartTime.GetHour(),StartTime.GetMinute(),StartTime.GetSecond());
		CTime toTime = CTime::CTime(EndDate.GetYear(),EndDate.GetMonth(),EndDate.GetDay(),EndTime.GetHour(),EndTime.GetMinute(),EndTime.GetSecond());

		CString strBeginTime = beginTime.Format("%Y-%m-%d %H:%M:%S");//设置开始时间
		CString strEndTime = toTime.Format("%Y-%m-%d %H:%M:%S");//设置结束时间

		int interval = GetDlgItemInt(IDC_EDITINTERVAL);//获取时间间隔
		interval=interval*60;


		if(checkSendImme.GetCheck() == 1)//如果是立即发送
		{
			interval = 0;//时间间隔为0
			NoticeType=1;//即时公告
		}
		else//如果不是立即发送
		{
			if(toTime <= curTime)//结束时间不能小于当前时间
			{
				MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_StartTime"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
				return;
			}
			if(toTime <= beginTime)//结束时间不能小于开始时间
			{
				MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_TimeSpan"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
				return;
			}
			if(interval <= 0)//时间间隔必须大于0
			{
				MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_IntervalNull"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
				return;
			}
			CTimeSpan sTimeSpan = toTime - beginTime;
			if(interval >=sTimeSpan.GetTotalSeconds())///interval/60 >= sTimeSpan.GetTotalMinutes())//时间间隔必须在时间范围之内
			{
				MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_IntervalLong"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
				return;
			}
			NoticeType=0;//定时公告
		}

		CString strMsg = theApp.operSDO.ReadValue("MSDO","NI_Hint_AddNotice"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //提示玩家是否确定要添加公告
		{
			return;
		}

		CSocketData socketdata;
		char strInt[10];
		socketdata.InitCreate(1,10);//共有七个参数：开始时间、结束时间、时间间隔、公告内容、操作员ID、服务器IP，服务器名称

		socketdata.AddTFLV(CEnumCore::TagName::SDO_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//开始时间
		socketdata.AddTFLV(CEnumCore::TagName::SDO_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//结束时间

		_itoa(interval,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Interval,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//时间间隔
		socketdata.AddTFLV(CEnumCore::TagName::SDO_BoardMessage,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeContent),(unsigned char *)mIni.wcharToChar(NoticeContent));//公告内容

		//CString GSServerIP = "255.255.255.255";
		//socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(GSServerIP),(unsigned char *)mIni.wcharToChar(GSServerIP));//大区IP
		
		_itoa(NoticeType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Type,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//公告是即时还是定时

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		char strServerIP[2048];
		ZeroMemory(strServerIP,2048);
		if(AllServer)
		{
			ReturnServerIP(strServerIP);
			ServerName=ReturnServerName();
		}
		else
		{
			ReturnServerIP(strServerIP);
			ServerName=ReturnServerName();
		}

		int strlength=strlen(ServerName);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(strServerIP),(unsigned char *)&strServerIP);//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器IP)

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_BOARDTASK_INSERT))//发送添加公告的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//编辑公告
void CSDONoticeInfo::EditNotice()
{
	try
	{		
		CIni mIni;

		UpdateData(true);

		int svrCheck = 0;
		for(int i=0;i<listServer.GetItemCount();i++)
		{
			if(listServer.GetCheck(i))//查看有没有选中当前的游戏服务器
			{
				svrCheck++;
			}
		}
		if(svrCheck == 0)//发送公告时，游戏服务器不能为空
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_ServerListNull"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
			return;
		}

		CString NoticeContent = "";
		GetDlgItemText(IDC_EDITCONTENT, NoticeContent);//获取公告内容


		if(NoticeContent == "")//公告内容不能为空
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_ContentNotNull"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
			return;
		}

		if(strlen(NoticeContent) >= 256)//公告内容不能超过256个字符
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_ContentTooLong"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
			return;
		}

		CTime curTime = CTime::GetCurrentTime();

		CTime StartDate;
		dtcStartDate.GetTime(StartDate);
		CTime StartTime;
		dtcStartTime.GetTime(StartTime);//获取开始时间

		CTime EndDate;
		dtcEndDate.GetTime(EndDate);
		CTime EndTime;
		dtcEndTime.GetTime(EndTime);//获取结束时间

		CTime beginTime = CTime::CTime(StartDate.GetYear(),StartDate.GetMonth(),StartDate.GetDay(),StartTime.GetHour(),StartTime.GetMinute(),StartTime.GetSecond());
		CTime toTime = CTime::CTime(EndDate.GetYear(),EndDate.GetMonth(),EndDate.GetDay(),EndTime.GetHour(),EndTime.GetMinute(),EndTime.GetSecond());

		CString strBeginTime = beginTime.Format("%Y-%m-%d %H:%M:%S");//设置开始时间
		CString strEndTime = toTime.Format("%Y-%m-%d %H:%M:%S");//设置结束时间

		int interval = GetDlgItemInt(IDC_EDITINTERVAL);//获取时间间隔
		interval=interval*60;


		if(checkSendImme.GetCheck() == 1)//即时公告////cmbStatus.GetCurSel() == 1)//如果选择的公告状态是已发送，所有的参数都可以不做限制
		{
			interval = 0;//时间间隔为0
			NoticeType=1;//即时公告
		}
		else//如果选择的是未发送，要限制一些参数
		{
			/*if(NoticeContent == "")//公告内容不能为空
			{
				MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_ContentNotNull"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
				return;
			}

			if(strlen(NoticeContent) >= 256)//公告内容不能超过256个字符
			{
				MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_ContentTooLong"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
				return;
			}*/
			NoticeType=0;//定时公告

			if(toTime <= curTime)//结束时间不能小于当前时间
			{
				MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_StartTime"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
				return;
			}

			if(toTime <= beginTime)//结束时间不能小于开始时间
			{
				MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_TimeSpan"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
				return;
			}

			if(interval <= 0)//时间间隔必须大于0
			{
				MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_Interval"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
				return;
			}

			CTimeSpan sTimeSpan = toTime - beginTime;
			if(interval >= sTimeSpan.GetTotalSeconds())//sTimeSpan.GetTotalMinutes())//时间间隔必须在时间范围之内
			{
				MessageBox(theApp.operSDO.ReadValue("MSDO","NI_Warn_IntervalLong"),theApp.operSDO.ReadValue("MSDO","Warn"),0);
				return;
			}
		}

		CString strMsg = theApp.operSDO.ReadValue("MSDO","NI_Hint_EditNotice"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //提示是否编辑公告
		{
			return;
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,15);//共有9个参数：开始时间、结束时间、时间间隔、公告内容、大区IP、操作员ID、公告状态、公告ID、服务器IP
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::SDO_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//开始时间
		socketdata.AddTFLV(CEnumCore::TagName::SDO_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//结束时间

		_itoa(interval,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Interval,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//时间间隔
		socketdata.AddTFLV(CEnumCore::TagName::SDO_BoardMessage,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeContent),(unsigned char *)mIni.wcharToChar(NoticeContent));//公告内容

		//CString GSServerIP = "255.255.255.255";
		//socketdata.AddTFLV(CEnumCore::TagName::PAL2_GSServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(GSServerIP),(unsigned char *)mIni.wcharToChar(GSServerIP));//大区IP

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		_itoa(cmbStatus.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Status,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//公告状态

		_itoa(NoticeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_TaskID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//公告ID

		_itoa(NoticeType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Type,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//公告是即时还是定时

		char strServerIP[2048];
		ZeroMemory(strServerIP,2048);
		if(AllServer)
		{
			ReturnServerIP(strServerIP);
			ServerName=ReturnServerName();
		}
		else
		{
			ReturnServerIP(strServerIP);
			ServerName=ReturnServerName();
		}

		int strlength=strlen(ServerName);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(strServerIP),(unsigned char *)&strServerIP);//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器IP)


		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_BOARDTASK_UPDATE))//发送编辑公告的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

// 发送公告或编辑公告
void CSDONoticeInfo::OnBnClickedBtnnotice()
{
	try
	{
		UpdateData(true);

		CString NoticeOp = "";
		GetDlgItemText(IDBTNNOTICE, NoticeOp);

		if(NoticeOp == theApp.operSDO.ReadValue("MSDO","NI_UI_AddNotice"))//如果按钮为添加公告
		{
			AddNotice();//添加公告
		}
		else if(NoticeOp == theApp.operSDO.ReadValue("MSDO","NI_UI_EditNotice"))//如果按钮为编辑公告
		{
			EditNotice();//编辑公告
		}
	}
	catch(...)
	{
	}
	
}

// 是否立即发送公告
void CSDONoticeInfo::OnBnClickedCheckimme()
{
	// TODO: 在此添加控件通知处理程序代码
	if(checkSendImme.GetCheck() == 1)//选择立即发送，让开始时间、结束时间、时间间隔的控件都变成Disable的状态
	{
		GetDlgItem(IDC_DTPSTARTDATE)->EnableWindow(false);
		GetDlgItem(IDC_DTPSTARTTIME)->EnableWindow(false);
		GetDlgItem(IDC_DTPENDDATE)->EnableWindow(false);
		GetDlgItem(IDC_DTPENDTIME)->EnableWindow(false);
		GetDlgItem(IDC_EDITINTERVAL)->EnableWindow(false);///IDC_EDITINTERVAL
	}
	else//不选择立即发送，让开始时间、结束时间、时间间隔的控件都变成Enable的状态
	{
		GetDlgItem(IDC_DTPSTARTDATE)->EnableWindow(true);
		GetDlgItem(IDC_DTPSTARTTIME)->EnableWindow(true);
		GetDlgItem(IDC_DTPENDDATE)->EnableWindow(true);
		GetDlgItem(IDC_DTPENDTIME)->EnableWindow(true);
		GetDlgItem(IDC_EDITINTERVAL)->EnableWindow(true);
	}
}

//返回要发送公告的游戏服务器列表
void CSDONoticeInfo::ReturnServerIP(char* allServerIP)
{
	CString serverName="";
	for(int i=0;i<listServer.GetItemCount();i++)
	{
		if(listServer.GetCheck(i))
		{
			ServerList.Lookup(i+1,serverName);//查找服务器IP
			if(i==0)
			{
				
				sprintf(allServerIP,"%s",serverName);
			}
			else
			{
				sprintf(allServerIP,"%s,%s",allServerIP,serverName);
			}
		}
	}
	sprintf(allServerIP,"%s,",allServerIP);
}

//返回要发送公告的游戏服务器名称列表
CString CSDONoticeInfo::ReturnServerName()
{
	CString rServerName = "";
	CString serverName = "";
	for(int i=0;i<listServer.GetItemCount();i++)
	{
		if(listServer.GetCheck(i))
		{
			serverName=listServer.GetItemText(i,0);//查找服务器名称
			rServerName += serverName;
			rServerName += ",";//将所有的服务器IP用","隔开
		}
	}
	return rServerName;
}

// 重置信息
void CSDONoticeInfo::OnBnClickedBtnreset()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CTime curTime = CTime::GetCurrentTime();//获取当前时间
		dtcStartDate.SetTime(&curTime);
		dtcStartTime.SetTime(&curTime);
		dtcEndDate.SetTime(&curTime);
		dtcEndTime.SetTime(&curTime);
		SetDlgItemText(IDC_EDITINTERVAL,"60");//设置时间间隔为60
		SetDlgItemText(IDC_EDITCONTENT,"");//设置公告内容为空
		GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//隐藏公告状态
		GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);//显示立即发送
		GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);
		cmbStatus.SetCurSel(0);
		checkSendImme.SetCheck(0);
	}
	catch(...)
	{
	}
}

// 接收返回信息
LRESULT  CSDONoticeInfo::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_DTPSTARTDATE)->EnableWindow(true);
	GetDlgItem(IDC_DTPSTARTTIME)->EnableWindow(true);
	GetDlgItem(IDC_DTPENDDATE)->EnableWindow(true);
	GetDlgItem(IDC_DTPENDTIME)->EnableWindow(true);
	GetDlgItem(IDC_EDITINTERVAL)->EnableWindow(true);

	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;
	//OperationPAL operPAL;	

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operSDO.ReadValue("MSDO","Main_UI_ParseData"),theApp.operSDO.ReadValue("MSDO","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	int pageCount = 0;

	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://查询服务器列表信息的回应
		{
			listServer.EnableWindow(true);

			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);//获取返回信息中的第一个模块
			if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)//如果第一个模块的TagName是MESSAGE，表示出现了错误信息，显示错误信息并返回
			{
				MessageBox((LPCSTR)&m_tflv.lpdata,theApp.operSDO.ReadValue("MSDO","Error"),0);
				socketdata.Destroy();
				return false;
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//获取所有的服务器IP
				ServerList.SetAt(i,ServerIP);//添加到CMap类的对象ServerList中
			}

			listServer.DeleteAllItems();//清除服务器列表中的所有内容
			CString serverName = "";
			int nRow = 0;
			for(int i=0;i<socketdata.getQueryNum();i++)
			{
				nRow = listServer.InsertItem(i,"");
				serverName = (LPSTR)&socketdata.getTLVByName(i+1,CEnumCore::TagName::ServerInfo_City).lpdata;//获取游戏服务器名称
				listServer.SetItemText(nRow,0,serverName);//将游戏服务器名称添加到服务器列表中
			}

			
		}
		break;
		////如果接收到的是公告列表请求的返回信息///公告查询//SDO_BOARDTASK_QUERY
	case CEnumCore::Message_Tag_ID::SDO_BOARDTASK_QUERY_RESP:
		{
			if(pageInfo)//已经可以翻页
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listNotice,&pageCount);//构造公告列表信息
			}
			else
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listNotice,&pageCount);//构造公告列表信息

				if(pageCount<=0)//如果页数不大于0
				{
					pageInfo = false;//清除公告列表信息
					nItem = 0;
					cmbPage.ResetContent();
					while(listNotice.DeleteColumn(0)){}
				}
				else//如果页数大于0
				{
					nItem = 0;//没有选择公告列表中的特定项
					cmbPage.ResetContent();//清除公告翻页复选框中的内容
					for(int i=1;i<=pageCount;i++)//添加所有的页数
					{
						CString str="";
						str.Format("%d",i);
						cmbPage.AddString(str);
					}
					cmbPage.SetCurSel(0);//初始页数为1
					if(pageCount == 1)//如果只有1页
					{
						pageInfo = false;//不能翻页
					}
					else//如果超过1页
					{
						pageInfo = true;//可以翻页
					}
				}				
			}
		}
		break;
		//如果接收到的是添加公告请求的返回信息//SDO_BOARDTASK_INSERT
	case CEnumCore::Message_Tag_ID::SDO_BOARDTASK_INSERT_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operSDO.ShowResult(result);//显示添加公告的结果
			NoticeInfo();//查询所有的公告信息

			CTime curTime = CTime::GetCurrentTime();//重置所有控件信息
			dtcStartDate.SetTime(&curTime);
			dtcStartTime.SetTime(&curTime);
			dtcEndDate.SetTime(&curTime);
			dtcEndTime.SetTime(&curTime);
			SetDlgItemText(IDC_EDITINTERVAL,"");
			SetDlgItemText(IDC_EDITCONTENT,"");
			GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);
			cmbStatus.SetCurSel(0);
			checkSendImme.SetCheck(0);
			SetDlgItemText(IDBTNNOTICE,theApp.operSDO.ReadValue("MSDO","NI_UI_AddNotice"));
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_BOARDMESSAGE_REQ_RESP:
		{
			listServer.EnableWindow(true);
			for(int i=0;i<listServer.GetItemCount();i++)
			{
				listServer.SetCheck(i,false);//取消选中所有的游戏服务器
			}

			CString serverName = "";
			for(int i=0;i<listServer.GetItemCount();i++)
			{
				for(int x=0;x<socketdata.getQueryNum();x++)
				{
					serverName = (LPSTR)&socketdata.getTLVByName(i+1,CEnumCore::TagName::ServerInfo_City).lpdata;//获取游戏服务器名称
					if(listServer.GetItemData(i)==serverName)
					{
						listServer.SetCheck(i);
					}
				}

			}


			CTime curTime = CTime::GetCurrentTime();//重置所有控件信息
			dtcStartDate.SetTime(&curTime);
			dtcStartTime.SetTime(&curTime);
			dtcEndDate.SetTime(&curTime);
			dtcEndTime.SetTime(&curTime);
			SetDlgItemText(IDC_EDITINTERVAL,"60");
			SetDlgItemText(IDC_EDITCONTENT,"");
			GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);
			cmbStatus.SetCurSel(0);

			SetDlgItemText(IDBTNNOTICE,theApp.operSDO.ReadValue("MSDO","NI_UI_EditNotice"));
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_BOARDTASK_UPDATE_RESP://
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operSDO.ShowResult(result);//显示添加公告的结果
			NoticeInfo();//查询所有的公告信息

			CTime curTime = CTime::GetCurrentTime();//重置所有控件信息
			dtcStartDate.SetTime(&curTime);
			dtcStartTime.SetTime(&curTime);
			dtcEndDate.SetTime(&curTime);
			dtcEndTime.SetTime(&curTime);
			SetDlgItemText(IDC_EDITINTERVAL,"60");
			SetDlgItemText(IDC_EDITCONTENT,"");
			GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);
			cmbStatus.SetCurSel(0);
			SetDlgItemText(IDBTNNOTICE,theApp.operSDO.ReadValue("MSDO","NI_UI_AddNotice"));
		}
		break;
	default:
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return FALSE;
}

//单击公告信息的列名进行排序
void CSDONoticeInfo::OnLvnColumnclickListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&listNotice,pNMHDR,pResult);
}

// 关闭对话框
void CSDONoticeInfo::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Close");//关闭窗体
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
