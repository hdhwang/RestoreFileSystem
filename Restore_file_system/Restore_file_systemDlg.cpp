
// Restore_file_systemDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Restore_file_system.h"
#include "Restore_file_systemDlg.h"
#include "afxdialogex.h"
#include "Restore_file_system_NTFS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


Restore_file_system_NTFS test;
// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CRestore_file_systemDlg ��ȭ ����




CRestore_file_systemDlg::CRestore_file_systemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRestore_file_systemDlg::IDD, pParent)
	, image_path(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRestore_file_systemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, Image_Path, image_path);
}

BEGIN_MESSAGE_MAP(CRestore_file_systemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(Search_image, &CRestore_file_systemDlg::OnBnClickedimage)
	ON_BN_CLICKED(Partion_Set, &CRestore_file_systemDlg::OnBnClickedSet)
	ON_BN_CLICKED(Partion_Unset, &CRestore_file_systemDlg::OnBnClickedUnset)
END_MESSAGE_MAP()


// CRestore_file_systemDlg �޽��� ó����

BOOL CRestore_file_systemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CRestore_file_systemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CRestore_file_systemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CRestore_file_systemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRestore_file_systemDlg::OnBnClickedimage()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ���� �޾ƿ���
	TCHAR szFilter[] = _T("image Files(*.dd)|*.dd||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter, this);
	if(IDOK == dlg.DoModal()) {
		image_path = dlg.GetPathName();
		GetDlgItem(Partion_Set)->EnableWindow(TRUE);
		GetDlgItem(Partion_Unset)->EnableWindow(TRUE);
		UpdateData(FALSE);
	} else {
		return;
	}

}


void CRestore_file_systemDlg::OnBnClickedSet()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	test.Start_analysis(image_path,1);

	MessageBox((_T("��Ƽ�� ������ �Ϸ��Ͽ����ϴ�.")),
		_T("����"),
		MB_OK|MB_ICONINFORMATION
		);
}


void CRestore_file_systemDlg::OnBnClickedUnset()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	test.Start_analysis(image_path,0);
	MessageBox((_T("��Ƽ�� �ʱ�ȭ�� �Ϸ��Ͽ����ϴ�.")),
		_T("����"),
		MB_OK|MB_ICONINFORMATION
		);
}
