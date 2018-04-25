// WABankManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_WA.h"
#include "ChangeMoney.h"
#include ".\changeMoney.h"


// ChangeMoney �Ի���

IMPLEMENT_DYNAMIC(ChangeMoney, CDialog)
ChangeMoney::ChangeMoney(CWnd* pParent /*=NULL*/)
: CDialog(ChangeMoney::IDD, pParent)
{
}

ChangeMoney::~ChangeMoney()
{
}

void ChangeMoney::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listResult);

	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_LISTCHARACTER, listUser);
	
	DDX_Control(pDX, IDC_CMBUSERPAGE, cmbUPage);
	DDX_Control(pDX, IDC_CKITEMTYPE, ckItemType);
	//DDX_Control(pDX, IDC_LISTITEM, listItem);
	DDX_Control(pDX, IDC_CMB2, cmbItemName);

	DDX_Control(pDX, IDC_CMB1, cmbItemType);
}


BEGIN_MESSAGE_MAP(ChangeMoney, CDialog)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_CBN_SELCHANGE(IDC_CMBUIPAGE, OnCbnSelchangeCmbuipage)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_LISTCHARACTER, OnNMClickListcharacter)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTCHARACTER, OnNMDblclkListcharacter)
	ON_CBN_SELCHANGE(IDC_CMBUSERPAGE, OnCbnSelchangeCmbuserpage)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CKITEMTYPE, OnBnClickedCkitemtype)
	ON_BN_CLICKED(IDC_BTN1, OnBnClickedBtn1)
	ON_BN_CLICKED(IDC_BTN2, OnBnClickedBtn2)
//	ON_BN_CLICKED(IDC_BTRIGHT, OnBnClickedBtright)
//	ON_BN_CLICKED(IDC_BTLEFT, OnBnClickedBtleft)
//	ON_NOTIFY(NM_CLICK, IDC_LISTITEM, OnNMClickListitem)
	ON_CBN_SELCHANGE(IDC_CMB1, OnCbnSelchangeCmb1)
	ON_BN_CLICKED(IDC_BTN3, OnBnClickedBtn3)
END_MESSAGE_MAP()

// ��ʼ���Ի���
BOOL ChangeMoney::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// ��ʼ����ʾ�ַ�

	nItem = -1;
	pageInfo = false;
	pageUInfo = false;
	ServerIP = "";
	UserID = "";
	UserName = "";
	UserNick = "";//��ʼ��һЩ˽�б���

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

		if(listResult.m_hWnd != NULL)
		{
			listResult.MoveWindow(newRect);//���ú�listResult��λ�ã�listResult��listUser��λ����ȫ�ص�
		}
	}


	ShowAddBankItem(SW_HIDE);
	ShowBankMoney(SW_HIDE);

	//maple add/////��־��ѯ������������

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	if(theApp.operWA.GetServerList())//�������е���Ϸ�������б�
	{
		//MessageBox("t");
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void ChangeMoney::InitUI()
{
	//OperationWA theApp.operWA;

	SetWindowText(theApp.operWA.ReadValue("MWA","UIC_UI_UserInfo"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operWA.ReadValue("MWA","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operWA.ReadValue("MWA","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operWA.ReadValue("MWA","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operWA.ReadValue("MWA","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operWA.ReadValue("MWA","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operWA.ReadValue("MWA","UIC_UI_Page"));


	tbcResult.InsertItem(0,theApp.operWA.ReadValue("MWA","UIC_UI_tpgUserInfo"));
	//tbcResult.InsertItem(1,theApp.operWA.ReadValue("MWA","WA_NUIBankInfor"));
	//tbcResult.InsertItem(2,theApp.operWA.ReadValue("MWA","BU_UI_tpgAddBankItem"));
	//tbcResult.InsertItem(2,theApp.operWA.ReadValue("MWA","BU_UI_tpgModiBankMoney"));//BU_UI_tpgModiBodyMoney
	tbcResult.InsertItem(1,theApp.operWA.ReadValue("MWA","BU_UI_tpgModiBodyMoney"));
	//MessageBox(theApp.operWA.ReadValue("MWA","BU_UI_tpgModiBodyMoney"));
	//tbcResult.InsertItem(3,theApp.operWA.ReadValue("MWA","BU_UI_tpgMultiAddBankItem"));
	///////////////////////////
	//////////////////////////
	SetDlgItemText(IDC_GRPSEARCH,theApp.operWA.ReadValue("MWA","UIC_UI_GrpSearch"));

	SetDlgItemText(IDC_LBLSERVER,theApp.operWA.ReadValue("MWA","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operWA.ReadValue("MWA","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operWA.ReadValue("MWA","Search"));
	SetDlgItemText(IDCANCEL,theApp.operWA.ReadValue("MWA","Reset"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operWA.ReadValue("MWA","UIC_UI_Page"));
	SetDlgItemText(IDC_LBLSELFTYPE,theApp.operWA.ReadValue("MWA","UIC_UI_SelfType"));
	/////////////////////////
	////////////////////////

}

// �Զ��ı��С
void ChangeMoney::OnSize(UINT nType, int cx, int cy)
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

		if(listResult.m_hWnd != NULL)
		{
			listResult.MoveWindow(newRect);//���ú�listResult��λ��
		}
	}
}

//���ñ�����ɫ
HBRUSH ChangeMoney::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ���������Ϣ
void ChangeMoney::OnBnClickedUisearch()
{
	try
	{
		CIni mIni;

		tbcResult.SetCurSel(0);
		ShowBankMoney(SW_HIDE);
		ShowMultiAdd(SW_HIDE);
		GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б����ܷ�ҳ	
		cmbUPage.ResetContent();//�����������б���ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);

		UpdateData(true);			

		CString m_ServerName;
		GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//��ȡ��Ϸ������������
		if(m_ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_SelectServer"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//��ȡ����ʺ�
		GetDlgItemText(IDC_EDITUINICK,UserNick);//��ȡ����ǳ�
		if((UserName == "") && (UserNick == ""))//����ʺź�����ǳƲ���ͬʱΪ��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_InputAccount"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		UserInfo();// ��ѯ���������Ϣ
	}
	catch(...)
	{
	}
}

// ��ѯ���������Ϣ
void ChangeMoney::UserInfo()
{	
	try
	{		
		CIni mIni;		

		int index = theApp.operWA.ReadIntValue("MWA","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б����ܷ�ҳ	
		cmbUPage.ResetContent();//�����������б���ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query);//���Ͳ�ѯ���������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_UserInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// ��ҳ��ѯ���������Ϣ
void ChangeMoney::OnCbnSelchangeCmbuserpage()
{	
	try
	{	
		if(pageUInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;
			//OperationWA theApp.operWA;	

			int index = cmbUPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//ÿҳ��ʾ50����¼

			while(listUser.DeleteColumn(0)){}//���ҳ������

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query );//���Ͳ�ѯ���������Ϣ������

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// �����û��б����浱ǰ�к�
void ChangeMoney::OnNMClickListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
{
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
void ChangeMoney::OnNMDblclkListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
{
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
				

				CIni mIni;
				pageInfo = false;
				cmbPage.ResetContent();
				while(listResult.DeleteColumn(0)){}// �������б��е���������


				GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);

				UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_ACCOUNT"));
				UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));
               tbcResult.SetCurSel(1);
              //��ʾ�޸Ľ�Ǯ
			   GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			   GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			   GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			   GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			   GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			   GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			   ShowMultiAdd(SW_HIDE);
			   ShowAddBankItem(SW_HIDE);
			   ShowBankMoney(SW_SHOW);
			   if((listUser.GetItemCount() > 0) && (nItem >= 0))
			   {
				   UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// ����ѡ�е�����ʺ�
				   UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserID"));// ����ѡ�е����ID
				   UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// ����ѡ�е�����ǳ�
                   CString    moneycount = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Money"));// ����ѡ����ҽ�Ǯ����

				   SetDlgItemText(IDC_ED1,UserNick);
				   SetDlgItemText(IDC_ED7,moneycount);
			   }
			   //��ʾ�޸Ľ�Ǯ����
				//BankItem();// ��ѯ������Ʒ
			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

// �л�ѡ����в�ѯ
void ChangeMoney::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{		
	switch(tbcResult.GetCurSel())
	{
	case 0:
		{
			ShowAddBankItem(SW_HIDE);
			ShowBankMoney(SW_HIDE);
			ShowMultiAdd(SW_HIDE);
			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
            //UserInfo();

		}
		break;
	case 1:
		{
			//CIni mIni;
			//pageInfo = false;
			//cmbPage.ResetContent();
			//while(listResult.DeleteColumn(0)){}// �������б��е���������

			//GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			//GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			//GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
			//GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			//GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			//GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);

			//ShowAddBankItem(SW_HIDE);
			//ShowMultiAdd(SW_HIDE);
			//ShowBankMoney(SW_HIDE);

			//if((listUser.GetItemCount() > 0) && (nItem >= 0))
			//{
			//	UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserName"));// ����ѡ�е�����ʺ�
			//	UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserID"));// ����ѡ�е����ID
			//	UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_nickname"));// ����ѡ�е�����ǳ�

			//	BankItem();// ��ѯ��ɫ��������
			//}
			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			ShowMultiAdd(SW_HIDE);
			ShowAddBankItem(SW_HIDE);
			ShowBankMoney(SW_SHOW);
			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// ����ѡ�е�����ʺ�
				UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserID"));// ����ѡ�е����ID
				UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// ����ѡ�е�����ǳ�
                CString moneycount = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Money"));// ����ѡ����ҽ�Ǯ����

				SetDlgItemText(IDC_ED1,UserNick);
				SetDlgItemText(IDC_ED7,moneycount);
			}
		}
		break;
	case 2:
		{
			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			ShowMultiAdd(SW_HIDE);
			ShowBankMoney(SW_HIDE);
			ShowAddBankItem(SW_SHOW);

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserName"));// ����ѡ�е�����ʺ�
				UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserID"));// ����ѡ�е����ID
				UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_nickname"));// ����ѡ�е�����ǳ�

				SetDlgItemText(IDC_ED1,UserName);

				ItemType();

			}
		}
		break;
	case 3:
		{
			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			ShowMultiAdd(SW_HIDE);
			ShowAddBankItem(SW_HIDE);
			ShowBankMoney(SW_SHOW);
			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserName"));// ����ѡ�е�����ʺ�
				UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserID"));// ����ѡ�е����ID
				UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_nickname"));// ����ѡ�е�����ǳ�

				SetDlgItemText(IDC_ED1,UserName);

				BankInfo();

			}	
		}
		break;
	case 4:
		{
			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			ShowAddBankItem(SW_HIDE);
			ShowBankMoney(SW_HIDE);
			ShowMultiAdd(SW_SHOW);

		}
		break;
	default:
		break;
	}
	*pResult = 0;
}

// ���д����Ϣ
void ChangeMoney::BankInfo()
{
	//OperationWA theApp.operWA;	
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BankItemInfo_Query );

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Item"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// ��ѯ������Ʒ��Ϣ
void ChangeMoney::BankItem()
{
	//OperationWA theApp.operWA;	
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BankItemInfo_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Item"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}


// ��ҳ���в�ѯ
void ChangeMoney::OnCbnSelchangeCmbuipage()
{
	//OperationWA theApp.operWA;	
	try
	{
		if(pageInfo)
		{
			CIni mIni;

			int index = cmbPage.GetCurSel() + 1;
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

			while(listResult.DeleteColumn(0)){}

			if((listUser.GetItemCount() > 0) && (nItem>=0))
			{
				CSocketData socketdata;
				socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
				socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
				socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
				socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//���IDKEY

				_itoa(index,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

				_itoa(iPageSize,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


				int midlength = socketdata.EnBody();				
				if(tbcResult.GetCurSel() == 0)
				{
					theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query);// ��ѯ��ɫ��ϸ����
				}
				//else if(tbcResult.GetCurSel() == 2)
				//{
				//	theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BankItemInfo_Query);// ��ѯ��ɫ��������
				//}
				//else if(tbcResult.GetCurSel() == 3)
				//{
				//	theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BankItemInfo_Query);// ��ѯ��ɫ��������
				//}

				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				socketdata.Destroy();
			}
		}		
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Page"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// ���շ�����Ϣ
LRESULT ChangeMoney::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{	
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	//OperationWA theApp.operWA;
	CIni mIni;

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	socketdata.DeBody(lpReceive,bodyLength);

	int pageCount = 0;
 //   CString temp;
	//temp.Format("%s",theApp.m_TagID);
	//MessageBox(temp);
	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��ѯ�������б���Ϣ�Ļ�Ӧ
		{
			//for(int i = 1;i <= socketdata.getQueryNum();i++)
			//{
			//	CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ�������IP
			//	ServerList.SetAt(i,ServerIP);//��������IP������CMap��Ķ���ServerList��
			//}

			//theApp.operWA.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
			if(!ServerList.IsEmpty())
			{
				ServerList.RemoveAll();
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ�������IP
				ServerList.SetAt(i,ServerIP);//��������IP������CMap��Ķ���ServerList��
				//MessageBox(ServerIP);
			}
			theApp.operWA.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Account_Query_Resp://��ѯ���������Ϣ�Ļ�Ӧ
		{
			if(pageUInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operWA.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����

				if(pageCount<0)//ҳ��<=0��˵��û�����ݷ���
				{
					nItem = -1;//����ѡ��ĳһ��
					pageUInfo = false;//���ܷ�ҳ					
					cmbUPage.ResetContent();//���ҳ����ѡ��
					while(listUser.DeleteColumn(0)){}//���CListCtrl����
				}
				else
				{
					nItem = 0;
					cmbUPage.ResetContent();//���ҳ����ѡ���Ա����¹���
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbUPage.AddString(str);//�ڸ�ѡ���й���ҳ����Ϣ
					}
					cmbUPage.SetCurSel(0);//�ڸ�ѡ����ѡ�е�һҳ
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
	case CEnumCore::Message_Tag_ID::WA_Money_Update_Resp://
		{
			theApp.operWA.BuildCombox(&socketdata,&cmbItemType,2);
            UserInfo();//�޸Ľ�Ǯ����
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_BankItemInfo_Query_Resp+1 ://�������Ʋ�ѯ
		{
			theApp.operWA.BuildCombox(&socketdata,&cmbItemName,1);
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_BankItemInfo_Query_Resp+2:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//��ʾ�������
			tbcResult.SetCurSel(1);
			CIni mIni;
			pageInfo = false;
			cmbPage.ResetContent();
			while(listResult.DeleteColumn(0)){}// �������б��е���������
			ShowAddBankItem(SW_HIDE);
			ShowBankMoney(SW_HIDE);
			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);


			BankItem();// ��ѯ��ɫ��������
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_BankItemInfo_Query_Resp+3:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			if(m_tflv.m_tagName==CEnumCore::TagName::MESSAGE)
			{

				theApp.operWA.ShowResult(result);//��ʾ�������
			}
			else
			{
				CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(2);
				result = (LPCTSTR)&m_tflv.lpdata;
				SetDlgItemText(IDC_ED7,result);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_BankItemInfo_Query_Resp+4:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//��ʾ�������
			SetDlgItemText(IDC_ED3,"");
			BankInfo();
		}
		break;
	default:
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

				if(pageCount<0)//ҳ��<=0��˵��û�����ݷ���
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

// �رնԻ���
void ChangeMoney::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// �رնԻ���
void ChangeMoney::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}




void ChangeMoney::ShowAddBankItem(int n_cmdShow)
{
	GetDlgItem(IDC_ED1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ED2)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ED3)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ED4)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ED5)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL2)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL3)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL4)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL5)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBL6)->ShowWindow(n_cmdShow);
	//GetDlgItem(IDC_LBL7)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_CKITEMTYPE)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_CMB1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_CMB2)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTN1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTN2)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTN3)->ShowWindow(n_cmdShow);
	//GetDlgItem(IDC_BTRIGHT)->ShowWindow(n_cmdShow);
	//GetDlgItem(IDC_BTLEFT)->ShowWindow(n_cmdShow);
	//GetDlgItem(IDC_LISTITEM)->ShowWindow(n_cmdShow);



	SetDlgItemText(IDC_LBL1,theApp.operWA.ReadValue("MWA","BU_UI_ROLESNAME"));
	SetDlgItemText(IDC_LBL2,theApp.operWA.ReadValue("MWA","UIC_ItemType"));
	SetDlgItemText(IDC_LBL3,theApp.operWA.ReadValue("MWA","UIC_ItemName"));
	SetDlgItemText(IDC_LBL4,theApp.operWA.ReadValue("MWA","UIC_ItemNumber"));
	SetDlgItemText(IDC_LBL5,theApp.operWA.ReadValue("MWA","UIC_Title"));
	SetDlgItemText(IDC_LBL6,theApp.operWA.ReadValue("MWA","UIC_Context"));

	SetDlgItemText(IDC_BTN1,theApp.operWA.ReadValue("MWA","BU_UI_btnSearch"));
	SetDlgItemText(IDC_BTN2,theApp.operWA.ReadValue("MWA","WA_UI_tpgAddItem"));
	SetDlgItemText(IDC_BTN3,theApp.operWA.ReadValue("MWA","BU_UI_RESET"));

	SetDlgItemText(IDC_CKITEMTYPE,theApp.operWA.ReadValue("MWA","BU_UI_LBLSearchItemType"));
	//SetDlgItemText(IDC_LISTITEM,theApp.operWA.ReadValue("MWA","UIC_PresentItemList"));

	ckItemType.SetCheck(0);

	GetDlgItem(IDC_BTN1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ED4)->ShowWindow(SW_HIDE);



}
void ChangeMoney::ShowBankMoney(int m_cmdShow)
{
	GetDlgItem(IDC_LBL1)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBL2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBL4)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_ED1)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_ED7)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_ED3)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_BTN2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTN3)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_LBL1,theApp.operWA.ReadValue("MWA","BU_UI_ROLESNAME"));
	SetDlgItemText(IDC_LBL2,theApp.operWA.ReadValue("MWA","BU_UI_OLDBANKMONEY"));
	SetDlgItemText(IDC_LBL4,theApp.operWA.ReadValue("MWA","BU_UI_NEWBANKMONEY"));
	SetDlgItemText(IDC_BTN2,theApp.operWA.ReadValue("MWA","BU_UI_SETBANKMONEY"));
}

void ChangeMoney::ShowMultiAdd(int m_cmdShow)
{
	GetDlgItem(IDC_LBL2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_ED4)->ShowWindow(m_cmdShow);


	GetDlgItem(IDC_BTN1)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTN2)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_LBL2,theApp.operWA.ReadValue("MWA","BU_UI_FILEPATH"));
	SetDlgItemText(IDC_BTN1,theApp.operWA.ReadValue("MWA","BU_UI_BROWSE"));
	SetDlgItemText(IDC_BTN2,theApp.operWA.ReadValue("MWA","BU_UI_MULTIADD"));
}



void ChangeMoney::OnBnClickedCkitemtype()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	switch(ckItemType.GetCheck())
	{
	case 0:
		{
			GetDlgItem(IDC_BTN1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ED4)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMB1)->ShowWindow(SW_SHOW);
			SetDlgItemText(IDC_CKITEMTYPE,theApp.operWA.ReadValue("MWA","BU_UI_LBLSearchItemType"));

		}
		break;
	case 1:
		{
			GetDlgItem(IDC_BTN1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_ED4)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMB1)->ShowWindow(SW_HIDE);
			SetDlgItemText(IDC_CKITEMTYPE,theApp.operWA.ReadValue("MWA","BU_UI_LBLItemType"));
		}	
		break;
	}
}
//��ѯģ������
void ChangeMoney::OnBnClickedBtn1()
{
	switch(tbcResult.GetCurSel())
	{
	case 2:
		SearchItem();
		break;
	case 4:
		{
			char path[256];
			GetCurrentDirectory(256,path);
			CFileDialog *lpszOpenFile;    //����һ��CfileDialog����

			lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,"�ļ�����(*.xls)|*.xls||");


			if(lpszOpenFile->DoModal()==IDOK)//�������Ի���ȷ����ť
			{
				CString szGetName;
				szGetName=lpszOpenFile->GetPathName();
				SetDlgItemText(IDC_ED4,szGetName);
				SetCurrentDirectory(path);

			}
			delete lpszOpenFile;
		}
		break;
	default:
		break;
	}
	// TODO: �ڴ����ӿؼ�֪ͨ�����������


}
//��ѯ����
void ChangeMoney::SearchItem()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserName"));// ����ѡ�е�����ʺ�
			UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserID"));// ����ѡ�е����ID
			UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_nickname"));// ����ѡ�е�����ǳ�



			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

			_itoa(1,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��


			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BankItemInfo_Query );

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Item"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	

}
//���ӵ���,�޸����н�Ǯ
void ChangeMoney::OnBnClickedBtn2()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	switch(tbcResult.GetCurSel())
	{
	case 2:
		AddBankItem();
		break;
	case 1:
		ModifyBankMoney();
		break;
	case 4:
		MultiAddBankItem();
		break;
	}
}

//�������е���
void ChangeMoney::AddBankItem()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	try
	{
		CIni mIni;
		CSocketData socketdata;
		socketdata.InitCreate(1,20);//����7��������������IP������ʺš���ɫIDKEY����ɫ�š���ע���������ơ���������

		CString ItemName="";
		CString ItemNumber="";
		char strInt[10];

		/*int itemCount = 0;
		CString rItemName = "";
		CString rItemNum = "";
		for(int i=0;i<listItem.GetItemCount();i++)
		{
		rItemName=listItem.GetItemText(i,0);
		rItemNum=listItem.GetItemText(i,1);
		ItemName += rItemName;
		ItemName += "|";
		ItemNumber+=rItemNum;
		ItemNumber+="|";
		}*/

		GetDlgItemText(IDC_CMB2,ItemName);
		GetDlgItemText(IDC_ED3,ItemNumber);
		UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserName"));// ����ѡ�е�����ʺ�
		UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserID"));// ����ѡ�е����ID
		UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_nickname"));// ����ѡ�е�����ǳ�
		int iCharNo=atoi(theApp.operWA.GetValueByColName(&listUser,nItem,theApp.operWA.ReadValue("MWA","WA_CharNo")));

		_itoa(iCharNo,strInt,10);



		//socketdata.AddTFLV(CEnumCore::TagName::WA_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		//socketdata.AddTFLV(CEnumCore::TagName::WA_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		//socketdata.AddTFLV(CEnumCore::TagName::WA_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ɫ��
		//socketdata.AddTFLV(CEnumCore::TagName::WA_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY
		//socketdata.AddTFLV(CEnumCore::TagName::WA_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//��������
		//socketdata.AddTFLV(CEnumCore::TagName::WA_ItemNum,CEnumCore::TagFormat::TLV_STRING,strlen(ItemNumber),(unsigned char *)mIni.wcharToChar(ItemNumber));//��������

		int midlength = socketdata.EnBody();
		theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BankItemInfo_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
	}

}

//�޸����н�Ǯ
void ChangeMoney::ModifyBankMoney()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	try
	{
		CIni mIni;
		CSocketData socketdata;
		socketdata.InitCreate(1,20);//����7��������������IP������ʺš���ɫIDKEY����ɫ�š���ע���������ơ���������

		CString CurMoney = "";
		CString BankMoney= "";

		char strInt[10];

		GetDlgItemText(IDC_ED7,CurMoney);
		GetDlgItemText(IDC_ED3,BankMoney);
		//UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserName"));// ����ѡ�е�����ʺ�
		//UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserID"));// ����ѡ�е����ID
		//UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_nickname"));// ����ѡ�е�����ǳ�
		int iCharNo=atoi(theApp.operWA.GetValueByColName(&listUser,nItem,theApp.operWA.ReadValue("MWA","WA_NickID")));
		UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// ����ѡ�е�����ʺ�
		UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_NickID"));// ����ѡ�е����ID
		UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// ����ѡ�е�����ǳ�
		_itoa(iCharNo,strInt,10);

		//socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		//socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		//socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ɫ��
		//socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

		int userbyID = theApp.UserByID;
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid
		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//���IDKEY

		socketdata.AddTFLV(CEnumCore::TagName::WA_CurMoney,CEnumCore::TagFormat::TLV_STRING,strlen(CurMoney),(unsigned char *)mIni.wcharToChar(CurMoney));//ԭ�еĽ�Ǯ����
		socketdata.AddTFLV(CEnumCore::TagName::WA_Money,CEnumCore::TagFormat::TLV_STRING,strlen(BankMoney),(unsigned char *)mIni.wcharToChar(BankMoney));//��������

		int midlength = socketdata.EnBody();
		theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Money_Update);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
	}

}
//�����������е���
void ChangeMoney::MultiAddBankItem()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	try
	{
		CIni mIni;
		CSocketData socketdata;
		socketdata.InitCreate(1,20);//����7��������������IP������ʺš���ɫIDKEY����ɫ�š���ע���������ơ���������

		CString strFilePath="";
		CString strUserName="";
		CString strUserID="";
		CString strItemName="";
		CString strItemNum="";


		/////////�����ݿ��ȡ����////////////
		GetDlgItemText(IDC_ED4,strFilePath);
		ReadXls(strFilePath,&strUserName,&strUserID,&strItemName,&strItemNum);
		//socketdata.AddTFLV(CEnumCore::TagName::WA_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		//socketdata.AddTFLV(CEnumCore::TagName::WA_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(strUserName),(unsigned char *)mIni.wcharToChar(strUserName));//����ʺ�
		//socketdata.AddTFLV(CEnumCore::TagName::WA_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(strUserID),(unsigned char *)mIni.wcharToChar(strUserID));//��ɫΨһIDKEY
		//socketdata.AddTFLV(CEnumCore::TagName::WA_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(strItemName),(unsigned char *)mIni.wcharToChar(strItemName));//��������
		//socketdata.AddTFLV(CEnumCore::TagName::WA_ItemNum,CEnumCore::TagFormat::TLV_STRING,strlen(strItemNum),(unsigned char *)mIni.wcharToChar(strItemNum));//��������

		int midlength = socketdata.EnBody();
		theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BankItemInfo_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
	}

}
void ChangeMoney::OnBnClickedBtright()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	//��ȡ��������
	int iPos=((CComboBox*)GetDlgItem(IDC_CMB2))->GetCurSel();//��ǰѡ�е���
	CString ItemName="";
	((CComboBox*)GetDlgItem(IDC_CMB2))->GetLBText(iPos,ItemName); //����nΪ��0��ʼ������ֵ

	//��ȡ��������
	CString ItemNumber;
	GetDlgItemText(IDC_ED3,ItemNumber);
	//if(StrToInt(ItemNumber)<1)
	//{
	//	MessageBox("����������");
	//	return;

	//}

	listItem.InsertItem(0,ItemName);
	listItem.SetItemText(0,1,ItemNumber);
}

void ChangeMoney::OnBnClickedBtleft()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	listItem.DeleteItem(nListItem);
}

void ChangeMoney::OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	if(listItem.GetItemCount() != 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nListItem = listItem.SubItemHitTest(&lvinfo);//���������͵����б���ѡ�е��к�
	}
	else
	{
		nListItem = -1;
	}
	*pResult = 0;
}


//��������ѯ
void ChangeMoney::ItemType()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,5);//����2��������������IP������ʺ�
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�

			_itoa(1,strInt,10);
			//socketdata.AddTFLV(CEnumCore::TagName::WA_TypeID,CEnumCore::TagFormat::TLV_STRING,sizeof(int),(unsigned char *)&strInt);//����ʺ�

			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BankItemInfo_Query );

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_AddItem"),theApp.operWA.ReadValue("MWA","Error"),0);
	}
}

void ChangeMoney::OnCbnSelchangeCmb1()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������


	try
	{		
		CIni mIni;

		int iPos=((CComboBox*)GetDlgItem(IDC_CMB1))->GetCurSel();//��ǰѡ�е���
		CString ItemType="";
		((CComboBox*)GetDlgItem(IDC_CMB1))->GetLBText(iPos,ItemType); //����nΪ��0��ʼ������ֵ

		CSocketData socketdata;
		socketdata.InitCreate(1,3);//����3��������������IP������ʺš��������


		//socketdata.AddTFLV(CEnumCore::TagName::WA_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		//socketdata.AddTFLV(CEnumCore::TagName::WA_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		//socketdata.AddTFLV(CEnumCore::TagName::WA_ItemType,CEnumCore::TagFormat::TLV_STRING,strlen(ItemType),(unsigned char *)mIni.wcharToChar(ItemType));//�������


		int midlength = socketdata.EnBody();
		theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BankItemInfo_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
		//	}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_AddItem"),theApp.operWA.ReadValue("MWA","Error"),0);
	}
}

void ChangeMoney::GetListItem(CString m_ItemName, CString m_ItemNum)
{
	int itemCount = 0;
	CString rItemName = "";
	CString rItemNum = "";
	for(int i=0;i<listItem.GetItemCount();i++)
	{
		rItemName=listItem.GetItemText(i,0);
		rItemNum=listItem.GetItemText(i,1);
		m_ItemName += rItemName;
		m_ItemName += "|";
		m_ItemNum+=rItemNum;
		m_ItemNum+="|";
	}

}


bool ChangeMoney::ReadXls(CString strFilePath,CString* strUserName, CString* strUserID, CString* strItemName, CString* strItemNum)
{
	//try
	//{
	//	CoInitialize(NULL);
	//	_ConnectionPtr m_pConnection;
	//	_RecordsetPtr	m_pRecordset;
	//	CString ConnectionString="";
	//	CString UserName="";
	//	CString UserID="";
	//	CString ItemName="";
	//	CString ItemNum="";
	//	ConnectionString = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=");   
	//	ConnectionString += strFilePath;   //excel   file   name   
	//	ConnectionString += _T(";Extended Properties=\"Excel 8.0;HDR=Yes;IMEX=1\""); 


	//	BSTR resultsString = ConnectionString.AllocSysString();



	//	m_pConnection.CreateInstance(__uuidof(Connection));

	//	m_pConnection->Open(resultsString,"","",adModeUnknown);
	//	m_pRecordset.CreateInstance(__uuidof(Recordset));
	//	m_pRecordset->Open("select * from [Sheet1$]",
	//		m_pConnection.GetInterfacePtr(),
	//		adOpenDynamic,
	//		adLockOptimistic,
	//		adCmdText);

	//	if(m_pRecordset->adoEOF) AfxMessageBox("���ĵ�û������");
	//	while(!m_pRecordset->adoEOF)
	//	{
	//		if(m_pRecordset->GetFields()->GetItem(long(0))->Value.vt==VT_NULL) break;
	//		UserName=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem((long)0)->GetValue());
	//		UserID=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem((long)1)->GetValue());
	//		ItemName=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem((long)2)->GetValue());
	//		ItemNum=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem((long)3)->GetValue());

	//		*strUserName += UserName;
	//		*strUserName += "|";
	//		*strUserID+=UserID;
	//		*strUserID+="|";
	//		*strItemName += ItemName;
	//		*strItemName += "|";
	//		*strItemNum+=ItemNum;
	//		*strItemNum+="|";

	//		m_pRecordset->MoveNext();
	//	}
	//	m_pRecordset->Close();
	//	if(m_pRecordset) m_pRecordset.Release();
	//	m_pConnection->Close();
	//	if(m_pConnection) m_pConnection.Release();
	//	CoUninitialize();

	//}
	//catch(...)
	//{
	//	return false;
	//}

	return true;
}

void ChangeMoney::OnBnClickedBtn3()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	SetDlgItemText(IDC_ED3,"");

}
//������ݼ���Ӧ����
BOOL ChangeMoney::PreTranslateMessage(MSG* pMsg)
{
	//OperationPAL operXD;
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listResult);
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
