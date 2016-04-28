// MainFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Management.h"
#include "MainFrame.h"
#include "afxdialogex.h"
#include "AddInfo.h"
#include "Modify.h"


// CMainFrame �Ի���

IMPLEMENT_DYNAMIC(CMainFrame, CDialogEx)

CMainFrame::CMainFrame(CWnd* pParent)
	: CDialogEx(CMainFrame::IDD, pParent)
	, m_pParent(NULL)
{
	m_pParent = (CManagementDlg*)pParent;
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INFO, m_ListInfo);
	DDX_Control(pDX, IDC_COMBO_FLOOR, m_Floor);
	DDX_Control(pDX, IDC_COMBO_DISCOUNT, m_Discount);
}


BEGIN_MESSAGE_MAP(CMainFrame, CDialogEx)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_FLOOR, &CMainFrame::OnCbnSelchangeComboFloor)
	ON_CBN_SELCHANGE(IDC_COMBO_DISCOUNT, &CMainFrame::OnCbnSelchangeComboDiscount)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMainFrame::OnBnClickedButtonDelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST_INFO, &CMainFrame::OnNMClickListInfo)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMainFrame::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MODIFTY, &CMainFrame::OnBnClickedButtonModifty)
END_MESSAGE_MAP()


// CMainFrame ��Ϣ�������


// ��ʼ�����пؼ�
void CMainFrame::InitCtrls()
{
	//��½��������
	m_pParent->ShowWindow(FALSE);
	
	SetWindowText(_T("XX�̳���̨����ϵͳ"));
	m_ListInfo.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListInfo.InsertColumn(0, _T("��Ʒ���"), LVCFMT_LEFT, 60);
	m_ListInfo.InsertColumn(1, _T("��Ʒ��"), LVCFMT_LEFT, 120);
	m_ListInfo.InsertColumn(2, _T("����¥��"), LVCFMT_LEFT, 90);
	m_ListInfo.InsertColumn(3, _T("ԭ��"), LVCFMT_LEFT, 90);
	m_ListInfo.InsertColumn(4, _T("�ۿ���"), LVCFMT_LEFT, 90);
	m_ListInfo.InsertColumn(5, _T("λ�ñ��"), LVCFMT_LEFT, 100);

	//��ʼ����ƷLOGO��
	CRect rc;
	GetClientRect(rc);
	rc.left = 646;
	rc.top = 126;
	rc.bottom = rc.top + 300;
	rc.right = rc.left + 300;

	m_Logo.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_WND_LOGO);


	//��ʼ�����пؼ�����Ʒ��Ϣ
	InitAllInfo();
}


// ����
void CMainFrame::DestoryCtrls()
{
	//�ر�������

	m_pParent->OnClose();
	
}


BOOL CMainFrame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitCtrls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CMainFrame::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DestoryCtrls();
	CDialogEx::OnClose();
}


// ��ʼ��������Ʒ��Ϣ
void CMainFrame::InitAllInfo()
{
	// ��ȡ¥��
	GetFloor();
	//��ȡ�ۿ���
	GetDiscountByFNO();
	//����FNO/DISCOUNT��ȡ��Ʒ��Ϣ
	GetInfoByFNO_Discount();
}


// ��ȡ¥��
void CMainFrame::GetFloor()
{
	m_vFloor.clear();
	m_Floor.ResetContent();
	m_Floor.AddString(_T("����¥��"));
	m_vFloor.push_back(_T("-1"));
	CString strSQL = _T("select * from tbFloor");

	CADORecordset rs(&CManagementApp::MarketDB);
	if (rs.Open(strSQL))
	{

		CString FNO;
		CString PS;
		while (!rs.IsEof())//�Ƿ���ĩβ
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
	m_Floor.SetCurSel(0);
}


// ��ȡ�ۿ���
void CMainFrame::GetDiscountByFNO()
{
	m_vDiscount.clear();
	m_Discount.ResetContent();
	m_Discount.AddString(_T("��ѡ��"));
	m_vDiscount.push_back(_T("-1"));
	CString Sql;
	if (m_Floor.GetCurSel() == 0)
	{
		Sql = _T("select Pdiscount from tbPrice group by Pdiscount order by Pdiscount ASC");
	}
	else
	{
		Sql.Format(_T("select Pdiscount from tbPrice where PID IN (select PID from tbPro where FNO = %s) group by Pdiscount order by Pdiscount ASC"), m_vFloor[m_Floor.GetCurSel()]);
	}

	CADORecordset rs(&CManagementApp::MarketDB);
	if (rs.Open(Sql))
	{
		CString strDiscount;
	
		m_Discount.AddString(L"ԭ��");
		m_vDiscount.push_back(L"0");
		rs.MoveNext();
		while (!rs.IsEof())
		{
			rs.GetFieldValue(_T("Pdiscount"), strDiscount);
			m_vDiscount.push_back(strDiscount);
			if (strDiscount.Compare(_T("0")) == 0)
			{
				m_Discount.AddString(_T("δ����"));
			}
			else
			{
				CString str;
				str.Format(_T("%s��"), strDiscount);
				m_Discount.AddString(str);
			}
			rs.MoveNext();
		}
		rs.Close();
	}
	m_Discount.SetCurSel(0);
}


// ��ȡ��Ʒ��Ϣ
void CMainFrame::GetInfoByFNO_Discount()
{
	//ɾ������������Ϣ
	m_ListInfo.DeleteAllItems();
	m_vProPicID.clear();
	CString Sql;
	if (m_Floor.GetCurSel() == 0 && m_Discount.GetCurSel() == 0)
	{
		Sql = _T("select tbPro.PID,tbPro.Pname,tbPro.FNO,tbPrice.Price,tbPrice.Pdiscount,tbPro.PosID,tbPro.PicID from tbPro,tbPrice where tbPro.PID=tbPrice.PID order by PID ASC");
	}
	else if (m_Floor.GetCurSel() != 0 && m_Discount.GetCurSel() == 0)
	{
		Sql.Format(_T("select tbPro.PID, tbPro.Pname, tbPro.FNO, tbPrice.Price, tbPrice.Pdiscount,tbPro.PosID,tbPro.PicID from tbPro, tbPrice where tbPro.PID = tbPrice.PID AND tbPro.FNO=%s order by PID ASC"), m_vFloor[m_Floor.GetCurSel()]);
	}
	else if (m_Floor.GetCurSel() == 0 && m_Discount.GetCurSel() != 0)
	{
		Sql.Format(_T("select tbPro.PID, tbPro.Pname, tbPro.FNO, tbPrice.Price, tbPrice.Pdiscount,tbPro.PosID,tbPro.PicID from tbPro, tbPrice where tbPro.PID = tbPrice.PID AND tbPrice.Pdiscount='%s' order by PID ASC"), m_vDiscount[m_Discount.GetCurSel()]);
	}
	else
	{
		Sql.Format(_T("select tbPro.PID, tbPro.Pname, tbPro.FNO, tbPrice.Price, tbPrice.Pdiscount,tbPro.PosID,tbPro.PicID from tbPro, tbPrice where tbPro.PID = tbPrice.PID AND tbPro.FNO=%s AND tbPrice.Pdiscount='%s' order by PID ASC"), m_vFloor[m_Floor.GetCurSel()], m_vDiscount[m_Discount.GetCurSel()]);
	}


	CADORecordset  Rs(&CManagementApp::MarketDB);

	//�򿪼�¼��
	if (Rs.Open(Sql))
	{

		CString strField;
		int nRow = 0;

		while (!Rs.IsEof())
		{
			Rs.GetFieldValue(_T("PID"), strField);

			m_ListInfo.InsertItem(nRow, strField);

			Rs.GetFieldValue(_T("Pname"), strField);
			m_ListInfo.SetItemText(nRow, 1, strField);

			Rs.GetFieldValue(_T("FNO"), strField);
			m_ListInfo.SetItemText(nRow, 2, strField);

			Rs.GetFieldValue(_T("Price"), strField);
			m_ListInfo.SetItemText(nRow, 3, strField);

			Rs.GetFieldValue(_T("Pdiscount"), strField);

			if (strField.Compare(_T("0")) == 0)
			{
				strField = L"���ۿ�";
			}
			m_ListInfo.SetItemText(nRow, 4, strField);


			Rs.GetFieldValue(_T("PosID"), strField);
			m_ListInfo.SetItemText(nRow, 5, strField);

			Rs.GetFieldValue(_T("PicID"), strField);
			int nPic = _ttoi(strField);
			m_vProPicID.push_back(nPic);

			//�ƶ���¼ָ��
			Rs.MoveNext();
			nRow++;
		}

		//�رռ�¼��
		Rs.Close();
	}
	m_Logo.DrawWnd(m_vProPicID[0]);

}


void CMainFrame::OnCbnSelchangeComboFloor()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDiscountByFNO();
	GetInfoByFNO_Discount();
}


void CMainFrame::OnCbnSelchangeComboDiscount()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetInfoByFNO_Discount();
}


void CMainFrame::OnBnClickedButtonDelete()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int uSelectedCount = m_ListInfo.GetSelectedCount();

	if (uSelectedCount == 0)
	{
		AfxMessageBox(_T("��ѡ��Ҫɾ������!"));
		return;
	}

	int  nItem = -1;

	CString strSql;

	for (int i = 0; i < uSelectedCount; i++)
	{
		nItem = m_ListInfo.GetNextItem(nItem, LVNI_SELECTED);

		//��ȡPID
		CString strId = m_ListInfo.GetItemText(nItem, 0);

		//Sql
		strSql.Format(_T("delete from tbPrice where PID= '%s'"), strId);
	
		//ִ��Sql
		if (!CManagementApp::MarketDB.Execute(strSql))//ִ��
		{
			CString str;
			str.Format(_T("ɾ��%sʧ��"), strId);
			AfxMessageBox(str);
			return;
		}
		strSql.Format(_T("delete from tbPro where PID = '%s'"), strId);
		if (!CManagementApp::MarketDB.Execute(strSql))//ִ��
		{
			CString str;
			str.Format(_T("ɾ��%sʧ��"), strId);
			AfxMessageBox(str);
			return;
		}

	}

	//���»�ȡ����
	GetInfoByFNO_Discount();
}


void CMainFrame::OnNMClickListInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nItem = -1;

	//��õ�����к�
	if (pNMItemActivate != NULL)
	{
		nItem = pNMItemActivate->iItem;
	}

	m_Logo.DrawWnd(m_vProPicID[nItem]);


	*pResult = 0;
}


void CMainFrame::OnBnClickedButtonAdd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CAddInfo dlg;
	if (IDOK == dlg.DoModal())
	{
		GetInfoByFNO_Discount();
	}
	
}


void CMainFrame::OnBnClickedButtonModifty()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int uSelectedCount = m_ListInfo.GetSelectedCount();

	if (uSelectedCount == 0)
	{
		AfxMessageBox(_T("��ѡ��!"));
		return;
	}
	CModify dlg(this);
	if (dlg.DoModal() == IDOK)
	{
		GetInfoByFNO_Discount();
	}



}
