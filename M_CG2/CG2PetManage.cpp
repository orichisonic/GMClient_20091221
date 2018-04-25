// CG2PetManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2PetManage.h"
#include ".\CG2PetManage.h"


// CCG2PetManage �Ի���

IMPLEMENT_DYNAMIC(CCG2PetManage, CDialog)
CCG2PetManage::CCG2PetManage(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2PetManage::IDD, pParent)
{
}

CCG2PetManage::~CCG2PetManage()
{
}

void CCG2PetManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_LISTPET, listPet);
	DDX_Control(pDX, IDC_CMBUSERPAGE, cmbUPage);
	DDX_Control(pDX, IDC_CMBPETPAGE, cmbPetPage);
	DDX_Control(pDX, IDC_EDITUSERNAME, editUserName);
	DDX_Control(pDX, IDC_CMBPETNAME, cmbPet);
	DDX_Control(pDX, IDC_EDITNOWLEVEL, m_NowLevel);
}


BEGIN_MESSAGE_MAP(CCG2PetManage, CDialog)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_CBN_SELCHANGE(IDC_CMBUIPAGE, OnCbnSelchangeCmbuipage)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListUser)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListUser)

	ON_NOTIFY(NM_CLICK, IDC_LISTPET, OnNMClickListPet)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTPET, OnNMDblclkListPet)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTNCONFIRM, OnBnClickedBtnconfirm)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
END_MESSAGE_MAP()

// ��ʼ���Ի���
BOOL CCG2PetManage::OnInitDialog()
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

		if(listPet.m_hWnd!=NULL)
		{
			listPet.MoveWindow(newRect);//���ú�listResult��λ�ã�listResult��listUser��λ����ȫ�ص�
		}
	}

	ShowUpdatePet(SW_HIDE);
	ShowAddPet(SW_HIDE);
	ShowUpdatePetLevel(SW_HIDE);
	

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	theApp.operCG2.GetServerList();//�������е���Ϸ�������б�
	::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CCG2PetManage::InitUI()
{
	//OperationCG2 theApp.operCG2;

	SetWindowText(theApp.operCG2.ReadValue("MCG2","CG2_UI_ItemInfo"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operCG2.ReadValue("MCG2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));


	tbcResult.InsertItem(0,theApp.operCG2.ReadValue("MCG2","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgPetInfo"));
	tbcResult.InsertItem(2,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgUpdatePet"));
	tbcResult.InsertItem(3,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgAddPet"));
	tbcResult.InsertItem(4,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgUpdatePetLevel"));
}


// �Զ��ı��С
void CCG2PetManage::OnSize(UINT nType, int cx, int cy)
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

		if(listPet.m_hWnd!=NULL)
		{
			listPet.MoveWindow(newRect);//���ú�listPet��λ��
		}
	}
}

//���ñ�����ɫ
HBRUSH CCG2PetManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ���������Ϣ
void CCG2PetManage::OnBnClickedUisearch()
{
	try
	{
		CIni mIni;
		//OperationCG2 theApp.operCG2;		

		tbcResult.SetCurSel(0);

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б��ܷ�ҳ	
		cmbUPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������
		
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LISTPET)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_HIDE);


		UpdateData(true);			

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

	    UserInfo();// ��ѯ���������Ϣ
	}
	catch(...)
	{
	}
}

// ��ѯ���������Ϣ
void CCG2PetManage::UserInfo()
{	
	//OperationCG2 theApp.operCG2;
	try
	{		
		CIni mIni;		
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б��ܷ�ҳ	
		cmbUPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
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

// ��ҳ��ѯ���������Ϣ
void CCG2PetManage::OnCbnSelchangeCmbuserpage()
{	
	try
	{	
		if(pageUInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;
			//OperationCG2 theApp.operCG2;	
			
			int index = cmbUPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼

			while(listUser.DeleteColumn(0)){}//���ҳ������

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Query );//���Ͳ�ѯ���������Ϣ������

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// �����û��б��浱ǰ�к�
void CCG2PetManage::OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult)
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
void CCG2PetManage::OnNMDblclkListUser(NMHDR *pNMHDR, LRESULT *pResult)
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
				tbcResult.SetCurSel(1);

				CIni mIni;
				pagePetInfo = false;
				cmbPetPage.ResetContent();
				while(listPet.DeleteColumn(0)){}// �������б��е���������
				

				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);



				GetDlgItem(IDC_LISTPET)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_SHOW);



				//OperationCG2 theApp.operCG2;
				UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
				UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ����ѡ�е����ID
			    UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// ����ѡ�е�����ǳ�

				PetInfo();// ��ѯ��ɫ��ϸ����
			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}
// ���������б��浱ǰ�к�
void CCG2PetManage::OnNMClickListPet(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 1)
	{
		if(listPet.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listPet.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nPetItem = listPet.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�
		}
		else
		{
			nPetItem = -1;
		}
	}
	*pResult = 0;
}

// ˫��������Ϣ���в�ѯ
void CCG2PetManage::OnNMDblclkListPet(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 1)
	{
		if(listPet.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listPet.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nPetItem = listPet.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

			if(nPetItem >= 0)
			{
				tbcResult.SetCurSel(2);

				CIni mIni;
				UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
				UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ����ѡ�е����ID
				UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// ����ѡ�е�����ǳ�
				PetID=atoi(theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_PetID")));

				GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_LISTPET)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_HIDE);

				ShowAddPet(SW_HIDE);
				ShowUpdatePetLevel(SW_HIDE);
				ShowUpdatePet(SW_SHOW);
				
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
void CCG2PetManage::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{		
	switch(tbcResult.GetCurSel())
	{
	case 0:
		{
			ShowUpdatePet(SW_HIDE);
			ShowAddPet(SW_HIDE);
			ShowUpdatePetLevel(SW_HIDE);

			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_LISTPET)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

		}
		break;
	case 1:
		{
			ShowUpdatePet(SW_HIDE);
			ShowAddPet(SW_HIDE);
			ShowUpdatePetLevel(SW_HIDE);

			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LISTPET)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_SHOW);


			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			if((listUser.GetItemCount() > 0) && (nItem>=0))
			{
				PetInfo();// ��ѯ��ɫ��������
			}

		}
		break;
	case 2:
		{
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LISTPET)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_HIDE);
			
			ShowAddPet(SW_HIDE);
			ShowUpdatePetLevel(SW_HIDE);
			ShowUpdatePet(SW_SHOW);
			

		}
		break;
	case 3:
		{
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTPET)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_HIDE);

			
			ShowUpdatePetLevel(SW_HIDE);
			ShowUpdatePet(SW_HIDE);
			ShowAddPet(SW_SHOW);

			PetListQuery();
		}
		break;
	case 4:
		{
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTPET)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_HIDE);

			ShowUpdatePet(SW_HIDE);
			ShowAddPet(SW_HIDE);
			ShowUpdatePetLevel(SW_SHOW);
			
		}
		break;
	default:
		break;
	}
	*pResult = 0;
}

// �����������
void CCG2PetManage::PetInfo()
{
	//OperationCG2 theApp.operCG2;	
	try
	{		
		CIni mIni;
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		nPetItem = -1;//��������б�û��ѡ����
		pagePetInfo = false;//��������б��ܷ�ҳ	
		cmbPetPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listPet.DeleteColumn(0)){}//�����������б��е���������

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
			UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ����ѡ�е����ID
			UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// ����ѡ�е�����ǳ�

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//���IDKEY

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_PetInfo_Query );

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_LEVELEXP"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// ���＼����Ϣ
void CCG2PetManage::PetSkill()
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
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//���IDKEY

			_itoa(PetID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::CG2_PetID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_PetSkill_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Item"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}


//  ���³�������
void CCG2PetManage::UpdatePet()
{
	//OperationCG2 theApp.operCG2;

	try
	{		
		CIni mIni;

		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");
		int cg2_charno=0;
		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,20);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
			UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ����ѡ�е����ID
			UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// ����ѡ�е�����ǳ�
			cg2_charno=atoi(theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_CharNo")));

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//���IDKEY

			_itoa(cg2_charno,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID



			if((listPet.GetItemCount() > 0) && (nPetItem>=0))
			{
				PetID=atoi(theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_PetID")));
				PetName=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_PetSrcName"));
				int	 PetAttr0=GetDlgItemInt(IDC_EDITPETATTR0);
				int  PetAttr1=GetDlgItemInt(IDC_EDITPETATTR1);
				int  PetAttr2=GetDlgItemInt(IDC_EDITPETATTR2);
				int  PetAttr3=GetDlgItemInt(IDC_EDITPETATTR3);
				int  PetAttr4=GetDlgItemInt(IDC_EDITPETATTR4);

				_itoa(PetID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetSrcName,CEnumCore::TagFormat::TLV_STRING,strlen(PetName),(unsigned char *)mIni.wcharToChar(PetName));//���IDKEY
				_itoa(PetAttr0,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetPhysical,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID
				_itoa(PetAttr1,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetPower,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID
				_itoa(PetAttr2,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetSmart,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID
				_itoa(PetAttr3,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetSpeed,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID
				_itoa(PetAttr4,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetSpirit,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID


			}



			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Update_Pet_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Item"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}
//�����б�
void CCG2PetManage::PetListQuery()
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
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//���IDKEY


			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_PetList_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Item"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}
// ��ӳ���
void CCG2PetManage::AddPet()
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
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];
			int cg2_charno=0;

			UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
			UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ����ѡ�е����ID
			UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// ����ѡ�е�����ǳ�
			cg2_charno=atoi(theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_CharNo")));

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//���IDKEY

			_itoa(cg2_charno,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID

		

			CString strPetID;
			GetDlgItemText(IDC_CMBPETNAME,PetName);//��ȡ��Ϸ������������
			PetList.Lookup(cmbPet.GetCurSel()+1,strPetID);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

			PetID=atoi(strPetID);
			_itoa(PetID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::CG2_PetID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID

			socketdata.AddTFLV(CEnumCore::TagName::CG2_PetSrcName,CEnumCore::TagFormat::TLV_STRING,strlen(PetName),(unsigned char *)mIni.wcharToChar(PetName));//��������

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_AddPet_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Item"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}


// ���＼����Ϣ
void CCG2PetManage::UpdatePetLevel()
{
	//OperationCG2 theApp.operCG2;

	try
	{		
		CIni mIni;

		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");
		int cg2_charno=0;
		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
			UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ����ѡ�е����ID
			UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// ����ѡ�е�����ǳ�
			cg2_charno=atoi(theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_CharNo")));

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//���IDKEY

			_itoa(cg2_charno,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID

			if((listPet.GetItemCount() > 0) && (nPetItem>=0))
			{
				PetID=atoi(theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_PetID")));
				PetName=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_PetSrcName"));
				int  NewPetLevel=GetDlgItemInt(IDC_EDITPETATTR2);



				_itoa(PetID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetSrcName,CEnumCore::TagFormat::TLV_STRING,strlen(PetName),(unsigned char *)mIni.wcharToChar(PetName));//���IDKEY
				_itoa(NewPetLevel,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_Level,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID


			}

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_UpdatePetLevel_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Item"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}


// ��ҳ���в�ѯ
void CCG2PetManage::OnCbnSelchangeCmbuipage()
{
	//OperationCG2 theApp.operCG2;	
	try
	{
		if(pageInfo)
		{
			CIni mIni;
			
			int index = cmbPage.GetCurSel() + 1;
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");


			if((listUser.GetItemCount() > 0) && (nItem>=0))
			{
				CSocketData socketdata;
				socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
				socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
				socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
				socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//���IDKEY

				_itoa(index,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

				_itoa(iPageSize,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

				
				
				int midlength = socketdata.EnBody();				
				if(tbcResult.GetCurSel() == 1)
				{
					theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_PetInfo_Query);// ��ѯ��ɫ��ϸ����
				}
				else if(tbcResult.GetCurSel() == 2)
				{
					theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_PetSkill_Query);// ��ѯ��ɫ��������
				}
				
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				socketdata.Destroy();
			}
		}		
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Page"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// ���շ�����Ϣ
LRESULT CCG2PetManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{	
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
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
	case CEnumCore::Message_Tag_ID::CG2_PetInfo_Query_Resp://��ѯ������Ϣ�Ļ�Ӧ
		{
			if(pagePetInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listPet,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listPet,&pageCount);//����CListCtrl����

				if(pageCount<0)//ҳ��<=0��˵��û�����ݷ���
				{
					nPetItem = -1;//����ѡ��ĳһ��
					pagePetInfo = false;//���ܷ�ҳ					
					cmbPetPage.ResetContent();//���ҳ����ѡ��
					while(listPet.DeleteColumn(0)){}//���CListCtrl����
				}
				else
				{
					nPetItem = 0;
					cmbPetPage.ResetContent();//���ҳ����ѡ���Ա����¹���
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbPetPage.AddString(str);//�ڸ�ѡ���й���ҳ����Ϣ
					}
					cmbPetPage.SetCurSel(0);//�ڸ�ѡ����ѡ�е�һҳ
					if(pageCount == 1)
					{
						pagePetInfo = false;//ֻ��һҳ���ݣ����ܷ�ҳ
					}
					else
					{
						pagePetInfo = true;//�ж�ҳ���ݣ����Է�ҳ
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_PetList_Query_Resp://�����б�
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString strPetID=(LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::CG2_PetID).lpdata;
				PetList.SetAt(i,strPetID);//��������IP������CMap��Ķ���ServerList��
			}
			theApp.operCG2.BuildPetCombox(&socketdata,&cmbPet);
		}
		break;
	default:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//��ʾ�������
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

// �رնԻ���
void CCG2PetManage::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");

}

// �رնԻ���
void CCG2PetManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}



//���ĳ�������,��ӳ���,���ĳ���ȼ�
void CCG2PetManage::OnBnClickedBtnconfirm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(tbcResult.GetCurSel())
	{
	case 2:
		UpdatePet();
		break;
	case 3:
		AddPet();
		break;
	case 4:
		UpdatePetLevel();
		break;
	}
}

void CCG2PetManage::ShowUpdatePet(int n_cmdShow)
{
	GetDlgItem(IDC_LBLUSERNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBLNOWLEVEL)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBLPETNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBLPETATTR3)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBLPETATTR4)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITPETATTR0)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITPETATTR1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITPETATTR2)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITPETATTR3)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITPETATTR4)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTNCONFIRM)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(n_cmdShow);

	SetDlgItemText(IDC_LBLUSERNAME,theApp.operCG2.ReadValue("MCG2","BU_UI_PETATTR0"));
	SetDlgItemText(IDC_LBLNOWLEVEL,theApp.operCG2.ReadValue("MCG2","BU_UI_PETATTR1"));
	SetDlgItemText(IDC_LBLPETNAME,theApp.operCG2.ReadValue("MCG2","BU_UI_PETATTR2"));
	SetDlgItemText(IDC_LBLPETATTR3,theApp.operCG2.ReadValue("MCG2","BU_UI_PETATTR3"));
	SetDlgItemText(IDC_LBLPETATTR4,theApp.operCG2.ReadValue("MCG2","BU_UI_PETATTR4"));
	SetDlgItemText(IDC_BTNCONFIRM,theApp.operCG2.ReadValue("MCG2","BU_UI_CHANGEPETATTR"));
	SetDlgItemText(IDC_BTNRESET,theApp.operCG2.ReadValue("MCG2","BU_UI_RESET"));
	if((listPet.GetItemCount() > 0) && (nPetItem>=0))
	{
		CString PetAttr0=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_PetPhysical"));
		CString PetAttr1=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_Power"));
		CString PetAttr2=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_Smart"));
		CString PetAttr3=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_Speed"));
		CString PetAttr4=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_Spirit"));
		SetDlgItemText(IDC_EDITPETATTR0,PetAttr0);
		SetDlgItemText(IDC_EDITPETATTR1,PetAttr1);
		SetDlgItemText(IDC_EDITPETATTR2,PetAttr2);
		SetDlgItemText(IDC_EDITPETATTR3,PetAttr3);
		SetDlgItemText(IDC_EDITPETATTR4,PetAttr4);

	}
}

void CCG2PetManage::ShowAddPet(int n_cmdShow)
{
	GetDlgItem(IDC_LBLUSERNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITUSERNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBLPETNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_CMBPETNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTNCONFIRM)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(n_cmdShow);

	SetDlgItemText(IDC_LBLUSERNAME,theApp.operCG2.ReadValue("MCG2","BU_UI_USERNAME"));
	SetDlgItemText(IDC_LBLPETNAME,theApp.operCG2.ReadValue("MCG2","BU_UI_PETNAME"));
	SetDlgItemText(IDC_BTNCONFIRM,theApp.operCG2.ReadValue("MCG2","BU_UI_ADDPET"));
	SetDlgItemText(IDC_BTNRESET,theApp.operCG2.ReadValue("MCG2","BU_UI_RESET"));
	if((listUser.GetItemCount() > 0) && (nItem>=0))
	{
		UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
		SetDlgItemText(IDC_EDITUSERNAME,UserName);
		editUserName.SetReadOnly(true);
	}

}

void CCG2PetManage::ShowUpdatePetLevel(int n_cmdShow)
{
	GetDlgItem(IDC_LBLUSERNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITUSERNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBLNOWLEVEL)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITNOWLEVEL)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBLPETNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITPETATTR2)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTNCONFIRM)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(n_cmdShow);

	SetDlgItemText(IDC_LBLUSERNAME,theApp.operCG2.ReadValue("MCG2","BU_UI_PETNAME"));
	SetDlgItemText(IDC_LBLNOWLEVEL,theApp.operCG2.ReadValue("MCG2","BU_UI_NOWLEVEL"));
	SetDlgItemText(IDC_LBLPETNAME,theApp.operCG2.ReadValue("MCG2","BU_UI_NEWLEVEL"));
	SetDlgItemText(IDC_BTNCONFIRM,theApp.operCG2.ReadValue("MCG2","BU_UI_CHANGELEVEL"));
	SetDlgItemText(IDC_BTNRESET,theApp.operCG2.ReadValue("MCG2","BU_UI_RESET"));
	if((listPet.GetItemCount() > 0) && (nPetItem>=0))
	{
		PetName = theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_PetSrcName"));// ����ѡ�еĳ���
		CString nowLevel=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_Level"));
		SetDlgItemText(IDC_EDITUSERNAME,PetName);
		SetDlgItemText(IDC_EDITNOWLEVEL,nowLevel);
		SetDlgItemText(IDC_EDITPETATTR2,nowLevel);
		editUserName.SetReadOnly(true);
		m_NowLevel.SetReadOnly(true);
	}
}
//����һ��
void CCG2PetManage::OnBnClickedBtnreset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(tbcResult.GetCurSel())
	{
	case 2:
		ShowUpdatePet(SW_SHOW);
		break;
	case 3:
		ShowAddPet(SW_SHOW);
		break;
	case 4:
		ShowUpdatePetLevel(SW_SHOW);
		break;
	}
}
