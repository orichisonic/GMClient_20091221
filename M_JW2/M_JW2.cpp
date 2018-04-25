// M_JW2.cpp : ���� DLL �ĳ�ʼ�����̡�
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

// CM_JW2App

BEGIN_MESSAGE_MAP(CM_JW2App, CWinApp)
END_MESSAGE_MAP()


// CM_JW2App ����

CM_JW2App::CM_JW2App()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CM_JW2App ����

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

// CM_JW2App ��ʼ��

BOOL CM_JW2App::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
extern "C" __declspec(dllexport) BOOL JW2_TRANSLATEMESSAGE(MSG* pMsg)
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
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��������Ϣ
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
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_QUERY_RESP://�û����ϲ�ѯ
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
	case CEnumCore::Message_Tag_ID::JW2_RPG_QUERY_RESP://���������Ϣ
	case CEnumCore::Message_Tag_ID::JW2_ITEMSHOP_BYOWNER_QUERY_RESP://��ҵ�����Ϣ
	case CEnumCore::Message_Tag_ID::JW2_SMALL_PRESENT_QUERY_RESP://����������Ϣ
	case CEnumCore::Message_Tag_ID::JW2_WASTE_ITEM_QUERY_RESP://�����Ե���
	case CEnumCore::Message_Tag_ID::JW2_SMALL_BUGLE_QUERY_RESP://С������Ϣ	
	case CEnumCore::Message_Tag_ID::JW2_User_Family_Query_Resp:
		{
			if((userInfo.m_hWnd != NULL) &&(userInfo.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_HOME_ITEM_QUERY_RESP://������Ʒ�嵥������
		{
			if((userInfo.m_hWnd != NULL) &&(userInfo.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
			else if((houseInfo.m_hWnd != NULL) &&(houseInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				houseInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_BANISHPLAYER_RESP://ǿ���������
		{
			if((kickPlayer.m_hWnd != NULL) &&(kickPlayer.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_CLOSE_RESP://��ͣ����ʺ�
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_OPEN_RESP://�������ʺ�
		{
			if((banPlayer.m_hWnd != NULL) &&(banPlayer.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_BANISHMENT_QUERY_RESP://��ѯ�ʺ���û�б���ͣ
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNTREMOTE_QUERY_RESP://��ѯ���з�ͣ�ʺ�
		{
			if((banPlayer.m_hWnd != NULL) &&(banPlayer.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
			else if((banList.m_hWnd != NULL) &&(banList.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				banList.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_BOARDTASK_QUERY_RESP://��ѯ���й�����Ϣ
	case CEnumCore::Message_Tag_ID::JW2_BOARDTASK_INSERT_RESP://��ӹ�����Ϣ
	case CEnumCore::Message_Tag_ID::JW2_BOARDTASK_UPDATE_RESP://�༭������Ϣ
		{
			if((noticeInfo.m_hWnd != NULL) &&(noticeInfo.dlgStatus == operJW2.ReadIntValue("MJW2","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_WEDDINGINFO_QUERY_RESP:
	case CEnumCore::Message_Tag_ID::JW2_WEDDINGLOG_QUERY_RESP:
		{
			if((weddingInfo.m_hWnd != NULL) &&(weddingInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				weddingInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_COUPLEINFO_QUERY_RESP:
	case CEnumCore::Message_Tag_ID::JW2_COUPLELOG_QUERY_RESP:
		{
			if((coupleInfo.m_hWnd != NULL) &&(coupleInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				coupleInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_FAMILYINFO_QUERY_RESP://���������Ϣ
		{
			if((familyInfo.m_hWnd != NULL) &&(familyInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
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
				familyInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
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
				loginInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
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
				userManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ItemInfo_Query_Resp:
	case CEnumCore::Message_Tag_ID::JW2_ITEM_DEL_RESP:
	case CEnumCore::Message_Tag_ID::JW2_ADD_ITEM_RESP:
	case CEnumCore::Message_Tag_ID::JW2_MODIFY_MONEY_RESP:
	///maple add
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Validate_Resp://��֤Ȩ��
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Deduct_Resp://��֤ͨ����Ȩ�ޱ��м�ȥ
		{
			if((itemManage.m_hWnd != NULL) &&(itemManage.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ITEM_SELECT_RESP:
		{
			if((itemManage.m_hWnd != NULL) &&(itemManage.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				itemManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
			else if((productManage.m_hWnd != NULL) &&(productManage.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				productManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}	
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_PetInfo_Query_Resp:
		{
			if((petInfo.m_hWnd != NULL) &&(petInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_MailInfo_Query_Resp:
		{
			if((mailInfo.m_hWnd != NULL) &&(mailInfo.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				mailInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_Messenger_Query_Resp:
		{
			if((messenger.m_hWnd != NULL) &&(messenger.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				messenger.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_FamilyFund_Log_Resp:
		{
			if((familyFundLog.m_hWnd != NULL) &&(familyFundLog.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyFundLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;

	case CEnumCore::Message_Tag_ID::JW2_Wedding_Paper_Resp:
		{
			if((weddingPaper.m_hWnd != NULL) &&(weddingPaper.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				weddingPaper.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_CoupleParty_Card_Resp:
		{
			if((coupleCard.m_hWnd != NULL) &&(coupleCard.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				coupleCard.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_Item_Log_Resp:
		{
			if((itemLog.m_hWnd != NULL) &&(itemLog.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				itemLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_FamilyBuyLog_Query_Resp:
		{
			if((familyBuyLog.m_hWnd != NULL) &&(familyBuyLog.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				familyBuyLog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_MoneyLog_Query_Resp:
	case CEnumCore::Message_Tag_ID::JW2_CashMoney_Log_Resp:
		{
			if((gMoney.m_hWnd != NULL) &&(gMoney.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				gMoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
			else if((mMoney.m_hWnd != NULL) &&(mMoney.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				mMoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_Import_KickPlayer_Resp:
	case CEnumCore::Message_Tag_ID::JW2_Import_AccountClose_Resp:
	case CEnumCore::Message_Tag_ID::JW2_Import_AccountOpen_Resp:
		{
			if((Import.m_hWnd != NULL) &&(Import.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				Import.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_GM_Update_Resp:
		{
			if((gmUpdate.m_hWnd != NULL) &&(gmUpdate.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				gmUpdate.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_QUERY_ALL_RESP:
	//maple add
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Insert_Resp://����Ȩ��
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Del_Resp://ɾ��Ȩ��
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_View_Resp://�鿴Ȩ��
	////case CEnumCore::Message_Tag_ID::JW2_ProductManage_Validate_Resp://��֤Ȩ��
		{
			if((productManage.m_hWnd != NULL) &&(productManage.dlgStatus==operJW2.ReadIntValue("MJW2","Send")))
			{
				productManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//���û�������淢��Ϣ
			}	
		}
		break;
	default:
		break;
	}
}
//ѡ��򿪲�ͬ���ӶԻ���
extern "C" __declspec(dllexport) void JW2_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserInfo")))//ѡ���˲�ѯ�û���Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(userInfo.m_hWnd == NULL)
		{
			userInfo.Create(IDD_DLGUSERINFO);
			userInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(userInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2KickPlayer")))//ѡ����ǿ���������
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(kickPlayer.m_hWnd == NULL)
		{
			kickPlayer.Create(IDD_DLGKICKPLAYER);
			kickPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(kickPlayer.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2BanPlayer")))//ѡ��������ʺŽ��ͣ(�ɽ�)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(banPlayer.m_hWnd == NULL)
		{
			banPlayer.Create(IDD_DLGBANPLAYER);
			banPlayer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(banPlayer.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2NoticeInfo")))//ѡ���˹�����Ϣ(�ɽ�)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(noticeInfo.m_hWnd == NULL)
		{
			noticeInfo.Create(IDD_DLGNOTICE);
			noticeInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(noticeInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2WeddingInfo")))//ѡ���˻�����Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(weddingInfo.m_hWnd == NULL)
		{
			weddingInfo.Create(IDD_DLGWEDDINGINFO);
			weddingInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(weddingInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(weddingInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2CoupleInfo")))//ѡ����������Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(coupleInfo.m_hWnd == NULL)
		{
			coupleInfo.Create(IDD_DLGCOUPLEINFO);
			coupleInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(coupleInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(coupleInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyInfo")))//ѡ���˼�����Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(familyInfo.m_hWnd == NULL)
		{
			familyInfo.Create(IDD_DLGFAMILYINFO);
			familyInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(familyInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2LoginInfo")))//ѡ������ҵ���/�ǳ���Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(loginInfo.m_hWnd == NULL)
		{
			loginInfo.Create(IDD_DLGLOGININFO);
			loginInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(loginInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserManage")))//���û�������淢��Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(userManage.m_hWnd == NULL)
		{
			userManage.Create(IDD_DLGUSERMANAGE);
			userManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(userManage.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(userManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyItemInfo")))//���������Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(familyItemInfo.m_hWnd == NULL)
		{
			familyItemInfo.Create(IDD_DLGFAMILYITEMINFO);
			familyItemInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyItemInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(familyItemInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyBuyLog")))//���幺����־��Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(familyBuyLog.m_hWnd == NULL)
		{
			familyBuyLog.Create(IDD_DLGFAMILYBUYLOG);
			familyBuyLog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyBuyLog.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(familyBuyLog.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyTransfer")))//����ת����Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(familyTransfer.m_hWnd == NULL)
		{
			familyTransfer.Create(IDD_DLGFAMILYTRANSFER);
			familyTransfer.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyTransfer.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(familyTransfer.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ItemManage")))//���߹���
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(itemManage.m_hWnd == NULL)
		{
			itemManage.Create(IDD_DLGITEMMANAGE);
			itemManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemManage.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(itemManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserInfoPart")))//���߹���
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(userInfoPart.m_hWnd == NULL)
		{
			userInfoPart.Create(IDD_DLGUSERINFOPART);
			userInfoPart.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(userInfoPart.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(userInfoPart.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2BanList")))//��ͣ�б�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(banList.m_hWnd == NULL)
		{
			banList.Create(IDD_DLGBANLIST);
			banList.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(banList.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(banList.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2MailInfo")))//�ʼ���Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(mailInfo.m_hWnd == NULL)
		{
			mailInfo.Create(IDD_DLGMAILINFO);
			mailInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(mailInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(mailInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2PetInfo")))//������Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(petInfo.m_hWnd == NULL)
		{
			petInfo.Create(IDD_DLGPETINFO);
			petInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(petInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2Messenger")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(messenger.m_hWnd == NULL)
		{
			messenger.Create(IDD_DLGMESSENGER);
			messenger.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(messenger.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(messenger.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyFundLog")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(familyFundLog.m_hWnd == NULL)
		{
			familyFundLog.Create(IDD_DLGFAMILYFUNDLOG);
			familyFundLog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(familyFundLog.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(familyFundLog.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2WeddingPaper")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(weddingPaper.m_hWnd == NULL)
		{
			weddingPaper.Create(IDD_DLGWEDDINGPAPER);
			weddingPaper.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(weddingPaper.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(weddingPaper.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ItemLog")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(itemLog.m_hWnd == NULL)
		{
			itemLog.Create(IDD_DLGITEMLOG);
			itemLog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemLog.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(itemLog.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2CoupleCard")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(coupleCard.m_hWnd == NULL)
		{
			coupleCard.Create(IDD_DLGCOUPLECARD);
			coupleCard.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(coupleCard.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(coupleCard.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2HouseInfo")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(houseInfo.m_hWnd == NULL)
		{
			houseInfo.Create(IDD_DLGHOUSEINFO);
			houseInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(houseInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(houseInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2MMoney")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(mMoney.m_hWnd == NULL)
		{
			mMoney.Create(IDD_DLGMMONEY);
			mMoney.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(mMoney.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(mMoney.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2GMoney")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(gMoney.m_hWnd == NULL)
		{
			gMoney.Create(IDD_DLGGMONEY);
			gMoney.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(gMoney.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(gMoney.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2Import")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(Import.m_hWnd == NULL)
		{
			Import.Create(IDD_DLGIMPORT);
			Import.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(Import.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(Import.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2GMUpdate")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(gmUpdate.m_hWnd == NULL)
		{
			gmUpdate.Create(IDD_DLGGMUPDATE);
			gmUpdate.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(gmUpdate.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(gmUpdate.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ProductManage")))//Messenger
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if(productManage.m_hWnd == NULL)
		{
			productManage.Create(IDD_DLGPRODUCTMANAGE);
			productManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(productManage.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(productManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
	}
}

//ѡ����ʾ��ͬ���ӶԻ���
extern "C" __declspec(dllexport) BOOL JW2_SHOWDIALOG(CString m_MenuName)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserInfo")))//ѡ���˲�ѯ�û���Ϣ
	{
		if(userInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2KickPalyer")))//ѡ����ǿ���������
	{
		if(kickPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(kickPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2BanPlayer")))//ѡ��������ʺŽ��ͣ
	{
		if(banPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(banPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2NoticeInfo")))//ѡ���˹�����Ϣ
	{
		if(noticeInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(noticeInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2WeddingInfo")))//ѡ���˻�����Ϣ
	{
		if(weddingInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(weddingInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2CoupleInfo")))//ѡ����������Ϣ
	{
		if(coupleInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(coupleInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyInfo")))//ѡ���˼�����Ϣ
	{
		if(familyInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(familyInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2LoginInfo")))//ѡ������ҵ���/�ǳ���Ϣ
	{
		if(loginInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(loginInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserManage")))//���û�������淢��Ϣ
	{
		if(userManage.m_hWnd!=NULL)
		{
			::SetWindowPos(userManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyItemInfo")))//���������Ϣ
	{
		if(familyItemInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(familyItemInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyBuyLog")))//���幺����־��Ϣ
	{
		if(familyBuyLog.m_hWnd!=NULL)
		{
			::SetWindowPos(familyBuyLog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyTransfer")))//����ת����Ϣ
	{
		if(familyTransfer.m_hWnd!=NULL)
		{
			::SetWindowPos(familyTransfer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ItemManage")))//���߹���
	{
		if(itemManage.m_hWnd!=NULL)
		{
			::SetWindowPos(itemManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserInfoPart")))//���߹���
	{
		if(userInfoPart.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfoPart.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2BanList")))//���߹���
	{
		if(banList.m_hWnd!=NULL)
		{
			::SetWindowPos(banList.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2PetInfo")))//���߹���
	{
		if(petInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(petInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2MailInfo")))//���߹���
	{
		if(mailInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(mailInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2Messenger")))//���߹���
	{
		if(messenger.m_hWnd!=NULL)
		{
			::SetWindowPos(messenger.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyFundLog")))//���߹���
	{
		if(familyFundLog.m_hWnd!=NULL)
		{
			::SetWindowPos(familyFundLog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2WeddingPaper")))//���߹���
	{
		if(weddingPaper.m_hWnd!=NULL)
		{
			::SetWindowPos(weddingPaper.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ItemLog")))//���߹���
	{
		if(itemLog.m_hWnd!=NULL)
		{
			::SetWindowPos(itemLog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2CoupleCard")))//���߹���
	{
		if(coupleCard.m_hWnd!=NULL)
		{
			::SetWindowPos(coupleCard.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2HouseInfo")))//���߹���
	{
		if(houseInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(houseInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2MMoney")))//���߹���
	{
		if(mMoney.m_hWnd!=NULL)
		{
			::SetWindowPos(mMoney.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2Import")))//���߹���
	{
		if(Import.m_hWnd!=NULL)
		{
			::SetWindowPos(Import.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2GMUpdate")))//���߹���
	{
		if(gmUpdate.m_hWnd!=NULL)
		{
			::SetWindowPos(gmUpdate.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ProductManage")))//����Ȩ��
	{
		if(productManage.m_hWnd!=NULL)
		{
			::SetWindowPos(productManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}

	return FALSE;
}
//ѡ�����ͬ���ӶԻ�������Ϣ
extern "C" __declspec(dllexport) void JW2_DIALOGMSG(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam)
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
		if(weddingInfo.m_hWnd != NULL)
		{
			::SetParent(weddingInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(weddingInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(coupleInfo.m_hWnd != NULL)
		{
			::SetParent(coupleInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(coupleInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(familyInfo.m_hWnd != NULL)
		{
			::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(loginInfo.m_hWnd != NULL)
		{
			::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(loginInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(userManage.m_hWnd != NULL)
		{
			::SetParent(userManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(familyBuyLog.m_hWnd != NULL)
		{
			::SetParent(familyBuyLog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyBuyLog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(familyTransfer.m_hWnd != NULL)
		{
			::SetParent(familyTransfer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyTransfer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(familyItemInfo.m_hWnd != NULL)
		{
			::SetParent(familyItemInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyItemInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(itemManage.m_hWnd != NULL)
		{
			::SetParent(itemManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(userInfoPart.m_hWnd != NULL)
		{
			::SetParent(userInfoPart.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userInfoPart.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(banList.m_hWnd != NULL)
		{
			::SetParent(banList.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banList.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(messenger.m_hWnd != NULL)
		{
			::SetParent(messenger.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(messenger.m_hWnd, Msg, wParam, lParam);//������Ϣ
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
		if(familyFundLog.m_hWnd != NULL)
		{
			::SetParent(familyFundLog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyFundLog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(weddingPaper.m_hWnd != NULL)
		{
			::SetParent(weddingPaper.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(weddingPaper.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(itemLog.m_hWnd != NULL)
		{
			::SetParent(itemLog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemLog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(coupleCard.m_hWnd != NULL)
		{
			::SetParent(coupleCard.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(coupleCard.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(houseInfo.m_hWnd != NULL)
		{
			::SetParent(houseInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(houseInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(mMoney.m_hWnd != NULL)
		{
			::SetParent(mMoney.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mMoney.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(gMoney.m_hWnd != NULL)
		{
			::SetParent(gMoney.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(gMoney.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(Import.m_hWnd != NULL)
		{
			::SetParent(Import.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(Import.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(gmUpdate.m_hWnd != NULL)
		{
			::SetParent(gmUpdate.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(gmUpdate.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(productManage.m_hWnd != NULL)
		{
			::SetParent(productManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(productManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserInfo")))//ѡ���˲�ѯ�û���Ϣ
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2KickPlayer")))//ѡ����ǿ���������
	{
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2BanPlayer")))//��ҽ�ɫ��Ϣ���������ߣ�
	{
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2NoticeInfo")))//��ҽ�ɫ��Ϣ���������ߣ�
	{
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2WeddingInfo")))//ѡ���˻�����Ϣ
	{
		if(weddingInfo.m_hWnd != NULL)
		{
			::SetParent(weddingInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(weddingInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2CoupleInfo")))//ѡ����������Ϣ
	{
		if(coupleInfo.m_hWnd != NULL)
		{
			::SetParent(coupleInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(coupleInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyInfo")))//ѡ���˼�����Ϣ
	{
		if(familyInfo.m_hWnd != NULL)
		{
			::SetParent(familyInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2LoginInfo")))//ѡ���˼�����Ϣ
	{
		if(loginInfo.m_hWnd != NULL)
		{
			::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(loginInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserManage")))//ѡ���˼�����Ϣ
	{
		if(userManage.m_hWnd != NULL)
		{
			::SetParent(userManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyItemInfo")))//ѡ���˼�����Ϣ
	{
		if(familyItemInfo.m_hWnd != NULL)
		{
			::SetParent(familyItemInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyItemInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyBuyLog")))//ѡ���˼�����Ϣ
	{
		if(familyBuyLog.m_hWnd != NULL)
		{
			::SetParent(familyBuyLog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyBuyLog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyTransfer")))//ѡ���˼�����Ϣ
	{
		if(familyTransfer.m_hWnd != NULL)
		{
			::SetParent(familyTransfer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyTransfer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ItemManage")))//ѡ���˼�����Ϣ
	{
		if(itemManage.m_hWnd != NULL)
		{
			::SetParent(itemManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2UserInfoPart")))//ѡ���˼�����Ϣ
	{
		if(userInfoPart.m_hWnd != NULL)
		{
			::SetParent(userInfoPart.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userInfoPart.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2BanList")))//ѡ���˼�����Ϣ
	{
		if(banList.m_hWnd != NULL)
		{
			::SetParent(banList.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banList.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2PetInfo")))//ѡ���˼�����Ϣ
	{
		if(petInfo.m_hWnd != NULL)
		{
			::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2MailInfo")))//ѡ���˼�����Ϣ
	{
		if(mailInfo.m_hWnd != NULL)
		{
			::SetParent(mailInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mailInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2Messenger")))//ѡ���˼�����Ϣ
	{
		if(messenger.m_hWnd != NULL)
		{
			::SetParent(messenger.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(messenger.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2FamilyFundLog")))//ѡ���˼�����Ϣ
	{
		if(familyFundLog.m_hWnd != NULL)
		{
			::SetParent(familyFundLog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(familyFundLog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2WeddingPaper")))//ѡ���˼�����Ϣ
	{
		if(weddingPaper.m_hWnd != NULL)
		{
			::SetParent(weddingPaper.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(weddingPaper.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2CoupleCard")))//ѡ���˼�����Ϣ
	{
		if(coupleCard.m_hWnd != NULL)
		{
			::SetParent(coupleCard.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(coupleCard.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2HouseInfo")))//ѡ���˼�����Ϣ
	{
		if(houseInfo.m_hWnd != NULL)
		{
			::SetParent(houseInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(houseInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ItemLog")))//ѡ���˼�����Ϣ
	{
		if(itemLog.m_hWnd != NULL)
		{
			::SetParent(itemLog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemLog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2MMoney")))//ѡ���˼�����Ϣ
	{
		if(mMoney.m_hWnd != NULL)
		{
			::SetParent(mMoney.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mMoney.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2GMoney")))//ѡ���˼�����Ϣ
	{
		if(gMoney.m_hWnd != NULL)
		{
			::SetParent(gMoney.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(gMoney.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2Import")))//ѡ���˼�����Ϣ
	{
		if(Import.m_hWnd != NULL)
		{
			::SetParent(Import.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(Import.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2GMUpdate")))//ѡ���˼�����Ϣ
	{
		if(gmUpdate.m_hWnd != NULL)
		{
			::SetParent(gmUpdate.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(gmUpdate.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CJW2ProductManage")))//ѡ���˵���Ȩ��
	{
		if(productManage.m_hWnd != NULL)
		{
			::SetParent(productManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(productManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}

}

//�ٴη���ͬ����Query
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