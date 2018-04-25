// M_PAL.cpp : ���� DLL �ĳ�ʼ�����̡�
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

// CM_PALApp

BEGIN_MESSAGE_MAP(CM_PALApp, CWinApp)
END_MESSAGE_MAP()


// CM_PALApp ����

CM_PALApp::CM_PALApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CM_PALApp ����

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

// CM_PALApp ��ʼ��

BOOL CM_PALApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" __declspec(dllexport) BOOL PAL_TRANSLATEMESSAGE(MSG* pMsg)
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
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��������Ϣ
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
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERINFO_RESP://ȡ�ý�ɫ������Ѷ��Ӧ
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

	case CEnumCore::Message_Tag_ID::PAL_CHARACTERFRIENDLIST_RESP://��ɫ�����б�
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERQUEST_RESP://��ɫ����
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERADVANCEINFO_RESP://��ɫ������Ѷ
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERSKILL_RESP://��ɫ������Ѷ
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERBLACKLIST_RESP://��ɫ�������б�
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
	case CEnumCore::Message_Tag_ID::PAL_BANISHPLAYER_RESP://ǿ���������
		{
			if(kickPlayer.m_hWnd != NULL)
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��ǿ��������߽��淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_ACCOUNT_CLOSE_RESP://��ͣ����ʺ�
	case CEnumCore::Message_Tag_ID::PAL_ACCOUNT_OPEN_RESP://�������ʺ�	
	case CEnumCore::Message_Tag_ID::PAL_ACCOUNTLOCAL_QUERY_RESP://��ѯ���з�ͣ�ʺ�
	case CEnumCore::Message_Tag_ID::PAL_RELOADFUNCTIONSWITCH_RESP://����������ͣ�Ľ��//maple add
		{
			if(banPlayer.m_hWnd != NULL)
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//������ʺŽ��ͣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_ACCOUNT_BANISHMENT_QUERY_RESP://��ѯ�ʺ���û�б���ͣ
		{
			if(queryBanInfo.m_hWnd != NULL)
			{
				queryBanInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//����ѯ����ʺŷ�ͣ������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_GUILDBASEINFO_RESP://������Ϣ�Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_GUILDMEMBERLIST_RESP://�����б��Ӧ
		{
			if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus==operPAL.ReadIntValue("MPAL","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��������Ϣ���淢��Ϣ
			}
			else if((guildInfo.m_hWnd != NULL) && (guildInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				guildInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_DISMISSGUILD_RESP://��ɢ�����Ӧ
	case CEnumCore::Message_Tag_ID::PAL_MODIFYGUILDLV_RESP://���Ĺ���ȼ���Ӧ
	case CEnumCore::Message_Tag_ID::PAL_MODIFYGUILDNAME_RESP://���Ĺ������ƻ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_MODIFYGUILDMEMBERPL_RESP://���Ĺ����Աְ����Ӧ
	case CEnumCore::Message_Tag_ID::PAL_MODIFYGUILDNOTICE_RESP://�޸Ĺ��ṫ����Ӧ
		{
			if(guildmanage.m_hWnd != NULL)
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//�����������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_BOARDTASK_INSERT_RESP://���������Ӧ
	case CEnumCore::Message_Tag_ID::PAL_BOARDTASK_QUERY_RESP://�����ѯ��Ӧ
	case CEnumCore::Message_Tag_ID::PAL_BOARDTASK_UPDATE_RESP://���������Ӧ
		{
			if(noticeInfo.m_hWnd != NULL)
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��������Ϣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_MODIFYACCOUNTPW_RESP://�޸Ľ�ɫ��Ϸ����Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_RECALLACCOUNTPW_RESP://�ָ���ɫ��Ϸ����Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_MODIFYCHARACTERDROPPW_RESP://�޸Ľ�ɫɾ������Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_RECALLCHARACTERDROPPW_RESP://�ָ���ɫɾ������Ļ�Ӧ	
	case CEnumCore::Message_Tag_ID::PAL_MODIFYACCOUNTBANKPW_RESP://�޸Ľ�ɫ��������Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_RECALLACCOUNTBANKPW_RESP://�ָ���ɫ��������Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_MODIFYCHARACTERMONEY_RESP://�޸Ľ�ɫ��Ǯ�Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_MODIFYCHARACTERQUEST_RESP://�޸Ľ�ɫ����״̬�Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_MODIFYSECONDPW_RESP://�޸Ķ�������Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_RECALLSECONDPW_RESP://�ָ���������Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_USESAFELOCK_RESP://ʹ�ð�ȫ��
	case CEnumCore::Message_Tag_ID::PAL_FREESAFELOCK_RESP://�ͷŰ�ȫ����Ӧ
	case CEnumCore::Message_Tag_ID::PAL_MODIFYACCOUNTPWALL_RESP://�޸�ȫ��������ʱ����Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_RECALLACCOUNTPWALL_RESP://�ָ�ȫ��������ʱ����Ļ�Ӧ
		{
			if(roleManage.m_hWnd!=NULL)
			{
				roleManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_LOG_BIGTYPE_QUERY_RESP://��־������Ϣ
	case CEnumCore::Message_Tag_ID::PAL_LOG_SMALLTYPE_QUERY_RESP://��־С����Ϣ
		{
			if((logInfo.m_hWnd != NULL) && (logInfo.dlgStatus==operPAL.ReadIntValue("MPAL","Send")))
			{
				logInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//����־��Ϣ���淢��Ϣ
			}
			else if((hislogInfo.m_hWnd != NULL) && (hislogInfo.dlgStatus==operPAL.ReadIntValue("MPAL","Send")))
			{
				hislogInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//����־��Ϣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_LOGINFO_QUERY_RESP://��־��Ϣ
		{
			if(logInfo.m_hWnd!=NULL)
			{
				logInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//����־��Ϣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_HISTORY_LOGINFO_QUERY_RESP:
		{
			if(hislogInfo.m_hWnd!=NULL)
			{
				hislogInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//����־��Ϣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERBAG_RESP://��ɫ����
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
			else if((itemInfo.m_hWnd != NULL) && (itemInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				itemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��������Ϣ���淢��Ϣ
			}
			else if((itemManage.m_hWnd != NULL) && (itemManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//�����߹�����淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_DELCHARACTERITEM_RESP://ɾ����ɫ����
	case CEnumCore::Message_Tag_ID::PAL_SENDGIFTMAIL_RESP://���͵���
	case CEnumCore::Message_Tag_ID::PAL_ITEMTYPE_QUERY_RESP://��ѯ���������Ϣ�Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_ITEMNAME_QUERY_RESP://��ѯ����������Ϣ�Ļ�Ӧ
		{
			if(itemManage.m_hWnd!=NULL)
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//�����߹�����淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHECKMAILBOX_QUERY_RESP://���������Ϣ��ѯ
	case CEnumCore::Message_Tag_ID::PAL_CHECKMAILBOX_DETAIL_RESP://����ʼ�������ѯ
		{
			if(mailBoxInfo.m_hWnd!=NULL)
			{
				mailBoxInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//�����������Ϣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PALLOG_ACCOUNT_LOGIN_RESP://�ʺŵ���ǳ���־
		{
			if(accountLogin.m_hWnd!=NULL)
			{
				accountLogin.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���ʺŵ���ǳ���־���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PALLOG_ITEMMAIL_RESP://�̳ǹ����¼
	case CEnumCore::Message_Tag_ID::PAL_ITEMMAIL_WASTE_RESP://Ԫ�����ļ�¼
		{
			if(shopBuyLog.m_hWnd!=NULL)
			{
				shopBuyLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���̳ǹ����¼���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_AUCTION_QUERY_RESP://���������Ϣ
		{
			if(auctionInfo.m_hWnd!=NULL)
			{
				auctionInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//�����������Ϣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CDKEY_QUERY_RESP://CDKey������ȡ
		{
			if(CDKeyItemGet.m_hWnd!=NULL)
			{
				CDKeyItemGet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��CDKey������ȡ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_MAILBOX_QUERY_RESP://��ѯ�����ַ
	case CEnumCore::Message_Tag_ID::PAL_SendBankPwd_Query_RESP://���Ͳֿ�����
	case CEnumCore::Message_Tag_ID::PAL_SendDeletePwd_Query_RESP://���ͽ�ɫɾ������
		{
			if(sendUserPwd.m_hWnd!=NULL)
			{
				sendUserPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//������������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERMOB_RESP://��ħ��Ϣ
		{
			if((mobInfo.m_hWnd != NULL) && (mobInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				mobInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
			else if((mobManage.m_hWnd != NULL) && (mobManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				mobManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��������Ϣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_DELCHARACTERMOB_RESP://��ħ��Ϣ
		{
			if((mobManage.m_hWnd != NULL) && (mobManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				mobManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��������Ϣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERPUZZLEMAP_RESP://ͼ����Ϣ
		{
			if((puzzleMapInfo.m_hWnd != NULL) && (puzzleMapInfo.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				puzzleMapInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
			else if((puzzleMapManage.m_hWnd != NULL) && (puzzleMapManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				puzzleMapManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��������Ϣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_MODIFYPUZZLEMAP_RESP://ͼ����Ϣ
		{
			if((puzzleMapManage.m_hWnd != NULL) && (puzzleMapManage.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				puzzleMapManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��������Ϣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_MOVECHARACTERTOSAFE_RESP://��ȫ��
	case CEnumCore::Message_Tag_ID::PAL_SearchMap_Query_Resp:
		{
			if((moveToSafe.m_hWnd != NULL) && (moveToSafe.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				moveToSafe.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��������Ϣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_ROLEDEL_QUERY_RESP:
		{
			if((roleDel.m_hWnd != NULL) && (roleDel.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				roleDel.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��������Ϣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_EQUIPMENT_QUERY_RESP://װ����ѯ//PAL_EQUIPMENT_QUERY
		{
			if((sendCustomerItem.m_hWnd != NULL) && (sendCustomerItem.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				sendCustomerItem.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��������Ϣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_SENDCUSTOMITEMMAIL_RESP://���Ϳ�����Ʒ
		{
			if((sendCustomerItem.m_hWnd != NULL) && (sendCustomerItem.dlgStatus == operPAL.ReadIntValue("MPAL","Send")))
			{
				sendCustomerItem.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��������Ϣ���淢��Ϣ
			}
		}
	default:
		break;
	}
}

//ѡ��򿪲�ͬ���ӶԻ���
extern "C" __declspec(dllexport) bool PAL_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALUserInfo")))//ѡ���˲�ѯ�û���Ϣ(�ɽ�)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALKickPlayer")))//ѡ����ǿ�����(�ɽ�)����
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALBanPlayer")))//ѡ��������ʺŽ��ͣ(�ɽ�)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALNoticeInfo")))//ѡ���˹�����Ϣ(�ɽ�)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALGuildManage")))//ѡ���˹������(�ɽ�)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(guildmanage.m_hWnd == NULL)
		{
			guildmanage.Create(IDD_DLGGUILDMANAGE);
			guildmanage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(guildmanage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALRoleManage")))//ѡ���˽�ɫ����(�ɽ�)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALLogInfo")))//ѡ������־��Ϣ(�ɽ�)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALHisLogInfo")))//ѡ������־��Ϣ-��ʷ(�ɽ�)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(hislogInfo.m_hWnd == NULL)
		{
			hislogInfo.Create(IDD_DLGHISLOGINFO);
			hislogInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(hislogInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(hislogInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALItemInfo")))//ѡ���˵�����Ϣ(�ɽ�)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALItemManage")))//ѡ���˵��߹���(�ɽ�)
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALGuildInfo")))//ѡ���˹�����Ϣ(�ɽ�)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(guildInfo.m_hWnd == NULL)
		{
			guildInfo.Create(IDD_DLGGUILDINFO);
			guildInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(guildInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(guildInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMailBoxInfo")))//ѡ����������Ϣ(�ɽ�)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(mailBoxInfo.m_hWnd == NULL)
		{
			mailBoxInfo.Create(IDD_DLGMAILBOXINFO);
			mailBoxInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(mailBoxInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(mailBoxInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_UI_AccountLogin")))//ѡ�����ʺŵ�¼��Ϣ(�ɽ�)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(accountLogin.m_hWnd == NULL)
		{
			accountLogin.Create(IDD_DLGLOGINLOG);
			accountLogin.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(accountLogin.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(accountLogin.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALShopBuyLog")))//ѡ�����̳ǹ����¼(�ɽ�)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(shopBuyLog.m_hWnd == NULL)
		{
			shopBuyLog.Create(IDD_DLGSHOPBUYLOG);
			shopBuyLog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(shopBuyLog.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(shopBuyLog.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CQueryBanInfo")))//ѡ���˲�ѯ�ض�����ʺ���û�б���ͣ(�ɽ�)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(queryBanInfo.m_hWnd == NULL)
		{
			queryBanInfo.Create(IDD_DLGQUERYBAN);
			queryBanInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(queryBanInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(queryBanInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALAuctionInfo")))//ѡ���˲�ѯ���������¼(�ɽ�)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(auctionInfo.m_hWnd == NULL)
		{
			auctionInfo.Create(IDD_DLGAUCTIONINFO);
			auctionInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(auctionInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(auctionInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALCDKeyItemGet")))//ѡ����CDKEY������ȡ��ѯ(�ɽ�)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(CDKeyItemGet.m_hWnd == NULL)
		{
			CDKeyItemGet.Create(IDD_DLGCDKEYITEMGET);
			CDKeyItemGet.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(CDKeyItemGet.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(CDKeyItemGet.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmPalSendDelRolePass")))//ѡ���˷�������(�ɽ�)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(sendUserPwd.m_hWnd == NULL)
		{
			sendUserPwd.Create(IDD_DLGSENDPWD);
			sendUserPwd.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(sendUserPwd.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(sendUserPwd.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMobInfo")))//��ɫ��ħ��Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(mobInfo.m_hWnd == NULL)
		{
			mobInfo.Create(IDD_DLGMOBINFO);
			mobInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(mobInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(mobInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMobManage")))//��ɫ��ħ����
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(mobManage.m_hWnd == NULL)
		{
			mobManage.Create(IDD_DLGMOBMANAGE);
			mobManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(mobManage.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(mobManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALPuzzleMapInfo")))//��ɫͼ����Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(puzzleMapInfo.m_hWnd == NULL)
		{
			puzzleMapInfo.Create(IDD_DLGPUZZLEMAPINFO);
			puzzleMapInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(puzzleMapInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(puzzleMapInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALPuzzleMapManage")))//��ɫͼ������
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(puzzleMapManage.m_hWnd == NULL)
		{
			puzzleMapManage.Create(IDD_DLGPUZZLEMAPMANAGE);
			puzzleMapManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(puzzleMapManage.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(puzzleMapManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMoveToSafe")))//�ƶ���ɫ����ȫ��
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(moveToSafe.m_hWnd == NULL)
		{
			moveToSafe.Create(IDD_DLGMOVETOSAFE);
			moveToSafe.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(moveToSafe.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(moveToSafe.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALRoleDel")))//�ƶ���ɫ����ȫ��
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(roleDel.m_hWnd == NULL)
		{
			roleDel.Create(IDD_DLGROLEDEL);
			roleDel.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(roleDel.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(roleDel.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALCharacterInfo")))//��ɫ��Ϣ�����ƣ�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(characterInfo.m_hWnd == NULL)
		{
			characterInfo.Create(IDD_DLGCHARACTERINFO);
			characterInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(characterInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(characterInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALSendCustomerItem")))//���Ϳ�����Ʒ(�ɽ�)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(sendCustomerItem.m_hWnd == NULL)
		{
			sendCustomerItem.Create(IDD_DLGSENDCUSTOMERITEM);
			sendCustomerItem.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(sendCustomerItem.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(sendCustomerItem.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALUserInfoOnly")))//�û���Ϣ��ѯ��ֻ�������ɽ���
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(userInfoOnly.m_hWnd == NULL)
		{
			userInfoOnly.Create(IDD_DLGUSERINFO);
			userInfoOnly.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(userInfoOnly.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(userInfoOnly.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}

	return false;
}

//ѡ����ʾ��ͬ���ӶԻ���
extern "C" __declspec(dllexport) BOOL PAL_SHOWDIALOG(CString m_MenuName)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALUserInfo")))//ѡ���˲�ѯ�û���Ϣ(�ɽ�)
	{		
		if(userInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}		
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALKickPlayer")))//ѡ����ǿ�����(�ɽ�)����
	{
		if(kickPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(kickPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALBanPlayer")))//ѡ��������ʺŽ��ͣ(�ɽ�)
	{
		if(banPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(banPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALNoticeInfo")))//ѡ���˹�����Ϣ(�ɽ�)
	{
		if(noticeInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(noticeInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALGuildManage")))//ѡ���˹������(�ɽ�)
	{
		if(guildmanage.m_hWnd!=NULL)
		{
			::SetWindowPos(guildmanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALRoleManage")))//ѡ���˽�ɫ����(�ɽ�)
	{
		if(roleManage.m_hWnd!=NULL)
		{
			::SetWindowPos(roleManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALLogInfo")))//ѡ������־��Ϣ(�ɽ�)
	{
		if(logInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(logInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALHisLogInfo")))//ѡ������־��Ϣ-��ʷ(�ɽ�)
	{
		if(hislogInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(hislogInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALItemInfo")))//ѡ���˵�����Ϣ(�ɽ�)
	{
		if(itemInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(itemInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}		
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALItemManage")))//ѡ���˵��߹���(�ɽ�)
	{
		if(itemManage.m_hWnd!=NULL)
		{
			::SetWindowPos(itemManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALGuildInfo")))//ѡ���˹�����Ϣ(�ɽ�)
	{
		if(guildInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(guildInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}		
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMailBoxInfo")))//ѡ����������Ϣ(�ɽ�)
	{
		if(mailBoxInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(mailBoxInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_UI_AccountLogin")))//ѡ�����ʺŵ�¼��Ϣ(�ɽ�)
	{
		if(accountLogin.m_hWnd!=NULL)
		{
			::SetWindowPos(accountLogin.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}		
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALShopBuyLog")))//ѡ�����̳ǹ����¼(�ɽ�)
	{
		if(shopBuyLog.m_hWnd!=NULL)
		{
			::SetWindowPos(shopBuyLog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CQueryBanInfo")))//ѡ���˲�ѯ�ض�����ʺ���û�б���ͣ(�ɽ�)
	{
		if(queryBanInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(queryBanInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALAuctionInfo")))//ѡ���˲�ѯ���������¼(�ɽ�)
	{
		if(auctionInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(auctionInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALCDKeyItemGet")))//ѡ����CDKEY������ȡ��ѯ(�ɽ�)
	{
		if(CDKeyItemGet.m_hWnd!=NULL)
		{
			::SetWindowPos(CDKeyItemGet.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmPalSendDelRolePass")))//ѡ���˷�������(�ɽ�)
	{
		if(sendUserPwd.m_hWnd!=NULL)
		{
			::SetWindowPos(sendUserPwd.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMobInfo")))//ѡ���˷�������(�ɽ�)
	{
		if(mobInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(mobInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMobManage")))//ѡ���˷�������(�ɽ�)
	{
		if(mobManage.m_hWnd!=NULL)
		{
			::SetWindowPos(mobManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALPuzzleMapInfo")))//ѡ���˷�������(�ɽ�)
	{
		if(puzzleMapInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(puzzleMapInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALPuzzleMapManage")))//ѡ���˷�������(�ɽ�)
	{
		if(puzzleMapManage.m_hWnd!=NULL)
		{
			::SetWindowPos(puzzleMapManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMoveToSafe")))//ѡ���˷�������(�ɽ�)
	{
		if(moveToSafe.m_hWnd!=NULL)
		{
			::SetWindowPos(moveToSafe.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALRoleDel")))//ѡ���˷�������(�ɽ�)
	{
		if(roleDel.m_hWnd!=NULL)
		{
			::SetWindowPos(roleDel.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALCharacterInfo")))//��ɫ��Ϣ�����ƣ�
	{
		if(characterInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(characterInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALSendCustomerItem")))//���Ϳ�����Ʒ
	{
		if(sendCustomerItem.m_hWnd!=NULL)
		{
			::SetWindowPos(sendCustomerItem.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALUserInfoOnly")))//�û���Ϣ��ѯ��ֻ�������ɽ���
	{		
		if(userInfoOnly.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfoOnly.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}		
	}
	return FALSE;
}

//ѡ�����ͬ���ӶԻ�����Ϣ
extern "C" __declspec(dllexport) void PAL_DIALOGMSG(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam)
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
		if(guildmanage.m_hWnd != NULL)
		{
			::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//���о��������
		    ::SendMessage(guildmanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(roleManage.m_hWnd != NULL)
		{
			::SetParent(roleManage.m_hWnd,theApp.mHwndParent);//���о��������
		    ::SendMessage(roleManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(logInfo.m_hWnd != NULL)
		{
			::SetParent(logInfo.m_hWnd,theApp.mHwndParent);//���о��������
		    ::SendMessage(logInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(hislogInfo.m_hWnd!=NULL)
		{
			::SetParent(hislogInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(hislogInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
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
		if(guildInfo.m_hWnd != NULL)
		{
			::SetParent(guildInfo.m_hWnd,theApp.mHwndParent);//���о��������
		    ::SendMessage(guildInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(mailBoxInfo.m_hWnd != NULL)
		{
			::SetParent(mailBoxInfo.m_hWnd,theApp.mHwndParent);//���о��������
		    ::SendMessage(mailBoxInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(accountLogin.m_hWnd != NULL)
		{
			::SetParent(accountLogin.m_hWnd,theApp.mHwndParent);//���о��������
		    ::SendMessage(accountLogin.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(shopBuyLog.m_hWnd != NULL)
		{
			::SetParent(shopBuyLog.m_hWnd,theApp.mHwndParent);//���о��������
		    ::SendMessage(shopBuyLog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(queryBanInfo.m_hWnd != NULL)
		{
			::SetParent(queryBanInfo.m_hWnd,theApp.mHwndParent);//���о��������
		    ::SendMessage(queryBanInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(auctionInfo.m_hWnd != NULL)
		{
			::SetParent(auctionInfo.m_hWnd,theApp.mHwndParent);//���о��������
		    ::SendMessage(auctionInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(CDKeyItemGet.m_hWnd != NULL)
		{
			::SetParent(CDKeyItemGet.m_hWnd,theApp.mHwndParent);//���о��������
		    ::SendMessage(CDKeyItemGet.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(sendUserPwd.m_hWnd != NULL)
		{
			::SetParent(sendUserPwd.m_hWnd,theApp.mHwndParent);//���о��������
		    ::SendMessage(sendUserPwd.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}

		if(mobInfo.m_hWnd != NULL)
		{
			::SetParent(mobInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mobInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(mobManage.m_hWnd != NULL)
		{
			::SetParent(mobManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mobManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(puzzleMapInfo.m_hWnd != NULL)
		{
			::SetParent(puzzleMapInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(puzzleMapInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(puzzleMapManage.m_hWnd != NULL)
		{
			::SetParent(puzzleMapManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(puzzleMapManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}

		if(moveToSafe.m_hWnd != NULL)
		{
			::SetParent(moveToSafe.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(moveToSafe.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}

		if(roleDel.m_hWnd != NULL)
		{
			::SetParent(roleDel.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(roleDel.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(characterInfo.m_hWnd != NULL)
		{
			::SetParent(characterInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(characterInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(sendCustomerItem.m_hWnd != NULL)
		{
			::SetParent(sendCustomerItem.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(sendCustomerItem.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(userInfoOnly.m_hWnd != NULL)
		{
			::SetParent(userInfoOnly.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userInfoOnly.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALUserInfo")))//ѡ���˲�ѯ�û���Ϣ(�ɽ�)
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALKickPlayer")))//ѡ����ǿ�����(�ɽ�)����
	{
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALBanPlayer")))//ѡ��������ʺŽ��ͣ(�ɽ�)
	{
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALNoticeInfo")))//ѡ���˹�����Ϣ(�ɽ�)
	{
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALGuildManage")))//ѡ���˹������(�ɽ�)
	{
		if(guildmanage.m_hWnd != NULL)
		{
			::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildmanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALRoleManage")))//ѡ���˽�ɫ����(�ɽ�)
	{
		if(roleManage.m_hWnd != NULL)
		{
			::SetParent(roleManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(roleManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALLogInfo")))//ѡ������־��Ϣ(�ɽ�)
	{
		if(logInfo.m_hWnd != NULL)
		{
			::SetParent(logInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(logInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALItemInfo")))//ѡ���˵�����Ϣ(�ɽ�)
	{
		if(itemInfo.m_hWnd != NULL)
		{
			::SetParent(itemInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALItemManage")))//ѡ���˵��߹���(�ɽ�)
	{
		if(itemManage.m_hWnd != NULL)
		{
			::SetParent(itemManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALGuildInfo")))//ѡ���˹�����Ϣ(�ɽ�)
	{
		if(guildInfo.m_hWnd != NULL)
		{
			::SetParent(guildInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMailBoxInfo")))//ѡ����������Ϣ(�ɽ�)
	{
		if(mailBoxInfo.m_hWnd != NULL)
		{
			::SetParent(mailBoxInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mailBoxInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_UI_AccountLogin")))//ѡ�����ʺŵ�¼��Ϣ(�ɽ�)
	{
		if(accountLogin.m_hWnd != NULL)
		{
			::SetParent(accountLogin.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(accountLogin.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALShopBuyLog")))//ѡ�����̳ǹ����¼(�ɽ�)
	{
		if(shopBuyLog.m_hWnd != NULL)
		{
			::SetParent(shopBuyLog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(shopBuyLog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CQueryBanInfo")))//ѡ���˲�ѯ�ض�����ʺ���û�б���ͣ(�ɽ�)
	{
		if(queryBanInfo.m_hWnd != NULL)
		{
			::SetParent(queryBanInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(queryBanInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALAuctionInfo")))//ѡ���˲�ѯ���������¼(�ɽ�)
	{
		if(auctionInfo.m_hWnd != NULL)
		{
			::SetParent(auctionInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(auctionInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALCDKeyItemGet")))//ѡ����CDKEY������ȡ��ѯ(�ɽ�)
	{
		if(CDKeyItemGet.m_hWnd != NULL)
		{
			::SetParent(CDKeyItemGet.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(CDKeyItemGet.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmPalSendDelRolePass")))//ѡ���˷�������(�ɽ�)
	{
		if(sendUserPwd.m_hWnd != NULL)
		{
			::SetParent(sendUserPwd.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(sendUserPwd.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALHisLogInfo")))//ѡ���˷�������(�ɽ�)
	{
		if(hislogInfo.m_hWnd != NULL)
		{
			::SetParent(hislogInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(hislogInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMobInfo")))//ѡ���˷�������(�ɽ�)
	{
		if(mobInfo.m_hWnd != NULL)
		{
			::SetParent(mobInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mobInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMobManage")))//ѡ���˷�������(�ɽ�)
	{
		if(mobManage.m_hWnd != NULL)
		{
			::SetParent(mobManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mobManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALPuzzleMapInfo")))//ѡ���˷�������(�ɽ�)
	{
		if(puzzleMapInfo.m_hWnd != NULL)
		{
			::SetParent(puzzleMapInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(puzzleMapInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALPuzzleMapManage")))//ѡ���˷�������(�ɽ�)
	{
		if(puzzleMapManage.m_hWnd != NULL)
		{
			::SetParent(puzzleMapManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(puzzleMapManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALMoveToSafe")))//ѡ���˷�������(�ɽ�)
	{
		if(moveToSafe.m_hWnd != NULL)
		{
			::SetParent(moveToSafe.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(moveToSafe.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALRoleDel")))//ѡ���˷�������(�ɽ�)
	{
		if(roleDel.m_hWnd != NULL)
		{
			::SetParent(roleDel.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(roleDel.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALCharacterInfo")))//��ɫ��Ϣ�����ƣ�
	{
		if(characterInfo.m_hWnd != NULL)
		{
			::SetParent(characterInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(characterInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALSendCustomerItem")))//���Ϳ�����Ʒ
	{
		if(sendCustomerItem.m_hWnd != NULL)
		{
			::SetParent(sendCustomerItem.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(sendCustomerItem.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CPALUserInfoOnly")))//ѡ���˲�ѯ�û���Ϣ(�ɽ�)
	{
		if(userInfoOnly.m_hWnd != NULL)
		{
			::SetParent(userInfoOnly.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userInfoOnly.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
}

//�ٴη���ͬ����Query
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