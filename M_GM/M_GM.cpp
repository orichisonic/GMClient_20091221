// M_GM.cpp : 定义 DLL 的初始化例程。
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
//	注意！
//
//		如果此 DLL 动态链接到 MFC
//		DLL，从此 DLL 导出并
//		调入 MFC 的任何函数在函数的最前面
//		都必须添加 AFX_MANAGE_STATE 宏。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CM_GMApp

BEGIN_MESSAGE_MAP(CM_GMApp, CWinApp)
END_MESSAGE_MAP()


// CM_GMApp 构造

CM_GMApp::CM_GMApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CM_GMApp 对象

CM_GMApp theApp;//CM_GMApp类的全局对象，用于向成员类传递数据

CModiPwd modiPwd;//修改密码的类
CUserManage uerManage;//用户管理的类
CGMOperationLog GMOperLog;//GM操作日志
GMGameAssist gameassist;//游戏外挂信息

// CM_GMApp 初始化

BOOL CM_GMApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" __declspec(dllexport) BOOL GM_TRANSLATEMESSAGE(MSG* pMsg)
{	
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
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

extern "C" __declspec(dllexport) HWND GM_CLIENT_MODIPWD()//在整个dll工程中，用于输出CModiPwd类的句柄指针
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(modiPwd.m_hWnd == NULL)
	{
	    modiPwd.Create(IDD_DLGMODIPWD);//创建CModiPwd类的对象
	    modiPwd.ShowWindow(SW_SHOWMAXIMIZED);//显示为最大化
	}

	return modiPwd.m_hWnd;

}
extern "C" __declspec(dllexport) HWND GM_CLIENT_USERMANAGE()//在整个dll工程中，用于输出CUserManage类的句柄指针
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(uerManage.m_hWnd == NULL)
	{
	    uerManage.Create(IDD_DLGUSERMANAGE);//创建CUserManage类的对象
	    uerManage.ShowWindow(SW_SHOWMAXIMIZED);//显示为最大化
	}

	return uerManage.m_hWnd;
}
extern "C" __declspec(dllexport) HWND GM_CLIENT_GMOPERLOG()//在整个dll工程中，用于输出CGMOperationLog类的句柄指针
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(GMOperLog.m_hWnd == NULL)
	{
	    GMOperLog.Create(IDD_DLGGMLOG);//创建CGMOperationLog类的对象
	    GMOperLog.ShowWindow(SW_SHOWMAXIMIZED);//显示为最大化
	}

	return GMOperLog.m_hWnd;
}

//在整个dll工程中，传递接收到的返回信息的输出函数
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
	case CEnumCore::Message_Tag_ID::USER_QUERY_ALL_RESP://用户查询
		{
			if((uerManage.m_hWnd != NULL) && (uerManage.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
			    uerManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给CUserManage类的界面发消息
			}
			else if((GMOperLog.m_hWnd != NULL) && (GMOperLog.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
				GMOperLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给CGMOperationLog类的界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_CREATE_RESP://用户创建
	case CEnumCore::Message_Tag_ID::USER_DELETE_RESP://用户删除
	case CEnumCore::Message_Tag_ID::USER_UPDATE_RESP://用户编辑
	case CEnumCore::Message_Tag_ID::DEPART_QUERY_RESP://部门查询
		{
			if((uerManage.m_hWnd != NULL)&& (uerManage.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
			    uerManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给CUserManage类的界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_PASSWD_MODIF_RESP://修改密码
		{
			if((modiPwd.m_hWnd != NULL) && (modiPwd.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
			    modiPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给CUserManage类的界面发消息
			}
			else if((theApp.modiUserPwd.m_hWnd != NULL) && (theApp.modiUserPwd.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
			    theApp.modiUserPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给CModiPwd类的界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_MODULE_QUERY_RESP://获取用户模块列表
	case CEnumCore::Message_Tag_ID::GAME_MODULE_QUERY_RESP://获取游戏模块列表
	case CEnumCore::Message_Tag_ID::USER_MODULE_UPDATE_RESP://给用户分配权限
		{
			theApp.popedomManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给CPopedomManage类的界面发消息
		}
		break;
	case CEnumCore::Message_Tag_ID::GMTOOLS_OperateLog_Query_RESP://查询GM操作日志信息回应
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_ALL_QUERY_RESP://查询所有游戏大区
		{
			if((GMOperLog.m_hWnd != NULL) && (GMOperLog.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
				GMOperLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给CGMOperationLog类的界面发消息
			}
		}		
		break;
	case CEnumCore::Message_Tag_ID::GAME_QUERY_RESP://查询游戏信息的回应	
		{
			if((GMOperLog.m_hWnd != NULL) && (GMOperLog.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
				GMOperLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给CGMOperationLog类的界面发消息
			}
			else if((gameassist.m_hWnd != NULL) && (gameassist.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
				gameassist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GMTOOLS_USERMAC_UPDATE_RESP://重置用户Mac
		{
			theApp.updateUserMac.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给CGMOperationLog类的界面发消息
		}
		break;
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://查询游戏大区
	case CEnumCore::Message_Tag_ID::WA_KickPlayer_Resp://强制玩家下线
	case CEnumCore::Message_Tag_ID::WA_ClosePlayer_Resp://封停用户
	case CEnumCore::Message_Tag_ID::HARMFUL_PROC_QUERY_RESP://外挂进程工具包
		{
			//gameassist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给GMGameAssist类的界面发消息
			if((gameassist.m_hWnd != NULL) && (gameassist.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
				gameassist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GM_AccountInfo_Resp://查询是否vip帐号
		{
			if((gameassist.m_hWnd != NULL) && (gameassist.dlgStatus == theApp.operGM.ReadIntValue("MGM","Send")))
			{
				gameassist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GM_ClosePlayerGroup_Resp_WA://批量封停帐号(WA勇士无双)
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

//选择打开不同的子对话框
extern "C" __declspec(dllexport) bool GM_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","UserSelfEditPwd")))//选中了修改密码
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(modiPwd.m_hWnd == NULL)
		{
			modiPwd.Create(IDD_DLGMODIPWD);
			modiPwd.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(modiPwd.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(modiPwd.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","AccountList")))//选中了用户管理
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(uerManage.m_hWnd == NULL)
		{
			uerManage.Create(IDD_DLGUSERMANAGE);
			uerManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(uerManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(uerManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmOperatorLog")))///选中了GM操作日志
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(GMOperLog.m_hWnd == NULL)
		{
			GMOperLog.Create(IDD_DLGGMLOG);
			GMOperLog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(GMOperLog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(GMOperLog.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGMGameAssit")))///游戏外挂信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(gameassist.m_hWnd == NULL)
		{
			gameassist.Create(IDD_DLGGAMEASSIST);
			gameassist.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(gameassist.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(gameassist.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	return false;
}

//选择显示不同的子对话框
extern "C" __declspec(dllexport) BOOL GM_SHOWDIALOG(CString m_MenuName)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","UserSelfEditPwd")))//选中了修改密码
	{
		if(modiPwd.m_hWnd!=NULL)
		{
			::SetWindowPos(modiPwd.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","AccountList")))//选中了用户管理
	{
		if(uerManage.m_hWnd!=NULL)
		{
			::SetWindowPos(uerManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmOperatorLog")))///选中了GM操作日志
	{
		if(GMOperLog.m_hWnd!=NULL)
		{
			::SetWindowPos(GMOperLog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGMGameAssit")))///游戏外挂信息
	{
		if(gameassist.m_hWnd!=NULL)
		{
			::SetWindowPos(gameassist.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	return FALSE;
}

//选择给不同的子对话框发消息
extern "C" __declspec(dllexport) void GM_DIALOGMSG(CString m_DlgName, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	CIni mIni;
	if(!strcmp("",m_DlgName))
	{
		if(modiPwd.m_hWnd != NULL)
		{
			::SetParent(modiPwd.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(modiPwd.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(uerManage.m_hWnd != NULL)
		{
			::SetParent(uerManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(uerManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(GMOperLog.m_hWnd != NULL)
		{
			::SetParent(GMOperLog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(GMOperLog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(theApp.popedomManage.m_hWnd != NULL)
		{
			::SendMessage(theApp.popedomManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(theApp.modiUserPwd.m_hWnd != NULL)
		{
			::SendMessage(theApp.modiUserPwd.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(theApp.updateUserMac.m_hWnd != NULL)
		{
			::SendMessage(theApp.updateUserMac.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(gameassist.m_hWnd != NULL)
		{
			::SendMessage(gameassist.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_DlgName,mIni.ReadValue("Global","UserSelfEditPwd")))//选中了修改密码
	{
		if(modiPwd.m_hWnd != NULL)
		{
			::SetParent(modiPwd.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(modiPwd.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_DlgName,mIni.ReadValue("Global","AccountList")))//选中了用户管理
	{
		if(uerManage.m_hWnd != NULL)
		{
			::SetParent(uerManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(uerManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_DlgName,mIni.ReadValue("Global","FrmOperatorLog")))///选中了GM操作日志
	{
		if(GMOperLog.m_hWnd != NULL)
		{
			::SetParent(GMOperLog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(GMOperLog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_DlgName,mIni.ReadValue("Global","CGMGameAssit")))///游戏外挂信息
	{
		if(gameassist.m_hWnd != NULL)
		{
			::SetParent(gameassist.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(gameassist.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
}

//再次发送同样的Query
extern "C" __declspec(dllexport) void GM_SENDINFOAGAIN()
{
	theApp.operGM.SendSameQuery();
}

//初始化信息
extern "C" __declspec(dllexport) void GETINFO(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent, int* m_SelectDll)//在整个dll工程中，传递全局信息的输出函数
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	theApp.UserByID = userByID;//操作员ID
	theApp.userName = userName;//操作员名称
	theApp.mHwndParent = m_HwndParent;
	theApp.operGM.initSocket(m_socket);
	theApp.operGM.intGM = m_SelectDll;
}
