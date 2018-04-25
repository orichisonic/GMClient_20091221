#include "stdafx.h"
#include "OperationGM.h"

OperationGM::OperationGM()
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );//��ȫ�ֱ�������
	intGM = NULL;
}
OperationGM::~OperationGM()
{
	selfSocket.MyDestory();
	packethead.Destroy();
	if(intGM != NULL)
	{
	    intGM = NULL;
	}
}

//����SOCKET
void OperationGM::initSocket(SOCKET m_Socket)
{
	selfSocket.SetSocket(m_Socket);
}

// ��ȡini�ļ������ֵ
CString OperationGM::ReadValue(CString strSection,CString strKey)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MGM.ini");//��ȡ�����ļ��ĵ�ַ
	if(GetPrivateProfileString(strSection,strKey,"",strValue,2048,filepath)!=-1)//�����Ҫ��ȡ��ֵ����CString����ʽ���
	{
		return (LPSTR)&strValue;
	}
	return "";
}

// ��ȡini�ļ����������
int OperationGM::ReadIntValue(CString strSection,CString strKey)
{
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MGM.ini");
	int result = GetPrivateProfileInt(strSection,strKey,0,filepath);
	return result;
}

//ͨ���кź������õ���Ӧ��ֵ
CString OperationGM::GetValueByColName(CListCtrl* listCtrlS, int nIndex, CString ColName)
{
	CString ItemInfo = "";
	LVCOLUMN pColumn;   
	pColumn.mask = LVCF_TEXT;   
	    
	char buff[255];   
	pColumn.pszText = buff;   
	pColumn.cchTextMax = 255;   

	for(int i=0;i < listCtrlS->GetHeaderCtrl()->GetItemCount();i++)
	{
		listCtrlS->GetColumn(i, &pColumn);   
		if(!strcmp(ColName, pColumn.pszText))
		{
			ItemInfo = listCtrlS->GetItemText(nIndex, i);
			break;
		}
	}
	return ItemInfo;
}

// ����Query
bool OperationGM::SendQuery(unsigned char* sendData,int allLength,CEnumCore::Msg_Category m_category,CEnumCore::ServiceKey m_ServiceKey)
{
	try
	{
		packethead.Create(allLength);
		packethead.AddHeader(1,m_category,m_ServiceKey,allLength);//�����ݰ����ͷ��Ϣ
		
		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);//���첢�������Ҫ���͵����ݰ�
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))//��������
		{
			MessageBox(NULL,ReadValue("MGM","GM_ERROR_SENDDATAERROR"),ReadValue("MGM","ERROR"),MB_OK);
			return false;
		}
		*intGM = 1;
	}
	catch(...)
	{
	}
	return true;
}

//�ٴη���ͬ����Query
bool OperationGM::SendSameQuery()
{
	try
	{
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),packetLength))//��������
		{
			MessageBox(NULL,ReadValue("MGM","GM_ERROR_SENDDATAERROR"),ReadValue("MGM","ERROR"),MB_OK);
			return false;
		}
	}
	catch(...)
	{
	}
	return true;
}

// ���츴ѡ��
bool OperationGM::BuildCombox(CSocketData* psocketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;
		cmbSelect->ResetContent();//��ո�ѡ�������

		m_tSvrCity = psocketData->getTLV(1,1);
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MGM","Result"),0);
			return false;
		}

		for(int i=1;i<=psocketData->getQueryNum();i++)
		{
			m_tSvrCity = psocketData->getTLV(i,2);//��ȡҪ��ӵ���������
			cmbSelect->AddString((LPCTSTR)&m_tSvrCity.lpdata);//���õ����������ݱ����ڸ�ѡ����
		}
		cmbSelect->SetCurSel(0);
	}
	catch(...)
	{
		MessageBox(NULL,ReadValue("MGM","UM_Error_BuildComboBox"),ReadValue("MGM","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

// ���츴ѡ��
bool OperationGM::BuildComboxs(CSocketData* psocketData,CComboBox* cmbSelect,int bItem,CEnumCore::TagName m_TegName)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;
		cmbSelect->ResetContent();//��ո�ѡ�������

		m_tSvrCity = psocketData->getTLV(1,1);
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MGM","Result"),0);
			return false;
		}

		for(int i=bItem;i<=psocketData->getQueryNum();i++)
		{
			m_tSvrCity = psocketData->getTLVByName(i,m_TegName);//��ȡҪ��ӵ���������
			cmbSelect->AddString((LPCTSTR)&m_tSvrCity.lpdata);//���õ����������ݱ����ڸ�ѡ����
		}
		cmbSelect->SetCurSel(0);
	}
	catch(...)
	{
		MessageBox(NULL,ReadValue("MGM","UM_Error_BuildComboBox"),ReadValue("MGM","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

// �����û��б�
bool OperationGM::BuildComboxUser(CSocketData* psocketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;
		cmbSelect->ResetContent();//��ո�ѡ�������

		m_tSvrCity = psocketData->getTLV(1,1);
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MGM","Result"),0);
			return false;
		}

		for(int i=1;i<=psocketData->getQueryNum();i++)
		{
			m_tSvrCity = psocketData->getTLVByName(i,CEnumCore::TagName::RealName);//��ȡҪ��ӵ���������
			cmbSelect->AddString((LPCTSTR)&m_tSvrCity.lpdata);//���õ����������ݱ����ڸ�ѡ����
		}
		cmbSelect->SetCurSel(0);
	}
	catch(...)
	{
		MessageBox(NULL,ReadValue("MGM","UM_Error_BuildComboBox"),ReadValue("MGM","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

//������Ϸ�б�
bool OperationGM::BuildComboxGame(CSocketData* psocketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;
		cmbSelect->ResetContent();//��ո�ѡ�������

		m_tSvrCity = psocketData->getTLV(1,1);
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MGM","Result"),0);
			return false;
		}

		cmbSelect->AddString(ReadValue("MGM","OL_UI_AllGame"));
		for(int i=1;i<=psocketData->getQueryNum();i++)
		{
			m_tSvrCity = psocketData->getTLVByName(i,CEnumCore::TagName::GameName);//��ȡҪ��ӵ���������
			cmbSelect->AddString((LPCTSTR)&m_tSvrCity.lpdata);//���õ����������ݱ����ڸ�ѡ����
		}
		cmbSelect->SetCurSel(0);
	}
	catch(...)
	{
		MessageBox(NULL,ReadValue("MGM","UM_Error_BuildComboBox"),ReadValue("MGM","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

//��������б�
bool OperationGM::BuildComboxCity(CSocketData* psocketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;
		cmbSelect->ResetContent();//��ո�ѡ�������

		m_tSvrCity = psocketData->getTLV(1,1);
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MGM","Result"),0);
			return false;
		}

		cmbSelect->AddString(ReadValue("MGM","OL_UI_AllCity"));
		for(int i=1;i<=psocketData->getQueryNum();i++)
		{
			m_tSvrCity = psocketData->getTLVByName(i,CEnumCore::TagName::ServerInfo_City);//��ȡҪ��ӵ���������
			cmbSelect->AddString((LPCTSTR)&m_tSvrCity.lpdata);//���õ����������ݱ����ڸ�ѡ����
		}
		cmbSelect->SetCurSel(0);
	}
	catch(...)
	{
		MessageBox(NULL,ReadValue("MGM","UM_Error_BuildComboBox"),ReadValue("MGM","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

// ����CListCtrl
bool OperationGM::BuildDataTable(CSocketData* psocketData,CListCtrl* listCtrlS,int* pageCount)
{
	try
	{
		LONG lStyle;
		lStyle = GetWindowLong(listCtrlS->m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
		lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
		lStyle |= LVS_REPORT; //����style
		SetWindowLong(listCtrlS->m_hWnd, GWL_STYLE, lStyle);//����style
		
		DWORD dwStyle = listCtrlS->GetExtendedStyle();
		dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
		dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
		listCtrlS->SetExtendedStyle(dwStyle); //������չ���

		while(listCtrlS->DeleteColumn(0)){}	//���CListCtrl������

		CGlobalStruct::TFLV m_BGS,m_ConGS;
		m_BGS = psocketData->getTLV(1,1);//��ȡ��һ��Ҫ��ӵ���������
		if(m_BGS.m_tagName == CEnumCore::TagName::MESSAGE) //�����һ��Ҫ��ӵ�����������ʧ����Ϣ�Ļ�
		{
			MessageBox(NULL,(LPCTSTR)&m_BGS.lpdata,"Error",MB_ICONWARNING+MB_OK);//��ʾʧ����Ϣ������
			return false;
		}

		for(int i=1;i<=psocketData->getColTFLVNum();i++)//��ӵõ������ݰ������е�TagName
		{
			m_BGS = psocketData->getTLV(1,i);
			if(m_BGS.m_tagName != CEnumCore::TagName::PageCount)//ҳ����Ϣ������ӵ�CListCtrl��
			{
				ReadValue("MGM",tagToStr(m_BGS.m_tagName));//��ȡTagName�Ķ�Ӧ�ַ�����
				listCtrlS->InsertColumn( i, this->strValue, LVCFMT_LEFT, 80 );//��TagName���ַ����Ʋ��뵽CListCtrl�У���Ϊ����
			}
		}
		m_BGS = psocketData->getTLV(1,psocketData->getColTFLVNum());
		*pageCount = atoi((char *)&m_BGS.lpdata);//��ȡҳ����Ϣ

		listCtrlS->DeleteAllItems();//���CListCtrl�����������
		int nRow=0;
		for(int j=1;j<=psocketData->getQueryNum();j++)
		{
			for(int k=1;k<=psocketData->getColTFLVNum();k++)
			{
				m_ConGS = psocketData->getTLV(j,k);
				if(k==1)
				{
					nRow=listCtrlS->InsertItem(j-1,(LPCTSTR)&m_ConGS.lpdata);//�������еĽ�����õ���Ϣ���뵽CListCtrl��
				}
				else
				{
					if(m_ConGS.m_tagName == CEnumCore::TagName::PageCount)
					{
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::OnlineActive)//����״̬��Ҫ��������ʾ
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//����״̬Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGM","UM_Code_Online"));//��ʾΪ����
						}
						else//����״̬��Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGM","UM_Code_NotOnline"));//��ʾΪ������
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::SysAdmin)//�Ƿ�ϵͳ����Ա��Ҫ��������ʾ
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//ϵͳ����Ա״̬Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGM","UM_Code_SysAdmin"));//��ʾΪϵͳ����Ա
						}
						else//ϵͳ����Ա״̬��Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGM","UM_Code_DepartAdmin"));//��ʾΪ���Ź���Ա
						}
					}
					else
					{
						listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);//�������еĽ�����õ���Ϣ���뵽CListCtrl��
					}
				}
			}
		}
	}
	catch (...)
	{
		MessageBox(NULL,ReadValue("MGM","UM_Error_BuildList"),ReadValue("MGM","Error"),0);
	}
	return false;
}

// TagNameת����CString����
char* OperationGM::tagToStr(CEnumCore::TagName tag)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	switch(tag)
	{
	case CEnumCore::TagName::UserName: //Format:STRING �û���
		sprintf(strValue,"%s","UserName");
		break;
	case CEnumCore::TagName::PassWord: //Format:STRING ����
		sprintf(strValue,"%s","PassWord");
		break;
	case CEnumCore::TagName::MAC: //Format:STRING  MAC��
		sprintf(strValue,"%s","MAC");
		break;
	case CEnumCore::TagName::Limit://Format:DateTime GM�ʺ�ʹ��ʱЧ
		sprintf(strValue,"%s","Limit");
		break;
	case CEnumCore::TagName::User_Status://Format:INT ״̬��Ϣ
		sprintf(strValue,"%s","User_Status");
		break;
	case CEnumCore::TagName::UserByID://Format:INT ����ԱID
		sprintf(strValue,"%s","UserByID");
		break;
	case CEnumCore::TagName::RealName://Format:STRING ������
		sprintf(strValue,"%s","RealName");
		break;
	case CEnumCore::TagName::DepartID://Format:INT ����ID
		sprintf(strValue,"%s","DepartID");
		break;
	case CEnumCore::TagName::DepartName://Format:STRING ��������
		sprintf(strValue,"%s","DepartName");
		break;
	case CEnumCore::TagName::DepartRemark://Format:STRING ��������
		sprintf(strValue,"%s","DepartRemark");
		break;
	case CEnumCore::TagName::OnlineActive://Format:Integer ����״̬
		sprintf(strValue,"%s","OnlineActive");
		break;
	case CEnumCore::TagName::UpdateFileName://Format:String �ļ���
		sprintf(strValue,"%s","UpdateFileName");
		break;
	case CEnumCore::TagName::UpdateFileVersion://Format:String �ļ��汾
		sprintf(strValue,"%s","UpdateFileVersion");
		break;
	case CEnumCore::TagName::UpdateFilePath://Format:String �ļ�·��
		sprintf(strValue,"%s","UpdateFilePath");
		break;
	case CEnumCore::TagName::UpdateFileSize://Format:Integer �ļ���С
		sprintf(strValue,"%s","UpdateFileSize");
		break;
	case CEnumCore::TagName::Process_Reason://Format tring
		sprintf(strValue,"%s","Process_Reason");
		break;
	case CEnumCore::TagName::userIP://Format::STRING IP��ַ(�¼�)
		sprintf(strValue,"%s","userIP");
		break;
	case CEnumCore::TagName::DepartStrGameID://Format:STRING������ϷID�ܺ�(�¼�)
		sprintf(strValue,"%s","DepartStrGameID");
		break;
	case CEnumCore::TagName::DugID:////Format:STRINGBBugID(�¼�)
		sprintf(strValue,"%s","DugID");
		break;
	case CEnumCore::TagName::DugSubject:////Format:STRINGBBug����(�¼�)
		sprintf(strValue,"%s","DugSubject");
		break;
	case CEnumCore::TagName::DugType:////Format:INTBug����(�¼�)
		sprintf(strValue,"%s","DugType");
		break;
	case CEnumCore::TagName::DugContent:////Format:STRINGBug����(�¼�)
		sprintf(strValue,"%s","DugContent");
		break;
	case CEnumCore::TagName::DugResult:////Format:STRINGBug���(�¼�)
		sprintf(strValue,"%s","DugResult");
		break;
	case CEnumCore::TagName::ServerInfo_IP://Format:String ������IP
		sprintf(strValue,"%s","ServerInfo_IP");
		break;
	case CEnumCore::TagName::ServerInfo_City://Format:String ����
		sprintf(strValue,"%s","ServerInfo_City");
		break;
	case CEnumCore::TagName::ServerInfo_GameID://Format:Integer ��ϷID
		sprintf(strValue,"%s","ServerInfo_GameID");
		break;
	case CEnumCore::TagName::ServerInfo_GameName://Format:String ��Ϸ��
		sprintf(strValue,"%s","ServerInfo_GameName");
		break;
	case CEnumCore::TagName::ServerInfo_GameDBID://Format:Integer ��Ϸ���ݿ�����
		sprintf(strValue,"%s","ServerInfo_GameDBID");
		break;
	case CEnumCore::TagName::ServerInfo_GameFlag://Format:Integer ��Ϸ������״̬
		sprintf(strValue,"%s","ServerInfo_GameFlag");
		break;
	case CEnumCore::TagName::ServerInfo_Idx:
		sprintf(strValue,"%s","ServerInfo_Idx");
		break;
	case CEnumCore::TagName::ServerInfo_DBName:
		sprintf(strValue,"%s","ServerInfo_DBName");
		break;

	case CEnumCore::TagName::ServerInfo_UserName:////Format:STRING�������û���(�¼�)
		sprintf(strValue,"%s","ServerInfo_UserName");
		break;
	case CEnumCore::TagName::ServerInfo_PassWord:////Format:STRINGB����������(�¼�)
		sprintf(strValue,"%s","ServerInfo_PassWord");
		break;

	case CEnumCore::TagName::GameID: //Format:INTEGER ��ϢID
		sprintf(strValue,"%s","GameID");
		break;
	case CEnumCore::TagName::ModuleName: //Format:STRING ģ������
		sprintf(strValue,"%s","ModuleName");
		break;
	case CEnumCore::TagName::ModuleClass://Format:STRING ģ�����
		sprintf(strValue,"%s","ModuleClass");
		break;
	case CEnumCore::TagName::ModuleContent: //Format:STRING ģ������
		sprintf(strValue,"%s","ModuleContent");
		break;

	case CEnumCore::TagName::Module_ID: //Format:INTEGER ģ��ID
		sprintf(strValue,"%s","Module_ID");
		break;
	case CEnumCore::TagName::User_ID: //Format:INTEGER �û�ID
		sprintf(strValue,"%s","User_ID");
		break;
	case CEnumCore::TagName::ModuleList: //Format:String ģ���б�
		sprintf(strValue,"%s","ModuleList");
		break;
	case CEnumCore::TagName::SysAdmin://Format:Integer �Ƿ���ϵͳ����Ա
		sprintf(strValue,"%s","SysAdmin");
		break;
	case CEnumCore::TagName::Host_Addr: //Format:STRING
		sprintf(strValue,"%s","Host_Addr");
		break;
	case CEnumCore::TagName::Host_Port: //Format:STRING
		sprintf(strValue,"%s","Host_Port");
		break;
	case CEnumCore::TagName::Host_Pat:  //Format:STRING
		sprintf(strValue,"%s","Host_Pat");
		break;
	case CEnumCore::TagName::Conn_Time: //Format:DateTime �������Ӧʱ��
		sprintf(strValue,"%s","Conn_Time");
		break;
	case CEnumCore::TagName::Connect_Msg://Format:STRING ����������Ϣ
		sprintf(strValue,"%s","Connect_Msg");
		break;
	case CEnumCore::TagName::DisConnect_Msg://Format:STRING	 ����˿���Ϣ
		sprintf(strValue,"%s","DisConnect_Msg");
		break;
	case CEnumCore::TagName::Author_Msg: //Format:STRING ��֤�û�����Ϣ
		sprintf(strValue,"%s","Author_Msg");
		break;
	case CEnumCore::TagName::Status://Format:STRING �������
		sprintf(strValue,"%s","Status");
		break;
	case CEnumCore::TagName::Index: //Format:Integer ��¼�����
		sprintf(strValue,"%s","Index");
		break;
	case CEnumCore::TagName::PageSize://Format:Integer ��¼ҳ��ʾ����
		sprintf(strValue,"%s","PageSize");
		break;
	case CEnumCore::TagName::PageCount://Format:Integer ��ʾ��ҳ��
		sprintf(strValue,"%s","PageCount");
		break;
	case CEnumCore::TagName::SP_Name://Format:Integer �洢������
		sprintf(strValue,"%s","SP_Name");
		break;
	case CEnumCore::TagName::Real_ACT://Format:String ����������
		sprintf(strValue,"%s","Real_ACT");
		break;
	case CEnumCore::TagName::ACT_Time://Format:TimeStamp ����ʱ��
		sprintf(strValue,"%s","ACT_Time");
		break;
	case CEnumCore::TagName::BeginTime://Format:Date ��ʼ����
		sprintf(strValue,"%s","BeginTime");
		break;
	case CEnumCore::TagName::EndTime://Format:Date ��������
		sprintf(strValue,"%s","EndTime");
		break;
	case CEnumCore::TagName::GameName: //Format:STRING ��Ϸ����
		sprintf(strValue,"%s","GameName");
		break;
	case CEnumCore::TagName::GameContent: //Format:STRING ��Ϣ����
		sprintf(strValue,"%s","GameContent");
		break;
	case CEnumCore::TagName::Letter_ID://Format:Integer 
		sprintf(strValue,"%s","Letter_ID");
		break;
	case CEnumCore::TagName::Letter_Sender: //Format:String
		sprintf(strValue,"%s","Letter_Sender");
		break;
	case CEnumCore::TagName::Letter_Receiver: //Format:String
		sprintf(strValue,"%s","Letter_Receiver");
		break;
	case CEnumCore::TagName::Letter_Subject: //Format:String
		sprintf(strValue,"%s","Letter_Subject");
		break;
	case CEnumCore::TagName::Letter_Text: //Format:String
		sprintf(strValue,"%s","Letter_Text");
		break;
	case CEnumCore::TagName::Send_Date: //Format:Date
		sprintf(strValue,"%s","Send_Date");
		break;
	case CEnumCore::TagName::Process_Man: //Format:Integer
		sprintf(strValue,"%s","Process_Man");
		break;
	case CEnumCore::TagName::Process_Date: //Format:Date
		sprintf(strValue,"%s","Process_Date");
		break;
	case CEnumCore::TagName::Transmit_Man: //Format:Integer
		sprintf(strValue,"%s","Transmit_Man");
		break;
	case CEnumCore::TagName::Is_Process: //Format:Integer
		sprintf(strValue,"%s","Is_Process");
		break;
	case CEnumCore::TagName::LINKER_NAME:
		sprintf(strValue,"%s","LINKER_NAME");
		break;
	case CEnumCore::TagName::LINKER_CONTENT:
		sprintf(strValue,"%s","LINKER_CONTENT");
		break;
	case CEnumCore::TagName::ToolProcTypeID:
		sprintf(strValue,"%s","ToolProcTypeID");
		break;
	case CEnumCore::TagName::PlayerAccount:
		sprintf(strValue,"%s","PlayerAccount");
		break;
	case CEnumCore::TagName::PlayerName:
		sprintf(strValue,"%s","PlayerName");
		break;
	case CEnumCore::TagName::ToolProcPath:
		sprintf(strValue,"%s","ToolProcPath");
		break;
	case CEnumCore::TagName::KickProcTime:
		sprintf(strValue,"%s","KickProcTime");
		break;
	case CEnumCore::TagName::PlayerInServer:
		sprintf(strValue,"%s","PlayerInServer");
		break;
	case CEnumCore::TagName::RealmIP:
		sprintf(strValue,"%s","RealmIP");
		break;
	default:
		sprintf(strValue,"%s","UnKnown");
		break;
	}	
	return strValue;
}

// ��ʾ�������
void OperationGM::ShowResult(CString result)
{
	if (result == "SCUESS")
	{
		MessageBox(NULL,ReadValue("MGM","Success"),ReadValue("MGM","Result"),0);
	}
	else if (result == "FAILURE")
	{
		MessageBox(NULL,ReadValue("MGM","Failure"),ReadValue("MGM","Result"),0);
	}
	else
	{
		MessageBox(NULL,result,ReadValue("MGM","Result"),0);
	}
}

//�Լ�����ĸ��ƺ���
void OperationGM::CopyListInfo(CListCtrl* m_listCtrl)
{
	try
	{
		POSITION pos = m_listCtrl->GetFirstSelectedItemPosition();  
		if (pos != NULL)
		{			
			char strCopy[40960];
			ZeroMemory(strCopy, 40960);

			LVCOLUMN lvcol;
			char str[256];
			int nColNum;

			nColNum = 0;
			lvcol.mask = LVCF_TEXT;
			lvcol.pszText = str;
			lvcol.cchTextMax = 256;
			while(m_listCtrl->GetColumn(nColNum, &lvcol))
			{
				if(nColNum == 0)
				{
					sprintf(strCopy,"%s%s",strCopy,lvcol.pszText);
				}
				else
				{
					sprintf(strCopy,"%s\t%s",strCopy,lvcol.pszText);				
				}							
				nColNum++;
			}
			sprintf(strCopy,"%s\r\n",strCopy);
			int nItem = 0;

			while(pos)
			{
				nItem = m_listCtrl->GetNextSelectedItem(pos);
				for(int j=0; j < m_listCtrl->GetHeaderCtrl()->GetItemCount(); j++)
				{
					if(j == 0)
					{
						sprintf(strCopy,"%s%s",strCopy,m_listCtrl->GetItemText(nItem,j));
					}
					else
					{
						sprintf(strCopy,"%s\t%s",strCopy,m_listCtrl->GetItemText(nItem,j));				
					}				
				}
				sprintf(strCopy,"%s\r\n",strCopy);
			}
			HGLOBAL clipBuff;   
			clipBuff=::GlobalAlloc(GMEM_DDESHARE,40960);   
			char* p;   
			p=(char*)GlobalLock(clipBuff);
			strcpy(p,strCopy);
			GlobalUnlock(clipBuff);   
			if(OpenClipboard(NULL))   
			{   
				if(EmptyClipboard())   
				{   
					SetClipboardData(CF_TEXT,clipBuff);   
					CloseClipboard();   
				}   
			}
		}	
		else
		{
			HGLOBAL clipBuff;   
			clipBuff=::GlobalAlloc(GMEM_DDESHARE,40960);   
			char* p;   
			p=(char*)GlobalLock(clipBuff);
			strcpy(p,"");
			GlobalUnlock(clipBuff);   
			if(OpenClipboard(NULL))   
			{   
				if(EmptyClipboard())   
				{   
					SetClipboardData(CF_TEXT,clipBuff);   
					CloseClipboard();   
				}   
			}
		}
	}
	catch(...)
	{
	}
}

struct MyData{
    CListCtrl *listctrl;       //CListCtrl�ؼ�ָ��
    int isub;        //l�к�
    int seq;        //1Ϊ����0Ϊ����
}; 

//����ص�����
int CALLBACK SortListProc(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort)
{
	CIni mIni;
	MyData *p=(MyData *)lParamSort;
	CListCtrl* list =p->listctrl;
	int isub=p->isub;

	LVFINDINFO findInfo;
	findInfo.flags = LVFI_PARAM;
	findInfo.lParam = lParam1;
	int iItem1 = list->FindItem(&findInfo, -1);
	findInfo.lParam = lParam2;
	int iItem2 = list->FindItem(&findInfo, -1);

	CString strItem1 =list->GetItemText(iItem1,isub);
	CString strItem2 =list->GetItemText(iItem2,isub);

	int iCompRes;

	if (mIni.bIsNumber(strItem1) && mIni.bIsNumber(strItem2))
    {
		int nStr1 = atoi(mIni.wcharToChar(strItem1));
		int nStr2 = atoi(mIni.wcharToChar(strItem2));
        if (nStr1 > nStr2)
            iCompRes = 1;
        else if (nStr1 == nStr2)
            iCompRes = 0;
        else
            iCompRes = -1;
	}
	else
	{
		if(strItem1 > strItem2)
			iCompRes = 1;
		else if(strItem1 == strItem2)
			iCompRes = 0;
		else
			iCompRes = -1;
	}

	if(p->seq)
	    return iCompRes;
	else
	    return -iCompRes;
}

//�Լ������������
void OperationGM::SortListInfo(CListCtrl* m_listCtrl,NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	MyData *tmpData=new MyData;

	tmpData->listctrl = m_listCtrl;
	tmpData->isub=pNMListView->iSubItem;

	int sortnum=(int)GetProp(m_listCtrl->GetSafeHwnd(),"�����к�");
	int sortasc=(int)GetProp(m_listCtrl->GetSafeHwnd(),"����˳��");

	if(sortnum==pNMListView->iSubItem){
	    sortasc=(sortasc+1)%2;
	    SetProp(m_listCtrl->GetSafeHwnd(),"����˳��",(HANDLE)sortasc);
	}
	SetProp(m_listCtrl->GetSafeHwnd(),"�����к�",(HANDLE)pNMListView->iSubItem);
	tmpData->seq=sortasc;//ѡ�������ǽ���
	m_listCtrl->SortItems(SortListProc,(LPARAM)tmpData);//��������

	*pResult = 0;
}

//����CListCtrl�е����ݵ�xls�ļ�
bool OperationGM::ExportCListCtrlToExcel(CListCtrl* pList, CString sExcelFile, CString sSheetName)
{
	if (pList->GetItemCount() < 1) 
	{
		MessageBox(NULL, "�޿�������", NULL, MB_OK|MB_TOPMOST);
		return FALSE;
	}

	//�����Ƿ�װ��Excel���� "Microsoft Excel Driver (*.xls)"
	CString sDriver;
	sDriver = GetExcelDriver("Excel");
	if (sDriver.IsEmpty())
	{
		MessageBox(NULL, "��û�а�װEXCEL!\n���Ȱ�װEXCEL��ʹ�ñ�����.", NULL, MB_OK|MB_TOPMOST);
		return FALSE;
	}

	//�������д�ȡ���ַ���
	CString sSql;

	sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver, sExcelFile, sExcelFile);

	//������ṹ(��xls�ļ�)
	CDatabase database;
	if(database.OpenEx(sSql, CDatabase::noOdbcDialog))
	{
		LVCOLUMN columnData;
		CString columnName;
		CString strH;
		CString strV;
		
		columnData.mask = LVCF_TEXT;
		columnData.pszText = columnName.GetBuffer(128);
		columnData.cchTextMax = 128;

		sSql = "";
		strH = "";
		int i, columnNum = 0;
		for (i = 0; pList->GetColumn(i, &columnData); i++)
		{
			if(i != 0)
			{
				sSql = sSql + ",";
				strH = strH + ",";
			}
			sSql = sSql + columnData.pszText + " TEXT";
			strH = strH + columnData.pszText + " ";
		}
		columnName.ReleaseBuffer();
		columnNum = i;
		
		sSql = "CREATE TABLE " + sSheetName + " (" + sSql + " )";
		database.ExecuteSQL(sSql);

		//����������
		int nItemIndex;
		for (nItemIndex = 0; nItemIndex < pList->GetItemCount(); nItemIndex++)
		{
			strV = "";
			for (i = 0; i < columnNum; i++)
			{
				if (i != 0)
					strV = strV + ",";
				strV = strV + "'" + pList->GetItemText(nItemIndex, i) + "'";
			}
			//sSql = "DELETE * FROM [" + sSheetName + "$]";
			//database.ExecuteSQL(sSql);
			

			//sSql = "INSERT INTO [" + sSheetName + "$] (" + strH + ")" + " VALUES(" + strV + ")";
			sSql = "INSERT INTO " + sSheetName + " (" + strH + ")" + " VALUES(" + strV + ")";
			database.ExecuteSQL(sSql);
		}

		database.Close();
		CString strTip;
		strTip.Format("�����ļ�������: %s", sExcelFile);
		MessageBox(NULL, strTip, NULL, MB_OK | MB_TOPMOST);
		return TRUE;
	}
	return FALSE;
}

//��ȡ����
CString OperationGM::GetExcelDriver(char* driverName)
{
	CString sDriver = "";

	char szBuf[2001];
	WORD cbBufMax = 2000;
	WORD cbBufOut;

	//��ȡ�Ѿ���װ����������
	if(!SQLGetInstalledDrivers(szBuf, cbBufMax, &cbBufOut))
		return "";

	char* pszBuf = szBuf;
	do 
	{
		if (strstr(pszBuf, driverName) != NULL)
		{
			//����excel����
			sDriver = CString(pszBuf);
			break;
		}
		pszBuf = strchr(pszBuf,'\0') + 1;

	} while (pszBuf[1] !='\0'); 

	return sDriver;
}




//��Excel�ļ�����CListCtrl
bool OperationGM::ImportCListCtrlFromExcel(CListCtrl* pList, CString sExcelFile, CString sSheetName)
{

	CString sDriver;
	sDriver = GetExcelDriver("Excel");
	if (sDriver.IsEmpty())
	{
		MessageBox(NULL, "��û�а�װEXCEL!\n���Ȱ�װEXCEL��ʹ�ñ�����.", NULL, MB_OK|MB_TOPMOST);
		return FALSE;
	}

	//�������д�ȡ���ַ���
	CString sSql;
	sSql.Format("ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, sExcelFile);
	
	CDatabase database;
	if(database.Open(NULL, FALSE, FALSE, sSql))
	{
		CRecordset record(&database);
		
		sSql.ReleaseBuffer();
		sSql = "SELECT * FROM [" + sSheetName + "$]";      //
		record.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
		
		CODBCFieldInfo fieldinfo;
		int i;
		int fieldCount =  record.GetODBCFieldCount();
		
		int col = pList->GetHeaderCtrl()->GetItemCount();
		for (i=0; i < col ; i++)
			pList->DeleteColumn(0);


		for(i = 0; i <fieldCount; i++)
		{
			record.GetODBCFieldInfo(i, fieldinfo);
			pList->InsertColumn(i, fieldinfo.m_strName, LVCFMT_LEFT, 160);
		}

		CString sItem;
		int rowNum = 0;
		while ( !record.IsEOF() )
		{
			pList->InsertItem(rowNum,"");
			for(i = 0; i < fieldCount; i++)
			{
				record.GetFieldValue(i, sItem);	
				
				pList->SetItemText(rowNum,i,sItem);
			}
			record.MoveNext();	
			rowNum++;
		}
		record.Close();
		database.Close();
	}
}

bool OperationGM::ShowVIP(CSocketData *socketdata, CListCtrl* pList)
{
	//MessageBox(NULL, "���յ�����������Ϣ", MB_OK | MB_TOPMOST);
	CGlobalStruct::TFLV m_BGS;
	m_BGS = socketdata->getTLV(1,1);//��ȡ��һ��Ҫ��ӵ���������

	pList->InsertItem(0, (LPCTSTR)m_BGS.lpdata);
	


	return true;
}

void OperationGM::ConsoleLog(CString msg)
{
	if(AllocConsole())
	{
		freopen("CONOUT$","w+t", stdout);
		cout<<(LPCTSTR)msg<<endl;
		fclose(stdout);
		FreeConsole();
	}
}