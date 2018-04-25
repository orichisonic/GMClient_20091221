// Notice.cpp : 实现文件
//

#include "stdafx.h"
#include "M_WA.h"
#include "Notice.h"
#include ".\notice.h"


// CNotice 对话框

IMPLEMENT_DYNAMIC(CNotice, CDialog)
CNotice::CNotice(CWnd* pParent /*=NULL*/)
: CDialog(CNotice::IDD, pParent)
{
}

CNotice::~CNotice()
{
}
void CNotice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTSERVER, listResult);
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


BEGIN_MESSAGE_MAP(CNotice, CDialog)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECKSELECTALL, OnBnClickedCheckselectall)
	ON_BN_CLICKED(IDC_CHECKIMME, OnBnClickedCheckimme)
	ON_BN_CLICKED(IDBTNNOTICE, OnBnClickedBtnnotice)
	ON_BN_CLICKED(IDBTNRESET, OnBnClickedBtnreset)
	ON_BN_CLICKED(IDC_BTNNOTICEINFO, OnBnClickedBtnnoticeinfo)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTNOTICE, OnNMDblclkListnotice)
	ON_NOTIFY(NM_CLICK, IDC_LISTNOTICE, OnNMDblclkListnotice)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTNOTICE, OnLvnColumnclickListnotice)
	ON_BN_CLICKED(IDC_BTDELETE, OnBtdelete)

END_MESSAGE_MAP()
//删除公告操作
void CNotice::OnBtdelete()
{
	try
	{
		CString NoticeIDString;
		NoticeIDString.Format("%d",NoticeID);
		if(!ishaveselect)
		{
			MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_DelNotice"));
			return;
		}
		CString strMsg;//="是否确定要删除所选择公告";
		char* message=new char[100];
		sprintf(message,"%s%s%s",theApp.operWA.ReadValue("MWA","NI_Hint_DelNoticeID"),NoticeIDString,theApp.operWA.ReadValue("MWA","NI_Hint_DelNotice"));
		strMsg.Format("%s",message);
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //提示是否删除公告
		{
			return;
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,3);//共有2个参数：操作员ID、公告ID
		char strInt[10];
		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID
		_itoa(NoticeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::WA_TaskID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//公告ID
		int midlength = socketdata.EnBody();
		if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BoardTasker_Del))//发送编辑公告的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}
// 初始化对话框
BOOL CNotice::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();
	ishaveselect=false;
	dtcStartTime.SetFormat("HH:mm:ss");
	dtcEndTime.SetFormat("HH:mm:ss");

	nItem = 0;// 单击公告列表得到行号
	pageInfo = false;// 判断是否需要翻页
	addOrEdit = false;// 发送公告
	ServerIP = "";// 服务器IP
	NoticeID = 0;// 公告ID	
	AllServer = false;// 是否在所有大区发送公告
	cmbStatus.ResetContent();
	cmbStatus.AddString(theApp.operWA.ReadValue("MWA","NI_UI_UnSend"));//未发送
	cmbStatus.AddString(theApp.operWA.ReadValue("MWA","NI_UI_Sended"));//已发送
	cmbStatus.SetCurSel(0);
	GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//隐藏公告状态
	GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
	listResult.SetExtendedStyle(listResult.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);//服务器列表中需要显示CheckBox
	listResult.InsertColumn(0,theApp.operWA.ReadValue("MWA","NI_UI_ServerList"),LVCFMT_CENTER,150,-1);
	SetProp(listNotice.GetSafeHwnd(),"排序列号",(HANDLE)0);
	SetProp(listNotice.GetSafeHwnd(),"排序顺序",(HANDLE)1);
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
	dlgStatus = theApp.operWA.ReadIntValue("MWA","Create");//初始建立对话框
	if(theApp.operWA.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
	}

	return TRUE;
}

// 初始化显示字符
void CNotice::InitUI()
{
	SetWindowText(theApp.operWA.ReadValue("MWA","NI_UI_NoticeInfo"));
	SetDlgItemText(IDC_CHECKSELECTALL,theApp.operWA.ReadValue("MWA","NI_UI_SelectAll"));
	SetDlgItemText(IDC_BTNNOTICEINFO,theApp.operWA.ReadValue("MWA","NI_UI_NoticeCheck"));
	SetDlgItemText(IDC_LBLHINT,theApp.operWA.ReadValue("MWA","NI_UI_NoticeHint"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operWA.ReadValue("MWA","BU_UI_LblPage"));
	SetDlgItemText(IDC_LBLSTARTTIME,theApp.operWA.ReadValue("MWA","NI_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operWA.ReadValue("MWA","NI_UI_EndTime"));
	SetDlgItemText(IDC_LBLINTERVAL,theApp.operWA.ReadValue("MWA","NI_UI_TimeInterval"));
	SetDlgItemText(IDC_LBLTIME,theApp.operWA.ReadValue("MWA","NI_UI_Minite"));	
	SetDlgItemText(IDC_LBLCONTENT,theApp.operWA.ReadValue("MWA","NI_UI_SendContent"));
	SetDlgItemText(IDC_CHECKIMME,theApp.operWA.ReadValue("MWA","NI_UI_SendImme"));
	SetDlgItemText(IDC_LBLSTATUS,theApp.operWA.ReadValue("MWA","NI_UI_NoticeStatus"));
	SetDlgItemText(IDBTNNOTICE,theApp.operWA.ReadValue("MWA","NI_UI_AddNotice"));
	SetDlgItemText(IDBTNRESET,theApp.operWA.ReadValue("MWA","Reset"));
	SetDlgItemText(IDC_BTDELETE,theApp.operWA.ReadValue("MWA","NI_UI_DelNotice"));
}

//处理快捷键响应函数 处理A C键的反应
BOOL CNotice::PreTranslateMessage(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listNotice.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listNotice);				
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
void CNotice::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CNotice::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);
	return CreateSolidBrush(backColor);
}

// 选择所有游戏服务器进行发送
void CNotice::OnBnClickedCheckselectall()
{
	if(AllServer == false)
	{
		for(int i=0; i<listResult.GetItemCount(); i++)
		{
			listResult.SetCheck(i);//选中所有的游戏服务器
		}
		listResult.EnableWindow(true);//让游戏服务器列表变为Disable的状态
		AllServer = true;
	}
	else
	{
		for(int i=0; i<listResult.GetItemCount(); i++)
		{
			listResult.SetCheck(i,false);//取消选中所有的游戏服务器
		}
		//listResult.EnableWindow(true);//让游戏服务器列表变为Enable的状态
		AllServer = false;
	}
}

// 查看公告信息
void CNotice::OnBnClickedBtnnoticeinfo()
{
	NoticeInfo();
}

// 查看公告信息
void CNotice::NoticeInfo()
{
	nItem = 0;
	pageInfo = false;//公告信息不能翻页
	cmbPage.ResetContent();//公告信息翻页复选框为空
	while(listNotice.DeleteColumn(0)){}//删除所有公告列表信息
	try
	{
		char strInt[10];
		int index = theApp.operWA.ReadIntValue("MWA","index");//查看第一页的记录
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//每页有50条记录
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有两个参数，页数、每页的记录数
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录数
		int midlength = socketdata.EnBody();
		if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BoardTasker_Query))//发送查询公告信息的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","NI_Error_NoticeInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// 翻页查看公告信息
void CNotice::OnCbnSelchangeCmbpage()
{
	try
	{
		if(pageInfo)
		{
			while(listNotice.DeleteColumn(0)){}//清除公告列表中的所有内容
			int index = cmbPage.GetCurSel() + 1;//翻页查看的页数
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//每页有50条记录
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有两个参数，页数、每页的记录数
			char strInt[10];
			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录数
			int midlength = socketdata.EnBody();
			if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BoardTasker_Query))//发送查询公告信息的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","NI_Error_NoticeInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
	}
}

// 双击公告信息进行编辑
void CNotice::OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{
	CIni mIni;
	try
	{
		ishaveselect=true;
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
				NoticeID = atoi(theApp.operWA.GetValueByColName(&listNotice, nItem, theApp.operWA.ReadValue("MWA","WA_TaskID")));//获取公告ID
				CString startTime = theApp.operWA.GetValueByColName(&listNotice, nItem, theApp.operWA.ReadValue("MWA","WA_BeginTime"));//获取开始时间
				CString endTime = theApp.operWA.GetValueByColName(&listNotice, nItem, theApp.operWA.ReadValue("MWA","WA_EndTime"));//获取结束时间
				int nYear, nMonth, nDate, nHour, nMin, nSec;  
				sscanf(startTime, "%d-%d-%d  %d:%d:%d", &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);  
				CTime sTime(nYear, nMonth, nDate, nHour, nMin, nSec); //将开始时间变为CTime类型
				dtcStartDate.SetTime(&sTime);
				dtcStartTime.SetTime(&sTime);
				sscanf(endTime, "%d-%d-%d  %d:%d:%d", &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);  				
				CTime eTime(nYear, nMonth, nDate, nHour, nMin, nSec); //将结束时间变为CTime类型
				dtcEndDate.SetTime(&eTime);//设置开始时间
				dtcEndTime.SetTime(&eTime);//设置结束时间
				SetDlgItemText(IDC_EDITINTERVAL,theApp.operWA.GetValueByColName(&listNotice, nItem, theApp.operWA.ReadValue("MWA","WA_Interval")));//获取时间间隔并设置
				SetDlgItemText(IDC_EDITCONTENT,theApp.operWA.GetValueByColName(&listNotice, nItem, theApp.operWA.ReadValue("MWA","WA_BoardMessage")));//获取公告内容并设置
				ServerIP = theApp.operWA.GetValueByColName(&listNotice, nItem, theApp.operWA.ReadValue("MWA","WA_ServerName"));//获取服务器IP
				SetDlgItemText(IDBTNNOTICE,theApp.operWA.ReadValue("MWA","NI_UI_EditNotice"));
				//GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_SHOW);//显示公告状态
				//GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_HIDE);//不显示立即发送公告的CheckBox
				GetDlgItem(IDC_LISTSERVER)->EnableWindow(false);//让服务器列表的状态变为Disable
				GetDlgItem(IDC_CHECKSELECTALL)->EnableWindow(false);

			}
		}
		else
		{
			nItem = 0;
			GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//不显示公告状态
			GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);//让服务器列表的状态变为Enable	

			SetDlgItemText(IDBTNNOTICE,theApp.operWA.ReadValue("MWA","NI_UI_AddNotice"));
		}
		///////////////把已经选择的ip列表显示出来
		for(int i=0;i<listResult.GetItemCount();i++)
		{
			//if(listResult.GetItem())
			listResult.SetCheck(i,false);
		}
		LVFINDINFO info;
		int x;
		int lx;
		CString temprleft;
		CString now;
		temprleft=ServerIP;

		while((x= temprleft.Find('|',0))>=0)
		{	

			now=temprleft.Left(x);
			temprleft=temprleft.Right(temprleft.GetLength()-x-1);
			int nIndex;
			info.flags = LVFI_PARTIAL|LVFI_STRING;
			info.psz =now;
			if ((nIndex=listResult.FindItem(&info)) != -1)
			{
				//listResult.DeleteItem(nIndex);
				listResult.SetCheck(nIndex,true);
				//MessageBox(now);
			}
		}
		if((lx= temprleft.Find('|',0))<0)
		{

			int nIndex;
			info.flags = LVFI_PARTIAL|LVFI_STRING;
			info.psz =temprleft;
			if ((nIndex=listResult.FindItem(&info)) != -1)
			{
				//listResult.DeleteItem(nIndex);
				listResult.SetCheck(nIndex,true);
			}
			// Delete all of the items that begin with the string lpszmyString.



		}
		if((x= ServerIP.Find('|',0))<0)
		{
			int nIndex;
			info.flags = LVFI_PARTIAL|LVFI_STRING;
			info.psz =ServerIP;
			if ((nIndex=listResult.FindItem(&info)) != -1)
			{
				//listResult.DeleteItem(nIndex);
				listResult.SetCheck(nIndex,true);
			}
			// Delete all of the items that begin with the string lpszmyString.



		}

		//// Delete all of the items that begin with the string lpszmyString.


		//for(int i=0;i<listResult.GetItemCount();i++)
		//{
		//	//if(listResult.GetItem())
		//}
		//int nCount= listResult.GetItemCount();  
		//if(nCount>=0)  
		//{  
		//	//MessageBox("1");
		//	LVITEM   lvitem;  
		//	lvitem.mask= LVIF_TEXT|LVIF_PARAM;  
		//	for(int i=0;i<nCount;++i)  
		//	{  
		//		//MessageBox("11");
		//		lvitem.iItem=i;  
		//		//lvitem.iSubItem=0;
		//		listResult.GetItem(&lvitem);
		//		CString ItemText="";
		//		ItemText.Format("%s",lvitem.pszText);
		//		MessageBox(ItemText);
		//		if(ServerIP.Find(ItemText))
		//		{
		//			MessageBox(ItemText);
		//		}
		//	}  
		//}
		///////////////把已经选择的ip列表显示出来结束
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// 发送或编辑公告
void CNotice::OnBnClickedBtnnotice()
{
	try
	{
		UpdateData(true);
		CString NoticeOp = "";
		GetDlgItemText(IDBTNNOTICE, NoticeOp);

		if(NoticeOp == theApp.operWA.ReadValue("MWA","NI_UI_AddNotice"))//如果按钮为添加公告
		{
			AddNotice();//添加公告
		}
		else if(NoticeOp == theApp.operWA.ReadValue("MWA","NI_UI_EditNotice"))//如果按钮为编辑公告
		{
			EditNotice();//编辑公告
		}
	}
	catch(...)
	{
	}
}

// 是否发送公告
void CNotice::OnBnClickedCheckimme()
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
void CNotice::AddNotice()
{;	
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
		MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_ServerListNull"),theApp.operWA.ReadValue("MWA","Warn"),0);
		return;
	}
	CString NoticeContent = "";
	GetDlgItemText(IDC_EDITCONTENT, NoticeContent);//获取公告内容
	if(NoticeContent == "")//公告内容不能为空
	{
		MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_ContentNotNull"),theApp.operWA.ReadValue("MWA","Warn"),0);
		return;
	}
	//对字符最大值限制
	if(strlen(NoticeContent) >= 400)//公告内容不能超过250个字符
	{
		MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_ContentTooLong"),theApp.operWA.ReadValue("MWA","Warn"),0);
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

	if(checkSendImme.GetCheck() == 1)//如果是立即发送
	{
		interval = 0;//时间间隔为0
	}
	else//如果不是立即发送
	{
		if(toTime <= curTime)//结束时间不能小于当前时间
		{
			MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_StartTime"),theApp.operWA.ReadValue("MWA","Warn"),0);
			return;
		}
		if(toTime <= beginTime)//结束时间不能小于开始时间
		{
			MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_TimeSpan"),theApp.operWA.ReadValue("MWA","Warn"),0);
			return;
		}
		if(interval <= 0)//时间间隔必须大于0
		{
			MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_IntervalNull"),theApp.operWA.ReadValue("MWA","Warn"),0);
			return;
		}
								if(interval <= 1)//时间间隔必须大于0
			{
				MessageBox("时间间隔不能小于1分钟",theApp.operWA.ReadValue("MXD","Warn"),0);
				return;
			}
		CTimeSpan sTimeSpan = toTime - beginTime;
		if(interval >= sTimeSpan.GetTotalMinutes())//时间间隔必须在时间范围之内
		{
			MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_IntervalLong"),theApp.operWA.ReadValue("MWA","Warn"),0);
			return;
		}
	}

	CString strMsg = theApp.operWA.ReadValue("MWA","NI_Hint_AddNotice"); 
	if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //提示玩家是否确定要添加公告
	{
		return;
	}

	CSocketData socketdata;
	char strInt[10];
	socketdata.InitCreate(1,10);//共有七个参数：开始时间、结束时间、时间间隔、公告内容、操作员ID、服务器IP，服务器名称、公告类型

	socketdata.AddTFLV(CEnumCore::TagName::WA_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//开始时间
	socketdata.AddTFLV(CEnumCore::TagName::WA_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//结束时间

	_itoa(interval,strInt,10);
	socketdata.AddTFLV(CEnumCore::TagName::WA_Interval,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//时间间隔
	socketdata.AddTFLV(CEnumCore::TagName::WA_BoardMessage,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeContent),(unsigned char *)mIni.wcharToChar(NoticeContent));//公告内容
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
	socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(strServerIP),(unsigned char *)&strServerIP);//服务器IP
	socketdata.AddTFLV(CEnumCore::TagName::WA_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器IP)

	int midlength = socketdata.EnBody();
	if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BoardTasker_Add))//发送添加公告的请求
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
	}
	socketdata.Destroy();
}
catch(...)
{
}	
}

//编辑公告
void CNotice::EditNotice()
{	
	try
	{		
		CIni mIni;
		UpdateData(true);
		CString strStatus = "";
		GetDlgItemText(IDC_CMBSTATUS, strStatus);//获取公告状态
		if(strStatus == ""&&false)//公告状态不能为空
		{
			MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_StatusNotNull"),theApp.operWA.ReadValue("MWA","Warn"),0);
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
		CString strBeginTime = beginTime.Format("%Y-%m-%d %H:%M:%S");//获取开始时间
		CString strEndTime = toTime.Format("%Y-%m-%d %H:%M:%S");//获取结束时间
		int interval = GetDlgItemInt(IDC_EDITINTERVAL);//获取时间间隔
		if(cmbStatus.GetCurSel() == 1&&false)//如果选择的公告状态是已发送，所有的参数都可以不做限制
		{
		}
		else//如果选择的是未发送，要限制一些参数
		{
			if(NoticeContent == "")//公告内容不能为空
			{
				MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_ContentNotNull"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return;
			}
			//公告最大字符有限制
			if(strlen(NoticeContent) >= 400)//公告内容不能超过250个字符
			{
				MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_ContentTooLong"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return;
			}

			if(toTime <= curTime)//结束时间不能小于当前时间
			{
				MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_StartTime"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return;
			}

			if(toTime <= beginTime)//结束时间不能小于开始时间
			{
				MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_TimeSpan"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return;
			}

			if(interval <= 0)//时间间隔必须大于0
			{
				MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_IntervalNull"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return;
			}

			CTimeSpan sTimeSpan = toTime - beginTime;
			if(interval >= sTimeSpan.GetTotalMinutes())//时间间隔必须在时间范围之内
			{
				MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_IntervalLong"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return;
			}
		}

		CString strMsg = theApp.operWA.ReadValue("MWA","NI_Hint_EditNotice"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //提示是否编辑公告
		{
			return;
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,15);//共有9个参数：开始时间、结束时间、时间间隔、公告内容、大区IP、操作员ID、公告状态、公告ID、服务器IP
		char strInt[10];
		socketdata.AddTFLV(CEnumCore::TagName::WA_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//开始时间
		socketdata.AddTFLV(CEnumCore::TagName::WA_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//结束时间
		_itoa(interval,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::WA_Interval,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//时间间隔
		socketdata.AddTFLV(CEnumCore::TagName::WA_BoardMessage,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeContent),(unsigned char *)mIni.wcharToChar(NoticeContent));//公告内容
		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		//_itoa(cmbStatus.GetCurSel(),strInt,10);
		//socketdata.AddTFLV(CEnumCore::TagName::WA_STATUS,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//公告状态

		_itoa(NoticeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::WA_TaskID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//公告ID

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP

		int midlength = socketdata.EnBody();
		if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BoardTasker_Update))//发送编辑公告的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//返回要发送公告的游戏服务器列表
void  CNotice::ReturnServerIP(char* allServerIP)
{
	CString serverName="";
	int index=0;
	for(int i=0;i<listResult.GetItemCount();i++)
	{

		if(listResult.GetCheck(i))
		{

			ServerList.Lookup(i+1,serverName);//查找服务器IP
			index++;
			if(i==0||index==1)
			{

				sprintf(allServerIP,"%s",serverName);
			}
			else
			{
				if(serverName!="")
				{
					sprintf(allServerIP,"%s|%s",allServerIP,serverName);
				}
			}
		}
	}
	sprintf(allServerIP,"%s",allServerIP);
}

//返回要发送公告的游戏服务器名称列表
CString CNotice::ReturnServerName()
{
	CString rServerName = "";
	CString serverName = "";
	for(int i=0;i<listResult.GetItemCount();i++)
	{
		if(listResult.GetCheck(i))
		{
			serverName=listResult.GetItemText(i,0);//查找服务器名称
			rServerName += serverName;
			rServerName += "|";//将所有的服务器IP用"|"隔开
		}
	}
	return rServerName;
}

//返回所有游戏服务器列表
CString  CNotice::ReturnAllServerIP()
{
	//OperationWA operWA;
	CString rServerIP = "";
	CString serverName = "";
	for(int i=0;i<listResult.GetItemCount();i++)
	{
		ServerList.Lookup(i+1,serverName);//查找服务器IP
		rServerIP += serverName;
		rServerIP += "|";//将所有的服务器IP用"|"隔开
	}
	return rServerIP;
}
void CNotice::ReturnAllServerIP(char* allServerIP)
{
	CString serverName="";
	for(int i=0;i<listResult.GetItemCount();i++)
	{
		ServerList.Lookup(i+1,serverName);//查找服务器IP
		if(i==0)
		{

			sprintf(allServerIP,"%s",serverName);
		}
		else
		{
			sprintf(allServerIP,"%s|%s",allServerIP,serverName);
		}
	}
	sprintf(allServerIP,"%s",allServerIP);

}
//返回所有游戏服务器名称列表
CString CNotice::ReturnAllServerName()
{
	CString rServerName = "";
	CString serverName = "";
	for(int i=0;i<listResult.GetItemCount();i++)
	{
		serverName=listResult.GetItemText(i,0);//查找服务器名称
		rServerName += serverName;
		rServerName += "|";//将所有的服务器IP用"|"隔开
	}
	return rServerName;
}

// 重置信息
void CNotice::OnBnClickedBtnreset()
{
	//OperationWA operWA;
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
		SetDlgItemText(IDBTNNOTICE,theApp.operWA.ReadValue("MWA","NI_UI_AddNotice"));
		GetDlgItem(IDC_CHECKSELECTALL)->EnableWindow(true);
	}
	catch(...)
	{
	}
}

// 接收返回信息
LRESULT CNotice::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_DTPSTARTDATE)->EnableWindow(true);
	GetDlgItem(IDC_DTPSTARTTIME)->EnableWindow(true);
	GetDlgItem(IDC_DTPENDDATE)->EnableWindow(true);
	GetDlgItem(IDC_DTPENDTIME)->EnableWindow(true);
	GetDlgItem(IDC_EDITINTERVAL)->EnableWindow(true);

	unsigned char* lpReceive=(unsigned char*)wParam;
	int bodyLength = (int)lParam;

	//OperationWA operWA;
	CIni mIni;

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Receive");//当前的状态为接收到返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operWA.ReadValue("MWA","Main_UI_ParseData"),theApp.operWA.ReadValue("MWA","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	int pageCount = 0;

	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://如果接收到的是服务器列表返回信息
		{
			listResult.EnableWindow(true);

			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);//获取返回信息中的第一个模块
			if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)//如果第一个模块的TagName是MESSAGE，表示出现了错误信息，显示错误信息并返回
			{
				MessageBox((LPCSTR)&m_tflv.lpdata,theApp.operWA.ReadValue("MWA","Error"),0);
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
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Query_Resp://如果接收到的是公告列表请求的返回信息
		{

			if(pageInfo)//已经可以翻页
			{
				theApp.operWA.BuildDataTable(&socketdata,&listNotice,&pageCount);//构造公告列表信息
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listNotice,&pageCount);//构造公告列表信息

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
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Add_Resp://如果接收到的是添加公告请求的返回信息
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//显示添加公告的结果
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
			SetDlgItemText(IDBTNNOTICE,theApp.operWA.ReadValue("MWA","NI_UI_AddNotice"));
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Update_Resp://如果接收到的是编辑公告请求的返回信息
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//显示编辑公告的结果
			NoticeInfo();//查询所有的公告信息

			//CTime curTime = CTime::GetCurrentTime();//重置所有控件信息
			//dtcStartDate.SetTime(&curTime);
			//dtcStartTime.SetTime(&curTime);
			//dtcEndDate.SetTime(&curTime);
			//dtcEndTime.SetTime(&curTime);
			//SetDlgItemText(IDC_EDITINTERVAL,"60");
			//SetDlgItemText(IDC_EDITCONTENT,"");
			//GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);
			//GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
			//GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);
			//GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);
			//cmbStatus.SetCurSel(0);
			//checkSendImme.SetCheck(0);
			//SetDlgItemText(IDBTNNOTICE,theApp.operWA.ReadValue("MWA","NI_UI_AddNotice"));
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Del_Resp://如果接收到的是删除公告请求的返回信息
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//显示编辑公告的结果
			NoticeInfo();//查询所有的公告信息

			//CTime curTime = CTime::GetCurrentTime();//重置所有控件信息
			//dtcStartDate.SetTime(&curTime);
			//dtcStartTime.SetTime(&curTime);
			//dtcEndDate.SetTime(&curTime);
			//dtcEndTime.SetTime(&curTime);
			//SetDlgItemText(IDC_EDITINTERVAL,"60");
			//SetDlgItemText(IDC_EDITCONTENT,"");
			//GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);
			//GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
			//GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);
			//GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);
			//cmbStatus.SetCurSel(0);
			//checkSendImme.SetCheck(0);
			//SetDlgItemText(IDBTNNOTICE,theApp.operWA.ReadValue("MWA","NI_UI_AddNotice"));
		}
		break;
	default:
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

//单击公告信息的列名进行排序
void CNotice::OnLvnColumnclickListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationWA operWA;
	theApp.operWA.SortListInfo(&listNotice,pNMHDR,pResult);
}

// 关闭对话框
void CNotice::OnClose()
{
	//OperationWA operWA;
	dlgStatus = theApp.operWA.ReadIntValue("MWA","Close");//关闭窗体
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
