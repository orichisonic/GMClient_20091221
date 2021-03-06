#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"


// CCG2GuildManage 对话框

class CCG2GuildManage : public CDialog
{
	DECLARE_DYNAMIC(CCG2GuildManage)

public:
	CCG2GuildManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCG2GuildManage();

// 对话框数据
	enum { IDD = IDD_DLGGUILDMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;
	int mItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断是否需要翻页
	bool pageUInfo;
	bool pageInfo;	

	// 游戏服务器IP
	CString ServerIP;

	//输入的公会名称
	CString GuildName;

	//输入的公会ID
	int GuildId;

	//玩家用户名
	CString UserName;

	// 玩家昵称
	CString UserNick;

	// 玩家ID
	CString UserID;

	//角色名
	int iCharNo;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	// CComboBox翻页查询
	CComboBox cmbPage;

	// CListCtrl结果显示
	CListCtrl listResult;

	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CGroupBox翻页容器
	CStatic GrpPage;

	// CEdit玩家帐号
	CEdit txtAccount;

	// CDateTimeCtrl封停截止日期
	CDateTimeCtrl dtcBanEndDate;

	// CDateTimeCtrl封停截止时间
	CDateTimeCtrl dtcBanEndTime;

	// CComboBox封停类型
	CComboBox cmbBanType;

	// CListCtrl公会资料信息
	CListCtrl listGuild;

	//用户资料信息翻页
	CComboBox cmbUPage;

	// CEdit解封或封停原因
	CEdit txtReason;

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

	// 查询资料信息
	afx_msg void OnBnClickedUisearch();

	// 查询公会信息
	void GuildInfo();

	// 查询公会成员信息
	void GuildDetail();

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbuipage();

	// 翻页查询封停账号列表
	afx_msg void OnCbnSelchangeCmbpage();

	// 单击资料信息保存当前行号
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击资料信息进行操作
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);
	

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 关闭对话框	
	afx_msg void OnBnClickedUicancel();	

	// 关闭对话框
	afx_msg void OnClose();

	//显示更改公会名称界面
	void ShowGuildName(int m_cmdShow);

	//显示更改公会等级界面
	void ShowGuildLevel(int m_cmdShow);

	//显示更改公会等级界面
	void ShowGuildHonor(int m_cmdShow);


	afx_msg void OnBnClickedBtnchange();

	//修改公会名称
	void RenameGuild();

	//修改公会等级
	void UpdateGuildLevel();
	CEdit m_Resource;
	CComboBox cmbNewGuildLevel;
};
