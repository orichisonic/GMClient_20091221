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

	//���ڷ���/��������.
	CMSocket m_socketRecvSend;
};
