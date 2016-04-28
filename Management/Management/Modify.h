#pragma once
#include "afxwin.h"
#include "MainFrame.h"
#include <vector>

// CModify �Ի���
using namespace std;
class CModify : public CDialogEx
{
	DECLARE_DYNAMIC(CModify)

public:
	CModify(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModify();

// �Ի�������
	enum { IDD = IDD_DIALOG_MODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CMainFrame* m_Parent;


	virtual BOOL OnInitDialog();
	void InitCtrls();
	void GetFloor();
	CString m_Pname;
	CComboBox m_Floor;
	vector<CString> m_vFloor;


	CString m_Price;
	CString m_Discount;
	afx_msg void OnBnClickedOk();
};
