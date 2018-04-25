// MainFrm.h : CMainFrame ��Ľӿ�
//


#pragma once
class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//�����ݼ���Ӧ����
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	//�ػ�ϵͳ��Ϣ
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	//CStatusBar  m_wndStatusBar;
	//CToolBar    m_wndToolBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:

	//�з��ܽ���
	CSplitterWnd wndSplitter;

	//�зֶԻ������
	CSplitterWnd wndSplitDlg;

	// �����ͻ���
	BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	// ����ģ���б�����
	LRESULT OnReceiveMessage(WPARAM wParam, LPARAM lParam);

	//�жϷ�������û�г�ʱ
//	afx_msg void OnTimer(UINT nIDEvent);

	//�������ѶϿ�SOCKET����
	LRESULT OnSocketClose(WPARAM wParam, LPARAM lParam);
	
	// ѡ��ͬ�Ĳ˵���
	void OnMyMenuSelect(UINT nID);

	//���ڽ�������
	CPacketHead packethead;

	//�رմ���
	afx_msg void OnClose();		
	bool ReturnActive(unsigned char * lpRecvBuf, int length);
	bool ReturnActive(void);
	bool CMainFrame::GetLocalDllFile(char* dllname);
};


