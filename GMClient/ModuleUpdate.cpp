// ModuleUpdate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GMClient.h"
#include "ModuleUpdate.h"
#include ".\moduleupdate.h"

#include "FileUpdate.h"

// CModuleUpdate �Ի���

IMPLEMENT_DYNAMIC(CModuleUpdate, CDialog)
CModuleUpdate::CModuleUpdate(CWnd* pParent /*=NULL*/)
	: CDialog(CModuleUpdate::IDD, pParent)
{
}

CModuleUpdate::~CModuleUpdate()
{
}

void CModuleUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESSUPDATE, progUpdate);
	DDX_Control(pDX, IDC_EDITUPDATE, txtContent);
	DDX_Control(pDX, IDC_BTNUPDATE, btnUpdate);
	DDX_Control(pDX, IDC_LBLUPDATE, lblUpdate);
}


BEGIN_MESSAGE_MAP(CModuleUpdate, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTNUPDATE, OnBnClickedBtnupdate)
	ON_MESSAGE(UM_RECEIVE,OnLoginReceive)
END_MESSAGE_MAP()


// ��ʼ���Ի���
BOOL CModuleUpdate::OnInitDialog()
{
	CDialog::OnInitDialog();

	HICON hIcon = NULL;       
    hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME),IMAGE_ICON, 16, 16, 0);   
	SetIcon(hIcon, FALSE); 

	UpdateFileNum = 0;
	InitUI();// ��ʼ����ʾ�ַ�
	theApp.m_clientsocket.SetParentHwnd(this->m_hWnd);
	CheckUpdate();

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CModuleUpdate::InitUI()
{
	CIni mIni;

	SetWindowText(mIni.ReadValue("Global","UP_UI_Update"));

	SetDlgItemText(IDC_LBLUPDATE,mIni.ReadValue("Global","UP_UI_CheckUpdate"));
	SetDlgItemText(IDC_LBLCONTENT,mIni.ReadValue("Global","UP_UI_UpdateContent"));
	SetDlgItemText(IDC_BTNUPDATE,mIni.ReadValue("Global","UP_UI_Update"));
	SetDlgItemText(IDOK,mIni.ReadValue("Global","UP_UI_ResetGMTools"));
	SetDlgItemText(IDCANCEL,mIni.ReadValue("Global","Close"));
}

//���ñ�����ɫ
HBRUSH CModuleUpdate::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//����Ƿ���Ҫ����
void CModuleUpdate::CheckUpdate()
{
	try
	{
		CIni mIni;
		//CPacketHead packethead;		
	    CSocketData socketdata;

	    char path[256];
		GetCurrentDirectory(256,path);
		char filepath[256];
		wsprintf(filepath,"%s%s",path,"\\");//��ȡ�����ļ��ĵ�ַ

		CFileUpdate fUpdate;

		CString dllFileInfo = fUpdate.GetLocalDllFile(filepath);
		CString exeFileInfo = fUpdate.GetLocalExeFile(filepath);

		socketdata.InitCreate(1,2);//����2��������dll��exe�ļ���Ϣ��Ini�ļ���Ϣ
		int alllength=0;

		socketdata.AddTFLV(CEnumCore::TagName::UpdateFileName,CEnumCore::TagFormat::TLV_STRING,strlen(dllFileInfo),(unsigned char*)mIni.wcharToChar(dllFileInfo));//dll�汾��Ϣ
		socketdata.AddTFLV(CEnumCore::TagName::UpdateFilePath,CEnumCore::TagFormat::TLV_STRING,strlen(exeFileInfo),(unsigned char*)mIni.wcharToChar(exeFileInfo));//exe�汾��Ϣ

		alllength=socketdata.EnBody();

		theApp.packethead.Create(alllength);
		theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::CLIENT_PATCH_COMPARE,alllength);
		theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
		theApp.packetLength = alllength;

		theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//���Ͳ�ѯ�Ƿ���Ҫ���µ�����
		theApp.m_SendCount = 0;//�ظ����ʹ���Ϊ0

		::EnableWindow(this->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	}
	catch(...)
	{
	}
}

//�Զ�����
void CModuleUpdate::OnBnClickedBtnupdate()
{
	try
	{
		CIni mIni;
		//CPacketHead packethead;		
	    CSocketData socketdata;

		CString FileName = "";
		int FileSize = 0;
		CString FilePath = "";
		CString DownloadNow = mIni.ReadValue("Global","UP_UI_DownloadNow");
		CString refreshContent = "";
		progUpdate.SetRange(0,UpdateData.getQueryNum() + 1);
		progUpdate.SetStep(1);
		UpdateFileNum = 1;

		if(UpdateFileNum <= UpdateData.getQueryNum())
		{
			FileName = (LPCSTR)&UpdateData.getTLVByName(1, CEnumCore::TagName::UpdateFileName).lpdata;
			FileSize = atoi((LPCSTR)&UpdateData.getTLVByName(1, CEnumCore::TagName::UpdateFileSize).lpdata);
			FilePath = (LPCSTR)&UpdateData.getTLVByName(1, CEnumCore::TagName::UpdateFilePath).lpdata;

			socketdata.InitCreate(1,3);//����3��������dll��exe�ļ���Ϣ��·���ļ���Ϣ
			char strInt[10];
			ZeroMemory(strInt,10);
			int alllength=0;

			socketdata.AddTFLV(CEnumCore::TagName::UpdateFileName,CEnumCore::TagFormat::TLV_STRING,strlen(FileName),(unsigned char*)mIni.wcharToChar(FileName));//�ļ�����
			socketdata.AddTFLV(CEnumCore::TagName::UpdateFilePath,CEnumCore::TagFormat::TLV_STRING,strlen(FilePath),(unsigned char*)mIni.wcharToChar(FilePath));//�ļ�·��

			_itoa(FileSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UpdateFileSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char*)strInt);//�ļ�·��

			alllength=socketdata.EnBody();

			theApp.packethead.Create(alllength);
			theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::CLIENT_PATCH_UPDATE,alllength);
			theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
			theApp.packetLength = alllength;

			theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//���͸��µ�һ���ļ�������
			theApp.m_SendCount = 0;//�ظ����ʹ���Ϊ0

			::EnableWindow(this->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);

			progUpdate.StepIt();
			
			refreshContent.Format("%s%s", DownloadNow, FileName);
			lblUpdate.SetWindowText(refreshContent);
		}
	}
	catch(...)
	{
	}
}

// ���͵�¼��Ϣ֮����н���
LRESULT CModuleUpdate::OnLoginReceive(WPARAM wParam, LPARAM lParam)
{
	CIni mIni;

	CMSocket selfSocket;
	CPacketHead m_PacketHead;	
	CSocketData socketdata;
	
	int actlength=0;

	selfSocket.SetSocket(theApp.m_clientsocket.m_hSocket);
	actlength=selfSocket.MyReceive();//���շ�����Ϣ

	if(actlength == -1)
	{
		::EnableWindow(this->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
		::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	//	MessageBox(mIni.ReadValue("GLOBAL","MAIN_ERROR_RECVDATAERROR"),mIni.ReadValue("GLOBAL","ERROR"),MB_OK);
		return false;
	}

	m_PacketHead.Create(actlength);
	if(m_PacketHead.DeHead((unsigned char *)selfSocket.recvBuffer(),actlength))
	{

		char path[256];
		GetCurrentDirectory(256,path);
		char localFilePath[256];
		char filepath[256];
		wsprintf(localFilePath,"%s%s",path,"\\");//��ȡ�����ļ��ĵ�ַ
		wsprintf(filepath,"%s%s",path,"\\temp\\");//��ȡ�����ļ��ĵ�ַ

		theApp.m_SendCount = 0;//�ظ����ʹ���Ϊ0

		try
		{		
			switch((unsigned int)m_PacketHead.GetMessageID())
			{
			case CEnumCore::Message_Tag_ID::CLIENT_PATCH_COMPARE_RESP:
				{
					UpdateData.Create(m_PacketHead.m_packethead.bodylen/8);
					UpdateData.DeBody(m_PacketHead.getDataBuf()+18,m_PacketHead.m_packethead.bodylen);

					CGlobalStruct::TFLV m_tflv;
					m_tflv = UpdateData.getTLV(1,1);
					if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)
					{
						lblUpdate.SetWindowText(mIni.ReadValue("Global","UP_Item_NoUpdateModule"));
						btnUpdate.EnableWindow(FALSE);
					}
					else
					{
						lblUpdate.SetWindowText(mIni.ReadValue("Global","UP_Item_CanUpdateModule"));
						btnUpdate.EnableWindow(TRUE);
					}
					::EnableWindow(this->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
					::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
				}
				break;
			case CEnumCore::Message_Tag_ID::GMTOOLS_UPDATELIST_QUERY_RESP:
				{
					socketdata.Create(m_PacketHead.m_packethead.bodylen/8);
					socketdata.DeBody(m_PacketHead.getDataBuf()+18,m_PacketHead.m_packethead.bodylen);
					CString updateList = "";
					CString tmpUpdateList = "";

					CGlobalStruct::TFLV m_tflv;
					m_tflv = socketdata.getTLV(1,1);
					if(m_tflv.m_tagName = CEnumCore::TagName::MESSAGE)
					{
						updateList.Format("%s", (LPCSTR)&m_tflv.lpdata);
					}
					else
					{
						for(int i = 1; i <= socketdata.getQueryNum(); i++)
						{
							tmpUpdateList.Format("%( %i %) %s �� %s \r\n", i, socketdata.getTLV(i, 1).lpdata, socketdata.getTLV(i, 2).lpdata);
							updateList += tmpUpdateList;
						}						
					}
					lblUpdate.SetWindowText(mIni.ReadValue("Global","UP_Item_CanUpdateModule"));
					btnUpdate.EnableWindow(TRUE);
					txtContent.SetWindowText(updateList);
				}
				break;
			case CEnumCore::Message_Tag_ID::CLIENT_PATCH_UPDATE_RESP:
				{
					CFileFind finder;				    
					BOOL isFound = finder.FindFile(filepath);
					if(!isFound)
					{
						if (!CreateDirectory(filepath, NULL ))
						{ 
						}
					}

					int realLength = 0;
					int judge = 0;
					CGlobalStruct::TFLV tflv_FileName = socketdata.DeMakeTLV(m_PacketHead.getDataBuf() + 18, &actlength, 1, &judge);
					realLength = realLength + actlength;
					CGlobalStruct::TFLV tflv_FileSize = socketdata.DeMakeTLV(m_PacketHead.getDataBuf() + realLength + 18, &actlength, 2, &judge);
					realLength = realLength + actlength;

					CString FilePath = "";
					FilePath.Format("%s%s",filepath,tflv_FileName.lpdata);

					CFile file(FilePath,CFile::modeCreate|CFile::modeWrite);
					file.Write(m_PacketHead.getDataBuf() + realLength  + 18, atoi((LPCSTR)&tflv_FileSize.lpdata));
					file.Close(); 

					CString FileName = "";
					int FileSize = 0;
					CString UpdateFilePath = "";
					CString DownloadNow = mIni.ReadValue("Global","UP_UI_DownloadNow");
					CString refreshContent = "";

					int nPos;  
					nPos = FilePath.Find(_T("ini"),0);  
					if(nPos >= 0)  
					{  
						if(UpdateFileNum < UpdateData.getQueryNum())
						{
							UpdateFileNum++;
							FileName = (LPCSTR)&UpdateData.getTLVByName(UpdateFileNum, CEnumCore::TagName::UpdateFileName).lpdata;
							FileSize = atoi((LPCSTR)&UpdateData.getTLVByName(UpdateFileNum, CEnumCore::TagName::UpdateFileSize).lpdata);
							UpdateFilePath = (LPCSTR)&UpdateData.getTLVByName(UpdateFileNum, CEnumCore::TagName::UpdateFilePath).lpdata;

							socketdata.InitCreate(1,3);//����3��������dll��exe�ļ���Ϣ��·���ļ���Ϣ
							char strInt[10];
							int alllength=0;

							socketdata.AddTFLV(CEnumCore::TagName::UpdateFileName,CEnumCore::TagFormat::TLV_STRING,strlen(FileName),(unsigned char*)mIni.wcharToChar(FileName));//�ļ�����
							socketdata.AddTFLV(CEnumCore::TagName::UpdateFilePath,CEnumCore::TagFormat::TLV_STRING,strlen(UpdateFilePath),(unsigned char*)mIni.wcharToChar(UpdateFilePath));//�ļ�·��

							_itoa(FileSize,strInt,10);
							socketdata.AddTFLV(CEnumCore::TagName::UpdateFileSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char*)strInt);//�ļ�·��

							alllength=socketdata.EnBody();

							theApp.packethead.Create(alllength);
							theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::CLIENT_PATCH_UPDATE,alllength);
							theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
							theApp.packetLength = alllength;

							theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//���͸����ļ�������
							theApp.m_SendCount = 0;//�ظ����ʹ���Ϊ0

							::EnableWindow(this->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
							::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);

							progUpdate.StepIt();
							
							refreshContent.Format("%s%s", DownloadNow, FileName);
							lblUpdate.SetWindowText(refreshContent);
						}
						else
						{
							CString localFileName = "";
							CString tempFileName = "";

							CString strPath = filepath;
							strPath += _T ("*.exe");

							HANDLE hFind;  
							WIN32_FIND_DATA fd; 

							if ((hFind = ::FindFirstFile(strPath,&fd)) !=  INVALID_HANDLE_VALUE)    
							{
								if(!strcmp("Run.exe",fd.cFileName))
								{
									localFileName.Format("%s%s", localFilePath, fd.cFileName);
									tempFileName.Format("%s%s", filepath, fd.cFileName);

									SetFileAttributes(localFileName, FILE_ATTRIBUTE_NORMAL);  
			                        SetFileAttributes(tempFileName, FILE_ATTRIBUTE_NORMAL);  

									DeleteFile(localFileName);
									while(!CopyFile(tempFileName, localFileName, FALSE)){}
									while(!DeleteFile(tempFileName)){}
								}
								else
								{
									//����
									while(::FindNextFile(hFind, &fd))
									{
										if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
										{
											if(!strcmp("Run.exe",fd.cFileName))
											{
												localFileName.Format("%s%s", localFilePath, fd.cFileName);
												tempFileName.Format("%s%s", filepath, fd.cFileName);

												SetFileAttributes(localFileName, FILE_ATTRIBUTE_NORMAL);  
			                                    SetFileAttributes(tempFileName, FILE_ATTRIBUTE_NORMAL);  

												DeleteFile(localFileName);
												while(!CopyFile(tempFileName, localFileName, FALSE)){}
												while(!DeleteFile(tempFileName)){}
											}
										}
									}
								}
								::FindClose(hFind);  
							}  
							progUpdate.StepIt();

							UpdateData.Destroy();
							refreshContent.Format(mIni.ReadValue("Global","UP_UI_DownloadOver"));
							lblUpdate.SetWindowText(refreshContent);
							::EnableWindow(this->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
							::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
							btnUpdate.EnableWindow(FALSE);
						}
					}
					else
					{
						CFileUpdate fUpdate;
						CString isValid = fUpdate.GetVersionFromPath(FilePath);
						if(!strcmp("",isValid))
						{
							SetFileAttributes(FilePath, FILE_ATTRIBUTE_NORMAL);  
							while(!DeleteFile(FilePath)){}

							FileName = (LPCSTR)&UpdateData.getTLVByName(UpdateFileNum, CEnumCore::TagName::UpdateFileName).lpdata;
							FileSize = atoi((LPCSTR)&UpdateData.getTLVByName(UpdateFileNum, CEnumCore::TagName::UpdateFileSize).lpdata);
							UpdateFilePath = (LPCSTR)&UpdateData.getTLVByName(UpdateFileNum, CEnumCore::TagName::UpdateFilePath).lpdata;

							socketdata.InitCreate(1,3);//����3��������dll��exe�ļ���Ϣ��·���ļ���Ϣ
							char strInt[10];
							int alllength=0;

							socketdata.AddTFLV(CEnumCore::TagName::UpdateFileName,CEnumCore::TagFormat::TLV_STRING,strlen(FileName),(unsigned char*)mIni.wcharToChar(FileName));//�ļ�����
							socketdata.AddTFLV(CEnumCore::TagName::UpdateFilePath,CEnumCore::TagFormat::TLV_STRING,strlen(UpdateFilePath),(unsigned char*)mIni.wcharToChar(UpdateFilePath));//�ļ�·��

							_itoa(FileSize,strInt,10);
							socketdata.AddTFLV(CEnumCore::TagName::UpdateFileSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char*)strInt);//�ļ�·��

							alllength=socketdata.EnBody();

							theApp.packethead.Create(alllength);
							theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::CLIENT_PATCH_UPDATE,alllength);
							theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
							theApp.packetLength = alllength;

							theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//���͸����ļ�������
							theApp.m_SendCount = 0;//�ظ����ʹ���Ϊ0

							::EnableWindow(this->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
							::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
							
							refreshContent.Format("%s%s", DownloadNow, FileName);
							lblUpdate.SetWindowText(refreshContent);
						}
						else
						{
							if(UpdateFileNum < UpdateData.getQueryNum())
							{
								UpdateFileNum++;
								FileName = (LPCSTR)&UpdateData.getTLVByName(UpdateFileNum, CEnumCore::TagName::UpdateFileName).lpdata;
								FileSize = atoi((LPCSTR)&UpdateData.getTLVByName(UpdateFileNum, CEnumCore::TagName::UpdateFileSize).lpdata);
								UpdateFilePath = (LPCSTR)&UpdateData.getTLVByName(UpdateFileNum, CEnumCore::TagName::UpdateFilePath).lpdata;

								socketdata.InitCreate(1,3);//����3��������dll��exe�ļ���Ϣ��·���ļ���Ϣ
								char strInt[10];
								int alllength=0;

								socketdata.AddTFLV(CEnumCore::TagName::UpdateFileName,CEnumCore::TagFormat::TLV_STRING,strlen(FileName),(unsigned char*)mIni.wcharToChar(FileName));//�ļ�����
								socketdata.AddTFLV(CEnumCore::TagName::UpdateFilePath,CEnumCore::TagFormat::TLV_STRING,strlen(UpdateFilePath),(unsigned char*)mIni.wcharToChar(UpdateFilePath));//�ļ�·��

								_itoa(FileSize,strInt,10);
								socketdata.AddTFLV(CEnumCore::TagName::UpdateFileSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char*)strInt);//�ļ�·��

								alllength=socketdata.EnBody();

								theApp.packethead.Create(alllength);
								theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::CLIENT_PATCH_UPDATE,alllength);
								theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
								theApp.packetLength = alllength;

								theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//���͸����ļ�������
								theApp.m_SendCount = 0;//�ظ����ʹ���Ϊ0

								::EnableWindow(this->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
								::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);

								progUpdate.StepIt();
								
								refreshContent.Format("%s%s", DownloadNow, FileName);
								lblUpdate.SetWindowText(refreshContent);
							}
							else
							{
								CString localFileName = "";
								CString tempFileName = "";

								CString strPath = filepath;
								strPath += _T ("*.exe");

								HANDLE hFind;  
								WIN32_FIND_DATA fd; 

								if ((hFind = ::FindFirstFile(strPath,&fd)) !=  INVALID_HANDLE_VALUE)    
								{
									if(!strcmp("Run.exe",fd.cFileName))
									{
										localFileName.Format("%s%s", localFilePath, fd.cFileName);
										tempFileName.Format("%s%s", filepath, fd.cFileName);

										SetFileAttributes(localFileName, FILE_ATTRIBUTE_NORMAL);  
			                            SetFileAttributes(tempFileName, FILE_ATTRIBUTE_NORMAL);  

										DeleteFile(localFileName);
										while(!CopyFile(tempFileName, localFileName, FALSE)){}
										while(!DeleteFile(tempFileName)){}
									}
									else
									{
										//����
										while(::FindNextFile(hFind, &fd))
										{
											if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
											{
												if(!strcmp("Run.exe",fd.cFileName))
												{
													localFileName.Format("%s%s", localFilePath, fd.cFileName);
													tempFileName.Format("%s%s", filepath, fd.cFileName);

													SetFileAttributes(localFileName, FILE_ATTRIBUTE_NORMAL);  
			                                        SetFileAttributes(tempFileName, FILE_ATTRIBUTE_NORMAL);  

													DeleteFile(localFileName);
													while(!CopyFile(tempFileName, localFileName, FALSE)){}
													while(!DeleteFile(tempFileName)){}
												}
											}
										}
									}
									::FindClose(hFind);  
								}  
								progUpdate.StepIt();

								UpdateData.Destroy();
								refreshContent.Format(mIni.ReadValue("Global","UP_UI_DownloadOver"));
								lblUpdate.SetWindowText(refreshContent);
								::EnableWindow(this->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
								::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
								btnUpdate.EnableWindow(FALSE);
							}
						}
					}
				}
				break;
			default:
				break;
			}
		}
		catch(...)
		{
		}	
	}
	else
	{
		if(theApp.m_SendCount<5)//����ظ����ʹ���С��5��
		{
			theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),theApp.packetLength);//����ԭ��������
			theApp.m_SendCount++;//�ظ����ʹ�����1
		}
		else
		{
			::EnableWindow(this->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
			::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),MB_OK);//���ݽ����쳣
			return false;
		}
	}
	return false;
}

//����GMTools
void CModuleUpdate::OnBnClickedOk()
{
	UpdateData.Destroy();
	theApp.packethead.Destroy();
	OnOK();
}
