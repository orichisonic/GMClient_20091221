// DlgSelect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GMClient.h"
#include "DlgSelect.h"
#include ".\dlgselect.h"


// CDlgSelect

IMPLEMENT_DYNCREATE(CDlgSelect, CFormView)

CDlgSelect::CDlgSelect()
	: CFormView(CDlgSelect::IDD)
{
}

CDlgSelect::~CDlgSelect()
{
}

void CDlgSelect::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABSELECT, tbcSelect);
}

BEGIN_MESSAGE_MAP(CDlgSelect, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABSELECT, OnTcnSelchangeTabselect)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RESVIEW,OnRecView)
	ON_MESSAGE(UM_RECEIVE,OnShowDlg)
	ON_NOTIFY(NM_CLICK, IDC_TABSELECT, OnNMClickTabselect)
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

#ifdef _DEBUG
void CDlgSelect::AssertValid() const
{
	CFormView::AssertValid();
}

void CDlgSelect::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

// CTabSelect ��Ϣ�������
void CDlgSelect::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_imagetab.Create(16,16,TRUE,1,1);
	m_imagetab.Add(AfxGetApp()->LoadIcon(IDI_ICONCLOSE));
	tbcSelect.SetImageList(&m_imagetab);

	CRect rs;
	GetClientRect(rs);
	if(tbcSelect.m_hWnd!=NULL)
	{
		tbcSelect.MoveWindow(rs);//���ú�tbcSelect��λ��
	}
}


//�Զ��ı��С
void CDlgSelect::OnSize(UINT nType, int cx, int cy)
{
	CRect rs;
	GetClientRect(rs);
	if(tbcSelect.m_hWnd!=NULL)
	{
		tbcSelect.MoveWindow(rs);//���ú�tbcSelect��λ��
	}
	CFormView::OnSize(nType, cx, cy);
}

//����ѡ����йر�
void CDlgSelect::OnNMClickTabselect(NMHDR *pNMHDR, LRESULT *pResult)
{
	DWORD dwPos = GetMessagePos();
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

	tbcSelect.ScreenToClient(&point);

	TCHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = TCHT_ONITEMICON;

	int nItem = tbcSelect.HitTest(&lvinfo);
	if(nItem > -1)  
	{  
		CRect rect;  
		tbcSelect.GetItemRect( nItem, &rect);
		rect.left = rect.left + 8 ;
		rect.right = rect.left + 16;//PADDING��ICON���ıߵļ��...  
		if(::PtInRect(rect,point))  
		{  
			char szItemName[100];
			TC_ITEM m_PTCItem;   
			memset( &m_PTCItem, 0, sizeof( TC_ITEM ) );   
			m_PTCItem.mask = TCIF_TEXT;   
			m_PTCItem.pszText = szItemName;   
			m_PTCItem.cchTextMax = 100;   
			m_PTCItem.iImage = 0;   

			tbcSelect.GetItem(nItem, &m_PTCItem);
			CString tabName=m_PTCItem.pszText;
			CString DlgName=tabName.Right(tabName.GetLength()-tabName.Find('-')-1);
			CString GameName=tabName.Left(tabName.Find('-'));


			ShowDialog(GameName,DlgName);
			


			tbcSelect.DeleteItem(nItem);//ɾȥ��Ӧ��ǩҳ

			
			CloseDialog(GameName,DlgName);
			//nItem = tbcSelect.GetCurSel();
			nItem=0;
			tbcSelect.GetItem(nItem, &m_PTCItem);
			tabName=m_PTCItem.pszText;
			DlgName=tabName.Right(tabName.GetLength()-tabName.Find('-')-1);
			GameName=tabName.Left(tabName.Find('-'));

			ShowDialog(GameName,DlgName);

		}
	}   

	*pResult = 0;
}

//ѡ��ͬ��CTabCtrl�����л��Ի���
void CDlgSelect::OnTcnSelchangeTabselect(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		int selectItem = tbcSelect.GetCurSel();//��ȡ��ѡ�еı�ǩҳ����

		char szItemName[100];
		TC_ITEM m_PTCItem;   
		memset( &m_PTCItem, 0, sizeof( TC_ITEM ) );   
		m_PTCItem.mask = TCIF_TEXT;   
		m_PTCItem.pszText = szItemName;   
		m_PTCItem.cchTextMax = 100;   
		m_PTCItem.iImage = -1;   

		tbcSelect.GetItem(selectItem, &m_PTCItem);
		CString tabName=m_PTCItem.pszText;
		CString DlgName=tabName.Right(tabName.GetLength()-tabName.Find('-')-1);
		CString GameName=tabName.Left(tabName.Find('-'));
		Ctabname::tabname=tabName;//��tab���Ƹ���tabname �����  090901
		ShowDialog(GameName,DlgName);
	}
	catch(...)
	{
	}

	*pResult = 0;
}

//���մ򿪶Ի������Ϣ
LRESULT CDlgSelect::OnRecView(WPARAM wParam, LPARAM lParam)
{
	//theApp.XD_OpenDialog("��ѯ�����Ϣ");
	char* strDlgName = (char*)wParam;//��ȡҪ�򿪵�ģ������
	char* strGameName=(char *)lParam;
	
	CString DlgName = "";
	DlgName.Format("%s",strDlgName);//��ʼ��Ҫ�򿪵�ģ������


	char tabName[256];
	sprintf(tabName,"%s-%s",strGameName,strDlgName);

	TC_ITEM m_PTCItem;
	m_PTCItem.mask = TCIF_TEXT|TCIF_IMAGE;	
	m_PTCItem.pszText =(char *)&tabName;//�趨��Ϸ����
	CIni mIni;
	if(tbcSelect.GetItemCount() == 0)//Tab Control��û���κ�ѡ��
	{	
		if(!strcmp(strDlgName, mIni.ReadValue("Global","AGABUNB"))||!strcmp(strDlgName, mIni.ReadValue("Global","AccountQuery"))||!strcmp(strDlgName, mIni.ReadValue("Global","BanQuery")))
		{
			// AGABUNB ������Ϸ�ʺŽ��ͷ�ͣ.
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);
			tbcSelect.SetCurSel(0);

			theApp.m_pOpenCAGABUNBDlgFun(DlgName);
		}
		else if(!strcmp(strGameName,mIni.ReadValue("Global","GM_Name")))
		{
			theApp.GM_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
			tbcSelect.SetCurSel(0);

		}
		else if(!strcmp(strGameName,mIni.ReadValue("Global","PAL_Name")))
		{
			theApp.PAL_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
			tbcSelect.SetCurSel(0);
		}
		else if(!strcmp(strGameName,mIni.ReadValue("Global","CG2_Name")))
		{
			theApp.CG2_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
			tbcSelect.SetCurSel(0);
		}
		else if(!strcmp(strGameName,mIni.ReadValue("Global","GT_Name")))
		{
			theApp.GTOWN_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
			tbcSelect.SetCurSel(0);
		}
		else if(!strcmp(strGameName,mIni.ReadValue("Global","SDO_Name")))
		{
			theApp.SDO_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
			tbcSelect.SetCurSel(0);
		}
		else if(!strcmp(strGameName,mIni.ReadValue("Global","JW2_Name")))
		{
			theApp.JW2_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
			tbcSelect.SetCurSel(0);
		}
		else if(!strcmp(strGameName,mIni.ReadValue("Global","WA_Name")))
		{
		
			theApp.WA_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
			tbcSelect.SetCurSel(0);
		}
		//////////////////////peng start ����
		else if(!strcmp(strGameName,mIni.ReadValue("Global","XD_Name")))
		{
			theApp.XD_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
			tbcSelect.SetCurSel(0);
		}
		/////////////////////peng end

	}
	else
	{
		int nIndex = -1;
		CString curName = "";
		CString actName="";

		char szItemName[100];
		TC_ITEM s_PTCItem;   //���ڱ����Ѿ����򿪵ı�ǩҳ��Ϣ
		memset( &s_PTCItem, 0, sizeof( TC_ITEM ) );   
		s_PTCItem.mask = TCIF_TEXT;   
		s_PTCItem.pszText = szItemName;
		s_PTCItem.cchTextMax = 100;   

		int i=0;
		for(i=0;i<tbcSelect.GetItemCount();i++)
		{
			tbcSelect.GetItem(i, &s_PTCItem);
			curName = s_PTCItem.pszText;//��ȡÿһ����ǩҳ������
			actName=curName.Right(curName.GetLength()-curName.Find('-')-1);
			if(!strcmp(DlgName, actName))//����Ի����Ѿ�����
			{
				nIndex = i;
				break;
			}
		}
		if(nIndex < 0)//û�д򿪹��Ի���
		{
			if(!strcmp(strDlgName, mIni.ReadValue("Global","AGABUNB"))||!strcmp(strDlgName, mIni.ReadValue("Global","AccountQuery"))||!strcmp(strDlgName, mIni.ReadValue("Global","BanQuery")))
			{
				// AGABUNB ������Ϸ�ʺŽ��ͷ�ͣ.
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);
				tbcSelect.SetCurSel(0);

				theApp.m_pOpenCAGABUNBDlgFun(DlgName);
			}
			else if(!strcmp(strGameName,mIni.ReadValue("Global","GM_Name")))
			{
				theApp.GM_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
				tbcSelect.SetCurSel(0);

			}
			else if(!strcmp(strGameName,mIni.ReadValue("Global","PAL_Name")))
			{
				theApp.PAL_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
				tbcSelect.SetCurSel(0);
			}
			else if(!strcmp(strGameName,mIni.ReadValue("Global","CG2_Name")))
			{
				theApp.CG2_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
				tbcSelect.SetCurSel(0);
			}
			else if(!strcmp(strGameName,mIni.ReadValue("Global","GT_Name")))
			{
				theApp.GTOWN_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
				tbcSelect.SetCurSel(0);
			}
			else if(!strcmp(strGameName,mIni.ReadValue("Global","SDO_Name")))
			{
				theApp.SDO_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
				tbcSelect.SetCurSel(0);
			}
			else if(!strcmp(strGameName,mIni.ReadValue("Global","JW2_Name")))
			{
				theApp.JW2_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
				tbcSelect.SetCurSel(0);
			}
			else if(!strcmp(strGameName,mIni.ReadValue("Global","WA_Name")))
			{
				theApp.WA_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
				tbcSelect.SetCurSel(0);
			}

			//////////////////////peng start ����
			else if(!strcmp(strGameName,mIni.ReadValue("Global","XD_Name")))
			{
				theApp.XD_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//����Ҫ�ı�ǩҳ��ӽ�ȥ
				tbcSelect.SetCurSel(0);
			}
			/////////////////////peng end
		}
		else//�Ի����Ѿ�����
		{
			tbcSelect.SetCurSel(nIndex);//�л�����Ӧ�ı�ǩҳ
			ShowDialog(strGameName,DlgName);
		}
	}

	return true;
}

//������ʾ�Ի������Ϣ
LRESULT CDlgSelect::OnShowDlg(WPARAM wParam, LPARAM lParam)
{
	try
	{
		int selectItem = tbcSelect.GetCurSel();//��ȡ��ѡ�еı�ǩҳ����

		if(selectItem> -1)
		{
			char szItemName[100];
			TC_ITEM m_PTCItem;   
			memset( &m_PTCItem, 0, sizeof( TC_ITEM ) );   
			m_PTCItem.mask = TCIF_TEXT;   
			m_PTCItem.pszText = szItemName;   
			m_PTCItem.cchTextMax = 100;   
			m_PTCItem.iImage = -1;   

			tbcSelect.GetItem(selectItem, &m_PTCItem);
			CString DlgName = m_PTCItem.pszText;//��ȡ��ѡ�еı�ǩҳ����

			theApp.GM_ShowDialog(DlgName);//��ʾ�µ�TOP��ǩҳ��Ӧ�ĶԻ���
			theApp.PAL_ShowDialog(DlgName);
			theApp.GTOWN_ShowDialog(DlgName);
			theApp.CG2_ShowDialog(DlgName);

			//maple add
			theApp.SDO_ShowDialog(DlgName);
			theApp.JW2_ShowDialog(DlgName);
			theApp.WA_ShowDialog(DlgName);
			theApp.m_pShowGABUNBDlgFun(DlgName);
		}
		
	}
	catch(...)
	{
	}
	return true;
}


//�رնԻ���
void CDlgSelect::OnClose()
{
	if(tbcSelect.GetItemCount() != 0)
	{
		tbcSelect.DeleteAllItems();
	}
	m_imagetab.DeleteImageList();
	CFormView::OnClose();
}

void CDlgSelect::ShowDialog(CString GameName,CString DlgName)
{
	CIni mIni;
	if(!strcmp(DlgName, mIni.ReadValue("Global","AGABUNB"))||!strcmp(DlgName, mIni.ReadValue("Global","AccountQuery"))||!strcmp(DlgName, mIni.ReadValue("Global","BanQuery")))
	{
		// AGABUNB ������Ϸ�ʺŽ��ͷ�ͣ.
		theApp.m_pShowGABUNBDlgFun(DlgName);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","GM_Name")))
	{
		theApp.GM_ShowDialog(DlgName);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","PAL_Name")))
	{
		theApp.PAL_ShowDialog(DlgName);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","CG2_Name")))
	{
		theApp.CG2_ShowDialog(DlgName);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","GT_Name")))
	{
		theApp.GTOWN_ShowDialog(DlgName);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","SDO_Name")))
	{
		theApp.SDO_ShowDialog(DlgName);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","JW2_Name")))
	{
		theApp.JW2_ShowDialog(DlgName);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","WA_Name")))
	{
		theApp.WA_ShowDialog(DlgName);
	}
	///////peng begin
	else if(!strcmp(GameName,mIni.ReadValue("Global","XD_Name")))
	{
		theApp.XD_ShowDialog(DlgName);
	}
	//////peng end
}
void CDlgSelect::CloseDialog(CString GameName,CString DlgName)
{
	CIni mIni;
	if(!strcmp(GameName,mIni.ReadValue("Global","GM_Name")))
	{
		theApp.GM_DialogMsg(DlgName, WM_CLOSE, 0, 0);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","PAL_Name")))
	{
		theApp.PAL_DialogMsg(DlgName, WM_CLOSE, 0, 0);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","CG2_Name")))
	{
		theApp.CG2_DialogMsg(DlgName, WM_CLOSE, 0, 0);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","GT_Name")))
	{
		theApp.GTOWN_DialogMsg(DlgName, WM_CLOSE, 0, 0);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","SDO_Name")))
	{
		theApp.SDO_DialogMsg(DlgName,WM_CLOSE,0,0);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","JW2_Name")))
	{
		theApp.JW2_DialogMsg(DlgName,WM_CLOSE,0,0);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","WA_Name")))
	{
		theApp.WA_DialogMsg(DlgName,WM_CLOSE,0,0);
	}
	if(!strcmp(DlgName, mIni.ReadValue("Global","AGABUNB")))
	{
		// AGABUNB ������Ϸ�ʺŽ��ͷ�ͣ.
		theApp.m_pCloseDialogFun(DlgName);//"AGABUNB");//maple update
	}
	else if(!strcmp(DlgName, mIni.ReadValue("Global","AccountQuery")))
	{
		// AGABUNB ������Ϸ�ʺŽ��ͷ�ͣ.
		theApp.m_pCloseDialogFun(DlgName);//"AccountQuery");//maple update
	}
	else if(!strcmp(DlgName, mIni.ReadValue("Global","BanQuery")))
	{
		// AGABUNB ������Ϸ�ʺŽ��ͷ�ͣ.
		theApp.m_pCloseDialogFun(DlgName);//"AccountQuery");//maple update
	}
	/////////////peng begin
	else if(!strcmp(GameName, mIni.ReadValue("Global","XD_Name")))
	{
		// AGABUNB ������Ϸ�ʺŽ��ͷ�ͣ.
		theApp.XD_DialogMsg(DlgName, WM_CLOSE, 0, 0);
	}
	////////////peng end
}

void CDlgSelect::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CFormView::OnPaint()
	int selectItem = tbcSelect.GetCurSel();//��ȡ��ѡ�еı�ǩҳ����

	if(selectItem> -1)
	{
		char szItemName[100];
		TC_ITEM m_PTCItem;   
		memset( &m_PTCItem, 0, sizeof( TC_ITEM ) );   
		m_PTCItem.mask = TCIF_TEXT;   
		m_PTCItem.pszText = szItemName;   
		m_PTCItem.cchTextMax = 100;   
		m_PTCItem.iImage = -1;   

		tbcSelect.GetItem(selectItem, &m_PTCItem);
		CString DlgName = m_PTCItem.pszText;//��ȡ��ѡ�еı�ǩҳ����
		Ctabname::tabname=DlgName;

	}
}
