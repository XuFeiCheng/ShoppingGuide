// Modify.cpp : 实现文件
//

#include "stdafx.h"
#include "Management.h"
#include "Modify.h"
#include "afxdialogex.h"



// CModify 对话框

IMPLEMENT_DYNAMIC(CModify, CDialogEx)

CModify::CModify(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModify::IDD, pParent)
	, m_Pname(_T(""))
	, m_Price(_T(""))
	, m_Discount(_T(""))
{
	m_Parent = (CMainFrame*)pParent;
}

CModify::~CModify()
{
}

void CModify::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Pname);
	DDX_Control(pDX, IDC_COMBO1, m_Floor);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_Price);
	DDX_Text(pDX, IDC_EDIT_DISCOUNT, m_Discount);
}


BEGIN_MESSAGE_MAP(CModify, CDialogEx)
	ON_BN_CLICKED(IDOK, &CModify::OnBnClickedOk)
END_MESSAGE_MAP()


// CModify 消息处理程序


BOOL CModify::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitCtrls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CModify::InitCtrls()
{
	GetFloor();
	int nRow = m_Parent->m_ListInfo.GetSelectionMark();
	CString nFloor;
	m_Pname = m_Parent->m_ListInfo.GetItemText(nRow, 1);
	//设置楼层
	nFloor = m_Parent->m_ListInfo.GetItemText(nRow, 2);
	m_Floor.SetCurSel(m_Floor.FindString(-1, nFloor));
	m_Price = m_Parent->m_ListInfo.GetItemText(nRow, 3);
	m_Discount = m_Parent->m_ListInfo.GetItemText(nRow, 4);
	UpdateData(FALSE);

	
}


void CModify::GetFloor()
{
	m_vFloor.clear();
	m_Floor.ResetContent();

	CString strSQL = _T("select * from tbFloor");

	CADORecordset rs(&CManagementApp::MarketDB);
	if (rs.Open(strSQL))
	{

		CString FNO;
		CString PS;
		while (!rs.IsEof())
		{
			rs.GetFieldValue(_T("FNO"), FNO);

			rs.GetFieldValue(_T("PS"), PS);
			CString str;
			str.Format(_T("%s楼(%s)"), FNO, PS);
			m_Floor.AddString(str);


			m_vFloor.push_back(FNO);

			rs.MoveNext();
		}
		rs.Close();
	}


}


void CModify::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//修改
	UpdateData(TRUE);
	int nRow = m_Parent->m_ListInfo.GetSelectionMark();
	CString PID = m_Parent->m_ListInfo.GetItemText(nRow, 0);
	CString SQL;
//更新价格表
	SQL.Format(_T("update tbPrice set Pdiscount='%s',Price='%s' where PID = '%s'"), m_Discount, m_Price, PID);
	if (!CManagementApp::MarketDB.Execute(SQL))//执行
	{
	
		AfxMessageBox(L"修改失败！");
		return;
	}
	CString sql;
	//更新所在楼层
	sql.Format(_T("update tbPro set FNO=%s where PID='%s'"), m_vFloor[m_Floor.GetCurSel()], PID);
	if (!CManagementApp::MarketDB.Execute(sql))//执行
	{

		AfxMessageBox(L"修改失败！");
		return;
	}
	CDialogEx::OnOK();
}
