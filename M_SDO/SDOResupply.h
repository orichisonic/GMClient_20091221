#pragma once
#include "afxwin.h"


// CSDOResupply 对话框

class CSDOResupply : public CDialog
{
	DECLARE_DYNAMIC(CSDOResupply)

public:
	CSDOResupply(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSDOResupply();

// 对话框数据
	enum { IDD = IDD_DLGRESUPPLY };

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

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	//输入的玩家帐号和角色名
//	CString Account, Name;

	// 获得的玩家帐号和角色名
	CString UserAccount, UserName;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

	//玩家ID
	int UserID;


public:
	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CComboBox游戏服务器
	CComboBox cmbServer;

	// 指示对话框当前状态
	int dlgStatus;

	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// 关闭对话框
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();

	//搜索玩家G币
	afx_msg void OnBnClickedSearch();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//补发G币金额
	afx_msg void OnBnClickedBtadd();
};
