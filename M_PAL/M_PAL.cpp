// M_PAL.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "M_PAL.h"
#include "PALUserInfo.h"
#include "PALKickPlayer.h"
#include "PALBanPlayer.h"
#include "PALNoticeInfo.h"
#include "PALGuildManage.h"
#include "PALLogInfo.h"
#include "PALItemInfo.h"
#include "PALItemManage.h"
#include "PALRoleManage.h"
#include "PALGuildInfo.h"
#include "PALMailBoxInfo.h"
#include "PALAccountLogin.h"
#include "PALShopBuyLog.h"
#include "QueryBanInfo.h"
#include "PALAuctionInfo.h"
#include "PALCDKeyItemGet.h"
#include "PALSendPwd.h"
#include "PALHisLogInfo.h"
#include "PALMobInfo.h"
#include "PALMobManage.h"
#include "PALPuzzleMapInfo.h"
#include "PALPuzzleMapManage.h"
#include "PALMoveToSafe.h"
#include "PALRoleDel.h"
#include "PALCharacterInfo.h"
#include "PALSendCustomerItem.h"
#include "PALUserInfoOnly.h"


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

// CM_PALApp

BEGIN_MESSAGE_MAP(CM_PALApp, CWinApp)
END_MESSAGE_MAP()


// CM_PALApp 构造

CM_PALApp::CM_PALApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CM_PALApp 对象

CM_PALApp theApp;
CPALUserInfo userInfo;
CPALKickPlayer kickPlayer;
CPALBanPlayer banPlayer;
CPALNoticeInfo noticeInfo;
CPALGuildManage guildmanage;
CPALRoleManage roleManage;
CPALLogInfo logInfo;
CPALHisLogInfo hislogInfo;
CPALItemInfo itemInfo;
CPALItemManage itemManage;
CPALGuildInfo guildInfo;
CPALMailBoxInfo mailBoxInfo;
CPALAccountLogin accountLogin;
CPALShopBuyLog shopBuyLog;
CQueryBanInfo queryBanInfo;
CPALAuctionInfo auctionInfo;
CPALCDKeyItemGet CDKeyItemGet;
CPALSendPwd sendUserPwd;
CPALMobInfo mobInfo;
CPALMobManage mobManage;
CPALPuzzleMapInfo puzzleMapInfo;
CPALPuzzleMapManage puzzleMapManage;
CPALMoveToSafe moveToSafe;
CPALRoleDel roleDel;

CPALCharacterInfo characterInfo;
CPALSendCustomerItem sendCustomerItem;
//add by ltx
CPALUserInfoOnly userInfoOnly;

// CM_PALApp 初始化

BOOL CM_PALApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" __declspec(dllexport) BOOL PAL_TRANSLATEMESSAGE(MSG* pMsg)
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
				if(guildmanage.m_hWnd != NULL)
				{
					guildmanage.PreTranslateMessage(pMsg);
				}
				if(roleManage.m_hWnd != NULL)
				{
					roleManage.PreTranslateMessage(pMsg);
				}
				if(logInfo.m_hWnd != NULL)
				{
					logInfo.PreTranslateMessage(pMsg);
				}
				if(hislogInfo.m_hWnd!=NULL)
				{
					hislogInfo.PreTranslateMessage(pMsg);
				}
				if(itemInfo.m_hWnd != NULL)
				{
					itemInfo.PreTranslateMessage(pMsg);
				}
				if(itemManage.m_hWnd != NULL)
				{
					itemManage.PreTranslateMessage(pMsg);
				}
				if(guildInfo.m_hWnd != NULL)
				{
					guildInfo.PreTranslateMessage(pMsg);
				}
				if(mailBoxInfo.m_hWnd != NULL)
				{
					mailBoxInfo.PreTranslateMessage(pMsg);
				}
				if(accountLogin.m_hWnd != NULL)
				{
					accountLogin.PreTranslateMessage(pMsg);
				}
				if(shopBuyLog.m_hWnd != NULL)
				{
					shopBuyLog.PreTranslateMessage(pMsg);
				}
				if(queryBanInfo.m_hWnd != NULL)
				{
					queryBanInfo.PreTranslateMessage(pMsg);
				}
				if(auctionInfo.m_hWnd != NULL)
				{
					auctionInfo.PreTranslateMessage(pMsg);
				}
				if(CDKeyItemGet.m_hWnd != NULL)
				{
					CDKeyItemGet.PreTranslateMessage(pMsg);
				}
				if(sendUserPwd.m_hWnd != NULL)
				{
					sendUserPwd.PreTranslateMessage(pMsg);
				}
				if(mobInfo.m_hWnd != NULL)
				{
					mobInfo.PreTranslateMessage(pMsg);
				}
				if(mobManage.m_hWnd != NULL)
				{
					mobManage.PreTranslateMessage(pMsg);
				}
				if(puzzleMapInfo.m_hWnd != NULL)
				{
					puzzleMapInfo.PreTranslateMessage(pMsg);
				}
				if(puzzleMapManage.m_hWnd != NULL)
				{
					puzzleMapManage.PreTranslateMessage(pMsg);
				}
				if(moveToSafe.m_hWnd != NULL)
				{
					moveToSafe.PreTranslateMessage(pMsg);
				}
				if(roleDel.m_hWnd != NULL)
				{
					roleDel.PreTranslateMessage(pMsg);
				}
				if(characterInfo.m_hWnd != NULL)
				{
					characterInfo.PreTranslateMessage(pMsg);
				}
				//add by ltx
				if(userInfoOnly.m_hWnd != NULL)
				{
					userInfoOnly.PreTranslateMessage(pMsg);
				}

			}
		}		
	}
	return FALSE;
}

extern "C" __declspec(dllexport) void GETPALMESSAGE(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.m_TagID = m_message_tag_id;
	OperationPAL operPAL;

	switch(m_message_tag_id)
	{	
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://服务器信息
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((noticeInfo.m_hWnd != NULL) && (noticeInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus==operPAL.ReadIntValue("MPAL","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((roleManage.m_hWnd != NULL) && (roleManage.dlgStatus==operPAL.ReadIntValue("MPAL","Send")))
			{
				roleManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((logInfo.m_hWnd != NULL) && (logInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				logInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((hislogInfo.m_hWnd != NULL) && (hislogInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				hislogInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemInfo.m_hWnd != NULL) && (itemInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				itemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemManage.m_hWnd != NULL) && (itemManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildInfo.m_hWnd != NULL) && (guildInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				guildInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailBoxInfo.m_hWnd != NULL) && (mailBoxInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				mailBoxInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((accountLogin.m_hWnd != NULL) && (accountLogin.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				accountLogin.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((shopBuyLog.m_hWnd != NULL) && (shopBuyLog.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				shopBuyLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((queryBanInfo.m_hWnd != NULL) && (queryBanInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				queryBanInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((auctionInfo.m_hWnd != NULL) && (auctionInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				auctionInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((CDKeyItemGet.m_hWnd != NULL) && (CDKeyItemGet.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				CDKeyItemGet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((sendUserPwd.m_hWnd != NULL) && (sendUserPwd.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				sendUserPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mobInfo.m_hWnd != NULL) && (mobInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				mobInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mobManage.m_hWnd != NULL) && (mobManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				mobManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((puzzleMapInfo.m_hWnd != NULL) && (puzzleMapInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				puzzleMapInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((puzzleMapManage.m_hWnd != NULL) && (puzzleMapManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				puzzleMapManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((moveToSafe.m_hWnd != NULL) && (moveToSafe.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				moveToSafe.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((roleDel.m_hWnd != NULL) && (roleDel.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				roleDel.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((characterInfo.m_hWnd != NULL) && (characterInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				characterInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((sendCustomerItem.m_hWnd != NULL) && (sendCustomerItem.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				sendCustomerItem.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			//add by ltx
			if((userInfoOnly.m_hWnd != NULL) && (userInfoOnly.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				userInfoOnly.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}

		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERINFO_RESP://取得角色基本资讯响应
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((roleManage.m_hWnd != NULL) && (roleManage.dlgStatus==operPAL.ReadIntValue("MPAL","Send")))
			{
				roleManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((logInfo.m_hWnd != NULL) && (logInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				logInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((hislogInfo.m_hWnd != NULL) && (hislogInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				hislogInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemInfo.m_hWnd != NULL) && (itemInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				itemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemManage.m_hWnd != NULL) && (itemManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailBoxInfo.m_hWnd != NULL) && (mailBoxInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				mailBoxInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((accountLogin.m_hWnd != NULL) && (accountLogin.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				accountLogin.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((shopBuyLog.m_hWnd != NULL) && (shopBuyLog.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				shopBuyLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((queryBanInfo.m_hWnd != NULL) && (queryBanInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				queryBanInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((auctionInfo.m_hWnd != NULL) && (auctionInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				auctionInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((CDKeyItemGet.m_hWnd != NULL) && (CDKeyItemGet.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				CDKeyItemGet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((sendUserPwd.m_hWnd != NULL) && (sendUserPwd.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				sendUserPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mobInfo.m_hWnd != NULL) && (mobInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				mobInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mobManage.m_hWnd != NULL) && (mobManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				mobManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((puzzleMapInfo.m_hWnd != NULL) && (puzzleMapInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				puzzleMapInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((puzzleMapManage.m_hWnd != NULL) && (puzzleMapManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				puzzleMapManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((moveToSafe.m_hWnd != NULL) && (moveToSafe.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				moveToSafe.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((characterInfo.m_hWnd != NULL) && (characterInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				characterInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((sendCustomerItem.m_hWnd != NULL) && (sendCustomerItem.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				sendCustomerItem.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			//add by ltx
			if((userInfoOnly.m_hWnd != NULL) && (userInfoOnly.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				userInfoOnly.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;

	case CEnumCore::Message_Tag_ID::PAL_CHARACTERFRIENDLIST_RESP://角色好友列表
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERQUEST_RESP://角色任务
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERADVANCEINFO_RESP://角色进阶资讯
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERSKILL_RESP://角色技能资讯
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERBLACKLIST_RESP://角色黑名单列表
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((roleManage.m_hWnd != NULL) && (roleManage.dlgStatus==operPAL.ReadIntValue("MPAL","Send")))
			{
				roleManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_BANISHPLAYER_RESP://强制玩家下线
		{
			if(kickPlayer.m_hWnd != NULL)
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给强制玩家下线界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_ACCOUNT_CLOSE_RESP://封停玩家帐号
	case CEnumCore::Message_Tag_ID::PAL_ACCOUNT_OPEN_RESP://解封玩家帐号	
	case CEnumCore::Message_Tag_ID::PAL_ACCOUNTLOCAL_QUERY_RESP://查询所有封停帐号
	case CEnumCore::Message_Tag_ID::PAL_RELOADFUNCTIONSWITCH_RESP://返回批量封停的结果//maple add
		{
			if(banPlayer.m_hWnd != NULL)
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给玩家帐号解封停界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_ACCOUNT_BANISHMENT_QUERY_RESP://查询帐号有没有被封停
		{
			if(queryBanInfo.m_hWnd != NULL)
			{
				queryBanInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给查询玩家帐号封停情况界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_GUILDBASEINFO_RESP://公会信息的回应
	case CEnumCore::Message_Tag_ID::PAL_GUILDMEMBERLIST_RESP://公会列表回应
		{
			if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus==operPAL.ReadIntValue("MPAL","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给公会信息界面发消息
			}
			else if((guildInfo.m_hWnd != NULL) && (guildInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				guildInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_DISMISSGUILD_RESP://解散公会回应
	case CEnumCore::Message_Tag_ID::PAL_MODIFYGUILDLV_RESP://更改公会等级回应
	case CEnumCore::Message_Tag_ID::PAL_MODIFYGUILDNAME_RESP://更改公会名称回应
	case CEnumCore::Message_Tag_ID::PAL_MODIFYGUILDMEMBERPL_RESP://更改公会成员职级回应
	case CEnumCore::Message_Tag_ID::PAL_MODIFYGUILDNOTICE_RESP://修改公会公告响应
		{
			if(guildmanage.m_hWnd != NULL)
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给公会管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_BOARDTASK_INSERT_RESP://公告添加响应
	case CEnumCore::Message_Tag_ID::PAL_BOARDTASK_QUERY_RESP://公告查询响应
	case CEnumCore::Message_Tag_ID::PAL_BOARDTASK_UPDATE_RESP://公告更新响应
		{
			if(noticeInfo.m_hWnd != NULL)
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给公告信息界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_MODIFYACCOUNTPW_RESP://修改角色游戏密码的回应
	case CEnumCore::Message_Tag_ID::PAL_RECALLACCOUNTPW_RESP://恢复角色游戏密码的回应
	case CEnumCore::Message_Tag_ID::PAL_MODIFYCHARACTERDROPPW_RESP://修改角色删除密码的回应
	case CEnumCore::Message_Tag_ID::PAL_RECALLCHARACTERDROPPW_RESP://恢复角色删除密码的回应	
	case CEnumCore::Message_Tag_ID::PAL_MODIFYACCOUNTBANKPW_RESP://修改角色银行密码的回应
	case CEnumCore::Message_Tag_ID::PAL_RECALLACCOUNTBANKPW_RESP://恢复角色银行密码的回应
	case CEnumCore::Message_Tag_ID::PAL_MODIFYCHARACTERMONEY_RESP://修改角色金钱的回应
	case CEnumCore::Message_Tag_ID::PAL_MODIFYCHARACTERQUEST_RESP://修改角色人物状态的回应
	case CEnumCore::Message_Tag_ID::PAL_MODIFYSECONDPW_RESP://修改二级密码的回应
	case CEnumCore::Message_Tag_ID::PAL_RECALLSECONDPW_RESP://恢复二级密码的回应
	case CEnumCore::Message_Tag_ID::PAL_USESAFELOCK_RESP://使用安全锁
	case CEnumCore::Message_Tag_ID::PAL_FREESAFELOCK_RESP://释放安全锁响应
	case CEnumCore::Message_Tag_ID::PAL_MODIFYACCOUNTPWALL_RESP://修改全部大区临时密码的回应
	case CEnumCore::Message_Tag_ID::PAL_RECALLACCOUNTPWALL_RESP://恢复全部大区临时密码的回应
		{
			if(roleManage.m_hWnd!=NULL)
			{
				roleManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_LOG_BIGTYPE_QUERY_RESP://日志大类信息
	case CEnumCore::Message_Tag_ID::PAL_LOG_SMALLTYPE_QUERY_RESP://日志小类信息
		{
			if((logInfo.m_hWnd != NULL) && (logInfo.dlgStatus==operPAL.ReadIntValue("MPAL","Send")))
			{
				logInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给日志信息界面发消息
			}
			else if((hislogInfo.m_hWnd != NULL) && (hislogInfo.dlgStatus==operPAL.ReadIntValue("MPAL","Send")))
			{
				hislogInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给日志信息界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_LOGINFO_QUERY_RESP://日志信息
		{
			if(logInfo.m_hWnd!=NULL)
			{
				logInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给日志信息界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_HISTORY_LOGINFO_QUERY_RESP:
		{
			if(hislogInfo.m_hWnd!=NULL)
			{
				hislogInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给日志信息界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERBAG_RESP://角色背包
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
			else if((itemInfo.m_hWnd != NULL) && (itemInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				itemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给道具信息界面发消息
			}
			else if((itemManage.m_hWnd != NULL) && (itemManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给道具管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_DELCHARACTERITEM_RESP://删除角色背包
	case CEnumCore::Message_Tag_ID::PAL_SENDGIFTMAIL_RESP://发送道具
	case CEnumCore::Message_Tag_ID::PAL_ITEMTYPE_QUERY_RESP://查询道具类别信息的回应
	case CEnumCore::Message_Tag_ID::PAL_ITEMNAME_QUERY_RESP://查询道具名称信息的回应
		{
			if(itemManage.m_hWnd!=NULL)
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给道具管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHECKMAILBOX_QUERY_RESP://玩家邮箱信息查询
	case CEnumCore::Message_Tag_ID::PAL_CHECKMAILBOX_DETAIL_RESP://玩家邮件附件查询
		{
			if(mailBoxInfo.m_hWnd!=NULL)
			{
				mailBoxInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给玩家邮箱信息界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PALLOG_ACCOUNT_LOGIN_RESP://帐号登入登出日志
		{
			if(accountLogin.m_hWnd!=NULL)
			{
				accountLogin.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给帐号登入登出日志界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PALLOG_ITEMMAIL_RESP://商城购买记录
	case CEnumCore::Message_Tag_ID::PAL_ITEMMAIL_WASTE_RESP://元宝消耗记录
		{
			if(shopBuyLog.m_hWnd!=NULL)
			{
				shopBuyLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给商城购买记录界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_AUCTION_QUERY_RESP://玩家拍卖信息
		{
			if(auctionInfo.m_hWnd!=NULL)
			{
				auctionInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给玩家拍卖信息界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CDKEY_QUERY_RESP://CDKey道具领取
		{
			if(CDKeyItemGet.m_hWnd!=NULL)
			{
				CDKeyItemGet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给CDKey道具领取界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_MAILBOX_QUERY_RESP://查询邮箱地址
	case CEnumCore::Message_Tag_ID::PAL_SendBankPwd_Query_RESP://发送仓库密码
	case CEnumCore::Message_Tag_ID::PAL_SendDeletePwd_Query_RESP://发送角色删除密码
		{
			if(sendUserPwd.m_hWnd!=NULL)
			{
				sendUserPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给发送密码界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERMOB_RESP://伏魔信息
		{
			if((mobInfo.m_hWnd != NULL) && (mobInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				mobInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
			else if((mobManage.m_hWnd != NULL) && (mobManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				mobManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给道具信息界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_DELCHARACTERMOB_RESP://伏魔信息
		{
			if((mobManage.m_hWnd != NULL) && (mobManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				mobManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给道具信息界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERPUZZLEMAP_RESP://图鉴信息
		{
			if((puzzleMapInfo.m_hWnd != NULL) && (puzzleMapInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				puzzleMapInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
			else if((puzzleMapManage.m_hWnd != NULL) && (puzzleMapManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				puzzleMapManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给道具信息界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_MODIFYPUZZLEMAP_RESP://图鉴信息
		{
			if((puzzleMapManage.m_hWnd != NULL) && (puzzleMapManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				puzzleMapManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给道具信息界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_MOVECHARACTERTOSAFE_RESP://安全点
	case CEnumCore::Message_Tag_ID::PAL_SearchMap_Query_Resp:
		{
			if((moveToSafe.m_hWnd != NULL) && (moveToSafe.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				moveToSafe.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给道具信息界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_ROLEDEL_QUERY_RESP:
		{
			if((roleDel.m_hWnd != NULL) && (roleDel.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				roleDel.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给道具信息界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_EQUIPMENT_QUERY_RESP://装备查询//PAL_EQUIPMENT_QUERY
		{
			if((sendCustomerItem.m_hWnd != NULL) && (sendCustomerItem.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				sendCustomerItem.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给道具信息界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_SENDCUSTOMITEMMAIL_RESP://寄送客制物品
		{
			if((sendCustomerItem.m_hWnd != NULL) && (sendCustomerItem.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				sendCustomerItem.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给道具信息界面发消息
			}
		}
	default:
		break;
	}
}

//选择打开不同的子对话框
extern "C" __declspec(dllexport) bool PAL_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALUserInfo")))//选中了查询用户信息(仙剑)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALKickPlayer")))//选中了强制玩家(仙剑)下线
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALBanPlayer")))//选中了玩家帐号解封停(仙剑)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALNoticeInfo")))//选中了公告信息(仙剑)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALGuildManage")))//选中了公会管理(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(guildmanage.m_hWnd == NULL)
		{
			guildmanage.Create(IDD_DLGGUILDMANAGE);
			guildmanage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(guildmanage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALRoleManage")))//选中了角色管理(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(roleManage.m_hWnd == NULL)
		{
			roleManage.Create(IDD_DLGROLEMANAGE);
			roleManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(roleManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(roleManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALLogInfo")))//选中了日志信息(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(logInfo.m_hWnd == NULL)
		{
			logInfo.Create(IDD_DLGLOGINFO);
			logInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(logInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(logInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALHisLogInfo")))//选中了日志信息-历史(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(hislogInfo.m_hWnd == NULL)
		{
			hislogInfo.Create(IDD_DLGHISLOGINFO);
			hislogInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(hislogInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(hislogInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALItemInfo")))//选中了道具信息(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(itemInfo.m_hWnd == NULL)
		{
			itemInfo.Create(IDD_DLGITEMINFO);
			itemInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(itemInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALItemManage")))//选中了道具管理(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(itemManage.m_hWnd == NULL)
		{
			itemManage.Create(IDD_DLGITEMMANAGE);
			itemManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(itemManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALGuildInfo")))//选中了公会信息(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(guildInfo.m_hWnd == NULL)
		{
			guildInfo.Create(IDD_DLGGUILDINFO);
			guildInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(guildInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(guildInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMailBoxInfo")))//选中了邮箱信息(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(mailBoxInfo.m_hWnd == NULL)
		{
			mailBoxInfo.Create(IDD_DLGMAILBOXINFO);
			mailBoxInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(mailBoxInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(mailBoxInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_UI_AccountLogin")))//选中了帐号登录信息(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(accountLogin.m_hWnd == NULL)
		{
			accountLogin.Create(IDD_DLGLOGINLOG);
			accountLogin.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(accountLogin.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(accountLogin.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALShopBuyLog")))//选中了商城购买记录(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(shopBuyLog.m_hWnd == NULL)
		{
			shopBuyLog.Create(IDD_DLGSHOPBUYLOG);
			shopBuyLog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(shopBuyLog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(shopBuyLog.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CQueryBanInfo")))//选中了查询特定玩家帐号有没有被封停(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(queryBanInfo.m_hWnd == NULL)
		{
			queryBanInfo.Create(IDD_DLGQUERYBAN);
			queryBanInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(queryBanInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(queryBanInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALAuctionInfo")))//选中了查询玩家拍卖纪录(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(auctionInfo.m_hWnd == NULL)
		{
			auctionInfo.Create(IDD_DLGAUCTIONINFO);
			auctionInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(auctionInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(auctionInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALCDKeyItemGet")))//选中了CDKEY道具领取查询(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(CDKeyItemGet.m_hWnd == NULL)
		{
			CDKeyItemGet.Create(IDD_DLGCDKEYITEMGET);
			CDKeyItemGet.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(CDKeyItemGet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(CDKeyItemGet.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmPalSendDelRolePass")))//选中了发送密码(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(sendUserPwd.m_hWnd == NULL)
		{
			sendUserPwd.Create(IDD_DLGSENDPWD);
			sendUserPwd.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(sendUserPwd.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(sendUserPwd.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMobInfo")))//角色伏魔信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(mobInfo.m_hWnd == NULL)
		{
			mobInfo.Create(IDD_DLGMOBINFO);
			mobInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(mobInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(mobInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMobManage")))//角色伏魔管理
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(mobManage.m_hWnd == NULL)
		{
			mobManage.Create(IDD_DLGMOBMANAGE);
			mobManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(mobManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(mobManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALPuzzleMapInfo")))//角色图鉴信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(puzzleMapInfo.m_hWnd == NULL)
		{
			puzzleMapInfo.Create(IDD_DLGPUZZLEMAPINFO);
			puzzleMapInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(puzzleMapInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(puzzleMapInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALPuzzleMapManage")))//角色图鉴管理
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(puzzleMapManage.m_hWnd == NULL)
		{
			puzzleMapManage.Create(IDD_DLGPUZZLEMAPMANAGE);
			puzzleMapManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(puzzleMapManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(puzzleMapManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMoveToSafe")))//移动角色至安全点
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(moveToSafe.m_hWnd == NULL)
		{
			moveToSafe.Create(IDD_DLGMOVETOSAFE);
			moveToSafe.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(moveToSafe.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(moveToSafe.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALRoleDel")))//移动角色至安全点
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(roleDel.m_hWnd == NULL)
		{
			roleDel.Create(IDD_DLGROLEDEL);
			roleDel.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(roleDel.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(roleDel.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALCharacterInfo")))//角色信息（限制）
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(characterInfo.m_hWnd == NULL)
		{
			characterInfo.Create(IDD_DLGCHARACTERINFO);
			characterInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(characterInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(characterInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALSendCustomerItem")))//寄送客制物品(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(sendCustomerItem.m_hWnd == NULL)
		{
			sendCustomerItem.Create(IDD_DLGSENDCUSTOMERITEM);
			sendCustomerItem.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(sendCustomerItem.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(sendCustomerItem.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALUserInfoOnly")))//用户信息查询（只读）（仙剑）
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(userInfoOnly.m_hWnd == NULL)
		{
			userInfoOnly.Create(IDD_DLGUSERINFO);
			userInfoOnly.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(userInfoOnly.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(userInfoOnly.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}

	return false;
}

//选择显示不同的子对话框
extern "C" __declspec(dllexport) BOOL PAL_SHOWDIALOG(CString m_MenuName)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALUserInfo")))//选中了查询用户信息(仙剑)
	{		
		if(userInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}		
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALKickPlayer")))//选中了强制玩家(仙剑)下线
	{
		if(kickPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(kickPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALBanPlayer")))//选中了玩家帐号解封停(仙剑)
	{
		if(banPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(banPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALNoticeInfo")))//选中了公告信息(仙剑)
	{
		if(noticeInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(noticeInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALGuildManage")))//选中了公会管理(仙剑)
	{
		if(guildmanage.m_hWnd!=NULL)
		{
			::SetWindowPos(guildmanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALRoleManage")))//选中了角色管理(仙剑)
	{
		if(roleManage.m_hWnd!=NULL)
		{
			::SetWindowPos(roleManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALLogInfo")))//选中了日志信息(仙剑)
	{
		if(logInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(logInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALHisLogInfo")))//选中了日志信息-历史(仙剑)
	{
		if(hislogInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(hislogInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALItemInfo")))//选中了道具信息(仙剑)
	{
		if(itemInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(itemInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}		
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALItemManage")))//选中了道具管理(仙剑)
	{
		if(itemManage.m_hWnd!=NULL)
		{
			::SetWindowPos(itemManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALGuildInfo")))//选中了公会信息(仙剑)
	{
		if(guildInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(guildInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}		
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMailBoxInfo")))//选中了邮箱信息(仙剑)
	{
		if(mailBoxInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(mailBoxInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_UI_AccountLogin")))//选中了帐号登录信息(仙剑)
	{
		if(accountLogin.m_hWnd!=NULL)
		{
			::SetWindowPos(accountLogin.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}		
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALShopBuyLog")))//选中了商城购买记录(仙剑)
	{
		if(shopBuyLog.m_hWnd!=NULL)
		{
			::SetWindowPos(shopBuyLog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CQueryBanInfo")))//选中了查询特定玩家帐号有没有被封停(仙剑)
	{
		if(queryBanInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(queryBanInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALAuctionInfo")))//选中了查询玩家拍卖纪录(仙剑)
	{
		if(auctionInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(auctionInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALCDKeyItemGet")))//选中了CDKEY道具领取查询(仙剑)
	{
		if(CDKeyItemGet.m_hWnd!=NULL)
		{
			::SetWindowPos(CDKeyItemGet.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmPalSendDelRolePass")))//选中了发送密码(仙剑)
	{
		if(sendUserPwd.m_hWnd!=NULL)
		{
			::SetWindowPos(sendUserPwd.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMobInfo")))//选中了发送密码(仙剑)
	{
		if(mobInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(mobInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMobManage")))//选中了发送密码(仙剑)
	{
		if(mobManage.m_hWnd!=NULL)
		{
			::SetWindowPos(mobManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALPuzzleMapInfo")))//选中了发送密码(仙剑)
	{
		if(puzzleMapInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(puzzleMapInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALPuzzleMapManage")))//选中了发送密码(仙剑)
	{
		if(puzzleMapManage.m_hWnd!=NULL)
		{
			::SetWindowPos(puzzleMapManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMoveToSafe")))//选中了发送密码(仙剑)
	{
		if(moveToSafe.m_hWnd!=NULL)
		{
			::SetWindowPos(moveToSafe.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALRoleDel")))//选中了发送密码(仙剑)
	{
		if(roleDel.m_hWnd!=NULL)
		{
			::SetWindowPos(roleDel.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALCharacterInfo")))//角色信息（限制）
	{
		if(characterInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(characterInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALSendCustomerItem")))//寄送客制物品
	{
		if(sendCustomerItem.m_hWnd!=NULL)
		{
			::SetWindowPos(sendCustomerItem.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALUserInfoOnly")))//用户信息查询（只读）（仙剑）
	{		
		if(userInfoOnly.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfoOnly.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}		
	}
	return FALSE;
}

//选择给不同的子对话框发消息
extern "C" __declspec(dllexport) void PAL_DIALOGMSG(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam)
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
		if(guildmanage.m_hWnd != NULL)
		{
			::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(guildmanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(roleManage.m_hWnd != NULL)
		{
			::SetParent(roleManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(roleManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(logInfo.m_hWnd != NULL)
		{
			::SetParent(logInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(logInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(hislogInfo.m_hWnd!=NULL)
		{
			::SetParent(hislogInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(hislogInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(itemInfo.m_hWnd != NULL)
		{
			::SetParent(itemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(itemInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(itemManage.m_hWnd != NULL)
		{
			::SetParent(itemManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(itemManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(guildInfo.m_hWnd != NULL)
		{
			::SetParent(guildInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(guildInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(mailBoxInfo.m_hWnd != NULL)
		{
			::SetParent(mailBoxInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(mailBoxInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(accountLogin.m_hWnd != NULL)
		{
			::SetParent(accountLogin.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(accountLogin.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(shopBuyLog.m_hWnd != NULL)
		{
			::SetParent(shopBuyLog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(shopBuyLog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(queryBanInfo.m_hWnd != NULL)
		{
			::SetParent(queryBanInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(queryBanInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(auctionInfo.m_hWnd != NULL)
		{
			::SetParent(auctionInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(auctionInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(CDKeyItemGet.m_hWnd != NULL)
		{
			::SetParent(CDKeyItemGet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(CDKeyItemGet.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(sendUserPwd.m_hWnd != NULL)
		{
			::SetParent(sendUserPwd.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		    ::SendMessage(sendUserPwd.m_hWnd, Msg, wParam, lParam);//发送消息
		}

		if(mobInfo.m_hWnd != NULL)
		{
			::SetParent(mobInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mobInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(mobManage.m_hWnd != NULL)
		{
			::SetParent(mobManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mobManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(puzzleMapInfo.m_hWnd != NULL)
		{
			::SetParent(puzzleMapInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(puzzleMapInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(puzzleMapManage.m_hWnd != NULL)
		{
			::SetParent(puzzleMapManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(puzzleMapManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}

		if(moveToSafe.m_hWnd != NULL)
		{
			::SetParent(moveToSafe.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(moveToSafe.m_hWnd, Msg, wParam, lParam);//发送消息
		}

		if(roleDel.m_hWnd != NULL)
		{
			::SetParent(roleDel.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(roleDel.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(characterInfo.m_hWnd != NULL)
		{
			::SetParent(characterInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(characterInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(sendCustomerItem.m_hWnd != NULL)
		{
			::SetParent(sendCustomerItem.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(sendCustomerItem.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(userInfoOnly.m_hWnd != NULL)
		{
			::SetParent(userInfoOnly.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userInfoOnly.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALUserInfo")))//选中了查询用户信息(仙剑)
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALKickPlayer")))//选中了强制玩家(仙剑)下线
	{
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALBanPlayer")))//选中了玩家帐号解封停(仙剑)
	{
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALNoticeInfo")))//选中了公告信息(仙剑)
	{
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALGuildManage")))//选中了公会管理(仙剑)
	{
		if(guildmanage.m_hWnd != NULL)
		{
			::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildmanage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALRoleManage")))//选中了角色管理(仙剑)
	{
		if(roleManage.m_hWnd != NULL)
		{
			::SetParent(roleManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(roleManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALLogInfo")))//选中了日志信息(仙剑)
	{
		if(logInfo.m_hWnd != NULL)
		{
			::SetParent(logInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(logInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALItemInfo")))//选中了道具信息(仙剑)
	{
		if(itemInfo.m_hWnd != NULL)
		{
			::SetParent(itemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALItemManage")))//选中了道具管理(仙剑)
	{
		if(itemManage.m_hWnd != NULL)
		{
			::SetParent(itemManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALGuildInfo")))//选中了公会信息(仙剑)
	{
		if(guildInfo.m_hWnd != NULL)
		{
			::SetParent(guildInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(guildInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMailBoxInfo")))//选中了邮箱信息(仙剑)
	{
		if(mailBoxInfo.m_hWnd != NULL)
		{
			::SetParent(mailBoxInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mailBoxInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_UI_AccountLogin")))//选中了帐号登录信息(仙剑)
	{
		if(accountLogin.m_hWnd != NULL)
		{
			::SetParent(accountLogin.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(accountLogin.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALShopBuyLog")))//选中了商城购买记录(仙剑)
	{
		if(shopBuyLog.m_hWnd != NULL)
		{
			::SetParent(shopBuyLog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(shopBuyLog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CQueryBanInfo")))//选中了查询特定玩家帐号有没有被封停(仙剑)
	{
		if(queryBanInfo.m_hWnd != NULL)
		{
			::SetParent(queryBanInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(queryBanInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALAuctionInfo")))//选中了查询玩家拍卖纪录(仙剑)
	{
		if(auctionInfo.m_hWnd != NULL)
		{
			::SetParent(auctionInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(auctionInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALCDKeyItemGet")))//选中了CDKEY道具领取查询(仙剑)
	{
		if(CDKeyItemGet.m_hWnd != NULL)
		{
			::SetParent(CDKeyItemGet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(CDKeyItemGet.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmPalSendDelRolePass")))//选中了发送密码(仙剑)
	{
		if(sendUserPwd.m_hWnd != NULL)
		{
			::SetParent(sendUserPwd.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(sendUserPwd.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALHisLogInfo")))//选中了发送密码(仙剑)
	{
		if(hislogInfo.m_hWnd != NULL)
		{
			::SetParent(hislogInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(hislogInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMobInfo")))//选中了发送密码(仙剑)
	{
		if(mobInfo.m_hWnd != NULL)
		{
			::SetParent(mobInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mobInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMobManage")))//选中了发送密码(仙剑)
	{
		if(mobManage.m_hWnd != NULL)
		{
			::SetParent(mobManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mobManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALPuzzleMapInfo")))//选中了发送密码(仙剑)
	{
		if(puzzleMapInfo.m_hWnd != NULL)
		{
			::SetParent(puzzleMapInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(puzzleMapInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALPuzzleMapManage")))//选中了发送密码(仙剑)
	{
		if(puzzleMapManage.m_hWnd != NULL)
		{
			::SetParent(puzzleMapManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(puzzleMapManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMoveToSafe")))//选中了发送密码(仙剑)
	{
		if(moveToSafe.m_hWnd != NULL)
		{
			::SetParent(moveToSafe.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(moveToSafe.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALRoleDel")))//选中了发送密码(仙剑)
	{
		if(roleDel.m_hWnd != NULL)
		{
			::SetParent(roleDel.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(roleDel.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALCharacterInfo")))//角色信息（限制）
	{
		if(characterInfo.m_hWnd != NULL)
		{
			::SetParent(characterInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(characterInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALSendCustomerItem")))//寄送客制物品
	{
		if(sendCustomerItem.m_hWnd != NULL)
		{
			::SetParent(sendCustomerItem.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(sendCustomerItem.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALUserInfoOnly")))//选中了查询用户信息(仙剑)
	{
		if(userInfoOnly.m_hWnd != NULL)
		{
			::SetParent(userInfoOnly.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userInfoOnly.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
}

//再次发送同样的Query
extern "C" __declspec(dllexport) void PAL_SENDINFOAGAIN()
{
	theApp.operPAL.SendSameQuery();
}

extern "C" __declspec(dllexport) void GETPALINFO(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent, int* m_SelectDll)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//theApp.mSocket = m_socket;
	theApp.UserByID = userByID;
	theApp.userName = userName;
	theApp.mHwndParent = m_HwndParent;
	theApp.operPAL.initSocket(m_socket);
	theApp.operPAL.intPAL = m_SelectDll;
}