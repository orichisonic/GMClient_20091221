// M_WA.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "M_WA.h"
#include "OperationWA.h"
#include "WAUserInfor.h"
#include "KickPlayer.h"
#include "BanPlayer.h"
#include "Notice.h"
#include "CWADelItemInfo.h"
#include "MailInfor.h"
#include "PetInfor.h"
#include "AccountLog.h"
#include "goodsinfor.h"
#include "ChangeMoney.h"
#include "WAItemLog.h"
#include "WACashLog.h"
#include "WAQuestLog.h"
#include "WAMailLog.h"
#include "WAUserLog.h"
#include "WAItemShop.h"
#include "WAUserManage.h"
#include "WAItemManage.h"
#include "WABanList.h"
#include "WACharLog.h"
#include "WAGuildLog.h"
#include "WAPetLog.h"
#include "WAPlayerInfo.h"
#include "WAGuildInfo.h"
#include "WAPetManage.h"
#include "WAGuildManage.h"
#include "WAMailSend.h"

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

// CM_WAApp

BEGIN_MESSAGE_MAP(CM_WAApp, CWinApp)
END_MESSAGE_MAP()


// CM_WAApp 构造

CM_WAApp::CM_WAApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CM_WAApp 对象

CM_WAApp theApp;
WAUserInfor userInfo;
CKickPlayer kickPlayer;
CBanPlayer banPlayer;
CNotice noticeInfo;
PetInfor petinfor;
CWADelItemInfo deliteminfo;//删除道具
MailInfor mailinfor;//邮箱信息查询
CWAAccountLogin accountlogin;//用户登录信息
GoodsInfor goodsinfor;
ChangeMoney changemoney;
CWAItemLog itemlog;
CWACashLog cashlog;
CWAQuestLog questlog;
CWAMailLog maillog;
CWAUserLog userlog;
CWAItemShop itemshop;
CWAUserManage usermanage;
CWAItemManage itemmanage;
CWABanList banlist;
CWACharLog charlog;
CWAGuildLog guildlog;
CWAPetLog petlog;
CWAPlayerInfo playerinfo;
CWAGuildInfo guildinfo;
CWAPetManage petmanage;
CWAGuildManage guildmanage;
CWAMailSend mailsend;

// CM_WAApp 初始化

BOOL CM_WAApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
//选择打开不同的子对话框
extern "C" __declspec(dllexport) bool WA_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserInfor")))//玩家帐号信息查询
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
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAKickPlayer")))//强制玩家下线
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
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWABanPlayer")))//玩家账号解/封停
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
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWANoticeInfor")))//公告管理
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
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAToolsDel")))//道具删除
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(deliteminfo.m_hWnd== NULL)
		{
			deliteminfo.Create(IDD_DLGDELITEMINFO);
					
			::SetParent(deliteminfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			deliteminfo.ShowWindow(SW_SHOWMAXIMIZED);
				
		}
		else
		{
			deliteminfo.ShowWindow(SW_SHOWMAXIMIZED);
			deliteminfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailInfor")))//邮箱信息查询
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(mailinfor.m_hWnd== NULL)
		{
			mailinfor.Create(IDD_DLGMAIL);	

			::SetParent(mailinfor.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			mailinfor.ShowWindow(SW_SHOWMAXIMIZED);

		}
		else
		{
			mailinfor.ShowWindow(SW_SHOWMAXIMIZED);
			mailinfor.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetInfor")))//宠物信息查询
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(petinfor.m_hWnd== NULL)
		{
			petinfor.Create(IDD_DLGPETINFOR);	

			::SetParent(petinfor.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			petinfor.ShowWindow(SW_SHOWMAXIMIZED);

		}
		else
		{
			petinfor.ShowWindow(SW_SHOWMAXIMIZED);
			petinfor.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWALoginLog")))//用户登录信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(accountlogin.m_hWnd== NULL)
		{
			accountlogin.Create(IDD_DLGLOGINLOG);
		
			::SetParent(accountlogin.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			accountlogin.ShowWindow(SW_SHOWMAXIMIZED);

		}
		else
		{
			accountlogin.ShowWindow(SW_SHOWMAXIMIZED);
			accountlogin.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemInfor")))//道具信息查询
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(goodsinfor.m_hWnd== NULL)
		{
			goodsinfor.Create(IDD_DLGGOODSINFOR);

			::SetParent(goodsinfor.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			goodsinfor.ShowWindow(SW_SHOWMAXIMIZED);

		}
		else
		{			
			goodsinfor.ShowWindow(SW_SHOWMAXIMIZED);
			goodsinfor.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAChangeMoney")))//修改角色身上和银行金钱数量
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(changemoney.m_hWnd== NULL)
		{
			changemoney.Create(IDD_DLGBANKMANAGE);

			::SetParent(changemoney.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			changemoney.ShowWindow(SW_SHOWMAXIMIZED);

		}
		else
		{

			goodsinfor.ShowWindow(SW_SHOWMAXIMIZED);
			goodsinfor.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemLog")))//物品日志
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWACashLog")))//游戏币日志
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(cashlog.m_hWnd== NULL)
		{
			cashlog.Create(IDD_DLGCASHLOG);

			::SetParent(cashlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			cashlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			cashlog.ShowWindow(SW_SHOWMAXIMIZED);
			cashlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAQuestLog")))//任务日志
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(questlog.m_hWnd== NULL)
		{
			questlog.Create(IDD_DLGQUESTLOG);

			::SetParent(questlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			questlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			questlog.ShowWindow(SW_SHOWMAXIMIZED);
			questlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailLog")))//邮件日志
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserLog")))//用户日志
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(userlog.m_hWnd== NULL)
		{
			userlog.Create(IDD_DLGUSERLOG);

			::SetParent(userlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			userlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			userlog.ShowWindow(SW_SHOWMAXIMIZED);
			userlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemShop")))//商城购买记录查询
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserManage")))//玩家账号管理(勇士)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemManage")))//玩家道具管理(勇士)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWABanList")))//封停账号列表(勇士)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWACharLog")))//角色日志((勇士)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildLog")))//佣兵团日志((勇士)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetLog")))//宠物日志((勇士)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(petlog.m_hWnd== NULL)
		{
			petlog.Create(IDD_DLGPETLOG);

			::SetParent(petlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			petlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			petlog.ShowWindow(SW_SHOWMAXIMIZED);
			petlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPlayerInfo")))//用户信息((勇士)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(playerinfo.m_hWnd== NULL)
		{
			playerinfo.Create(IDD_DLGPLAYERINFO);

			::SetParent(playerinfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			playerinfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			playerinfo.ShowWindow(SW_SHOWMAXIMIZED);
			playerinfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildInfo")))//佣兵团信息查询((勇士)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetManage")))//宠物管理((勇士)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(petmanage.m_hWnd== NULL)
		{
			petmanage.Create(IDD_DLGPETMANAGE);

			::SetParent(petmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			petmanage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			petmanage.ShowWindow(SW_SHOWMAXIMIZED);
			petmanage.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildManage")))//佣兵团管理((勇士)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailSend")))//批量发送邮件(勇士)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(mailsend.m_hWnd== NULL)
		{
			mailsend.Create(IDD_DLGMAILSEND);

			::SetParent(mailsend.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			mailsend.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			mailsend.ShowWindow(SW_SHOWMAXIMIZED);
			mailsend.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	return false;
}
//选择显示不同的子对话框
extern "C" __declspec(dllexport) BOOL WA_SHOWDIALOG(CString m_MenuName)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserInfor")))//选中了查询用户信息
	{		
		if(userInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}		
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAKickPlayer")))//选中了强制玩家下线
	{
		if(kickPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(kickPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWABanPlayer")))//选中了玩家帐号解封停
	{
		if(banPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(banPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWANoticeInfor")))//选中了公告信息(
	{
		if(noticeInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(noticeInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAToolsDel")))//选中了道具删除
	{
		if(deliteminfo.m_hWnd!=NULL)
		{
			::SetWindowPos(deliteminfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailInfor")))//选中了mail
	{
		if(mailinfor.m_hWnd!=NULL)
		{
			::SetWindowPos(mailinfor.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetInfor")))//选中了宠物信息查询
	{
		if(petinfor.m_hWnd!=NULL)
		{
			::SetWindowPos(petinfor.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAAcountLoginInfor")))//选中了登录日志信息查询
	{
		if(accountlogin.m_hWnd!=NULL)
		{
			::SetWindowPos(accountlogin.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemInfor")))//选中了玩家道具信息查询
	{
		if(goodsinfor.m_hWnd!=NULL)
		{
			::SetWindowPos(goodsinfor.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAChangeMoney")))//选中了修改角色身上和银行金钱数量
	{
		if(changemoney.m_hWnd!=NULL)
		{
			::SetWindowPos(changemoney.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemLog")))//物品日志
	{
		if(itemlog.m_hWnd!=NULL)
		{
			::SetWindowPos(itemlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWACashLog")))//游戏币日志
	{
		if(cashlog.m_hWnd!=NULL)
		{
			::SetWindowPos(cashlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAQuestLog")))//任务日志
	{
		if(questlog.m_hWnd!=NULL)
		{
			::SetWindowPos(questlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailLog")))//邮件日志
	{
		if(maillog.m_hWnd!=NULL)
		{
			::SetWindowPos(maillog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserLog")))//用户日志
	{
		if(userlog.m_hWnd!=NULL)
		{
			::SetWindowPos(userlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemShop")))//商城购买记录查询
	{
		if(itemshop.m_hWnd!=NULL)
		{
			::SetWindowPos(itemshop.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserManage")))//玩家账号管理
	{
		if(usermanage.m_hWnd!=NULL)
		{
			::SetWindowPos(usermanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemManage")))//玩家道具管理
	{
		if(itemmanage.m_hWnd!=NULL)
		{
			::SetWindowPos(itemmanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWABanList")))//封停账号列表
	{
		if(banlist.m_hWnd!=NULL)
		{
			::SetWindowPos(banlist.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWACharLog")))//角色日志
	{
		if(charlog.m_hWnd!=NULL)
		{
			::SetWindowPos(charlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildLog")))//佣兵团日志
	{
		if(guildlog.m_hWnd!=NULL)
		{
			::SetWindowPos(guildlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetLog")))//宠物日志
	{
		if(petlog.m_hWnd!=NULL)
		{
			::SetWindowPos(petlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPlayerInfo")))//用户信息查询(勇士)
	{
		if(playerinfo.m_hWnd!=NULL)
		{
			::SetWindowPos(playerinfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildInfo")))//佣兵团信息查询
	{
		if(guildinfo.m_hWnd!=NULL)
		{
			::SetWindowPos(guildinfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetManage")))//宠物管理
	{
		if(petmanage.m_hWnd!=NULL)
		{
			::SetWindowPos(petmanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildManage")))//佣兵团管理
	{
		if(guildmanage.m_hWnd!=NULL)
		{
			::SetWindowPos(guildmanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailSend")))//批量发送邮件(勇士)
	{
		if(mailsend.m_hWnd!=NULL)
		{
			::SetWindowPos(mailsend.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	return false;
}

//再次发送同样的Query
extern "C" __declspec(dllexport) void WA_SENDINFOAGAIN()
{
	theApp.operWA.SendSameQuery();
}

/////////////////////////////////初始化基本信息
extern "C" __declspec(dllexport) void GETWAINFO(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent, int* m_SelectDll)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.UserByID = userByID;
	theApp.userName = userName;
	theApp.mHwndParent = m_HwndParent;
	theApp.operWA.initSocket(m_socket);
	theApp.operWA.intWA = m_SelectDll;
}
extern "C" __declspec(dllexport) BOOL WA_TRANSLATEMESSAGE(MSG* pMsg)
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
				if(deliteminfo.m_hWnd != NULL)
				{
					deliteminfo.PreTranslateMessage(pMsg);
				}
				if(petinfor.m_hWnd != NULL)
				{
					petinfor.PreTranslateMessage(pMsg);
				}
				if(accountlogin.m_hWnd != NULL)
				{
					accountlogin.PreTranslateMessage(pMsg);
				}
				if(goodsinfor.m_hWnd != NULL)
				{
					goodsinfor.PreTranslateMessage(pMsg);
				}
				if(changemoney.m_hWnd != NULL)
				{
					changemoney.PreTranslateMessage(pMsg);
				}
				if(itemlog.m_hWnd != NULL)
				{
					itemlog.PreTranslateMessage(pMsg);
				}
				if(cashlog.m_hWnd != NULL)
				{
					cashlog.PreTranslateMessage(pMsg);
				}
				if(questlog.m_hWnd != NULL)
				{
					questlog.PreTranslateMessage(pMsg);
				}
				if(maillog.m_hWnd != NULL)
				{
					maillog.PreTranslateMessage(pMsg);
				}
				if(userlog.m_hWnd != NULL)
				{
					userlog.PreTranslateMessage(pMsg);
				}
				if(itemshop.m_hWnd != NULL)
				{
					itemshop.PreTranslateMessage(pMsg);
				}
				if(usermanage.m_hWnd != NULL)
				{
					usermanage.PreTranslateMessage(pMsg);
				}
				if(itemmanage.m_hWnd != NULL)
				{
					itemmanage.PreTranslateMessage(pMsg);
				}
				if(banlist.m_hWnd != NULL)
				{
					banlist.PreTranslateMessage(pMsg);
				}
				if(charlog.m_hWnd != NULL)
				{
					charlog.PreTranslateMessage(pMsg);
				}
				if(guildlog.m_hWnd != NULL)
				{
					guildlog.PreTranslateMessage(pMsg);
				}
				if(petlog.m_hWnd != NULL)
				{
					petlog.PreTranslateMessage(pMsg);
				}
				if(playerinfo.m_hWnd != NULL)
				{
					playerinfo.PreTranslateMessage(pMsg);
				}
				if(guildinfo.m_hWnd != NULL)
				{
					guildinfo.PreTranslateMessage(pMsg);
				}
				if(petmanage.m_hWnd != NULL)
				{
					petmanage.PreTranslateMessage(pMsg);
				}
				if(guildmanage.m_hWnd != NULL)
				{
					guildmanage.PreTranslateMessage(pMsg);
				}
				if(mailsend.m_hWnd != NULL)
				{
					mailsend.PreTranslateMessage(pMsg);
				}
			}
		}
	}
	return FALSE;
}

//选择给不同的子对话框发消息
extern "C" __declspec(dllexport) void WA_DIALOGMSG(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam)
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
		if(deliteminfo.m_hWnd != NULL)
		{
			::SetParent(deliteminfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(deliteminfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(petinfor.m_hWnd != NULL)
		{
			::SetParent(petinfor.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petinfor.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(accountlogin.m_hWnd != NULL)
		{
			::SetParent(accountlogin.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(accountlogin.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(goodsinfor.m_hWnd != NULL)
		{
			::SetParent(goodsinfor.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(goodsinfor.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(changemoney.m_hWnd != NULL)
		{
			::SetParent(changemoney.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(changemoney.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(itemlog.m_hWnd != NULL)
		{
			::SetParent(itemlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(cashlog.m_hWnd != NULL)
		{
			::SetParent(cashlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(cashlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(questlog.m_hWnd != NULL)
		{
			::SetParent(questlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(questlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(userlog.m_hWnd != NULL)
		{
			::SetParent(userlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(itemshop.m_hWnd != NULL)
		{
			::SetParent(itemshop.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemshop.m_hWnd, Msg, wParam, lParam);//发送消息
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
		if(banlist.m_hWnd != NULL)
		{
			::SetParent(banlist.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banlist.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(charlog.m_hWnd != NULL)
		{
			::SetParent(charlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(charlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(guildlog.m_hWnd != NULL)
		{
			::SetParent(guildlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(petlog.m_hWnd != NULL)
		{
			::SetParent(petlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(playerinfo.m_hWnd != NULL)
		{
			::SetParent(playerinfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(playerinfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(guildinfo.m_hWnd != NULL)
		{
			::SetParent(guildinfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildinfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(petmanage.m_hWnd != NULL)
		{
			::SetParent(petmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petmanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(guildmanage.m_hWnd != NULL)
		{
			::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildmanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(mailsend.m_hWnd != NULL)
		{
			::SetParent(mailsend.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mailsend.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserInfor")))
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAKickPlayer")))////强制玩家下线
	{
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWABanPlayer")))//玩家账号解/封停
	{
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWANoticeInfor")))//公告管理
	{
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAToolsDel")))//道具删除
	{
		if(deliteminfo.m_hWnd != NULL)
		{
			::SetParent(deliteminfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(deliteminfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailInfor")))//邮箱信息查询
	{
		if(mailinfor.m_hWnd != NULL)
		{
			::SetParent(mailinfor.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mailinfor.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetInfor")))//宠物信息查询
	{
		if(petinfor.m_hWnd != NULL)
		{
			::SetParent(petinfor.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petinfor.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAAcountLoginInfor")))//登录信息查询
	{
		if(accountlogin.m_hWnd != NULL)
		{
			::SetParent(accountlogin.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(accountlogin.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemInfor")))//玩家道具信息查询
	{
		if(goodsinfor.m_hWnd != NULL)
		{
			::SetParent(goodsinfor.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(goodsinfor.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAChangeMoney")))//修改角色身上和银行金钱数量
	{
		if(changemoney.m_hWnd != NULL)
		{
			::SetParent(changemoney.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(changemoney.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemLog")))//物品日志
	{
		if(itemlog.m_hWnd!=NULL)
		{
			::SetParent(itemlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWACashLog")))//游戏币日志
	{
		if(cashlog.m_hWnd!=NULL)
		{
			::SetParent(cashlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(cashlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAQuestLog")))//任务日志
	{
		if(questlog.m_hWnd!=NULL)
		{
			::SetParent(questlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(questlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserLog")))//用户日志
	{
		if(userlog.m_hWnd!=NULL)
		{
			::SetParent(userlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemShop")))//商城购买记录查询
	{
		if(itemshop.m_hWnd!=NULL)
		{
			::SetParent(itemshop.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemshop.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserManage")))//玩家账号管理
	{
		if(usermanage.m_hWnd!=NULL)
		{
			::SetParent(usermanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(usermanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemManage")))//玩家道具管理
	{
		if(itemmanage.m_hWnd!=NULL)
		{
			::SetParent(itemmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemmanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWABanList")))//封停账号列表
	{
		if(banlist.m_hWnd!=NULL)
		{
			::SetParent(banlist.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banlist.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWACharLog")))//角色日志
	{
		if(charlog.m_hWnd!=NULL)
		{
			::SetParent(charlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(charlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildLog")))//佣兵团日志
	{
		if(guildlog.m_hWnd!=NULL)
		{
			::SetParent(guildlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetLog")))//宠物日志
	{
		if(petlog.m_hWnd!=NULL)
		{
			::SetParent(petlog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petlog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPlayerInfo")))//=用户信息查询(勇士)
	{
		if(playerinfo.m_hWnd!=NULL)
		{
			::SetParent(playerinfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(playerinfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildInfo")))//佣兵团信息查询
	{
		if(guildinfo.m_hWnd!=NULL)
		{
			::SetParent(guildinfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildinfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetManage")))//宠物管理
	{
		if(petmanage.m_hWnd!=NULL)
		{
			::SetParent(petmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petmanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildManage")))//佣兵团管理
	{
		if(guildmanage.m_hWnd!=NULL)
		{
			::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildmanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailSend")))//批量发送邮件
	{
		if(mailsend.m_hWnd!=NULL)
		{
			::SetParent(mailsend.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mailsend.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
}
extern "C" __declspec(dllexport) void GETWAMESSAGE(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.m_TagID = m_message_tag_id;
	OperationWA operWA;
	// MessageBox(NULL,(LPCTSTR)lpRecvbuf,"",0);
	CString tagid="";

	//MessageBox(NULL,tagid,"",0);
	/////////////////////测试
	if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
	{
		userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
	}
	//////////////////////
	switch(m_message_tag_id)
	{	
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://服务器信息
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((noticeInfo.m_hWnd != NULL) && (noticeInfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((goodsinfor.m_hWnd != NULL) && (goodsinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				goodsinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petinfor.m_hWnd != NULL) && (petinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}	
			else if((changemoney.m_hWnd != NULL) && (changemoney.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				changemoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((deliteminfo.m_hWnd != NULL) && (deliteminfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				deliteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((accountlogin.m_hWnd != NULL) && (accountlogin.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				accountlogin.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailinfor.m_hWnd != NULL) && (mailinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				mailinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemlog.m_hWnd != NULL) && (itemlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((cashlog.m_hWnd != NULL) && (cashlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				cashlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((questlog.m_hWnd != NULL) && (questlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				questlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((maillog.m_hWnd != NULL) && (maillog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				maillog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((userlog.m_hWnd != NULL) && (userlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				userlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemshop.m_hWnd != NULL) && (itemshop.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemshop.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((usermanage.m_hWnd != NULL) && (usermanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				usermanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banlist.m_hWnd != NULL) && (banlist.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				banlist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((charlog.m_hWnd != NULL) && (charlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				charlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((playerinfo.m_hWnd != NULL) && (playerinfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				playerinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildlog.m_hWnd != NULL) && (guildlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petlog.m_hWnd != NULL) && (petlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildinfo.m_hWnd != NULL) && (guildinfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petmanage.m_hWnd != NULL) && (petmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailsend.m_hWnd != NULL) && (mailsend.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				mailsend.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Account_Query_Resp://取得角色基本资讯响应
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((noticeInfo.m_hWnd != NULL) && (noticeInfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((goodsinfor.m_hWnd != NULL) && (goodsinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				goodsinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petinfor.m_hWnd != NULL) && (petinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}	
			else if((changemoney.m_hWnd != NULL) && (changemoney.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				changemoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((deliteminfo.m_hWnd != NULL) && (deliteminfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				deliteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((accountlogin.m_hWnd != NULL) && (accountlogin.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				accountlogin.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailinfor.m_hWnd != NULL) && (mailinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				mailinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemlog.m_hWnd != NULL) && (itemlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((cashlog.m_hWnd != NULL) && (cashlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				cashlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((questlog.m_hWnd != NULL) && (questlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				questlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((maillog.m_hWnd != NULL) && (maillog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				maillog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((userlog.m_hWnd != NULL) && (userlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				userlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemshop.m_hWnd != NULL) && (itemshop.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemshop.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((usermanage.m_hWnd != NULL) && (usermanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				usermanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((charlog.m_hWnd != NULL) && (charlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				charlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petlog.m_hWnd != NULL) && (petlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((playerinfo.m_hWnd != NULL) && (playerinfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				playerinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petmanage.m_hWnd != NULL) && (petmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_KickPlayer_Resp://强制玩家下线
		{
			if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给强制玩家下线界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_ClosePlayer_Resp://封停玩家帐号
	case CEnumCore::Message_Tag_ID::WA_OpenPlayer_Resp://解封玩家帐号
		{
			if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给玩家帐号解封停界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_CloseList_Resp://封停帐号列表
		{
			if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给玩家帐号解封停界面发消息
			}
			else if((banlist.m_hWnd != NULL) && (banlist.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				banlist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给封停帐号列表界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_CloseSingle_Resp://单个封停帐号
		{
			if((banlist.m_hWnd != NULL) && (banlist.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				banlist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给封停帐号列表界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Add_Resp://公告添加响应
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Query_Resp://公告查询响应
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Update_Resp://公告更新响应
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Del_Resp://公告删除响应
		{
			if((noticeInfo.m_hWnd != NULL) && (noticeInfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给公告信息界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_FriendInfo_Query_Resp://好友列表查询
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_BodyItemInfo_Query_Resp://查询玩家身上物品的回应
	case CEnumCore::Message_Tag_ID::WA_BagItemInfo_Query_Resp://查询玩家背包物品的回应
	case CEnumCore::Message_Tag_ID::WA_BankItemInfo_Query_Resp://查询玩家银行物品的回应
		{
			if((goodsinfor.m_hWnd != NULL) && (goodsinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				goodsinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_EmblemInfo_Query_Resp://查询玩家徽章的回应
	case CEnumCore::Message_Tag_ID::WA_PetInfo_Query_Resp://查询玩家宠物的回应
		{
			if((petinfor.m_hWnd != NULL) && (petinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petmanage.m_hWnd != NULL) && (petmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_LoginLogoutByIP://查询帐号登录信息的回应
		{
			if((accountlogin.m_hWnd != NULL) && (accountlogin.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				accountlogin.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Money_Update_Resp://金钱修改反馈信息的回应
		{
			if((changemoney.m_hWnd != NULL) && (changemoney.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				changemoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Item_Del_Resp://道具删除的回应
		{			
			if((goodsinfor.m_hWnd != NULL) && (goodsinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				goodsinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_MonsterDropItem_Resp://怪物掉落
	case CEnumCore::Message_Tag_ID::WA_Query_BuyItemNPC_Resp://从NPC处购买
	case CEnumCore::Message_Tag_ID::WA_Query_SellItemTONPC_Resp://卖给NPC
	case CEnumCore::Message_Tag_ID::WA_Query_DropItem_Resp://玩家自行删除
	case CEnumCore::Message_Tag_ID::WA_Query_GetItemTrade_Resp://交易获得
	case CEnumCore::Message_Tag_ID::WA_Query_LoseItemTrade_Resp://交易失去
	case CEnumCore::Message_Tag_ID::WA_Query_BindItem_Resp://装备绑定
	case CEnumCore::Message_Tag_ID::WA_Query_UnBindItem_Resp://装备解绑
	case CEnumCore::Message_Tag_ID::WA_Query_BoothItem_Resp://玩家摆摊
	case CEnumCore::Message_Tag_ID::WA_Query_DeleteItem_Resp://道具删除
	case CEnumCore::Message_Tag_ID::WA_Query_UseItem_Resp://道具使用
	case CEnumCore::Message_Tag_ID::WA_Query_CraftItem_Resp://装备制作
	case CEnumCore::Message_Tag_ID::WA_Query_PunchItem_Resp://装备打孔
	case CEnumCore::Message_Tag_ID::WA_Query_ChangeSlotItem_Resp://装备改孔
	case CEnumCore::Message_Tag_ID::WA_Query_UpgradeStar_Resp://装备升星
	case CEnumCore::Message_Tag_ID::WA_Query_Gem_Resp://宝石
	case CEnumCore::Message_Tag_ID::WA_Query_Pharma_Resp://制药记录
	case CEnumCore::Message_Tag_ID::WA_Query_CraftGem_Resp://宝石合成
	case CEnumCore::Message_Tag_ID::WA_Query_CraftMatirail_Resp://材料合成
	case CEnumCore::Message_Tag_ID::WA_Query_CraftRecipe_Resp://图纸合成
	case CEnumCore::Message_Tag_ID::WA_Query_MazeIntegral_Resp://迷宫积分兑换奖励
		{
			if((itemlog.m_hWnd != NULL) && (itemlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_MonsterDropMoney_Resp://怪物掉落
	case CEnumCore::Message_Tag_ID::WA_Query_GetMoneyQuest_Resp://任务获得
	case CEnumCore::Message_Tag_ID::WA_Query_LoseMoneyRepair_Resp://修装
	case CEnumCore::Message_Tag_ID::WA_Query_GetMoneyTrade_Resp://交易获得
	case CEnumCore::Message_Tag_ID::WA_Query_LoseMoneyTrade_Resp://交易失去
		{
			if((cashlog.m_hWnd != NULL) && (cashlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				cashlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_QuestReward_Resp://任务完成获得记录
	case CEnumCore::Message_Tag_ID::WA_Query_QuestGive_Resp://任务物品删除记录
		{
			if((questlog.m_hWnd != NULL) && (questlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				questlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_MailSend_Resp://邮件:发送记录
	case CEnumCore::Message_Tag_ID::WA_Query_MailRecv_Resp://邮件:接收记录
	case CEnumCore::Message_Tag_ID::WA_Query_MailDelete_Resp://邮件:删除记录
		{
			if((maillog.m_hWnd != NULL) && (maillog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				maillog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_Instance_Resp://查询用户的副本日志
		{
			if((userlog.m_hWnd != NULL) && (userlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				userlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_LoginLogoutByIP_Resp://玩家登陆/登出日志
		{
			if((accountlogin.m_hWnd != NULL) && (accountlogin.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				accountlogin.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_LoginLogout_Resp://玩家登陆/登出日志
		{
			if((userlog.m_hWnd != NULL) && (userlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				userlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((accountlogin.m_hWnd != NULL) && (accountlogin.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				accountlogin.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_ItemShop_Resp://商城:购买记录
		{
			if((itemshop.m_hWnd != NULL) && (itemshop.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemshop.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_ModifyCharacterSkill_Resp://修改角色技能
	case CEnumCore::Message_Tag_ID::WA_RecoverCharacter_Resp://恢复角色
	case CEnumCore::Message_Tag_ID::WA_ModifyAccountPassw_Resp://修改密码
	case CEnumCore::Message_Tag_ID::WA_SkillList_Query_Resp://技能列表查询
	case CEnumCore::Message_Tag_ID::WA_PlayerRole_Modfiy_Resp://修改角色名
	case CEnumCore::Message_Tag_ID::WA_RoleInfo_Modfiy_Resp://修改角色属性值(改钱,改名,改等级)
	case CEnumCore::Message_Tag_ID::WA_RoleSkill_Query_Resp://查询玩家身上技能信息
	case CEnumCore::Message_Tag_ID::WA_UserPwd_Recover_Resp://恢复密码
	case CEnumCore::Message_Tag_ID::WA_Query_ResumePassw_Resp://恢复密码
	case CEnumCore::Message_Tag_ID::WA_ResumeAttribute_Op_Resp://恢复角色属性
		{
			if((usermanage.m_hWnd != NULL) && (usermanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				usermanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_MailItem_Resp://给角色邮寄物品
	case CEnumCore::Message_Tag_ID::WA_Item_Add_Resp://添加道具
	case CEnumCore::Message_Tag_ID::WA_ItemList_Query_Resp://道具列表查询
	case CEnumCore::Message_Tag_ID::WA_ItemType_Query_Resp://查询玩家道具类型查询	
		{
			if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Character_Upgrade_Resp://角色升级记录查询
	case CEnumCore::Message_Tag_ID::WA_Character_Create_Resp://角色创建记录查询
	case CEnumCore::Message_Tag_ID::WA_Character_Delete_Resp://角色删除记录查询
	case CEnumCore::Message_Tag_ID::WA_Join_Guild_Resp://加入帮会
	case CEnumCore::Message_Tag_ID::WA_Quit_Guild_Resp://离开帮会
	case CEnumCore::Message_Tag_ID::WA_Create_Guild_Resp://创建帮会
	case CEnumCore::Message_Tag_ID::WA_Dissolve_Guild_Resp://解散帮会
	case CEnumCore::Message_Tag_ID::WA_Transfer_Info_Resp://转职信息查询
	case CEnumCore::Message_Tag_ID::WA_Skills_Log_Resp://技能日志记录
	case CEnumCore::Message_Tag_ID::WA_LifeSkills_Log_Resp://生活技能日志记录
		{
			if((charlog.m_hWnd != NULL) && (charlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				charlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Create_MercenaryGroup_Resp://创建记录
	case CEnumCore::Message_Tag_ID::WA_Dissolve_MercenaryGroup_Resp://解散记录
		{
			if((guildlog.m_hWnd != NULL) && (guildlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_CatchPetSpirit_Record_Resp://宠物精魂捕捉记录
	case CEnumCore::Message_Tag_ID::WA_GainSpirit_Record_Resp://精魂交易获得
	case CEnumCore::Message_Tag_ID::WA_LoseSpirit_Record_Resp://精魂交易失去
	case CEnumCore::Message_Tag_ID::WA_SellSpirit_Record_Resp://精魂出售记录
		{
			if((petlog.m_hWnd != NULL) && (petlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_MercenaryGroup_Info_Query_Resp://佣兵团信息查询
		{
			if((guildlog.m_hWnd != NULL) && (guildlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildinfo.m_hWnd != NULL) && (guildinfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_MemberList_Query_Resp://佣兵团成员列表查询
		{
			if((guildinfo.m_hWnd != NULL) && (guildinfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_SkillsInfo_Query_Resp://技能信息查询
	case CEnumCore::Message_Tag_ID::WA_MissionsCompleted_Query_Resp://已完成任务
	case CEnumCore::Message_Tag_ID::WA_MissionsReceived_Query_Resp://已接任务	
		{
			if((playerinfo.m_hWnd != NULL) && (playerinfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				playerinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_PetList_Query_Resp://宠物列表查询
	case CEnumCore::Message_Tag_ID::WA_PetAdded_Operate_Resp://添加宠物
	case CEnumCore::Message_Tag_ID::WA_PetDeleted_Operate_Resp://删除宠物	
		{
			if((petmanage.m_hWnd != NULL) && (petmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_AttornPopedom_Operate_Resp://家族管理
	case CEnumCore::Message_Tag_ID::WA_ModifyGuildName_Operate_Resp://修改公会名称
	case CEnumCore::Message_Tag_ID::WA_KickGuildMember_Operate_Resp://踢出公会成员
	case CEnumCore::Message_Tag_ID::WA_DissolveGuild_Operate_Resp://解散公会
		{
			if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_SendMails_Op_Resp://批量发送邮件
		{
			if((mailsend.m_hWnd != NULL) && (mailsend.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				mailsend.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	default:
		break;
	}
}

