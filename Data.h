#if !defined(AFX_DATA_H__D42E6B4E_16CF_4600_92D2_413684752821__INCLUDED_)
#define AFX_DATA_H__D42E6B4E_16CF_4600_92D2_413684752821__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Data.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CData dialog

class CData : public CDialog
{
// Construction
public:
	CData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CData)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CData)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATA_H__D42E6B4E_16CF_4600_92D2_413684752821__INCLUDED_)
