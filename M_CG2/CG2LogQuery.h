#pragma once

#include "OperationCG2.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"
// CCG2LogQuery 对话框

class CCG2LogQuery : public CDialog
{
	DECLARE_DYNAMIC(CCG2LogQuery)

public:
	CCG2LogQuery(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCG2LogQuery();

// 对话框数据
	enum { IDD = IDD_DLGLOGQUERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

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

	// 玩家ID
	CString UserID;

	// 输入的玩家帐号
	CString UserName;

	// 输入的玩家昵称
	CString UserNick;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

public:
	//游戏服务器组合框
	CComboBox cmbServer;

	//翻页组合框
	CComboBox cmbPage;

	//显示列表框
	CListCtrl listUser;
	CListCtrl listResult;

	//搜索容器
	CStatic GrpSearch;

	//翻页容器
	CStatic GrpPage;

	// 指示对话框当前状态
	int dlgStatus;

	//自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedUisearch();

	void UserInfo();//玩家资料信息

	//关闭对话框
	afx_msg void OnClose();
	afx_msg void OnBnClickedUicancel();

	//CTabCtrl选项卡
	CTabCtrl tbcResult;

	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);//切换tabCtrl

	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);//单击列表框

	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);//双击列表框

	CComboBox cmbCategory;//日志大类

	afx_msg void OnCbnSelchangeCmbcategory();//切换日志大类组合框

	CComboBox cmbAction;//日志小类

	afx_msg void OnBnClickedBtsearch();//日志查询按钮

	CDateTimeCtrl dtcStartDate;//开始日期
	CDateTimeCtrl dtcStartTime;//开始时间

	CDateTimeCtrl dtcEndDate;//开始日期
	CDateTimeCtrl dtcEndTime;//结束时间
};
