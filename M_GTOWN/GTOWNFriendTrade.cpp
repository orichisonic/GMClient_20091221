// GTOWNFriendTrade.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_GTOWN.h"
#include "GTOWNFriendTrade.h"
#include ".\GTOWNFriendTrade.h"


// CGTOWNFriendTrade �Ի���

IMPLEMENT_DYNAMIC(CGTOWNFriendTrade, CDialog)
CGTOWNFriendTrade::CGTOWNFriendTrade(CWnd* pParent /*=NULL*/)
	: CDialog(CGTOWNFriendTrade::IDD, pParent)
{
}

CGTOWNFriendTrade::~CGTOWNFriendTrade()
{
}

void CGTOWNFriendTrade::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbUIPage);
	DDX_Control(pDX, IDC_CMBTYPE, m_cmbType);
}


BEGIN_MESSAGE_MAP(CGTOWNFriendTrade, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
	ON_CBN_SELCHANGE(IDC_CMBUPAGE, OnCbnSelchangeCmbupage)
	ON_CBN_SELCHANGE(IDC_CMBTYPE, OnCbnSelchangeCmbtype)
	ON_CBN_SELCHANGE(IDC_CMBUIPAGE, OnCbnSelchangeCmbuipage)
END_MESSAGE_MAP()


// CGTOWNFriendTrade ��Ϣ�������

BOOL CGTOWNFriendTrade::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// ��ʼ����ʾ�ַ�

	nItem = 0;
	pageInfo = false;
	ServerIP = "";
	UserAccount = "";
	UserName = "";//��ʼ��һЩ˽�б���
	UserID=0;

	ShowUserInfo();//��ʾ�û�������Ϣ

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

void CGTOWNFriendTrade::InitUI()
{
	SetWindowText(theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_UserInfo"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operGTOWN.ReadValue("MGTOWN","Search"));
	SetDlgItemText(IDCANCEL,theApp.operGTOWN.ReadValue("MGTOWN","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_tpgUserInfo"));//��һ�����Ϣ
	tbcResult.InsertItem(1,theApp.operGTOWN.ReadValue("MGTOWN","FT_UI_tpgFriendTrade"));//���������еĽ�ɫ��Ϣ
	tbcResult.InsertItem(2,theApp.operGTOWN.ReadValue("MGTOWN","FT_UI_tpgHelotInfo"));//ū����Ϣ
	tbcResult.InsertItem(3,theApp.operGTOWN.ReadValue("MGTOWN","FT_UI_tpgTradeQueue"));//����
	tbcResult.InsertItem(4,theApp.operGTOWN.ReadValue("MGTOWN","FT_UI_tpgTradeLog"));//������־
}

//�����ݼ���Ӧ����
BOOL CGTOWNFriendTrade::PreTranslateMessage(MSG* pMsg)
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
void CGTOWNFriendTrade::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CGTOWNFriendTrade::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//��ѯ���������Ϣ
void CGTOWNFriendTrade::OnBnClickedSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		CIni mIni;
		

		index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");//��ѯ��һҳ����Ϣ
		iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//ÿҳ��ʾ50����¼

		nItem = 0;//��������б�û��ѡ����
		pageInfo=false;
		cmbPage.ResetContent();
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������
		if(ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Warn_SelectServer"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP
		if(tbcResult.GetCurSel()==3)
		{
			TradeQueue();
		}
		else
		{
			ShowUserInfo();//��ʾ���������Ϣ�Ľ���
			GetDlgItemText(IDC_EDITACCOUNT,Account);//��ȡ����ʺ�//IDC_EDITACCOUNT
			GetDlgItemText(IDC_EDITNAME,Name);//��ȡ��ҽ�ɫ��//IDC_EDITNAME
			if((Account == "") && (Name == ""))//����ʺź���ҽ�ɫ������ͬʱΪ��
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Warn_InputAccount"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}

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
	}
}

// ��ҳ���в�ѯ
void CGTOWNFriendTrade::OnCbnSelchangeCmbpage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{	
		if(pageInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;

			index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//ÿҳ��ʾ50����¼

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

// �����û��б��浱ǰ�к�
void CGTOWNFriendTrade::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// ˫�����������Ϣ���в�ѯ
void CGTOWNFriendTrade::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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

			if(nItem >= 0)
			{
				tbcResult.SetCurSel(1);
				ShowOtherInfo();				

				while(listResult.DeleteColumn(0)){}// �������б��е���������

				UserAccount = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Account"));//����ʺ�
				UserName = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserNick"));//����ǳ�
				UserID= atoi(theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserID")));//���ID

				FriendTrade();//�����ϸ���ϲ�ѯ
			}
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// �л�ѡ����в�ѯ
void CGTOWNFriendTrade::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(tbcResult.GetCurSel() == 0)
	{
		ShowUserInfo();//��ʾ�û�������Ϣ
	}
	else
	{
		ShowOtherInfo();

		while(listResult.DeleteColumn(0)){}// �������б��е���������

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			UserAccount = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Account"));//����ʺ�
			UserName = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserNick"));//����ǳ�
			UserID= atoi(theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserID")));//���ID


			if(tbcResult.GetCurSel()==1)
			{
				FriendTrade();//�����ϸ���ϲ�ѯ
			}
			if(tbcResult.GetCurSel()==2)
			{
				HelotInfo();//��ɫ������Ϣ��ѯ
			}
			if(tbcResult.GetCurSel()==3)
			{
				TradeQueue();//������Ϣ��ѯ
			}
			if(tbcResult.GetCurSel()==4)
			{
				TradeLog();//�����Ϣ��ѯ
			}

		}
	}
	*pResult = 0;
}

//�����ϸ���ϲ�ѯ
void CGTOWNFriendTrade::FriendTrade()
{
	try
	{		
		CIni mIni;

		index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");
		iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");

		pageUIInfo=false;
		cmbUIPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_FriendTrade_Info))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_DetailInfo"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}	
}

//��ɫ������Ϣ
void CGTOWNFriendTrade::HelotInfo()
{
	try
	{		
		CIni mIni;

		index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");
		iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");

		pageUIInfo=false;
		cmbUIPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_HelotInfo_Query))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_DetailInfo"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}	
}

//������Ϣ��ѯ
void CGTOWNFriendTrade::TradeQueue()
{
	try
	{		
		CIni mIni;

		index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");
		iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");

		pageUIInfo=false;
		cmbUIPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		int iType=m_cmbType.GetCurSel();
		_itoa(iType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_Type,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID


		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_FriendTrade_Queue))//����������Ϣ��ѯ
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_DetailInfo"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}	
}

//�����Ϣ��ѯ
void CGTOWNFriendTrade::TradeLog()
{
	try
	{		
		CIni mIni;

		index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");
		iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");

		pageUIInfo=false;
		cmbUIPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_FriendTrade_Log))//���ͽ����Ϣ��ѯ
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_DetailInfo"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}	
}


// ���շ�����Ϣ
LRESULT CGTOWNFriendTrade::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::GT_UserInfo_Query_Resp://��ѯ���������Ϣ�Ļ�Ӧ
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
					pageInfo = false;//���ܷ�ҳ		
					cmbPage.ResetContent();
					while(listUser.DeleteColumn(0)){}
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
	case CEnumCore::Message_Tag_ID::GT_FriendTrade_Queue_Resp://��ѯ���������Ϣ�Ļ�Ӧ
		{
			if(pageUIInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operGTOWN.BuildNoDataTable(&socketdata,&listResult,&pageCount,index,iPageSize);//����CListCtrl����
			}
			else
			{
				theApp.operGTOWN.BuildNoDataTable(&socketdata,&listResult,&pageCount,index,iPageSize);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					pageUIInfo = false;//���ܷ�ҳ		
					cmbUIPage.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					cmbUIPage.ResetContent();
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbUIPage.AddString(str);
					}
					cmbUIPage.SetCurSel(0);
					if(pageCount == 1)
					{
						pageUIInfo = false;
					}
					else
					{
						pageUIInfo = true;
					}
				}				
			}
		}
		break;
	default:
		{
			if(pageUIInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					pageUIInfo = false;//���ܷ�ҳ		
					cmbUIPage.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					cmbUIPage.ResetContent();
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbUIPage.AddString(str);
					}
					cmbUIPage.SetCurSel(0);
					if(pageCount == 1)
					{
						pageUIInfo = false;
					}
					else
					{
						pageUIInfo = true;
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
void CGTOWNFriendTrade::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operGTOWN.SortListInfo(&listUser,pNMHDR,pResult);
}


//���������Ϣ��������������
void CGTOWNFriendTrade::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operGTOWN.SortListInfo(&listResult,pNMHDR,pResult);
}

//�رնԻ���
void CGTOWNFriendTrade::OnClose()
{
	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Close");//�رմ���	

	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CGTOWNFriendTrade::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	ShowUserInfo();
}

// ��ʾ��ɫ������Ϣ
void CGTOWNFriendTrade::ShowUserInfo()
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
	InitType();
}

// ��ʾ������Ϣ
void CGTOWNFriendTrade::ShowOtherInfo()
{
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
	if(tbcResult.GetCurSel()==3)
	{
		GetDlgItem(IDC_LBLTYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBTYPE)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_LBLTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBTYPE)->ShowWindow(SW_HIDE);
	}
	InitType();
	
}

void CGTOWNFriendTrade::OnCbnSelchangeCmbupage()
{
	try
	{	
		if(pageUIInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;

			int index = cmbUIPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//ÿҳ��ʾ50����¼

			int midlength = 0;
			while(listResult.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

			_itoa(UserID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::GT_UserID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


			switch(tbcResult.GetCurSel())
			{
			case 1:
				{
					midlength=socketdata.EnBody();
					if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_FriendTrade_Info))//�����ʼ���Ϣ����
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}
				break;
			case 2:
				{
					midlength=socketdata.EnBody();
					if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_HelotInfo_Query))//�����ʼ���Ϣ����
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}
				break;
			case 3:
				{
					midlength=socketdata.EnBody();
					if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_FriendTrade_Queue))//�����ʼ���Ϣ����
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}
				break;
			case 4:
				{
					midlength=socketdata.EnBody();
					if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_FriendTrade_Log))//�����ʼ���Ϣ����
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}
				break;
			
			default:
				break;

			}
			socketdata.Destroy();//����CSocketData�ֲ�����
		}
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_Page"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CGTOWNFriendTrade::InitType(void)
{
	m_cmbType.ResetContent();
	m_cmbType.AddString("������");
	m_cmbType.AddString("���±���");
	m_cmbType.AddString("�ʲ����");
	m_cmbType.AddString("�ֽ����");
	m_cmbType.AddString("�ۿ����");
	m_cmbType.SetCurSel(0);

}

void CGTOWNFriendTrade::OnCbnSelchangeCmbtype()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TradeQueue();
}

void CGTOWNFriendTrade::OnCbnSelchangeCmbuipage()
{
	try
	{	
		if(pageUIInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;

			int index = cmbUIPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//ÿҳ��ʾ50����¼

			int midlength = 0;
			while(listResult.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

			_itoa(UserID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::GT_UserID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


			switch(tbcResult.GetCurSel())
			{
			case 1:
				{
					midlength=socketdata.EnBody();
					if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_FriendTrade_Info))//�����ʼ���Ϣ����
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}
				break;
			case 2:
				{
					midlength=socketdata.EnBody();
					if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_HelotInfo_Query))//�����ʼ���Ϣ����
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}
				break;
			case 3:
				{
					midlength=socketdata.EnBody();
					if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_FriendTrade_Queue))//�����ʼ���Ϣ����
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}
				break;
			case 4:
				{
					midlength=socketdata.EnBody();
					if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_FriendTrade_Log))//�����ʼ���Ϣ����
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}
				break;

			default:
				break;

			}
			socketdata.Destroy();//����CSocketData�ֲ�����
		}
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_Page"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}// TODO: �ڴ���ӿؼ�֪ͨ����������
}
