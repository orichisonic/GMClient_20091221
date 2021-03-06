#pragma once

#include "OperationCG2.h"
#include "afxcmn.h"
#include "afxwin.h"

// CCG2PetInfo 对话框

class CCG2PetInfo : public CDialog
{
	DECLARE_DYNAMIC(CCG2PetInfo)

public:
	CCG2PetInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCG2PetInfo();

// 对话框数据
	enum { IDD = IDD_DLGPETINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;
	
	// 单击用户列表得到行号
	int nItem;

	// 判断用户列表是否需要翻页
	bool pageUInfo;

	// 单击宠物列表得到行号
	int nPetItem;

	// 判断用户列表是否需要翻页
	bool pagePetInfo;


	// 判断是否需要翻页
	bool pageInfo;

	// 游戏服务器IP
	CString ServerIP;

	// 玩家ID
	CString UserID;

	// 输入的玩家帐号
	CString UserName;

	// 输入的玩家昵称
	CString UserNick;

	//宠物位置
	int PetID;

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

	// CComboBox翻页查询
	CComboBox cmbPetPage;

	// CListCtrl玩家资料信息
	CListCtrl listUser;

	// CListCtrl宠物信息
	CListCtrl listPet;

	// CListCtrl结果显示
	CListCtrl listResult;

	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CGroupBox翻页容器
	CStatic GrpPage;

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

	// 查询玩家资料信息
	afx_msg void OnBnClickedUisearch();

	// 翻页查询玩家资料信息
	afx_msg void OnCbnSelchangeCmbuserpage();

	// 单击玩家资料信息保存当前行号
	afx_msg void OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击玩家资料信息进行查询
	afx_msg void OnNMDblclkListUser(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 单击宠物列表保存当前行号
	void OnNMClickListPet(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击宠物信息进行查询
	void OnNMDblclkListPet(NMHDR *pNMHDR, LRESULT *pResult);

	// 查询玩家资料信息
	void UserInfo();

	// 宠物基本资料
	void PetInfo();

	// 宠物技能信息
	void PetSkill();

	

	

	// 翻页进行查询
	afx_msg void OnCbnSelchangeCmbuipage();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 关闭对话框
	afx_msg void OnBnClickedUicancel();

	// 关闭对话框
	afx_msg void OnClose();			



};
