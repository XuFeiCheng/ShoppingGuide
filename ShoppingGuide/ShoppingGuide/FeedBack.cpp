// FeedBack.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShoppingGuide.h"
#include "FeedBack.h"
#include "afxdialogex.h"


// CFeedBack �Ի���

IMPLEMENT_DYNAMIC(CFeedBack, CDialogEx)

CFeedBack::CFeedBack(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFeedBack::IDD, pParent)
	, m_name(_T("·�˼�"))
	, m_msg(_T(""))
{

}

CFeedBack::~CFeedBack()
{
}

void CFeedBack::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_UNAME, m_Uname);
	DDX_Control(pDX, IDC_EDIT_MESSAGE, m_Message);
	DDX_Text(pDX, IDC_EDIT_UNAME, m_name);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, m_msg);
}


BEGIN_MESSAGE_MAP(CFeedBack, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CFeedBack::OnBnClickedOk)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CFeedBack ��Ϣ�������


BOOL CFeedBack::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitCtrls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CFeedBack::InitCtrls()
{
	VERIFY(m_font.CreateFont(
		22,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		DEFAULT_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("΢���ź�")));                 // lpszFacename

	CheckDlgButton(IDC_RADIO_1, BST_CHECKED);
	m_Uname.SetFont(&m_font);
	m_Message.SetFont(&m_font);
	SetWindowText(L"�������");
	UpdateData(FALSE);
}


void CFeedBack::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_font.GetSafeHandle() != NULL)
	{
		m_font.DeleteObject();
	}
	CDialogEx::OnClose();
}


void CFeedBack::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_name.IsEmpty() || m_msg.IsEmpty())
	{
		MessageBox(L"����Ϊ��",L"��ܰ��ʾ");
		return;
	}
	//��ȡRadioButton  String
	int nID = GetCheckedRadioButton(IDC_RADIO_1, IDC_RADIO_3);
	CString strCheck;
	GetDlgItemTextW(nID, strCheck);

	CString strSQL;
	strSQL.Format(_T("insert into tbFeedBack(Type, Uname,Message) values('%s','%s','%s')"), strCheck, m_name, m_msg);


	if (!CShoppingGuideApp::staffDB.Execute(strSQL))
	{

		MessageBox(L"������", L"��ܰ��ʾ");
		return;
	}




	CDialogEx::OnOK();
}


BOOL CFeedBack::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR1);
	SetCursor(hCursor);
	return TRUE;//CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}
