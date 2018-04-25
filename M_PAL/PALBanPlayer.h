#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#import "c:\program files\common files\system\ado\msado15.dll"\
	no_namespace \
	rename ("EOF", "adoEOF")

// CPALBanPlayer 对话框

class CPALBanPlayer : public CDialog
{
	DECLARE_DYNAMIC(CPALBanPlayer)

public:
	CPALBanPlayer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPALBanPlayer();

// 对话框数据
	enum { IDD = IDD_DLGBANPLAYER };

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

	// CListCtrl结果显示
	CListCtrl listResult;

	// CEdit玩家帐号
	CEdit txtAccount;

	// CEdit解封或封停原因
	CEdit txtReason;

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
	afx_msg void OnBnClickedOk();

	// 查询玩家资料信息
	void UserInfo();

	// 查询所有被封停帐号列表信息
	void AllBanUserList();

	// 单击用户列表保存当前行号
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击用户列表切换界面
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行操作
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 单击封停帐号列表保存当前行号
	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击封停帐号列表切换界面
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbpage();

	// 封停或解封帐号
	afx_msg void OnBnClickedBtnban();

	// 重置信息
	afx_msg void OnBnClickedBtnreset();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 关闭对话框	
	afx_msg void OnBnClickedCancel();

	//单击用户资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//单击结果信息的列名进行排序
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 关闭对话框
	afx_msg void OnClose();

public:
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

	
	//读取excel文件
	bool ReadXls(CString m_filePath,CString* m_allUserAccount,CString* m_allUserChar);

	afx_msg void OnBnClickedBtbrowse();
	afx_msg void OnBnClickedBtmulticlose();
};
