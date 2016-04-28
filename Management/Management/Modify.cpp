// Modify.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Management.h"
#include "Modify.h"
#include "afxdialogex.h"



// CModify �Ի���

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


// CModify ��Ϣ�������


BOOL CModify::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitCtrls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CModify::InitCtrls()
{
	GetFloor();
	int nRow = m_Parent->m_ListInfo.GetSelectionMark();
	CString nFloor;
	m_Pname = m_Parent->m_ListInfo.GetItemText(nRow, 1);
	//����¥��
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
			str.Format(_T("%s¥(%s)"), FNO, PS);
			m_Floor.AddString(str);


			m_vFloor.push_back(FNO);

			rs.MoveNext();
		}
		rs.Close();
	}


}


void CModify::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�޸�
	UpdateData(TRUE);
	int nRow = m_Parent->m_ListInfo.GetSelectionMark();
	CString PID = m_Parent->m_ListInfo.GetItemText(nRow, 0);
	CString SQL;
//���¼۸��
	SQL.Format(_T("update tbPrice set Pdiscount='%s',Price='%s' where PID = '%s'"), m_Discount, m_Price, PID);
	if (!CManagementApp::MarketDB.Execute(SQL))//ִ��
	{
	
		AfxMessageBox(L"�޸�ʧ�ܣ�");
		return;
	}
	CString sql;
	//��������¥��
	sql.Format(_T("update tbPro set FNO=%s where PID='%s'"), m_vFloor[m_Floor.GetCurSel()], PID);
	if (!CManagementApp::MarketDB.Execute(sql))//ִ��
	{

		AfxMessageBox(L"�޸�ʧ�ܣ�");
		return;
	}
	CDialogEx::OnOK();
}
