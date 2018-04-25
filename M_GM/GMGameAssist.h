#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using std::vector;
using std::map;
using std::pair;


void CALLBACK CircleGameAssist(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime);

// GMGameAssist 对话框

class GMGameAssist : public CDialog
{
	DECLARE_DYNAMIC(GMGameAssist)

public:
	GMGameAssist(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~GMGameAssist();

// 对话框数据
	enum { IDD = IDD_DLGGAMEASSIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	// 所有游戏信息
	CMap<int,int,int,int> GameList;

	// 相应的服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断是否需要翻页
	bool pageInfo;

	//游戏ID
	int GameID;

	//游戏名称
	CString GameName;

	// 要查询的外挂类型
	int AssitType;

	// 单击外挂信息列表得到行号
	int mItem;

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	// 待封停的玩家帐号
	CString UserAccount;

	// 待封停的玩家角色名
	CString UserName;

	//页数和每页显示的记录条数
	int iIndex,iPageSize;

	//是否启用刷新
	bool iRefresh;

	//刷新时间
	int refreshTime;

	//各个控件的高度
	int grpHeight, tbcHeight, grpPHeight;

	//导出文件路径名
	CString exportFilePath;

	//导入文件路径名
	CString importFilePath;

public:
	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CComboBox游戏名称
	CComboBox cmbGame;

	// CComboBox游戏服务器
	CComboBox cmbServer;

	//CComboBox 外挂类型
	CComboBox cmbAssit;

	// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	// CGroupBox翻页容器
	CStatic GrpPage;

	// CComboBox翻页查询
	CComboBox cmbPage;

	// CListCtrl结果显示
	CListCtrl listResult;

	// CComboBox封停类型
	CComboBox cmbType;

	// 指示对话框当前状态
	int dlgStatus;

	//显示excel导入的帐号信息
	CListCtrl listAccountImport;
	
	//显示excel导入帐号信息中的vip用户
	CListCtrl listVIPAccount;

	//游戏大区对应IP表
	map<CString, CString> ServerCityToServerIP;

	//当前发送的帐号
	CString m_curAccount;

	//当前发送帐号是否为VIP
	BOOL m_isVipAccount;

public:
	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	//处理快捷键响应函数
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//相应定时器函数
	afx_msg void OnTimer(UINT nIDEvent);

	//获取所有的游戏名称
	void QueryGameList();

	//通过游戏名称查询相应的游戏服务器IP
	afx_msg void OnCbnSelchangeCmbgamename();

	//查询游戏外挂信息
	afx_msg void OnBnClickedSearch();

	//修改循环查询的时间间隔
	afx_msg void OnBnClickedBtnstart();

	//查询游戏外挂信息
	void GameAssist();

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbpage();

	// 单击外挂信息列表保存当前行号
	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击外挂信息列表踢玩家下线
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行操作
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);	

	// 封停帐号
	afx_msg void OnBnClickedBtnban();

	// 重置信息
	afx_msg void OnBnClickedBtnreset();

	//导出数据到xls文件  Added by yanfei_qin 2010-9-15
	afx_msg void OnBnClickedBtnExport();
	
	//打开导出文件对话框
	//afx_msg void OnBnClickedOpenFileExport();
	
	//打开导入文件对话框
	//afx_msg void OnBnClickedOpenFileImport();

	//从xls文件导出到clistctrl
	afx_msg void OnBnClickedBtnImport();
	
	//批量封停帐号
	afx_msg void OnBnClickedBtnBanBatch();

	//批量查询帐号是否vip
	afx_msg void OnBnClickedCheckVip();

	//批量查询外挂信息
	afx_msg void OnBnClickedBtnCheckAccountAll();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);


	// 关闭对话框
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();

public:
	//显示外挂信息列表
	void ShowUserInfo(int m_cmdShow);

	//显示封停帐号
	void ShowBanPlayer(int m_cmdShow);	

	//显示导入的封停帐号页面
	void ShowExcelBanPlayer(int m_cmdShow);

public:
	HANDLE m_hCheckVipEvent;
	HANDLE m_hCheckVipThread;

	HANDLE m_hBanAccountEvent;
	HANDLE m_hBanAccountThread;
	
	//封装批量帐号信息
	static DWORD WINAPI sendBanAccountList(LPVOID pClsParam);
	static DWORD WINAPI GMGameAssist::sendVIPAccountRequest(LPVOID pClsParam); 
public:
	
};
