// MainFrm.h : CMainFrame 类的接口
//


#pragma once
class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 属性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//处理快捷键响应函数
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	//截获系统消息
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	//CStatusBar  m_wndStatusBar;
	//CToolBar    m_wndToolBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:

	//切分总界面
	CSplitterWnd wndSplitter;

	//切分对话框界面
	CSplitterWnd wndSplitDlg;

	// 创建客户端
	BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	// 接收模块列表数据
	LRESULT OnReceiveMessage(WPARAM wParam, LPARAM lParam);

	//判断服务器有没有超时
//	afx_msg void OnTimer(UINT nIDEvent);

	//服务器已断开SOCKET连接
	LRESULT OnSocketClose(WPARAM wParam, LPARAM lParam);
	
	// 选择不同的菜单项
	void OnMyMenuSelect(UINT nID);

	//用于接收数据
	CPacketHead packethead;

	//关闭窗体
	afx_msg void OnClose();		
	bool ReturnActive(unsigned char * lpRecvBuf, int length);
	bool ReturnActive(void);
	bool CMainFrame::GetLocalDllFile(char* dllname);
};


