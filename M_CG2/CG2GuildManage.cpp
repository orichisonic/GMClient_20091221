// CG2GuildManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2GuildManage.h"
#include ".\CG2GuildManage.h"


// CCG2GuildManage �Ի���

IMPLEMENT_DYNAMIC(CCG2GuildManage, CDialog)
CCG2GuildManage::CCG2GuildManage(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2GuildManage::IDD, pParent)
{
}

CCG2GuildManage::~CCG2GuildManage()
{
}

void CCG2GuildManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbUPage);
	DDX_Control(pDX, IDC_LISTGUILDINFO,listGuild);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_EDITRESOURCE, m_Resource);
	DDX_Control(pDX, IDC_CMBNEWGUILDLEVEL, cmbNewGuildLevel);
}


BEGIN_MESSAGE_MAP(CCG2GuildManage, CDialog)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_CBN_SELCHANGE(IDC_CMBUIPAGE, OnCbnSelchangeCmbuipage)
	ON_NOTIFY(NM_CLICK, IDC_LISTGUILDINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTGUILDINFO, OnNMDblclkListuserinfo)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_BN_CLICKED(IDC_BTNCHANGE, OnBnClickedBtnchange)
END_MESSAGE_MAP()

// ��ʼ���Ի���
BOOL CCG2GuildManage::OnInitDialog()
{
	CDialog::OnInitDialog();	
	InitUI();// ��ʼ����ʾ�ַ�	
	//InitBanType();

	nItem = -1;// �����û��б�õ��к�
	mItem = -1;
	pageInfo = false;// �ж��Ƿ���Ҫ��ҳ
	pageUInfo = false;
	ServerIP = "";// ��Ϸ������IP	
	GuildName = "";//����ʺ�
	UserNick = "";//����ǳ�
	UserID = "";//���ID

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

		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listGuild.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listGuild.MoveWindow(newRect);//���ú�listResult��λ��
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//���ú�listResult��λ��
	}

	//��ʾ����
	ShowGuildName(SW_HIDE);
	ShowGuildLevel(SW_HIDE);
	ShowGuildHonor(SW_HIDE);

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//��ʼ�����Ի���

	theApp.operCG2.GetServerList();//�������е���Ϸ�������б�

	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//���Ͳ�ѯ����	

	

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CCG2GuildManage::InitUI()
{

	SetWindowText(theApp.operCG2.ReadValue("MCG2","CG2_UI_GuildManage"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operCG2.ReadValue("MCG2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIGUILDNAME,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblGuildName"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLHINT,theApp.operCG2.ReadValue("MCG2","BU_UI_LblHint"));	
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgGuildInfo"));
	tbcResult.InsertItem(1,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgGuildMember"));
	tbcResult.InsertItem(2,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgModifyGuildName"));
	tbcResult.InsertItem(3,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgModifyGuildLevel"));
	tbcResult.InsertItem(4,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgModifyGuildHonor"));


}

// �Զ��ı��С
void CCG2GuildManage::OnSize(UINT nType, int cx, int cy)
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

	if(GrpPage.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listGuild.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listGuild.MoveWindow(newRect);//���ú�listResult��λ��
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
HBRUSH CCG2GuildManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ������Ϣ
void CCG2GuildManage::OnBnClickedUisearch()
{
	try
	{

		nItem = -1;//�б�û��ѡ����
		mItem = -1;
		pageInfo = false;//�б��ܷ�ҳ	
		pageUInfo = false;
		cmbPage.ResetContent();//����б�ҳ�ĸ�ѡ��
		cmbUPage.ResetContent();
		while(listGuild.DeleteColumn(0)){}
		while(listResult.DeleteColumn(0)){}//����б��е���������

		UpdateData(true);			

		CString m_ServerName;
		GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//��ȡ��Ϸ������������
		if(m_ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_SelectServer"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP
	
		GetDlgItemText(IDC_EDITUIGUILDNAME,GuildName);//��ȡ����ʺ�
		GuildInfo();
		
	}
	catch(...)
	{
	}
}

// ��ѯ������Ϣ
void CCG2GuildManage::GuildInfo()
{
	try
	{		
		CIni mIni;	

		nItem = -1;
		pageUInfo = false;		
		cmbUPage.ResetContent();
		while(listGuild.DeleteColumn(0)){}
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//����ʺ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SearchGuild_Query);//���Ͳ�ѯ����������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

//��ѯ�����Ա
void CCG2GuildManage::GuildDetail()
{
	try
	{				
		CIni mIni;
		
		mItem = -1;
		pageInfo = false;		
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}

		char strInt[10];
		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//����ʺ�
		_itoa(GuildId,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_GuildID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SearchGuild_Detail_Query);
		
		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}
//�޸Ĺ�������
void CCG2GuildManage::RenameGuild()
{
	try
	{				
		CIni mIni;


		char strInt[10];
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		
		GetDlgItemText(IDC_EDITNEWGUILDNAME,GuildName);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//����ʺ�
		
		_itoa(GuildId,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_GuildID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_RenameGuild_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}
//�޸Ĺ���ȼ�
void CCG2GuildManage::UpdateGuildLevel()
{
	try
	{				
		CIni mIni;


		char strInt[10];

		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP

		socketdata.AddTFLV(CEnumCore::TagName::CG2_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//����ʺ�

		_itoa(GuildId,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_GuildID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int NewGuildLevel=0;
		NewGuildLevel=GetDlgItemInt(IDC_CMBNEWGUILDLEVEL);

		_itoa(NewGuildLevel,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_GuildRank,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_UpdateGuildLv_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}
// ��ҳ���в�ѯ
void CCG2GuildManage::OnCbnSelchangeCmbuipage()
{	
	////OperationCG2 operCG2;
	try
	{		
		if(pageUInfo)
		{	
			CIni mIni;

			while(listGuild.DeleteColumn(0)){}
			
			int index = cmbUPage.GetCurSel() + 1;//ҳ��ΪcmbPage��ǰ������ֵ��1��Ҳ����cmbPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼
			
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
		
			if(tbcResult.GetCurSel() == 0)
			{
				theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SearchGuild_Query);
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Page"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// ��ҳ��ѯ��Ա�б�
void CCG2GuildManage::OnCbnSelchangeCmbpage()
{
	//OperationCG2 operCG2;
	try
	{		
		if(pageInfo)
		{	
			CIni mIni;

			while(listResult.DeleteColumn(0)){}
			
			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbPage��ǰ������ֵ��1��Ҳ����cmbPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼
			
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
		
			if(tbcResult.GetCurSel() == 2)
			{				
				theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SearchGuild_Detail_Query);				
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Page"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// ����������Ϣ���浱ǰ�к�
void CCG2GuildManage::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listGuild.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listGuild.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listGuild.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

// ˫��������Ϣ���в���
void CCG2GuildManage::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		if(listGuild.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listGuild.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listGuild.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�

			if(nItem >= 0)
			{
				//////OperationCG2 operCG2;
				CIni mIni;
				if(tbcResult.GetCurSel() == 0)//�����ǰ�������������Ϣ��ҳ��
				{
					tbcResult.SetCurSel(1);//��ת�������ʺŷ�ͣ��ҳ��

					GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LISTGUILDINFO)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);

					
					GuildName = theApp.operCG2.GetValueByColName(&listGuild, nItem, theApp.operCG2.ReadValue("MCG2","CG2_GuildName"));// ����ѡ�еĹ�������
					GuildId = atoi(theApp.operCG2.GetValueByColName(&listGuild, nItem, theApp.operCG2.ReadValue("MCG2","CG2_GuildID")));//��ȡ����ID
					GuildDetail();	
				}	
				
			}
		}
		else
		{
			nItem = -1;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}


// �л�ѡ����в�ѯ
void CCG2GuildManage::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{	
	CIni mIni;
	//OperationCG2 operCG2;

	if(tbcResult.GetCurSel()==0)//���ѡ�е������������Ϣ��ҳ��
	{
		ShowGuildLevel(SW_HIDE);
		ShowGuildHonor(SW_HIDE);
		ShowGuildName(SW_HIDE);

		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTGUILDINFO)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
		
	}
	else if(tbcResult.GetCurSel()==1)//���ѡ�е��Ƿ�ͣ�ʺ��б��ҳ��
	{

		CIni mIni;
		pageInfo = false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}// �������б��е���������

		ShowGuildLevel(SW_HIDE);
		ShowGuildHonor(SW_HIDE);
		ShowGuildName(SW_HIDE);

		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTGUILDINFO)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);

		if((listGuild.GetItemCount() > 0) && (nItem >= 0))
		{
			GuildName = theApp.operCG2.GetValueByColName(&listGuild, nItem, theApp.operCG2.ReadValue("MCG2","CG2_GuildName"));// ����ѡ�еĹ�������
			GuildId = atoi(theApp.operCG2.GetValueByColName(&listGuild, nItem, theApp.operCG2.ReadValue("MCG2","CG2_GuildID")));//��ȡ����ID

			if(tbcResult.GetCurSel()==1)
			{
				GuildDetail();	// ��ѯ��Ա�б�
			}
			
		}
		
	}
	else if(tbcResult.GetCurSel()==2)
	{
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTGUILDINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

		ShowGuildLevel(SW_HIDE);
		ShowGuildHonor(SW_HIDE);
		ShowGuildName(SW_SHOW);
	}
	else if(tbcResult.GetCurSel()==3)
	{
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTGUILDINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

		ShowGuildHonor(SW_HIDE);
		ShowGuildName(SW_HIDE);
		ShowGuildLevel(SW_SHOW);
	}
	else if(tbcResult.GetCurSel()==5)
	{
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTGUILDINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

		
		ShowGuildName(SW_HIDE);
		ShowGuildLevel(SW_HIDE);
		ShowGuildHonor(SW_SHOW);
	}
	*pResult = 0;
}


// ���շ�����Ϣ
LRESULT CCG2GuildManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
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
				CString sIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ�������IP
				ServerList.SetAt(i,sIP);//��������IP������CMap��Ķ���ServerList��
			}

			theApp.operCG2.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_SearchGuild_Query_Resp://��ѯ����������Ϣ�Ļ�Ӧ
		{
			if(pageInfo)
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listGuild,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listGuild,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					nItem = -1;//����ѡ��ĳһ��
					pageInfo = false;//���ܷ�ҳ				
					cmbPage.ResetContent();//���ҳ����ѡ��
					while(listResult.DeleteColumn(0)){}//���CListCtrl����
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
	case CEnumCore::Message_Tag_ID::CG2_SearchGuild_Detail_Query_Resp://��ѯ�����Ա
		{
			if(pageInfo)
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					nItem = -1;
					pageInfo = false;					
					cmbPage.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					nItem = 0;
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
		CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
		CString result = (LPCTSTR)&m_tflv.lpdata;
		theApp.operCG2.ShowResult(result);//��ʾ�������
		break;
	}
	//socketdata.Destroy();
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	return false;
}

// �رնԻ���
void CCG2GuildManage::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIGUILDNAME,"");
}

// �رնԻ���
void CCG2GuildManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}



//��ʾ���Ĺ������ƽ���
void CCG2GuildManage::ShowGuildName(int m_cmdShow)
{
	
	GetDlgItem(IDC_EDITRESOURCE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLRESOURCE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNCHANGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_LBLNEWGUILDNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNEWGUILDNAME)->ShowWindow(m_cmdShow);

	if((listGuild.GetItemCount() > 0) && (nItem >= 0))
	{
		SetDlgItemText(IDC_LBLRESOURCE,theApp.operCG2.ReadValue("MCG2","BU_UI_OldGuildName"));
		SetDlgItemText(IDC_LBLNEWGUILDNAME,theApp.operCG2.ReadValue("MCG2","BU_UI_NewGuildName"));
		GuildName = theApp.operCG2.GetValueByColName(&listGuild, nItem, theApp.operCG2.ReadValue("MCG2","CG2_GuildName"));// ����ѡ�еĹ�������
		GuildId = atoi(theApp.operCG2.GetValueByColName(&listGuild, nItem, theApp.operCG2.ReadValue("MCG2","CG2_GuildID")));//��ȡ����ID
		SetDlgItemText(IDC_EDITRESOURCE,GuildName);
		m_Resource.SetReadOnly(true);

	}

}


//��ʾ���Ĺ���ȼ�����
void CCG2GuildManage::ShowGuildLevel(int m_cmdShow)
{
	GetDlgItem(IDC_EDITRESOURCE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLRESOURCE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNCHANGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNEWGUILDNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBNEWGUILDLEVEL)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_LBLRESOURCE,theApp.operCG2.ReadValue("MCG2","BU_UI_OldGuildLevel"));
	SetDlgItemText(IDC_LBLNEWGUILDNAME,theApp.operCG2.ReadValue("MCG2","BU_UI_NewGuildLevel"));
	int oldguildlevel=0;

	if((listGuild.GetItemCount() > 0) && (nItem >= 0))
	{
		
		GuildName = theApp.operCG2.GetValueByColName(&listGuild, nItem, theApp.operCG2.ReadValue("MCG2","CG2_GuildName"));// ����ѡ�еĹ�������
		GuildId = atoi(theApp.operCG2.GetValueByColName(&listGuild, nItem, theApp.operCG2.ReadValue("MCG2","CG2_GuildID")));//��ȡ����ID

		oldguildlevel= atoi(theApp.operCG2.GetValueByColName(&listGuild, nItem, theApp.operCG2.ReadValue("MCG2","CG2_GuildRank")));//��ȡ����ID

		SetDlgItemInt(IDC_EDITRESOURCE,oldguildlevel);

		m_Resource.SetReadOnly(true);
		cmbNewGuildLevel.ResetContent();
		cmbNewGuildLevel.AddString("1");
		cmbNewGuildLevel.AddString("2");
		cmbNewGuildLevel.AddString("3");
		cmbNewGuildLevel.AddString("4");
		cmbNewGuildLevel.SetCurSel(0);
	}
}

//��ʾ���Ĺ�����������
void CCG2GuildManage::ShowGuildHonor(int m_cmdShow)
{
	GetDlgItem(IDC_EDITRESOURCE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLRESOURCE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNEWGUILDNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNEWHONOR)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNCHANGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_LBLRESOURCE,theApp.operCG2.ReadValue("MCG2","BU_UI_OldGuildLevel"));
	SetDlgItemText(IDC_LBLNEWGUILDNAME,theApp.operCG2.ReadValue("MCG2","BU_UI_NewGuildLevel"));


}
//���Ĺ������ƣ�����ȼ�������������
void CCG2GuildManage::OnBnClickedBtnchange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(tbcResult.GetCurSel())
	{
	case 2:
		RenameGuild();
		break;
	case 3:
		UpdateGuildLevel();
		break;
	case 4:
		break;
	}
}
