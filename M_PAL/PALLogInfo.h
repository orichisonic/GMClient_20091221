#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"


// CPALLogInfo 对话框

class CPALLogInfo : public CDialog
{
	DECLARE_DYNAMIC(CPALLogInfo)

public:
	CPALLogInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPALLogInfo();

// 对话框数据
	enum { IDD = IDD_DLGLOGINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	// 单击用户列表得到行号
	int nItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 所有大类信息
	CMap<int,int,int,int> BigTypeID;

	// 相应的小类信息
	CMap<int,int,int,int> SmallTypeID;

	// 判断是否需要翻页
	bool pageInfo;

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	// 玩家帐号
	CString UserAccount;

	// 玩家角色名
	CString UserName;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

	//日志大类
	CString BigType;

	//日志大类ID
	int bTypeID;

	//日志小类
	CString SmallType;

	//日志小类ID
	int sTypeID;

	//开始时间
	CString strStartTime;

	//结束时间
	CString strEndTime;
public:
	// CComboBox游戏服务器列表
	CComboBox cmbServer;

	// CTabCtrl查询结果选择
	CTabCtrl tbcResult;

	// CComboBox日志大类
	CComboBox cmbBigType;

	// CComboBox日志小类
	CComboBox cmbSmallType;

	// CDateTimeCtrl日志开始时间	
	CDateTimeCtrl dtcStartDate;	

	// CDateTimeCtrl日志结束时间
	CDateTimeCtrl dtcEndDate;

	// CComboBox日志翻页
	CComboBox cmbPage;

	// CListCtrl日志信息列表
	CListCtrl listResult;

	// CListCtrl用户资料信息列表
	CListCtrl listUser;

	// GroupBox搜索条件
	CStatic GrpSearch;

	// GroupBox翻页信息
	CStatic GrpPage;

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

	// 单击玩家资料信息保存当前行号
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击玩家资料信息进行切换
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//获取所有大类信息
	void GetAllBigType();

	// 选择大类查询小类
	afx_msg void OnCbnSelchangeCmbbigtype();

	// 查询日志信息
	afx_msg void OnBnClickedBtnsearchlog();

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbpage();

	//单击用户信息进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//单击日志列表信息进行排序
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//显示用户信息界面
	void ShowUserInfo();

	//显示日志信息界面
	void ShowLogInfo();	
	
	// 关闭对话框
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();
};
