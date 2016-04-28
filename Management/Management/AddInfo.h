#pragma once
#include "afxwin.h"

#include <vector>
using namespace std;
// CAddInfo �Ի���

class CAddInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CAddInfo)

public:
	CAddInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADD};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Pname;
	CString m_Price;
	CComboBox m_Floor;
	CComboBox m_PosID;
	CString m_PicID;
	virtual BOOL OnInitDialog();
	void InitCtrls();
	void GetFloor();
	typedef struct
	{
		CString FNO;
		CString LOCAL;
	}Floor;


	vector<Floor> m_vFloor;
	void GetPosByFNO();
	vector<CString> m_vPosID;
	afx_msg void OnCbnSelchangeComboFloor();
	afx_msg void OnBnClickedOk();
};
