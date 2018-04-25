#pragma once
#include "afxwin.h"


// CGTOWNItemConsume 对话框
class CGTOWNItemConsume : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNItemConsume)

public:
	CGTOWNItemConsume(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGTOWNItemConsume();

	// 对话框数据
	enum { IDD = IDD_DLGITEMCONSUME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断是否需要翻页
	bool pageUInfo;
	bool pageInfo;

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	//输入的玩家帐号和角色名
	CString Account, Name;

	// 获得的玩家帐号和角色名
	CString UserAccount, UserName;

	//玩家角色ID
	int UserID;

	//开始时间
	CString strStartTime;

	//结束时间
	CString strEndTime;

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
	CStatic GrpPage;

	//玩家信息翻页复选框
	CComboBox cmbUPage;

	// CComboBox翻页查询
	CComboBox cmbPage;

	// CListCtrl玩家资料信息
	CListCtrl listUser;

	// CListCtrl结果显示
	CListCtrl listResult;

	//开始时间
	CDateTimeCtrl dtcStartDate;

	//结束时间
	CDateTimeCtrl dtcEndDate;

	//日志类型
	CComboBox cmbType;

	// 指示对话框当前状态
	int dlgStatus;

public:
	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//处理快捷键响应
	virtual BOOL PreTranslateMessage(MSG* pMsg);



	// 查询玩家资料信息
	afx_msg void OnBnClickedSearch();

	//翻页查询角色资料信息
	afx_msg void OnCbnSelchangeCmbupage();

	// 单击用户列表保存当前行号
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击玩家资料信息进行查询
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);



	//道具购买消费记录
	void ItemConsume();

	//切换类型查询道具购买消费记录
	afx_msg void OnCbnSelchangeCmbtype();

	//翻页进行查询
	afx_msg void OnCbnSelchangeCmbpage();



	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//导入道具购买消费类型
	void InitType();

	// 显示角色资料信息
	void ShowUserInfo();

	// 显示其它信息
	void ShowOtherInfo();

	//单击用户资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//单击结果信息的列名进行排序
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//使用关闭按钮
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();	
	afx_msg void OnBnClickedQuery();
	CComboBox cmbUser;
	afx_msg void OnCbnSelchangeCmbuser();
};
