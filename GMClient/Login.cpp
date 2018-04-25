// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "GMClient.h"
#include "Login.h"
#include ".\login.h"
#include "ModuleUpdate.h"
#include "FileUpdate.h"

#include <iphlpapi.h>
#include <Iptypes.h>
#pragma comment(lib,"iphlpapi.lib")

// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialog)
CLogin::CLogin(CWnd* pParent /*=NULL*/)
: CDialog(CLogin::IDD, pParent)
{
}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICVIEW, m_PicView);
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_MESSAGE(UM_RECEIVE,OnLoginReceive)
	ON_MESSAGE(UM_CLOSE,OnLoginClose)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// 初始化对话框
BOOL CLogin::OnInitDialog()
{
	CDialog::OnInitDialog();
	//CBitmap bitmap;
	//bitmap.LoadBitmap(IDB_BITMAP3);
	//m_PicView.SetBitmap((HBITMAP)bitmap); //IDC_PICVIEW是图片框ID
    //bitmap.Detach();
	InitUI();
	m_connectflag = false;
	theApp.m_clientsocket.SetParentHwnd(this->m_hWnd);
	return TRUE;  // return TRUE unless you set the focus to a control
}

// 初始化显示字符
void CLogin::InitUI()
{
	CIni mIni;
	SetWindowText(mIni.ReadValue("Global","GMClient_UI_UserLogin"));
	SetDlgItemText(IDC_STATLOGINUSER,mIni.ReadValue("Global","GMClient_UI_LoginUser"));
	SetDlgItemText(IDC_STATLOGINPWD,mIni.ReadValue("Global","GMClient_UI_LoginPwd"));
	SetDlgItemText(IDOK,mIni.ReadValue("Global","GMClient_UI_Login"));
	SetDlgItemText(IDCANCEL,mIni.ReadValue("Global","Cancel"));
}

// 改变控件背景颜色
HBRUSH CLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	COLORREF backColor = RGB(255, 255, 255);
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);
	return CreateSolidBrush(backColor);
}

// 使用登录按钮
void CLogin::OnBnClickedOk()
{
	try
	{				
		CIni mIni;
		UpdateData(true);
		CString m_username;
		GetDlgItemText(IDC_EDITLOGINUSER,m_username);//用户名
		if(m_username=="")
		{
			MessageBox(mIni.ReadValue("Global","Login_UI_InputUser"),mIni.ReadValue("Global","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		theApp.userName = m_username;
		CString m_pwd;
		GetDlgItemText(IDC_EDITLOGINPWD,m_pwd);//密码
		if(m_pwd=="")
		{
			MessageBox(mIni.ReadValue("Global","Login_UI_InputPwd"),mIni.ReadValue("Global","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		char path[256];
		ZeroMemory(path,256);
		GetCurrentDirectory(256,path);
		char filepath[256];
		ZeroMemory(filepath,256);
		wsprintf(filepath,"%s%s",path,"\\Config\\Scheme.ini");//获取配置文件的地址
		char remoteip[20];
		int remotePort=GetPrivateProfileInt("SERVER","Port",0,filepath);//获取服务器端接口
		GetPrivateProfileString("SERVER","Address","127.0.0.1",remoteip,20,filepath);//获取服务器端IP地址
		if(!m_connectflag)
		{
			if(theApp.m_clientsocket.m_hSocket==INVALID_SOCKET)
			{
				theApp.m_clientsocket.Create();
			}
			if(theApp.m_clientsocket.Connect(remoteip,remotePort) == 0)//连接到服务器
			{
				m_connectflag=false;
			}
			else
			{
				m_connectflag=true;
			}
		}
		char* localip=this->GetIP();//获取本机IP地址
		CString localmac=this->GetMAC();//获取本机Mac码
		if(m_connectflag)
		{
		    //Cpackethead packethead;		
		    CSocketData socketdata;
			socketdata.InitCreate(1,4);//共有4个参数，用户名、密码、用户电脑IP、用户的MAC码
			int alllength=0;
			socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(m_username),(unsigned char*)mIni.wcharToChar(m_username));//用户名
			socketdata.AddTFLV(CEnumCore::TagName::PassWord,CEnumCore::TagFormat::TLV_STRING,strlen(m_pwd),(unsigned char*)mIni.wcharToChar(m_pwd));//密码
			socketdata.AddTFLV(CEnumCore::TagName::userIP,CEnumCore::TagFormat::TLV_STRING,strlen(localip),(unsigned char*)localip);//用户电脑IP
			socketdata.AddTFLV(CEnumCore::TagName::MAC,CEnumCore::TagFormat::TLV_STRING,strlen(localmac),(unsigned char*)mIni.wcharToChar(localmac));//用户的MAC码
			alllength = socketdata.EnBody();
			theApp.packethead.Create(alllength);
			theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::CONNECT,alllength);
			theApp.packethead.EnSendBuf(&alllength,(unsigned char *)socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
			theApp.packetLength = alllength;
			theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//发送连接服务器的请求
			theApp.m_SendCount = 0;//重复发送次数为0
			::EnableWindow(this->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			socketdata.Destroy();
		}
		else
		{
			MessageBox("CONNECT ERROR");
		}
	}
	catch(...)
	{
	}	
}

// 获取IP地址
char* CLogin::GetIP(void)
{
	hostent* thisHost;
	thisHost = gethostbyname("");
	char* ip = inet_ntoa (*(struct in_addr *)*thisHost->h_addr_list);
	return ip;
}

// 获取MAC码
CString CLogin::GetMAC(void)
{
	CString sMac;
	IP_ADAPTER_INFO myinfo;
	ULONG xx=sizeof(IP_ADAPTER_INFO);
	PULONG pxx=&xx;
	GetAdaptersInfo(&myinfo,pxx);
	unsigned char x=0x0d;
	unsigned char y=x+0x37;
	unsigned char mac[12];
	for(int i=0;i<6;i++)
	{
		if((myinfo.Address[i]>>4)>=0x0A)
		{
			mac[i*2]=(myinfo.Address[i]>>4)+0x37;
		}
		else
		{
			mac[i*2]=(myinfo.Address[i]>>4)+0x30;
		}
		if((myinfo.Address[i]&0x0F)>=0x0A)
		{
			mac[i*2+1]=(myinfo.Address[i]&0x0F)+0x37;
		}
		else
		{
			mac[i*2+1]=(myinfo.Address[i]&0x0F)+0x30;
		}
	}
	sMac.Format("%c%c:%c%c:%c%c:%c%c:%c%c:%c%c",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5],mac[6],mac[7],mac[8],mac[9],mac[10],mac[11]);
	return sMac;
}

// 发送登录信息之后进行接收
LRESULT CLogin::OnLoginReceive(WPARAM wParam, LPARAM lParam)
{	
	CIni mIni;
	CFileUpdate fUpdate;
	CMSocket selfSocket;
	CPacketHead m_PacketHead;
	CSocketData socketdata;
	char strInt[10];
	ZeroMemory(strInt,10);
	int actlength=0;
	int alllength=0;
	selfSocket.SetSocket(theApp.m_clientsocket.m_hSocket);
	actlength=selfSocket.MyReceive();//接收返回信息
	if(actlength == -1)
	{
		::EnableWindow(this->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		//MessageBox(mIni.ReadValue("GLOBAL","/MAIN_ERROR_RECVDATAERROR"),mIni.ReadValue("GLOBAL","ERROR"),MB_OK);
		return false;
	}
	m_PacketHead.Create(actlength);
	if(m_PacketHead.DeHead((unsigned char *)selfSocket.recvBuffer(),actlength))
	{
		socketdata.Create(m_PacketHead.m_packethead.bodylen/8);
		if(!socketdata.DeBody(m_PacketHead.getDataBuf()+18,m_PacketHead.m_packethead.bodylen))
		{
			if(theApp.m_SendCount<5)//重复发送次数小于5次
			{
				theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),theApp.packetLength);//发送原来的请求
				theApp.m_SendCount++;
				socketdata.Destroy();
				return false;
			}
			else//重复发送次数超过5次
			{
				::EnableWindow(this->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
				::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
				MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),MB_OK);//数据解析异常
				socketdata.Destroy();
				return false;
			}
		}
		theApp.m_SendCount = 0;//重复发送次数为0
		try
		{		
			switch((unsigned int)m_PacketHead.GetMessageID())
			{
			case CEnumCore::Message_Tag_ID::CONNECT_RESP:
				{
					CGlobalStruct::TFLV m_tflv;
					m_tflv = socketdata.getTLV(1,1);
					if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)
					{
						::EnableWindow(this->m_hWnd,true);
						MessageBox((LPCSTR)&m_tflv.lpdata,mIni.ReadValue("Global","Error"),0);
						m_connectflag=false;
						theApp.m_clientsocket.Close();
						return false;
					}

					m_tflv=socketdata.getTLVByTag(CEnumCore::TagName::UserName,0);//获取用户名
					theApp.userName = (LPCTSTR)&m_tflv.lpdata;
					m_tflv=socketdata.getTLVByTag(CEnumCore::TagName::UserByID,0);//获取用户ID
					theApp.UserByID = atoi(mIni.wcharToChar((LPCTSTR)&m_tflv.lpdata));
					//peng 升级标识 
					//bool toUpdate = false;//true:需要升级,false:不需要升级
					bool toUpdate = true;//true:需要升级,false:不需要升级
					if(toUpdate)
					{
						char path[256];
						SecureZeroMemory(path,256);
						GetCurrentDirectory(256,path);
						char filepath[256];
						SecureZeroMemory(filepath,256);
						wsprintf(filepath,"%s%s",path,"\\");//获取配置文件的地址
						CString dllFileInfo = fUpdate.GetLocalDllFile(filepath);
						CString exeFileInfo = fUpdate.GetLocalExeFile(filepath);
						socketdata.InitCreate(1,2);//共有2个参数，dll文件信息、exe文件信息
						int alllength=0;
						socketdata.AddTFLV(CEnumCore::TagName::UpdateFileName,CEnumCore::TagFormat::TLV_STRING,strlen(dllFileInfo),(unsigned char*)mIni.wcharToChar(dllFileInfo));//dll版本信息
						socketdata.AddTFLV(CEnumCore::TagName::UpdateFilePath,CEnumCore::TagFormat::TLV_STRING,strlen(exeFileInfo),(unsigned char*)mIni.wcharToChar(exeFileInfo));//exe版本信息
						alllength=socketdata.EnBody();

						theApp.packethead.Create(alllength);
						theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::CLIENT_PATCH_COMPARE,alllength);
						theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
						theApp.packetLength = alllength;
						theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//发送查询用户模块升级信息的请求
						theApp.m_SendCount = 0;//重复发送次数为0

						::EnableWindow(this->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
						::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);

						socketdata.Destroy();
					}
					else
					{
						socketdata.InitCreate(1,1);//共有1个参数，操作员ID

						_itoa(theApp.UserByID,strInt,10);
						socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

						alllength=socketdata.EnBody();

						theApp.packethead.Create(alllength);

						theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::USER_MODULE_ADMIN,CEnumCore::ServiceKey::USER_MODULE_QUERY,alllength);

						theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
						theApp.packetLength = alllength;
						theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//发送查询用户模块信息的请求
						theApp.m_SendCount = 0;//重复发送次数为0

						socketdata.Destroy();
						OnOK();
					}
				}
				break;
			case CEnumCore::Message_Tag_ID::CLIENT_PATCH_COMPARE_RESP:
				{
					CGlobalStruct::TFLV m_tflv;
					m_tflv = socketdata.getTLV(1,1);
					if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)//如果不需要升级
					{
						socketdata.InitCreate(1,1);//共有1个参数，操作员ID

						_itoa(theApp.UserByID,strInt,10);
						socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

						alllength=socketdata.EnBody();

						theApp.packethead.Create(alllength);

						theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::USER_MODULE_ADMIN,CEnumCore::ServiceKey::USER_MODULE_QUERY,alllength);

						theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
						theApp.packetLength = alllength;
						theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//发送查询用户模块信息的请求
						theApp.m_SendCount = 0;//重复发送次数为0

						socketdata.Destroy();
						OnOK();
					}
					else
					{
						CModuleUpdate mUpdate;
						ShowWindow(SW_HIDE);
						
						INT_PTR iRet = mUpdate.DoModal();
						
						if(iRet == IDOK) //使用IDOK按钮时继续，否则关闭
						{
							char path[256];
							ZeroMemory(path,256);
							GetCurrentDirectory(256,path);
							char filepath[256];
							wsprintf(filepath,"%s%s",path,"\\Run.exe");//获取Run.exe的地址
							ShellExecute(NULL,"open", filepath, NULL, NULL, SW_SHOW);
							OnCancel();
						}
						else
						{
							OnCancel();
						}									
					}
					
				}
				break;
			default:
				::EnableWindow(this->m_hWnd,true);
				break;
			}		
		}
		catch(...)
		{
		}
	}
	else
	{
		if(theApp.m_SendCount<5)//如果重复发送次数小于5次
		{
			theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),theApp.packetLength);//发送原来的请求
			theApp.m_SendCount++;//重复发送次数加1
		}
		else
		{
			::EnableWindow(this->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
			::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),MB_OK);//数据解析异常
			return false;
		}		
	}
	return false;
}

// 关闭的时候进行的操作
LRESULT CLogin::OnLoginClose(WPARAM wParam, LPARAM lParam)
{
	theApp.m_clientsocket.Close();
	theApp.packethead.Destroy();
	return false;
}

// 使用关闭按钮
void CLogin::OnBnClickedCancel()
{
	OnCancel();
}
