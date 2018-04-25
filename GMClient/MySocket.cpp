// MySocket.cpp : 实现文件
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

// 设置句柄
void CMySocket::SetParentHwnd(HWND m_hwnd)
{
	m_parenthwnd=m_hwnd;
}

// Socket接收
void CMySocket::OnReceive(int nErrorCode)
{
	SendMessage(m_parenthwnd,UM_RECEIVE,0,(LPARAM)this);
	CSocket::OnReceive(nErrorCode);
}

// Socket关闭
void CMySocket::OnClose(int nErrorCode)
{
	SendMessage(m_parenthwnd,UM_CLOSE,0,(LPARAM)this);
	CSocket::OnClose(nErrorCode);
}
