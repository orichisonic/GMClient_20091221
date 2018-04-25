// XDGuildManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_XD.h"
#include "XDGuildManage.h"
#include ".\xdguildmanage.h"


// CXDGuildManage �Ի���

IMPLEMENT_DYNAMIC(CXDGuildManage, CDialog)
CXDGuildManage::CXDGuildManage(CWnd* pParent /*=NULL*/)
	: CDialog(CXDGuildManage::IDD, pParent)
{
}

CXDGuildManage::~CXDGuildManage()
{
}

void CXDGuildManage::DoDataExchange(CDataExchange* pDX)
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

	DDX_Control(pDX, IDC_CMBTYPE, cmbType);
}


BEGIN_MESSAGE_MAP(CXDGuildManage, CDialog)
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
	ON_CBN_SELCHANGE(IDC_CMBTYPE, OnCbnSelchangeCmbtype)
END_MESSAGE_MAP()


// CXDGuildManage ��Ϣ�������

// ��ʼ���Ի���
BOOL CXDGuildManage::OnInitDialog()
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


	dlgStatus = theApp.operXD.ReadIntValue("MXD","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���
	if(theApp.operXD.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}
	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CXDGuildManage::InitUI()
{
	SetWindowText(theApp.operXD.ReadValue("MXD","GM_UI_GuildManage"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operXD.ReadValue("MXD","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operXD.ReadValue("MXD","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLNAME,theApp.operXD.ReadValue("MXD","GM_UI_GuildName"));
	SetDlgItemText(IDSEARCH,theApp.operXD.ReadValue("MXD","Search"));
	SetDlgItemText(IDCANCEL,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operXD.ReadValue("MXD","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLEDITNAME,theApp.operXD.ReadValue("MXD","GM_UI_MemberName"));
	SetDlgItemText(IDC_BTNDEL,theApp.operXD.ReadValue("MXD","GM_UI_DelMember"));

	SetDlgItemText(IDC_LBLMODNAME,theApp.operXD.ReadValue("MXD","GM_UI_GuildName"));
	SetDlgItemText(IDC_LBLTYPE,theApp.operXD.ReadValue("MXD","GM_UI_Type"));
	SetDlgItemText(IDC_LBLNEWVALUE,theApp.operXD.ReadValue("MXD","GM_UI_NewValue"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","GM_UI_Edit"));
	SetDlgItemText(IDC_BTNRESET,theApp.operXD.ReadValue("MXD","Reset"));

	tbcResult.InsertItem(0,theApp.operXD.ReadValue("MXD","GI_UI_GuildInfo"));
	tbcResult.InsertItem(1,theApp.operXD.ReadValue("MXD","GI_UI_GuildMember"));
	tbcResult.InsertItem(2,theApp.operXD.ReadValue("MXD","GM_UI_InfoEdit"));
	//tbcResult.InsertItem(3,theApp.operXD.ReadValue("MXD","GM_UI_GuildEdit"));	

	cmbType.ResetContent();
	cmbType.AddString(theApp.operXD.ReadValue("MXD","GM_UI_Level"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","GM_UI_Name"));
}


// �Զ��ı��С
void CXDGuildManage::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CXDGuildManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ����������Ϣ
void CXDGuildManage::OnBnClickedSearch()
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
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_SelectServer"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
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
void CXDGuildManage::BasicInfo()
{	
	try
	{		
		CIni mIni;		

		int index = theApp.operXD.ReadIntValue("MXD","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//���������б�û��ѡ����
		pageBasic = false;//���������б��ܷ�ҳ	
		cmbBasic.ResetContent();//������������б�ҳ�ĸ�ѡ��
		while(listBasic.DeleteColumn(0)){}//������������б��е���������

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//������IP���������ơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
		
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_GuildBaseInfo_Query);//���Ͳ�ѯ����������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_BasicInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

// ��ҳ��ѯ����������Ϣ
void CXDGuildManage::OnCbnSelchangeCmbbasic()
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
			socketdata.InitCreate(1,10);//������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
			
			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_GuildBaseInfo_Query);//���Ͳ�ѯ����������Ϣ������

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
void CXDGuildManage::OnNMClickListbasic(NMHDR *pNMHDR, LRESULT *pResult)
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
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

// ˫������������Ϣ���в�ѯ
void CXDGuildManage::OnNMDblclkListbasic(NMHDR *pNMHDR, LRESULT *pResult)
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

				GuildID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildID"));// ����ѡ�еĹ���ID
				GuildName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildName"));// ����ѡ�еĹ�������

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
void CXDGuildManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{		
	OnBnClickedBtnreset();
	if(tbcResult.GetCurSel() == 0)//ѡ�е��ǻ���������Ϣѡ�
	{
		ShowEditInfo(SW_HIDE);	
		ShowResultInfo(SW_HIDE);
		ShowBasicInfo(SW_SHOW);
	}
	else if(tbcResult.GetCurSel() == 1)//ѡ�е��ǽ��������Ϣѡ�
	{
		pageResult = false;
		cmbResult.ResetContent();
		while(listResult.DeleteColumn(0)){}// �������б��е���������

		ShowEditInfo(SW_HIDE);
		ShowBasicInfo(SW_HIDE);		
		ShowResultInfo(SW_SHOW);

		if((listBasic.GetItemCount() > 0) && (nItem >= 0))
		{
			GuildID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildID"));// ����ѡ�еĹ���ID
			GuildName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildName"));// ����ѡ�еĹ�������

			//��ѯ���������Ϣ
			ResultInfo();
		}
	}
	else if(tbcResult.GetCurSel() == 3)//ѡ�е��ǽ�ɢ/�ָ�����ҳ��
	{
		ShowBasicInfo(SW_HIDE);		
		ShowResultInfo(SW_HIDE);
		ShowEditInfo(SW_SHOW);

		GetDlgItem(IDC_LBLTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBTYPE)->ShowWindow(SW_HIDE);	
		GetDlgItem(IDC_LBLNEWVALUE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITNEWVALUE)->ShowWindow(SW_HIDE);

		SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","GM_UI_DelGuild"));
		SetDlgItemText(IDC_BTNRESET,theApp.operXD.ReadValue("MXD","GM_UI_RecoverGuild"));

		if((listBasic.GetItemCount() > 0) && (nItem >= 0))
		{
			GuildID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildID"));// ����ѡ�еĹ���ID
			GuildName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildName"));// ����ѡ�еĹ�������

			SetDlgItemText(IDC_EDITMODNAME,GuildName);
		}
	}
	else if(tbcResult.GetCurSel() == 2)//ѡ�е����޸Ĺ�����Ϣ
	{
		ShowBasicInfo(SW_HIDE);		
		ShowResultInfo(SW_HIDE);
		ShowEditInfo(SW_SHOW);

		SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","GM_UI_Edit"));
		SetDlgItemText(IDC_BTNRESET,theApp.operXD.ReadValue("MXD","Reset"));

		if((listBasic.GetItemCount() > 0) && (nItem >= 0))
		{
			GuildID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildID"));// ����ѡ�еĹ���ID
			GuildName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildName"));// ����ѡ�еĹ�������

			SetDlgItemText(IDC_EDITMODNAME,GuildName);
		}
	}
	*pResult = 0;
}

//��ѯ���������Ϣ
void CXDGuildManage::ResultInfo()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listBasic.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildID,CEnumCore::TagFormat::TLV_STRING,strlen(GuildID),(unsigned char *)mIni.wcharToChar(GuildID));//����ID
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
			
			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_GuildMemberList_Query);//��ؼ�¼��Ϣ

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_ResultInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

// ��ҳ���в�ѯ
void CXDGuildManage::OnCbnSelchangeCmbresult()
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
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildID,CEnumCore::TagFormat::TLV_STRING,strlen(GuildID),(unsigned char *)mIni.wcharToChar(GuildID));//����ID
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
			
				_itoa(index,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

				_itoa(iPageSize,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

				int midlength = socketdata.EnBody();
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_GuildMemberList_Query);//��ؼ�¼��Ϣ
				
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				socketdata.Destroy();
			}
		}		
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_ResultInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

//��������б����к�
void CXDGuildManage::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
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
			UserName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// ����ѡ�е�����ʺ�
			//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_AccountID"));// ����ѡ�е����ID
			UserNick = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// ����ѡ�е�����ǳ�

			SetDlgItemText(IDC_EDITEDITNAME,UserNick);
		}
	}
	else
	{
		mItem = -1;
	}
	*pResult = 0;
}

//����˳�����
void CXDGuildManage::OnBnClickedBtndel()
{
	try
	{
		if((listResult.GetItemCount() == 0) || (mItem<0))
			return;	

		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		GetDlgItemText(IDC_EDITEDITNAME,UserNick);//��ȡ����ʺ�
		if(UserNick == "")//Ҫ�߳����������ǳƲ���Ϊ��
		{
			MessageBox(theApp.operXD.ReadValue("MXD","GM_HINT_PARAMNULL"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��

		int userbyID = theApp.UserByID;
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildID,CEnumCore::TagFormat::TLV_STRING,strlen(GuildID),(unsigned char *)mIni.wcharToChar(GuildID));//����ID
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
		
		int midlength = socketdata.EnBody();
		//theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_KickGuildMember_Operate);//����˳�����

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","GM_Error_EditGuild"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//�л�������Ϣ�޸ĵ�����
void CXDGuildManage::OnCbnSelchangeCmbtype()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//�޸Ĺ��������Ϣ
void CXDGuildManage::OnBnClickedBtnedit()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listBasic.GetItemCount() > 0) && (nItem>=0))
		{
			GetDlgItemText(IDC_EDITMODNAME,GuildName);//��ȡԭ��������
			if(GuildName == "")//Ҫ�޸ĵĹ������Ʋ���Ϊ��
			{
				MessageBox(theApp.operXD.ReadValue("MXD","GM_HINT_PARAMNULL"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}

			CString NewValue = "";			
			if(tbcResult.GetCurSel() == 3)
			{
				GetDlgItemText(IDC_EDITNEWVALUE,NewValue);//��ȡ�޸ĺ��ֵ
				if(NewValue == "")//�޸ĺ��ֵ����Ϊ��
				{
					MessageBox(theApp.operXD.ReadValue("MXD","GM_HINT_PARAMNULL"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
			}

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildID,CEnumCore::TagFormat::TLV_STRING,strlen(GuildID),(unsigned char *)mIni.wcharToChar(GuildID));//����ID
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
			
			//socketdata.AddTFLV(CEnumCore::TagName::WA_NewGuildName,CEnumCore::TagFormat::TLV_STRING,strlen(NewGuildName),(unsigned char *)mIni.wcharToChar(NewGuildName));//�¹�������
			
			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ������

			int midlength = socketdata.EnBody();
			//theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_ModifyGuildName_Operate);//�޸Ĺ�������

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","GM_Error_EditName"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

//���ù��������Ϣ
void CXDGuildManage::OnBnClickedBtnreset()
{	
	try
	{
		SetDlgItemText(IDC_EDITNEWVALUE,"");
		SetDlgItemText(IDC_EDITEDITNAME,"");
		if(tbcResult.GetCurSel() == 2)
		{
			CIni mIni;

			int index = theApp.operXD.ReadIntValue("MXD","index");
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

			if((listBasic.GetItemCount() > 0) && (nItem>=0))
			{
				GetDlgItemText(IDC_EDITMODNAME,GuildName);//��ȡ��������
				if(GuildName == "")//Ҫ�޸ĵĹ������Ʋ���Ϊ��
				{
					MessageBox(theApp.operXD.ReadValue("MXD","GM_HINT_PARAMNULL"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}

				CSocketData socketdata;
				socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildID,CEnumCore::TagFormat::TLV_STRING,strlen(GuildID),(unsigned char *)mIni.wcharToChar(GuildID));//����ID
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
				
				//socketdata.AddTFLV(CEnumCore::TagName::WA_NewGuildName,CEnumCore::TagFormat::TLV_STRING,strlen(NewGuildName),(unsigned char *)mIni.wcharToChar(NewGuildName));//�¹�������
				
				int userbyID = theApp.UserByID;
				_itoa(userbyID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

				_itoa(0,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
				_itoa(0,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ������

				int midlength = socketdata.EnBody();
				//theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_ModifyGuildName_Operate);//�޸Ĺ�������

				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

				socketdata.Destroy();
			}
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","GM_Error_EditName"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

// ���շ�����Ϣ
LRESULT CXDGuildManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::WA_MercenaryGroup_Info_Query_Resp://��ѯ����������Ϣ�Ļ�Ӧ
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
	case CEnumCore::Message_Tag_ID::WA_DissolveGuild_Operate_Resp://��ɢ����
	case CEnumCore::Message_Tag_ID::WA_KickGuildMember_Operate_Resp://�߳������Ա
	case CEnumCore::Message_Tag_ID::WA_AttornPopedom_Operate_Resp://�������
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operXD.ShowResult(result);//��ʾ���ؽ��
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_ModifyGuildName_Operate_Resp://�޸Ĺ�������
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operXD.ShowResult(result);//��ʾ���ؽ��

			SetDlgItemText(IDC_EDITNEWVALUE,"");
		}
		break;
	default:
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
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

// ���ҳ��
void CXDGuildManage::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITNAME,"");
}

// �رնԻ���
void CXDGuildManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//ȫѡ������
BOOL CXDGuildManage::PreTranslateMessage(MSG* pMsg)
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

//����������Ϣҳ��
void CXDGuildManage::ShowBasicInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);
}

//���������Ϣҳ��
void CXDGuildManage::ShowResultInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBRESULT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_LBLEDITNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITEDITNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNDEL)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_EDITEDITNAME,"");
}

//�޸���Ϣҳ��
void CXDGuildManage::ShowEditInfo(int m_cmdShow)
{
	SetDlgItemText(IDC_EDITNEWVALUE,"");

	GetDlgItem(IDC_LBLMODNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITMODNAME)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_LBLTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBTYPE)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_LBLNEWVALUE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNEWVALUE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(m_cmdShow);
}
