#pragma once
#include "afxcmn.h"



// CTreeMenu 窗体视图

class CTreeMenu : public CFormView
{
	DECLARE_DYNCREATE(CTreeMenu)

protected:
	CTreeMenu();           // 动态创建所使用的受保护的构造函数
	virtual ~CTreeMenu();

public:
	enum { IDD = IDD_DLGTREE };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
    //树根部
	HTREEITEM m_root[50];

	//CTreeCtrl对象
	CTreeCtrl tMenuList;

	//初始化更新
	virtual void OnInitialUpdate();

	//创建Form
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	//自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//接收消息
	LRESULT OnRecView(WPARAM wParam, LPARAM lParam);

	//双击CTreeCtrl
	afx_msg void OnNMDblclkTreemenu(NMHDR *pNMHDR, LRESULT *pResult);

	//右键点击CTreeCtrl弹出菜单
	afx_msg void OnNMRclickTreemenu(NMHDR *pNMHDR, LRESULT *pResult);

	//点击刷新菜单时进行的操作
	afx_msg void OnRefresh();
};


