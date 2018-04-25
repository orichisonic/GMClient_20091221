// UpdateUserMAC.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_GM.h"
#include "UpdateUserMAC.h"
#include ".\updateusermac.h"


// CUpdateUserMAC �Ի���

IMPLEMENT_DYNAMIC(CUpdateUserMAC, CDialog)
CUpdateUserMAC::CUpdateUserMAC(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateUserMAC::IDD, pParent)
{
}

CUpdateUserMAC::~CUpdateUserMAC()
{
}

void CUpdateUserMAC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DTPENDTIME, dtcEndTime);
}


BEGIN_MESSAGE_MAP(CUpdateUserMAC, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
END_MESSAGE_MAP()

// ��ʼ���Ի���
BOOL CUpdateUserMAC::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// ��ʼ����ʾ�ַ�
	SetDlgItemText(IDC_EDITACCOUNT, userName);

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CUpdateUserMAC::InitUI()
{
	//OperationGM operGM;

	SetWindowText(theApp.operGM.ReadValue("MGM","UM_UI_UpdateUserMac"));

	SetDlgItemText(IDC_LBLACCOUNT,theApp.operGM.ReadValue("MGM","UM_UI_UserName"));
	SetDlgItemText(IDC_STATENDTIME,theApp.operGM.ReadValue("MGM","UM_UI_EndTime"));
	SetDlgItemText(IDOK,theApp.operGM.ReadValue("MGM","MakeSure"));
	SetDlgItemText(IDCANCEL,theApp.operGM.ReadValue("MGM","Cancel"));
}

// ��ʼ��˽�б���
void CUpdateUserMAC::initVar(CString uName,int uID)
{
	userName = uName;
	userID = uID;
}

//����Mac�벢����ʹ��ʱЧ
void CUpdateUserMAC::OnBnClickedOk()
{
	try
	{
		CIni mIni;//��Ҫ���ڽ�CString���͵��ַ�ת��Ϊchar*���͵�
		//OperationGM operGM;	//�����࣬���ڶ�ȡ�����ļ�������Query�����츴ѡ���CListCtrl	

		CTime mTime;		
		dtcEndTime.GetTime(mTime);//��ȡ���õ�ʹ��ʱЧ
		CTime curTime = CTime::GetCurrentTime();//��ȡϵͳ��ǰʱ��
		if(mTime <= curTime)//ʹ��ʱЧ����С�ڵ�ǰʱ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_TimeLimit"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		CString strLimitTime = "";
		strLimitTime.Format("%i-%i-%i 00:00:00",mTime.GetYear(),mTime.GetMonth(),mTime.GetDay());//��ʹ��ʱЧ��ʽ����CString����
		
		CSocketData socketdata;
		socketdata.InitCreate(1,4); //����������������������ID���û�ID���û�����ģ���б�
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//������ID����¼ʱ�Ѿ�ȷ��

		_itoa(userID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//Ҫ����Ȩ�޵��û�ID

		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(userName),(unsigned char*)mIni.wcharToChar(userName));//Ҫ����Ȩ�޵��û���
		socketdata.AddTFLV(CEnumCore::TagName::Limit,CEnumCore::TagFormat::TLV_DATE,strlen(strLimitTime),(unsigned char *)mIni.wcharToChar(strLimitTime));//ʹ��ʱЧ
		
		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::GMTOOLS_USERMAC_UPDATE))//��������MAC����
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
LRESULT CUpdateUserMAC::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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

	::EnableWindow(this->GetParent()->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	OnCancel();

	return true;
}

//�رնԻ���
void CUpdateUserMAC::OnBnClickedCancel()
{
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Close");//�رմ���
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::EnableWindow(this->GetParent()->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	OnCancel();
}
