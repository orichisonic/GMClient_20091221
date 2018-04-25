// CG2UserShoppingInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2UserShoppingInfo.h"
#include ".\CG2UserShoppingInfo.h"


// CCG2UserShoppingInfo �Ի���

IMPLEMENT_DYNAMIC(CCG2UserShoppingInfo, CDialog)
CCG2UserShoppingInfo::CCG2UserShoppingInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2UserShoppingInfo::IDD, pParent)
{
}

CCG2UserShoppingInfo::~CCG2UserShoppingInfo()
{
}

void CCG2UserShoppingInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBKPPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listResult);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPKPPAGE, GrpPage);
	DDX_Control(pDX, IDC_BEGINTIME, dtcBeginDate);
	DDX_Control(pDX, IDC_ENDTIME, dtcEndDate);
	DDX_Control(pDX, IDC_CK1, ck_Send);
	DDX_Control(pDX, IDC_CK2, ck_Recv);
}


BEGIN_MESSAGE_MAP(CCG2UserShoppingInfo, CDialog)
	ON_CBN_SELCHANGE(IDC_CMBKPPAGE, OnCbnSelchangeCmbkppage)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CK1, OnBnClickedCk1)
	ON_BN_CLICKED(IDC_CK2, OnBnClickedCk2)
END_MESSAGE_MAP()

// ��ʼ���Ի���
BOOL CCG2UserShoppingInfo::OnInitDialog()
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

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//��ʼ�����Ի���


	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CCG2UserShoppingInfo::InitUI()
{
	//OperationCG2 theApp.operCG2;

	SetWindowText(theApp.operCG2.ReadValue("MCG2","KP_UI_KickPlayer"));
	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));
	SetDlgItemText(IDC_LBLBEGINTIME,theApp.operCG2.ReadValue("MCG2","NI_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operCG2.ReadValue("MCG2","NI_UI_EndTime"));
	SetDlgItemText(IDC_CK1,theApp.operCG2.ReadValue("MCG2","BU_UI_SENDLOG"));
	SetDlgItemText(IDC_CK2,theApp.operCG2.ReadValue("MCG2","BU_UI_RECVLOG"));
	ck_Send.SetCheck(1);

	
	

}

// �Զ��ı��С
void CCG2UserShoppingInfo::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CCG2UserShoppingInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ���������Ϣ
void CCG2UserShoppingInfo::OnBnClickedUisearch()
{
	try
	{
		//OperationCG2 theApp.operCG2;

		nItem = -1;//��������б�û��ѡ����
		pageInfo = false;//��������б��ܷ�ҳ	
		cmbPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listResult.DeleteColumn(0)){}//�����������б��е���������

		UpdateData(true);			



		GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//��ȡ����ʺ�
		if(UserName == "")//����ʺŲ���ͬʱΪ��
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_InputUserName"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

	    UserInfo();
	}
	catch(...)
	{
	}
}

// ��ѯ���������Ϣ
void CCG2UserShoppingInfo::UserInfo()
{
	//OperationCG2 theApp.operCG2;
	try
	{
		CIni mIni;	

		int index = theApp.operCG2.ReadIntValue("MCG2","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//��������б�û��ѡ����
		pageInfo = false;//��������б��ܷ�ҳ		
		cmbPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listResult.DeleteColumn(0)){}//�����������б��е���������		

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];


		CTime BeginDate,EndDate;
		dtcBeginDate.GetTime(BeginDate);
		dtcEndDate.GetTime(EndDate);



		CTime LoginDT=CTime::CTime(BeginDate.GetYear(),BeginDate.GetMonth(),BeginDate.GetDay(),0,0,0);
		CTime LogoutDT=CTime::CTime(EndDate.GetYear(),EndDate.GetMonth(),EndDate.GetDay(),0,0,0);

		CString strLoginTime,strLogoutTime;
		strLoginTime=LoginDT.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��
		strLogoutTime=LogoutDT.Format("%Y-%m-%d %H:%M:%S");//���ý���ʱ��

		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		socketdata.AddTFLV(CEnumCore::TagName::CG2_StartTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLoginTime),(unsigned char *)mIni.wcharToChar(strLoginTime));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLogoutTime),(unsigned char *)mIni.wcharToChar(strLogoutTime));//����ǳ�


		int iTypeID=0;
		switch(ck_Send.GetCheck())
		{
		case 0:
			iTypeID=2;
			break;
		case 1:
			iTypeID=1;
			break;
		}
		_itoa(iTypeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_TypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_UserShoppingInfo_Query);//���Ͳ�ѯ���������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// ��ҳ���в�ѯ
void CCG2UserShoppingInfo::OnCbnSelchangeCmbkppage()
{	
	try
	{
		if(pageInfo)//������Է�ҳ�Ļ�
		{	
			CIni mIni;
			//OperationCG2 theApp.operCG2;
			
			char strInt[10];
			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbPage��ǰ������ֵ��1��Ҳ����cmbPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼

			while(listResult.DeleteColumn(0)){}//���ҳ������

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����


			CTime BeginDate,EndDate;
			dtcBeginDate.GetTime(BeginDate);
			dtcEndDate.GetTime(EndDate);



			CTime LoginDT=CTime::CTime(BeginDate.GetYear(),BeginDate.GetMonth(),BeginDate.GetDay(),0,0,0);
			CTime LogoutDT=CTime::CTime(EndDate.GetYear(),EndDate.GetMonth(),EndDate.GetDay(),0,0,0);

			CString strLoginTime,strLogoutTime;
			strLoginTime=LoginDT.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��
			strLogoutTime=LogoutDT.Format("%Y-%m-%d %H:%M:%S");//���ý���ʱ��

			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�


			socketdata.AddTFLV(CEnumCore::TagName::CG2_StartTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLoginTime),(unsigned char *)mIni.wcharToChar(strLoginTime));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLogoutTime),(unsigned char *)mIni.wcharToChar(strLogoutTime));//����ǳ�
			int iTypeID=0;
			switch(ck_Send.GetCheck())
			{
			case 0:
				iTypeID=2;
				break;
			case 1:
				iTypeID=1;
				break;
			}
			_itoa(iTypeID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::CG2_TypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_UserShoppingInfo_Query);//��ǰ��״̬Ϊ���Ͳ�ѯ����

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// ���շ�����Ϣ
LRESULT CCG2UserShoppingInfo::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	//OperationCG2 theApp.operCG2;
	CIni mIni;

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	socketdata.DeBody(lpReceive,bodyLength);

	int pageCount = 0;

	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::CG2_UserShoppingInfo_Query_Resp ://��ѯ���������Ϣ�Ļ�Ӧ
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

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
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	return false;
}

// �رնԻ���
void CCG2UserShoppingInfo::OnBnClickedUicancel()
{
	//OperationCG2 theApp.operCG2;
	/*dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Close");//�رմ���
	OnClose();*/
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	ck_Send.SetCheck(1);
	ck_Recv.SetCheck(0);
	SYSTEMTIME sys; 
	GetLocalTime( &sys );
	dtcBeginDate.SetTime(sys);
	dtcEndDate.SetTime(sys);
	nItem = -1;//��������б�û��ѡ����
	pageInfo = false;//��������б��ܷ�ҳ	
	cmbPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
	while(listResult.DeleteColumn(0)){}//�����������б��е���������


}

// �رնԻ���
void CCG2UserShoppingInfo::OnClose()
{
	DestroyWindow();
	CDialog::OnClose();
}



void CCG2UserShoppingInfo::OnBnClickedCk1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(ck_Send.GetCheck())
	{
	case 0:
		{
			ck_Recv.SetCheck(1);

		}
		break;
	case 1:
		{
			ck_Recv.SetCheck(0);
		}	
		break;
	}
}

void CCG2UserShoppingInfo::OnBnClickedCk2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(ck_Recv.GetCheck())
	{
	case 0:
		{
			ck_Send.SetCheck(1);

		}
		break;
	case 1:
		{
			ck_Send.SetCheck(0);
		}	
		break;
	}
}
