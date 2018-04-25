#pragma once

#include "..\\Event\\Event.h"
#pragma comment(lib,"..\\Event\\Debug\\Event.lib")

class CDataOper
{
public:
	CDataOper(void);
	~CDataOper(void);

	void SetSocket(SOCKET sock);

	BOOL SendQuery(CSocketData &socketdata, CEnumCore::Msg_Category ecategory, CEnumCore::ServiceKey eServiceKey);

private:

	//用于发送/接收数据.
	CMSocket m_socketRecvSend;
};
