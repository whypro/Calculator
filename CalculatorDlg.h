// CalculatorDlg.h : header file
//

#if !defined(AFX_CalculatorDLG_H__0126D703_350E_44AB_AB5E_FBF9BF11BDEC__INCLUDED_)
#define AFX_CalculatorDLG_H__0126D703_350E_44AB_AB5E_FBF9BF11BDEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg dialog

class CCalculatorDlg : public CDialog
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// standard constructor
        BOOL CCalculatorDlg::PreTranslateMessage(MSG* pMsg);     // жиди PreTranslateMessage

// Dialog Data
	//{{AFX_DATA(CCalculatorDlg)
	enum { IDD = IDD_CALCULATOR_DIALOG };
	CEdit	m_InputBox;
	CString	m_Result;
	CString	m_Expression;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalculatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCalculatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCalc();
	afx_msg void OnOff();
	//}}AFX_MSG
        afx_msg void OnButtonClicked(UINT nID);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CalculatorDLG_H__0126D703_350E_44AB_AB5E_FBF9BF11BDEC__INCLUDED_)
