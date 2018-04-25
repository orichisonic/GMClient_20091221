#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CGTOWNFamilyInfo 对话框

class CGTOWNFamilyInfo : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNFamilyInfo)

public:
	CGTOWNFamilyInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGTOWNFamilyInfo();

// 对话框数据
	enum { IDD = IDD_DLGFAMILYINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断是否需要翻页
	bool pageFInfo;
	bool pageInfo;

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	// 输入的家族名称
	CString Name;

	// 获取的家族名称
	CString FamilyName;

	//获取的家族ID
	int FamilyID;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	//翻页容器
	CStatic GrpPage;

	//家族翻页复选框
	CComboBox cmbFPage;

	//翻页组合框
	CComboBox cmbPage;

	//显示玩家信息列表框
	CListCtrl listFamily;

	//显示结果信息
	CListCtrl listMember;

	// 指示对话框当前状态
	int dlgStatus;

public:

	// 初始化对话框
	virtual BOOL OnInitDialog();

	//初始化显示字符
	void InitUI();

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//处理快捷键响应函数
	virtual BOOL PreTranslateMessage(MSG* pMsg);


	//查询家族信息
	afx_msg void OnBnClickedSearch();

	// 翻页查询家族基本信息
	afx_msg void OnCbnSelchangeCmbfpage();	


	// 单击家族列表保存当前行号
	afx_msg void OnNMClickListfamily(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击家族资料信息进行查询
	afx_msg void OnNMDblclkListfamily(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击玩家资料信息进行查询
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//家族成员详细信息
	void MemberInfo();

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbpage();


	//接受返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//显示家族信息
	void ShowFamilyInfo();

	//显示其它信息
	void ShowOtherInfo();



	//单击家族资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListfamily(NMHDR *pNMHDR, LRESULT *pResult);

	//单击成员信息的列名进行排序
	afx_msg void OnLvnColumnclickListmember(NMHDR *pNMHDR, LRESULT *pResult);

	//使用关闭按钮
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();		
	
};
