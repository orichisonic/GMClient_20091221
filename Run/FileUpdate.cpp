#include "stdafx.h"
#include "FileUpdate.h"

#include <Winbase.h> 
#pragma comment(lib,"Version.lib")


//构造函数
CFileUpdate::CFileUpdate()
{
}

//析构函数
CFileUpdate::~CFileUpdate()
{
}

//获取本地的dll文件
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
		//遍历
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

//获取本地的exe文件
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
		//遍历
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

//获取本地的ini文件
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
		//遍历
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

//获取文件的版本号
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
        TEXT("\\StringFileInfo\\040904b0\\FileVersion"), //0409英文,0804中文
        //04b0即1252,ANSI
        //可以从ResourceView中的Version中BlockHeader中看到
        //可以测试的属性
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