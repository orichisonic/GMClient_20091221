// GMClientView.h : CGMClientView ��Ľӿ�
//


#pragma once


class CGMClientView : public CView
{
protected: // �������л�����
	CGMClientView();
	DECLARE_DYNCREATE(CGMClientView)

// ����
public:
	CGMClientDoc* GetDocument() const;

// ����
public:

// ��д
	public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CGMClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GMClientView.cpp �ĵ��԰汾
inline CGMClientDoc* CGMClientView::GetDocument() const
   { return reinterpret_cast<CGMClientDoc*>(m_pDocument); }
#endif

