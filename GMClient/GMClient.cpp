// GMClient.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "GMClient.h"
#include "MainFrm.h"

#include "GMClientDoc.h"
#include "GMClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <io.h>

// CGMClientApp

BEGIN_MESSAGE_MAP(CGMClientApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CGMClientApp ����

CGMClientApp::CGMClientApp():menuflag(false)
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CGMClientApp ����

CGMClientApp theApp;

// CGMClientApp ��ʼ��

BOOL CGMClientApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	//��ʼ��Socket
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// ���е�¼����
	CLogin pLogon;
	INT_PTR nRet=pLogon.DoModal();
	if(nRet==IDOK) //ʹ��IDOK��ťʱ����������ر�
	{
	}
	else
	{
		return false;
	}

	//�������е�dll
	LoadAllDll();

	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)
	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGMClientDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CGMClientView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	// �������ں�׺ʱ�ŵ��� DragAcceptFiles��
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand  ֮����
	return TRUE;
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CGMClientApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

//�������е�dll
void CGMClientApp::LoadAllDll(void)
{
	m_SelectDll = 0;
	//��̬����Ŀ¼��dll�ļ�,�ж��Ƿ������Ӧdll
	if(GetLocalDllFile("M_GM.dll"))
	{
	hinstDLL = LoadLibrary("M_GM.dll");
	if(hinstDLL!=NULL)
	{
		GM_OpenDialog = (GM_OPENDIALOG)GetProcAddress (hinstDLL,"GM_OPENDIALOG");
		GM_ShowDialog = (GM_SHOWDIALOG)GetProcAddress (hinstDLL,"GM_SHOWDIALOG");	//ѡ����ʾ��ͬ���ӶԻ���	
		GM_DialogMsg = (GM_DIALOGMSG)GetProcAddress (hinstDLL,"GM_DIALOGMSG");
		GM_Message = (GETFRAMEMESSAGE)GetProcAddress (hinstDLL,"GETFRAMEMESSAGE");
		GM_SendInfoAgain = (GM_SENDINFOAGAIN)GetProcAddress (hinstDLL,"GM_SENDINFOAGAIN");
		GM_Info = (GETINFO)GetProcAddress (hinstDLL,"GETINFO");
		GM_TranslateMessage = (GM_TRANSLATEMESSAGE)GetProcAddress(hinstDLL,"GM_TRANSLATEMESSAGE");
	}
	}
	//��̬����Ŀ¼��dll�ļ�,�ж��Ƿ������Ӧdll
   if(GetLocalDllFile("M_PAL.dll"))
   {
	hinstDLL = LoadLibrary("M_PAL.dll");
	if(hinstDLL!=NULL)
	{
		PAL_OpenDialog = (PAL_OPENDIALOG)GetProcAddress (hinstDLL,"PAL_OPENDIALOG");		
		PAL_ShowDialog = (PAL_SHOWDIALOG)GetProcAddress (hinstDLL,"PAL_SHOWDIALOG");	//ѡ����ʾ��ͬ���ӶԻ���	
		PAL_DialogMsg = (PAL_DIALOGMSG)GetProcAddress (hinstDLL,"PAL_DIALOGMSG");		
		PAL_TranslateMessage = (PAL_TRANSLATEMESSAGE)GetProcAddress(hinstDLL,"PAL_TRANSLATEMESSAGE");
		PAL_Message = (GETPALMESSAGE)GetProcAddress (hinstDLL,"GETPALMESSAGE");
		PAL_SendInfoAgagin = (PAL_SENDINFOAGAIN)GetProcAddress (hinstDLL,"PAL_SENDINFOAGAIN");
		PAL_Info = (GETPALINFO)GetProcAddress (hinstDLL,"GETPALINFO");		
	}
   }
	//maple add
   	//��̬����Ŀ¼��dll�ļ�,�ж��Ƿ������Ӧdll
   if(GetLocalDllFile("M_GTOWN.dll"))
   {
	hinstDLL = LoadLibrary("M_GTOWN.dll");
	if(hinstDLL!=NULL)
	{
		GTOWN_OpenDialog = (GTOWN_OPENDIALOG)GetProcAddress (hinstDLL,"GTOWN_OPENDIALOG");	
		GTOWN_ShowDialog = (GTOWN_SHOWDIALOG)GetProcAddress (hinstDLL,"GTOWN_SHOWDIALOG");	//ѡ����ʾ��ͬ���ӶԻ���	
		GTOWN_DialogMsg = (GTOWN_DIALOGMSG)GetProcAddress (hinstDLL,"GTOWN_DIALOGMSG");		
		GTOWN_TranslateMessage = (GTOWN_TRANSLATEMESSAGE)GetProcAddress(hinstDLL,"GTOWN_TRANSLATEMESSAGE");
		GTOWN_Message = (GETGTOWNMESSAGE)GetProcAddress (hinstDLL,"GETGTOWNMESSAGE");
		GTOWN_SendInfoAgagin = (GTOWN_SENDINFOAGAIN)GetProcAddress (hinstDLL,"GTOWN_SENDINFOAGAIN");
		GTOWN_Info = (GETGTOWNINFO)GetProcAddress (hinstDLL,"GETGTOWNINFO");	
	}
   }
   	//��̬����Ŀ¼��dll�ļ�,�ж��Ƿ������Ӧdll
   if(GetLocalDllFile("M_CG2.dll"))
   {
	hinstDLL=LoadLibrary("M_CG2.dll");
	if(hinstDLL!=NULL)
	{
		CG2_OpenDialog = (CG2_OPENDIALOG)GetProcAddress (hinstDLL,"CG2_OPENDIALOG");	
		CG2_ShowDialog = (CG2_SHOWDIALOG)GetProcAddress (hinstDLL,"CG2_SHOWDIALOG");	//ѡ����ʾ��ͬ���ӶԻ���	
		CG2_DialogMsg = (CG2_DIALOGMSG)GetProcAddress (hinstDLL,"CG2_DIALOGMSG");		
		CG2_TranslateMessage = (CG2_TRANSLATEMESSAGE)GetProcAddress(hinstDLL,"CG2_TRANSLATEMESSAGE");
		CG2_SendInfoAgagin = (CG2_SENDINFOAGAIN)GetProcAddress (hinstDLL,"CG2_SENDINFOAGAIN");
		CG2_Message = (GETCG2MESSAGE)GetProcAddress (hinstDLL,"GETCG2MESSAGE");
		CG2_Info = (GETCG2INFO)GetProcAddress (hinstDLL,"GETCG2INFO");
	}
   }
	//maple add
   	//��̬����Ŀ¼��dll�ļ�,�ж��Ƿ������Ӧdll
   if(GetLocalDllFile("M_SDO.dll"))
   {
	hinstDLL=LoadLibrary("M_SDO.dll");
	if(hinstDLL!=NULL)
	{
		SDO_OpenDialog = (SDO_OPENDIALOG)GetProcAddress (hinstDLL,"SDO_OPENDIALOG");	
		SDO_ShowDialog = (SDO_SHOWDIALOG)GetProcAddress (hinstDLL,"SDO_SHOWDIALOG");	//ѡ����ʾ��ͬ���ӶԻ���	
		SDO_DialogMsg = (SDO_DIALOGMSG)GetProcAddress (hinstDLL,"SDO_DIALOGMSG");		
		SDO_TranslateMessage = (SDO_TRANSLATEMESSAGE)GetProcAddress(hinstDLL,"SDO_TRANSLATEMESSAGE");
		SDO_Message = (GETSDOMESSAGE)GetProcAddress (hinstDLL,"GETSDOMESSAGE");
		SDO_SendInfoAgagin = (SDO_SENDINFOAGAIN)GetProcAddress (hinstDLL,"SDO_SENDINFOAGAIN");
		SDO_Info = (GETSDOINFO)GetProcAddress (hinstDLL,"GETSDOINFO");
	}
   }

	//maple add
   	//��̬����Ŀ¼��dll�ļ�,�ж��Ƿ������Ӧdll
   if(GetLocalDllFile("M_JW2.dll"))
   {
	hinstDLL=LoadLibrary("M_JW2.dll");
	if(hinstDLL!=NULL)
	{
		JW2_OpenDialog = (JW2_OPENDIALOG)GetProcAddress (hinstDLL,"JW2_OPENDIALOG");	
		JW2_ShowDialog = (JW2_SHOWDIALOG)GetProcAddress (hinstDLL,"JW2_SHOWDIALOG");	//ѡ����ʾ��ͬ���ӶԻ���	
		JW2_DialogMsg = (JW2_DIALOGMSG)GetProcAddress (hinstDLL,"JW2_DIALOGMSG");		
		JW2_TranslateMessage = (JW2_TRANSLATEMESSAGE)GetProcAddress(hinstDLL,"JW2_TRANSLATEMESSAGE");
		JW2_Message = (GETJW2MESSAGE)GetProcAddress (hinstDLL,"GETJW2MESSAGE");
		JW2_SendInfoAgagin = (JW2_SENDINFOAGAIN)GetProcAddress (hinstDLL,"JW2_SENDINFOAGAIN");
		JW2_Info = (GETJW2INFO)GetProcAddress (hinstDLL,"GETJW2INFO");
	}
   }
	//��̬����Ŀ¼��dll�ļ�,�ж��Ƿ������Ӧdll
   if(GetLocalDllFile("M_WA.dll"))
   {
	hinstDLL=LoadLibrary("M_WA.dll");
	if(hinstDLL!=NULL)
	{      
		WA_OpenDialog = (WA_OPENDIALOG)GetProcAddress (hinstDLL,"WA_OPENDIALOG");	
		WA_ShowDialog = (WA_SHOWDIALOG)GetProcAddress (hinstDLL,"WA_SHOWDIALOG");	//ѡ����ʾ��ͬ���ӶԻ���	
		WA_DialogMsg = (WA_DIALOGMSG)GetProcAddress (hinstDLL,"WA_DIALOGMSG");		
		WA_TranslateMessage = (WA_TRANSLATEMESSAGE)GetProcAddress(hinstDLL,"WA_TRANSLATEMESSAGE");
		WA_Message = (GETWAMESSAGE)GetProcAddress (hinstDLL,"GETWAMESSAGE");
		WA_SendInfoAgagin = (WA_SENDINFOAGAIN)GetProcAddress (hinstDLL,"WA_SENDINFOAGAIN");
		WA_Info = (GETWAINFO)GetProcAddress (hinstDLL,"GETWAINFO");
	}
   }

	// AGABUNB.
   	//��̬����Ŀ¼��dll�ļ�,�ж��Ƿ������Ӧdll
   if(GetLocalDllFile("AGABUNB.dll"))
   {
	HMODULE hinstDLL=LoadLibrary("AGABUNB.dll");
	if(hinstDLL != NULL)
	{
		m_pOpenCAGABUNBDlgFun = (POpenCAGABUNBDlg)GetProcAddress (hinstDLL,"OpenCAGABUNBDlg");
		m_pInitializeCAGABUNBFun = (PInitialize)GetProcAddress (hinstDLL,"Initialize");
		m_pSetRecvDataFun = (PSetRecvData)GetProcAddress (hinstDLL,"SetRecvData");
		m_pCloseDialogFun = (PCloseDialog)GetProcAddress (hinstDLL,"CloseDialog");
		m_pShowGABUNBDlgFun = (PShowGABUNBDlg)GetProcAddress (hinstDLL,"ShowGABUNBDlg");
	}
   }
   	//��̬����Ŀ¼��dll�ļ�,�ж��Ƿ������Ӧdll
   if(GetLocalDllFile("M_XD.dll"))
   {
	////peng begin �������
    hinstDLL=LoadLibrary("M_XD.dll");
	if(hinstDLL!=NULL)
	{
		XD_Info = (GETXDINFO)GetProcAddress (hinstDLL,"GETXDINFO");
		XD_OpenDialog=(XD_OPENDIALOG)GetProcAddress(hinstDLL,"XD_OPENDIALOG");
	    XD_DialogMsg = (XD_DIALOGMSG)GetProcAddress (hinstDLL,"XD_DIALOGMSG");
	    XD_ShowDialog = (XD_SHOWDIALOG)GetProcAddress (hinstDLL,"XD_SHOWDIALOG");
	    XD_Message = (GETXDMESSAGE)GetProcAddress (hinstDLL,"GETXDMESSAGE");	
		XD_TranslateMessage = (XD_TRANSLATEMESSAGE)GetProcAddress(hinstDLL,"XD_TRANSLATEMESSAGE");
		XD_SendInfoAgagin = (XD_SENDINFOAGAIN)GetProcAddress (hinstDLL,"XD_SENDINFOAGAIN");
	}
   }
	//////////////////////////////////////////////////////////////////////////peng end
}

void CGMClientApp::FreeAllDll(void)
{
	
	FreeLibrary(hinstDLL);
}

int CGMClientApp::ExitInstance()
{
	theApp.packethead.Destroy();
	theApp.m_clientsocket.Close();
	FreeAllDll();
	
	return CWinApp::ExitInstance();
}
//��̬�ж�dll,��ȡ���ص�dll�ļ��Ƿ����
bool CGMClientApp::GetLocalDllFile(char* dllname)
{
	char currentpath[200];
	char searchpath[200];
    GetCurrentDirectory(200,currentpath);
	sprintf(searchpath,"%s%s%s",currentpath,"\\",dllname);
    if(!access(searchpath,0))
	{
		return true;
	}
	else
	{
		return false;
	}
}
CString Ctabname::tabname="";