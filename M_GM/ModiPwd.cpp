#include ".\modipwd.h"
// ModiPwd.cpp : 实现文件
//

#include "stdafx.h"
#include "M_GM.h"
#include "ModiPwd.h"


// CModiPwd 对话框

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


// 初始化对话框
BOOL CModiPwd::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();//初始化显示字符

	return TRUE;  // return TRUE unless you set the focus to a control
}

// 初始化显示字符
void CModiPwd::InitUI()
{
	//OperationGM operGM;

	SetWindowText(theApp.operGM.ReadValue("MGM","GM_UI_ModiPwd"));

	SetDlgItemText(IDC_STATNEWPWD,theApp.operGM.ReadValue("MGM","GM_UI_NewPwd"));
	SetDlgItemText(IDC_STATPWDAG,theApp.operGM.ReadValue("MGM","GM_UI_NewPwdAG"));
	SetDlgItemText(IDMODIPWD,theApp.operGM.ReadValue("MGM","GM_UI_ModiPwd"));
	SetDlgItemText(IDMPRESET,theApp.operGM.ReadValue("MGM","Reset"));
}

// 自动改变大小
void CModiPwd::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
}

//设置背景颜色
HBRUSH CModiPwd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 修改玩家密码
void CModiPwd::OnBnClickedModipwd()
{
	try
	{
		CIni mIni;//主要用于将CString类型的字符转换为char*类型的
		//OperationGM operGM;	//公共类，用于读取配置文件、发送Query、构造复选框和CListCtrl

		UpdateData(true);

		CString newPass; //新密码
		GetDlgItemText(IDC_EDITNEWPWD,newPass);	
		if(newPass=="") //新密码不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","MP_Warn_InputNPwd"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString newPassAG; //重复新密码
		GetDlgItemText(IDC_EDITPWDAG,newPassAG);	
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
		socketdata.InitCreate(1,4); //共发送三个参数：操作者ID、用户名、新密码
		char strInt[10];

		int userByID=theApp.UserByID; //操作者ID，登录时已经确定
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//要分配权限的用户ID

		CString m_username;
		m_username=theApp.userName; //操作者用户名，登录时已经确定
		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(m_username),(unsigned char*)mIni.wcharToChar(m_username));

		socketdata.AddTFLV(CEnumCore::TagName::PassWord,CEnumCore::TagFormat::TLV_STRING,strlen(newPass),(unsigned char*)mIni.wcharToChar(newPass));

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_PASSWD_MODIF))//发送修改密码请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}	
}

// 重置信息
void CModiPwd::OnBnClickedMpreset()
{	
	SetDlgItemText(IDC_EDITNEWPWD,"");
	SetDlgItemText(IDC_EDITPWDAG,"");
}

// 发送修改玩家密码信息之后进行接收
LRESULT CModiPwd::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	SetDlgItemText(IDC_EDITNEWPWD,"");
	SetDlgItemText(IDC_EDITPWDAG,"");

	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return true;
}

// 关闭对话框
void CModiPwd::OnClose()
{
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Close");//关闭窗体
	DestroyWindow();
	CDialog::OnClose();
}
