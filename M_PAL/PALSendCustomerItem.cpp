// PALSendCustomerItem.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_PAL.h"
#include "PALSendCustomerItem.h"
#include ".\palsendcustomeritem.h"


// CPALSendCustomerItem �Ի���

IMPLEMENT_DYNAMIC(CPALSendCustomerItem, CDialog)
CPALSendCustomerItem::CPALSendCustomerItem(CWnd* pParent /*=NULL*/)
	: CDialog(CPALSendCustomerItem::IDD, pParent)
{
}

CPALSendCustomerItem::~CPALSendCustomerItem()
{
}

void CPALSendCustomerItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	//DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	//DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_CMBITEMNAME, cmbItemName);
	DDX_Control(pDX, IDC_CHECKBIND, checkBind);
	DDX_Control(pDX, IDC_CHECKNOTBIND, checkNotBind);
	DDX_Control(pDX, IDC_CHECKSTONE, checkStone);
}


BEGIN_MESSAGE_MAP(CPALSendCustomerItem, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDC_CHECKBIND, OnBnClickedCheckbind)
	ON_BN_CLICKED(IDC_CHECKNOTBIND, OnBnClickedChecknotbind)
	ON_BN_CLICKED(IDC_CHECKSTONE, OnBnClickedCheckstone)
	ON_BN_CLICKED(IDC_BTNSEND, OnBnClickedBtnsend)
	ON_BN_CLICKED(IDC_BTQUEIRYITEM, OnBnClickedBtqueiryitem)
END_MESSAGE_MAP()


// CPALSendCustomerItem ��Ϣ�������

// ��ʼ���Ի���
BOOL CPALSendCustomerItem::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitUI();
	nItem = 0;
	pageInfo = false;
	ServerIP = "";
	UserAccount = "";
	UserName = "";//��ʼ��һЩ˽�б���

	ShowUserInfo();//��ʾ�û�������Ϣ

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

		listUser.MoveWindow(newRect);//���ú�listUser��λ��
	}

	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	if(theApp.operPAL.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//�����ݼ���Ӧ����
BOOL CPALSendCustomerItem::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CDialog::PreTranslateMessage(pMsg);
}

// ��ʼ����ʾ�ַ�
void CPALSendCustomerItem::InitUI()
{
	SetWindowText(theApp.operPAL.ReadValue("MPAL","SCI_UI_SendCustomerItem"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operPAL.ReadValue("MPAL","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operPAL.ReadValue("MPAL","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblRole"));
	SetDlgItemText(IDSEARCH,theApp.operPAL.ReadValue("MPAL","Search"));
	SetDlgItemText(IDCANCEL,theApp.operPAL.ReadValue("MPAL","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operPAL.ReadValue("MPAL","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operPAL.ReadValue("MPAL","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operPAL.ReadValue("MPAL","SCI_UI_tpgSendCustomerItem"));
}
// �Զ��ı��С
void CPALSendCustomerItem::OnSize(UINT nType, int cx, int cy)
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

		listUser.MoveWindow(newRect);//���ú�listUser��λ��
	}

	
}

//���ñ�����ɫ
HBRUSH CPALSendCustomerItem::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ���������Ϣ
void CPALSendCustomerItem::OnBnClickedSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}
}

// �����û��б��浱ǰ�к�
void CPALSendCustomerItem::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

			UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// ����ѡ�е���ҽ�ɫ��
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// �л�ѡ����в�ѯ
void CPALSendCustomerItem::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(tbcResult.GetCurSel() == 0)
	{
		ShowUserInfo();//��ʾ�û�������Ϣ
	}
	else
	{
		ShowOtherInfo();
		///ItemNameQuery();//װ����ѯ

	}
	*pResult = 0;
}

//��ѯ������
void CPALSendCustomerItem::OnBnClickedBtqueiryitem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ItemNameQuery();
}

//�������Ʋ�ѯ
void CPALSendCustomerItem::ItemNameQuery()
{
	try
	{		
		CIni mIni;


		cmbItemName.ResetContent();

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//��������������������IP��������Name������ǳơ���������,ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name

		//��Ʒ����
		CString ItemName="";
		GetDlgItemText(IDC_ETITEM,ItemName);

		if(ItemName == "")//��Ϸ����������Ϊ��
		{
			MessageBox("������ģ��������!",theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		socketdata.AddTFLV(CEnumCore::TagName::PAL_CustomIter,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_EQUIPMENT_QUERY))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Error_SearchItemName"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}	
}

// ���շ�����Ϣ
LRESULT CPALSendCustomerItem::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	int ItemNameID =0;

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
	case CEnumCore::Message_Tag_ID::PAL_EQUIPMENT_QUERY_RESP://��ѯ������Ʒ��Ϣ�Ļ�Ӧ
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				ItemNameID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::PAL_CustomIterID).lpdata);//�õ����߱��
				ItemNameList.SetAt(i,ItemNameID);//�����߱�ű�����CMap��Ķ���GiftList��
			}

			theApp.operPAL.BuildComboxs(&socketdata,&cmbItemName);//������������б���Ϣ
			cmbItemName.SetCurSel(0);
			
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERINFO_RESP://��ѯ���������Ϣ�Ļ�Ӧ
		{
			theApp.operPAL.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_SENDCUSTOMITEMMAIL_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operPAL.ShowResult(result);//��ʾ���ؽ��
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

// �رնԻ���
void CPALSendCustomerItem::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	SetDlgItemText(IDC_EDITNAME,"");
	ShowUserInfo();
}

void CPALSendCustomerItem::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Close");//�رմ���	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!ItemNameList.IsEmpty())
	{
		ItemNameList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CPALSendCustomerItem::ShowUserInfo(void)
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICSUBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSUBJECT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICCONTENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCONTENT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICMONEY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETMONEY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICITEM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETITEM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTQUEIRYITEM)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTATUS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKBIND)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKNOTBIND)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSENDREASON)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_CHECKSTONE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE0)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE0)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE1)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE2)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE3)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE4)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE5)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE6)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE7)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE8)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSTONE9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSTONE9)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTNSEND)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
}

void CPALSendCustomerItem::ShowOtherInfo(void)
{
	tbcResult.SetCurSel(1);
	checkStone.SetCheck(true);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSUBJECT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSUBJECT)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICCONTENT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETCONTENT)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICMONEY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETMONEY)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICITEM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETITEM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTQUEIRYITEM)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICITEMNAME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBITEMNAME)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICSTATUS)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECKBIND)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECKNOTBIND)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSENDREASON)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_CHECKSTONE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICSTONE0)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE0)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE0,"-1");
	GetDlgItem(IDC_ETSTONE0)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE1)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE1,"-1");
	GetDlgItem(IDC_ETSTONE1)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE2)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE2,"-1");
	GetDlgItem(IDC_ETSTONE2)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE3)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE3,"-1");
	GetDlgItem(IDC_ETSTONE3)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE4)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE4,"-1");
	GetDlgItem(IDC_ETSTONE4)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE5)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE5)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE5,"-1");
	GetDlgItem(IDC_ETSTONE5)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE6)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE6)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE6,"-1");
	GetDlgItem(IDC_ETSTONE6)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE7)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE7)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE7,"-1");
	GetDlgItem(IDC_ETSTONE7)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE8)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE8)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE8,"-1");
	GetDlgItem(IDC_ETSTONE8)->EnableWindow(false);

	GetDlgItem(IDC_STATICSTONE9)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSTONE9)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_ETSTONE9,"-1");
	GetDlgItem(IDC_ETSTONE9)->EnableWindow(false);

	GetDlgItem(IDC_BTNSEND)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);
}

//��Ϊ��
void CPALSendCustomerItem::OnBnClickedCheckbind()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(checkBind.GetCheck() == 1)
		checkNotBind.SetCheck(false);
	else
		checkNotBind.SetCheck(true);
}
//ά��ԭ���涨
void CPALSendCustomerItem::OnBnClickedChecknotbind()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(checkNotBind.GetCheck() ==1)
		checkBind.SetCheck(false);
	else
		checkBind.SetCheck(true);
}

void CPALSendCustomerItem::OnBnClickedCheckstone()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(checkStone.GetCheck() == 1)
	{

		SetDlgItemText(IDC_ETSTONE0,"-1");
		SetDlgItemText(IDC_ETSTONE1,"-1");
		SetDlgItemText(IDC_ETSTONE2,"-1");
		SetDlgItemText(IDC_ETSTONE3,"-1");
		SetDlgItemText(IDC_ETSTONE4,"-1");
		SetDlgItemText(IDC_ETSTONE5,"-1");
		SetDlgItemText(IDC_ETSTONE6,"-1");
		SetDlgItemText(IDC_ETSTONE7,"-1");
		SetDlgItemText(IDC_ETSTONE8,"-1");
		SetDlgItemText(IDC_ETSTONE9,"-1");

		GetDlgItem(IDC_ETSTONE0)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE1)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE2)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE3)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE4)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE5)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE6)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE7)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE8)->EnableWindow(false);
		GetDlgItem(IDC_ETSTONE9)->EnableWindow(false);



	}
	else
	{
		GetDlgItem(IDC_ETSTONE0)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE1)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE2)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE3)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE4)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE5)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE6)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE7)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE8)->EnableWindow(true);
		GetDlgItem(IDC_ETSTONE9)->EnableWindow(true);

		SetDlgItemText(IDC_ETSTONE0,"");
		SetDlgItemText(IDC_ETSTONE1,"");
		SetDlgItemText(IDC_ETSTONE2,"");
		SetDlgItemText(IDC_ETSTONE3,"");
		SetDlgItemText(IDC_ETSTONE4,"");
		SetDlgItemText(IDC_ETSTONE5,"");
		SetDlgItemText(IDC_ETSTONE6,"");
		SetDlgItemText(IDC_ETSTONE7,"");
		SetDlgItemText(IDC_ETSTONE8,"");
		SetDlgItemText(IDC_ETSTONE9,"");
	}

}


//���Ϳ�����Ʒ
void CPALSendCustomerItem::OnBnClickedBtnsend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{		
		CIni mIni;

		///////////////////ȡ�ʼ�����///////////////////////

		CString m_strSubject;
		GetDlgItemText(IDC_ETSUBJECT,m_strSubject);
		if(m_strSubject == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_MailSubject"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		CString m_strContent;
		GetDlgItemText(IDC_ETCONTENT,m_strContent);
		if(m_strContent == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_MailContent"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		CString m_strReason;
		GetDlgItemText(IDC_ETSENDREASON,m_strReason);
		if(m_strReason == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_MailReason"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		int iMoney=0;//�ʼ���Ǯ
		iMoney=GetDlgItemInt(IDC_ETMONEY);
		//int iGift[5]={-1,-1,-1,-1,-1};


		//��Ʒid
		int ItemID=0;
		ItemNameList.Lookup(cmbItemName.GetCurSel()+1,ItemID);//��CMap��Ķ���ItemNameList�л�ȡ

		//��Ʒ����
		CString ItemName="";
		GetDlgItemText(IDC_CMBITEMNAME,ItemName);

		//�Ƿ��
		int bindornot=1;
		if(checkBind.GetCheck() == 1)
			bindornot=1;
		else
			bindornot=0;

		//�Ƿ�ʹ����ʯ
		char szStone[512];
		ZeroMemory(szStone,512);
		if(checkStone.GetCheck() == 1)
			//strStone="-1,-1,-1,-1,-1,-1,-1,-1,-1,-1";
			sprintf(szStone,"%s","-1,-1,-1,-1,-1,-1,-1,-1,-1,-1");
		else
		{
			int iStone = 0,j;
			iStone=GetDlgItemInt(IDC_ETSTONE0);
			j = sprintf(szStone,"%d",iStone);
			j += sprintf(szStone + j,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE1);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE2);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE3);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE4);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE5);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE6);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE7);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE8);
			j += sprintf(szStone + j,"%d",iStone);
			j += sprintf(szStone + j ,"%s",",");

			iStone=GetDlgItemInt(IDC_ETSTONE9);
			j += sprintf(szStone + j,"%d",iStone);
			//j += sprintf(szStone + j ,"%s",",");

		}




		int iUserByID=theApp.UserByID;

		CSocketData socketdata;	
		socketdata.InitCreate(1,15);//��������������������IP��������Name������ǳơ���������,ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		//socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILSUBJECT,CEnumCore::TagFormat::TLV_STRING,strlen(m_strSubject),(unsigned char *)mIni.wcharToChar(m_strSubject));//����
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILCONTENT,CEnumCore::TagFormat::TLV_STRING,strlen(m_strContent),(unsigned char *)mIni.wcharToChar(m_strContent));//����

		_itoa(iMoney,strInt,10);//�ʼ���Ǯ
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILMONEY,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//


		//��Ʒid
		_itoa(ItemID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_CustomIterID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		//��Ʒ����
		socketdata.AddTFLV(CEnumCore::TagName::PAL_CustomIter,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));

		//�Ƿ��
		_itoa(bindornot,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_BindSetup,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		//�Ƿ�ʹ����ʯ//PAL_INHERITID0_NAME
		socketdata.AddTFLV(CEnumCore::TagName::PAL_INHERITID0_NAME,CEnumCore::TagFormat::TLV_STRING,strlen(szStone),(unsigned char *)szStone);//(unsigned char *)mIni.wcharToChar(strStone));//��ʯ����
		
		//ԭ��
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILREASON,CEnumCore::TagFormat::TLV_STRING,strlen(m_strReason),(unsigned char *)mIni.wcharToChar(m_strReason));//ԭ��
		

		_itoa(iUserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid


		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_SENDCUSTOMITEMMAIL))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Error_ADDITEM"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}	
}


