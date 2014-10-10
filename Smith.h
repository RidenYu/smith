// Smith.h : main header file for the SMITH application
//

#if !defined(AFX_MYDLGOPENGL_H__0BB6B4AF_44E2_4C2C_93EC_1DCAB106E433__INCLUDED_)
#define AFX_MYDLGOPENGL_H__0BB6B4AF_44E2_4C2C_93EC_1DCAB106E433__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSmithApp:
// See Smith.cpp for the implementation of this class
//

class CSmithApp : public CWinApp
{
public:
	CSmithApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmithApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSmithApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLGOPENGL_H__0BB6B4AF_44E2_4C2C_93EC_1DCAB106E433__INCLUDED_)
