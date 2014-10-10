// SmithDlg.h : header file
//

#if !defined(AFX_MYDLGOPENGLDLG_H__CE54B02D_9E37_4B5D_9F1C_DC72363B5446__INCLUDED_)
#define AFX_MYDLGOPENGLDLG_H__CE54B02D_9E37_4B5D_9F1C_DC72363B5446__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "opengl.h"

/////////////////////////////////////////////////////////////////////////////
// CSmithDlg dialog

class CSmithDlg : public CDialog
{
// Construction
public:
	CSmithDlg(CWnd* pParent = NULL);	// standard constructor
    

	// 添加类的虚构函数和成员变量
	~CSmithDlg(void);
	COpenGL *m_pDisplay;
/////////////////////////////////////////////////////////////////////////////

// Dialog Data
	//{{AFX_DATA(CSmithDlg)
	enum { IDD = IDD_SMITH_DIALOG };
	double	m_num1;
	double	m_num2;
	double	m_num3;
	double	m_num4;
	double	m_num5;
	double	m_num6;
	double	m_num7;
	double	m_num8;
	double	m_num9;
	double	m_num10;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmithDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSmithDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton10();
	afx_msg void OnButton12();
	afx_msg void OnButton13();
	afx_msg void OnButton14();
	afx_msg void OnButton21();
	afx_msg void OnButton11();
	afx_msg void OnButton15();
	afx_msg void OnButton16();
	afx_msg void OnButton17();
	afx_msg void OnButton18();
	afx_msg void OnButton19();
	afx_msg void OnButton20();
	afx_msg void OnButton23();
	afx_msg void OnButton22();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLGOPENGLDLG_H__CE54B02D_9E37_4B5D_9F1C_DC72363B5446__INCLUDED_)
