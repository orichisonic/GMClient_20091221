// M_CG2.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2UserInfo.h"
#include "CG2KickPlayer.h"
#include "CG2BanPlayer.h"
#include "CG2NoticeInfo.h"
#include "CG2LoginInfo.h"
#include "CG2LogQuery.h"
#include "CG2UpdateChar.h"
#include "CG2UpdateSkill.h"
#include "CG2AddItem.h"

//new add
#include "CG2BakAccount.h"
#include "CG2BakAccountInfo.h"
#include "CG2GuildManage.h"

#include "CG2GuildInfo.h"
#include "CG2BankInfo.h"
#include "CG2BankManage.h"
#include "CG2ItemInfo.h"
#include "CG2PetInfo.h"
#include "CG2PetManage.h"
#include "CG2PetPic.h"
#include "CG2PetSkillManage.h"
#include "CG2TmpPwd.h"
#include "CG2ChangeCharNo.h"
#include "CG2ChangeMap.h"
#include "CG2DelItemInfo.h"
#include "CG2SendAsk.h"
#include "CG2UserShoppingInfo.h"
#include "CG2SendItemPwd.h"

#include "CG2AccountBan.h"
#include "CG2AccountActive.h"
#include "CG2RecallLogItem.h"
#include "CG2RecallLogPet.h"

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

// CM_CG2App

BEGIN_MESSAGE_MAP(CM_CG2App, CWinApp)
END_MESSAGE_MAP()


// CM_CG2App 构造

CM_CG2App::CM_CG2App()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CM_CG2App 对象

CM_CG2App theApp;
CCG2UserInfo userInfo;
CCG2KickPlayer kickPlayer;
CCG2BanPlayer banPlayer;
CCG2NoticeInfo noticeInfo;
CCG2LoginInfo loginInfo;
CCG2LogQuery logQuery;
CCG2UpdateChar updateChar;
CCG2UpdateSkill updateSkill;
CCG2AddItem addItem;

//new add
CCG2BakAccount bakAccount;
CCG2BakAccountInfo bakAccountInfo;
CCG2GuildManage guildManage;

CCG2GuildInfo guildInfo;
CCG2BankInfo bankInfo;
CCG2BankManage bankManage;
CCG2ItemInfo itemInfo;
CCG2DelItemInfo delItemInfo;
CCG2PetInfo  petInfo;
CCG2PetManage petManage;
CCG2PetPic petPic;
CCG2PetSkillManage petSkillManage;
CCG2TmpPwd tmpPwd;
CCG2ChangeCharNo changeCharNo;
CCG2ChangeMap changeMap;
CCG2SendAsk sendAsk;
CCG2UserShoppingInfo userShoppingInfo;
CCG2SendItemPwd sendItemPwd;

CCG2AccountActive accountActive;
CCG2AccountBan accountBan;
CCG2RecallLogItem recallLogItem;
CCG2RecallLogPet recallLogPet;


// CM_CG2App 初始化

BOOL CM_CG2App::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	return TRUE;
}
extern "C" __declspec(dllexport) BOOL CG2_TRANSLATEMESSAGE(MSG* pMsg)
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
				if(loginInfo.m_hWnd !=NULL)
				{
					loginInfo.PreTranslateMessage(pMsg);
				}
				if(logQuery.m_hWnd !=NULL)
				{
					logQuery.PreTranslateMessage(pMsg);
				}
				if(updateChar.m_hWnd !=NULL)
				{
					updateChar.PreTranslateMessage(pMsg);
				}
				if(updateSkill.m_hWnd !=NULL)
				{
					updateSkill.PreTranslateMessage(pMsg);
				}
				if(addItem.m_hWnd !=NULL)
				{
					addItem.PreTranslateMessage(pMsg);
				}
				if(bakAccount.m_hWnd!=NULL)
				{
					bakAccount.PreTranslateMessage(pMsg);
				}
				if(bakAccountInfo.m_hWnd!=NULL)
				{
					bakAccountInfo.PreTranslateMessage(pMsg);
				}
				if(guildManage.m_hWnd!=NULL)
				{
					guildManage.PreTranslateMessage(pMsg);
				}
				if(guildInfo.m_hWnd!=NULL)
				{
					guildInfo.PreTranslateMessage(pMsg);
				}
				if(bankInfo.m_hWnd!=NULL)
				{
					bankInfo.PreTranslateMessage(pMsg);
				}
				if(bankManage.m_hWnd!=NULL)
				{
					bankManage.PreTranslateMessage(pMsg);
				}
				if(itemInfo.m_hWnd!=NULL)
				{
					itemInfo.PreTranslateMessage(pMsg);
				}
				if(delItemInfo.m_hWnd!=NULL)
				{
					delItemInfo.PreTranslateMessage(pMsg);
				}
				if(petInfo.m_hWnd!=NULL)
				{
					petInfo.PreTranslateMessage(pMsg);
				}
				if(petManage.m_hWnd!=NULL)
				{
					petManage.PreTranslateMessage(pMsg);
				}
				if(petPic.m_hWnd!=NULL)
				{
					petPic.PreTranslateMessage(pMsg);
				}
				if(petSkillManage.m_hWnd!=NULL)
				{
					petSkillManage.PreTranslateMessage(pMsg);
				}
				if(tmpPwd.m_hWnd!=NULL)
				{
					tmpPwd.PreTranslateMessage(pMsg);
				}
				if(changeCharNo.m_hWnd!=NULL)
				{
					changeCharNo.PreTranslateMessage(pMsg);
				}
				if(changeMap.m_hWnd!=NULL)
				{
					changeMap.PreTranslateMessage(pMsg);
				}
				if(sendAsk.m_hWnd!=NULL)
				{
					sendAsk.PreTranslateMessage(pMsg);
				}
				if(userShoppingInfo.m_hWnd!=NULL)
				{
					userShoppingInfo.PreTranslateMessage(pMsg);
				}
				if(accountActive.m_hWnd!=NULL)
				{
					accountActive.PreTranslateMessage(pMsg);
				}
				if(accountBan.m_hWnd!=NULL)
				{
					accountBan.PreTranslateMessage(pMsg);
				}
				if(recallLogItem.m_hWnd!=NULL)
				{
					recallLogItem.PreTranslateMessage(pMsg);
				}
				if(recallLogPet.m_hWnd!=NULL)
				{
					recallLogPet.PreTranslateMessage(pMsg);
				}

			}
		}
	}
	return FALSE;
}

//打开新的对话框
extern "C" __declspec(dllexport) bool CG2_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicUserInfo")))//选中了查询用户信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(userInfo.m_hWnd == NULL)
		{
			userInfo.Create(IDD_DLGUSERINFO);
			userInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(userInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicKickPlayer")))//选中了强制玩家下线
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(kickPlayer.m_hWnd == NULL)
		{
			kickPlayer.Create(IDD_DLGKICKPLAYER);
			kickPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(kickPlayer.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBanPlayer")))//选中了玩家帐号解封停
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(banPlayer.m_hWnd == NULL)
		{
			banPlayer.Create(IDD_DLGBANPLAYER);
			banPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(banPlayer.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicNoticeInfo")))//选中了公告信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(noticeInfo.m_hWnd == NULL)
		{
			noticeInfo.Create(IDD_DLGNOTICE);
			noticeInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(noticeInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAccountLogin")))//选中了登入信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(loginInfo.m_hWnd == NULL)
		{
			loginInfo.Create(IDD_DLGLOGININFO);
			loginInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(loginInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	//maple add
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicMailLog")))//双击的是玩家日志查询菜单
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(logQuery.m_hWnd == NULL)
		{
			logQuery.Create(IDD_DLGLOGQUERY);
			logQuery.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(logQuery.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(logQuery.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicModiCharInfo")))//双击的是修改玩家角色信息菜单
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(updateChar.m_hWnd == NULL)
		{
			updateChar.Create(IDD_DLGUPDATECHAR);
			updateChar.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(updateChar.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(updateChar.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_UpdateSkill")))//双击的是修改玩家技能信息菜单
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(updateSkill.m_hWnd == NULL)
		{
			updateSkill.Create(IDD_DLGUPDATESKILL);//IDD_DLGUPDATESKILL
			updateSkill.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(updateSkill.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(updateSkill.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAddItem")))//双击的是添加道具菜单
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(addItem.m_hWnd == NULL)
		{
			addItem.Create(IDD_DLGADDITEM);//
			addItem.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(addItem.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(addItem.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicResumeChar")))//双击的是恢复角色
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(bakAccount.m_hWnd == NULL)
		{
			bakAccount.Create(IDD_DLGBAKACCOUNT);//
			bakAccount.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(bakAccount.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(bakAccount.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_BakAccountInfo")))//双击的是恢复角色只读
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(bakAccountInfo.m_hWnd == NULL)
		{
			bakAccountInfo.Create(IDD_DLGBAKACCOUNTINFO);//
			bakAccountInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(bakAccountInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(bakAccountInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGuildInfo")))//双击的是公会管理
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(guildManage.m_hWnd == NULL)
		{
			guildManage.Create(IDD_DLGGUILDMANAGE);//
			guildManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(guildManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(guildManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGuildInfoRead")))//双击的是公会信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(guildInfo.m_hWnd == NULL)
		{
			guildInfo.Create(IDD_DLGGUILDINFO);//
			guildInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(guildInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(guildInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBankItem")))//双击的是银行信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(bankInfo.m_hWnd == NULL)
		{
			bankInfo.Create(IDD_DLGBANKINFO);//
			bankInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(bankInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(bankInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_BankManage")))//双击的是银行管理
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(bankManage.m_hWnd == NULL)
		{
			bankManage.Create(IDD_DLGBANKMANAGE);//
			bankManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(bankManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(bankManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicPackGoods")))//双击的是道具信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(itemInfo.m_hWnd == NULL)
		{
			itemInfo.Create(IDD_DLGITEMINFO);//
			itemInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(itemInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicItemDel")))//双击的是删除道具信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(delItemInfo.m_hWnd == NULL)
		{
			delItemInfo.Create(IDD_DLGDELITEMINFO);//
			delItemInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(delItemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(delItemInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicPetInfo")))//双击的是宠物信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(petInfo.m_hWnd == NULL)
		{
			petInfo.Create(IDD_DLGPETINFO);//
			petInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(petInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetManage")))//双击的是宠物管理
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(petManage.m_hWnd == NULL)
		{
			petManage.Create(IDD_DLGPETMANAGE);//
			petManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(petManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(petManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetPic")))//双击的是宠物图鉴
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(petPic.m_hWnd == NULL)
		{
			petPic.Create(IDD_DLGPETPIC);//
			petPic.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(petPic.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(petPic.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetSkillManage")))//双击的是宠物技能修改
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(petSkillManage.m_hWnd == NULL)
		{
			petSkillManage.Create(IDD_DLGPETSKILLMANAGE);//
			petSkillManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(petSkillManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(petSkillManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_TmpPwd")))//双击的是修改玩家临时密码
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(tmpPwd.m_hWnd == NULL)
		{
			tmpPwd.Create(IDD_DLGTMPPWD);//
			tmpPwd.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(tmpPwd.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(tmpPwd.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_ChangeCharNo")))//双击的是角色换位
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(changeCharNo.m_hWnd == NULL)
		{
			changeCharNo.Create(IDD_DLGCHANGECHARNO);//
			changeCharNo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(changeCharNo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(changeCharNo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicMoveCharacter")))//双击的是移动角色坐标
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(changeMap.m_hWnd == NULL)
		{
			changeMap.Create(IDD_DLGCHANGEMAP);//
			changeMap.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(changeMap.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(changeMap.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicSendAsk")))//双击的是发送问答信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(sendAsk.m_hWnd == NULL)
		{
			sendAsk.Create(IDD_DLGSENDASK);//
			sendAsk.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(sendAsk.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(sendAsk.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGetBuyLog")))//双击的是商城-获取玩家购买日志信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(userShoppingInfo.m_hWnd == NULL)
		{
			userShoppingInfo.Create(IDD_DLGUSERSHOPPINGINFO);//
			userShoppingInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(userShoppingInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(userShoppingInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicSendMail")))//双击的是发送道具锁
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(sendItemPwd.m_hWnd == NULL)
		{
			sendItemPwd.Create(IDD_DLGSENDITEMPWD);//
			sendItemPwd.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(sendItemPwd.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(sendItemPwd.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAccountActive")))//双击的是帐户激活查询（魔力宝贝2）
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(accountActive.m_hWnd == NULL)
		{
			accountActive.Create(IDD_DLGACCOUNTACTIVE);//
			accountActive.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(accountActive.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(accountActive.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBanKick")))//双击的是玩家封停被踢次数（魔力宝贝2）
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(accountBan.m_hWnd == NULL)
		{
			accountBan.Create(IDD_DLGACCOUNTBAN);//
			accountBan.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(accountBan.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(accountBan.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_RecallLogItem")))//双击的是恢复日志道具（魔力宝贝2）
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(recallLogItem.m_hWnd == NULL)
		{
			recallLogItem.Create(IDD_DLGRECALLLOGITEM);//
			recallLogItem.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(recallLogItem.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(recallLogItem.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicRecoverPetLog")))//双击的是恢复日志宠物（魔力宝贝2）
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(recallLogPet.m_hWnd == NULL)
		{
			recallLogPet.Create(IDD_DLGRECALLLOGPET);//
			recallLogPet.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(recallLogPet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(recallLogPet.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	return false;
}

//选择显示不同的子对话框
extern "C" __declspec(dllexport) BOOL CG2_SHOWDIALOG(CString m_MenuName)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicUserInfo")))//选中了查询用户信息
	{
		if(userInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicKickPlayer")))//选中了强制玩家下线
	{
		if(kickPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(kickPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBanPlayer")))//选中了玩家帐号解封停
	{
		if(banPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(banPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicNoticeInfo")))//选中了公告信息
	{
		if(noticeInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(noticeInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAccountLogin")))//选中了登入信息
	{
		if(loginInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(loginInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	//maple add
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicMailLog")))//双击的是玩家日志查询菜单
	{
		if(logQuery.m_hWnd!=NULL)
		{
			::SetWindowPos(logQuery.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicModiCharInfo")))//双击的是修改玩家角色信息菜单
	{
		if(updateChar.m_hWnd!=NULL)
		{
			::SetWindowPos(updateChar.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_UpdateSkill")))//双击的是修改玩家技能信息菜单
	{
		if(updateSkill.m_hWnd!=NULL)
		{
			::SetWindowPos(updateSkill.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAddItem")))//双击的是添加道具菜单
	{
		if(addItem.m_hWnd!=NULL)
		{
			::SetWindowPos(addItem.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicResumeChar")))//双击的是恢复角色菜单
	{
		if(bakAccount.m_hWnd!=NULL)
		{
			::SetWindowPos(bakAccount.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_BakAccountInfo")))//双击的是恢复角色(只读)菜单
	{
		if(bakAccountInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(bakAccountInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGuildInfo")))//双击的是公会管理菜单
	{
		if(guildManage.m_hWnd!=NULL)
		{
			::SetWindowPos(guildManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGuildInfoRead")))//双击的是恢复角色菜单
	{
		if(guildInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(guildInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBankItem")))//双击的是银行信息菜单
	{
		if(bankInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(bankInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_BankManage")))//双击的是银行管理菜单
	{
		if(bankManage.m_hWnd!=NULL)
		{
			::SetWindowPos(bankManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GCCG_CG2_ItemInfo")))//双击的是道具信息菜单
	{
		if(itemInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(itemInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicItemDel")))//双击的是道具信息菜单
	{
		if(delItemInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(delItemInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicPetInfo")))//双击的是宠物信息菜单
	{
		if(petInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(petInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetManage")))//双击的是宠物管理菜单
	{
		if(petManage.m_hWnd!=NULL)
		{
			::SetWindowPos(petManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetPic")))//双击的是宠物图鉴菜单
	{
		if(petPic.m_hWnd!=NULL)
		{
			::SetWindowPos(petPic.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetSkillManage")))//双击的是修改宠物技能信息
	{
		if(petSkillManage.m_hWnd!=NULL)
		{
			::SetWindowPos(petSkillManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_TmpPwd")))//双击的是修改宠物技能信息
	{
		if(tmpPwd.m_hWnd!=NULL)
		{
			::SetWindowPos(tmpPwd.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_ChangeCharNo")))//双击的是角色换位信息
	{
		if(changeCharNo.m_hWnd!=NULL)
		{
			::SetWindowPos(changeCharNo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicMoveCharacter")))//双击的是移动角色坐标
	{
		if(changeMap.m_hWnd!=NULL)
		{
			::SetWindowPos(changeMap.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicSendAsk")))//双击的是发送问答信息
	{
		if(sendAsk.m_hWnd!=NULL)
		{
			::SetWindowPos(sendAsk.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGetBuyLog")))//双击的是发送问答信息
	{
		if(userShoppingInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(userShoppingInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicSendMail")))//双击的是发送问答信息
	{
		if(sendItemPwd.m_hWnd!=NULL)
		{
			::SetWindowPos(sendItemPwd.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAccountActive")))//双击的是帐户激活查询（魔力宝贝2）
	{
		if(accountActive.m_hWnd!=NULL)
		{
			::SetWindowPos(accountActive.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBanKick")))//双击的是玩家封停被踢次数（魔力宝贝2）
	{
		if(accountBan.m_hWnd!=NULL)
		{
			::SetWindowPos(accountBan.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_RecallLogItem")))//双击的是恢复日志道具（魔力宝贝2）
	{
		if(recallLogItem.m_hWnd!=NULL)
		{
			::SetWindowPos(recallLogItem.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicRecoverPetLog")))//双击的是恢复日志宠物（魔力宝贝2）
	{
		if(recallLogPet.m_hWnd!=NULL)
		{
			::SetWindowPos(recallLogPet.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	return FALSE;
}
//选择给不同的子对话框发送消息
extern "C" __declspec(dllexport) void CG2_DIALOGMSG(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam)
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
		if(loginInfo.m_hWnd != NULL)
		{
			::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(loginInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(logQuery.m_hWnd != NULL)
		{
			::SetParent(logQuery.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(logQuery.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(updateChar.m_hWnd != NULL)
		{
			::SetParent(updateChar.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(updateChar.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(updateSkill.m_hWnd != NULL)
		{
			::SetParent(updateSkill.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(updateSkill.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(addItem.m_hWnd != NULL)
		{
			::SetParent(addItem.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(addItem.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(bakAccount.m_hWnd!=NULL)
		{
			::SetParent(bakAccount.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(bakAccount.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(bakAccountInfo.m_hWnd!=NULL)
		{
			::SetParent(bakAccountInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(bakAccountInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(guildManage.m_hWnd!=NULL)
		{
			::SetParent(guildManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}

		if(guildInfo.m_hWnd!=NULL)
		{
			::SetParent(guildInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(bankInfo.m_hWnd!=NULL)
		{
			::SetParent(bankInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(bankInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(bankManage.m_hWnd!=NULL)
		{
			::SetParent(bankManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(bankManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(itemInfo.m_hWnd!=NULL)
		{
			::SetParent(itemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(delItemInfo.m_hWnd!=NULL)
		{
			::SetParent(delItemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(delItemInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(petInfo.m_hWnd!=NULL)
		{
			::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(petManage.m_hWnd!=NULL)
		{
			::SetParent(petManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(petPic.m_hWnd!=NULL)
		{
			::SetParent(petPic.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petPic.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(petSkillManage.m_hWnd!=NULL)
		{
			::SetParent(petSkillManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petSkillManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(tmpPwd.m_hWnd!=NULL)
		{
			::SetParent(tmpPwd.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(tmpPwd.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(changeCharNo.m_hWnd!=NULL)
		{
			::SetParent(changeCharNo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(changeCharNo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(changeMap.m_hWnd!=NULL)
		{
			::SetParent(changeMap.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(changeMap.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(sendAsk.m_hWnd!=NULL)
		{
			::SetParent(sendAsk.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(sendAsk.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(userShoppingInfo.m_hWnd!=NULL)
		{
			::SetParent(userShoppingInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userShoppingInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(sendItemPwd.m_hWnd!=NULL)
		{
			::SetParent(sendItemPwd.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(sendItemPwd.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(accountActive.m_hWnd!=NULL)
		{
			::SetParent(accountActive.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(accountActive.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(accountBan.m_hWnd!=NULL)
		{
			::SetParent(accountBan.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(accountBan.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(recallLogItem.m_hWnd!=NULL)
		{
			::SetParent(recallLogItem.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(recallLogItem.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(recallLogPet.m_hWnd!=NULL)
		{
			::SetParent(recallLogPet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(recallLogPet.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicUserInfo")))//选中了查询用户信息
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicKickPlayer")))//选中了强制玩家下线
	{
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}

	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBanPlayer")))//选中了玩家帐号解封停
	{
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicNoticeInfo")))//选中了公告信息
	{
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAccountLogin")))//选中了登入信息
	{
		if(loginInfo.m_hWnd != NULL)
		{
			::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(loginInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	//maple add
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicMailLog")))//双击的是玩家日志查询菜单
	{
		if(logQuery.m_hWnd != NULL)
		{
			::SetParent(logQuery.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(logQuery.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicModiCharInfo")))//双击的是修改玩家角色信息菜单
	{
		if(updateChar.m_hWnd != NULL)
		{
			::SetParent(updateChar.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(updateChar.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_UpdateSkill")))//双击的是修改玩家技能信息菜单
	{
		if(updateSkill.m_hWnd != NULL)
		{
			::SetParent(updateSkill.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(updateSkill.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAddItem")))//双击的是添加道具菜单
	{
		if(addItem.m_hWnd != NULL)
		{
			::SetParent(addItem.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(addItem.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicResumeChar")))//双击的是恢复角色菜单
	{
		if(bakAccount.m_hWnd != NULL)
		{
			::SetParent(bakAccount.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(bakAccount.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_BakAccountInfo")))//双击的是恢复角色(只读)菜单
	{
		if(bakAccountInfo.m_hWnd != NULL)
		{
			::SetParent(bakAccountInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(bakAccountInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGuildInfo")))//双击的是公会管理
	{
		if(guildManage.m_hWnd != NULL)
		{
			::SetParent(guildManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}	

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGuildInfoRead")))//双击的是公会管理
	{
		if(guildInfo.m_hWnd != NULL)
		{
			::SetParent(guildInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBankItem")))//双击的是银行信息
	{
		if(bankInfo.m_hWnd != NULL)
		{
			::SetParent(bankInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(bankInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_BankManage")))//双击的是银行管理
	{
		if(bankManage.m_hWnd != NULL)
		{
			::SetParent(bankManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(bankManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicPackGoods")))//双击的是道具信息
	{
		if(itemInfo.m_hWnd != NULL)
		{
			::SetParent(itemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicItemDel")))//双击的是删除道具信息
	{
		if(delItemInfo.m_hWnd != NULL)
		{
			::SetParent(delItemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(delItemInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicPetInfo")))//双击的是宠物信息
	{
		if(petInfo.m_hWnd != NULL)
		{
			::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetManage")))//双击的是宠物管理
	{
		if(petManage.m_hWnd != NULL)
		{
			::SetParent(petManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetPic")))//双击的是宠物图鉴
	{
		if(petPic.m_hWnd != NULL)
		{
			::SetParent(petPic.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petPic.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetSkillManage")))//双击的是宠物技能管理
	{
		if(petSkillManage.m_hWnd != NULL)
		{
			::SetParent(petSkillManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petSkillManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_TmpPwd")))//双击的是修改玩家临时密码
	{
		if(tmpPwd.m_hWnd != NULL)
		{
			::SetParent(tmpPwd.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(tmpPwd.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_ChangeCharNo")))//双击的是角色换位
	{
		if(changeCharNo.m_hWnd != NULL)
		{
			::SetParent(changeCharNo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(changeCharNo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicMoveCharacter")))//双击的是移动角色坐标
	{
		if(changeMap.m_hWnd != NULL)
		{
			::SetParent(changeMap.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(changeMap.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicSendAsk")))//双击的是发送问答信息
	{
		if(sendAsk.m_hWnd != NULL)
		{
			::SetParent(sendAsk.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(sendAsk.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGetBuyLog")))//双击的是发送问答信息
	{
		if(userShoppingInfo.m_hWnd != NULL)
		{
			::SetParent(userShoppingInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userShoppingInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicSendMail")))//双击的是发送问答信息
	{
		if(sendItemPwd.m_hWnd != NULL)
		{
			::SetParent(sendItemPwd.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(sendItemPwd.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAccountActive")))//双击的是发送问答信息
	{
		if(accountActive.m_hWnd != NULL)
		{
			::SetParent(accountActive.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(accountActive.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBanKick")))//双击的是发送问答信息
	{
		if(accountBan.m_hWnd != NULL)
		{
			::SetParent(accountBan.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(accountBan.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_RecallLogItem")))//双击的是发送问答信息
	{
		if(recallLogItem.m_hWnd != NULL)
		{
			::SetParent(recallLogItem.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(recallLogItem.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicRecoverPetLog")))//双击的是发送问答信息
	{
		if(recallLogPet.m_hWnd != NULL)
		{
			::SetParent(recallLogPet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(recallLogPet.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}


}
extern "C" __declspec(dllexport) void GETCG2MESSAGE(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.m_TagID = m_message_tag_id;
	OperationCG2 operCG2;

	switch(m_message_tag_id)
	{	
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://服务器信息
		{
			if((userInfo.m_hWnd!=NULL)&&(userInfo.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd!=NULL)&&(kickPlayer.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd!=NULL)&&(banPlayer.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((noticeInfo.m_hWnd!=NULL)&&(noticeInfo.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((loginInfo.m_hWnd!=NULL)&&(loginInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				loginInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			//maple add
			else if((logQuery.m_hWnd!=NULL)&&(logQuery.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//玩家日志查询中服务器列表查询
			{
				logQuery.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((updateChar.m_hWnd!=NULL)&&(updateChar.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//修改玩家角色信息
			{
				updateChar.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((updateSkill.m_hWnd!=NULL)&&(updateSkill.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//修改玩家技能信息
			{
				updateSkill.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((addItem.m_hWnd!=NULL)&&(addItem.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//添加道具信息
			{
				addItem.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bakAccount.m_hWnd!=NULL)&&(bakAccount.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//恢复角色信息
			{
				bakAccount.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bakAccountInfo.m_hWnd!=NULL)&&(bakAccountInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//恢复角色(只读)信息
			{
				bakAccountInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildManage.m_hWnd!=NULL)&&(guildManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//公会管理
			{
				guildManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildInfo.m_hWnd!=NULL)&&(guildInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//公会信息
			{
				guildInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bankInfo.m_hWnd!=NULL)&&(bankInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//银行信息
			{
				bankInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bankManage.m_hWnd!=NULL)&&(bankManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//银行管理
			{
				bankManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemInfo.m_hWnd!=NULL)&&(itemInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//道具信息
			{
				itemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((delItemInfo.m_hWnd!=NULL)&&(delItemInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//删除道具信息
			{
				delItemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petInfo.m_hWnd!=NULL)&&(petInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//宠物信息
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petManage.m_hWnd!=NULL)&&(petManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//宠物管理
			{
				petManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petSkillManage.m_hWnd!=NULL)&&(petSkillManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//宠物管理
			{
				petSkillManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petPic.m_hWnd!=NULL)&&(petPic.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//宠物管理
			{
				petPic.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((tmpPwd.m_hWnd!=NULL)&&(tmpPwd.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//宠物管理
			{
				tmpPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((changeCharNo.m_hWnd!=NULL)&&(changeCharNo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//角色换位
			{
				changeCharNo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((changeMap.m_hWnd!=NULL)&&(changeMap.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//移动角色坐标
			{
				changeMap.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((sendAsk.m_hWnd!=NULL)&&(sendAsk.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//移动角色坐标
			{
				sendAsk.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((sendItemPwd.m_hWnd!=NULL)&&(sendItemPwd.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//移动角色坐标
			{
				sendItemPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((accountActive.m_hWnd!=NULL)&&(accountActive.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//移动角色坐标
			{
				accountActive.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((accountBan.m_hWnd!=NULL)&&(accountBan.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//移动角色坐标
			{
				accountBan.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((recallLogItem.m_hWnd!=NULL)&&(recallLogItem.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//移动角色坐标
			{
				recallLogItem.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((recallLogPet.m_hWnd!=NULL)&&(recallLogPet.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//移动角色坐标
			{
				recallLogPet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Query_Resp://用户资料查询
		{
			if((userInfo.m_hWnd!=NULL)&&(userInfo.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd!=NULL)&&(kickPlayer.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd!=NULL)&&(banPlayer.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			//maple add
			else if((logQuery.m_hWnd!=NULL)&&(logQuery.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//玩家日志查询中服务器列表查询
			{
				logQuery.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((updateChar.m_hWnd!=NULL)&&(updateChar.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//修改玩家角色信息
			{
				updateChar.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((updateSkill.m_hWnd!=NULL)&&(updateSkill.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//修改玩家技能信息
			{
				updateSkill.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((addItem.m_hWnd!=NULL)&&(addItem.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//添加道具信息
			{
				addItem.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemInfo.m_hWnd!=NULL)&&(itemInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//角色道具信息
			{
				itemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((delItemInfo.m_hWnd!=NULL)&&(delItemInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//角色道具信息
			{
				delItemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petInfo.m_hWnd!=NULL)&&(petInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//宠物信息
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petManage.m_hWnd!=NULL)&&(petManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//宠物资料信息
			{
				petManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bankInfo.m_hWnd!=NULL)&&(bankInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//银行信息
			{
				bankInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bankManage.m_hWnd!=NULL)&&(bankManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//银行管理
			{
				bankManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petPic.m_hWnd!=NULL)&&(petPic.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//宠物图鉴
			{
				petPic.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petSkillManage.m_hWnd!=NULL)&&(petSkillManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//宠物管理
			{
				petSkillManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((tmpPwd.m_hWnd!=NULL)&&(tmpPwd.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//宠物管理
			{
				tmpPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((changeCharNo.m_hWnd!=NULL)&&(changeCharNo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//角色换位
			{
				changeCharNo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((changeMap.m_hWnd!=NULL)&&(changeMap.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//移动角色坐标
			{
				changeMap.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((sendAsk.m_hWnd!=NULL)&&(sendAsk.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//发送问答信息
			{
				sendAsk.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((sendItemPwd.m_hWnd!=NULL)&&(sendItemPwd.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//发送问答信息
			{
				sendItemPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Detail_Query_Resp ://角色详细资料
	case CEnumCore::Message_Tag_ID::CG2_Account_Attribute_Query_Resp://角色属性资料
	case CEnumCore::Message_Tag_ID::CG2_Account_Guild_Query_Resp://角色工会资料
	case CEnumCore::Message_Tag_ID::CG2_Account_Title_Query_Resp://角色称号资料
	case CEnumCore::Message_Tag_ID::CG2_Account_Address_Query_Resp://角色社会关系
	case CEnumCore::Message_Tag_ID::CG2_Account_Skill_Query_Resp ://角色技能信息////maple add
		{
			if((userInfo.m_hWnd!=NULL)&&(userInfo.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((updateSkill.m_hWnd!=NULL)&&(updateSkill.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//修改玩家技能信息
			{
				updateSkill.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Teach_Query_Resp ://查看玩家师生关系
	case CEnumCore::Message_Tag_ID::CG2_LoveTree_Query_Resp://查看爱情树
	case CEnumCore::Message_Tag_ID::CG2_Marriage_Info_Query_Resp://查看玩家婚姻信息
		{
			if((userInfo.m_hWnd!=NULL)&&(userInfo.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_KickAccount_Query_Resp ://踢下线
		{
			if((kickPlayer.m_hWnd!=NULL)&&(kickPlayer.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Close_RESP://封停玩家帐号响应
	case CEnumCore::Message_Tag_ID::CG2_Account_Open_RESP://解封玩家帐号响应
	case CEnumCore::Message_Tag_ID::CG2_Account_BANISHMENT_QUERY_RESP://查询玩家帐号有没有被封停
	case CEnumCore::Message_Tag_ID::CG2_BanAccount_Query_Resp://查询所有封停玩家帐号信息
		{
			if((banPlayer.m_hWnd!=NULL)&&(banPlayer.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_SendNote_Query_Resp://发送公告
	case CEnumCore::Message_Tag_ID::CG2_UpdateNote_Query_Resp://修改公告
	case CEnumCore::Message_Tag_ID::CG2_DeleteNote_Query_Resp://删除公告
	case CEnumCore::Message_Tag_ID::CG2_SearchNote_Query_Resp://查看公告
		{
			if((noticeInfo.m_hWnd != NULL)&&(noticeInfo.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Use_Query_Resp://玩家登陆日志
		{
			if((loginInfo.m_hWnd != NULL)&&(loginInfo.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				loginInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
		//maple add
	case CEnumCore::Message_Tag_ID::CG2_Log_Query_Resp:////查询玩家日志信息
		{
			if((logQuery.m_hWnd!=NULL)&&(logQuery.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				logQuery.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Job_Query_Resp://查询职业种类
	case CEnumCore::Message_Tag_ID::CG2_UpdateJob_Query_Resp://修改玩家角色职业
		{
			if((updateChar.m_hWnd!=NULL)&&(updateChar.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				updateChar.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;

	case CEnumCore::Message_Tag_ID::CG2_GerSkill_Query_Resp://技能类别查询
	case CEnumCore::Message_Tag_ID::CG2_SkillList_Query_Resp://技能名称查询
		{
			if((updateSkill.m_hWnd!=NULL)&&(updateSkill.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				updateSkill.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petSkillManage.m_hWnd!=NULL)&&(petSkillManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petSkillManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Update_Account_Skill_Query_Resp://修改角色技能等级
	case CEnumCore::Message_Tag_ID::CG2_Insert_Account_Skill_Query_Resp://添加角色技能信息
		{
			if((updateSkill.m_hWnd!=NULL)&&(updateSkill.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				updateSkill.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Get_Item_Query_Resp://道具类别查询
	case CEnumCore::Message_Tag_ID::CG2_Get_Item_Detail_Query_Resp://道具名称查询
		{
			if((addItem.m_hWnd!=NULL)&&(addItem.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				addItem.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bankManage.m_hWnd!=NULL)&&(bankManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				bankManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Insert_Item_Query_Resp://添加道具
		{
			if((addItem.m_hWnd!=NULL)&&(addItem.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				addItem.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_BakAccount_Query_Resp://查询备份玩家角色信息
		{
			if((bakAccount.m_hWnd!=NULL)&&(bakAccount.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				bakAccount.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bakAccountInfo.m_hWnd!=NULL)&&(bakAccountInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				bakAccountInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Recovery_Account_Qurey_Resp:
		{
			if((bakAccount.m_hWnd!=NULL)&&(bakAccount.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				bakAccount.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_SearchGuild_Query_Resp://公会信息
	case CEnumCore::Message_Tag_ID::CG2_SearchGuild_Detail_Query_Resp://公会成员
		{
			if((guildManage.m_hWnd!=NULL)&&(guildManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				guildManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildInfo.m_hWnd!=NULL)&&(guildInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				guildInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}	
		break;
	case CEnumCore::Message_Tag_ID::CG2_RenameGuild_Query_Resp://修改公会名称
	case CEnumCore::Message_Tag_ID::CG2_UpdateGuildLv_Query_Resp://修改公会等级
	case CEnumCore::Message_Tag_ID::CG2_UpdateGuildHonor_Query_Resp://修改公会荣誉
		{
			if((guildManage.m_hWnd!=NULL)&&(guildManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				guildManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			
		}	
		break;
	case CEnumCore::Message_Tag_ID::CG2_PackItem_Query_Resp://角色背包道具信息
	case CEnumCore::Message_Tag_ID::CG2_TempItem_Query_Resp://角色临时背包信息
	case CEnumCore::Message_Tag_ID::CG2_CharItem_Query_Resp://身上装备信息
		{
			if((itemInfo.m_hWnd!=NULL)&&(itemInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				itemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((delItemInfo.m_hWnd!=NULL)&&(delItemInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				delItemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_ShopItem_Query_Resp://收费道具查询
		{
			if((itemInfo.m_hWnd!=NULL)&&(itemInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				itemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_PetInfo_Query_Resp://宠物基本信息
			if((petInfo.m_hWnd!=NULL)&&(petInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petManage.m_hWnd!=NULL)&&(petManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petSkillManage.m_hWnd!=NULL)&&(petSkillManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//宠物管理
			{
				petSkillManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		break;
	case CEnumCore::Message_Tag_ID::CG2_PetSkill_Query_Resp://宠物技能信息
		{
			if((petInfo.m_hWnd!=NULL)&&(petInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petSkillManage.m_hWnd!=NULL)&&(petSkillManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//宠物管理
			{
				petSkillManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Update_Pet_Query_Resp://修改宠物属性
	case CEnumCore::Message_Tag_ID::CG2_AddPet_Query_Resp://添加宠物
	case CEnumCore::Message_Tag_ID::CG2_UpdatePetLevel_Query_Resp://修改宠物等级
		{
			if((petManage.m_hWnd!=NULL)&&(petManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_PetList_Query_Resp://宠物列表查询
		{
			if((petManage.m_hWnd!=NULL)&&(petManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petPic.m_hWnd!=NULL)&&(petPic.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petPic.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_PetItem_Query_Resp://宠物物品信息
		{
			if((petInfo.m_hWnd!=NULL)&&(petInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_BankItem_Query_Resp://银行物品信息
		{
			if((bankInfo.m_hWnd!=NULL)&&(bankInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				bankInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((delItemInfo.m_hWnd!=NULL)&&(delItemInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				delItemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bankManage.m_hWnd!=NULL)&&(bankManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				bankManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_BankInfo_Query_Resp://银行存款信息
		{
			if((bankInfo.m_hWnd!=NULL)&&(bankInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				bankInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bankManage.m_hWnd!=NULL)&&(bankManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				bankManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_BankPet_Query_Resp://银行宠物信息
		{
			if((bankInfo.m_hWnd!=NULL)&&(bankInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				bankInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Insert_Pet_Skill_Query_Resp://银行宠物信息
	case CEnumCore::Message_Tag_ID::CG2_Update_Pet_Skill_Query_Resp://
		{
			if((petSkillManage.m_hWnd!=NULL)&&(petSkillManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petSkillManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_PetPic_Query_Resp://银行宠物信息
	case CEnumCore::Message_Tag_ID::CG2_PetPic_Del_Query_Resp:
		{
			if((petPic.m_hWnd!=NULL)&&(petPic.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petPic.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Insert_TmpPwd_Query_Resp://银行宠物信息
	case CEnumCore::Message_Tag_ID::CG2_Recover_TmpPwd_Query_Resp:
	case CEnumCore::Message_Tag_ID::CG2_SearchPassWord_Query_Resp:
		{
			if((tmpPwd.m_hWnd!=NULL)&&(tmpPwd.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				tmpPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_ChangeCharNo_Query_Resp:
		{
			if((changeCharNo.m_hWnd!=NULL)&&(changeCharNo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				changeCharNo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Change_Map_Query_Resp:
	case CEnumCore::Message_Tag_ID::CG2_MapList_Query_Resp:
	case CEnumCore::Message_Tag_ID::CG2_SearchMap_Query_Resp:
		{
			if((changeMap.m_hWnd!=NULL)&&(changeMap.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				changeMap.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_BagItem_Del_Query_Resp:
	case CEnumCore::Message_Tag_ID::CG2_TmpItem_Del_Query_Resp:
	case CEnumCore::Message_Tag_ID::CG2_EquipItem_Del_Query_Resp:
	case CEnumCore::Message_Tag_ID::CG2_BankItem_Del_Query_Resp:
		{
			if((delItemInfo.m_hWnd!=NULL)&&(delItemInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				delItemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_SendAsk_Query_Resp:
		{
			if((sendAsk.m_hWnd!=NULL)&&(sendAsk.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				sendAsk.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_InsertBankItem_Query_Resp:
	case CEnumCore::Message_Tag_ID::CG2_SetBankMoney_Query_Resp:
	case CEnumCore::Message_Tag_ID::CG2_InsertBankItemALL_Query:
		{
			if((bankManage.m_hWnd!=NULL)&&(bankManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				bankManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_UserShoppingInfo_Query_Resp:
		{
			if((userShoppingInfo.m_hWnd!=NULL)&&(userShoppingInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				userShoppingInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Send_ItemPassword_Resp:
	case CEnumCore::Message_Tag_ID::CG2_Get_EmailAddress_Resp:
		{
			if((sendItemPwd.m_hWnd!=NULL)&&(sendItemPwd.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				sendItemPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Active_Query_Resp:
	case CEnumCore::Message_Tag_ID::CG2_Sn_Active_Query_Resp:
		{
			if((accountActive.m_hWnd!=NULL)&&(accountActive.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				accountActive.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	default:
		break;
	}
}

//再次发送同样的Query
extern "C" __declspec(dllexport) void CG2_SENDINFOAGAIN()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//theApp.operGTOWN.SendSameQuery();
}

extern "C" __declspec(dllexport) void GETCG2INFO(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent, int* m_SelectDll)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//theApp.mSocket = m_socket;
	theApp.UserByID = userByID;
	theApp.userName = userName;
	theApp.mHwndParent = m_HwndParent;
	theApp.operCG2.initSocket(m_socket);//operPAL.initSocket(m_socket);
	theApp.operCG2.intCG2 = m_SelectDll;//operPAL.intPAL = m_SelectDll;
}