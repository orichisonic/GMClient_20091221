// GMClientDoc.cpp :  CGMClientDoc ���ʵ��
//

#include "stdafx.h"
#include "GMClient.h"

#include "GMClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGMClientDoc

IMPLEMENT_DYNCREATE(CGMClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CGMClientDoc, CDocument)
END_MESSAGE_MAP()


// CGMClientDoc ����/����

CGMClientDoc::CGMClientDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CGMClientDoc::~CGMClientDoc()
{
}

BOOL CGMClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CGMClientDoc ���л�

void CGMClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CGMClientDoc ���

#ifdef _DEBUG
void CGMClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGMClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGMClientDoc ����
