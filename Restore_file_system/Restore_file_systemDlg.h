
// Restore_file_systemDlg.h : ��� ����
//

#pragma once


// CRestore_file_systemDlg ��ȭ ����
class CRestore_file_systemDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CRestore_file_systemDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RESTORE_FILE_SYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedimage();
	afx_msg void OnBnClickedSet();
	afx_msg void OnBnClickedUnset();
	CString image_path;
};
