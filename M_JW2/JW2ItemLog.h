#pragma once

#include "OperationJW2.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"

// CJW2ItemLog 对话框

class CJW2ItemLog : public CDialog
{
	DECLARE_DYNAMIC(CJW2ItemLog)

public:
	CJW2ItemLog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJW2ItemLog();

// 对话框数据
	enum { IDD = IDD_DLGITEMLOG };

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

	//游戏服务器Name
	CString ServerName;

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

	//查询购物送礼记录的类型
	int iType;

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

	// CListCtrl结果显示
	CListCtrl listResult;

	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CGroupBox翻页容器
	CStatic GrpPage;

	//CComboBox购物送礼类型
	CComboBox cmbType;

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

	// 查询婚姻信息
	void ItemLog();



	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbuipage();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//单击用户资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//单击结果信息的列名进行排序
	afx_msg void OnLvnColumnclickListcharacter(NMHDR *pNMHDR, LRESULT *pResult);

	// 关闭对话框
	afx_msg void OnBnClickedUicancel();

	// 关闭对话框
	afx_msg void OnClose();			

	CDateTimeCtrl dtcLoginDate;
	CDateTimeCtrl dtcLogoutDate;
};
