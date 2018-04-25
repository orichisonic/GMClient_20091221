#pragma once
#include "afxcmn.h"



// CDlgSelect 窗体视图

class CDlgSelect : public CFormView
{
	DECLARE_DYNCREATE(CDlgSelect)

protected:
	CDlgSelect();           // 动态创建所使用的受保护的构造函数
	virtual ~CDlgSelect();

public:
	enum { IDD = IDD_DLGTABSELECT };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	//在标签里面添加关闭符号
	CImageList m_imagetab;

public:
	//CTabCtrl对象，切换对话框
	CTabCtrl tbcSelect;

	//初始化更新
	virtual void OnInitialUpdate();

	//自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//单击图标进行关闭
	afx_msg void OnNMClickTabselect(NMHDR *pNMHDR, LRESULT *pResult);

	//选择不同的CTabCtrl对象，切换对话框
	afx_msg void OnTcnSelchangeTabselect(NMHDR *pNMHDR, LRESULT *pResult);

	//接收打开对话框的消息
	LRESULT OnRecView(WPARAM wParam, LPARAM lParam);

	//接收显示对话框的消息
	LRESULT OnShowDlg(WPARAM wParam, LPARAM lParam);

	//响应WM_CLOSE消息
	afx_msg void OnClose();

	//显示对话框
	void ShowDialog(CString GameName,CString DlgName);

	void CloseDialog(CString GameName,CString DlgName);
	afx_msg void OnPaint();
};


