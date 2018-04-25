#pragma once

#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"

// CWAUserLog 对话框

class CWAUserLog : public CDialog
{
	DECLARE_DYNAMIC(CWAUserLog)

public:
	CWAUserLog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWAUserLog();

// 对话框数据
	enum { IDD = IDD_DLGUSERLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断是否需要翻页
	bool pageInfo;

	// 判断用户列表是否需要翻页
	bool pageUInfo;

	// 游戏服务器IP
	CString ServerIP;

	// 玩家ID
	CString UserID;

	// 输入的玩家帐号
	CString UserName;

	// 输入的玩家昵称
	CString UserNick;

	//日志开始时间
	CString BeginTime;

	//日志结束时间
	CString EndTime;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	// CComboBox玩家角色信息翻页查询
	CComboBox cmbUPage;

	// CComboBox翻页查询
	CComboBox cmbPage;

	// CListCtrl玩家资料信息
	CListCtrl listUser;

	//CComboBox日志类型
	CComboBox cmbLogType;

	// CListCtrl结果显示
	CListCtrl listResult;

	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CGroupBox翻页容器
	CStatic GrpPage;

	//CDateTimeCtrl开始时间
	CDateTimeCtrl dtcStartTime;

	//CDateTimeCtrl结束时间
	CDateTimeCtrl dtcEndTime;

	// 指示对话框当前状态
	int dlgStatus;

public:
	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// 查询玩家资料信息
	afx_msg void OnBnClickedUisearch();

	// 翻页查询玩家资料信息
	afx_msg void OnCbnSelchangeCmbuserpage();

	// 单击玩家资料信息保存当前行号
	afx_msg void OnNMClickListcharacter(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击玩家资料信息进行查询
	afx_msg void OnNMDblclkListcharacter(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 查询玩家资料信息
	void UserInfo();

	//查询角色物品日志
	afx_msg void OnBnClickedBtnlog();

	//角色用户日志
	void CharUserLog(CString logType);

	//切换日志类型进行查询
	//afx_msg void OnCbnSelchangeCmblogtype();	

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbuipage();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 关闭对话框
	afx_msg void OnBnClickedUicancel();

	// 关闭对话框
	afx_msg void OnClose();			

	//全选、复制
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
