// Run.cpp : ����Ӧ�ó��������Ϊ��
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


// CRunApp ����

CRunApp::CRunApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CRunApp ����

CRunApp theApp;


// CRunApp ��ʼ��

BOOL CRunApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

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

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

//�ƶ��ļ�
BOOL CRunApp::MoveFiles()
{
	try
	{
		CFileUpdate fUpdate;

		char path[256];
		GetCurrentDirectory(256,path);
		char FilePath[256];
		char localFilePath[256];
		wsprintf(localFilePath,"%s%s",path,"\\");//��ȡ�����ļ�Ŀ¼�ĵ�ַ
		wsprintf(FilePath,"%s%s",path,"\\temp\\");//��ȡ�����ļ��ĵ�ַ

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

			//����
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

			//����
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

			//����
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
		wsprintf(execFilepath,"%s%s",path,"\\GMClient.exe");//��ȡ�����ļ��ĵ�ַ
		ShellExecute(NULL,"open", execFilepath, NULL, NULL, SW_SHOW);
	}
	catch(...)
	{
	}
	return TRUE;
}