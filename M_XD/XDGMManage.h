#pragma once


// CXDGMManage 对话框

class CXDGMManage : public CDialog
{
	DECLARE_DYNAMIC(CXDGMManage)

public:
	CXDGMManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXDGMManage();

// 对话框数据
	enum { IDD = IDD_DLGGMMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 所有技能信息列表
	CMap<int,int,int,int> BuffList;

	// 判断基本资料信息列表是否需要翻页
	bool pageBasic;

	// 游戏服务器IP
	CString ServerIP;

	// 玩家ID
	CString UserID;

	// 输入的玩家帐号
	CString UserName;

	// 输入的玩家昵称
	CString UserNick;

	//添加或移除的BUFFID
	int BuffID;

	//添加或移除的BUFF名称
	CString BuffName;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	// CComboBox基本资料信息翻页查询
	CComboBox cmbBasic;

	// CListCtrl基本资料信息
	CListCtrl listBasic;

	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CGroupBox翻页容器
	CStatic GrpPage;

	//显示列表信息
	CComboBox cmbList;

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

	// 查询玩家资料信息
	afx_msg void OnBnClickedSearch();

	// 查询玩家资料信息
	void UserInfo();

	// 翻页查询玩家资料信息
	afx_msg void OnCbnSelchangeCmbbasic();

	// 单击玩家资料信息保存当前行号
	afx_msg void OnNMClickListbasic(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击玩家资料信息进行操作
	afx_msg void OnNMDblclkListbasic(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行操作
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);	

	//查询所有BUFF信息
	void SearchBuff();

	//移动角色位置
	afx_msg void OnBnClickedBtnedit();

	//重置信息
	afx_msg void OnBnClickedBtnrecover();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 关闭对话框
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();	

	//用户基本资料信息页面
	void ShowUserInfo(int m_cmdShow);

	//传送至指定坐标页面
	void ShowCoordinate(int m_cmdShow);

	//玩家和GM互相传送至对方位置
	void ShowTransferGM(int m_cmdShow);

	//添加/移除BUFF页面
	void ShowEditBuff(int m_cmdShow);

	//对Ctrl+A/C做出响应
	virtual	BOOL PreTranslateMessage(MSG* pMsg);
};
