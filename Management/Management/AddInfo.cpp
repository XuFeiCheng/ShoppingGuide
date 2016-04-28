// AddInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Management.h"
#include "AddInfo.h"
#include "afxdialogex.h"


// CAddInfo �Ի���

IMPLEMENT_DYNAMIC(CAddInfo, CDialogEx)

CAddInfo::CAddInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddInfo::IDD, pParent)
	, m_Pname(_T(""))
	, m_Price(_T(""))
	, m_PicID(_T(""))
{

}

CAddInfo::~CAddInfo()
{
}

void CAddInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PNAME, m_Pname);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_Price);
	DDX_Control(pDX, IDC_COMBO_FLOOR, m_Floor);
	DDX_Control(pDX, IDC_COMBO_POSID, m_PosID);
	DDX_Text(pDX, IDC_EDIT_PICID, m_PicID);
}


BEGIN_MESSAGE_MAP(CAddInfo, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_FLOOR, &CAddInfo::OnCbnSelchangeComboFloor)
	ON_BN_CLICKED(IDOK, &CAddInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddInfo ��Ϣ�������


BOOL CAddInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitCtrls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CAddInfo::InitCtrls()
{
	m_Price = _T("50");
	m_PicID = _T("9999");
	UpdateData(FALSE);
	GetFloor();
	GetPosByFNO();
}


void CAddInfo::GetFloor()
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


			rs.GetFieldValue(_T("Location"), PS);

			Floor t;
			t.FNO = FNO;
			t.LOCAL = PS;
			m_vFloor.push_back(t);

			rs.MoveNext();
		}
		rs.Close();
	}
	m_Floor.SetCurSel(0);
}


void CAddInfo::GetPosByFNO()
{
	m_vPosID.clear();
	m_PosID.ResetContent();

	CString strSQL; 
	strSQL.Format(_T("select LID from %s where LID NOT IN (select PosID from tbPro where FNO=%s)"), m_vFloor[m_Floor.GetCurSel()].LOCAL, m_vFloor[m_Floor.GetCurSel()].FNO);

	CADORecordset rs(&CManagementApp::MarketDB);
	if (rs.Open(strSQL))
	{

		CString PosID;

		while (!rs.IsEof())
		{
			rs.GetFieldValue(_T("LID"), PosID);

	
		
			m_PosID.AddString(PosID);

			m_vPosID.push_back(PosID);

			rs.MoveNext();
		}
		rs.Close();
	}
	m_PosID.SetCurSel(0);
}

//��¥��ı�ִ�еĲ���
void CAddInfo::OnCbnSelchangeComboFloor()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetPosByFNO();
}


void CAddInfo::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString str;
	m_PosID.GetWindowTextW(str);
	if (m_Pname.IsEmpty() || m_Price.IsEmpty() || m_PicID.IsEmpty() || str.IsEmpty())
	{
		AfxMessageBox(_T("������ȷ��Ϣ��"));
		return;
	}
	CString Sql;

	//��ȡ����id
	Sql.Format(L"select PID from tbPro");
	CADORecordset rs(&CManagementApp::MarketDB);
	rs.Open(Sql);
	int PID = rs.GetRecordCount() + 1;
	rs.Close();

	//������Ʒ��Ϣ-----------------------------------------------------------------------------------
	CString strSql;
	
	strSql.Format(_T("insert into tbPro(PID,Pname,FNO,PicID,PosID) values(%d, '%s', %s, '%s',%s)"), PID, m_Pname, m_vFloor[m_Floor.GetCurSel()].FNO, m_PicID, str);

	if (!CManagementApp::MarketDB.Execute(strSql))//ִ��
	{

		AfxMessageBox(L"���ʧ�ܣ�");
		return;
	}
	CString strSql1;
	strSql1.Format(_T("insert into tbPrice(PID, Price) values('%d','%s')"), PID, m_Price);
	if (!CManagementApp::MarketDB.Execute(strSql1))//ִ��
	{

		AfxMessageBox(L"���ʧ�ܣ�");
		return;
	}

	CDialogEx::OnOK();
}
