#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPALItemManage 对话框

class CPALItemManage : public CDialog
{
	DECLARE_DYNAMIC(CPALItemManage)

public:
	CPALItemManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPALItemManage();

// 对话框数据
	enum { IDD = IDD_DLGITEMMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	// 单击道具列表得到行号
	int nSelectItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 所有大类信息
	CMap<int,int,int,int> BigTypeList;

	// 所有小类信息
	CMap<int,int,int,int> GiftList;

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

	// CComboBox道具类别
	CComboBox cmbType;

	// CComboBox道具名称
	CComboBox cmbName;

	// CListCtrl待赠送的道具列表
	CListCtrl listItem;

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

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//查询玩家背包信息
	void BagInfo(int iBagType);

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbpage();

	// 双击道具信息进行删除
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 查询道具类别信息
    void ItemTypeInfo(void);

	// 根据道具类别查询相应的道具名称
	afx_msg void OnCbnSelchangeCmbbigtype();

	//向道具列表中添加道具
	afx_msg void OnBnClickedBtnadd();

	//单击道具列表保存行号
	afx_msg void OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//双击道具列表进行删除
	afx_msg void OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//从道具列表中进行删除
	afx_msg void OnBnClickedBtndelete();

	// 通过邮件添加道具
	afx_msg void OnBnClickedBtnsend();

	// 重置信息
	afx_msg void OnBnClickedBtnreset();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//单击用户资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//单击结果信息的列名进行排序
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 关闭对话框
	afx_msg void OnBnClickedCancel();

	// 关闭对话框
	afx_msg void OnClose();

public:

	// 显示角色资料信息
	void ShowUserInfo(void);

	// 显示背包信息
	void ShowBagType(void);	

	// 显示其它信息
	void ShowOtherInfo(void);	

	// 显示发送道具页面
	void ShowMailItem(int m_cmdShow);
	
	//重置邮件信息
	void ResetMailInfo(void);
};
