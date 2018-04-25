#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSDOITEMSET 对话框

class CSDOITEMSET : public CDialog
{
	DECLARE_DYNAMIC(CSDOITEMSET)

public:
	CSDOITEMSET(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSDOITEMSET();

// 对话框数据
	enum { IDD = IDD_DLGITEMSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	// 单击用户列表得到行号
	int nItem;

	int nSelect,mItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;
		//道具列表
	CMap<int,int,int,int> ItemCodeList;

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

	//玩家等级
	int iLevel;

	//经验值
	int iExperience;

	//总局数
	int iTotal;

	//胜局数
	int iWin;

	//平局数
	int iBalance;

	//负句数
	int iFall;

	//声望值
	int iReputation;

	//G币
	int iGCash;

	//M币
	int iMCash;

	//社交值
	int iSocial;
	//幸运值
	int iLucky;

	int iSex;//性别

	int iType;//大类值
	int iSort;//小类值

	int iItemCode;//道具编号
	CString ItemName;//道具名称

	int iItemCode1;//添加道具的编号
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
	CComboBox cmbUPage;

	//显示玩家信息列表框
	CListCtrl listUser;

	// CListCtrl装备
	CListCtrl listResult;

		//礼物盒信息列表
	CListCtrl listGiftBox;

	// 指示对话框当前状态
	int dlgStatus;

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

	//显示修改角色资料
	void ShowUpdateUser();

	//显示装备
	void ShowEquipment();

	//显示礼物盒
	void ShowGiftBox();

	//显示添加道具
	void ShowAddItem();

	// 单击用户列表保存当前行号
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//双击装备信息列表删除
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//双击礼物盒信息列表删除
	afx_msg void OnNMDblclkListgiftbox(NMHDR *pNMHDR, LRESULT *pResult);

	//处理快捷键响应函数
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//单击列名进行排序
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickListgiftbox(NMHDR *pNMHDR, LRESULT *pResult);

	//切换翻页组合框
	afx_msg void OnCbnSelchangeCmbpage();
	afx_msg void OnCbnSelchangeCmbuipage();

	//查询玩家资料信息
	afx_msg void OnBnClickedSearch();

	//切换tabCtrl
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//装备查询
	void EquipmentInfo();

	//礼物盒查询
	void GiftBoxInfo();

	//修改角色信息
	afx_msg void OnBnClickedBtupdate();

	//重置角色信息
	afx_msg void OnBnClickedBtreset();
	CComboBox cmbBigType;//大类
	CComboBox cmbSmallType;//小类
	CComboBox cmbGoods;//物品名称

	//大类导入数据
	void BigTypeData();

	//切换大类
	afx_msg void OnCbnSelchangeCmbbigtype();

	//切换小类
	afx_msg void OnCbnSelchangeCmbsmalltype();

	//道具查询
	void MaleItem();

	//模糊查询道具
	afx_msg void OnBnClickedBtquery();

	afx_msg void OnBnClickedCheck1();
	CButton btnDark;//模糊查询

	//添加道具
	afx_msg void OnBnClickedBtadd();

	//模糊查询的道具列表
	CListBox listItem;

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//删除身上装备
	void DeleteEquipment();

	//删除礼物盒
	void DeleteGiftBox();

	//双击角色信息列表
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//修改社交值
	afx_msg void OnBnClickedBtnsocial();

	//修改幸运值
	afx_msg void OnBnClickedBtnlucky();
};
