// ModiUserPwd.cpp : 实现文件
//

#include "stdafx.h"
#include "M_GM.h"
#include "ModiUserPwd.h"
#include ".\modiuserpwd.h"


// CModiUserPwd 对话框

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


// 初始化对话框
BOOL CModiUserPwd::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// 初始化显示字符
	SetDlgItemText(IDC_EDITACCOUNT, userName);

	return TRUE;
}

// 初始化显示字符
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

// 初始化私有变量
void CModiUserPwd::initVar(CString uName,int uID)
{
	userName = uName;
	userID = uID;
}

//修改用户密码
void CModiUserPwd::OnBnClickedOk()
{
	try
	{
		CIni mIni;//主要用于将CString类型的字符转换为char*类型的
		//OperationGM operGM;	//公共类，用于读取配置文件、发送Query、构造复选框和CListCtrl	

		CString newPass; //新密码
		GetDlgItemText(IDC_EDITPWD,newPass);	
		if(newPass=="") //新密码不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","MP_Warn_InputNPwd"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString newPassAG; //重复新密码
		GetDlgItemText(IDC_EDITREPWD,newPassAG);	
		if(newPassAG=="") //重复新密码不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","MP_Warn_InputNPwdAG"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		if(newPassAG!=newPass) //密码前后要相同
		{
			MessageBox(theApp.operGM.ReadValue("MGM","MP_Warn_PwdNotSame"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		
		CSocketData socketdata;
		socketdata.InitCreate(1,4); //共发送三个参数：操作者ID、用户ID、用户名、模块列表
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作者ID，登录时已经确定

		_itoa(userID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//要分配权限的用户ID

		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(userName),(unsigned char*)mIni.wcharToChar(userName));//要分配权限的用户名
		socketdata.AddTFLV(CEnumCore::TagName::PassWord,CEnumCore::TagFormat::TLV_STRING,strlen(newPass),(unsigned char*)mIni.wcharToChar(newPass));

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_PASSWD_MODIF))//发送修改密码请求
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
LRESULT CModiUserPwd::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	
	CGlobalStruct::TFLV m_tflv=socketdata.getTLVByName(1,CEnumCore::TagName::MESSAGE);//操作类的都只返回一个MESSAGE，指示操作有没有成功
	CString result = (LPCTSTR)&m_tflv.lpdata;
	theApp.operGM.ShowResult(result);//显示操作结果
	SetDlgItemText(IDC_EDITNEWPWD,"");
	SetDlgItemText(IDC_EDITPWDAG,"");

	::EnableWindow(this->GetParent()->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	OnCancel();

	return true;
}

//关闭对话框
void CModiUserPwd::OnBnClickedCancel()
{
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Close");//关闭窗体
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::EnableWindow(this->GetParent()->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	OnCancel();
}