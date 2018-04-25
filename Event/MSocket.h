#ifndef MSOCKET_H_
#define MSOCKET_H_

#include <afxsock.h>

#include <queue>

typedef struct _SOCK_IO_DATA_
{
	LPSTR	lpData;
	DWORD	dwDataLen;
} SOCK_IO_DATA, *LPSOCK_IO_DATA;

class  __declspec(dllexport) CMSocket
{
public:
	CMSocket(void);
	~CMSocket(void);

private:
	//保存接收到的数据
	unsigned char* lpRecvbuf;

	// 获取m_socket
	SOCKET m_socket;

public:	

	// 接收发送的数据
	int MyReceive();

	// 发送全部数据并判断
	bool SendData(char *msg,int wSize);

	// 发送部分数据
	int SendBuf(char* buff,int length);

	// 设置m_socket
	void SetSocket(SOCKET tmpsocket);

	//获取m_socket
	SOCKET GetSocket();

	// 销毁m_socket
	bool MyDestory(void);

	// 返回接收到的数据
	char* recvBuffer();

	// Attribute
public:

	int MakeIntegerityData();
	SOCK_IO_DATA m_sIntegerityRecvData;
	std::queue<LPSOCK_IO_DATA> m_QueueRecvData;
};

#endif