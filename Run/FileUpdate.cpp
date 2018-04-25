#include "stdafx.h"
#include "FileUpdate.h"

#include <Winbase.h> 
#pragma comment(lib,"Version.lib")


//���캯��
CFileUpdate::CFileUpdate()
{
}

//��������
CFileUpdate::~CFileUpdate()
{
}

//��ȡ���ص�dll�ļ�
CString CFileUpdate::GetLocalDllFile(CString pszPath)
{
	CString strPath = pszPath;
    strPath += _T ("*.dll");  
	CString FileInfo = "";
	CString tmpFileInfo = "";

    HANDLE hFind;  
    WIN32_FIND_DATA fd;  
    int nCount = 0;  

    if ((hFind = ::FindFirstFile(strPath,&fd)) !=  INVALID_HANDLE_VALUE)    
    {
		tmpFileInfo.Format("%s,",fd.cFileName);
		FileInfo += tmpFileInfo;
		//����
		while(::FindNextFile(hFind, &fd))
		{
			if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				tmpFileInfo.Format("%s,",fd.cFileName);
				FileInfo += tmpFileInfo;
			}
		}
		::FindClose(hFind);  
    }   
	return FileInfo;
}

//��ȡ���ص�exe�ļ�
CString CFileUpdate::GetLocalExeFile(CString pszPath)
{
	CString strPath = pszPath;
    strPath += _T ("*.exe");  
	CString FileInfo = "";
	CString tmpFileInfo = "";

    HANDLE hFind;  
    WIN32_FIND_DATA fd;  
    int nCount = 0;  

   if ((hFind = ::FindFirstFile(strPath,&fd)) !=  INVALID_HANDLE_VALUE)    
    {
		tmpFileInfo.Format("%s,",fd.cFileName);
		FileInfo += tmpFileInfo;
		//����
		while(::FindNextFile(hFind, &fd))
		{
			if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				tmpFileInfo.Format("%s,",fd.cFileName);
				FileInfo += tmpFileInfo;
			}
		}
		::FindClose(hFind);  
    }   
	return FileInfo;
}

//��ȡ���ص�ini�ļ�
CString CFileUpdate::GetLocalIniFile(CString pszPath)
{
	CString strPath = pszPath;
    strPath += _T ("*.ini");  
	CString FileInfo = "";
	CString tmpFileInfo = "";

    HANDLE hFind;  
    WIN32_FIND_DATA fd;  
    int nCount = 0;  

    if ((hFind = ::FindFirstFile(strPath,&fd)) !=  INVALID_HANDLE_VALUE)    
    {
		tmpFileInfo.Format("%s,",fd.cFileName);
		FileInfo += tmpFileInfo;
		//����
		while(::FindNextFile(hFind, &fd))
		{
			if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				tmpFileInfo.Format("%s,",fd.cFileName);
				FileInfo += tmpFileInfo;
			}
		}
		::FindClose(hFind);  
    }   
	return FileInfo;
}

//��ȡ�ļ��İ汾��
CString CFileUpdate::GetVersionFromPath(CString IDEPath)
{
	DWORD dwLen = 0;
    char* lpData = NULL;

    dwLen = GetFileVersionInfoSize(IDEPath, 0);
    if (0 == dwLen)
	{
        return CString("");
	}

    lpData =new char [dwLen+1];

    if(!GetFileVersionInfo(IDEPath, 0, dwLen, lpData))
    {
        delete lpData;
        return CString("");
    }

    LPVOID lpBuffer = NULL;
    UINT uLen = 0;

    BOOL bSuccess = VerQueryValue(lpData,
        TEXT("\\StringFileInfo\\040904b0\\FileVersion"), //0409Ӣ��,0804����
        //04b0��1252,ANSI
        //���Դ�ResourceView�е�Version��BlockHeader�п���
        //���Բ��Ե�����
        /*
        CompanyName
        FileDescription
        FileVersion
        InternalName
        LegalCopyright
        OriginalFilename
        ProductName
        ProductVersion
        Comments
        LegalTrademarks
        PrivateBuild
        SpecialBuild
        */             
        &lpBuffer,
        &uLen);
    if (!bSuccess)
    {
        delete lpData;
        return CString("");
    }
    CString Ret = (char*)lpBuffer;
    Ret.Replace(',', '.');
    Ret.Replace(' ', '0');

	if(lpData != NULL)
	{
        delete [] lpData;
		lpData = NULL;
	}
    return Ret;
}