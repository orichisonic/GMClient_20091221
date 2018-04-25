// M_XD.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "M_XD.h"
#include "OperationXD.h"
#include "XDUserInfor.h"
#include "KickPlayer.h"
#include "BanPlayer.h"
#include "Notice.h"
#include "XDItemInfo.h"
#include "XDMailInfo.h"
#include "XDAuctionInfo.h"
#include "XDLoginLog.h"
#include "XDItemShop.h"
#include "XDItemLog.h"
#include "XDMailLog.h"
#include "XDMCashLog.h"
#include "XDCharLog.h"
#include "XDUserManage.h"
#include "XDItemManage.h"
#include "XDGuildInfo.h"
#include "XDQuestInfo.h"
#include "XDCarDetail.h"
#include "XDUserGuild.h"
#include "XDGuildLog.h"
#include "XDNPCItemInfo.h"
#include "XDBanList.h"
#include "XDGuildManage.h"
#include "XDGMManage.h"

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

// CM_XDApp

BEGIN_MESSAGE_MAP(CM_XDApp, CWinApp)
END_MESSAGE_MAP()


// CM_XDApp 构造

CM_XDApp::CM_XDApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CM_XDApp 对象

CM_XDApp theApp;
XDUserInfor userInfo;
CKickPlayer kickPlayer;
CBanPlayer banPlayer;
CNotice noticeInfo;
CXDItemInfo iteminfo;
CXDMailInfo mailinfo;
CXDAuctionInfo auctioninfo;
CXDLoginLog loginlog;
CXDItemShop itemshop;
CXDItemLog itemlog;
CXDMailLog maillog;
CXDMCashLog mcashlog;
CXDCharLog charlog;
CXDUserManage usermanage;
CXDItemManage itemmanage;
CXDGuildInfo guildinfo;
CXDQuestInfo questinfo;
CXDCarDetail cardetail;
CXDUserGuild userguild;
CXDGuildLog guildlog;
CXDNPCItemInfo npciteminfo;
CXDBanList banlist;
CXDGuildManage guildmanage;
CXDGMManage gmmanage;

// CM_XDApp 初始化

BOOL CM_XDApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" __declspec(dllexport) BOOL XD_TRANSLATEMESSAGE(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if((pMsg->wParam == 'C') || (pMsg->wParam == 'A'))
			{
				if(userInfo.m_hWnd != NULL)
				{
					userInfo.PreTranslateMessage(pMsg);
				}
				if(kickPlayer.m_hWnd != NULL)
				{
					kickPlayer.PreTranslateMessage(pMsg);
				}
				if(banPlayer.m_hWnd != NULL)
				{
					banPlayer.PreTranslateMessage(pMsg);
				}
				if(noticeInfo.m_hWnd != NULL)
				{
					noticeInfo.PreTranslateMessage(pMsg);
				}
				if(iteminfo.m_hWnd != NULL)
				{
					iteminfo.PreTranslateMessage(pMsg);
				}
				if(mailinfo.m_hWnd != NULL)
				{
					mailinfo.PreTranslateMessage(pMsg);
				}
				if(auctioninfo.m_hWnd != NULL)
				{
					auctioninfo.PreTranslateMessage(pMsg);
				}
				if(loginlog.m_hWnd!=NULL)
				{
					loginlog.PreTranslateMessage(pMsg);
				}
				if(itemshop.m_hWnd != NULL)
				{
					itemshop.PreTranslateMessage(pMsg);
				}
				if(itemlog.m_hWnd != NULL)
				{
					itemlog.PreTranslateMessage(pMsg);
				}
				if(maillog.m_hWnd != NULL)
				{
					maillog.PreTranslateMessage(pMsg);
				}
				if(mcashlog.m_hWnd != NULL)
				{
					mcashlog.PreTranslateMessage(pMsg);
				}
				if(charlog.m_hWnd != NULL)
				{
					charlog.PreTranslateMessage(pMsg);
				}
				if(usermanage.m_hWnd != NULL)
				{
					usermanage.PreTranslateMessage(pMsg);
				}
				if(itemmanage.m_hWnd != NULL)
				{
					itemmanage.PreTranslateMessage(pMsg);
				}
				if(guildinfo.m_hWnd != NULL)
				{
					guildinfo.PreTranslateMessage(pMsg);
				}
				if(questinfo.m_hWnd != NULL)
				{
					questinfo.PreTranslateMessage(pMsg);
				}
				if(cardetail.m_hWnd != NULL)
				{
					cardetail.PreTranslateMessage(pMsg);
				}
				if(userguild.m_hWnd != NULL)
				{
					userguild.PreTranslateMessage(pMsg);
				}
				if(guildlog.m_hWnd != NULL)
				{
					guildlog.PreTranslateMessage(pMsg);
				}
				if(npciteminfo.m_hWnd != NULL)
				{
					npciteminfo.PreTranslateMessage(pMsg);
				}
				if(banlist.m_hWnd != NULL)
				{
					banlist.PreTranslateMessage(pMsg);
				}
				if(guildmanage.m_hWnd != NULL)
				{
					guildmanage.PreTranslateMessage(pMsg);
				}
				if(gmmanage.m_hWnd != NULL)
				{
					gmmanage.PreTranslateMessage(pMsg);
				}
			}
		}		
	}
	return FALSE;
}

//选择打开不同的子对话框
extern "C" __declspec(dllexport) bool XD_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDUserInfor")))//玩家帐号信息查询
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(userInfo.m_hWnd== NULL)
		{			
			userInfo.Create(IDD_DLGUSERINFO);			
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			userInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			userInfo.ShowWindow(SW_SHOWMAXIMIZED);
			userInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDKickPlayer")))//强制玩家下线
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(kickPlayer.m_hWnd== NULL)
		{
			kickPlayer.Create(IDD_DLGKICKPLAYER);		
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			kickPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			kickPlayer.ShowWindow(SW_SHOWMAXIMIZED);
			kickPlayer.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDBanPlayer")))//玩家账号解/封停
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(banPlayer.m_hWnd== NULL)
		{
			banPlayer.Create(IDD_DLGBANPLAYER);		
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			banPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			banPlayer.ShowWindow(SW_SHOWMAXIMIZED);
			banPlayer.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDNoticeInfo")))//公告管理
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(noticeInfo.m_hWnd== NULL)
		{
			noticeInfo.Create(IDD_DLGNOTICE);		
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			noticeInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			noticeInfo.ShowWindow(SW_SHOWMAXIMIZED);
			noticeInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemInfo")))//玩家物品信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(iteminfo.m_hWnd== NULL)
		{
			iteminfo.Create(IDD_DLGITEMINFO);		
			::SetParent(iteminfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			iteminfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			iteminfo.ShowWindow(SW_SHOWMAXIMIZED);
			iteminfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMailInfo")))//邮件信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(mailinfo.m_hWnd== NULL)
		{
			mailinfo.Create(IDD_DLGMAILINFO);		
			::SetParent(mailinfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			mailinfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			mailinfo.ShowWindow(SW_SHOWMAXIMIZED);
			mailinfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDAuctionInfo")))//拍卖行信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(auctioninfo.m_hWnd== NULL)
		{
			auctioninfo.Create(IDD_DLGAUCTIONINFO);		
			::SetParent(auctioninfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			auctioninfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			auctioninfo.ShowWindow(SW_SHOWMAXIMIZED);
			auctioninfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDLoginLog")))//玩家登录日志
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(loginlog.m_hWnd== NULL)
		{
			loginlog.Create(IDD_DLGLOGINLOG);		
			::SetParent(loginlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			loginlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			loginlog.ShowWindow(SW_SHOWMAXIMIZED);
			loginlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemShop")))//商城物品购买日志
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(itemshop.m_hWnd== NULL)
		{
			itemshop.Create(IDD_DLGITEMSHOP);		
			::SetParent(itemshop.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			itemshop.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			itemshop.ShowWindow(SW_SHOWMAXIMIZED);
			itemshop.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemLog")))//玩家物品日志
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(itemlog.m_hWnd== NULL)
		{
			itemlog.Create(IDD_DLGITEMLOG);		
			::SetParent(itemlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			itemlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			itemlog.ShowWindow(SW_SHOWMAXIMIZED);
			itemlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMailLog")))//玩家邮件日志
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(maillog.m_hWnd== NULL)
		{
			maillog.Create(IDD_DLGMAILLOG);		
			::SetParent(maillog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			maillog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			maillog.ShowWindow(SW_SHOWMAXIMIZED);
			maillog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMCashLog")))//M币使用日志
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(mcashlog.m_hWnd== NULL)
		{
			mcashlog.Create(IDD_DLGMCASHLOG);		
			::SetParent(mcashlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			mcashlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			mcashlog.ShowWindow(SW_SHOWMAXIMIZED);
			mcashlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDCharLog")))//玩家角色日志
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(charlog.m_hWnd== NULL)
		{
			charlog.Create(IDD_DLGCHARLOG);		
			::SetParent(charlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			charlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			charlog.ShowWindow(SW_SHOWMAXIMIZED);
			charlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDUserManage")))//玩家角色管理
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(usermanage.m_hWnd== NULL)
		{
			usermanage.Create(IDD_DLGUSERMANAGE);		
			::SetParent(usermanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			usermanage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			usermanage.ShowWindow(SW_SHOWMAXIMIZED);
			usermanage.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemManage")))//玩家道具管理
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(itemmanage.m_hWnd== NULL)
		{
			itemmanage.Create(IDD_DLGITEMMANAGE);		
			::SetParent(itemmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			itemmanage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			itemmanage.ShowWindow(SW_SHOWMAXIMIZED);
			itemmanage.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildInfo")))//公会信息查询
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(guildinfo.m_hWnd== NULL)
		{
			guildinfo.Create(IDD_DLGGUILDINFO);		
			::SetParent(guildinfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			guildinfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			guildinfo.ShowWindow(SW_SHOWMAXIMIZED);
			guildinfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDQuestInfo")))//玩家任务查询
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(questinfo.m_hWnd== NULL)
		{
			questinfo.Create(IDD_DLGQUESTINFO);		
			::SetParent(questinfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			questinfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			questinfo.ShowWindow(SW_SHOWMAXIMIZED);
			questinfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDCarDetail")))//金刚车辆信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(cardetail.m_hWnd== NULL)
		{
			cardetail.Create(IDD_DLGCARDETAIL);		
			::SetParent(cardetail.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			cardetail.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			cardetail.ShowWindow(SW_SHOWMAXIMIZED);
			cardetail.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDUserGuild")))//玩家公会信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(userguild.m_hWnd== NULL)
		{
			userguild.Create(IDD_DLGUSERGUILD);		
			::SetParent(userguild.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			userguild.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			userguild.ShowWindow(SW_SHOWMAXIMIZED);
			userguild.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildLog")))//公会日志
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(guildlog.m_hWnd== NULL)
		{
			guildlog.Create(IDD_DLGGUILDLOG);		
			::SetParent(guildlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			guildlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			guildlog.ShowWindow(SW_SHOWMAXIMIZED);
			guildlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDNPCItemInfo")))//NPC道具领取查询
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(npciteminfo.m_hWnd== NULL)
		{
			npciteminfo.Create(IDD_DLGGETNPCITEM);		
			::SetParent(npciteminfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			npciteminfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			npciteminfo.ShowWindow(SW_SHOWMAXIMIZED);
			npciteminfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDBanList")))//封停信息查询
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(banlist.m_hWnd== NULL)
		{
			banlist.Create(IDD_DLGBANLIST);		
			::SetParent(banlist.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			banlist.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			banlist.ShowWindow(SW_SHOWMAXIMIZED);
			banlist.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildManage")))//公会管理
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(guildmanage.m_hWnd== NULL)
		{
			guildmanage.Create(IDD_DLGGUILDMANAGE);		
			::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			guildmanage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			guildmanage.ShowWindow(SW_SHOWMAXIMIZED);
			guildmanage.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGMManage")))//GMTools操作
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(gmmanage.m_hWnd== NULL)
		{
			gmmanage.Create(IDD_DLGGMMANAGE);		
			::SetParent(gmmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			gmmanage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			gmmanage.ShowWindow(SW_SHOWMAXIMIZED);
			gmmanage.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	return false;
}
//选择显示不同的子对话框
extern "C" __declspec(dllexport) BOOL XD_SHOWDIALOG(CString m_MenuName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDUserInfor")))//查询用户信息
	{		
		if(userInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}		
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDKickPlayer")))//强制玩家下线
	{
		if(kickPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(kickPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDBanPlayer")))//玩家帐号解封停
	{
		if(banPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(banPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDNoticeInfo")))//公告信息
	{
		if(noticeInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(noticeInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemInfo")))//玩家物品信息
	{
		if(iteminfo.m_hWnd!=NULL)
		{
			::SetWindowPos(iteminfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMailInfo")))//邮件信息
	{
		if(mailinfo.m_hWnd!=NULL)
		{
			::SetWindowPos(mailinfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDAuctionInfo")))//拍卖行信息
	{
		if(auctioninfo.m_hWnd!=NULL)
		{
			::SetWindowPos(auctioninfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDLoginLog")))//玩家登录日志
	{
		if(loginlog.m_hWnd!=NULL)
		{
			::SetWindowPos(loginlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemShop")))//商城物品购买日志
	{
		if(itemshop.m_hWnd!=NULL)
		{
			::SetWindowPos(itemshop.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemLog")))//玩家物品日志
	{
		if(itemlog.m_hWnd!=NULL)
		{
			::SetWindowPos(itemlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMailLog")))//玩家邮件日志
	{
		if(maillog.m_hWnd!=NULL)
		{
			::SetWindowPos(maillog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMCashLog")))//M币使用日志
	{
		if(mcashlog.m_hWnd!=NULL)
		{
			::SetWindowPos(mcashlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDCharLog")))//玩家角色日志
	{
		if(charlog.m_hWnd!=NULL)
		{
			::SetWindowPos(charlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDUserManage")))//玩家角色管理
	{
		if(usermanage.m_hWnd!=NULL)
		{
			::SetWindowPos(usermanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemManage")))//玩家道具管理
	{
		if(itemmanage.m_hWnd!=NULL)
		{
			::SetWindowPos(itemmanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildInfo")))//公会信息查询
	{
		if(guildinfo.m_hWnd!=NULL)
		{
			::SetWindowPos(guildinfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDQuestInfo")))//玩家任务查询
	{
		if(questinfo.m_hWnd!=NULL)
		{
			::SetWindowPos(questinfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDCarDetail")))//金刚车辆信息
	{
		if(cardetail.m_hWnd!=NULL)
		{
			::SetWindowPos(cardetail.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDUserGuild")))//玩家公会信息
	{
		if(userguild.m_hWnd!=NULL)
		{
			::SetWindowPos(userguild.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildLog")))//公会日志
	{
		if(guildlog.m_hWnd!=NULL)
		{
			::SetWindowPos(guildlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDNPCItemInfo")))//NPC道具领取查询
	{
		if(npciteminfo.m_hWnd!=NULL)
		{
			::SetWindowPos(npciteminfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDBanList")))//封停信息查询
	{
		if(banlist.m_hWnd!=NULL)
		{
			::SetWindowPos(banlist.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildManage")))//公会管理
	{
		if(guildmanage.m_hWnd!=NULL)
		{
			::SetWindowPos(guildmanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGMManage")))//GMTools操作
	{
		if(gmmanage.m_hWnd!=NULL)
		{
			::SetWindowPos(gmmanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	return FALSE;
}

//再次发送同样的Query
extern "C" __declspec(dllexport) void XD_SENDINFOAGAIN()
{
	theApp.operXD.SendSameQuery();
}

/////////////////////////////////初始化基本信息
extern "C" __declspec(dllexport) void GETXDINFO(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent, int* m_SelectDll)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.UserByID = userByID;
	theApp.userName = userName;
	theApp.mHwndParent = m_HwndParent;
	theApp.operXD.initSocket(m_socket);
	theApp.operXD.intXD = m_SelectDll;
}

//选择给不同的子对话框发消息
extern "C" __declspec(dllexport) void XD_DIALOGMSG(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	CIni mIni;
	if(!strcmp("",m_MenuName))
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(iteminfo.m_hWnd != NULL)
		{
			::SetParent(iteminfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(iteminfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(mailinfo.m_hWnd != NULL)
		{
			::SetParent(mailinfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mailinfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(auctioninfo.m_hWnd != NULL)
		{
			::SetParent(auctioninfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(auctioninfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(loginlog.m_hWnd != NULL)
		{
			::SetParent(loginlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(loginlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(itemshop.m_hWnd != NULL)
		{
			::SetParent(itemshop.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemshop.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(itemlog.m_hWnd != NULL)
		{
			::SetParent(itemlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(maillog.m_hWnd != NULL)
		{
			::SetParent(maillog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(maillog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(mcashlog.m_hWnd != NULL)
		{
			::SetParent(mcashlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mcashlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(charlog.m_hWnd != NULL)
		{
			::SetParent(charlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(charlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(usermanage.m_hWnd != NULL)
		{
			::SetParent(usermanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(usermanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(itemmanage.m_hWnd != NULL)
		{
			::SetParent(itemmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemmanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(guildinfo.m_hWnd != NULL)
		{
			::SetParent(guildinfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildinfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(questinfo.m_hWnd != NULL)
		{
			::SetParent(questinfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(questinfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(cardetail.m_hWnd != NULL)
		{
			::SetParent(cardetail.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(cardetail.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(userguild.m_hWnd != NULL)
		{
			::SetParent(userguild.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userguild.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(guildlog.m_hWnd != NULL)
		{
			::SetParent(guildlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(npciteminfo.m_hWnd != NULL)
		{
			::SetParent(npciteminfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(npciteminfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(banlist.m_hWnd != NULL)
		{
			::SetParent(banlist.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banlist.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(guildmanage.m_hWnd != NULL)
		{
			::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildmanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(gmmanage.m_hWnd != NULL)
		{
			::SetParent(gmmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(gmmanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDUserInfor")))
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDKickPlayer")))////强制玩家下线
	{
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDBanPlayer")))//玩家账号解/封停
	{
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDNoticeInfo")))//公告管理
	{
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemInfo")))//玩家物品信息
	{
		if(iteminfo.m_hWnd != NULL)
		{
			::SetParent(iteminfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(iteminfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMailInfo")))//邮件信息
	{
		if(mailinfo.m_hWnd != NULL)
		{
			::SetParent(mailinfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mailinfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDAuctionInfo")))//拍卖行信息
	{
		if(auctioninfo.m_hWnd != NULL)
		{
			::SetParent(auctioninfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(auctioninfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDLoginLog")))//玩家登录日志
	{
		if(loginlog.m_hWnd != NULL)
		{
			::SetParent(loginlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(loginlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemShop")))//商城物品购买日志
	{
		if(itemshop.m_hWnd != NULL)
		{
			::SetParent(itemshop.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemshop.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemLog")))//玩家物品日志
	{
		if(itemlog.m_hWnd != NULL)
		{
			::SetParent(itemlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMailLog")))//玩家邮件日志
	{
		if(maillog.m_hWnd != NULL)
		{
			::SetParent(maillog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(maillog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMCashLog")))//M币使用日志
	{
		if(mcashlog.m_hWnd != NULL)
		{
			::SetParent(mcashlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mcashlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDCharLog")))//玩家角色日志
	{
		if(charlog.m_hWnd != NULL)
		{
			::SetParent(charlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(charlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDUserManage")))//玩家角色管理
	{
		if(usermanage.m_hWnd != NULL)
		{
			::SetParent(usermanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(usermanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemManage")))//玩家道具管理
	{
		if(itemmanage.m_hWnd != NULL)
		{
			::SetParent(itemmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemmanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildInfo")))//公会信息查询
	{
		if(guildinfo.m_hWnd != NULL)
		{
			::SetParent(guildinfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildinfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDQuestInfo")))//玩家任务查询
	{
		if(questinfo.m_hWnd != NULL)
		{
			::SetParent(questinfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(questinfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDCarDetail")))//金刚车辆信息
	{
		if(cardetail.m_hWnd != NULL)
		{
			::SetParent(cardetail.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(cardetail.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDUserGuild")))//玩家公会信息
	{
		if(userguild.m_hWnd != NULL)
		{
			::SetParent(userguild.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userguild.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildLog")))//公会日志
	{
		if(guildlog.m_hWnd != NULL)
		{
			::SetParent(guildlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDNPCItemInfo")))//NPC道具领取查询
	{
		if(npciteminfo.m_hWnd != NULL)
		{
			::SetParent(npciteminfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(npciteminfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDBanList")))//封停信息查询
	{
		if(banlist.m_hWnd != NULL)
		{
			::SetParent(banlist.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banlist.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildManage")))//公会管理
	{
		if(guildmanage.m_hWnd != NULL)
		{
			::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildmanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGMManage")))//GMTools操作
	{
		if(gmmanage.m_hWnd != NULL)
		{
			::SetParent(gmmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(gmmanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
}
extern "C" __declspec(dllexport) void GETXDMESSAGE(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.m_TagID = m_message_tag_id;
	OperationXD operXD;

	//////////////////////
	switch(m_message_tag_id)
	{	
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://服务器信息
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((noticeInfo.m_hWnd != NULL) && (noticeInfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((iteminfo.m_hWnd != NULL) && (iteminfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				iteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailinfo.m_hWnd != NULL) && (mailinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				mailinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((auctioninfo.m_hWnd != NULL) && (auctioninfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				auctioninfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((loginlog.m_hWnd != NULL) && (loginlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				loginlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemshop.m_hWnd != NULL) && (itemshop.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemshop.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemlog.m_hWnd != NULL) && (itemlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((maillog.m_hWnd != NULL) && (maillog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				maillog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mcashlog.m_hWnd != NULL) && (mcashlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				mcashlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((charlog.m_hWnd != NULL) && (charlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				charlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((usermanage.m_hWnd != NULL) && (usermanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				usermanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildinfo.m_hWnd != NULL) && (guildinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((questinfo.m_hWnd != NULL) && (questinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				questinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((cardetail.m_hWnd != NULL) && (cardetail.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				cardetail.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((userguild.m_hWnd != NULL) && (userguild.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				userguild.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildlog.m_hWnd != NULL) && (guildlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((npciteminfo.m_hWnd != NULL) && (npciteminfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				npciteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banlist.m_hWnd != NULL) && (banlist.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				banlist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((gmmanage.m_hWnd != NULL) && (gmmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				gmmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_Account_Query_Resp://取得角色基本资讯响应
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((iteminfo.m_hWnd != NULL) && (iteminfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				iteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((iteminfo.m_hWnd != NULL) && (iteminfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				iteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailinfo.m_hWnd != NULL) && (mailinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				mailinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((auctioninfo.m_hWnd != NULL) && (auctioninfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				auctioninfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((loginlog.m_hWnd != NULL) && (loginlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				loginlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemshop.m_hWnd != NULL) && (itemshop.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemshop.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemlog.m_hWnd != NULL) && (itemlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((maillog.m_hWnd != NULL) && (maillog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				maillog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mcashlog.m_hWnd != NULL) && (mcashlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				mcashlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((charlog.m_hWnd != NULL) && (charlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				charlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((usermanage.m_hWnd != NULL) && (usermanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				usermanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((questinfo.m_hWnd != NULL) && (questinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				questinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((cardetail.m_hWnd != NULL) && (cardetail.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				cardetail.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((userguild.m_hWnd != NULL) && (userguild.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				userguild.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((npciteminfo.m_hWnd != NULL) && (npciteminfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				npciteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((gmmanage.m_hWnd != NULL) && (gmmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				gmmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_KickPlayer_Resp://强制玩家下线
		{
			if(kickPlayer.m_hWnd != NULL)
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给强制玩家下线界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ClosePlayer_Resp://封停玩家帐号
	case CEnumCore::Message_Tag_ID::XDJG_OpenPlayer_Resp://解封玩家帐号	
		{
			if(banPlayer.m_hWnd != NULL)
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给玩家帐号解封停界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_CloseList_Resp://查询所有被封停帐号列表的回应
	case CEnumCore::Message_Tag_ID::XDJG_AccountIsClose_Query_Log_Resp://帐号是否封停
		{
			if(banPlayer.m_hWnd != NULL)
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给玩家帐号解封停界面发消息
			}
			else if(banlist.m_hWnd != NULL)
			{
				banlist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给封停信息查询页面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_BoardTasker_Add_Resp://公告添加响应
	case CEnumCore::Message_Tag_ID::XDJG_BoardTasker_Query_Resp://公告查询响应
	case CEnumCore::Message_Tag_ID::XDJG_BoardTasker_Update_Resp://公告更新响应
	case CEnumCore::Message_Tag_ID::XDJG_BoardTasker_Del_Resp://公告删除响应
		{
			if(noticeInfo.m_hWnd != NULL)
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给公告信息界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ItemBody_Query_Resp://身上物品信息
	case CEnumCore::Message_Tag_ID::XDJG_Itembackpack_Query_Resp://背包物品信息
	case CEnumCore::Message_Tag_ID::XDJG_ItemStorage_Query_Resp://仓库物品信息
	case CEnumCore::Message_Tag_ID::XDJG_GuildStorage_Query_Resp://公会仓库信息
	case CEnumCore::Message_Tag_ID::XDJG_KingkongStorage_Query_Resp://金刚仓库信息
		{
			if((iteminfo.m_hWnd != NULL) && (iteminfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				iteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_MailInfo_Query_Resp://邮件信息
		{
			if((mailinfo.m_hWnd != NULL) && (mailinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				mailinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_AuctioneerInfo_Query_Resp://拍卖行信息
		{
			if((auctioninfo.m_hWnd != NULL) && (auctioninfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				auctioninfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_Login_Log_Resp://玩家登录日志
		{
			if((loginlog.m_hWnd != NULL) && (loginlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				loginlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_Shoping_Log_Resp://商城物品购买日志
		{
			if((itemshop.m_hWnd != NULL) && (itemshop.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemshop.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_TransGain_Log_Resp://交易获得
	case CEnumCore::Message_Tag_ID::XDJG_TransLose_Log_Resp://交易失去
	case CEnumCore::Message_Tag_ID::XDJG_BuyFromNpc_Log_Resp://从NPC处购买
	case CEnumCore::Message_Tag_ID::XDJG_SaleToNpc_Log_Resp://卖给NPC
	case CEnumCore::Message_Tag_ID::XDJG_PickUpItem_Log_Resp://拾取物品
	case CEnumCore::Message_Tag_ID::XDJG_DiscardItem_Log_Resp://丢弃物品
	case CEnumCore::Message_Tag_ID::XDJG_ConsumeItem_Log_Resp://物品消耗
	case CEnumCore::Message_Tag_ID::XDJG_AuctioneerSaled_Log_Resp://拍卖行卖出
	case CEnumCore::Message_Tag_ID::XDJG_AuctioneerBought_Log_Resp://拍卖行购入	
	case CEnumCore::Message_Tag_ID::XDJG_EquipIncrease_Log_Resp://装备增幅日志
	case CEnumCore::Message_Tag_ID::XDJG_Synthesis_Log_Resp://插片合成日志
	case CEnumCore::Message_Tag_ID::XDJG_EquipTransfer_Log_Resp://装备传导日志
	case CEnumCore::Message_Tag_ID::XDJG_ItemIdentify_Log_Resp://物品鉴定
	case CEnumCore::Message_Tag_ID::XDJG_RoleStore_Log_Resp://个人仓库存放日志
	case CEnumCore::Message_Tag_ID::XDJG_GuildStore_Log_Resp://公会仓库存放日志
		{
			if((itemlog.m_hWnd != NULL) && (itemlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ItemAttribute_Query_Resp://物品属性查询
	{
			if((itemlog.m_hWnd != NULL) && (itemlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailinfo.m_hWnd != NULL) && (mailinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				mailinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((maillog.m_hWnd != NULL) && (maillog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				maillog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_SendMail_Log_Resp://发送邮件
	case CEnumCore::Message_Tag_ID::XDJG_ReceiveMail_Log_Resp://收取邮件
		{
			if((maillog.m_hWnd != NULL) && (maillog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				maillog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ExpansionPack_Log_Resp://背包扩充续费记录
	case CEnumCore::Message_Tag_ID::XDJG_Deliver_Log_Resp://传送日志
	case CEnumCore::Message_Tag_ID::XDJG_ExpansionWarehouse_Log_Resp://角色仓库扩充续费记录
		{
			if((mcashlog.m_hWnd != NULL) && (mcashlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				mcashlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_RoleUpgrade_Log_Resp://角色升级
	case CEnumCore::Message_Tag_ID::XDJG_RoleCreate_Log_Resp://角色创建
	case CEnumCore::Message_Tag_ID::XDJG_RoleSkill_Log_Resp://角色技能学习
	case CEnumCore::Message_Tag_ID::XDJG_ReceiveTask_Log_Resp://领取任务
	case CEnumCore::Message_Tag_ID::XDJG_CompleteTask_Log_Resp://完成任务
	case CEnumCore::Message_Tag_ID::XDJG_Copy_Log_Resp://副本查询
		{
			if((charlog.m_hWnd != NULL) && (charlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				charlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_RoleSkillAdd_Resp://角色技能添加
	case CEnumCore::Message_Tag_ID::XDJG_RoleSkillDel_Resp://角色技能删除
	case CEnumCore::Message_Tag_ID::XDJG_ModifyLevel_operate_Resp://修改等级
	case CEnumCore::Message_Tag_ID::XDJG_ModifyPwd_operate_Resp://修改密码
	case CEnumCore::Message_Tag_ID::XDJG_ResumePwd_operate_Resp://临时密码恢复
	case CEnumCore::Message_Tag_ID::XDJG_ResumeRole_operate_Resp://角色恢复
	case CEnumCore::Message_Tag_ID::XDJG_DeleteRole_operate_Resp://角色删除
	case CEnumCore::Message_Tag_ID::XDJG_RoleSkills_Query_Resp://角色技能信息查询
	case CEnumCore::Message_Tag_ID::XDJG_SkillList_Query_Resp://技能列表查询
	case CEnumCore::Message_Tag_ID::XDJG_TitleList_Query_Resp://称号列表查询
	case CEnumCore::Message_Tag_ID::XDJG_AddTitle_Query_Resp://添加称号
	case CEnumCore::Message_Tag_ID::XDJG_RemoveTitle_Query_Resp://移除称号
		{
			if((usermanage.m_hWnd != NULL) && (usermanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				usermanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ItemAdd_Resp://道具添加
	case CEnumCore::Message_Tag_ID::XDJG_ItemDel_Resp://道具删除
	case CEnumCore::Message_Tag_ID::XDJG_MoneyAdd_Resp://添加游戏币
	case CEnumCore::Message_Tag_ID::XDJG_AddRoleBind_operate_Resp://添加角色身上金钱数量(绑定币)
	case CEnumCore::Message_Tag_ID::XDJG_AddRoleNonBind_operate_Resp://添加角色身上金钱数量(非绑定币)
	case CEnumCore::Message_Tag_ID::XDJG_UpRoleBind_operate_Resp://修改角色身上金钱数量(绑定币)
	case CEnumCore::Message_Tag_ID::XDJG_UpRoleNonBind_operate_Resp://修改角色身上金钱数量(非绑定币)
	case CEnumCore::Message_Tag_ID::XDJG_ItemType_Query_Resp://道具类型查询
	case CEnumCore::Message_Tag_ID::XDJG_ItemNameLst_Query_Resp://相应类型的道具列表查询
		{
			if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_GuildBaseInfo_Query_Resp://公会基本信息	
		{
			if((guildinfo.m_hWnd != NULL) && (guildinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildlog.m_hWnd != NULL) && (guildlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_GuildMemberList_Query_Resp://公会成员列表
		{
			if((guildinfo.m_hWnd != NULL) && (guildinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_PlayerTaskInfo_Query_Resp://玩家任务查询
		{
			if((questinfo.m_hWnd != NULL) && (questinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				questinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_CarBaseInfo_Query_Resp://金刚车辆基本信息
	case CEnumCore::Message_Tag_ID::XDJG_CarDetailInfo_Query_Resp://金刚车辆详细信息
		{
			if((cardetail.m_hWnd != NULL) && (cardetail.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				cardetail.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_PlayerGuildBaseInfo_Query_Resp://玩家公会基本信息
	case CEnumCore::Message_Tag_ID::XDJG_PlayerGuildItemInfo_Query_Resp://玩家公会物品信息
		{
			if((userguild.m_hWnd != NULL) && (userguild.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				userguild.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_GuildCreate_Log_Resp://公会成立
	case CEnumCore::Message_Tag_ID::XDJG_GuildDismiss_Log_Resp://公会解散
	case CEnumCore::Message_Tag_ID::XDJG_GuildAddMember_Log_Resp://公会添加成员
	case CEnumCore::Message_Tag_ID::XDJG_GuildMemberLeaved_Log_Resp://公会成员离开
	case CEnumCore::Message_Tag_ID::XDJG_GuildPostChanged_Log_Resp://公会职务变更
		{
			if((guildlog.m_hWnd != NULL) && (guildlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_NPCGetItem_Query_Resp://NPC道具领取查询
		{
			if((npciteminfo.m_hWnd != NULL) && (npciteminfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				npciteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_MoveToPosition_Query_Resp://移动到指定位置
	case CEnumCore::Message_Tag_ID::XDJG_MoveToRole_Query_Resp://移动到指定玩家身边
	case CEnumCore::Message_Tag_ID::XDJG_MoveToTargetRole_Query_Resp://移动到目标玩家身边
	case CEnumCore::Message_Tag_ID::XDJG_BuffList_Query_Resp://BUFF列表查询
	case CEnumCore::Message_Tag_ID::XDJG_AddBuff_Query_Resp://添加BUFF
	case CEnumCore::Message_Tag_ID::XDJG_RemoveBuff_Query_Resp://移除BUFF
		{
			if((gmmanage.m_hWnd != NULL) && (gmmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				gmmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	}
}

