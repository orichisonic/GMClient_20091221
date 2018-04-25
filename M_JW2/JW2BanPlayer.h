#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAUBanPlayer 对话框

class CJW2BanPlayer : public CDialog
{
	DECLARE_DYNAMIC(CJW2BanPlayer)

public:
	CJW2BanPlayer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJW2BanPlayer();

// 对话框数据
	enum { IDD = IDD_DLGBANPLAYER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	//单击封停账号列表得到行号
	int mItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断是否需要翻页
	bool pageInfo;
	bool pageUInfo;

	//游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	// 玩家帐号
	CString UserAccount;

	//输入的玩家帐号和昵称
	CString UserName;

	//输入的玩家昵称
	CString UserNick;

	// 玩家ID
	int UserID;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	// CComboBox翻页查询
	CComboBox cmbPage;

	//CComboBox翻页查询封停帐号列表信息
	CComboBox cmbLPage;

	//CListCtrl用户信息
	CListCtrl listUser;

	// CListCtrl结果显示
	CListCtrl listResult;

	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CGroupBox翻页容器
	CStatic GrpPage;

	// CEdit玩家帐号
	CEdit txtAccount;

	// CEdit解封或封停原因
	CEdit txtReason;

	// 指示对话框当前状态
	int dlgStatus;
public:
	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	//处理快捷键响应函数
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// 查询资料信息
	afx_msg void OnBnClickedUisearch();

	// 查询玩家资料信息
	void UserInfo();

	// 查询所有被封停帐号列表信息
	void AllBanUserList();

	// 翻页进行查询玩家资料信息
	afx_msg void OnCbnSelchangeCmbuipage();

	// 翻页进行查询封停帐号列表信息
	afx_msg void OnCbnSelchangeCmbpage();

	// 单击资料信息保存当前行号
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击资料信息进行操作
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 单击封停账号列表信息保存当前行号
	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击封停账号列表信息进行解封
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);
	
	// 封停或解封帐号
	afx_msg void OnBnClickedBtnban();

	// 重置信息
	afx_msg void OnBnClickedBtnreset();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//单击用户资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//单击结果信息的列名进行排序
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 关闭对话框	
	afx_msg void OnBnClickedUicancel();	

	// 关闭对话框
	afx_msg void OnClose();		
};
