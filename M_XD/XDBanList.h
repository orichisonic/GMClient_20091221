#pragma once


// CXDBanList 对话框

class CXDBanList : public CDialog
{
	DECLARE_DYNAMIC(CXDBanList)

public:
	CXDBanList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXDBanList();

// 对话框数据
	enum { IDD = IDD_DLGBANLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断结果列表是否需要翻页
	bool pageResult;

	// 游戏服务器IP
	CString ServerIP;

	// 玩家帐号
	CString UserName;

	//各个控件的高度
	int grpHeight, grpPHeight;

public:
	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CComboBox翻页查询
	CComboBox cmbPage;

	// CListCtrl结果显示
	CListCtrl listResult;

	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CGroupBox翻页容器
	CStatic GrpPage;

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
	afx_msg void OnCbnSelchangeCmbpage();	

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 清空页面
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();			

	//全选、复制
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//单击结果信息的列名进行排序
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);
};
