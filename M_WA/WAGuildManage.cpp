// WAGuildManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_WA.h"
#include "WAGuildManage.h"
#include ".\waguildmanage.h"


// CWAGuildManage �Ի���

IMPLEMENT_DYNAMIC(CWAGuildManage, CDialog)
CWAGuildManage::CWAGuildManage(CWnd* pParent /*=NULL*/)
	: CDialog(CWAGuildManage::IDD, pParent)
{
}

CWAGuildManage::~CWAGuildManage()
{
}

void CWAGuildManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBBASIC, cmbBasic);
	DDX_Control(pDX, IDC_CMBRESULT, cmbResult);	

	DDX_Control(pDX, IDC_LISTBASIC, listBasic);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);

	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
}


BEGIN_MESSAGE_MAP(CWAGuildManage, CDialog)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LISTBASIC, OnNMClickListbasic)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTBASIC, OnNMDblclkListbasic)
	ON_CBN_SELCHANGE(IDC_CMBRESULT, OnCbnSelchangeCmbresult)
	ON_CBN_SELCHANGE(IDC_CMBBASIC, OnCbnSelchangeCmbbasic)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
	ON_BN_CLICKED(IDC_BTNEDIT, OnBnClickedBtnedit)
	ON_BN_CLICKED(IDC_BTNDEL, OnBnClickedBtndel)
	ON_BN_CLICKED(IDC_BTNTRANSFER, OnBnClickedBtntransfer)
END_MESSAGE_MAP()


// CWAGuildManage ��Ϣ�������

// ��ʼ���Ի���
BOOL CWAGuildManage::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// ��ʼ����ʾ�ַ�	
	nItem = -1;
	pageBasic = false;
	pageResult = false;
	ServerIP = "";
	UserID = "";
	UserName = "";
	UserNick = "";//��ʼ��һЩ˽�б���

	ShowEditInfo(SW_HIDE);	
	ShowResultInfo(SW_HIDE);
	ShowBasicInfo(SW_SHOW);

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


	dlgStatus = theApp.operWA.ReadIntValue("MWA","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���
	if(theApp.operWA.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}
	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CWAGuildManage::InitUI()
{
	SetWindowText(theApp.operWA.ReadValue("MWA","GM_UI_GuildManage"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operWA.ReadValue("MWA","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operWA.ReadValue("MWA","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLNAME,theApp.operWA.ReadValue("MWA","GM_UI_GuildName"));
	SetDlgItemText(IDSEARCH,theApp.operWA.ReadValue("MWA","Search"));
	SetDlgItemText(IDCANCEL,theApp.operWA.ReadValue("MWA","Reset"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operWA.ReadValue("MWA","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLEDITNAME,theApp.operWA.ReadValue("MWA","GM_UI_GuildName"));
	SetDlgItemText(IDC_BTNDEL,theApp.operWA.ReadValue("MWA","GM_UI_DelGuild"));
	SetDlgItemText(IDC_BTNTRANSFER,theApp.operWA.ReadValue("MWA","GM_UI_TransferPrev"));

	SetDlgItemText(IDC_LBLMODNAME,theApp.operWA.ReadValue("MWA","GM_UI_GuildName"));
	SetDlgItemText(IDC_LBLNEWVALUE,theApp.operWA.ReadValue("MWA","GM_UI_NewGuildName"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operWA.ReadValue("MWA","GM_UI_EditName"));
	SetDlgItemText(IDC_BTNRESET,theApp.operWA.ReadValue("MWA","AM_UI_Reset"));

	tbcResult.InsertItem(0,theApp.operWA.ReadValue("MWA","GI_UI_GuildInfo"));
	tbcResult.InsertItem(1,theApp.operWA.ReadValue("MWA","GI_UI_GuildMember"));
	//tbcResult.InsertItem(3,theApp.operWA.ReadValue("MWA","GM_UI_EditGuild"));
}


// �Զ��ı��С
void CWAGuildManage::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CWAGuildManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ����������Ϣ
void CWAGuildManage::OnBnClickedSearch()
{
	try
	{
		CIni mIni;

		tbcResult.SetCurSel(0);

		nItem = -1;//���������б�û��ѡ����
		pageBasic = false;//���������б��ܷ�ҳ	
		cmbBasic.ResetContent();//������������б�ҳ�ĸ�ѡ��
		while(listBasic.DeleteColumn(0)){}//������������б��е���������

		ShowEditInfo(SW_HIDE);	
		ShowResultInfo(SW_HIDE);
		ShowBasicInfo(SW_SHOW);

		UpdateData(true);			

		CString m_ServerName;
		GetDlgItemText(IDC_CMBSERVER,m_ServerName);//��ȡ��Ϸ������������
		if(m_ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_SelectServer"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITNAME,GuildName);//��ȡ��������
		BasicInfo();// ��ѯ����������Ϣ
	}
	catch(...)
	{
	}
}

// ��ѯ����������Ϣ
void CWAGuildManage::BasicInfo()
{	
	try
	{		
		CIni mIni;		

		int index = theApp.operWA.ReadIntValue("MWA","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//���������б�û��ѡ����
		pageBasic = false;//���������б��ܷ�ҳ	
		cmbBasic.ResetContent();//������������б�ҳ�ĸ�ѡ��
		while(listBasic.DeleteColumn(0)){}//������������б��е���������

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//������IP���������ơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
			
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_MercenaryGroup_Info_Query);//���Ͳ�ѯ����������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_BasicInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// ��ҳ��ѯ����������Ϣ
void CWAGuildManage::OnCbnSelchangeCmbbasic()
{	
	try
	{	
		if(pageBasic)//������Է�ҳ�Ļ�
		{
			CIni mIni;

			int index = cmbBasic.GetCurSel() + 1;//ҳ��ΪcmbBasic��ǰ������ֵ��1��Ҳ����cmbBasic�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//ÿҳ��ʾ50����¼

			while(listBasic.DeleteColumn(0)){}//���ҳ������

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
			
			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_MercenaryGroup_Info_Query);//���Ͳ�ѯ����������Ϣ������

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// ��������������Ϣ���浱ǰ�к�
void CWAGuildManage::OnNMClickListbasic(NMHDR *pNMHDR, LRESULT *pResult)
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

			nItem = listBasic.SubItemHitTest(&lvinfo);//�����ڻ���������Ϣ�б���ѡ�е��к�

			if(nItem >= 0)
			{			
				GuildID = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_GuildID"));// ����ѡ�еĹ���ID
				GuildName = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_GuildName"));// ����ѡ�еĹ�����Ϣ
				SetDlgItemText(IDC_EDITEDITNAME,GuildName);
			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

// ˫������������Ϣ���в�ѯ
void CWAGuildManage::OnNMDblclkListbasic(NMHDR *pNMHDR, LRESULT *pResult)
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
				pageResult = false;
				cmbResult.ResetContent();
				while(listResult.DeleteColumn(0)){}// �������б��е���������

				ShowBasicInfo(SW_HIDE);
				ShowResultInfo(SW_SHOW);
				SetDlgItemText(IDC_LBLEDITNAME,theApp.operWA.ReadValue("MWA","GM_UI_MemberName"));
				SetDlgItemText(IDC_EDITEDITNAME,"");
				SetDlgItemText(IDC_BTNDEL,theApp.operWA.ReadValue("MWA","GM_UI_DelMember"));

				GuildID = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_GuildID"));// ����ѡ�еĹ���ID
				GuildName = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_GuildName"));// ����ѡ�еĹ�����Ϣ

				tbcResult.SetCurSel(1);

				//��ѯ���������Ϣ
				ResultInfo();
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
void CWAGuildManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{		
	OnBnClickedBtnreset();
	if(tbcResult.GetCurSel() == 0)//ѡ�е��ǻ���������Ϣѡ�
	{
		ShowEditInfo(SW_HIDE);	
		ShowResultInfo(SW_HIDE);
		ShowBasicInfo(SW_SHOW);

		SetDlgItemText(IDC_LBLEDITNAME,theApp.operWA.ReadValue("MWA","GM_UI_GuildName"));
		SetDlgItemText(IDC_BTNDEL,theApp.operWA.ReadValue("MWA","GM_UI_DelGuild"));
	}
	else if(tbcResult.GetCurSel() == 1)//ѡ�е��ǽ��������Ϣѡ�
	{
		pageResult = false;
		cmbResult.ResetContent();
		while(listResult.DeleteColumn(0)){}// �������б��е���������

		ShowEditInfo(SW_HIDE);
		ShowBasicInfo(SW_HIDE);		
		ShowResultInfo(SW_SHOW);

		SetDlgItemText(IDC_LBLEDITNAME,theApp.operWA.ReadValue("MWA","GM_UI_MemberName"));
		SetDlgItemText(IDC_BTNDEL,theApp.operWA.ReadValue("MWA","GM_UI_DelMember"));

		if((listBasic.GetItemCount() > 0) && (nItem >= 0))
		{
			GuildID = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_GuildID"));// ����ѡ�еĹ���ID
			GuildName = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_GuildName"));// ����ѡ�еĹ�������

			//��ѯ���������Ϣ
			ResultInfo();
		}
	}
	else if(tbcResult.GetCurSel() == 2)//ѡ�е��ǽ��������Ϣѡ�
	{
		pageResult = false;
		cmbResult.ResetContent();
		while(listResult.DeleteColumn(0)){}// �������б��е���������

		ShowEditInfo(SW_HIDE);
		ShowBasicInfo(SW_HIDE);		
		ShowResultInfo(SW_SHOW);

		if((listBasic.GetItemCount() > 0) && (nItem >= 0))
		{
			GuildID = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_GuildID"));// ����ѡ�еĹ���ID
			GuildName = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_GuildName"));// ����ѡ�еĹ�������

			SetDlgItemText(IDC_EDITMODNAME,GuildName);
		}
	}
	*pResult = 0;
}

//��ѯ���������Ϣ
void CWAGuildManage::ResultInfo()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listBasic.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_GuildID,CEnumCore::TagFormat::TLV_STRING,strlen(GuildID),(unsigned char *)mIni.wcharToChar(GuildID));//����ID
			socketdata.AddTFLV(CEnumCore::TagName::WA_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
			
			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operWA.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_MemberList_Query);//��ؼ�¼��Ϣ

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_ResultInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// ��ҳ���в�ѯ
void CWAGuildManage::OnCbnSelchangeCmbresult()
{	
	try
	{
		if(pageResult)
		{
			CIni mIni;

			int index = cmbResult.GetCurSel() + 1;
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

			while(listResult.DeleteColumn(0)){}

			if((listBasic.GetItemCount() > 0) && (nItem>=0))
			{
				CSocketData socketdata;
				socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
				socketdata.AddTFLV(CEnumCore::TagName::WA_GuildID,CEnumCore::TagFormat::TLV_STRING,strlen(GuildID),(unsigned char *)mIni.wcharToChar(GuildID));//����ID
				socketdata.AddTFLV(CEnumCore::TagName::WA_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
			
				_itoa(index,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

				_itoa(iPageSize,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

				int midlength = socketdata.EnBody();
				theApp.operWA.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_MemberList_Query);//��ؼ�¼��Ϣ
				
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				socketdata.Destroy();
			}
		}		
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_ResultInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

//��������б����к�
void CWAGuildManage::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listResult.GetItemCount() != 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		mItem = listResult.SubItemHitTest(&lvinfo);//�����ڽ����Ϣ�б���ѡ�е��к�

		if(mItem >= 0)
		{			
			UserName = theApp.operWA.GetValueByColName(&listResult, mItem, theApp.operWA.ReadValue("MWA","WA_Account"));// ����ѡ�е�����ʺ�
			UserID = theApp.operWA.GetValueByColName(&listResult, mItem, theApp.operWA.ReadValue("MWA","WA_NickID"));// ����ѡ�е����ID
			UserNick = theApp.operWA.GetValueByColName(&listResult, mItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// ����ѡ�е�����ǳ�
			SetDlgItemText(IDC_EDITEDITNAME,UserNick);
		}
	}
	else
	{
		mItem = -1;
	}
	*pResult = 0;
}

//ִ����Ӧ�Ĳ�����Ϣ
void CWAGuildManage::OnBnClickedBtndel()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if(tbcResult.GetCurSel() == 0)
		{
			if((listBasic.GetItemCount() == 0) || (nItem<0))
				return;
		}
		else if(tbcResult.GetCurSel() == 1)
		{
			if((listResult.GetItemCount() == 0) || (mItem<0))
				return;	
		}

		GetDlgItemText(IDC_EDITEDITNAME,UserNick);//��ȡ����ʺ�
		if(UserNick == "")//Ҫ�߳����������ǳƲ���Ϊ��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","GM_HINT_PARAMNULL"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

		int userbyID = theApp.UserByID;
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

		socketdata.AddTFLV(CEnumCore::TagName::WA_GuildID,CEnumCore::TagFormat::TLV_STRING,strlen(GuildID),(unsigned char *)mIni.wcharToChar(GuildID));//����ID
		socketdata.AddTFLV(CEnumCore::TagName::WA_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
		
		int midlength = socketdata.EnBody();
		if(tbcResult.GetCurSel() == 0)
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_DissolveGuild_Operate);//��ɢ����
		else if(tbcResult.GetCurSel() ==1)
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_KickGuildMember_Operate);//�߳������Ա

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","GM_Error_EditGuild"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

//ת��Ӷ�����ų���Ȩ��
void CWAGuildManage::OnBnClickedBtntransfer()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listResult.GetItemCount() > 0) && (mItem>=0))
		{		
			GetDlgItemText(IDC_EDITEDITNAME,UserNick);//��ȡ����ʺ�
			if(UserNick == "")//Ҫת��Ӷ�����ų���Ȩ�޵�����ʺŲ���Ϊ��
			{
				MessageBox(theApp.operWA.ReadValue("MWA","GM_HINT_PARAMNULL"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

			socketdata.AddTFLV(CEnumCore::TagName::WA_GuildID,CEnumCore::TagFormat::TLV_STRING,strlen(GuildID),(unsigned char *)mIni.wcharToChar(GuildID));//����ID
			socketdata.AddTFLV(CEnumCore::TagName::WA_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
			
			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_AttornPopedom_Operate);//ת��Ӷ�����ų���Ȩ��

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","GM_Error_TransferPrev"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

//�޸�Ӷ���������Ϣ
void CWAGuildManage::OnBnClickedBtnedit()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listBasic.GetItemCount() > 0) && (nItem>=0))
		{
			GetDlgItemText(IDC_EDITMODNAME,GuildName);//��ȡԭ��������
			if(GuildName == "")//Ҫ�޸ĵĹ������Ʋ���Ϊ��
			{
				MessageBox(theApp.operWA.ReadValue("MWA","GM_HINT_PARAMNULL"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}

			CString NewGuildName = "";
			GetDlgItemText(IDC_EDITNEWVALUE,NewGuildName);//��ȡ��������
			if(NewGuildName == "")//�޸ĺ�Ĺ������Ʋ���Ϊ��
			{
				MessageBox(theApp.operWA.ReadValue("MWA","GM_HINT_PARAMNULL"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_GuildID,CEnumCore::TagFormat::TLV_STRING,strlen(GuildID),(unsigned char *)mIni.wcharToChar(GuildID));//����ID
			socketdata.AddTFLV(CEnumCore::TagName::WA_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
			socketdata.AddTFLV(CEnumCore::TagName::WA_NewGuildName,CEnumCore::TagFormat::TLV_STRING,strlen(NewGuildName),(unsigned char *)mIni.wcharToChar(NewGuildName));//�¹�������
			
			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ������

			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_ModifyGuildName_Operate);//�޸Ĺ�������

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","GM_Error_EditName"),theApp.operWA.ReadValue("MWA","Error"),0);
	}
}

//����Ӷ���Ź�����Ϣ
void CWAGuildManage::OnBnClickedBtnreset()
{
	SetDlgItemText(IDC_EDITNEWVALUE,"");
	SetDlgItemText(IDC_EDITEDITNAME,"");
}

// ���շ�����Ϣ
LRESULT CWAGuildManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{	
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);	
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

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
			theApp.operWA.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_MercenaryGroup_Info_Query_Resp://��ѯ����������Ϣ�Ļ�Ӧ
		{
			if(pageBasic)//����Ѿ��ܹ���ҳ
			{
				theApp.operWA.BuildDataTable(&socketdata,&listBasic,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listBasic,&pageCount);//����CListCtrl����

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
	case CEnumCore::Message_Tag_ID::WA_DissolveGuild_Operate_Resp://��ɢ����
	case CEnumCore::Message_Tag_ID::WA_KickGuildMember_Operate_Resp://�߳������Ա
	case CEnumCore::Message_Tag_ID::WA_AttornPopedom_Operate_Resp://�������
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//��ʾ���ؽ��
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_ModifyGuildName_Operate_Resp://�޸Ĺ�������
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//��ʾ���ؽ��

			SetDlgItemText(IDC_EDITNEWVALUE,"");
		}
		break;
	default:
		{
			if(pageResult)//����Ѿ��ܹ���ҳ
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

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
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

// ���ҳ��
void CWAGuildManage::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITNAME,"");
}

// �رնԻ���
void CWAGuildManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//ȫѡ������
BOOL CWAGuildManage::PreTranslateMessage(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listBasic.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listBasic);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listResult);
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

//����������Ϣҳ��
void CWAGuildManage::ShowBasicInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_LBLEDITNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITEDITNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNDEL)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_EDITEDITNAME,"");
}

//���������Ϣҳ��
void CWAGuildManage::ShowResultInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBRESULT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_LBLEDITNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITEDITNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNDEL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNTRANSFER)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_EDITEDITNAME,"");
}

//�޸���Ϣҳ��
void CWAGuildManage::ShowEditInfo(int m_cmdShow)
{
	SetDlgItemText(IDC_EDITNEWVALUE,"");

	GetDlgItem(IDC_LBLMODNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITMODNAME)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_LBLNEWVALUE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNEWVALUE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(m_cmdShow);
}
