#ifndef CINI_H_
#define CINI_H_


#define DF_DEFAULT_LENGTH 2048

class __declspec(dllexport) CIni  
{
public:
	 CIni();
	 ~CIni();

	 // ���ֽ�תΪ�ֽ�
	 char* wcharToChar(CString str);

	 // �ֽ�תΪ���ֽ�
	 //wchar_t* charToWChar(char* str);
	 wchar_t* charToWChar(char* str);

	 // ���ֽ�תΪʱ��
	 CTime StrToTime(CString strTime);

	 // ���ֽ�תΪ��ϸʱ��
	 CTime DetStrToTime(CString strTime);

	 // ʱ��תΪ���ֽ�
	 CString TimeToStr(CDateTimeCtrl& DateTime);

	 // ��ȡ�ֽڳ���
	 int getLength();

	 // ��ȡini�ļ������ֵ
	CString ReadValue(CString strSection,CString strKey);

	//�ж�CString�ǲ�������
	bool bIsNumber(CString str);

private:
	char* psText;
	wchar_t* pwText;
	int parseLength;
};

#endif