// CJW2LoginInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_JW2.h"
#include "JW2LoginInfo.h"
#include ".\JW2LoginInfo.h"


// CJW2KickPlayer �Ի���

IMPLEMENT_DYNAMIC(CJW2LoginInfo, CDialog)
CJW2LoginInfo::CJW2LoginInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CJW2LoginInfo::IDD, pParent)
{
}

CJW2LoginInfo::~CJW2LoginInfo()
{
}

void CJW2LoginInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBKPPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listResult);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPKPPAGE, GrpPage);

	DDX_Control(pDX, IDC_DATETIMELOGIN, dtcLoginDate);
	DDX_Control(pDX, IDC_DATETIMELOGOUT, dtcLogoutDate);

	DDX_Control(pDX, IDC_CHECKBYACCOUNT, m_ckAccount);
	DDX_Control(pDX, IDC_CHECKBYIP, m_ckIP);
}


BEGIN_MESSAGE_MAP(CJW2LoginInfo, CDialog)
	ON_CBN_SELCHANGE(IDC_CMBKPPAGE, OnCbnSelchangeCmbkppage)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECKBYACCOUNT, OnBnClickedCheckbyaccount)
	ON_BN_CLICKED(IDC_CHECKBYIP, OnBnClickedCheckbyip)
END_MESSAGE_MAP()

// ��ʼ���Ի���
BOOL CJW2LoginInfo::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// ��ʼ����ʾ�ַ�	

	nItem = -1;
	pageInfo = false;//��ʼ��һЩ˽�б���

	CRect rs;
	GetClientRect(rs);//��ȡ�Ի���Ĵ�С��Ϣ

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

		listResult.MoveWindow(newRect);//���ú�listUser��λ��
	}

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Create");//��ʼ�����Ի���

	theApp.operJW2.GetServerList();
	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//���Ͳ�ѯ����

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CJW2LoginInfo::InitUI()
{
	//OperationJW2 theApp.operJW2;

	SetWindowText(theApp.operJW2.ReadValue("MJW2","LI_UI_LoginInfo"));


	SetDlgItemText(IDC_GRPSEARCH,theApp.operJW2.ReadValue("MJW2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operJW2.ReadValue("MJW2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operJW2.ReadValue("MJW2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operJW2.ReadValue("MJW2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operJW2.ReadValue("MJW2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operJW2.ReadValue("MJW2","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operJW2.ReadValue("MJW2","UIC_UI_Page"));
	SetDlgItemText(IDC_LBLHINT,theApp.operJW2.ReadValue("MJW2","KP_UI_KickHint"));
	GetDlgItem(IDC_LBLIP)->ShowWindow(SW_HIDE);
	m_ckAccount.SetCheck(1);
	m_ckIP.SetCheck(0);
}

// �Զ��ı��С
void CJW2LoginInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rs;
	GetClientRect(rs);

	CRect newRect;
	
	if(GrpSearch.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + grpHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

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
HBRUSH CJW2LoginInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ���������Ϣ
void CJW2LoginInfo::OnBnClickedUisearch()
{
	try
	{
		//OperationJW2 theApp.operJW2;

		nItem = -1;//��������б�û��ѡ����
		pageInfo = false;//��������б��ܷ�ҳ	
		cmbPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listResult.DeleteColumn(0)){}//�����������б��е���������

		UpdateData(true);			


		GetDlgItemText(IDC_CMBUISERVER,ServerName);//��ȡ��Ϸ������������
		if(ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Warn_SelectServer"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		if(m_ckIP.GetCheck()==0)
		{
			GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//��ȡ����ʺ�
			GetDlgItemText(IDC_EDITUINICK,UserNick);//��ȡ����ǳ�
			if((UserName == "") && (UserNick == ""))//����ʺź�����ǳƲ���ͬʱΪ��
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Warn_InputAccount"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}	
		}
		

	    LoginInfo();
	}
	catch(...)
	{
	}
}

// ��ѯ��ҵ�½��Ϣ
void CJW2LoginInfo::LoginInfo()
{
	try
	{
		CIni mIni;	

		int index = theApp.operJW2.ReadIntValue("MJW2","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//��������б�û��ѡ����
		pageInfo = false;//��������б��ܷ�ҳ		
		cmbPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listResult.DeleteColumn(0)){}//�����������б��е���������		

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
	
		if(m_ckIP.GetCheck()==1)
		{
			CString JW2_IP;
			GetDlgItemText(IDC_IPADDRESSCHECK,JW2_IP);
			socketdata.AddTFLV(CEnumCore::TagName::JW2_IP,CEnumCore::TagFormat::TLV_STRING,strlen(JW2_IP),(unsigned char *)mIni.wcharToChar(JW2_IP));//����ʺ�

		}
		else
		{
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
		}

	
		CTime LoginDate,LogoutDate;
		dtcLoginDate.GetTime(LoginDate);
		dtcLogoutDate.GetTime(LogoutDate);

		CTime LoginDT=CTime::CTime(LoginDate.GetYear(),LoginDate.GetMonth(),LoginDate.GetDay(),0,0,0);
		CTime LogoutDT=CTime::CTime(LogoutDate.GetYear(),LogoutDate.GetMonth(),LogoutDate.GetDay(),0,0,0);

		CString strLoginTime,strLogoutTime;
		strLoginTime=LoginDT.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��
		strLogoutTime=LogoutDT.Format("%Y-%m-%d %H:%M:%S");//���ý���ʱ��

		socketdata.AddTFLV(CEnumCore::TagName::JW2_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLoginTime),(unsigned char *)mIni.wcharToChar(strLoginTime));

		socketdata.AddTFLV(CEnumCore::TagName::JW2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLogoutTime),(unsigned char *)mIni.wcharToChar(strLogoutTime));


		
		
		
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����



		
		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_LOGINOUT_QUERY);//���Ͳ�ѯ���������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_UserInfo"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// ��ҳ���в�ѯ
void CJW2LoginInfo::OnCbnSelchangeCmbkppage()
{	
	try
	{
		if(pageInfo)//������Է�ҳ�Ļ�
		{	
			CIni mIni;
			//OperationJW2 theApp.operJW2;
			
			char strInt[10];
			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbPage��ǰ������ֵ��1��Ҳ����cmbPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//ÿҳ��ʾ50����¼

			while(listResult.DeleteColumn(0)){}//���ҳ������

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����

			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			if(m_ckIP.GetCheck()==1)
			{
				CString JW2_IP;
				GetDlgItemText(IDC_IPADDRESSCHECK,JW2_IP);
				socketdata.AddTFLV(CEnumCore::TagName::JW2_IP,CEnumCore::TagFormat::TLV_STRING,strlen(JW2_IP),(unsigned char *)mIni.wcharToChar(JW2_IP));//����ʺ�

			}
			else
			{
				socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
				socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			}

			CTime LoginDate,LogoutDate;
			dtcLoginDate.GetTime(LoginDate);
			dtcLogoutDate.GetTime(LogoutDate);

			CTime LoginDT=CTime::CTime(LoginDate.GetYear(),LoginDate.GetMonth(),LoginDate.GetDay(),0,0,0);
			CTime LogoutDT=CTime::CTime(LogoutDate.GetYear(),LogoutDate.GetMonth(),LogoutDate.GetDay(),0,0,0);

			CString strLoginTime,strLogoutTime;
			strLoginTime=LoginDT.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��
			strLogoutTime=LogoutDT.Format("%Y-%m-%d %H:%M:%S");//���ý���ʱ��

			socketdata.AddTFLV(CEnumCore::TagName::JW2_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLoginTime),(unsigned char *)mIni.wcharToChar(strLoginTime));

			socketdata.AddTFLV(CEnumCore::TagName::JW2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLogoutTime),(unsigned char *)mIni.wcharToChar(strLogoutTime));




			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);



						

			int midlength = socketdata.EnBody();
			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_LOGINOUT_QUERY);//��ǰ��״̬Ϊ���Ͳ�ѯ����

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// ˫�����������Ϣ��������
void CJW2LoginInfo::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	*pResult = 0;
}

// ���շ�����Ϣ
LRESULT CJW2LoginInfo::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	//OperationJW2 theApp.operJW2;
	CIni mIni;

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	socketdata.DeBody(lpReceive,bodyLength);

	int pageCount = 0;

	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��ѯ�������б���Ϣ�Ļ�Ӧ
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString sIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ�������IP
				ServerList.SetAt(i,sIP);//��������IP������CMap��Ķ���ServerList��
			}

			theApp.operJW2.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_LOGINOUT_QUERY_RESP://��ѯ��ҵ�½��Ϣ�Ļ�Ӧ
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{					
					nItem = -1;//����ѡ��ĳһ��
					pageInfo = false;//���ܷ�ҳ
					cmbPage.ResetContent();//���ҳ����ѡ��
					while(listResult.DeleteColumn(0)){}//���CListCtrl����
				}
				else
				{
					nItem = 0;
					cmbPage.ResetContent();//���ҳ����ѡ���Ա����¹���
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbPage.AddString(str);//�ڸ�ѡ���й���ҳ����Ϣ
					}
					cmbPage.SetCurSel(0);//�ڸ�ѡ����ѡ�е�һҳ
					if(pageCount == 1)
					{
						pageInfo = false;//ֻ��һҳ���ݣ����ܷ�ҳ
					}
					else
					{
						pageInfo = true;//�ж�ҳ���ݣ����Է�ҳ
					}
				}				
			}
		}
		break;
	default:
		break;
	}

	socketdata.Destroy();
	return false;
}

// �رնԻ���
void CJW2LoginInfo::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// �رնԻ���
void CJW2LoginInfo::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}




//ѡ��ͨ���ʺź��ǳƲ�ѯ
void CJW2LoginInfo::OnBnClickedCheckbyaccount()
{
	switch(m_ckAccount.GetCheck())
	{
	case 0:
		{
			GetDlgItem(IDC_EDITUIACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITUINICK)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUINICK)->ShowWindow(SW_HIDE);

			/////////����/////////////////////////
			GetDlgItem(IDC_LBLIP)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_IPADDRESSCHECK)->ShowWindow(SW_SHOW);
			
			m_ckIP.SetCheck(1);
		}
		break;
	case 1:
		{
			///////////��ʾ////////////////////////////////////
			GetDlgItem(IDC_EDITUIACCOUNT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDITUINICK)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIACCOUNT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUINICK)->ShowWindow(SW_SHOW);

			/////////����/////////////////////////
			GetDlgItem(IDC_LBLIP)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_IPADDRESSCHECK)->ShowWindow(SW_HIDE);

			m_ckIP.SetCheck(0);
		}
		break;
	default:
		break;
	}
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CJW2LoginInfo::OnBnClickedCheckbyip()
{
	switch(m_ckIP.GetCheck())
	{
	case 0:
		{
			///////////��ʾ////////////////////////////////////
			GetDlgItem(IDC_EDITUIACCOUNT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDITUINICK)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIACCOUNT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUINICK)->ShowWindow(SW_SHOW);

			/////////����/////////////////////////
			GetDlgItem(IDC_LBLIP)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_IPADDRESSCHECK)->ShowWindow(SW_HIDE);
			

			m_ckAccount.SetCheck(1);
		}
		break;
	case 1:
		{
			GetDlgItem(IDC_EDITUIACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITUINICK)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUINICK)->ShowWindow(SW_HIDE);

			/////////����/////////////////////////
			GetDlgItem(IDC_LBLIP)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_IPADDRESSCHECK)->ShowWindow(SW_SHOW);

			m_ckAccount.SetCheck(0);
		}
		break;
	default:
		break;
	}
}
