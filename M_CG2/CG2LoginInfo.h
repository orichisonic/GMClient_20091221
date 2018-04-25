#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CCG2LoginInfo 对话框

class CCG2LoginInfo : public CDialog
{
	DECLARE_DYNAMIC(CCG2LoginInfo)

public:
	CCG2LoginInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCG2LoginInfo();

// 对话框数据
	enum { IDD = IDD_DLGLOGININFO };

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

	// 游戏服务器IP
	CString ServerIP;

	// 玩家帐号
	CString UserAccount;

	// 玩家ID
	int UserID;

	// 输入的玩家帐号
	CString UserName;

	// 输入的玩家昵称
	CString UserNick;

	//各个控件的高度
	int grpHeight, grpPHeight;

public:
	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CComboBox翻页查询
	CComboBox cmbPage;

	// CListCtrl结果显示
	CListCtrl listResult;

	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CGroupBox翻页容器
	CStatic GrpPage;

	// 指示对话框当前状态
	int dlgStatus;


	// CDateTimeCtrl日期
	CDateTimeCtrl dtcLoginDate;
	CDateTimeCtrl dtcLogoutDate;

	// CDateTimeCtrl时间
	CDateTimeCtrl dtcLoginTime;
	CDateTimeCtrl dtcLogoutTime;

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

	// 查询玩家登陆信息
	void LoginInfo();

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbkppage();

	// 双击玩家资料信息进行踢人
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 关闭对话框	
	afx_msg void OnBnClickedUicancel();

	// 关闭对话框
	afx_msg void OnClose();
};
