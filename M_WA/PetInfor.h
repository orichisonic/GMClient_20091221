#pragma once


// PetInfor 对话框

class PetInfor : public CDialog
{
	DECLARE_DYNAMIC(PetInfor)

public:
	PetInfor(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PetInfor();
	// 对话框数据
	enum { IDD = IDD_DLGPETINFOR};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;
    int nItemresult;
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
	// 选择的查找类型
	CString SearchType;
	// 输入的玩家角色名
	CString UserName;
	//宠物序号
    CString WA_medalPetIndex;
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

	// CListCtrl结果显示
	CListCtrl listResult;

	// CComboBox任务类型
	CComboBox cmbQuestType;

	// 指示对话框当前状态
	int dlgStatus;

public:
	// 初始化对话框
	virtual BOOL OnInitDialog();

	//处理快捷键响应函数
	//virtual BOOL PreTranslateMessage(MSG* pMsg);

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

	// 双击玩家资料信息进行查询
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);
	// 单击徽章列表保存当前行号
	//afx_msg void OnNMClickListhuizhanginfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击徽章资料信息进行查询
	//afx_msg void OnNMDblclkListhuizhanginfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//查询玩家徽章信息
	void EmblemList();

	//显示好友信息列表
	void ShowFriendInfo();

	//查询玩家任务信息
	void QuestInfo();
	
	void  PetList();
	//切换任务状态查询玩家任务信息
	afx_msg void OnCbnSelchangeCmbquesttype();

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbpage();

	// 关闭对话框
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();

public:
	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//单击用户资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//单击结果信息的列名进行排序
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 初始化查询列表复选框
	void InitQuestType(void);

	// 显示角色资料信息
	void ShowUserInfo(void);

	// 显示其它信息
	//void ShowOtherInfo(void);	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
