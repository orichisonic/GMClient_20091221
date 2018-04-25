// MainFrm.cpp : CMainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
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

	cs.style&=~FWS_ADDTOTITLE ; //ֱ��ȥ���ĵ����� 
	cs.lpszName=_TEXT("GMTools"); 


	return TRUE;
}


// CMainFrame ���

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


// CMainFrame ��Ϣ�������

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	if(!wndSplitter.CreateStatic(this,1,2))//���������滮��Ϊһ������
	{
		return FALSE;
	}
	wndSplitter.CreateView(0,0,RUNTIME_CLASS(CTreeMenu),CSize(200,300),pContext);

	if(!wndSplitDlg.CreateStatic(&wndSplitter,2,1,WS_CHILD | WS_VISIBLE,wndSplitter.IdFromRowCol(0,1)))//���ұߵ��л���Ϊ��������
	{
		return FALSE;
	}
	wndSplitDlg.CreateView(0,0,RUNTIME_CLASS(CDlgSelect),CSize(400,25),pContext);
	wndSplitDlg.CreateView(1,0,RUNTIME_CLASS(CDialogView),CSize(400,275),pContext);

	theApp.m_clientsocket.SetParentHwnd(this->m_hWnd);
	return TRUE;
}

//�����ݼ���Ӧ����
BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{	
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
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
		//���õ����ָ���  
		if(pMsg->hwnd == wndSplitDlg.m_hWnd)  
		{
			return TRUE;  
		}
	}
	return FALSE;
}

//�ػ�ϵͳ��Ϣ
void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	CFrameWnd::OnSysCommand(nID, lParam);

/*	if ((nID == SC_MAXIMIZE) || (nID == SC_RESTORE) || (nID == 0xF001) || (nID == 0xF002) || (nID == 0xF003) || (nID == 0xF006) || (nID == 0xF032) || (nID == 0xF122))
	{
		theApp.GM_DialogMsg("", WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		theApp.PAL_DialogMsg("", WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		theApp.GTOWN_DialogMsg("", WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		theApp.CG2_DialogMsg("", WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		theApp.SDO_DialogMsg("",WM_SYSCOMMAND,SC_MAXIMIZE,0);
		theApp.JW2_DialogMsg("",WM_SYSCOMMAND,SC_MAXIMIZE,0);
		theApp.WA_DialogMsg("",WM_SYSCOMMAND,SC_MAXIMIZE,0);	
		if(this->wndSplitDlg.m_hWnd != NULL)
		{
			::SendMessage(this->wndSplitDlg.GetPane(0,0)->m_hWnd,UM_RECEIVE, 0, 0);//��ʾ��ǩҳ���ƴ���������ĶԻ���
		}
	}*/
	if ((nID == SC_MAXIMIZE) || (nID == SC_RESTORE) || (nID == 0xF001) || (nID == 0xF002) || (nID == 0xF003) || (nID == 0xF006) || (nID == 0xF032) || (nID == 0xF122))
	{
		//��ֻ����󻯻�����󻯸�ԭʱ��ִ�з����Ӵ������������봰�������β�    �������  090901
		if(nID==SC_MAXIMIZE|nID==0xF032|nID==0xF002|nID==0xF003|nID==0xF006)
		{
			CString DlgName=Ctabname::tabname.Right(Ctabname::tabname.GetLength()-Ctabname::tabname.Find('-')-1);
			CString GameName=Ctabname::tabname.Left(Ctabname::tabname.Find('-'));
			if(theApp.GM_DialogMsg!=NULL)
				theApp.GM_DialogMsg(DlgName, WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
			if(theApp.PAL_DialogMsg!=NULL)
				theApp.PAL_DialogMsg(DlgName, WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
			if(theApp.GTOWN_DialogMsg!=NULL)
				theApp.GTOWN_DialogMsg(DlgName, WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
			if(theApp.CG2_DialogMsg!=NULL)
				theApp.CG2_DialogMsg(DlgName, WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
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
				::SendMessage(this->wndSplitDlg.GetPane(0,0)->m_hWnd,UM_RECEIVE, 0, 0);//��ʾ��ǩҳ���ƴ���������ĶԻ���
			}
		}
	}
	if(nID==SC_MINIMIZE)
	{
		CMess mytest;
		mytest.Create(IDD_DIALOG2,NULL);
		mytest.ShowWindow(SW_NORMAL);
		
	}

	//���Ӳ��ֽ��� 090901 �����
}

///���շ���˷��͵����ݰ�
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
	selfSocket.SetSocket(theApp.m_clientsocket.m_hSocket);//���շ���˴��ݻ�������Ϣ
	actlength=selfSocket.MyReceive();
	if(actlength==1)
		AfxMessageBox("aa");

	if(actlength == -1)
	{
		::EnableWindow(this->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
		::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		return false;
	}

	if(theApp.menuflag==false)//�����û�й�����˵���CTreeCtrl��������Ҫ���¹���
	{
		::SendMessage(this->wndSplitter.GetPane(0,0)->m_hWnd,UM_RESVIEW,(WPARAM)(selfSocket.recvBuffer()),(LPARAM)actlength);//�����յ���ģ����Ϣ���ݸ�CTreeMenu��
	}

	packethead.Create(actlength);
	try
	{
		bool b_result=packethead.DeHead((unsigned char *)selfSocket.recvBuffer(),actlength);

		if(b_result)
		{
			theApp.m_SendCount = 0;//�ظ����ʹ���Ϊ0
			switch((unsigned int)packethead.GetMessageID())
			{	
			case CEnumCore::Message_Tag_ID::USER_ACTIVE_RESP:
				ReturnActive();
				break;
			case CEnumCore::Message_Tag_ID::USER_MODULE_QUERY_RESP://������յ������û�ģ����Ϣ
				{
					if(theApp.menuflag==false)//���û�й�����û�ģ����Ϣ
					{					
						CSocketData socketdata;
						CGlobalStruct::TFLV m_tflv,m_tflv1,tmpm_tflv;

						theApp.menuflag=true;
						socketdata.Create(packethead.m_packethead.bodylen/8);
						socketdata.DeBody(packethead.getDataBuf()+18,packethead.m_packethead.bodylen);

						m_tflv=socketdata.getTLV(1,1);//��ȡ��һ��TFLV
						if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)
						{
							MessageBox((LPCSTR)&m_tflv.lpdata,mIni.ReadValue("Global","Result"),0);
							socketdata.Destroy();
							return false;
						}
						CMainFrame::m_bAutoMenuEnable = true;
						char strTabName[256];
						char strModuleName[256];
						VERIFY(m_NewMenu.CreateMenu());//�����µ�CMenu�����
						
						for(int i=0;i<30;i++)
						{
							m_FileMenu[i].CreateMenu();
						}
					
						m_tflv=socketdata.getTLVByName(1, CEnumCore::TagName::GameName);//��ȡ��Ϸ����
						tmpm_tflv=m_tflv;
						//m_tflv1=socketdata.getTLVByName(1, CEnumCore::TagName::ModuleName);//��ȡ��Ӧ��Ϸ�ĵ�һ��ģ������
						m_tflv1=socketdata.getTLVByName(1, CEnumCore::TagName::ModuleClass);
						
						sprintf(strTabName,"%s-%s",m_tflv.lpdata,mIni.ReadValue("Global",(LPCSTR)m_tflv1.lpdata));
						m_FileMenu[num].AppendMenu(MF_STRING,m_tflv1.nIndex,(LPCTSTR)strTabName);//����һ��ģ�����Ƽ��ص��˵���
						for(int i=2;i <= socketdata.getQueryNum();i++)
						{
							tmpm_tflv=socketdata.getTLVByName(i, CEnumCore::TagName::GameName);//��ȡ��һ����Ϸ����
							if(!strcmp((char *)&tmpm_tflv.lpdata,(char *)&m_tflv.lpdata))//���ǰ����Ϸ������ͬ
							{					
								m_tflv1=socketdata.getTLVByName(i, CEnumCore::TagName::ModuleClass);
								sprintf(strTabName,"%s-%s",m_tflv.lpdata,mIni.ReadValue("Global",(LPCSTR)m_tflv1.lpdata));
								m_FileMenu[num].AppendMenu(MF_STRING,m_tflv1.nIndex,(LPCTSTR)strTabName);//��������µ�ģ������
							}
							else//���ǰ����Ϸ���Ʋ�ͬ
							{
								m_NewMenu.AppendMenu(MF_POPUP, (UINT) m_FileMenu[num].m_hMenu, (LPCTSTR)m_tflv.lpdata);//����һ���Ӳ˵��б���뵽��һ����Ϸ��������Ϊһ���˵���

								num++;
								m_tflv=tmpm_tflv;
								m_tflv1=socketdata.getTLVByName(i, CEnumCore::TagName::ModuleClass);//��ȡ�µ�ģ������
								sprintf(strTabName,"%s-%s",m_tflv.lpdata,mIni.ReadValue("Global",(LPCSTR)m_tflv1.lpdata));
								m_FileMenu[num].AppendMenu(MF_STRING,m_tflv1.nIndex,(LPCTSTR)strTabName);//�����µ�ģ������
							}					
						}
						m_NewMenu.AppendMenu(MF_POPUP, (UINT) m_FileMenu[num].m_hMenu, (LPCTSTR)m_tflv.lpdata);//�����һ���Ӳ˵��б���뵽���һ����Ϸ��������Ϊһ���˵���

						AfxGetMainWnd()->SetMenu(NULL);
						
						//����µĲ˵�
						AfxGetMainWnd()->SetMenu(&m_NewMenu);
						AfxGetMainWnd()->GetMenu()->m_hMenu= m_NewMenu.m_hMenu;

						//�������оֲ��Ĳ˵����ֹ�����ڴ��ͻ
						m_NewMenu.Detach();
						for(i=0;i<=num;i++)
						{
							m_FileMenu[i].Detach();
						}				
						//��SOCKET������ԱID������Ա���Ƶ���Ϣ���ݸ��ײ��dll
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
					else//����Ѿ�������û�ģ����Ϣ
					{
						theApp.GM_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//�����յ�����Ϣ���ݸ�ϵͳ����ģ��
					}			
				}
				break;
			case CEnumCore::Message_Tag_ID::GAME_QUERY_RESP:
				if(theApp.GM_Message!=NULL)
					theApp.GM_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//������յ�����ϵͳ������أ������յ�����Ϣ���ݸ�ϵͳ����ģ��
				// ������Ϸ�ʺŷ�ͣ/���ģ��(AGABUNB).
				if(theApp.m_pSetRecvDataFun!=NULL)
					theApp.m_pSetRecvDataFun(packethead.getDataBuf()+18, packethead.m_packethead.bodylen, packethead.GetMessageID());
				break;
			case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP:
                if(theApp.PAL_Message!=NULL)
					theApp.PAL_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//�����յ�����Ϣ���ݸ��ɽ�ģ��
				if(theApp.GTOWN_Message!=NULL)
					theApp.GTOWN_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//�����յ�����Ϣ���ݸ�����ģ��
                if(theApp.CG2_Message!=NULL)
					theApp.CG2_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//�����յ�����Ϣ���ݸ�CG2ģ��
                if(theApp.SDO_Message!=NULL)
					theApp.SDO_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);
				if(theApp.JW2_Message!=NULL)
					theApp.JW2_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);
				if(theApp.WA_Message!=NULL)
					theApp.WA_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);
				// ������Ϸ�ʺŷ�ͣ/���ģ��(AGABUNB).
				if(theApp.m_pSetRecvDataFun!=NULL)
					theApp.m_pSetRecvDataFun(packethead.getDataBuf()+18, packethead.m_packethead.bodylen, packethead.GetMessageID());
				if(theApp.XD_Message!=NULL)
					theApp.XD_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);
				if(theApp.GM_Message!=NULL)
					theApp.GM_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//������յ�����ϵͳ������أ������յ�����Ϣ���ݸ�ϵͳ����ģ��
				break;
			case CEnumCore::Message_Tag_ID::USER_QUERY_ALL_RESP:
                if(theApp.GM_Message!=NULL)
					theApp.GM_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//������յ�����ϵͳ������أ������յ�����Ϣ���ݸ�ϵͳ����ģ��
                if(theApp.JW2_Message!=NULL)
					theApp.JW2_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//�����ܵ�����Ϣ���ݸ���������ģ��
				break;
			case CEnumCore::Message_Tag_ID::WA_KickPlayer_Resp:
			case CEnumCore::Message_Tag_ID::WA_ClosePlayer_Resp:
				if(theApp.GM_Message!=NULL)
					theApp.GM_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//������յ�����ϵͳ������أ������յ�����Ϣ���ݸ�ϵͳ����ģ��
				if(theApp.WA_Message!=NULL)
					theApp.WA_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//�����ܵ�����Ϣ���ݸ���ʿ��˫ģ��
				break;
			default:
				switch((unsigned int)packethead.m_packethead.m_msg_category)
				{		
				case CEnumCore::Msg_Category::COMMON://������յ�������ͨ��Ϣ
				case CEnumCore::Msg_Category::GAME_ADMIN://������յ�������Ϸģ����Ϣ
				case CEnumCore::Msg_Category::MODULE_ADMIN:
				case CEnumCore::Msg_Category::USER_ADMIN:
				case CEnumCore::Msg_Category::USER_MODULE_ADMIN:
					theApp.GM_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//������յ�����ϵͳ������أ������յ�����Ϣ���ݸ�ϵͳ����ģ��
					break;
				case CEnumCore::Msg_Category::PAL_ADMIN:
				case CEnumCore::Msg_Category::PALLOG_ADMIN:
					theApp.PAL_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//�����յ�����Ϣ���ݸ��ɽ�ģ��
					break;
				case CEnumCore::Msg_Category::GTOWN_ADMIN:
				case CEnumCore::Msg_Category::GT_OP_ADMIN:
					theApp.GTOWN_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//�����յ�����Ϣ���ݸ�����ģ��
					break;
				case CEnumCore::Msg_Category::CG2_ADMIN:
					theApp.CG2_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//�����յ�����Ϣ���ݸ�����ģ��
					break;

				case CEnumCore::Msg_Category::SDO_ADMIN:
					theApp.SDO_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//�����ܵ�����Ϣ���ݸ���������ģ��
					break;
				case CEnumCore::Msg_Category::JW2_ADMIN:
					theApp.JW2_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//�����ܵ�����Ϣ���ݸ�����2ģ��
					break;
				case CEnumCore::Msg_Category::WA_ADMIN:
					theApp.WA_Message(packethead.getDataBuf()+18,actlength,packethead.GetMessageID(),packethead.m_packethead);//�����ܵ�����Ϣ���ݸ���ʿ��˫ģ��
					break;
				case CEnumCore::Msg_Category::Ban_ADMIN:
					// ������Ϸ�ʺŷ�ͣ/���ģ��(AGABUNB).
					theApp.m_pSetRecvDataFun(packethead.getDataBuf()+18, packethead.m_packethead.bodylen, packethead.GetMessageID());
					break;
					// peng begin.������ص����������
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
			if(theApp.menuflag==false)//���û�й�����û�ģ����Ϣ
			{
			}
			else
			{
				if(theApp.m_SendCount<5)//�ظ����ʹ���С��5��
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
					//maple add////ѡ����Ǽ���ģ���dll
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
				else//�ظ����ʹ�������5��
				{
					::EnableWindow(this->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
					::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
					MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),MB_OK);//���ݽ����쳣
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

// ѡ��ͬ�Ĳ˵�����д���
void CMainFrame::OnMyMenuSelect(UINT nID)
{
	char m_MenuName[50];
	char m_ParentMenuName[50];
	ZeroMemory(m_MenuName, 50);
	ZeroMemory(m_ParentMenuName,50);

	GetMenuString(AfxGetMainWnd()->GetMenu()->m_hMenu,nID,m_MenuName,50,MF_BYCOMMAND);//��ȡѡ�еĲ˵�������
	CString tabName="";

	tabName.Format("%s",m_MenuName);
	sprintf(m_MenuName,"%s",tabName.Right(tabName.GetLength()-tabName.Find('-')-1));
	sprintf(m_ParentMenuName,"%s",tabName.Left(tabName.Find('-')));

	::SendMessage(this->wndSplitDlg.GetPane(0,0)->m_hWnd,UM_RESVIEW,(WPARAM)(m_MenuName),(LPARAM)m_ParentMenuName);//�����յ���ģ����Ϣ���ݸ�CDlgSelect��
}

//�������ѶϿ�SOCKET����
LRESULT CMainFrame::OnSocketClose(WPARAM wParam, LPARAM lParam)
{
	::EnableWindow(this->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	CIni mIni;
	MessageBox(mIni.ReadValue("Global","MAIN_ERROR_ServerDisconnect"),mIni.ReadValue("Global","Error"),MB_OK);//��ʾ�������ѶϿ�����
	return true;
}

//�رմ���
void CMainFrame::OnClose()
{	
	::SendMessage(this->wndSplitDlg.GetPane(0,0)->m_hWnd,WM_CLOSE,0,0);//�رնԻ���
	if(theApp.GM_DialogMsg!=NULL)
		theApp.GM_DialogMsg("", WM_CLOSE, 0, 0);//�ر�GM���ӶԻ���
	if(theApp.PAL_DialogMsg!=NULL)
		theApp.PAL_DialogMsg("", WM_CLOSE, 0, 0);//�ر�PAL���ӶԻ���
	if(theApp.GTOWN_DialogMsg!=NULL)
		theApp.GTOWN_DialogMsg("", WM_CLOSE, 0, 0);//�ر�GTown���ӶԻ���
	if(theApp.CG2_DialogMsg!=NULL)
		theApp.CG2_DialogMsg("", WM_CLOSE, 0, 0);//�ر�CG2���ӶԻ���
	if(theApp.SDO_DialogMsg!=NULL)
		theApp.SDO_DialogMsg("", WM_CLOSE, 0, 0);//�ر�SDO���ӶԻ���
	if(theApp.WA_DialogMsg!=NULL)
		theApp.WA_DialogMsg("",WM_CLOSE,0,0);//�ر�WA���ӶԻ���
	if(theApp.XD_DialogMsg!=NULL)
		theApp.XD_DialogMsg("",WM_CLOSE,0,0);//�ر�XD���ӶԻ���
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
	theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),length);//�������ӷ�����������
	socketdata.Destroy();

	return false;
}
//��̬�ж�dll,��ȡ���ص�dll�ļ��Ƿ����
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
