// GMClientDoc.h :  CGMClientDoc ��Ľӿ�
//


#pragma once

class CGMClientDoc : public CDocument
{
protected: // �������л�����
	CGMClientDoc();
	DECLARE_DYNCREATE(CGMClientDoc)

// ����
public:

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CGMClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


