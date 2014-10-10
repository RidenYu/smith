#if !defined(AFX_OPENGL_H__5F24BFC3_AC0B_4C09_BBBE_2807361BBA52__INCLUDED_)
#define AFX_OPENGL_H__5F24BFC3_AC0B_4C09_BBBE_2807361BBA52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenGL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenGL window
class COpenGL : public CWnd
{
// Construction
public:
	COpenGL();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGL)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COpenGL();

	//添加的成员函数与成员变量
	int MySetPixelFormat(HDC hdc);
	void DrawColorBox(void);
	HDC hdc ;
	HGLRC hglrc;
	GLfloat step,s;
	double color_cc,color_dd,color_ff,color_fff;
	double c_x,y_x;
	int x_show,y_show;/////X，Y坐标轴的显示
	int reflect_show;/////////////////////显示与隐藏等反射系数圆标志
	int r_show;////////////////////////////显示与隐藏等电阻圆标志
	int k_show;///////////////////////////显示与隐藏等电抗圆标志
	int tor_normalized_show,tor2_normalized_show,r_normalized_show,x_normalized_show,fi_normalized_show,pot_normalized_show;////////////////画交点时等电阻圆与等反射系数圆的显示标志
	int y_normalized_show,y_reflectcircle_show,g_unit_show,c_show,d_show,f_show,ff_show;
	double r_color;//////////////////////找点时，等电阻圆闪烁颜色设置
	double Fi_x,Fi_y,Fi_dis,Fi;////////////////////////////////定义变量画相角线
	double theta_y,theta_c,theta_d,theta_f,theta_ff;////////////////////////////定义角度对应单支节阻抗匹配时，各点由X轴逆时针旋转得到的角度
	////////////////////////////////////////////////////////////////

	// Generated message map functions
protected:
	//{{AFX_MSG(COpenGL)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGL_H__5F24BFC3_AC0B_4C09_BBBE_2807361BBA52__INCLUDED_)
