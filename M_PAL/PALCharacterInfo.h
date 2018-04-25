#pragma once


// CPALCharacterInfo 对话框

class CPALCharacterInfo : public CDialog
{
	DECLARE_DYNAMIC(CPALCharacterInfo)

public:
	CPALCharacterInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPALCharacterInfo();

// 对话框数据
	enum { IDD = IDD_DLGCHARACTERINFO };

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
	CStatic GrpPage;

	// CComboBox翻页查询
	CComboBox cmbPage;

	// CListCtrl玩家资料信息
	CListCtrl listUser;

	// 指示对话框当前状态
	int dlgStatus;

public:
	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	//关闭对话框
	afx_msg void OnClose();

	//设置对话框颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//设置对话框大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//处理快捷键响应函数
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// 查询玩家资料信息
	afx_msg void OnBnClickedSearch();

	// 关闭对话框
	afx_msg void OnBnClickedCancel();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//单击用户资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbpage();
};
