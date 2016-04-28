// FeedBack.cpp : 实现文件
//

#include "stdafx.h"
#include "ShoppingGuide.h"
#include "FeedBack.h"
#include "afxdialogex.h"


// CFeedBack 对话框

IMPLEMENT_DYNAMIC(CFeedBack, CDialogEx)

CFeedBack::CFeedBack(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFeedBack::IDD, pParent)
	, m_name(_T("路人甲"))
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


// CFeedBack 消息处理程序


BOOL CFeedBack::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitCtrls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
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
		_T("微软雅黑")));                 // lpszFacename

	CheckDlgButton(IDC_RADIO_1, BST_CHECKED);
	m_Uname.SetFont(&m_font);
	m_Message.SetFont(&m_font);
	SetWindowText(L"意见反馈");
	UpdateData(FALSE);
}


void CFeedBack::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_font.GetSafeHandle() != NULL)
	{
		m_font.DeleteObject();
	}
	CDialogEx::OnClose();
}


void CFeedBack::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_name.IsEmpty() || m_msg.IsEmpty())
	{
		MessageBox(L"不能为空",L"温馨提示");
		return;
	}
	//获取RadioButton  String
	int nID = GetCheckedRadioButton(IDC_RADIO_1, IDC_RADIO_3);
	CString strCheck;
	GetDlgItemTextW(nID, strCheck);

	CString strSQL;
	strSQL.Format(_T("insert into tbFeedBack(Type, Uname,Message) values('%s','%s','%s')"), strCheck, m_name, m_msg);


	if (!CShoppingGuideApp::staffDB.Execute(strSQL))
	{

		MessageBox(L"出错啦", L"温馨提示");
		return;
	}




	CDialogEx::OnOK();
}


BOOL CFeedBack::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR1);
	SetCursor(hCursor);
	return TRUE;//CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}
