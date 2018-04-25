#include "StdAfx.h"
#include "DataOper.h"

CDataOper::CDataOper(void)
{
}

CDataOper::~CDataOper(void)
{
}

void CDataOper::SetSocket(SOCKET sock)
{
	m_socketRecvSend.SetSocket(sock);
}

BOOL CDataOper::SendQuery(CSocketData &socketdata, CEnumCore::Msg_Category ecategory, CEnumCore::ServiceKey eServiceKey)
{
	// TFLV 结构总长度.
	int nDataLen = socketdata.EnBody();
	ASSERT(0 < nDataLen);

	//添加造包头
	CPacketHead packethead;	
	packethead.Create(nDataLen);
	packethead.AddHeader(1, ecategory, eServiceKey, nDataLen);

	// 构造加密后的数据包.
	int nAllDataLen = nDataLen;	//数据包总长度.
	packethead.EnSendBuf(&nAllDataLen, (unsigned char*)socketdata.getDes(), packethead.m_packethead.bodylen);

	//发送数据
	if(!m_socketRecvSend.SendData((char*)packethead.getSendBuf(), nAllDataLen))
	{
//		MessageBox(NULL,ReadValue("MGM","GM_ERROR_SENDDATAERROR"),ReadValue("MGM","ERROR"),MB_OK);
		return false;
	}

	return TRUE;
}