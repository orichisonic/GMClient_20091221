#ifndef FILEUPDATE_H_
#define FILEUPDATE_H_

class CFileUpdate
{
public:
	//���캯��
	CFileUpdate();

	//��������
	~CFileUpdate();
public:
	//��ȡ���ص�dll�ļ�
	CString GetLocalDllFile(CString pszPath);

	//��ȡ���ص�exe�ļ�
	CString GetLocalExeFile(CString pszPath);

	//��ȡ���ص�ini�ļ�
	CString GetLocalIniFile(CString pszPath);

	//��ȡ�ļ��İ汾��
	CString GetVersionFromPath(CString IDEPath);
};

#endif