#pragma once


// CXDCharLog 对话框

class CXDCharLog : public CDialog
{
	DECLARE_DYNAMIC(CXDCharLog)

public:
	CXDCharLog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXDCharLog();

// 对话框数据
	enum { IDD = IDD_DLGCHARLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:

	// 单击基本信息列表得到行号
	int nItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断基本列表是否需要翻页
	bool pageBasic;

	// 判断是否需要翻页
	bool pageResult;	

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

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 关闭对话框
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();			

	//全选、复制
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//单击基本资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListbasic(NMHDR *pNMHDR, LRESULT *pResult);

	//单击结果信息的列名进行排序
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);
};
