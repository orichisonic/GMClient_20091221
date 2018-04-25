#pragma once


// CWABanList 对话框

class CWABanList : public CDialog
{
	DECLARE_DYNAMIC(CWABanList)

public:
	CWABanList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWABanList();

// 对话框数据
	enum { IDD = IDD_DLGBANLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击帐号封停列表得到行号
	int mItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断是否需要翻页
	bool pageInfo;

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	//要查询的玩家帐号
	CString UserName;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CGroupBox翻页容器
	CStatic GrpPage;

	// CComboBox翻页查询
	CComboBox cmbPage;

	// CListCtrl结果显示
	CListCtrl listResult;

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

	// 查询封停帐号列表
	afx_msg void OnBnClickedSearch();

	// 查询所有被封停帐号列表信息
	void AllBanUserList();

	// 查询特定玩家帐号的封停信息
	void BanInfo();

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbpage();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 关闭对话框
	afx_msg void OnClose();	

	//处理快捷键响应函数
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
