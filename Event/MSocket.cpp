#include "StdAfx.h"
#include ".\msocket.h"

#define MAXBUFFER 8192*1000

#define BUFF_SIZE 1024 *3096

static SOCK_IO_DATA m_TempRecvData;	
static bool flag=false;


CMSocket::CMSocket(void)
{
	lpRecvbuf = NULL;

	m_sIntegerityRecvData.lpData = new char[BUFF_SIZE];
	m_sIntegerityRecvData.dwDataLen = 0;
	if(flag==false)
	{
		m_TempRecvData.lpData = new char[BUFF_SIZE];
	//	m_TempRecvData.lpData=(LPSTR)&buf;
		m_TempRecvData.dwDataLen = 0;
		flag=true;
	}
	
}

CMSocket::~CMSocket(void)
{
	MyDestory();
	delete[] m_sIntegerityRecvData.lpData;
}

// 接收数据
int CMSocket::MyReceive()
{/*
 MyDestory();
 lpRecvbuf = new unsigned char[MAXBUFFER];
 ZeroMemory(lpRecvbuf, MAXBUFFER);
 int actlength=0;
 unsigned char* tmpprecvbuf=NULL;
 int i=1;
 int tmpLength = 0;
 if((tmpLength = recv(m_socket,(char *)lpRecvbuf+actlength,MAXBUFFER,0)) == SOCKET_ERROR)
 {
 return -1;
 }
 actlength = actlength + tmpLength;
 while(*(lpRecvbuf+actlength-1)!=0xEF)
 {
 i++;
 tmpprecvbuf=new unsigned char[MAXBUFFER*i];
 ZeroMemory(tmpprecvbuf, MAXBUFFER*i);
 memcpy(tmpprecvbuf,lpRecvbuf,actlength);
 if(lpRecvbuf != NULL)
 {
 delete[] lpRecvbuf;
 lpRecvbuf = NULL;
 }

 lpRecvbuf=tmpprecvbuf;
 if((tmpLength = recv(m_socket,(char *)lpRecvbuf+actlength,MAXBUFFER,0)) == SOCKET_ERROR)
 {
 return -1;
 }
 actlength = actlength + tmpLength;
 }
 */
	int actlength = 0;

	char *szRecvBuff=new char[BUFF_SIZE];
	ZeroMemory(szRecvBuff,BUFF_SIZE);
	int nRecvBytes = recv(m_socket, szRecvBuff, BUFF_SIZE, 0);

	//if(nRecvBytes==8)
	//{
		//send(m_socket,"88888888",8,0);
		//return -1;
	//}

	if (0 == nRecvBytes)
	{
		actlength = -1;
	}
	else if (SOCKET_ERROR == nRecvBytes)
	{
		actlength = -1;
	}
	else
	{
		LPSOCK_IO_DATA lpdata = new SOCK_IO_DATA;
		lpdata->dwDataLen = nRecvBytes;
		lpdata->lpData = new char[lpdata->dwDataLen];
		memcpy((LPVOID)lpdata->lpData,szRecvBuff, nRecvBytes);
		m_QueueRecvData.push(lpdata);
	}
	delete[] szRecvBuff;
	szRecvBuff=NULL;
	if (0 == MakeIntegerityData())
		return -1;

	return m_sIntegerityRecvData.dwDataLen;
}

// @ret 0 NO_INTEGRITY_DATA
//		>0 data-length
int CMSocket::MakeIntegerityData()
{
	m_sIntegerityRecvData.dwDataLen = 0;

	while(!m_QueueRecvData.empty())
	{
		int nSeparaterNum = 0;
		LPSOCK_IO_DATA lpRecvData = m_QueueRecvData.front();
		m_QueueRecvData.pop();
		memcpy((LPVOID)(m_TempRecvData.lpData+m_TempRecvData.dwDataLen),(LPVOID)lpRecvData->lpData, lpRecvData->dwDataLen);
		m_TempRecvData.dwDataLen += lpRecvData->dwDataLen;
		delete[] lpRecvData->lpData;
		delete lpRecvData;

		for (int i=0; i<m_TempRecvData.dwDataLen; i++)
		{
			unsigned char ch_str=m_TempRecvData.lpData[i];

			if (ch_str == 0XEF||ch_str==0xFE)
				nSeparaterNum++;

			if (2 == nSeparaterNum)
			{
				memcpy((LPVOID)m_sIntegerityRecvData.lpData,(LPVOID)m_TempRecvData.lpData, ++i);
				m_sIntegerityRecvData.dwDataLen += i;
				ZeroMemory(m_TempRecvData.lpData,i);
				m_TempRecvData.dwDataLen=m_TempRecvData.dwDataLen-i;

				for (int j=0; i<m_TempRecvData.dwDataLen; j++)
				{
					i++;
					m_TempRecvData.lpData[j] = m_TempRecvData.lpData[i];
				}

				break;
			}
		}
	}

	return m_sIntegerityRecvData.dwDataLen;
}

// 发送部分数据
// ??????????????????????
int CMSocket::SendBuf(char* buff,int length)
{
	int sended = 0;
	while(sended < length)
	{
		int now = send(m_socket, buff+sended, length-sended ,0);
		if(now==SOCKET_ERROR)
		{
			break;
		}
		sended += now;
	}
	return sended;
}

// 发送全部数据并判断
bool CMSocket::SendData(char *msg,int wSize)
{
	return SendBuf(msg, wSize) >= wSize;
}

// 设置m_socket
void CMSocket::SetSocket(SOCKET tmpsocket)
{
	m_socket = tmpsocket;  
}

//获取m_socket
SOCKET CMSocket::GetSocket()
{
	return m_socket;
}

// 销毁m_socket
bool CMSocket::MyDestory(void)
{
	if(lpRecvbuf != NULL)
	{
		delete[] lpRecvbuf;
		lpRecvbuf = NULL;
	}
	return false;
}

//返回接收到的数据
char* CMSocket::recvBuffer()
{
	//return lpRecvbuf;
	return m_sIntegerityRecvData.lpData;
}
