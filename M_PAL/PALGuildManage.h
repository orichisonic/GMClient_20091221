#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPALGuildManage 对话框

class CPALGuildManage : public CDialog
{
	DECLARE_DYNAMIC(CPALGuildManage)

public:
	CPALGuildManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPALGuildManage();

// 对话框数据
	enum { IDD = IDD_DLGGUILDMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击公会列表得到行号
	int nGuildItem;

	// 单击公会用户列表得到行号
	int nGuildMemberItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断是否需要翻页
	bool pageInfo;

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	//输入的公会名称
	CString GuildName;

	//玩家角色名
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

	//CComboBox成员职级
	CComboBox cmbMemberLvl;

	// CListCtrl公会列表
	CListCtrl listGuild;

	// CListCtrl公会成员列表
	CListCtrl listMember;

	// CEdit公告原等级
	CEdit txtGuildLvl;

	//CComboBox等级
	CComboBox cmbLvl;

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

	// 查询资料信息
	afx_msg void OnBnClickedSearch();

	// 查询公会成员信息
	void GuildMemberList();

	// 单击公会资料信息保存当前行号
	afx_msg void OnNMClickListguild(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击公会资料信息进行操作
	afx_msg void OnNMDblclkListguild(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行操作
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbpage();

	// 单击公会成员信息保存当前行号
	afx_msg void OnNMClickListmember(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击公会成员信息进行操作
	afx_msg void OnNMDblclkListmember(NMHDR *pNMHDR, LRESULT *pResult);

	// 进行修改
	afx_msg void OnBnClickedBtnmodi();

	//修改公会成员等级信息
	afx_msg void OnBnClickedBtnmodimemberlvl();

	// 重置信息
	afx_msg void OnBnClickedBtnreset();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//单击公会信息的列名进行排序
	afx_msg void OnLvnColumnclickListguild(NMHDR *pNMHDR, LRESULT *pResult);

	//单击公会成员信息的列名进行排序
	afx_msg void OnLvnColumnclickListmember(NMHDR *pNMHDR, LRESULT *pResult);

	// 关闭对话框	
	afx_msg void OnBnClickedCancel();

	// 关闭对话框	
	afx_msg void OnClose();

public:
	// 初始化公会成员等级
	void InitMemberLevel(void);

	// 初始化所有的新公会等级
	void InitNewGuildLevl(void);

	// 显示公会信息
	void ShowGuildInfo();

	// 显示修改信息界面
	void ShowModiTab(int m_cmdShow);

	// 显示修改公会成员信息
	void ShowGuildMember(int m_cmdShow);
};
