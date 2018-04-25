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
	//������յ�������
	unsigned char* lpRecvbuf;

	// ��ȡm_socket
	SOCKET m_socket;

public:	

	// ���շ��͵�����
	int MyReceive();

	// ����ȫ�����ݲ��ж�
	bool SendData(char *msg,int wSize);

	// ���Ͳ�������
	int SendBuf(char* buff,int length);

	// ����m_socket
	void SetSocket(SOCKET tmpsocket);

	//��ȡm_socket
	SOCKET GetSocket();

	// ����m_socket
	bool MyDestory(void);

	// ���ؽ��յ�������
	char* recvBuffer();

	// Attribute
public:

	int MakeIntegerityData();
	SOCK_IO_DATA m_sIntegerityRecvData;
	std::queue<LPSOCK_IO_DATA> m_QueueRecvData;
};

#endif