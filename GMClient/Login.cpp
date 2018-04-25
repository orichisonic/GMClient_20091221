// Login.cpp : ʵ���ļ�
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

// CLogin �Ի���

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

// ��ʼ���Ի���
BOOL CLogin::OnInitDialog()
{
	CDialog::OnInitDialog();
	//CBitmap bitmap;
	//bitmap.LoadBitmap(IDB_BITMAP3);
	//m_PicView.SetBitmap((HBITMAP)bitmap); //IDC_PICVIEW��ͼƬ��ID
    //bitmap.Detach();
	InitUI();
	m_connectflag = false;
	theApp.m_clientsocket.SetParentHwnd(this->m_hWnd);
	return TRUE;  // return TRUE unless you set the focus to a control
}

// ��ʼ����ʾ�ַ�
void CLogin::InitUI()
{
	CIni mIni;
	SetWindowText(mIni.ReadValue("Global","GMClient_UI_UserLogin"));
	SetDlgItemText(IDC_STATLOGINUSER,mIni.ReadValue("Global","GMClient_UI_LoginUser"));
	SetDlgItemText(IDC_STATLOGINPWD,mIni.ReadValue("Global","GMClient_UI_LoginPwd"));
	SetDlgItemText(IDOK,mIni.ReadValue("Global","GMClient_UI_Login"));
	SetDlgItemText(IDCANCEL,mIni.ReadValue("Global","Cancel"));
}

// �ı�ؼ�������ɫ
HBRUSH CLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	COLORREF backColor = RGB(255, 255, 255);
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);
	return CreateSolidBrush(backColor);
}

// ʹ�õ�¼��ť
void CLogin::OnBnClickedOk()
{
	try
	{				
		CIni mIni;
		UpdateData(true);
		CString m_username;
		GetDlgItemText(IDC_EDITLOGINUSER,m_username);//�û���
		if(m_username=="")
		{
			MessageBox(mIni.ReadValue("Global","Login_UI_InputUser"),mIni.ReadValue("Global","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		theApp.userName = m_username;
		CString m_pwd;
		GetDlgItemText(IDC_EDITLOGINPWD,m_pwd);//����
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
		wsprintf(filepath,"%s%s",path,"\\Config\\Scheme.ini");//��ȡ�����ļ��ĵ�ַ
		char remoteip[20];
		int remotePort=GetPrivateProfileInt("SERVER","Port",0,filepath);//��ȡ�������˽ӿ�
		GetPrivateProfileString("SERVER","Address","127.0.0.1",remoteip,20,filepath);//��ȡ��������IP��ַ
		if(!m_connectflag)
		{
			if(theApp.m_clientsocket.m_hSocket==INVALID_SOCKET)
			{
				theApp.m_clientsocket.Create();
			}
			if(theApp.m_clientsocket.Connect(remoteip,remotePort) == 0)//���ӵ�������
			{
				m_connectflag=false;
			}
			else
			{
				m_connectflag=true;
			}
		}
		char* localip=this->GetIP();//��ȡ����IP��ַ
		CString localmac=this->GetMAC();//��ȡ����Mac��
		if(m_connectflag)
		{
		    //Cpackethead packethead;		
		    CSocketData socketdata;
			socketdata.InitCreate(1,4);//����4���������û��������롢�û�����IP���û���MAC��
			int alllength=0;
			socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(m_username),(unsigned char*)mIni.wcharToChar(m_username));//�û���
			socketdata.AddTFLV(CEnumCore::TagName::PassWord,CEnumCore::TagFormat::TLV_STRING,strlen(m_pwd),(unsigned char*)mIni.wcharToChar(m_pwd));//����
			socketdata.AddTFLV(CEnumCore::TagName::userIP,CEnumCore::TagFormat::TLV_STRING,strlen(localip),(unsigned char*)localip);//�û�����IP
			socketdata.AddTFLV(CEnumCore::TagName::MAC,CEnumCore::TagFormat::TLV_STRING,strlen(localmac),(unsigned char*)mIni.wcharToChar(localmac));//�û���MAC��
			alllength = socketdata.EnBody();
			theApp.packethead.Create(alllength);
			theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::CONNECT,alllength);
			theApp.packethead.EnSendBuf(&alllength,(unsigned char *)socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
			theApp.packetLength = alllength;
			theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//�������ӷ�����������
			theApp.m_SendCount = 0;//�ظ����ʹ���Ϊ0
			::EnableWindow(this->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
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

// ��ȡIP��ַ
char* CLogin::GetIP(void)
{
	hostent* thisHost;
	thisHost = gethostbyname("");
	char* ip = inet_ntoa (*(struct in_addr *)*thisHost->h_addr_list);
	return ip;
}

// ��ȡMAC��
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

// ���͵�¼��Ϣ֮����н���
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
	actlength=selfSocket.MyReceive();//���շ�����Ϣ
	if(actlength == -1)
	{
		::EnableWindow(this->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
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
			if(theApp.m_SendCount<5)//�ظ����ʹ���С��5��
			{
				theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),theApp.packetLength);//����ԭ��������
				theApp.m_SendCount++;
				socketdata.Destroy();
				return false;
			}
			else//�ظ����ʹ�������5��
			{
				::EnableWindow(this->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
				::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
				MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),MB_OK);//���ݽ����쳣
				socketdata.Destroy();
				return false;
			}
		}
		theApp.m_SendCount = 0;//�ظ����ʹ���Ϊ0
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

					m_tflv=socketdata.getTLVByTag(CEnumCore::TagName::UserName,0);//��ȡ�û���
					theApp.userName = (LPCTSTR)&m_tflv.lpdata;
					m_tflv=socketdata.getTLVByTag(CEnumCore::TagName::UserByID,0);//��ȡ�û�ID
					theApp.UserByID = atoi(mIni.wcharToChar((LPCTSTR)&m_tflv.lpdata));
					//peng ������ʶ 
					//bool toUpdate = false;//true:��Ҫ����,false:����Ҫ����
					bool toUpdate = true;//true:��Ҫ����,false:����Ҫ����
					if(toUpdate)
					{
						char path[256];
						SecureZeroMemory(path,256);
						GetCurrentDirectory(256,path);
						char filepath[256];
						SecureZeroMemory(filepath,256);
						wsprintf(filepath,"%s%s",path,"\\");//��ȡ�����ļ��ĵ�ַ
						CString dllFileInfo = fUpdate.GetLocalDllFile(filepath);
						CString exeFileInfo = fUpdate.GetLocalExeFile(filepath);
						socketdata.InitCreate(1,2);//����2��������dll�ļ���Ϣ��exe�ļ���Ϣ
						int alllength=0;
						socketdata.AddTFLV(CEnumCore::TagName::UpdateFileName,CEnumCore::TagFormat::TLV_STRING,strlen(dllFileInfo),(unsigned char*)mIni.wcharToChar(dllFileInfo));//dll�汾��Ϣ
						socketdata.AddTFLV(CEnumCore::TagName::UpdateFilePath,CEnumCore::TagFormat::TLV_STRING,strlen(exeFileInfo),(unsigned char*)mIni.wcharToChar(exeFileInfo));//exe�汾��Ϣ
						alllength=socketdata.EnBody();

						theApp.packethead.Create(alllength);
						theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::CLIENT_PATCH_COMPARE,alllength);
						theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
						theApp.packetLength = alllength;
						theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//���Ͳ�ѯ�û�ģ��������Ϣ������
						theApp.m_SendCount = 0;//�ظ����ʹ���Ϊ0

						::EnableWindow(this->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);

						socketdata.Destroy();
					}
					else
					{
						socketdata.InitCreate(1,1);//����1������������ԱID

						_itoa(theApp.UserByID,strInt,10);
						socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

						alllength=socketdata.EnBody();

						theApp.packethead.Create(alllength);

						theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::USER_MODULE_ADMIN,CEnumCore::ServiceKey::USER_MODULE_QUERY,alllength);

						theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
						theApp.packetLength = alllength;
						theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//���Ͳ�ѯ�û�ģ����Ϣ������
						theApp.m_SendCount = 0;//�ظ����ʹ���Ϊ0

						socketdata.Destroy();
						OnOK();
					}
				}
				break;
			case CEnumCore::Message_Tag_ID::CLIENT_PATCH_COMPARE_RESP:
				{
					CGlobalStruct::TFLV m_tflv;
					m_tflv = socketdata.getTLV(1,1);
					if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)//�������Ҫ����
					{
						socketdata.InitCreate(1,1);//����1������������ԱID

						_itoa(theApp.UserByID,strInt,10);
						socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

						alllength=socketdata.EnBody();

						theApp.packethead.Create(alllength);

						theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::USER_MODULE_ADMIN,CEnumCore::ServiceKey::USER_MODULE_QUERY,alllength);

						theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
						theApp.packetLength = alllength;
						theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//���Ͳ�ѯ�û�ģ����Ϣ������
						theApp.m_SendCount = 0;//�ظ����ʹ���Ϊ0

						socketdata.Destroy();
						OnOK();
					}
					else
					{
						CModuleUpdate mUpdate;
						ShowWindow(SW_HIDE);
						
						INT_PTR iRet = mUpdate.DoModal();
						
						if(iRet == IDOK) //ʹ��IDOK��ťʱ����������ر�
						{
							char path[256];
							ZeroMemory(path,256);
							GetCurrentDirectory(256,path);
							char filepath[256];
							wsprintf(filepath,"%s%s",path,"\\Run.exe");//��ȡRun.exe�ĵ�ַ
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
		if(theApp.m_SendCount<5)//����ظ����ʹ���С��5��
		{
			theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),theApp.packetLength);//����ԭ��������
			theApp.m_SendCount++;//�ظ����ʹ�����1
		}
		else
		{
			::EnableWindow(this->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
			::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),MB_OK);//���ݽ����쳣
			return false;
		}		
	}
	return false;
}

// �رյ�ʱ����еĲ���
LRESULT CLogin::OnLoginClose(WPARAM wParam, LPARAM lParam)
{
	theApp.m_clientsocket.Close();
	theApp.packethead.Destroy();
	return false;
}

// ʹ�ùرհ�ť
void CLogin::OnBnClickedCancel()
{
	OnCancel();
}
