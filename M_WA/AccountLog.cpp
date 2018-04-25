// WAAccountLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_WA.h"
#include "AccountLog.h"
#include ".\accountlog.h"


// CWAAccountLogin �Ի���

IMPLEMENT_DYNAMIC(CWAAccountLogin, CDialog)
CWAAccountLogin::CWAAccountLogin(CWnd* pParent /*=NULL*/)
: CDialog(CWAAccountLogin::IDD, pParent)
{
	//unsigned long long temp=0;
}

CWAAccountLogin::~CWAAccountLogin()
{
}

void CWAAccountLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_CHECKBYACCOUNT, checkByAccount);
	DDX_Control(pDX, IDC_DTPSTARTDATE, dtcStartTime);
	DDX_Control(pDX, IDC_DTPENDDATE, dtcEndTime);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listResult);
	DDX_Control(pDX, IDC_CHECKBYIP, checkByIP);
	DDX_Control(pDX, IDC_IPADDRESSCHECK, IPACtrl_UserIP);
}

BEGIN_MESSAGE_MAP(CWAAccountLogin, CDialog)
	ON_BN_CLICKED(IDC_CHECKBYACCOUNT, OnBnClickedCheckbyaccount)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECKBYIP, OnBnClickedCheckbyip)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
END_MESSAGE_MAP()


// ��ʼ���Ի���
BOOL CWAAccountLogin::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// ��ʼ����ʾ�ַ�
	ServerName = "";
	ServerIP = "";
	UserNick = "";
	UserIP = "";//��ʼ��һЩ˽�б���
	checkType = 1;//ͨ���˺Ų�ѯ
	checkByAccount.SetCheck(1);
	ShowCheckByAccount();//��ʾͨ���ʺŲ�ѯ����Ϣ

	SetProp(listResult.GetSafeHwnd(),"�����к�",(HANDLE)0);
	SetProp(listResult.GetSafeHwnd(),"����˳��",(HANDLE)1);

	CRect rs;
	GetClientRect(rs);; //��ȡ�Ի���Ĵ�С��Ϣ
	CRect srcRect;
	CRect newRect;
	if(GrpSearch.m_hWnd != NULL)
	{
		GrpSearch.GetWindowRect(srcRect);//��ȡGrpSearch�Ĵ�С��Ϣ
		grpHeight = srcRect.bottom - srcRect.top;//�õ�GrpSearch�ĸ߶���Ϣ
		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + grpHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;
		GrpSearch.MoveWindow(newRect);//���ú�GrpSearch��λ��
	}

	if(GrpPage.m_hWnd != NULL)
	{
		GrpPage.GetWindowRect(srcRect);//��ȡGrpPage�Ĵ�С��Ϣ
		grpPHeight = srcRect.bottom - srcRect.top;//�õ�GrpPage�ĸ߶���Ϣ
		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;
		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}
	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;
		listResult.MoveWindow(newRect);//���ú�listResult��λ��		
	}
	dlgStatus = theApp.operWA.ReadIntValue("MWA","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	if(theApp.operWA.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CWAAccountLogin::InitUI()
{
	//OperationWA operWA;
	SetWindowText(theApp.operWA.ReadValue("MWA","AL_UI_AccountLoginLog"));
	SetDlgItemText(IDC_GRPSEARCH,theApp.operWA.ReadValue("MWA","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operWA.ReadValue("MWA","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operWA.ReadValue("MWA","AL_UI_UserNick"));
	SetDlgItemText(IDC_LBLIP,theApp.operWA.ReadValue("MWA","AL_UI_UserIP"));
	SetDlgItemText(IDC_CHECKBYACCOUNT,theApp.operWA.ReadValue("MWA","AL_UI_CheckByAccount"));
	SetDlgItemText(IDC_CHECKBYIP,theApp.operWA.ReadValue("MWA","AL_UI_CheckByIP"));
	SetDlgItemText(IDC_LBLSTARTTIME,theApp.operWA.ReadValue("MWA","NI_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operWA.ReadValue("MWA","NI_UI_EndTime"));
	SetDlgItemText(IDSEARCH,theApp.operWA.ReadValue("MWA","Search"));
	SetDlgItemText(IDCANCEL,theApp.operWA.ReadValue("MWA","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operWA.ReadValue("MWA","UIC_UI_Page"));
}

//�����ݼ���Ӧ����
BOOL CWAAccountLogin::PreTranslateMessage(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listResult);
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listResult.m_hWnd)
				{
					for(int i=0; i<listResult.GetItemCount(); i++)
					{
						listResult.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listResult.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

// �Զ��ı��С
void CWAAccountLogin::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	CRect rs;
	GetClientRect(rs);
	CRect newRect;
	if(GrpSearch.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4;		
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;
		newRect.bottom = newRect.top + grpHeight;
		GrpSearch.MoveWindow(newRect);//���ú�GrpSearch��λ��
	}

	if(GrpPage.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;
		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;
		listResult.MoveWindow(newRect);//���ú�listResult��λ��
	}
}

//���ñ�����ɫ
HBRUSH CWAAccountLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);
	return CreateSolidBrush(backColor);
}

// ����ͨ���ʺ�����ѯ
void CWAAccountLogin::OnBnClickedCheckbyaccount()
{
	if(checkByAccount.GetCheck() == 1)
	{
		checkByIP.SetCheck(0);
		ShowCheckByAccount();
	}
	else
	{
		checkByIP.SetCheck(1);
		ShowCheckByIP();
	}
}

// ����ͨ��IP����ѯ
void CWAAccountLogin::OnBnClickedCheckbyip()
{
	if(checkByIP.GetCheck() == 1)
	{
		checkByAccount.SetCheck(0);
		ShowCheckByIP();
	}
	else
	{
		checkByAccount.SetCheck(1);
		ShowCheckByAccount();
	}
}

// ��ѯ��ҵ�¼��־��Ϣ
void CWAAccountLogin::OnBnClickedSearch()
{
	try
	{
		CIni mIni;
		int index = theApp.operWA.ReadIntValue("MWA","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//ÿҳ��ʾ50����¼

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}//�����������б��е���������

		UpdateData(true);			
		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������
		if(ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_SelectServer"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		if(checkByAccount.GetCheck() == 1) 
			checkType = 1;
		else 
			checkType = 2;

		if(checkType == 1)//ͨ���˺Ų�ѯ
		{
			GetDlgItemText(IDC_EDITACCOUNT,UserNick);//��ȡ����ʺ�
			if(UserNick == "")//����ʺŲ���Ϊ��
			{
				MessageBox(theApp.operWA.ReadValue("MWA","AL_Warn_InputNotNull"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
		}
		else//ͨ��IP��ѯ
		{
			GetDlgItemText(IDC_IPADDRESSCHECK,UserIP);//��ȡ���IP
			if(!strcmp(UserIP,"0.0.0.0"))//���IP����Ϊ��
			{
				MessageBox(theApp.operWA.ReadValue("MWA","AL_Warn_InputNotNull"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
		}		

		CTime sTime;
		dtcStartTime.GetTime(sTime);//��ȡ��ʼʱ��
		CTime eTime;
		dtcEndTime.GetTime(eTime);//��ȡ����ʱ��
		BeginTime = sTime.Format("%Y-%m-%d %H:%M:%S");//��ȡ��ʼʱ��
		EndTime = eTime.Format("%Y-%m-%d %H:%M:%S");//��ȡ����ʱ��

		CSocketData socketdata;	
		socketdata.InitCreate(1,12);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
		char strInt[10];
		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_LoginIP,CEnumCore::TagFormat::TLV_STRING,strlen(UserIP),(unsigned char *)mIni.wcharToChar(UserIP));//���IP
		
		socketdata.AddTFLV(CEnumCore::TagName::WA_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(BeginTime),(unsigned char*)mIni.wcharToChar(BeginTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::WA_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(EndTime),(unsigned char*)mIni.wcharToChar(EndTime));//����ʱ��

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����
		
		int midlength=socketdata.EnBody();
		if(checkType == 1)
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Query_LoginLogout);//��ҵ�½/�ǳ���־			
		else
			theApp.operWA.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Query_LoginLogoutByIP);//���Ͳ�ѯ��ҵ�½��¼��־������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}
}

// ��ҳ���в�ѯ
void CWAAccountLogin::OnCbnSelchangeCmbpage()
{
	try
	{	
		if(pageInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;

			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//ÿҳ��ʾ50����¼

			int midlength = 0;
			while(listResult.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,12);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
			char strInt[10];
			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_LoginIP,CEnumCore::TagFormat::TLV_STRING,strlen(UserIP),(unsigned char *)mIni.wcharToChar(UserIP));//���IP
		
			socketdata.AddTFLV(CEnumCore::TagName::WA_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(BeginTime),(unsigned char*)mIni.wcharToChar(BeginTime));//��ʼʱ��
			socketdata.AddTFLV(CEnumCore::TagName::WA_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(EndTime),(unsigned char*)mIni.wcharToChar(EndTime));//����ʱ��

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����
			
			midlength=socketdata.EnBody();
			if(checkType == 1)
				theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Query_LoginLogout);//��ҵ�½/�ǳ���־			
			else
				theApp.operWA.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Query_LoginLogoutByIP);//���Ͳ�ѯ��ҵ�½��¼��־������

			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();//����CSocketData�ֲ�����
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Page"),theApp.operWA.ReadValue("MWA","Error"),0);
	}
}

// ���շ�����Ϣ
LRESULT CWAAccountLogin::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

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
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��ѯ�������б���Ϣ�Ļ�Ӧ
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ�������IP
				ServerList.SetAt(i,ServerIP);//��������IP������CMap��Ķ���ServerList��
			}

			theApp.operWA.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	default://��ѯ��ҵ�¼��־��Ϣ��Ӧ
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					pageInfo = false;//���ܷ�ҳ		
					cmbPage.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					cmbPage.ResetContent();
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbPage.AddString(str);
					}
					cmbPage.SetCurSel(0);
					if(pageCount == 1)
					{
						pageInfo = false;
					}
					else
					{
						pageInfo = true;
					}
				}				
			}
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);

	socketdata.Destroy();
	return false;
}

//�����û�������Ϣ��������������
void CWAAccountLogin::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operWA.SortListInfo(&listResult,pNMHDR,pResult);
}

// �رնԻ���
void CWAAccountLogin::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_IPADDRESSCHECK,"");
	CTime curTime = CTime::GetCurrentTime();//��ȡ��ǰʱ��
	dtcStartTime.SetTime(&curTime);
	dtcEndTime.SetTime(&curTime);
	ShowCheckByAccount();
}

// �رնԻ���
void CWAAccountLogin::OnClose()
{
	dlgStatus = theApp.operWA.ReadIntValue("MWA","Close");//�رմ���	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//��ʾͨ���ʺŲ�ѯ����Ϣ
void CWAAccountLogin::ShowCheckByAccount(void)
{
	GetDlgItem(IDC_LBLIP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_IPADDRESSCHECK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_IPADDRESSCHECK,"");
}

//��ʾͨ��IP��ѯ����Ϣ
void CWAAccountLogin::ShowCheckByIP(void)
{
	GetDlgItem(IDC_LBLIP)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_IPADDRESSCHECK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(SW_HIDE);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_IPADDRESSCHECK,"");
}