// Run.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Run.h"
#include "RunDlg.h"
#include "FileUpdate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRunApp

BEGIN_MESSAGE_MAP(CRunApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRunApp 构造

CRunApp::CRunApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CRunApp 对象

CRunApp theApp;


// CRunApp 初始化

BOOL CRunApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	MoveFiles();

	//CRunDlg dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{		
	//}
	//else
	//{
	//}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	// 而不是启动应用程序的消息泵。
	return FALSE;
}

//移动文件
BOOL CRunApp::MoveFiles()
{
	try
	{
		CFileUpdate fUpdate;

		char path[256];
		GetCurrentDirectory(256,path);
		char FilePath[256];
		char localFilePath[256];
		wsprintf(localFilePath,"%s%s",path,"\\");//获取本地文件目录的地址
		wsprintf(FilePath,"%s%s",path,"\\temp\\");//获取配置文件的地址

		CString localFileName = "";
		CString tempFileName = "";

		CString strPath = FilePath;
		strPath += _T ("*.dll");

		HANDLE hFind;  
		WIN32_FIND_DATA fd; 

		if ((hFind = ::FindFirstFile(strPath,&fd)) !=  INVALID_HANDLE_VALUE)    
		{
			localFileName.Format("%s%s", localFilePath, fd.cFileName);
			tempFileName.Format("%s%s", FilePath, fd.cFileName);

			SetFileAttributes(localFileName, FILE_ATTRIBUTE_NORMAL);  
			SetFileAttributes(tempFileName, FILE_ATTRIBUTE_NORMAL);  

			DeleteFile(localFileName);
			while(!CopyFile(tempFileName, localFileName, FALSE)){}
			while(!DeleteFile(tempFileName)){}

			//遍历
			while(::FindNextFile(hFind, &fd))
			{
				if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					localFileName.Format("%s%s", localFilePath, fd.cFileName);
					tempFileName.Format("%s%s", FilePath, fd.cFileName);

					SetFileAttributes(localFileName, FILE_ATTRIBUTE_NORMAL);  
			        SetFileAttributes(tempFileName, FILE_ATTRIBUTE_NORMAL);  

					DeleteFile(localFileName);
					while(!CopyFile(tempFileName, localFileName, FALSE)){}
					while(!DeleteFile(tempFileName)){}
				}
			}
			::FindClose(hFind);  
		}  

		strPath.Replace("dll","exe");

		if ((hFind = ::FindFirstFile(strPath,&fd)) !=  INVALID_HANDLE_VALUE)    
		{
			localFileName.Format("%s%s", localFilePath, fd.cFileName);
			tempFileName.Format("%s%s", FilePath, fd.cFileName);

			SetFileAttributes(localFileName, FILE_ATTRIBUTE_NORMAL);  
			SetFileAttributes(tempFileName, FILE_ATTRIBUTE_NORMAL);  

			DeleteFile(localFileName);
			while(!CopyFile(tempFileName, localFileName, FALSE)){}
			while(!DeleteFile(tempFileName)){}

			//遍历
			while(::FindNextFile(hFind, &fd))
			{
				if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					localFileName.Format("%s%s", localFilePath, fd.cFileName);
					tempFileName.Format("%s%s", FilePath, fd.cFileName);

					SetFileAttributes(localFileName, FILE_ATTRIBUTE_NORMAL);  
			        SetFileAttributes(tempFileName, FILE_ATTRIBUTE_NORMAL);  

					DeleteFile(localFileName);
					while(!CopyFile(tempFileName, localFileName, FALSE)){}
					while(!DeleteFile(tempFileName)){}
				}
			}
			::FindClose(hFind);  
		}  

		strPath.Replace("exe","ini");

		if ((hFind = ::FindFirstFile(strPath,&fd)) !=  INVALID_HANDLE_VALUE)    
		{
			localFileName.Format("%sConfig\\%s", localFilePath, fd.cFileName);
			tempFileName.Format("%s%s", FilePath, fd.cFileName);

			SetFileAttributes(localFileName, FILE_ATTRIBUTE_NORMAL);  
			SetFileAttributes(tempFileName, FILE_ATTRIBUTE_NORMAL);  

			DeleteFile(localFileName);
			while(!CopyFile(tempFileName, localFileName, FALSE)){}
			while(!DeleteFile(tempFileName)){}

			//遍历
			while(::FindNextFile(hFind, &fd))
			{
				if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					localFileName.Format("%sConfig\\%s", localFilePath, fd.cFileName);
					tempFileName.Format("%s%s", FilePath, fd.cFileName);

					SetFileAttributes(localFileName, FILE_ATTRIBUTE_NORMAL);  
			        SetFileAttributes(tempFileName, FILE_ATTRIBUTE_NORMAL);  

					DeleteFile(localFileName);
					while(!CopyFile(tempFileName, localFileName, FALSE)){}
					while(!DeleteFile(tempFileName)){}
				}
			}
			::FindClose(hFind);  
		}  

		Sleep(1000);

		char execFilepath[256];
		wsprintf(execFilepath,"%s%s",path,"\\GMClient.exe");//获取配置文件的地址
		ShellExecute(NULL,"open", execFilepath, NULL, NULL, SW_SHOW);
	}
	catch(...)
	{
	}
	return TRUE;
}