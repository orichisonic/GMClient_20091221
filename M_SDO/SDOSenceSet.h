#pragma once
#include "afxcmn.h"


// CSDOSenceSet 对话框

class CSDOSenceSet : public CDialog
{
	DECLARE_DYNAMIC(CSDOSenceSet)

public:
	CSDOSenceSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSDOSenceSet();

// 对话框数据
	enum { IDD = IDD_DLGSENCESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
		int nItem;

		int tbcHeight;//TabCtrl的高度

		//场景ID
		int SenceID;

		//场景名称
		CString SenceName;

public:
	// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	// 指示对话框当前状态
	int dlgStatus;

	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	//显示场景列表信息
	void ShowSence();

	//单击列表头排序
	afx_msg void OnLvnColumnclickListsence(NMHDR *pNMHDR, LRESULT *pResult);

	//发送场景信息
	void SenceInfo();

	//显示其它界面
	void ShowOther();

	//场景列表框
	CListCtrl listSence;

	//切换tabCtrl
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//单击场景列表框
	afx_msg void OnNMClickListsence(NMHDR *pNMHDR, LRESULT *pResult);

	//添加或者编辑场景
	afx_msg void OnBnClickedSearch();

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//关闭对话框
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();

	//处理快捷键响应函数
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//添加场景
	void AddSence();

	//编辑场景
	void UpdateSence();

	//双击场景列表删除
	afx_msg void OnNMDblclkListsence(NMHDR *pNMHDR, LRESULT *pResult);

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);
};
