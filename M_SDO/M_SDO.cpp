// M_SDO.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOAccountInfo.h"
#include "SDOUserInfo.h"
#include "SDOLoginInfo.h"
#include "SDOTradeInfo.h"
#include "SDOShopInfo.h"
#include "SDOStatusInfo.h"
#include "SDOMarryInfo.h"
#include "SDORewardItemInfo.h"
#include "SDOKickPlayer.h"
#include "SDONoticeInfo.h"
#include "SDOFamilyInfo.h"
#include "SDOFamilyDonate.h"
#include "SDOPurchaseInfo.h"
#include "SDOFamilyManager.h"
#include "SDOResupply.h"
#include "SDOMatchManager.h"
#include "SDOMatchMul.h"
#include "SDOItemManager.h"
#include "SDORateSet.h"
#include "SDOITEMSET.h"
#include "SDOBanPlayer.h"
#include "SDOSenceSet.h"
#include "SDOPetSet.h"
#include "SDOPCashSet.h"
#include "SDOFriendManager.h"


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

// CM_SDOApp

BEGIN_MESSAGE_MAP(CM_SDOApp, CWinApp)
END_MESSAGE_MAP()


// CM_SDOApp 构造

CM_SDOApp::CM_SDOApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CM_SDOApp 对象

CM_SDOApp theApp;
CSDOAccountInfo accountInfo;
CSDOUserInfo userInfo;
CSDOLoginInfo loginInfo;
CSDOTradeInfo tradeInfo;
CSDOShopInfo shopInfo;
CSDOStatusInfo statusInfo;
CSDOMarryInfo marryInfo;
CSDORewardItemInfo rewardItemInfo;
CSDOKickPlayer kickPlayer;
CSDONoticeInfo noticeInfo;
CSDOFamilyInfo familyInfo;
CSDOFamilyDonate familyDonate;
CSDOPurchaseInfo purchaseInfo;
CSDOFamilyManager familyManager;
CSDOResupply resupply;
CSDOMatchManager matchManager;
CSDOMatchMul matchMul;
CSDOItemManager itemManager;
CSDORateSet rateSet;
CSDOITEMSET itemSet;
CSDOBanPlayer banPlayer;
CSDOSenceSet senceSet;
CSDOPetSet petSet;
CSDOPCashSet PCashSet;
CSDOFriendManager friendManager;


// CM_SDOApp 初始化

BOOL CM_SDOApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" __declspec(dllexport) BOOL SDO_TRANSLATEMESSAGE(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if((pMsg->wParam == 'C') || (pMsg->wParam == 'A'))
			{
				if(accountInfo.m_hWnd != NULL)
				{
					accountInfo.PreTranslateMessage(pMsg);
				}
				if(userInfo.m_hWnd != NULL)
				{
					userInfo.PreTranslateMessage(pMsg);
				}
				if(loginInfo.m_hWnd != NULL)
				{
					loginInfo.PreTranslateMessage(pMsg);
				}
				if(tradeInfo.m_hWnd != NULL)
				{
					tradeInfo.PreTranslateMessage(pMsg);
				}
				if(shopInfo.m_hWnd != NULL)
				{
					shopInfo.PreTranslateMessage(pMsg);
				}
				if(statusInfo.m_hWnd != NULL)
				{
					statusInfo.PreTranslateMessage(pMsg);
				}
				if(marryInfo.m_hWnd != NULL)
				{
					marryInfo.PreTranslateMessage(pMsg);
				}
				if(rewardItemInfo.m_hWnd != NULL)
				{
					rewardItemInfo.PreTranslateMessage(pMsg);
				}
				if(kickPlayer.m_hWnd != NULL)
				{
					kickPlayer.PreTranslateMessage(pMsg);
				}
				if(noticeInfo.m_hWnd != NULL)
				{
					noticeInfo.PreTranslateMessage(pMsg);
				}
				if(familyInfo.m_hWnd != NULL)
				{
					familyInfo.PreTranslateMessage(pMsg);
				}
				if(familyDonate.m_hWnd != NULL)
				{
					familyDonate.PreTranslateMessage(pMsg);
				}
				if(purchaseInfo.m_hWnd != NULL)
				{
					purchaseInfo.PreTranslateMessage(pMsg);
				}
				if(familyManager.m_hWnd != NULL)
				{
					familyManager.PreTranslateMessage(pMsg);
				}
				if(matchManager.m_hWnd != NULL)
				{
					matchManager.PreTranslateMessage(pMsg);
				}
				if(itemManager.m_hWnd != NULL)
				{
					itemManager.PreTranslateMessage(pMsg);
				}
				if(rateSet.m_hWnd != NULL)
				{
					rateSet.PreTranslateMessage(pMsg);
				}
				if(itemSet.m_hWnd != NULL)
				{
					itemSet.PreTranslateMessage(pMsg);
				}
				if(banPlayer.m_hWnd != NULL)
				{
					banPlayer.PreTranslateMessage(pMsg);
				}
				if(petSet.m_hWnd != NULL)
				{
					petSet.PreTranslateMessage(pMsg);
				}
				if(PCashSet.m_hWnd != NULL)
				{
					PCashSet.PreTranslateMessage(pMsg);
				}
				if(friendManager.m_hWnd != NULL)
				{
					friendManager.PreTranslateMessage(pMsg);
				}
			}
		}
	}
	return FALSE;
}

extern "C" __declspec(dllexport) void GETSDOMESSAGE(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.m_TagID = m_message_tag_id;
	OperationSDO operSDO;

	switch(m_message_tag_id)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://服务器信息
		{
			if((accountInfo.m_hWnd != NULL) && !accountInfo.IsWindowEnabled())
			{
				accountInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if(userInfo.m_hWnd != NULL && !userInfo.IsWindowEnabled())
			{
				userInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((loginInfo.m_hWnd != NULL) && !loginInfo.IsWindowEnabled())
			{
				loginInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((tradeInfo.m_hWnd != NULL) && !tradeInfo.IsWindowEnabled())
			{
				tradeInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((shopInfo.m_hWnd != NULL) && !shopInfo.IsWindowEnabled())
			{
				shopInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((statusInfo.m_hWnd != NULL) && !statusInfo.IsWindowEnabled())
			{
				statusInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((marryInfo.m_hWnd != NULL) && !marryInfo.IsWindowEnabled())
			{
				marryInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((rewardItemInfo.m_hWnd != NULL) && !rewardItemInfo.IsWindowEnabled())
			{
				rewardItemInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);///SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((kickPlayer.m_hWnd != NULL) && !kickPlayer.IsWindowEnabled())
			{
				kickPlayer.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((noticeInfo.m_hWnd != NULL) && (noticeInfo.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((familyInfo.m_hWnd != NULL) && !familyInfo.IsWindowEnabled())//(familyInfo.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				familyInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((familyDonate.m_hWnd != NULL) && !familyDonate.IsWindowEnabled())
			{
				familyDonate.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((purchaseInfo.m_hWnd != NULL) && !purchaseInfo.IsWindowEnabled())
			{
				purchaseInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((familyManager.m_hWnd != NULL) && !familyManager.IsWindowEnabled())
			{
				familyManager.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((resupply.m_hWnd != NULL) && (resupply.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				resupply.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((matchManager.m_hWnd != NULL) && (matchManager.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				matchManager.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((matchMul.m_hWnd != NULL) && (matchMul.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				matchMul.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((itemManager.m_hWnd != NULL) && (itemManager.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				itemManager.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((rateSet.m_hWnd != NULL) && (rateSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				rateSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((itemSet.m_hWnd != NULL) && (itemSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				itemSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((banPlayer.m_hWnd != NULL) && !banPlayer.IsWindowEnabled())
			{
				banPlayer.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((petSet.m_hWnd != NULL) && (petSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				petSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((PCashSet.m_hWnd != NULL) && (PCashSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				PCashSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((friendManager.m_hWnd != NULL) && (friendManager.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				friendManager.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_ACCOUNT_QUERY_RESP://帐号信息查询
		{
			if((accountInfo.m_hWnd != NULL) && !accountInfo.IsWindowEnabled())
			{
				accountInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHARACTERINFO_QUERY_RESP://角色信息
		{
			if((userInfo.m_hWnd != NULL) && !userInfo.IsWindowEnabled())
			{
				userInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);///SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((tradeInfo.m_hWnd != NULL) && !tradeInfo.IsWindowEnabled())
			{
				tradeInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((shopInfo.m_hWnd != NULL) && !shopInfo.IsWindowEnabled())
			{
				shopInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((kickPlayer.m_hWnd != NULL) && !kickPlayer.IsWindowEnabled())
			{
				kickPlayer.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((itemSet.m_hWnd != NULL) && (itemSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				itemSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((banPlayer.m_hWnd != NULL) && !banPlayer.IsWindowEnabled())
			{
				banPlayer.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((statusInfo.m_hWnd != NULL) && !statusInfo.IsWindowEnabled())
			{
				statusInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((marryInfo.m_hWnd != NULL) && !marryInfo.IsWindowEnabled())
			{
				marryInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((rewardItemInfo.m_hWnd != NULL) && !rewardItemInfo.IsWindowEnabled())
			{
				rewardItemInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((petSet.m_hWnd != NULL) && (petSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				petSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((PCashSet.m_hWnd != NULL) && (PCashSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				PCashSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((friendManager.m_hWnd != NULL) && (friendManager.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				friendManager.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_ITEMSHOP_BYOWNER_QUERY_RESP://物品信息
		{
			if(userInfo.m_hWnd != NULL && !userInfo.IsWindowEnabled())
			{
				userInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);/////SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((itemSet.m_hWnd != NULL) && (itemSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				itemSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_PetInfo_Query_RESP://宠物信息
		{
			if(userInfo.m_hWnd != NULL && !userInfo.IsWindowEnabled())
			{
				userInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);////SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((petSet.m_hWnd != NULL) && (petSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				petSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_PetDrop_Query_RESP://宠物删除信息
		{
			if(userInfo.m_hWnd != NULL && !userInfo.IsWindowEnabled())
			{
				userInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);////SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_USERONLINE_QUERY_RESP://登录信息
		{
			if((loginInfo.m_hWnd != NULL) && !loginInfo.IsWindowEnabled())//(loginInfo.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				loginInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_ITEMSHOP_TRADE_QUERY_RESP://交易信息
		{
			if((tradeInfo.m_hWnd != NULL) && !tradeInfo.IsWindowEnabled())
			{
				tradeInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CONSUME_QUERY_RESP://消费信息
		{
			if((shopInfo.m_hWnd != NULL) && !shopInfo.IsWindowEnabled())
			{
				shopInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);///SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_USERLOGIN_STATUS_QUERY_RESP://状态信息
		{
			if((statusInfo.m_hWnd != NULL) && !statusInfo.IsWindowEnabled())
			{
				statusInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_USERMARRIAGEQUERY_RESP://结婚信息
		{
			if((marryInfo.m_hWnd != NULL) && !marryInfo.IsWindowEnabled())
			{
				marryInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_RewardItem_QUERY_RESP://
		{
			if((rewardItemInfo.m_hWnd != NULL) && !rewardItemInfo.IsWindowEnabled())
			{
				rewardItemInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_USERLOGIN_DEL_RESP:
		{
			if((kickPlayer.m_hWnd != NULL) && !kickPlayer.IsWindowEnabled())
			{
				kickPlayer.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_BOARDMESSAGE_REQ_RESP://编辑公告之前的返回
	case CEnumCore::Message_Tag_ID::SDO_BOARDTASK_INSERT_RESP://添加公告
	case CEnumCore::Message_Tag_ID::SDO_BOARDTASK_QUERY_RESP://查询公告
	case CEnumCore::Message_Tag_ID::SDO_BOARDTASK_UPDATE_RESP://编辑公告
		{
			if((noticeInfo.m_hWnd != NULL) && (noticeInfo.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_Family_Info_QUERY_RESP://家族基本信息
		{
			if((familyInfo.m_hWnd != NULL) && !familyInfo.IsWindowEnabled())
			{
				familyInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((familyDonate.m_hWnd != NULL) && !familyDonate.IsWindowEnabled())
			{
				familyDonate.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((purchaseInfo.m_hWnd != NULL) && !purchaseInfo.IsWindowEnabled())
			{
				purchaseInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((familyManager.m_hWnd != NULL) && !familyManager.IsWindowEnabled())
			{
				familyManager.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);///SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_FamilyMember_Query_RESP://家族成员
		{
			if((familyInfo.m_hWnd != NULL) && !familyInfo.IsWindowEnabled())
			{
				familyInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((familyManager.m_hWnd != NULL) && !familyManager.IsWindowEnabled())
			{
				familyManager.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_FamilyFormal_Query_RESP://申请中成员
	case CEnumCore::Message_Tag_ID::SDO_Personal_Emblem_Query_RESP://家族徽章
		{
			if((familyInfo.m_hWnd != NULL) && !familyInfo.IsWindowEnabled())
			{
				familyInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((familyManager.m_hWnd != NULL) && !familyManager.IsWindowEnabled())
			{
				familyManager.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);///SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_Family_Donate_Query_RES://家族金库捐赠明细
		{
			if((familyDonate.m_hWnd != NULL) && !familyDonate.IsWindowEnabled())
			{
				familyDonate.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_Family_CONSUME_QUERY_RESP:
		{
			if((purchaseInfo.m_hWnd != NULL) && !purchaseInfo.IsWindowEnabled())
			{
				purchaseInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_Family_Emblem_Insert_Query_RESP://
	case CEnumCore::Message_Tag_ID::SDO_Family_Duty_Query_RESP:
	case CEnumCore::Message_Tag_ID::SDO_Family_Emblem_Delete_Query_RESP:
	case CEnumCore::Message_Tag_ID::SDO_Family_Delete_Query_RESP:
		{
			if((familyManager.m_hWnd != NULL) && !familyManager.IsWindowEnabled())
			{
				familyManager.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_USERGCASH_QUERY_RESP://返回G币金额
	case CEnumCore::Message_Tag_ID::SDO_USERGCASH_UPDATE_RESP://补发G币金额
		{
			if((resupply.m_hWnd != NULL) && (resupply.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				resupply.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_INSERT_RESP://添加比赛
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_UPDATE_RESP://编辑比赛
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_DELETE_RESP://删除比赛
		{
			if((matchManager.m_hWnd != NULL) && (matchManager.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				matchManager.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_QUERY_RESP://比赛信息查询
		{
			if((matchManager.m_hWnd != NULL) && (matchManager.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				matchManager.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_QUERY_RESP://比赛场景查询
		{
			if((matchManager.m_hWnd != NULL) && (matchManager.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				matchManager.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((matchMul.m_hWnd != NULL) && (matchMul.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				matchMul.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((senceSet.m_hWnd != NULL) && (senceSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				senceSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_INSERTALL_RESP://批量添加场景
		{
			if((matchMul.m_hWnd != NULL) && (matchMul.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				matchMul.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_YYHAPPYITEM_QUERY_RESP:
	case CEnumCore::Message_Tag_ID::SDO_YYHAPPYITEM_CREATE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_YYHAPPYITEM_DELETE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_YYHAPPYITEM_UPDATE_RESP:
		{
			if((itemManager.m_hWnd != NULL) && (itemManager.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				itemManager.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_ITEMSHOP_QUERY_RESP:
		{
			if((itemManager.m_hWnd != NULL) && (itemManager.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				itemManager.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((rateSet.m_hWnd != NULL) && (rateSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				rateSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			if((itemSet.m_hWnd != NULL) && (itemSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				itemSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_MEDALITEM_QUERY_RESP://没有ItemName
	case CEnumCore::Message_Tag_ID::SDO_MEDALITEM_OWNER_QUERY_RESP://有ItemName
	case CEnumCore::Message_Tag_ID::SDO_MEDALITEM_CREATE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_MEDALITEM_DELETE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_MEDALITEM_UPDATE_RESP:
		{
			if((rateSet.m_hWnd != NULL) && (rateSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				rateSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHARACTERINFO_UPDATE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_GIFTBOX_CREATE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_GIFTBOX_DELETE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_ITEMSHOP_DELETE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_GIFTBOX_QUERY_RESP://礼盒
	case CEnumCore::Message_Tag_ID::SDO_Social_Update_Resp:
	case CEnumCore::Message_Tag_ID::SDO_Lucky_Update_Resp:
		{
			if((itemSet.m_hWnd != NULL) && (itemSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				itemSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_MEMBERBANISHMENT_QUERY_RESP://查询所有停封帐号
	case CEnumCore::Message_Tag_ID::SDO_ACCOUNT_CLOSE_RESP://封停帐号
	case CEnumCore::Message_Tag_ID::SDO_ACCOUNT_OPEN_RESP://解封帐号
	case CEnumCore::Message_Tag_ID::SDO_MEMBERSTOPSTATUS_QUERY_RESP:
		{
			if((banPlayer.m_hWnd != NULL) && !banPlayer.IsWindowEnabled())
			{
				banPlayer.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_DELETE_RESP://SDO_CHALLENGE_SCENE_DELETE
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_UPDATE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_CREATE_RESP:
		{
			if((senceSet.m_hWnd != NULL) && (senceSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				senceSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_Pet_Update_RESP://修改宠物等级和经验
		{
			if((petSet.m_hWnd != NULL) && (petSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				petSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_PCash_Update_Resp://修改红利点数
		{
			if((PCashSet.m_hWnd != NULL) && (PCashSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				PCashSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_Friend_Query_Resp://好友查询
	case CEnumCore::Message_Tag_ID::SDO_Friend_Delete_Resp:
		{
			if((friendManager.m_hWnd != NULL) && (friendManager.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				friendManager.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	default:
		break;
	}
}

//选择打开不同的子对话框
extern "C" __declspec(dllexport) bool SDO_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Account")))//玩家帐号信息查询
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(accountInfo.m_hWnd == NULL)
		{
			accountInfo.Create(IDD_DLGACCOUNTINFO);
			accountInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(accountInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(accountInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		*/

		if(accountInfo.m_hWnd == NULL)
		{
			accountInfo.Create(CSDOBaseDlg::IDD);
			accountInfo.SetDlgCtrlID(CSDOAccountInfo::IDD);			
			::SetParent(accountInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			accountInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			accountInfo.ShowWindow(SW_SHOWMAXIMIZED);
			accountInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Part")))//玩家角色信息
	{

		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		
		if(userInfo.m_hWnd == NULL)
		{
			//characterInfo.Create(IDD_DLGFRIENDMANAGER);
			userInfo.Create(CSDOBaseDlg::IDD);//CCG2BaseDlg
			userInfo.SetDlgCtrlID(CSDOUserInfo::IDD);			
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			userInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			userInfo.ShowWindow(SW_SHOWMAXIMIZED);
			userInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
//		::SendMessage(characterInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Login")))//玩家登录信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(loginInfo.m_hWnd == NULL)
		{
			loginInfo.Create(IDD_DLGLOGININFO);
			loginInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(loginInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		*/
		if(loginInfo.m_hWnd == NULL)
		{
			loginInfo.Create(CSDOBaseDlg::IDD);
			loginInfo.SetDlgCtrlID(CSDOAccountInfo::IDD);			
			::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			loginInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			loginInfo.ShowWindow(SW_SHOWMAXIMIZED);
			loginInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Trade")))//玩家交易信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(tradeInfo.m_hWnd == NULL)
		{
			tradeInfo.Create(IDD_DLGTRADEINFO);
			tradeInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(tradeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(tradeInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		*/
		if(tradeInfo.m_hWnd == NULL)
		{
			tradeInfo.Create(CSDOBaseDlg::IDD);
			tradeInfo.SetDlgCtrlID(CSDOTradeInfo::IDD);			
			::SetParent(tradeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			tradeInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			tradeInfo.ShowWindow(SW_SHOWMAXIMIZED);
			tradeInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Shopping")))//玩家消费信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(shopInfo.m_hWnd == NULL)
		{
			shopInfo.Create(IDD_DLGSHOPINFO);
			shopInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(shopInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(shopInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		*/
		if(shopInfo.m_hWnd == NULL)
		{
			shopInfo.Create(CSDOBaseDlg::IDD);
			shopInfo.SetDlgCtrlID(CSDOShopInfo::IDD);			
			::SetParent(shopInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			shopInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			shopInfo.ShowWindow(SW_SHOWMAXIMIZED);
			shopInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Status")))//玩家状态信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(statusInfo.m_hWnd == NULL)
		{
			statusInfo.Create(IDD_DLGSTATUSINFO);////IDD_DLGSTATUSINFO
			statusInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(statusInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(statusInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		*/
		if(statusInfo.m_hWnd == NULL)
		{
			statusInfo.Create(CSDOBaseDlg::IDD);
			statusInfo.SetDlgCtrlID(CSDOStatusInfo::IDD);			
			::SetParent(statusInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			statusInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			statusInfo.ShowWindow(SW_SHOWMAXIMIZED);
			statusInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMarry")))//玩家婚姻信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(marryInfo.m_hWnd == NULL)
		{
			marryInfo.Create(IDD_DLGMARRYINFO);
			marryInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(marryInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(marryInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		*/
		if(marryInfo.m_hWnd == NULL)
		{
			marryInfo.Create(CSDOBaseDlg::IDD);
			marryInfo.SetDlgCtrlID(CSDOMarryInfo::IDD);			
			::SetParent(marryInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			marryInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			marryInfo.ShowWindow(SW_SHOWMAXIMIZED);
			marryInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryRewardItem")))//玩家摇摇乐获奖信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(rewardItemInfo.m_hWnd == NULL)
		{
			rewardItemInfo.Create(IDD_DLGREWARDITEMINFO);
			rewardItemInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(rewardItemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(rewardItemInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		*/
		if(rewardItemInfo.m_hWnd == NULL)
		{
			rewardItemInfo.Create(CSDOBaseDlg::IDD);
			rewardItemInfo.SetDlgCtrlID(CSDORewardItemInfo::IDD);			
			::SetParent(rewardItemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			rewardItemInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			rewardItemInfo.ShowWindow(SW_SHOWMAXIMIZED);
			rewardItemInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","LogOff")))//强制玩家下线
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(kickPlayer.m_hWnd == NULL)
		{
			kickPlayer.Create(IDD_DLGKICKPLAYER);
			kickPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(kickPlayer.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		*/
		if(kickPlayer.m_hWnd == NULL)
		{
			kickPlayer.Create(CSDOBaseDlg::IDD);
			kickPlayer.SetDlgCtrlID(CSDOKickPlayer::IDD);			
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
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmSdoNotice")))//公告管理系统
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
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyInfo")))//家族信息查询
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(familyInfo.m_hWnd == NULL)
		{
			familyInfo.Create(IDD_DLGFAMILYINFO);
			familyInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(familyInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		*/
		if(familyInfo.m_hWnd == NULL)
		{
			familyInfo.Create(CSDOFamilyBaseDlg::IDD);
			familyInfo.SetDlgCtrlID(CSDOFamilyInfo::IDD);			
			::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			familyInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			familyInfo.ShowWindow(SW_SHOWMAXIMIZED);
			familyInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyClubHouse")))//家族会所日志
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(familyDonate.m_hWnd == NULL)
		{
			familyDonate.Create(IDD_DLGCLUBINFO);
			familyDonate.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyDonate.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(familyDonate.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		*/
		if(familyDonate.m_hWnd == NULL)
		{
			familyDonate.Create(CSDOFamilyBaseDlg::IDD);
			familyDonate.SetDlgCtrlID(CSDOFamilyDonate::IDD);			
			::SetParent(familyDonate.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			familyDonate.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			familyDonate.ShowWindow(SW_SHOWMAXIMIZED);
			familyDonate.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyPurchaseInfo")))//家族购买记录
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(purchaseInfo.m_hWnd == NULL)
		{
			purchaseInfo.Create(IDD_DLGPURCHASEINFO);
			purchaseInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(purchaseInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(purchaseInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		*/
		if(purchaseInfo.m_hWnd == NULL)
		{
			purchaseInfo.Create(CSDOFamilyBaseDlg::IDD);
			purchaseInfo.SetDlgCtrlID(CSDOPurchaseInfo::IDD);			
			::SetParent(purchaseInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			purchaseInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			purchaseInfo.ShowWindow(SW_SHOWMAXIMIZED);
			purchaseInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyManage")))//家族管理
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(familyManager.m_hWnd == NULL)
		{
			familyManager.Create(IDD_DLGFAMILYMANAGER);
			familyManager.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyManager.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(familyManager.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		*/
		if(familyManager.m_hWnd == NULL)
		{
			familyManager.Create(CSDOFamilyBaseDlg::IDD);
			familyManager.SetDlgCtrlID(CSDOFamilyManager::IDD);			
			::SetParent(familyManager.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			familyManager.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			familyManager.ShowWindow(SW_SHOWMAXIMIZED);
			familyManager.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Resupply")))//补Ｇ币
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(resupply.m_hWnd == NULL)
		{
			resupply.Create(IDD_DLGRESUPPLY);
			resupply.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(resupply.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(resupply.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","MatchInfo")))//比赛信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(matchManager.m_hWnd == NULL)
		{
			matchManager.Create(IDD_DLGMATCHMANAGER);
			matchManager.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(matchManager.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(matchManager.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmSdoGameinfo")))//大赛信息编辑(批量添加比赛)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(matchMul.m_hWnd == NULL)
		{
			matchMul.Create(IDD_DLGMATCHMUL);
			matchMul.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(matchMul.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(matchMul.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","RateEdit")))//道具获取比率设置
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(rateSet.m_hWnd == NULL)
		{
			rateSet.Create(IDD_DLGRATESET);
			rateSet.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(rateSet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(rateSet.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Update")))//SDO玩家道具管理
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(itemSet.m_hWnd == NULL)
		{
			itemSet.Create(IDD_DLGITEMSET);
			itemSet.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemSet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(itemSet.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Close")))//帐号解/封停
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(banPlayer.m_hWnd == NULL)
		{
			banPlayer.Create(IDD_DLGBANPLAYER);
			banPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(banPlayer.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		*/
		if(banPlayer.m_hWnd == NULL)
		{
			banPlayer.Create(CSDOBaseDlg::IDD);
			banPlayer.SetDlgCtrlID(CSDOBanPlayer::IDD);			
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
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","SenceEdit")))//场景设置
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(senceSet.m_hWnd == NULL)
		{
			senceSet.Create(IDD_DLGSENCESET);
			senceSet.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(senceSet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(senceSet.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmYYItem")))//摇摇乐道具设置
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(itemManager.m_hWnd == NULL)
		{
			itemManager.Create(IDD_DLGITEMMANAGER);
			itemManager.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemManager.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(itemManager.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","PetSet")))//宠物信息修改
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(petSet.m_hWnd == NULL)
		{
			petSet.Create(IDD_DLGPETSET);
			petSet.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(petSet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(petSet.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","PCashSet")))//红利点数修改
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(PCashSet.m_hWnd == NULL)
		{
			PCashSet.Create(IDD_DLGPCASHSET);
			PCashSet.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(PCashSet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(PCashSet.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","SDOFriendManager")))//好友管理
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(friendManager.m_hWnd == NULL)
		{
			friendManager.Create(IDD_DLGFRIENDMANAGER);
			friendManager.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(friendManager.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(friendManager.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	return FALSE;
}

//选择显示不同的子对话框
extern "C" __declspec(dllexport) BOOL SDO_SHOWDIALOG(CString m_MenuName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Account")))//玩家帐号信息查询
	{
		if(accountInfo.m_hWnd!=NULL)
		{
			accountInfo.ShowWindow(SW_SHOWMAXIMIZED);
			accountInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Part")))//玩家角色信息
	{
		if(userInfo.m_hWnd!=NULL)
		{
			userInfo.ShowWindow(SW_SHOWMAXIMIZED);
			userInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Login")))//玩家登录信息
	{
		if(loginInfo.m_hWnd!=NULL)
		{
			loginInfo.ShowWindow(SW_SHOWMAXIMIZED);
			loginInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Trade")))//玩家交易信息
	{
		if(tradeInfo.m_hWnd!=NULL)
		{
			tradeInfo.ShowWindow(SW_SHOWMAXIMIZED);
			tradeInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Shopping")))//玩家消费信息
	{
		if(shopInfo.m_hWnd!=NULL)
		{
			shopInfo.ShowWindow(SW_SHOWMAXIMIZED);
			shopInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Status")))//玩家状态信息
	{
		if(statusInfo.m_hWnd!=NULL)
		{
			statusInfo.ShowWindow(SW_SHOWMAXIMIZED);
			statusInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMarry")))//玩家婚姻信息
	{
		if(marryInfo.m_hWnd!=NULL)
		{
			marryInfo.ShowWindow(SW_SHOWMAXIMIZED);
			marryInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryRewardItem")))//玩家摇摇乐获奖信息
	{
		if(rewardItemInfo.m_hWnd!=NULL)
		{
			rewardItemInfo.ShowWindow(SW_SHOWMAXIMIZED);
			rewardItemInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","LogOff")))//强制玩家下线
	{
		if(kickPlayer.m_hWnd!=NULL)
		{
			kickPlayer.ShowWindow(SW_SHOWMAXIMIZED);
			kickPlayer.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmSdoNotice")))//公告管理系统
	{
		if(noticeInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(noticeInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyInfo")))//家族信息查询
	{
		if(familyInfo.m_hWnd!=NULL)
		{
			familyInfo.ShowWindow(SW_SHOWMAXIMIZED);
			familyInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyClubHouse")))//家族会所日志
	{
		if(familyDonate.m_hWnd!=NULL)
		{
			familyDonate.ShowWindow(SW_SHOWMAXIMIZED);
			familyDonate.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyPurchaseInfo")))//家族购买记录
	{
		if(purchaseInfo.m_hWnd!=NULL)
		{
			purchaseInfo.ShowWindow(SW_SHOWMAXIMIZED);
			purchaseInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyManage")))//家族管理
	{
		/*if(familyManager.m_hWnd!=NULL)
		{
			::SetWindowPos(familyManager.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}*/
		if(familyManager.m_hWnd!=NULL)
		{
			familyManager.ShowWindow(SW_SHOWMAXIMIZED);
			familyManager.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}

	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Resupply")))//补Ｇ币
	{
		if(resupply.m_hWnd!=NULL)
		{
			::SetWindowPos(resupply.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","MatchInfo")))//比赛信息
	{
		if(matchManager.m_hWnd!=NULL)
		{
			::SetWindowPos(matchManager.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmSdoGameinfo")))//批量添加比赛
	{
		if(matchMul.m_hWnd!=NULL)
		{
			::SetWindowPos(matchMul.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmYYItem")))//摇摇乐道具设置
	{
		if(itemManager.m_hWnd!=NULL)
		{
			::SetWindowPos(itemManager.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","RateEdit")))//道具获取比率设置
	{
		if(rateSet.m_hWnd!=NULL)
		{
			::SetWindowPos(rateSet.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Update")))//SDO玩家道具管理
	{
		if(itemSet.m_hWnd!=NULL)
		{
			::SetWindowPos(itemSet.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Close")))//帐号解/封停
	{
		if(banPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(banPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","SenceEdit")))//场景设置
	{
		if(senceSet.m_hWnd!=NULL)
		{
			::SetWindowPos(senceSet.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","petSet")))//宠物修改
	{
		if(petSet.m_hWnd!=NULL)
		{
			::SetWindowPos(petSet.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","PCashSet")))//红利点数修改
	{
		if(PCashSet.m_hWnd!=NULL)
		{
			::SetWindowPos(PCashSet.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","SDOFriendManager")))//好友管理
	{
		if(friendManager.m_hWnd!=NULL)
		{
			::SetWindowPos(friendManager.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	return FALSE;
}

//选择给子对话框发送不同的消息
extern "C" __declspec(dllexport) void SDO_DIALOGMSG(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	CIni mIni;
	if(!strcmp("",m_MenuName))
	{
		if(accountInfo.m_hWnd != NULL)
		{
			::SetParent(accountInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(accountInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(loginInfo.m_hWnd != NULL)
		{
			::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(loginInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(tradeInfo.m_hWnd != NULL)
		{
			::SetParent(tradeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(tradeInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(shopInfo.m_hWnd != NULL)
		{
			::SetParent(shopInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(shopInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(statusInfo.m_hWnd != NULL)
		{
			::SetParent(statusInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(statusInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(marryInfo.m_hWnd != NULL)
		{
			::SetParent(marryInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(marryInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(rewardItemInfo.m_hWnd != NULL)
		{
			::SetParent(rewardItemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(rewardItemInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(familyInfo.m_hWnd != NULL)
		{
			::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(familyDonate.m_hWnd != NULL)
		{
			::SetParent(familyDonate.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyDonate.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(purchaseInfo.m_hWnd != NULL)
		{
			::SetParent(purchaseInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(purchaseInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(familyManager.m_hWnd != NULL)
		{
			::SetParent(familyManager.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyManager.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(resupply.m_hWnd != NULL)
		{
			::SetParent(resupply.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(resupply.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(matchManager.m_hWnd != NULL)
		{
			::SetParent(matchManager.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(matchManager.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(matchMul.m_hWnd != NULL)
		{
			::SetParent(matchMul.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(matchMul.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(itemManager.m_hWnd != NULL)
		{
			::SetParent(itemManager.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemManager.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(rateSet.m_hWnd != NULL)
		{
			::SetParent(rateSet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(rateSet.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(itemSet.m_hWnd != NULL)
		{
			::SetParent(itemSet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemSet.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(senceSet.m_hWnd != NULL)
		{
			::SetParent(senceSet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(senceSet.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(petSet.m_hWnd != NULL)
		{
			::SetParent(petSet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petSet.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(PCashSet.m_hWnd != NULL)
		{
			::SetParent(PCashSet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(PCashSet.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(friendManager.m_hWnd != NULL)
		{
			::SetParent(friendManager.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(friendManager.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Account")))//玩家帐号信息查询
	{
		if(accountInfo.m_hWnd != NULL)
		{
			::SetParent(accountInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(accountInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Part")))//玩家角色信息
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Login")))//玩家登录信息
	{
		if(loginInfo.m_hWnd != NULL)
		{
			::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(loginInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Trade")))//玩家交易信息
	{
		if(tradeInfo.m_hWnd != NULL)
		{
			::SetParent(tradeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(tradeInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Shopping")))//玩家消费信息
	{
		if(shopInfo.m_hWnd != NULL)
		{
			::SetParent(shopInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(shopInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Status")))//玩家状态信息
	{
		if(statusInfo.m_hWnd != NULL)
		{
			::SetParent(statusInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(statusInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMarry")))//玩家婚姻信息
	{
		if(marryInfo.m_hWnd != NULL)
		{
			::SetParent(marryInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(marryInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryRewardItem")))//玩家摇摇乐获奖信息
	{
		if(rewardItemInfo.m_hWnd != NULL)
		{
			::SetParent(rewardItemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(rewardItemInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","LogOff")))//强制玩家下线
	{
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmSdoNotice")))//公告管理系统
	{
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyInfo")))//家族信息查询
	{
		if(familyInfo.m_hWnd != NULL)
		{
			::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyClubHouse")))//家族会所日志
	{
		if(familyDonate.m_hWnd != NULL)
		{
			::SetParent(familyDonate.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyDonate.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyPurchaseInfo")))//家族购买记录
	{
		if(purchaseInfo.m_hWnd != NULL)
		{
			::SetParent(purchaseInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(purchaseInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyManage")))//家族管理
	{
		if(familyManager.m_hWnd != NULL)
		{
			::SetParent(familyManager.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyManager.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Resupply")))//补Ｇ币
	{
		if(resupply.m_hWnd != NULL)
		{
			::SetParent(resupply.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(resupply.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","MatchInfo")))//比赛信息
	{
		if(matchManager.m_hWnd != NULL)
		{
			::SetParent(matchManager.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(matchManager.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmSdoGameinfo")))//批量添加比赛
	{
		if(matchMul.m_hWnd != NULL)
		{
			::SetParent(matchMul.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(matchMul.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmYYItem")))//摇摇乐道具设置
	{
		if(itemManager.m_hWnd != NULL)
		{
			::SetParent(itemManager.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemManager.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","RateEdit")))//道具获取比率设置
	{
		if(rateSet.m_hWnd != NULL)
		{
			::SetParent(rateSet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(rateSet.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Update")))//SDO玩家道具管理
	{
		if(itemSet.m_hWnd != NULL)
		{
			::SetParent(itemSet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemSet.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Close")))//帐号解/封停
	{
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","SenceEdit")))//场景设置
	{
		if(senceSet.m_hWnd != NULL)
		{
			::SetParent(senceSet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(senceSet.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","petSet")))//宠物修改
	{
		if(petSet.m_hWnd != NULL)
		{
			::SetParent(petSet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petSet.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","PCashSet")))//红利点数修改
	{
		if(PCashSet.m_hWnd != NULL)
		{
			::SetParent(PCashSet.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(PCashSet.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","SDOFriendManager")))//好友管理
	{
		if(friendManager.m_hWnd != NULL)
		{
			::SetParent(friendManager.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(friendManager.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
}

//再次发送同样的Query
extern "C" __declspec(dllexport) void SDO_SENDINFOAGAIN()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.operSDO.SendSameQuery();
}

extern "C" __declspec(dllexport) void GETSDOINFO(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent, int* m_SelectDll)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.UserByID = userByID;
	theApp.userName = userName;
	theApp.mHwndParent = m_HwndParent;
	theApp.operSDO.initSocket(m_socket);
	theApp.operSDO.intSDO = m_SelectDll;
}
