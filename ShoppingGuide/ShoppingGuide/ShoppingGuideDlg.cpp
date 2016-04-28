
// ShoppingGuideDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShoppingGuide.h"
#include "ShoppingGuideDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CShoppingGuideDlg �Ի���



CShoppingGuideDlg::CShoppingGuideDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShoppingGuideDlg::IDD, pParent)
	, m_Pname(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


}

void CShoppingGuideDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_Search);

	DDX_Control(pDX, IDC_COMBO_FLOOR, m_Floor);
	DDX_Control(pDX, IDC_COMBO_ENTER, m_Enter);
	DDX_Control(pDX, IDC_COMBO_GOODS, m_Pros);
	DDX_Control(pDX, IDC_COMBO_ENTER2, m_Discount);
	DDX_Text(pDX, IDC_EDIT1, m_Pname);
}

BEGIN_MESSAGE_MAP(CShoppingGuideDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CShoppingGuideDlg::OnBnClickedButtonSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_FLOOR, &CShoppingGuideDlg::OnCbnSelchangeComboFloor)
	ON_CBN_SELCHANGE(IDC_COMBO_GOODS, &CShoppingGuideDlg::OnCbnSelchangeComboGoods)
	ON_BN_CLICKED(IDC_BUTTON_FEEDBACK, &CShoppingGuideDlg::OnBnClickedButtonFeedback)
	ON_WM_SETCURSOR()
	ON_CBN_SELCHANGE(IDC_COMBO_DISCOUNT, &CShoppingGuideDlg::OnCbnSelchangeComboDiscount)
END_MESSAGE_MAP()


// CShoppingGuideDlg ��Ϣ�������

BOOL CShoppingGuideDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	InitShopData();



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CShoppingGuideDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CShoppingGuideDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CShoppingGuideDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// ��ʼ���̳�������Ϣ
void CShoppingGuideDlg::InitShopData()
{
	CRect rc;
	GetClientRect(rc);
	rc.left = 322;        
	rc.top = 18;
	rc.bottom = rc.top + 600;
	rc.right = rc.left + 860;

	m_Map.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_WND_MAP);
	
	GetClientRect(rc);


	rc.top = 285;
	rc.bottom = rc.top+290;	
	rc.left = 5;
	rc.right = rc.left+290;

	m_Pic.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_WND_PROLOG);

	//shopLOG
	GetClientRect(rc);

//	rc.left = (rc.Width() - 1024) / 2;
	rc.top = rc.bottom-40;
	rc.right = 1024;
//	rc.bottom = rc.top + 40;
	m_ShopLog.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_WND_SHOPLOG);
	m_ShopLog.SetMoveText(CString(_T("~��ӭ����XX�̳�~")), 30,RGB(133,202,125));


	//BottomTime
	GetClientRect(rc);
	rc.top = rc.bottom - 40;
	rc.left = 1024;
	m_BottomTime.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_WND_BOTTOMTIME);
	m_BottomTime.SetBottomTime();

	if (!LinkDB())
	{
		AfxMessageBox(_T("�������ݿ�ʧ�ܣ�"));
		exit(0);
	}
	//��ȡ¥��
	GetAllFloor();


	//�ۿ�
	InitDiscount();
	//��ȡ��Ʒ���۸�
	GetProByFNO(m_vFloor[m_Floor.GetCurSel()].nID, m_vDiscount[m_Discount.GetCurSel()]);
	//�������
	SetFloorEnter(m_vFloor[m_Floor.GetCurSel()].nID);
	//LOGO
	m_Pic.DrawWnd(m_vPros[m_Pros.GetCurSel()].nPic);
	//����ͼ
	m_Map.DrawWnd(m_vFloor[m_Floor.GetCurSel()].nPic);


	SetTimer(1, 1000, NULL);
}


// ���ٿؼ�
void CShoppingGuideDlg::DestoryCtrls()
{
	if (m_Map.GetSafeHwnd() != NULL)
	{
		m_Map.DestroyWindow();
	}

	if (CShoppingGuideApp::staffDB.IsOpen())
	{
		CShoppingGuideApp::staffDB.Close();
	}
	if (m_ShopLog.GetSafeHwnd() != NULL)
	{
		m_ShopLog.DestroyWindow();
	}
	if (m_Pic.GetSafeHwnd() != NULL)
	{
		m_Pic.DestroyWindow();
	}
	if (m_BottomTime.GetSafeHwnd() != NULL)
	{
		m_BottomTime.DestroyWindow();
	}
	m_Road.Clear();
}


void CShoppingGuideDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
	DestoryCtrls();
}


void CShoppingGuideDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ



	CTime tm = CTime::GetCurrentTime();
	CString strTime = tm.Format(_T("%Y/%m/%d %H:%M:%S"));

	CString strTitle;
	strTitle.Format(_T("XX�̳�����ϵͳ   %s"),strTime);
	SetWindowText(strTitle);

	CDialogEx::OnTimer(nIDEvent);
}

//�����ѯ��ť�¼�
void CShoppingGuideDlg::OnBnClickedButtonSearch()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);



	int nPro = m_vPros[m_Pros.GetCurSel()].nID;
	int nPic = m_vPros[m_Pros.GetCurSel()].nPic;
	if (!m_Pname.IsEmpty())
	{
		
		nPro = FindProbyName(nPic);
		if (nPro == -1)
		{
			AfxMessageBox(L"��¥��û�и���Ʒ���뻻��¥�����ԡ�");
			return;
		}
		
	}
	m_Pic.DrawWnd(nPic);
	//��ʼ��ͼ
	InitRoad();


	m_Road.find_the_path(m_vEnter[m_Enter.GetCurSel()], nPro);//Ѱ·

	m_Road.m_road.push_back(nPro);//������Ʒλ��

	CPoint start;
	start.x = m_vLocation[m_vEnter[m_Enter.GetCurSel()]].x;
	start.y = m_vLocation[m_vEnter[m_Enter.GetCurSel()]].y;

	
	vector<CPoint > locat;
	locat.push_back(start);
	for (UINT i = 0; i < m_Road.m_road.size(); i++)
	{
		locat.push_back(CPoint(m_vLocation[m_Road.m_road[i]].x, m_vLocation[m_Road.m_road[i]].y));
	}

	m_Map.DrawLine(locat);

	m_Pname = L"";
	UpdateData(FALSE);

}


// �������ݿ�
BOOL CShoppingGuideDlg::LinkDB()
{
	CString SVname;
	CString DBname;
	CString Account;
	CString PassWord;
	//��ȡ�����ļ�
	//����������
	GetPrivateProfileString(_T("DataBaseConfig"), _T("ServerName "), _T("��ȡ����"), SVname.GetBuffer(20), 20, _T(".\\DB.ini"));
	SVname.ReleaseBuffer();
	//��½�˺�
	GetPrivateProfileString(_T("DataBaseConfig"), _T("Account"), _T("��ȡ����"), Account.GetBuffer(20), 20, _T(".\\DB.ini"));
	Account.ReleaseBuffer();
	//��½����
	GetPrivateProfileString(_T("DataBaseConfig"), _T("PassWord"), _T("��ȡ����"), PassWord.GetBuffer(20), 20, _T(".\\DB.ini"));
	PassWord.ReleaseBuffer();
	//�������ݿ������
	GetPrivateProfileString(_T("PrivateConfig"), _T("DataBaseName "), _T("��ȡ����"), DBname.GetBuffer(20), 20, _T(".\\DB.ini"));
	DBname.ReleaseBuffer();


	if (SVname.Compare(_T("��ȡ����")) == 0 || DBname.Compare(_T("��ȡ����")) == 0 || Account.Compare(_T("��ȡ����")) == 0 || PassWord.Compare(_T("��ȡ����")) == 0)
	{
		MessageBox(_T("Ӧ�ó��������ļ���ȡ����"), _T("ϵͳ��ʾ"), MB_ICONSTOP);
		exit(0);
	}





	CString strConnect;
	strConnect.Format(_T("Provider=sqloledb;Data Source=%s;Initial Catalog=%s;User Id=%s;Password=%s;"), SVname,DBname, Account, PassWord);
	return CShoppingGuideApp::staffDB.Open(strConnect);
}


// ��ȡ¥�㲢��ʼ���ؼ�
void CShoppingGuideDlg::GetAllFloor()
{
	m_vFloor.clear();
	m_Floor.ResetContent();
	CString strSQL = _T("select * from tbFloor");

	CADORecordset rs(&CShoppingGuideApp::staffDB);
	if (rs.Open(strSQL))
	{
		CString strField;
		Data t;
		while (!rs.IsEof())
		{
			rs.GetFieldValue(_T("FNO"), strField);
			int i = _ttoi(strField);
			t.nID = i;

			rs.GetFieldValue(_T("PS"), strField);
			CString str;
			str.Format(_T("%d¥(%s)"), i, strField);
			m_Floor.AddString(str);


			rs.GetFieldValue(_T("PicID"), strField);
			i = _ttoi(strField);
			t.nPic = i;


			rs.GetFieldValue(_T("Matrix"), strField);
			t.tbMatrix = strField;
			rs.GetFieldValue(_T("Location"), strField);
			t.tbLocation = strField;
			m_vFloor.push_back(t);

			rs.MoveNext();
		}
		rs.Close();
	}
	m_Floor.SetCurSel(0);
	GetFloorPosition();
}


// ��ȡ�������Ʒ��Ϣ
void CShoppingGuideDlg::GetProByFNO(int Fno, CString& Discount)
{
	m_vPros.clear();

	CString strSQL;
	if (Discount.Compare(L"-1") == 0)
	{
		strSQL.Format(_T("select * from tbPro where FNO = %d"), Fno);
	}
	else
	{
		strSQL.Format(_T("select * from tbPro where FNO=%d AND PID IN (select PID from tbPrice where Pdiscount='%s') order by PID ASC"), Fno, Discount);
	}

	

	CADORecordset rs(&CShoppingGuideApp::staffDB);
	if (rs.Open(strSQL))
	{
		
		if (0 == rs.GetRecordCount())
		{
			
			//���²���
			m_Discount.SetCurSel(0);
			GetProByFNO(Fno, m_vDiscount[0]);
			CString str;
			str.Format(_T("��%s�ۿ���Ʒ"), Discount);
			AfxMessageBox(str);
			rs.Close();
			return;
		}


		CString strField;
		Data t;
		while (!rs.IsEof())
		{

		//	rs.GetFieldValue(_T("Pname"), strField);
		//	m_Pros.AddString(strField);


			rs.GetFieldValue(_T("PicID"), strField);
			int i = _ttoi(strField);
			t.nPic = i;
		
			rs.GetFieldValue(_T("PosID"), strField);
			 i = _ttoi(strField);
			t.nID = i;

			m_vPros.push_back(t);

			rs.MoveNext();
		}
		rs.Close();
	}
	//m_Pros.SetCurSel(0);
	InitPrice(Fno, Discount);
}

//¥��ı�
void CShoppingGuideDlg::OnCbnSelchangeComboFloor()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//����¥��ͼ

	m_Map.DrawWnd(m_vFloor[m_Floor.GetCurSel()].nPic);

	//����¥�����
	SetFloorEnter(m_vFloor[m_Floor.GetCurSel()].nID);

	//��ȡ¥��λ����Ϣ
	GetFloorPosition();
	//��ȡ��¥���ۿ���Ϣ
	InitDiscount();

	//��ȡ�ۿ���Ʒ
	GetProByFNO(m_vFloor[m_Floor.GetCurSel()].nID, m_vDiscount[m_Discount.GetCurSel()]);

	//������Ʒͼ
	m_Pic.DrawWnd(m_vPros[m_Pros.GetCurSel()].nPic);
	


	

	m_Road.Clear();
	
}


void CShoppingGuideDlg::SetFloorEnter(int Fno)
{
	m_vEnter.clear();
	m_Enter.ResetContent();
	CString strSQL;
	strSQL.Format(_T("select * from tbEnter where FNO = %d"), Fno);

	CADORecordset rs(&CShoppingGuideApp::staffDB);
	if (rs.Open(strSQL))
	{
		CString strField;
		while (!rs.IsEof())
		{

			rs.GetFieldValue(_T("PosNO"), strField);
			int i = _ttoi(strField);
			m_vEnter.push_back(i);

			rs.GetFieldValue(_T("PS"), strField);

			m_Enter.AddString(strField);

			rs.MoveNext();
		}
		rs.Close();
	}
	m_Enter.SetCurSel(0);
}

//��Ʒ���ı�
void CShoppingGuideDlg::OnCbnSelchangeComboGoods()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//������ƷͼƬ
	m_Pic.DrawWnd(m_vPros[m_Pros.GetCurSel()].nPic);


}


// ��ȡ¥��λ����Ϣ
void CShoppingGuideDlg::GetFloorPosition()
{
	m_vLocation.clear();

	CString strSQL;
	strSQL.Format(_T("select * from %s"), m_vFloor[m_Floor.GetCurSel()].tbLocation);

	CADORecordset rs(&CShoppingGuideApp::staffDB);
	
	if (rs.Open(strSQL))
	{
		CString strField;
		LocatPosition t;
		int i;
		while (!rs.IsEof())
		{
		
			rs.GetFieldValue(_T("LID"), strField);
			i = _ttoi(strField);
			t.nID = i;

			rs.GetFieldValue(_T("Lx"), strField);
			i = _ttoi(strField);
			t.x = i;

			rs.GetFieldValue(_T("Ly"), strField);
			int i = _ttoi(strField);
			t.y = i;
			m_vLocation.push_back(t);//�������нڵ�λ����Ϣ
			rs.MoveNext();
		}
		rs.Close();
	}

}


// ����ͼ;//����ͼ������ڵ���Ϣ
void CShoppingGuideDlg::InitRoad()
{
	
	m_Road.Clear();//������Ϣ�����
	m_Road.CreateMap(m_vLocation.size());//��ʼ��ͼ�Ľڵ���


	

	CString strSQL;
	strSQL.Format(_T("select * from %s"), m_vFloor[m_Floor.GetCurSel()].tbMatrix);

	CADORecordset rs(&CShoppingGuideApp::staffDB);

	if (rs.Open(strSQL))
	{
		CString strField;
		int LID1, LID2, Edge;
		while (!rs.IsEof())
		{

			rs.GetFieldValue(_T("LID1"), strField);
			LID1 = _ttoi(strField);
			

			rs.GetFieldValue(_T("LID2"), strField);
			LID2 = _ttoi(strField);

			rs.GetFieldValue(_T("Edge"), strField);
			Edge = _ttoi(strField);
			m_Road.setEdge(LID1, LID2, Edge);
			m_Road.setEdge(LID2, LID1, Edge);
			rs.MoveNext();
		}
		rs.Close();
	}
}


void CShoppingGuideDlg::OnBnClickedButtonFeedback()
{
	CFeedBack m_FeedBack(this);
	if (IDOK == m_FeedBack.DoModal())
	{
		MessageBox(L"̫��л��ķ�����",L"Thanks");
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


BOOL CShoppingGuideDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//���ù��
	HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR1);
	SetCursor(hCursor);
	return TRUE;//CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


// ��ʼ���ۿ�����

void CShoppingGuideDlg::InitDiscount()
{
	m_Discount.ResetContent();
	m_vDiscount.clear();
	int FNO = m_vFloor[m_Floor.GetCurSel()].nID;
	//��ѯ�ۿ۱���ȥ��
	CString strSQL;
	strSQL.Format(_T("select Pdiscount from tbPrice where PID IN(select PID from tbPro where FNO =%d) group by Pdiscount order by Pdiscount ASC"), FNO);

	CADORecordset rs(&CShoppingGuideApp::staffDB);
	//Ĭ��ֵ
	m_Discount.AddString(L"��ѡ��");
	m_vDiscount.push_back(L"-1");

	if (rs.Open(strSQL))
	{
		CString strDiscount;
		CString strField;
		//����ֵ
		m_Discount.AddString(L"ԭ��");
		m_vDiscount.push_back(L"0");
		rs.MoveNext();
		while (!rs.IsEof())
		{

			rs.GetFieldValue(_T("Pdiscount"), strField);
			m_vDiscount.push_back(strField);
			strDiscount.Format(_T("%s��"), strField);
			m_Discount.AddString(strDiscount);
	
			rs.MoveNext();
		}
		rs.Close();
	}



	

	m_Discount.SetCurSel(0);

}

//�ı��ۿ�
void CShoppingGuideDlg::OnCbnSelchangeComboDiscount()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//��ѯ���ۿ۵�������Ʒ
	GetProByFNO(m_vFloor[m_Floor.GetCurSel()].nID, m_vDiscount[m_Discount.GetCurSel()]);

}

//�ı�������Ʒ��Ϣ
int CShoppingGuideDlg::FindProbyName(int& nPic)
{
	CString strSQL;
	strSQL.Format(_T("select PicID,PosID from tbPro where Pname = '%s' AND FNO = %d"), m_Pname, m_vFloor[m_Floor.GetCurSel()]);

	CADORecordset rs(&CShoppingGuideApp::staffDB);

	if (rs.Open(strSQL))
	{
		if (rs.GetRecordCount() == 0)
		{
			rs.Close();
			return -1;
		}


		CString strField;
		rs.GetFieldValue(_T("PicID"), strField);
		nPic = _ttoi(strField);
	
		rs.GetFieldValue(_T("PosID"), strField);
	
	

		rs.Close();
		return _ttoi(strField);
		}

	return -1;
}


// ��ʼ����ǰ��Ʒ�۸�
void CShoppingGuideDlg::InitPrice(int Fno, CString& Discount)
{

	m_Pros.ResetContent();
	CString strSQL;
	if (Discount.Compare(L"-1") == 0)
	{
		strSQL.Format(_T("select  tbPro.PID,tbPro.Pname,tbPrice.Price from tbPro,tbPrice where tbPro.PID=tbPrice.PID AND tbPro.FNO=%d order by PID ASC"), Fno);
	}
	else
	{
		strSQL.Format(_T("select  tbPro.PID,tbPro.Pname,tbPrice.Price from tbPro,tbPrice where tbPro.PID=tbPrice.PID AND tbPro.FNO=%d AND tbPrice.Pdiscount = '%s' order by PID ASC"), Fno, Discount);
	}

	CADORecordset rs(&CShoppingGuideApp::staffDB);

	if (rs.Open(strSQL))
	{
		CString strDiscount;
		CString strField;
	
		CString strPro;
		double price = 0;
		double discount = 0;
		while (!rs.IsEof())
		{
			
			rs.GetFieldValue(_T("Pname"), strField);
	
			rs.GetFieldValue(_T("Price"), strDiscount);
			//�ַ�ת������
			price = _ttof(strDiscount);
			discount = _ttof(m_vDiscount[m_Discount.GetCurSel()]);
			if (0 == m_Discount.GetCurSel())
			{
				strPro.Format(_T("%s(ԭ��:%s)"), strField, strDiscount);

			}
			else if (1 == m_Discount.GetCurSel())
			{
				discount = discount + 1;
				strPro.Format(_T("%s(ԭ��:%s,��ǰ�۸�:%.2f)"), strField, strDiscount, price*discount);
			}
			else
			{
				discount = discount*0.1;
				strPro.Format(_T("%s(ԭ��:%s,��ǰ�۸�:%.2f)"), strField, strDiscount, price*discount);
			}
		
		
			m_Pros.AddString(strPro);
			rs.MoveNext();
		}
		rs.Close();
	}
	//
	m_Pros.SetCurSel(0);


	//������ƷLOGO
	m_Pic.DrawWnd(m_vPros[m_Pros.GetCurSel()].nPic);
}
