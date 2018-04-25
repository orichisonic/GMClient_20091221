#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPALRoleManage 对话框

class CPALRoleManage : public CDialog
{
	DECLARE_DYNAMIC(CPALRoleManage)

public:
	CPALRoleManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPALRoleManage();

// 对话框数据
	enum { IDD = IDD_DLGROLEMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	// 单击任务列表得到行号
	int nQuestItem;

	//进行查询的任务类别
	int iQuestType;

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

	// 选择的任务号
	int QuestNum;

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

	// CComboBox用户信息翻页查询
	CComboBox cmbUPage;

	// CComboBox翻页查询
	CComboBox cmbPage;

	// CListCtrl玩家资料信息
	CListCtrl listUser;

	// CListCtrl结果显示
	CListCtrl listResult;

	// CComboBox任务类型
	CComboBox cmbStatus;

	// CComboBox新任务类型
	CComboBox cmbNewStatus;

	// CComboBox类型
	CComboBox cmbType;

	// CEdit原本信息
	CEdit txtSrc;

	// CEdit修改信息
	CEdit txtNew;

	// 指示对话框当前状态
	int dlgStatus;

public:

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

	// 双击玩家资料信息进行操作
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行操作
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);
	
	//查询玩家任务信息
	void QuestInfo();

	//切换任务类型查询玩家任务信息
	afx_msg void OnCbnSelchangeCmbqueststatus();

	//翻页查询任务信息
	afx_msg void OnCbnSelchangeCmbpage();

	//双击任务列表进行修改
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//修改任务类型
	afx_msg void OnBnClickedBtnmodiquest();

	//切换不同类型
	afx_msg void OnCbnSelchangeCmbtype();

	//修改金钱或密码信息
	afx_msg void OnBnClickedBtnmodi();

	// 重置信息
	afx_msg void OnBnClickedBtnreset();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//单击用户资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//单击结果信息的列名进行排序
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 关闭对话框
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();

public:

	// 初始化密码类型复选框
	void InitPwdType(void);

	// 初始化文钱类型复选框
	void InitMoneyType(void);

	// 初始化任务类型复选框
	void InitQuestType(void);

	// 初始化要修改的任务类型复选框
	void InitQuestStatus(void);

	// 显示角色资料信息
	void ShowUserInfo(void);

	// 显示操作页面
	void ShowOperTab(int m_cmdShow);

	//显示任务操作界面
	void ShowQuestTab(int m_cmdShow,int selectShow);		
};
