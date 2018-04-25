// M_GTOWN.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "M_GTOWN.h"
#include "GTOWNUserInfo.h"
#include "GTOWNBanPlayer.h"
#include "GTOWNNoticeInfo.h"
#include "GTOWNKickPlayer.h"
#include "GTOWNFamilyInfo.h"
#include "GTOWNItemInfo.h"
#include "GTOWNItemManage.h"
#include "GTOWNLogInfo.h"
#include "GTOWNTreasureBoxInfo.h"
#include "GTOWNRoomInfo.h"
#include "GTOWNPetInfo.h"
#include "GTOWNMailInfo.h"
#include "GTOWNRelationshipInfo.h"
#include "GTOWNItemConsume.h"
#include "GTOWNRoleManage.h"
#include "GTOWNPictureManage.h"
#include "GTOWNTransmit.h"
#include "GTOWNQueueInfo.h"
#include "GTOWNFriendTrade.h"
#include "GTOWNBanList.h"
#include "GTOWNUserInfoPart.h"
#include "GTOWNRoleManagePart.h"
#include "GTOWNImport.h"
#include "GTOWNBackMoney.h"

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

// CM_GTOWNApp

BEGIN_MESSAGE_MAP(CM_GTOWNApp, CWinApp)
END_MESSAGE_MAP()


// CM_GTOWNApp 构造

CM_GTOWNApp::CM_GTOWNApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CM_GTOWNApp 对象

CM_GTOWNApp theApp;
CGTOWNUserInfo userInfo;
CGTOWNBanPlayer banPlayer;
CGTOWNNoticeInfo noticeInfo;
CGTOWNKickPlayer kickPlayer;
CGTOWNFamilyInfo familyInfo;
CGTOWNItemInfo itemInfo;
CGTOWNItemManage itemManage;
CGTOWNLogInfo logInfo;
CGTOWNTreasureBoxInfo treasureBoxInfo;
CGTOWNRoomInfo roomInfo;
CGTOWNPetInfo petInfo;
CGTOWNMailInfo mailInfo;
CGTOWNRelationshipInfo relationshipInfo;
CGTOWNItemConsume itemConsume;
CGTOWNRoleManage roleManage;
CGTOWNPictureManage pictureManage;
CGTOWNTransmit transMit;
CGTOWNQueueInfo queueInfo;
CGTOWNFriendTrade friendTrade;
CGTOWNBanList banList;
CGTOWNUserInfoPart userInfoPart;
CGTOWNRoleManagePart roleManagePart;
CGTOWNImport import;
CGTOWNBackMoney backMoney;

// CM_GTOWNApp 初始化

BOOL CM_GTOWNApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" __declspec(dllexport) BOOL GTOWN_TRANSLATEMESSAGE(MSG* pMsg)
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
				if(familyInfo.m_hWnd !=NULL)
				{
					familyInfo.PreTranslateMessage(pMsg);
				}
				if(itemInfo.m_hWnd !=NULL)
				{
					itemInfo.PreTranslateMessage(pMsg);
				}
				if(itemManage.m_hWnd !=NULL)
				{
					itemManage.PreTranslateMessage(pMsg);
				}
				if(logInfo.m_hWnd !=NULL)
				{
					logInfo.PreTranslateMessage(pMsg);
				}
				if(treasureBoxInfo.m_hWnd !=NULL)
				{
					treasureBoxInfo.PreTranslateMessage(pMsg);
				}
				if(roomInfo.m_hWnd !=NULL)
				{
					roomInfo.PreTranslateMessage(pMsg);
				}
				if(petInfo.m_hWnd !=NULL)
				{
					petInfo.PreTranslateMessage(pMsg);
				}
				if(mailInfo.m_hWnd !=NULL)
				{
					mailInfo.PreTranslateMessage(pMsg);
				}
				if(relationshipInfo.m_hWnd !=NULL)
				{
					relationshipInfo.PreTranslateMessage(pMsg);
				}
				if(itemConsume.m_hWnd !=NULL)
				{
					itemConsume.PreTranslateMessage(pMsg);
				}
				if(roleManage.m_hWnd !=NULL)
				{
					roleManage.PreTranslateMessage(pMsg);
				}
				if(pictureManage.m_hWnd !=NULL)
				{
					pictureManage.PreTranslateMessage(pMsg);
				}
				if(transMit.m_hWnd !=NULL)
				{
					transMit.PreTranslateMessage(pMsg);
				}
				if(queueInfo.m_hWnd !=NULL)
				{
					queueInfo.PreTranslateMessage(pMsg);
				}
				if(friendTrade.m_hWnd !=NULL)
				{
					friendTrade.PreTranslateMessage(pMsg);
				}
				if(banList.m_hWnd !=NULL)
				{
					banList.PreTranslateMessage(pMsg);
				}
				if(userInfoPart.m_hWnd !=NULL)
				{
					userInfoPart.PreTranslateMessage(pMsg);
				}
				if(roleManagePart.m_hWnd !=NULL)
				{
					roleManagePart.PreTranslateMessage(pMsg);
				}
				if(import.m_hWnd !=NULL)
				{
					import.PreTranslateMessage(pMsg);
				}
				if(backMoney.m_hWnd !=NULL)
				{
					backMoney.PreTranslateMessage(pMsg);
				}

			}
		}
	}
	return FALSE;
}

extern "C" __declspec(dllexport) void GETGTOWNMESSAGE(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.m_TagID = m_message_tag_id;
	OperationGTOWN operGTOWN;

	switch(m_message_tag_id)
	{	
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://服务器信息
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((noticeInfo.m_hWnd != NULL) && (noticeInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((familyInfo.m_hWnd != NULL) && (familyInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				familyInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemInfo.m_hWnd != NULL) && (itemInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				itemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemManage.m_hWnd != NULL) && (itemManage.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((logInfo.m_hWnd != NULL) && (logInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				logInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((treasureBoxInfo.m_hWnd != NULL) && (treasureBoxInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				treasureBoxInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((roomInfo.m_hWnd != NULL) && (roomInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				roomInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petInfo.m_hWnd != NULL) && (petInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailInfo.m_hWnd != NULL) && (mailInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				mailInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((relationshipInfo.m_hWnd != NULL) && (relationshipInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				relationshipInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemConsume.m_hWnd != NULL) && (itemConsume.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				itemConsume.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((roleManage.m_hWnd != NULL) && (roleManage.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				roleManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((pictureManage.m_hWnd != NULL) && (pictureManage.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				pictureManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((transMit.m_hWnd != NULL) && (transMit.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				transMit.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((queueInfo.m_hWnd != NULL) && (queueInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				queueInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((friendTrade.m_hWnd != NULL) && (friendTrade.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				friendTrade.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banList.m_hWnd != NULL) && (banList.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				banList.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((userInfoPart.m_hWnd != NULL) && (userInfoPart.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				userInfoPart.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((roleManagePart.m_hWnd != NULL) && (roleManagePart.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				roleManagePart.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((import.m_hWnd != NULL) && (import.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				import.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((backMoney.m_hWnd != NULL) && (backMoney.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				backMoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_UserInfo_Query_Resp://玩家资料查询
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemInfo.m_hWnd != NULL) && (itemInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				itemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemManage.m_hWnd != NULL) && (itemManage.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((logInfo.m_hWnd != NULL) && (logInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				logInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((treasureBoxInfo.m_hWnd != NULL) && (treasureBoxInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				treasureBoxInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((roomInfo.m_hWnd != NULL) && (roomInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				roomInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petInfo.m_hWnd != NULL) && (petInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailInfo.m_hWnd != NULL) && (mailInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				mailInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((relationshipInfo.m_hWnd != NULL) && (relationshipInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				relationshipInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemConsume.m_hWnd != NULL) && (itemConsume.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				itemConsume.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((roleManage.m_hWnd != NULL) && (roleManage.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				roleManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((pictureManage.m_hWnd != NULL) && (pictureManage.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				pictureManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((transMit.m_hWnd != NULL) && (transMit.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				transMit.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((friendTrade.m_hWnd != NULL) && (friendTrade.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				friendTrade.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((userInfoPart.m_hWnd != NULL) && (userInfoPart.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				userInfoPart.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((roleManagePart.m_hWnd != NULL) && (roleManagePart.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				roleManagePart.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((backMoney.m_hWnd != NULL) && (backMoney.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				backMoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			

		}
		break;
	case CEnumCore::Message_Tag_ID::GT_User_DetailInfo_Query_Resp://玩家详细资料查询反应
	case CEnumCore::Message_Tag_ID::GT_User_FamilyInfo_Query_Resp://角色家族信息查询反应
	case CEnumCore::Message_Tag_ID::GT_User_SentiInfo_Query_Resp://情侣信息查询反应
	case CEnumCore::Message_Tag_ID::GT_User_MarrigeInfo_Query_Resp://结婚信息查询反应
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户资料信息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_KICK_USER_ACK://踢玩家下线反应
		{
			if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_USER_STOP_ACK://封停玩家帐号
		{
			if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}

		}
		break;
	case CEnumCore::Message_Tag_ID::GT_BanUser_Query_Resp://查询单个玩家是否封停
	case CEnumCore::Message_Tag_ID::GT_AllBanUser_Query_Resp://封停玩家帐号列表查询
		{
			if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banList.m_hWnd != NULL) && (banList.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				banList.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_BROADCAST_SELECT_ACK://查询公告信息
	case CEnumCore::Message_Tag_ID::GT_BROADCAST_ADD_ACK://添加公告
	case CEnumCore::Message_Tag_ID::GT_BROADCAST_REMOVE_ACK://删除公告
		{
			if((noticeInfo.m_hWnd != NULL) && (noticeInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_FamilyInfo_Query_Resp:///家族基本信息查询//GT_FamilyInfo_Query_Resp
	case CEnumCore::Message_Tag_ID::GT_MemberInfo_Query_Resp://家庭成员详细信息返回
		{
			if((familyInfo.m_hWnd != NULL) && (familyInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				familyInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_UserPack_Query_Resp://背包物品资料返回
	case CEnumCore::Message_Tag_ID::GT_UserEquip_Query_Resp://角色装备信息的返回
	case CEnumCore::Message_Tag_ID::GT_PetPack_Query_Resp://宠物背包信息的返回
		{
			if((itemInfo.m_hWnd != NULL) && (itemInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				itemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
	case CEnumCore::Message_Tag_ID::GT_ITEM_SELECT_ACK://查询道具的返回
	case CEnumCore::Message_Tag_ID::GT_Select_Item_Resp:
	case CEnumCore::Message_Tag_ID::GT_ADD_ITEM_ACK://添加道具的返回
		{
			if((itemManage.m_hWnd != NULL) && (itemManage.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_TradeLog_Query_Resp://交易日志
	case CEnumCore::Message_Tag_ID::GT_MailLog_Query_Resp://邮件日志
	case CEnumCore::Message_Tag_ID::GT_TaskLog_Query_Resp://任务完成日志
	case CEnumCore::Message_Tag_ID::GT_UseItemLog_Query_Resp://使用道具日志
	case CEnumCore::Message_Tag_ID::GT_GuajiLog_Query_Resp://挂机奖励日志
	case CEnumCore::Message_Tag_ID::GT_BugleLog_Query_Resp://大小喇叭日志
	case CEnumCore::Message_Tag_ID::GT_LoginLog_Query_Resp://登陆登出日志
		{
			if((logInfo.m_hWnd != NULL) && (logInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				logInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_TreasureBox_Query_Resp://宝箱开启信息返回
		{
			if((treasureBoxInfo.m_hWnd != NULL) && (treasureBoxInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				treasureBoxInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_RoomInfo_Query_Resp://房屋信息的回应
		{
			if((roomInfo.m_hWnd != NULL) && (roomInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				roomInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_PetInfo_Query_Resp://宠物信息的回应
		{
			if((petInfo.m_hWnd != NULL) && (petInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_MailInfo_Query_Resp://邮件信息的回应
		{
			if((mailInfo.m_hWnd != NULL) && (mailInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				mailInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_IMFriend_Query_Resp://好友名单查询的返回
	case CEnumCore::Message_Tag_ID::GT_IMBlackList_Query_Resp://黑名单查询的返回
	case CEnumCore::Message_Tag_ID::GT_IMSecretLove_Query_Resp://暗恋名单查询的返回
		{
			if((relationshipInfo.m_hWnd != NULL) && (relationshipInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				relationshipInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_ItemConsume_Query_Resp://道具购买消费记录的返回
		{
			if((itemConsume.m_hWnd != NULL) && (itemConsume.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				itemConsume.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((backMoney.m_hWnd != NULL) && (backMoney.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				backMoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_MOVE_USER_ACK://将角色移至黑屋的返回
	case CEnumCore::Message_Tag_ID::GT_ClearName_Query_Resp://清空个性签名
		{
			if((roleManage.m_hWnd != NULL) && (roleManage.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				roleManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_USER_RESET_ACK://重设玩家到出生状态的回应
		{
			if((roleManage.m_hWnd != NULL) && (roleManage.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				roleManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((roleManagePart.m_hWnd != NULL) && (roleManagePart.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				roleManagePart.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_Picture_Clear_Resp://清理图片
	case CEnumCore::Message_Tag_ID::GT_Picture_Stop_Resp:
	case CEnumCore::Message_Tag_ID::GT_AllStopUser_Query_Resp:
		{
			if((pictureManage.m_hWnd != NULL) && (pictureManage.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				pictureManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_Transmit_Query_Resp://瞬移
		{
			if((transMit.m_hWnd != NULL) && (transMit.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				transMit.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_Mcoin_Rank_Resp://血拼战绩
	case CEnumCore::Message_Tag_ID::GT_Sns_Query_Resp://空间排行
	case CEnumCore::Message_Tag_ID::GT_Attr_Queue_Resp://属性排行
	case CEnumCore::Message_Tag_ID::GT_Card_Record_Resp://名片排行
		{
			if((queueInfo.m_hWnd != NULL) && (queueInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				queueInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_FriendTrade_Info_Resp://朋友买卖中角色信息
	case CEnumCore::Message_Tag_ID::GT_HelotInfo_Query_Resp://奴隶信息
	case CEnumCore::Message_Tag_ID::GT_FriendTrade_Queue_Resp://排行
	case CEnumCore::Message_Tag_ID::GT_FriendTrade_Log_Resp://买卖Log
		{
			if((friendTrade.m_hWnd != NULL) && (friendTrade.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				friendTrade.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_Import_Item_Resp:
		{
			if((import.m_hWnd != NULL) && (import.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				import.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_Back_Money_Resp://退款反馈
		{
			if((backMoney.m_hWnd != NULL) && (backMoney.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				backMoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	default:
		break;
	}
}

//选择打开不同的子对话框
extern "C" __declspec(dllexport) bool GTOWN_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNUserInfo")))//选中了查询用户信息(吉堂)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBanPlayer")))//选中了玩家帐号解封停(吉堂)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNNoticeInfo")))//选中了公告信息管理(吉堂)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNKickPlayer")))//选中了强制玩家下线(吉堂)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNFamilyInfo")))//选中了家族信息(吉堂)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(familyInfo.m_hWnd == NULL)
		{
			familyInfo.Create(IDD_DLGFAMILYINFO);
			familyInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(familyInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemInfo")))//选中了道具信息(吉堂)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemManage")))//选中了道具管理(吉堂)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNLogInfo")))//选中了玩家日志信息(吉堂)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNTreasureBoxInfo")))//选中了宝箱开启信息(吉堂)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(treasureBoxInfo.m_hWnd == NULL)
		{
			treasureBoxInfo.Create(IDD_DLGTREASUREBOXINFO);
			treasureBoxInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(treasureBoxInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(treasureBoxInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoomInfo")))//选中了玩家房屋信息(吉堂)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(roomInfo.m_hWnd == NULL)
		{
			roomInfo.Create(IDD_DLGROOMINFO);
			roomInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(roomInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(roomInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNPetInfo")))//选中了宠物信息(吉堂)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(petInfo.m_hWnd == NULL)
		{
			petInfo.Create(IDD_DLGPETINFO);
			petInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(petInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNMailInfo")))//选中了邮件信息(吉堂)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(mailInfo.m_hWnd == NULL)
		{
			mailInfo.Create(IDD_DLGMAILINFO);
			mailInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(mailInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(mailInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRelationshipInfo")))//选中玩家社会关系信息(吉堂)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(relationshipInfo.m_hWnd == NULL)
		{
			relationshipInfo.Create(IDD_DLGRELATIONSHIPINFO);
			relationshipInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(relationshipInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(relationshipInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemConsume")))//选中道具购买消费记录(吉堂)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(itemConsume.m_hWnd == NULL)
		{
			itemConsume.Create(IDD_DLGITEMCONSUME);
			itemConsume.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemConsume.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(itemConsume.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoleManage")))//选中玩家角色管理(吉堂)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNTransmit")))//选中瞬间移动(吉堂)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(transMit.m_hWnd == NULL)
		{
			transMit.Create(IDD_DLGTRANSMIT);
			transMit.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(transMit.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(transMit.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNPictureManage")))//选中清理违禁图片(吉堂)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(pictureManage.m_hWnd == NULL)
		{
			pictureManage.Create(IDD_DLGPICTUREMANAGE);
			pictureManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(pictureManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(pictureManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNQueueInfo")))//选中排行榜查询（吉堂）
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(queueInfo.m_hWnd == NULL)
		{
			queueInfo.Create(IDD_DLGQUEUEINFO);
			queueInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(queueInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(queueInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNFriendTrade")))//选中朋友买卖（吉堂）
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(friendTrade.m_hWnd == NULL)
		{
			friendTrade.Create(IDD_DLGFRIENDTRADE);
			friendTrade.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(friendTrade.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(friendTrade.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBanList")))//停封列表查询（只读）（吉堂）
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(banList.m_hWnd == NULL)
		{
			banList.Create(IDD_DLGBANLIST);
			banList.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(banList.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(banList.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNUserInfoPart")))//选中用户资料信息（只读）（吉堂）
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(userInfoPart.m_hWnd == NULL)
		{
			userInfoPart.Create(IDD_DLGUSERINFOPART);
			userInfoPart.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(userInfoPart.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(userInfoPart.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoleManagePart")))//选中玩家角色管理（限制）（吉堂）
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(roleManagePart.m_hWnd == NULL)
		{
			roleManagePart.Create(IDD_DLGROLEMANAGEPART);
			roleManagePart.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(roleManagePart.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(roleManagePart.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNImport")))//选中玩家角色管理（限制）（吉堂）
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(import.m_hWnd == NULL)
		{
			import.Create(IDD_DLGIMPORT);
			import.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(import.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(import.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBackMoney")))//选中玩家角色管理（限制）（吉堂）
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(backMoney.m_hWnd == NULL)
		{
			backMoney.Create(IDD_DLGBACKMONEY);
			backMoney.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(backMoney.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(backMoney.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
		return true;
	}
	return false;
}

//选择显示不同的子对话框
extern "C" __declspec(dllexport) BOOL GTOWN_SHOWDIALOG(CString m_MenuName)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNUserInfo")))//选中了查询用户信息(吉堂)
	{
		if(userInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBanPlayer")))//选中了玩家帐号解封停(吉堂)
	{
		if(banPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(banPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNNoticeInfo")))//选中了公告信息管理(吉堂)
	{
		if(noticeInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(noticeInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNKickPlayer")))//选中了强制玩家下线(吉堂)
	{
		if(kickPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(kickPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNFamilyInfo")))//选中了家族信息(吉堂)
	{
		if(familyInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(familyInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemInfo")))//选中了道具信息(吉堂)
	{
		if(itemInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(itemInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemManage")))//选中了道具管理(吉堂)
	{
		if(itemManage.m_hWnd!=NULL)
		{
			::SetWindowPos(itemManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNLogInfo")))//选中了玩家日志信息(吉堂)
	{
		if(logInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(logInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNTreasureBoxInfo")))//选中了宝箱开启信息(吉堂)
	{
		if(treasureBoxInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(treasureBoxInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoomInfo")))//选中了玩家房屋信息(吉堂)
	{
		if(roomInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(roomInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNPetInfo")))//选中了宠物信息(吉堂)
	{
		if(petInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(petInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNMailInfo")))//选中了邮件信息(吉堂)
	{
		if(mailInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(mailInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRelationshipInfo")))//选中玩家社会关系信息(吉堂)
	{
		if(relationshipInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(relationshipInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemConsume")))//选中道具购买消费记录(吉堂)
	{
		if(itemConsume.m_hWnd!=NULL)
		{
			::SetWindowPos(itemConsume.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoleManage")))//选中玩家角色管理(吉堂)
	{
		if(roleManage.m_hWnd!=NULL)
		{
			::SetWindowPos(roleManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNPictureManage")))//选中清理违禁图片(吉堂)
	{
		if(pictureManage.m_hWnd!=NULL)
		{
			::SetWindowPos(pictureManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNTransmit")))//选中瞬间移动(吉堂)
	{
		if(transMit.m_hWnd!=NULL)
		{
			::SetWindowPos(transMit.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNQueueInfo")))//选中排行榜查询（吉堂）
	{
		if(queueInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(queueInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNFriendTrade")))//选中朋友买卖（吉堂）
	{
		if(friendTrade.m_hWnd!=NULL)
		{
			::SetWindowPos(friendTrade.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBanList")))//选中停封列表查询（只读）
	{
		if(banList.m_hWnd!=NULL)
		{
			::SetWindowPos(banList.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNUserInfoPart")))//选中用户资料信息（只读）
	{
		if(userInfoPart.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfoPart.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoleManagePart")))//选中玩家角色管理（限制）
	{
		if(roleManagePart.m_hWnd!=NULL)
		{
			::SetWindowPos(roleManagePart.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNImport")))//选中玩家角色管理（限制）
	{
		if(import.m_hWnd!=NULL)
		{
			::SetWindowPos(import.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBackMoney")))//选中玩家角色管理（限制）
	{
		if(backMoney.m_hWnd!=NULL)
		{
			::SetWindowPos(backMoney.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	return FALSE;
}

//选择给子对话框发送不同的消息
extern "C" __declspec(dllexport) void GTOWN_DIALOGMSG(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam)
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
		if(familyInfo.m_hWnd != NULL)
		{
			::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyInfo.m_hWnd, Msg, wParam, lParam);//发送消息
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
		if(logInfo.m_hWnd != NULL)
		{
			::SetParent(logInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(logInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(treasureBoxInfo.m_hWnd != NULL)
		{
			::SetParent(treasureBoxInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(treasureBoxInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(roomInfo.m_hWnd != NULL)
		{
			::SetParent(roomInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(roomInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(petInfo.m_hWnd != NULL)
		{
			::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(mailInfo.m_hWnd != NULL)
		{
			::SetParent(mailInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mailInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(relationshipInfo.m_hWnd != NULL)
		{
			::SetParent(relationshipInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(relationshipInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(itemConsume.m_hWnd != NULL)
		{
			::SetParent(itemConsume.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemConsume.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(roleManage.m_hWnd!=NULL)
		{
			::SetParent(roleManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(roleManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(pictureManage.m_hWnd!=NULL)
		{
			::SetParent(pictureManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(pictureManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(transMit.m_hWnd!=NULL)
		{
			::SetParent(transMit.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(transMit.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(queueInfo.m_hWnd!=NULL)
		{
			::SetParent(queueInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(queueInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(friendTrade.m_hWnd!=NULL)
		{
			::SetParent(friendTrade.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(friendTrade.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(banList.m_hWnd!=NULL)
		{
			::SetParent(banList.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banList.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(userInfoPart.m_hWnd!=NULL)
		{
			::SetParent(userInfoPart.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userInfoPart.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(roleManagePart.m_hWnd!=NULL)
		{
			::SetParent(roleManagePart.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(roleManagePart.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(import.m_hWnd!=NULL)
		{
			::SetParent(import.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(import.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(backMoney.m_hWnd!=NULL)
		{
			::SetParent(backMoney.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(backMoney.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNUserInfo")))//选中了查询用户信息(吉堂)
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBanPlayer")))//选中了玩家帐号解封停(吉堂)
	{
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNNoticeInfo")))//选中了公告信息管理(吉堂)
	{
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNKickPlayer")))//选中了强制玩家下线(吉堂)
	{
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNFamilyInfo")))//选中了家族信息管理(吉堂)
	{
		if(familyInfo.m_hWnd != NULL)
		{
			::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemInfo")))//选中了道具信息(吉堂)
	{
		if(itemInfo.m_hWnd != NULL)
		{
			::SetParent(itemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemManage")))//选中了道具管理(吉堂)
	{
		if(itemManage.m_hWnd != NULL)
		{
			::SetParent(itemManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNLogInfo")))//选中了玩家日志信息(吉堂)
	{
		if(logInfo.m_hWnd != NULL)
		{
			::SetParent(logInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(logInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNTreasureBoxInfo")))//选中了玩家宝箱开启信息(吉堂)
	{
		if(treasureBoxInfo.m_hWnd != NULL)
		{
			::SetParent(treasureBoxInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(treasureBoxInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoomInfo")))//选中了玩家房屋信息(吉堂)
	{
		if(roomInfo.m_hWnd != NULL)
		{
			::SetParent(roomInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(roomInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNPetInfo")))//选中了宠物信息(吉堂)
	{
		if(petInfo.m_hWnd != NULL)
		{
			::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNMailInfo")))//选中了邮件信息(吉堂)
	{
		if(mailInfo.m_hWnd != NULL)
		{
			::SetParent(mailInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mailInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRelationshipInfo")))//选中社会关系信息(吉堂)
	{
		if(relationshipInfo.m_hWnd != NULL)
		{
			::SetParent(relationshipInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(relationshipInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemConsume")))//选中道具购买消费记录(吉堂)
	{
		if(itemConsume.m_hWnd!=NULL)
		{
			::SetParent(itemConsume.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemConsume.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoleManage")))//选中玩家角色管理(吉堂)
	{
		if(roleManage.m_hWnd!=NULL)
		{
			::SetParent(roleManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(roleManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNPictureManage")))//选中清理违禁图片(吉堂)
	{
		if(pictureManage.m_hWnd!=NULL)
		{
			::SetParent(pictureManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(pictureManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNTransmit")))//选中瞬间移动(吉堂)
	{
		if(transMit.m_hWnd!=NULL)
		{
			::SetParent(transMit.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(transMit.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNQueueInfo")))//选中排行榜查询（吉堂）
	{
		if(queueInfo.m_hWnd!=NULL)
		{
			::SetParent(queueInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(queueInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNFriendTrade")))//选中朋友买卖（吉堂）
	{
		if(friendTrade.m_hWnd!=NULL)
		{
			::SetParent(friendTrade.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(friendTrade.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBanList")))//选中停封列表查询（只读）
	{
		if(banList.m_hWnd!=NULL)
		{
			::SetParent(banList.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banList.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNUserInfoPart")))//选中用户资料信息（只读）
	{
		if(userInfoPart.m_hWnd!=NULL)
		{
			::SetParent(userInfoPart.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userInfoPart.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoleManagePart")))//选中玩家角色管理（限制）
	{
		if(roleManagePart.m_hWnd!=NULL)
		{
			::SetParent(roleManagePart.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(roleManagePart.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNImport")))//选中玩家角色管理（限制）
	{
		if(import.m_hWnd!=NULL)
		{
			::SetParent(import.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(import.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBackMoney")))//选中玩家角色管理（限制）
	{
		if(backMoney.m_hWnd!=NULL)
		{
			::SetParent(backMoney.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(backMoney.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
}

//再次发送同样的Query
extern "C" __declspec(dllexport) void GTOWN_SENDINFOAGAIN()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.operGTOWN.SendSameQuery();
}

extern "C" __declspec(dllexport) void GETGTOWNINFO(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent, int* m_SelectDll)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.UserByID = userByID;
	theApp.userName = userName;
	theApp.mHwndParent = m_HwndParent;
	theApp.operGTOWN.initSocket(m_socket);
	theApp.operGTOWN.intGTOWN = m_SelectDll;
}

