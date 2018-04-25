#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"


// CGMOperationLog 对话框

class CGMOperationLog : public CDialog
{
	DECLARE_DYNAMIC(CGMOperationLog)

public:
	CGMOperationLog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGMOperationLog();

// 对话框数据
	enum { IDD = IDD_DLGGMLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 所有游戏信息
	CMap<int,int,int,int> GameList;

	// 相应的服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 相应的玩家信息
	CMap<int,int,int,int> UserList;

	// 判断是否需要翻页
	bool pageInfo;

	//游戏ID
	int GameID;

	//游戏名称
	CString GameName;

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	// 得到的玩家真实姓名
	CString UserName;

	// 得到的玩家ID
	int UserID;

	//各个控件的高度
	int grpHeight, grpPHeight;

	//开始时间
	CString strStartTime;

	//结束时间
	CString strEndTime;

public:
	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CComboBox游戏名称
	CComboBox cmbGame;

	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CDateTimeCtrl开始时间
	CDateTimeCtrl dtcStartTime;

	// CDateTimeCtrl结束时间
	CDateTimeCtrl dtcEndTime;

	//CComboBox GM真实姓名
	CComboBox cmbRealName;

	// CGroupBox翻页容器
	CStatic GrpPage;

	// CComboBox翻页查询
	CComboBox cmbPage;

	// CListCtrl结果显示
	CListCtrl listResult;

	// 指示对话框当前状态
	int dlgStatus;

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

	//获取所有的用户名称
	void QueryUserList();

	//获取所有的游戏名称
	void QueryGameList();

	//通过游戏名称查询相应的游戏服务器IP
	afx_msg void OnCbnSelchangeCmbgamename();

	// 查询GM操作日志
	afx_msg void OnBnClickedSearch();

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbpage();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 关闭对话框
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();
};
