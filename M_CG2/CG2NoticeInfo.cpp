// CG2NoticeInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2NoticeInfo.h"
#include ".\CG2noticeinfo.h"


// CCG2NoticeInfo �Ի���

IMPLEMENT_DYNAMIC(CCG2NoticeInfo, CDialog)
CCG2NoticeInfo::CCG2NoticeInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2NoticeInfo::IDD, pParent)
{
}

CCG2NoticeInfo::~CCG2NoticeInfo()
{
}

void CCG2NoticeInfo::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CCG2NoticeInfo, CDialog)
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
END_MESSAGE_MAP()

// ��ʼ���Ի���
BOOL CCG2NoticeInfo::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();

	dtcStartTime.SetFormat("HH:mm:ss");
	dtcEndTime.SetFormat("HH:mm:ss");
	
	nItem = -1;// ���������б�õ��к�
	pageInfo = false;// �ж��Ƿ���Ҫ��ҳ
	addOrEdit = false;// ���͹���
	ServerIP = "";// ������IP
	NoticeID = "";// ����ID	
	AllServer = false;// �Ƿ������д������͹���

	//OperationCG2 theApp.operCG2;

	cmbStatus.ResetContent();
	cmbStatus.AddString(theApp.operCG2.ReadValue("MCG2","NI_UI_UnSend"));//δ����
	cmbStatus.AddString(theApp.operCG2.ReadValue("MCG2","NI_UI_Sended"));//�ѷ���
	cmbStatus.SetCurSel(0);

	SetDlgItemText(IDC_EDITINTERVAL,"60");
	GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//���ع���״̬
	GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);

	listResult.SetExtendedStyle(listResult.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);//�������б�����Ҫ��ʾCheckBox
	listResult.InsertColumn(0,theApp.operCG2.ReadValue("MCG2","NI_UI_ServerList"),LVCFMT_CENTER,150,-1);

	CRect rs;
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
		newRect.bottom = rs.bottom - 8;

		listResult.MoveWindow(newRect);//����listResult��λ��
	}  

	CWnd* pWnd = GetDlgItem(IDC_EDITCONTENT);  
	if( pWnd )   
	{
		pWnd->GetWindowRect(srcRect);//��ȡ��������CEdit�Ĵ�С��Ϣ
		contentLength = srcRect.bottom - srcRect.top;//��ȡ��������CEdit�ĸ߶���Ϣ

		newRect.top = rs.top + 117;		
		newRect.left = newRect.right + 86;
		newRect.right = rs.right - 8;
		newRect.bottom = newRect.top + contentLength;

		pWnd->MoveWindow(newRect);//���ù�������CEdit��λ��
	}   
	
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
		newRect.left = rs.left + 10 + listRWidth;
		newRect.right = rs.right - 8;
		newRect.bottom = rs.bottom - 8;

		listNotice.MoveWindow(newRect);//����listNotice��λ��
	}   

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//��ʼ�����Ի���

	theApp.operCG2.GetServerList();

	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CCG2NoticeInfo::InitUI()
{
	//OperationCG2 theApp.operCG2;

	SetWindowText(theApp.operCG2.ReadValue("MCG2","NI_UI_NoticeInfo"));

	SetDlgItemText(IDC_CHECKSELECTALL,theApp.operCG2.ReadValue("MCG2","NI_UI_SelectAll"));

	SetDlgItemText(IDC_BTNNOTICEINFO,theApp.operCG2.ReadValue("MCG2","NI_UI_NoticeCheck"));
	SetDlgItemText(IDC_LBLHINT,theApp.operCG2.ReadValue("MCG2","NI_UI_NoticeHint"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","BU_UI_LblPage"));

	SetDlgItemText(IDC_LBLSTARTTIME,theApp.operCG2.ReadValue("MCG2","NI_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operCG2.ReadValue("MCG2","NI_UI_EndTime"));
	SetDlgItemText(IDC_LBLINTERVAL,theApp.operCG2.ReadValue("MCG2","NI_UI_TimeInterval"));
	SetDlgItemText(IDC_LBLTIME,theApp.operCG2.ReadValue("MCG2","NI_UI_Minite"));	
	SetDlgItemText(IDC_LBLCONTENT,theApp.operCG2.ReadValue("MCG2","NI_UI_SendContent"));
	SetDlgItemText(IDC_CHECKIMME,theApp.operCG2.ReadValue("MCG2","NI_UI_SendImme"));
	SetDlgItemText(IDC_LBLSTATUS,theApp.operCG2.ReadValue("MCG2","NI_UI_NoticeStatus"));
	SetDlgItemText(IDBTNNOTICE,theApp.operCG2.ReadValue("MCG2","NI_UI_AddNotice"));
	SetDlgItemText(IDBTNRESET,theApp.operCG2.ReadValue("MCG2","Reset"));
}

// �Զ��ı��С
void CCG2NoticeInfo::OnSize(UINT nType, int cx, int cy)
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

		listResult.MoveWindow(newRect);//����listResult��λ��
	}  

	CWnd* pWnd = GetDlgItem(IDC_EDITCONTENT);  
	if( pWnd )   
	{
		newRect.top = rs.top + 117;		
		newRect.left = newRect.right + 86;
		newRect.right = rs.right - 8;
		newRect.bottom = newRect.top + contentLength;

		pWnd->MoveWindow(newRect);//���ù�������CEdit��λ��
	}   
	
	pWnd = GetDlgItem(IDC_GRPPAGE);  
	if( pWnd )   
	{
		newRect.top = newRect.bottom + 33;		
		newRect.left = rs.left + 10 + listRWidth;
		newRect.right = rs.right - 8;
		newRect.bottom = newRect.top + gPageLength;

		pWnd->MoveWindow(newRect);//����GrpPage��λ��
	}   

	if( listNotice.m_hWnd != NULL )   
	{
		newRect.top = newRect.bottom;		
		newRect.left = rs.left + 10 + listRWidth;
		newRect.right = rs.right - 8;
		newRect.bottom = rs.bottom - 8;

		listNotice.MoveWindow(newRect);//����listNotice��λ��
	}   
}

//���ñ�����ɫ
HBRUSH CCG2NoticeInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ѡ��������Ϸ���������з���
void CCG2NoticeInfo::OnBnClickedCheckselectall()
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

// �鿴������Ϣ
void CCG2NoticeInfo::OnBnClickedBtnnoticeinfo()
{
	NoticeInfo();
}

// �鿴������Ϣ
void CCG2NoticeInfo::NoticeInfo()
{
	nItem = -1;
	pageInfo = false;//������Ϣ���ܷ�ҳ
	cmbPage.ResetContent();//������Ϣ��ҳ��ѡ��Ϊ��
	while(listNotice.DeleteColumn(0)){}//ɾ�����й����б���Ϣ
	
	//OperationCG2 theApp.operCG2;	
	try
	{
		char strInt[10];
		int index = theApp.operCG2.ReadIntValue("MCG2","index");//�鿴��һҳ�ļ�¼
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��50����¼
        
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//��������������ҳ����ÿҳ�ļ�¼��

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼��

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SearchNote_Query);//���Ͳ�ѯ������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_NoticeInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// ��ҳ�鿴������Ϣ
void CCG2NoticeInfo::OnCbnSelchangeCmbuipage()
{
	//OperationCG2 theApp.operCG2;
	try
	{
		if(pageInfo)
		{
			while(listNotice.DeleteColumn(0)){}//��������б��е���������
			
			int index = cmbPage.GetCurSel() + 1;//��ҳ�鿴��ҳ��
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��50����¼

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//��������������ҳ����ÿҳ�ļ�¼��
			char strInt[10];

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼��

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SearchNote_Query);//���Ͳ�ѯ������Ϣ������

			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_NoticeInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
}

// ˫��������Ϣ����ɾ��
void CCG2NoticeInfo::OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{
	CIni mIni;
	//OperationCG2 theApp.operCG2;	
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

				NoticeID = theApp.operCG2.GetValueByColName(&listNotice, nItem, theApp.operCG2.ReadValue("MCG2","CG2_NoticeID"));//��ȡ����ID
				ServerIP =theApp.operCG2.GetValueByColName(&listNotice, nItem, theApp.operCG2.ReadValue("MCG2","ServerInfo_IP"));//��ȡ������IP
				DelNotice();
			}
		}
		else
		{
			nItem = -1;
			GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//����ʾ����״̬
			GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);//�÷������б��״̬��ΪEnable		
			SetDlgItemText(IDBTNNOTICE,theApp.operCG2.ReadValue("MCG2","NI_UI_AddNotice"));
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// ���ͻ�༭����
void CCG2NoticeInfo::OnBnClickedBtnnotice()
{
	//OperationCG2 theApp.operCG2;
	try
	{
		UpdateData(true);

		CString NoticeOp = "";
		GetDlgItemText(IDBTNNOTICE, NoticeOp);

		if(NoticeOp == theApp.operCG2.ReadValue("MCG2","NI_UI_AddNotice"))//�����ťΪ��ӹ���
		{
			AddNotice();//��ӹ���
		}
		else if(NoticeOp == theApp.operCG2.ReadValue("MCG2","NI_UI_EditNotice"))//�����ťΪ�༭����
		{
			EditNotice();//�༭����
		}
	}
	catch(...)
	{
	}
}

// �Ƿ��͹���
void CCG2NoticeInfo::OnBnClickedCheckimme()
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
void CCG2NoticeInfo::AddNotice()
{
	//OperationCG2 theApp.operCG2;	
	try
	{		
		CIni mIni;

		UpdateData(true);

		int iTypeID=0;
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
			MessageBox(theApp.operCG2.ReadValue("MCG2","NI_Warn_ServerListNull"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
			return;
		}

		CString NoticeContent = "";
		GetDlgItemText(IDC_EDITCONTENT, NoticeContent);//��ȡ��������

		if(NoticeContent == "")//�������ݲ���Ϊ��
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","NI_Warn_ContentNotNull"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
			return;
		}

		if(strlen(NoticeContent) >= 256)//�������ݲ��ܳ���256���ַ�
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","NI_Warn_ContentTooLong"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
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

		CString strBeginTime = beginTime.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��
		CString strEndTime = toTime.Format("%Y-%m-%d %H:%M:%S");//���ý���ʱ��

		int interval = GetDlgItemInt(IDC_EDITINTERVAL);//��ȡʱ����

		if(checkSendImme.GetCheck() == 1)//�������������
		{
			interval = 0;//ʱ����Ϊ0
			iTypeID=0;
		}
		else//���������������
		{
			iTypeID=1;
			if(toTime <= curTime)//����ʱ�䲻��С�ڵ�ǰʱ��
			{
				MessageBox(theApp.operCG2.ReadValue("MCG2","NI_Warn_StartTime"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
				return;
			}

			if(toTime <= beginTime)//����ʱ�䲻��С�ڿ�ʼʱ��
			{
				MessageBox(theApp.operCG2.ReadValue("MCG2","NI_Warn_TimeSpan"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
				return;
			}
			if(interval <= 0)//ʱ�����������0
			{
				MessageBox(theApp.operCG2.ReadValue("MCG2","NI_Warn_Interval"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
				return;
			}
		}

		CString strMsg = theApp.operCG2.ReadValue("MCG2","NI_Hint_AddNotice"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //��ʾ����Ƿ�ȷ��Ҫ��ӹ���
		{
			return;
		}

		CSocketData socketdata;
		char strInt[10];
		socketdata.InitCreate(1,15);//�����߸���������ʼʱ�䡢����ʱ�䡢ʱ�������������ݡ�����IP������ԱID��������IP

		socketdata.AddTFLV(CEnumCore::TagName::CG2_StartTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::CG2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//����ʱ��

		_itoa(interval,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Interval,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ʱ����

		_itoa(iTypeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_TypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�Ƿ�����


		socketdata.AddTFLV(CEnumCore::TagName::CG2_NoteContent,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeContent),(unsigned char *)mIni.wcharToChar(NoticeContent));//��������

		//CString GSServerIP = "255.255.255.255";
		//socketdata.AddTFLV(CEnumCore::TagName::CG22_GSServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(GSServerIP),(unsigned char *)mIni.wcharToChar(GSServerIP));//����IP

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		if(AllServer)
		{
			ServerIP = ReturnServerIP();
			ServerName=ReturnServerName();
		}
		else
		{
			ServerIP = ReturnServerIP();
			ServerName=ReturnServerName();
		}
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP

		socketdata.AddTFLV(CEnumCore::TagName::CG2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SendNote_Query);//������ӹ��������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�������
		socketdata.Destroy();
	}
	catch(...)
	{
	}	
}

//�༭����
void CCG2NoticeInfo::EditNotice()
{
	//OperationCG2 theApp.operCG2;	
	try
	{		
		CIni mIni;

		UpdateData(true);

		CString strStatus = "";
		GetDlgItemText(IDC_CMBSTATUS, strStatus);//��ȡ����״̬
		if(strStatus == "")//����״̬����Ϊ��
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","NI_Warn_StatusNotNull"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
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
				MessageBox(theApp.operCG2.ReadValue("MCG2","NI_Warn_ContentNotNull"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
				return;
			}

			if(strlen(NoticeContent) >= 256)//�������ݲ��ܳ���256���ַ�
			{
				MessageBox(theApp.operCG2.ReadValue("MCG2","NI_Warn_ContentTooLong"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
				return;
			}

			if(toTime <= curTime)//����ʱ�䲻��С�ڵ�ǰʱ��
			{
				MessageBox(theApp.operCG2.ReadValue("MCG2","NI_Warn_StartTime"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
				return;
			}

			if(toTime <= beginTime)//����ʱ�䲻��С�ڿ�ʼʱ��
			{
				MessageBox(theApp.operCG2.ReadValue("MCG2","NI_Warn_TimeSpan"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
				return;
			}

			if(interval <= 0)//ʱ����Ҫ����0
			{
				MessageBox(theApp.operCG2.ReadValue("MCG2","NI_Warn_Interval"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
				return;
			}
		}

		CString strMsg = theApp.operCG2.ReadValue("MCG2","NI_Hint_EditNotice"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //��ʾ�Ƿ�༭����
		{
			return;
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//����9����������ʼʱ�䡢����ʱ�䡢ʱ�������������ݡ�����IP������ԱID������״̬������ID��������IP
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//����ʱ��

	//	_itoa(interval,strInt,10);
//		socketdata.AddTFLV(CEnumCore::TagName::CG22_Interval,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ʱ����
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Content,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeContent),(unsigned char *)mIni.wcharToChar(NoticeContent));//��������

	//	CString GSServerIP = "255.255.255.255";
//		socketdata.AddTFLV(CEnumCore::TagName::CG22_GSServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(GSServerIP),(unsigned char *)mIni.wcharToChar(GSServerIP));//����IP

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		_itoa(cmbStatus.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Status,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����״̬

		socketdata.AddTFLV(CEnumCore::TagName::CG2_NoticeID,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeID),(unsigned char *)mIni.wcharToChar(NoticeID));//����ID

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_UpdateNote_Query);//���ͱ༭���������

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�������
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}
//ɾ������
void CCG2NoticeInfo::DelNotice()
{
	//OperationCG2 theApp.operCG2;	
	try
	{		
		CIni mIni;

		CString strMsg = theApp.operCG2.ReadValue("MCG2","NI_Hint_DelNotice"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //��ʾ�Ƿ�༭����
		{
			return;
		}
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//����9����������ʼʱ�䡢����ʱ�䡢ʱ�������������ݡ�����IP������ԱID������״̬������ID��������IP
		char strInt[10];

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID


		socketdata.AddTFLV(CEnumCore::TagName::CG2_NoticeID,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeID),(unsigned char *)mIni.wcharToChar(NoticeID));//����ID

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_DeleteNote_Query);//���ͱ༭���������

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�������
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//����Ҫ���͹������Ϸ������IP�б�
CString  CCG2NoticeInfo::ReturnServerIP()
{
	//OperationCG2 theApp.operCG2;
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
//����Ҫ���͹������Ϸ�����������б�
CString  CCG2NoticeInfo::ReturnServerName()
{
	//OperationCG2 theApp.operCG2;
	CString rServerName = "";
	CString serverName = "";
	for(int i=0;i<listResult.GetItemCount();i++)
	{
		if(listResult.GetCheck(i))
		{
			serverName=listResult.GetItemText(i,0);
			rServerName += serverName;
			rServerName += "|";//�����еķ�����IP��"|"����
		}
	}
	return rServerName;
}

// ������Ϣ
void CCG2NoticeInfo::OnBnClickedBtnreset()
{
	//OperationCG2 theApp.operCG2;
	try
	{
		CTime curTime = CTime::GetCurrentTime();//��ȡ��ǰʱ��
		dtcStartDate.SetTime(&curTime);
		dtcStartTime.SetTime(&curTime);
		dtcEndDate.SetTime(&curTime);
		dtcEndTime.SetTime(&curTime);
		SetDlgItemText(IDC_EDITINTERVAL,"60");//����ʱ����Ϊ60
		SetDlgItemText(IDC_EDITCONTENT,"");//���ù�������Ϊ��
		GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//���ع���״̬
		GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);//��ʾ��������
		GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);
		cmbStatus.SetCurSel(0);
		checkSendImme.SetCheck(0);
		SetDlgItemText(IDBTNNOTICE,theApp.operCG2.ReadValue("MCG2","NI_UI_AddNotice"));
	}
	catch(...)
	{
	}
}

// ���շ�����Ϣ
LRESULT CCG2NoticeInfo::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);//���������洦�����

	GetDlgItem(IDC_DTPSTARTDATE)->EnableWindow(true);
	GetDlgItem(IDC_DTPSTARTTIME)->EnableWindow(true);
	GetDlgItem(IDC_DTPENDDATE)->EnableWindow(true);
	GetDlgItem(IDC_DTPENDTIME)->EnableWindow(true);
	GetDlgItem(IDC_EDITINTERVAL)->EnableWindow(true);

	unsigned char* lpReceive=(unsigned char*)wParam;
	int bodyLength = (int)lParam;

	//OperationCG2 theApp.operCG2;
	CIni mIni;

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Receive");//��ǰ��״̬Ϊ���յ�������Ϣ

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
				MessageBox((LPCSTR)&m_tflv.lpdata,theApp.operCG2.ReadValue("MCG2","Error"),0);
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
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_SearchNote_Query_Resp://������յ����ǹ����б�����ķ�����Ϣ
		{
			if(pageInfo)//�Ѿ����Է�ҳ
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listNotice,&pageCount);//���칫���б���Ϣ
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listNotice,&pageCount);//���칫���б���Ϣ

				if(pageCount<=0)//���ҳ��������0
				{
					pageInfo = false;//��������б���Ϣ
					nItem = -1;
					cmbPage.ResetContent();
					while(listNotice.DeleteColumn(0)){}
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
	case CEnumCore::Message_Tag_ID::CG2_SendNote_Query_Resp://������յ�������ӹ�������ķ�����Ϣ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//��ʾ��ӹ���Ľ��
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
			SetDlgItemText(IDBTNNOTICE,theApp.operCG2.ReadValue("MCG2","NI_UI_AddNotice"));
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_UpdateNote_Query_Resp://������յ����Ǳ༭��������ķ�����Ϣ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//��ʾ�༭����Ľ��
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
			SetDlgItemText(IDBTNNOTICE,theApp.operCG2.ReadValue("MCG2","NI_UI_AddNotice"));
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_DeleteNote_Query_Resp://������յ�����ɾ������
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//��ʾɾ������Ľ��
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
			SetDlgItemText(IDBTNNOTICE,theApp.operCG2.ReadValue("MCG2","NI_UI_AddNotice"));
		}
		break;
	default:
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

// �رնԻ���
void CCG2NoticeInfo::OnClose()
{
	//OperationCG2 theApp.operCG2;
	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Close");//�رմ���
	DestroyWindow();
	CDialog::OnClose();
}
