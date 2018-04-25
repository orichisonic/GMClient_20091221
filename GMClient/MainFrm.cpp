// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "GMClient.h"

#include "MainFrm.h"

#include "TreeMenu.h"
#include "DialogView.h"
#include "DlgSelect.h"
#include "Mess.h"
#include ".\mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <io.h>
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE(UM_RECEIVE,OnReceiveMessage)
	ON_MESSAGE(UM_CLOSE,OnSocketClose)
	ON_COMMAND_RANGE(1,1000,OnMyMenuSelect)
	ON_WM_CLOSE()
ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style&=~FWS_ADDTOTITLE ; //直接去掉文档标题 
	cs.lpszName=_TEXT("GMTools"); 


	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	if(!wndSplitter.CreateStatic(this,1,2))//将整个界面划分为一行两列
	{
		return FALSE;
	}
	wndSplitter.CreateView(0,0,RUNTIME_CLASS(CTreeMenu),CSize(200,300),pContext);

	if(!wndSplitDlg.CreateStatic(&wndSplitter,2,1,WS_CHILD | WS_VISIBLE,wndSplitter.IdFromRowCol(0,1)))//将右边的列划分为上下两列
	{
		return FALSE;
	}
	wndSplitDlg.CreateView(0,0,RUNTIME_CLASS(CDlgSelect),CSize(400,25),pContext);
	wndSplitDlg.CreateView(1,0,RUNTIME_CLASS(CDialogView),CSize(400,275),pContext);

	theApp.m_clientsocket.SetParentHwnd(this->m_hWnd);
	return TRUE;
}

//处理快捷键响应函数
BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{	
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{
			if(pMsg->wParam == 'C')
			{	
				if(theApp.GM_TranslateMessage!=NULL)
					theApp.GM_TranslateMessage(pMsg);
				if(theApp.PAL_TranslateMessage!=NULL)
					theApp.PAL_TranslateMessage(pMsg);
				if(theApp.GTOWN_TranslateMessage!=NULL)
					theApp.GTOWN_TranslateMessage(pMsg);
				if(theApp.CG2_TranslateMessage!=NULL)
					theApp.CG2_TranslateMessage(pMsg);
				if(theApp.SDO_TranslateMessage!=NULL)
					theApp.SDO_TranslateMessage(pMsg);
				if(theApp.JW2_TranslateMessage!=NULL)
					theApp.JW2_TranslateMessage(pMsg);
				if(theApp.WA_TranslateMessage!=NULL)
					theApp.WA_TranslateMessage(pMsg);
				if(theApp.XD_TranslateMessage!=NULL)
					theApp.XD_TranslateMessage(pMsg);
			}
			else if(pMsg->wParam == 'A')
			{
				if(theApp.GM_TranslateMessage!=NULL)
					theApp.GM_TranslateMessage(pMsg);
				if(theApp.PAL_TranslateMessage!=NULL)
					theApp.PAL_TranslateMessage(pMsg);
				if(theApp.GTOWN_TranslateMessage!=NULL)
					theApp.GTOWN_TranslateMessage(pMsg);
				if(theApp.CG2_TranslateMessage!=NULL)
					theApp.CG2_TranslateMessage(pMsg);
			    if(theApp.SDO_TranslateMessage!=NULL)
					theApp.SDO_TranslateMessage(pMsg);
				if(theApp.JW2_TranslateMessage!=NULL)
					theApp.JW2_TranslateMessage(pMsg);
			    if(theApp.WA_TranslateMessage!=NULL)
					theApp.WA_TranslateMessage(pMsg);
				if(theApp.XD_TranslateMessage!=NULL)
					theApp.XD_TranslateMessage(pMsg);
			}
		}		
	}
	if(pMsg->message == WM_LBUTTONDOWN) 
	{
		//不让调整分割条  
		if(pMsg->hwnd == wndSplitDlg.m_hWnd)  
		{
			return TRUE;  
		}
	}
	return FALSE;
}

//截获系统消息
void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	CFrameWnd::OnSysCommand(nID, lParam);

/*	if ((nID == SC_MAXIMIZE) || (nID == SC_RESTORE) || (nID == 0xF001) || (nID == 0xF002) || (nID == 0xF003) || (nID == 0xF006) || (nID == 0xF032) || (nID == 0xF122))
	{
		theApp.GM_DialogMsg("", WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		theApp.PAL_DialogMsg("", WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		theApp.GTOWN_DialogMsg("", WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		theApp.CG2_DialogMsg("", WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		theApp.SDO_DialogMsg("",WM_SYSCOMMAND,SC_MAXIMIZE,0);
		theApp.JW2_DialogMsg("",WM_SYSCOMMAND,SC_MAXIMIZE,0);
		theApp.WA_DialogMsg("",WM_SYSCOMMAND,SC_MAXIMIZE,0);	
		if(this->wndSplitDlg.m_hWnd != NULL)
		{
			::SendMessage(this->wndSplitDlg.GetPane(0,0)->m_hWnd,UM_RECEIVE, 0, 0);//显示标签页名称处于最上面的对话框
		}
	}*/
	if ((nID == SC_MAXIMIZE) || (nID == SC_RESTORE) || (nID == 0xF001) || (nID == 0xF002) || (nID == 0xF003) || (nID == 0xF006) || (nID == 0xF032) || (nID == 0xF122))
	{
		//当只有最大化或者最大化复原时，执行发送子窗体最大化命令，传入窗体名称形参    彭根国加  090901
		if(nID==SC_MAXIMIZE|nID==0xF032|nID==0xF002|nID==0xF003|nID==0xF006)
		{
			CString DlgName=Ctabname::tabname.Right(Ctabname::tabname.GetLength()-Ctabname::tabname.Find('-')-1);
			CString GameName=Ctabname::tabname.Left(Ctabname::tabname.Find('-'));
			if(theApp.GM_DialogMsg!=NULL)
				theApp.GM_DialogMsg(DlgName, WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
			if(theApp.PAL_DialogMsg!=NULL)
				theApp.PAL_DialogMsg(DlgName, WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
			if(theApp.GTOWN_DialogMsg!=NULL)
				theApp.GTOWN_DialogMsg(DlgName, WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
			if(theApp.CG2_DialogMsg!=NULL)
				theApp.CG2_DialogMsg(DlgName, WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
			if(theApp.SDO_DialogMsg!=NULL)
				theApp.SDO_DialogMsg(DlgName,WM_SYSCOMMAND,SC_MAXIMIZE,0);
			if(theApp.JW2_DialogMsg!=NULL)
				theApp.JW2_DialogMsg(DlgName,WM_SYSCOMMAND,SC_MAXIMIZE,0);
			if(theApp.WA_DialogMsg!=NULL)
				theApp.WA_DialogMsg(DlgName,WM_SYSCOMMAND,SC_MAXIMIZE,0);	
		   
		}
		{
			if(this->wndSplitDlg.m_hWnd != NULL)
			{
				::SendMessage(this->wndSplitDlg.GetPane(0,0)->m_hWnd,UM_RECEIVE, 0, 0);//显示标签页名称处于最上面的对话框
			}
		}
	}
	if(nID==SC_MINIMIZE)
	{
		CMess mytest;
		mytest.Create(IDD_DIALOG2,NULL);
		mytest.ShowWindow(SW_NORMAL);
		
	}

	//增加部分结束 090901 彭根国
}

///接收服务端发送的数据包
LRESULT CMainFrame::OnReceiveMessage(WPARAM wParam, LPARAM lParam)
{	
	Sleep(200);
	KillTimer(1);
	Sleep(200);
	CIni mIni;
	CMSocket selfSocket;		

	CMenu m_NewMenu,m_FileMenu[30];
	int actlength=0;
	int num=0;
	selfSocket.SetSocket(theApp.m_clientsocket.m_hSocket);//接收服务端传递回来的信息
	actlength=selfSocket.MyReceive();
	if(actlength==1)
		AfxMessageBox("aa");

	if(actlength == -1)
	{
		::EnableWindow(this->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		return false;
	}

	if(theApp.menuflag==false)//如果还没有构造过菜单和CTreeCtrl，或者需要重新构造
	{
		::SendMessage(this->wndSplitter.GetPane(0,0)->m_hWnd,UM_RESVIEW,(WPARAM)(selfSocket.recvBuffer()),(LPARAM)actlength);//将接收到的模块信息传递给CTreeMenu类
	}

	packethead.Create(actlength);
	try
	{
		bool b_result=packethead.DeHead((unsigned char *)selfSocket.recvBuffer(),actlength);

		if(b_result)
		{
			theApp.m_SendCount = 0;//重复发送次数为0
			switch((unsigned int)packethead.GetMessageID())
			{	
			case CEnumCore::Message_Tag_ID::USER_ACTIVE_RESP:
				ReturnActive();
				break;
			case CEnumCore::Message_Tag_ID::USER_MODULE_QUERY_RESP://如果接收到的是用户模块信息
				{
					if(theApp.menuflag==false)//如果没有构造过用户模块信息
					{					
						CSocketData socketdata;
						CGlobalStruct::TFLV m_tflv,m_tflv1,tmpm_tflv;

						theApp.menuflag=true;
						socketdata.Create(packethead.m_packethead.bodylen/8);
						socketdata.DeBody(packethead.getDataBuf()+18,packethead.m_packethead.bodylen);

						m_tflv=socketdata.getTLV(1,1);//获取第一个TFLV
						if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)
						{
							MessageBox((LPCSTR)&m_tflv.lpdata,mIni.ReadValue("Global","Result"),0);
							socketdata.Destroy();
							return false;
						}
						CMainFrame::m_bAutoMenuEnable = true;
						char strTabName[256];
						char strModuleName[256];
						VERIFY(m_NewMenu.CreateMenu());//创建新的CMenu类对象
						
						for(int i=0;i<30;i++)
						{
							m_FileMenu[i].CreateMenu();
						}
					
						m_tflv=socketdata.getTLVByName(1, CEnumCore::TagName::GameName);//获取游戏名称
						tmpm_tflv=m_tflv;
						//m_tflv1=socketdata.getTLVByName(1, CEnumCore::TagName::ModuleName);//获取对应游戏的第一个模块名称
						m_tflv1=socketdata.getTLVByName(1, CEnumCore::TagName::ModuleClass);
						
						sprintf(strTabName,"%s-%s",m_tflv.lpdata,mIni.ReadValue("Global",(LPCSTR)m_tflv1.lpdata));
						m_FileMenu[num].AppendMenu(MF_STRING,m_tflv1.nIndex,(LPCTSTR)strTabName);//将第一个模块名称加载到菜单中
						for(int i=2;i <= socketdata.getQueryNum();i++)
						{
							tmpm_tflv=socketdata.getTLVByName(i, CEnumCore::TagName::GameName);//获取下一个游戏名称
							if(!strcmp((char *)&tmpm_tflv.lpdata,(char *)&m_tflv.lpdata))//如果前后游戏名称相同
							{					
								m_tflv1=socketdata.getTLVByName(i, CEnumCore::TagName::ModuleClass);
								sprintf(strTabName,"%s-%s",m_tflv.lpdata,mIni.ReadValue("Global",(LPCSTR)m_tflv1.lpdata));
								m_FileMenu[num].AppendMenu(MF_STRING,m_tflv1.nIndex,(LPCTSTR)strTabName);//继续添加新的模块名称
							}
							else//如果前后游戏名称不同
							{
								m_NewMenu.AppendMenu(MF_POPUP, (UINT) m_FileMenu[num].m_hMenu, (LPCTSTR)m_tflv.lpdata);//将第一个子菜单列表插入到第一个游戏名称下作为一个菜单项

								num++;
								m_tflv=tmpm_tflv;
								m_tflv1=socketdata.getTLVByName(i, CEnumCore::TagName::ModuleClass);//获取新的模块名称
								sprintf(strTabName,"%s-%s",m_tflv.lpdata,mIni.ReadValue("Global",(LPCSTR)m_tflv1.lpdata));
								m_FileMenu[num].AppendMenu(MF_STRING,m_tflv1.nIndex,(LPCTSTR)strTabName);//加载新的模块名称
							}					
						}
						m_NewMenu.AppendMenu(MF_POPUP, (UINT) m_FileMenu[num].m_hMenu, (LPCTSTR)m_tflv.lpdata);//将最后一个子菜单列表插入到最后一个游戏名称下做为一个菜单项

						AfxGetMainWnd()->SetMenu(NULL);
						
						//添加新的菜单
						AfxGetMainWnd()->SetMenu(&m_NewMenu);
						AfxGetMainWnd()->GetMenu()->m_hMenu= m_NewMenu.m_hMenu;

						//销毁所有局部的菜单项，防止发生内存冲突
						m_NewMenu.Detach();
						for(i=0;i<=num;i++)
						{
							m_FileMenu[i].Detach();
						}				
						//将SOCKET、操作员ID、操作员名称的信息传递给底层的dll
						if(GetLocalDllFile("M_GM.dll"))
							theApp.GM_Info(theApp.m_clientsocket.m_hSocket,theApp.UserByID,theApp.userName, this->wndSplitDlg.GetPane(1,0)->m_hWnd, &theApp.m_SelectDll);
						if(GetLocalDllFile("M_PAL.dll"))
							theApp.PAL_Info(theApp.m_clientsocket.m_hSocket, theApp.UserByID, theApp.userName, this->wndSplitDlg.GetPane(1,0)->m_hWnd, &theApp.m_SelectDll);
						if(GetLocalDllFile("M_GTOWN.dll"))
							theApp.GTOWN_Info(theApp.m_clientsocket.m_hSocket,theApp.UserByID,theApp.userName, this->wndSplitDlg.GetPane(1,0)->m_hWnd, &theApp.m_SelectDll);
						if(GetLocalDllFile("M_CG2.dll"))
							theApp.CG2_Info(theApp.m_clientsocket.m_hSocket, theApp.UserByID, theApp.userName, this->wndSplitDlg.GetPane(1,0)->m_hWnd, &theApp.m_SelectDll);
						if(GetLocalDllFile("M_SDO.dll"))
							theApp.SDO_Info(theApp.m_clientsocket.m_hSocket, theApp.UserByID, theApp.userName, this->wndSplitDlg.GetPane(1,0)->m_hWnd, &theApp.m_SelectDll);
						if(GetLocalDllFile("M_JW2.dll"))
							theApp.JW2_Info(theApp.m_clientsocket.m_hSocket, theApp.UserByID, theApp.userName, this->wndSplitDlg.GetPane(1,0)->m_hWnd, &theApp.m_SelectDll);
						if(GetLocalDllFile("M_WA.dll"))
							theApp.WA_Info(theApp.m_clientsocket.m_hSocket, theApp.UserByID, theApp.userName, this->wndSplitDlg.GetPane(1,0)->m_hWnd, &theApp.m_SelectDll);
						if(GetLocalDllFile("AGABUNB.dll"))
							theApp.m_pInitializeCAGABUNBFun(theApp.m_clientsocket.m_hSocket, theApp.UserByID, theApp.userName, this->wndSplitDlg.GetPane(1,0)->m_hWnd, &theApp.m_SelectDll);
						if(GetLocalDllFile("M_XD.dll"))
							theApp.XD_Info(theApp.m_clientsocket.m_hSocket, theApp.UserByID, theApp.userName, this->wndSplitDlg.GetPane(1,0)->m_hWnd, &theApp.m_SelectDll);

						socketdata.Destroy();
						socketdata.Destroy();
					}
					else//如果已经构造过用户模块信息
					{
						theApp.GM_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//将接收到的信息传递给系统管理模块
					}			
				}
				break;
			case CEnumCore::Message_Tag_ID::GAME_QUERY_RESP:
				if(theApp.GM_Message!=NULL)
					theApp.GM_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//如果接收到的是系统管理相关，将接收到的信息传递给系统管理模块
				// 所有游戏帐号封停/解封模块(AGABUNB).
				if(theApp.m_pSetRecvDataFun!=NULL)
					theApp.m_pSetRecvDataFun(packethead.getDataBuf()+18, packethead.m_packethead.bodylen, packethead.GetMessageID());
				break;
			case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP:
                if(theApp.PAL_Message!=NULL)
					theApp.PAL_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//将接收到的信息传递给仙剑模块
				if(theApp.GTOWN_Message!=NULL)
					theApp.GTOWN_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//将接收到的信息传递给吉堂模块
                if(theApp.CG2_Message!=NULL)
					theApp.CG2_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//将接收到的信息传递给CG2模块
                if(theApp.SDO_Message!=NULL)
					theApp.SDO_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);
				if(theApp.JW2_Message!=NULL)
					theApp.JW2_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);
				if(theApp.WA_Message!=NULL)
					theApp.WA_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);
				// 所有游戏帐号封停/解封模块(AGABUNB).
				if(theApp.m_pSetRecvDataFun!=NULL)
					theApp.m_pSetRecvDataFun(packethead.getDataBuf()+18, packethead.m_packethead.bodylen, packethead.GetMessageID());
				if(theApp.XD_Message!=NULL)
					theApp.XD_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);
				if(theApp.GM_Message!=NULL)
					theApp.GM_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//如果接收到的是系统管理相关，将接收到的信息传递给系统管理模块
				break;
			case CEnumCore::Message_Tag_ID::USER_QUERY_ALL_RESP:
                if(theApp.GM_Message!=NULL)
					theApp.GM_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//如果接收到的是系统管理相关，将接收到的信息传递给系统管理模块
                if(theApp.JW2_Message!=NULL)
					theApp.JW2_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//将接受到的信息传递给超级舞者模块
				break;
			case CEnumCore::Message_Tag_ID::WA_KickPlayer_Resp:
			case CEnumCore::Message_Tag_ID::WA_ClosePlayer_Resp:
				if(theApp.GM_Message!=NULL)
					theApp.GM_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//如果接收到的是系统管理相关，将接收到的信息传递给系统管理模块
				if(theApp.WA_Message!=NULL)
					theApp.WA_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//将接受到的信息传递给勇士无双模块
				break;
			default:
				switch((unsigned int)packethead.m_packethead.m_msg_category)
				{		
				case CEnumCore::Msg_Category::COMMON://如果接收到的是普通信息
				case CEnumCore::Msg_Category::GAME_ADMIN://如果接收到的是游戏模块信息
				case CEnumCore::Msg_Category::MODULE_ADMIN:
				case CEnumCore::Msg_Category::USER_ADMIN:
				case CEnumCore::Msg_Category::USER_MODULE_ADMIN:
					theApp.GM_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//如果接收到的是系统管理相关，将接收到的信息传递给系统管理模块
					break;
				case CEnumCore::Msg_Category::PAL_ADMIN:
				case CEnumCore::Msg_Category::PALLOG_ADMIN:
					theApp.PAL_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//将接收到的信息传递给仙剑模块
					break;
				case CEnumCore::Msg_Category::GTOWN_ADMIN:
				case CEnumCore::Msg_Category::GT_OP_ADMIN:
					theApp.GTOWN_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//将接收到的信息传递给吉堂模块
					break;
				case CEnumCore::Msg_Category::CG2_ADMIN:
					theApp.CG2_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//将接收到的信息传递给吉堂模块
					break;

				case CEnumCore::Msg_Category::SDO_ADMIN:
					theApp.SDO_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//将接受到的信息传递给超级舞者模块
					break;
				case CEnumCore::Msg_Category::JW2_ADMIN:
					theApp.JW2_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//将接受到的信息传递给劲舞2模块
					break;
				case CEnumCore::Msg_Category::WA_ADMIN:
					theApp.WA_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//将接受到的信息传递给勇士无双模块
					break;
				case CEnumCore::Msg_Category::Ban_ADMIN:
					// 所有游戏帐号封停/解封模块(AGABUNB).
					theApp.m_pSetRecvDataFun(packethead.getDataBuf()+18, packethead.m_packethead.bodylen, packethead.GetMessageID());
					break;
					// peng begin.如果返回的是侠盗金刚
				case CEnumCore::Msg_Category::XDJG_ADMIN:
					
					theApp.XD_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);
					//MessageBox("have receive");
					break;
					//peng end
				}
				break;
			}
		}	
		else
		{
			if(theApp.menuflag==false)//如果没有构造过用户模块信息
			{
			}
			else
			{
				if(theApp.m_SendCount<5)//重复发送次数小于5次
				{
					if(theApp.m_SelectDll == 1)
					{
						theApp.GM_SendInfoAgain();
						theApp.m_SendCount++;
					}
					else if(theApp.m_SelectDll == 2)
					{
						theApp.PAL_SendInfoAgagin();
						theApp.m_SendCount++;
					}
					//maple add////选择的是吉堂模块的dll
					else if(theApp.m_SelectDll ==3)
					{
						theApp.GTOWN_SendInfoAgagin();
						theApp.m_SendCount++;
					}

					else if(theApp.m_SelectDll ==4)
					{
						theApp.CG2_SendInfoAgagin();
						theApp.m_SendCount++;
					}
					else if(theApp.m_SelectDll ==5)
					{
						theApp.SDO_SendInfoAgagin();
						theApp.m_SendCount++;
					}
					else if(theApp.m_SelectDll ==6)
					{
						theApp.JW2_SendInfoAgagin();
						theApp.m_SendCount++;
					}
					else if(theApp.m_SelectDll ==7)
					{
						theApp.WA_SendInfoAgagin();
						theApp.m_SendCount++;
					}
					else if(theApp.m_SelectDll ==8)
					{
						theApp.XD_SendInfoAgagin();
						theApp.m_SendCount++;
					}
				}
				else//重复发送次数超过5次
				{
					::EnableWindow(this->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
					::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
					MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),MB_OK);//数据解析异常
					return false;
				}
			}	
		}
	}
	catch(...)
	{
	}
	return true;
}

// 选择不同的菜单项进行处理
void CMainFrame::OnMyMenuSelect(UINT nID)
{
	char m_MenuName[50];
	char m_ParentMenuName[50];
	ZeroMemory(m_MenuName, 50);
	ZeroMemory(m_ParentMenuName,50);

	GetMenuString(AfxGetMainWnd()->GetMenu()->m_hMenu,nID,m_MenuName,50,MF_BYCOMMAND);//获取选中的菜单项名称
	CString tabName="";

	tabName.Format("%s",m_MenuName);
	sprintf(m_MenuName,"%s",tabName.Right(tabName.GetLength()-tabName.Find('-')-1));
	sprintf(m_ParentMenuName,"%s",tabName.Left(tabName.Find('-')));

	::SendMessage(this->wndSplitDlg.GetPane(0,0)->m_hWnd,UM_RESVIEW,(WPARAM)(m_MenuName),(LPARAM)m_ParentMenuName);//将接收到的模块信息传递给CDlgSelect类
}

//服务器已断开SOCKET连接
LRESULT CMainFrame::OnSocketClose(WPARAM wParam, LPARAM lParam)
{
	::EnableWindow(this->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	CIni mIni;
	MessageBox(mIni.ReadValue("Global","MAIN_ERROR_ServerDisconnect"),mIni.ReadValue("Global","Error"),MB_OK);//显示服务器已断开连接
	return true;
}

//关闭窗体
void CMainFrame::OnClose()
{	
	::SendMessage(this->wndSplitDlg.GetPane(0,0)->m_hWnd,WM_CLOSE,0,0);//关闭对话框
	if(theApp.GM_DialogMsg!=NULL)
		theApp.GM_DialogMsg("", WM_CLOSE, 0, 0);//关闭GM的子对话框
	if(theApp.PAL_DialogMsg!=NULL)
		theApp.PAL_DialogMsg("", WM_CLOSE, 0, 0);//关闭PAL的子对话框
	if(theApp.GTOWN_DialogMsg!=NULL)
		theApp.GTOWN_DialogMsg("", WM_CLOSE, 0, 0);//关闭GTown的子对话框
	if(theApp.CG2_DialogMsg!=NULL)
		theApp.CG2_DialogMsg("", WM_CLOSE, 0, 0);//关闭CG2的子对话框
	if(theApp.SDO_DialogMsg!=NULL)
		theApp.SDO_DialogMsg("", WM_CLOSE, 0, 0);//关闭SDO的子对话框
	if(theApp.WA_DialogMsg!=NULL)
		theApp.WA_DialogMsg("",WM_CLOSE,0,0);//关闭WA的子对话框
	if(theApp.XD_DialogMsg!=NULL)
		theApp.XD_DialogMsg("",WM_CLOSE,0,0);//关闭XD的子对话框
	CFrameWnd::OnClose();
}

bool CMainFrame::ReturnActive(void)
{
	CSocketData socketdata;
	socketdata.InitCreate(1,1);
	socketdata.AddTFLV(CEnumCore::TagName::MESSAGE,CEnumCore::TagFormat::TLV_STRING,strlen("Active"),(unsigned char *)&"Active");
	int length=socketdata.EnBody();

	theApp.packethead.Create(length);
	theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::USER_ACTIVE,length);

	theApp.packethead.EnSendBuf(&length,(unsigned char *)socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
	theApp.packetLength = length;
	theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),length);//发送连接服务器的请求
	socketdata.Destroy();

	return false;
}
//动态判断dll,获取本地的dll文件是否存在
bool CMainFrame::GetLocalDllFile(char* dllname)
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
