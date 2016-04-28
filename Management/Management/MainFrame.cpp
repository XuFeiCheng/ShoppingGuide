// MainFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "Management.h"
#include "MainFrame.h"
#include "afxdialogex.h"
#include "AddInfo.h"
#include "Modify.h"


// CMainFrame 对话框

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


// CMainFrame 消息处理程序


// 初始化所有控件
void CMainFrame::InitCtrls()
{
	//登陆窗口隐身
	m_pParent->ShowWindow(FALSE);
	
	SetWindowText(_T("XX商场后台管理系统"));
	m_ListInfo.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListInfo.InsertColumn(0, _T("商品编号"), LVCFMT_LEFT, 60);
	m_ListInfo.InsertColumn(1, _T("商品名"), LVCFMT_LEFT, 120);
	m_ListInfo.InsertColumn(2, _T("所在楼层"), LVCFMT_LEFT, 90);
	m_ListInfo.InsertColumn(3, _T("原价"), LVCFMT_LEFT, 90);
	m_ListInfo.InsertColumn(4, _T("折扣率"), LVCFMT_LEFT, 90);
	m_ListInfo.InsertColumn(5, _T("位置编号"), LVCFMT_LEFT, 100);

	//初始化商品LOGO区
	CRect rc;
	GetClientRect(rc);
	rc.left = 646;
	rc.top = 126;
	rc.bottom = rc.top + 300;
	rc.right = rc.left + 300;

	m_Logo.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_WND_LOGO);


	//初始化所有控件及商品信息
	InitAllInfo();
}


// 销毁
void CMainFrame::DestoryCtrls()
{
	//关闭主窗口

	m_pParent->OnClose();
	
}


BOOL CMainFrame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitCtrls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CMainFrame::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	DestoryCtrls();
	CDialogEx::OnClose();
}


// 初始化所有商品信息
void CMainFrame::InitAllInfo()
{
	// 获取楼层
	GetFloor();
	//获取折扣率
	GetDiscountByFNO();
	//根据FNO/DISCOUNT获取商品信息
	GetInfoByFNO_Discount();
}


// 获取楼层
void CMainFrame::GetFloor()
{
	m_vFloor.clear();
	m_Floor.ResetContent();
	m_Floor.AddString(_T("所有楼层"));
	m_vFloor.push_back(_T("-1"));
	CString strSQL = _T("select * from tbFloor");

	CADORecordset rs(&CManagementApp::MarketDB);
	if (rs.Open(strSQL))
	{

		CString FNO;
		CString PS;
		while (!rs.IsEof())//是否在末尾
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
	m_Floor.SetCurSel(0);
}


// 获取折扣率
void CMainFrame::GetDiscountByFNO()
{
	m_vDiscount.clear();
	m_Discount.ResetContent();
	m_Discount.AddString(_T("不选择"));
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
	
		m_Discount.AddString(L"原价");
		m_vDiscount.push_back(L"0");
		rs.MoveNext();
		while (!rs.IsEof())
		{
			rs.GetFieldValue(_T("Pdiscount"), strDiscount);
			m_vDiscount.push_back(strDiscount);
			if (strDiscount.Compare(_T("0")) == 0)
			{
				m_Discount.AddString(_T("未打折"));
			}
			else
			{
				CString str;
				str.Format(_T("%s折"), strDiscount);
				m_Discount.AddString(str);
			}
			rs.MoveNext();
		}
		rs.Close();
	}
	m_Discount.SetCurSel(0);
}


// 获取商品信息
void CMainFrame::GetInfoByFNO_Discount()
{
	//删除所有已有信息
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

	//打开记录集
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
				strField = L"无折扣";
			}
			m_ListInfo.SetItemText(nRow, 4, strField);


			Rs.GetFieldValue(_T("PosID"), strField);
			m_ListInfo.SetItemText(nRow, 5, strField);

			Rs.GetFieldValue(_T("PicID"), strField);
			int nPic = _ttoi(strField);
			m_vProPicID.push_back(nPic);

			//移动记录指针
			Rs.MoveNext();
			nRow++;
		}

		//关闭记录集
		Rs.Close();
	}
	m_Logo.DrawWnd(m_vProPicID[0]);

}


void CMainFrame::OnCbnSelchangeComboFloor()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDiscountByFNO();
	GetInfoByFNO_Discount();
}


void CMainFrame::OnCbnSelchangeComboDiscount()
{
	// TODO:  在此添加控件通知处理程序代码
	GetInfoByFNO_Discount();
}


void CMainFrame::OnBnClickedButtonDelete()
{
	// TODO:  在此添加控件通知处理程序代码
	int uSelectedCount = m_ListInfo.GetSelectedCount();

	if (uSelectedCount == 0)
	{
		AfxMessageBox(_T("请选择要删除的行!"));
		return;
	}

	int  nItem = -1;

	CString strSql;

	for (int i = 0; i < uSelectedCount; i++)
	{
		nItem = m_ListInfo.GetNextItem(nItem, LVNI_SELECTED);

		//获取PID
		CString strId = m_ListInfo.GetItemText(nItem, 0);

		//Sql
		strSql.Format(_T("delete from tbPrice where PID= '%s'"), strId);
	
		//执行Sql
		if (!CManagementApp::MarketDB.Execute(strSql))//执行
		{
			CString str;
			str.Format(_T("删除%s失败"), strId);
			AfxMessageBox(str);
			return;
		}
		strSql.Format(_T("delete from tbPro where PID = '%s'"), strId);
		if (!CManagementApp::MarketDB.Execute(strSql))//执行
		{
			CString str;
			str.Format(_T("删除%s失败"), strId);
			AfxMessageBox(str);
			return;
		}

	}

	//重新获取数据
	GetInfoByFNO_Discount();
}


void CMainFrame::OnNMClickListInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	int nItem = -1;

	//获得点击的行号
	if (pNMItemActivate != NULL)
	{
		nItem = pNMItemActivate->iItem;
	}

	m_Logo.DrawWnd(m_vProPicID[nItem]);


	*pResult = 0;
}


void CMainFrame::OnBnClickedButtonAdd()
{
	// TODO:  在此添加控件通知处理程序代码
	CAddInfo dlg;
	if (IDOK == dlg.DoModal())
	{
		GetInfoByFNO_Discount();
	}
	
}


void CMainFrame::OnBnClickedButtonModifty()
{
	// TODO:  在此添加控件通知处理程序代码
	int uSelectedCount = m_ListInfo.GetSelectedCount();

	if (uSelectedCount == 0)
	{
		AfxMessageBox(_T("请选择!"));
		return;
	}
	CModify dlg(this);
	if (dlg.DoModal() == IDOK)
	{
		GetInfoByFNO_Discount();
	}



}
