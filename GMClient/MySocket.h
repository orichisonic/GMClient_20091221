#ifndef MYSOCKET_H_
#define MYSOCKET_H_

class CMySocket : public CSocket
{
public:
	CMySocket();
	virtual ~CMySocket();   

public:
	//���
	HWND m_parenthwnd;

	// ���þ��
	void SetParentHwnd(HWND m_hwnd);
	
	// Socket����
	virtual void OnReceive(int nErrorCode);

	// Socket�ر�
	virtual void OnClose(int nErrorCode);
};

#endif