#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPALSendCustomerItem 对话框

class CPALSendCustomerItem : public CDialog
{
	DECLARE_DYNAMIC(CPALSendCustomerItem)

public:
	CPALSendCustomerItem(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPALSendCustomerItem();

// 对话框数据
	enum { IDD = IDD_DLGSENDCUSTOMERITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	// 单击道具列表得到行号
	//int nSelectItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 所有大类信息
	CMap<int,int,int,int> BigTypeList;

	// 所有小类信息
	CMap<int,int,int,int> ItemNameList;

	// 判断是否需要翻页
	bool pageInfo;

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	// 输入的玩家帐号
	CString UserAccount;

	// 输入的玩家角色名
	CString UserName;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	// CGroupBox翻页容器
	//CStatic GrpPage;

	// CComboBox翻页查询
	//CComboBox cmbPage;

	// CListCtrl玩家资料信息
	CListCtrl listUser;

	// 指示对话框当前状态
	int dlgStatus;

	//道具名称
	CComboBox cmbItemName;

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

	// 单击用户列表保存当前行号
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 关闭对话框
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();

public:

		// 显示角色资料信息
		void ShowUserInfo(void);

		// 显示其它信息
		void ShowOtherInfo(void);

		//道具名称查询
		void ItemNameQuery();

		//设为绑定
		CButton checkBind;

		//维持原样版设定
		CButton checkNotBind;

		//是否使用玄石设定
		CButton checkStone;
		afx_msg void OnBnClickedCheckbind();
		afx_msg void OnBnClickedChecknotbind();
		afx_msg void OnBnClickedCheckstone();
		afx_msg void OnBnClickedBtnsend();
		afx_msg void OnBnClickedBtqueiryitem();
};
