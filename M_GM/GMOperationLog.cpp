// GMOperationLog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_GM.h"
#include "GMOperationLog.h"
#include ".\gmoperationlog.h"


// CGMOperationLog �Ի���

IMPLEMENT_DYNAMIC(CGMOperationLog, CDialog)
CGMOperationLog::CGMOperationLog(CWnd* pParent /*=NULL*/)
	: CDialog(CGMOperationLog::IDD, pParent)
{
}

CGMOperationLog::~CGMOperationLog()
{
}

void CGMOperationLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBGAMENAME, cmbGame);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_DTPSTARTDATE, dtcStartTime);
	DDX_Control(pDX, IDC_DTPENDDATE, dtcEndTime);
	DDX_Control(pDX, IDC_CMBREALNAME, cmbRealName);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
}


BEGIN_MESSAGE_MAP(CGMOperationLog, CDialog)
	ON_CBN_SELCHANGE(IDC_CMBGAMENAME, OnCbnSelchangeCmbgamename)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
END_MESSAGE_MAP()


// ��ʼ���Ի���
BOOL CGMOperationLog::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// ��ʼ����ʾ�ַ�

	GameName = "";
	ServerName = "";
	ServerIP = "";
	UserName = "";
	UserID = 0;
	strStartTime = "";
	strEndTime = "";//��ʼ��һЩ˽�б���

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
	//OperationGM operGM;
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	QueryUserList();

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CGMOperationLog::InitUI()
{
	//OperationGM operGM;

	SetWindowText(theApp.operGM.ReadValue("MGM","OL_UI_GMOperLog"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operGM.ReadValue("MGM","OL_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLGAMENAME,theApp.operGM.ReadValue("MGM","OL_UI_LblGame"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operGM.ReadValue("MGM","OL_UI_LblServer"));
	SetDlgItemText(IDC_LBLSTARTTIME,theApp.operGM.ReadValue("MGM","OL_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operGM.ReadValue("MGM","OL_UI_EndTime"));
	SetDlgItemText(IDC_LBLREALNAME,theApp.operGM.ReadValue("MGM","OL_UI_GMRealName"));
	SetDlgItemText(IDSEARCH,theApp.operGM.ReadValue("MGM","Search"));
	SetDlgItemText(IDCANCEL,theApp.operGM.ReadValue("MGM","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operGM.ReadValue("MGM","UM_UI_Page"));
}

//�����ݼ���Ӧ����
BOOL CGMOperationLog::PreTranslateMessage(MSG* pMsg)
{
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operGM.CopyListInfo(&listResult);
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
void CGMOperationLog::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CGMOperationLog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//��ȡ���е��û�����
void CGMOperationLog::QueryUserList()
{
	//OperationGM operGM;	
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
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_QUERY_ALL))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","IM_Error_SearchItemType"),theApp.operGM.ReadValue("MGM","Error"),0);
	}	
}

//��ȡ���е���Ϸ����
void CGMOperationLog::QueryGameList()
{
	//OperationGM operGM;	
	try
	{		
		CIni mIni;

		int index = theApp.operGM.ReadIntValue("MGM","index");
		int iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");

		cmbGame.ResetContent();
		cmbServer.ResetContent();

		CSocketData socketdata;	
		socketdata.InitCreate(1,3);//����3��������ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::GAME_ADMIN,CEnumCore::ServiceKey::GAME_QUERY))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","IM_Error_SearchItemType"),theApp.operGM.ReadValue("MGM","Error"),0);
	}	
}

//ͨ����Ϸ���Ʋ�ѯ��Ӧ����Ϸ������IP
void CGMOperationLog::OnCbnSelchangeCmbgamename()
{
	//OperationGM operGM;	
	try
	{		
		if(cmbGame.GetCurSel() == 0)
		{
			if(!ServerList.IsEmpty())
			{
				ServerList.RemoveAll();
			}
			ServerList.SetAt(0,0);
			cmbServer.ResetContent();
			cmbServer.AddString(theApp.operGM.ReadValue("MGM","OL_UI_AllCity"));//��ȡ��Ӧ����Ϸ������
			cmbServer.SetCurSel(0);
			return;
		}

		CIni mIni;

		int index = theApp.operGM.ReadIntValue("MGM","index");
		int iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");

		cmbServer.ResetContent();

		GetDlgItemText(IDC_CMBGAMENAME,GameName);//��ȡ��Ϸ����
		if(GameName == "")//��Ϸ���Ʋ���Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","OL_Warn_GameNameNull"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		GameList.Lookup(cmbGame.GetCurSel(),GameID);//��CMap��Ķ���GameList�л�ȡ��ϷID

		CSocketData socketdata;	
		socketdata.InitCreate(1,5);//��������������������IP��������Name������ǳơ���������,ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(GameID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GameID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID
		socketdata.AddTFLV(CEnumCore::TagName::GameName,CEnumCore::TagFormat::TLV_STRING,strlen(GameName),(unsigned char *)mIni.wcharToChar(GameName));//��Ϸ����
		
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::SERVERINFO_IP_ALL_QUERY))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","IM_Error_SearchItemType"),theApp.operGM.ReadValue("MGM","Error"),0);
	}	
}

// ��ѯGM������¼��־��Ϣ
void CGMOperationLog::OnBnClickedSearch()
{
	try
	{
		CIni mIni;

		int index = theApp.operGM.ReadIntValue("MGM","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");//ÿҳ��ʾ50����¼

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}//�����������б��е���������

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������
		if(ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UIC_Warn_SelectServer"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel(),ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_CMBGAMENAME,GameName);//��ȡ��Ϸ��
		if(GameName == "")//��Ϸ������Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UIC_Warn_SelectServer"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		GameList.Lookup(cmbGame.GetCurSel(),GameID);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_CMBREALNAME,UserName);//��ȡGM��ʵ����
		if(UserName == "")//����ʺŲ���Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","OL_Warn_InputNotNull"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		UserList.Lookup(cmbRealName.GetCurSel()+1,UserID);//��CMap��Ķ���UserList�л�ȡ�û�ID

		strStartTime = "";//��ʼʱ��
	    strEndTime = "";//����ʱ��
		CTime curTime = CTime::GetCurrentTime();
		CTime StartTime;
		dtcStartTime.GetTime(StartTime);//��ȡ��ʼʱ��
		CTime EndTime;
		dtcEndTime.GetTime(EndTime);//��ȡ����ʱ��

		if(StartTime >= curTime)//��ʼʱ�䲻�ܴ��ڵ�ǰʱ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","LI_Warn_StartTime"),theApp.operGM.ReadValue("MGM","Warn"),0);
			return;
		}
		if(EndTime <= StartTime)//����ʱ�䲻��С�ڿ�ʼʱ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","LI_Warn_TimeSpan"),theApp.operGM.ReadValue("MGM","Warn"),0);
			return;
		}
		strStartTime = StartTime.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��
		strEndTime = EndTime.Format("%Y-%m-%d %H:%M:%S");//���ý���ʱ��

	    
		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
		char strInt[10];
	

		_itoa(GameID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GameID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID
		socketdata.AddTFLV(CEnumCore::TagName::GameName,CEnumCore::TagFormat::TLV_STRING,strlen(GameName),(unsigned char *)mIni.wcharToChar(GameName));//��Ϸ����
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_City,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		if(cmbServer.GetCurSel() == 0)
		{
			ServerIP = "ALL";
		}
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_IP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		
		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID
		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//�û���ʵ����
		
		socketdata.AddTFLV(CEnumCore::TagName::BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//����ʱ��

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength=socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::GMTOOLS_OperateLog_Query))//���Ͳ�ѯGM������¼��־��Ϣ������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		    dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}		
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}
}

// ��ҳ���в�ѯ
void CGMOperationLog::OnCbnSelchangeCmbpage()
{
	//OperationGM operGM;
	try
	{	
		if(pageInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;
		
			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");//ÿҳ��ʾ50����¼

			int midlength = 0;
			while(listResult.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,10);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			_itoa(GameID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::GameID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ϷID		
			socketdata.AddTFLV(CEnumCore::TagName::GameName,CEnumCore::TagFormat::TLV_STRING,strlen(GameName),(unsigned char *)mIni.wcharToChar(GameName));//��Ϸ����
			socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_City,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_IP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			
			_itoa(UserID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID
			socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//�û���ʵ����
			
			socketdata.AddTFLV(CEnumCore::TagName::BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//��ʼʱ��
			socketdata.AddTFLV(CEnumCore::TagName::EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//����ʱ��

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			midlength=socketdata.EnBody();
			if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::GMTOOLS_OperateLog_Query))//���Ͳ�ѯGM������¼��־��Ϣ������
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
				dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
			socketdata.Destroy();//����CSocketData�ֲ�����
		}
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","UIC_Error_Page"),theApp.operGM.ReadValue("MGM","Error"),0);
	}
}

// ���շ�����Ϣ
LRESULT CGMOperationLog::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;

	dlgStatus = theApp.operGM.ReadIntValue("MGM","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	int pageCount = 0;

	switch(theApp.m_tag_id)
	{
	case CEnumCore::Message_Tag_ID::USER_QUERY_ALL_RESP://��ѯ�û���Ϣ�Ļ�Ӧ
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int UserID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::User_ID).lpdata);//�õ��û�ID
				UserList.SetAt(i,UserID);//���û�ID������CMap��Ķ���UserList��
			}

			theApp.operGM.BuildComboxUser(&socketdata,&cmbRealName);//������������б���Ϣ
			QueryGameList();
		}
		break;
	case CEnumCore::Message_Tag_ID::GAME_QUERY_RESP://��ѯ��Ϸ��Ϣ�Ļ�Ӧ
		{
			if(!GameList.IsEmpty())
			{
				GameList.RemoveAll();
			}
			GameList.SetAt(0,0);
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int GameID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::GameID).lpdata);//�õ���ϷID
				GameList.SetAt(i,GameID);//����ϷID������CMap��Ķ���UserList��
			}

			theApp.operGM.BuildComboxGame(&socketdata,&cmbGame);//������Ϸ�����б���Ϣ

			if(!ServerList.IsEmpty())
			{
				ServerList.RemoveAll();
			}
			ServerList.SetAt(0,0);
			cmbServer.ResetContent();
			cmbServer.AddString(theApp.operGM.ReadValue("MGM","OL_UI_AllCity"));//��ȡ��Ӧ����Ϸ������
			cmbServer.SetCurSel(0);

			::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	        ::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		}
		break;
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_ALL_QUERY_RESP://��ѯ��Ϸ������IP�Ļ�Ӧ
		{
			if(!ServerList.IsEmpty())
			{
				ServerList.RemoveAll();
			}
			ServerList.SetAt(0,0);
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ���Ϸ������IP
				ServerList.SetAt(i,ServerIP);//����Ϸ������IP������CMap��Ķ���ServerList��
			}

			theApp.operGM.BuildComboxCity(&socketdata,&cmbServer);//������Ϸ�������б���Ϣ

			::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	        ::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		}
		break;
	case CEnumCore::Message_Tag_ID::GMTOOLS_OperateLog_Query_RESP://��ѯGM������־��Ϣ��Ӧ
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operGM.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operGM.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

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
			::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	        ::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		}
		break;
	default:
		break;
	}	
	return false;
}

// �رնԻ���
void CGMOperationLog::OnBnClickedCancel()
{
	CTime curTime = CTime::GetCurrentTime();//��ȡ��ǰʱ��
	dtcStartTime.SetTime(&curTime);
	dtcEndTime.SetTime(&curTime);
	cmbServer.SetCurSel(0);
	cmbGame.SetCurSel(0);
	cmbRealName.SetCurSel(0);
}

// �رնԻ���
void CGMOperationLog::OnClose()
{
	if(!GameList.IsEmpty())
	{
		GameList.RemoveAll();
	}
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!UserList.IsEmpty())
	{
		UserList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}