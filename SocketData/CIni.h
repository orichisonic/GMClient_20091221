#ifndef CINI_H_
#define CINI_H_


#define DF_DEFAULT_LENGTH 2048

class __declspec(dllexport) CIni  
{
public:
	 CIni();
	 ~CIni();

	 // 宽字节转为字节
	 char* wcharToChar(CString str);

	 // 字节转为宽字节
	 //wchar_t* charToWChar(char* str);
	 wchar_t* charToWChar(char* str);

	 // 宽字节转为时间
	 CTime StrToTime(CString strTime);

	 // 宽字节转为详细时间
	 CTime DetStrToTime(CString strTime);

	 // 时间转为宽字节
	 CString TimeToStr(CDateTimeCtrl& DateTime);

	 // 获取字节长度
	 int getLength();

	 // 读取ini文件里面的值
	CString ReadValue(CString strSection,CString strKey);

	//判断CString是不是数字
	bool bIsNumber(CString str);

private:
	char* psText;
	wchar_t* pwText;
	int parseLength;
};

#endif