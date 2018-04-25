#pragma once
//#include "OperationCG2.h"
//#include "afxcmn.h"
//#include "afxwin.h"
//
//#import "c:\program files\common files\system\ado\msado15.dll"\
//	no_namespace \
//	rename ("EOF", "adoEOF")

// ChangeMoney 对话框

class ChangeMoney : public CDialog
{
	DECLARE_DYNAMIC(ChangeMoney)

public:
	ChangeMoney(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ChangeMoney();

	// 对话框数据
	enum { IDD = IDD_DLGBANKMANAGE };

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

	// 判断用户列表是否需要翻页
	bool pageUInfo;

	// 游戏服务器IP
	CString ServerIP;

	// 玩家ID
	CString UserID;

	// 输入的玩家帐号
	CString UserName;

	// 输入的玩家昵称
	CString UserNick;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	// CComboBox玩家角色信息翻页查询
	CComboBox cmbUPage;

	// CComboBox翻页查询
	CComboBox cmbPage;

	// CListCtrl玩家资料信息
	CListCtrl listUser;

	// CListCtrl结果显示
	CListCtrl listResult;

	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CGroupBox翻页容器
	CStatic GrpPage;

	// 指示对话框当前状态
	int dlgStatus;

	int nListItem;

public:
	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// 查询玩家资料信息
	afx_msg void OnBnClickedUisearch();

	// 翻页查询玩家资料信息
	afx_msg void OnCbnSelchangeCmbuserpage();

	// 单击玩家资料信息保存当前行号
	afx_msg void OnNMClickListcharacter(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击玩家资料信息进行查询
	afx_msg void OnNMDblclkListcharacter(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 查询玩家资料信息
	void UserInfo();

	// 查询角色详细资料
	void BankInfo();

	// 查询角色属性资料
	void BankItem();

	// 查询角色工会资料
	void BankPet();

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbuipage();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 关闭对话框
	afx_msg void OnBnClickedUicancel();

	// 关闭对话框
	afx_msg void OnClose();			

	//道具类别查询
	void ItemType();


	void ShowAddBankItem(int n_cmdShow);
	afx_msg void OnEnChangeEdit3();
	CButton ckItemType;
	afx_msg void OnBnClickedCkitemtype();
	afx_msg void OnBnClickedBtn1();
	afx_msg void OnBnClickedBtn2();

	//添加银行道具
	void AddBankItem();

	//修改银行金钱
	void ModifyBankMoney();

	//批量添加银行道具
	void MultiAddBankItem();

	//查询道具
	void SearchItem();

	afx_msg void OnBnClickedBtright();
	afx_msg void OnBnClickedBtleft();
	CListCtrl listItem;
	afx_msg void OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox cmbItemName;
	CComboBox cmbItemType;
	afx_msg void OnCbnSelchangeCmb1();
	void GetListItem(CString m_ItemName, CString m_ItemNum);
	void ShowBankMoney(int m_cmdShow);
	void ShowMultiAdd(int m_cmdShow);
	bool ReadXls(CString strFilePath,CString* strUserName, CString* strUserID, CString* strItemName, CString* strItemNum);
	afx_msg void OnBnClickedBtn3();
	virtual	BOOL PreTranslateMessage(MSG* pMsg);
};
