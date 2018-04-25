#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"


// CPALAccountLogin 对话框

class CPALAccountLogin : public CDialog
{
	DECLARE_DYNAMIC(CPALAccountLogin)

public:
	CPALAccountLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPALAccountLogin();

// 对话框数据
	enum { IDD = IDD_DLGLOGINLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断是否需要翻页
	bool pageInfo;

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	// 输入的玩家帐号
	CString UserAccount;

	// 输入的玩家IP
	CString UserIP;

	//各个控件的高度
	int grpHeight, grpPHeight;

	//开始时间
	CString strStartTime;

	//结束时间
	CString strEndTime;

public:
	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CButton通过帐号查询
	CButton checkByAccount;

	// CButton通过IP查询
	CButton checkByIP;

	// CDateTimeCtrl开始时间
	CDateTimeCtrl dtcStartTime;

	// CDateTimeCtrl结束时间
	CDateTimeCtrl dtcEndTime;

	// CGroupBox翻页容器
	CStatic GrpPage;

	// CComboBox翻页查询
	CComboBox cmbPage;

	// CListCtrl结果显示
	CListCtrl listResult;

	// CIPAddressCtrl玩家IP
	CIPAddressCtrl IPACtrl_UserIP;

	// 指示对话框当前状态
	int dlgStatus;

public:
	// 初始化对话框
	virtual BOOL OnInitDialog();

	//处理快捷键响应函数
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	// 初始化显示字符
	void InitUI();

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// 设置通过帐号来查询
	afx_msg void OnBnClickedCheckbyaccount();

	// 设置通过IP来查询
	afx_msg void OnBnClickedCheckbyip();

	// 查询玩家登录日志信息
	afx_msg void OnBnClickedSearch();

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbpage();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//单击用户资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 关闭对话框
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();

public:

	//显示通过帐号查询的信息
	void ShowCheckByAccount(void);

	//显示通过IP查询的信息
	void ShowCheckByIP(void);	
	CComboBox cmbType;
};
