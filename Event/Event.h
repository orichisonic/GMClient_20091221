#ifndef EVENT_H_
#define EVENT_H_

#include "..\\SocketData\\SocketData.h"
#pragma comment(lib,"..\\SocketData\\Debug\\SocketData.lib")
#include "MSocket.h"
#include "Resource.h"


// CEventApp
// �йش���ʵ�ֵ���Ϣ������� Event.cpp
//

class __declspec(dllexport) CEventApp : public CWinApp
{
public:
	CEventApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
#endif
