// GTOWNNoticeInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_GTOWN.h"
#include "GTOWNNoticeInfo.h"
#include ".\gtownnoticeinfo.h"


// CGTOWNNoticeInfo �Ի���

IMPLEMENT_DYNAMIC(CGTOWNNoticeInfo, CDialog)
CGTOWNNoticeInfo::CGTOWNNoticeInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CGTOWNNoticeInfo::IDD, pParent)
{
}

CGTOWNNoticeInfo::~CGTOWNNoticeInfo()
{
}

void CGTOWNNoticeInfo::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CGTOWNNoticeInfo, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECKSELECTALL, OnBnClickedCheckselectall)
	ON_BN_CLICKED(IDC_BTNNOTICEINFO, OnBnClickedBtnnoticeinfo)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTNOTICE, OnNMDblclkListnotice)
	ON_BN_CLICKED(IDBTNNOTICE, OnBnClickedBtnnotice)
	ON_BN_CLICKED(IDC_CHECKIMME, OnBnClickedCheckimme)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTNOTICE, OnLvnColumnclickListnotice)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDBTNRESET, OnBnClickedBtnreset)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
END_MESSAGE_MAP()


// CGTOWNNoticeInfo ��Ϣ�������

//��ʼ���Ի���
BOOL CGTOWNNoticeInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitUI();

	dtcStartTime.SetFormat("HH:mm:ss");
	dtcEndTime.SetFormat("HH:mm:ss");
	
	nItem = 0;// ���������б�õ��к�
	pageInfo = false;// �ж��Ƿ���Ҫ��ҳ
	addOrEdit = false;// ���͹���
	ServerIP = "";// ������IP
	NoticeID = 0;// ����ID	
	AllServer = false;// �Ƿ������д������͹���
	NoticeType=0;

	//OperationPAL operPAL;

	cmbStatus.ResetContent();
	cmbStatus.AddString(theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_UnSend"));//δ����
	cmbStatus.AddString(theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_Sended"));//�ѷ���
	cmbStatus.SetCurSel(0);

	GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//���ع���״̬
	GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);

	listServer.SetExtendedStyle(listServer.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);//�������б�����Ҫ��ʾCheckBox
	listServer.InsertColumn(0,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_ServerList"),LVCFMT_CENTER,150,-1);

	SetProp(listNotice.GetSafeHwnd(),"�����к�",(HANDLE)0);
    SetProp(listNotice.GetSafeHwnd(),"����˳��",(HANDLE)1);

	CRect rs;
	GetClientRect(rs);; //��ȡ�Ի���Ĵ�С��Ϣ

	CRect srcRect;
	CRect newRect;

	if( listServer.m_hWnd != NULL )   
	{
		listServer.GetWindowRect(srcRect);//��ȡlistResult�Ĵ�С��Ϣ
		listRWidth = srcRect.right - srcRect.left;//�õ�listResult�Ŀ����Ϣ

		newRect.top = rs.top + 45;		
		newRect.left = rs.left + 10;
		newRect.right = newRect.left + listRWidth;
		newRect.bottom = rs.bottom - 8;

		listServer.MoveWindow(newRect);//����listResult��λ��
	}  

	CWnd* pWnd = GetDlgItem(IDC_EDITCONTENT);  
	if( pWnd )   
	{
		pWnd->GetWindowRect(srcRect);//��ȡ��������CEdit�Ĵ�С��Ϣ
		contentLength = srcRect.bottom - srcRect.top;//��ȡ��������CEdit�ĸ߶���Ϣ

		newRect.top = rs.top + 117;		
		newRect.left = newRect.right + 110;
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

	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	if(theApp.operGTOWN.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CGTOWNNoticeInfo::InitUI()
{
	SetWindowText(theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_NoticeInfo"));

	SetDlgItemText(IDC_CHECKSELECTALL,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_SelectAll"));

	SetDlgItemText(IDC_BTNNOTICEINFO,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_NoticeCheck"));
	SetDlgItemText(IDC_LBLHINT,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_NoticeHint"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operGTOWN.ReadValue("MGTOWN","BU_UI_LblPage"));

	SetDlgItemText(IDC_LBLSTARTTIME,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_EndTime"));
	SetDlgItemText(IDC_LBLINTERVAL,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_TimeInterval"));
	SetDlgItemText(IDC_LBLTIME,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_Minite"));	
	SetDlgItemText(IDC_LBLCONTENT,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_SendContent"));
	SetDlgItemText(IDC_CHECKIMME,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_SendImme"));
	SetDlgItemText(IDC_LBLSTATUS,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_NoticeStatus"));
	SetDlgItemText(IDBTNNOTICE,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_AddNotice"));
	SetDlgItemText(IDBTNRESET,theApp.operGTOWN.ReadValue("MGTOWN","Reset"));
}

//�����ݼ���Ӧ
BOOL CGTOWNNoticeInfo::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listServer.m_hWnd)
				{
					theApp.operGTOWN.CopyListInfo(&listServer);				
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

//�Զ��ı��С
void CGTOWNNoticeInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rs;
	GetClientRect(rs);

	CRect newRect;

	if( listServer.m_hWnd != NULL )   
	{
		newRect.top = rs.top + 45;		
		newRect.left = rs.left + 10;
		newRect.right = newRect.left + listRWidth;
		newRect.bottom = rs.bottom - 10;

		listServer.MoveWindow(newRect);//����listResult��λ��
	}  

	CWnd* pWnd = GetDlgItem(IDC_EDITCONTENT);  
	if( pWnd )   
	{
		newRect.top = rs.top + 117;		
		newRect.left = newRect.right + 81;
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
HBRUSH CGTOWNNoticeInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//ѡ�����з���������
void CGTOWNNoticeInfo::OnBnClickedCheckselectall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(AllServer == false)
	{
		for(int i=0; i<listServer.GetItemCount(); i++)
		{
			listServer.SetCheck(i);//ѡ�����е���Ϸ������
		}
		listServer.EnableWindow(true);//����Ϸ�������б��ΪDisable��״̬
		AllServer = true;
	}
	else
	{
		for(int i=0; i<listServer.GetItemCount(); i++)
		{
			listServer.SetCheck(i,false);//ȡ��ѡ�����е���Ϸ������
		}
		//listResult.EnableWindow(true);//����Ϸ�������б��ΪEnable��״̬
		AllServer = false;
	}
}

//�鿴������Ϣ
void CGTOWNNoticeInfo::OnBnClickedBtnnoticeinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NoticeInfo();
}

void CGTOWNNoticeInfo::NoticeInfo()
{
	nItem = 0;
	pageInfo = false;//������Ϣ���ܷ�ҳ
	cmbPage.ResetContent();//������Ϣ��ҳ��ѡ��Ϊ��
	while(listNotice.DeleteColumn(0)){}//ɾ�����й����б���Ϣ
	CIni mIni;

	CString serverIP;
	int iSelect=0;
	for(int i=0;i<listServer.GetItemCount();i++)
	{
		if(listServer.GetCheck(i))
		{
			iSelect++;
			if(iSelect==2)
			{
				MessageBox("ֻ��ѡ��һ������");
				return ;
			}
			ServerList.Lookup(i+1,serverIP);//���ҷ�����IP
		}
	}
	if(iSelect==0)
	{
		MessageBox("ѡ��һ������");
		return ;
	}
	//OperationPAL operPAL;	
	try
	{
		char strInt[10];
		int index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");//�鿴��һҳ�ļ�¼
		int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//ÿҳ��50����¼


        
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//��������������ҳ����ÿҳ�ļ�¼��


		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(serverIP),(unsigned char *)mIni.wcharToChar(serverIP));//������IP

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼��

		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_BROADCAST_SELECT))//���Ͳ�ѯ������Ϣ������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_NoticeInfo"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}	
}

//��ҳ�鿴������Ϣ
void CGTOWNNoticeInfo::OnCbnSelchangeCmbpage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		if(pageInfo)
		{
			CString serverIP;
			int iSelect=0;
			CIni mIni;
			for(int i=0;i<listServer.GetItemCount();i++)
			{
				if(listServer.GetCheck(i))
				{
					iSelect++;
					if(iSelect==2)
					{
						MessageBox("ֻ��ѡ��һ������");
						return ;
					}
					ServerList.Lookup(i+1,serverIP);//���ҷ�����IP
				}
			}
			if(iSelect==0)
			{
				MessageBox("ѡ��һ������");
				return ;
			}

			while(listNotice.DeleteColumn(0)){}//��������б��е���������
			
			int index = cmbPage.GetCurSel() + 1;//��ҳ�鿴��ҳ��
			int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//ÿҳ��50����¼

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//��������������ҳ����ÿҳ�ļ�¼��
			char strInt[10];
			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(serverIP),(unsigned char *)mIni.wcharToChar(serverIP));//������IP

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼��

			int midlength = socketdata.EnBody();
			if(theApp.operGTOWN.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_BROADCAST_SELECT))//���Ͳ�ѯ������Ϣ������
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_NoticeInfo"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}
}

// ˫��������Ϣ����ɾ������///maple add
void CGTOWNNoticeInfo::OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIni mIni;
	//OperationPAL operPAL;	
	try
	{
		if(listNotice.GetItemCount() > 0)//��������б��е�ǰ�м�¼
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
				NoticeID = atoi(theApp.operGTOWN.GetValueByColName(&listNotice, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_NoticeID")));//��ȡ����ID

				CString startTime = theApp.operGTOWN.GetValueByColName(&listNotice, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_StartTime"));//��ȡ��ʼʱ��
				CString endTime = theApp.operGTOWN.GetValueByColName(&listNotice, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_EndTime"));//��ȡ����ʱ��

/*				int nYear, nMonth, nDate, nHour, nMin, nSec;  
				sscanf(startTime, "%d-%d-%d  %d:%d:%d", &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);  
				CTime sTime(nYear, nMonth, nDate, nHour, nMin, nSec); //����ʼʱ���ΪCTime����

				dtcStartDate.SetTime(&sTime);
				dtcStartTime.SetTime(&sTime);

				sscanf(endTime, "%d-%d-%d  %d:%d:%d", &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);  
				CTime eTime(nYear, nMonth, nDate, nHour, nMin, nSec); //������ʱ���ΪCTime����

				dtcEndDate.SetTime(&eTime);//���ÿ�ʼʱ��
				dtcEndTime.SetTime(&eTime);//���ý���ʱ��

				SetDlgItemText(IDC_EDITINTERVAL,theApp.operGTOWN.GetValueByColName(&listNotice, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Interval")));//��ȡʱ����������
				SetDlgItemText(IDC_EDITCONTENT,theApp.operGTOWN.GetValueByColName(&listNotice, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_BoardMessage")));//��ȡ�������ݲ�����

				ServerIP = theApp.operGTOWN.GetValueByColName(&listNotice, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_ServerIP"));//��ȡ������IP

				SetDlgItemText(IDBTNNOTICE,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_EditNotice"));

				GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_SHOW);//��ʾ����״̬
				GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_HIDE);//����ʾ�������͹����CheckBox

				GetDlgItem(IDC_LISTSERVER)->EnableWindow(false);//�÷������б��״̬��ΪDisable*/
				DelNotice();
			}
		}
		else
		{
			nItem = 0;
			GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//����ʾ����״̬
			GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);//�÷������б��״̬��ΪEnable		
			SetDlgItemText(IDBTNNOTICE,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_AddNotice"));
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

//ɾ������///maple add
void CGTOWNNoticeInfo::DelNotice()
{
	try
	{
		CIni mIni;

		UpdateData(true);
		CString strMsg = theApp.operGTOWN.ReadValue("MGTOWN","NI_Hint_DelNotice");//operCG2.ReadValue("MCG2","NI_Hint_DelNotice"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //��ʾ�Ƿ�༭����
		{
			return;
		}
		CString serverIP;
		int iSelect=0;
		for(int i=0;i<listServer.GetItemCount();i++)
		{
			if(listServer.GetCheck(i))
			{
				iSelect++;
				if(iSelect==2)
				{
					MessageBox("ֻ��ѡ��һ������");
					return ;
				}
				ServerList.Lookup(i+1,serverIP);//���ҷ�����IP
			}
		}
		
		
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//����9����������ʼʱ�䡢����ʱ�䡢ʱ�������������ݡ�����IP������ԱID������״̬������ID��������IP
		char strInt[10];

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		_itoa(NoticeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_NoticeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID




		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(serverIP),(unsigned char *)mIni.wcharToChar(serverIP));//������IP


		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_BROADCAST_REMOVE))//����ɾ�����������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//���ͻ�༭����
void CGTOWNNoticeInfo::OnBnClickedBtnnotice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		UpdateData(true);

		CString NoticeOp = "";
		GetDlgItemText(IDBTNNOTICE, NoticeOp);

		if(NoticeOp == theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_AddNotice"))//�����ťΪ��ӹ���
		{
			AddNotice();//��ӹ���
		}
		else if(NoticeOp == theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_EditNotice"))//�����ťΪ�༭����
		{
			EditNotice();//�༭����
		}
	}
	catch(...)
	{
	}
}

//�Ƿ���������
void CGTOWNNoticeInfo::OnBnClickedCheckimme()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
void CGTOWNNoticeInfo::AddNotice()
{
	try
	{		
		CIni mIni;

		UpdateData(true);

		int svrCheck = 0;
		for(int i=0;i<listServer.GetItemCount();i++)
		{
			if(listServer.GetCheck(i))//�鿴��û��ѡ�е�ǰ����Ϸ������
			{
				svrCheck++;
			}
		}
		if(svrCheck == 0)//���͹���ʱ����Ϸ����������Ϊ��
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","NI_Warn_ServerListNull"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
			return;
		}

		CString NoticeContent = "";
		GetDlgItemText(IDC_EDITCONTENT, NoticeContent);//��ȡ��������

		if(NoticeContent == "")//�������ݲ���Ϊ��
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","NI_Warn_ContentNotNull"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
			return;
		}

		if(strlen(NoticeContent) >= 256)//�������ݲ��ܳ���256���ַ�
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","NI_Warn_ContentTooLong"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
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
		interval=interval*60;


		if(checkSendImme.GetCheck() == 1)//�������������
		{
			interval = 0;//ʱ����Ϊ0
			NoticeType=1;//��ʱ����
		}
		else//���������������
		{
			if(toTime <= curTime)//����ʱ�䲻��С�ڵ�ǰʱ��
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","NI_Warn_StartTime"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
				return;
			}
			if(toTime <= beginTime)//����ʱ�䲻��С�ڿ�ʼʱ��
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","NI_Warn_TimeSpan"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
				return;
			}
			if(interval <= 0)//ʱ�����������0
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","NI_Warn_IntervalNull"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
				return;
			}
			CTimeSpan sTimeSpan = toTime - beginTime;
			if(interval/60 >= sTimeSpan.GetTotalMinutes())//ʱ����������ʱ�䷶Χ֮��
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","NI_Warn_IntervalLong"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
				return;
			}
			NoticeType=0;//��ʱ����
		}

		CString strMsg = theApp.operGTOWN.ReadValue("MGTOWN","NI_Hint_AddNotice"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //��ʾ����Ƿ�ȷ��Ҫ��ӹ���
		{
			return;
		}

		CSocketData socketdata;
		char strInt[10];
		socketdata.InitCreate(1,10);//�����߸���������ʼʱ�䡢����ʱ�䡢ʱ�������������ݡ�����ԱID��������IP������������

		socketdata.AddTFLV(CEnumCore::TagName::GT_StartTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::GT_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//����ʱ��

		_itoa(interval,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_Interval,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ʱ����
		socketdata.AddTFLV(CEnumCore::TagName::GT_BoardMessage,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeContent),(unsigned char *)mIni.wcharToChar(NoticeContent));//��������

		//CString GSServerIP = "255.255.255.255";
		//socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(GSServerIP),(unsigned char *)mIni.wcharToChar(GSServerIP));//����IP
		
		_itoa(NoticeType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_IsImmediate,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�����Ǽ�ʱ���Ƕ�ʱ

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		CString strServerIP;
		if(AllServer)
		{
			strServerIP=ReturnServerIP();
			ServerName=ReturnServerName();
		}
		else
		{
			strServerIP=ReturnServerIP();
			ServerName=ReturnServerName();
		}

		int strlength=strlen(ServerName);
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(strServerIP),(unsigned char *)mIni.wcharToChar(strServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������IP)

		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_BROADCAST_ADD))//������ӹ��������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}	
}

//�༭����
void CGTOWNNoticeInfo::EditNotice()
{
	try
	{		
		CIni mIni;

		UpdateData(true);

		CString strStatus = "";
		GetDlgItemText(IDC_CMBSTATUS, strStatus);//��ȡ����״̬
		if(strStatus == "")//����״̬����Ϊ��
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","NI_Warn_StatusNotNull"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
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

		CString strBeginTime = beginTime.Format("%Y-%m-%d %H:%M:%S");//��ȡ��ʼʱ��
		CString strEndTime = toTime.Format("%Y-%m-%d %H:%M:%S");//��ȡ����ʱ��

		int interval = GetDlgItemInt(IDC_EDITINTERVAL);//��ȡʱ����

		if(cmbStatus.GetCurSel() == 1)//���ѡ��Ĺ���״̬���ѷ��ͣ����еĲ��������Բ�������
		{
		}
		else//���ѡ�����δ���ͣ�Ҫ����һЩ����
		{
			if(NoticeContent == "")//�������ݲ���Ϊ��
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","NI_Warn_ContentNotNull"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
				return;
			}

			if(strlen(NoticeContent) >= 256)//�������ݲ��ܳ���256���ַ�
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","NI_Warn_ContentTooLong"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
				return;
			}

			if(toTime <= curTime)//����ʱ�䲻��С�ڵ�ǰʱ��
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","NI_Warn_StartTime"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
				return;
			}

			if(toTime <= beginTime)//����ʱ�䲻��С�ڿ�ʼʱ��
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","NI_Warn_TimeSpan"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
				return;
			}

			if(interval <= 0)//ʱ�����������0
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","NI_Warn_IntervalNull"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
				return;
			}

			CTimeSpan sTimeSpan = toTime - beginTime;
			if(interval >= sTimeSpan.GetTotalMinutes())//ʱ����������ʱ�䷶Χ֮��
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","NI_Warn_IntervalLong"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
				return;
			}
		}

		CString strMsg = theApp.operGTOWN.ReadValue("MGTOWN","NI_Hint_EditNotice"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //��ʾ�Ƿ�༭����
		{
			return;
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,15);//����9����������ʼʱ�䡢����ʱ�䡢ʱ�������������ݡ�����IP������ԱID������״̬������ID��������IP
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_StartTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::GT_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//����ʱ��

		_itoa(interval,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_Interval,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ʱ����
		socketdata.AddTFLV(CEnumCore::TagName::GT_BoardMessage,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeContent),(unsigned char *)mIni.wcharToChar(NoticeContent));//��������

		//CString GSServerIP = "255.255.255.255";
		//socketdata.AddTFLV(CEnumCore::TagName::PAL2_GSServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(GSServerIP),(unsigned char *)mIni.wcharToChar(GSServerIP));//����IP

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		_itoa(cmbStatus.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_STATUS,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����״̬

		_itoa(NoticeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_TASKID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP

		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_BOARDTASK_UPDATE))//���ͱ༭���������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//����Ҫ���͹������Ϸ�������б�
CString  CGTOWNNoticeInfo::ReturnServerIP()
{
	CString rServerIP = "";
	CString serverIP = "";
	for(int i=0;i<listServer.GetItemCount();i++)
	{
		if(listServer.GetCheck(i))
		{
			ServerList.Lookup(i+1,serverIP);//���ҷ�����IP
			rServerIP += serverIP;
			rServerIP += "|";//�����еķ�����IP��","����
		}
	}
	return rServerIP;
	/*CString serverName="";
	for(int i=0;i<listServer.GetItemCount();i++)
	{
		if(listServer.GetCheck(i))
		{
			ServerList.Lookup(i+1,serverName);//���ҷ�����IP
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
	sprintf(allServerIP,"%s,",allServerIP);*/

}

//����Ҫ���͹������Ϸ�����������б�
CString CGTOWNNoticeInfo::ReturnServerName()
{
	CString rServerName = "";
	CString serverName = "";
	for(int i=0;i<listServer.GetItemCount();i++)
	{
		if(listServer.GetCheck(i))
		{
			serverName=listServer.GetItemText(i,0);//���ҷ���������
			rServerName += serverName;
			rServerName += "|";//�����еķ�����IP��","����
		}
	}
	return rServerName;
}

//����������Ϸ�������б�
CString  CGTOWNNoticeInfo::ReturnAllServerIP()
{
	//OperationPAL operPAL;
	CString rServerIP = "";
	CString serverName = "";
	for(int i=0;i<listServer.GetItemCount();i++)
	{
		ServerList.Lookup(i+1,serverName);//���ҷ�����IP
		rServerIP += serverName;
		rServerIP += ",";//�����еķ�����IP��","����
	}
	return rServerIP;
}

void CGTOWNNoticeInfo::ReturnAllServerIP(char* allServerIP)
{
	CString serverName="";
	for(int i=0;i<listServer.GetItemCount();i++)
	{
		ServerList.Lookup(i+1,serverName);//���ҷ�����IP
		if(i==0)
		{
			
			sprintf(allServerIP,"%s",serverName);
		}
		else
		{
			sprintf(allServerIP,"%s,%s",allServerIP,serverName);
		}
	}
	sprintf(allServerIP,"%s,",allServerIP);

}
//����������Ϸ�����������б�
CString CGTOWNNoticeInfo::ReturnAllServerName()
{
	CString rServerName = "";
	CString serverName = "";
	for(int i=0;i<listServer.GetItemCount();i++)
	{
		serverName=listServer.GetItemText(i,0);//���ҷ���������
		rServerName += serverName;
		rServerName += ",";//�����еķ�����IP��","����
	}
	return rServerName;
}
//������Ϣ
void CGTOWNNoticeInfo::OnBnClickedBtnreset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		SetDlgItemText(IDBTNNOTICE,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_AddNotice"));
	}
	catch(...)
	{
	}
}

// ���շ�����Ϣ
LRESULT CGTOWNNoticeInfo::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_DTPSTARTDATE)->EnableWindow(true);
	GetDlgItem(IDC_DTPSTARTTIME)->EnableWindow(true);
	GetDlgItem(IDC_DTPENDDATE)->EnableWindow(true);
	GetDlgItem(IDC_DTPENDTIME)->EnableWindow(true);
	GetDlgItem(IDC_EDITINTERVAL)->EnableWindow(true);

	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;
	//OperationPAL operPAL;	

	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","Main_UI_ParseData"),theApp.operGTOWN.ReadValue("MGTOWN","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	int pageCount = 0;

	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��ѯ�������б���Ϣ�Ļ�Ӧ
		{
			listServer.EnableWindow(true);

			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);//��ȡ������Ϣ�еĵ�һ��ģ��
			if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)//�����һ��ģ���TagName��MESSAGE����ʾ�����˴�����Ϣ����ʾ������Ϣ������
			{
				MessageBox((LPCSTR)&m_tflv.lpdata,theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
				socketdata.Destroy();
				return false;
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//��ȡ���еķ�����IP
				ServerList.SetAt(i,ServerIP);//��ӵ�CMap��Ķ���ServerList��
			}

			listServer.DeleteAllItems();//����������б��е���������
			CString serverName = "";
			int nRow = 0;
			for(int i=0;i<socketdata.getQueryNum();i++)
			{
				nRow = listServer.InsertItem(i,"");
				serverName = (LPSTR)&socketdata.getTLVByName(i+1,CEnumCore::TagName::ServerInfo_City).lpdata;//��ȡ��Ϸ����������
				listServer.SetItemText(nRow,0,serverName);//����Ϸ������������ӵ��������б���
			}

			
		}
		break;
		////������յ����ǹ����б�����ķ�����Ϣ///�����ѯ
	case CEnumCore::Message_Tag_ID::GT_BROADCAST_SELECT_ACK:
		{
			if(pageInfo)//�Ѿ����Է�ҳ
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listNotice,&pageCount);//���칫���б���Ϣ
			}
			else
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listNotice,&pageCount);//���칫���б���Ϣ

				if(pageCount<=0)//���ҳ��������0
				{
					pageInfo = false;//��������б���Ϣ
					nItem = 0;
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
		//������յ�������ӹ�������ķ�����Ϣ
	case CEnumCore::Message_Tag_ID::GT_BROADCAST_ADD_ACK:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operGTOWN.ShowResult(result);//��ʾ��ӹ���Ľ��
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
			SetDlgItemText(IDBTNNOTICE,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_AddNotice"));
		}
		break;
		//������ܵ�����ɾ������ķ���
	case CEnumCore::Message_Tag_ID::GT_BROADCAST_REMOVE_ACK:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operGTOWN.ShowResult(result);//��ʾ��ӹ���Ľ��
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
			SetDlgItemText(IDBTNNOTICE,theApp.operGTOWN.ReadValue("MGTOWN","NI_UI_AddNotice"));
		}
	default:
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return FALSE;
}

//����������Ϣ�н�������
void CGTOWNNoticeInfo::OnLvnColumnclickListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operGTOWN.SortListInfo(&listNotice,pNMHDR,pResult);
}

//�رնԻ���
void CGTOWNNoticeInfo::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Close");//�رմ���
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}


