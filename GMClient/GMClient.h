// GMClient.h : GMClient Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������
#include "MySocket.h"
#include "Login.h"


// CGMClientApp:
// �йش����ʵ�֣������ GMClient.cpp
//

//�򿪶Ի���
typedef bool(_cdecl *GM_OPENDIALOG)(CString m_MenuName);

//ѡ����ʾ��ͬ���ӶԻ���
typedef BOOL (_cdecl *GM_SHOWDIALOG)(CString m_MenuName);

//�رնԻ���
typedef HWND(_cdecl *GM_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//���ͽ��յ�����Ϣ
typedef HWND(_cdecl *GETFRAMEMESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//���������·�������
typedef HWND(_cdecl *GM_SENDINFOAGAIN)();

//���ͻ���������Ϣ
typedef HWND(_cdecl *GETINFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);

//��Ϣ����
typedef HWND(_cdecl *GM_TRANSLATEMESSAGE)(MSG* pMsg);



//ѡ��򿪲�ͬ���ӶԻ���
typedef bool(_cdecl *PAL_OPENDIALOG)(CString m_MenuName);

//ѡ����ʾ��ͬ���ӶԻ���
typedef BOOL (_cdecl *PAL_SHOWDIALOG)(CString m_MenuName);

//ѡ��رղ�ͬ���ӶԻ���
typedef HWND(_cdecl *PAL_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//��Ϣ����
typedef HWND (_cdecl *PAL_TRANSLATEMESSAGE)(MSG* pMsg);

//���ͽ��յ�����Ϣ(�ɽ�)
typedef HWND(_cdecl *GETPALMESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//���������·�������
typedef HWND(_cdecl *PAL_SENDINFOAGAIN)();

//���ͻ���������Ϣ(�ɽ�)
typedef HWND(_cdecl *GETPALINFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);



//GTOWN maple add
//ѡ��򿪲�ͬ���ӶԻ���
typedef bool(_cdecl *GTOWN_OPENDIALOG)(CString m_MenuName);

//ѡ����ʾ��ͬ���ӶԻ���
typedef BOOL (_cdecl *GTOWN_SHOWDIALOG)(CString m_MenuName);

//ѡ�����ͬ���ӶԻ�������Ϣ
typedef HWND(_cdecl *GTOWN_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//��Ϣ����
typedef HWND(_cdecl *GTOWN_TRANSLATEMESSAGE)(MSG* pMsg);

//���ͽ��յ�����Ϣ(GTOWN)
typedef HWND(_cdecl *GETGTOWNMESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//���������·�������
typedef HWND(_cdecl *GTOWN_SENDINFOAGAIN)();

//���ͻ���������Ϣ(GTOWN)
typedef HWND(_cdecl *GETGTOWNINFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);




//ѡ��򿪲�ͬ���ӶԻ���(CG2)
typedef bool (_cdecl *CG2_OPENDIALOG)(CString m_MenuName);

//ѡ����ʾ��ͬ���ӶԻ���
typedef BOOL (_cdecl *CG2_SHOWDIALOG)(CString m_MenuName);

//ѡ��رղ�ͬ���ӶԻ���(CG2)
typedef void (_cdecl *CG2_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//��Ϣ����(CG2)
typedef bool(_cdecl *CG2_TRANSLATEMESSAGE)(MSG* pMsg);

//���ͽ��յ�����Ϣ(CG2)
typedef void(_cdecl *GETCG2MESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//���������·�������(CG2)
typedef void(_cdecl *CG2_SENDINFOAGAIN)();

//���ͻ���������Ϣ(CG2)
typedef void(_cdecl *GETCG2INFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);


//maple add
//ѡ��򿪲�ͬ���ӶԻ���
typedef bool(_cdecl *SDO_OPENDIALOG)(CString m_MenuName);

//ѡ����ʾ��ͬ���ӶԻ���
typedef BOOL (_cdecl *SDO_SHOWDIALOG)(CString m_MenuName);

//ѡ�����ͬ���ӶԻ�������Ϣ
typedef HWND(_cdecl *SDO_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//��Ϣ����
typedef HWND(_cdecl *SDO_TRANSLATEMESSAGE)(MSG* pMsg);

//���ͽ��յ�����Ϣ(GTOWN)
typedef HWND(_cdecl *GETSDOMESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//���������·�������
typedef HWND(_cdecl *SDO_SENDINFOAGAIN)();

//���ͻ���������Ϣ(GTOWN)
typedef HWND(_cdecl *GETSDOINFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);



//ѡ��򿪲�ͬ���ӶԻ���
typedef bool(_cdecl *JW2_OPENDIALOG)(CString m_MenuName);

//ѡ����ʾ��ͬ���ӶԻ���
typedef BOOL (_cdecl *JW2_SHOWDIALOG)(CString m_MenuName);

//ѡ�����ͬ���ӶԻ�������Ϣ
typedef void(_cdecl *JW2_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//��Ϣ����
typedef void(_cdecl *JW2_TRANSLATEMESSAGE)(MSG* pMsg);

//���ͽ��յ�����Ϣ(GTOWN)
typedef void(_cdecl *GETJW2MESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//���������·�������
typedef void(_cdecl *JW2_SENDINFOAGAIN)();

//���ͻ���������Ϣ(GTOWN)
typedef void(_cdecl *GETJW2INFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);


//ѡ��򿪲�ͬ���ӶԻ���
typedef bool(_cdecl *WA_OPENDIALOG)(CString m_MenuName);

//ѡ����ʾ��ͬ���ӶԻ���
typedef BOOL (_cdecl *WA_SHOWDIALOG)(CString m_MenuName);

//ѡ�����ͬ���ӶԻ�������Ϣ
typedef void(_cdecl *WA_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//��Ϣ����
typedef void(_cdecl *WA_TRANSLATEMESSAGE)(MSG* pMsg);

//���ͽ��յ�����Ϣ(GTOWN)
typedef void(_cdecl *GETWAMESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//���������·�������
typedef void(_cdecl *WA_SENDINFOAGAIN)();

//���ͻ���������Ϣ(GTOWN)
typedef void(_cdecl *GETWAINFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);


// AGABUNBģ��.
typedef void (*POpenCAGABUNBDlg)(CString m_MenuName);
typedef void (*PInitialize)(SOCKET sock, int nUserID, CString strUserName, HWND hParent, int* nSelectDll);
typedef void (*PSetRecvData)(unsigned char * lpRecvbuf, int m_length, CEnumCore::Message_Tag_ID m_message_tag_id);
typedef void (*PCloseDialog)(LPCTSTR lpDlgName);
typedef void (*PShowGABUNBDlg)(CString DlgName);

//////////////////////////////peng begin
//������� add
//ѡ��򿪲�ͬ���ӶԻ���
typedef bool(_cdecl *XD_OPENDIALOG)(CString m_MenuName);

//ѡ����ʾ��ͬ���ӶԻ���
typedef BOOL (_cdecl *XD_SHOWDIALOG)(CString m_MenuName);

//ѡ�����ͬ���ӶԻ�������Ϣ
typedef HWND(_cdecl *XD_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//��Ϣ����
typedef HWND(_cdecl *XD_TRANSLATEMESSAGE)(MSG* pMsg);

//���ͽ��յ�����Ϣ
typedef HWND(_cdecl *GETXDMESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//���������·�������
typedef HWND(_cdecl *XD_SENDINFOAGAIN)();

//���ͻ���������Ϣ
typedef void(_cdecl *GETXDINFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);

/////////////////////////////peng end
class CGMClientApp : public CWinApp
{
public:
	CGMClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	//�򿪶Ի���
	GM_OPENDIALOG GM_OpenDialog;

	//ѡ����ʾ��ͬ���ӶԻ���
	GM_SHOWDIALOG GM_ShowDialog;

	//�رնԻ���
    GM_DIALOGMSG GM_DialogMsg;

	//���ͽ��յ�����Ϣ
	GETFRAMEMESSAGE GM_Message;

	//���������·�������
	GM_SENDINFOAGAIN GM_SendInfoAgain;

	//���ͻ���������Ϣ
	GETINFO GM_Info;

	//��Ϣ����
	GM_TRANSLATEMESSAGE GM_TranslateMessage;


	//ѡ��򿪲�ͬ���ӶԻ���
	PAL_OPENDIALOG PAL_OpenDialog;

	//ѡ����ʾ��ͬ���ӶԻ���
	PAL_SHOWDIALOG PAL_ShowDialog;

	//ѡ��رղ�ͬ���ӶԻ���
    PAL_DIALOGMSG PAL_DialogMsg;

	//��Ϣ����
	PAL_TRANSLATEMESSAGE PAL_TranslateMessage;

	//���ͽ��յ�����Ϣ(�ɽ�)
	GETPALMESSAGE PAL_Message;

	//���������·�������
	PAL_SENDINFOAGAIN PAL_SendInfoAgagin;

	//���ͻ���������Ϣ(�ɽ�)
	GETPALINFO PAL_Info;



	//ѡ��򿪲�ͬ���ӶԻ���
	GTOWN_OPENDIALOG GTOWN_OpenDialog;

	//ѡ����ʾ��ͬ���ӶԻ���
	GTOWN_SHOWDIALOG GTOWN_ShowDialog;

	//ѡ��رղ�ͬ���ӶԻ���
	GTOWN_DIALOGMSG GTOWN_DialogMsg;

	//��Ϣ����
	GTOWN_TRANSLATEMESSAGE GTOWN_TranslateMessage;

	//���ͽ��յ�����Ϣ(����)
	GETGTOWNMESSAGE GTOWN_Message;

	//���������·�������
	GTOWN_SENDINFOAGAIN GTOWN_SendInfoAgagin;

	//���ͻ���������Ϣ(����)
	GETGTOWNINFO GTOWN_Info;




	//ѡ��򿪲�ͬ���ӶԻ���(CG2)
	CG2_OPENDIALOG CG2_OpenDialog;

	//ѡ����ʾ��ͬ���ӶԻ���
	CG2_SHOWDIALOG CG2_ShowDialog;

	//ѡ��رղ�ͬ���ӶԻ���(CG2)
	CG2_DIALOGMSG CG2_DialogMsg;

	//��Ϣ����(CG2)
	CG2_TRANSLATEMESSAGE CG2_TranslateMessage;

	//���ͽ��յ�����Ϣ(CG2)
	GETCG2MESSAGE CG2_Message;

	//���������·�������(CG2)
	CG2_SENDINFOAGAIN CG2_SendInfoAgagin;

	//���ͻ���������Ϣ(CG2)
	GETCG2INFO CG2_Info;



	//ѡ��򿪲�ͬ���ӶԻ���
	SDO_OPENDIALOG SDO_OpenDialog;

	//ѡ����ʾ��ͬ���ӶԻ���
	SDO_SHOWDIALOG SDO_ShowDialog;

	//ѡ��رղ�ͬ���ӶԻ���
	SDO_DIALOGMSG SDO_DialogMsg;

	//��Ϣ����
	SDO_TRANSLATEMESSAGE SDO_TranslateMessage;

	//���ͽ��յ�����Ϣ(SDO)
	GETSDOMESSAGE SDO_Message;

	//���������·�������
	SDO_SENDINFOAGAIN SDO_SendInfoAgagin;

	//���ͻ���������Ϣ(SDO)
	GETSDOINFO SDO_Info;


	//ѡ��򿪲�ͬ���ӶԻ���
	JW2_OPENDIALOG JW2_OpenDialog;

	//ѡ����ʾ��ͬ���ӶԻ���
	JW2_SHOWDIALOG JW2_ShowDialog;

	//ѡ��رղ�ͬ���ӶԻ���
	JW2_DIALOGMSG JW2_DialogMsg;

	//��Ϣ����
	JW2_TRANSLATEMESSAGE JW2_TranslateMessage;

	//���ͽ��յ�����Ϣ(SDO)
	GETJW2MESSAGE JW2_Message;

	//���������·�������
	JW2_SENDINFOAGAIN JW2_SendInfoAgagin;

	//���ͻ���������Ϣ(SDO)
	GETJW2INFO JW2_Info;


	//ѡ��򿪲�ͬ���ӶԻ���
	WA_OPENDIALOG WA_OpenDialog;

	//ѡ����ʾ��ͬ���ӶԻ���
	WA_SHOWDIALOG WA_ShowDialog;

	//ѡ��رղ�ͬ���ӶԻ���
	WA_DIALOGMSG WA_DialogMsg;

	//��Ϣ����
	WA_TRANSLATEMESSAGE WA_TranslateMessage;

	//���ͽ��յ�����Ϣ(WA)
	GETWAMESSAGE WA_Message;

	//���������·�������
	WA_SENDINFOAGAIN WA_SendInfoAgagin;

	//���ͻ���������Ϣ(WA)
	GETWAINFO WA_Info;


	// CAGABUNB �����ĺ���ָ��.
	POpenCAGABUNBDlg	m_pOpenCAGABUNBDlgFun;
	PInitialize			m_pInitializeCAGABUNBFun;
	PSetRecvData		m_pSetRecvDataFun;
	PCloseDialog		m_pCloseDialogFun;
	PShowGABUNBDlg		m_pShowGABUNBDlgFun;

    ///////////////////////////peng begin
	//ѡ��򿪲�ͬ���ӶԻ���
	XD_OPENDIALOG XD_OpenDialog;

	////ѡ����ʾ��ͬ���ӶԻ���
	XD_SHOWDIALOG XD_ShowDialog;

	//ѡ��رղ�ͬ���ӶԻ���
	XD_DIALOGMSG XD_DialogMsg;

	//��Ϣ����
	XD_TRANSLATEMESSAGE XD_TranslateMessage;

	//���ͽ��յ�����Ϣ()
	GETXDMESSAGE XD_Message;

	//���������·�������
	XD_SENDINFOAGAIN XD_SendInfoAgagin;

	//���ͻ���������Ϣ()
	GETXDINFO XD_Info;
	//////////////////////////peng end

	//ѡ����һ��dll��Query���з���
	int m_SelectDll;

	//�����ظ�����Query�Ĵ���
	int m_SendCount;

	//SOCKET�����Ϣ
	CMySocket m_clientsocket;

	//����ԱID
	int UserByID;

	//����Ա�ʺ�
	CString userName;

	//�Ƿ���Ҫ���ز˵�
	bool menuflag;

	//Ҫ���͵����ݰ�
	CPacketHead packethead;

	//Ҫ���͵����ݳ���
	int packetLength;

	//��̬����dll
	HINSTANCE hinstDLL;

	//�������е�dll
	void LoadAllDll(void);

	//�ͷ����е�dll
	void FreeAllDll(void);

	//�ر���������
	virtual int ExitInstance();
	//�����ļ���Ŀ¼
	bool GetLocalDllFile(char* dllname);
};

extern CGMClientApp theApp;

class Ctabname
{
public:
	static	CString tabname;
};