// M_JW2.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "M_JW2.h"
#include "JW2UserInfo.h"
#include "JW2BanPlayer.h"
#include "JW2KickPlayer.h"
#include "JW2NoticeInfo.h"
#include "JW2WeddingInfo.h"
#include "JW2CoupleInfo.h"
#include "JW2FamilyInfo.h"
#include "JW2LoginInfo.h"
#include "JW2UserManage.h"
#include "JW2FamilyItemInfo.h"
#include "JW2FamilyTransfer.h"
#include "JW2ItemManage.h"
#include "JW2UserInfoPart.h"
#include "JW2BanList.h"
#include "JW2PetInfo.h"
#include "JW2MailInfo.h"
#include "JW2Messenger.h"
#include "JW2FamilyFundLog.h"
#include "JW2FamilyBuyLog.h"
#include "JW2WeddingPaper.h"
#include "JW2ItemLog.h"
#include "JW2CoupleCard.h"
#include "JW2HouseInfo.h"
#include "JW2MMoney.h"
#include "JW2GMoney.h"
#include "JW2Import.h"
#include "JW2GMUpdate.h"
#include "JW2ProductManage.h"

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

// CM_JW2App

BEGIN_MESSAGE_MAP(CM_JW2App, CWinApp)
END_MESSAGE_MAP()


// CM_JW2App 构造

CM_JW2App::CM_JW2App()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CM_JW2App 对象

CM_JW2App theApp;
CJW2UserInfo userInfo;
CJW2NoticeInfo noticeInfo;
CJW2BanPlayer banPlayer;
CJW2KickPlayer kickPlayer;
CJW2WeddingInfo weddingInfo;
CJW2CoupleInfo coupleInfo;
CJW2FamilyInfo familyInfo;
CJW2LoginInfo loginInfo;
CJW2UserManage userManage;
CJW2FamilyTransfer familyTransfer;
CJW2FamilyBuyLog familyBuyLog;
CJW2FamilyItemInfo familyItemInfo;
CJW2ItemManage itemManage;
CJW2UserInfoPart userInfoPart;
CJW2BanList banList;
CJW2MailInfo mailInfo;
CJW2PetInfo petInfo;
CJW2Messenger messenger;
CJW2FamilyFundLog familyFundLog;
CJW2WeddingPaper weddingPaper;
CJW2ItemLog itemLog;
CJW2CoupleCard coupleCard;
CJW2HouseInfo houseInfo;
CJW2MMoney mMoney;
CJW2GMoney gMoney;
CJW2Import Import;
CJW2GMUpdate gmUpdate;
CJW2ProductManage productManage;

// CM_JW2App 初始化

BOOL CM_JW2App::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
extern "C" __declspec(dllexport) BOOL JW2_TRANSLATEMESSAGE(MSG* pMsg)
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
				if(weddingInfo.m_hWnd!=NULL)
				{
					weddingInfo.PreTranslateMessage(pMsg);
				}
				if(coupleInfo.m_hWnd!=NULL)
				{
					coupleInfo.PreTranslateMessage(pMsg);
				}
				if(familyInfo.m_hWnd!=NULL)
				{
					familyInfo.PreTranslateMessage(pMsg);
				}
				if(loginInfo.m_hWnd!=NULL)
				{
					loginInfo.PreTranslateMessage(pMsg);
				}
				if(userManage.m_hWnd!=NULL)
				{
					userManage.PreTranslateMessage(pMsg);
				}
				if(familyBuyLog.m_hWnd!=NULL)
				{
					familyBuyLog.PreTranslateMessage(pMsg);
				}
				if(familyItemInfo.m_hWnd!=NULL)
				{
					familyItemInfo.PreTranslateMessage(pMsg);
				}
				if(familyTransfer.m_hWnd!=NULL)
				{
					familyTransfer.PreTranslateMessage(pMsg);
				}
				if(itemManage.m_hWnd!=NULL)
				{
					itemManage.PreTranslateMessage(pMsg);
				}
				if(userInfoPart.m_hWnd!=NULL)
				{
					userInfoPart.PreTranslateMessage(pMsg);
				}
				if(banList.m_hWnd!=NULL)
				{
					banList.PreTranslateMessage(pMsg);
				}
				if(mailInfo.m_hWnd!=NULL)
				{
					mailInfo.PreTranslateMessage(pMsg);
				}
				if(petInfo.m_hWnd!=NULL)
				{
					petInfo.PreTranslateMessage(pMsg);
				}
				if(messenger.m_hWnd!=NULL)
				{
					messenger.PreTranslateMessage(pMsg);
				}
				if(familyFundLog.m_hWnd!=NULL)
				{
					familyFundLog.PreTranslateMessage(pMsg);
				}
				
				if(weddingPaper.m_hWnd!=NULL)
				{
					weddingPaper.PreTranslateMessage(pMsg);
				}
				if(itemLog.m_hWnd!=NULL)
				{
					itemLog.PreTranslateMessage(pMsg);
				}
				if(coupleCard.m_hWnd!=NULL)
				{
					coupleCard.PreTranslateMessage(pMsg);
				}
				if(houseInfo.m_hWnd!=NULL)
				{
					houseInfo.PreTranslateMessage(pMsg);
				}
				if(mMoney.m_hWnd!=NULL)
				{
					mMoney.PreTranslateMessage(pMsg);
				}
				if(gMoney.m_hWnd!=NULL)
				{
					gMoney.PreTranslateMessage(pMsg);
				}
				if(Import.m_hWnd!=NULL)
				{
					Import.PreTranslateMessage(pMsg);
				}
				if(gmUpdate.m_hWnd!=NULL)
				{
					gmUpdate.PreTranslateMessage(pMsg);
				}
				if(productManage.m_hWnd!=NULL)
				{
					productManage.PreTranslateMessage(pMsg);
				}
			}
		}		
	}
	return FALSE;
}
extern "C" __declspec(dllexport) void GETJW2MESSAGE(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.m_TagID = m_message_tag_id;
	OperationJW2 operJW2;

	switch(m_message_tag_id)
	{	
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://服务器信息
		{
			if((userInfo.m_hWnd != NULL) &&(userInfo.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd != NULL) &&(kickPlayer.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd != NULL) &&(banPlayer.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((noticeInfo.m_hWnd != NULL) &&(noticeInfo.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((weddingInfo.m_hWnd != NULL) &&(weddingInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				weddingInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((coupleInfo.m_hWnd != NULL) &&(coupleInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				coupleInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((familyInfo.m_hWnd != NULL) &&(familyInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((loginInfo.m_hWnd != NULL) &&(loginInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				loginInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((userManage.m_hWnd != NULL) &&(userManage.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				userManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((familyBuyLog.m_hWnd != NULL) &&(familyBuyLog.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyBuyLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((familyItemInfo.m_hWnd != NULL) &&(familyItemInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyItemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((familyTransfer.m_hWnd != NULL) &&(familyTransfer.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyTransfer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemManage.m_hWnd != NULL) &&(itemManage.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((userInfoPart.m_hWnd != NULL) &&(userInfoPart.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				userInfoPart.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banList.m_hWnd != NULL) &&(banList.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				banList.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((messenger.m_hWnd != NULL) &&(messenger.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				messenger.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailInfo.m_hWnd != NULL) &&(mailInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				mailInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petInfo.m_hWnd != NULL) &&(petInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((familyFundLog.m_hWnd != NULL) &&(familyFundLog.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyFundLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((weddingPaper.m_hWnd != NULL) &&(weddingPaper.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				weddingPaper.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemLog.m_hWnd != NULL) &&(itemLog.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				itemLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((coupleCard.m_hWnd != NULL) &&(coupleCard.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				coupleCard.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((houseInfo.m_hWnd != NULL) &&(houseInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				houseInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mMoney.m_hWnd != NULL) &&(mMoney.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				mMoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((gMoney.m_hWnd != NULL) &&(gMoney.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				gMoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((Import.m_hWnd != NULL) &&(Import.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				Import.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((gmUpdate.m_hWnd != NULL) &&(gmUpdate.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				gmUpdate.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((productManage.m_hWnd != NULL) &&(productManage.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				productManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}

		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_QUERY_RESP://用户资料查询
		{
			if((userInfo.m_hWnd != NULL) &&(userInfo.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd != NULL) &&(kickPlayer.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd != NULL) &&(banPlayer.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((weddingInfo.m_hWnd != NULL) &&(weddingInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				weddingInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((coupleInfo.m_hWnd != NULL) &&(coupleInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				coupleInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((familyInfo.m_hWnd != NULL) &&(familyInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((userManage.m_hWnd != NULL) &&(userManage.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				userManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemManage.m_hWnd != NULL) &&(itemManage.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((userInfoPart.m_hWnd != NULL) &&(userInfoPart.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				userInfoPart.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailInfo.m_hWnd != NULL) &&(mailInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				mailInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((messenger.m_hWnd != NULL) &&(messenger.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				messenger.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petInfo.m_hWnd != NULL) &&(petInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((weddingPaper.m_hWnd != NULL) &&(weddingPaper.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				weddingPaper.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemLog.m_hWnd != NULL) &&(itemLog.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				itemLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((coupleCard.m_hWnd != NULL) &&(coupleCard.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				coupleCard.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((houseInfo.m_hWnd != NULL) &&(houseInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				houseInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mMoney.m_hWnd != NULL) &&(mMoney.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				mMoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((gMoney.m_hWnd != NULL) &&(gMoney.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				gMoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((gmUpdate.m_hWnd != NULL) &&(gmUpdate.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				gmUpdate.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_RPG_QUERY_RESP://故事情节信息
	case CEnumCore::Message_Tag_ID::JW2_ITEMSHOP_BYOWNER_QUERY_RESP://玩家道具信息
	case CEnumCore::Message_Tag_ID::JW2_SMALL_PRESENT_QUERY_RESP://购物送礼信息
	case CEnumCore::Message_Tag_ID::JW2_WASTE_ITEM_QUERY_RESP://消耗性道具
	case CEnumCore::Message_Tag_ID::JW2_SMALL_BUGLE_QUERY_RESP://小喇叭信息	
	case CEnumCore::Message_Tag_ID::JW2_User_Family_Query_Resp:
		{
			if((userInfo.m_hWnd != NULL) &&(userInfo.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_HOME_ITEM_QUERY_RESP://房间物品清单与期限
		{
			if((userInfo.m_hWnd != NULL) &&(userInfo.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
			else if((houseInfo.m_hWnd != NULL) &&(houseInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				houseInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_BANISHPLAYER_RESP://强制玩家下线
		{
			if((kickPlayer.m_hWnd != NULL) &&(kickPlayer.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_CLOSE_RESP://封停玩家帐号
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_OPEN_RESP://解封玩家帐号
		{
			if((banPlayer.m_hWnd != NULL) &&(banPlayer.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_BANISHMENT_QUERY_RESP://查询帐号有没有被封停
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNTREMOTE_QUERY_RESP://查询所有封停帐号
		{
			if((banPlayer.m_hWnd != NULL) &&(banPlayer.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
			else if((banList.m_hWnd != NULL) &&(banList.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				banList.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_BOARDTASK_QUERY_RESP://查询所有公告信息
	case CEnumCore::Message_Tag_ID::JW2_BOARDTASK_INSERT_RESP://添加公告信息
	case CEnumCore::Message_Tag_ID::JW2_BOARDTASK_UPDATE_RESP://编辑公告信息
		{
			if((noticeInfo.m_hWnd != NULL) &&(noticeInfo.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_WEDDINGINFO_QUERY_RESP:
	case CEnumCore::Message_Tag_ID::JW2_WEDDINGLOG_QUERY_RESP:
		{
			if((weddingInfo.m_hWnd != NULL) &&(weddingInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				weddingInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_COUPLEINFO_QUERY_RESP:
	case CEnumCore::Message_Tag_ID::JW2_COUPLELOG_QUERY_RESP:
		{
			if((coupleInfo.m_hWnd != NULL) &&(coupleInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				coupleInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_FAMILYINFO_QUERY_RESP://家族基本信息
		{
			if((familyInfo.m_hWnd != NULL) &&(familyInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
			else if((familyBuyLog.m_hWnd != NULL) &&(familyBuyLog.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyBuyLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((familyTransfer.m_hWnd != NULL) &&(familyTransfer.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyTransfer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((familyItemInfo.m_hWnd != NULL) &&(familyItemInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyItemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((familyFundLog.m_hWnd != NULL) &&(familyFundLog.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyFundLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_FAMILYMEMBER_QUERY_RESP:
	case CEnumCore::Message_Tag_ID::JW2_BasicInfo_Query_Resp:
	case CEnumCore::Message_Tag_ID::JW2_BasicRank_Query_Resp:
	case CEnumCore::Message_Tag_ID::JW2_FamilyMember_Applying_Resp:
		{
			if((familyInfo.m_hWnd != NULL) &&(familyInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_FamilyItemInfo_Query_Resp:
		{
			if((familyItemInfo.m_hWnd != NULL) &&(familyItemInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyItemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_LOGINOUT_QUERY_RESP:
		{
			if((loginInfo.m_hWnd != NULL) &&(loginInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				loginInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_MODIFY_PWD_RESP:
	case CEnumCore::Message_Tag_ID::JW2_RECALL_PWD_RESP:
	case CEnumCore::Message_Tag_ID::JW2_MODIFYSEX_QUERY_RESP:
	case CEnumCore::Message_Tag_ID::JW2_MODIFYLEVEL_QUERY_RESP:
	case CEnumCore::Message_Tag_ID::JW2_MODIFYEXP_QUERY_RESP:
		{
			if((userManage.m_hWnd != NULL) &&(userManage.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				userManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ItemInfo_Query_Resp:
	case CEnumCore::Message_Tag_ID::JW2_ITEM_DEL_RESP:
	case CEnumCore::Message_Tag_ID::JW2_ADD_ITEM_RESP:
	case CEnumCore::Message_Tag_ID::JW2_MODIFY_MONEY_RESP:
	///maple add
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Validate_Resp://验证权限
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Deduct_Resp://验证通过在权限表中减去
		{
			if((itemManage.m_hWnd != NULL) &&(itemManage.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ITEM_SELECT_RESP:
		{
			if((itemManage.m_hWnd != NULL) &&(itemManage.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
			else if((productManage.m_hWnd != NULL) &&(productManage.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				productManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}	
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_PetInfo_Query_Resp:
		{
			if((petInfo.m_hWnd != NULL) &&(petInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_MailInfo_Query_Resp:
		{
			if((mailInfo.m_hWnd != NULL) &&(mailInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				mailInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_Messenger_Query_Resp:
		{
			if((messenger.m_hWnd != NULL) &&(messenger.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				messenger.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_FamilyFund_Log_Resp:
		{
			if((familyFundLog.m_hWnd != NULL) &&(familyFundLog.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyFundLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;

	case CEnumCore::Message_Tag_ID::JW2_Wedding_Paper_Resp:
		{
			if((weddingPaper.m_hWnd != NULL) &&(weddingPaper.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				weddingPaper.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_CoupleParty_Card_Resp:
		{
			if((coupleCard.m_hWnd != NULL) &&(coupleCard.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				coupleCard.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_Item_Log_Resp:
		{
			if((itemLog.m_hWnd != NULL) &&(itemLog.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				itemLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_FamilyBuyLog_Query_Resp:
		{
			if((familyBuyLog.m_hWnd != NULL) &&(familyBuyLog.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyBuyLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_MoneyLog_Query_Resp:
	case CEnumCore::Message_Tag_ID::JW2_CashMoney_Log_Resp:
		{
			if((gMoney.m_hWnd != NULL) &&(gMoney.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				gMoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
			else if((mMoney.m_hWnd != NULL) &&(mMoney.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				mMoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_Import_KickPlayer_Resp:
	case CEnumCore::Message_Tag_ID::JW2_Import_AccountClose_Resp:
	case CEnumCore::Message_Tag_ID::JW2_Import_AccountOpen_Resp:
		{
			if((Import.m_hWnd != NULL) &&(Import.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				Import.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_GM_Update_Resp:
		{
			if((gmUpdate.m_hWnd != NULL) &&(gmUpdate.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				gmUpdate.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_QUERY_ALL_RESP:
	//maple add
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Insert_Resp://增加权限
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Del_Resp://删除权限
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_View_Resp://查看权限
	////case CEnumCore::Message_Tag_ID::JW2_ProductManage_Validate_Resp://验证权限
		{
			if((productManage.m_hWnd != NULL) &&(productManage.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				productManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//给用户管理界面发消息
			}	
		}
		break;
	default:
		break;
	}
}
//选择打开不同的子对话框
extern "C" __declspec(dllexport) void JW2_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserInfo")))//选中了查询用户信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(userInfo.m_hWnd == NULL)
		{
			userInfo.Create(IDD_DLGUSERINFO);
			userInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(userInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2KickPlayer")))//选中了强制玩家下线
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(kickPlayer.m_hWnd == NULL)
		{
			kickPlayer.Create(IDD_DLGKICKPLAYER);
			kickPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(kickPlayer.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2BanPlayer")))//选中了玩家帐号解封停(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(banPlayer.m_hWnd == NULL)
		{
			banPlayer.Create(IDD_DLGBANPLAYER);
			banPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(banPlayer.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2NoticeInfo")))//选中了公告信息(仙剑)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(noticeInfo.m_hWnd == NULL)
		{
			noticeInfo.Create(IDD_DLGNOTICE);
			noticeInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(noticeInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2WeddingInfo")))//选中了婚姻信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(weddingInfo.m_hWnd == NULL)
		{
			weddingInfo.Create(IDD_DLGWEDDINGINFO);
			weddingInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(weddingInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(weddingInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2CoupleInfo")))//选中了情侣信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(coupleInfo.m_hWnd == NULL)
		{
			coupleInfo.Create(IDD_DLGCOUPLEINFO);
			coupleInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(coupleInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(coupleInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyInfo")))//选中了家族信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(familyInfo.m_hWnd == NULL)
		{
			familyInfo.Create(IDD_DLGFAMILYINFO);
			familyInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(familyInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2LoginInfo")))//选中了玩家登入/登出信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(loginInfo.m_hWnd == NULL)
		{
			loginInfo.Create(IDD_DLGLOGININFO);
			loginInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(loginInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserManage")))//给用户管理界面发消息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(userManage.m_hWnd == NULL)
		{
			userManage.Create(IDD_DLGUSERMANAGE);
			userManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(userManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(userManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyItemInfo")))//家族道具信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(familyItemInfo.m_hWnd == NULL)
		{
			familyItemInfo.Create(IDD_DLGFAMILYITEMINFO);
			familyItemInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyItemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(familyItemInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyBuyLog")))//家族购买日志信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(familyBuyLog.m_hWnd == NULL)
		{
			familyBuyLog.Create(IDD_DLGFAMILYBUYLOG);
			familyBuyLog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyBuyLog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(familyBuyLog.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyTransfer")))//家族转让信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(familyTransfer.m_hWnd == NULL)
		{
			familyTransfer.Create(IDD_DLGFAMILYTRANSFER);
			familyTransfer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyTransfer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(familyTransfer.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ItemManage")))//道具管理
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(itemManage.m_hWnd == NULL)
		{
			itemManage.Create(IDD_DLGITEMMANAGE);
			itemManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(itemManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserInfoPart")))//道具管理
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(userInfoPart.m_hWnd == NULL)
		{
			userInfoPart.Create(IDD_DLGUSERINFOPART);
			userInfoPart.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(userInfoPart.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(userInfoPart.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2BanList")))//封停列表
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(banList.m_hWnd == NULL)
		{
			banList.Create(IDD_DLGBANLIST);
			banList.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(banList.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(banList.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2MailInfo")))//邮件信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(mailInfo.m_hWnd == NULL)
		{
			mailInfo.Create(IDD_DLGMAILINFO);
			mailInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(mailInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(mailInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2PetInfo")))//宠物信息
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(petInfo.m_hWnd == NULL)
		{
			petInfo.Create(IDD_DLGPETINFO);
			petInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(petInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2Messenger")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(messenger.m_hWnd == NULL)
		{
			messenger.Create(IDD_DLGMESSENGER);
			messenger.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(messenger.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(messenger.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyFundLog")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(familyFundLog.m_hWnd == NULL)
		{
			familyFundLog.Create(IDD_DLGFAMILYFUNDLOG);
			familyFundLog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyFundLog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(familyFundLog.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2WeddingPaper")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(weddingPaper.m_hWnd == NULL)
		{
			weddingPaper.Create(IDD_DLGWEDDINGPAPER);
			weddingPaper.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(weddingPaper.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(weddingPaper.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ItemLog")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(itemLog.m_hWnd == NULL)
		{
			itemLog.Create(IDD_DLGITEMLOG);
			itemLog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemLog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(itemLog.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2CoupleCard")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(coupleCard.m_hWnd == NULL)
		{
			coupleCard.Create(IDD_DLGCOUPLECARD);
			coupleCard.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(coupleCard.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(coupleCard.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2HouseInfo")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(houseInfo.m_hWnd == NULL)
		{
			houseInfo.Create(IDD_DLGHOUSEINFO);
			houseInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(houseInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(houseInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2MMoney")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(mMoney.m_hWnd == NULL)
		{
			mMoney.Create(IDD_DLGMMONEY);
			mMoney.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(mMoney.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(mMoney.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2GMoney")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(gMoney.m_hWnd == NULL)
		{
			gMoney.Create(IDD_DLGGMONEY);
			gMoney.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(gMoney.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(gMoney.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2Import")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(Import.m_hWnd == NULL)
		{
			Import.Create(IDD_DLGIMPORT);
			Import.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(Import.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(Import.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2GMUpdate")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(gmUpdate.m_hWnd == NULL)
		{
			gmUpdate.Create(IDD_DLGGMUPDATE);
			gmUpdate.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(gmUpdate.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(gmUpdate.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ProductManage")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(productManage.m_hWnd == NULL)
		{
			productManage.Create(IDD_DLGPRODUCTMANAGE);
			productManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(productManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
		::SendMessage(productManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//让对话框最大化
	}
}

//选择显示不同的子对话框
extern "C" __declspec(dllexport) BOOL JW2_SHOWDIALOG(CString m_MenuName)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserInfo")))//选中了查询用户信息
	{
		if(userInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2KickPalyer")))//选中了强制玩家下线
	{
		if(kickPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(kickPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2BanPlayer")))//选中了玩家帐号解封停
	{
		if(banPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(banPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2NoticeInfo")))//选中了公告信息
	{
		if(noticeInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(noticeInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2WeddingInfo")))//选中了婚姻信息
	{
		if(weddingInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(weddingInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2CoupleInfo")))//选中了情侣信息
	{
		if(coupleInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(coupleInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyInfo")))//选中了家族信息
	{
		if(familyInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(familyInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2LoginInfo")))//选中了玩家登入/登出信息
	{
		if(loginInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(loginInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserManage")))//给用户管理界面发消息
	{
		if(userManage.m_hWnd!=NULL)
		{
			::SetWindowPos(userManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyItemInfo")))//家族道具信息
	{
		if(familyItemInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(familyItemInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyBuyLog")))//家族购买日志信息
	{
		if(familyBuyLog.m_hWnd!=NULL)
		{
			::SetWindowPos(familyBuyLog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyTransfer")))//家族转让信息
	{
		if(familyTransfer.m_hWnd!=NULL)
		{
			::SetWindowPos(familyTransfer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ItemManage")))//道具管理
	{
		if(itemManage.m_hWnd!=NULL)
		{
			::SetWindowPos(itemManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserInfoPart")))//道具管理
	{
		if(userInfoPart.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfoPart.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2BanList")))//道具管理
	{
		if(banList.m_hWnd!=NULL)
		{
			::SetWindowPos(banList.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2PetInfo")))//道具管理
	{
		if(petInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(petInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2MailInfo")))//道具管理
	{
		if(mailInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(mailInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2Messenger")))//道具管理
	{
		if(messenger.m_hWnd!=NULL)
		{
			::SetWindowPos(messenger.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyFundLog")))//道具管理
	{
		if(familyFundLog.m_hWnd!=NULL)
		{
			::SetWindowPos(familyFundLog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2WeddingPaper")))//道具管理
	{
		if(weddingPaper.m_hWnd!=NULL)
		{
			::SetWindowPos(weddingPaper.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ItemLog")))//道具管理
	{
		if(itemLog.m_hWnd!=NULL)
		{
			::SetWindowPos(itemLog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2CoupleCard")))//道具管理
	{
		if(coupleCard.m_hWnd!=NULL)
		{
			::SetWindowPos(coupleCard.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2HouseInfo")))//道具管理
	{
		if(houseInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(houseInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2MMoney")))//道具管理
	{
		if(mMoney.m_hWnd!=NULL)
		{
			::SetWindowPos(mMoney.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2Import")))//道具管理
	{
		if(Import.m_hWnd!=NULL)
		{
			::SetWindowPos(Import.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2GMUpdate")))//道具管理
	{
		if(gmUpdate.m_hWnd!=NULL)
		{
			::SetWindowPos(gmUpdate.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ProductManage")))//道具权限
	{
		if(productManage.m_hWnd!=NULL)
		{
			::SetWindowPos(productManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}

	return FALSE;
}
//选择给不同的子对话框发送消息
extern "C" __declspec(dllexport) void JW2_DIALOGMSG(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam)
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
		if(weddingInfo.m_hWnd != NULL)
		{
			::SetParent(weddingInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(weddingInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(coupleInfo.m_hWnd != NULL)
		{
			::SetParent(coupleInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(coupleInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(familyInfo.m_hWnd != NULL)
		{
			::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(loginInfo.m_hWnd != NULL)
		{
			::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(loginInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(userManage.m_hWnd != NULL)
		{
			::SetParent(userManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(familyBuyLog.m_hWnd != NULL)
		{
			::SetParent(familyBuyLog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyBuyLog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(familyTransfer.m_hWnd != NULL)
		{
			::SetParent(familyTransfer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyTransfer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(familyItemInfo.m_hWnd != NULL)
		{
			::SetParent(familyItemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyItemInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(itemManage.m_hWnd != NULL)
		{
			::SetParent(itemManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(userInfoPart.m_hWnd != NULL)
		{
			::SetParent(userInfoPart.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userInfoPart.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(banList.m_hWnd != NULL)
		{
			::SetParent(banList.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banList.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(messenger.m_hWnd != NULL)
		{
			::SetParent(messenger.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(messenger.m_hWnd, Msg, wParam, lParam);//发送消息
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
		if(familyFundLog.m_hWnd != NULL)
		{
			::SetParent(familyFundLog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyFundLog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(weddingPaper.m_hWnd != NULL)
		{
			::SetParent(weddingPaper.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(weddingPaper.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(itemLog.m_hWnd != NULL)
		{
			::SetParent(itemLog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemLog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(coupleCard.m_hWnd != NULL)
		{
			::SetParent(coupleCard.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(coupleCard.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(houseInfo.m_hWnd != NULL)
		{
			::SetParent(houseInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(houseInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(mMoney.m_hWnd != NULL)
		{
			::SetParent(mMoney.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mMoney.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(gMoney.m_hWnd != NULL)
		{
			::SetParent(gMoney.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(gMoney.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(Import.m_hWnd != NULL)
		{
			::SetParent(Import.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(Import.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(gmUpdate.m_hWnd != NULL)
		{
			::SetParent(gmUpdate.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(gmUpdate.m_hWnd, Msg, wParam, lParam);//发送消息
		}
		if(productManage.m_hWnd != NULL)
		{
			::SetParent(productManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(productManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserInfo")))//选中了查询用户信息
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2KickPlayer")))//选中了强制玩家下线
	{
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2BanPlayer")))//玩家角色信息（超级舞者）
	{
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2NoticeInfo")))//玩家角色信息（超级舞者）
	{
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2WeddingInfo")))//选中了婚姻信息
	{
		if(weddingInfo.m_hWnd != NULL)
		{
			::SetParent(weddingInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(weddingInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2CoupleInfo")))//选中了情侣信息
	{
		if(coupleInfo.m_hWnd != NULL)
		{
			::SetParent(coupleInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(coupleInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyInfo")))//选中了家族信息
	{
		if(familyInfo.m_hWnd != NULL)
		{
			::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2LoginInfo")))//选中了家族信息
	{
		if(loginInfo.m_hWnd != NULL)
		{
			::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(loginInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserManage")))//选中了家族信息
	{
		if(userManage.m_hWnd != NULL)
		{
			::SetParent(userManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyItemInfo")))//选中了家族信息
	{
		if(familyItemInfo.m_hWnd != NULL)
		{
			::SetParent(familyItemInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyItemInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyBuyLog")))//选中了家族信息
	{
		if(familyBuyLog.m_hWnd != NULL)
		{
			::SetParent(familyBuyLog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyBuyLog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyTransfer")))//选中了家族信息
	{
		if(familyTransfer.m_hWnd != NULL)
		{
			::SetParent(familyTransfer.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyTransfer.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ItemManage")))//选中了家族信息
	{
		if(itemManage.m_hWnd != NULL)
		{
			::SetParent(itemManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserInfoPart")))//选中了家族信息
	{
		if(userInfoPart.m_hWnd != NULL)
		{
			::SetParent(userInfoPart.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(userInfoPart.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2BanList")))//选中了家族信息
	{
		if(banList.m_hWnd != NULL)
		{
			::SetParent(banList.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(banList.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2PetInfo")))//选中了家族信息
	{
		if(petInfo.m_hWnd != NULL)
		{
			::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(petInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2MailInfo")))//选中了家族信息
	{
		if(mailInfo.m_hWnd != NULL)
		{
			::SetParent(mailInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mailInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2Messenger")))//选中了家族信息
	{
		if(messenger.m_hWnd != NULL)
		{
			::SetParent(messenger.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(messenger.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyFundLog")))//选中了家族信息
	{
		if(familyFundLog.m_hWnd != NULL)
		{
			::SetParent(familyFundLog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(familyFundLog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2WeddingPaper")))//选中了家族信息
	{
		if(weddingPaper.m_hWnd != NULL)
		{
			::SetParent(weddingPaper.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(weddingPaper.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2CoupleCard")))//选中了家族信息
	{
		if(coupleCard.m_hWnd != NULL)
		{
			::SetParent(coupleCard.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(coupleCard.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2HouseInfo")))//选中了家族信息
	{
		if(houseInfo.m_hWnd != NULL)
		{
			::SetParent(houseInfo.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(houseInfo.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ItemLog")))//选中了家族信息
	{
		if(itemLog.m_hWnd != NULL)
		{
			::SetParent(itemLog.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(itemLog.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2MMoney")))//选中了家族信息
	{
		if(mMoney.m_hWnd != NULL)
		{
			::SetParent(mMoney.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(mMoney.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2GMoney")))//选中了家族信息
	{
		if(gMoney.m_hWnd != NULL)
		{
			::SetParent(gMoney.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(gMoney.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2Import")))//选中了家族信息
	{
		if(Import.m_hWnd != NULL)
		{
			::SetParent(Import.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(Import.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2GMUpdate")))//选中了家族信息
	{
		if(gmUpdate.m_hWnd != NULL)
		{
			::SetParent(gmUpdate.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(gmUpdate.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ProductManage")))//选中了道具权限
	{
		if(productManage.m_hWnd != NULL)
		{
			::SetParent(productManage.m_hWnd,theApp.mHwndParent);//进行句柄的设置
			::SendMessage(productManage.m_hWnd, Msg, wParam, lParam);//发送消息
		}
	}

}

//再次发送同样的Query
extern "C" __declspec(dllexport) void JW2_SENDINFOAGAIN()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.operJW2.SendSameQuery();
}

extern "C" __declspec(dllexport) void GETJW2INFO(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent, int* m_SelectDll)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.UserByID = userByID;
	theApp.userName = userName;
	theApp.mHwndParent = m_HwndParent;
	theApp.operJW2.initSocket(m_socket);//operPAL.initSocket(m_socket);
	theApp.operJW2.intJW2 = m_SelectDll;//operPAL.intPAL = m_SelectDll;
}