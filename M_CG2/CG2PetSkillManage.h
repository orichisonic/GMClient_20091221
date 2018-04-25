#pragma once

#include "OperationCG2.h"
#include "afxcmn.h"
#include "afxwin.h"

// CCG2PetSkillManage �Ի���

class CCG2PetSkillManage : public CDialog
{
	DECLARE_DYNAMIC(CCG2PetSkillManage)

public:
	CCG2PetSkillManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCG2PetSkillManage();

// �Ի�������
	enum { IDD = IDD_DLGPETSKILLMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;
	
	// �����û��б��õ��к�
	int nItem;

	// �ж��û��б��Ƿ���Ҫ��ҳ
	bool pageUInfo;

	// ���������б��õ��к�
	int nPetItem;

	int nResultItem;
	// �ж��û��б��Ƿ���Ҫ��ҳ
	bool pagePetInfo;


	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// ��Ϸ������IP
	CString ServerIP;

	// ���ID
	CString UserID;

	// ���������ʺ�
	CString UserName;

	// ���������ǳ�
	CString UserNick;

	//����λ��
	int PetID;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	// CComboBox��ҽ�ɫ��Ϣ��ҳ��ѯ
	CComboBox cmbUPage;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPetPage;

	// CListCtrl���������Ϣ
	CListCtrl listUser;

	// CListCtrl������Ϣ
	CListCtrl listPet;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// CGroupBox��������
	CStatic GrpSearch;

	// CGroupBox��ҳ����
	CStatic GrpPage;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// ��ѯ���������Ϣ
	afx_msg void OnBnClickedUisearch();

	// ��ҳ��ѯ���������Ϣ
	afx_msg void OnCbnSelchangeCmbuserpage();

	// �������������Ϣ���浱ǰ�к�
	afx_msg void OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�����������Ϣ���в�ѯ
	afx_msg void OnNMDblclkListUser(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ���������б����浱ǰ�к�
	void OnNMClickListPet(NMHDR *pNMHDR, LRESULT *pResult);

	void OnNMClickListResult(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫��������Ϣ���в�ѯ
	void OnNMDblclkListPet(NMHDR *pNMHDR, LRESULT *pResult);

	void OnNMDblclkListResult(NMHDR *pNMHDR, LRESULT *pResult);

	// ��ѯ���������Ϣ
	void UserInfo();

	// �����������
	void PetInfo();

	// ���＼����Ϣ
	void PetSkill();

	

	

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbuipage();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���
	afx_msg void OnBnClickedUicancel();

	// �رնԻ���
	afx_msg void OnClose();			



	void ShowAddPetSkill(int n_cmdShow);

	void ShowUpdatePetSkill(int n_cmdShow);
	CComboBox cmbSkillType;
	CComboBox cmbSkillName;

	//��ѯ�������
	void SkillType();

	//������Ϣ��ѯ
	void SkillInfo();

	// ���ӳ��＼��
	void AddPetSkill();

	// ���ӳ��＼��
	void UpdatePetSkill();

	afx_msg void OnCbnSelchangeCmbskilltype();
	afx_msg void OnBnClickedBtnconfirm();
	CEdit m_SkillName;
	CEdit m_NowLevel;
};