// GMClient.cpp : 定义应用程序的类行为。
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
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CGMClientApp 构造

CGMClientApp::CGMClientApp():menuflag(false)
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CGMClientApp 对象

CGMClientApp theApp;

// CGMClientApp 初始化

BOOL CGMClientApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();

	CWinApp::InitInstance();

	//初始化Socket
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// 运行登录程序
	CLogin pLogon;
	INT_PTR nRet=pLogon.DoModal();
	if(nRet==IDOK) //使用IDOK按钮时继续，否则关闭
	{
	}
	else
	{
		return false;
	}

	//加载所有的dll
	LoadAllDll();

	AfxEnableControlContainer();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)
	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGMClientDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CGMClientView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	// 仅当存在后缀时才调用 DragAcceptFiles，
	//  在 SDI 应用程序中，这应在 ProcessShellCommand  之后发生
	return TRUE;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

// 用于运行对话框的应用程序命令
void CGMClientApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

//加载所有的dll
void CGMClientApp::LoadAllDll(void)
{
	m_SelectDll = 0;
	//动态查找目录下dll文件,判断是否加载相应dll
	if(GetLocalDllFile("M_GM.dll"))
	{
	hinstDLL = LoadLibrary("M_GM.dll");
	if(hinstDLL!=NULL)
	{
		GM_OpenDialog = (GM_OPENDIALOG)GetProcAddress (hinstDLL,"GM_OPENDIALOG");
		GM_ShowDialog = (GM_SHOWDIALOG)GetProcAddress (hinstDLL,"GM_SHOWDIALOG");	//选择显示不同的子对话框	
		GM_DialogMsg = (GM_DIALOGMSG)GetProcAddress (hinstDLL,"GM_DIALOGMSG");
		GM_Message = (GETFRAMEMESSAGE)GetProcAddress (hinstDLL,"GETFRAMEMESSAGE");
		GM_SendInfoAgain = (GM_SENDINFOAGAIN)GetProcAddress (hinstDLL,"GM_SENDINFOAGAIN");
		GM_Info = (GETINFO)GetProcAddress (hinstDLL,"GETINFO");
		GM_TranslateMessage = (GM_TRANSLATEMESSAGE)GetProcAddress(hinstDLL,"GM_TRANSLATEMESSAGE");
	}
	}
	//动态查找目录下dll文件,判断是否加载相应dll
   if(GetLocalDllFile("M_PAL.dll"))
   {
	hinstDLL = LoadLibrary("M_PAL.dll");
	if(hinstDLL!=NULL)
	{
		PAL_OpenDialog = (PAL_OPENDIALOG)GetProcAddress (hinstDLL,"PAL_OPENDIALOG");		
		PAL_ShowDialog = (PAL_SHOWDIALOG)GetProcAddress (hinstDLL,"PAL_SHOWDIALOG");	//选择显示不同的子对话框	
		PAL_DialogMsg = (PAL_DIALOGMSG)GetProcAddress (hinstDLL,"PAL_DIALOGMSG");		
		PAL_TranslateMessage = (PAL_TRANSLATEMESSAGE)GetProcAddress(hinstDLL,"PAL_TRANSLATEMESSAGE");
		PAL_Message = (GETPALMESSAGE)GetProcAddress (hinstDLL,"GETPALMESSAGE");
		PAL_SendInfoAgagin = (PAL_SENDINFOAGAIN)GetProcAddress (hinstDLL,"PAL_SENDINFOAGAIN");
		PAL_Info = (GETPALINFO)GetProcAddress (hinstDLL,"GETPALINFO");		
	}
   }
	//maple add
   	//动态查找目录下dll文件,判断是否加载相应dll
   if(GetLocalDllFile("M_GTOWN.dll"))
   {
	hinstDLL = LoadLibrary("M_GTOWN.dll");
	if(hinstDLL!=NULL)
	{
		GTOWN_OpenDialog = (GTOWN_OPENDIALOG)GetProcAddress (hinstDLL,"GTOWN_OPENDIALOG");	
		GTOWN_ShowDialog = (GTOWN_SHOWDIALOG)GetProcAddress (hinstDLL,"GTOWN_SHOWDIALOG");	//选择显示不同的子对话框	
		GTOWN_DialogMsg = (GTOWN_DIALOGMSG)GetProcAddress (hinstDLL,"GTOWN_DIALOGMSG");		
		GTOWN_TranslateMessage = (GTOWN_TRANSLATEMESSAGE)GetProcAddress(hinstDLL,"GTOWN_TRANSLATEMESSAGE");
		GTOWN_Message = (GETGTOWNMESSAGE)GetProcAddress (hinstDLL,"GETGTOWNMESSAGE");
		GTOWN_SendInfoAgagin = (GTOWN_SENDINFOAGAIN)GetProcAddress (hinstDLL,"GTOWN_SENDINFOAGAIN");
		GTOWN_Info = (GETGTOWNINFO)GetProcAddress (hinstDLL,"GETGTOWNINFO");	
	}
   }
   	//动态查找目录下dll文件,判断是否加载相应dll
   if(GetLocalDllFile("M_CG2.dll"))
   {
	hinstDLL=LoadLibrary("M_CG2.dll");
	if(hinstDLL!=NULL)
	{
		CG2_OpenDialog = (CG2_OPENDIALOG)GetProcAddress (hinstDLL,"CG2_OPENDIALOG");	
		CG2_ShowDialog = (CG2_SHOWDIALOG)GetProcAddress (hinstDLL,"CG2_SHOWDIALOG");	//选择显示不同的子对话框	
		CG2_DialogMsg = (CG2_DIALOGMSG)GetProcAddress (hinstDLL,"CG2_DIALOGMSG");		
		CG2_TranslateMessage = (CG2_TRANSLATEMESSAGE)GetProcAddress(hinstDLL,"CG2_TRANSLATEMESSAGE");
		CG2_SendInfoAgagin = (CG2_SENDINFOAGAIN)GetProcAddress (hinstDLL,"CG2_SENDINFOAGAIN");
		CG2_Message = (GETCG2MESSAGE)GetProcAddress (hinstDLL,"GETCG2MESSAGE");
		CG2_Info = (GETCG2INFO)GetProcAddress (hinstDLL,"GETCG2INFO");
	}
   }
	//maple add
   	//动态查找目录下dll文件,判断是否加载相应dll
   if(GetLocalDllFile("M_SDO.dll"))
   {
	hinstDLL=LoadLibrary("M_SDO.dll");
	if(hinstDLL!=NULL)
	{
		SDO_OpenDialog = (SDO_OPENDIALOG)GetProcAddress (hinstDLL,"SDO_OPENDIALOG");	
		SDO_ShowDialog = (SDO_SHOWDIALOG)GetProcAddress (hinstDLL,"SDO_SHOWDIALOG");	//选择显示不同的子对话框	
		SDO_DialogMsg = (SDO_DIALOGMSG)GetProcAddress (hinstDLL,"SDO_DIALOGMSG");		
		SDO_TranslateMessage = (SDO_TRANSLATEMESSAGE)GetProcAddress(hinstDLL,"SDO_TRANSLATEMESSAGE");
		SDO_Message = (GETSDOMESSAGE)GetProcAddress (hinstDLL,"GETSDOMESSAGE");
		SDO_SendInfoAgagin = (SDO_SENDINFOAGAIN)GetProcAddress (hinstDLL,"SDO_SENDINFOAGAIN");
		SDO_Info = (GETSDOINFO)GetProcAddress (hinstDLL,"GETSDOINFO");
	}
   }

	//maple add
   	//动态查找目录下dll文件,判断是否加载相应dll
   if(GetLocalDllFile("M_JW2.dll"))
   {
	hinstDLL=LoadLibrary("M_JW2.dll");
	if(hinstDLL!=NULL)
	{
		JW2_OpenDialog = (JW2_OPENDIALOG)GetProcAddress (hinstDLL,"JW2_OPENDIALOG");	
		JW2_ShowDialog = (JW2_SHOWDIALOG)GetProcAddress (hinstDLL,"JW2_SHOWDIALOG");	//选择显示不同的子对话框	
		JW2_DialogMsg = (JW2_DIALOGMSG)GetProcAddress (hinstDLL,"JW2_DIALOGMSG");		
		JW2_TranslateMessage = (JW2_TRANSLATEMESSAGE)GetProcAddress(hinstDLL,"JW2_TRANSLATEMESSAGE");
		JW2_Message = (GETJW2MESSAGE)GetProcAddress (hinstDLL,"GETJW2MESSAGE");
		JW2_SendInfoAgagin = (JW2_SENDINFOAGAIN)GetProcAddress (hinstDLL,"JW2_SENDINFOAGAIN");
		JW2_Info = (GETJW2INFO)GetProcAddress (hinstDLL,"GETJW2INFO");
	}
   }
	//动态查找目录下dll文件,判断是否加载相应dll
   if(GetLocalDllFile("M_WA.dll"))
   {
	hinstDLL=LoadLibrary("M_WA.dll");
	if(hinstDLL!=NULL)
	{      
		WA_OpenDialog = (WA_OPENDIALOG)GetProcAddress (hinstDLL,"WA_OPENDIALOG");	
		WA_ShowDialog = (WA_SHOWDIALOG)GetProcAddress (hinstDLL,"WA_SHOWDIALOG");	//选择显示不同的子对话框	
		WA_DialogMsg = (WA_DIALOGMSG)GetProcAddress (hinstDLL,"WA_DIALOGMSG");		
		WA_TranslateMessage = (WA_TRANSLATEMESSAGE)GetProcAddress(hinstDLL,"WA_TRANSLATEMESSAGE");
		WA_Message = (GETWAMESSAGE)GetProcAddress (hinstDLL,"GETWAMESSAGE");
		WA_SendInfoAgagin = (WA_SENDINFOAGAIN)GetProcAddress (hinstDLL,"WA_SENDINFOAGAIN");
		WA_Info = (GETWAINFO)GetProcAddress (hinstDLL,"GETWAINFO");
	}
   }

	// AGABUNB.
   	//动态查找目录下dll文件,判断是否加载相应dll
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
   	//动态查找目录下dll文件,判断是否加载相应dll
   if(GetLocalDllFile("M_XD.dll"))
   {
	////peng begin 侠盗金刚
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
//动态判断dll,获取本地的dll文件是否存在
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