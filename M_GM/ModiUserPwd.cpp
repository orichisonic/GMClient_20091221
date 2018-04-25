// ModiUserPwd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_GM.h"
#include "ModiUserPwd.h"
#include ".\modiuserpwd.h"


// CModiUserPwd �Ի���

IMPLEMENT_DYNAMIC(CModiUserPwd, CDialog)
CModiUserPwd::CModiUserPwd(CWnd* pParent /*=NULL*/)
	: CDialog(CModiUserPwd::IDD, pParent)
{
}

CModiUserPwd::~CModiUserPwd()
{
}

void CModiUserPwd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModiUserPwd, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
END_MESSAGE_MAP()


// ��ʼ���Ի���
BOOL CModiUserPwd::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// ��ʼ����ʾ�ַ�
	SetDlgItemText(IDC_EDITACCOUNT, userName);

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CModiUserPwd::InitUI()
{
	//OperationGM operGM;

	SetWindowText(theApp.operGM.ReadValue("MGM","GM_UI_ModiPwd"));

	SetDlgItemText(IDC_LBLACCOUNT,theApp.operGM.ReadValue("MGM","UM_UI_UserName"));
	SetDlgItemText(IDC_LBLPWD,theApp.operGM.ReadValue("MGM","GM_UI_NewPwd"));
	SetDlgItemText(IDC_LBLREPWD,theApp.operGM.ReadValue("MGM","GM_UI_NewPwdAG"));
	SetDlgItemText(IDOK,theApp.operGM.ReadValue("MGM","MakeSure"));
	SetDlgItemText(IDCANCEL,theApp.operGM.ReadValue("MGM","Cancel"));
}

// ��ʼ��˽�б���
void CModiUserPwd::initVar(CString uName,int uID)
{
	userName = uName;
	userID = uID;
}

//�޸��û�����
void CModiUserPwd::OnBnClickedOk()
{
	try
	{
		CIni mIni;//��Ҫ���ڽ�CString���͵��ַ�ת��Ϊchar*���͵�
		//OperationGM operGM;	//�����࣬���ڶ�ȡ�����ļ�������Query�����츴ѡ���CListCtrl	

		CString newPass; //������
		GetDlgItemText(IDC_EDITPWD,newPass);	
		if(newPass=="") //�����벻��Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","MP_Warn_InputNPwd"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString newPassAG; //�ظ�������
		GetDlgItemText(IDC_EDITREPWD,newPassAG);	
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
		socketdata.InitCreate(1,4); //����������������������ID���û�ID���û�����ģ���б�
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//������ID����¼ʱ�Ѿ�ȷ��

		_itoa(userID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//Ҫ����Ȩ�޵��û�ID

		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(userName),(unsigned char*)mIni.wcharToChar(userName));//Ҫ����Ȩ�޵��û���
		socketdata.AddTFLV(CEnumCore::TagName::PassWord,CEnumCore::TagFormat::TLV_STRING,strlen(newPass),(unsigned char*)mIni.wcharToChar(newPass));

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_PASSWD_MODIF))//�����޸���������
		{
			::EnableWindow(this->GetParent()->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}
}

// ���շ�����Ϣ
LRESULT CModiUserPwd::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	
	CGlobalStruct::TFLV m_tflv=socketdata.getTLVByName(1,CEnumCore::TagName::MESSAGE);//������Ķ�ֻ����һ��MESSAGE��ָʾ������û�гɹ�
	CString result = (LPCTSTR)&m_tflv.lpdata;
	theApp.operGM.ShowResult(result);//��ʾ�������
	SetDlgItemText(IDC_EDITNEWPWD,"");
	SetDlgItemText(IDC_EDITPWDAG,"");

	::EnableWindow(this->GetParent()->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	OnCancel();

	return true;
}

//�رնԻ���
void CModiUserPwd::OnBnClickedCancel()
{
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Close");//�رմ���
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::EnableWindow(this->GetParent()->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	OnCancel();
}