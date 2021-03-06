#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CXDMailLog 对话框

class CXDMailLog : public CDialog
{
	DECLARE_DYNAMIC(CXDMailLog)

public:
	CXDMailLog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXDMailLog();

// 对话框数据
	enum { IDD = IDD_DLGMAILLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:

	// 单击基本信息列表得到行号
	int nItem;

	//单击结果信息列表得到行号
	int mItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断基本列表是否需要翻页
	bool pageBasic;

	// 判断结果列表是否需要翻页
	bool pageResult;

	// 判断详细列表是否需要翻页
	bool pageDetail;

	// 游戏服务器IP
	CString ServerIP;

	// 玩家ID
	CString UserID;

	// 输入的玩家帐号
	CString UserName;

	// 输入的玩家昵称
	CString UserNick;

	//日志开始时间
	CString BeginTime;

	//日志结束时间
	CString EndTime;

	//查询的日志类型
	CString LogType;

	//道具ID
	CString ItemID;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	// CComboBoxl基本信息翻页查询
	CComboBox cmbBasic;

	// CComboBox翻页查询
	CComboBox cmbResult;

	// CListCtrl基本资料信息
	CListCtrl listBasic;

	//CComboBox日志类型
	CComboBox cmbLogType;

	// CListCtrl结果显示
	CListCtrl listResult;

	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CGroupBox翻页容器
	CStatic GrpPage;

	//CDateTimeCtrl开始时间
	CDateTimeCtrl dtcStartTime;

	//CDateTimeCtrl结束时间
	CDateTimeCtrl dtcEndTime;

	// CComboBox翻页查询
	CComboBox cmbDetail;

	//CListCtrl详细信息
	CListCtrl listDetail;

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

	// 查询基本资料信息
	afx_msg void OnBnClickedSearch();

	// 查询基本资料信息
	void BasicInfo();

	// 翻页查询基本资料信息
	afx_msg void OnCbnSelchangeCmbbasic();

	// 单击基本资料信息保存当前行号
	afx_msg void OnNMClickListbasic(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击基本资料信息进行查询
	afx_msg void OnNMDblclkListbasic(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//查询用户佣兵团日志
	afx_msg void OnBnClickedBtnlog();

	//查询相关日志信息
	void ResultLog();

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbresult();

	// 单击结果资料信息保存当前行号
	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击结果资料信息进行查询
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//查询详细资料信息
	void DetailInfo();

	//翻页查询详细资料信息
	afx_msg void OnCbnSelchangeCmbdetail();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 关闭对话框
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();			

	//全选、复制
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//基本资料信息页面
	void ShowBasicInfo(int m_cmdShow);

	//结果资料信息页面
	void ShowResultInfo(int m_cmdShow);

	//详细资料信息页面
	void ShowDetailInfo(int m_cmdShow);

	//单击基本资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListbasic(NMHDR *pNMHDR, LRESULT *pResult);

	//单击结果信息的列名进行排序
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//单击详细信息的列名进行排序
	afx_msg void OnLvnColumnclickListdetail(NMHDR *pNMHDR, LRESULT *pResult);	

	//获取一列中所有相同TagName的字符串
	CString GetFullItemName(CListCtrl* listCtrlS, int nIndex, CString ColName);
};
