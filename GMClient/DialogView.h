#pragma once

// CDialogView ��ͼ

class CDialogView : public CView
{
	DECLARE_DYNCREATE(CDialogView)

protected:
	CDialogView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDialogView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��ƴ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


