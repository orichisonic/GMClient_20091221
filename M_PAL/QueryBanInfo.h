#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CQueryBanInfo 对话框

class CQueryBanInfo : public CDialog
{
	DECLARE_DYNAMIC(CQueryBanInfo)

public:
	CQueryBanInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQueryBanInfo();

// 对话框数据
	enum { IDD = IDD_DLGQUERYBAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	// 输入的玩家帐号
	CString UserAccount;

	//各个控件的高度
	int grpHeight;

public:
	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CListCtrl结果显示
	CListCtrl listResult;

	// CEdit玩家帐号
	CEdit txtAccount;

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

	// 查询资料信息
	afx_msg void OnBnClickedSearch();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//单击用户封停信息的列名进行排序
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 关闭对话框	
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();
};
