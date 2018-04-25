#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CGTOWNUserInfoPart 对话框

class CGTOWNUserInfoPart : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNUserInfoPart)

public:
	CGTOWNUserInfoPart(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGTOWNUserInfoPart();

// 对话框数据
	enum { IDD = IDD_DLGUSERINFOPART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断是否需要翻页
	bool pageInfo;

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	//输入的玩家帐号和角色名
	CString Account, Name;

	// 获得的玩家帐号和角色名
	CString UserAccount, UserName;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

	//玩家ID
	int UserID;
public:
	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	//翻页容器
	CStatic GrpPage;

	//翻页组合框
	CComboBox cmbPage;

	//显示玩家信息列表框
	CListCtrl listUser;

	// CListCtrl结果显示
	CListCtrl listResult;

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

	// 关闭对话框
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();

	// 显示角色资料信息
	void ShowUserInfo(void);

	// 显示其它信息
	void ShowOtherInfo(void);

	// 单击用户列表保存当前行号
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击玩家资料信息进行查询
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//查询玩家资料信息
	afx_msg void OnBnClickedSearch();

	//处理快捷键响应函数
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//切换翻页组合框
	afx_msg void OnCbnSelchangeCmbpage();

	//单击用户资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//单击结果信息的列名进行排序
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//玩家详细资料
	void DetailInfo();

	//角色家族信息
	void FamilyInfo();

	//情侣信息查询
	void SentiInfo();

	//结婚信息查询
	void MarrigeInfo();
};
