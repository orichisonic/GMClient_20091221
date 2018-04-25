// M_SDO.cpp : ���� DLL �ĳ�ʼ�����̡�
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

// CM_SDOApp

BEGIN_MESSAGE_MAP(CM_SDOApp, CWinApp)
END_MESSAGE_MAP()


// CM_SDOApp ����

CM_SDOApp::CM_SDOApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CM_SDOApp ����

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


// CM_SDOApp ��ʼ��

BOOL CM_SDOApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" __declspec(dllexport) BOOL SDO_TRANSLATEMESSAGE(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
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
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��������Ϣ
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
	case CEnumCore::Message_Tag_ID::SDO_ACCOUNT_QUERY_RESP://�ʺ���Ϣ��ѯ
		{
			if((accountInfo.m_hWnd != NULL) && !accountInfo.IsWindowEnabled())
			{
				accountInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHARACTERINFO_QUERY_RESP://��ɫ��Ϣ
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
	case CEnumCore::Message_Tag_ID::SDO_ITEMSHOP_BYOWNER_QUERY_RESP://��Ʒ��Ϣ
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
	case CEnumCore::Message_Tag_ID::SDO_PetInfo_Query_RESP://������Ϣ
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
	case CEnumCore::Message_Tag_ID::SDO_PetDrop_Query_RESP://����ɾ����Ϣ
		{
			if(userInfo.m_hWnd != NULL && !userInfo.IsWindowEnabled())
			{
				userInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);////SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_USERONLINE_QUERY_RESP://��¼��Ϣ
		{
			if((loginInfo.m_hWnd != NULL) && !loginInfo.IsWindowEnabled())//(loginInfo.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				loginInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_ITEMSHOP_TRADE_QUERY_RESP://������Ϣ
		{
			if((tradeInfo.m_hWnd != NULL) && !tradeInfo.IsWindowEnabled())
			{
				tradeInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CONSUME_QUERY_RESP://������Ϣ
		{
			if((shopInfo.m_hWnd != NULL) && !shopInfo.IsWindowEnabled())
			{
				shopInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);///SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_USERLOGIN_STATUS_QUERY_RESP://״̬��Ϣ
		{
			if((statusInfo.m_hWnd != NULL) && !statusInfo.IsWindowEnabled())
			{
				statusInfo.SetRecvData(lpRecvbuf, m_packethead.bodylen, m_message_tag_id);//SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_USERMARRIAGEQUERY_RESP://�����Ϣ
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
	case CEnumCore::Message_Tag_ID::SDO_BOARDMESSAGE_REQ_RESP://�༭����֮ǰ�ķ���
	case CEnumCore::Message_Tag_ID::SDO_BOARDTASK_INSERT_RESP://��ӹ���
	case CEnumCore::Message_Tag_ID::SDO_BOARDTASK_QUERY_RESP://��ѯ����
	case CEnumCore::Message_Tag_ID::SDO_BOARDTASK_UPDATE_RESP://�༭����
		{
			if((noticeInfo.m_hWnd != NULL) && (noticeInfo.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_Family_Info_QUERY_RESP://���������Ϣ
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
	case CEnumCore::Message_Tag_ID::SDO_FamilyMember_Query_RESP://�����Ա
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
	case CEnumCore::Message_Tag_ID::SDO_FamilyFormal_Query_RESP://�����г�Ա
	case CEnumCore::Message_Tag_ID::SDO_Personal_Emblem_Query_RESP://�������
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
	case CEnumCore::Message_Tag_ID::SDO_Family_Donate_Query_RES://�����������ϸ
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
	case CEnumCore::Message_Tag_ID::SDO_USERGCASH_QUERY_RESP://����G�ҽ��
	case CEnumCore::Message_Tag_ID::SDO_USERGCASH_UPDATE_RESP://����G�ҽ��
		{
			if((resupply.m_hWnd != NULL) && (resupply.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				resupply.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_INSERT_RESP://��ӱ���
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_UPDATE_RESP://�༭����
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_DELETE_RESP://ɾ������
		{
			if((matchManager.m_hWnd != NULL) && (matchManager.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				matchManager.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_QUERY_RESP://������Ϣ��ѯ
		{
			if((matchManager.m_hWnd != NULL) && (matchManager.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				matchManager.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_QUERY_RESP://����������ѯ
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
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_INSERTALL_RESP://������ӳ���
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
	case CEnumCore::Message_Tag_ID::SDO_MEDALITEM_QUERY_RESP://û��ItemName
	case CEnumCore::Message_Tag_ID::SDO_MEDALITEM_OWNER_QUERY_RESP://��ItemName
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
	case CEnumCore::Message_Tag_ID::SDO_GIFTBOX_QUERY_RESP://���
	case CEnumCore::Message_Tag_ID::SDO_Social_Update_Resp:
	case CEnumCore::Message_Tag_ID::SDO_Lucky_Update_Resp:
		{
			if((itemSet.m_hWnd != NULL) && (itemSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				itemSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_MEMBERBANISHMENT_QUERY_RESP://��ѯ����ͣ���ʺ�
	case CEnumCore::Message_Tag_ID::SDO_ACCOUNT_CLOSE_RESP://��ͣ�ʺ�
	case CEnumCore::Message_Tag_ID::SDO_ACCOUNT_OPEN_RESP://����ʺ�
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
	case CEnumCore::Message_Tag_ID::SDO_Pet_Update_RESP://�޸ĳ���ȼ��;���
		{
			if((petSet.m_hWnd != NULL) && (petSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				petSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_PCash_Update_Resp://�޸ĺ�������
		{
			if((PCashSet.m_hWnd != NULL) && (PCashSet.dlgStatus == operSDO.ReadIntValue("MSDO","Send")))
			{
				PCashSet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_Friend_Query_Resp://���Ѳ�ѯ
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

//ѡ��򿪲�ͬ���ӶԻ���
extern "C" __declspec(dllexport) bool SDO_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Account")))//����ʺ���Ϣ��ѯ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(accountInfo.m_hWnd == NULL)
		{
			accountInfo.Create(IDD_DLGACCOUNTINFO);
			accountInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(accountInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(accountInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		*/

		if(accountInfo.m_hWnd == NULL)
		{
			accountInfo.Create(CSDOBaseDlg::IDD);
			accountInfo.SetDlgCtrlID(CSDOAccountInfo::IDD);			
			::SetParent(accountInfo.m_hWnd,theApp.mHwndParent);//���о��������
			accountInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			accountInfo.ShowWindow(SW_SHOWMAXIMIZED);
			accountInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Part")))//��ҽ�ɫ��Ϣ
	{

		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		
		if(userInfo.m_hWnd == NULL)
		{
			//characterInfo.Create(IDD_DLGFRIENDMANAGER);
			userInfo.Create(CSDOBaseDlg::IDD);//CCG2BaseDlg
			userInfo.SetDlgCtrlID(CSDOUserInfo::IDD);			
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//���о��������
			userInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			userInfo.ShowWindow(SW_SHOWMAXIMIZED);
			userInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
//		::SendMessage(characterInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Login")))//��ҵ�¼��Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(loginInfo.m_hWnd == NULL)
		{
			loginInfo.Create(IDD_DLGLOGININFO);
			loginInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(loginInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		*/
		if(loginInfo.m_hWnd == NULL)
		{
			loginInfo.Create(CSDOBaseDlg::IDD);
			loginInfo.SetDlgCtrlID(CSDOAccountInfo::IDD);			
			::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//���о��������
			loginInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			loginInfo.ShowWindow(SW_SHOWMAXIMIZED);
			loginInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Trade")))//��ҽ�����Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(tradeInfo.m_hWnd == NULL)
		{
			tradeInfo.Create(IDD_DLGTRADEINFO);
			tradeInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(tradeInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(tradeInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		*/
		if(tradeInfo.m_hWnd == NULL)
		{
			tradeInfo.Create(CSDOBaseDlg::IDD);
			tradeInfo.SetDlgCtrlID(CSDOTradeInfo::IDD);			
			::SetParent(tradeInfo.m_hWnd,theApp.mHwndParent);//���о��������
			tradeInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			tradeInfo.ShowWindow(SW_SHOWMAXIMIZED);
			tradeInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Shopping")))//���������Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(shopInfo.m_hWnd == NULL)
		{
			shopInfo.Create(IDD_DLGSHOPINFO);
			shopInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(shopInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(shopInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		*/
		if(shopInfo.m_hWnd == NULL)
		{
			shopInfo.Create(CSDOBaseDlg::IDD);
			shopInfo.SetDlgCtrlID(CSDOShopInfo::IDD);			
			::SetParent(shopInfo.m_hWnd,theApp.mHwndParent);//���о��������
			shopInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			shopInfo.ShowWindow(SW_SHOWMAXIMIZED);
			shopInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Status")))//���״̬��Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(statusInfo.m_hWnd == NULL)
		{
			statusInfo.Create(IDD_DLGSTATUSINFO);////IDD_DLGSTATUSINFO
			statusInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(statusInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(statusInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		*/
		if(statusInfo.m_hWnd == NULL)
		{
			statusInfo.Create(CSDOBaseDlg::IDD);
			statusInfo.SetDlgCtrlID(CSDOStatusInfo::IDD);			
			::SetParent(statusInfo.m_hWnd,theApp.mHwndParent);//���о��������
			statusInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			statusInfo.ShowWindow(SW_SHOWMAXIMIZED);
			statusInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMarry")))//��һ�����Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(marryInfo.m_hWnd == NULL)
		{
			marryInfo.Create(IDD_DLGMARRYINFO);
			marryInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(marryInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(marryInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		*/
		if(marryInfo.m_hWnd == NULL)
		{
			marryInfo.Create(CSDOBaseDlg::IDD);
			marryInfo.SetDlgCtrlID(CSDOMarryInfo::IDD);			
			::SetParent(marryInfo.m_hWnd,theApp.mHwndParent);//���о��������
			marryInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			marryInfo.ShowWindow(SW_SHOWMAXIMIZED);
			marryInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryRewardItem")))//���ҡҡ�ֻ���Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(rewardItemInfo.m_hWnd == NULL)
		{
			rewardItemInfo.Create(IDD_DLGREWARDITEMINFO);
			rewardItemInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(rewardItemInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(rewardItemInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		*/
		if(rewardItemInfo.m_hWnd == NULL)
		{
			rewardItemInfo.Create(CSDOBaseDlg::IDD);
			rewardItemInfo.SetDlgCtrlID(CSDORewardItemInfo::IDD);			
			::SetParent(rewardItemInfo.m_hWnd,theApp.mHwndParent);//���о��������
			rewardItemInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			rewardItemInfo.ShowWindow(SW_SHOWMAXIMIZED);
			rewardItemInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","LogOff")))//ǿ���������
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(kickPlayer.m_hWnd == NULL)
		{
			kickPlayer.Create(IDD_DLGKICKPLAYER);
			kickPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(kickPlayer.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		*/
		if(kickPlayer.m_hWnd == NULL)
		{
			kickPlayer.Create(CSDOBaseDlg::IDD);
			kickPlayer.SetDlgCtrlID(CSDOKickPlayer::IDD);			
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			kickPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			kickPlayer.ShowWindow(SW_SHOWMAXIMIZED);
			kickPlayer.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmSdoNotice")))//�������ϵͳ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(noticeInfo.m_hWnd == NULL)
		{
			noticeInfo.Create(IDD_DLGNOTICE);
			noticeInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(noticeInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyInfo")))//������Ϣ��ѯ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(familyInfo.m_hWnd == NULL)
		{
			familyInfo.Create(IDD_DLGFAMILYINFO);
			familyInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(familyInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		*/
		if(familyInfo.m_hWnd == NULL)
		{
			familyInfo.Create(CSDOFamilyBaseDlg::IDD);
			familyInfo.SetDlgCtrlID(CSDOFamilyInfo::IDD);			
			::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//���о��������
			familyInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			familyInfo.ShowWindow(SW_SHOWMAXIMIZED);
			familyInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyClubHouse")))//���������־
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(familyDonate.m_hWnd == NULL)
		{
			familyDonate.Create(IDD_DLGCLUBINFO);
			familyDonate.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyDonate.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(familyDonate.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		*/
		if(familyDonate.m_hWnd == NULL)
		{
			familyDonate.Create(CSDOFamilyBaseDlg::IDD);
			familyDonate.SetDlgCtrlID(CSDOFamilyDonate::IDD);			
			::SetParent(familyDonate.m_hWnd,theApp.mHwndParent);//���о��������
			familyDonate.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			familyDonate.ShowWindow(SW_SHOWMAXIMIZED);
			familyDonate.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyPurchaseInfo")))//���幺���¼
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(purchaseInfo.m_hWnd == NULL)
		{
			purchaseInfo.Create(IDD_DLGPURCHASEINFO);
			purchaseInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(purchaseInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(purchaseInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		*/
		if(purchaseInfo.m_hWnd == NULL)
		{
			purchaseInfo.Create(CSDOFamilyBaseDlg::IDD);
			purchaseInfo.SetDlgCtrlID(CSDOPurchaseInfo::IDD);			
			::SetParent(purchaseInfo.m_hWnd,theApp.mHwndParent);//���о��������
			purchaseInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			purchaseInfo.ShowWindow(SW_SHOWMAXIMIZED);
			purchaseInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyManage")))//�������
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(familyManager.m_hWnd == NULL)
		{
			familyManager.Create(IDD_DLGFAMILYMANAGER);
			familyManager.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyManager.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(familyManager.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		*/
		if(familyManager.m_hWnd == NULL)
		{
			familyManager.Create(CSDOFamilyBaseDlg::IDD);
			familyManager.SetDlgCtrlID(CSDOFamilyManager::IDD);			
			::SetParent(familyManager.m_hWnd,theApp.mHwndParent);//���о��������
			familyManager.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			familyManager.ShowWindow(SW_SHOWMAXIMIZED);
			familyManager.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Resupply")))//���Ǳ�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(resupply.m_hWnd == NULL)
		{
			resupply.Create(IDD_DLGRESUPPLY);
			resupply.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(resupply.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(resupply.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","MatchInfo")))//������Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(matchManager.m_hWnd == NULL)
		{
			matchManager.Create(IDD_DLGMATCHMANAGER);
			matchManager.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(matchManager.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(matchManager.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmSdoGameinfo")))//������Ϣ�༭(������ӱ���)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(matchMul.m_hWnd == NULL)
		{
			matchMul.Create(IDD_DLGMATCHMUL);
			matchMul.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(matchMul.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(matchMul.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","RateEdit")))//���߻�ȡ��������
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(rateSet.m_hWnd == NULL)
		{
			rateSet.Create(IDD_DLGRATESET);
			rateSet.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(rateSet.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(rateSet.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Update")))//SDO��ҵ��߹���
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(itemSet.m_hWnd == NULL)
		{
			itemSet.Create(IDD_DLGITEMSET);
			itemSet.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemSet.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(itemSet.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Close")))//�ʺŽ�/��ͣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		/*if(banPlayer.m_hWnd == NULL)
		{
			banPlayer.Create(IDD_DLGBANPLAYER);
			banPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(banPlayer.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		*/
		if(banPlayer.m_hWnd == NULL)
		{
			banPlayer.Create(CSDOBaseDlg::IDD);
			banPlayer.SetDlgCtrlID(CSDOBanPlayer::IDD);			
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			banPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			banPlayer.ShowWindow(SW_SHOWMAXIMIZED);
			banPlayer.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","SenceEdit")))//��������
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(senceSet.m_hWnd == NULL)
		{
			senceSet.Create(IDD_DLGSENCESET);
			senceSet.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(senceSet.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(senceSet.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmYYItem")))//ҡҡ�ֵ�������
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(itemManager.m_hWnd == NULL)
		{
			itemManager.Create(IDD_DLGITEMMANAGER);
			itemManager.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemManager.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(itemManager.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","PetSet")))//������Ϣ�޸�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(petSet.m_hWnd == NULL)
		{
			petSet.Create(IDD_DLGPETSET);
			petSet.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(petSet.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(petSet.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","PCashSet")))//���������޸�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(PCashSet.m_hWnd == NULL)
		{
			PCashSet.Create(IDD_DLGPCASHSET);
			PCashSet.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(PCashSet.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(PCashSet.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","SDOFriendManager")))//���ѹ���
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(friendManager.m_hWnd == NULL)
		{
			friendManager.Create(IDD_DLGFRIENDMANAGER);
			friendManager.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(friendManager.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(friendManager.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	return FALSE;
}

//ѡ����ʾ��ͬ���ӶԻ���
extern "C" __declspec(dllexport) BOOL SDO_SHOWDIALOG(CString m_MenuName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Account")))//����ʺ���Ϣ��ѯ
	{
		if(accountInfo.m_hWnd!=NULL)
		{
			accountInfo.ShowWindow(SW_SHOWMAXIMIZED);
			accountInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Part")))//��ҽ�ɫ��Ϣ
	{
		if(userInfo.m_hWnd!=NULL)
		{
			userInfo.ShowWindow(SW_SHOWMAXIMIZED);
			userInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Login")))//��ҵ�¼��Ϣ
	{
		if(loginInfo.m_hWnd!=NULL)
		{
			loginInfo.ShowWindow(SW_SHOWMAXIMIZED);
			loginInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Trade")))//��ҽ�����Ϣ
	{
		if(tradeInfo.m_hWnd!=NULL)
		{
			tradeInfo.ShowWindow(SW_SHOWMAXIMIZED);
			tradeInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Shopping")))//���������Ϣ
	{
		if(shopInfo.m_hWnd!=NULL)
		{
			shopInfo.ShowWindow(SW_SHOWMAXIMIZED);
			shopInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Status")))//���״̬��Ϣ
	{
		if(statusInfo.m_hWnd!=NULL)
		{
			statusInfo.ShowWindow(SW_SHOWMAXIMIZED);
			statusInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMarry")))//��һ�����Ϣ
	{
		if(marryInfo.m_hWnd!=NULL)
		{
			marryInfo.ShowWindow(SW_SHOWMAXIMIZED);
			marryInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryRewardItem")))//���ҡҡ�ֻ���Ϣ
	{
		if(rewardItemInfo.m_hWnd!=NULL)
		{
			rewardItemInfo.ShowWindow(SW_SHOWMAXIMIZED);
			rewardItemInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","LogOff")))//ǿ���������
	{
		if(kickPlayer.m_hWnd!=NULL)
		{
			kickPlayer.ShowWindow(SW_SHOWMAXIMIZED);
			kickPlayer.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmSdoNotice")))//�������ϵͳ
	{
		if(noticeInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(noticeInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyInfo")))//������Ϣ��ѯ
	{
		if(familyInfo.m_hWnd!=NULL)
		{
			familyInfo.ShowWindow(SW_SHOWMAXIMIZED);
			familyInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyClubHouse")))//���������־
	{
		if(familyDonate.m_hWnd!=NULL)
		{
			familyDonate.ShowWindow(SW_SHOWMAXIMIZED);
			familyDonate.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyPurchaseInfo")))//���幺���¼
	{
		if(purchaseInfo.m_hWnd!=NULL)
		{
			purchaseInfo.ShowWindow(SW_SHOWMAXIMIZED);
			purchaseInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyManage")))//�������
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
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Resupply")))//���Ǳ�
	{
		if(resupply.m_hWnd!=NULL)
		{
			::SetWindowPos(resupply.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","MatchInfo")))//������Ϣ
	{
		if(matchManager.m_hWnd!=NULL)
		{
			::SetWindowPos(matchManager.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmSdoGameinfo")))//������ӱ���
	{
		if(matchMul.m_hWnd!=NULL)
		{
			::SetWindowPos(matchMul.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmYYItem")))//ҡҡ�ֵ�������
	{
		if(itemManager.m_hWnd!=NULL)
		{
			::SetWindowPos(itemManager.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","RateEdit")))//���߻�ȡ��������
	{
		if(rateSet.m_hWnd!=NULL)
		{
			::SetWindowPos(rateSet.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Update")))//SDO��ҵ��߹���
	{
		if(itemSet.m_hWnd!=NULL)
		{
			::SetWindowPos(itemSet.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Close")))//�ʺŽ�/��ͣ
	{
		if(banPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(banPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","SenceEdit")))//��������
	{
		if(senceSet.m_hWnd!=NULL)
		{
			::SetWindowPos(senceSet.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","petSet")))//�����޸�
	{
		if(petSet.m_hWnd!=NULL)
		{
			::SetWindowPos(petSet.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","PCashSet")))//���������޸�
	{
		if(PCashSet.m_hWnd!=NULL)
		{
			::SetWindowPos(PCashSet.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","SDOFriendManager")))//���ѹ���
	{
		if(friendManager.m_hWnd!=NULL)
		{
			::SetWindowPos(friendManager.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	return FALSE;
}

//ѡ����ӶԻ����Ͳ�ͬ����Ϣ
extern "C" __declspec(dllexport) void SDO_DIALOGMSG(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	CIni mIni;
	if(!strcmp("",m_MenuName))
	{
		if(accountInfo.m_hWnd != NULL)
		{
			::SetParent(accountInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(accountInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(loginInfo.m_hWnd != NULL)
		{
			::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(loginInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(tradeInfo.m_hWnd != NULL)
		{
			::SetParent(tradeInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(tradeInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(shopInfo.m_hWnd != NULL)
		{
			::SetParent(shopInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(shopInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(statusInfo.m_hWnd != NULL)
		{
			::SetParent(statusInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(statusInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(marryInfo.m_hWnd != NULL)
		{
			::SetParent(marryInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(marryInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(rewardItemInfo.m_hWnd != NULL)
		{
			::SetParent(rewardItemInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(rewardItemInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(familyInfo.m_hWnd != NULL)
		{
			::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(familyDonate.m_hWnd != NULL)
		{
			::SetParent(familyDonate.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyDonate.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(purchaseInfo.m_hWnd != NULL)
		{
			::SetParent(purchaseInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(purchaseInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(familyManager.m_hWnd != NULL)
		{
			::SetParent(familyManager.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyManager.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(resupply.m_hWnd != NULL)
		{
			::SetParent(resupply.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(resupply.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(matchManager.m_hWnd != NULL)
		{
			::SetParent(matchManager.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(matchManager.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(matchMul.m_hWnd != NULL)
		{
			::SetParent(matchMul.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(matchMul.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(itemManager.m_hWnd != NULL)
		{
			::SetParent(itemManager.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemManager.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(rateSet.m_hWnd != NULL)
		{
			::SetParent(rateSet.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(rateSet.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(itemSet.m_hWnd != NULL)
		{
			::SetParent(itemSet.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemSet.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(senceSet.m_hWnd != NULL)
		{
			::SetParent(senceSet.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(senceSet.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(petSet.m_hWnd != NULL)
		{
			::SetParent(petSet.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petSet.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(PCashSet.m_hWnd != NULL)
		{
			::SetParent(PCashSet.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(PCashSet.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(friendManager.m_hWnd != NULL)
		{
			::SetParent(friendManager.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(friendManager.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Account")))//����ʺ���Ϣ��ѯ
	{
		if(accountInfo.m_hWnd != NULL)
		{
			::SetParent(accountInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(accountInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Part")))//��ҽ�ɫ��Ϣ
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Login")))//��ҵ�¼��Ϣ
	{
		if(loginInfo.m_hWnd != NULL)
		{
			::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(loginInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Trade")))//��ҽ�����Ϣ
	{
		if(tradeInfo.m_hWnd != NULL)
		{
			::SetParent(tradeInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(tradeInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Shopping")))//���������Ϣ
	{
		if(shopInfo.m_hWnd != NULL)
		{
			::SetParent(shopInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(shopInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Status")))//���״̬��Ϣ
	{
		if(statusInfo.m_hWnd != NULL)
		{
			::SetParent(statusInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(statusInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMarry")))//��һ�����Ϣ
	{
		if(marryInfo.m_hWnd != NULL)
		{
			::SetParent(marryInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(marryInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryRewardItem")))//���ҡҡ�ֻ���Ϣ
	{
		if(rewardItemInfo.m_hWnd != NULL)
		{
			::SetParent(rewardItemInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(rewardItemInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","LogOff")))//ǿ���������
	{
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmSdoNotice")))//�������ϵͳ
	{
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyInfo")))//������Ϣ��ѯ
	{
		if(familyInfo.m_hWnd != NULL)
		{
			::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyClubHouse")))//���������־
	{
		if(familyDonate.m_hWnd != NULL)
		{
			::SetParent(familyDonate.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyDonate.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyPurchaseInfo")))//���幺���¼
	{
		if(purchaseInfo.m_hWnd != NULL)
		{
			::SetParent(purchaseInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(purchaseInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmQueryFamilyManage")))//�������
	{
		if(familyManager.m_hWnd != NULL)
		{
			::SetParent(familyManager.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyManager.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Resupply")))//���Ǳ�
	{
		if(resupply.m_hWnd != NULL)
		{
			::SetParent(resupply.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(resupply.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","MatchInfo")))//������Ϣ
	{
		if(matchManager.m_hWnd != NULL)
		{
			::SetParent(matchManager.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(matchManager.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmSdoGameinfo")))//������ӱ���
	{
		if(matchMul.m_hWnd != NULL)
		{
			::SetParent(matchMul.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(matchMul.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmYYItem")))//ҡҡ�ֵ�������
	{
		if(itemManager.m_hWnd != NULL)
		{
			::SetParent(itemManager.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemManager.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","RateEdit")))//���߻�ȡ��������
	{
		if(rateSet.m_hWnd != NULL)
		{
			::SetParent(rateSet.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(rateSet.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Update")))//SDO��ҵ��߹���
	{
		if(itemSet.m_hWnd != NULL)
		{
			::SetParent(itemSet.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemSet.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","Frm_SDO_Close")))//�ʺŽ�/��ͣ
	{
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","SenceEdit")))//��������
	{
		if(senceSet.m_hWnd != NULL)
		{
			::SetParent(senceSet.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(senceSet.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","petSet")))//�����޸�
	{
		if(petSet.m_hWnd != NULL)
		{
			::SetParent(petSet.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petSet.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","PCashSet")))//���������޸�
	{
		if(PCashSet.m_hWnd != NULL)
		{
			::SetParent(PCashSet.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(PCashSet.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","SDOFriendManager")))//���ѹ���
	{
		if(friendManager.m_hWnd != NULL)
		{
			::SetParent(friendManager.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(friendManager.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
}

//�ٴη���ͬ����Query
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
