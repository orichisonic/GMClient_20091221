#pragma once
#include "afxwin.h"


// CWAUserManage 对话框

class CWAUserManage : public CDialog
{
	DECLARE_DYNAMIC(CWAUserManage)

public:
	CWAUserManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWAUserManage();

// 对话框数据
	enum { IDD = IDD_DLGUSERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 所有技能信息列表
	CMap<int,int,int,int> SkillList;

	// 判断是否需要翻页
	bool pageInfo;

	// 判断用户列表是否需要翻页
	bool pageUInfo;

	// 游戏服务器IP
	CString ServerIP;

	// 玩家ID
	CString UserID;

	// 输入的玩家帐号
	CString UserName;

	// 输入的玩家昵称
	CString UserNick;

	//修改或添加的技能ID
	int SkillID;

	//修改或添加的技能名称
	CString SkillName;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	// CComboBox玩家角色信息翻页查询
	CComboBox cmbUPage;

	// CComboBox翻页查询
	CComboBox cmbPage;

	// CListCtrl玩家资料信息
	CListCtrl listUser;

	// CListCtrl结果显示
	CListCtrl listResult;

	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CGroupBox翻页容器
	CStatic GrpPage;

	//显示技能列表
	CComboBox cmbList;

	//设置Password属性
	CEdit CEditOld;

	//设置Number属性
	CEdit CEditNew;

	// 指示对话框当前状态
	int dlgStatus;

	int nListItem;

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

	// 翻页查询玩家资料信息
	afx_msg void OnCbnSelchangeCmbuserpage();

	// 单击玩家资料信息保存当前行号
	afx_msg void OnNMClickListcharacter(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击玩家资料信息进行查询
	afx_msg void OnNMDblclkListcharacter(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 查询玩家资料信息
	void UserInfo();

	// 查询角色技能信息
	void SkillInfo();

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbuipage();

	//选择相应的技能信息进行修改
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//修改选中的角色技能信息
	afx_msg void OnBnClickedBtneditlvl();

	//删除选中的角色技能信息
	afx_msg void OnBnClickedBtndelskill();

	//查询所有技能信息
	void SearchSkill();

	//修改或添加信息
	afx_msg void OnBnClickedBtnedit();

	//删除或恢复信息
	afx_msg void OnBnClickedBtnrecover();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 关闭对话框
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();	

	//选择不同的属性进行修改
	afx_msg void OnCbnSelchangeCmbskill();

	//用户基本资料信息页面
	void ShowUserInfo(int m_cmdShow);

	//用户技能信息页面
	void ShowSkillInfo(int m_cmdShow);

	//添加新技能页面
	void ShowNewSkill(int m_cmdShow);

	//修改/恢复用户密码页面
	void ShowPwdInfo(int m_cmdShow);

	//删除/恢复用户页面
	void ShowManageInfo(int m_cmdShow);

	//修改用户角色名/等级/金钱页面
	void ShowAccountInfo(int m_cmdShow);

	//对Ctrl+A/C做出响应
	virtual	BOOL PreTranslateMessage(MSG* pMsg);
};
