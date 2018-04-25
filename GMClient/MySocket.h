#ifndef MYSOCKET_H_
#define MYSOCKET_H_

class CMySocket : public CSocket
{
public:
	CMySocket();
	virtual ~CMySocket();   

public:
	//句柄
	HWND m_parenthwnd;

	// 设置句柄
	void SetParentHwnd(HWND m_hwnd);
	
	// Socket接收
	virtual void OnReceive(int nErrorCode);

	// Socket关闭
	virtual void OnClose(int nErrorCode);
};

#endif