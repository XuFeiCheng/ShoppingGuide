#pragma once
#include "afxwin.h"


// CFeedBack 对话框

class CFeedBack : public CDialogEx
{
	DECLARE_DYNAMIC(CFeedBack)

public:
	CFeedBack(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFeedBack();

// 对话框数据
	enum { IDD = IDD_DIALOG_FEEDBACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:

	CFont m_font;


	CEdit m_Uname;
	CEdit m_Message;




public:
	virtual BOOL OnInitDialog();
private:
	void InitCtrls();
public:
	afx_msg void OnClose();


private:
	CString m_name;
	CString m_msg;
public:
	afx_msg void OnBnClickedOk();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};
