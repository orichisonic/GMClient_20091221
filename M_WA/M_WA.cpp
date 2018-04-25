// M_WA.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "M_WA.h"
#include "OperationWA.h"
#include "WAUserInfor.h"
#include "KickPlayer.h"
#include "BanPlayer.h"
#include "Notice.h"
#include "CWADelItemInfo.h"
#include "MailInfor.h"
#include "PetInfor.h"
#include "AccountLog.h"
#include "goodsinfor.h"
#include "ChangeMoney.h"
#include "WAItemLog.h"
#include "WACashLog.h"
#include "WAQuestLog.h"
#include "WAMailLog.h"
#include "WAUserLog.h"
#include "WAItemShop.h"
#include "WAUserManage.h"
#include "WAItemManage.h"
#include "WABanList.h"
#include "WACharLog.h"
#include "WAGuildLog.h"
#include "WAPetLog.h"
#include "WAPlayerInfo.h"
#include "WAGuildInfo.h"
#include "WAPetManage.h"
#include "WAGuildManage.h"
#include "WAMailSend.h"

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

// CM_WAApp

BEGIN_MESSAGE_MAP(CM_WAApp, CWinApp)
END_MESSAGE_MAP()


// CM_WAApp ����

CM_WAApp::CM_WAApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CM_WAApp ����

CM_WAApp theApp;
WAUserInfor userInfo;
CKickPlayer kickPlayer;
CBanPlayer banPlayer;
CNotice noticeInfo;
PetInfor petinfor;
CWADelItemInfo deliteminfo;//ɾ������
MailInfor mailinfor;//������Ϣ��ѯ
CWAAccountLogin accountlogin;//�û���¼��Ϣ
GoodsInfor goodsinfor;
ChangeMoney changemoney;
CWAItemLog itemlog;
CWACashLog cashlog;
CWAQuestLog questlog;
CWAMailLog maillog;
CWAUserLog userlog;
CWAItemShop itemshop;
CWAUserManage usermanage;
CWAItemManage itemmanage;
CWABanList banlist;
CWACharLog charlog;
CWAGuildLog guildlog;
CWAPetLog petlog;
CWAPlayerInfo playerinfo;
CWAGuildInfo guildinfo;
CWAPetManage petmanage;
CWAGuildManage guildmanage;
CWAMailSend mailsend;

// CM_WAApp ��ʼ��

BOOL CM_WAApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
//ѡ��򿪲�ͬ���ӶԻ���
extern "C" __declspec(dllexport) bool WA_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserInfor")))//����ʺ���Ϣ��ѯ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(userInfo.m_hWnd== NULL)
		{
			userInfo.Create(IDD_DLGUSERINFO);

			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//���о��������
			userInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			userInfo.ShowWindow(SW_SHOWMAXIMIZED);
			userInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAKickPlayer")))//ǿ���������
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(kickPlayer.m_hWnd== NULL)
		{
			kickPlayer.Create(IDD_DLGKICKPLAYER);

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
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWABanPlayer")))//����˺Ž�/��ͣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(banPlayer.m_hWnd== NULL)
		{
			banPlayer.Create(IDD_DLGBANPLAYER);

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
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWANoticeInfor")))//�������
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(noticeInfo.m_hWnd== NULL)
		{
			noticeInfo.Create(IDD_DLGNOTICE);

			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//���о��������
			noticeInfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			noticeInfo.ShowWindow(SW_SHOWMAXIMIZED);
			noticeInfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAToolsDel")))//����ɾ��
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(deliteminfo.m_hWnd== NULL)
		{
			deliteminfo.Create(IDD_DLGDELITEMINFO);
					
			::SetParent(deliteminfo.m_hWnd,theApp.mHwndParent);//���о��������
			deliteminfo.ShowWindow(SW_SHOWMAXIMIZED);
				
		}
		else
		{
			deliteminfo.ShowWindow(SW_SHOWMAXIMIZED);
			deliteminfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailInfor")))//������Ϣ��ѯ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(mailinfor.m_hWnd== NULL)
		{
			mailinfor.Create(IDD_DLGMAIL);	

			::SetParent(mailinfor.m_hWnd,theApp.mHwndParent);//���о��������
			mailinfor.ShowWindow(SW_SHOWMAXIMIZED);

		}
		else
		{
			mailinfor.ShowWindow(SW_SHOWMAXIMIZED);
			mailinfor.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetInfor")))//������Ϣ��ѯ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(petinfor.m_hWnd== NULL)
		{
			petinfor.Create(IDD_DLGPETINFOR);	

			::SetParent(petinfor.m_hWnd,theApp.mHwndParent);//���о��������
			petinfor.ShowWindow(SW_SHOWMAXIMIZED);

		}
		else
		{
			petinfor.ShowWindow(SW_SHOWMAXIMIZED);
			petinfor.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWALoginLog")))//�û���¼��Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(accountlogin.m_hWnd== NULL)
		{
			accountlogin.Create(IDD_DLGLOGINLOG);
		
			::SetParent(accountlogin.m_hWnd,theApp.mHwndParent);//���о��������
			accountlogin.ShowWindow(SW_SHOWMAXIMIZED);

		}
		else
		{
			accountlogin.ShowWindow(SW_SHOWMAXIMIZED);
			accountlogin.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemInfor")))//������Ϣ��ѯ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(goodsinfor.m_hWnd== NULL)
		{
			goodsinfor.Create(IDD_DLGGOODSINFOR);

			::SetParent(goodsinfor.m_hWnd,theApp.mHwndParent);//���о��������
			goodsinfor.ShowWindow(SW_SHOWMAXIMIZED);

		}
		else
		{			
			goodsinfor.ShowWindow(SW_SHOWMAXIMIZED);
			goodsinfor.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else 	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAChangeMoney")))//�޸Ľ�ɫ���Ϻ����н�Ǯ����
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(changemoney.m_hWnd== NULL)
		{
			changemoney.Create(IDD_DLGBANKMANAGE);

			::SetParent(changemoney.m_hWnd,theApp.mHwndParent);//���о��������
			changemoney.ShowWindow(SW_SHOWMAXIMIZED);

		}
		else
		{

			goodsinfor.ShowWindow(SW_SHOWMAXIMIZED);
			goodsinfor.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemLog")))//��Ʒ��־
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(itemlog.m_hWnd== NULL)
		{
			itemlog.Create(IDD_DLGITEMLOG);
		
			::SetParent(itemlog.m_hWnd,theApp.mHwndParent);//���о��������
			itemlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			itemlog.ShowWindow(SW_SHOWMAXIMIZED);
			itemlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWACashLog")))//��Ϸ����־
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(cashlog.m_hWnd== NULL)
		{
			cashlog.Create(IDD_DLGCASHLOG);

			::SetParent(cashlog.m_hWnd,theApp.mHwndParent);//���о��������
			cashlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			cashlog.ShowWindow(SW_SHOWMAXIMIZED);
			cashlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAQuestLog")))//������־
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(questlog.m_hWnd== NULL)
		{
			questlog.Create(IDD_DLGQUESTLOG);

			::SetParent(questlog.m_hWnd,theApp.mHwndParent);//���о��������
			questlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			questlog.ShowWindow(SW_SHOWMAXIMIZED);
			questlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailLog")))//�ʼ���־
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(maillog.m_hWnd== NULL)
		{
			maillog.Create(IDD_DLGMAILLOG);

			::SetParent(maillog.m_hWnd,theApp.mHwndParent);//���о��������
			maillog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			maillog.ShowWindow(SW_SHOWMAXIMIZED);
			maillog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserLog")))//�û���־
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(userlog.m_hWnd== NULL)
		{
			userlog.Create(IDD_DLGUSERLOG);

			::SetParent(userlog.m_hWnd,theApp.mHwndParent);//���о��������
			userlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			userlog.ShowWindow(SW_SHOWMAXIMIZED);
			userlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemShop")))//�̳ǹ����¼��ѯ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(itemshop.m_hWnd== NULL)
		{
			itemshop.Create(IDD_DLGITEMSHOP);

			::SetParent(itemshop.m_hWnd,theApp.mHwndParent);//���о��������
			itemshop.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			itemshop.ShowWindow(SW_SHOWMAXIMIZED);
			itemshop.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserManage")))//����˺Ź���(��ʿ)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(usermanage.m_hWnd== NULL)
		{
			usermanage.Create(IDD_DLGUSERMANAGE);

			::SetParent(usermanage.m_hWnd,theApp.mHwndParent);//���о��������
			usermanage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			usermanage.ShowWindow(SW_SHOWMAXIMIZED);
			usermanage.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemManage")))//��ҵ��߹���(��ʿ)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(itemmanage.m_hWnd== NULL)
		{
			itemmanage.Create(IDD_DLGITEMMANAGE);

			::SetParent(itemmanage.m_hWnd,theApp.mHwndParent);//���о��������
			itemmanage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			itemmanage.ShowWindow(SW_SHOWMAXIMIZED);
			itemmanage.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWABanList")))//��ͣ�˺��б�(��ʿ)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(banlist.m_hWnd== NULL)
		{
			banlist.Create(IDD_DLGBANLIST);

			::SetParent(banlist.m_hWnd,theApp.mHwndParent);//���о��������
			banlist.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			banlist.ShowWindow(SW_SHOWMAXIMIZED);
			banlist.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWACharLog")))//��ɫ��־((��ʿ)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(charlog.m_hWnd== NULL)
		{
			charlog.Create(IDD_DLGCHARLOG);

			::SetParent(charlog.m_hWnd,theApp.mHwndParent);//���о��������
			charlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			charlog.ShowWindow(SW_SHOWMAXIMIZED);
			charlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildLog")))//Ӷ������־((��ʿ)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(guildlog.m_hWnd== NULL)
		{
			guildlog.Create(IDD_DLGGUILDLOG);

			::SetParent(guildlog.m_hWnd,theApp.mHwndParent);//���о��������
			guildlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			guildlog.ShowWindow(SW_SHOWMAXIMIZED);
			guildlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetLog")))//������־((��ʿ)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(petlog.m_hWnd== NULL)
		{
			petlog.Create(IDD_DLGPETLOG);

			::SetParent(petlog.m_hWnd,theApp.mHwndParent);//���о��������
			petlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			petlog.ShowWindow(SW_SHOWMAXIMIZED);
			petlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPlayerInfo")))//�û���Ϣ((��ʿ)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(playerinfo.m_hWnd== NULL)
		{
			playerinfo.Create(IDD_DLGPLAYERINFO);

			::SetParent(playerinfo.m_hWnd,theApp.mHwndParent);//���о��������
			playerinfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			playerinfo.ShowWindow(SW_SHOWMAXIMIZED);
			playerinfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildInfo")))//Ӷ������Ϣ��ѯ((��ʿ)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(guildinfo.m_hWnd== NULL)
		{
			guildinfo.Create(IDD_DLGGUILDINFO);

			::SetParent(guildinfo.m_hWnd,theApp.mHwndParent);//���о��������
			guildinfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			guildinfo.ShowWindow(SW_SHOWMAXIMIZED);
			guildinfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetManage")))//�������((��ʿ)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(petmanage.m_hWnd== NULL)
		{
			petmanage.Create(IDD_DLGPETMANAGE);

			::SetParent(petmanage.m_hWnd,theApp.mHwndParent);//���о��������
			petmanage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			petmanage.ShowWindow(SW_SHOWMAXIMIZED);
			petmanage.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildManage")))//Ӷ���Ź���((��ʿ)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(guildmanage.m_hWnd== NULL)
		{
			guildmanage.Create(IDD_DLGGUILDMANAGE);

			::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//���о��������
			guildmanage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			guildmanage.ShowWindow(SW_SHOWMAXIMIZED);
			guildmanage.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailSend")))//���������ʼ�(��ʿ)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(mailsend.m_hWnd== NULL)
		{
			mailsend.Create(IDD_DLGMAILSEND);

			::SetParent(mailsend.m_hWnd,theApp.mHwndParent);//���о��������
			mailsend.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			mailsend.ShowWindow(SW_SHOWMAXIMIZED);
			mailsend.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	return false;
}
//ѡ����ʾ��ͬ���ӶԻ���
extern "C" __declspec(dllexport) BOOL WA_SHOWDIALOG(CString m_MenuName)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserInfor")))//ѡ���˲�ѯ�û���Ϣ
	{		
		if(userInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}		
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAKickPlayer")))//ѡ����ǿ���������
	{
		if(kickPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(kickPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWABanPlayer")))//ѡ��������ʺŽ��ͣ
	{
		if(banPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(banPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWANoticeInfor")))//ѡ���˹�����Ϣ(
	{
		if(noticeInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(noticeInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAToolsDel")))//ѡ���˵���ɾ��
	{
		if(deliteminfo.m_hWnd!=NULL)
		{
			::SetWindowPos(deliteminfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailInfor")))//ѡ����mail
	{
		if(mailinfor.m_hWnd!=NULL)
		{
			::SetWindowPos(mailinfor.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetInfor")))//ѡ���˳�����Ϣ��ѯ
	{
		if(petinfor.m_hWnd!=NULL)
		{
			::SetWindowPos(petinfor.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAAcountLoginInfor")))//ѡ���˵�¼��־��Ϣ��ѯ
	{
		if(accountlogin.m_hWnd!=NULL)
		{
			::SetWindowPos(accountlogin.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemInfor")))//ѡ������ҵ�����Ϣ��ѯ
	{
		if(goodsinfor.m_hWnd!=NULL)
		{
			::SetWindowPos(goodsinfor.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAChangeMoney")))//ѡ�����޸Ľ�ɫ���Ϻ����н�Ǯ����
	{
		if(changemoney.m_hWnd!=NULL)
		{
			::SetWindowPos(changemoney.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemLog")))//��Ʒ��־
	{
		if(itemlog.m_hWnd!=NULL)
		{
			::SetWindowPos(itemlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWACashLog")))//��Ϸ����־
	{
		if(cashlog.m_hWnd!=NULL)
		{
			::SetWindowPos(cashlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAQuestLog")))//������־
	{
		if(questlog.m_hWnd!=NULL)
		{
			::SetWindowPos(questlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailLog")))//�ʼ���־
	{
		if(maillog.m_hWnd!=NULL)
		{
			::SetWindowPos(maillog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserLog")))//�û���־
	{
		if(userlog.m_hWnd!=NULL)
		{
			::SetWindowPos(userlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemShop")))//�̳ǹ����¼��ѯ
	{
		if(itemshop.m_hWnd!=NULL)
		{
			::SetWindowPos(itemshop.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserManage")))//����˺Ź���
	{
		if(usermanage.m_hWnd!=NULL)
		{
			::SetWindowPos(usermanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemManage")))//��ҵ��߹���
	{
		if(itemmanage.m_hWnd!=NULL)
		{
			::SetWindowPos(itemmanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWABanList")))//��ͣ�˺��б�
	{
		if(banlist.m_hWnd!=NULL)
		{
			::SetWindowPos(banlist.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWACharLog")))//��ɫ��־
	{
		if(charlog.m_hWnd!=NULL)
		{
			::SetWindowPos(charlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildLog")))//Ӷ������־
	{
		if(guildlog.m_hWnd!=NULL)
		{
			::SetWindowPos(guildlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetLog")))//������־
	{
		if(petlog.m_hWnd!=NULL)
		{
			::SetWindowPos(petlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPlayerInfo")))//�û���Ϣ��ѯ(��ʿ)
	{
		if(playerinfo.m_hWnd!=NULL)
		{
			::SetWindowPos(playerinfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildInfo")))//Ӷ������Ϣ��ѯ
	{
		if(guildinfo.m_hWnd!=NULL)
		{
			::SetWindowPos(guildinfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetManage")))//�������
	{
		if(petmanage.m_hWnd!=NULL)
		{
			::SetWindowPos(petmanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildManage")))//Ӷ���Ź���
	{
		if(guildmanage.m_hWnd!=NULL)
		{
			::SetWindowPos(guildmanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailSend")))//���������ʼ�(��ʿ)
	{
		if(mailsend.m_hWnd!=NULL)
		{
			::SetWindowPos(mailsend.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	return false;
}

//�ٴη���ͬ����Query
extern "C" __declspec(dllexport) void WA_SENDINFOAGAIN()
{
	theApp.operWA.SendSameQuery();
}

/////////////////////////////////��ʼ��������Ϣ
extern "C" __declspec(dllexport) void GETWAINFO(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent, int* m_SelectDll)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.UserByID = userByID;
	theApp.userName = userName;
	theApp.mHwndParent = m_HwndParent;
	theApp.operWA.initSocket(m_socket);
	theApp.operWA.intWA = m_SelectDll;
}
extern "C" __declspec(dllexport) BOOL WA_TRANSLATEMESSAGE(MSG* pMsg)
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
				if(deliteminfo.m_hWnd != NULL)
				{
					deliteminfo.PreTranslateMessage(pMsg);
				}
				if(petinfor.m_hWnd != NULL)
				{
					petinfor.PreTranslateMessage(pMsg);
				}
				if(accountlogin.m_hWnd != NULL)
				{
					accountlogin.PreTranslateMessage(pMsg);
				}
				if(goodsinfor.m_hWnd != NULL)
				{
					goodsinfor.PreTranslateMessage(pMsg);
				}
				if(changemoney.m_hWnd != NULL)
				{
					changemoney.PreTranslateMessage(pMsg);
				}
				if(itemlog.m_hWnd != NULL)
				{
					itemlog.PreTranslateMessage(pMsg);
				}
				if(cashlog.m_hWnd != NULL)
				{
					cashlog.PreTranslateMessage(pMsg);
				}
				if(questlog.m_hWnd != NULL)
				{
					questlog.PreTranslateMessage(pMsg);
				}
				if(maillog.m_hWnd != NULL)
				{
					maillog.PreTranslateMessage(pMsg);
				}
				if(userlog.m_hWnd != NULL)
				{
					userlog.PreTranslateMessage(pMsg);
				}
				if(itemshop.m_hWnd != NULL)
				{
					itemshop.PreTranslateMessage(pMsg);
				}
				if(usermanage.m_hWnd != NULL)
				{
					usermanage.PreTranslateMessage(pMsg);
				}
				if(itemmanage.m_hWnd != NULL)
				{
					itemmanage.PreTranslateMessage(pMsg);
				}
				if(banlist.m_hWnd != NULL)
				{
					banlist.PreTranslateMessage(pMsg);
				}
				if(charlog.m_hWnd != NULL)
				{
					charlog.PreTranslateMessage(pMsg);
				}
				if(guildlog.m_hWnd != NULL)
				{
					guildlog.PreTranslateMessage(pMsg);
				}
				if(petlog.m_hWnd != NULL)
				{
					petlog.PreTranslateMessage(pMsg);
				}
				if(playerinfo.m_hWnd != NULL)
				{
					playerinfo.PreTranslateMessage(pMsg);
				}
				if(guildinfo.m_hWnd != NULL)
				{
					guildinfo.PreTranslateMessage(pMsg);
				}
				if(petmanage.m_hWnd != NULL)
				{
					petmanage.PreTranslateMessage(pMsg);
				}
				if(guildmanage.m_hWnd != NULL)
				{
					guildmanage.PreTranslateMessage(pMsg);
				}
				if(mailsend.m_hWnd != NULL)
				{
					mailsend.PreTranslateMessage(pMsg);
				}
			}
		}
	}
	return FALSE;
}

//ѡ�����ͬ���ӶԻ�����Ϣ
extern "C" __declspec(dllexport) void WA_DIALOGMSG(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam)
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
		if(deliteminfo.m_hWnd != NULL)
		{
			::SetParent(deliteminfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(deliteminfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(petinfor.m_hWnd != NULL)
		{
			::SetParent(petinfor.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petinfor.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(accountlogin.m_hWnd != NULL)
		{
			::SetParent(accountlogin.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(accountlogin.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(goodsinfor.m_hWnd != NULL)
		{
			::SetParent(goodsinfor.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(goodsinfor.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(changemoney.m_hWnd != NULL)
		{
			::SetParent(changemoney.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(changemoney.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(itemlog.m_hWnd != NULL)
		{
			::SetParent(itemlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(cashlog.m_hWnd != NULL)
		{
			::SetParent(cashlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(cashlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(questlog.m_hWnd != NULL)
		{
			::SetParent(questlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(questlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(userlog.m_hWnd != NULL)
		{
			::SetParent(userlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(itemshop.m_hWnd != NULL)
		{
			::SetParent(itemshop.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemshop.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(usermanage.m_hWnd != NULL)
		{
			::SetParent(usermanage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(usermanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(itemmanage.m_hWnd != NULL)
		{
			::SetParent(itemmanage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemmanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(banlist.m_hWnd != NULL)
		{
			::SetParent(banlist.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banlist.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(charlog.m_hWnd != NULL)
		{
			::SetParent(charlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(charlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(guildlog.m_hWnd != NULL)
		{
			::SetParent(guildlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(petlog.m_hWnd != NULL)
		{
			::SetParent(petlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(playerinfo.m_hWnd != NULL)
		{
			::SetParent(playerinfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(playerinfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(guildinfo.m_hWnd != NULL)
		{
			::SetParent(guildinfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildinfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(petmanage.m_hWnd != NULL)
		{
			::SetParent(petmanage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petmanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(guildmanage.m_hWnd != NULL)
		{
			::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildmanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(mailsend.m_hWnd != NULL)
		{
			::SetParent(mailsend.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mailsend.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserInfor")))
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAKickPlayer")))////ǿ���������
	{
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWABanPlayer")))//����˺Ž�/��ͣ
	{
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWANoticeInfor")))//�������
	{
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAToolsDel")))//����ɾ��
	{
		if(deliteminfo.m_hWnd != NULL)
		{
			::SetParent(deliteminfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(deliteminfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailInfor")))//������Ϣ��ѯ
	{
		if(mailinfor.m_hWnd != NULL)
		{
			::SetParent(mailinfor.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mailinfor.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetInfor")))//������Ϣ��ѯ
	{
		if(petinfor.m_hWnd != NULL)
		{
			::SetParent(petinfor.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petinfor.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAAcountLoginInfor")))//��¼��Ϣ��ѯ
	{
		if(accountlogin.m_hWnd != NULL)
		{
			::SetParent(accountlogin.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(accountlogin.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemInfor")))//��ҵ�����Ϣ��ѯ
	{
		if(goodsinfor.m_hWnd != NULL)
		{
			::SetParent(goodsinfor.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(goodsinfor.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAChangeMoney")))//�޸Ľ�ɫ���Ϻ����н�Ǯ����
	{
		if(changemoney.m_hWnd != NULL)
		{
			::SetParent(changemoney.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(changemoney.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemLog")))//��Ʒ��־
	{
		if(itemlog.m_hWnd!=NULL)
		{
			::SetParent(itemlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWACashLog")))//��Ϸ����־
	{
		if(cashlog.m_hWnd!=NULL)
		{
			::SetParent(cashlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(cashlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAQuestLog")))//������־
	{
		if(questlog.m_hWnd!=NULL)
		{
			::SetParent(questlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(questlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserLog")))//�û���־
	{
		if(userlog.m_hWnd!=NULL)
		{
			::SetParent(userlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemShop")))//�̳ǹ����¼��ѯ
	{
		if(itemshop.m_hWnd!=NULL)
		{
			::SetParent(itemshop.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemshop.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAUserManage")))//����˺Ź���
	{
		if(usermanage.m_hWnd!=NULL)
		{
			::SetParent(usermanage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(usermanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAItemManage")))//��ҵ��߹���
	{
		if(itemmanage.m_hWnd!=NULL)
		{
			::SetParent(itemmanage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemmanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWABanList")))//��ͣ�˺��б�
	{
		if(banlist.m_hWnd!=NULL)
		{
			::SetParent(banlist.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banlist.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWACharLog")))//��ɫ��־
	{
		if(charlog.m_hWnd!=NULL)
		{
			::SetParent(charlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(charlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildLog")))//Ӷ������־
	{
		if(guildlog.m_hWnd!=NULL)
		{
			::SetParent(guildlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetLog")))//������־
	{
		if(petlog.m_hWnd!=NULL)
		{
			::SetParent(petlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPlayerInfo")))//=�û���Ϣ��ѯ(��ʿ)
	{
		if(playerinfo.m_hWnd!=NULL)
		{
			::SetParent(playerinfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(playerinfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildInfo")))//Ӷ������Ϣ��ѯ
	{
		if(guildinfo.m_hWnd!=NULL)
		{
			::SetParent(guildinfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildinfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAPetManage")))//�������
	{
		if(petmanage.m_hWnd!=NULL)
		{
			::SetParent(petmanage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(petmanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAGuildManage")))//Ӷ���Ź���
	{
		if(guildmanage.m_hWnd!=NULL)
		{
			::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildmanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CWAMailSend")))//���������ʼ�
	{
		if(mailsend.m_hWnd!=NULL)
		{
			::SetParent(mailsend.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mailsend.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
}
extern "C" __declspec(dllexport) void GETWAMESSAGE(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.m_TagID = m_message_tag_id;
	OperationWA operWA;
	// MessageBox(NULL,(LPCTSTR)lpRecvbuf,"",0);
	CString tagid="";

	//MessageBox(NULL,tagid,"",0);
	/////////////////////����
	if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
	{
		userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
	}
	//////////////////////
	switch(m_message_tag_id)
	{	
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��������Ϣ
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((noticeInfo.m_hWnd != NULL) && (noticeInfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((goodsinfor.m_hWnd != NULL) && (goodsinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				goodsinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petinfor.m_hWnd != NULL) && (petinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}	
			else if((changemoney.m_hWnd != NULL) && (changemoney.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				changemoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((deliteminfo.m_hWnd != NULL) && (deliteminfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				deliteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((accountlogin.m_hWnd != NULL) && (accountlogin.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				accountlogin.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailinfor.m_hWnd != NULL) && (mailinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				mailinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemlog.m_hWnd != NULL) && (itemlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((cashlog.m_hWnd != NULL) && (cashlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				cashlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((questlog.m_hWnd != NULL) && (questlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				questlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((maillog.m_hWnd != NULL) && (maillog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				maillog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((userlog.m_hWnd != NULL) && (userlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				userlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemshop.m_hWnd != NULL) && (itemshop.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemshop.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((usermanage.m_hWnd != NULL) && (usermanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				usermanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banlist.m_hWnd != NULL) && (banlist.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				banlist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((charlog.m_hWnd != NULL) && (charlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				charlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((playerinfo.m_hWnd != NULL) && (playerinfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				playerinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildlog.m_hWnd != NULL) && (guildlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petlog.m_hWnd != NULL) && (petlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildinfo.m_hWnd != NULL) && (guildinfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petmanage.m_hWnd != NULL) && (petmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailsend.m_hWnd != NULL) && (mailsend.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				mailsend.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Account_Query_Resp://ȡ�ý�ɫ������Ѷ��Ӧ
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((noticeInfo.m_hWnd != NULL) && (noticeInfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((goodsinfor.m_hWnd != NULL) && (goodsinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				goodsinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petinfor.m_hWnd != NULL) && (petinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}	
			else if((changemoney.m_hWnd != NULL) && (changemoney.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				changemoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((deliteminfo.m_hWnd != NULL) && (deliteminfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				deliteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((accountlogin.m_hWnd != NULL) && (accountlogin.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				accountlogin.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailinfor.m_hWnd != NULL) && (mailinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				mailinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemlog.m_hWnd != NULL) && (itemlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((cashlog.m_hWnd != NULL) && (cashlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				cashlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((questlog.m_hWnd != NULL) && (questlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				questlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((maillog.m_hWnd != NULL) && (maillog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				maillog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((userlog.m_hWnd != NULL) && (userlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				userlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemshop.m_hWnd != NULL) && (itemshop.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemshop.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((usermanage.m_hWnd != NULL) && (usermanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				usermanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((charlog.m_hWnd != NULL) && (charlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				charlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petlog.m_hWnd != NULL) && (petlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((playerinfo.m_hWnd != NULL) && (playerinfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				playerinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petmanage.m_hWnd != NULL) && (petmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_KickPlayer_Resp://ǿ���������
		{
			if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��ǿ��������߽��淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_ClosePlayer_Resp://��ͣ����ʺ�
	case CEnumCore::Message_Tag_ID::WA_OpenPlayer_Resp://�������ʺ�
		{
			if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//������ʺŽ��ͣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_CloseList_Resp://��ͣ�ʺ��б�
		{
			if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//������ʺŽ��ͣ���淢��Ϣ
			}
			else if((banlist.m_hWnd != NULL) && (banlist.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				banlist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//����ͣ�ʺ��б���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_CloseSingle_Resp://������ͣ�ʺ�
		{
			if((banlist.m_hWnd != NULL) && (banlist.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				banlist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//����ͣ�ʺ��б���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Add_Resp://���������Ӧ
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Query_Resp://�����ѯ��Ӧ
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Update_Resp://���������Ӧ
	case CEnumCore::Message_Tag_ID::WA_BoardTasker_Del_Resp://����ɾ����Ӧ
		{
			if((noticeInfo.m_hWnd != NULL) && (noticeInfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��������Ϣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_FriendInfo_Query_Resp://�����б��ѯ
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_BodyItemInfo_Query_Resp://��ѯ���������Ʒ�Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::WA_BagItemInfo_Query_Resp://��ѯ��ұ�����Ʒ�Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::WA_BankItemInfo_Query_Resp://��ѯ���������Ʒ�Ļ�Ӧ
		{
			if((goodsinfor.m_hWnd != NULL) && (goodsinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				goodsinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_EmblemInfo_Query_Resp://��ѯ��һ��µĻ�Ӧ
	case CEnumCore::Message_Tag_ID::WA_PetInfo_Query_Resp://��ѯ��ҳ���Ļ�Ӧ
		{
			if((petinfor.m_hWnd != NULL) && (petinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((petmanage.m_hWnd != NULL) && (petmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_LoginLogoutByIP://��ѯ�ʺŵ�¼��Ϣ�Ļ�Ӧ
		{
			if((accountlogin.m_hWnd != NULL) && (accountlogin.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				accountlogin.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Money_Update_Resp://��Ǯ�޸ķ�����Ϣ�Ļ�Ӧ
		{
			if((changemoney.m_hWnd != NULL) && (changemoney.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				changemoney.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Item_Del_Resp://����ɾ���Ļ�Ӧ
		{			
			if((goodsinfor.m_hWnd != NULL) && (goodsinfor.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				goodsinfor.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_MonsterDropItem_Resp://�������
	case CEnumCore::Message_Tag_ID::WA_Query_BuyItemNPC_Resp://��NPC������
	case CEnumCore::Message_Tag_ID::WA_Query_SellItemTONPC_Resp://����NPC
	case CEnumCore::Message_Tag_ID::WA_Query_DropItem_Resp://�������ɾ��
	case CEnumCore::Message_Tag_ID::WA_Query_GetItemTrade_Resp://���׻��
	case CEnumCore::Message_Tag_ID::WA_Query_LoseItemTrade_Resp://����ʧȥ
	case CEnumCore::Message_Tag_ID::WA_Query_BindItem_Resp://װ����
	case CEnumCore::Message_Tag_ID::WA_Query_UnBindItem_Resp://װ�����
	case CEnumCore::Message_Tag_ID::WA_Query_BoothItem_Resp://��Ұ�̯
	case CEnumCore::Message_Tag_ID::WA_Query_DeleteItem_Resp://����ɾ��
	case CEnumCore::Message_Tag_ID::WA_Query_UseItem_Resp://����ʹ��
	case CEnumCore::Message_Tag_ID::WA_Query_CraftItem_Resp://װ������
	case CEnumCore::Message_Tag_ID::WA_Query_PunchItem_Resp://װ�����
	case CEnumCore::Message_Tag_ID::WA_Query_ChangeSlotItem_Resp://װ���Ŀ�
	case CEnumCore::Message_Tag_ID::WA_Query_UpgradeStar_Resp://װ������
	case CEnumCore::Message_Tag_ID::WA_Query_Gem_Resp://��ʯ
	case CEnumCore::Message_Tag_ID::WA_Query_Pharma_Resp://��ҩ��¼
	case CEnumCore::Message_Tag_ID::WA_Query_CraftGem_Resp://��ʯ�ϳ�
	case CEnumCore::Message_Tag_ID::WA_Query_CraftMatirail_Resp://���Ϻϳ�
	case CEnumCore::Message_Tag_ID::WA_Query_CraftRecipe_Resp://ͼֽ�ϳ�
	case CEnumCore::Message_Tag_ID::WA_Query_MazeIntegral_Resp://�Թ����ֶһ�����
		{
			if((itemlog.m_hWnd != NULL) && (itemlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_MonsterDropMoney_Resp://�������
	case CEnumCore::Message_Tag_ID::WA_Query_GetMoneyQuest_Resp://������
	case CEnumCore::Message_Tag_ID::WA_Query_LoseMoneyRepair_Resp://��װ
	case CEnumCore::Message_Tag_ID::WA_Query_GetMoneyTrade_Resp://���׻��
	case CEnumCore::Message_Tag_ID::WA_Query_LoseMoneyTrade_Resp://����ʧȥ
		{
			if((cashlog.m_hWnd != NULL) && (cashlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				cashlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_QuestReward_Resp://������ɻ�ü�¼
	case CEnumCore::Message_Tag_ID::WA_Query_QuestGive_Resp://������Ʒɾ����¼
		{
			if((questlog.m_hWnd != NULL) && (questlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				questlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_MailSend_Resp://�ʼ�:���ͼ�¼
	case CEnumCore::Message_Tag_ID::WA_Query_MailRecv_Resp://�ʼ�:���ռ�¼
	case CEnumCore::Message_Tag_ID::WA_Query_MailDelete_Resp://�ʼ�:ɾ����¼
		{
			if((maillog.m_hWnd != NULL) && (maillog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				maillog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_Instance_Resp://��ѯ�û��ĸ�����־
		{
			if((userlog.m_hWnd != NULL) && (userlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				userlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_LoginLogoutByIP_Resp://��ҵ�½/�ǳ���־
		{
			if((accountlogin.m_hWnd != NULL) && (accountlogin.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				accountlogin.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_LoginLogout_Resp://��ҵ�½/�ǳ���־
		{
			if((userlog.m_hWnd != NULL) && (userlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				userlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((accountlogin.m_hWnd != NULL) && (accountlogin.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				accountlogin.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Query_ItemShop_Resp://�̳�:�����¼
		{
			if((itemshop.m_hWnd != NULL) && (itemshop.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemshop.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_ModifyCharacterSkill_Resp://�޸Ľ�ɫ����
	case CEnumCore::Message_Tag_ID::WA_RecoverCharacter_Resp://�ָ���ɫ
	case CEnumCore::Message_Tag_ID::WA_ModifyAccountPassw_Resp://�޸�����
	case CEnumCore::Message_Tag_ID::WA_SkillList_Query_Resp://�����б��ѯ
	case CEnumCore::Message_Tag_ID::WA_PlayerRole_Modfiy_Resp://�޸Ľ�ɫ��
	case CEnumCore::Message_Tag_ID::WA_RoleInfo_Modfiy_Resp://�޸Ľ�ɫ����ֵ(��Ǯ,����,�ĵȼ�)
	case CEnumCore::Message_Tag_ID::WA_RoleSkill_Query_Resp://��ѯ������ϼ�����Ϣ
	case CEnumCore::Message_Tag_ID::WA_UserPwd_Recover_Resp://�ָ�����
	case CEnumCore::Message_Tag_ID::WA_Query_ResumePassw_Resp://�ָ�����
	case CEnumCore::Message_Tag_ID::WA_ResumeAttribute_Op_Resp://�ָ���ɫ����
		{
			if((usermanage.m_hWnd != NULL) && (usermanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				usermanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_MailItem_Resp://����ɫ�ʼ���Ʒ
	case CEnumCore::Message_Tag_ID::WA_Item_Add_Resp://��ӵ���
	case CEnumCore::Message_Tag_ID::WA_ItemList_Query_Resp://�����б��ѯ
	case CEnumCore::Message_Tag_ID::WA_ItemType_Query_Resp://��ѯ��ҵ������Ͳ�ѯ	
		{
			if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Character_Upgrade_Resp://��ɫ������¼��ѯ
	case CEnumCore::Message_Tag_ID::WA_Character_Create_Resp://��ɫ������¼��ѯ
	case CEnumCore::Message_Tag_ID::WA_Character_Delete_Resp://��ɫɾ����¼��ѯ
	case CEnumCore::Message_Tag_ID::WA_Join_Guild_Resp://������
	case CEnumCore::Message_Tag_ID::WA_Quit_Guild_Resp://�뿪���
	case CEnumCore::Message_Tag_ID::WA_Create_Guild_Resp://�������
	case CEnumCore::Message_Tag_ID::WA_Dissolve_Guild_Resp://��ɢ���
	case CEnumCore::Message_Tag_ID::WA_Transfer_Info_Resp://תְ��Ϣ��ѯ
	case CEnumCore::Message_Tag_ID::WA_Skills_Log_Resp://������־��¼
	case CEnumCore::Message_Tag_ID::WA_LifeSkills_Log_Resp://�������־��¼
		{
			if((charlog.m_hWnd != NULL) && (charlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				charlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Create_MercenaryGroup_Resp://������¼
	case CEnumCore::Message_Tag_ID::WA_Dissolve_MercenaryGroup_Resp://��ɢ��¼
		{
			if((guildlog.m_hWnd != NULL) && (guildlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_CatchPetSpirit_Record_Resp://���ﾫ�겶׽��¼
	case CEnumCore::Message_Tag_ID::WA_GainSpirit_Record_Resp://���꽻�׻��
	case CEnumCore::Message_Tag_ID::WA_LoseSpirit_Record_Resp://���꽻��ʧȥ
	case CEnumCore::Message_Tag_ID::WA_SellSpirit_Record_Resp://������ۼ�¼
		{
			if((petlog.m_hWnd != NULL) && (petlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_MercenaryGroup_Info_Query_Resp://Ӷ������Ϣ��ѯ
		{
			if((guildlog.m_hWnd != NULL) && (guildlog.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildinfo.m_hWnd != NULL) && (guildinfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_MemberList_Query_Resp://Ӷ���ų�Ա�б��ѯ
		{
			if((guildinfo.m_hWnd != NULL) && (guildinfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_SkillsInfo_Query_Resp://������Ϣ��ѯ
	case CEnumCore::Message_Tag_ID::WA_MissionsCompleted_Query_Resp://���������
	case CEnumCore::Message_Tag_ID::WA_MissionsReceived_Query_Resp://�ѽ�����	
		{
			if((playerinfo.m_hWnd != NULL) && (playerinfo.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				playerinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_PetList_Query_Resp://�����б��ѯ
	case CEnumCore::Message_Tag_ID::WA_PetAdded_Operate_Resp://��ӳ���
	case CEnumCore::Message_Tag_ID::WA_PetDeleted_Operate_Resp://ɾ������	
		{
			if((petmanage.m_hWnd != NULL) && (petmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				petmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_AttornPopedom_Operate_Resp://�������
	case CEnumCore::Message_Tag_ID::WA_ModifyGuildName_Operate_Resp://�޸Ĺ�������
	case CEnumCore::Message_Tag_ID::WA_KickGuildMember_Operate_Resp://�߳������Ա
	case CEnumCore::Message_Tag_ID::WA_DissolveGuild_Operate_Resp://��ɢ����
		{
			if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_SendMails_Op_Resp://���������ʼ�
		{
			if((mailsend.m_hWnd != NULL) && (mailsend.dlgStatus == operWA.ReadIntValue("MWA","Send")))
			{
				mailsend.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	default:
		break;
	}
}

