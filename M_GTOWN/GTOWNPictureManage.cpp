// GTOWNPictureManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_GTOWN.h"
#include "GTOWNPictureManage.h"
#include ".\GTOWNPictureManage.h"


// CGTOWNPictureManage �Ի���

IMPLEMENT_DYNAMIC(CGTOWNPictureManage, CDialog)
CGTOWNPictureManage::CGTOWNPictureManage(CWnd* pParent /*=NULL*/)
	: CDialog(CGTOWNPictureManage::IDD, pParent)
{
}

CGTOWNPictureManage::~CGTOWNPictureManage()
{
}

void CGTOWNPictureManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_EDITBANACCOUNT, txtAccount);
	DDX_Control(pDX, IDC_EDITBANREASON, txtReason);
	DDX_Control(pDX, IDC_CMBUPAGE, cmbUPage);
}


BEGIN_MESSAGE_MAP(CGTOWNPictureManage, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_BN_CLICKED(IDC_BTNBAN, OnBnClickedBtnban)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_CBN_SELCHANGE(IDC_CMBUPAGE, OnCbnSelchangeCmbupage)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
END_MESSAGE_MAP()


// CGTOWNPictureManage ��Ϣ�������

BOOL CGTOWNPictureManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// ��ʼ����ʾ�ַ�		
	showUserInfo();

	nItem = 0;// �����û��б�õ��к�
	mItem = 0;// �����ʺŷ�ͣ�б�õ��к�
	pageUInfo = false;
	pageInfo = false;// �ж��Ƿ���Ҫ��ҳ
	ServerIP = "";// ��Ϸ������IP	
	ServerName = "";//��Ϸ����������
	UserAccount = "";// ����ʺ�	
	UserName = "";//����ʺź��ǳ�
	UserState=0;

	SetProp(listUser.GetSafeHwnd(),"�����к�",(HANDLE)0);
	SetProp(listUser.GetSafeHwnd(),"����˳��",(HANDLE)1);

	SetProp(listResult.GetSafeHwnd(),"�����к�",(HANDLE)0);
    SetProp(listResult.GetSafeHwnd(),"����˳��",(HANDLE)1);

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

	if(GrpPage.m_hWnd != NULL)
	{
		GrpPage.GetWindowRect(srcRect);//��ȡGrpPage�Ĵ�С��Ϣ
		grpPHeight = srcRect.bottom - srcRect.top;//�õ�GrpPage�ĸ߶���Ϣ

		newRect.top = rs.top + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listUser��λ��
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//���ú�listResult��λ��
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

void CGTOWNPictureManage::InitUI()
{
	SetWindowText(theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_BanPlayer"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operGTOWN.ReadValue("MGTOWN","Search"));
	SetDlgItemText(IDCANCEL,theApp.operGTOWN.ReadValue("MGTOWN","Close"));

	SetDlgItemText(IDC_LBLHINT,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_LblHint"));	
	SetDlgItemText(IDC_LBLPAGE,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLBANACCOUNT,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLBANREASON,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_reason"));
	SetDlgItemText(IDC_BTNBAN,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_TpgOpen"));
	SetDlgItemText(IDC_BTNRESET,theApp.operGTOWN.ReadValue("MGTOWN","Reset"));

	tbcResult.InsertItem(0,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_tpgPictureStop"));//��ֹͼƬ
	tbcResult.InsertItem(2,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_TpgStopList"));//��ֹͼƬ�б�
	tbcResult.InsertItem(3,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_tpgPictureStart"));//���ͼƬ
}

//�����ݼ���Ӧ
BOOL CGTOWNPictureManage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operGTOWN.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operGTOWN.CopyListInfo(&listResult);
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

//�Զ����ڴ�С
void CGTOWNPictureManage::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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

	if(tbcResult.m_hWnd != NULL)
	{
	    newRect.top = rs.top + 4 + grpHeight;
	    newRect.bottom = newRect.top + tbcHeight;
	    newRect.left = rs.left +10;
    	newRect.right = rs.right - 10;

	    tbcResult.MoveWindow(newRect);//���ú�tbcResult��λ��
	}

	if(GrpPage.m_hWnd != NULL)
	{
	    newRect.top = rs.top + grpHeight + tbcHeight;
	    newRect.bottom = newRect.top + grpPHeight;
	    newRect.left = rs.left +10;
	    newRect.right = rs.right - 10;
  
	    GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listUser��λ��
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//���ú�listResult��λ��
	}
}

//���ñ�����ɫ
HBRUSH CGTOWNPictureManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//��ѯ���������Ϣ
void CGTOWNPictureManage::OnBnClickedOk()
{
	try
	{
		CIni mIni;

		nItem = 0;//��������б�û��ѡ����
		mItem = 0;// �����ʺŷ�ͣ�б�õ��к�
		pageUInfo = false;//�б��ܷ�ҳ	
		pageInfo = false;//�б��ܷ�ҳ		
		cmbUPage.ResetContent();//����б�ҳ�ĸ�ѡ��
		cmbPage.ResetContent();//����б�ҳ�ĸ�ѡ��
		while(listResult.DeleteColumn(0)){}//����б��е���������
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������
		if(ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Warn_SelectServer"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITACCOUNT,Account);//��ȡ����ʺ�
		GetDlgItemText(IDC_EDITNAME,Name);//��ȡ��ҽ�ɫ��
		if((Name == "") && (Account == ""))//����ʺź���ҽ�ɫ��ͬʱΪ��
		{
			showBanList();
			AllStopUserList();//��ѯ���б���ͣ�ʺ��б���Ϣ
		}
		else
		{
			showUserInfo();
			UserInfo();//��ѯ���������Ϣ
		}
	}
	catch(...)
	{
	}
}

// ��ѯ���������Ϣ
void CGTOWNPictureManage::UserInfo()
{
	try
	{		
		CIni mIni;	

		nItem = 0;
		pageUInfo = false;
		cmbUPage.ResetContent();
		while(listUser.DeleteColumn(0)){}

		int index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//ÿҳ��ʾ50����¼

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(Name));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(Account),(unsigned char *)mIni.wcharToChar(Account));//����ʺ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_UserInfo_Query))//���Ͳ�ѯ���������Ϣ������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}

		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_UserInfo"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}	
}

//��ҳ��ѯ���������Ϣ
void CGTOWNPictureManage::OnCbnSelchangeCmbupage()
{
	try
	{	
		if(pageUInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;

			int index = cmbUPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//ÿҳ��ʾ50����¼

			while(listUser.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,6);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(Name));//��ҽ�ɫ��
			socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(Account),(unsigned char *)mIni.wcharToChar(Account));//����ʺ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_UserInfo_Query))//���Ͳ�ѯ���������Ϣ������
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
				dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
			socketdata.Destroy();//����CSocketData�ֲ�����
		}
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_Page"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}
}

// ��ѯ���б���ͣ�ʺ��б���Ϣ
void CGTOWNPictureManage::AllStopUserList()
{
	try
	{				
		CIni mIni;
		
		mItem = -1;
		pageInfo = false;		
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}

		char strInt[10];
		int index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");
		int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP����ҽ�ɫ����ҳ����ÿҳ�ļ�¼����

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(Name));
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(Account),(unsigned char *)mIni.wcharToChar(Account));//����ʺ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_AllStopUser_Query))
		{		
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//���Ͳ�ѯ����
		}

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_UserInfo"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}
}

// ��ҳ���в�ѯ//���б���ͣ���ʺ�
void CGTOWNPictureManage::OnCbnSelchangeCmbpage()
{
	try
	{		
		if(pageInfo)
		{	
			CIni mIni;

			while(listResult.DeleteColumn(0)){}

			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbPage��ǰ������ֵ��1��Ҳ����cmbPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//ÿҳ��ʾ50����¼

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
			if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_AllBanUser_Query))
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//���Ͳ�ѯ����
			}
			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_Page"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}
}

// �����û��б��浱ǰ�к�
void CGTOWNPictureManage::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(tbcResult.GetCurSel() == 0)
	{
		if(listUser.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listUser.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listUser.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// ˫���û��б��л�����
void CGTOWNPictureManage::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		if(listUser.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listUser.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listUser.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�

			if(nItem >= 0)
			{
				

			/*	showBanPlayer();*/

				UpdateData(false);

				UserAccount = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Account"));//��ȡҪ��ͣ������ʺ�
			    UserName = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserNick"));//��ȡҪ��ͣ����ҽ�ɫ��
				userID= atoi(theApp.operGTOWN.GetValueByColName(&listUser, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserID")));//���ID

				ClearPicture();
				//SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);//����Ҫ��ͣ������ʺ�
				//SetDlgItemText(IDC_EDITBANREASON,"");				
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



// ������ͣ�ʺ��б��浱ǰ�к�

void CGTOWNPictureManage::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 2)
	{
		if(listResult.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listResult.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			mItem = listResult.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�
		}
		else
		{
			mItem = -1;
		}
	}
	*pResult = 0;
}

// ˫����ͣ�ʺ��б��л�����

void CGTOWNPictureManage::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		if(listResult.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listResult.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			mItem = listResult.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�

			if(mItem >= 0)
			{
				CIni mIni;				
				showUnbindPlayer();

				UpdateData(false);

				UserAccount = theApp.operGTOWN.GetValueByColName(&listResult, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Account"));//��ȡҪ��������ʺ�
				UserName = theApp.operGTOWN.GetValueByColName(&listResult, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserNick"));//����ǳ�
				userID= atoi(theApp.operGTOWN.GetValueByColName(&listResult, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserID")));//���ID

				SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);//����Ҫ��ͣ������ʺ�
				SetDlgItemText(IDC_EDITBANREASON,"");				
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

//�л�tabCtrlѡ�
void CGTOWNPictureManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	CIni mIni;

	if(tbcResult.GetCurSel()==0)//���ѡ�е������������Ϣ��ҳ��
	{
		showUserInfo();
	}
	else if(tbcResult.GetCurSel()==2)//���ѡ�е��Ƿ�ͣ�ʺ��б��ҳ��
	{
		showBanList();
	}
	else if(tbcResult.GetCurSel()==1)//���ѡ�е��Ƿ�ͣ�ʺŵ�ҳ��
	{
		showBanPlayer();

		UpdateData(false);

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			UserAccount = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Account"));
			UserName = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserNick"));
			userID= atoi(theApp.operGTOWN.GetValueByColName(&listUser, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserID")));//���ID


			SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);
			SetDlgItemText(IDC_EDITBANREASON,"");
		}
		else
		{
			SetDlgItemText(IDC_EDITBANACCOUNT,"");
			SetDlgItemText(IDC_EDITBANREASON,"");
		}
	}
	else if(tbcResult.GetCurSel()==3)//���ѡ�е��ǽ���ʺŵ�ҳ��
	{
		showUnbindPlayer();

		UpdateData(false);

		if((listResult.GetItemCount() > 0) && (mItem >= 0))
		{
			UserAccount = theApp.operGTOWN.GetValueByColName(&listResult, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Account"));
			UserName = theApp.operGTOWN.GetValueByColName(&listResult, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserNick"));
			userID= atoi(theApp.operGTOWN.GetValueByColName(&listResult, mItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserID")));//���ID


			SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);
			SetDlgItemText(IDC_EDITBANREASON,"");
		}
		else
		{
			SetDlgItemText(IDC_EDITBANACCOUNT,"");
			SetDlgItemText(IDC_EDITBANREASON,"");
		}
	}
	else if(tbcResult.GetCurSel()==4)//���ѡ�е��ǲ�ѯ�ʺ���û�б���ͣ��ҳ��
	{
		showSearchPlayer();
		SetDlgItemText(IDC_EDITBANACCOUNT,"");
		SetDlgItemText(IDC_EDITBANREASON,"");
	}
	*pResult = 0;
}


//��ͣ�����ʺ�
void CGTOWNPictureManage::OnBnClickedBtnban()
{
	try
	{
		CIni mIni;		

		CString BanAccount = "";
		txtAccount.GetWindowText(BanAccount);//��ȡ����ʺ�
		if(BanAccount == "")//����ʺŲ���Ϊ��
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_AccountNull"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
			return;
		}				

		CString BanReason = "";
		txtReason.GetWindowText(BanReason);//��ȡ��ͣ����ԭ��
		if((tbcResult.GetCurSel() == 1) || (tbcResult.GetCurSel() == 3))// ѡ����Ƿ�ͣ�����ʺ�
		{	

			if(strlen(BanReason) >= 256)//��ͣ����ԭ����Ϊ��
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_ReasonTooLong"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
				return;
			}
		}
		else if(tbcResult.GetCurSel() == 4)// ѡ����ǲ�ѯ�ʺ���û�б���ͣ
		{
			CString m_ServerName;
			GetDlgItemText(IDC_CMBSERVER,m_ServerName);//��ȡ����������
			if(m_ServerName == "")//���������Ʋ���Ϊ��
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Warn_SelectServer"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��ȡ������IP
		}
		int userbyID = theApp.UserByID;//����ԱID

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�����ĸ�������������IP������ʺš���ͣ����ԭ�򡢲���ԱID
		char strInt[10];
		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char*)mIni.wcharToChar(ServerName));//������name
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(BanAccount),(unsigned char *)mIni.wcharToChar(BanAccount));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::GT_BanReason,CEnumCore::TagFormat::TLV_STRING,strlen(BanReason),(unsigned char *)mIni.wcharToChar(BanReason));//��ͣ����ԭ��

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		_itoa(userID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID

		if(tbcResult.GetCurSel() == 1)
		{

			UserState=0;
			_itoa(UserState,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::GT_UserState,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���״̬
			int midlength = socketdata.EnBody();

			if(theApp.operGTOWN.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_Picture_Stop))//���ͷ�ͣ����ʺŵ�����
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
		        dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
		}
		else if(tbcResult.GetCurSel() == 3)
		{
			UserState=1;
			_itoa(UserState,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::GT_UserState,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���״̬
			int midlength = socketdata.EnBody();

			if(theApp.operGTOWN.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_Picture_Stop))//���ͽ������ʺŵ�����
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
		        dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
		}
		else if(tbcResult.GetCurSel() == 4)
		{
			int midlength = socketdata.EnBody();
			if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_AllBanUser_Query))//���Ͳ�ѯ����ʺ���û�б���ͣ������
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
		        dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
		}		
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//������Ϣ
void CGTOWNPictureManage::OnBnClickedBtnreset()
{
	SetDlgItemText(IDC_EDITBANREASON,"");
	if(tbcResult.GetCurSel() == 4)
	{
		SetDlgItemText(IDC_EDITBANACCOUNT,"");
	}
}


//���ܷ�����Ϣ
LRESULT CGTOWNPictureManage::OnMessageReceive(WPARAM wParam,LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;
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
			if(!ServerList.IsEmpty())
			{
				ServerList.RemoveAll();
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ�������IP
				ServerList.SetAt(i,ServerIP);//��������IP������CMap��Ķ���ServerList��
			}

			theApp.operGTOWN.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_UserInfo_Query_Resp://������ϲ�ѯ�ķ�Ӧ
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					pageUInfo = false;//���ܷ�ҳ		
					cmbUPage.ResetContent();
					while(listUser.DeleteColumn(0)){}
				}
				else
				{
					cmbUPage.ResetContent();
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbUPage.AddString(str);
					}
					cmbUPage.SetCurSel(0);
					if(pageCount == 1)
					{
						pageUInfo = false;
					}
					else
					{
						pageUInfo = true;
					}
				}				
			}
		}
		break;
		//��ͣ����ʺŵĻ�Ӧ
	case CEnumCore::Message_Tag_ID::GT_Picture_Stop_Resp:
	case CEnumCore::Message_Tag_ID::GT_Picture_Clear_Resp:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operGTOWN.ShowResult(result);//��ʾ�������

			//showUserInfo();
			//UserInfo();//��ѯ����ʺ���Ϣ
		}
		break;
		//��ѯ���б���ͣ�ʺŵĻ�Ӧ
	case CEnumCore::Message_Tag_ID::GT_AllStopUser_Query_Resp:
		{
			if(pageInfo)
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					mItem = -1;
					pageInfo = false;					
					cmbPage.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					mItem = 0;
					cmbPage.ResetContent();//��ո�ѡ��
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
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return FALSE;
}

//��ʾ���������Ϣ
void CGTOWNPictureManage::showUserInfo()
{
	tbcResult.SetCurSel(0);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBUPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
}

//��ʾ��ͣ�ʺ�
void CGTOWNPictureManage::showBanPlayer()
{
	tbcResult.SetCurSel(1);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBUPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

	SetDlgItemText(IDC_LBLBANREASON,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_reason"));//��ͣԭ��
	SetDlgItemText(IDC_BTNBAN,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_BtnPost"));//"PM_UI_TpgOpen"));//�ʺŷ�ͣ
	txtAccount.SetReadOnly(true);//����ʺŵ�CEdit��������Ϊֻ������
}

//��ʾ��ͣ�ʺ��б�
void CGTOWNPictureManage::showBanList()
{
	tbcResult.SetCurSel(2);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBUPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
}

//��ʾ����ʺ�
void CGTOWNPictureManage::showUnbindPlayer()
{
	tbcResult.SetCurSel(3);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBUPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

	SetDlgItemText(IDC_LBLBANREASON,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_UnBind"));//���ԭ��
	SetDlgItemText(IDC_BTNBAN,theApp.operGTOWN.ReadValue("MGTOWN","PM_UI_BtnSave"));//����ʺ�

	txtAccount.SetReadOnly(true);//����ʺŵ�CEdit��������Ϊֻ������
}

//��ѯ�ʺ���û�з�ͣ
void CGTOWNPictureManage::showSearchPlayer()
{
	tbcResult.SetCurSel(4);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBUPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

	SetDlgItemText(IDC_BTNBAN,theApp.operGTOWN.ReadValue("MGTOWN","Search"));

	txtAccount.SetReadOnly(false);//����ʺŵ�CEdit����ȡ��ֻ������
}

//�����û�������Ϣ��������������
void CGTOWNPictureManage::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operGTOWN.SortListInfo(&listUser,pNMHDR,pResult);
}

//���������Ϣ��������������
void CGTOWNPictureManage::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operGTOWN.SortListInfo(&listResult,pNMHDR,pResult);
}

//ʹ�ùرհ�ť
void CGTOWNPictureManage::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	showUserInfo();
}

//�رնԻ���
void CGTOWNPictureManage::OnClose()
{
	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Close");//�رմ���

	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CGTOWNPictureManage::ClearPicture()
{

	try
	{
		CIni mIni;


		if (AfxMessageBox("�Ƿ����ͷ��", MB_YESNO) == IDNO) 
		{
			return;
		}

		int userbyID = theApp.UserByID;

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�����ĸ�������������IP��������Name������ǳơ�����ԱID
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_Picture_Clear))//����������ҵ�����״̬������
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