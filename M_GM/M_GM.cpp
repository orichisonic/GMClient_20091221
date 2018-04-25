// M_GM.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "M_GM.h"
#include "ModiPwd.h"
#include "UserManage.h"
#include "GMOperationLog.h"
#include "GMGameAssist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	ע�⣡
//
//		����� DLL ��̬���ӵ� MFC
//		DLL���Ӵ� DLL ������
//		���� MFC ���κκ����ں�������ǰ��
//		��������� AFX_MANAGE_STATE �ꡣ
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CM_GMApp

BEGIN_MESSAGE_MAP(CM_GMApp, CWinApp)
END_MESSAGE_MAP()


// CM_GMApp ����

CM_GMApp::CM_GMApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CM_GMApp ����

CM_GMApp theApp;//CM_GMApp���ȫ�ֶ����������Ա�ഫ������

CModiPwd modiPwd;//�޸��������
CUserManage uerManage;//�û��������
CGMOperationLog GMOperLog;//GM������־
GMGameAssist gameassist;//��Ϸ�����Ϣ

// CM_GMApp ��ʼ��

BOOL CM_GMApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" __declspec(dllexport) BOOL GM_TRANSLATEMESSAGE(MSG* pMsg)
{	
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if((pMsg->wParam == 'C') || (pMsg->wParam == 'A'))
			{
				if(uerManage.m_hWnd != NULL)
				{
					uerManage.PreTranslateMessage(pMsg);
				}
				if(GMOperLog.m_hWnd != NULL)
				{
					GMOperLog.PreTranslateMessage(pMsg);
				}
				if(gameassist.m_hWnd != NULL)
				{
					gameassist.PreTranslateMessage(pMsg);
				}
			}
		}
	}
	return FALSE;
}

extern "C" __declspec(dllexport) HWND GM_CLIENT_MODIPWD()//������dll�����У��������CModiPwd��ľ��ָ��
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(modiPwd.m_hWnd == NULL)
	{
	    modiPwd.Create(IDD_DLGMODIPWD);//����CModiPwd��Ķ���
	    modiPwd.ShowWindow(SW_SHOWMAXIMIZED);//��ʾΪ���
	}

	return modiPwd.m_hWnd;

}
extern "C" __declspec(dllexport) HWND GM_CLIENT_USERMANAGE()//������dll�����У��������CUserManage��ľ��ָ��
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(uerManage.m_hWnd == NULL)
	{
	    uerManage.Create(IDD_DLGUSERMANAGE);//����CUserManage��Ķ���
	    uerManage.ShowWindow(SW_SHOWMAXIMIZED);//��ʾΪ���
	}

	return uerManage.m_hWnd;
}
extern "C" __declspec(dllexport) HWND GM_CLIENT_GMOPERLOG()//������dll�����У��������CGMOperationLog��ľ��ָ��
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(GMOperLog.m_hWnd == NULL)
	{
	    GMOperLog.Create(IDD_DLGGMLOG);//����CGMOperationLog��Ķ���
	    GMOperLog.ShowWindow(SW_SHOWMAXIMIZED);//��ʾΪ���
	}

	return GMOperLog.m_hWnd;
}

//������dll�����У����ݽ��յ��ķ�����Ϣ���������
extern "C" __declspec(dllexport) void GETFRAMEMESSAGE(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.m_tag_id=m_message_tag_id;
/*
	CString str;
	str.Format("m_message_tag_id: %x", m_message_tag_id);
	AfxMessageBox(str);
*/
	switch(m_message_tag_id)
	{	
	case CEnumCore::Message_Tag_ID::USER_QUERY_ALL_RESP://�û���ѯ
		{
			if((uerManage.m_hWnd != NULL) && (uerManage.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
			    uerManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��CUserManage��Ľ��淢��Ϣ
			}
			else if((GMOperLog.m_hWnd != NULL) && (GMOperLog.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
				GMOperLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��CGMOperationLog��Ľ��淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_CREATE_RESP://�û�����
	case CEnumCore::Message_Tag_ID::USER_DELETE_RESP://�û�ɾ��
	case CEnumCore::Message_Tag_ID::USER_UPDATE_RESP://�û��༭
	case CEnumCore::Message_Tag_ID::DEPART_QUERY_RESP://���Ų�ѯ
		{
			if((uerManage.m_hWnd != NULL)&& (uerManage.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
			    uerManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��CUserManage��Ľ��淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_PASSWD_MODIF_RESP://�޸�����
		{
			if((modiPwd.m_hWnd != NULL) && (modiPwd.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
			    modiPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��CUserManage��Ľ��淢��Ϣ
			}
			else if((theApp.modiUserPwd.m_hWnd != NULL) && (theApp.modiUserPwd.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
			    theApp.modiUserPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��CModiPwd��Ľ��淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_MODULE_QUERY_RESP://��ȡ�û�ģ���б�
	case CEnumCore::Message_Tag_ID::GAME_MODULE_QUERY_RESP://��ȡ��Ϸģ���б�
	case CEnumCore::Message_Tag_ID::USER_MODULE_UPDATE_RESP://���û�����Ȩ��
		{
			theApp.popedomManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��CPopedomManage��Ľ��淢��Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::GMTOOLS_OperateLog_Query_RESP://��ѯGM������־��Ϣ��Ӧ
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_ALL_QUERY_RESP://��ѯ������Ϸ����
		{
			if((GMOperLog.m_hWnd != NULL) && (GMOperLog.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
				GMOperLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��CGMOperationLog��Ľ��淢��Ϣ
			}
		}		
		break;
	case CEnumCore::Message_Tag_ID::GAME_QUERY_RESP://��ѯ��Ϸ��Ϣ�Ļ�Ӧ	
		{
			if((GMOperLog.m_hWnd != NULL) && (GMOperLog.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
				GMOperLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��CGMOperationLog��Ľ��淢��Ϣ
			}
			else if((gameassist.m_hWnd != NULL) && (gameassist.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
				gameassist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GMTOOLS_USERMAC_UPDATE_RESP://�����û�Mac
		{
			theApp.updateUserMac.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��CGMOperationLog��Ľ��淢��Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��ѯ��Ϸ����
	case CEnumCore::Message_Tag_ID::WA_KickPlayer_Resp://ǿ���������
	case CEnumCore::Message_Tag_ID::WA_ClosePlayer_Resp://��ͣ�û�
	case CEnumCore::Message_Tag_ID::HARMFUL_PROC_QUERY_RESP://��ҽ��̹��߰�
		{
			//gameassist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��GMGameAssist��Ľ��淢��Ϣ
			if((gameassist.m_hWnd != NULL) && (gameassist.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
				gameassist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GM_AccountInfo_Resp://��ѯ�Ƿ�vip�ʺ�
		{
			if((gameassist.m_hWnd != NULL) && (gameassist.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
				gameassist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GM_ClosePlayerGroup_Resp_WA://������ͣ�ʺ�(WA��ʿ��˫)
		{
			if((gameassist.m_hWnd != NULL) && (gameassist.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
				gameassist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	default:
		break;
	}
}

//ѡ��򿪲�ͬ���ӶԻ���
extern "C" __declspec(dllexport) bool GM_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","UserSelfEditPwd")))//ѡ�����޸�����
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(modiPwd.m_hWnd == NULL)
		{
			modiPwd.Create(IDD_DLGMODIPWD);
			modiPwd.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(modiPwd.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(modiPwd.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","AccountList")))//ѡ�����û�����
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(uerManage.m_hWnd == NULL)
		{
			uerManage.Create(IDD_DLGUSERMANAGE);
			uerManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(uerManage.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(uerManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmOperatorLog")))///ѡ����GM������־
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(GMOperLog.m_hWnd == NULL)
		{
			GMOperLog.Create(IDD_DLGGMLOG);
			GMOperLog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(GMOperLog.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(GMOperLog.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGMGameAssit")))///��Ϸ�����Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(gameassist.m_hWnd == NULL)
		{
			gameassist.Create(IDD_DLGGAMEASSIST);
			gameassist.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(gameassist.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(gameassist.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	return false;
}

//ѡ����ʾ��ͬ���ӶԻ���
extern "C" __declspec(dllexport) BOOL GM_SHOWDIALOG(CString m_MenuName)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","UserSelfEditPwd")))//ѡ�����޸�����
	{
		if(modiPwd.m_hWnd!=NULL)
		{
			::SetWindowPos(modiPwd.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","AccountList")))//ѡ�����û�����
	{
		if(uerManage.m_hWnd!=NULL)
		{
			::SetWindowPos(uerManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmOperatorLog")))///ѡ����GM������־
	{
		if(GMOperLog.m_hWnd!=NULL)
		{
			::SetWindowPos(GMOperLog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGMGameAssit")))///��Ϸ�����Ϣ
	{
		if(gameassist.m_hWnd!=NULL)
		{
			::SetWindowPos(gameassist.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	return FALSE;
}

//ѡ�����ͬ���ӶԻ�����Ϣ
extern "C" __declspec(dllexport) void GM_DIALOGMSG(CString m_DlgName, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	CIni mIni;
	if(!strcmp("",m_DlgName))
	{
		if(modiPwd.m_hWnd != NULL)
		{
			::SetParent(modiPwd.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(modiPwd.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(uerManage.m_hWnd != NULL)
		{
			::SetParent(uerManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(uerManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(GMOperLog.m_hWnd != NULL)
		{
			::SetParent(GMOperLog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(GMOperLog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(theApp.popedomManage.m_hWnd != NULL)
		{
			::SendMessage(theApp.popedomManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(theApp.modiUserPwd.m_hWnd != NULL)
		{
			::SendMessage(theApp.modiUserPwd.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(theApp.updateUserMac.m_hWnd != NULL)
		{
			::SendMessage(theApp.updateUserMac.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(gameassist.m_hWnd != NULL)
		{
			::SendMessage(gameassist.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_DlgName,mIni.ReadValue("Global","UserSelfEditPwd")))//ѡ�����޸�����
	{
		if(modiPwd.m_hWnd != NULL)
		{
			::SetParent(modiPwd.m_hWnd,theApp.mHwndParent);//���о��������
		    ::SendMessage(modiPwd.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_DlgName,mIni.ReadValue("Global","AccountList")))//ѡ�����û�����
	{
		if(uerManage.m_hWnd != NULL)
		{
			::SetParent(uerManage.m_hWnd,theApp.mHwndParent);//���о��������
		    ::SendMessage(uerManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_DlgName,mIni.ReadValue("Global","FrmOperatorLog")))///ѡ����GM������־
	{
		if(GMOperLog.m_hWnd != NULL)
		{
			::SetParent(GMOperLog.m_hWnd,theApp.mHwndParent);//���о��������
		    ::SendMessage(GMOperLog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_DlgName,mIni.ReadValue("Global","CGMGameAssit")))///��Ϸ�����Ϣ
	{
		if(gameassist.m_hWnd != NULL)
		{
			::SetParent(gameassist.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(gameassist.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
}

//�ٴη���ͬ����Query
extern "C" __declspec(dllexport) void GM_SENDINFOAGAIN()
{
	theApp.operGM.SendSameQuery();
}

//��ʼ����Ϣ
extern "C" __declspec(dllexport) void GETINFO(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent, int* m_SelectDll)//������dll�����У�����ȫ����Ϣ���������
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	theApp.UserByID = userByID;//����ԱID
	theApp.userName = userName;//����Ա����
	theApp.mHwndParent = m_HwndParent;
	theApp.operGM.initSocket(m_socket);
	theApp.operGM.intGM = m_SelectDll;
}
