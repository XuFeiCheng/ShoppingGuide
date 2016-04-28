
// ManagementDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Management.h"
#include "ManagementDlg.h"
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


// CManagementDlg �Ի���



CManagementDlg::CManagementDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManagementDlg::IDD, pParent)
	, m_Uname(_T(""))
	, m_Upwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UNAME, m_Uname);
	DDX_Text(pDX, IDC_EDIT_UPWD, m_Upwd);
}

BEGIN_MESSAGE_MAP(CManagementDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CManagementDlg::OnBnClickedButtonLogin)
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CManagementDlg ��Ϣ�������

BOOL CManagementDlg::OnInitDialog()
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
	//��ʼ���ؼ�
	InitCtrls();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CManagementDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CManagementDlg::OnPaint()
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
HCURSOR CManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CManagementDlg::OnBnClickedButtonLogin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CMainFrame dlg(this);
	if (m_Uname.Compare(_T("admin")) == 0 && m_Upwd.Compare(_T("admin")) == 0)
	{
		if (!LinkDB())
		{
			MessageBox(_T("�������ݿ�ʧ�ܣ�"), _T("ϵͳ��ʾ"), MB_ICONSTOP);
		}
		else
		{
			KillTimer(1);
			
			dlg.DoModal();
		}
	}
	else
	{
		MessageBox(_T("��½��Ϣ����"), _T("ϵͳ��ʾ"), MB_ICONSTOP);
	}
}


BOOL CManagementDlg::LinkDB()
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
	strConnect.Format(_T("Provider=sqloledb;Data Source=%s;Initial Catalog=%s;User Id=%s;Password=%s;"), SVname, DBname, Account, PassWord);
	return CManagementApp::MarketDB.Open(strConnect);

}


void CManagementDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (CManagementApp::MarketDB.IsOpen())
	{
		CManagementApp::MarketDB.Close();
	}


	CDialogEx::OnClose();
}


void CManagementDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	static int _num = 20;
	if (_num == 0)
	{
		KillTimer(1);
		this->OnCancel();
	}
	CString time;
	time.Format(_T("XX�̳���̨����ϵͳ   ���� %d ���ڵ�½"), _num);
	SetWindowText(time);
	_num--;

	CDialogEx::OnTimer(nIDEvent);
}


void CManagementDlg::InitCtrls()
{
	SetTimer(1, 1000, NULL);
	SetWindowText(_T("XX�̳���̨����ϵͳ"));
	GetDlgItem(IDC_EDIT_UNAME)->SetFocus();
}
