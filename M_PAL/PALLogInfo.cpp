// PALLogInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_PAL.h"
#include "PALLogInfo.h"
#include ".\palloginfo.h"


// CPALLogInfo �Ի���

IMPLEMENT_DYNAMIC(CPALLogInfo, CDialog)
CPALLogInfo::CPALLogInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CPALLogInfo::IDD, pParent)
{
}

CPALLogInfo::~CPALLogInfo()
{
}

void CPALLogInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBBIGTYPE, cmbBigType);
	DDX_Control(pDX, IDC_CMBSMALLTYPE, cmbSmallType);
	DDX_Control(pDX, IDC_DTPSTARTDATE, dtcStartDate);
	DDX_Control(pDX, IDC_DTPENDDATE, dtcEndDate);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
}


BEGIN_MESSAGE_MAP(CPALLogInfo, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_CBN_SELCHANGE(IDC_CMBBIGTYPE, OnCbnSelchangeCmbbigtype)
	ON_BN_CLICKED(IDC_BTNSEARCHLOG, OnBnClickedBtnsearchlog)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
END_MESSAGE_MAP()


// CPALLogInfo ��Ϣ�������

// ��ʼ���Ի���
BOOL CPALLogInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// ��ʼ����ʾ�ַ�

	nItem = 0;
	pageInfo = false;
	ServerIP = "";//��ʼ��������IP
	ServerName = "";//��ʼ����������
	UserAccount = "";
	UserName = "";//��ʼ����ҽ�ɫ��
	BigType = "";//��־����
	bTypeID = 0;//��־����ID
	SmallType = "";//��־С��
	sTypeID = 0;//��־С��ID	
	strStartTime = "";//��ʼʱ��
	strEndTime = "";//����ʱ��

	ShowUserInfo();//��ʾ���������Ϣ����

	SetProp(listUser.GetSafeHwnd(),"�����к�",(HANDLE)0);
    SetProp(listUser.GetSafeHwnd(),"����˳��",(HANDLE)1);

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

	if(tbcResult.m_hWnd != NULL)
	{
		tbcResult.GetWindowRect(srcRect);//��ȡtbcResult�Ĵ�С��Ϣ
		tbcHeight = srcRect.bottom - srcRect.top;//�õ�tbcResult�ĸ߶���Ϣ

		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + tbcHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		tbcResult.MoveWindow(newRect);//���ú�tbcResult��λ��
	}
	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listResult��λ��
	}

	if(GrpPage.m_hWnd != NULL)
	{
		GrpPage.GetWindowRect(srcRect);//��ȡGrpPage�Ĵ�С��Ϣ
		grpPHeight = srcRect.bottom - srcRect.top;//�õ�GrpPage�ĸ߶���Ϣ

		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//���ú�listResult��λ��
	}

	//OperationPAL operPAL;
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	if(theApp.operPAL.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}
	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CPALLogInfo::InitUI()
{
	//OperationPAL operPAL;

	SetWindowText(theApp.operPAL.ReadValue("MPAL","LI_UI_LogInfo"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operPAL.ReadValue("MPAL","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operPAL.ReadValue("MPAL","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLNAME,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblRole"));
	SetDlgItemText(IDSEARCH,theApp.operPAL.ReadValue("MPAL","Search"));
	SetDlgItemText(IDCANCEL,theApp.operPAL.ReadValue("MPAL","Close"));

	SetDlgItemText(IDC_LBLBIGTYPE,theApp.operPAL.ReadValue("MPAL","LI_UI_BigType"));
	SetDlgItemText(IDC_LBLSMALLTYPE,theApp.operPAL.ReadValue("MPAL","LI_UI_SmallType"));
	SetDlgItemText(IDC_LBLSTARTTIME,theApp.operPAL.ReadValue("MPAL","LI_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operPAL.ReadValue("MPAL","LI_UI_EndTime"));
	SetDlgItemText(IDC_BTNSEARCHLOG,theApp.operPAL.ReadValue("MPAL","LI_UI_SearchLog"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operPAL.ReadValue("MPAL","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operPAL.ReadValue("MPAL","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operPAL.ReadValue("MPAL","LI_UI_tpgLogInfo"));
}

//�����ݼ���Ӧ����
BOOL CPALLogInfo::PreTranslateMessage(MSG* pMsg)
{
	//OperationPAL operPAL;
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operPAL.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operPAL.CopyListInfo(&listResult);
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					for(int i=0; i<listUser.GetItemCount(); i++)
					{
					    listUser.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listUser.EnsureVisible(i,false);
					}
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
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
void CPALLogInfo::OnSize(UINT nType, int cx, int cy)
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

	if(tbcResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + tbcHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		tbcResult.MoveWindow(newRect);//���ú�tbcResult��λ��
	}
	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listResult��λ��
	}

	if(GrpPage.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//���ú�listResult��λ��
	}
}

//���ñ�����ɫ
HBRUSH CPALLogInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//��ѯ���������Ϣ
void CPALLogInfo::OnBnClickedSearch()
{
	try
	{
		CIni mIni;
		//OperationPAL operPAL;

		ShowUserInfo();

		int index = theApp.operPAL.ReadIntValue("MPAL","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//ÿҳ��ʾ50����¼

		nItem = 0;//��������б�û��ѡ����
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������
		if(ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Warn_SelectServer"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITACCOUNT,UserAccount);//��ȡ����ʺ�
		GetDlgItemText(IDC_EDITNAME,UserName);//��ȡ��ҽ�ɫ��
		if((UserName == "") && (UserAccount == ""))//����ʺź���ҽ�ɫ������ͬʱΪ��
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Warn_InputAccount"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
	    
		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//��ҽ�ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERINFO))//���Ͳ�ѯ���������Ϣ������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}
}

// �������������Ϣ���浱ǰ�к�
void CPALLogInfo::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listUser.GetItemCount() > 0)//������������Ϣ��Ϊ��
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listUser.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nItem = listUser.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�
	}
	else
	{
		nItem = 0;
	}
	*pResult = 0;
}

// ˫�����������Ϣ�����л�
void CPALLogInfo::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		if(listUser.GetItemCount() > 0)//������������Ϣ��Ϊ��
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listUser.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listUser.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

			if(nItem >= 0)
			{
				ShowLogInfo();//��ʾ��־��Ϣ�б�

				GetAllBigType();//��ȡ���д�����Ϣ
				cmbSmallType.ResetContent();//С���б���Ϊ��

				CTime curTime = CTime::GetCurrentTime();//��ȡϵͳ��ǰʱ��
				dtcStartDate.SetTime(&curTime);//��ʼʱ����Ϊ��ǰʱ��
				dtcEndDate.SetTime(&curTime);//����ʱ����Ϊ��ǰʱ��

				pageInfo=false;//�����־��Ϣ���ܷ�ҳ
				cmbPage.ResetContent();//�����־��Ϣ���ܷ�ҳ
				while(listResult.DeleteColumn(0)){}//��������־��Ϣ

				//OperationPAL operPAL;

			    UserAccount = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// ����ѡ�е�����ʺ�
			    UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// ����ѡ�е���ҽ�ɫ��
			}
		}
		else
		{
			nItem = 0;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// �л�ѡ����в�ѯ
void CPALLogInfo::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		ShowUserInfo();//��ʾ�û���Ϣ����
	}
	else
	{
		ShowLogInfo();//��ʾ��־��Ϣ����

		GetAllBigType();//��ȡ���д�����Ϣ
		cmbSmallType.ResetContent();//С���б���Ϊ��

		CTime curTime = CTime::GetCurrentTime();//��ȡϵͳ��ǰʱ��
		dtcStartDate.SetTime(&curTime);//��ʼʱ����Ϊ��ǰʱ��
		dtcEndDate.SetTime(&curTime);//����ʱ����Ϊ��ǰʱ��

		pageInfo=false;//�����־��Ϣ���ܷ�ҳ
		cmbPage.ResetContent();//�����־��Ϣ���ܷ�ҳ00
		while(listResult.DeleteColumn(0)){}//��������־��Ϣ

		//OperationPAL operPAL;
		UserAccount = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// ����ѡ�е�����ʺ�
	    UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// ����ѡ�е���ҽ�ɫ��
	}
	*pResult = 0;
}

//��ȡ���д�����Ϣ
void CPALLogInfo::GetAllBigType()
{	
	try
	{	
		CIni mIni;	
		//OperationPAL operPAL;

		CSocketData socketdata;	
		socketdata.InitCreate(1,2);//��������������������IP������������

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_LOG_BIGTYPE_QUERY))//���Ͳ�ѯ��־������Ϣ������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}	
}

// ѡ������ѯС��
void CPALLogInfo::OnCbnSelchangeCmbbigtype()
{
	try
	{	
		CIni mIni;	
		//OperationPAL operPAL;

		BigType = "";//��־����
		bTypeID = 0;//��־����ID

		GetDlgItemText(IDC_CMBBIGTYPE,BigType);//��ȡ��־���������
		if(BigType == "")//��־���಻��Ϊ��
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","LI_Warn_BigTypeNULL"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		BigTypeID.Lookup(cmbBigType.GetCurSel()+1,bTypeID);//��CMap��Ķ���BigTypeID�л�ȡ��־����ID

		CSocketData socketdata;	
		socketdata.InitCreate(1,4);//�����ĸ�������������IP�����������ơ���־����ID����־��������
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		
		_itoa(bTypeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LogBigTypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��־����ID
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LogBigType,CEnumCore::TagFormat::TLV_STRING,strlen(BigType),(unsigned char *)mIni.wcharToChar(BigType));//��־����

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_LOG_SMALLTYPE_QUERY))//ͨ����־�����ѯ��־С����Ϣ������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}	
}

// ��ѯ��־��Ϣ
void CPALLogInfo::OnBnClickedBtnsearchlog()
{
	try
	{	
		CIni mIni;	
		//OperationPAL operPAL;

		pageInfo=false;//�����־��Ϣ���ܷ�ҳ
		cmbPage.ResetContent();//�����־��Ϣ���ܷ�ҳ
		while(listResult.DeleteColumn(0)){}//��������־��Ϣ

		BigType = "";//��־����
		bTypeID = 0;//��־����ID
		SmallType = "";//��־С��
		sTypeID = 0;//��־С��ID

		if(UserName == "")//��ҽ�ɫ������Ϊ��
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Warn_InputAccount"), theApp.operPAL.ReadValue("MPAL","Warn"), MB_ICONWARNING+MB_OK);
			return;
		}

		GetDlgItemText(IDC_CMBBIGTYPE,BigType);//��ȡ��־���������
		if(BigType == "")//��־���಻��Ϊ��
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","LI_Warn_BigTypeNULL"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		GetDlgItemText(IDC_CMBSMALLTYPE,SmallType);//��ȡ��־С�������
		if(SmallType == "")//��־С�಻��Ϊ��
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","LI_Warn_SmallTypeNULL"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		BigTypeID.Lookup(cmbBigType.GetCurSel()+1,bTypeID);//��CMap��Ķ���BigTypeID�л�ȡ��־����ID
		SmallTypeID.Lookup(cmbSmallType.GetCurSel()+1,sTypeID);//��CMap��Ķ���SmallTypeID�л�ȡ��־С��ID

		strStartTime = "";//��ʼʱ��
	    strEndTime = "";//����ʱ��

		CTime curTime = CTime::GetCurrentTime();

		CTime StartTime;
		dtcStartDate.GetTime(StartTime);//��ȡ��ʼʱ��

		CTime EndTime;
		dtcEndDate.GetTime(EndTime);//��ȡ����ʱ��

		if(StartTime >= curTime)//��ʼʱ�䲻�ܴ��ڵ�ǰʱ��
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","LI_Warn_StartTime"),theApp.operPAL.ReadValue("MPAL","Warn"),0);
			return;
		}

		if(EndTime <= StartTime)//����ʱ�䲻��С�ڿ�ʼʱ��
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","LI_Warn_TimeSpan"),theApp.operPAL.ReadValue("MPAL","Warn"),0);
			return;
		}
		strStartTime = StartTime.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��
		strEndTime = EndTime.Format("%Y-%m-%d %H:%M:%S");//���ý���ʱ��

		int index = theApp.operPAL.ReadIntValue("MPAL","index");//ҳ��
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//ҳ���¼��

		CSocketData socketdata;	
		socketdata.InitCreate(1,11);//����ʮһ��������������IP�����������ơ���ɫ���ơ���־����ID����־�������ơ���־С��ID����־С�����ơ���ʼʱ�䡢����ʱ�䡢ҳ����ҳ���¼��
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//��ҽ�ɫ��
		
		_itoa(bTypeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LogBigTypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��־����ID
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LogBigType,CEnumCore::TagFormat::TLV_STRING,strlen(BigType),(unsigned char *)mIni.wcharToChar(BigType));//��־����
		
		_itoa(sTypeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LogSmallTypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��־С��ID
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LogSmallType,CEnumCore::TagFormat::TLV_STRING,strlen(SmallType),(unsigned char *)mIni.wcharToChar(SmallType));//��־С��

		socketdata.AddTFLV(CEnumCore::TagName::PAL_LOGINTIME,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LOGOUTTIME,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//����ʱ��

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_LOGINFO_QUERY))//��ѯ��־��Ϣ
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}	
}

// ��ҳ���в�ѯ
void CPALLogInfo::OnCbnSelchangeCmbpage()
{
	try
	{	
		if(pageInfo)
		{
			CIni mIni;	
			//OperationPAL operPAL;

			while(listResult.DeleteColumn(0)){}//��������־��Ϣ

			int index = cmbPage.GetCurSel() + 1;//ҳ��
			int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//ҳ���¼��

			CSocketData socketdata;	
			socketdata.InitCreate(1,11);//����ʮһ��������������IP�����������ơ���ɫ���ơ���־����ID����־�������ơ���־С��ID����־С�����ơ���ʼʱ�䡢����ʱ�䡢ҳ����ҳ���¼��
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//��ҽ�ɫ��
			
			_itoa(bTypeID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PAL_LogBigTypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��־����ID
			socketdata.AddTFLV(CEnumCore::TagName::PAL_LogBigType,CEnumCore::TagFormat::TLV_STRING,strlen(BigType),(unsigned char *)mIni.wcharToChar(BigType));//��־����
			
			_itoa(sTypeID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PAL_LogSmallTypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��־С��ID
			socketdata.AddTFLV(CEnumCore::TagName::PAL_LogSmallType,CEnumCore::TagFormat::TLV_STRING,strlen(SmallType),(unsigned char *)mIni.wcharToChar(SmallType));//��־С��

			socketdata.AddTFLV(CEnumCore::TagName::PAL_LOGINTIME,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//��ʼʱ��
		    socketdata.AddTFLV(CEnumCore::TagName::PAL_LOGOUTTIME,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//����ʱ��

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			if(theApp.operPAL.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_LOGINFO_QUERY))//��ѯ��־��Ϣ
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
				dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
			socketdata.Destroy();//����CSocketData�ֲ�����
		}
	}
	catch(...)
	{
	}	
}

//�����û���Ϣ��������
void CPALLogInfo::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationPAL operPAL;
	theApp.operPAL.SortListInfo(&listUser,pNMHDR,pResult);
}

//������־�б���Ϣ��������
void CPALLogInfo::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationPAL operPAL;
	theApp.operPAL.SortListInfo(&listResult,pNMHDR,pResult);
}

// ���շ�����Ϣ
LRESULT CPALLogInfo::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;
	//OperationPAL operPAL;
	
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operPAL.ReadValue("MPAL","Main_UI_ParseData"),theApp.operPAL.ReadValue("MPAL","ERROR"),0);		
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
			theApp.operPAL.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERINFO_RESP://��ѯ���������Ϣ�Ļ�Ӧ
		{
			theApp.operPAL.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_LOGINFO_QUERY_RESP://��ѯ�����־��Ϣ�Ļ�Ӧ
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operPAL.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operPAL.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

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
	case CEnumCore::Message_Tag_ID::PAL_LOG_BIGTYPE_QUERY_RESP:
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				bTypeID = atoi((char*)&socketdata.getTLVByName(i,CEnumCore::TagName::PAL_LogBigTypeID).lpdata);//�õ����ߴ���ID
				BigTypeID.SetAt(i,bTypeID);//����־С��ID������CMap��Ķ���SmallTypeID��
			}
			theApp.operPAL.BuildComboxs(&socketdata,&cmbBigType);//������־�����б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_LOG_SMALLTYPE_QUERY_RESP:
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				sTypeID = atoi((char*)&socketdata.getTLVByName(i,CEnumCore::TagName::PAL_LogSmallTypeID).lpdata);//�õ�����С��ID
				SmallTypeID.SetAt(i,sTypeID);//����־С��ID������CMap��Ķ���SmallTypeID��
			}
			theApp.operPAL.BuildComboxs(&socketdata,&cmbSmallType);//������־С���б���Ϣ
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

//��ʾ�û���Ϣ����
void CPALLogInfo::ShowUserInfo()
{
	tbcResult.SetCurSel(0);//��ʾ�û�������Ϣ����
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBIGTYPE)->ShowWindow(SW_HIDE);	
	GetDlgItem(IDC_CMBBIGTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSMALLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSMALLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSTARTTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DTPSTARTDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLENDTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DTPENDDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNSEARCHLOG)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
}

//��ʾ��־��Ϣ����
void CPALLogInfo::ShowLogInfo()
{
	tbcResult.SetCurSel(1);//��ʾ��־��Ϣ����
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBIGTYPE)->ShowWindow(SW_SHOW);	
	GetDlgItem(IDC_CMBBIGTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLSMALLTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBSMALLTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLSTARTTIME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DTPSTARTDATE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLENDTIME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DTPENDDATE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNSEARCHLOG)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
}

//�رնԻ���
void CPALLogInfo::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	ShowUserInfo();
}

// �رնԻ���
void CPALLogInfo::OnClose()
{
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Close");//�رմ���	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!BigTypeID.IsEmpty())
	{
		BigTypeID.RemoveAll();
	}
	if(!SmallTypeID.IsEmpty())
	{
		SmallTypeID.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
