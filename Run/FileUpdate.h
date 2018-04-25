#ifndef FILEUPDATE_H_
#define FILEUPDATE_H_

class CFileUpdate
{
public:
	//构造函数
	CFileUpdate();

	//析构函数
	~CFileUpdate();
public:
	//获取本地的dll文件
	CString GetLocalDllFile(CString pszPath);

	//获取本地的exe文件
	CString GetLocalExeFile(CString pszPath);

	//获取本地的ini文件
	CString GetLocalIniFile(CString pszPath);

	//获取文件的版本号
	CString GetVersionFromPath(CString IDEPath);
};

#endif