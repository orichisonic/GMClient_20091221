// XDUserManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_XD.h"
#include "XDUserManage.h"
#include ".\xdusermanage.h"


// CXDUserManage �Ի���

IMPLEMENT_DYNAMIC(CXDUserManage, CDialog)
CXDUserManage::CXDUserManage(CWnd* pParent /*=NULL*/)
	: CDialog(CXDUserManage::IDD, pParent)
{
}

CXDUserManage::~CXDUserManage()
{
}

void CXDUserManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);

	DDX_Control(pDX, IDC_TABRESULT, tbcResult);

	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBBASIC, cmbBasic);
	DDX_Control(pDX, IDC_CMBRESULT, cmbResult);

	DDX_Control(pDX, IDC_LISTBASIC, listBasic);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);	
		
	DDX_Control(pDX, IDC_CMBSKILL, cmbList);
	DDX_Control(pDX, IDC_EDITNEW, CEditNew);
	DDX_Control(pDX, IDC_EDITOLD, CEditOld);
}


BEGIN_MESSAGE_MAP(CXDUserManage, CDialog)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_CMBBASIC, OnCbnSelchangeCmbbasic)
	ON_CBN_SELCHANGE(IDC_CMBRESULT, OnCbnSelchangeCmbresult)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTBASIC, OnNMClickListbasic)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTBASIC, OnNMDblclkListbasic)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)

	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	
	ON_BN_CLICKED(IDC_BTNEDIT, OnBnClickedBtnedit)
	ON_BN_CLICKED(IDC_BTNRECOVER, OnBnClickedBtnrecover)
	ON_BN_CLICKED(IDC_BTNEDITLVL, OnBnClickedBtneditlvl)
	ON_BN_CLICKED(IDC_BTNDELSKILL, OnBnClickedBtndelskill)
	ON_CBN_SELCHANGE(IDC_CMBSKILL, OnCbnSelchangeCmbskill)	
	
END_MESSAGE_MAP()


// CXDUserManage ��Ϣ�������

// ��ʼ���Ի���
BOOL CXDUserManage::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// ��ʼ����ʾ�ַ�

	nItem = -1;
	pageResult = false;
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

		if(listResult.m_hWnd != NULL)
		{
			listResult.MoveWindow(newRect);//���ú�listResult��λ�ã�listResult��listBasic��λ����ȫ�ص�
		}
	}

	//maple add/////��־��ѯ������������

	dlgStatus = theApp.operXD.ReadIntValue("MXD","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	if(theApp.operXD.GetServerList())//�������е���Ϸ�������б�
	{
		//MessageBox("t");
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CXDUserManage::InitUI()
{
	SetWindowText(theApp.operXD.ReadValue("MXD","UM_UI_UserManage"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operXD.ReadValue("MXD","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operXD.ReadValue("MXD","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operXD.ReadValue("MXD","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operXD.ReadValue("MXD","Search"));
	SetDlgItemText(IDCANCEL,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operXD.ReadValue("MXD","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operXD.ReadValue("MXD","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operXD.ReadValue("MXD","UM_UI_SkillInfo"));	
	tbcResult.InsertItem(2,theApp.operXD.ReadValue("MXD","UM_UI_PwdEdit"));
	tbcResult.InsertItem(3,theApp.operXD.ReadValue("MXD","UM_UI_UserEdit"));
	tbcResult.InsertItem(4,theApp.operXD.ReadValue("MXD","UM_UI_InfoEdit"));
	tbcResult.InsertItem(5,theApp.operXD.ReadValue("MXD","UM_UI_SkillEdit"));
	//tbcResult.InsertItem(6,theApp.operXD.ReadValue("MXD","UM_UI_TitleEdit"));

	SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNICK,theApp.operXD.ReadValue("MXD","UIC_UI_lblNick"));
	SetDlgItemText(IDC_LBLSKILL,theApp.operXD.ReadValue("MXD","UM_UI_SkillName"));
	SetDlgItemText(IDC_LBLLEVEL,theApp.operXD.ReadValue("MXD","UM_UI_SkillLevel"));
	SetDlgItemText(IDC_BTNEDITLVL,theApp.operXD.ReadValue("MXD","UM_UI_EditLevel"));
	SetDlgItemText(IDC_BTNDELSKILL,theApp.operXD.ReadValue("MXD","UM_UI_DelSkill"));
}

// �Զ��ı��С
void CXDUserManage::OnSize(UINT nType, int cx, int cy)
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

		if(listResult.m_hWnd != NULL)
		{
			listResult.MoveWindow(newRect);//���ú�listResult��λ��
		}
	}
}

//���ñ�����ɫ
HBRUSH CXDUserManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ���������Ϣ
void CXDUserManage::OnBnClickedSearch()
{
	try
	{
		CIni mIni;

		tbcResult.SetCurSel(0);

		nItem = -1;//��������б�û��ѡ����
		pageBasic = false;//��������б��ܷ�ҳ	
		cmbBasic.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listBasic.DeleteColumn(0)){}//�����������б��е���������

		ShowSkillInfo(SW_HIDE);
		ShowPwdInfo(SW_HIDE);
		ShowNewSkill(SW_HIDE);
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
void CXDUserManage::UserInfo()
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
void CXDUserManage::OnCbnSelchangeCmbbasic()
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
void CXDUserManage::OnNMClickListbasic(NMHDR *pNMHDR, LRESULT *pResult)
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
void CXDUserManage::OnNMDblclkListbasic(NMHDR *pNMHDR, LRESULT *pResult)
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
				CIni mIni;
				pageResult = false;
				cmbResult.ResetContent();
				while(listResult.DeleteColumn(0)){}// �������б��е���������

				ShowUserInfo(SW_HIDE);
				ShowPwdInfo(SW_HIDE);
				ShowNewSkill(SW_HIDE);
				ShowSkillInfo(SW_SHOW);

				if((listBasic.GetItemCount() > 0) && (nItem >= 0))
				{
					UserName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// ����ѡ�е�����ʺ�
					//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","WA_NickID"));// ����ѡ�е����ID
					UserNick = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// ����ѡ�е�����ǳ�
						
					tbcResult.SetCurSel(1);
					SkillInfo();
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
void CXDUserManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	UserName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// ����ѡ�е�����ʺ�
	//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_AccountID"));// ����ѡ�е����ID
	UserNick = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// ����ѡ�е�����ǳ�

	switch(tbcResult.GetCurSel())
	{
	case 0:
		{
			ShowSkillInfo(SW_HIDE);
			ShowPwdInfo(SW_HIDE);
			ShowNewSkill(SW_HIDE);
			ShowUserInfo(SW_SHOW);
		}
		break;
	case 1:
		{
			ShowPwdInfo(SW_HIDE);
			ShowNewSkill(SW_HIDE);
			ShowUserInfo(SW_HIDE);
			ShowSkillInfo(SW_SHOW);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SkillInfo();
			}
		}
		break;
	case 2:
		{				
			ShowUserInfo(SW_HIDE);
			ShowSkillInfo(SW_HIDE);
			ShowNewSkill(SW_HIDE);
			ShowPwdInfo(SW_SHOW);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);
			}	
		}
		break;
	case 3:
		{
			ShowUserInfo(SW_HIDE);
			ShowSkillInfo(SW_HIDE);
			ShowNewSkill(SW_HIDE);
			ShowPwdInfo(SW_HIDE);
			ShowManageInfo(SW_SHOW);

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
			ShowSkillInfo(SW_HIDE);
			ShowNewSkill(SW_HIDE);
			ShowPwdInfo(SW_HIDE);
			ShowAccountInfo(SW_SHOW);

			CEditNew.ModifyStyle(0,ES_NUMBER);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);
			}
		}
		break;
	case 5:
		{
			ShowPwdInfo(SW_HIDE);		
			ShowUserInfo(SW_HIDE);
			ShowSkillInfo(SW_HIDE);
			ShowNewSkill(SW_SHOW);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);

				SearchSkill();
			}
		}
		break;
	case 6:
		{
			ShowPwdInfo(SW_HIDE);		
			ShowUserInfo(SW_HIDE);
			ShowSkillInfo(SW_HIDE);
			ShowEditTitle(SW_SHOW);

			if((listBasic.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);

				SearchTitle();
			}
		}
		break;
	default:
		break;
	}
	*pResult = 0;
}

// ��ѯ���������Ϣ
void CXDUserManage::SkillInfo()
{	
	try
	{		
		CIni mIni;
		pageResult = false;
		cmbResult.ResetContent();
		while(listResult.DeleteColumn(0)){}// �������б��е���������

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listBasic.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_RoleSkills_Query );//��ѯ��ɫ������Ϣ

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_Skill"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

// ��ҳ���в�ѯ
void CXDUserManage::OnCbnSelchangeCmbresult()
{	
	try
	{
		if(pageResult)
		{
			CIni mIni;

			int index = cmbResult.GetCurSel() + 1;
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

			while(listResult.DeleteColumn(0)){}

			if((listBasic.GetItemCount() > 0) && (nItem>=0))
			{
				CSocketData socketdata;
				socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��

				_itoa(index,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

				_itoa(iPageSize,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

				int midlength = socketdata.EnBody();				
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_RoleSkills_Query);// ��ѯ��ɫ������Ϣ

				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				socketdata.Destroy();
			}
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_Page"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//�������������Ϣ�б����ѡ��
void CXDUserManage::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 1)
	{
		if(listResult.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listResult.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nListItem = listResult.SubItemHitTest(&lvinfo);//��������Ҽ�����Ϣ�б���ѡ�е��к�

			if(nListItem >= 0)
			{
				SkillID = atoi(theApp.operXD.GetValueByColName(&listResult, nListItem, theApp.operXD.ReadValue("MXD","XDJG_SkillID")));// ����ѡ�еļ���ID
				SkillName = theApp.operXD.GetValueByColName(&listResult, nListItem, theApp.operXD.ReadValue("MXD","XDJG_SkillName"));// ����ѡ�еļ�������
				SetDlgItemText(IDC_EDITSKILL,SkillName);
			}
		}
		else
		{
			nListItem = -1;
		}
	}
	*pResult = 0;
}

//�޸�ѡ�еĽ�ɫ������Ϣ
void CXDUserManage::OnBnClickedBtneditlvl()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listResult.GetItemCount() > 0) && (nListItem>=0))
		{		
			GetDlgItemText(IDC_EDITSKILL,SkillName);//��ȡ��������
			if(SkillName == "")//Ҫ�޸ĵļ������Ʋ���Ϊ��
			{
				MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_EditSkillNone"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}

			CString newValue; //�޸ĺ�ļ��ܵȼ�
			GetDlgItemText(IDC_EDITLEVEL,newValue);//��ȡ���ܵȼ�
			if(newValue == "")//Ҫ�޸ĵļ��ܵȼ�����Ϊ��
			{
				MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_NewSkillLevel"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
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

			_itoa(SkillID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_SkillID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_SkillName,CEnumCore::TagFormat::TLV_STRING,strlen(SkillName),(unsigned char *)mIni.wcharToChar(SkillName));//��������
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Level,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//���ܵȼ�

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ModifyLevel_operate);//�޸ļ��ܵȼ�

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_EditSkill"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//ɾ��ѡ�еĽ�ɫ������Ϣ
void CXDUserManage::OnBnClickedBtndelskill()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listResult.GetItemCount() > 0) && (nListItem>=0))
		{		
			GetDlgItemText(IDC_EDITSKILL,SkillName);//��ȡ��������
			if(SkillName == "")//Ҫɾ���ļ������Ʋ���Ϊ��
			{
				MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_DelSkillNone"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
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

			_itoa(SkillID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_SkillID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_SkillName,CEnumCore::TagFormat::TLV_STRING,strlen(SkillName),(unsigned char *)mIni.wcharToChar(SkillName));//��������
			
			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_RoleSkillDel);//ɾ����ɫ����

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_EditSkill"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//��ѯ���п�����ӵļ�����Ϣ
void CXDUserManage::SearchSkill()
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
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_SkillList_Query);

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

//��ѯ���гƺ���Ϣ
void CXDUserManage::SearchTitle()
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
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_TitleList_Query);

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

//�޸Ļ������Ϣ
void CXDUserManage::OnBnClickedBtnedit()
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

			CString newValue; //�޸ĺ��ֵ
			if(tbcResult.GetCurSel()==2)//�޸��û�����ʱ
			{
				GetDlgItemText(IDC_EDITOLD,newValue);	
				if(newValue=="") //�����벻��Ϊ��
				{
					MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_InputNPwd"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
				CString newPassAG; //�ظ�������
				GetDlgItemText(IDC_EDITNEW,newPassAG);	
				if(newPassAG=="") //�ظ������벻��Ϊ��
				{
					MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_InputNPwdAG"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
				if(newPassAG!=newValue) //����ǰ��Ҫ��ͬ
				{
					MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_PwdNotSame"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}		
			}
			else if(tbcResult.GetCurSel()==4)//��ɫ��Ϣ����
			{
				GetDlgItemText(IDC_EDITNEW,newValue);	
				if(newValue=="") //�޸ĺ��ֵ����Ϊ��
				{
					MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_NewValue"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
			}
			else if(tbcResult.GetCurSel()==5)//����¼���ʱ
			{
				GetDlgItemText(IDC_CMBSKILL,SkillName);//��ȡ��������
				if(SkillName == "")//��Ӽ��ܲ���Ϊ��
				{
					MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_SkillNone"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
				SkillList.Lookup(cmbList.GetCurSel()+1,SkillID);//��CMap��Ķ���SkillList�л�ȡSkillID

				GetDlgItemText(IDC_EDITNEW,newValue);	
				//if(newValue=="") //���ܵȼ�����Ϊ��
				//{
				//	MessageBox(theApp.operXD.ReadValue("MXD","UM_Warn_SkillLevel"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				//	return;
				//}
			}
			else if(tbcResult.GetCurSel()==6)//����³ƺ�ʱ
			{
				GetDlgItemText(IDC_CMBSKILL,TitleName);//��ȡ�ƺ�����
				if(TitleName == "")//��ӳƺŲ���Ϊ��
				{
					return;
				}
				TitleList.Lookup(cmbList.GetCurSel()+1,TitleID);//��CMap��Ķ���TitleList�л�ȡTitleID
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
			case 5:
				{
					_itoa(SkillID,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_SkillID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_SkillName,CEnumCore::TagFormat::TLV_STRING,strlen(SkillName),(unsigned char *)mIni.wcharToChar(SkillName));//��������
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_Level,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//���ܵȼ�
				}
				break;
			case 2:
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_Pwd,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//������
				break;
			case 4:
				{
					if(cmbList.GetCurSel()==0)
					{
						_itoa(1,strInt,10);
						socketdata.AddTFLV(CEnumCore::TagName::XDJG_UpdateType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ͣ�1���ȼ�
						socketdata.AddTFLV(CEnumCore::TagName::XDJG_Level,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//�µȼ�
					}
					else if(cmbList.GetCurSel()==1)
					{
						_itoa(2,strInt,10);
						socketdata.AddTFLV(CEnumCore::TagName::XDJG_UpdateType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ͣ�2������
						socketdata.AddTFLV(CEnumCore::TagName::XDJG_Exp,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//�½�Ǯ
					}
					//else if(cmbList.GetCurSel()==2)
						//socketdata.AddTFLV(CEnumCore::TagName::WA_NewRole,CEnumCore::TagFormat::TLV_STRING,strlen(newValue),(unsigned char *)mIni.wcharToChar(newValue));//�½�ɫ��
				}
				break;
			case 6:
				{
					_itoa(TitleID,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_TitleID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�ƺ�ID
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_TitleName,CEnumCore::TagFormat::TLV_STRING,strlen(TitleName),(unsigned char *)mIni.wcharToChar(TitleName));//�ƺ�����
				}
				break;
			}

			int midlength = socketdata.EnBody();
			switch(tbcResult.GetCurSel())
			{			
			case 2:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ModifyPwd_operate);//�޸�����
				break;
			case 3:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_DeleteRole_operate);//ɾ����ɫ
				break;
			case 4:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ModifyLevel_operate);//�޸ĵȼ�
				break;
			case 5:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_RoleSkillAdd);//��ӽ�ɫ����
				break;
			case 6:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_AddTitle_Query);//��ӳƺ�
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

//ɾ����ָ���Ϣ
void CXDUserManage::OnBnClickedBtnrecover()
{
	try
	{		
		cmbList.SetCurSel(0);
		SetDlgItemText(IDC_EDITOLD,"");
		SetDlgItemText(IDC_EDITNEW,"");	

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

			switch(tbcResult.GetCurSel())
			{
			case 6:
				{
					_itoa(TitleID,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_TitleID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�ƺ�ID
					socketdata.AddTFLV(CEnumCore::TagName::XDJG_TitleName,CEnumCore::TagFormat::TLV_STRING,strlen(TitleName),(unsigned char *)mIni.wcharToChar(TitleName));//�ƺ�����
				}
				break;
			}

			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

			int midlength = socketdata.EnBody();
			switch(tbcResult.GetCurSel())
			{
			case 2:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ResumePwd_operate);//�ָ�����
				break;
			case 3:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ResumeRole_operate);//�ָ���ɫ
				break;
			case 6:
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_RemoveTitle_Query);//�Ƴ��ƺ�
				break;
			}

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

// ���շ�����Ϣ
LRESULT CXDUserManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::XDJG_RoleSkills_Query_Resp://��ѯ������ϼ�����Ϣ
		{
			if(pageResult)//����Ѿ��ܹ���ҳ
			{
				theApp.operXD.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operXD.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

				if(pageCount<0)//ҳ��<=0��˵��û�����ݷ���
				{
					pageResult = false;//���ܷ�ҳ		
					cmbResult.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					cmbResult.ResetContent();
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbResult.AddString(str);
					}
					cmbResult.SetCurSel(0);
					if(pageCount == 1)
					{
						pageResult = false;
					}
					else
					{
						pageResult = true;
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_SkillList_Query_Resp://��ѯ���еļ�����Ϣ
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int SkillID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::XDJG_SkillID).lpdata);//�õ�����ID
				SkillList.SetAt(i,SkillID);//������ID������CMap��Ķ���SkillList��
			}
			theApp.operXD.BuildComboxs(&socketdata,&cmbList,CEnumCore::TagName::XDJG_SkillName);//���켼����Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_TitleList_Query_Resp://�ƺ��б��ѯ
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int TitleID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::XDJG_TitleID).lpdata);//�õ��ƺ�ID
				TitleList.SetAt(i,TitleID);//���ƺ�ID������CMap��Ķ���TitleList��
			}
			theApp.operXD.BuildComboxs(&socketdata,&cmbList,CEnumCore::TagName::XDJG_TitleName);//����ƺ���Ϣ
		}
		break;
	default:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operXD.ShowResult(result);//��ʾ���ؽ��

			cmbList.SetCurSel(0);
			SetDlgItemText(IDC_EDITOLD,"");
			SetDlgItemText(IDC_EDITNEW,"");
			SetDlgItemText(IDC_EDITLEVEL,"");
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

// �رնԻ���
void CXDUserManage::OnBnClickedCancel()
{
	ShowSkillInfo(SW_HIDE);
	ShowPwdInfo(SW_HIDE);
	GetDlgItem(IDC_CMBSKILL)->ShowWindow(SW_HIDE);		
	ShowUserInfo(SW_SHOW);

	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// �رնԻ���
void CXDUserManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!SkillList.IsEmpty())
	{
		SkillList.RemoveAll();
	}
	if(!TitleList.IsEmpty())
	{
		TitleList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//�����ݼ���Ӧ����
BOOL CXDUserManage::PreTranslateMessage(MSG* pMsg)
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
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operXD.CopyListInfo(&listResult);
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

void CXDUserManage::OnCbnSelchangeCmbskill()
{
	SetDlgItemText(IDC_EDITNEW,"");
	if(tbcResult.GetCurSel()==4)
	{
		//if(cmbList.GetCurSel()==0)
		//    CEditNew.ModifyStyle(ES_NUMBER,0);
		//else
		CEditNew.ModifyStyle(0,ES_NUMBER);
	}
}

//�û�����������Ϣҳ��
void CXDUserManage::ShowUserInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);
}

//�û�������Ϣҳ��
void CXDUserManage::ShowSkillInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBRESULT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSKILL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSKILL)->ShowWindow(m_cmdShow);
	//GetDlgItem(IDC_LBLLEVEL)->ShowWindow(m_cmdShow);
	//GetDlgItem(IDC_EDITLEVEL)->ShowWindow(m_cmdShow);
	//GetDlgItem(IDC_BTNEDITLVL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNDELSKILL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_EDITSKILL,"");
	SetDlgItemText(IDC_EDITLEVEL,"");
}

//�޸�/�ָ��û�����ҳ��
void CXDUserManage::ShowPwdInfo(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operXD.ReadValue("MXD","UM_UI_NewPwd"));
	SetDlgItemText(IDC_LBLNEW,theApp.operXD.ReadValue("MXD","UM_UI_ReNewPwd"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","UM_UI_EditPwd"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","UM_UI_RecoverPwd"));

	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITOLD,"");
	SetDlgItemText(IDC_EDITNEW,"");

	CEditOld.SetPasswordChar('*');
	CEditOld.ModifyStyle(0,ES_PASSWORD,0);
	CEditNew.SetPasswordChar('*');
	CEditNew.ModifyStyle(0,ES_PASSWORD,0);

	CEditNew.ModifyStyle(ES_NUMBER,0);

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLOLD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITOLD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

//ɾ��/�ָ��û�ҳ��
void CXDUserManage::ShowManageInfo(int m_cmdShow)
{
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","UM_UI_DelRole"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","UM_UI_RecoverRole"));

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

//�޸��û���ɫ��/�ȼ�/��Ǯҳ��
void CXDUserManage::ShowAccountInfo(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operXD.ReadValue("MXD","UM_UI_Type"));
	SetDlgItemText(IDC_LBLNEW,theApp.operXD.ReadValue("MXD","UM_UI_NewValue"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","UM_UI_Edit"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","UM_UI_Reset"));

	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITNEW,"");
	cmbList.ResetContent();
	//cmbList.AddString(theApp.operXD.ReadValue("MXD","UM_UI_RoleName"));
	cmbList.AddString(theApp.operXD.ReadValue("MXD","UM_UI_Level"));	
	//cmbList.AddString(theApp.operXD.ReadValue("MXD","UM_UI_Money"));
	cmbList.AddString(theApp.operXD.ReadValue("MXD","UM_UI_Exp"));
	cmbList.SetCurSel(0);

	CEditNew.SetPasswordChar(NULL);
	CEditNew.ModifyStyle(ES_PASSWORD,0);
	CEditNew.ModifyStyle(ES_NUMBER,0);

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLOLD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBSKILL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

//����¼���ҳ��
void CXDUserManage::ShowNewSkill(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operXD.ReadValue("MXD","UM_UI_NewSkill"));
	//SetDlgItemText(IDC_LBLNEW,theApp.operXD.ReadValue("MXD","UM_UI_SkillLevel"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","UM_UI_Add"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","UM_UI_Reset"));

	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	cmbList.ResetContent();

	//CEditNew.SetPasswordChar(NULL);
	//CEditNew.ModifyStyle(ES_PASSWORD,0);
	//SetDlgItemText(IDC_EDITNEW,"0");
	//CEditNew.ModifyStyle(0,ES_NUMBER);

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLOLD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBSKILL)->ShowWindow(m_cmdShow);
	//GetDlgItem(IDC_LBLNEW)->ShowWindow(m_cmdShow);
	//GetDlgItem(IDC_EDITNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

//���/�Ƴ��ƺ�ҳ��
void CXDUserManage::ShowEditTitle(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operXD.ReadValue("MXD","UM_UI_TitleList"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","Add"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","Remove"));

	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	cmbList.ResetContent();

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLOLD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBSKILL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}
