// TreeMenu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GMClient.h"
#include "TreeMenu.h"
#include ".\treemenu.h"
#include "MainFrm.h"


// CTreeMenu

IMPLEMENT_DYNCREATE(CTreeMenu, CFormView)

CTreeMenu::CTreeMenu()
	: CFormView(CTreeMenu::IDD)
{
}

CTreeMenu::~CTreeMenu()
{
}

void CTreeMenu::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREEMENU, tMenuList);
}

BEGIN_MESSAGE_MAP(CTreeMenu, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_TREEMENU, OnNMDblclkTreemenu)
	ON_MESSAGE(UM_RESVIEW,OnRecView)
	ON_NOTIFY(NM_RCLICK, IDC_TREEMENU, OnNMRclickTreemenu)
	ON_COMMAND(ID__REFRESH, OnRefresh)
END_MESSAGE_MAP()


// CTreeMenu ���

#ifdef _DEBUG
void CTreeMenu::AssertValid() const
{
	CFormView::AssertValid();
}

void CTreeMenu::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CTreeMenu ��Ϣ�������
void CTreeMenu::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CIni mIni;
	SetDlgItemText(ID__REFRESH,mIni.ReadValue("Global","Refresh"));

	DWORD dwStyle = GetWindowLong(tMenuList.m_hWnd,GWL_STYLE);
	dwStyle |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;

    SetWindowLong(tMenuList.m_hWnd,GWL_STYLE,dwStyle);

	CRect rs;
	GetClientRect(rs);
	tMenuList.MoveWindow(rs);//���ú�m_ResTree��λ��
}

//����Form
int CTreeMenu::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

//�Զ��ı��С
void CTreeMenu::OnSize(UINT nType, int cx, int cy)
{
	CRect rs;
	GetClientRect(rs);
	if(tMenuList.m_hWnd!=NULL)
	{
		tMenuList.MoveWindow(rs);//���ú�m_ResTree��λ��
	}
	CFormView::OnSize(nType, cx, cy);
}

//������Ϣ
LRESULT CTreeMenu::OnRecView(WPARAM wParam, LPARAM lParam)
{
	int num=0;

	unsigned char* lpReceive=(unsigned char*)wParam;
	int bodyLength = (int)lParam;

	CIni mIni;
	CPacketHead packethead;		
	packethead.Create(bodyLength);
	try
	{
		bool b_result=packethead.DeHead(lpReceive,bodyLength);
		if(b_result)
		{
			theApp.m_SendCount = 0;//�ظ����ʹ���Ϊ0
			switch((unsigned int)packethead.GetMessageID())
			{	
			case CEnumCore::Message_Tag_ID::USER_MODULE_QUERY_RESP://������ص���ģ����Ϣ
				{
					tMenuList.DeleteAllItems();

					CSocketData socketdata;
					socketdata.Create(packethead.m_packethead.bodylen/8);
					socketdata.DeBody(packethead.getDataBuf()+18,packethead.m_packethead.bodylen);

					CGlobalStruct::TFLV m_tflv,m_tflv1,tmpm_tflv;

					m_tflv=socketdata.getTLV(1,1);//��ȡ��һ��TFLV
					if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)
					{
						socketdata.Destroy();
						return false;
					}

					m_tflv=socketdata.getTLVByTag(CEnumCore::TagName::GameName,0);//��ȡ��һ����Ϸ����
					m_root[num]=tMenuList.InsertItem((LPCSTR)&m_tflv.lpdata);//����һ����Ϸ���Ʋ��뵽���ĸ���
					tmpm_tflv=m_tflv;
					m_tflv1=socketdata.getTLVByTag(CEnumCore::TagName::ModuleClass,tmpm_tflv.nIndex);//��ȡ��һ��ģ������
					//m_tflv1=socketdata.getTLVByName(1, CEnumCore::TagName::ModuleClass);


					tMenuList.InsertItem(mIni.ReadValue("Global",(LPCSTR)m_tflv1.lpdata),m_root[num]);//����һ��ģ�����Ʋ��뵽��һ����Ϸ���Ƶ�����
					while(tmpm_tflv.nIndex!=0)
					{
						tmpm_tflv=socketdata.getTLVByTag( CEnumCore::TagName::GameName,tmpm_tflv.nIndex+1);//��ȡ��һ����Ϸ����
						if(!strcmp((char *)&tmpm_tflv.lpdata,(char *)&m_tflv.lpdata))//���ǰ��������Ϸ������ͬ
						{
							m_tflv1=socketdata.getTLVByTag(CEnumCore::TagName::ModuleClass,tmpm_tflv.nIndex);//��ȡ��һ��ģ������
							tMenuList.InsertItem(mIni.ReadValue("Global",(LPCSTR)m_tflv1.lpdata),m_root[num]);//����һ��ģ������ֱ�Ӳ��뵽��Ϸ���Ƶ�����
						}
						else//���ǰ��������Ϸ���Ʋ�ͬ
						{
							num++;
							m_tflv=tmpm_tflv;//��ֵΪ�µ���Ϸ����
							if(m_tflv.nIndex!=0)
							{
								m_root[num]=tMenuList.InsertItem((LPCSTR)&m_tflv.lpdata);//���µ���Ϸ���Ʋ��뵽���ĸ���
							}
							m_tflv1=socketdata.getTLVByTag(CEnumCore::TagName::ModuleClass,tmpm_tflv.nIndex);//��ȡ��һ��ģ������
							if(m_tflv.nIndex!=0)
							{
								tMenuList.InsertItem(mIni.ReadValue("Global",(LPCSTR)m_tflv1.lpdata),m_root[num]);//��ģ�����Ʋ��뵽��Ϸ���Ƶ�����
							}
						}
					}
					socketdata.Destroy();
				}
			}
		}	
		else
		{
			if(theApp.m_SendCount<5)//����ظ����ʹ���С��5��
			{
				OnRefresh();//����ԭ��������
				theApp.m_SendCount++;//�ظ����ʹ�����1
			}
			else
			{
				::EnableWindow(this->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
				::SetWindowPos(this->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
				MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),MB_OK);//���ݽ����쳣
				return false;
			}
		}
	}
	catch(...)
	{
	}	
	return true;
}

//˫��CTreeCtrl
void CTreeMenu::OnNMDblclkTreemenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM m_hTreeItem = tMenuList.GetSelectedItem();//��ȡѡ�е����ڵ�
	HTREEITEM m_hParentTreeItem=tMenuList.GetParentItem(m_hTreeItem);//��ȡѡ�е����ڵ�ĸ����
	if(m_hTreeItem!=NULL&&m_hParentTreeItem!=NULL)
	{
		CIni mIni;
		char m_treemessage[150],m_parenttreemessage[150];
		sprintf(m_treemessage,"%s",mIni.wcharToChar(tMenuList.GetItemText(m_hTreeItem)));
		sprintf(m_parenttreemessage,"%s",mIni.wcharToChar(tMenuList.GetItemText(m_hParentTreeItem)));
	
		CMainFrame* pMainFrame=(CMainFrame*)this->GetParent()->GetParent();//��ȡ�������ָ��
		::SendMessage(pMainFrame->wndSplitDlg.GetPane(0,0)->m_hWnd,UM_RESVIEW,(WPARAM)(m_treemessage),(LPARAM)m_parenttreemessage);//�����յ���ģ����Ϣ���ݸ�CDlgSelect��
	}
	

	*pResult = 0;
}

//�Ҽ����CTreeCtrl�����˵�
void CTreeMenu::OnNMRclickTreemenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
    {
        DWORD dwPos = GetMessagePos();//��ȡ��ǰ�����λ��
        CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

        CMenu menu;
		VERIFY( menu.LoadMenu(IDR_TMENU));//����ˢ�²˵�
        CMenu* popup = menu.GetSubMenu(0);//��ȡ�Ӳ˵�
        ASSERT( popup != NULL );
        popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
		popup->DestroyMenu();
		popup=NULL;
		menu.DestroyMenu();
    } 
	catch(...)
	{
	}
    *pResult = 0;
}

//���ˢ�²˵�ʱ���еĲ���
void CTreeMenu::OnRefresh()
{
	try
	{
		theApp.menuflag = false;

		CSocketData socketdata;
		socketdata.InitCreate(1,1);	//ֻ��һ������������ԱID
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		int alllength=socketdata.EnBody();

		CPacketHead packethead;		
		packethead.Create(alllength);

		packethead.AddHeader(1,CEnumCore::Msg_Category::USER_MODULE_ADMIN,CEnumCore::ServiceKey::USER_MODULE_QUERY,alllength);//�����û�ģ������

		packethead.EnSendBuf(&alllength,socketdata.getDes(),packethead.m_packethead.bodylen);
		theApp.m_clientsocket.Send(packethead.getSendBuf(),alllength);//����ˢ�²˵�������
	}
	catch(...)
	{
	}
}
