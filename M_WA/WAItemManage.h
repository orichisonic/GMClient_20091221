#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CWAItemManage 对话框


class CWAItemManage : public CDialog
{
	DECLARE_DYNAMIC(CWAItemManage)

public:
	CWAItemManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWAItemManage();

// 对话框数据
	enum { IDD = IDD_DLGITEMMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 所有道具信息列表
	CMap<int,int,CString,CString> ItemList;

	// 所有用户信息列表
	CMap<int,int,CString,CString> UserList;

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

	//道具ID
	CString ItemID;

	//道具名称
	CString ItemName;

	//添加道具的最终结果
	char ItemResult[2048];

	//添加道具的临时结果
	char tmpItemResult[2048];	

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

	//显示类型列表
	CComboBox cmbType;

	//显示道具列表
	CComboBox cmbList;

	//道具列表
	CListCtrl listItem;

	//选择是否需要批量添加
	CButton checkSelect;

	//选择是否需要群发道具
	CButton checkGroup;

	//模糊道具名&新金钱数
	CEdit CEditNew;

	//道具品质
	CComboBox cmbQuality;

	//CProgressCtrl发送道具进度条
	CProgressCtrl progMail;

	// 指示对话框当前状态
	int dlgStatus;

	//选择是否属于第一次添加道具
	int nFirst;

	//选择相应的玩家道具行号
	int nListItem;

	//选择相应的添加道具行号
	int nSelectItem;

	//确定是否批量添加道具
	int multStatus;

	//待发送道具的角色名数量
	int UserNum;

	//当前正在发送的角色序号
	int mCurNum;

public:
	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//获取选择的ServerIP
	afx_msg void OnCbnSelchangeCmbuiserver();

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

	// 查询角色道具信息
	void ItemInfo();

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbuipage();

	//选择相应的技能信息进行修改
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//删除选中的道具
	afx_msg void OnBnClickedBtndelitem();

	//选择是否批量添加道具
	afx_msg void OnBnClickedCheckselect();

	//选择是否需要群发道具
	afx_msg void OnBnClickedCheckgroup();

	//选择批量添加道具的角色文件名
	afx_msg void OnBnClickedBtnbrowse();

	//查询道具类型信息
	void SearchItemType();

	//查询相应类型的道具信息
	afx_msg void OnBnClickedBtnitemlist();

	//向道具列表中添加道具
	afx_msg void OnBnClickedBtnadd();

	//单击道具列表保存行号
	afx_msg void OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//双击道具列表进行删除
	afx_msg void OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//从道具列表中进行删除
	afx_msg void OnBnClickedBtndelete();

	//修改或添加信息
	afx_msg void OnBnClickedBtnedit();

	//添加新道具
	void AddItem();

	//修改金钱数量
	void EditMoney();

	//重置信息
	afx_msg void OnBnClickedBtnrecover();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//单击基本资料信息的列名进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//单击结果信息的列名进行排序
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 关闭对话框
	afx_msg void OnBnClickedUicancel();

	// 关闭对话框
	afx_msg void OnClose();	

	//用户基本资料信息页面
	void ShowUserInfo(int m_cmdShow);

	//用户道具信息页面
	void ShowItemInfo(int m_cmdShow);

	//添加新道具页面
	void ShowNewItem(int m_cmdShow);

	//给新道具页面的相关参数赋值
	void NewItemValue();

	//修改用户金钱页面
	void ShowMoneyInfo(int m_cmdShow);

	//对Ctrl+A/C做出响应
	virtual	BOOL PreTranslateMessage(MSG* pMsg);
};
