// M_GTOWN.cpp : ���� DLL �ĳ�ʼ�����̡�
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

// CM_GTOWNApp

BEGIN_MESSAGE_MAP(CM_GTOWNApp, CWinApp)
END_MESSAGE_MAP()


// CM_GTOWNApp ����

CM_GTOWNApp::CM_GTOWNApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CM_GTOWNApp ����

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

// CM_GTOWNApp ��ʼ��

BOOL CM_GTOWNApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" __declspec(dllexport) BOOL GTOWN_TRANSLATEMESSAGE(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
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
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��������Ϣ
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
	case CEnumCore::Message_Tag_ID::GT_UserInfo_Query_Resp://������ϲ�ѯ
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
	case CEnumCore::Message_Tag_ID::GT_User_DetailInfo_Query_Resp://�����ϸ���ϲ�ѯ��Ӧ
	case CEnumCore::Message_Tag_ID::GT_User_FamilyInfo_Query_Resp://��ɫ������Ϣ��ѯ��Ӧ
	case CEnumCore::Message_Tag_ID::GT_User_SentiInfo_Query_Resp://������Ϣ��ѯ��Ӧ
	case CEnumCore::Message_Tag_ID::GT_User_MarrigeInfo_Query_Resp://�����Ϣ��ѯ��Ӧ
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_KICK_USER_ACK://��������߷�Ӧ
		{
			if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_USER_STOP_ACK://��ͣ����ʺ�
		{
			if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}

		}
		break;
	case CEnumCore::Message_Tag_ID::GT_BanUser_Query_Resp://��ѯ��������Ƿ��ͣ
	case CEnumCore::Message_Tag_ID::GT_AllBanUser_Query_Resp://��ͣ����ʺ��б��ѯ
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
	case CEnumCore::Message_Tag_ID::GT_BROADCAST_SELECT_ACK://��ѯ������Ϣ
	case CEnumCore::Message_Tag_ID::GT_BROADCAST_ADD_ACK://��ӹ���
	case CEnumCore::Message_Tag_ID::GT_BROADCAST_REMOVE_ACK://ɾ������
		{
			if((noticeInfo.m_hWnd != NULL) && (noticeInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_FamilyInfo_Query_Resp:///���������Ϣ��ѯ//GT_FamilyInfo_Query_Resp
	case CEnumCore::Message_Tag_ID::GT_MemberInfo_Query_Resp://��ͥ��Ա��ϸ��Ϣ����
		{
			if((familyInfo.m_hWnd != NULL) && (familyInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				familyInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_UserPack_Query_Resp://������Ʒ���Ϸ���
	case CEnumCore::Message_Tag_ID::GT_UserEquip_Query_Resp://��ɫװ����Ϣ�ķ���
	case CEnumCore::Message_Tag_ID::GT_PetPack_Query_Resp://���ﱳ����Ϣ�ķ���
		{
			if((itemInfo.m_hWnd != NULL) && (itemInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				itemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
	case CEnumCore::Message_Tag_ID::GT_ITEM_SELECT_ACK://��ѯ���ߵķ���
	case CEnumCore::Message_Tag_ID::GT_Select_Item_Resp:
	case CEnumCore::Message_Tag_ID::GT_ADD_ITEM_ACK://��ӵ��ߵķ���
		{
			if((itemManage.m_hWnd != NULL) && (itemManage.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_TradeLog_Query_Resp://������־
	case CEnumCore::Message_Tag_ID::GT_MailLog_Query_Resp://�ʼ���־
	case CEnumCore::Message_Tag_ID::GT_TaskLog_Query_Resp://���������־
	case CEnumCore::Message_Tag_ID::GT_UseItemLog_Query_Resp://ʹ�õ�����־
	case CEnumCore::Message_Tag_ID::GT_GuajiLog_Query_Resp://�һ�������־
	case CEnumCore::Message_Tag_ID::GT_BugleLog_Query_Resp://��С������־
	case CEnumCore::Message_Tag_ID::GT_LoginLog_Query_Resp://��½�ǳ���־
		{
			if((logInfo.m_hWnd != NULL) && (logInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				logInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_TreasureBox_Query_Resp://���俪����Ϣ����
		{
			if((treasureBoxInfo.m_hWnd != NULL) && (treasureBoxInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				treasureBoxInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_RoomInfo_Query_Resp://������Ϣ�Ļ�Ӧ
		{
			if((roomInfo.m_hWnd != NULL) && (roomInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				roomInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_PetInfo_Query_Resp://������Ϣ�Ļ�Ӧ
		{
			if((petInfo.m_hWnd != NULL) && (petInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_MailInfo_Query_Resp://�ʼ���Ϣ�Ļ�Ӧ
		{
			if((mailInfo.m_hWnd != NULL) && (mailInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				mailInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_IMFriend_Query_Resp://����������ѯ�ķ���
	case CEnumCore::Message_Tag_ID::GT_IMBlackList_Query_Resp://��������ѯ�ķ���
	case CEnumCore::Message_Tag_ID::GT_IMSecretLove_Query_Resp://����������ѯ�ķ���
		{
			if((relationshipInfo.m_hWnd != NULL) && (relationshipInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				relationshipInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_ItemConsume_Query_Resp://���߹������Ѽ�¼�ķ���
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
	case CEnumCore::Message_Tag_ID::GT_MOVE_USER_ACK://����ɫ�������ݵķ���
	case CEnumCore::Message_Tag_ID::GT_ClearName_Query_Resp://��ո���ǩ��
		{
			if((roleManage.m_hWnd != NULL) && (roleManage.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				roleManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_USER_RESET_ACK://������ҵ�����״̬�Ļ�Ӧ
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
	case CEnumCore::Message_Tag_ID::GT_Picture_Clear_Resp://����ͼƬ
	case CEnumCore::Message_Tag_ID::GT_Picture_Stop_Resp:
	case CEnumCore::Message_Tag_ID::GT_AllStopUser_Query_Resp:
		{
			if((pictureManage.m_hWnd != NULL) && (pictureManage.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				pictureManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_Transmit_Query_Resp://˲��
		{
			if((transMit.m_hWnd != NULL) && (transMit.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				transMit.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_Mcoin_Rank_Resp://Ѫƴս��
	case CEnumCore::Message_Tag_ID::GT_Sns_Query_Resp://�ռ�����
	case CEnumCore::Message_Tag_ID::GT_Attr_Queue_Resp://��������
	case CEnumCore::Message_Tag_ID::GT_Card_Record_Resp://��Ƭ����
		{
			if((queueInfo.m_hWnd != NULL) && (queueInfo.dlgStatus == operGTOWN.ReadIntValue("MGTOWN","Send")))
			{
				queueInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_FriendTrade_Info_Resp://���������н�ɫ��Ϣ
	case CEnumCore::Message_Tag_ID::GT_HelotInfo_Query_Resp://ū����Ϣ
	case CEnumCore::Message_Tag_ID::GT_FriendTrade_Queue_Resp://����
	case CEnumCore::Message_Tag_ID::GT_FriendTrade_Log_Resp://����Log
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
	case CEnumCore::Message_Tag_ID::GT_Back_Money_Resp://�˿��
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

//ѡ��򿪲�ͬ���ӶԻ���
extern "C" __declspec(dllexport) bool GTOWN_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNUserInfo")))//ѡ���˲�ѯ�û���Ϣ(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(userInfo.m_hWnd == NULL)
		{
			userInfo.Create(IDD_DLGUSERINFO);
			userInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(userInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBanPlayer")))//ѡ��������ʺŽ��ͣ(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(banPlayer.m_hWnd == NULL)
		{
			banPlayer.Create(IDD_DLGBANPLAYER);
			banPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(banPlayer.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNNoticeInfo")))//ѡ���˹�����Ϣ����(����)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNKickPlayer")))//ѡ����ǿ���������(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(kickPlayer.m_hWnd == NULL)
		{
			kickPlayer.Create(IDD_DLGKICKPLAYER);
			kickPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(kickPlayer.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNFamilyInfo")))//ѡ���˼�����Ϣ(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(familyInfo.m_hWnd == NULL)
		{
			familyInfo.Create(IDD_DLGFAMILYINFO);
			familyInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(familyInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemInfo")))//ѡ���˵�����Ϣ(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(itemInfo.m_hWnd == NULL)
		{
			itemInfo.Create(IDD_DLGITEMINFO);
			itemInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(itemInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemManage")))//ѡ���˵��߹���(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(itemManage.m_hWnd == NULL)
		{
			itemManage.Create(IDD_DLGITEMMANAGE);
			itemManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemManage.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(itemManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNLogInfo")))//ѡ���������־��Ϣ(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(logInfo.m_hWnd == NULL)
		{
			logInfo.Create(IDD_DLGLOGINFO);
			logInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(logInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(logInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNTreasureBoxInfo")))//ѡ���˱��俪����Ϣ(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(treasureBoxInfo.m_hWnd == NULL)
		{
			treasureBoxInfo.Create(IDD_DLGTREASUREBOXINFO);
			treasureBoxInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(treasureBoxInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(treasureBoxInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoomInfo")))//ѡ������ҷ�����Ϣ(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(roomInfo.m_hWnd == NULL)
		{
			roomInfo.Create(IDD_DLGROOMINFO);
			roomInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(roomInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(roomInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNPetInfo")))//ѡ���˳�����Ϣ(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(petInfo.m_hWnd == NULL)
		{
			petInfo.Create(IDD_DLGPETINFO);
			petInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(petInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNMailInfo")))//ѡ�����ʼ���Ϣ(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(mailInfo.m_hWnd == NULL)
		{
			mailInfo.Create(IDD_DLGMAILINFO);
			mailInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(mailInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(mailInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRelationshipInfo")))//ѡ���������ϵ��Ϣ(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(relationshipInfo.m_hWnd == NULL)
		{
			relationshipInfo.Create(IDD_DLGRELATIONSHIPINFO);
			relationshipInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(relationshipInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(relationshipInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemConsume")))//ѡ�е��߹������Ѽ�¼(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(itemConsume.m_hWnd == NULL)
		{
			itemConsume.Create(IDD_DLGITEMCONSUME);
			itemConsume.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemConsume.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(itemConsume.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoleManage")))//ѡ����ҽ�ɫ����(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(roleManage.m_hWnd == NULL)
		{
			roleManage.Create(IDD_DLGROLEMANAGE);
			roleManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(roleManage.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(roleManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNTransmit")))//ѡ��˲���ƶ�(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(transMit.m_hWnd == NULL)
		{
			transMit.Create(IDD_DLGTRANSMIT);
			transMit.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(transMit.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(transMit.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNPictureManage")))//ѡ������Υ��ͼƬ(����)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(pictureManage.m_hWnd == NULL)
		{
			pictureManage.Create(IDD_DLGPICTUREMANAGE);
			pictureManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(pictureManage.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(pictureManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNQueueInfo")))//ѡ�����а��ѯ�����ã�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(queueInfo.m_hWnd == NULL)
		{
			queueInfo.Create(IDD_DLGQUEUEINFO);
			queueInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(queueInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(queueInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNFriendTrade")))//ѡ���������������ã�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(friendTrade.m_hWnd == NULL)
		{
			friendTrade.Create(IDD_DLGFRIENDTRADE);
			friendTrade.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(friendTrade.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(friendTrade.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBanList")))//ͣ���б��ѯ��ֻ���������ã�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(banList.m_hWnd == NULL)
		{
			banList.Create(IDD_DLGBANLIST);
			banList.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(banList.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(banList.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNUserInfoPart")))//ѡ���û�������Ϣ��ֻ���������ã�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(userInfoPart.m_hWnd == NULL)
		{
			userInfoPart.Create(IDD_DLGUSERINFOPART);
			userInfoPart.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(userInfoPart.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(userInfoPart.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoleManagePart")))//ѡ����ҽ�ɫ�������ƣ������ã�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(roleManagePart.m_hWnd == NULL)
		{
			roleManagePart.Create(IDD_DLGROLEMANAGEPART);
			roleManagePart.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(roleManagePart.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(roleManagePart.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNImport")))//ѡ����ҽ�ɫ�������ƣ������ã�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(import.m_hWnd == NULL)
		{
			import.Create(IDD_DLGIMPORT);
			import.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(import.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(import.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBackMoney")))//ѡ����ҽ�ɫ�������ƣ������ã�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(backMoney.m_hWnd == NULL)
		{
			backMoney.Create(IDD_DLGBACKMONEY);
			backMoney.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(backMoney.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(backMoney.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	return false;
}

//ѡ����ʾ��ͬ���ӶԻ���
extern "C" __declspec(dllexport) BOOL GTOWN_SHOWDIALOG(CString m_MenuName)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNUserInfo")))//ѡ���˲�ѯ�û���Ϣ(����)
	{
		if(userInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBanPlayer")))//ѡ��������ʺŽ��ͣ(����)
	{
		if(banPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(banPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNNoticeInfo")))//ѡ���˹�����Ϣ����(����)
	{
		if(noticeInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(noticeInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNKickPlayer")))//ѡ����ǿ���������(����)
	{
		if(kickPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(kickPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNFamilyInfo")))//ѡ���˼�����Ϣ(����)
	{
		if(familyInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(familyInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemInfo")))//ѡ���˵�����Ϣ(����)
	{
		if(itemInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(itemInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemManage")))//ѡ���˵��߹���(����)
	{
		if(itemManage.m_hWnd!=NULL)
		{
			::SetWindowPos(itemManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNLogInfo")))//ѡ���������־��Ϣ(����)
	{
		if(logInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(logInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNTreasureBoxInfo")))//ѡ���˱��俪����Ϣ(����)
	{
		if(treasureBoxInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(treasureBoxInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoomInfo")))//ѡ������ҷ�����Ϣ(����)
	{
		if(roomInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(roomInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNPetInfo")))//ѡ���˳�����Ϣ(����)
	{
		if(petInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(petInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNMailInfo")))//ѡ�����ʼ���Ϣ(����)
	{
		if(mailInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(mailInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRelationshipInfo")))//ѡ���������ϵ��Ϣ(����)
	{
		if(relationshipInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(relationshipInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemConsume")))//ѡ�е��߹������Ѽ�¼(����)
	{
		if(itemConsume.m_hWnd!=NULL)
		{
			::SetWindowPos(itemConsume.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoleManage")))//ѡ����ҽ�ɫ����(����)
	{
		if(roleManage.m_hWnd!=NULL)
		{
			::SetWindowPos(roleManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNPictureManage")))//ѡ������Υ��ͼƬ(����)
	{
		if(pictureManage.m_hWnd!=NULL)
		{
			::SetWindowPos(pictureManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNTransmit")))//ѡ��˲���ƶ�(����)
	{
		if(transMit.m_hWnd!=NULL)
		{
			::SetWindowPos(transMit.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNQueueInfo")))//ѡ�����а��ѯ�����ã�
	{
		if(queueInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(queueInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNFriendTrade")))//ѡ���������������ã�
	{
		if(friendTrade.m_hWnd!=NULL)
		{
			::SetWindowPos(friendTrade.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBanList")))//ѡ��ͣ���б��ѯ��ֻ����
	{
		if(banList.m_hWnd!=NULL)
		{
			::SetWindowPos(banList.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNUserInfoPart")))//ѡ���û�������Ϣ��ֻ����
	{
		if(userInfoPart.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfoPart.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoleManagePart")))//ѡ����ҽ�ɫ�������ƣ�
	{
		if(roleManagePart.m_hWnd!=NULL)
		{
			::SetWindowPos(roleManagePart.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNImport")))//ѡ����ҽ�ɫ�������ƣ�
	{
		if(import.m_hWnd!=NULL)
		{
			::SetWindowPos(import.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBackMoney")))//ѡ����ҽ�ɫ�������ƣ�
	{
		if(backMoney.m_hWnd!=NULL)
		{
			::SetWindowPos(backMoney.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	return FALSE;
}

//ѡ����ӶԻ����Ͳ�ͬ����Ϣ
extern "C" __declspec(dllexport) void GTOWN_DIALOGMSG(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	CIni mIni;
	if(!strcmp("",m_MenuName))
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
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
		if(itemInfo.m_hWnd != NULL)
		{
			::SetParent(itemInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(itemManage.m_hWnd != NULL)
		{
			::SetParent(itemManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(logInfo.m_hWnd != NULL)
		{
			::SetParent(logInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(logInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(treasureBoxInfo.m_hWnd != NULL)
		{
			::SetParent(treasureBoxInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(treasureBoxInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(roomInfo.m_hWnd != NULL)
		{
			::SetParent(roomInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(roomInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(petInfo.m_hWnd != NULL)
		{
			::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(mailInfo.m_hWnd != NULL)
		{
			::SetParent(mailInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mailInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(relationshipInfo.m_hWnd != NULL)
		{
			::SetParent(relationshipInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(relationshipInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(itemConsume.m_hWnd != NULL)
		{
			::SetParent(itemConsume.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemConsume.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(roleManage.m_hWnd!=NULL)
		{
			::SetParent(roleManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(roleManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(pictureManage.m_hWnd!=NULL)
		{
			::SetParent(pictureManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(pictureManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(transMit.m_hWnd!=NULL)
		{
			::SetParent(transMit.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(transMit.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(queueInfo.m_hWnd!=NULL)
		{
			::SetParent(queueInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(queueInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(friendTrade.m_hWnd!=NULL)
		{
			::SetParent(friendTrade.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(friendTrade.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(banList.m_hWnd!=NULL)
		{
			::SetParent(banList.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banList.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(userInfoPart.m_hWnd!=NULL)
		{
			::SetParent(userInfoPart.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userInfoPart.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(roleManagePart.m_hWnd!=NULL)
		{
			::SetParent(roleManagePart.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(roleManagePart.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(import.m_hWnd!=NULL)
		{
			::SetParent(import.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(import.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(backMoney.m_hWnd!=NULL)
		{
			::SetParent(backMoney.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(backMoney.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNUserInfo")))//ѡ���˲�ѯ�û���Ϣ(����)
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBanPlayer")))//ѡ��������ʺŽ��ͣ(����)
	{
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNNoticeInfo")))//ѡ���˹�����Ϣ����(����)
	{
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNKickPlayer")))//ѡ����ǿ���������(����)
	{
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNFamilyInfo")))//ѡ���˼�����Ϣ����(����)
	{
		if(familyInfo.m_hWnd != NULL)
		{
			::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemInfo")))//ѡ���˵�����Ϣ(����)
	{
		if(itemInfo.m_hWnd != NULL)
		{
			::SetParent(itemInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemManage")))//ѡ���˵��߹���(����)
	{
		if(itemManage.m_hWnd != NULL)
		{
			::SetParent(itemManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNLogInfo")))//ѡ���������־��Ϣ(����)
	{
		if(logInfo.m_hWnd != NULL)
		{
			::SetParent(logInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(logInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNTreasureBoxInfo")))//ѡ������ұ��俪����Ϣ(����)
	{
		if(treasureBoxInfo.m_hWnd != NULL)
		{
			::SetParent(treasureBoxInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(treasureBoxInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoomInfo")))//ѡ������ҷ�����Ϣ(����)
	{
		if(roomInfo.m_hWnd != NULL)
		{
			::SetParent(roomInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(roomInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNPetInfo")))//ѡ���˳�����Ϣ(����)
	{
		if(petInfo.m_hWnd != NULL)
		{
			::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNMailInfo")))//ѡ�����ʼ���Ϣ(����)
	{
		if(mailInfo.m_hWnd != NULL)
		{
			::SetParent(mailInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mailInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRelationshipInfo")))//ѡ������ϵ��Ϣ(����)
	{
		if(relationshipInfo.m_hWnd != NULL)
		{
			::SetParent(relationshipInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(relationshipInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNItemConsume")))//ѡ�е��߹������Ѽ�¼(����)
	{
		if(itemConsume.m_hWnd!=NULL)
		{
			::SetParent(itemConsume.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemConsume.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoleManage")))//ѡ����ҽ�ɫ����(����)
	{
		if(roleManage.m_hWnd!=NULL)
		{
			::SetParent(roleManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(roleManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNPictureManage")))//ѡ������Υ��ͼƬ(����)
	{
		if(pictureManage.m_hWnd!=NULL)
		{
			::SetParent(pictureManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(pictureManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNTransmit")))//ѡ��˲���ƶ�(����)
	{
		if(transMit.m_hWnd!=NULL)
		{
			::SetParent(transMit.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(transMit.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNQueueInfo")))//ѡ�����а��ѯ�����ã�
	{
		if(queueInfo.m_hWnd!=NULL)
		{
			::SetParent(queueInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(queueInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNFriendTrade")))//ѡ���������������ã�
	{
		if(friendTrade.m_hWnd!=NULL)
		{
			::SetParent(friendTrade.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(friendTrade.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBanList")))//ѡ��ͣ���б��ѯ��ֻ����
	{
		if(banList.m_hWnd!=NULL)
		{
			::SetParent(banList.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banList.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNUserInfoPart")))//ѡ���û�������Ϣ��ֻ����
	{
		if(userInfoPart.m_hWnd!=NULL)
		{
			::SetParent(userInfoPart.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userInfoPart.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNRoleManagePart")))//ѡ����ҽ�ɫ�������ƣ�
	{
		if(roleManagePart.m_hWnd!=NULL)
		{
			::SetParent(roleManagePart.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(roleManagePart.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNImport")))//ѡ����ҽ�ɫ�������ƣ�
	{
		if(import.m_hWnd!=NULL)
		{
			::SetParent(import.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(import.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CGTOWNBackMoney")))//ѡ����ҽ�ɫ�������ƣ�
	{
		if(backMoney.m_hWnd!=NULL)
		{
			::SetParent(backMoney.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(backMoney.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
}

//�ٴη���ͬ����Query
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

