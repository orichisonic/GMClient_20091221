// GMClientView.cpp : CGMClientView ���ʵ��
//

#include "stdafx.h"
#include "GMClient.h"

#include "GMClientDoc.h"
#include "GMClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGMClientView

IMPLEMENT_DYNCREATE(CGMClientView, CView)

BEGIN_MESSAGE_MAP(CGMClientView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGMClientView ����/����

CGMClientView::CGMClientView()
{
	// TODO: �ڴ˴���ӹ������

}

CGMClientView::~CGMClientView()
{
}

BOOL CGMClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CGMClientView ����

void CGMClientView::OnDraw(CDC* /*pDC*/)
{
	CGMClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CGMClientView ��ӡ

BOOL CGMClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGMClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CGMClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CGMClientView ���

#ifdef _DEBUG
void CGMClientView::AssertValid() const
{
	CView::AssertValid();
}

void CGMClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGMClientDoc* CGMClientView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGMClientDoc)));
	return (CGMClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CGMClientView ��Ϣ�������
