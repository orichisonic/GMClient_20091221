// JW2NoticeInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_JW2.h"
#include "JW2NoticeInfo.h"
#include ".\JW2NoticeInfo.h"


// CJW2NoticeInfo �Ի���

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

// ��ʼ���Ի���
BOOL CJW2NoticeInfo::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();

	dtcStartTime.SetFormat("HH:mm:ss");
	dtcEndTime.SetFormat("HH:mm:ss");
	
	nItem = -1;// ���������б�õ��к�
	pageInfo = false;// �ж��Ƿ���Ҫ��ҳ
	addOrEdit = false;// ���͹���
	ServerIP = "";// ������IP
	NoticeID = 0;// ����ID	
	AllServer = false;// �Ƿ������д������͹���


	cmbStatus.ResetContent();
	cmbStatus.AddString(theApp.operJW2.ReadValue("MJW2","NI_UI_UnSend"));//δ����
	cmbStatus.AddString(theApp.operJW2.ReadValue("MJW2","NI_UI_Sended"));//�ѷ���
	cmbStatus.SetCurSel(0);

	GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//���ع���״̬
	GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);

	listResult.SetExtendedStyle(listResult.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);//�������б�����Ҫ��ʾCheckBox
	listResult.InsertColumn(0,theApp.operJW2.ReadValue("MJW2","NI_UI_ServerList"),LVCFMT_CENTER,150,-1);

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

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Create");//��ʼ�����Ի���
	theApp.operJW2.GetServerList();
	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

	return TRUE;
}

// ��ʼ����ʾ�ַ�
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

//�����ݼ���Ӧ����
BOOL CJW2NoticeInfo::PreTranslateMessage(MSG* pMsg)
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
HBRUSH CJW2NoticeInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ѡ��������Ϸ���������з���
void CJW2NoticeInfo::OnBnClickedCheckselectall()
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
void CJW2NoticeInfo::OnBnClickedBtnnoticeinfo()
{
	NoticeInfo();
}

// �鿴������Ϣ
void CJW2NoticeInfo::NoticeInfo()
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
void CJW2NoticeInfo::OnCbnSelchangeCmbuipage()
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
void CJW2NoticeInfo::OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult)
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

// ���ͻ�༭����
void CJW2NoticeInfo::OnBnClickedBtnnotice()
{
	try
	{
		UpdateData(true);

		CString NoticeOp = "";
		GetDlgItemText(IDBTNNOTICE, NoticeOp);

		if(NoticeOp == theApp.operJW2.ReadValue("MJW2","NI_UI_AddNotice"))//�����ťΪ��ӹ���
		{
			AddNotice();//��ӹ���
		}
		else if(NoticeOp == theApp.operJW2.ReadValue("MJW2","NI_UI_EditNotice"))//�����ťΪ�༭����
		{
			EditNotice();//�༭����
		}
	}
	catch(...)
	{
	}
}

// �Ƿ��͹���
void CJW2NoticeInfo::OnBnClickedCheckimme()
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
void CJW2NoticeInfo::AddNotice()
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

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		ServerIP = ReturnServerIP();

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP

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
void CJW2NoticeInfo::EditNotice()
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

//����Ҫ���͹������Ϸ�������б�
CString  CJW2NoticeInfo::ReturnServerIP()
{
	CString rServerIP = "";
	CString serverName = "";
	for(int i=0;i<listResult.GetItemCount();i++)
	{
		if(listResult.GetCheck(i))
		{
			ServerList.Lookup(i+1,serverName);//���ҷ�����IP
			rServerIP += serverName;
			rServerIP += "|";//�����еķ�����IP��","����
		}
	}
	return rServerIP;
}

// ������Ϣ
void CJW2NoticeInfo::OnBnClickedBtnreset()
{
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
		SetDlgItemText(IDBTNNOTICE,theApp.operJW2.ReadValue("MJW2","NI_UI_AddNotice"));
	}
	catch(...)
	{
	}
}

// ���շ�����Ϣ
LRESULT CJW2NoticeInfo::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_BOARDTASK_QUERY_RESP://������յ����ǹ����б�����ķ�����Ϣ
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
	case CEnumCore::Message_Tag_ID::JW2_BOARDTASK_INSERT_RESP://������յ�������ӹ�������ķ�����Ϣ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//��ʾ��ӹ���Ľ��
		//	NoticeInfo();//��ѯ���еĹ�����Ϣ

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
			//NoticeInfo();//��ѯ���еĹ�����Ϣ

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
	default:
		break;
	}

	socketdata.Destroy();
	return false;
}

//����������Ϣ��������������
void CJW2NoticeInfo::OnLvnColumnclickListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{

	theApp.operJW2.SortListInfo(&listNotice,pNMHDR,pResult);
}

// �رնԻ���
void CJW2NoticeInfo::OnClose()
{

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Close");//�رմ���
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
