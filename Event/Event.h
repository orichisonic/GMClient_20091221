#ifndef EVENT_H_
#define EVENT_H_

#include "..\\SocketData\\SocketData.h"
#pragma comment(lib,"..\\SocketData\\Debug\\SocketData.lib")
#include "MSocket.h"
#include "Resource.h"


// CEventApp
// 有关此类实现的信息，请参阅 Event.cpp
//

class __declspec(dllexport) CEventApp : public CWinApp
{
public:
	CEventApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
#endif
