#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#import "c:\program files\common files\system\ado\msado15.dll"\
	no_namespace \
	rename ("EOF", "adoEOF")


// CWAMailSend 对话框

class CWAMailSend : public CDialog
{
	DECLARE_DYNAMIC(CWAMailSend)

public:
	CWAMailSend(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWAMailSend();

// 对话框数据
	enum { IDD = IDD_DLGMAILSEND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 所有角色名信息
	CMap<int,int,CString,CString> UserList;

	// 所有邮件标题信息
	CMap<int,int,CString,CString> TitleList;

	// 所有邮件内容信息
	CMap<int,int,CString,CString> ContentList;

	// 游戏服务器IP
	CString ServerIP;

	//玩家角色名
	CString UserNick;

	//邮件标题
	CString MailTitle;

	//邮件内容
	CString MailContent;

public:
	// CComboBox游戏服务器
	CComboBox cmbServer;

	//CProgressCtrl发送道具进度条
	CProgressCtrl progMail;

	// 指示对话框当前状态
	int dlgStatus;

	//选择是否属于第一次发送邮件
	int nFirst;

	//待发送邮件的角色名数量
	int UserNum;

	//当前正在发送的角色序号
	int mCurNum;

public:
	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//获取选择的ServerIP
	afx_msg void OnCbnSelchangeCmbserver();

	//选择批量发送邮件的文件
	afx_msg void OnBnClickedBtnbrowse();

	//批量发送邮件信息
	afx_msg void OnBnClickedBtnsend();

	//读取xls文件
	bool ReadXls(CString m_filePath);

	//发送邮件
	void SendMail();

	//重置信息
	afx_msg void OnBnClickedBtnreset();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 关闭对话框
	afx_msg void OnClose();		
};
