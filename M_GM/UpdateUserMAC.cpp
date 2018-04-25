// UpdateUserMAC.cpp : 实现文件
//

#include "stdafx.h"
#include "M_GM.h"
#include "UpdateUserMAC.h"
#include ".\updateusermac.h"


// CUpdateUserMAC 对话框

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

// 初始化对话框
BOOL CUpdateUserMAC::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// 初始化显示字符
	SetDlgItemText(IDC_EDITACCOUNT, userName);

	return TRUE;
}

// 初始化显示字符
void CUpdateUserMAC::InitUI()
{
	//OperationGM operGM;

	SetWindowText(theApp.operGM.ReadValue("MGM","UM_UI_UpdateUserMac"));

	SetDlgItemText(IDC_LBLACCOUNT,theApp.operGM.ReadValue("MGM","UM_UI_UserName"));
	SetDlgItemText(IDC_STATENDTIME,theApp.operGM.ReadValue("MGM","UM_UI_EndTime"));
	SetDlgItemText(IDOK,theApp.operGM.ReadValue("MGM","MakeSure"));
	SetDlgItemText(IDCANCEL,theApp.operGM.ReadValue("MGM","Cancel"));
}

// 初始化私有变量
void CUpdateUserMAC::initVar(CString uName,int uID)
{
	userName = uName;
	userID = uID;
}

//重置Mac码并更改使用时效
void CUpdateUserMAC::OnBnClickedOk()
{
	try
	{
		CIni mIni;//主要用于将CString类型的字符转换为char*类型的
		//OperationGM operGM;	//公共类，用于读取配置文件、发送Query、构造复选框和CListCtrl	

		CTime mTime;		
		dtcEndTime.GetTime(mTime);//获取设置的使用时效
		CTime curTime = CTime::GetCurrentTime();//获取系统当前时间
		if(mTime <= curTime)//使用时效不能小于当前时间
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_TimeLimit"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		CString strLimitTime = "";
		strLimitTime.Format("%i-%i-%i 00:00:00",mTime.GetYear(),mTime.GetMonth(),mTime.GetDay());//将使用时效格式化成CString类型
		
		CSocketData socketdata;
		socketdata.InitCreate(1,4); //共发送三个参数：操作者ID、用户ID、用户名、模块列表
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作者ID，登录时已经确定

		_itoa(userID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//要分配权限的用户ID

		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(userName),(unsigned char*)mIni.wcharToChar(userName));//要分配权限的用户名
		socketdata.AddTFLV(CEnumCore::TagName::Limit,CEnumCore::TagFormat::TLV_DATE,strlen(strLimitTime),(unsigned char *)mIni.wcharToChar(strLimitTime));//使用时效
		
		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::GMTOOLS_USERMAC_UPDATE))//发送重置MAC请求
		{
		    ::EnableWindow(this->GetParent()->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}
}

// 接收返回信息
LRESULT CUpdateUserMAC::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的长度
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Receive");//当前的状态为接收到了返回信息

	CIni mIni;
	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	//OperationGM operGM;
	
	CGlobalStruct::TFLV m_tflv=socketdata.getTLVByName(1,CEnumCore::TagName::MESSAGE);//操作类的都只返回一个MESSAGE，指示操作有没有成功
	CString result = (LPCTSTR)&m_tflv.lpdata;
	theApp.operGM.ShowResult(result);//显示操作结果

	::EnableWindow(this->GetParent()->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	OnCancel();

	return true;
}

//关闭对话框
void CUpdateUserMAC::OnBnClickedCancel()
{
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Close");//关闭窗体
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::EnableWindow(this->GetParent()->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	OnCancel();
}
