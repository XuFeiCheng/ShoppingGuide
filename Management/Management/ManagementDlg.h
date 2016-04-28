
// ManagementDlg.h : ͷ�ļ�
//

#pragma once
#include "MainFrame.h"

// CManagementDlg �Ի���
class CManagementDlg : public CDialogEx
{
// ����
public:
	CManagementDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MANAGEMENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_Uname;
	CString m_Upwd;
	afx_msg void OnBnClickedButtonLogin();
private:
	BOOL LinkDB();
public:
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	void InitCtrls();
};
