// GMClient.h : GMClient 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h” 
#endif

#include "resource.h"       // 主符号
#include "MySocket.h"
#include "Login.h"


// CGMClientApp:
// 有关此类的实现，请参阅 GMClient.cpp
//

//打开对话框
typedef bool(_cdecl *GM_OPENDIALOG)(CString m_MenuName);

//选择显示不同的子对话框
typedef BOOL (_cdecl *GM_SHOWDIALOG)(CString m_MenuName);

//关闭对话框
typedef HWND(_cdecl *GM_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//发送接收到的信息
typedef HWND(_cdecl *GETFRAMEMESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//向服务端重新发送请求
typedef HWND(_cdecl *GM_SENDINFOAGAIN)();

//发送基本资料信息
typedef HWND(_cdecl *GETINFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);

//消息传递
typedef HWND(_cdecl *GM_TRANSLATEMESSAGE)(MSG* pMsg);



//选择打开不同的子对话框
typedef bool(_cdecl *PAL_OPENDIALOG)(CString m_MenuName);

//选择显示不同的子对话框
typedef BOOL (_cdecl *PAL_SHOWDIALOG)(CString m_MenuName);

//选择关闭不同的子对话框
typedef HWND(_cdecl *PAL_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//消息传递
typedef HWND (_cdecl *PAL_TRANSLATEMESSAGE)(MSG* pMsg);

//发送接收到的信息(仙剑)
typedef HWND(_cdecl *GETPALMESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//向服务端重新发送请求
typedef HWND(_cdecl *PAL_SENDINFOAGAIN)();

//发送基本资料信息(仙剑)
typedef HWND(_cdecl *GETPALINFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);



//GTOWN maple add
//选择打开不同的子对话框
typedef bool(_cdecl *GTOWN_OPENDIALOG)(CString m_MenuName);

//选择显示不同的子对话框
typedef BOOL (_cdecl *GTOWN_SHOWDIALOG)(CString m_MenuName);

//选择给不同的子对话框发送消息
typedef HWND(_cdecl *GTOWN_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//消息传递
typedef HWND(_cdecl *GTOWN_TRANSLATEMESSAGE)(MSG* pMsg);

//发送接收到的信息(GTOWN)
typedef HWND(_cdecl *GETGTOWNMESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//向服务端重新发送请求
typedef HWND(_cdecl *GTOWN_SENDINFOAGAIN)();

//发送基本资料信息(GTOWN)
typedef HWND(_cdecl *GETGTOWNINFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);




//选择打开不同的子对话框(CG2)
typedef bool (_cdecl *CG2_OPENDIALOG)(CString m_MenuName);

//选择显示不同的子对话框
typedef BOOL (_cdecl *CG2_SHOWDIALOG)(CString m_MenuName);

//选择关闭不同的子对话框(CG2)
typedef void (_cdecl *CG2_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//消息传递(CG2)
typedef bool(_cdecl *CG2_TRANSLATEMESSAGE)(MSG* pMsg);

//发送接收到的信息(CG2)
typedef void(_cdecl *GETCG2MESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//向服务端重新发送请求(CG2)
typedef void(_cdecl *CG2_SENDINFOAGAIN)();

//发送基本资料信息(CG2)
typedef void(_cdecl *GETCG2INFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);


//maple add
//选择打开不同的子对话框
typedef bool(_cdecl *SDO_OPENDIALOG)(CString m_MenuName);

//选择显示不同的子对话框
typedef BOOL (_cdecl *SDO_SHOWDIALOG)(CString m_MenuName);

//选择给不同的子对话框发送消息
typedef HWND(_cdecl *SDO_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//消息传递
typedef HWND(_cdecl *SDO_TRANSLATEMESSAGE)(MSG* pMsg);

//发送接收到的信息(GTOWN)
typedef HWND(_cdecl *GETSDOMESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//向服务端重新发送请求
typedef HWND(_cdecl *SDO_SENDINFOAGAIN)();

//发送基本资料信息(GTOWN)
typedef HWND(_cdecl *GETSDOINFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);



//选择打开不同的子对话框
typedef bool(_cdecl *JW2_OPENDIALOG)(CString m_MenuName);

//选择显示不同的子对话框
typedef BOOL (_cdecl *JW2_SHOWDIALOG)(CString m_MenuName);

//选择给不同的子对话框发送消息
typedef void(_cdecl *JW2_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//消息传递
typedef void(_cdecl *JW2_TRANSLATEMESSAGE)(MSG* pMsg);

//发送接收到的信息(GTOWN)
typedef void(_cdecl *GETJW2MESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//向服务端重新发送请求
typedef void(_cdecl *JW2_SENDINFOAGAIN)();

//发送基本资料信息(GTOWN)
typedef void(_cdecl *GETJW2INFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);


//选择打开不同的子对话框
typedef bool(_cdecl *WA_OPENDIALOG)(CString m_MenuName);

//选择显示不同的子对话框
typedef BOOL (_cdecl *WA_SHOWDIALOG)(CString m_MenuName);

//选择给不同的子对话框发送消息
typedef void(_cdecl *WA_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//消息传递
typedef void(_cdecl *WA_TRANSLATEMESSAGE)(MSG* pMsg);

//发送接收到的信息(GTOWN)
typedef void(_cdecl *GETWAMESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//向服务端重新发送请求
typedef void(_cdecl *WA_SENDINFOAGAIN)();

//发送基本资料信息(GTOWN)
typedef void(_cdecl *GETWAINFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);


// AGABUNB模块.
typedef void (*POpenCAGABUNBDlg)(CString m_MenuName);
typedef void (*PInitialize)(SOCKET sock, int nUserID, CString strUserName, HWND hParent, int* nSelectDll);
typedef void (*PSetRecvData)(unsigned char * lpRecvbuf, int m_length, CEnumCore::Message_Tag_ID m_message_tag_id);
typedef void (*PCloseDialog)(LPCTSTR lpDlgName);
typedef void (*PShowGABUNBDlg)(CString DlgName);

//////////////////////////////peng begin
//侠盗金刚 add
//选择打开不同的子对话框
typedef bool(_cdecl *XD_OPENDIALOG)(CString m_MenuName);

//选择显示不同的子对话框
typedef BOOL (_cdecl *XD_SHOWDIALOG)(CString m_MenuName);

//选择给不同的子对话框发送消息
typedef HWND(_cdecl *XD_DIALOGMSG)(CString m_MenuName, UINT Msg, WPARAM wParam, LPARAM lParam);

//消息传递
typedef HWND(_cdecl *XD_TRANSLATEMESSAGE)(MSG* pMsg);

//发送接收到的信息
typedef HWND(_cdecl *GETXDMESSAGE)(unsigned char * lpRecvbuf,int m_length,CEnumCore::Message_Tag_ID m_message_tag_id,CGlobalStruct::PACKETHEAD m_packethead);

//向服务端重新发送请求
typedef HWND(_cdecl *XD_SENDINFOAGAIN)();

//发送基本资料信息
typedef void(_cdecl *GETXDINFO)(SOCKET m_socket, int userByID, CString userName, HWND m_HwndParent,int* m_SelectDll);

/////////////////////////////peng end
class CGMClientApp : public CWinApp
{
public:
	CGMClientApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	//打开对话框
	GM_OPENDIALOG GM_OpenDialog;

	//选择显示不同的子对话框
	GM_SHOWDIALOG GM_ShowDialog;

	//关闭对话框
    GM_DIALOGMSG GM_DialogMsg;

	//发送接收到的信息
	GETFRAMEMESSAGE GM_Message;

	//向服务端重新发送请求
	GM_SENDINFOAGAIN GM_SendInfoAgain;

	//发送基本资料信息
	GETINFO GM_Info;

	//消息传递
	GM_TRANSLATEMESSAGE GM_TranslateMessage;


	//选择打开不同的子对话框
	PAL_OPENDIALOG PAL_OpenDialog;

	//选择显示不同的子对话框
	PAL_SHOWDIALOG PAL_ShowDialog;

	//选择关闭不同的子对话框
    PAL_DIALOGMSG PAL_DialogMsg;

	//消息传递
	PAL_TRANSLATEMESSAGE PAL_TranslateMessage;

	//发送接收到的信息(仙剑)
	GETPALMESSAGE PAL_Message;

	//向服务端重新发送请求
	PAL_SENDINFOAGAIN PAL_SendInfoAgagin;

	//发送基本资料信息(仙剑)
	GETPALINFO PAL_Info;



	//选择打开不同的子对话框
	GTOWN_OPENDIALOG GTOWN_OpenDialog;

	//选择显示不同的子对话框
	GTOWN_SHOWDIALOG GTOWN_ShowDialog;

	//选择关闭不同的子对话框
	GTOWN_DIALOGMSG GTOWN_DialogMsg;

	//消息传递
	GTOWN_TRANSLATEMESSAGE GTOWN_TranslateMessage;

	//发送接收到的信息(吉堂)
	GETGTOWNMESSAGE GTOWN_Message;

	//向服务端重新发送请求
	GTOWN_SENDINFOAGAIN GTOWN_SendInfoAgagin;

	//发送基本资料信息(吉堂)
	GETGTOWNINFO GTOWN_Info;




	//选择打开不同的子对话框(CG2)
	CG2_OPENDIALOG CG2_OpenDialog;

	//选择显示不同的子对话框
	CG2_SHOWDIALOG CG2_ShowDialog;

	//选择关闭不同的子对话框(CG2)
	CG2_DIALOGMSG CG2_DialogMsg;

	//消息传递(CG2)
	CG2_TRANSLATEMESSAGE CG2_TranslateMessage;

	//发送接收到的信息(CG2)
	GETCG2MESSAGE CG2_Message;

	//向服务端重新发送请求(CG2)
	CG2_SENDINFOAGAIN CG2_SendInfoAgagin;

	//发送基本资料信息(CG2)
	GETCG2INFO CG2_Info;



	//选择打开不同的子对话框
	SDO_OPENDIALOG SDO_OpenDialog;

	//选择显示不同的子对话框
	SDO_SHOWDIALOG SDO_ShowDialog;

	//选择关闭不同的子对话框
	SDO_DIALOGMSG SDO_DialogMsg;

	//消息传递
	SDO_TRANSLATEMESSAGE SDO_TranslateMessage;

	//发送接收到的信息(SDO)
	GETSDOMESSAGE SDO_Message;

	//向服务端重新发送请求
	SDO_SENDINFOAGAIN SDO_SendInfoAgagin;

	//发送基本资料信息(SDO)
	GETSDOINFO SDO_Info;


	//选择打开不同的子对话框
	JW2_OPENDIALOG JW2_OpenDialog;

	//选择显示不同的子对话框
	JW2_SHOWDIALOG JW2_ShowDialog;

	//选择关闭不同的子对话框
	JW2_DIALOGMSG JW2_DialogMsg;

	//消息传递
	JW2_TRANSLATEMESSAGE JW2_TranslateMessage;

	//发送接收到的信息(SDO)
	GETJW2MESSAGE JW2_Message;

	//向服务端重新发送请求
	JW2_SENDINFOAGAIN JW2_SendInfoAgagin;

	//发送基本资料信息(SDO)
	GETJW2INFO JW2_Info;


	//选择打开不同的子对话框
	WA_OPENDIALOG WA_OpenDialog;

	//选择显示不同的子对话框
	WA_SHOWDIALOG WA_ShowDialog;

	//选择关闭不同的子对话框
	WA_DIALOGMSG WA_DialogMsg;

	//消息传递
	WA_TRANSLATEMESSAGE WA_TranslateMessage;

	//发送接收到的信息(WA)
	GETWAMESSAGE WA_Message;

	//向服务端重新发送请求
	WA_SENDINFOAGAIN WA_SendInfoAgagin;

	//发送基本资料信息(WA)
	GETWAINFO WA_Info;


	// CAGABUNB 导出的函数指针.
	POpenCAGABUNBDlg	m_pOpenCAGABUNBDlgFun;
	PInitialize			m_pInitializeCAGABUNBFun;
	PSetRecvData		m_pSetRecvDataFun;
	PCloseDialog		m_pCloseDialogFun;
	PShowGABUNBDlg		m_pShowGABUNBDlgFun;

    ///////////////////////////peng begin
	//选择打开不同的子对话框
	XD_OPENDIALOG XD_OpenDialog;

	////选择显示不同的子对话框
	XD_SHOWDIALOG XD_ShowDialog;

	//选择关闭不同的子对话框
	XD_DIALOGMSG XD_DialogMsg;

	//消息传递
	XD_TRANSLATEMESSAGE XD_TranslateMessage;

	//发送接收到的信息()
	GETXDMESSAGE XD_Message;

	//向服务端重新发送请求
	XD_SENDINFOAGAIN XD_SendInfoAgagin;

	//发送基本资料信息()
	GETXDINFO XD_Info;
	//////////////////////////peng end

	//选择哪一个dll的Query进行发送
	int m_SelectDll;

	//保存重复发送Query的次数
	int m_SendCount;

	//SOCKET相关信息
	CMySocket m_clientsocket;

	//操作员ID
	int UserByID;

	//操作员帐号
	CString userName;

	//是否需要加载菜单
	bool menuflag;

	//要发送的数据包
	CPacketHead packethead;

	//要发送的数据长度
	int packetLength;

	//动态加载dll
	HINSTANCE hinstDLL;

	//加载所有的dll
	void LoadAllDll(void);

	//释放所有的dll
	void FreeAllDll(void);

	//关闭整个进程
	virtual int ExitInstance();
	//查找文件夹目录
	bool GetLocalDllFile(char* dllname);
};

extern CGMClientApp theApp;

class Ctabname
{
public:
	static	CString tabname;
};