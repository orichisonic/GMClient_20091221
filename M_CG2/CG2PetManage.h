#pragma once

#include "OperationCG2.h"
#include "afxcmn.h"
#include "afxwin.h"

// CCG2PetManage �Ի���

class CCG2PetManage : public CDialog
{
	DECLARE_DYNAMIC(CCG2PetManage)

public:
	CCG2PetManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCG2PetManage();

// �Ի�������
	enum { IDD = IDD_DLGPETMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// ���г����б�
	CMap<int,int,CString,CString> PetList;
	
	// �����û��б�õ��к�
	int nItem;

	// �ж��û��б��Ƿ���Ҫ��ҳ
	bool pageUInfo;

	// ���������б�õ��к�
	int nPetItem;

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

	//��������
	CString PetName;

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

	// ���������б��浱ǰ�к�
	void OnNMClickListPet(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫��������Ϣ���в�ѯ
	void OnNMDblclkListPet(NMHDR *pNMHDR, LRESULT *pResult);

	// ��ѯ���������Ϣ
	void UserInfo();

	// �����������
	void PetInfo();

	// ���＼����Ϣ
	void PetSkill();

	//���³�������
	void UpdatePet();

	//��ӳ���
	void AddPet();
	
	//���³���ȼ�
	void UpdatePetLevel();

	//�����б�
	void PetListQuery();

	

	

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbuipage();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���
	afx_msg void OnBnClickedUicancel();

	// �رնԻ���
	afx_msg void OnClose();			



	afx_msg void OnBnClickedBtnconfirm();
	void ShowUpdatePet(int n_cmdShow);
	void ShowAddPet(int n_cmdShow);
	void ShowUpdatePetLevel(int n_cmdShow);
	CEdit editUserName;
	CComboBox cmbPet;
	CEdit m_NowLevel;
	afx_msg void OnBnClickedBtnreset();
};
