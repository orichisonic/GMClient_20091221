// JW2NoticeInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "M_JW2.h"
#include "JW2NoticeInfo.h"
#include ".\JW2NoticeInfo.h"


// CJW2NoticeInfo 对话框

IMPLEMENT_DYNAMIC(CJW2NoticeInfo, CDialog)
CJW2NoticeInfo::CJW2NoticeInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CJW2NoticeInfo::IDD, pParent)
{
}

CJW2NoticeInfo::~CJW2NoticeInfo()
{
}

void CJW2NoticeInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTSERVER, listResult);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTNOTICE, listNotice);
	DDX_Control(pDX, IDC_DTPSTARTDATE, dtcStartDate);
	DDX_Control(pDX, IDC_DTPENDDATE, dtcEndDate);
	DDX_Control(pDX, IDC_DTPSTARTTIME, dtcStartTime);
	DDX_Control(pDX, IDC_DTPENDTIME, dtcEndTime);
	DDX_Control(pDX, IDC_CHECKIMME, checkSendImme);
	DDX_Control(pDX, IDC_CMBSTATUS, cmbStatus);
	DDX_Control(pDX, IDC_EDITINTERVAL, txtInterval);
}


BEGIN_MESSAGE_MAP(CJW2NoticeInfo, CDialog)
	ON_BN_CLICKED(IDC_BTNNOTICEINFO, OnBnClickedBtnnoticeinfo)
	ON_CBN_SELCHANGE(IDC_CMBUIPAGE, OnCbnSelchangeCmbuipage)
	ON_BN_CLICKED(IDBTNNOTICE, OnBnClickedBtnnotice)
	ON_BN_CLICKED(IDBTNRESET, OnBnClickedBtnreset)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTNOTICE, OnNMDblclkListnotice)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECKIMME, OnBnClickedCheckimme)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECKSELECTALL, OnBnClickedCheckselectall)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTNOTICE, OnLvnColumnclickListnotice)
END_MESSAGE_MAP()

// 初始化对话框
BOOL CJW2NoticeInfo::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();

	dtcStartTime.SetFormat("HH:mm:ss");
	dtcEndTime.SetFormat("HH:mm:ss");
	
	nItem = -1;// 单击公告列表得到行号
	pageInfo = false;// 判断是否需要翻页
	addOrEdit = false;// 发送公告
	ServerIP = "";// 服务器IP
	NoticeID = 0;// 公告ID	
	AllServer = false;// 是否在所有大区发送公告


	cmbStatus.ResetContent();
	cmbStatus.AddString(theApp.operJW2.ReadValue("MJW2","NI_UI_UnSend"));//未发送
	cmbStatus.AddString(theApp.operJW2.ReadValue("MJW2","NI_UI_Sended"));//已发送
	cmbStatus.SetCurSel(0);

	GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//隐藏公告状态
	GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);

	listResult.SetExtendedStyle(listResult.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);//服务器列表中需要显示CheckBox
	listResult.InsertColumn(0,theApp.operJW2.ReadValue("MJW2","NI_UI_ServerList"),LVCFMT_CENTER,150,-1);

	CRect rs;
	GetClientRect(rs);; //获取对话框的大小信息

	CRect srcRect;
	CRect newRect;

	if( listResult.m_hWnd != NULL )   
	{
		listResult.GetWindowRect(srcRect);//获取listResult的大小信息
		listRWidth = srcRect.right - srcRect.left;//得到listResult的宽度信息

		newRect.top = rs.top + 45;		
		newRect.left = rs.left + 10;
		newRect.right = newRect.left + listRWidth;
		newRect.bottom = rs.bottom - 8;

		listResult.MoveWindow(newRect);//设置listResult的位置
	}  

	CWnd* pWnd = GetDlgItem(IDC_EDITCONTENT);  
	if( pWnd )   
	{
		pWnd->GetWindowRect(srcRect);//获取公告内容CEdit的大小信息
		contentLength = srcRect.bottom - srcRect.top;//获取公告内容CEdit的高度信息

		newRect.top = rs.top + 117;		
		newRect.left = newRect.right + 86;
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

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Create");//初始建立对话框
	theApp.operJW2.GetServerList();
	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

	return TRUE;
}

// 初始化显示字符
void CJW2NoticeInfo::InitUI()
{

	SetWindowText(theApp.operJW2.ReadValue("MJW2","NI_UI_NoticeInfo"));

	SetDlgItemText(IDC_CHECKSELECTALL,theApp.operJW2.ReadValue("MJW2","NI_UI_SelectAll"));

	SetDlgItemText(IDC_BTNNOTICEINFO,theApp.operJW2.ReadValue("MJW2","NI_UI_NoticeCheck"));
	SetDlgItemText(IDC_LBLHINT,theApp.operJW2.ReadValue("MJW2","NI_UI_NoticeHint"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operJW2.ReadValue("MJW2","BU_UI_LblPage"));

	SetDlgItemText(IDC_LBLSTARTTIME,theApp.operJW2.ReadValue("MJW2","NI_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operJW2.ReadValue("MJW2","NI_UI_EndTime"));
	SetDlgItemText(IDC_LBLINTERVAL,theApp.operJW2.ReadValue("MJW2","NI_UI_TimeInterval"));
	SetDlgItemText(IDC_LBLTIME,theApp.operJW2.ReadValue("MJW2","NI_UI_Minite"));	
	SetDlgItemText(IDC_LBLCONTENT,theApp.operJW2.ReadValue("MJW2","NI_UI_SendContent"));
	SetDlgItemText(IDC_CHECKIMME,theApp.operJW2.ReadValue("MJW2","NI_UI_SendImme"));
	SetDlgItemText(IDC_LBLSTATUS,theApp.operJW2.ReadValue("MJW2","NI_UI_NoticeStatus"));
	SetDlgItemText(IDBTNNOTICE,theApp.operJW2.ReadValue("MJW2","NI_UI_AddNotice"));
	SetDlgItemText(IDBTNRESET,theApp.operJW2.ReadValue("MJW2","Reset"));
}

//处理快捷键响应函数
BOOL CJW2NoticeInfo::PreTranslateMessage(MSG* pMsg)
{

    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listNotice.m_hWnd)
				{
					theApp.operJW2.CopyListInfo(&listNotice);				
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listNotice.m_hWnd)
				{
					for(int i=0; i<listNotice.GetItemCount(); i++)
					{
					    listNotice.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listNotice.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

// 自动改变大小
void CJW2NoticeInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rs;
	GetClientRect(rs);

	CRect newRect;

	if( listResult.m_hWnd != NULL )   
	{
		newRect.top = rs.top + 45;		
		newRect.left = rs.left + 10;
		newRect.right = newRect.left + listRWidth;
		newRect.bottom = rs.bottom - 10;

		listResult.MoveWindow(newRect);//设置listResult的位置
	}  

	CWnd* pWnd = GetDlgItem(IDC_EDITCONTENT);  
	if( pWnd )   
	{
		newRect.top = rs.top + 117;		
		newRect.left = newRect.right + 86;
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
HBRUSH CJW2NoticeInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 选择所有游戏服务器进行发送
void CJW2NoticeInfo::OnBnClickedCheckselectall()
{
	if(AllServer == false)
	{
		for(int i=0; i<listResult.GetItemCount(); i++)
		{
			listResult.SetCheck(i);//选中所有的游戏服务器
		}
		listResult.EnableWindow(false);//让游戏服务器列表变为Disable的状态
		AllServer = true;
	}
	else
	{
		for(int i=0; i<listResult.GetItemCount(); i++)
		{
			listResult.SetCheck(i,false);//取消选中所有的游戏服务器
		}
		listResult.EnableWindow(true);//让游戏服务器列表变为Enable的状态
		AllServer = false;
	}
}

// 查看公告信息
void CJW2NoticeInfo::OnBnClickedBtnnoticeinfo()
{
	NoticeInfo();
}

// 查看公告信息
void CJW2NoticeInfo::NoticeInfo()
{
	nItem = -1;
	pageInfo = false;//公告信息不能翻页
	cmbPage.ResetContent();//公告信息翻页复选框为空
	while(listNotice.DeleteColumn(0)){}//删除所有公告列表信息
	
	try
	{
		char strInt[10];
		int index = theApp.operJW2.ReadIntValue("MJW2","index");//查看第一页的记录
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//每页有50条记录
        
		CSocketData socketdata;
		socketdata.InitCreate(1,2);//共有两个参数，页数、每页的记录数

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录数

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_BOARDTASK_QUERY);//发送查询公告信息的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_NoticeInfo"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 翻页查看公告信息
void CJW2NoticeInfo::OnCbnSelchangeCmbuipage()
{
	try
	{
		if(pageInfo)
		{
			while(listNotice.DeleteColumn(0)){}//清除公告列表中的所有内容
			
			int index = cmbPage.GetCurSel() + 1;//翻页查看的页数
			int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//每页有50条记录

			CSocketData socketdata;
			socketdata.InitCreate(1,2);//共有两个参数，页数、每页的记录数
			char strInt[10];

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录数

			int midlength = socketdata.EnBody();
			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_BOARDTASK_QUERY);//发送查询公告信息的请求

			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求
			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_NoticeInfo"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}
}

// 双击公告信息进行编辑
void CJW2NoticeInfo::OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{
	CIni mIni;
	try
	{
		if(listNotice.GetItemCount() != 0)//如果公告列表中当前有记录
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
				NoticeID = atoi(theApp.operJW2.GetValueByColName(&listNotice, nItem, theApp.operJW2.ReadValue("MJW2","JW2_TaskID")));//获取公告ID

				CTime curTime = CTime::GetCurrentTime();//获取当前时间
			    dtcStartDate.SetTime(&curTime);//设置开始时间
			    dtcStartTime.SetTime(&curTime);//设置开始时间
			    dtcEndDate.SetTime(&curTime);//设置结束时间
			    dtcEndTime.SetTime(&curTime);//设置结束时间

				SetDlgItemText(IDC_EDITINTERVAL,theApp.operJW2.GetValueByColName(&listNotice, nItem, theApp.operJW2.ReadValue("MJW2","JW2_Interval")));//获取时间间隔并设置
				SetDlgItemText(IDC_EDITCONTENT,theApp.operJW2.GetValueByColName(&listNotice, nItem, theApp.operJW2.ReadValue("MJW2","JW2_BoardMessage")));//获取公告内容并设置

				ServerIP = theApp.operJW2.GetValueByColName(&listNotice, nItem, theApp.operJW2.ReadValue("MJW2","JW2_ServerIP"));//获取服务器IP

				SetDlgItemText(IDBTNNOTICE,theApp.operJW2.ReadValue("MJW2","NI_UI_EditNotice"));

				GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_SHOW);//显示公告状态
				GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_HIDE);//不显示立即发送公告的CheckBox

				GetDlgItem(IDC_LISTSERVER)->EnableWindow(false);//让服务器列表的状态变为Disable
			}
		}
		else
		{
			nItem = -1;
			GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//不显示公告状态
			GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);//让服务器列表的状态变为Enable		
			SetDlgItemText(IDBTNNOTICE,theApp.operJW2.ReadValue("MJW2","NI_UI_AddNotice"));
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// 发送或编辑公告
void CJW2NoticeInfo::OnBnClickedBtnnotice()
{
	try
	{
		UpdateData(true);

		CString NoticeOp = "";
		GetDlgItemText(IDBTNNOTICE, NoticeOp);

		if(NoticeOp == theApp.operJW2.ReadValue("MJW2","NI_UI_AddNotice"))//如果按钮为添加公告
		{
			AddNotice();//添加公告
		}
		else if(NoticeOp == theApp.operJW2.ReadValue("MJW2","NI_UI_EditNotice"))//如果按钮为编辑公告
		{
			EditNotice();//编辑公告
		}
	}
	catch(...)
	{
	}
}

// 是否发送公告
void CJW2NoticeInfo::OnBnClickedCheckimme()
{
	if(checkSendImme.GetCheck() == 1)//选择立即发送，让开始时间、结束时间、时间间隔的控件都变成Disable的状态
	{
		GetDlgItem(IDC_DTPSTARTDATE)->EnableWindow(false);
		GetDlgItem(IDC_DTPSTARTTIME)->EnableWindow(false);
		GetDlgItem(IDC_DTPENDDATE)->EnableWindow(false);
		GetDlgItem(IDC_DTPENDTIME)->EnableWindow(false);
		GetDlgItem(IDC_EDITINTERVAL)->EnableWindow(false);
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

// 发送公告
void CJW2NoticeInfo::AddNotice()
{
	try
	{		
		CIni mIni;

		UpdateData(true);

		int svrCheck = 0;
		for(int i=0;i<listResult.GetItemCount();i++)
		{
			if(listResult.GetCheck(i))//查看有没有选中当前的游戏服务器
			{
				svrCheck++;
			}
		}
		if(svrCheck == 0)//发送公告时，游戏服务器不能为空
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_ServerListNull"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
			return;
		}

		CString NoticeContent = "";
		GetDlgItemText(IDC_EDITCONTENT, NoticeContent);//获取公告内容

		if(NoticeContent == "")//公告内容不能为空
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_ContentNotNull"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
			return;
		}

		if(strlen(NoticeContent) >= 256)//公告内容不能超过256个字符
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_ContentTooLong"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
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

		CString strBeginTime = beginTime.Format("%Y/%m/%d %H:%M:%S");//设置开始时间
		CString strEndTime = toTime.Format("%Y/%m/%d %H:%M:%S");//设置结束时间

		int interval = GetDlgItemInt(IDC_EDITINTERVAL);//获取时间间隔

		if(checkSendImme.GetCheck() == 1)//如果是立即发送
		{
			interval = 0;//时间间隔为0
		}
		else//如果不是立即发送
		{
			if(toTime <= curTime)//结束时间不能小于当前时间
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_StartTime"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}

			if(toTime <= beginTime)//结束时间不能小于开始时间
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_TimeSpan"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}
			if(interval <= 0)//时间间隔必须大于0
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_Interval"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}
		}

		CString strMsg = theApp.operJW2.ReadValue("MJW2","NI_Hint_AddNotice"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //提示玩家是否确定要添加公告
		{
			return;
		}

		CSocketData socketdata;
		char strInt[10];
		socketdata.InitCreate(1,7);//共有七个参数：开始时间、结束时间、时间间隔、公告内容、大区IP、操作员ID、服务器IP

		socketdata.AddTFLV(CEnumCore::TagName::JW2_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//开始时间
		socketdata.AddTFLV(CEnumCore::TagName::JW2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//结束时间

		_itoa(interval,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_Interval,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//时间间隔
		socketdata.AddTFLV(CEnumCore::TagName::JW2_BoardMessage,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeContent),(unsigned char *)mIni.wcharToChar(NoticeContent));//公告内容

		CString GSServerIP = "255.255.255.255";
		socketdata.AddTFLV(CEnumCore::TagName::JW2_GSServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(GSServerIP),(unsigned char *)mIni.wcharToChar(GSServerIP));//大区IP

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		ServerIP = ReturnServerIP();

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_BOARDTASK_INSERT);//发送添加公告的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送操作请求
		socketdata.Destroy();
	}
	catch(...)
	{
	}	
}

//编辑公告
void CJW2NoticeInfo::EditNotice()
{

	try
	{		
		CIni mIni;

		UpdateData(true);

		CString strStatus = "";
		GetDlgItemText(IDC_CMBSTATUS, strStatus);//获取公告状态
		if(strStatus == "")//公告状态不能为空
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_StatusNotNull"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
			return;
		}

		CString NoticeContent = "";
		GetDlgItemText(IDC_EDITCONTENT, NoticeContent);//获取公告内容

		CTime curTime = CTime::GetCurrentTime();//获取当前时间

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

		CString strBeginTime = beginTime.Format("%Y/%m/%d %H:%M:%S");//获取开始时间
		CString strEndTime = toTime.Format("%Y/%m/%d %H:%M:%S");//获取结束时间

		int interval = GetDlgItemInt(IDC_EDITINTERVAL);//获取时间间隔

		if(cmbStatus.GetCurSel() == 1)//如果选择的公告状态是已发送，所有的参数都可以不做限制
		{
		}
		else//如果选择的是未发送，要限制一些参数
		{
			if(NoticeContent == "")//公告内容不能为空
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_ContentNotNull"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}

			if(strlen(NoticeContent) >= 256)//公告内容不能超过256个字符
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_ContentTooLong"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}

			if(toTime <= curTime)//结束时间不能小于当前时间
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_StartTime"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}

			if(toTime <= beginTime)//结束时间不能小于开始时间
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_TimeSpan"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}

			if(interval <= 0)//时间间隔要大于0
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_Interval"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}
		}

		CString strMsg = theApp.operJW2.ReadValue("MJW2","NI_Hint_EditNotice"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //提示是否编辑公告
		{
			return;
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,9);//共有9个参数：开始时间、结束时间、时间间隔、公告内容、大区IP、操作员ID、公告状态、公告ID、服务器IP
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//开始时间
		socketdata.AddTFLV(CEnumCore::TagName::JW2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//结束时间

		_itoa(interval,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_Interval,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//时间间隔
		socketdata.AddTFLV(CEnumCore::TagName::JW2_BoardMessage,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeContent),(unsigned char *)mIni.wcharToChar(NoticeContent));//公告内容

		CString GSServerIP = "255.255.255.255";
		socketdata.AddTFLV(CEnumCore::TagName::JW2_GSServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(GSServerIP),(unsigned char *)mIni.wcharToChar(GSServerIP));//大区IP

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		_itoa(cmbStatus.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_Status,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//公告状态

		_itoa(NoticeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_TaskID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//公告ID

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_BOARDTASK_UPDATE);//发送编辑公告的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送操作请求
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//返回要发送公告的游戏服务器列表
CString  CJW2NoticeInfo::ReturnServerIP()
{
	CString rServerIP = "";
	CString serverName = "";
	for(int i=0;i<listResult.GetItemCount();i++)
	{
		if(listResult.GetCheck(i))
		{
			ServerList.Lookup(i+1,serverName);//查找服务器IP
			rServerIP += serverName;
			rServerIP += "|";//将所有的服务器IP用","隔开
		}
	}
	return rServerIP;
}

// 重置信息
void CJW2NoticeInfo::OnBnClickedBtnreset()
{
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
		SetDlgItemText(IDBTNNOTICE,theApp.operJW2.ReadValue("MJW2","NI_UI_AddNotice"));
	}
	catch(...)
	{
	}
}

// 接收返回信息
LRESULT CJW2NoticeInfo::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);//让整个界面处于最顶端

	GetDlgItem(IDC_DTPSTARTDATE)->EnableWindow(true);
	GetDlgItem(IDC_DTPSTARTTIME)->EnableWindow(true);
	GetDlgItem(IDC_DTPENDDATE)->EnableWindow(true);
	GetDlgItem(IDC_DTPENDTIME)->EnableWindow(true);
	GetDlgItem(IDC_EDITINTERVAL)->EnableWindow(true);

	unsigned char* lpReceive=(unsigned char*)wParam;
	int bodyLength = (int)lParam;


	CIni mIni;

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Receive");//当前的状态为接收到返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	socketdata.DeBody(lpReceive,bodyLength);

	int pageCount = 0;

	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://如果接收到的是服务器列表返回信息
		{
			listResult.EnableWindow(true);

			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);//获取返回信息中的第一个模块
			if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)//如果第一个模块的TagName是MESSAGE，表示出现了错误信息，显示错误信息并返回
			{
				MessageBox((LPCSTR)&m_tflv.lpdata,theApp.operJW2.ReadValue("MJW2","Error"),0);
				socketdata.Destroy();
				return false;
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//获取所有的服务器IP
				ServerList.SetAt(i,ServerIP);//添加到CMap类的对象ServerList中
			}

			listResult.DeleteAllItems();//清除服务器列表中的所有内容
			CString serverName = "";
			int nRow = 0;
			for(int i=0;i<socketdata.getQueryNum();i++)
			{
				nRow = listResult.InsertItem(i,"");
				serverName = (LPSTR)&socketdata.getTLVByName(i+1,CEnumCore::TagName::ServerInfo_City).lpdata;//获取游戏服务器名称
				listResult.SetItemText(nRow,0,serverName);//将游戏服务器名称添加到服务器列表中
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_BOARDTASK_QUERY_RESP://如果接收到的是公告列表请求的返回信息
		{
			if(pageInfo)//已经可以翻页
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listNotice,&pageCount);//构造公告列表信息
			}
			else
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listNotice,&pageCount);//构造公告列表信息

				if(pageCount<=0)//如果页数不大于0
				{
					pageInfo = false;//清除公告列表信息
					nItem = -1;
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
	case CEnumCore::Message_Tag_ID::JW2_BOARDTASK_INSERT_RESP://如果接收到的是添加公告请求的返回信息
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//显示添加公告的结果
		//	NoticeInfo();//查询所有的公告信息

			CTime curTime = CTime::GetCurrentTime();//重置所有控件信息
			dtcStartDate.SetTime(&curTime);
			dtcStartTime.SetTime(&curTime);
			dtcEndDate.SetTime(&curTime);
			dtcEndTime.SetTime(&curTime);
			SetDlgItemText(IDC_EDITINTERVAL,"60");
			SetDlgItemText(IDC_EDITCONTENT,"");
			GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);
			cmbStatus.SetCurSel(0);
			checkSendImme.SetCheck(0);
			SetDlgItemText(IDBTNNOTICE,theApp.operJW2.ReadValue("MJW2","NI_UI_AddNotice"));
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_BOARDTASK_UPDATE_RESP://如果接收到的是编辑公告请求的返回信息
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//显示编辑公告的结果
			//NoticeInfo();//查询所有的公告信息

			CTime curTime = CTime::GetCurrentTime();//重置所有控件信息
			dtcStartDate.SetTime(&curTime);
			dtcStartTime.SetTime(&curTime);
			dtcEndDate.SetTime(&curTime);
			dtcEndTime.SetTime(&curTime);
			SetDlgItemText(IDC_EDITINTERVAL,"60");
			SetDlgItemText(IDC_EDITCONTENT,"");
			GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);
			cmbStatus.SetCurSel(0);
			checkSendImme.SetCheck(0);
			SetDlgItemText(IDBTNNOTICE,theApp.operJW2.ReadValue("MJW2","NI_UI_AddNotice"));
		}
		break;
	default:
		break;
	}

	socketdata.Destroy();
	return false;
}

//单击公告信息的列名进行排序
void CJW2NoticeInfo::OnLvnColumnclickListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{

	theApp.operJW2.SortListInfo(&listNotice,pNMHDR,pResult);
}

// 关闭对话框
void CJW2NoticeInfo::OnClose()
{

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Close");//关闭窗体
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
