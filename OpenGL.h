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

	//��ӵĳ�Ա�������Ա����
	int MySetPixelFormat(HDC hdc);
	void DrawColorBox(void);
	HDC hdc ;
	HGLRC hglrc;
	GLfloat step,s;
	double color_cc,color_dd,color_ff,color_fff;
	double c_x,y_x;
	int x_show,y_show;/////X��Y���������ʾ
	int reflect_show;/////////////////////��ʾ�����صȷ���ϵ��Բ��־
	int r_show;////////////////////////////��ʾ�����صȵ���Բ��־
	int k_show;///////////////////////////��ʾ�����صȵ翹Բ��־
	int tor_normalized_show,tor2_normalized_show,r_normalized_show,x_normalized_show,fi_normalized_show,pot_normalized_show;////////////////������ʱ�ȵ���Բ��ȷ���ϵ��Բ����ʾ��־
	int y_normalized_show,y_reflectcircle_show,g_unit_show,c_show,d_show,f_show,ff_show;
	double r_color;//////////////////////�ҵ�ʱ���ȵ���Բ��˸��ɫ����
	double Fi_x,Fi_y,Fi_dis,Fi;////////////////////////////////��������������
	double theta_y,theta_c,theta_d,theta_f,theta_ff;////////////////////////////����Ƕȶ�Ӧ��֧���迹ƥ��ʱ��������X����ʱ����ת�õ��ĽǶ�
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
