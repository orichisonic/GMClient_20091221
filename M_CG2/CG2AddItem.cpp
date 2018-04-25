// CG2AddItem.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2AddItem.h"
#include ".\cg2additem.h"


// CCG2AddItem �Ի���

IMPLEMENT_DYNAMIC(CCG2AddItem, CDialog)
CCG2AddItem::CCG2AddItem(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2AddItem::IDD, pParent)
{
}

CCG2AddItem::~CCG2AddItem()
{
}

void CCG2AddItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBITEMTYPE, cmbItemType);
	DDX_Control(pDX, IDC_CMBITEMNAME, cmbItemName);
	DDX_Control(pDX, IDC_CMBITEMNUMBER, cmbItemNumber);
	DDX_Control(pDX, IDC_LISTITEM, listItem);
}


BEGIN_MESSAGE_MAP(CCG2AddItem, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_CBN_SELCHANGE(IDC_CMBITEMTYPE, OnCbnSelchangeCmbitemtype)
	ON_BN_CLICKED(IDC_BTRIGHT, OnBnClickedBtright)
	ON_BN_CLICKED(IDC_BTLEFT, OnBnClickedBtleft)
	ON_NOTIFY(NM_CLICK, IDC_LISTITEM, OnNMClickListitem)
	ON_BN_CLICKED(IDC_BTADD, OnBnClickedBtadd)
	ON_BN_CLICKED(IDC_BTRESET, OnBnClickedBtreset)
END_MESSAGE_MAP()


// CCG2AddItem ��Ϣ�������
//��ʼ����ʾ�ַ�
void CCG2AddItem::InitUI()
{
	//OperationCG2 theApp.operCG2;

	SetWindowText(theApp.operCG2.ReadValue("MCG2","CG2_UI_AddItem"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operCG2.ReadValue("MCG2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));
	SetDlgItemText(IDC_BTUPDATE,theApp.operCG2.ReadValue("MCG2","Update"));
	SetDlgItemText(IDC_BTRESET,theApp.operCG2.ReadValue("MCG2","Reset"));

	SetDlgItemText(IDC_BTSEARCH,theApp.operCG2.ReadValue("MCG2","Search"));

	SetDlgItemText(IDC_STATICCHARNICK,theApp.operCG2.ReadValue("MCG2","UIC_CharNick"));
	SetDlgItemText(IDC_CHECKUNSUREQUERY,theApp.operCG2.ReadValue("MCG2","UIC_UnsureQuery"));
	SetDlgItemText(IDC_STATICITEMTYPE,theApp.operCG2.ReadValue("MCG2","UIC_ItemType"));
	SetDlgItemText(IDC_STATICITEMNAME,theApp.operCG2.ReadValue("MCG2","UIC_ItemName"));
	SetDlgItemText(IDC_STATICITEMNUMBER,theApp.operCG2.ReadValue("MCG2","UIC_ItemNumber"));
	SetDlgItemText(IDC_STATICITEMLIST,theApp.operCG2.ReadValue("MCG2","UIC_PresentItemList"));
	SetDlgItemText(IDC_STATICTITLE,theApp.operCG2.ReadValue("MCG2","UIC_Title"));
	SetDlgItemText(IDC_STATICCONTEXT,theApp.operCG2.ReadValue("MCG2","UIC_Context"));
	SetDlgItemText(IDC_BTADD,theApp.operCG2.ReadValue("MCG2","MakeSure"));
	SetDlgItemText(IDC_BTRESET,theApp.operCG2.ReadValue("MCG2","UIC_Reset"));


	tbcResult.InsertItem(0,theApp.operCG2.ReadValue("MCG2","UIC_UI_tpgUserInfo"));//��һ�����Ϣ//
	tbcResult.InsertItem(1,theApp.operCG2.ReadValue("MCG2","CG2_UI_tpgAddItem"));

	GetDlgItem(IDC_STATICCHARNICK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCHARNICK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKUNSUREQUERY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMNUMBER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBITEMTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBITEMNUMBER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTLEFT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRIGHT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMLIST)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICTITLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETTITLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICCONTEXT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCONTEXT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTADD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

	UpdateData(true);
}
//��ʼ���Ի���
BOOL CCG2AddItem::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitUI();

	nItem = -1;
	pageInfo = false;
	pageUInfo = false;
	ServerIP = "";
	UserID = "";
	UserName = "";
	UserNick = "";//��ʼ��һЩ˽�б���
	iCharNo=0;

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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listUser��λ��

		
	}

	////OperationCG2 theApp.operCG2;
	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	theApp.operCG2.GetServerList();//�������е���Ϸ�������б�
	::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//�Զ����ڴ�С
void CCG2AddItem::OnSize(UINT nType, int cx, int cy)
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
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listUser��λ��

			
	}
}


//���ñ�����ɫ
HBRUSH CCG2AddItem::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//�رնԻ���
void CCG2AddItem::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CCG2AddItem::OnBnClickedUicancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

//��һ�����Ϣ


void CCG2AddItem::OnBnClickedUisearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		CIni mIni;
		//OperationCG2 theApp.operCG2;

		tbcResult.SetCurSel(0);//�����Ϣ

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б��ܷ�ҳ	
		cmbPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������


		CString m_ServerName;
		GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//��ȡ��Ϸ������������
		if(m_ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_SelectServer"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//��ȡ����ʺ�
		GetDlgItemText(IDC_EDITUINICK,UserNick);//��ȡ����ǳ�
		if((UserName == "") && (UserNick == ""))//����ʺź�����ǳƲ���ͬʱΪ��
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_InputAccount"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

	    //UserInfo();// ��ѯ���������Ϣ
		UserInfo();
	}
	catch(...)
	{
	}
}

void CCG2AddItem::UserInfo()
{
	//OperationCG2 theApp.operCG2;
	try
	{		
		CIni mIni;		
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б��ܷ�ҳ	
		cmbPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		CSocketData socketdata;		
		socketdata.InitCreate(1,5);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Query);//���Ͳ�ѯ���������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
}


//�л�tabctrl
void CCG2AddItem::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OperationCG2 theApp.operCG2;
	if(tbcResult.GetCurSel()==0)//ѡ�е������������Ϣѡ�
	{
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATICCHARNICK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETCHARNICK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECKUNSUREQUERY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICITEMTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICITEMNUMBER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBITEMTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBITEMNUMBER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTLEFT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICITEMLIST)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICTITLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETTITLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICCONTEXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETCONTEXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTADD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

		UpdateData(true);
	}
	else if(tbcResult.GetCurSel()==1)//ѡ�е�����ӵ���
	{
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICCHARNICK)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ETCHARNICK)->ShowWindow(SW_SHOW);
		////GetDlgItem(IDC_CHECKUNSUREQUERY)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICITEMTYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICITEMNUMBER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBITEMTYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBITEMNUMBER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTLEFT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTRIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICITEMLIST)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_SHOW);
		////GetDlgItem(IDC_STATICTITLE)->ShowWindow(SW_SHOW);
		////GetDlgItem(IDC_ETTITLE)->ShowWindow(SW_SHOW);
		////GetDlgItem(IDC_STATICCONTEXT)->ShowWindow(SW_SHOW);
		////GetDlgItem(IDC_ETCONTEXT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTADD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTRESET)->ShowWindow(SW_SHOW);

		while(listItem.DeleteColumn(0)){}// �������б��е���������

		UpdateData(true);
	}
	*pResult = 0;
}

// �����û��б��浱ǰ�к�
void CCG2AddItem::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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

			nItem = listUser.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

// ˫�����������Ϣ���в�ѯ
void CCG2AddItem::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OperationCG2 theApp.operCG2;

	if(tbcResult.GetCurSel() == 0)
	{
		if(listUser.GetItemCount() > 0)
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
				tbcResult.SetCurSel(1);

				CIni mIni;
				pageInfo = false;
				cmbPage.ResetContent();
				while(listItem.DeleteColumn(0)){}// �������б��е���������

				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_STATICCHARNICK)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_ETCHARNICK)->ShowWindow(SW_SHOW);
				////GetDlgItem(IDC_CHECKUNSUREQUERY)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICITEMTYPE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICITEMNUMBER)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBITEMTYPE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBITEMNUMBER)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTLEFT)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTRIGHT)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICITEMLIST)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_SHOW);
				////GetDlgItem(IDC_STATICTITLE)->ShowWindow(SW_SHOW);
				////GetDlgItem(IDC_ETTITLE)->ShowWindow(SW_SHOW);
				///GetDlgItem(IDC_STATICCONTEXT)->ShowWindow(SW_SHOW);
				///GetDlgItem(IDC_ETCONTEXT)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTADD)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTRESET)->ShowWindow(SW_SHOW);

				UpdateData(true);

				UpdateData(true);

				//OperationCG2 theApp.operCG2;
				UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
				UserID = theApp.operCG2.GetValueByColName(&listUser, nItem,theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ����ѡ�е����ID
				UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// ����ѡ�е�����ǳ�
				iCharNo =atoi(theApp.operCG2.GetValueByColName(&listUser,nItem,theApp.operCG2.ReadValue("MCG2","CG2_CharacterNum")));//����ѡ�е���ҽ�ɫ��

				SetDlgItemText(IDC_ETCHARNICK,UserNick);
				ItemType();
				SetNumber();
			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

//��������ѯ
void CCG2AddItem::ItemType()
{
	//OperationCG2 theApp.operCG2;	
	try
	{		
		CIni mIni;
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,2);//����2��������������IP������ʺ�
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			//socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

			//socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

			//_itoa(index,strInt,10);
			//socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			//_itoa(iPageSize,strInt,10);
			//socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Get_Item_Query );

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_AddItem"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
}

//�л����������Ͽ���м������Ʋ�ѯ
void CCG2AddItem::OnCbnSelchangeCmbitemtype()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iPos=((CComboBox*)GetDlgItem(IDC_CMBITEMTYPE))->GetCurSel();//��ǰѡ�е���
	CString ItemType="";
	((CComboBox*)GetDlgItem(IDC_CMBITEMTYPE))->GetLBText(iPos,ItemType); //����nΪ��0��ʼ������ֵ
	//((CComboBox*)GetDlgItem(IDC_CMBSKILLTYPE))->GetLBText(iPos,SkillType); //����nΪ��0��ʼ������ֵ

	//OperationCG2 theApp.operCG2;	
	try
	{		
		CIni mIni;
		
		//int index = theApp.operCG2.ReadIntValue("MCG2","index");
		//int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		//if((listUser.GetItemCount() > 0) && (nItem>=0))
		//{
			CSocketData socketdata;
			socketdata.InitCreate(1,3);//����3��������������IP������ʺš��������
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_ItemType,CEnumCore::TagFormat::TLV_STRING,strlen(ItemType),(unsigned char *)mIni.wcharToChar(ItemType));//�������

			//socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

			//_itoa(index,strInt,10);
			//socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			//_itoa(iPageSize,strInt,10);
			//socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Get_Item_Detail_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
	//	}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_AddItem"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
	
}
//���õ�������
void CCG2AddItem::SetNumber()
{
	cmbItemNumber.ResetContent();
	cmbItemNumber.AddString("1");
	cmbItemNumber.AddString("2");
	cmbItemNumber.AddString("3");
	cmbItemNumber.AddString("4");
	cmbItemNumber.AddString("5");
	cmbItemNumber.AddString("6");
	cmbItemNumber.AddString("7");
	cmbItemNumber.AddString("8");
	cmbItemNumber.AddString("9");
	cmbItemNumber.AddString("10");
	cmbItemNumber.AddString("11");
	cmbItemNumber.AddString("12");
	cmbItemNumber.SetCurSel(0);

	//��ʼ����ӵ����б��
	//OperationCG2 theApp.operCG2;
	listItem.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);//0,"�û���",LVCFMT_LEFT,70);
	CString ItemName="";
	ItemName=theApp.operCG2.ReadValue("MCG2","UIC_ItemName");
	CString ItemNumber="";
	ItemNumber=theApp.operCG2.ReadValue("MCG2","UIC_ItemNumber");
	listItem.InsertColumn(0,ItemName,LVCFMT_LEFT,170);//(LPCTSTR)theApp.operCG2.ReadValue("MCG2","UIC_ItemName"),LVCFMT_LEFT,120);
	listItem.InsertColumn(1,ItemNumber,LVCFMT_LEFT,70);
	//SetDlgItemText(IDC_BTRESET,theApp.operCG2.ReadValue("MCG2","Reset"));
}

//������͵����б�
void CCG2AddItem::OnBnClickedBtright()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ��������
	int iPos=((CComboBox*)GetDlgItem(IDC_CMBITEMNAME))->GetCurSel();//��ǰѡ�е���
	CString ItemName="";
	((CComboBox*)GetDlgItem(IDC_CMBITEMNAME))->GetLBText(iPos,ItemName); //����nΪ��0��ʼ������ֵ

	//��ȡ��������
	iPos=((CComboBox*)GetDlgItem(IDC_CMBITEMNUMBER))->GetCurSel();//��ǰѡ�е���
	CString ItemNumber="";
	((CComboBox*)GetDlgItem(IDC_CMBITEMNUMBER))->GetLBText(iPos,ItemNumber); //����nΪ��0��ʼ������ֵ

	listItem.InsertItem(0,ItemName);
	listItem.SetItemText(0,1,ItemNumber);
}

//���������б��浱ǰ�к�
void CCG2AddItem::OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(listItem.GetItemCount() != 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nItem = listItem.SubItemHitTest(&lvinfo);//���������͵����б���ѡ�е��к�
	}
	else
	{
		nItem = -1;
	}
	*pResult = 0;
}

//ɾ�����͵����б�
void CCG2AddItem::OnBnClickedBtleft()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	listItem.DeleteItem(nItem);
	
}

//��ӵ���
void CCG2AddItem::OnBnClickedBtadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		CIni mIni;
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//����7��������������IP������ʺš���ɫIDKEY����ɫ�š���ע���������ơ���������

		CString ItemName="";
		CString ItemNumber="";
		//OperationCG2 theApp.operCG2;
		//UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
		ItemName=theApp.operCG2.GetValueByColName(&listItem,nItem,theApp.operCG2.ReadValue("MCG2","CG2_ItemName"));//����ѡ�еĵ�������
		ItemNumber=theApp.operCG2.GetValueByColName(&listItem,nItem,theApp.operCG2.ReadValue("MCG2","CG2_ItemNum"));//����ѡ�еĵ�������

		CString remark="add item";
		//GetDlgItemText(IDC_ETTITLE,remark);
		char strInt[10];
		_itoa(iCharNo,strInt,10);

		

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Remark,CEnumCore::TagFormat::TLV_STRING,strlen(remark),(unsigned char *)mIni.wcharToChar(remark));//��עremark
		socketdata.AddTFLV(CEnumCore::TagName::CG2_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//��������
		socketdata.AddTFLV(CEnumCore::TagName::CG2_ItemNum,CEnumCore::TagFormat::TLV_STRING,strlen(ItemNumber),(unsigned char *)mIni.wcharToChar(ItemNumber));//��������

		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_TypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Insert_Item_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
	}

}


//������ð�ť
void CCG2AddItem::OnBnClickedBtreset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//listItem.DeleteAllItems();
	//SetDlgItemText(IDC_ETTITLE,"");
	//SetDlgItemText(IDC_ETCONTEXT,"");
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICCHARNICK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCHARNICK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKUNSUREQUERY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMNUMBER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBITEMTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBITEMNUMBER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTLEFT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRIGHT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICITEMLIST)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICTITLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETTITLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICCONTEXT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCONTEXT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTADD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

	UpdateData(true);
	UserInfo();
}

//���ܷ�����Ϣ
LRESULT CCG2AddItem::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��ѯ�������б���Ϣ�Ļ�Ӧ
		{

			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ�������IP
				ServerList.SetAt(i,ServerIP);//��������IP������CMap��Ķ���ServerList��
			}

			theApp.operCG2.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Query_Resp://��ѯ���������Ϣ�Ļ�Ӧ
		{
			if(pageUInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����

				if(pageCount<0)//ҳ��<=0��˵��û�����ݷ���
				{
					nItem = -1;//����ѡ��ĳһ��
					pageUInfo = false;//���ܷ�ҳ					
					cmbPage.ResetContent();//���ҳ����ѡ��
					while(listUser.DeleteColumn(0)){}//���CListCtrl����
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
						pageUInfo = false;//ֻ��һҳ���ݣ����ܷ�ҳ
					}
					else
					{
						pageUInfo = true;//�ж�ҳ���ݣ����Է�ҳ
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Get_Item_Query_Resp://��ѯ�������
		{
			theApp.operCG2.BuildPetCombox(&socketdata,&cmbItemType);
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Get_Item_Detail_Query_Resp ://�������Ʋ�ѯ
		{
			theApp.operCG2.BuildJobCombox(&socketdata,&cmbItemName);
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Insert_Item_Query_Resp://��ӵ���
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//��ʾ�������

			tbcResult.SetCurSel(0);
			cmbPage.ResetContent();

			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_STATICCHARNICK)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ETCHARNICK)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKUNSUREQUERY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICITEMTYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICITEMNUMBER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBITEMTYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBITEMNUMBER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTLEFT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTRIGHT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICITEMLIST)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICTITLE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ETTITLE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICCONTEXT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ETCONTEXT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTADD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

			UpdateData(true);

			UserInfo();
		}
		break;
	}


	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}












