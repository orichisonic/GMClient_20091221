#include ".\modipwd.h"
// ModiPwd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_GM.h"
#include "ModiPwd.h"


// CModiPwd �Ի���

IMPLEMENT_DYNAMIC(CModiPwd, CDialog)
CModiPwd::CModiPwd(CWnd* pParent /*=NULL*/)
	: CDialog(CModiPwd::IDD, pParent)
{
}

CModiPwd::~CModiPwd()
{
}

void CModiPwd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModiPwd, CDialog)
	ON_BN_CLICKED(IDMPRESET, OnBnClickedMpreset)
	ON_BN_CLICKED(IDMODIPWD, OnBnClickedModipwd)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// ��ʼ���Ի���
BOOL CModiPwd::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();//��ʼ����ʾ�ַ�

	return TRUE;  // return TRUE unless you set the focus to a control
}

// ��ʼ����ʾ�ַ�
void CModiPwd::InitUI()
{
	//OperationGM operGM;

	SetWindowText(theApp.operGM.ReadValue("MGM","GM_UI_ModiPwd"));

	SetDlgItemText(IDC_STATNEWPWD,theApp.operGM.ReadValue("MGM","GM_UI_NewPwd"));
	SetDlgItemText(IDC_STATPWDAG,theApp.operGM.ReadValue("MGM","GM_UI_NewPwdAG"));
	SetDlgItemText(IDMODIPWD,theApp.operGM.ReadValue("MGM","GM_UI_ModiPwd"));
	SetDlgItemText(IDMPRESET,theApp.operGM.ReadValue("MGM","Reset"));
}

// �Զ��ı��С
void CModiPwd::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
}

//���ñ�����ɫ
HBRUSH CModiPwd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// �޸��������
void CModiPwd::OnBnClickedModipwd()
{
	try
	{
		CIni mIni;//��Ҫ���ڽ�CString���͵��ַ�ת��Ϊchar*���͵�
		//OperationGM operGM;	//�����࣬���ڶ�ȡ�����ļ�������Query�����츴ѡ���CListCtrl

		UpdateData(true);

		CString newPass; //������
		GetDlgItemText(IDC_EDITNEWPWD,newPass);	
		if(newPass=="") //�����벻��Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","MP_Warn_InputNPwd"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString newPassAG; //�ظ�������
		GetDlgItemText(IDC_EDITPWDAG,newPassAG);	
		if(newPassAG=="") //�ظ������벻��Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","MP_Warn_InputNPwdAG"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		if(newPassAG!=newPass) //����ǰ��Ҫ��ͬ
		{
			MessageBox(theApp.operGM.ReadValue("MGM","MP_Warn_PwdNotSame"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}		
		
		CSocketData socketdata;
		socketdata.InitCreate(1,4); //����������������������ID���û�����������
		char strInt[10];

		int userByID=theApp.UserByID; //������ID����¼ʱ�Ѿ�ȷ��
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//Ҫ����Ȩ�޵��û�ID

		CString m_username;
		m_username=theApp.userName; //�������û�������¼ʱ�Ѿ�ȷ��
		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(m_username),(unsigned char*)mIni.wcharToChar(m_username));

		socketdata.AddTFLV(CEnumCore::TagName::PassWord,CEnumCore::TagFormat::TLV_STRING,strlen(newPass),(unsigned char*)mIni.wcharToChar(newPass));

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_PASSWD_MODIF))//�����޸���������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}	
}

// ������Ϣ
void CModiPwd::OnBnClickedMpreset()
{	
	SetDlgItemText(IDC_EDITNEWPWD,"");
	SetDlgItemText(IDC_EDITPWDAG,"");
}

// �����޸����������Ϣ֮����н���
LRESULT CModiPwd::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ��ĳ���
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

	CIni mIni;
	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	//OperationGM operGM;
	
	CGlobalStruct::TFLV m_tflv=socketdata.getTLVByName(1,CEnumCore::TagName::MESSAGE);//������Ķ�ֻ����һ��MESSAGE��ָʾ������û�гɹ�
	CString result = (LPCTSTR)&m_tflv.lpdata;
	theApp.operGM.ShowResult(result);//��ʾ�������
	SetDlgItemText(IDC_EDITNEWPWD,"");
	SetDlgItemText(IDC_EDITPWDAG,"");

	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return true;
}

// �رնԻ���
void CModiPwd::OnClose()
{
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Close");//�رմ���
	DestroyWindow();
	CDialog::OnClose();
}
