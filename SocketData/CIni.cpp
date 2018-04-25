// rwini.cpp: implementation of the Crwini class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CIni.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIni::CIni()
{
	psText = new char[2048];
	ZeroMemory( psText, 2048 );
	pwText = new wchar_t[2048];
	ZeroMemory( pwText, 2048 );
}

CIni::~CIni()
{
	if(psText != NULL)
	{
		delete[] psText;
		psText = NULL;
	}
	if(pwText != NULL)
	{
		delete[] pwText;
		pwText = NULL;
	}
}

// ���ֽ�תΪ�ֽ�
char* CIni::wcharToChar(CString str)
{
	ZeroMemory( psText, 2048 );
	int length=str.GetLength();	
	strncpy(psText,str,length);  
	psText[length+1]=0;
	parseLength = length;
	return psText;
}

//�ֽ�תΪ���ֽ�
wchar_t* CIni::charToWChar(char* str)
{
	ZeroMemory( pwText, 2048 );
	DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);	
	parseLength=MultiByteToWideChar(CP_ACP, 0, str, -1, pwText, dwNum);
	pwText[dwNum+1]='\0';
	return pwText;
}

// ���ֽ�תΪʱ��
CTime CIni::StrToTime(CString strTime)
{
	try
	{
		int nYear,nMonth,nDay;
		int mYear,mMonth,mDay;
		sscanf(strTime,"%d-%d-%d",&nYear,&nMonth,&nDay);
		sscanf(strTime,"%d/%d/%d",&mYear,&mMonth,&mDay);
		
		if(nMonth>=1 && nMonth<=12 && nDay>=1 && nDay<=31)
		{
			CTime Time(nYear,nMonth,nDay,0,0,0);	
			return Time;
		}
		else if(mMonth>=1 && mMonth<=12 && mDay>=1 && mDay<=31)
		{
			CTime Time(mYear,mMonth,mDay,0,0,0);
			return Time;
		}  
		else
		{
			CTime Time = CTime::GetCurrentTime();//��ȡ��ǰʱ��
			return Time;
		}		
	}
	catch(...)
	{
		CTime Time = CTime::GetCurrentTime();//��ȡ��ǰʱ��
		return Time;
	}
}

// ���ֽ�תΪ��ϸʱ��
CTime CIni::DetStrToTime(CString strTime)
{
    int nYear, nMonth, nDate, nHour, nMin, nSec; 
	int mYear, mMonth, mDate, mHour, mMin, mSec; 
	sscanf(strTime, "%d-%d-%d  %d:%d:%d", &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);  
    sscanf(strTime, "%d/%d/%d  %d:%d:%d", &mYear, &mMonth, &mDate, &mHour, &mMin, &mSec);
	CTime Time;
	if(nMonth>=1 && nMonth<=12 && nDate>=1 && nDate<=31)
	{
		CTime Time(nYear,nMonth,nDate,nHour,nMin,nSec);
	}
	else if(mMonth>=1 && mMonth<=12 && mDate>=1 && mDate<=31)
	{
		CTime Time(mYear,mMonth,mDate,mHour,mMin,mSec);		
	}
	return Time;
}

// ʱ��תΪ���ֽ�
CString CIni::TimeToStr(CDateTimeCtrl& DateTime)
{
    CTime Time;
    DateTime.GetTime(Time);
    return Time.Format("%Y/%m/%d");
}

// ��ȡ�ֽڳ���
int CIni::getLength()
{
	return parseLength;
}

// ��ȡini�ļ������ֵ
CString CIni::ReadValue(CString strSection,CString strKey)
{
	char strValue[DF_DEFAULT_LENGTH];
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\Global.ini");
	if(GetPrivateProfileString(strSection,strKey,"",strValue,2048,filepath)!=-1)
	{
		return (LPSTR)&strValue;
	}
	return "";
}

//�ж�CString�ǲ�������
bool CIni::bIsNumber(CString str)
{
    LPCTSTR pszText;
    pszText=str;
    for( int i = 0; i < lstrlen( pszText ); i++ )
        if( !_istdigit( pszText[ i ] ) )
            return false;
    return true;
}