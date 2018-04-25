// MySocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GMClient.h"
#include "MySocket.h"
#include ".\mysocket.h"


// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}

// ���þ��
void CMySocket::SetParentHwnd(HWND m_hwnd)
{
	m_parenthwnd=m_hwnd;
}

// Socket����
void CMySocket::OnReceive(int nErrorCode)
{
	SendMessage(m_parenthwnd,UM_RECEIVE,0,(LPARAM)this);
	CSocket::OnReceive(nErrorCode);
}

// Socket�ر�
void CMySocket::OnClose(int nErrorCode)
{
	SendMessage(m_parenthwnd,UM_CLOSE,0,(LPARAM)this);
	CSocket::OnClose(nErrorCode);
}
