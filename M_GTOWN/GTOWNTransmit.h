#pragma once

#include "OperationGTOWN.h"
#include "afxwin.h"
#include "afxcmn.h"

// CGTOWNTransmit 对话框

class CGTOWNTransmit : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNTransmit)

public:
	CGTOWNTransmit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGTOWNTransmit();

	// 对话框数据
	enum { IDD = IDD_DLGTRANSMIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	// 判断是否需要翻页
	bool pageInfo;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	//输入的玩家帐号和角色名
	CString Account, Name;

	// 获得的玩家帐号和角色名
	CString UserAccount, UserName;

	//各个控件的高度
	int grpHeight, grpPHeight;

public:
	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CListCtrl玩家资料信息
	CListCtrl listUser;

	//翻页容器
	CStatic GrpPage;

	//翻页组合框
	CComboBox cmbPage;

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

	// 查询玩家资料信息
	afx_msg void OnBnClickedSearch();

	//翻页查询玩家资料信息
	afx_msg void OnCbnSelchangeCmbpage();

	//单击玩家信息列表保存当前行号
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击玩家资料信息强制玩家下线
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);


	//重置玩家昵称信息
	afx_msg void OnBnClickedBtnreset();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//单击用户资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//选择是否显示相应的控件信息
	void ShowOperCtrl(int n_CmdShow);

	// 关闭对话框
	afx_msg void OnBnClickedCancel();

	//响应WM_CLOSE消息
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtntransmit();
};
