#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CGTOWNItemManage 对话框

class CGTOWNItemManage : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNItemManage)

public:
	CGTOWNItemManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGTOWNItemManage();

	// 对话框数据
	enum { IDD = IDD_DLGITEMMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	//单击道具列表得到要添加的道具的行号
	int addItem;

	//单击赠送道具列表得到要删除的道具列表
	int delItem;

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
	int grpHeight, tbcHeight,grpPHeight, listWidth;

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

	// 查询得到的道具列表
	CListCtrl listResult;

	//要添加的道具列表
	CListCtrl listItem;

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

	//处理快捷键响应函数
	virtual BOOL PreTranslateMessage(MSG* pMsg);


	//查询玩家资料信息
	afx_msg void OnBnClickedSearch();

	//翻页查询玩家资料信息
	afx_msg void OnCbnSelchangeCmbpage();


	// 单击用户列表保存当前行号
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击玩家资料信息进行查询
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);


	//模糊查询可以进行添加的道具信息
	afx_msg void OnBnClickedBtnblursearch();


	//单击可以添加的道具列表，保存行号
	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//双击可以添加的道具列表，进行添加
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//添加道具信息到赠送道具列表中
	afx_msg void OnBnClickedBtnadd();


	//单击赠送道具列表，保存行号
	afx_msg void OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//双击赠送道具列表，进行删除
	afx_msg void OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//从赠送道具列表中删除相应的道具
	afx_msg void OnBnClickedBtndelete();



	//添加道具
	afx_msg void OnBnClickedBtnsend();

	//重置添加道具中的信息
	afx_msg void OnBnClickedBtnreset();


	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);


	//单击用户资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//单击结果信息的列名进行排序
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//单击添加道具列表进行排序
	afx_msg void OnLvnColumnclickListitem(NMHDR *pNMHDR, LRESULT *pResult);


	// 显示角色资料信息
	void ShowUserInfo(int nCmdShow);

	// 显示其它信息
	void ShowItemInfo(int nCmdShow);

	//使用关闭按钮
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();	
	CComboBox cmbBigType;
	CComboBox cmbSmallType;
};
