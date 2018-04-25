#pragma once

#include <afxtempl.h>
#include ".\popedommanage.h"
#include "OperationGM.h"
// CUserManage 对话框

class CUserManage : public CDialog
{
	DECLARE_DYNAMIC(CUserManage)

public:
	CUserManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserManage();

// 对话框数据
	enum { IDD = IDD_DLGUSERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	// 所有部门信息
	CMap<int,int,CString,CString> DepartData;

	// 判断是否需要翻页
	bool pageInfo;

	//各个控件的高度
	int grpHeight,tbcHeight;

	//权限管理类
	CPopedomManage popedomManage;

public:
	// TabCtrl对象
	CTabCtrl tbcResult;

	// ListCtrl对象
	CListCtrl listUser;

	// 停用该帐号
	CButton cBtnExit;

	// 用户在线
	CButton cBtnOnline;

	// 系统管理员
	CButton cBtnSysAdmin;

	// 部门管理员
	CButton cBtnDepartAdmin;

	// 使用时效
	CDateTimeCtrl dtpEndTime;

	// 用户列表的页数
	CComboBox cmbPage;

	// GroupBox
	CStatic GrpSearch;

	// 玩家所在部门
	CComboBox cmbDepart;

	// 指示对话框当前状态
	int dlgStatus;

public:
	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	//处理快捷键响应函数
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// 请求所有用户信息列表
	void InitUserList();

	// 翻页查询用户列表
	afx_msg void OnCbnSelchangeCmbpage();

	// 切换选项卡进行操作
	afx_msg void OnTcnSelchangeTabusermanage(NMHDR *pNMHDR, LRESULT *pResult);

	// 请求所有部门列表
	void DepartList();

	// 添加或修改用户信息
	afx_msg void OnBnClickedAdduser();

	// 添加用户信息
	void AddUser();

	// 修改用户信息
	void EditUser();

	// 重置信息
	afx_msg void OnBnClickedReset();

	// 单击用户列表保存当前行号
	afx_msg void OnNMClickListuser(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击用户列表进行删除
	afx_msg void OnNMDblclkListuser(NMHDR *pNMHDR, LRESULT *pResult);

	// 右键点击用户列表分配权限
	afx_msg void OnNMRclickListuser(NMHDR *pNMHDR, LRESULT *pResult);

	//修改用户密码
	afx_msg void OnModiUserPwd();

	// 给选中用户分配权限
	afx_msg void OnPopedomManage();

	//重置用户MAC
	afx_msg void OnUpdateUserMAC();

	// 设置帐号为系统管理员
	afx_msg void OnBnClickedChecksysmanage();

	// 设置帐号为部门管理员
	afx_msg void OnBnClickedCheckdepart();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//关闭对话框
	afx_msg void OnClose();
};
