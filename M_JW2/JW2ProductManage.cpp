// JW2ProductManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_JW2.h"
#include "JW2ProductManage.h"
#include ".\JW2ProductManage.h"


// CJW2ProductManage �Ի���

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

// ��ʼ���Ի���
BOOL CJW2ProductManage::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();

	
	nItem = -1;// ���������б�õ��к�
	pageInfo = false;// �ж��Ƿ���Ҫ��ҳ
	addOrEdit = false;// ���͹���
	ServerIP = "";// ������IP
	ProductID = 0;// Ȩ��ID	
	AllServer = false;// �Ƿ������д������͹���
	CountItemPrice=0;//�����ܵĽ����
	



	listResult.SetExtendedStyle(listResult.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);//�������б�����Ҫ��ʾCheckBox
	listResult.InsertColumn(0,theApp.operJW2.ReadValue("MJW2","NI_UI_ServerList"),LVCFMT_CENTER,150,-1);

	/*CRect rs;
	GetClientRect(rs);; //��ȡ�Ի���Ĵ�С��Ϣ

	CRect srcRect;
	CRect newRect;

	if( listResult.m_hWnd != NULL )   
	{
		listResult.GetWindowRect(srcRect);//��ȡlistResult�Ĵ�С��Ϣ
		listRWidth = srcRect.right - srcRect.left;//�õ�listResult�Ŀ����Ϣ

		newRect.top = rs.top + 45;		
		newRect.left = rs.left + 10;
		newRect.right = newRect.left + listRWidth;
		newRect.bottom = rs.bottom/2;

		listResult.MoveWindow(newRect);//����listResult��λ��
	}  
	CWnd* pWnd = GetDlgItem(IDC_EDITCONTENT);  
	pWnd = GetDlgItem(IDC_GRPPAGE);  
	if( pWnd )   
	{
		pWnd->GetWindowRect(srcRect);//��ȡGrpPage�Ĵ�С��Ϣ
		gPageLength = srcRect.bottom - srcRect.top;//��ȡGrpPage�ĸ߶���Ϣ

		newRect.top = newRect.bottom + 33;		
		newRect.left = rs.left + 10 + listRWidth;
		newRect.right = rs.right - 8;
		newRect.bottom = newRect.top + gPageLength;

		pWnd->MoveWindow(newRect);//����GrpPage��λ��
	}   

	if( listNotice.m_hWnd != NULL )   
	{
		listNotice.GetWindowRect(srcRect);//��ȡlistNotice�Ĵ�С��Ϣ

		newRect.top = newRect.bottom;
		newRect.left = rs.left + 10;
		newRect.right = rs.right - 8;
		newRect.bottom = rs.bottom - 8;

		listNotice.MoveWindow(newRect);//����listNotice��λ��
	} */

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Create");//��ʼ�����Ի���
	theApp.operJW2.GetServerList();
	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

	return TRUE;
}

// ��ʼ����ʾ�ַ�
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
	SetDlgItemText(IDC_LBLITEMCHOICE,theApp.operJW2.ReadValue("MJW2","PM_UI_ItemChoice"));//����ѡ��
	SetDlgItemText(IDC_LBLITEMNAME,theApp.operJW2.ReadValue("MJW2","PM_UI_ItemName"));//��������
	SetDlgItemText(IDC_LBLITEMNUM,theApp.operJW2.ReadValue("MJW2","PM_UI_ItemNum"));//��������
	SetDlgItemText(IDC_BUTTON3,theApp.operJW2.ReadValue("MJW2","PM_UI_ItemQuery"));//��ѯ


	//SetDlgItemText(IDC_LBLINTERVAL,theApp.operJW2.ReadValue("MJW2","NI_UI_TimeInterval"));
	//SetDlgItemText(IDC_LBLTIME,theApp.operJW2.ReadValue("MJW2","NI_UI_Minite"));	
	//SetDlgItemText(IDC_LBLCONTENT,theApp.operJW2.ReadValue("MJW2","NI_UI_SendContent"));
	//SetDlgItemText(IDC_CHECKIMME,theApp.operJW2.ReadValue("MJW2","NI_UI_SendImme"));
	//SetDlgItemText(IDC_LBLSTATUS,theApp.operJW2.ReadValue("MJW2","NI_UI_NoticeStatus"));
	SetDlgItemText(IDBTNNOTICE,theApp.operJW2.ReadValue("MJW2","PM_UI_DelProductManager"));//����Ȩ��
	SetDlgItemText(IDBTNRESET,theApp.operJW2.ReadValue("MJW2","Reset"));
}

//�����ݼ���Ӧ����
BOOL CJW2ProductManage::PreTranslateMessage(MSG* pMsg)
{

    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
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

// �Զ��ı��С
void CJW2ProductManage::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

/*	CRect rs;
	GetClientRect(rs);; //��ȡ�Ի���Ĵ�С��Ϣ

	CRect srcRect;
	CRect newRect;

	if( listResult.m_hWnd != NULL )   
	{
		listResult.GetWindowRect(srcRect);//��ȡlistResult�Ĵ�С��Ϣ
		listRWidth = srcRect.right - srcRect.left;//�õ�listResult�Ŀ����Ϣ

		newRect.top = rs.top + 45;		
		newRect.left = rs.left + 10;
		newRect.right = newRect.left + listRWidth;
		newRect.bottom = rs.bottom/2;

		listResult.MoveWindow(newRect);//����listResult��λ��
	}  
	CWnd* pWnd = = GetDlgItem(IDC_GRPPAGE);  
	if( pWnd )   
	{
		pWnd->GetWindowRect(srcRect);//��ȡGrpPage�Ĵ�С��Ϣ
		gPageLength = srcRect.bottom - srcRect.top;//��ȡGrpPage�ĸ߶���Ϣ

		newRect.top = newRect.bottom + 33;		
		newRect.left = rs.left + 10 + listRWidth;
		newRect.right = rs.right - 8;
		newRect.bottom = newRect.top + gPageLength;

		pWnd->MoveWindow(newRect);//����GrpPage��λ��
	}   

	if( listNotice.m_hWnd != NULL )   
	{
		listNotice.GetWindowRect(srcRect);//��ȡlistNotice�Ĵ�С��Ϣ

		newRect.top = newRect.bottom;
		newRect.left = rs.left + 10;
		newRect.right = rs.right - 8;
		newRect.bottom = rs.bottom - 8;

		listNotice.MoveWindow(newRect);//����listNotice��λ��
	} */
}

//���ñ�����ɫ
HBRUSH CJW2ProductManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ѡ��������Ϸ���������з���
void CJW2ProductManage::OnBnClickedCheckselectall()
{
	if(AllServer == false)
	{
		for(int i=0; i<listResult.GetItemCount(); i++)
		{
			listResult.SetCheck(i);//ѡ�����е���Ϸ������
		}
		listResult.EnableWindow(false);//����Ϸ�������б��ΪDisable��״̬
		AllServer = true;
	}
	else
	{
		for(int i=0; i<listResult.GetItemCount(); i++)
		{
			listResult.SetCheck(i,false);//ȡ��ѡ�����е���Ϸ������
		}
		listResult.EnableWindow(true);//����Ϸ�������б��ΪEnable��״̬
		AllServer = false;
	}
}

//maple add
/*
// �鿴������Ϣ
void CJW2ProductManage::OnBnClickedBtnnoticeinfo()
{
	NoticeInfo();
}

// �鿴������Ϣ
void CJW2ProductManage::NoticeInfo()
{
	nItem = -1;
	pageInfo = false;//������Ϣ���ܷ�ҳ
	cmbPage.ResetContent();//������Ϣ��ҳ��ѡ��Ϊ��
	while(listNotice.DeleteColumn(0)){}//ɾ�����й����б���Ϣ
	
	try
	{
		char strInt[10];
		int index = theApp.operJW2.ReadIntValue("MJW2","index");//�鿴��һҳ�ļ�¼
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//ÿҳ��50����¼
        
		CSocketData socketdata;
		socketdata.InitCreate(1,2);//��������������ҳ����ÿҳ�ļ�¼��

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼��

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_BOARDTASK_QUERY);//���Ͳ�ѯ������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_NoticeInfo"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// ��ҳ�鿴������Ϣ
void CJW2ProductManage::OnCbnSelchangeCmbuipage()
{
	try
	{
		if(pageInfo)
		{
			while(listNotice.DeleteColumn(0)){}//��������б��е���������
			
			int index = cmbPage.GetCurSel() + 1;//��ҳ�鿴��ҳ��
			int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//ÿҳ��50����¼

			CSocketData socketdata;
			socketdata.InitCreate(1,2);//��������������ҳ����ÿҳ�ļ�¼��
			char strInt[10];

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼��

			int midlength = socketdata.EnBody();
			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_BOARDTASK_QUERY);//���Ͳ�ѯ������Ϣ������

			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_NoticeInfo"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}
}

// ˫��������Ϣ���б༭
void CJW2ProductManage::OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{
	CIni mIni;
	try
	{
		if(listNotice.GetItemCount() != 0)//��������б��е�ǰ�м�¼
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listNotice.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listNotice.SubItemHitTest(&lvinfo);//��ȡҪ�༭�Ĺ����������к�

			if(nItem >= 0)
			{
				NoticeID = atoi(theApp.operJW2.GetValueByColName(&listNotice, nItem, theApp.operJW2.ReadValue("MJW2","JW2_TaskID")));//��ȡ����ID

				CTime curTime = CTime::GetCurrentTime();//��ȡ��ǰʱ��
			    dtcStartDate.SetTime(&curTime);//���ÿ�ʼʱ��
			    dtcStartTime.SetTime(&curTime);//���ÿ�ʼʱ��
			    dtcEndDate.SetTime(&curTime);//���ý���ʱ��
			    dtcEndTime.SetTime(&curTime);//���ý���ʱ��

				SetDlgItemText(IDC_EDITINTERVAL,theApp.operJW2.GetValueByColName(&listNotice, nItem, theApp.operJW2.ReadValue("MJW2","JW2_Interval")));//��ȡʱ����������
				SetDlgItemText(IDC_EDITCONTENT,theApp.operJW2.GetValueByColName(&listNotice, nItem, theApp.operJW2.ReadValue("MJW2","JW2_BoardMessage")));//��ȡ�������ݲ�����

				ServerIP = theApp.operJW2.GetValueByColName(&listNotice, nItem, theApp.operJW2.ReadValue("MJW2","JW2_ServerIP"));//��ȡ������IP

				SetDlgItemText(IDBTNNOTICE,theApp.operJW2.ReadValue("MJW2","NI_UI_EditNotice"));

				GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_SHOW);//��ʾ����״̬
				GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_HIDE);//����ʾ�������͹����CheckBox

				GetDlgItem(IDC_LISTSERVER)->EnableWindow(false);//�÷������б��״̬��ΪDisable
			}
		}
		else
		{
			nItem = -1;
			GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//����ʾ����״̬
			GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);//�÷������б��״̬��ΪEnable		
			SetDlgItemText(IDBTNNOTICE,theApp.operJW2.ReadValue("MJW2","NI_UI_AddNotice"));
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}
*/

// ����Ȩ��
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

		//GM�ʺ�
		CString GMName;
		///int GMID=0;
		GetDlgItemText(IDC_CMBGM,GMName);//��ȡGM�ʺ�
		////UserList.Lookup(cmbRealName.GetCurSel()+1,GMID);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP
		///_itoa(GMID,strInt,10);
		////socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û����к�
		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(GMName),(unsigned char *)mIni.wcharToChar(GMName));//������IP


		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		ServerIP = ReturnServerIP();
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP

		char ItemData[2048];
		ZeroMemory(ItemData, 2048);//��ʼ��Ҫ���͵ĵ�����Ϣ
		char tmpItemData[2048];
		ZeroMemory(tmpItemData, 2048);//������ʱ�ĵ�����Ϣ

		int itemCount = listItemResult.GetItemCount();//Ҫ��ӵ��ߵ�����
		int mid = 0;//Ҫ��ӵĵ�����Ʒ��
		int itemNum = 0;//Ҫ��ӵĵ�������
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

		//��ӵĵ�������
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItem,CEnumCore::TagFormat::TLV_STRING,strlen(ItemData),(unsigned char *)ItemData);

		/////_itoa(itemCount,strInt,10);
		/////socketdata.AddTFLV(CEnumCore::TagName::PageCount,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�������


		CTime StartDate;
		dtcStartDate.GetTime(StartDate);

		CTime EndDate;
		dtcEndDate.GetTime(EndDate);

		CTime beginTime = CTime::CTime(StartDate.GetYear(),StartDate.GetMonth(),StartDate.GetDay(),0,0,0);
		CTime toTime = CTime::CTime(EndDate.GetYear(),EndDate.GetMonth(),EndDate.GetDay(),0,0,0);

		CString strBeginTime = beginTime.Format("%Y/%m/%d %H:%M:%S");//���ÿ�ʼʱ��
		CString strEndTime = toTime.Format("%Y/%m/%d %H:%M:%S");//���ý���ʱ��


		socketdata.AddTFLV(CEnumCore::TagName::JW2_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::JW2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//����ʱ��

		_itoa(CountItemPrice,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_TotalPrice,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�ܶ�

		////_itoa(iPageSize,strInt,10);
		///socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


		int midlength = socketdata.EnBody();
		if(theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ProductManage_Insert))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
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
// �Ƿ��͹���
void CJW2ProductManage::OnBnClickedCheckimme()
{
	if(checkSendImme.GetCheck() == 1)//ѡ���������ͣ��ÿ�ʼʱ�䡢����ʱ�䡢ʱ�����Ŀؼ������Disable��״̬
	{
		GetDlgItem(IDC_DTPSTARTDATE)->EnableWindow(false);
		GetDlgItem(IDC_DTPSTARTTIME)->EnableWindow(false);
		GetDlgItem(IDC_DTPENDDATE)->EnableWindow(false);
		GetDlgItem(IDC_DTPENDTIME)->EnableWindow(false);
		GetDlgItem(IDC_EDITINTERVAL)->EnableWindow(false);
	}
	else//��ѡ���������ͣ��ÿ�ʼʱ�䡢����ʱ�䡢ʱ�����Ŀؼ������Enable��״̬
	{
		GetDlgItem(IDC_DTPSTARTDATE)->EnableWindow(true);
		GetDlgItem(IDC_DTPSTARTTIME)->EnableWindow(true);
		GetDlgItem(IDC_DTPENDDATE)->EnableWindow(true);
		GetDlgItem(IDC_DTPENDTIME)->EnableWindow(true);
		GetDlgItem(IDC_EDITINTERVAL)->EnableWindow(true);
	}
}

// ���͹���
void CJW2ProductManage::AddNotice()
{
	try
	{		
		CIni mIni;

		UpdateData(true);

		int svrCheck = 0;
		for(int i=0;i<listResult.GetItemCount();i++)
		{
			if(listResult.GetCheck(i))//�鿴��û��ѡ�е�ǰ����Ϸ������
			{
				svrCheck++;
			}
		}
		if(svrCheck == 0)//���͹���ʱ����Ϸ����������Ϊ��
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_ServerListNull"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
			return;
		}

		CString NoticeContent = "";
		GetDlgItemText(IDC_EDITCONTENT, NoticeContent);//��ȡ��������

		if(NoticeContent == "")//�������ݲ���Ϊ��
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_ContentNotNull"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
			return;
		}

		if(strlen(NoticeContent) >= 256)//�������ݲ��ܳ���256���ַ�
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_ContentTooLong"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
			return;
		}

		CTime curTime = CTime::GetCurrentTime();

		CTime StartDate;
		dtcStartDate.GetTime(StartDate);
		CTime StartTime;
		dtcStartTime.GetTime(StartTime);//��ȡ��ʼʱ��

		CTime EndDate;
		dtcEndDate.GetTime(EndDate);
		CTime EndTime;
		dtcEndTime.GetTime(EndTime);//��ȡ����ʱ��

		CTime beginTime = CTime::CTime(StartDate.GetYear(),StartDate.GetMonth(),StartDate.GetDay(),StartTime.GetHour(),StartTime.GetMinute(),StartTime.GetSecond());
		CTime toTime = CTime::CTime(EndDate.GetYear(),EndDate.GetMonth(),EndDate.GetDay(),EndTime.GetHour(),EndTime.GetMinute(),EndTime.GetSecond());

		CString strBeginTime = beginTime.Format("%Y/%m/%d %H:%M:%S");//���ÿ�ʼʱ��
		CString strEndTime = toTime.Format("%Y/%m/%d %H:%M:%S");//���ý���ʱ��

		int interval = GetDlgItemInt(IDC_EDITINTERVAL);//��ȡʱ����

		if(checkSendImme.GetCheck() == 1)//�������������
		{
			interval = 0;//ʱ����Ϊ0
		}
		else//���������������
		{
			if(toTime <= curTime)//����ʱ�䲻��С�ڵ�ǰʱ��
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_StartTime"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}

			if(toTime <= beginTime)//����ʱ�䲻��С�ڿ�ʼʱ��
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_TimeSpan"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}
			if(interval <= 0)//ʱ�����������0
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_Interval"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}
		}

		CString strMsg = theApp.operJW2.ReadValue("MJW2","NI_Hint_AddNotice"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //��ʾ����Ƿ�ȷ��Ҫ��ӹ���
		{
			return;
		}

		CSocketData socketdata;
		char strInt[10];
		socketdata.InitCreate(1,7);//�����߸���������ʼʱ�䡢����ʱ�䡢ʱ�������������ݡ�����IP������ԱID��������IP

		socketdata.AddTFLV(CEnumCore::TagName::JW2_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::JW2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//����ʱ��

		_itoa(interval,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_Interval,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ʱ����
		socketdata.AddTFLV(CEnumCore::TagName::JW2_BoardMessage,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeContent),(unsigned char *)mIni.wcharToChar(NoticeContent));//��������

		CString GSServerIP = "255.255.255.255";
		socketdata.AddTFLV(CEnumCore::TagName::JW2_GSServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(GSServerIP),(unsigned char *)mIni.wcharToChar(GSServerIP));//����IP

	
		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_BOARDTASK_INSERT);//������ӹ��������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�������
		socketdata.Destroy();
	}
	catch(...)
	{
	}	
}

//�༭����
void CJW2ProductManage::EditNotice()
{

	try
	{		
		CIni mIni;

		UpdateData(true);

		CString strStatus = "";
		GetDlgItemText(IDC_CMBSTATUS, strStatus);//��ȡ����״̬
		if(strStatus == "")//����״̬����Ϊ��
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_StatusNotNull"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
			return;
		}

		CString NoticeContent = "";
		GetDlgItemText(IDC_EDITCONTENT, NoticeContent);//��ȡ��������

		CTime curTime = CTime::GetCurrentTime();//��ȡ��ǰʱ��

		CTime StartDate;
		dtcStartDate.GetTime(StartDate);
		CTime StartTime;
		dtcStartTime.GetTime(StartTime);//��ȡ��ʼʱ��

		CTime EndDate;
		dtcEndDate.GetTime(EndDate);
		CTime EndTime;
		dtcEndTime.GetTime(EndTime);//��ȡ����ʱ��

		CTime beginTime = CTime::CTime(StartDate.GetYear(),StartDate.GetMonth(),StartDate.GetDay(),StartTime.GetHour(),StartTime.GetMinute(),StartTime.GetSecond());
		CTime toTime = CTime::CTime(EndDate.GetYear(),EndDate.GetMonth(),EndDate.GetDay(),EndTime.GetHour(),EndTime.GetMinute(),EndTime.GetSecond());

		CString strBeginTime = beginTime.Format("%Y/%m/%d %H:%M:%S");//��ȡ��ʼʱ��
		CString strEndTime = toTime.Format("%Y/%m/%d %H:%M:%S");//��ȡ����ʱ��

		int interval = GetDlgItemInt(IDC_EDITINTERVAL);//��ȡʱ����

		if(cmbStatus.GetCurSel() == 1)//���ѡ��Ĺ���״̬���ѷ��ͣ����еĲ��������Բ�������
		{
		}
		else//���ѡ�����δ���ͣ�Ҫ����һЩ����
		{
			if(NoticeContent == "")//�������ݲ���Ϊ��
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_ContentNotNull"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}

			if(strlen(NoticeContent) >= 256)//�������ݲ��ܳ���256���ַ�
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_ContentTooLong"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}

			if(toTime <= curTime)//����ʱ�䲻��С�ڵ�ǰʱ��
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_StartTime"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}

			if(toTime <= beginTime)//����ʱ�䲻��С�ڿ�ʼʱ��
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_TimeSpan"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}

			if(interval <= 0)//ʱ����Ҫ����0
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","NI_Warn_Interval"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}
		}

		CString strMsg = theApp.operJW2.ReadValue("MJW2","NI_Hint_EditNotice"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //��ʾ�Ƿ�༭����
		{
			return;
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,9);//����9����������ʼʱ�䡢����ʱ�䡢ʱ�������������ݡ�����IP������ԱID������״̬������ID��������IP
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::JW2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//����ʱ��

		_itoa(interval,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_Interval,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ʱ����
		socketdata.AddTFLV(CEnumCore::TagName::JW2_BoardMessage,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeContent),(unsigned char *)mIni.wcharToChar(NoticeContent));//��������

		CString GSServerIP = "255.255.255.255";
		socketdata.AddTFLV(CEnumCore::TagName::JW2_GSServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(GSServerIP),(unsigned char *)mIni.wcharToChar(GSServerIP));//����IP

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		_itoa(cmbStatus.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_Status,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����״̬

		_itoa(NoticeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_TaskID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_BOARDTASK_UPDATE);//���ͱ༭���������

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�������
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}
*/

//����Ҫ���͹������Ϸ�������б�
CString  CJW2ProductManage::ReturnServerIP()
{
	CString rServerIP = "";
	CString serverName = "";
	for(int i=0;i<listResult.GetItemCount();i++)
	{
		if(listResult.GetCheck(i))
		{
			ServerList.Lookup(i+1,serverName);//���ҷ�����IP
			rServerIP += serverName;
			rServerIP += "|";//�����еķ�����IP��"|"����
		}
	}
	return rServerIP;
}

// ������Ϣ
void CJW2ProductManage::OnBnClickedBtnreset()
{
	try
	{
		CTime curTime = CTime::GetCurrentTime();//��ȡ��ǰʱ��
		dtcStartDate.SetTime(&curTime);
		//dtcStartTime.SetTime(&curTime);
		dtcEndDate.SetTime(&curTime);
		//dtcEndTime.SetTime(&curTime);

		//maple add
		cmbRealName.SetCurSel(0);
		SetDlgItemText(IDC_EDITITEM,"");//��յ�����
		SetDlgItemInt(IDC_EDITITEMNUM,1);//��������Ĭ��Ϊ1
		listItem.DeleteAllItems();
		listItemResult.DeleteAllItems();
		///////m_ckServer.SetCheck(0);




		//SetDlgItemText(IDC_EDITINTERVAL,"60");//����ʱ����Ϊ60
		//SetDlgItemText(IDC_EDITCONTENT,"");//���ù�������Ϊ��
		//GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//���ع���״̬
		//GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);//��ʾ��������
		//GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);
		//cmbStatus.SetCurSel(0);
		//checkSendImme.SetCheck(0);
		//SetDlgItemText(IDBTNNOTICE,theApp.operJW2.ReadValue("MJW2","NI_UI_AddNotice"));
	}
	catch(...)
	{
	}
}

// ���շ�����Ϣ
LRESULT CJW2ProductManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);//���������洦�����

	//GetDlgItem(IDC_DTPSTARTDATE)->EnableWindow(true);
	//GetDlgItem(IDC_DTPSTARTTIME)->EnableWindow(true);

	unsigned char* lpReceive=(unsigned char*)wParam;
	int bodyLength = (int)lParam;


	CIni mIni;

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Receive");//��ǰ��״̬Ϊ���յ�������Ϣ

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	socketdata.DeBody(lpReceive,bodyLength);

	int pageCount = 0;

	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://������յ����Ƿ������б�����Ϣ
		{
			listResult.EnableWindow(true);

			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);//��ȡ������Ϣ�еĵ�һ��ģ��
			if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)//�����һ��ģ���TagName��MESSAGE����ʾ�����˴�����Ϣ����ʾ������Ϣ������
			{
				MessageBox((LPCSTR)&m_tflv.lpdata,theApp.operJW2.ReadValue("MJW2","Error"),0);
				socketdata.Destroy();
				return false;
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//��ȡ���еķ�����IP
				ServerList.SetAt(i,ServerIP);//��ӵ�CMap��Ķ���ServerList��
			}

			listResult.DeleteAllItems();//����������б��е���������
			CString serverName = "";
			int nRow = 0;
			for(int i=0;i<socketdata.getQueryNum();i++)
			{
				nRow = listResult.InsertItem(i,"");
				serverName = (LPSTR)&socketdata.getTLVByName(i+1,CEnumCore::TagName::ServerInfo_City).lpdata;//��ȡ��Ϸ����������
				listResult.SetItemText(nRow,0,serverName);//����Ϸ������������ӵ��������б���
			}

			QueryUserList();
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_QUERY_ALL_RESP:
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int UserID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::User_ID).lpdata);//�õ��û�ID
				UserList.SetAt(i,UserID);//���û�ID������CMap��Ķ���UserList��
			}

			theApp.operJW2.BuildComboxUser(&socketdata,&cmbRealName);//������������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ITEM_SELECT_RESP:
		{
			theApp.operJW2.BuildDataTable(&socketdata,&listItem,&pageCount);//����CListCtrl����
		}
		break;
	//maple add
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Insert_Resp://����Ȩ��
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Del_Resp://ɾ��Ȩ��
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//��ʾ���

		}
		break;

	case CEnumCore::Message_Tag_ID::JW2_ProductManage_View_Resp://������յ����ǲ鿴Ȩ������ķ�����Ϣ
		{
			if(pageInfo)//�Ѿ����Է�ҳ
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listNotice,&pageCount);//���칫���б���Ϣ
			}
			else
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listNotice,&pageCount);//���칫���б���Ϣ

				if(pageCount<=0)//���ҳ��������0
				{
					pageInfo = false;//��������б���Ϣ
					nItem = -1;
					cmbPage.ResetContent();
					//while(listNotice.DeleteColumn(0)){}
				}
				else//���ҳ������0
				{
					nItem = 0;//û��ѡ�񹫸��б��е��ض���
					cmbPage.ResetContent();//������淭ҳ��ѡ���е�����
					for(int i=1;i<=pageCount;i++)//������е�ҳ��
					{
						CString str="";
						str.Format("%d",i);
						cmbPage.AddString(str);
					}
					cmbPage.SetCurSel(0);//��ʼҳ��Ϊ1
					if(pageCount == 1)//���ֻ��1ҳ
					{
						pageInfo = false;//���ܷ�ҳ
					}
					else//�������1ҳ
					{
						pageInfo = true;//���Է�ҳ
					}
				}				
			}
		}
		break;
/*	case CEnumCore::Message_Tag_ID::JW2_BOARDTASK_INSERT_RESP://������յ�������ӹ�������ķ�����Ϣ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//��ʾ��ӹ���Ľ��
			NoticeInfo();//��ѯ���еĹ�����Ϣ

			CTime curTime = CTime::GetCurrentTime();//�������пؼ���Ϣ
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
	case CEnumCore::Message_Tag_ID::JW2_BOARDTASK_UPDATE_RESP://������յ����Ǳ༭��������ķ�����Ϣ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//��ʾ�༭����Ľ��
			NoticeInfo();//��ѯ���еĹ�����Ϣ

			CTime curTime = CTime::GetCurrentTime();//�������пؼ���Ϣ
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


//����������Ϣ��������������
void CJW2ProductManage::OnLvnColumnclickListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{

	theApp.operJW2.SortListInfo(&listNotice,pNMHDR,pResult);
}

// �رնԻ���
void CJW2ProductManage::OnClose()
{

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Close");//�رմ���
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
//��ȡ���е��û�����
void CJW2ProductManage::QueryUserList()
{
	try
	{		
		CIni mIni;

		int index = 0;
		int iPageSize = 0;

		cmbRealName.ResetContent();

		CSocketData socketdata;	
		socketdata.InitCreate(1,3);//����3��������ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID

		//_itoa(index,strInt,10);
		//socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		//_itoa(iPageSize,strInt,10);
		//socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_QUERY_ALL))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�������
		}

		socketdata.Destroy();
	}
	catch(...)
	{
		//MessageBox(theApp.operJW2.ReadValue("MGM","IM_Error_SearchItemType"),theApp.operJW2.ReadValue("MGM","Error"),0);
	}	
}
//����ģ����ѯ
void CJW2ProductManage::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{		
		CIni mIni;

		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		while(listItem.DeleteColumn(0)){};

		UpdateData(true);			

		CString tmpName = "";//����ģ����ѯ�ĵ�������
		GetDlgItemText(IDC_EDITITEM,tmpName);//��ȡ����ģ����ѯ�ĵ�������
		if(tmpName == "")//����ģ����ѯ�ĵ������Ʋ���Ϊ��
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","IM_WARN_BlurItemNameNull"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

	//	socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
	//	socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
	//	socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
	//	socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		//����ģ����ѯ�ĵ�������
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItemName,CEnumCore::TagFormat::TLV_STRING,strlen(tmpName),(unsigned char *)mIni.wcharToChar(tmpName));

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ITEM_SELECT);//����ģ����ѯ

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ^����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_TreasureBox"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}
}

void CJW2ProductManage::OnBnClickedButton1()/////���ƣ��ѵ�����ӵ�����б�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
/*		CIni mIni;

		if((listItem.GetItemCount() == 0)||(addItem < 0))//���Ҫ��ӵĵ����б�Ϊ���򷵻�
		{
			return;
		}

		CString tmpItemID = listItem.GetItemText(addItem, 0);
		int ItemID = atoi(mIni.wcharToChar(tmpItemID));//��ȡҪ��ӵĵ���ID
		CString ItemName = listItem.GetItemText(addItem, 1);//��ȡҪ��ӵĵ�������
		CString ItemLimit= listItem.GetItemText(addItem, 2);

		//maple add
		CString ItemPrice=listItem.GetItemText(addItem,3);//���ߵ���
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
			dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
			listItemResult.SetExtendedStyle(dwStyle); //������չ���

			listItemResult.InsertColumn(0,"����ID",LVCFMT_CENTER,60,-1);
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
			listItemResult.SetItemText(nRow,3,ItemPrice);//���ߵ���

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
				listItemResult.SetItemText(nRow,3,ItemPrice);//���ߵ���

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
	int ItemID = atoi(mIni.wcharToChar(tmpItemID));//��ȡҪ��ӵĵ���ID
	CString ItemName = listItem.GetItemText(nSel, 1);//��ȡҪ��ӵĵ�������
	CString ItemLimit= listItem.GetItemText(nSel, 2);

	//maple add
	CString ItemPrice=listItem.GetItemText(nSel,3);//���ߵ���
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
		dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
		listItemResult.SetExtendedStyle(dwStyle); //������չ���

		listItemResult.InsertColumn(0,"����ID",LVCFMT_CENTER,60,-1);
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
		listItemResult.SetItemText(nRow,3,ItemPrice);//���ߵ���

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
			listItemResult.SetItemText(nRow,3,ItemPrice);//���ߵ���

			listItemResult.SetItemText(nRow,4,ItemLimit);
			listItemResult.SetItemText(nRow,5,ItemRemain);

		}

		//maple add
		CountItemPrice=CountItemPrice+iItemPrice*itemNum;
		SetDlgItemInt(IDC_ETCOUNTPRICE,CountItemPrice);	
	}

}


void CJW2ProductManage::OnBnClickedButton2()///����////ɾ��
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

			
		DelItemPrice=listItemResult.GetItemText(nDel,3);//���ߵ���
		DelItemNum=listItemResult.GetItemText(nDel,2);//��������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(listItem.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

//////		addItem = listItem.SubItemHitTest(&lvinfo);//�����ڿ�����ӵĵ����б���ѡ�е��к�
////		selectItemID=listItem.GetItemText(addItem,0);//�����ӵ��ߵ�ID
		
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

		addItem = listItem.SubItemHitTest(&lvinfo);//�����ڿ�����ӵĵ����б���ѡ�е��к�

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(listItemResult.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItemResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		delItem = listItemResult.SubItemHitTest(&lvinfo);//�����ڿ�����ӵĵ����б���ѡ�е��к�
	}
	else
	{
		delItem = -1;
	}
	*pResult = 0;
}

void CJW2ProductManage::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(listItemResult.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItemResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		delItem = listItemResult.SubItemHitTest(&lvinfo);//�����ڿ�����ӵĵ����б���ѡ�е��к�

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


//�鿴Ȩ��
void CJW2ProductManage::OnBnClickedBtnnoticeinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIni mIni;
	nItem = -1;
	pageInfo = false;//������Ϣ���ܷ�ҳ
	cmbPage.ResetContent();//������Ϣ��ҳ��ѡ��Ϊ��
	while(listNotice.DeleteColumn(0)){}//ɾ�����й����б���Ϣ

	try
	{
		char strInt[10];
		int index = theApp.operJW2.ReadIntValue("MJW2","index");//�鿴��һҳ�ļ�¼
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//ÿҳ��50����¼

		CSocketData socketdata;
		socketdata.InitCreate(1,2);//��������������ҳ����ÿҳ�ļ�¼��

		///ServerIP = ReturnServerIP();
		///socketdata.AddTFLV(CEnumCore::TagName::userIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼��

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ProductManage_View);//���Ͳ�ѯȨ�޵�����

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		///MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_NoticeInfo"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

//˫��ɾ��Ȩ��
void CJW2ProductManage::OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIni mIni;
	try
	{
		if(listNotice.GetItemCount() != 0)//��������б��е�ǰ�м�¼
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listNotice.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listNotice.SubItemHitTest(&lvinfo);//��ȡҪ�༭�Ĺ����������к�

			if(nItem >= 0)
			{
				ProductID = atoi(theApp.operJW2.GetValueByColName(&listNotice, nItem, theApp.operJW2.ReadValue("MJW2","JW2_TaskID")));//��ȡȨ��ID
				
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
//ɾ��Ȩ��
void CJW2ProductManage::DelProductManager()
{
	try
	{

		CIni mIni;

		CString strMsg = theApp.operJW2.ReadValue("MJW2","NI_Hint_DelProductManager"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //��ʾ�Ƿ�ɾ��Ȩ��
		{
			return;
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,9);//����9��������
		char strInt[10];

		
		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		
		_itoa(ProductID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_TaskID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ProductManage_Del);//����ɾ��Ȩ�޵�����

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�������
		socketdata.Destroy();
	}
	catch(...)
	{

	}
}




//��ҳ��ѯȨ��
void CJW2ProductManage::OnCbnSelchangeCmbuipage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIni mIni;
	try
	{
		if(pageInfo)
		{
			while(listNotice.DeleteColumn(0)){}//��������б��е���������

			int index = cmbPage.GetCurSel() + 1;//��ҳ�鿴��ҳ��
			int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//ÿҳ��50����¼

			CSocketData socketdata;
			socketdata.InitCreate(1,2);//��������������ҳ����ÿҳ�ļ�¼��
			char strInt[10];

			ServerIP = ReturnServerIP();
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼��

			int midlength = socketdata.EnBody();
			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ProductManage_View);//���Ͳ�ѯȨ�޵�����

			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			socketdata.Destroy();
		}
	}
	catch(...)
	{
		////MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_NoticeInfo"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}
}

//��֤Ȩ��
void CJW2ProductManage::OnBnClickedBtnvalidate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{		
		CIni mIni;

		
		CSocketData socketdata;	
		socketdata.InitCreate(1,25);
		char strInt[10];
		ZeroMemory(strInt, 10);

		//GM�ʺ�
		CString GMName;
		int GMID=0;
		GetDlgItemText(IDC_CMBGM,GMName);//��ȡGM�ʺ�
		UserList.Lookup(cmbRealName.GetCurSel()+1,GMID);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP
		_itoa(GMID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û����к�
		//////////////socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(GMName),(unsigned char *)mIni.wcharToChar(GMName));//������IP


		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		ServerIP = ReturnServerIP();
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP

		char ItemData[2048];
		ZeroMemory(ItemData, 2048);//��ʼ��Ҫ���͵ĵ�����Ϣ
		char tmpItemData[2048];
		ZeroMemory(tmpItemData, 2048);//������ʱ�ĵ�����Ϣ

		int itemCount = listItemResult.GetItemCount();//Ҫ��ӵ��ߵ�����
		int mid = 0;//Ҫ��ӵĵ�����Ʒ��
		int itemNum = 0;//Ҫ��ӵĵ�������
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

		//��ӵĵ�������
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItem,CEnumCore::TagFormat::TLV_STRING,strlen(ItemData),(unsigned char *)ItemData);

		/////_itoa(itemCount,strInt,10);
		/////socketdata.AddTFLV(CEnumCore::TagName::PageCount,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�������


		CTime StartDate;
		dtcStartDate.GetTime(StartDate);

		CTime EndDate;
		dtcEndDate.GetTime(EndDate);

		CTime beginTime = CTime::CTime(StartDate.GetYear(),StartDate.GetMonth(),StartDate.GetDay(),0,0,0);
		CTime toTime = CTime::CTime(EndDate.GetYear(),EndDate.GetMonth(),EndDate.GetDay(),0,0,0);

		CString strBeginTime = beginTime.Format("%Y/%m/%d %H:%M:%S");//���ÿ�ʼʱ��
		CString strEndTime = toTime.Format("%Y/%m/%d %H:%M:%S");//���ý���ʱ��


		socketdata.AddTFLV(CEnumCore::TagName::JW2_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::JW2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//����ʱ��

		///_itoa(CountItemPrice,strInt,10);
		////socketdata.AddTFLV(CEnumCore::TagName::JW2_TotalPrice,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�ܶ�

		
		int midlength = socketdata.EnBody();
		if(theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ProductManage_Validate))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		/////MessageBox(theApp.operJW2.ReadValue("MJW2","IM_Error_ADDITEM"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}
}
