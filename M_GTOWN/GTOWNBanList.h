#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CGTOWNBanList 对话框

class CGTOWNBanList : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNBanList)

public:
	CGTOWNBanList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGTOWNBanList();

// 对话框数据
	enum { IDD = IDD_DLGBANLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	// 单击帐号封停列表得到行号
	int mItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断是否需要翻页
	bool pageUInfo;
	bool pageInfo;

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	//输入的玩家帐号和角色名
	CString Account, Name;

	// 获得的玩家帐号和角色名
	CString UserAccount, UserName;

	//玩家ID
	int UserID;

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

	//玩家信息翻页复选框
	CComboBox cmbUPage;

	// CComboBox翻页查询
	CComboBox cmbPage;

	// CListCtrl玩家资料信息
	CListCtrl listUser;

	// CListCtrl结果显示
	CListCtrl listResult;

	//封停玩家帐号
	CEdit txtAccount;

	//封停原因
	CEdit txtReason;

	// 指示对话框当前状态
	int dlgStatus;

	//封停与解封的状态
	int UserState;

	//玩家ID
	int userID;

public:
	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//处理快捷键响应
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	

	//查询玩家资料信息
	afx_msg void OnBnClickedOk();
	void UserInfo();

	//翻页查询玩家资料信息
	afx_msg void OnCbnSelchangeCmbupage();


	// 单击用户列表保存当前行号
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击用户列表切换界面
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);



	// 查询所有被封停帐号列表信息
	void AllBanUserList();

	// 翻页查询被封停帐号列表信息
	afx_msg void OnCbnSelchangeCmbpage();


	// 单击封停帐号列表保存当前行号
	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击封停帐号列表切换界面
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);


	//切换tabCtrl选项卡
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);


	//封停或解封帐号
	afx_msg void OnBnClickedBtnban();


	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);


	//重置信息
	afx_msg void OnBnClickedBtnreset();


	//显示玩家资料信息
	void showUserInfo();

	//显示封停帐号
	void showBanPlayer();

	//显示封停帐号列表
	void showBanList();

	//显示解封帐号
	void showUnbindPlayer();

	//查询帐号有没有封停
	void showSearchPlayer();

	//单击用户资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//单击结果信息的列名进行排序
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 关闭对话框
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
};
