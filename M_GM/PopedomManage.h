#pragma once
#include "afxcmn.h"
#include <afxtempl.h>
#include "OperationGM.h"


// CPopedomManage 对话框

class CPopedomManage : public CDialog
{
	DECLARE_DYNAMIC(CPopedomManage)

public:
	CPopedomManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPopedomManage();

// 对话框数据
	enum { IDD = IDD_DLGPOPEDOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	//要分配权限的用户ID
	int userID;

	//要分配权限的用户名
	CString userName;

	//要分配的模块数据
	CMap<int,int,CString,CString> SendData;

	//所有的模块数据
	CSocketData ModuleData;

	//和玩家相关联的模块数据
	CSocketData UserModule;	

public:
	// ListCtrl对象，游戏列表
	CListCtrl listGame;

	// ListCtrl对象，模块列表
	CListCtrl listModule;

	// 指示对话框当前状态
	int dlgStatus;

public:
	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	// 初始化私有变量
	void initVar(CString uName,int uID);

	// 创建对话框
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	// 请求所有游戏列表
	void InitGameList();

	// 单击游戏列表，获取相应的模块列表
	afx_msg void OnNMClickListgame(NMHDR *pNMHDR, LRESULT *pResult);

	// 单击模块列表，保存相应的信息
	afx_msg void OnNMClickListmodule(NMHDR *pNMHDR, LRESULT *pResult);

	//给玩家分配游戏权限
	afx_msg void OnBnClickedOk();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//关闭对话框
	afx_msg void OnBnClickedCancel();		
};
