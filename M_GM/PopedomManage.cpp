// PopedomManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_GM.h"
#include "PopedomManage.h"
#include ".\popedommanage.h"


// CPopedomManage �Ի���

IMPLEMENT_DYNAMIC(CPopedomManage, CDialog)
CPopedomManage::CPopedomManage(CWnd* pParent /*=NULL*/)
	: CDialog(CPopedomManage::IDD, pParent)
{
}

CPopedomManage::~CPopedomManage()
{
}

void CPopedomManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTGAME, listGame);
	DDX_Control(pDX, IDC_LISTMODULE, listModule);
}


BEGIN_MESSAGE_MAP(CPopedomManage, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(NM_CLICK, IDC_LISTGAME, OnNMClickListgame)
	ON_NOTIFY(NM_CLICK, IDC_LISTMODULE, OnNMClickListmodule)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// ��ʼ���Ի���
BOOL CPopedomManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// ��ʼ����ʾ�ַ�

	//OperationGM operGM;

	listGame.SetExtendedStyle(listGame.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);
	listGame.InsertColumn(0,theApp.operGM.ReadValue("MGM","PM_UI_GameList"),LVCFMT_CENTER,250,-1);	

	listModule.SetExtendedStyle(listModule.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);
	listModule.InsertColumn(0,theApp.operGM.ReadValue("MGM","PM_UI_ModuleList"),LVCFMT_CENTER,250,-1);	

	listGame.DeleteAllItems();
	listModule.DeleteAllItems();

	InitGameList();

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CPopedomManage::InitUI()
{
	//OperationGM operGM;

	SetWindowText(theApp.operGM.ReadValue("MGM","PM_UI_PopedomManage"));

	SetDlgItemText(IDC_LBLGAMEPOPEDOM,theApp.operGM.ReadValue("MGM","PM_UI_GamePopedom"));
	SetDlgItemText(IDOK,theApp.operGM.ReadValue("MGM","MakeSure"));
	SetDlgItemText(IDCANCEL,theApp.operGM.ReadValue("MGM","Cancel"));
}

// ��ʼ��˽�б���
void CPopedomManage::initVar(CString uName,int uID)
{
	userName = uName;
	userID = uID;
}

// �����Ի���
int CPopedomManage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;	

	return 0;
}

// ����������Ϸ�б�
void CPopedomManage::InitGameList()
{
	//OperationGM operGM;
	try
	{		
		CIni mIni;

		CSocketData socketdata;		
		socketdata.InitCreate(1,2);//������������������ʺź����ID
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(userName),(unsigned char *)mIni.wcharToChar(userName));//����ʺ�

		_itoa(userID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::GAME_ADMIN,CEnumCore::ServiceKey::GAME_MODULE_QUERY))//���Ͳ�ѯ��Ϸģ����Ϣ������
		{
		    ::EnableWindow(this->GetParent()->GetParent()->m_hWnd,false);//��������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}	
}

// ������Ϸ�б���ȡ��Ӧ��ģ���б�
void CPopedomManage::OnNMClickListgame(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listGame.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		UINT nFlag;
		int selectItem = listGame.HitTest(point,&nFlag);//�������û��б���ѡ�е��к�	
		listModule.DeleteAllItems();

		CGlobalStruct::TFLV m_tflv;
		CGlobalStruct::TFLV tmp_tflv;
		if(nFlag == LVHT_ONITEMSTATEICON) 
		{			
			if(!listGame.GetCheck(selectItem))
			{
				CString gameName = listGame.GetItemText(selectItem,0);
				CString moduleName = "";
				CString gameModule="";
				int num = 0;
				for(int i=1;i <= ModuleData.getQueryNum();i++)
				{
					m_tflv = ModuleData.getTLVByName(i, CEnumCore::TagName::GameName);
					tmp_tflv = ModuleData.getTLVByName(i, CEnumCore::TagName::ModuleName);
					if(!strcmp((LPCSTR)m_tflv.lpdata,gameName))
					{
						moduleName = (LPCSTR)tmp_tflv.lpdata;
						gameModule.Format("%s-%s",gameName,moduleName);
						listModule.InsertItem(num, gameModule);//����ѡ�е���Ϸ��ص�����ģ����Ϣ�����뵽�б���

						POSITION pos = SendData.GetStartPosition(); //��ȡ�ѷ����ģ���еĵ�һ��
						int nKey;
						CString pt;
						while (pos != NULL)//ѭ������CMap��Ķ���
						{
							SendData.GetNextAssoc(pos, nKey, pt);//��ȡCMap��Ķ���������һ������ݣ�posΪλ�ã�nkeyΪ��ֵ��ptΪ���������
							if(!strcmp(pt,gameModule))//�����ģ���������û�ģ�����Ѿ����ڵĻ�
							{
								listModule.SetCheck(num);//����Ϊѡ��״̬
							}
						}
						num++;
					}
				}
			}
		} 
		else if(listGame.GetCheck(selectItem))
		{
			CString gameName = listGame.GetItemText(selectItem,0);
			CString moduleName = "";
			CString gameModule="";
			int num = 0;
			for(int i=1;i <= ModuleData.getQueryNum();i++)
			{
				m_tflv = ModuleData.getTLVByName(i, CEnumCore::TagName::GameName);
				tmp_tflv = ModuleData.getTLVByName(i, CEnumCore::TagName::ModuleName);
				if(!strcmp((LPCSTR)m_tflv.lpdata,gameName))
				{
					moduleName = (LPCSTR)tmp_tflv.lpdata;
					gameModule.Format("%s-%s",gameName,moduleName);
					listModule.InsertItem(num, gameModule);//����ѡ�е���Ϸ��ص�����ģ����Ϣ�����뵽�б���
				

					POSITION pos = SendData.GetStartPosition(); //��ȡ�ѷ����ģ���еĵ�һ��
					int nKey;
					CString pt;
					while (pos != NULL)//ѭ������CMap��Ķ���
					{
						SendData.GetNextAssoc(pos, nKey, pt);//��ȡCMap��Ķ���������һ������ݣ�posΪλ�ã�nkeyΪ��ֵ��ptΪ���������
						if(!strcmp(pt,gameModule))//�����ģ���������û�ģ�����Ѿ����ڵĻ�
						{
							listModule.SetCheck(num);//����Ϊѡ��״̬
						}
					}
					num++;
				}
			}
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}
//
//// ����ģ���б�������Ӧ����Ϣ
void CPopedomManage::OnNMClickListmodule(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listModule.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		UINT nFlag;
		int selectItem = listModule.HitTest(point,&nFlag);//�������û��б���ѡ�е��к�	
		CIni mIni;

		if(selectItem >= 0)
		{
			CString moduleName = "";
			CString GameName="";
	
			CGlobalStruct::TFLV m_tflv;
			CGlobalStruct::TFLV tmp_tflv;
			CGlobalStruct::TFLV game_tflv;
			CString gameModule="";
			if(nFlag == LVHT_ONITEMSTATEICON) //���ѡ���˸�ѡ��
			{
				if(!listModule.GetCheck(selectItem))//���ԭ������ѡ��״̬
				{
					moduleName = listModule.GetItemText(selectItem,0);
					int moduleID = 0;
					for(int i = 1;i <= ModuleData.getQueryNum();i++)
					{
						game_tflv=ModuleData.getTLVByName(i, CEnumCore::TagName::GameName);
						m_tflv = ModuleData.getTLVByName(i, CEnumCore::TagName::ModuleName);
						tmp_tflv = ModuleData.getTLVByName(i, CEnumCore::TagName::Module_ID);
						gameModule.Format("%s-%s",game_tflv.lpdata,m_tflv.lpdata);
						if(!strcmp(gameModule,moduleName))
						{
							moduleID = atoi((LPCSTR)tmp_tflv.lpdata);//��ȡģ��ID
							SendData.SetAt(moduleID,moduleName);//��ģ��ID�Ͷ�Ӧ��ģ�����Ʊ��浽CMap��Ķ�����
						}
					}
				}
				else//���ԭ����ѡ��״̬
				{
					moduleName = listModule.GetItemText(selectItem,0);//��ȡģ������
					POSITION pos = SendData.GetStartPosition();//����CMap��Ķ���
					int nKey;
					CString pt;
					while (pos != NULL)
					{
						SendData.GetNextAssoc( pos, nKey, pt );
						if (pt == moduleName)//����û�ԭ�����������Ӧ��ģ��
						{
							SendData.RemoveKey( nKey );//��CMap��Ķ������Ƴ���Ӧ��ģ��
						}
					}
				}
			} 			
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}
//
////����ҷ�����ϷȨ��
void CPopedomManage::OnBnClickedOk()
{
	try
	{
		CIni mIni;//��Ҫ���ڽ�CString���͵��ַ�ת��Ϊchar*���͵�
		//OperationGM operGM;	//�����࣬���ڶ�ȡ�����ļ�������Query�����츴ѡ���CListCtrl	

		CString moduleList;
		CString moduleID;
		POSITION pos = SendData.GetStartPosition();//����CMap��Ķ���
		int nKey;
		CString pt;
		while (pos != NULL)
		{
			SendData.GetNextAssoc( pos, nKey, pt );
			moduleID.Format("%i",nKey);//��Ҫ��ӵ�ģ��IDת��ΪCString����
			moduleList += moduleID;
			moduleList += ",";
		}
		SendData.RemoveAll();
		
		CSocketData socketdata;
		socketdata.InitCreate(1,4); //����������������������ID���û�ID���û�����ģ���б�
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//������ID����¼ʱ�Ѿ�ȷ��

		_itoa(userID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//Ҫ����Ȩ�޵��û�ID

		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(userName),(unsigned char*)mIni.wcharToChar(userName));//Ҫ����Ȩ�޵��û���
		socketdata.AddTFLV(CEnumCore::TagName::ModuleList,CEnumCore::TagFormat::TLV_STRING,strlen(moduleList),(unsigned char*)mIni.wcharToChar(moduleList));//Ҫ������û���ģ��ID

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_MODULE_ADMIN,CEnumCore::ServiceKey::USER_MODULE_UPDATE))//���ͷ���Ȩ������
		{
		    ::EnableWindow(this->GetParent()->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}
}
//
//// ���շ�����Ϣ
LRESULT CPopedomManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ��ĳ���
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ
	
	CIni mIni;
	//OperationGM operGM;

	switch(theApp.m_tag_id)
	{
	case CEnumCore::Message_Tag_ID::GAME_MODULE_QUERY_RESP://������ص��Ƕ�������Ϸģ���б����Ӧ
		{
			ModuleData.Create(bodyLength/8);
			if(!ModuleData.DeBody(lpReceive,bodyLength))
			{
				::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
				::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
				MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),0);		
				ModuleData.Destroy();
				return false;
			}

			listGame.DeleteAllItems();			
			int i=1;
			CGlobalStruct::TFLV m_tflv;
			CGlobalStruct::TFLV tmp_tflv;
			m_tflv = ModuleData.getTLVByName(i,CEnumCore::TagName::GameName);//��ȡ��һ�����ص���Ϸ����
			if(m_tflv.nIndex != 0)//�������Ϸ���ƴ��ڵĻ�
			{
				listGame.InsertItem(i,(LPCTSTR)ModuleData.getTLVByTag(CEnumCore::TagName::GameName,0).lpdata);//��ӵ�CListCtrl�Ķ�����
			}
			for(i = 2;i <= ModuleData.getQueryNum();i++)//ѭ�������е���Ϸ���Ʋ��뵽CListCtrl�Ķ�����
			{
				tmp_tflv = ModuleData.getTLVByName(i,CEnumCore::TagName::GameName);
				if(strcmp((LPCSTR)tmp_tflv.lpdata,(LPCSTR)m_tflv.lpdata))
				{
					listGame.InsertItem(i,(LPCSTR)tmp_tflv.lpdata);
				}
				m_tflv=ModuleData.getTLVByName(i,CEnumCore::TagName::GameName);
			}

			CSocketData socketdata;		
			socketdata.InitCreate(1,2);//������������������ʺź����ID
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(userName),(unsigned char *)mIni.wcharToChar(userName));//����ʺ�

			_itoa(userID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID

			int midlength = socketdata.EnBody();
			if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_MODULE_ADMIN,CEnumCore::ServiceKey::USER_MODULE_QUERY))//���Ͳ�ѯ�û�ģ����Ϣ������
			{
			    ::EnableWindow(this->GetParent()->GetParent()->m_hWnd,false);//��������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
				dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
			socketdata.Destroy();//����CSocketData�ֲ�����
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_MODULE_QUERY_RESP://������ص��Ƕ������û�ģ���б����Ӧ
		{
			UserModule.Create(bodyLength/8);
			if(!UserModule.DeBody(lpReceive,bodyLength))
			{
				::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
				::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
				MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),0);		
				UserModule.Destroy();
				return false;
			}

			CGlobalStruct::TFLV m_tflv;
			CGlobalStruct::TFLV tmp_tflv;
			CGlobalStruct::TFLV gameName_tflv;
			char gameModule[256];
			m_tflv = UserModule.getTLVByName(1,CEnumCore::TagName::GameName);//��ȡ��һ�����ص���Ϸ����
			if(m_tflv.nIndex != 0)//�������Ϸ���ƴ��ڵĻ�
			{
				for(int i=0;i<listGame.GetItemCount();i++)
				{
					if(!strcmp((LPCSTR)m_tflv.lpdata,listGame.GetItemText(i,0)))
					{
						listGame.SetCheck(i);
					}				
				}
			}
			else
			{
				break;
			}
			for(int j = 2;j <= UserModule.getQueryNum();j++)//ѭ�������е���Ϸ���Ʋ��뵽CListCtrl�Ķ�����
			{
				tmp_tflv = UserModule.getTLVByName(j,CEnumCore::TagName::GameName);
				if(strcmp((LPCSTR)tmp_tflv.lpdata,(LPCSTR)m_tflv.lpdata))
				{
					m_tflv=UserModule.getTLVByName(j,CEnumCore::TagName::GameName);
					for(int k=0;k<listGame.GetItemCount();k++)
					{
						if(!strcmp((LPCSTR)m_tflv.lpdata,listGame.GetItemText(k,0)))
						{
							listGame.SetCheck(k);
						}				
					}				
				}				
			}
			for(int index = 1;index<=UserModule.getQueryNum();index++)
			{
				gameName_tflv=UserModule.getTLVByName(index,CEnumCore::TagName::GameName);
				m_tflv=UserModule.getTLVByName(index,CEnumCore::TagName::Module_ID);
				tmp_tflv = UserModule.getTLVByName(index,CEnumCore::TagName::ModuleName);
				sprintf(gameModule,"%s-%s",gameName_tflv.lpdata,tmp_tflv.lpdata);
				SendData.SetAt(atoi((LPCSTR)m_tflv.lpdata),(LPCSTR)gameModule);//���û���ǰ��ģ��Ȩ����Ϣ��ӵ�CMap��Ķ�����
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_MODULE_UPDATE_RESP://������ص��ǲ������������Ӧ
		{
			CSocketData socketdata;
			socketdata.Create(bodyLength/8);
			if(!socketdata.DeBody(lpReceive,bodyLength))
			{
				::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
				::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
				MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),0);		
				socketdata.Destroy();
				return false;
			}

			CGlobalStruct::TFLV m_tflv=socketdata.getTLVByName(1,CEnumCore::TagName::MESSAGE);//������Ķ�ֻ����һ��MESSAGE��ָʾ������û�гɹ�
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operGM.ShowResult(result);//��ʾ�������
			
			::EnableWindow(this->GetParent()->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
			::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
			socketdata.Destroy();
			ModuleData.Destroy();
	        UserModule.Destroy();
			OnCancel();
		}
		break;
	default:
		{
			MessageBox("Error","Error",0);
		}
		break;
	}
	return true;
}

//�رնԻ���
void CPopedomManage::OnBnClickedCancel()
{
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Close");//�رմ���
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::EnableWindow(this->GetParent()->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	if(!SendData.IsEmpty())
	{
	    SendData.RemoveAll();
	}
	ModuleData.Destroy();
	UserModule.Destroy();
	OnCancel();
}