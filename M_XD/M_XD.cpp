// M_XD.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "M_XD.h"
#include "OperationXD.h"
#include "XDUserInfor.h"
#include "KickPlayer.h"
#include "BanPlayer.h"
#include "Notice.h"
#include "XDItemInfo.h"
#include "XDMailInfo.h"
#include "XDAuctionInfo.h"
#include "XDLoginLog.h"
#include "XDItemShop.h"
#include "XDItemLog.h"
#include "XDMailLog.h"
#include "XDMCashLog.h"
#include "XDCharLog.h"
#include "XDUserManage.h"
#include "XDItemManage.h"
#include "XDGuildInfo.h"
#include "XDQuestInfo.h"
#include "XDCarDetail.h"
#include "XDUserGuild.h"
#include "XDGuildLog.h"
#include "XDNPCItemInfo.h"
#include "XDBanList.h"
#include "XDGuildManage.h"
#include "XDGMManage.h"

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

// CM_XDApp

BEGIN_MESSAGE_MAP(CM_XDApp, CWinApp)
END_MESSAGE_MAP()


// CM_XDApp ����

CM_XDApp::CM_XDApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CM_XDApp ����

CM_XDApp theApp;
XDUserInfor userInfo;
CKickPlayer kickPlayer;
CBanPlayer banPlayer;
CNotice noticeInfo;
CXDItemInfo iteminfo;
CXDMailInfo mailinfo;
CXDAuctionInfo auctioninfo;
CXDLoginLog loginlog;
CXDItemShop itemshop;
CXDItemLog itemlog;
CXDMailLog maillog;
CXDMCashLog mcashlog;
CXDCharLog charlog;
CXDUserManage usermanage;
CXDItemManage itemmanage;
CXDGuildInfo guildinfo;
CXDQuestInfo questinfo;
CXDCarDetail cardetail;
CXDUserGuild userguild;
CXDGuildLog guildlog;
CXDNPCItemInfo npciteminfo;
CXDBanList banlist;
CXDGuildManage guildmanage;
CXDGMManage gmmanage;

// CM_XDApp ��ʼ��

BOOL CM_XDApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" __declspec(dllexport) BOOL XD_TRANSLATEMESSAGE(MSG* pMsg)
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
				if(iteminfo.m_hWnd != NULL)
				{
					iteminfo.PreTranslateMessage(pMsg);
				}
				if(mailinfo.m_hWnd != NULL)
				{
					mailinfo.PreTranslateMessage(pMsg);
				}
				if(auctioninfo.m_hWnd != NULL)
				{
					auctioninfo.PreTranslateMessage(pMsg);
				}
				if(loginlog.m_hWnd!=NULL)
				{
					loginlog.PreTranslateMessage(pMsg);
				}
				if(itemshop.m_hWnd != NULL)
				{
					itemshop.PreTranslateMessage(pMsg);
				}
				if(itemlog.m_hWnd != NULL)
				{
					itemlog.PreTranslateMessage(pMsg);
				}
				if(maillog.m_hWnd != NULL)
				{
					maillog.PreTranslateMessage(pMsg);
				}
				if(mcashlog.m_hWnd != NULL)
				{
					mcashlog.PreTranslateMessage(pMsg);
				}
				if(charlog.m_hWnd != NULL)
				{
					charlog.PreTranslateMessage(pMsg);
				}
				if(usermanage.m_hWnd != NULL)
				{
					usermanage.PreTranslateMessage(pMsg);
				}
				if(itemmanage.m_hWnd != NULL)
				{
					itemmanage.PreTranslateMessage(pMsg);
				}
				if(guildinfo.m_hWnd != NULL)
				{
					guildinfo.PreTranslateMessage(pMsg);
				}
				if(questinfo.m_hWnd != NULL)
				{
					questinfo.PreTranslateMessage(pMsg);
				}
				if(cardetail.m_hWnd != NULL)
				{
					cardetail.PreTranslateMessage(pMsg);
				}
				if(userguild.m_hWnd != NULL)
				{
					userguild.PreTranslateMessage(pMsg);
				}
				if(guildlog.m_hWnd != NULL)
				{
					guildlog.PreTranslateMessage(pMsg);
				}
				if(npciteminfo.m_hWnd != NULL)
				{
					npciteminfo.PreTranslateMessage(pMsg);
				}
				if(banlist.m_hWnd != NULL)
				{
					banlist.PreTranslateMessage(pMsg);
				}
				if(guildmanage.m_hWnd != NULL)
				{
					guildmanage.PreTranslateMessage(pMsg);
				}
				if(gmmanage.m_hWnd != NULL)
				{
					gmmanage.PreTranslateMessage(pMsg);
				}
			}
		}		
	}
	return FALSE;
}

//ѡ��򿪲�ͬ���ӶԻ���
extern "C" __declspec(dllexport) bool XD_OPENDIALOG(CString m_MenuName)
{
	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDUserInfor")))//����ʺ���Ϣ��ѯ
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDKickPlayer")))//ǿ���������
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDBanPlayer")))//����˺Ž�/��ͣ
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDNoticeInfo")))//�������
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemInfo")))//�����Ʒ��Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(iteminfo.m_hWnd== NULL)
		{
			iteminfo.Create(IDD_DLGITEMINFO);		
			::SetParent(iteminfo.m_hWnd,theApp.mHwndParent);//���о��������
			iteminfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			iteminfo.ShowWindow(SW_SHOWMAXIMIZED);
			iteminfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMailInfo")))//�ʼ���Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(mailinfo.m_hWnd== NULL)
		{
			mailinfo.Create(IDD_DLGMAILINFO);		
			::SetParent(mailinfo.m_hWnd,theApp.mHwndParent);//���о��������
			mailinfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			mailinfo.ShowWindow(SW_SHOWMAXIMIZED);
			mailinfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDAuctionInfo")))//��������Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(auctioninfo.m_hWnd== NULL)
		{
			auctioninfo.Create(IDD_DLGAUCTIONINFO);		
			::SetParent(auctioninfo.m_hWnd,theApp.mHwndParent);//���о��������
			auctioninfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			auctioninfo.ShowWindow(SW_SHOWMAXIMIZED);
			auctioninfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDLoginLog")))//��ҵ�¼��־
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(loginlog.m_hWnd== NULL)
		{
			loginlog.Create(IDD_DLGLOGINLOG);		
			::SetParent(loginlog.m_hWnd,theApp.mHwndParent);//���о��������
			loginlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			loginlog.ShowWindow(SW_SHOWMAXIMIZED);
			loginlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemShop")))//�̳���Ʒ������־
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemLog")))//�����Ʒ��־
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMailLog")))//����ʼ���־
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMCashLog")))//M��ʹ����־
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(mcashlog.m_hWnd== NULL)
		{
			mcashlog.Create(IDD_DLGMCASHLOG);		
			::SetParent(mcashlog.m_hWnd,theApp.mHwndParent);//���о��������
			mcashlog.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			mcashlog.ShowWindow(SW_SHOWMAXIMIZED);
			mcashlog.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDCharLog")))//��ҽ�ɫ��־
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDUserManage")))//��ҽ�ɫ����
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemManage")))//��ҵ��߹���
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildInfo")))//������Ϣ��ѯ
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDQuestInfo")))//��������ѯ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(questinfo.m_hWnd== NULL)
		{
			questinfo.Create(IDD_DLGQUESTINFO);		
			::SetParent(questinfo.m_hWnd,theApp.mHwndParent);//���о��������
			questinfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			questinfo.ShowWindow(SW_SHOWMAXIMIZED);
			questinfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDCarDetail")))//��ճ�����Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(cardetail.m_hWnd== NULL)
		{
			cardetail.Create(IDD_DLGCARDETAIL);		
			::SetParent(cardetail.m_hWnd,theApp.mHwndParent);//���о��������
			cardetail.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			cardetail.ShowWindow(SW_SHOWMAXIMIZED);
			cardetail.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDUserGuild")))//��ҹ�����Ϣ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(userguild.m_hWnd== NULL)
		{
			userguild.Create(IDD_DLGUSERGUILD);		
			::SetParent(userguild.m_hWnd,theApp.mHwndParent);//���о��������
			userguild.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			userguild.ShowWindow(SW_SHOWMAXIMIZED);
			userguild.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildLog")))//������־
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDNPCItemInfo")))//NPC������ȡ��ѯ
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(npciteminfo.m_hWnd== NULL)
		{
			npciteminfo.Create(IDD_DLGGETNPCITEM);		
			::SetParent(npciteminfo.m_hWnd,theApp.mHwndParent);//���о��������
			npciteminfo.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			npciteminfo.ShowWindow(SW_SHOWMAXIMIZED);
			npciteminfo.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDBanList")))//��ͣ��Ϣ��ѯ
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildManage")))//�������
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
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGMManage")))//GMTools����
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(gmmanage.m_hWnd== NULL)
		{
			gmmanage.Create(IDD_DLGGMMANAGE);		
			::SetParent(gmmanage.m_hWnd,theApp.mHwndParent);//���о��������
			gmmanage.ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			gmmanage.ShowWindow(SW_SHOWMAXIMIZED);
			gmmanage.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		}
		return true;
	}
	return false;
}
//ѡ����ʾ��ͬ���ӶԻ���
extern "C" __declspec(dllexport) BOOL XD_SHOWDIALOG(CString m_MenuName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CIni mIni;
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDUserInfor")))//��ѯ�û���Ϣ
	{		
		if(userInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(userInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}		
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDKickPlayer")))//ǿ���������
	{
		if(kickPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(kickPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDBanPlayer")))//����ʺŽ��ͣ
	{
		if(banPlayer.m_hWnd!=NULL)
		{
			::SetWindowPos(banPlayer.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDNoticeInfo")))//������Ϣ
	{
		if(noticeInfo.m_hWnd!=NULL)
		{
			::SetWindowPos(noticeInfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemInfo")))//�����Ʒ��Ϣ
	{
		if(iteminfo.m_hWnd!=NULL)
		{
			::SetWindowPos(iteminfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMailInfo")))//�ʼ���Ϣ
	{
		if(mailinfo.m_hWnd!=NULL)
		{
			::SetWindowPos(mailinfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDAuctionInfo")))//��������Ϣ
	{
		if(auctioninfo.m_hWnd!=NULL)
		{
			::SetWindowPos(auctioninfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDLoginLog")))//��ҵ�¼��־
	{
		if(loginlog.m_hWnd!=NULL)
		{
			::SetWindowPos(loginlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemShop")))//�̳���Ʒ������־
	{
		if(itemshop.m_hWnd!=NULL)
		{
			::SetWindowPos(itemshop.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemLog")))//�����Ʒ��־
	{
		if(itemlog.m_hWnd!=NULL)
		{
			::SetWindowPos(itemlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMailLog")))//����ʼ���־
	{
		if(maillog.m_hWnd!=NULL)
		{
			::SetWindowPos(maillog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMCashLog")))//M��ʹ����־
	{
		if(mcashlog.m_hWnd!=NULL)
		{
			::SetWindowPos(mcashlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDCharLog")))//��ҽ�ɫ��־
	{
		if(charlog.m_hWnd!=NULL)
		{
			::SetWindowPos(charlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDUserManage")))//��ҽ�ɫ����
	{
		if(usermanage.m_hWnd!=NULL)
		{
			::SetWindowPos(usermanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemManage")))//��ҵ��߹���
	{
		if(itemmanage.m_hWnd!=NULL)
		{
			::SetWindowPos(itemmanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildInfo")))//������Ϣ��ѯ
	{
		if(guildinfo.m_hWnd!=NULL)
		{
			::SetWindowPos(guildinfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDQuestInfo")))//��������ѯ
	{
		if(questinfo.m_hWnd!=NULL)
		{
			::SetWindowPos(questinfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDCarDetail")))//��ճ�����Ϣ
	{
		if(cardetail.m_hWnd!=NULL)
		{
			::SetWindowPos(cardetail.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDUserGuild")))//��ҹ�����Ϣ
	{
		if(userguild.m_hWnd!=NULL)
		{
			::SetWindowPos(userguild.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildLog")))//������־
	{
		if(guildlog.m_hWnd!=NULL)
		{
			::SetWindowPos(guildlog.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDNPCItemInfo")))//NPC������ȡ��ѯ
	{
		if(npciteminfo.m_hWnd!=NULL)
		{
			::SetWindowPos(npciteminfo.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDBanList")))//��ͣ��Ϣ��ѯ
	{
		if(banlist.m_hWnd!=NULL)
		{
			::SetWindowPos(banlist.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildManage")))//�������
	{
		if(guildmanage.m_hWnd!=NULL)
		{
			::SetWindowPos(guildmanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGMManage")))//GMTools����
	{
		if(gmmanage.m_hWnd!=NULL)
		{
			::SetWindowPos(gmmanage.m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			return TRUE;
		}
	}
	return FALSE;
}

//�ٴη���ͬ����Query
extern "C" __declspec(dllexport) void XD_SENDINFOAGAIN()
{
	theApp.operXD.SendSameQuery();
}

/////////////////////////////////��ʼ��������Ϣ
extern "C" __declspec(dllexport) void GETXDINFO(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent, int* m_SelectDll)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.UserByID = userByID;
	theApp.userName = userName;
	theApp.mHwndParent = m_HwndParent;
	theApp.operXD.initSocket(m_socket);
	theApp.operXD.intXD = m_SelectDll;
}

//ѡ�����ͬ���ӶԻ�����Ϣ
extern "C" __declspec(dllexport) void XD_DIALOGMSG(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam)
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
		if(iteminfo.m_hWnd != NULL)
		{
			::SetParent(iteminfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(iteminfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(mailinfo.m_hWnd != NULL)
		{
			::SetParent(mailinfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mailinfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(auctioninfo.m_hWnd != NULL)
		{
			::SetParent(auctioninfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(auctioninfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(loginlog.m_hWnd != NULL)
		{
			::SetParent(loginlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(loginlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(itemshop.m_hWnd != NULL)
		{
			::SetParent(itemshop.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemshop.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(itemlog.m_hWnd != NULL)
		{
			::SetParent(itemlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(maillog.m_hWnd != NULL)
		{
			::SetParent(maillog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(maillog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(mcashlog.m_hWnd != NULL)
		{
			::SetParent(mcashlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mcashlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(charlog.m_hWnd != NULL)
		{
			::SetParent(charlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(charlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
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
		if(guildinfo.m_hWnd != NULL)
		{
			::SetParent(guildinfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildinfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(questinfo.m_hWnd != NULL)
		{
			::SetParent(questinfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(questinfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(cardetail.m_hWnd != NULL)
		{
			::SetParent(cardetail.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(cardetail.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(userguild.m_hWnd != NULL)
		{
			::SetParent(userguild.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userguild.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(guildlog.m_hWnd != NULL)
		{
			::SetParent(guildlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(npciteminfo.m_hWnd != NULL)
		{
			::SetParent(npciteminfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(npciteminfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(banlist.m_hWnd != NULL)
		{
			::SetParent(banlist.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banlist.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(guildmanage.m_hWnd != NULL)
		{
			::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildmanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
		if(gmmanage.m_hWnd != NULL)
		{
			::SetParent(gmmanage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(gmmanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDUserInfor")))
	{
		if(userInfo.m_hWnd != NULL)
		{
			::SetParent(userInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}

	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDKickPlayer")))////ǿ���������
	{
		if(kickPlayer.m_hWnd != NULL)
		{
			::SetParent(kickPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(kickPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDBanPlayer")))//����˺Ž�/��ͣ
	{
		if(banPlayer.m_hWnd != NULL)
		{
			::SetParent(banPlayer.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banPlayer.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","XDNoticeInfo")))//�������
	{
		if(noticeInfo.m_hWnd != NULL)
		{
			::SetParent(noticeInfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(noticeInfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemInfo")))//�����Ʒ��Ϣ
	{
		if(iteminfo.m_hWnd != NULL)
		{
			::SetParent(iteminfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(iteminfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMailInfo")))//�ʼ���Ϣ
	{
		if(mailinfo.m_hWnd != NULL)
		{
			::SetParent(mailinfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mailinfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDAuctionInfo")))//��������Ϣ
	{
		if(auctioninfo.m_hWnd != NULL)
		{
			::SetParent(auctioninfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(auctioninfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDLoginLog")))//��ҵ�¼��־
	{
		if(loginlog.m_hWnd != NULL)
		{
			::SetParent(loginlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(loginlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemShop")))//�̳���Ʒ������־
	{
		if(itemshop.m_hWnd != NULL)
		{
			::SetParent(itemshop.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemshop.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemLog")))//�����Ʒ��־
	{
		if(itemlog.m_hWnd != NULL)
		{
			::SetParent(itemlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMailLog")))//����ʼ���־
	{
		if(maillog.m_hWnd != NULL)
		{
			::SetParent(maillog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(maillog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDMCashLog")))//M��ʹ����־
	{
		if(mcashlog.m_hWnd != NULL)
		{
			::SetParent(mcashlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(mcashlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDCharLog")))//��ҽ�ɫ��־
	{
		if(charlog.m_hWnd != NULL)
		{
			::SetParent(charlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(charlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDUserManage")))//��ҽ�ɫ����
	{
		if(usermanage.m_hWnd != NULL)
		{
			::SetParent(usermanage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(usermanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDItemManage")))//��ҵ��߹���
	{
		if(itemmanage.m_hWnd != NULL)
		{
			::SetParent(itemmanage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(itemmanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildInfo")))//������Ϣ��ѯ
	{
		if(guildinfo.m_hWnd != NULL)
		{
			::SetParent(guildinfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildinfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDQuestInfo")))//��������ѯ
	{
		if(questinfo.m_hWnd != NULL)
		{
			::SetParent(questinfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(questinfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDCarDetail")))//��ճ�����Ϣ
	{
		if(cardetail.m_hWnd != NULL)
		{
			::SetParent(cardetail.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(cardetail.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDUserGuild")))//��ҹ�����Ϣ
	{
		if(userguild.m_hWnd != NULL)
		{
			::SetParent(userguild.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(userguild.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildLog")))//������־
	{
		if(guildlog.m_hWnd != NULL)
		{
			::SetParent(guildlog.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildlog.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDNPCItemInfo")))//NPC������ȡ��ѯ
	{
		if(npciteminfo.m_hWnd != NULL)
		{
			::SetParent(npciteminfo.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(npciteminfo.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDBanList")))//��ͣ��Ϣ��ѯ
	{
		if(banlist.m_hWnd != NULL)
		{
			::SetParent(banlist.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(banlist.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGuildManage")))//�������
	{
		if(guildmanage.m_hWnd != NULL)
		{
			::SetParent(guildmanage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(guildmanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
	else if(!strcmp(m_MenuName,mIni.ReadValue("Global","CXDGMManage")))//GMTools����
	{
		if(gmmanage.m_hWnd != NULL)
		{
			::SetParent(gmmanage.m_hWnd,theApp.mHwndParent);//���о��������
			::SendMessage(gmmanage.m_hWnd, Msg, wParam, lParam);//������Ϣ
		}
	}
}
extern "C" __declspec(dllexport) void GETXDMESSAGE(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.m_TagID = m_message_tag_id;
	OperationXD operXD;

	//////////////////////
	switch(m_message_tag_id)
	{	
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��������Ϣ
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((noticeInfo.m_hWnd != NULL) && (noticeInfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((iteminfo.m_hWnd != NULL) && (iteminfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				iteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailinfo.m_hWnd != NULL) && (mailinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				mailinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((auctioninfo.m_hWnd != NULL) && (auctioninfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				auctioninfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((loginlog.m_hWnd != NULL) && (loginlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				loginlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemshop.m_hWnd != NULL) && (itemshop.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemshop.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemlog.m_hWnd != NULL) && (itemlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((maillog.m_hWnd != NULL) && (maillog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				maillog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mcashlog.m_hWnd != NULL) && (mcashlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				mcashlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((charlog.m_hWnd != NULL) && (charlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				charlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((usermanage.m_hWnd != NULL) && (usermanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				usermanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildinfo.m_hWnd != NULL) && (guildinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((questinfo.m_hWnd != NULL) && (questinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				questinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((cardetail.m_hWnd != NULL) && (cardetail.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				cardetail.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((userguild.m_hWnd != NULL) && (userguild.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				userguild.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildlog.m_hWnd != NULL) && (guildlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((npciteminfo.m_hWnd != NULL) && (npciteminfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				npciteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banlist.m_hWnd != NULL) && (banlist.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				banlist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((gmmanage.m_hWnd != NULL) && (gmmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				gmmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_Account_Query_Resp://ȡ�ý�ɫ������Ѷ��Ӧ
		{
			if((userInfo.m_hWnd != NULL) && (userInfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				userInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((kickPlayer.m_hWnd != NULL) && (kickPlayer.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((banPlayer.m_hWnd != NULL) && (banPlayer.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((iteminfo.m_hWnd != NULL) && (iteminfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				iteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((iteminfo.m_hWnd != NULL) && (iteminfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				iteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailinfo.m_hWnd != NULL) && (mailinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				mailinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((auctioninfo.m_hWnd != NULL) && (auctioninfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				auctioninfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((loginlog.m_hWnd != NULL) && (loginlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				loginlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemshop.m_hWnd != NULL) && (itemshop.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemshop.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemlog.m_hWnd != NULL) && (itemlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((maillog.m_hWnd != NULL) && (maillog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				maillog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mcashlog.m_hWnd != NULL) && (mcashlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				mcashlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((charlog.m_hWnd != NULL) && (charlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				charlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((usermanage.m_hWnd != NULL) && (usermanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				usermanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((questinfo.m_hWnd != NULL) && (questinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				questinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((cardetail.m_hWnd != NULL) && (cardetail.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				cardetail.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((userguild.m_hWnd != NULL) && (userguild.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				userguild.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((npciteminfo.m_hWnd != NULL) && (npciteminfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				npciteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((gmmanage.m_hWnd != NULL) && (gmmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				gmmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_KickPlayer_Resp://ǿ���������
		{
			if(kickPlayer.m_hWnd != NULL)
			{
				kickPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��ǿ��������߽��淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ClosePlayer_Resp://��ͣ����ʺ�
	case CEnumCore::Message_Tag_ID::XDJG_OpenPlayer_Resp://�������ʺ�	
		{
			if(banPlayer.m_hWnd != NULL)
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//������ʺŽ��ͣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_CloseList_Resp://��ѯ���б���ͣ�ʺ��б�Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::XDJG_AccountIsClose_Query_Log_Resp://�ʺ��Ƿ��ͣ
		{
			if(banPlayer.m_hWnd != NULL)
			{
				banPlayer.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//������ʺŽ��ͣ���淢��Ϣ
			}
			else if(banlist.m_hWnd != NULL)
			{
				banlist.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//����ͣ��Ϣ��ѯҳ�淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_BoardTasker_Add_Resp://���������Ӧ
	case CEnumCore::Message_Tag_ID::XDJG_BoardTasker_Query_Resp://�����ѯ��Ӧ
	case CEnumCore::Message_Tag_ID::XDJG_BoardTasker_Update_Resp://���������Ӧ
	case CEnumCore::Message_Tag_ID::XDJG_BoardTasker_Del_Resp://����ɾ����Ӧ
		{
			if(noticeInfo.m_hWnd != NULL)
			{
				noticeInfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);//��������Ϣ���淢��Ϣ
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ItemBody_Query_Resp://������Ʒ��Ϣ
	case CEnumCore::Message_Tag_ID::XDJG_Itembackpack_Query_Resp://������Ʒ��Ϣ
	case CEnumCore::Message_Tag_ID::XDJG_ItemStorage_Query_Resp://�ֿ���Ʒ��Ϣ
	case CEnumCore::Message_Tag_ID::XDJG_GuildStorage_Query_Resp://����ֿ���Ϣ
	case CEnumCore::Message_Tag_ID::XDJG_KingkongStorage_Query_Resp://��ղֿ���Ϣ
		{
			if((iteminfo.m_hWnd != NULL) && (iteminfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				iteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_MailInfo_Query_Resp://�ʼ���Ϣ
		{
			if((mailinfo.m_hWnd != NULL) && (mailinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				mailinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_AuctioneerInfo_Query_Resp://��������Ϣ
		{
			if((auctioninfo.m_hWnd != NULL) && (auctioninfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				auctioninfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_Login_Log_Resp://��ҵ�¼��־
		{
			if((loginlog.m_hWnd != NULL) && (loginlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				loginlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_Shoping_Log_Resp://�̳���Ʒ������־
		{
			if((itemshop.m_hWnd != NULL) && (itemshop.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemshop.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_TransGain_Log_Resp://���׻��
	case CEnumCore::Message_Tag_ID::XDJG_TransLose_Log_Resp://����ʧȥ
	case CEnumCore::Message_Tag_ID::XDJG_BuyFromNpc_Log_Resp://��NPC������
	case CEnumCore::Message_Tag_ID::XDJG_SaleToNpc_Log_Resp://����NPC
	case CEnumCore::Message_Tag_ID::XDJG_PickUpItem_Log_Resp://ʰȡ��Ʒ
	case CEnumCore::Message_Tag_ID::XDJG_DiscardItem_Log_Resp://������Ʒ
	case CEnumCore::Message_Tag_ID::XDJG_ConsumeItem_Log_Resp://��Ʒ����
	case CEnumCore::Message_Tag_ID::XDJG_AuctioneerSaled_Log_Resp://����������
	case CEnumCore::Message_Tag_ID::XDJG_AuctioneerBought_Log_Resp://�����й���	
	case CEnumCore::Message_Tag_ID::XDJG_EquipIncrease_Log_Resp://װ��������־
	case CEnumCore::Message_Tag_ID::XDJG_Synthesis_Log_Resp://��Ƭ�ϳ���־
	case CEnumCore::Message_Tag_ID::XDJG_EquipTransfer_Log_Resp://װ��������־
	case CEnumCore::Message_Tag_ID::XDJG_ItemIdentify_Log_Resp://��Ʒ����
	case CEnumCore::Message_Tag_ID::XDJG_RoleStore_Log_Resp://���˲ֿ�����־
	case CEnumCore::Message_Tag_ID::XDJG_GuildStore_Log_Resp://����ֿ�����־
		{
			if((itemlog.m_hWnd != NULL) && (itemlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ItemAttribute_Query_Resp://��Ʒ���Բ�ѯ
	{
			if((itemlog.m_hWnd != NULL) && (itemlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((mailinfo.m_hWnd != NULL) && (mailinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				mailinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((maillog.m_hWnd != NULL) && (maillog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				maillog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_SendMail_Log_Resp://�����ʼ�
	case CEnumCore::Message_Tag_ID::XDJG_ReceiveMail_Log_Resp://��ȡ�ʼ�
		{
			if((maillog.m_hWnd != NULL) && (maillog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				maillog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ExpansionPack_Log_Resp://�����������Ѽ�¼
	case CEnumCore::Message_Tag_ID::XDJG_Deliver_Log_Resp://������־
	case CEnumCore::Message_Tag_ID::XDJG_ExpansionWarehouse_Log_Resp://��ɫ�ֿ��������Ѽ�¼
		{
			if((mcashlog.m_hWnd != NULL) && (mcashlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				mcashlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_RoleUpgrade_Log_Resp://��ɫ����
	case CEnumCore::Message_Tag_ID::XDJG_RoleCreate_Log_Resp://��ɫ����
	case CEnumCore::Message_Tag_ID::XDJG_RoleSkill_Log_Resp://��ɫ����ѧϰ
	case CEnumCore::Message_Tag_ID::XDJG_ReceiveTask_Log_Resp://��ȡ����
	case CEnumCore::Message_Tag_ID::XDJG_CompleteTask_Log_Resp://�������
	case CEnumCore::Message_Tag_ID::XDJG_Copy_Log_Resp://������ѯ
		{
			if((charlog.m_hWnd != NULL) && (charlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				charlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_RoleSkillAdd_Resp://��ɫ�������
	case CEnumCore::Message_Tag_ID::XDJG_RoleSkillDel_Resp://��ɫ����ɾ��
	case CEnumCore::Message_Tag_ID::XDJG_ModifyLevel_operate_Resp://�޸ĵȼ�
	case CEnumCore::Message_Tag_ID::XDJG_ModifyPwd_operate_Resp://�޸�����
	case CEnumCore::Message_Tag_ID::XDJG_ResumePwd_operate_Resp://��ʱ����ָ�
	case CEnumCore::Message_Tag_ID::XDJG_ResumeRole_operate_Resp://��ɫ�ָ�
	case CEnumCore::Message_Tag_ID::XDJG_DeleteRole_operate_Resp://��ɫɾ��
	case CEnumCore::Message_Tag_ID::XDJG_RoleSkills_Query_Resp://��ɫ������Ϣ��ѯ
	case CEnumCore::Message_Tag_ID::XDJG_SkillList_Query_Resp://�����б��ѯ
	case CEnumCore::Message_Tag_ID::XDJG_TitleList_Query_Resp://�ƺ��б��ѯ
	case CEnumCore::Message_Tag_ID::XDJG_AddTitle_Query_Resp://��ӳƺ�
	case CEnumCore::Message_Tag_ID::XDJG_RemoveTitle_Query_Resp://�Ƴ��ƺ�
		{
			if((usermanage.m_hWnd != NULL) && (usermanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				usermanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ItemAdd_Resp://�������
	case CEnumCore::Message_Tag_ID::XDJG_ItemDel_Resp://����ɾ��
	case CEnumCore::Message_Tag_ID::XDJG_MoneyAdd_Resp://�����Ϸ��
	case CEnumCore::Message_Tag_ID::XDJG_AddRoleBind_operate_Resp://��ӽ�ɫ���Ͻ�Ǯ����(�󶨱�)
	case CEnumCore::Message_Tag_ID::XDJG_AddRoleNonBind_operate_Resp://��ӽ�ɫ���Ͻ�Ǯ����(�ǰ󶨱�)
	case CEnumCore::Message_Tag_ID::XDJG_UpRoleBind_operate_Resp://�޸Ľ�ɫ���Ͻ�Ǯ����(�󶨱�)
	case CEnumCore::Message_Tag_ID::XDJG_UpRoleNonBind_operate_Resp://�޸Ľ�ɫ���Ͻ�Ǯ����(�ǰ󶨱�)
	case CEnumCore::Message_Tag_ID::XDJG_ItemType_Query_Resp://�������Ͳ�ѯ
	case CEnumCore::Message_Tag_ID::XDJG_ItemNameLst_Query_Resp://��Ӧ���͵ĵ����б��ѯ
		{
			if((itemmanage.m_hWnd != NULL) && (itemmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				itemmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_GuildBaseInfo_Query_Resp://���������Ϣ	
		{
			if((guildinfo.m_hWnd != NULL) && (guildinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildlog.m_hWnd != NULL) && (guildlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_GuildMemberList_Query_Resp://�����Ա�б�
		{
			if((guildinfo.m_hWnd != NULL) && (guildinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
			else if((guildmanage.m_hWnd != NULL) && (guildmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_PlayerTaskInfo_Query_Resp://��������ѯ
		{
			if((questinfo.m_hWnd != NULL) && (questinfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				questinfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_CarBaseInfo_Query_Resp://��ճ���������Ϣ
	case CEnumCore::Message_Tag_ID::XDJG_CarDetailInfo_Query_Resp://��ճ�����ϸ��Ϣ
		{
			if((cardetail.m_hWnd != NULL) && (cardetail.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				cardetail.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_PlayerGuildBaseInfo_Query_Resp://��ҹ��������Ϣ
	case CEnumCore::Message_Tag_ID::XDJG_PlayerGuildItemInfo_Query_Resp://��ҹ�����Ʒ��Ϣ
		{
			if((userguild.m_hWnd != NULL) && (userguild.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				userguild.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_GuildCreate_Log_Resp://�������
	case CEnumCore::Message_Tag_ID::XDJG_GuildDismiss_Log_Resp://�����ɢ
	case CEnumCore::Message_Tag_ID::XDJG_GuildAddMember_Log_Resp://������ӳ�Ա
	case CEnumCore::Message_Tag_ID::XDJG_GuildMemberLeaved_Log_Resp://�����Ա�뿪
	case CEnumCore::Message_Tag_ID::XDJG_GuildPostChanged_Log_Resp://����ְ����
		{
			if((guildlog.m_hWnd != NULL) && (guildlog.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				guildlog.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_NPCGetItem_Query_Resp://NPC������ȡ��ѯ
		{
			if((npciteminfo.m_hWnd != NULL) && (npciteminfo.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				npciteminfo.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_MoveToPosition_Query_Resp://�ƶ���ָ��λ��
	case CEnumCore::Message_Tag_ID::XDJG_MoveToRole_Query_Resp://�ƶ���ָ��������
	case CEnumCore::Message_Tag_ID::XDJG_MoveToTargetRole_Query_Resp://�ƶ���Ŀ��������
	case CEnumCore::Message_Tag_ID::XDJG_BuffList_Query_Resp://BUFF�б��ѯ
	case CEnumCore::Message_Tag_ID::XDJG_AddBuff_Query_Resp://���BUFF
	case CEnumCore::Message_Tag_ID::XDJG_RemoveBuff_Query_Resp://�Ƴ�BUFF
		{
			if((gmmanage.m_hWnd != NULL) && (gmmanage.dlgStatus == operXD.ReadIntValue("MXD","Send")))
			{
				gmmanage.SendMessage(UM_RECEIVE,(WPARAM)lpRecvbuf,(LPARAM)m_packethead.bodylen);
			}
		}
		break;
	}
}

