// DialogView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GMClient.h"
#include "DialogView.h"


// CDialogView

IMPLEMENT_DYNCREATE(CDialogView, CView)

CDialogView::CDialogView()
{
}

CDialogView::~CDialogView()
{
}

BEGIN_MESSAGE_MAP(CDialogView, CView)
END_MESSAGE_MAP()


// CDialogView ��ͼ

void CDialogView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CDialogView ���

#ifdef _DEBUG
void CDialogView::AssertValid() const
{
	CView::AssertValid();
}

void CDialogView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// CDialogView ��Ϣ�������
