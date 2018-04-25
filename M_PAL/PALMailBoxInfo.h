#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"


// CPALMailBoxInfo 对话框

class CPALMailBoxInfo : public CDialog
{
	DECLARE_DYNAMIC(CPALMailBoxInfo)

public:
	CPALMailBoxInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPALMailBoxInfo();

// 对话框数据
	enum { IDD = IDD_DLGMAILBOXINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	//单击邮箱列表
	int nMailItem;

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

	//获取的玩家ID
	int UserID;

	//获取MAILID
	int MailID;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;
	
public:
	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CDateTimeCtrl开始时间
	CDateTimeCtrl dtcStartTime;

	// CDateTimeCtrl结束时间
	CDateTimeCtrl dtcEndTime;

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

	//CListCtrl显示附件（最多5个）
	CListCtrl listMailDetail;

	//开始时间
	CString strStartTime;

	//结束时间
	CString strEndTime;

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

	// 双击玩家资料信息进行查询
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击邮箱邮件进行查询
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);


	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//查询玩家邮箱信息
	void MailBoxInfo();

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

	// 显示角色资料信息
	void ShowUserInfo(void);

	// 显示其它信息
	void ShowMailInfo(void);

	// 显示邮件附件界面
	void ShowMailDetail(void);

	//查询玩家邮箱附件信息
	void MailBoxDetail();

	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);
};
