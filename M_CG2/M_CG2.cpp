// M_CG2.cpp : ���� DLL �ĳ�ʼ�����̡�
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

// CM_CG2App

BEGIN_MESSAGE_MAP(CM_CG2App, CWinApp)
END_MESSAGE_MAP()


// CM_CG2App ����

CM_CG2App::CM_CG2App()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CM_CG2App ����

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


// CM_CG2App ��ʼ��

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

//���µĶԻ���
extern "C" __declspec(dllexport) bool CG2_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicUserInfo")))//ѡ���˲�ѯ�û���Ϣ
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicKickPlayer")))//ѡ����ǿ���������
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBanPlayer")))//ѡ��������ʺŽ��ͣ
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicNoticeInfo")))//ѡ���˹�����Ϣ
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAccountLogin")))//ѡ���˵�����Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(loginInfo.m_hWnd == NULL)
		{
			loginInfo.Create(IDD_DLGLOGININFO);
			loginInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(loginInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	//maple add
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicMailLog")))//˫�����������־��ѯ�˵�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(logQuery.m_hWnd == NULL)
		{
			logQuery.Create(IDD_DLGLOGQUERY);
			logQuery.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(logQuery.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(logQuery.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicModiCharInfo")))//˫�������޸���ҽ�ɫ��Ϣ�˵�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(updateChar.m_hWnd == NULL)
		{
			updateChar.Create(IDD_DLGUPDATECHAR);
			updateChar.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(updateChar.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(updateChar.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_UpdateSkill")))//˫�������޸���Ҽ�����Ϣ�˵�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(updateSkill.m_hWnd == NULL)
		{
			updateSkill.Create(IDD_DLGUPDATESKILL);//IDD_DLGUPDATESKILL
			updateSkill.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(updateSkill.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(updateSkill.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAddItem")))//˫��������ӵ��߲˵�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(addItem.m_hWnd == NULL)
		{
			addItem.Create(IDD_DLGADDITEM);//
			addItem.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(addItem.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(addItem.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicResumeChar")))//˫�����ǻָ���ɫ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(bakAccount.m_hWnd == NULL)
		{
			bakAccount.Create(IDD_DLGBAKACCOUNT);//
			bakAccount.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(bakAccount.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(bakAccount.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_BakAccountInfo")))//˫�����ǻָ���ɫֻ��
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(bakAccountInfo.m_hWnd == NULL)
		{
			bakAccountInfo.Create(IDD_DLGBAKACCOUNTINFO);//
			bakAccountInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(bakAccountInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(bakAccountInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGuildInfo")))//˫�����ǹ������
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(guildManage.m_hWnd == NULL)
		{
			guildManage.Create(IDD_DLGGUILDMANAGE);//
			guildManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(guildManage.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(guildManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGuildInfoRead")))//˫�����ǹ�����Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(guildInfo.m_hWnd == NULL)
		{
			guildInfo.Create(IDD_DLGGUILDINFO);//
			guildInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(guildInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(guildInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBankItem")))//˫������������Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(bankInfo.m_hWnd == NULL)
		{
			bankInfo.Create(IDD_DLGBANKINFO);//
			bankInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(bankInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(bankInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_BankManage")))//˫���������й���
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(bankManage.m_hWnd == NULL)
		{
			bankManage.Create(IDD_DLGBANKMANAGE);//
			bankManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(bankManage.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(bankManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicPackGoods")))//˫�����ǵ�����Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(itemInfo.m_hWnd == NULL)
		{
			itemInfo.Create(IDD_DLGITEMINFO);//
			itemInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(itemInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(itemInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicItemDel")))//˫������ɾ��������Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(delItemInfo.m_hWnd == NULL)
		{
			delItemInfo.Create(IDD_DLGDELITEMINFO);//
			delItemInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(delItemInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(delItemInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicPetInfo")))//˫�����ǳ�����Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(petInfo.m_hWnd == NULL)
		{
			petInfo.Create(IDD_DLGPETINFO);//
			petInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(petInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetManage")))//˫�����ǳ������
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(petManage.m_hWnd == NULL)
		{
			petManage.Create(IDD_DLGPETMANAGE);//
			petManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(petManage.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(petManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetPic")))//˫�����ǳ���ͼ��
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(petPic.m_hWnd == NULL)
		{
			petPic.Create(IDD_DLGPETPIC);//
			petPic.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(petPic.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(petPic.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetSkillManage")))//˫�����ǳ��＼���޸�
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(petSkillManage.m_hWnd == NULL)
		{
			petSkillManage.Create(IDD_DLGPETSKILLMANAGE);//
			petSkillManage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(petSkillManage.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(petSkillManage.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_TmpPwd")))//˫�������޸������ʱ����
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(tmpPwd.m_hWnd == NULL)
		{
			tmpPwd.Create(IDD_DLGTMPPWD);//
			tmpPwd.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(tmpPwd.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(tmpPwd.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_ChangeCharNo")))//˫�����ǽ�ɫ��λ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(changeCharNo.m_hWnd == NULL)
		{
			changeCharNo.Create(IDD_DLGCHANGECHARNO);//
			changeCharNo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(changeCharNo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(changeCharNo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicMoveCharacter")))//˫�������ƶ���ɫ����
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(changeMap.m_hWnd == NULL)
		{
			changeMap.Create(IDD_DLGCHANGEMAP);//
			changeMap.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(changeMap.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(changeMap.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicSendAsk")))//˫�����Ƿ����ʴ���Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(sendAsk.m_hWnd == NULL)
		{
			sendAsk.Create(IDD_DLGSENDASK);//
			sendAsk.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(sendAsk.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(sendAsk.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGetBuyLog")))//˫�������̳�-��ȡ��ҹ�����־��Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(userShoppingInfo.m_hWnd == NULL)
		{
			userShoppingInfo.Create(IDD_DLGUSERSHOPPINGINFO);//
			userShoppingInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(userShoppingInfo.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(userShoppingInfo.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicSendMail")))//˫�����Ƿ��͵�����
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(sendItemPwd.m_hWnd == NULL)
		{
			sendItemPwd.Create(IDD_DLGSENDITEMPWD);//
			sendItemPwd.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(sendItemPwd.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(sendItemPwd.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAccountActive")))//˫�������ʻ������ѯ��ħ������2��
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(accountActive.m_hWnd == NULL)
		{
			accountActive.Create(IDD_DLGACCOUNTACTIVE);//
			accountActive.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(accountActive.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(accountActive.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBanKick")))//˫��������ҷ�ͣ���ߴ�����ħ������2��
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(accountBan.m_hWnd == NULL)
		{
			accountBan.Create(IDD_DLGACCOUNTBAN);//
			accountBan.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(accountBan.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(accountBan.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_RecallLogItem")))//˫�����ǻָ���־���ߣ�ħ������2��
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(recallLogItem.m_hWnd == NULL)
		{
			recallLogItem.Create(IDD_DLGRECALLLOGITEM);//
			recallLogItem.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(recallLogItem.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(recallLogItem.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicRecoverPetLog")))//˫�����ǻָ���־���ħ������2��
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(recallLogPet.m_hWnd == NULL)
		{
			recallLogPet.Create(IDD_DLGRECALLLOGPET);//
			recallLogPet.ShowWindow(SW_SHOWMAXIMIZED);
		}
		::SetParent(recallLogPet.m_hWnd,theApp.mHwndParent);//���о��������
		::SendMessage(recallLogPet.m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);//�öԻ������
		return true;
	}
	return false;
}

//ѡ����ʾ��ͬ���ӶԻ���
extern "C" __declspec(dllexport) BOOL CG2_SHOWDIALOG(CString m_MenuName)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicUserInfo")))//ѡ���˲�ѯ�û���Ϣ
	{
		if(userInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicKickPlayer")))//ѡ����ǿ���������
	{
		if(kickPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(kickPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBanPlayer")))//ѡ��������ʺŽ��ͣ
	{
		if(banPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(banPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicNoticeInfo")))//ѡ���˹�����Ϣ
	{
		if(noticeInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(noticeInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAccountLogin")))//ѡ���˵�����Ϣ
	{
		if(loginInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(loginInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	//maple add
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicMailLog")))//˫�����������־��ѯ�˵�
	{
		if(logQuery.m_hWnd!=NULL)
		{
			::SetWindowPos(logQuery.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicModiCharInfo")))//˫�������޸���ҽ�ɫ��Ϣ�˵�
	{
		if(updateChar.m_hWnd!=NULL)
		{
			::SetWindowPos(updateChar.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_UpdateSkill")))//˫�������޸���Ҽ�����Ϣ�˵�
	{
		if(updateSkill.m_hWnd!=NULL)
		{
			::SetWindowPos(updateSkill.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAddItem")))//˫��������ӵ��߲˵�
	{
		if(addItem.m_hWnd!=NULL)
		{
			::SetWindowPos(addItem.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicResumeChar")))//˫�����ǻָ���ɫ�˵�
	{
		if(bakAccount.m_hWnd!=NULL)
		{
			::SetWindowPos(bakAccount.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_BakAccountInfo")))//˫�����ǻָ���ɫ(ֻ��)�˵�
	{
		if(bakAccountInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(bakAccountInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGuildInfo")))//˫�����ǹ������˵�
	{
		if(guildManage.m_hWnd!=NULL)
		{
			::SetWindowPos(guildManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGuildInfoRead")))//˫�����ǻָ���ɫ�˵�
	{
		if(guildInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(guildInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBankItem")))//˫������������Ϣ�˵�
	{
		if(bankInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(bankInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_BankManage")))//˫���������й���˵�
	{
		if(bankManage.m_hWnd!=NULL)
		{
			::SetWindowPos(bankManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GCCG_CG2_ItemInfo")))//˫�����ǵ�����Ϣ�˵�
	{
		if(itemInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(itemInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicItemDel")))//˫�����ǵ�����Ϣ�˵�
	{
		if(delItemInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(delItemInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicPetInfo")))//˫�����ǳ�����Ϣ�˵�
	{
		if(petInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(petInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetManage")))//˫�����ǳ������˵�
	{
		if(petManage.m_hWnd!=NULL)
		{
			::SetWindowPos(petManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetPic")))//˫�����ǳ���ͼ���˵�
	{
		if(petPic.m_hWnd!=NULL)
		{
			::SetWindowPos(petPic.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetSkillManage")))//˫�������޸ĳ��＼����Ϣ
	{
		if(petSkillManage.m_hWnd!=NULL)
		{
			::SetWindowPos(petSkillManage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_TmpPwd")))//˫�������޸ĳ��＼����Ϣ
	{
		if(tmpPwd.m_hWnd!=NULL)
		{
			::SetWindowPos(tmpPwd.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_ChangeCharNo")))//˫�����ǽ�ɫ��λ��Ϣ
	{
		if(changeCharNo.m_hWnd!=NULL)
		{
			::SetWindowPos(changeCharNo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicMoveCharacter")))//˫�������ƶ���ɫ����
	{
		if(changeMap.m_hWnd!=NULL)
		{
			::SetWindowPos(changeMap.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicSendAsk")))//˫�����Ƿ����ʴ���Ϣ
	{
		if(sendAsk.m_hWnd!=NULL)
		{
			::SetWindowPos(sendAsk.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGetBuyLog")))//˫�����Ƿ����ʴ���Ϣ
	{
		if(userShoppingInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(userShoppingInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicSendMail")))//˫�����Ƿ����ʴ���Ϣ
	{
		if(sendItemPwd.m_hWnd!=NULL)
		{
			::SetWindowPos(sendItemPwd.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAccountActive")))//˫�������ʻ������ѯ��ħ������2��
	{
		if(accountActive.m_hWnd!=NULL)
		{
			::SetWindowPos(accountActive.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBanKick")))//˫��������ҷ�ͣ���ߴ�����ħ������2��
	{
		if(accountBan.m_hWnd!=NULL)
		{
			::SetWindowPos(accountBan.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_RecallLogItem")))//˫�����ǻָ���־���ߣ�ħ������2��
	{
		if(recallLogItem.m_hWnd!=NULL)
		{
			::SetWindowPos(recallLogItem.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicRecoverPetLog")))//˫�����ǻָ���־���ħ������2��
	{
		if(recallLogPet.m_hWnd!=NULL)
		{
			::SetWindowPos(recallLogPet.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	return FALSE;
}
//ѡ�����ͬ���ӶԻ�������Ϣ
extern "C" __declspec(dllexport) void CG2_DIALOGMSG(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam)
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
		if(loginInfo.m_hWnd != NULL)
		{
			::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(loginInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(logQuery.m_hWnd != NULL)
		{
			::SetParent(logQuery.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(logQuery.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(updateChar.m_hWnd != NULL)
		{
			::SetParent(updateChar.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(updateChar.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(updateSkill.m_hWnd != NULL)
		{
			::SetParent(updateSkill.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(updateSkill.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(addItem.m_hWnd != NULL)
		{
			::SetParent(addItem.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(addItem.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(bakAccount.m_hWnd!=NULL)
		{
			::SetParent(bakAccount.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(bakAccount.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(bakAccountInfo.m_hWnd!=NULL)
		{
			::SetParent(bakAccountInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(bakAccountInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(guildManage.m_hWnd!=NULL)
		{
			::SetParent(guildManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}

		if(guildInfo.m_hWnd!=NULL)
		{
			::SetParent(guildInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(bankInfo.m_hWnd!=NULL)
		{
			::SetParent(bankInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(bankInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(bankManage.m_hWnd!=NULL)
		{
			::SetParent(bankManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(bankManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(itemInfo.m_hWnd!=NULL)
		{
			::SetParent(itemInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(delItemInfo.m_hWnd!=NULL)
		{
			::SetParent(delItemInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(delItemInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(petInfo.m_hWnd!=NULL)
		{
			::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(petManage.m_hWnd!=NULL)
		{
			::SetParent(petManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(petPic.m_hWnd!=NULL)
		{
			::SetParent(petPic.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petPic.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(petSkillManage.m_hWnd!=NULL)
		{
			::SetParent(petSkillManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petSkillManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(tmpPwd.m_hWnd!=NULL)
		{
			::SetParent(tmpPwd.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(tmpPwd.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(changeCharNo.m_hWnd!=NULL)
		{
			::SetParent(changeCharNo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(changeCharNo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(changeMap.m_hWnd!=NULL)
		{
			::SetParent(changeMap.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(changeMap.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(sendAsk.m_hWnd!=NULL)
		{
			::SetParent(sendAsk.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(sendAsk.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(userShoppingInfo.m_hWnd!=NULL)
		{
			::SetParent(userShoppingInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userShoppingInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(sendItemPwd.m_hWnd!=NULL)
		{
			::SetParent(sendItemPwd.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(sendItemPwd.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(accountActive.m_hWnd!=NULL)
		{
			::SetParent(accountActive.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(accountActive.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(accountBan.m_hWnd!=NULL)
		{
			::SetParent(accountBan.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(accountBan.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(recallLogItem.m_hWnd!=NULL)
		{
			::SetParent(recallLogItem.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(recallLogItem.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(recallLogPet.m_hWnd!=NULL)
		{
			::SetParent(recallLogPet.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(recallLogPet.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicUserInfo")))//ѡ���˲�ѯ�û���Ϣ
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicKickPlayer")))//ѡ����ǿ���������
	{
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}

	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBanPlayer")))//ѡ��������ʺŽ��ͣ
	{
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicNoticeInfo")))//ѡ���˹�����Ϣ
	{
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAccountLogin")))//ѡ���˵�����Ϣ
	{
		if(loginInfo.m_hWnd != NULL)
		{
			::SetParent(loginInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(loginInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	//maple add
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicMailLog")))//˫�����������־��ѯ�˵�
	{
		if(logQuery.m_hWnd != NULL)
		{
			::SetParent(logQuery.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(logQuery.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicModiCharInfo")))//˫�������޸���ҽ�ɫ��Ϣ�˵�
	{
		if(updateChar.m_hWnd != NULL)
		{
			::SetParent(updateChar.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(updateChar.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_UpdateSkill")))//˫�������޸���Ҽ�����Ϣ�˵�
	{
		if(updateSkill.m_hWnd != NULL)
		{
			::SetParent(updateSkill.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(updateSkill.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAddItem")))//˫��������ӵ��߲˵�
	{
		if(addItem.m_hWnd != NULL)
		{
			::SetParent(addItem.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(addItem.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicResumeChar")))//˫�����ǻָ���ɫ�˵�
	{
		if(bakAccount.m_hWnd != NULL)
		{
			::SetParent(bakAccount.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(bakAccount.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_BakAccountInfo")))//˫�����ǻָ���ɫ(ֻ��)�˵�
	{
		if(bakAccountInfo.m_hWnd != NULL)
		{
			::SetParent(bakAccountInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(bakAccountInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGuildInfo")))//˫�����ǹ������
	{
		if(guildManage.m_hWnd != NULL)
		{
			::SetParent(guildManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}	

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGuildInfoRead")))//˫�����ǹ������
	{
		if(guildInfo.m_hWnd != NULL)
		{
			::SetParent(guildInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBankItem")))//˫������������Ϣ
	{
		if(bankInfo.m_hWnd != NULL)
		{
			::SetParent(bankInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(bankInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_BankManage")))//˫���������й���
	{
		if(bankManage.m_hWnd != NULL)
		{
			::SetParent(bankManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(bankManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicPackGoods")))//˫�����ǵ�����Ϣ
	{
		if(itemInfo.m_hWnd != NULL)
		{
			::SetParent(itemInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicItemDel")))//˫������ɾ��������Ϣ
	{
		if(delItemInfo.m_hWnd != NULL)
		{
			::SetParent(delItemInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(delItemInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicPetInfo")))//˫�����ǳ�����Ϣ
	{
		if(petInfo.m_hWnd != NULL)
		{
			::SetParent(petInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetManage")))//˫�����ǳ������
	{
		if(petManage.m_hWnd != NULL)
		{
			::SetParent(petManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}	
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetPic")))//˫�����ǳ���ͼ��
	{
		if(petPic.m_hWnd != NULL)
		{
			::SetParent(petPic.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petPic.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_PetSkillManage")))//˫�����ǳ��＼�ܹ���
	{
		if(petSkillManage.m_hWnd != NULL)
		{
			::SetParent(petSkillManage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petSkillManage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_TmpPwd")))//˫�������޸������ʱ����
	{
		if(tmpPwd.m_hWnd != NULL)
		{
			::SetParent(tmpPwd.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(tmpPwd.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_ChangeCharNo")))//˫�����ǽ�ɫ��λ
	{
		if(changeCharNo.m_hWnd != NULL)
		{
			::SetParent(changeCharNo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(changeCharNo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicMoveCharacter")))//˫�������ƶ���ɫ����
	{
		if(changeMap.m_hWnd != NULL)
		{
			::SetParent(changeMap.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(changeMap.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicSendAsk")))//˫�����Ƿ����ʴ���Ϣ
	{
		if(sendAsk.m_hWnd != NULL)
		{
			::SetParent(sendAsk.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(sendAsk.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicGetBuyLog")))//˫�����Ƿ����ʴ���Ϣ
	{
		if(userShoppingInfo.m_hWnd != NULL)
		{
			::SetParent(userShoppingInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userShoppingInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicSendMail")))//˫�����Ƿ����ʴ���Ϣ
	{
		if(sendItemPwd.m_hWnd != NULL)
		{
			::SetParent(sendItemPwd.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(sendItemPwd.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicAccountActive")))//˫�����Ƿ����ʴ���Ϣ
	{
		if(accountActive.m_hWnd != NULL)
		{
			::SetParent(accountActive.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(accountActive.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicBanKick")))//˫�����Ƿ����ʴ���Ϣ
	{
		if(accountBan.m_hWnd != NULL)
		{
			::SetParent(accountBan.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(accountBan.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","GC_CG2_RecallLogItem")))//˫�����Ƿ����ʴ���Ϣ
	{
		if(recallLogItem.m_hWnd != NULL)
		{
			::SetParent(recallLogItem.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(recallLogItem.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","FrmMagicRecoverPetLog")))//˫�����Ƿ����ʴ���Ϣ
	{
		if(recallLogPet.m_hWnd != NULL)
		{
			::SetParent(recallLogPet.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(recallLogPet.m_hWnd, Msg, wParam, lParam);//������Ϣ
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
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��������Ϣ
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
			else if((logQuery.m_hWnd!=NULL)&&(logQuery.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�����־��ѯ�з������б��ѯ
			{
				logQuery.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((updateChar.m_hWnd!=NULL)&&(updateChar.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�޸���ҽ�ɫ��Ϣ
			{
				updateChar.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((updateSkill.m_hWnd!=NULL)&&(updateSkill.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�޸���Ҽ�����Ϣ
			{
				updateSkill.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((addItem.m_hWnd!=NULL)&&(addItem.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//��ӵ�����Ϣ
			{
				addItem.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bakAccount.m_hWnd!=NULL)&&(bakAccount.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�ָ���ɫ��Ϣ
			{
				bakAccount.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bakAccountInfo.m_hWnd!=NULL)&&(bakAccountInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�ָ���ɫ(ֻ��)��Ϣ
			{
				bakAccountInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildManage.m_hWnd!=NULL)&&(guildManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�������
			{
				guildManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildInfo.m_hWnd!=NULL)&&(guildInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//������Ϣ
			{
				guildInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bankInfo.m_hWnd!=NULL)&&(bankInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//������Ϣ
			{
				bankInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bankManage.m_hWnd!=NULL)&&(bankManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//���й���
			{
				bankManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemInfo.m_hWnd!=NULL)&&(itemInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//������Ϣ
			{
				itemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((delItemInfo.m_hWnd!=NULL)&&(delItemInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//ɾ��������Ϣ
			{
				delItemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petInfo.m_hWnd!=NULL)&&(petInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//������Ϣ
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petManage.m_hWnd!=NULL)&&(petManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�������
			{
				petManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petSkillManage.m_hWnd!=NULL)&&(petSkillManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�������
			{
				petSkillManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petPic.m_hWnd!=NULL)&&(petPic.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�������
			{
				petPic.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((tmpPwd.m_hWnd!=NULL)&&(tmpPwd.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�������
			{
				tmpPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((changeCharNo.m_hWnd!=NULL)&&(changeCharNo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//��ɫ��λ
			{
				changeCharNo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((changeMap.m_hWnd!=NULL)&&(changeMap.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�ƶ���ɫ����
			{
				changeMap.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((sendAsk.m_hWnd!=NULL)&&(sendAsk.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�ƶ���ɫ����
			{
				sendAsk.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((sendItemPwd.m_hWnd!=NULL)&&(sendItemPwd.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�ƶ���ɫ����
			{
				sendItemPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((accountActive.m_hWnd!=NULL)&&(accountActive.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�ƶ���ɫ����
			{
				accountActive.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((accountBan.m_hWnd!=NULL)&&(accountBan.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�ƶ���ɫ����
			{
				accountBan.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((recallLogItem.m_hWnd!=NULL)&&(recallLogItem.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�ƶ���ɫ����
			{
				recallLogItem.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((recallLogPet.m_hWnd!=NULL)&&(recallLogPet.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�ƶ���ɫ����
			{
				recallLogPet.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Query_Resp://�û����ϲ�ѯ
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
			else if((logQuery.m_hWnd!=NULL)&&(logQuery.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�����־��ѯ�з������б��ѯ
			{
				logQuery.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((updateChar.m_hWnd!=NULL)&&(updateChar.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�޸���ҽ�ɫ��Ϣ
			{
				updateChar.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((updateSkill.m_hWnd!=NULL)&&(updateSkill.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�޸���Ҽ�����Ϣ
			{
				updateSkill.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((addItem.m_hWnd!=NULL)&&(addItem.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//��ӵ�����Ϣ
			{
				addItem.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemInfo.m_hWnd!=NULL)&&(itemInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//��ɫ������Ϣ
			{
				itemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((delItemInfo.m_hWnd!=NULL)&&(delItemInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//��ɫ������Ϣ
			{
				delItemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petInfo.m_hWnd!=NULL)&&(petInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//������Ϣ
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petManage.m_hWnd!=NULL)&&(petManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//����������Ϣ
			{
				petManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bankInfo.m_hWnd!=NULL)&&(bankInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//������Ϣ
			{
				bankInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((bankManage.m_hWnd!=NULL)&&(bankManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//���й���
			{
				bankManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petPic.m_hWnd!=NULL)&&(petPic.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//����ͼ��
			{
				petPic.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petSkillManage.m_hWnd!=NULL)&&(petSkillManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�������
			{
				petSkillManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((tmpPwd.m_hWnd!=NULL)&&(tmpPwd.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�������
			{
				tmpPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((changeCharNo.m_hWnd!=NULL)&&(changeCharNo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//��ɫ��λ
			{
				changeCharNo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((changeMap.m_hWnd!=NULL)&&(changeMap.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�ƶ���ɫ����
			{
				changeMap.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((sendAsk.m_hWnd!=NULL)&&(sendAsk.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�����ʴ���Ϣ
			{
				sendAsk.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((sendItemPwd.m_hWnd!=NULL)&&(sendItemPwd.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�����ʴ���Ϣ
			{
				sendItemPwd.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Detail_Query_Resp ://��ɫ��ϸ����
	case CEnumCore::Message_Tag_ID::CG2_Account_Attribute_Query_Resp://��ɫ��������
	case CEnumCore::Message_Tag_ID::CG2_Account_Guild_Query_Resp://��ɫ��������
	case CEnumCore::Message_Tag_ID::CG2_Account_Title_Query_Resp://��ɫ�ƺ�����
	case CEnumCore::Message_Tag_ID::CG2_Account_Address_Query_Resp://��ɫ����ϵ
	case CEnumCore::Message_Tag_ID::CG2_Account_Skill_Query_Resp ://��ɫ������Ϣ////maple add
		{
			if((userInfo.m_hWnd!=NULL)&&(userInfo.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((updateSkill.m_hWnd!=NULL)&&(updateSkill.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�޸���Ҽ�����Ϣ
			{
				updateSkill.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Teach_Query_Resp ://�鿴���ʦ����ϵ
	case CEnumCore::Message_Tag_ID::CG2_LoveTree_Query_Resp://�鿴������
	case CEnumCore::Message_Tag_ID::CG2_Marriage_Info_Query_Resp://�鿴��һ�����Ϣ
		{
			if((userInfo.m_hWnd!=NULL)&&(userInfo.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_KickAccount_Query_Resp ://������
		{
			if((kickPlayer.m_hWnd!=NULL)&&(kickPlayer.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Close_RESP://��ͣ����ʺ���Ӧ
	case CEnumCore::Message_Tag_ID::CG2_Account_Open_RESP://�������ʺ���Ӧ
	case CEnumCore::Message_Tag_ID::CG2_Account_BANISHMENT_QUERY_RESP://��ѯ����ʺ���û�б���ͣ
	case CEnumCore::Message_Tag_ID::CG2_BanAccount_Query_Resp://��ѯ���з�ͣ����ʺ���Ϣ
		{
			if((banPlayer.m_hWnd!=NULL)&&(banPlayer.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_SendNote_Query_Resp://���͹���
	case CEnumCore::Message_Tag_ID::CG2_UpdateNote_Query_Resp://�޸Ĺ���
	case CEnumCore::Message_Tag_ID::CG2_DeleteNote_Query_Resp://ɾ������
	case CEnumCore::Message_Tag_ID::CG2_SearchNote_Query_Resp://�鿴����
		{
			if((noticeInfo.m_hWnd != NULL)&&(noticeInfo.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Use_Query_Resp://��ҵ�½��־
		{
			if((loginInfo.m_hWnd != NULL)&&(loginInfo.dlgStatus == operCG2.ReadIntValue("MCG2","Send")))
			{
				loginInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
		//maple add
	case CEnumCore::Message_Tag_ID::CG2_Log_Query_Resp:////��ѯ�����־��Ϣ
		{
			if((logQuery.m_hWnd!=NULL)&&(logQuery.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				logQuery.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Job_Query_Resp://��ѯְҵ����
	case CEnumCore::Message_Tag_ID::CG2_UpdateJob_Query_Resp://�޸���ҽ�ɫְҵ
		{
			if((updateChar.m_hWnd!=NULL)&&(updateChar.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				updateChar.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;

	case CEnumCore::Message_Tag_ID::CG2_GerSkill_Query_Resp://��������ѯ
	case CEnumCore::Message_Tag_ID::CG2_SkillList_Query_Resp://�������Ʋ�ѯ
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
	case CEnumCore::Message_Tag_ID::CG2_Update_Account_Skill_Query_Resp://�޸Ľ�ɫ���ܵȼ�
	case CEnumCore::Message_Tag_ID::CG2_Insert_Account_Skill_Query_Resp://��ӽ�ɫ������Ϣ
		{
			if((updateSkill.m_hWnd!=NULL)&&(updateSkill.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				updateSkill.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Get_Item_Query_Resp://��������ѯ
	case CEnumCore::Message_Tag_ID::CG2_Get_Item_Detail_Query_Resp://�������Ʋ�ѯ
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
	case CEnumCore::Message_Tag_ID::CG2_Insert_Item_Query_Resp://��ӵ���
		{
			if((addItem.m_hWnd!=NULL)&&(addItem.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				addItem.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_BakAccount_Query_Resp://��ѯ������ҽ�ɫ��Ϣ
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
	case CEnumCore::Message_Tag_ID::CG2_SearchGuild_Query_Resp://������Ϣ
	case CEnumCore::Message_Tag_ID::CG2_SearchGuild_Detail_Query_Resp://�����Ա
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
	case CEnumCore::Message_Tag_ID::CG2_RenameGuild_Query_Resp://�޸Ĺ�������
	case CEnumCore::Message_Tag_ID::CG2_UpdateGuildLv_Query_Resp://�޸Ĺ���ȼ�
	case CEnumCore::Message_Tag_ID::CG2_UpdateGuildHonor_Query_Resp://�޸Ĺ�������
		{
			if((guildManage.m_hWnd!=NULL)&&(guildManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				guildManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			
		}	
		break;
	case CEnumCore::Message_Tag_ID::CG2_PackItem_Query_Resp://��ɫ����������Ϣ
	case CEnumCore::Message_Tag_ID::CG2_TempItem_Query_Resp://��ɫ��ʱ������Ϣ
	case CEnumCore::Message_Tag_ID::CG2_CharItem_Query_Resp://����װ����Ϣ
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
	case CEnumCore::Message_Tag_ID::CG2_ShopItem_Query_Resp://�շѵ��߲�ѯ
		{
			if((itemInfo.m_hWnd!=NULL)&&(itemInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				itemInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_PetInfo_Query_Resp://���������Ϣ
			if((petInfo.m_hWnd!=NULL)&&(petInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petManage.m_hWnd!=NULL)&&(petManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petSkillManage.m_hWnd!=NULL)&&(petSkillManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�������
			{
				petSkillManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		break;
	case CEnumCore::Message_Tag_ID::CG2_PetSkill_Query_Resp://���＼����Ϣ
		{
			if((petInfo.m_hWnd!=NULL)&&(petInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petSkillManage.m_hWnd!=NULL)&&(petSkillManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))//�������
			{
				petSkillManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Update_Pet_Query_Resp://�޸ĳ�������
	case CEnumCore::Message_Tag_ID::CG2_AddPet_Query_Resp://��ӳ���
	case CEnumCore::Message_Tag_ID::CG2_UpdatePetLevel_Query_Resp://�޸ĳ���ȼ�
		{
			if((petManage.m_hWnd!=NULL)&&(petManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_PetList_Query_Resp://�����б��ѯ
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
	case CEnumCore::Message_Tag_ID::CG2_PetItem_Query_Resp://������Ʒ��Ϣ
		{
			if((petInfo.m_hWnd!=NULL)&&(petInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_BankItem_Query_Resp://������Ʒ��Ϣ
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
	case CEnumCore::Message_Tag_ID::CG2_BankInfo_Query_Resp://���д����Ϣ
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
	case CEnumCore::Message_Tag_ID::CG2_BankPet_Query_Resp://���г�����Ϣ
		{
			if((bankInfo.m_hWnd!=NULL)&&(bankInfo.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				bankInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Insert_Pet_Skill_Query_Resp://���г�����Ϣ
	case CEnumCore::Message_Tag_ID::CG2_Update_Pet_Skill_Query_Resp://
		{
			if((petSkillManage.m_hWnd!=NULL)&&(petSkillManage.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petSkillManage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_PetPic_Query_Resp://���г�����Ϣ
	case CEnumCore::Message_Tag_ID::CG2_PetPic_Del_Query_Resp:
		{
			if((petPic.m_hWnd!=NULL)&&(petPic.dlgStatus==operCG2.ReadIntValue("MCG2","Send")))
			{
				petPic.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Insert_TmpPwd_Query_Resp://���г�����Ϣ
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

//�ٴη���ͬ����Query
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