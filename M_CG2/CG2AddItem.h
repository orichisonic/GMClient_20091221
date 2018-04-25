#pragma once


// CCG2AddItem 对话框
#include "OperationCG2.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"

class CCG2AddItem : public CDialog
{
	DECLARE_DYNAMIC(CCG2AddItem)

public:
	CCG2AddItem(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCG2AddItem();

// 对话框数据
	enum { IDD = IDD_DLGADDITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	public:
	// 初始化显示字符
	void InitUI();

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

	//玩家角色技能名称
	CString UserSkill;
	
	//玩家角色技能等级
	int UserSkillLevel;

	//玩家角色号
	int iCharNo;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;
public:
	//游戏服务器组合框
	CComboBox cmbServer;

	//翻页组合框
	CComboBox cmbPage;

	//显示列表框
	CListCtrl listUser;

	//搜索容器
	CStatic GrpSearch;

	//翻页容器
	CStatic GrpPage;

	//// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	// 指示对话框当前状态
	int dlgStatus;

	//初始化对话框
	virtual BOOL OnInitDialog();

	//自动调节大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//关闭对话框
	afx_msg void OnClose();
	afx_msg void OnBnClickedUicancel();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//玩家基本信息
	void UserInfo();
	afx_msg void OnBnClickedUisearch();

	//切换tabCtrl
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 单击用户列表保存当前行号
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击玩家资料信息进行查询
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//道具类别查询
	void ItemType();

	//道具类别组合框
	CComboBox cmbItemType;

	//道具名称组合框
	CComboBox cmbItemName;


   //切换道具类别组合框
	afx_msg void OnCbnSelchangeCmbitemtype();

	//设置道具数量
	void SetNumber();

	//道具数量组合框
	CComboBox cmbItemNumber;

	//添加赠送道具列表
	afx_msg void OnBnClickedBtright();

	//添加赠送道具列表
	CListCtrl listItem;

	//删除赠送道具列表
	afx_msg void OnBnClickedBtleft();

	//单击道具列表获得行号
	afx_msg void OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//添加道具
	afx_msg void OnBnClickedBtadd();

	//点击重置按钮
	afx_msg void OnBnClickedBtreset();
};
