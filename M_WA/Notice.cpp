// Notice.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_WA.h"
#include "Notice.h"
#include ".\notice.h"


// CNotice �Ի���

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
//ɾ���������
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
		CString strMsg;//="�Ƿ�ȷ��Ҫɾ����ѡ�񹫸�";
		char* message=new char[100];
		sprintf(message,"%s%s%s",theApp.operWA.ReadValue("MWA","NI_Hint_DelNoticeID"),NoticeIDString,theApp.operWA.ReadValue("MWA","NI_Hint_DelNotice"));
		strMsg.Format("%s",message);
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //��ʾ�Ƿ�ɾ������
		{
			return;
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,3);//����2������������ԱID������ID
		char strInt[10];
		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID
		_itoa(NoticeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::WA_TaskID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID
		int midlength = socketdata.EnBody();
		if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BoardTasker_Del))//���ͱ༭���������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}
// ��ʼ���Ի���
BOOL CNotice::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();
	ishaveselect=false;
	dtcStartTime.SetFormat("HH:mm:ss");
	dtcEndTime.SetFormat("HH:mm:ss");

	nItem = 0;// ���������б�õ��к�
	pageInfo = false;// �ж��Ƿ���Ҫ��ҳ
	addOrEdit = false;// ���͹���
	ServerIP = "";// ������IP
	NoticeID = 0;// ����ID	
	AllServer = false;// �Ƿ������д������͹���
	cmbStatus.ResetContent();
	cmbStatus.AddString(theApp.operWA.ReadValue("MWA","NI_UI_UnSend"));//δ����
	cmbStatus.AddString(theApp.operWA.ReadValue("MWA","NI_UI_Sended"));//�ѷ���
	cmbStatus.SetCurSel(0);
	GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//���ع���״̬
	GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
	listResult.SetExtendedStyle(listResult.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);//�������б�����Ҫ��ʾCheckBox
	listResult.InsertColumn(0,theApp.operWA.ReadValue("MWA","NI_UI_ServerList"),LVCFMT_CENTER,150,-1);
	SetProp(listNotice.GetSafeHwnd(),"�����к�",(HANDLE)0);
	SetProp(listNotice.GetSafeHwnd(),"����˳��",(HANDLE)1);
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
	dlgStatus = theApp.operWA.ReadIntValue("MWA","Create");//��ʼ�����Ի���
	if(theApp.operWA.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}

	return TRUE;
}

// ��ʼ����ʾ�ַ�
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

//�����ݼ���Ӧ���� ����A C���ķ�Ӧ
BOOL CNotice::PreTranslateMessage(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
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

// �Զ��ı��С
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
		listResult.MoveWindow(newRect);//����listResult��λ��
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
HBRUSH CNotice::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);
	return CreateSolidBrush(backColor);
}

// ѡ��������Ϸ���������з���
void CNotice::OnBnClickedCheckselectall()
{
	if(AllServer == false)
	{
		for(int i=0; i<listResult.GetItemCount(); i++)
		{
			listResult.SetCheck(i);//ѡ�����е���Ϸ������
		}
		listResult.EnableWindow(true);//����Ϸ�������б��ΪDisable��״̬
		AllServer = true;
	}
	else
	{
		for(int i=0; i<listResult.GetItemCount(); i++)
		{
			listResult.SetCheck(i,false);//ȡ��ѡ�����е���Ϸ������
		}
		//listResult.EnableWindow(true);//����Ϸ�������б��ΪEnable��״̬
		AllServer = false;
	}
}

// �鿴������Ϣ
void CNotice::OnBnClickedBtnnoticeinfo()
{
	NoticeInfo();
}

// �鿴������Ϣ
void CNotice::NoticeInfo()
{
	nItem = 0;
	pageInfo = false;//������Ϣ���ܷ�ҳ
	cmbPage.ResetContent();//������Ϣ��ҳ��ѡ��Ϊ��
	while(listNotice.DeleteColumn(0)){}//ɾ�����й����б���Ϣ
	try
	{
		char strInt[10];
		int index = theApp.operWA.ReadIntValue("MWA","index");//�鿴��һҳ�ļ�¼
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//ÿҳ��50����¼
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//��������������ҳ����ÿҳ�ļ�¼��
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼��
		int midlength = socketdata.EnBody();
		if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BoardTasker_Query))//���Ͳ�ѯ������Ϣ������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","NI_Error_NoticeInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// ��ҳ�鿴������Ϣ
void CNotice::OnCbnSelchangeCmbpage()
{
	try
	{
		if(pageInfo)
		{
			while(listNotice.DeleteColumn(0)){}//��������б��е���������
			int index = cmbPage.GetCurSel() + 1;//��ҳ�鿴��ҳ��
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//ÿҳ��50����¼
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//��������������ҳ����ÿҳ�ļ�¼��
			char strInt[10];
			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼��
			int midlength = socketdata.EnBody();
			if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BoardTasker_Query))//���Ͳ�ѯ������Ϣ������
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","NI_Error_NoticeInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
	}
}

// ˫��������Ϣ���б༭
void CNotice::OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{
	CIni mIni;
	try
	{
		ishaveselect=true;
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
				NoticeID = atoi(theApp.operWA.GetValueByColName(&listNotice, nItem, theApp.operWA.ReadValue("MWA","WA_TaskID")));//��ȡ����ID
				CString startTime = theApp.operWA.GetValueByColName(&listNotice, nItem, theApp.operWA.ReadValue("MWA","WA_BeginTime"));//��ȡ��ʼʱ��
				CString endTime = theApp.operWA.GetValueByColName(&listNotice, nItem, theApp.operWA.ReadValue("MWA","WA_EndTime"));//��ȡ����ʱ��
				int nYear, nMonth, nDate, nHour, nMin, nSec;  
				sscanf(startTime, "%d-%d-%d  %d:%d:%d", &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);  
				CTime sTime(nYear, nMonth, nDate, nHour, nMin, nSec); //����ʼʱ���ΪCTime����
				dtcStartDate.SetTime(&sTime);
				dtcStartTime.SetTime(&sTime);
				sscanf(endTime, "%d-%d-%d  %d:%d:%d", &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);  				
				CTime eTime(nYear, nMonth, nDate, nHour, nMin, nSec); //������ʱ���ΪCTime����
				dtcEndDate.SetTime(&eTime);//���ÿ�ʼʱ��
				dtcEndTime.SetTime(&eTime);//���ý���ʱ��
				SetDlgItemText(IDC_EDITINTERVAL,theApp.operWA.GetValueByColName(&listNotice, nItem, theApp.operWA.ReadValue("MWA","WA_Interval")));//��ȡʱ����������
				SetDlgItemText(IDC_EDITCONTENT,theApp.operWA.GetValueByColName(&listNotice, nItem, theApp.operWA.ReadValue("MWA","WA_BoardMessage")));//��ȡ�������ݲ�����
				ServerIP = theApp.operWA.GetValueByColName(&listNotice, nItem, theApp.operWA.ReadValue("MWA","WA_ServerName"));//��ȡ������IP
				SetDlgItemText(IDBTNNOTICE,theApp.operWA.ReadValue("MWA","NI_UI_EditNotice"));
				//GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_SHOW);//��ʾ����״̬
				//GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_HIDE);//����ʾ�������͹����CheckBox
				GetDlgItem(IDC_LISTSERVER)->EnableWindow(false);//�÷������б��״̬��ΪDisable
				GetDlgItem(IDC_CHECKSELECTALL)->EnableWindow(false);

			}
		}
		else
		{
			nItem = 0;
			GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);//����ʾ����״̬
			GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKIMME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTSERVER)->EnableWindow(true);//�÷������б��״̬��ΪEnable	

			SetDlgItemText(IDBTNNOTICE,theApp.operWA.ReadValue("MWA","NI_UI_AddNotice"));
		}
		///////////////���Ѿ�ѡ���ip�б���ʾ����
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
		///////////////���Ѿ�ѡ���ip�б���ʾ��������
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// ���ͻ�༭����
void CNotice::OnBnClickedBtnnotice()
{
	try
	{
		UpdateData(true);
		CString NoticeOp = "";
		GetDlgItemText(IDBTNNOTICE, NoticeOp);

		if(NoticeOp == theApp.operWA.ReadValue("MWA","NI_UI_AddNotice"))//�����ťΪ��ӹ���
		{
			AddNotice();//��ӹ���
		}
		else if(NoticeOp == theApp.operWA.ReadValue("MWA","NI_UI_EditNotice"))//�����ťΪ�༭����
		{
			EditNotice();//�༭����
		}
	}
	catch(...)
	{
	}
}

// �Ƿ��͹���
void CNotice::OnBnClickedCheckimme()
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
void CNotice::AddNotice()
{;	
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
		MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_ServerListNull"),theApp.operWA.ReadValue("MWA","Warn"),0);
		return;
	}
	CString NoticeContent = "";
	GetDlgItemText(IDC_EDITCONTENT, NoticeContent);//��ȡ��������
	if(NoticeContent == "")//�������ݲ���Ϊ��
	{
		MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_ContentNotNull"),theApp.operWA.ReadValue("MWA","Warn"),0);
		return;
	}
	//���ַ����ֵ����
	if(strlen(NoticeContent) >= 400)//�������ݲ��ܳ���250���ַ�
	{
		MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_ContentTooLong"),theApp.operWA.ReadValue("MWA","Warn"),0);
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
	}
	else//���������������
	{
		if(toTime <= curTime)//����ʱ�䲻��С�ڵ�ǰʱ��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_StartTime"),theApp.operWA.ReadValue("MWA","Warn"),0);
			return;
		}
		if(toTime <= beginTime)//����ʱ�䲻��С�ڿ�ʼʱ��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_TimeSpan"),theApp.operWA.ReadValue("MWA","Warn"),0);
			return;
		}
		if(interval <= 0)//ʱ�����������0
		{
			MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_IntervalNull"),theApp.operWA.ReadValue("MWA","Warn"),0);
			return;
		}
								if(interval <= 1)//ʱ�����������0
			{
				MessageBox("ʱ��������С��1����",theApp.operWA.ReadValue("MXD","Warn"),0);
				return;
			}
		CTimeSpan sTimeSpan = toTime - beginTime;
		if(interval >= sTimeSpan.GetTotalMinutes())//ʱ����������ʱ�䷶Χ֮��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_IntervalLong"),theApp.operWA.ReadValue("MWA","Warn"),0);
			return;
		}
	}

	CString strMsg = theApp.operWA.ReadValue("MWA","NI_Hint_AddNotice"); 
	if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //��ʾ����Ƿ�ȷ��Ҫ��ӹ���
	{
		return;
	}

	CSocketData socketdata;
	char strInt[10];
	socketdata.InitCreate(1,10);//�����߸���������ʼʱ�䡢����ʱ�䡢ʱ�������������ݡ�����ԱID��������IP�����������ơ���������

	socketdata.AddTFLV(CEnumCore::TagName::WA_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//��ʼʱ��
	socketdata.AddTFLV(CEnumCore::TagName::WA_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//����ʱ��

	_itoa(interval,strInt,10);
	socketdata.AddTFLV(CEnumCore::TagName::WA_Interval,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ʱ����
	socketdata.AddTFLV(CEnumCore::TagName::WA_BoardMessage,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeContent),(unsigned char *)mIni.wcharToChar(NoticeContent));//��������
	int userByID = theApp.UserByID;
	_itoa(userByID,strInt,10);
	socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID
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
	socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(strServerIP),(unsigned char *)&strServerIP);//������IP
	socketdata.AddTFLV(CEnumCore::TagName::WA_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������IP)

	int midlength = socketdata.EnBody();
	if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BoardTasker_Add))//������ӹ��������
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}
	socketdata.Destroy();
}
catch(...)
{
}	
}

//�༭����
void CNotice::EditNotice()
{	
	try
	{		
		CIni mIni;
		UpdateData(true);
		CString strStatus = "";
		GetDlgItemText(IDC_CMBSTATUS, strStatus);//��ȡ����״̬
		if(strStatus == ""&&false)//����״̬����Ϊ��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_StatusNotNull"),theApp.operWA.ReadValue("MWA","Warn"),0);
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
		if(cmbStatus.GetCurSel() == 1&&false)//���ѡ��Ĺ���״̬���ѷ��ͣ����еĲ��������Բ�������
		{
		}
		else//���ѡ�����δ���ͣ�Ҫ����һЩ����
		{
			if(NoticeContent == "")//�������ݲ���Ϊ��
			{
				MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_ContentNotNull"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return;
			}
			//��������ַ�������
			if(strlen(NoticeContent) >= 400)//�������ݲ��ܳ���250���ַ�
			{
				MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_ContentTooLong"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return;
			}

			if(toTime <= curTime)//����ʱ�䲻��С�ڵ�ǰʱ��
			{
				MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_StartTime"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return;
			}

			if(toTime <= beginTime)//����ʱ�䲻��С�ڿ�ʼʱ��
			{
				MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_TimeSpan"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return;
			}

			if(interval <= 0)//ʱ�����������0
			{
				MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_IntervalNull"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return;
			}

			CTimeSpan sTimeSpan = toTime - beginTime;
			if(interval >= sTimeSpan.GetTotalMinutes())//ʱ����������ʱ�䷶Χ֮��
			{
				MessageBox(theApp.operWA.ReadValue("MWA","NI_Warn_IntervalLong"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return;
			}
		}

		CString strMsg = theApp.operWA.ReadValue("MWA","NI_Hint_EditNotice"); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) //��ʾ�Ƿ�༭����
		{
			return;
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,15);//����9����������ʼʱ�䡢����ʱ�䡢ʱ�������������ݡ�����IP������ԱID������״̬������ID��������IP
		char strInt[10];
		socketdata.AddTFLV(CEnumCore::TagName::WA_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::WA_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//����ʱ��
		_itoa(interval,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::WA_Interval,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ʱ����
		socketdata.AddTFLV(CEnumCore::TagName::WA_BoardMessage,CEnumCore::TagFormat::TLV_STRING,strlen(NoticeContent),(unsigned char *)mIni.wcharToChar(NoticeContent));//��������
		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		//_itoa(cmbStatus.GetCurSel(),strInt,10);
		//socketdata.AddTFLV(CEnumCore::TagName::WA_STATUS,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����״̬

		_itoa(NoticeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::WA_TaskID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP

		int midlength = socketdata.EnBody();
		if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BoardTasker_Update))//���ͱ༭���������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//����Ҫ���͹������Ϸ�������б�
void  CNotice::ReturnServerIP(char* allServerIP)
{
	CString serverName="";
	int index=0;
	for(int i=0;i<listResult.GetItemCount();i++)
	{

		if(listResult.GetCheck(i))
		{

			ServerList.Lookup(i+1,serverName);//���ҷ�����IP
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

//����Ҫ���͹������Ϸ�����������б�
CString CNotice::ReturnServerName()
{
	CString rServerName = "";
	CString serverName = "";
	for(int i=0;i<listResult.GetItemCount();i++)
	{
		if(listResult.GetCheck(i))
		{
			serverName=listResult.GetItemText(i,0);//���ҷ���������
			rServerName += serverName;
			rServerName += "|";//�����еķ�����IP��"|"����
		}
	}
	return rServerName;
}

//����������Ϸ�������б�
CString  CNotice::ReturnAllServerIP()
{
	//OperationWA operWA;
	CString rServerIP = "";
	CString serverName = "";
	for(int i=0;i<listResult.GetItemCount();i++)
	{
		ServerList.Lookup(i+1,serverName);//���ҷ�����IP
		rServerIP += serverName;
		rServerIP += "|";//�����еķ�����IP��"|"����
	}
	return rServerIP;
}
void CNotice::ReturnAllServerIP(char* allServerIP)
{
	CString serverName="";
	for(int i=0;i<listResult.GetItemCount();i++)
	{
		ServerList.Lookup(i+1,serverName);//���ҷ�����IP
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
//����������Ϸ�����������б�
CString CNotice::ReturnAllServerName()
{
	CString rServerName = "";
	CString serverName = "";
	for(int i=0;i<listResult.GetItemCount();i++)
	{
		serverName=listResult.GetItemText(i,0);//���ҷ���������
		rServerName += serverName;
		rServerName += "|";//�����еķ�����IP��"|"����
	}
	return rServerName;
}

// ������Ϣ
void CNotice::OnBnClickedBtnreset()
{
	//OperationWA operWA;
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
		SetDlgItemText(IDBTNNOTICE,theApp.operWA.ReadValue("MWA","NI_UI_AddNotice"));
		GetDlgItem(IDC_CHECKSELECTALL)->EnableWindow(true);
	}
	catch(...)
	{
	}
}

// ���շ�����Ϣ
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

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Receive");//��ǰ��״̬Ϊ���յ�������Ϣ

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operWA.ReadValue("MWA","Main_UI_ParseData"),theApp.operWA.ReadValue("MWA","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	int pageCount = 0;

	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://������յ����Ƿ������б�����Ϣ
		{
			listResult.EnableWindow(true);

			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);//��ȡ������Ϣ�еĵ�һ��ģ��
			if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)//�����һ��ģ���TagName��MESSAGE����ʾ�����˴�����Ϣ����ʾ������Ϣ������
			{
				MessageBox((LPCSTR)&m_tflv.lpdata,theApp.operWA.ReadValue("MWA","Error"),0);
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
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Query_Resp://������յ����ǹ����б�����ķ�����Ϣ
		{

			if(pageInfo)//�Ѿ����Է�ҳ
			{
				theApp.operWA.BuildDataTable(&socketdata,&listNotice,&pageCount);//���칫���б���Ϣ
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listNotice,&pageCount);//���칫���б���Ϣ

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
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Add_Resp://������յ�������ӹ�������ķ�����Ϣ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//��ʾ��ӹ���Ľ��
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
			SetDlgItemText(IDBTNNOTICE,theApp.operWA.ReadValue("MWA","NI_UI_AddNotice"));
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Update_Resp://������յ����Ǳ༭��������ķ�����Ϣ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//��ʾ�༭����Ľ��
			NoticeInfo();//��ѯ���еĹ�����Ϣ

			//CTime curTime = CTime::GetCurrentTime();//�������пؼ���Ϣ
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
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Del_Resp://������յ�����ɾ����������ķ�����Ϣ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//��ʾ�༭����Ľ��
			NoticeInfo();//��ѯ���еĹ�����Ϣ

			//CTime curTime = CTime::GetCurrentTime();//�������пؼ���Ϣ
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
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

//����������Ϣ��������������
void CNotice::OnLvnColumnclickListnotice(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationWA operWA;
	theApp.operWA.SortListInfo(&listNotice,pNMHDR,pResult);
}

// �رնԻ���
void CNotice::OnClose()
{
	//OperationWA operWA;
	dlgStatus = theApp.operWA.ReadIntValue("MWA","Close");//�رմ���
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
