#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CCG2UpdateSkill �Ի���
#include "OperationCG2.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"

class CCG2UpdateSkill : public CDialog
{
	DECLARE_DYNCREATE(CCG2UpdateSkill)

public:
	CCG2UpdateSkill(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCG2UpdateSkill();


// �Ի�������
	enum { IDD = IDD_DLGUPDATESKILL};//, IDH = IDR_HTML_CG2UPDATESKILL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()

	public:
	// ��ʼ����ʾ�ַ�
	void InitUI();

	private:
	// �����û��б�õ��к�
	int nItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// �ж��û��б��Ƿ���Ҫ��ҳ
	bool pageUInfo;

	// ��Ϸ������IP
	CString ServerIP;

	// ���ID
	CString UserID;

	// ���������ʺ�
	CString UserName;

	// ���������ǳ�
	CString UserNick;

	//��ҽ�ɫ��������
	CString UserSkill;
	
	//��ҽ�ɫ���ܵȼ�
	int UserSkillLevel;

	//��Ҽ���ID
	CString SkillID;

	//��ҽ�ɫ��
	int iCharNo;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;
public:
	//��Ϸ��������Ͽ�
	CComboBox cmbServer;

	//��ҳ��Ͽ�
	CComboBox cmbPage;

	//��ʾ�б��
	CListCtrl listUser;

	//��������
	CStatic GrpSearch;

	//��ҳ����
	CStatic GrpPage;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	//��ʼ���Ի���
	virtual BOOL OnInitDialog();

	//// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	//�رնԻ���
	afx_msg void OnClose();
	afx_msg void OnBnClickedUicancel();

	//�Զ����ڴ�С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	void UserInfo();//���������Ϣ
	afx_msg void OnBnClickedUisearch();

	//�¼��ܵȼ�
	CComboBox cmbNewLevel;

	//�л�tabCtrl
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);

	//�������������Ϣ�б��
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//˫�����������Ϣ�б��
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//������Ϣ�б��
	CListCtrl listSkill;

	//������Ϣ��ҳ��Ͽ�
	CComboBox cmbSkillPage;

	//���ܵȼ�����ʼ��
	void SetLevel();


	//����������Ϣ�б��
	afx_msg void OnNMClickListskillinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//˫��������Ϣ�б��
	afx_msg void OnNMDblclkListskillinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//������Ϣ��ѯ
	void SkillInfo();

	//�޸ļ��ܵȼ�
	afx_msg void OnBnClickedBtupdate();

	//�����޸ļ��ܵȼ�
	afx_msg void OnBnClickedBtreset();

	//��Ӽ�����Ϣ
	afx_msg void OnBnClickedBtaddskill();

	//������Ӽ�����Ϣ
	afx_msg void OnBnClickedBtresetskill();

	//��ѯ�������
	void SkillType();

	//����������Ͽ�
	CComboBox cmbSkillType;

	//����������Ͽ�
	CComboBox cmbSkillName;

	//�������Ʋ�ѯ
	afx_msg void OnCbnSelchangeCmbskilltype();



};
