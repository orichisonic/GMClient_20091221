// XDGMManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_XD.h"
#include "XDGMManage.h"


// CXDGMManage �Ի���

IMPLEMENT_DYNAMIC(CXDGMManage, CDialog)
CXDGMManage::CXDGMManage(CWnd* pParent /*=NULL*/)
	: CDialog(CXDGMManage::IDD, pParent)
{
}

CXDGMManage::~CXDGMManage()
{
}

void CXDGMManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);

	DDX_Control(pDX, IDC_TABRESULT, tbcResult);

	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBBASIC, cmbBasic);
	DDX_Control(pDX, IDC_LISTBASIC, listBasic);
	DDX_Control(pDX, IDC_CMBLIST, cmbList);
}


BEGIN_MESSAGE_MAP(CXDGMManage, CDialog)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_CMBBASIC, OnCbnSelchangeCmbbasic)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTBASIC, OnNMClickListbasic)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTBASIC, OnNMDblclkListbasic)

	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	
	ON_BN_CLICKED(IDC_BTNEDIT, OnBnClickedBtnedit)
	ON_BN_CLICKED(IDC_BTNRECOVER, OnBnClickedBtnrecover)
END_MESSAGE_MAP()


// CXDGMManage ��Ϣ�������

// ��ʼ���Ի���
BOOL CXDGMManage::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// ��ʼ����ʾ�ַ�

	nItem = -1;
	pageBasic = false;
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

	if(listBasic.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listBasic.MoveWindow(newRect);//���ú�listBasic��λ��
	}

	dlgStatus = theApp.operXD.ReadIntValue("MXD","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	if(theApp.operXD.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CXDGMManage::InitUI()
{
	SetWindowText(theApp.operXD.ReadValue("MXD","GMM_UI_GMManage"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operXD.ReadValue("MXD","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operXD.ReadValue("MXD","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operXD.ReadValue("MXD","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operXD.ReadValue("MXD","Search"));
	SetDlgItemText(IDCANCEL,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operXD.ReadValue("MXD","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operXD.ReadValue("MXD","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operXD.ReadValue("MXD","GMM_UI_TransferXYZ"));	
	tbcResult.InsertItem(2,theApp.operXD.ReadValue("MXD","GMM_UI_TransferGM"));
	tbcResult.InsertItem(3,theApp.operXD.ReadValue("MXD","GMM_UI_GMTransfer"));
	tbcResult.InsertItem(4,theApp.operXD.ReadValue("MXD","GMM_UI_BuffEdit"));

	SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNICK,theApp.operXD.ReadValue("MXD","UIC_UI_lblNick"));
	SetDlgItemText(IDC_LBLGMNAME,theApp.operXD.ReadValue("MXD","GMM_UI_GMName"));
	SetDlgItemText(IDC_LBLCOORDINATE,theApp.operXD.ReadValue("MXD","GMM_UI_Coordinate"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","Move"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_EDITX,"0");
	SetDlgItemText(IDC_EDITY,"0");
	SetDlgItemText(IDC_EDITZ,"0");
}

// �Զ��ı��С
void CXDGMManage::OnSize(UINT nType, int cx, int cy)
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

	if(listBasic.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listBasic.MoveWindow(newRect);//���ú�listBasic��λ��
	}
}

//���ñ�����ɫ
HBRUSH CXDGMManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ���������Ϣ
void CXDGMManage::OnBnClickedSearch()
{
	try
	{
		CIni mIni;

		tbcResult.SetCurSel(0);

		nItem = -1;//��������б�û��ѡ����
		pageBasic = false;//��������б��ܷ�ҳ	
		cmbBasic.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listBasic.DeleteColumn(0)){}//�����������б��е���������

		ShowCoordinate(SW_HIDE);
		ShowTransferGM(SW_HIDE);
		ShowEditBuff(SW_HIDE);
		ShowUserInfo(SW_SHOW);

		UpdateData(true);

		CString m_ServerName;
		GetDlgItemText(IDC_CMBSERVER,m_ServerName);//��ȡ��Ϸ������������
		if(m_ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_SelectServer"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//��ȡ����ʺ�
		GetDlgItemText(IDC_EDITUINICK,UserNick);//��ȡ����ǳ�
		if((UserName == "") && (UserNick == ""))//����ʺź�����ǳƲ���ͬʱΪ��
		{
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_InputAccount"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		UserInfo();// ��ѯ���������Ϣ
	}
	catch(...)
	{
	}
}

// ��ѯ���������Ϣ
void CXDGMManage::UserInfo()
{	
	try
	{		
		CIni mIni;		

		int index = theApp.operXD.ReadIntValue("MXD","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//��������б�û��ѡ����
		pageBasic = false;//��������б��ܷ�ҳ	
		cmbBasic.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listBasic.DeleteColumn(0)){}//�����������б��е���������

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_SEARCHTYPE,CEnumCore::TagFormat::TLV_STRING,strlen("1"),(unsigned char *)mIni.wcharToChar("1"));//��������

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Account_Query);//���Ͳ�ѯ���������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_UserInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

// ��ҳ��ѯ���������Ϣ
void CXDGMManage::OnCbnSelchangeCmbbasic()
{	
	try
	{	
		if(pageBasic)//������Է�ҳ�Ļ�
		{
			CIni mIni;	

			int index = cmbBasic.GetCurSel() + 1;//ҳ��ΪcmbBasic��ǰ������ֵ��1��Ҳ����cmbBasic�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//ÿҳ��ʾ50����¼

			while(listBasic.DeleteColumn(0)){}//���ҳ������

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_SEARCHTYPE,CEnumCore::TagFormat::TLV_STRING,strlen("1"),(unsigned char *)mIni.wcharToChar("1"));//��������

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Account_Query);//���Ͳ�ѯ���������Ϣ������

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// ��������������Ϣ���浱ǰ�к�
void CXDGMManage::OnNMClickListbasic(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listBasic.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listBasic.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listBasic.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

// ˫������������Ϣ���в�ѯ
void CXDGMManage::OnNMDblclkListbasic(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listBasic.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listBasic.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listBasic.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

			if(nItem >= 0)
			{
				ShowUserInfo(SW_HIDE);
				ShowTransferGM(SW_HIDE);
				ShowEditBuff(SW_HIDE);
				ShowCoordinate(SW_SHOW);

				if((listBasic.GetItemCount() > 0) && (nItem >= 0))
				{
					UserName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// ����ѡ�е�����ʺ�
					//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","WA_NickID"));// ����ѡ�е����ID
					UserNick = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// ����ѡ�е�����ǳ�
						
					tbcResult.SetCurSel(1);
					SetDlgItemText(IDC_EDITACCOUNT,UserName);
					SetDlgItemText(IDC_EDITNICK,UserNick);
				}
			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

// �л�ѡ����в���
void CXDGMManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	UserName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// ����ѡ�е�����ʺ�
	//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_AccountID"));// ����ѡ�е����ID
	UserNick = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// ����ѡ�е�����ǳ�

	switch(tbcResult.GetCurSel())
	{
	case 0:
		{
			ShowCoordinate(SW_HIDE);
			ShowTransferGM(SW_HIDE);
			ShowEditBuff(SW_HIDE);
			ShowUserInfo(SW_SHOW);
		}
		break;
	case 1:
		{
			ShowUserInfo(SW_HIDE);
			ShowTransferGM(SW_HIDE);
			ShowEditBuff(SW_HIDE);
			ShowCoordinate(SW_SHOW);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);
			}
		}
		break;
	case 4:
		{
			ShowUserInfo(SW_HIDE);
			ShowCoordinate(SW_HIDE);
			ShowTransferGM(SW_HIDE);			
			ShowEditBuff(SW_SHOW);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);

				SearchBuff();
			}
		}
		break;
	default:
		{	
			ShowUserInfo(SW_HIDE);
			ShowCoordinate(SW_HIDE);
			ShowEditBuff(SW_HIDE);
			ShowTransferGM(SW_SHOW);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);
			}	
		}
		break;
	}
	*pResult = 0;
}

//��ѯ����BUFF��Ϣ
void CXDGMManage::SearchBuff()
{
	try
	{		
		CIni mIni;

		if((listBasic.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			CString Profession = "";
			Profession = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Profession"));// ����ѡ�е�ְҵ����

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Profession,CEnumCore::TagFormat::TLV_STRING,strlen(Profession),(unsigned char *)mIni.wcharToChar(Profession));//ְҵ����

			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_BuffList_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_SearchSkill"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//�ƶ���ɫλ��
void CXDGMManage::OnBnClickedBtnedit()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listBasic.GetItemCount() > 0) && (nItem>=0))
		{			
			GetDlgItemText(IDC_EDITACCOUNT,UserName);
			GetDlgItemText(IDC_EDITNICK,UserNick);

			CString m_Name = ""; //GM��ɫ��
			CString xPos = "";//x����
			CString yPos = "";//y����
			CString zPos = "";//z����
			if(tbcResult.GetCurSel()==1)//������ָ��λ��
			{
				GetDlgItemText(IDC_EDITX,xPos);
				GetDlgItemText(IDC_EDITY,yPos);
				GetDlgItemText(IDC_EDITZ,zPos);	
			}
			else if(tbcResult.GetCurSel()==4)//���BUFF
			{
				GetDlgItemText(IDC_CMBLIST,BuffName);//��ȡBuff����
				if(BuffName == "")//���Buff����Ϊ��
				{
					return;
				}
				BuffList.Lookup(cmbList.GetCurSel()+1,BuffID);//��CMap��Ķ���BuffList�л�ȡBuffID
			}
			else//��GM���ഫ��ʱ
			{
				GetDlgItemText(IDC_EDITGMNAME,m_Name);
				if(m_Name=="") //GM��ɫ������Ϊ��
				{
					MessageBox(theApp.operXD.ReadValue("MXD","GMM_Warn_GMNameNull"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
			}

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��

			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

			switch(tbcResult.GetCurSel())
			{
			case 1:
				{
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_PositionX,CEnumCore::TagFormat::TLV_STRING,strlen(xPos),(unsigned char *)mIni.wcharToChar(xPos));//x����
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_PositionY,CEnumCore::TagFormat::TLV_STRING,strlen(yPos),(unsigned char *)mIni.wcharToChar(yPos));//y����
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_PositionZ,CEnumCore::TagFormat::TLV_STRING,strlen(zPos),(unsigned char *)mIni.wcharToChar(zPos));//z����
				}
				break;
			case 4:
				{
					_itoa(BuffID,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_BuffID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//BuffID
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_BuffName,CEnumCore::TagFormat::TLV_STRING,strlen(BuffName),(unsigned char *)mIni.wcharToChar(BuffName));//Buff����
				}
				break;
			default:
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_TargetCharacter,CEnumCore::TagFormat::TLV_STRING,strlen(m_Name),(unsigned char *)mIni.wcharToChar(m_Name));//GM��ɫ��
				break;
			}

			int midlength = socketdata.EnBody();
			switch(tbcResult.GetCurSel())
			{			
			case 1:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_MoveToPosition_Query);//���������ָ��λ��
				break;
			case 2:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_MoveToRole_Query);//���������GM���
				break;
			case 3:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_MoveToTargetRole_Query);//GM�ƶ���ָ����ɫ���
				break;
			case 4:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_AddBuff_Query);//���BUFF
				break;
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_Edit"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//������Ϣ
void CXDGMManage::OnBnClickedBtnrecover()
{
	SetDlgItemText(IDC_EDITX,"0");
	SetDlgItemText(IDC_EDITY,"0");
	SetDlgItemText(IDC_EDITZ,"0");
	SetDlgItemText(IDC_EDITGMNAME,"");
	if(tbcResult.GetCurSel() == 4)
	{
		try
		{
			CIni mIni;

			int index = theApp.operXD.ReadIntValue("MXD","index");
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

			if((listBasic.GetItemCount() > 0) && (nItem>=0))
			{
				GetDlgItemText(IDC_EDITACCOUNT,UserName);
				GetDlgItemText(IDC_EDITNICK,UserNick);

				CSocketData socketdata;
				socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��

				_itoa(BuffID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_BuffID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//BuffID
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_BuffName,CEnumCore::TagFormat::TLV_STRING,strlen(BuffName),(unsigned char *)mIni.wcharToChar(BuffName));//Buff����
			

				int userbyID = theApp.UserByID;
				_itoa(userbyID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

				int midlength = socketdata.EnBody();
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_RemoveBuff_Query_Resp);//�Ƴ�BUFF
				
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

				socketdata.Destroy();
			}
		}
		catch(...)
		{
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_Item"),theApp.operXD.ReadValue("MXD","Error"),0);
		}	
	}
}

// ���շ�����Ϣ
LRESULT CXDGMManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{	
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);	
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;

	dlgStatus = theApp.operXD.ReadIntValue("MXD","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

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
			theApp.operXD.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_Account_Query_Resp://��ѯ���������Ϣ�Ļ�Ӧ
		{
			if(pageBasic)//����Ѿ��ܹ���ҳ
			{
				theApp.operXD.BuildDataTable(&socketdata,&listBasic,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operXD.BuildDataTable(&socketdata,&listBasic,&pageCount);//����CListCtrl����

				if(pageCount<0)//ҳ��<=0��˵��û�����ݷ���
				{
					nItem = -1;//����ѡ��ĳһ��
					pageBasic = false;//���ܷ�ҳ					
					cmbBasic.ResetContent();//���ҳ����ѡ��
					while(listBasic.DeleteColumn(0)){}//���CListCtrl����
				}
				else
				{
					nItem = 0;
					cmbBasic.ResetContent();//���ҳ����ѡ���Ա����¹���
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbBasic.AddString(str);//�ڸ�ѡ���й���ҳ����Ϣ
					}
					cmbBasic.SetCurSel(0);//�ڸ�ѡ����ѡ�е�һҳ
					if(pageCount == 1)
					{
						pageBasic = false;//ֻ��һҳ���ݣ����ܷ�ҳ
					}
					else
					{
						pageBasic = true;//�ж�ҳ���ݣ����Է�ҳ
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_BuffList_Query_Resp://BUFF�б��ѯ
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int BuffID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::XDJG_BuffID).lpdata);//�õ�BuffID
				BuffList.SetAt(i,BuffID);//��BuffID������CMap��Ķ���BuffList��
			}
			theApp.operXD.BuildComboxs(&socketdata,&cmbList,CEnumCore::TagName::XDJG_BuffName);//����Buff��Ϣ
		}
		break;
	default:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operXD.ShowResult(result);//��ʾ���ؽ��

			SetDlgItemText(IDC_EDITX,"0");
			SetDlgItemText(IDC_EDITY,"0");
			SetDlgItemText(IDC_EDITZ,"0");
			SetDlgItemText(IDC_EDITGMNAME,"");
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

// �رնԻ���
void CXDGMManage::OnBnClickedCancel()
{
	ShowCoordinate(SW_HIDE);
	ShowTransferGM(SW_HIDE);
	ShowUserInfo(SW_SHOW);

	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// �رնԻ���
void CXDGMManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!BuffList.IsEmpty())
	{
		BuffList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//�����ݼ���Ӧ����
BOOL CXDGMManage::PreTranslateMessage(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listBasic.m_hWnd)
				{
					theApp.operXD.CopyListInfo(&listBasic);				
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listBasic.m_hWnd)
				{
					for(int i=0; i<listBasic.GetItemCount(); i++)
					{
						listBasic.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listBasic.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

//�û�����������Ϣҳ��
void CXDGMManage::ShowUserInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);
}

//������ָ������ҳ��
void CXDGMManage::ShowCoordinate(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLCOORDINATE,theApp.operXD.ReadValue("MXD","GMM_UI_Coordinate"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","Move"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITX,"0");
	SetDlgItemText(IDC_EDITY,"0");
	SetDlgItemText(IDC_EDITZ,"0");

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLCOORDINATE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLX)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITX)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLY)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITY)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLZ)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITZ)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

//��Һ�GM���ഫ�����Է�λ��
void CXDGMManage::ShowTransferGM(int m_cmdShow)
{
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","Move"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITGMNAME,"");

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLGMNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITGMNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

//���/�Ƴ�BUFFҳ��
void CXDGMManage::ShowEditBuff(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLCOORDINATE,theApp.operXD.ReadValue("MXD","GMM_UI_BuffList"));
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITGMNAME,"");
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","Add"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","Remove"));

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLCOORDINATE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBLIST)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

