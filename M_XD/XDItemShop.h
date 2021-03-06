#pragma once


// CXDItemShop 对话框

class CXDItemShop : public CDialog
{
	DECLARE_DYNAMIC(CXDItemShop)

public:
	CXDItemShop(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXDItemShop();

// 对话框数据
	enum { IDD = IDD_DLGITEMSHOP };

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

	// 玩家帐号
	CString UserName;

	// 玩家昵称
	CString UserNick;

	//开始时间
	CString BeginTime;

	//结束时间
	CString EndTime;

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

	//按赠送人查询
	CButton checkSender;

	//按受赠人查询
	CButton checkReceiver;

	// 指示对话框当前状态
	int dlgStatus;

	//按照赠送人还是受赠人进行查询
	int userType;

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

	//按照赠送人信息查询
	afx_msg void OnBnClickedChecksender();	

	//按照受赠人信息查询
	afx_msg void OnBnClickedCheckreceiver();

	//查询相关资料信息
	void ResultInfo();
	
	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbresult();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 清空页面
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();			

	//全选、复制
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//基本资料信息页面
	void ShowBasicInfo(int m_cmdShow);

	//结果资料信息页面
	void ShowResultInfo(int m_cmdShow);
};
