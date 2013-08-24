// CalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"

#include "Expression.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
private:
        int textPage;
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CButton	m_TextButton;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual void OnCancel();
	afx_msg void OnAboutTxt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
        textPage = 0;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_ABOUT_TXT, m_TextButton);
	//}}AFX_DATA_MAP
}

void CAboutDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	MessageBox("不好意思，你只能点确定。", "小提示", MB_ICONINFORMATION | MB_OK);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_ABOUT_TXT, OnAboutTxt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg dialog

CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalculatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalculatorDlg)
	m_Result = _T("");
	m_Expression = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalculatorDlg)
	DDX_Control(pDX, IDC_INPUT, m_InputBox);
	DDX_Text(pDX, IDC_OUTPUT, m_Result);
	DDX_Text(pDX, IDC_INPUT, m_Expression);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialog)
	//{{AFX_MSG_MAP(CCalculatorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CALC, OnCalc)
	ON_BN_CLICKED(IDC_CTR_OFF, OnOff)
	//}}AFX_MSG_MAP
        ON_CONTROL_RANGE(BN_CLICKED,1010,1031,OnButtonClicked)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
                // 禁用关闭按钮
                // pSysMenu->DeleteMenu(SC_CLOSE,MF_BYCOMMAND);

		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAboutDlg::OnAboutTxt() 
{
	// TODO: Add your control notification handler code here
        static CString AboutText[6] = {"本程序开始编写于2010-03-28，耗时一周。" , 
                                       "绝大部分代码和构思均属原创。" , 
                                       "仅供小范围使用和学习。" , 
                                       "程序中不免有很多未知的Bug，期待大家指出。" , 
                                       "他人修改及完善时请注明原作者：whypro " ,
                                       "The End" };
        
        m_TextButton.SetWindowText(AboutText[textPage]);
        textPage++;
        if (textPage == 6) {
                textPage = 0;
        }	
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalculatorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 重载 PreTranslateMessage 函数，防止按回车和ESC键退出
BOOL CCalculatorDlg::PreTranslateMessage(MSG* pMsg)     
{   
        if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) {
                return TRUE;   
        }
        if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
        return TRUE;
        }

        return   CDialog::PreTranslateMessage(pMsg);   
} 

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCalculatorDlg::OnButtonClicked(UINT nID) {
        m_InputBox.SetFocus();
        DWORD pos = m_InputBox.GetSel();
        m_InputBox.SetSel(pos);

        switch (nID) {        
        case IDC_NUM_0:
                m_InputBox.ReplaceSel("0");
                break;
        case IDC_NUM_1:
                m_InputBox.ReplaceSel("1");
                break;
        case IDC_NUM_2:
                m_InputBox.ReplaceSel("2");
                break;
        case IDC_NUM_3:
                m_InputBox.ReplaceSel("3");
                break;
        case IDC_NUM_4:
                m_InputBox.ReplaceSel("4");
                break;
        case IDC_NUM_5:
                m_InputBox.ReplaceSel("5");
                break;
        case IDC_NUM_6:
                m_InputBox.ReplaceSel("6");
                break;
        case IDC_NUM_7:
                m_InputBox.ReplaceSel("7");
                break;
        case IDC_NUM_8:
                m_InputBox.ReplaceSel("8");
                break;
        case IDC_NUM_9:
                m_InputBox.ReplaceSel("9");
                break;
        case IDC_DOT:
                m_InputBox.ReplaceSel(".");
                break;
        case IDC_NEG:
                m_InputBox.ReplaceSel("-");
                break;
        case IDC_LEFT_BR:
                m_InputBox.ReplaceSel("(");
                break;
        case IDC_RIGHT_BR:
                m_InputBox.ReplaceSel(")");
                break;
        case IDC_OP_PLUS:
                m_InputBox.ReplaceSel("+");
                break;
        case IDC_OP_MINUS:
                m_InputBox.ReplaceSel("-");
                break;
        case IDC_OP_MULTI:
                m_InputBox.ReplaceSel("*");
                break;
        case IDC_OP_DIV:
                m_InputBox.ReplaceSel("/");
                break;
        case IDC_CTR_BKSPC:
                // 退格键的实现比较复杂
                int pos_a, pos_b;
                m_InputBox.GetSel(pos_a, pos_b);
                // 如果文本被选中则直接删除
                if (pos_a != pos_b) {
                        m_InputBox.ReplaceSel("");
                }
                // 如果文本没有被选中，用 "" 替换pos之前的字符
                else {
                        m_InputBox.SetSel(HIWORD(pos) - 1, HIWORD(pos));
                        m_InputBox.ReplaceSel("");
                }
                break;
        case IDC_CTR_C:
                // 清空输入输出。
                m_Expression = "";
                m_Result = "";
                UpdateData(FALSE);
                break;
        case IDC_CTR_OFF:
                CDialog::OnCancel();
                break;
        case IDC_CTR_ABOUT:
                CAboutDlg dlg;
                dlg.DoModal();
                break;
        }
}

void CCalculatorDlg::OnOff() 
{
	// TODO: Add your control notification handler code here
        CDialog::OnCancel();
	
}

void CCalculatorDlg::OnCalc() 
{
	// TODO: Add your control notification handler code here
        UpdateData();
        CExpression aInstance;
        string input_exp;       // 原始的表达式
        string infix_exp;       // 经修正后的中缀表达式
        string postfix_exp;     // 转化后的后缀表达式
        input_exp = (LPTSTR)(LPCTSTR)m_Expression;

        int illegal = aInstance.fix(input_exp, infix_exp);       // 修正输入，illegal = 0 时合法

        if (!illegal) {                
                aInstance.convert(infix_exp, postfix_exp);        // 表达式转换
                double value = aInstance.calculate(postfix_exp);  // 表达式计算
                m_Result.Format("%f", value);

                // 删除显示结果后多余的 0 和小数点
                int i;
                for (i = m_Result.GetLength() - 1; m_Result[i] == '0'; i--) {
                        m_Result.Delete(i);
                }
                if (m_Result[i] == '.') {
                        m_Result.Delete(i);
                }
        }
        else {
                // 输入有误
                switch (illegal) {
                case 1:
                        m_Result = "Error 1";
                        UpdateData(FALSE);
                        MessageBox("请输入一个表达式", "小提示", MB_ICONINFORMATION | MB_OK );
                        break;
                case 2:
                        m_Result = "Error 2";
                        UpdateData(FALSE);
                        MessageBox("请检查表达式是否含非法字符", "小提示", MB_ICONINFORMATION | MB_OK );
                        break;
                case 3:
                        m_Result = "Error 3";
                        UpdateData(FALSE);
                        MessageBox("请检查表达式括号是否配对。", "小提示", MB_ICONINFORMATION | MB_OK );
                        break;
                case 4 :
                        m_Result = "Error 4";
                        UpdateData(FALSE);
                        MessageBox("请检查表达式运算符及小数点是否合法。", "小提示", MB_ICONINFORMATION | MB_OK );
                        break;
                }
                
        }
        UpdateData(FALSE);	
}

