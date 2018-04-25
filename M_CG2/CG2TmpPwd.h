#pragma once

#include "OperationCG2.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"
// CCG2TmpPwd 对话框

class CCG2TmpPwd : public CDialog
{
	DECLARE_DYNAMIC(CCG2TmpPwd)

public:
	CCG2TmpPwd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCG2TmpPwd();

// 对话框数据
	enum { IDD = IDD_DLGTMPPWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 初始化显示字符
	void InitUI();

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

	CString ServerName;

	// 玩家ID
	CString UserID;

	// 输入的玩家帐号
	CString UserName;

	// 输入的玩家昵称
	CString UserNick;

	//玩家角色的职业id
	CString UserJob;
	
	//玩家角色号
	int iCharNo;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;
public:
	//游戏服务器组合框
	CComboBox cmbServer;

	//翻页组合框
	CComboBox cmbPage;

	//显示列表框
	CListCtrl listUser;

	//搜索容器
	CStatic GrpSearch;

	//翻页容器
	CStatic GrpPage;

	// 指示对话框当前状态
	int dlgStatus;

	//初始化对话框
	virtual BOOL OnInitDialog();
	
	//关闭对话框
	afx_msg void OnClose();
	afx_msg void OnBnClickedUicancel();

	// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	//自动调节窗口
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	void UserInfo();//玩家资料信息

	afx_msg void OnBnClickedUisearch();//点击查询按钮
	
	//切换tabCtrl
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);
	
	// 单击用户列表保存当前行号
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);
	
	// 双击玩家资料信息进行查询
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);


	//修改按钮
	afx_msg void OnBnClickedBtupdate();
	//重置按钮
	afx_msg void OnBnClickedBtreset();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtseetmppwd();
};
