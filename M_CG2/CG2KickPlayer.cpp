// CG2KickPlayer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2KickPlayer.h"
#include ".\CG2kickplayer.h"


// CCG2KickPlayer �Ի���

IMPLEMENT_DYNAMIC(CCG2KickPlayer, CDialog)
CCG2KickPlayer::CCG2KickPlayer(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2KickPlayer::IDD, pParent)
{
}

CCG2KickPlayer::~CCG2KickPlayer()
{
}

void CCG2KickPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBKPPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listResult);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPKPPAGE, GrpPage);
}


BEGIN_MESSAGE_MAP(CCG2KickPlayer, CDialog)
	ON_CBN_SELCHANGE(IDC_CMBKPPAGE, OnCbnSelchangeCmbkppage)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// ��ʼ���Ի���
BOOL CCG2KickPlayer::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// ��ʼ����ʾ�ַ�	

	nItem = -1;
	pageInfo = false;//��ʼ��һЩ˽�б���

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

	if(GrpPage.m_hWnd != NULL)
	{
		GrpPage.GetWindowRect(srcRect);//��ȡGrpPage�Ĵ�С��Ϣ
		grpPHeight = srcRect.bottom - srcRect.top;//�õ�GrpPage�ĸ߶���Ϣ

		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//���ú�listUser��λ��
	}

	//OperationCG2 theApp.operCG2;
	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//��ʼ�����Ի���

	theApp.operCG2.GetServerList();
	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//���Ͳ�ѯ����

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CCG2KickPlayer::InitUI()
{
	//OperationCG2 theApp.operCG2;

	SetWindowText(theApp.operCG2.ReadValue("MCG2","KP_UI_KickPlayer"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operCG2.ReadValue("MCG2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));
	SetDlgItemText(IDC_LBLHINT,theApp.operCG2.ReadValue("MCG2","KP_UI_KickHint"));
}

// �Զ��ı��С
void CCG2KickPlayer::OnSize(UINT nType, int cx, int cy)
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

	if(GrpPage.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//���ú�listResult��λ��
	}
}

//���ñ�����ɫ
HBRUSH CCG2KickPlayer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ���������Ϣ
void CCG2KickPlayer::OnBnClickedUisearch()
{
	try
	{
		//OperationCG2 theApp.operCG2;

		nItem = -1;//��������б�û��ѡ����
		pageInfo = false;//��������б��ܷ�ҳ	
		cmbPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listResult.DeleteColumn(0)){}//�����������б��е���������

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

	    UserInfo();
	}
	catch(...)
	{
	}
}

// ��ѯ���������Ϣ
void CCG2KickPlayer::UserInfo()
{
	//OperationCG2 theApp.operCG2;
	try
	{
		CIni mIni;	

		int index = theApp.operCG2.ReadIntValue("MCG2","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//��������б�û��ѡ����
		pageInfo = false;//��������б��ܷ�ҳ		
		cmbPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listResult.DeleteColumn(0)){}//�����������б��е���������		

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

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// ��ҳ���в�ѯ
void CCG2KickPlayer::OnCbnSelchangeCmbkppage()
{	
	try
	{
		if(pageInfo)//������Է�ҳ�Ļ�
		{	
			CIni mIni;
			//OperationCG2 theApp.operCG2;
			
			char strInt[10];
			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbPage��ǰ������ֵ��1��Ҳ����cmbPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼

			while(listResult.DeleteColumn(0)){}//���ҳ������

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Query);//��ǰ��״̬Ϊ���Ͳ�ѯ����

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// ˫�����������Ϣ��������
void CCG2KickPlayer::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		if(listResult.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listResult.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listResult.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

			if(nItem >= 0)
			{	
				CIni mIni;				
				//OperationCG2 theApp.operCG2;

				UserName = theApp.operCG2.GetValueByColName(&listResult, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
				UserID = theApp.operCG2.GetValueByColName(&listResult, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ����ѡ�е����ID
			    UserNick = theApp.operCG2.GetValueByColName(&listResult, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// ����ѡ�е�����ǳ�
				int iCharNo = atoi(theApp.operCG2.GetValueByColName(&listResult, nItem, theApp.operCG2.ReadValue("MCG2","CG2_CharacterNum")));//��ȡ��ɫ��

				if (AfxMessageBox(theApp.operCG2.ReadValue("MCG2","KP_Hint_KickPlayer"), MB_YESNO) == IDNO) 
				{
					return;
				}

				int userbyID = theApp.UserByID;

				CSocketData socketdata;
				socketdata.InitCreate(1,10);//�����ĸ�������������IP������ʺš����ID������ԱID
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
				socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
				socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
				socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//���IDKEY

				_itoa(iCharNo,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ɫ��


				_itoa(userbyID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

				int midlength = socketdata.EnBody();
				theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_KickAccount_Query);//����ǿ��������ߵ�����

				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

				socketdata.Destroy();
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

// ���շ�����Ϣ
LRESULT CCG2KickPlayer::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
				CString sIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ�������IP
				ServerList.SetAt(i,sIP);//��������IP������CMap��Ķ���ServerList��
			}

			theApp.operCG2.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Query_Resp ://��ѯ���������Ϣ�Ļ�Ӧ
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

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
	case CEnumCore::Message_Tag_ID::CG2_KickAccount_Query_Resp://ǿ��������ߵĻ�Ӧ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//��ʾ�������
			UserInfo();//��ѯ����ʺ���Ϣ
		}
		break;
	default:
		break;
	}
	socketdata.Destroy();
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	return false;
}

// �رնԻ���
void CCG2KickPlayer::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// �رնԻ���
void CCG2KickPlayer::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
