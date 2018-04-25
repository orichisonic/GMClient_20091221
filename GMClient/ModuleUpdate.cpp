// ModuleUpdate.cpp : 实现文件
//

#include "stdafx.h"
#include "GMClient.h"
#include "ModuleUpdate.h"
#include ".\moduleupdate.h"

#include "FileUpdate.h"

// CModuleUpdate 对话框

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


// 初始化对话框
BOOL CModuleUpdate::OnInitDialog()
{
	CDialog::OnInitDialog();

	HICON hIcon = NULL;       
    hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME),IMAGE_ICON, 16, 16, 0);   
	SetIcon(hIcon, FALSE); 

	UpdateFileNum = 0;
	InitUI();// 初始化显示字符
	theApp.m_clientsocket.SetParentHwnd(this->m_hWnd);
	CheckUpdate();

	return TRUE;
}

// 初始化显示字符
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

//设置背景颜色
HBRUSH CModuleUpdate::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//检测是否需要更新
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
		wsprintf(filepath,"%s%s",path,"\\");//获取配置文件的地址

		CFileUpdate fUpdate;

		CString dllFileInfo = fUpdate.GetLocalDllFile(filepath);
		CString exeFileInfo = fUpdate.GetLocalExeFile(filepath);

		socketdata.InitCreate(1,2);//共有2个参数，dll、exe文件信息、Ini文件信息
		int alllength=0;

		socketdata.AddTFLV(CEnumCore::TagName::UpdateFileName,CEnumCore::TagFormat::TLV_STRING,strlen(dllFileInfo),(unsigned char*)mIni.wcharToChar(dllFileInfo));//dll版本信息
		socketdata.AddTFLV(CEnumCore::TagName::UpdateFilePath,CEnumCore::TagFormat::TLV_STRING,strlen(exeFileInfo),(unsigned char*)mIni.wcharToChar(exeFileInfo));//exe版本信息

		alllength=socketdata.EnBody();

		theApp.packethead.Create(alllength);
		theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::CLIENT_PATCH_COMPARE,alllength);
		theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
		theApp.packetLength = alllength;

		theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//发送查询是否需要更新的请求
		theApp.m_SendCount = 0;//重复发送次数为0

		::EnableWindow(this->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	}
	catch(...)
	{
	}
}

//自动更新
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

			socketdata.InitCreate(1,3);//共有3个参数，dll、exe文件信息、路径文件信息
			char strInt[10];
			ZeroMemory(strInt,10);
			int alllength=0;

			socketdata.AddTFLV(CEnumCore::TagName::UpdateFileName,CEnumCore::TagFormat::TLV_STRING,strlen(FileName),(unsigned char*)mIni.wcharToChar(FileName));//文件名称
			socketdata.AddTFLV(CEnumCore::TagName::UpdateFilePath,CEnumCore::TagFormat::TLV_STRING,strlen(FilePath),(unsigned char*)mIni.wcharToChar(FilePath));//文件路径

			_itoa(FileSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UpdateFileSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char*)strInt);//文件路径

			alllength=socketdata.EnBody();

			theApp.packethead.Create(alllength);
			theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::CLIENT_PATCH_UPDATE,alllength);
			theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
			theApp.packetLength = alllength;

			theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//发送更新第一个文件的请求
			theApp.m_SendCount = 0;//重复发送次数为0

			::EnableWindow(this->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
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

// 发送登录信息之后进行接收
LRESULT CModuleUpdate::OnLoginReceive(WPARAM wParam, LPARAM lParam)
{
	CIni mIni;

	CMSocket selfSocket;
	CPacketHead m_PacketHead;	
	CSocketData socketdata;
	
	int actlength=0;

	selfSocket.SetSocket(theApp.m_clientsocket.m_hSocket);
	actlength=selfSocket.MyReceive();//接收返回信息

	if(actlength == -1)
	{
		::EnableWindow(this->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
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
		wsprintf(localFilePath,"%s%s",path,"\\");//获取配置文件的地址
		wsprintf(filepath,"%s%s",path,"\\temp\\");//获取配置文件的地址

		theApp.m_SendCount = 0;//重复发送次数为0

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
					::EnableWindow(this->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
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
							tmpUpdateList.Format("%( %i %) %s ： %s \r\n", i, socketdata.getTLV(i, 1).lpdata, socketdata.getTLV(i, 2).lpdata);
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

							socketdata.InitCreate(1,3);//共有3个参数，dll、exe文件信息、路径文件信息
							char strInt[10];
							int alllength=0;

							socketdata.AddTFLV(CEnumCore::TagName::UpdateFileName,CEnumCore::TagFormat::TLV_STRING,strlen(FileName),(unsigned char*)mIni.wcharToChar(FileName));//文件名称
							socketdata.AddTFLV(CEnumCore::TagName::UpdateFilePath,CEnumCore::TagFormat::TLV_STRING,strlen(UpdateFilePath),(unsigned char*)mIni.wcharToChar(UpdateFilePath));//文件路径

							_itoa(FileSize,strInt,10);
							socketdata.AddTFLV(CEnumCore::TagName::UpdateFileSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char*)strInt);//文件路径

							alllength=socketdata.EnBody();

							theApp.packethead.Create(alllength);
							theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::CLIENT_PATCH_UPDATE,alllength);
							theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
							theApp.packetLength = alllength;

							theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//发送更新文件的请求
							theApp.m_SendCount = 0;//重复发送次数为0

							::EnableWindow(this->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
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
									//遍历
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
							::EnableWindow(this->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
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

							socketdata.InitCreate(1,3);//共有3个参数，dll、exe文件信息、路径文件信息
							char strInt[10];
							int alllength=0;

							socketdata.AddTFLV(CEnumCore::TagName::UpdateFileName,CEnumCore::TagFormat::TLV_STRING,strlen(FileName),(unsigned char*)mIni.wcharToChar(FileName));//文件名称
							socketdata.AddTFLV(CEnumCore::TagName::UpdateFilePath,CEnumCore::TagFormat::TLV_STRING,strlen(UpdateFilePath),(unsigned char*)mIni.wcharToChar(UpdateFilePath));//文件路径

							_itoa(FileSize,strInt,10);
							socketdata.AddTFLV(CEnumCore::TagName::UpdateFileSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char*)strInt);//文件路径

							alllength=socketdata.EnBody();

							theApp.packethead.Create(alllength);
							theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::CLIENT_PATCH_UPDATE,alllength);
							theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
							theApp.packetLength = alllength;

							theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//发送更新文件的请求
							theApp.m_SendCount = 0;//重复发送次数为0

							::EnableWindow(this->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
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

								socketdata.InitCreate(1,3);//共有3个参数，dll、exe文件信息、路径文件信息
								char strInt[10];
								int alllength=0;

								socketdata.AddTFLV(CEnumCore::TagName::UpdateFileName,CEnumCore::TagFormat::TLV_STRING,strlen(FileName),(unsigned char*)mIni.wcharToChar(FileName));//文件名称
								socketdata.AddTFLV(CEnumCore::TagName::UpdateFilePath,CEnumCore::TagFormat::TLV_STRING,strlen(UpdateFilePath),(unsigned char*)mIni.wcharToChar(UpdateFilePath));//文件路径

								_itoa(FileSize,strInt,10);
								socketdata.AddTFLV(CEnumCore::TagName::UpdateFileSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char*)strInt);//文件路径

								alllength=socketdata.EnBody();

								theApp.packethead.Create(alllength);
								theApp.packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::CLIENT_PATCH_UPDATE,alllength);
								theApp.packethead.EnSendBuf(&alllength,socketdata.getDes(),theApp.packethead.m_packethead.bodylen);
								theApp.packetLength = alllength;

								theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),alllength);//发送更新文件的请求
								theApp.m_SendCount = 0;//重复发送次数为0

								::EnableWindow(this->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
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
										//遍历
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
								::EnableWindow(this->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
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
		if(theApp.m_SendCount<5)//如果重复发送次数小于5次
		{
			theApp.m_clientsocket.Send(theApp.packethead.getSendBuf(),theApp.packetLength);//发送原来的请求
			theApp.m_SendCount++;//重复发送次数加1
		}
		else
		{
			::EnableWindow(this->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
			::SetWindowPos(this->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
			MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),MB_OK);//数据解析异常
			return false;
		}
	}
	return false;
}

//重启GMTools
void CModuleUpdate::OnBnClickedOk()
{
	UpdateData.Destroy();
	theApp.packethead.Destroy();
	OnOK();
}
