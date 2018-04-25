#ifndef GLOBALSTRUCT_H_
#define GLOBALSTRUCT_H_

#include "..\\Global\\Global.h"
#pragma comment(lib,"..\\Global\\Debug\\Global.lib")

class __declspec(dllexport) CGlobalStruct
{
public:
	CGlobalStruct(void);
	~CGlobalStruct(void);

public:
	// 数据单元的定义
	struct TFLV
	{
		unsigned int nIndex;
		CEnumCore::TagName m_tagName;//2个字节
		CEnumCore::TagFormat m_tagFormat;//2个字节
		unsigned int m_tvlength;//4个字节
		unsigned char lpdata[2048];
		TFLV()
		{
			nIndex=0;
			ZeroMemory(lpdata, 2048);
		}  
	};

	// 数据包的定义
	struct PACKETHEAD
	{
		unsigned int uId;//4个字节
		CEnumCore::Msg_Category m_msg_category;//2个字节
		CEnumCore::ServiceKey m_servicekey;//2个字节
		unsigned char SystemData[6];//6个字节
		unsigned int bodylen;//4个字节
	};
};

#endif