// CG2UpdateSkill.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2UpdateSkill.h"
#include ".\cg2updateskill.h"


// CCG2UpdateSkill �Ի���


IMPLEMENT_DYNCREATE(CCG2UpdateSkill, CDialog)

CCG2UpdateSkill::CCG2UpdateSkill(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2UpdateSkill::IDD, pParent)
{
}

CCG2UpdateSkill::~CCG2UpdateSkill()
{
}

void CCG2UpdateSkill::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBNEWLEVEL, cmbNewLevel);
	DDX_Control(pDX, IDC_LISTSKILLINFO, listSkill);
	DDX_Control(pDX, IDC_CMBSKILLPAGE, cmbSkillPage);
	DDX_Control(pDX, IDC_CMBNEWLEVEL, cmbNewLevel);
	DDX_Control(pDX, IDC_CMBSKILLTYPE, cmbSkillType);
	DDX_Control(pDX, IDC_CMBSKILLNAME, cmbSkillName);
}

BEGIN_MESSAGE_MAP(CCG2UpdateSkill, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_NOTIFY(NM_CLICK, IDC_LISTSKILLINFO, OnNMClickListskillinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTSKILLINFO, OnNMDblclkListskillinfo)
	ON_BN_CLICKED(IDC_BTUPDATE, OnBnClickedBtupdate)
	ON_BN_CLICKED(IDC_BTRESET, OnBnClickedBtreset)
	ON_BN_CLICKED(IDC_BTADDSKILL, OnBnClickedBtaddskill)
	ON_BN_CLICKED(IDC_BTRESETSKILL, OnBnClickedBtresetskill)


ON_CBN_SELCHANGE(IDC_CMBSKILLTYPE, OnCbnSelchangeCmbskilltype)

END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CCG2UpdateSkill)

END_DHTML_EVENT_MAP()





// ��ʼ����ʾ�ַ�
void CCG2UpdateSkill::InitUI()
{
	//OperationCG2 theApp.operCG2;

	SetWindowText(theApp.operCG2.ReadValue("MCG2","CG2_UI_UpdateSkill"));

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


	SetDlgItemText(IDC_STATICSKILL,theApp.operCG2.ReadValue("MCG2","US_UI_Skill"));
	SetDlgItemText(IDC_STATICCURLEVEL,theApp.operCG2.ReadValue("MCG2","US_UI_CurrentLevel"));
	SetDlgItemText(IDC_STATICNEWLEVEL,theApp.operCG2.ReadValue("MCG2","US_UI_NewLevel"));
	SetDlgItemText(IDC_STATICSKILLTYPE,theApp.operCG2.ReadValue("MCG2","US_UI_SkillType"));
	SetDlgItemText(IDC_STATICSKILLNAME,theApp.operCG2.ReadValue("MCG2","US_UI_Skill"));
	SetDlgItemText(IDC_STATICSKILLLEVEL,theApp.operCG2.ReadValue("MCG2","US_UI_SkillLevel"));
	SetDlgItemText(IDC_BTUPDATE,theApp.operCG2.ReadValue("MCG2","MakeSure"));
	SetDlgItemText(IDC_BTRESET,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_BTADDSKILL,theApp.operCG2.ReadValue("MCG2","MakeSure"));
	SetDlgItemText(IDC_BTRESETSKILL,theApp.operCG2.ReadValue("MCG2","Reset"));



	tbcResult.InsertItem(0,theApp.operCG2.ReadValue("MCG2","UIC_UI_tpgUserInfo"));//��һ�����Ϣ
	tbcResult.InsertItem(1,theApp.operCG2.ReadValue("MCG2","CG2_UI_tpgSkillInfo"));//������Ϣ
	tbcResult.InsertItem(2,theApp.operCG2.ReadValue("MCG2","CG2_UI_tpgSkillLevel"));//�޸Ľ�ɫ���ܵȼ�
	tbcResult.InsertItem(3,theApp.operCG2.ReadValue("MCG2","CG2_UI_tpgAddSkill"));//��ӽ�ɫ����


	GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

}



BOOL CCG2UpdateSkill::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: �ڴ˴������Ϣ����������
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

		if(listSkill.m_hWnd != NULL)
		{
			listSkill.MoveWindow(newRect);//���ú�listResult��λ��
		}
		
	}

	//OperationCG2 theApp.operCG2;
	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	theApp.operCG2.GetServerList();//�������е���Ϸ�������б�
	::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

	return TRUE;
}

void CCG2UpdateSkill::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CCG2UpdateSkill::OnBnClickedUicancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");

}

void CCG2UpdateSkill::OnSize(UINT nType, int cx, int cy)
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

		if(listSkill.m_hWnd != NULL)
		{
			listSkill.MoveWindow(newRect);//���ú�listResult��λ��
		}

		
	}
}

HBRUSH CCG2UpdateSkill::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

void CCG2UpdateSkill::OnBnClickedUisearch()
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

	    UserInfo();// ��ѯ���������Ϣ
	}
	catch(...)
	{
	}
}

void CCG2UpdateSkill::UserInfo()
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

//������Ϣ��ѯ
void CCG2UpdateSkill::SkillInfo()
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
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Skill_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
	    }
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Skill"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
}

//�л�tabCtrl
void CCG2UpdateSkill::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OperationCG2 theApp.operCG2;
	if(tbcResult.GetCurSel()==0)//ѡ�е������������Ϣѡ�
	{
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

		UpdateData(true);
	}
	else if(tbcResult.GetCurSel()==1)
	{
		GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

		//GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);
		UpdateData(true);

		SkillInfo();
	}
	else if(tbcResult.GetCurSel()==2)//ѡ�е����޸Ľ�ɫ���ܵȼ�
	{
		CIni mIni;
		pageInfo = false;
		cmbPage.ResetContent();

		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTRESET)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

		UpdateData(true);
		//OperationCG2 theApp.operCG2;

		UserSkill = theApp.operCG2.GetValueByColName(&listSkill,nItem,theApp.operCG2.ReadValue("MCG2","CG2_SkillName"));//����ѡ�еļ�������
		UserSkillLevel = atoi(theApp.operCG2.GetValueByColName(&listSkill,nItem,theApp.operCG2.ReadValue("MCG2","CG2_SkillLevel")));//����ѡ�еļ��ܵȼ�

		char strInt[10];
		_itoa(UserSkillLevel,strInt,10);
		SetDlgItemText(IDC_ETSKILL,UserSkill);
		SetDlgItemText(IDC_ETCURLEVEL,strInt);
	}
	else if(tbcResult.GetCurSel()==3)//ѡ�е�����Ӽ�����Ϣ
	{
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_SHOW);

		SetDlgItemText(IDC_ETSKILLLEVEL,"1");

		GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_SHOW);

		UpdateData(true);

		SkillType();
	}
	*pResult = 0;
}

//��ѯ�������
void CCG2UpdateSkill::SkillType()
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
			socketdata.InitCreate(1,2);//�������������������IP������ʺš�ҳ����ÿҳ�ļ�¼����
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
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_GetSkill_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_AddSkill"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
}
// �����û��б��浱ǰ�к�
void CCG2UpdateSkill::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
void CCG2UpdateSkill::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
				//while(listUser.DeleteColumn(0)){}// �������б��е���������

				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

				UpdateData(true);

				//OperationCG2 theApp.operCG2;
				UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
				UserID = theApp.operCG2.GetValueByColName(&listUser, nItem,theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ����ѡ�е����ID
				UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// ����ѡ�е�����ǳ�
				iCharNo =atoi(theApp.operCG2.GetValueByColName(&listUser,nItem,theApp.operCG2.ReadValue("MCG2","CG2_CharacterNum")));//����ѡ�е���ҽ�ɫ��

				SkillInfo();

			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

//����������Ϣ�б��
void CCG2UpdateSkill::OnNMClickListskillinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(tbcResult.GetCurSel() == 1)
	{
		if(listSkill.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listSkill.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listSkill.SubItemHitTest(&lvinfo);//�����ڼ�����Ϣ�б���ѡ�е��к�
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}
//˫��������Ϣ�б��
void CCG2UpdateSkill::OnNMDblclkListskillinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OperationCG2 theApp.operCG2;

	if(tbcResult.GetCurSel() == 1)
	{
		if(listSkill.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listSkill.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listSkill.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

			if(nItem >= 0)
			{
				tbcResult.SetCurSel(2);

				CIni mIni;
				pageInfo = false;
				cmbPage.ResetContent();
				//while(listUser.DeleteColumn(0)){}// �������б��е���������

				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTRESET)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

				UpdateData(true);

				//OperationCG2 theApp.operCG2;


				UserSkill = theApp.operCG2.GetValueByColName(&listSkill,nItem,theApp.operCG2.ReadValue("MCG2","CG2_SkillName"));//����ѡ�еļ�������
				SkillID =theApp.operCG2.GetValueByColName(&listSkill,nItem,theApp.operCG2.ReadValue("MCG2","CG2_SkillID"));//����ѡ�еļ���id
				UserSkillLevel = atoi(theApp.operCG2.GetValueByColName(&listSkill,nItem,theApp.operCG2.ReadValue("MCG2","CG2_SkillLevel")));//����ѡ�еļ��ܵȼ�

				char strInt[10];
				_itoa(UserSkillLevel,strInt,10);
				SetDlgItemText(IDC_ETSKILL,UserSkill);
				SetDlgItemText(IDC_ETCURLEVEL,strInt);
				cmbNewLevel.ResetContent();
				SetLevel();

			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}
///�޸���ҽ�ɫ���ܵȼ�
void CCG2UpdateSkill::OnBnClickedBtupdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OperationCG2 theApp.operCG2;
	try
	{
		CIni mIni;
		CSocketData socketdata;
		socketdata.InitCreate(1,7);//�������������������IP������ʺš���ɫIDKEY����ɫ�š���ע�����ܵȼ�������ID

		char strInt[10];
		_itoa(iCharNo,strInt,10);
		CString remark="Update Skill Level";
		CString SkillLevel="";

		cmbNewLevel.GetWindowText(SkillLevel);

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Remark,CEnumCore::TagFormat::TLV_STRING,strlen(remark),(unsigned char *)mIni.wcharToChar(remark));//��ע
		socketdata.AddTFLV(CEnumCore::TagName::CG2_SkillLevel,CEnumCore::TagFormat::TLV_STRING,strlen(SkillLevel),(unsigned char *)mIni.wcharToChar(SkillLevel));//���ܵȼ�

		socketdata.AddTFLV(CEnumCore::TagName::CG2_SkillID,CEnumCore::TagFormat::TLV_STRING,strlen(SkillID),(unsigned char *)mIni.wcharToChar(SkillID));//����id
		//_itoa(index,strInt,10);
		//socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		//_itoa(iPageSize,strInt,10);
		//socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Update_Account_Skill_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UpdateSkillLevel"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
}
//�����޸Ľ�ɫ���ܵȼ�
void CCG2UpdateSkill::OnBnClickedBtreset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	tbcResult.SetCurSel(1);



	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

	cmbNewLevel.ResetContent();
	SetLevel();

	UpdateData(true);

	SkillInfo();
}

//�л�ְҵ�����Ͽ�,�������Ʋ�ѯ
void CCG2UpdateSkill::OnCbnSelchangeCmbskilltype()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int iPos=((CComboBox*)GetDlgItem(IDC_CMBSKILLTYPE))->GetCurSel();//��ǰѡ�е���
	CString SkillType="";
	//cmbSkillType.GetWindowText(SkillType);
	//GetDlgItemText(IDC_CMBSKILLTYPE,SkillType);
	((CComboBox*)GetDlgItem(IDC_CMBSKILLTYPE))->GetLBText(iPos,SkillType); //����nΪ��0��ʼ������ֵ
	CString m_ServerName="";
	GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//��ȡ��Ϸ������������

	ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

	//OperationCG2 theApp.operCG2;	
	try
	{		
		CIni mIni;
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		//if((listUser.GetItemCount() > 0) && (nItem>=0))
		//{
			CSocketData socketdata;
			socketdata.InitCreate(1,5);//�������������������IP������ʺš�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_SkillType,CEnumCore::TagFormat::TLV_STRING,strlen(SkillType),(unsigned char *)mIni.wcharToChar(SkillType));//�������

			//socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SkillList_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
	//	}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_AddSkill"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}

}




//��Ӽ�����Ϣ
void CCG2UpdateSkill::OnBnClickedBtaddskill()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OperationCG2 theApp.operCG2;
	try
	{
		CIni mIni;
		CSocketData socketdata;
		socketdata.InitCreate(1,6);//�������������������IP������ʺš���ɫIDKEY����ɫ�š���ְҵ����ע

		char strInt[10];
		_itoa(iCharNo,strInt,10);
		CString remark="Add Skill";
		CString SkillName="";

		//cmbNewLevel.GetWindowText(SkillLevel);
		GetDlgItemText(IDC_CMBSKILLNAME,SkillName);

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Remark,CEnumCore::TagFormat::TLV_STRING,strlen(remark),(unsigned char *)mIni.wcharToChar(remark));//��ɫΨһIDKEY
		socketdata.AddTFLV(CEnumCore::TagName::CG2_SkillName,CEnumCore::TagFormat::TLV_STRING,strlen(SkillName),(unsigned char *)mIni.wcharToChar(SkillName));//��������

		//_itoa(index,strInt,10);
		//socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		//_itoa(iPageSize,strInt,10);
		//socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Insert_Account_Skill_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_AddSkill"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
}
//������Ӽ�����Ϣ
void CCG2UpdateSkill::OnBnClickedBtresetskill()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	tbcResult.SetCurSel(1);



	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

	cmbNewLevel.ResetContent();
	SetLevel();

	UpdateData(true);

	SkillInfo();
}

void CCG2UpdateSkill::SetLevel()
{
	cmbNewLevel.ResetContent();
	cmbNewLevel.AddString("0");
	cmbNewLevel.AddString("1");
	cmbNewLevel.AddString("2");
	cmbNewLevel.AddString("3");
	cmbNewLevel.AddString("4");
	cmbNewLevel.AddString("5");
	cmbNewLevel.AddString("6");
	cmbNewLevel.AddString("7");
	cmbNewLevel.AddString("8");
	cmbNewLevel.AddString("9");
	cmbNewLevel.SetCurSel(0);
	
}

LRESULT CCG2UpdateSkill::OnMessageReceive(WPARAM wParam,LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::CG2_Account_Skill_Query_Resp://��ѯ��Ҽ�����Ϣ
		{
			if(pageUInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listSkill,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listSkill,&pageCount);//����CListCtrl����

				if(pageCount<0)//ҳ��<=0��˵��û�����ݷ���
				{
					nItem = -1;//����ѡ��ĳһ��
					pageUInfo = false;//���ܷ�ҳ					
					cmbSkillPage.ResetContent();//���ҳ����ѡ��
					while(listSkill.DeleteColumn(0)){}//���CListCtrl����
				}
				else
				{
					nItem = 0;
					cmbSkillPage.ResetContent();//���ҳ����ѡ���Ա����¹���
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbSkillPage.AddString(str);//�ڸ�ѡ���й���ҳ����Ϣ
					}
					cmbSkillPage.SetCurSel(0);//�ڸ�ѡ����ѡ�е�һҳ
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
		//�޸���ҽ�ɫ���ܵȼ�
	case CEnumCore::Message_Tag_ID::CG2_Update_Account_Skill_Query_Resp:
		//��Ӽ�����Ϣ
	case CEnumCore::Message_Tag_ID::CG2_Insert_Account_Skill_Query_Resp:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//��ʾ�������
			tbcResult.SetCurSel(1);

			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBSKILLPAGE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_LISTSKILLINFO)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_STATICSKILL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICCURLEVEL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICNEWLEVEL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ETSKILL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ETCURLEVEL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBNEWLEVEL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATICSKILLTYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICSKILLNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATICSKILLLEVEL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBSKILLTYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBSKILLNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ETSKILLLEVEL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTADDSKILL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTRESETSKILL)->ShowWindow(SW_HIDE);

			cmbNewLevel.ResetContent();
			SetLevel();

			UpdateData(true);

			SkillInfo();
		}
		break;

		
		//��ѯ�������
	case CEnumCore::Message_Tag_ID::CG2_GerSkill_Query_Resp:
		{
			theApp.operCG2.BuildJobCombox(&socketdata,&cmbSkillType);//���켼�������Ͽ�
		}
		break;
		//�������Ʋ�ѯ
	case CEnumCore::Message_Tag_ID::CG2_SkillList_Query_Resp:
		{
			theApp.operCG2.BuildJobCombox(&socketdata,&cmbSkillName);//���켼��������Ͽ�
		}
		break;
	}


	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}


















