// JW2ProductManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_JW2.h"
#include "JW2ProductManage.h"
#include ".\JW2ProductManage.h"


// CJW2ProductManage 对话框

IMPLEMENT_DYNAMIC(CJW2ProductManage, CDialog)
CJW2ProductManage::CJW2ProductManage(CWnd* pParent /*=NULL*/)
	: CDialog(CJW2ProductManage::IDD, pParent)
{
}

CJW2ProductManage::~CJW2ProductManage()
{
}

void CJW2ProductManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTSERVER, listResult);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTNOTICE, listNotice);
	DDX_Control(pDX, IDC_DTPSTARTDATE, dtcStartDate);
	DDX_Control(pDX, IDC_DTPENDDATE, dtcEndDate);
	DDX_Control(pDX, IDC_CMBGM, cmbRealName);
	DDX_Control(pDX, IDC_LIST3, listItem);
	DDX_Control(pDX, IDC_LIST2, listItemResult);
	DDX_Control(pDX, IDC_CHECKSELECTALL, m_ckServer);
}


BEGIN_MESSAGE_MAP(CJW2ProductManage, CDialog)
////	ON_BN_CLICKED(IDC_BTNNOTICEINFO, OnBnClickedBtnnoticeinfo)
////	ON_CBN_SELCHANGE(IDC_CMBUIPAGE, OnCbnSelchangeCmbuipage)
	ON_BN_CLICKED(IDBTNNOTICE, OnBnClickedBtnnotice)
	ON_BN_CLICKED(IDBTNRESET, OnBnClickedBtnreset)
/////	ON_NOTIFY(NM_DBLCLK, IDC_LISTNOTICE, OnNMDblclkListnotice)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
//	ON_BN_CLICKED(IDC_CHECKSELECTALL, OnBnClickedCheckselectall)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTNOTICE, OnLvnColumnclickListnotice)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, OnNMClickList3)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, OnNMDblclkList3)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, OnNMClickList2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnNMDblclkList2)
	ON_BN_CLICKED(IDC_CHECKSELECTALL, OnBnClickedCheckselectall)
	ON_BN_CLICKED(IDC_BTNNOTICEINFO, OnBnClickedBtnnoticeinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTNOTICE, OnNMDblclkListnotice)
	ON_CBN_SELCHANGE(IDC_CMBUIPAGE, OnCbnSelchangeCmbuipage)
	ON_BN_CLICKED(IDC_BTNVALIDATE, OnBnClickedBtnvalidate)
END_MESSAGE_MAP()

// 初始化对话框
BOOL CJW2ProductManage::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();

	
	nItem = -1;// 单击公告列表得到行号
	pageInfo = false;// 判断是否需要翻页
	addOrEdit = false;// 发送公告
	ServerIP = "";// 服务器IP
	ProductID = 0;// 权限ID	
	AllServer = false;// 是否在所有大区发送公告
	CountItemPrice=0;//道具总的金额数
	



	listResult.SetExtendedStyle(listResult.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);//服务器列表中需要显示CheckBox
	listResult.InsertColumn(0,theApp.operJW2.ReadValue("MJW2","NI_UI_ServerList"),LVCFMT_CENTER,150,-1);

	/*CRect rs;
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
		newRect.bottom = rs.bottom/2;

		listResult.MoveWindow(newRect);//设置listResult的位置
	}  
	CWnd* pWnd = GetDlgItem(IDC_EDITCONTENT);  
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
		newRect.left = rs.left + 10;
		newRect.right = rs.right - 8;
		newRect.bottom = rs.bottom - 8;

		listNotice.MoveWindow(newRect);//设置listNotice的位置
	} */

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Create");//初始建立对话框
	theApp.operJW2.GetServerList();
	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

	return TRUE;
}

// 初始化显示字符
void CJW2ProductManage::InitUI()
{

	SetWindowText(theApp.operJW2.ReadValue("MJW2","PM_UI_ProductManager"));

	SetDlgItemText(IDC_CHECKSELECTALL,theApp.operJW2.ReadValue("MJW2","NI_UI_SelectAll"));

	SetDlgItemText(IDC_BTNNOTICEINFO,theApp.operJW2.ReadValue("MJW2","PM_UI_QueryProductManager"));
	SetDlgItemText(IDC_LBLHINT,theApp.operJW2.ReadValue("MJW2","PM_UI_ProductManagerHint"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operJW2.ReadValue("MJW2","BU_UI_LblPage"));

	SetDlgItemText(IDC_LBLSTARTTIME,theApp.operJW2.ReadValue("MJW2","NI_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operJW2.ReadValue("MJW2","NI_UI_EndTime"));
	SetDlgItemText(IDC_GMACCOUNT,theApp.operJW2.ReadValue("MJW2","PM_UI_GMAccount"));
	SetDlgItemText(IDC_LBLITEMCHOICE,theApp.operJW2.ReadValue("MJW2","PM_UI_ItemChoice"));//道具选择
	SetDlgItemText(IDC_LBLITEMNAME,theApp.operJW2.ReadValue("MJW2","PM_UI_ItemName"));//道具名称
	SetDlgItemText(IDC_LBLITEMNUM,theApp.operJW2.ReadValue("MJW2","PM_UI_ItemNum"));//道具数量
	SetDlgItemText(IDC_BUTTON3,theApp.operJW2.ReadValue("MJW2","PM_UI_ItemQuery"));//查询


	//SetDlgItemText(IDC_LBLINTERVAL,theApp.operJW2.ReadValue("MJW2","NI_UI_TimeInterval"));
	//SetDlgItemText(IDC_LBLTIME,theApp.operJW2.ReadValue("MJW2","NI_UI_Minite"));	
	//SetDlgItemText(IDC_LBLCONTENT,theApp.operJW2.ReadValue("MJW2","NI_UI_SendContent"));
	//SetDlgItemText(IDC_CHECKIMME,theApp.operJW2.ReadValue("MJW2","NI_UI_SendImme"));
	//SetDlgItemText(IDC_LBLSTATUS,theApp.operJW2.ReadValue("MJW2","NI_UI_NoticeStatus"));
	SetDlgItemText(IDBTNNOTICE,theApp.operJW2.ReadValue("MJW2","PM_UI_DelProductManager"));//增加权限
	SetDlgItemText(IDBTNRESET,theApp.operJW2.ReadValue("MJW2","Reset"));
}

//处理快捷键响应函数
BOOL CJW2ProductManage::PreTranslateMessage(MSG* pMsg)
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
void CJW2ProductManage::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

/*	CRect rs;
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
		newRect.bottom = rs.bottom/2;

		listResult.MoveWindow(newRect);//设置listResult的位置
	}  
	CWnd* pWnd = = GetDlgItem(IDC_GRPPAGE);  
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
		newRect.left = rs.left + 10;
		newRect.right = rs.right - 8;
		newRect.bottom = rs.bottom - 8;

		listNotice.MoveWindow(newRect);//设置listNotice的位置
	} */
}

//设置背景颜色
HBRUSH CJW2ProductManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 选择所有游戏服务器进行发送
void CJW2ProductManage::OnBnClickedCheckselectall()
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

//maple add
/*
// 查看公告信息
void CJW2ProductManage::OnBnClickedBtnnoticeinfo()
{
	NoticeInfo();
}

// 查看公告信息
void CJW2ProductManage::NoticeInfo()
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
void CJW2ProductManage::OnCbnSelchangeCmbuipage()
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
void CJW2ProductManage::OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult)
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
*/

// 增加权限
void CJW2ProductManage::OnBnClickedBtnnotice()
{
	try
	{		
		CIni mIni;

		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");
		CSocketData socketdata;	
		socketdata.InitCreate(1,25);
		char strInt[10];
		ZeroMemory(strInt, 10);

		//GM帐号
		CString GMName;
		///int GMID=0;
		GetDlgItemText(IDC_CMBGM,GMName);//获取GM帐号
		////UserList.Lookup(cmbRealName.GetCurSel()+1,GMID);//从CMap类的对象ServerList中获取游戏服务器的IP
		///_itoa(GMID,strInt,10);
		////socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户序列号
		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(GMName),(unsigned char *)mIni.wcharToChar(GMName));//服务器IP


		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		ServerIP = ReturnServerIP();
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP

		char ItemData[2048];
		ZeroMemory(ItemData, 2048);//初始化要发送的道具信息
		char tmpItemData[2048];
		ZeroMemory(tmpItemData, 2048);//保存临时的道具信息

		int itemCount = listItemResult.GetItemCount();//要添加道具的行数
		int mid = 0;//要添加的道具商品号
		int itemNum = 0;//要添加的道具数量
		for(int i=0;i<itemCount;i++)
		{
			mid = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,0)));
			itemNum = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,2)));
			sprintf(tmpItemData, "%i*%i", mid, itemNum);
			if(i == 0)
			{
				sprintf(ItemData, "%s|", tmpItemData);
			}
			else
			{
				sprintf(ItemData, "%s%s|", ItemData, tmpItemData);
			}
		}		

		//添加的道具内容
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItem,CEnumCore::TagFormat::TLV_STRING,strlen(ItemData),(unsigned char *)ItemData);

		/////_itoa(itemCount,strInt,10);
		/////socketdata.AddTFLV(CEnumCore::TagName::PageCount,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//添加数量


		CTime StartDate;
		dtcStartDate.GetTime(StartDate);

		CTime EndDate;
		dtcEndDate.GetTime(EndDate);

		CTime beginTime = CTime::CTime(StartDate.GetYear(),StartDate.GetMonth(),StartDate.GetDay(),0,0,0);
		CTime toTime = CTime::CTime(EndDate.GetYear(),EndDate.GetMonth(),EndDate.GetDay(),0,0,0);

		CString strBeginTime = beginTime.Format("%Y/%m/%d %H:%M:%S");//设置开始时间
		CString strEndTime = toTime.Format("%Y/%m/%d %H:%M:%S");//设置结束时间


		socketdata.AddTFLV(CEnumCore::TagName::JW2_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//开始时间
		socketdata.AddTFLV(CEnumCore::TagName::JW2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//结束时间

		_itoa(CountItemPrice,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_TotalPrice,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//总额

		////_itoa(iPageSize,strInt,10);
		///socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数


		int midlength = socketdata.EnBody();
		if(theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ProductManage_Insert))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		/////MessageBox(theApp.operJW2.ReadValue("MJW2","IM_Error_ADDITEM"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}
}

/*

//maple add
// 是否发送公告
void CJW2ProductManage::OnBnClickedCheckimme()
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
void CJW2ProductManage::AddNotice()
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
void CJW2ProductManage::EditNotice()
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
*/

//返回要发送公告的游戏服务器列表
CString  CJW2ProductManage::ReturnServerIP()
{
	CString rServerIP = "";
	CString serverName = "";
	for(int i=0;i<listResult.GetItemCount();i++)
	{
		if(listResult.GetCheck(i))
		{
			ServerList.Lookup(i+1,serverName);//查找服务器IP
			rServerIP += serverName;
			rServerIP += "|";//将所有的服务器IP用"|"隔开
		}
	}
	return rServerIP;
}

// 重置信息
void CJW2ProductManage::OnBnClickedBtnreset()
{
	try
	{
		CTime curTime = CTime::GetCurrentTime();//获取当前时间
		dtcStartDate.SetTime(&curTime);
		//dtcStartTime.SetTime(&curTime);
		dtcEndDate.SetTime(&curTime);
		//dtcEndTime.SetTime(&curTime);

		//maple add
		cmbRealName.SetCurSel(0);
		SetDlgItemText(IDC_EDITITEM,"");//清空道具名
		SetDlgItemInt(IDC_EDITITEMNUM,1);//道具数量默认为1
		listItem.DeleteAllItems();
		listItemResult.DeleteAllItems();
		///////m_ckServer.SetCheck(0);




		//SetDlgItemText(IDC_EDITINTERVAL,"60");//设置时间间隔为60
		//SetDlgItemText(IDC_EDITCONTENT,"");//设置公告内容为空
		//GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//隐藏公告状态
		//GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);//显示立即发送
		//GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);
		//cmbStatus.SetCurSel(0);
		//checkSendImme.SetCheck(0);
		//SetDlgItemText(IDBTNNOTICE,theApp.operJW2.ReadValue("MJW2","NI_UI_AddNotice"));
	}
	catch(...)
	{
	}
}

// 接收返回信息
LRESULT CJW2ProductManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);//让整个界面处于最顶端

	//GetDlgItem(IDC_DTPSTARTDATE)->EnableWindow(true);
	//GetDlgItem(IDC_DTPSTARTTIME)->EnableWindow(true);

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

			QueryUserList();
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_QUERY_ALL_RESP:
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int UserID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::User_ID).lpdata);//得到用户ID
				UserList.SetAt(i,UserID);//将用户ID保存在CMap类的对象UserList中
			}

			theApp.operJW2.BuildComboxUser(&socketdata,&cmbRealName);//构造玩家姓名列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ITEM_SELECT_RESP:
		{
			theApp.operJW2.BuildDataTable(&socketdata,&listItem,&pageCount);//构造CListCtrl对象
		}
		break;
	//maple add
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Insert_Resp://增加权限
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Del_Resp://删除权限
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//显示结果

		}
		break;

	case CEnumCore::Message_Tag_ID::JW2_ProductManage_View_Resp://如果接收到的是查看权限请求的返回信息
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
					//while(listNotice.DeleteColumn(0)){}
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
/*	case CEnumCore::Message_Tag_ID::JW2_BOARDTASK_INSERT_RESP://如果接收到的是添加公告请求的返回信息
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//显示添加公告的结果
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
			GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);
			cmbStatus.SetCurSel(0);
			checkSendImme.SetCheck(0);
			SetDlgItemText(IDBTNNOTICE,theApp.operJW2.ReadValue("MJW2","NI_UI_AddNotice"));
		}
		break;
*/
	default:
		break;
	}

	socketdata.Destroy();
	return false;
}


//单击公告信息的列名进行排序
void CJW2ProductManage::OnLvnColumnclickListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{

	theApp.operJW2.SortListInfo(&listNotice,pNMHDR,pResult);
}

// 关闭对话框
void CJW2ProductManage::OnClose()
{

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Close");//关闭窗体
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
//获取所有的用户名称
void CJW2ProductManage::QueryUserList()
{
	try
	{		
		CIni mIni;

		int index = 0;
		int iPageSize = 0;

		cmbRealName.ResetContent();

		CSocketData socketdata;	
		socketdata.InitCreate(1,3);//共有3个参数，页数、每页的记录条数
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID

		//_itoa(index,strInt,10);
		//socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		//_itoa(iPageSize,strInt,10);
		//socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_QUERY_ALL))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送操作请求
		}

		socketdata.Destroy();
	}
	catch(...)
	{
		//MessageBox(theApp.operJW2.ReadValue("MGM","IM_Error_SearchItemType"),theApp.operJW2.ReadValue("MGM","Error"),0);
	}	
}
//道具模糊查询
void CJW2ProductManage::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{		
		CIni mIni;

		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		while(listItem.DeleteColumn(0)){};

		UpdateData(true);			

		CString tmpName = "";//用于模糊查询的道具名称
		GetDlgItemText(IDC_EDITITEM,tmpName);//获取用于模糊查询的道具名称
		if(tmpName == "")//用于模糊查询的道具名称不能为空
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","IM_WARN_BlurItemNameNull"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

	//	socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
	//	socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
	//	socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
	//	socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

		//用于模糊查询的道具名称
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItemName,CEnumCore::TagFormat::TLV_STRING,strlen(tmpName),(unsigned char *)mIni.wcharToChar(tmpName));

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数


		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ITEM_SELECT);//道具模糊查询

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询^请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_TreasureBox"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}
}

void CJW2ProductManage::OnBnClickedButton1()/////右移，把道具添加到添加列表
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	try
	{
/*		CIni mIni;

		if((listItem.GetItemCount() == 0)||(addItem < 0))//如果要添加的道具列表为空则返回
		{
			return;
		}

		CString tmpItemID = listItem.GetItemText(addItem, 0);
		int ItemID = atoi(mIni.wcharToChar(tmpItemID));//获取要添加的道具ID
		CString ItemName = listItem.GetItemText(addItem, 1);//获取要添加的道具名称
		CString ItemLimit= listItem.GetItemText(addItem, 2);

		//maple add
		CString ItemPrice=listItem.GetItemText(addItem,3);//道具单价
		int iItemPrice=atoi(mIni.wcharToChar(ItemPrice));
		CString ItemRemain= listItem.GetItemText(addItem, 4);

		int itemNum = GetDlgItemInt(IDC_EDITITEMNUM);
		if(itemNum == 0)
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","IM_Warn_ItemNumNull"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		int nRow = 0;
		char strInt[10];
		ZeroMemory(strInt,10);
		if(listItemResult.GetItemCount() == 0)
		{
			DWORD dwStyle = listItemResult.GetExtendedStyle();
			dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;//选中某行使整行高亮（只适用与report风格的listctrl）
			listItemResult.SetExtendedStyle(dwStyle); //设置扩展风格

			listItemResult.InsertColumn(0,"道具ID",LVCFMT_CENTER,60,-1);
			listItemResult.InsertColumn(1,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMNAME"),LVCFMT_CENTER,80,-1);
			listItemResult.InsertColumn(2,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMNUM"),LVCFMT_CENTER,80,-1);

			//maple add
			listItemResult.InsertColumn(3,theApp.operJW2.ReadValue("MJW2","IM_UI_ItemPrice"),LVCFMT_CENTER,80,-1);

			listItemResult.InsertColumn(4,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMEXPIREDATE"),LVCFMT_CENTER,80,-1);
			listItemResult.InsertColumn(5,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMREMAINCOUNT"),LVCFMT_CENTER,80,-1);

			_itoa(ItemID,strInt,10);
			int nRow=listItemResult.InsertItem(0,strInt);
			listItemResult.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItemResult.SetItemText(nRow,2,strInt);

			//maple add
			listItemResult.SetItemText(nRow,3,ItemPrice);//道具单价

			listItemResult.SetItemText(nRow,4,ItemLimit);
			listItemResult.SetItemText(nRow,5,ItemRemain);

			CountItemPrice=iItemPrice*itemNum;
			SetDlgItemInt(IDC_ETCOUNTPRICE,CountItemPrice);
		}
		else
		{

			CString str;
			bool EditOrAppend=false;
			for(int jj=0;jj<listItemResult.GetItemCount();jj++)
			{
				str=listItemResult.GetItemText(jj,0);
				if(str==selectItemID)
				{
					CString PreNum=listItemResult.GetItemText(jj,2);
					int iPreNum=atoi(mIni.wcharToChar(PreNum));
					int iNewNum=iPreNum+itemNum;
					_itoa(iNewNum,strInt,10);
					listItemResult.SetItemText(nRow,2,strInt);

					CountItemPrice=CountItemPrice+iItemPrice*itemNum;
					SetDlgItemInt(IDC_ETCOUNTPRICE,CountItemPrice);	

					EditOrAppend=true;
				}

			}

			if(EditOrAppend==false)
			{
				_itoa(ItemID,strInt,10);
				int nRow=listItemResult.InsertItem(0,strInt);

				listItemResult.SetItemText(nRow,1,ItemName);
				_itoa(itemNum,strInt,10);
				listItemResult.SetItemText(nRow,2,strInt);

				//maple add
				listItemResult.SetItemText(nRow,3,ItemPrice);//道具单价

				listItemResult.SetItemText(nRow,4,ItemLimit);
				listItemResult.SetItemText(nRow,5,ItemRemain);

			}
			
			//maple add
			CountItemPrice=CountItemPrice+iItemPrice*itemNum;
			SetDlgItemInt(IDC_ETCOUNTPRICE,CountItemPrice);	

		}
*/
		//int ii=0;


		POSITION pos = listItem.GetFirstSelectedItemPosition();
		int nNext=0;
		while(pos)
		{
			nNext=listItem.GetNextSelectedItem(pos);

			selectItemID=listItem.GetItemText(nNext,0);

			MulInsertListCtrl(nNext);

			//ii++;
		}
//		for(int n=0;n<ii;n++)
//		{
//			MulInsertListCtrl(nNext[n]);
//		}

	}
	catch(...)
	{
	}

}

void CJW2ProductManage::MulInsertListCtrl(int nSel)
{
//////	CString selItemID=selectItemID[nSel];

	CIni mIni;
	CString tmpItemID = listItem.GetItemText(nSel, 0);
	int ItemID = atoi(mIni.wcharToChar(tmpItemID));//获取要添加的道具ID
	CString ItemName = listItem.GetItemText(nSel, 1);//获取要添加的道具名称
	CString ItemLimit= listItem.GetItemText(nSel, 2);

	//maple add
	CString ItemPrice=listItem.GetItemText(nSel,3);//道具单价
	int iItemPrice=atoi(mIni.wcharToChar(ItemPrice));
	CString ItemRemain= listItem.GetItemText(nSel, 4);

	int itemNum = GetDlgItemInt(IDC_EDITITEMNUM);
	if(itemNum == 0)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","IM_Warn_ItemNumNull"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
		return;
	}
	int nRow = 0;
	char strInt[10];
	ZeroMemory(strInt,10);
	if(listItemResult.GetItemCount() == 0)
	{
		DWORD dwStyle = listItemResult.GetExtendedStyle();
		dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;//选中某行使整行高亮（只适用与report风格的listctrl）
		listItemResult.SetExtendedStyle(dwStyle); //设置扩展风格

		listItemResult.InsertColumn(0,"道具ID",LVCFMT_CENTER,60,-1);
		listItemResult.InsertColumn(1,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMNAME"),LVCFMT_CENTER,80,-1);
		listItemResult.InsertColumn(2,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMNUM"),LVCFMT_CENTER,80,-1);

		//maple add
		listItemResult.InsertColumn(3,theApp.operJW2.ReadValue("MJW2","IM_UI_ItemPrice"),LVCFMT_CENTER,80,-1);

		listItemResult.InsertColumn(4,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMEXPIREDATE"),LVCFMT_CENTER,80,-1);
		listItemResult.InsertColumn(5,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMREMAINCOUNT"),LVCFMT_CENTER,80,-1);

		_itoa(ItemID,strInt,10);
		int nRow=listItemResult.InsertItem(0,strInt);
		listItemResult.SetItemText(nRow,1,ItemName);
		_itoa(itemNum,strInt,10);
		listItemResult.SetItemText(nRow,2,strInt);

		//maple add
		listItemResult.SetItemText(nRow,3,ItemPrice);//道具单价

		listItemResult.SetItemText(nRow,4,ItemLimit);
		listItemResult.SetItemText(nRow,5,ItemRemain);

		CountItemPrice=iItemPrice*itemNum;
		SetDlgItemInt(IDC_ETCOUNTPRICE,CountItemPrice);
	}
	else
	{

		CString str;
		bool EditOrAppend=false;
		for(int jj=0;jj<listItemResult.GetItemCount();jj++)
		{
			str=listItemResult.GetItemText(jj,0);
			if(str==selectItemID)
			//if(str==selItemID)
			{
				CString PreNum=listItemResult.GetItemText(jj,2);
				int iPreNum=atoi(mIni.wcharToChar(PreNum));
				int iNewNum=iPreNum+itemNum;
				_itoa(iNewNum,strInt,10);
				listItemResult.SetItemText(jj,2,strInt);

				CountItemPrice=CountItemPrice+iItemPrice*itemNum;
				SetDlgItemInt(IDC_ETCOUNTPRICE,CountItemPrice);	

				EditOrAppend=true;
			}

		}

		if(EditOrAppend==false)
		{
			_itoa(ItemID,strInt,10);
			int nRow=listItemResult.InsertItem(0,strInt);

			listItemResult.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItemResult.SetItemText(nRow,2,strInt);

			//maple add
			listItemResult.SetItemText(nRow,3,ItemPrice);//道具单价

			listItemResult.SetItemText(nRow,4,ItemLimit);
			listItemResult.SetItemText(nRow,5,ItemRemain);

		}

		//maple add
		CountItemPrice=CountItemPrice+iItemPrice*itemNum;
		SetDlgItemInt(IDC_ETCOUNTPRICE,CountItemPrice);	
	}

}


void CJW2ProductManage::OnBnClickedButton2()///右移////删除
{
	//maple add
	CString DelItemPrice;
	CString DelItemNum;
	int iDelItemPrice=0;
	int iDelItemNum=0;

	int i,nSelCount=listItemResult.GetSelectedCount();
	POSITION pos = listItem.GetFirstSelectedItemPosition();
	int nDel=0;

	//if(listItemResult.GetItemCount() > 0)
	if(nSelCount>0)
	{
		for(i=0;i<nSelCount;i++)
		{
			nDel=listItemResult.GetNextItem(-1,LVNI_SELECTED);

			listItemResult.DeleteItem(nDel);
		}
		
	}
/*	while(pos)
	{
		nDel=listItem.GetNextSelectedItem(pos);

			
		DelItemPrice=listItemResult.GetItemText(nDel,3);//道具单价
		DelItemNum=listItemResult.GetItemText(nDel,2);//道具数量
		iDelItemPrice=atoi(DelItemPrice.GetBuffer(DelItemPrice.GetLength()));
		iDelItemNum=atoi(DelItemNum.GetBuffer(DelItemNum.GetLength()));
		CountItemPrice=CountItemPrice-iDelItemPrice*iDelItemNum;


		if((listItemResult.GetItemCount() != 0) && (nDel >= 0))
		{
			listItemResult.DeleteItem(nDel);
		}

	}
*/
	SetDlgItemInt(IDC_ETCOUNTPRICE,CountItemPrice);
	if(listItemResult.GetItemCount() == 0)
	{
		while(listItemResult.DeleteColumn(0)){};
	}


}

void CJW2ProductManage::OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(listItem.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

//////		addItem = listItem.SubItemHitTest(&lvinfo);//保存在可以添加的道具列表中选中的行号
////		selectItemID=listItem.GetItemText(addItem,0);//获得添加道具的ID
		
/*		POSITION pos = listItem.GetFirstSelectedItemPosition();
		/////int i=0;
		while(pos)
		{
			nNext[ii]=listItem.GetNextSelectedItem(pos);
			selectItemID[ii]=listItem.GetItemText(nNext[ii],0);
			ii++;
		}
*/
	}
	else
	{
		addItem = -1;
	}
	*pResult = 0;
}

void CJW2ProductManage::OnNMDblclkList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listItem.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		addItem = listItem.SubItemHitTest(&lvinfo);//保存在可以添加的道具列表中选中的行号

		if(addItem >= 0)
		{
			OnBnClickedButton1();
		}
	}
	else
	{
		addItem = -1;
	}
	*pResult = 0;
}

void CJW2ProductManage::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(listItemResult.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItemResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		delItem = listItemResult.SubItemHitTest(&lvinfo);//保存在可以添加的道具列表中选中的行号
	}
	else
	{
		delItem = -1;
	}
	*pResult = 0;
}

void CJW2ProductManage::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(listItemResult.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItemResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		delItem = listItemResult.SubItemHitTest(&lvinfo);//保存在可以添加的道具列表中选中的行号

		if(delItem >= 0)
		{
			OnBnClickedButton2();
		}
	}
	else
	{
		delItem = -1;
	}
	*pResult = 0;
}


//查看权限
void CJW2ProductManage::OnBnClickedBtnnoticeinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CIni mIni;
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

		///ServerIP = ReturnServerIP();
		///socketdata.AddTFLV(CEnumCore::TagName::userIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录数

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ProductManage_View);//发送查询权限的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		///MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_NoticeInfo"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

//双击删除权限
void CJW2ProductManage::OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
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
				ProductID = atoi(theApp.operJW2.GetValueByColName(&listNotice, nItem, theApp.operJW2.ReadValue("MJW2","JW2_TaskID")));//获取权限ID
				
				DelProductManager();
				
			}
		}
		else
		{
			nItem = -1;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}
//删除权限
void CJW2ProductManage::DelProductManager()
{
	try
	{

		CIni mIni;

		CString strMsg = theApp.operJW2.ReadValue("MJW2","NI_Hint_DelProductManager"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //提示是否删除权限
		{
			return;
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,9);//共有9个参数：
		char strInt[10];

		
		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		
		_itoa(ProductID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_TaskID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//公告ID

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ProductManage_Del);//发送删除权限的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送操作请求
		socketdata.Destroy();
	}
	catch(...)
	{

	}
}




//翻页查询权限
void CJW2ProductManage::OnCbnSelchangeCmbuipage()
{
	// TODO: 在此添加控件通知处理程序代码
	CIni mIni;
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

			ServerIP = ReturnServerIP();
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录数

			int midlength = socketdata.EnBody();
			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ProductManage_View);//发送查询权限的请求

			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求
			socketdata.Destroy();
		}
	}
	catch(...)
	{
		////MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_NoticeInfo"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}
}

//验证权限
void CJW2ProductManage::OnBnClickedBtnvalidate()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{		
		CIni mIni;

		
		CSocketData socketdata;	
		socketdata.InitCreate(1,25);
		char strInt[10];
		ZeroMemory(strInt, 10);

		//GM帐号
		CString GMName;
		int GMID=0;
		GetDlgItemText(IDC_CMBGM,GMName);//获取GM帐号
		UserList.Lookup(cmbRealName.GetCurSel()+1,GMID);//从CMap类的对象ServerList中获取游戏服务器的IP
		_itoa(GMID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户序列号
		//////////////socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(GMName),(unsigned char *)mIni.wcharToChar(GMName));//服务器IP


		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		ServerIP = ReturnServerIP();
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP

		char ItemData[2048];
		ZeroMemory(ItemData, 2048);//初始化要发送的道具信息
		char tmpItemData[2048];
		ZeroMemory(tmpItemData, 2048);//保存临时的道具信息

		int itemCount = listItemResult.GetItemCount();//要添加道具的行数
		int mid = 0;//要添加的道具商品号
		int itemNum = 0;//要添加的道具数量
		for(int i=0;i<itemCount;i++)
		{
			mid = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,0)));
			itemNum = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,2)));
			sprintf(tmpItemData, "%i*%i", mid, itemNum);
			if(i == 0)
			{
				sprintf(ItemData, "%s|", tmpItemData);
			}
			else
			{
				sprintf(ItemData, "%s%s|", ItemData, tmpItemData);
			}
		}		

		//添加的道具内容
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItem,CEnumCore::TagFormat::TLV_STRING,strlen(ItemData),(unsigned char *)ItemData);

		/////_itoa(itemCount,strInt,10);
		/////socketdata.AddTFLV(CEnumCore::TagName::PageCount,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//添加数量


		CTime StartDate;
		dtcStartDate.GetTime(StartDate);

		CTime EndDate;
		dtcEndDate.GetTime(EndDate);

		CTime beginTime = CTime::CTime(StartDate.GetYear(),StartDate.GetMonth(),StartDate.GetDay(),0,0,0);
		CTime toTime = CTime::CTime(EndDate.GetYear(),EndDate.GetMonth(),EndDate.GetDay(),0,0,0);

		CString strBeginTime = beginTime.Format("%Y/%m/%d %H:%M:%S");//设置开始时间
		CString strEndTime = toTime.Format("%Y/%m/%d %H:%M:%S");//设置结束时间


		socketdata.AddTFLV(CEnumCore::TagName::JW2_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//开始时间
		socketdata.AddTFLV(CEnumCore::TagName::JW2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//结束时间

		///_itoa(CountItemPrice,strInt,10);
		////socketdata.AddTFLV(CEnumCore::TagName::JW2_TotalPrice,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//总额

		
		int midlength = socketdata.EnBody();
		if(theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ProductManage_Validate))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		/////MessageBox(theApp.operJW2.ReadValue("MJW2","IM_Error_ADDITEM"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}
}
