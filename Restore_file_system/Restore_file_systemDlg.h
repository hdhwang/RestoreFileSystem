
// Restore_file_systemDlg.h : 헤더 파일
//

#pragma once


// CRestore_file_systemDlg 대화 상자
class CRestore_file_systemDlg : public CDialogEx
{
// 생성입니다.
public:
	CRestore_file_systemDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RESTORE_FILE_SYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
