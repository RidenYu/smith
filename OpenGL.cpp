// OpenGL.cpp : implementation file
#include "stdafx.h"
#include "Smith.h"
#include "OpenGL.h"
#include "math.h"
#include "SmithDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define pi 3.1415926535898 
/////////////////////////////////////////////////////////////////////////////
// COpenGL

COpenGL::COpenGL()
{
	//����Ա��������ֵ
	step=0.0;
	s=0.1;
	x_show=1.0f;
	y_show=1.0f;
	reflect_show=0;
	r_show=1;
	k_show=1;
	r_color=1.0f;
	tor_normalized_show=0.0f;
	tor2_normalized_show=0.0f;
	x_normalized_show=0.0f;
	r_normalized_show=0.0f;
	fi_normalized_show=0.0f;
	pot_normalized_show=0.0f;
	/////////////////////////////////��ʾ����֧ƥ��ʱ�ı�����ʼ��
	y_normalized_show=0.0f;///��ʾ��һ����������λ��
	y_reflectcircle_show=0.0f;////��ʾ��һ�����ɵ����ڷ���ϵ��Բ
	g_unit_show=0.0f;///��ʾG=1��Ӧ��Բ
	c_show=0.0f;///��ʾ����ϵ��Բ��G=1Բ����C
	d_show=0.0f;///��ʾ����ϵ��Բ��G=1Բ����D
	f_show=0.0f;//��ʾF��
	ff_show=0.0f;//��ʾF'��
	color_cc=1.0f;
	color_dd=1.0f;
	color_ff=1.0f;
	color_fff=1.0f;
}

COpenGL::~COpenGL()
{
	wglMakeCurrent(NULL, NULL) ; 
	wglDeleteContext(hglrc);	//ɾ����Ⱦ������
	::ReleaseDC (m_hWnd, hdc) ; //�ͷ��豸������

}


BEGIN_MESSAGE_MAP(COpenGL, CWnd)
	//{{AFX_MSG_MAP(COpenGL)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// COpenGL message handlers

////////////////////////////////////////////////////////////////////////////
// �������ظ�ʽ����
int COpenGL::MySetPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd = { 
	    sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С 
	    1,                                // �汾�� 
	    PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ 
	    PFD_SUPPORT_OPENGL |              // ֧�� OpenGL 
	    PFD_DOUBLEBUFFER,                 // ˫����ģʽ 
	    PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ 
	    24,                               // 24 λ��ɫ��� 
	    0, 0, 0, 0, 0, 0,                 // ������ɫλ 
	    0,                                // û�з�͸���Ȼ��� 
	    0,                                // ������λλ 
	    0,                                // ���ۼӻ��� 
	    0, 0, 0, 0,                       // �����ۼ�λ 
	    32,                               // 32 λ��Ȼ���     
	    0,                                // ��ģ�建�� 
	    0,                                // �޸������� 
	    PFD_MAIN_PLANE,                   // ���� 
	    0,                                // ���� 
	    0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ 
	}; 
	
	int  iPixelFormat; 
 
	// Ϊ�豸������õ���ƥ������ظ�ʽ 
	if((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
	{
		MessageBox("ChoosePixelFormat Failed", NULL, MB_OK);
		return 0;
	}
	 
	// ������ƥ������ظ�ʽΪ��ǰ�����ظ�ʽ 
	if(SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
	{
		MessageBox("SetPixelFormat Failed", NULL, MB_OK);
		return 0;
	}

	return 1;
}

int COpenGL::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	// TODO: Add your specialized creation code here
	// ���õ�ǰ�Ļ�ͼ���ظ�ʽ
	MySetPixelFormat(::GetDC(m_hWnd));

	// ��û�ͼ������
	hdc = ::GetDC(m_hWnd);
	// ������Ⱦ������
	hglrc = wglCreateContext(hdc);
	// ʹ��ͼ������Ϊ��ǰ�����̵ֳĵ�ǰ��ͼ������ 
	wglMakeCurrent(hdc, hglrc);	
	return 0;
}

void COpenGL::OnPaint() 
{
	//CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// TODO: Add your message handler code here
	SetTimer(1,20,NULL);
	//����OpenGL��ͼ��������ͼ�λ���
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//�����ɫ�������Ȼ���

	float unit_x,unit_y;////////////////////////////////////////�洢��λԲX,Y����
	float R_x,R_y;///////////////////////////////////////////////�洢��rԲX��Y����
	float K_x,K_y;/////////////////////////////////////////////////�洢�ȵ翹xԲ��X��Y����
	float r=0.2;////////����rԲ

	double r_normalized;////////////////�����һ������ֵ
	double x_normalized;////////////////�����һ���翹ֵ
	float angle_normalized;///////////////����������õ��Ƕ�
	float x_angle;

	extern double num1;//////////////////////ȫ�ֱ������öԻ������������
	extern double num2;
	extern double num3;

	////////////////////////////////////���� �ȵ翹Բ�õ��Ĳ���
	float theta;
	float k;//////////���ȵ翹xԲ

	/////////////////////////////////////////////////���ƹ�һ�������õ���������
	r_normalized=num2/num1;///////////�����һ������ֵ
	x_normalized=num3/num1;//////////�����һ���翹ֵ
	angle_normalized=acos((x_normalized*x_normalized-(1+r_normalized)*(1+r_normalized))/(x_normalized*x_normalized+(1+r_normalized)*(1+r_normalized)));
	x_angle=acos((1-x_normalized*x_normalized)/(1+x_normalized*x_normalized));

	/////////////////////////////////////////////////////////////////����X��Y��
	glColor3f(1.0f,1.0f,1.0f);
	if(x_show==1.0f)
	{
		glBegin(GL_LINES);
			glVertex3f(-1.0f,0.0f,0.0f);
			glVertex3f(1.0f,0.0f,0.0f);
		glEnd();
	}
	if(y_show==1.0f)
	{
		glBegin(GL_LINES);
			glVertex3f(0.0f,-1.0f,0.0f);
			glVertex3f(0.0f,1.0f,0.0f);
		glEnd();
	}
///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////����������ĵ�λԲ
	glColor3f(r_color,0.0f,0.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINE_STRIP);
		for(float angle=0.0f;angle<=2*pi+0.1;angle+=0.01)
		{
			unit_x=0.0f+1*cos(angle);
			unit_y=0.0f+1*sin(angle);
			glVertex3f(unit_x,unit_y,0.0f);
		}			
	glEnd();

////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////���Ƶȵ���rԲ
	glColor3f(0.0f,1.0f,0.0f);
	glLineWidth(0.5f);
	if(r_show==1)
	{
		glBegin(GL_LINE_STRIP);
		while(r<5)
		{
			for(angle=0.0f;angle<=2*pi+0.1;angle+=0.01)
			{
				R_x=r/(1+r)+(1/(1+r))*cos(angle);
				R_y=0+(1/(1+r))*sin(angle);
				glVertex3f(R_x,R_y,0.0f);
			}
			r+=1.0;
		}
		glEnd();
	}

	//////////////////////////////////////////////////////
	/////////////////////////////////////���Ƶȵ翹xԲ

	glColor3f(1.0f,1.0f,0.0f);
	if(k_show==1)
	{
		glBegin(GL_LINE_STRIP);
			k=0.0f;
			theta=acos((1-k*k)/(1+k*k));
			for(angle=3*pi/2-theta;angle<3*pi/2;angle+=0.01)
			{
				K_x=1+(1/k)*cos(angle);
				K_y=(1/k)+(1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();
		glBegin(GL_LINE_STRIP);
			k=0.2f;
			theta=acos((1-k*k)/(1+k*k));
			for(angle=3*pi/2-theta;angle<3*pi/2;angle+=0.01)
			{
			
				K_x=1+(1/k)*cos(angle);
				K_y=(1/k)+(1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();
		glBegin(GL_LINE_STRIP);
			k=0.5f;
			theta=acos((1-k*k)/(1+k*k));
			for(angle=3*pi/2-theta;angle<3*pi/2;angle+=0.01)
			{
			
				K_x=1+(1/k)*cos(angle);
				K_y=(1/k)+(1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();
		glBegin(GL_LINE_STRIP);
			k=1.0f;
			theta=acos((1-k*k)/(1+k*k));
			for(angle=3*pi/2-theta;angle<3*pi/2;angle+=0.01)
			{
			
				K_x=1+(1/k)*cos(angle);
				K_y=(1/k)+(1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();
		glBegin(GL_LINE_STRIP);
			k=1.5f;
			theta=acos((1-k*k)/(1+k*k));
			for(angle=3*pi/2-theta;angle<3*pi/2;angle+=0.01)
			{	
				K_x=1+(1/k)*cos(angle);
				K_y=(1/k)+(1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();
		glBegin(GL_LINE_STRIP);
			k=2.0f;
			theta=acos((1-k*k)/(1+k*k));
			for(angle=3*pi/2-theta;angle<3*pi/2;angle+=0.01)
			{
			
				K_x=1+(1/k)*cos(angle);
				K_y=(1/k)+(1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();
		glBegin(GL_LINE_STRIP);
			k=2.5f;
			theta=acos((1-k*k)/(1+k*k));
			for(angle=3*pi/2-theta;angle<3*pi/2;angle+=0.01)
			{
			
				K_x=1+(1/k)*cos(angle);
				K_y=(1/k)+(1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();
		glBegin(GL_LINE_STRIP);
			k=5.0f;
			theta=acos((1-k*k)/(1+k*k));
			for(angle=3*pi/2-theta;angle<3*pi/2;angle+=0.01)
			{
			
				K_x=1+(1/k)*cos(angle);
				K_y=(1/k)+(1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();

	///////////////////////////////////////////////�°벿�ֵȵ翹xԲ
		glBegin(GL_LINE_STRIP);
			k=-0.2f;
			theta=acos((1-k*k)/(1+k*k));
			for(angle=pi/2;angle<=pi/2+theta;angle+=0.01)
			{
			
				K_x=1+(-1/k)*cos(angle);
				K_y=(1/k)+(-1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();
		glBegin(GL_LINE_STRIP);
			k=-0.5f;
			theta=acos((1-k*k)/(1+k*k));
			for(angle=pi/2;angle<=pi/2+theta;angle+=0.01)
			{
			
				K_x=1+(-1/k)*cos(angle);
				K_y=(1/k)+(-1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();
		glBegin(GL_LINE_STRIP);
			k=-1.0f;
			theta=acos((1-k*k)/(1+k*k));
			for(angle=pi/2;angle<=pi/2+theta;angle+=0.01)
			{
			
				K_x=1+(-1/k)*cos(angle);
				K_y=(1/k)+(-1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();
		glBegin(GL_LINE_STRIP);
			k=-1.5f;
			theta=acos((1-k*k)/(1+k*k));
			for(angle=pi/2;angle<=pi/2+theta;angle+=0.01)
			{
			
				K_x=1+(-1/k)*cos(angle);
				K_y=(1/k)+(-1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();
		glBegin(GL_LINE_STRIP);
			k=-2.0f;
			theta=acos((1-k*k)/(1+k*k));
			for(angle=pi/2;angle<=pi/2+theta;angle+=0.01)
			{
			
				K_x=1+(-1/k)*cos(angle);
				K_y=(1/k)+(-1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();
		glBegin(GL_LINE_STRIP);
			k=-2.5f;
			theta=acos((1-k*k)/(1+k*k));
			for(angle=pi/2;angle<=pi/2+theta;angle+=0.01)
			{
			
				K_x=1+(-1/k)*cos(angle);
				K_y=(1/k)+(-1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();
		glBegin(GL_LINE_STRIP);
			k=-5.0f;
			theta=acos((1-k*k)/(1+k*k));
			for(angle=pi/2;angle<=pi/2+theta;angle+=0.01)
			{
			
				K_x=1+(-1/k)*cos(angle);
				K_y=(1/k)+(-1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();
	}
	/////////////////////////////////////////////////////////���ȷ���ϵ��Բ
	float reflect_r=0.0;////////////////////////////////////�ȷ���ϵ��Բ�뾶
	if(reflect_show==1)
	{

		glColor3f(0.0f,1.0f,1.0f);
		while(reflect_r<1.0)
		{
			glBegin(GL_LINE_STRIP);
			for(angle=0.0f;angle<=2*pi+0.1;angle+=0.01)
			{
				glVertex3f(0.0f+reflect_r*cos(angle),0.0f+reflect_r*sin(angle),0.0f);
			}
			glEnd();
			reflect_r+=0.2;
		}
	}
	/////////////////////////////////////////////////�����������ݼ���Ŀ������

	glColor3f(1.0f,0.0,1.0f);///////////////////////////��ɫͳһ����Ϊ��ɫ
	//////////////////////////////�ȵ���Բ
	if(r_normalized_show==1.0f)
	{
		glBegin(GL_LINE_STRIP);
			for(angle=0.0f;angle<=2*pi+0.1;angle+=0.01)
				{
					R_x=r_normalized/(1+r_normalized)+(1/(1+r_normalized))*cos(angle);
					R_y=0+(1/(1+r_normalized))*sin(angle);
					glVertex3f(R_x,R_y,0.0f);
				}
		glEnd();
	}
	/////////////////////////////�ȵ翹Բ

	if(x_normalized_show==1.0f)
	{
		if(num3>=0)
		{
			glBegin(GL_LINE_STRIP);
					k=x_normalized;
					theta=acos((1-k*k)/(1+k*k));
					for(angle=3*pi/2-theta;angle<3*pi/2;angle+=0.01)
					{
			
						K_x=1+(1/k)*cos(angle);
						K_y=(1/k)+(1/k)*sin(angle);
						glVertex3f(K_x,K_y,0.0f);
					}
			glEnd();
		}
		else
		{
			glBegin(GL_LINE_STRIP);
			k=num3/num1;
			x_angle=acos((1-k*k)/(1+k*k));
			for(angle=pi/2;angle<=pi/2+x_angle;angle+=0.01)
			{
			
				K_x=1+(-1/k)*cos(angle);
				K_y=(1/k)+(-1/k)*sin(angle);
				glVertex3f(K_x,K_y,0.0f);
			}
		glEnd();
		}
	}
	//////////////////////////////////��ʾ���ȵ���Բ��ȵ翹Բ�Ľ��㣬����ɫ��ʾ
	if(pot_normalized_show==1.0f)
	{
		glColor3f(1.0f,0.0f,1.0f);
		glPointSize(8.0f);
		glBegin(GL_POINTS);
		if(num3>=0)
			glVertex3f(r_normalized/(1+r_normalized)+(1/(1+r_normalized))*cos(angle_normalized),0+(1/(1+r_normalized))*sin(angle_normalized),0.0f);

		else
			glVertex3f(r_normalized/(1+r_normalized)+(1/(1+r_normalized))*cos(angle_normalized),0-(1/(1+r_normalized))*sin(angle_normalized),0.0f);

		glEnd();
	}
	////////////////////////////////////////////////////��������Բ�������������뵥λԲ�Ľ���õ����Fi
	//double Fi_x,Fi_y,Fi_dis,Fi;////////////////////////////////��������������
	Fi_x=r_normalized/(1+r_normalized)+(1/(1+r_normalized))*cos(angle_normalized);
	Fi_y=0+(1/(1+r_normalized))*sin(angle_normalized);
	Fi_dis=sqrt(Fi_x*Fi_x+Fi_y*Fi_y);
	Fi=acos(Fi_x/Fi_dis);
	if(fi_normalized_show==1.0f)
	{
		if(num3>=0)
		{
			glBegin(GL_LINE_STRIP);
				glVertex3f(0.0f,0.0f,0.0f);
				glVertex3f(1.0f*cos(Fi),1.0f*sin(Fi),0.0f);
			glEnd();		
		}
		else
		{
			glBegin(GL_LINE_STRIP);
				glVertex3f(0.0f,0.0f,0.0f);
				glVertex3f(1.0f*cos(Fi),-1.0f*sin(Fi),0.0f);
			glEnd();
		}
	}
	/////////////////////////////////����ϵ��Բ
	if(tor_normalized_show==1.0f)
	{
			glBegin(GL_LINE_STRIP);
			for(angle=0.0f;angle<=2*pi;angle+=0.01f)
			{
				glVertex3f(Fi_dis*cos(angle),Fi_dis*sin(angle),0.0f);
			}
			glEnd();						
	}
//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////��֧��ƥ��

	double y_y,y_dis;/////////////////��һ�����ɵ��Ӧ��X,Y ����
	y_x=-(r_normalized/(1+r_normalized)+(1/(1+r_normalized))*((x_normalized*x_normalized-(1+r_normalized)*(1+r_normalized))/(x_normalized*x_normalized+(1+r_normalized)*(1+r_normalized))));
	if(num3>=0)
	{
		y_y=-(0+(1/(1+r_normalized))*sin(angle_normalized));
	}
	else
	{
		y_y=(0+(1/(1+r_normalized))*sin(angle_normalized));
	}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////�����һ����Ӧ�Ƕ�theta_y
	y_dis=sqrt(y_x*y_x+y_y*y_y);
/////////////////////////////////////////////////////////////////////��һ������λ����ʾ	
	glColor3f(0.2f,1.0f,0.8f);
	if(y_normalized_show==1.0f)
	{
		glPointSize(8.0f);
		glBegin(GL_POINTS);
			glVertex3f(y_x,y_y,0.0f);
		glEnd();
	}
	//////////////////////////////////////////////////////////////////////////////�����һ����Ӧ�Ƕ�theta_y
	if(y_y>=0)
	{
		theta_y=acos((y_x/y_dis));
	}
	else
	{
		theta_y=2*pi-acos((y_x/y_dis));
	}
	//////////////////////////////��һ���������ڵ㷴��ϵ��Բ��ʾ
	if(tor2_normalized_show==1.0f)
	{
			glBegin(GL_LINE_STRIP);
			for(angle=0.0f;angle<=2*pi;angle+=0.01f)
			{
				glVertex3f(Fi_dis*cos(angle),Fi_dis*sin(angle),0.0f);
			}
			glEnd();						
	}
//////////////////////////////////////////G=1Բ��ʾ
	if(g_unit_show==1.0f)
	{
		glBegin(GL_LINE_STRIP);
			 r=1.0f;
				for(angle=0.0f;angle<=2*pi+0.1;angle+=0.01)
				{
					R_x=r/(1+r)+(1/(1+r))*cos(angle);
					R_y=0+(1/(1+r))*sin(angle);
					glVertex3f(R_x,R_y,0.0f);
				}
		glEnd();
	}
	//////////////////////////////////////////////����C���Ӧ�Ƕ�theta_c,�ϰ벿
	 c_x=Fi_dis*Fi_dis;
	double c_y=Fi_dis*sin(acos(Fi_dis));
	double c_dis=sqrt(c_x*c_x+c_y*c_y);
	theta_c=acos(c_x/(c_dis));
///////////////////////////////////////////////����C��ʾ
	glColor3f(1.0f,0.0f,0.0f);
	if(c_show==1.0f)
	{
		glBegin(GL_POINTS);
			glVertex3f(Fi_dis*Fi_dis,Fi_dis*sin(acos(Fi_dis)),0.0f);
		glEnd();
		glColor3f(0.0f,color_cc,color_cc);
		glBegin(GL_LINE_STRIP);
			for(angle=theta_c;angle<=theta_y;angle+=0.01f)
			{
				glVertex3f((Fi_dis+0.1)*cos(angle),(Fi_dis+0.1)*sin(angle),0.0f);
			}
			glEnd();
	}

	/////////////////////////////////////////////����D���Ӧ�Ƕ�theta_d
	theta_d=2*pi-theta_c;
////////////////////////////////////////////////����D��ʾ
	glColor3f(1.0f,0.0f,0.0f);
	if(d_show==1.0f)
	{
		glBegin(GL_POINTS);
			glVertex3f(Fi_dis*Fi_dis,Fi_dis*sin(-acos(Fi_dis)),0.0f);
		glEnd();
		glColor3f(0.0f,color_dd,color_dd);
		if(y_x>=c_x)
		{
		glBegin(GL_LINE_STRIP);
		for(angle=theta_d;angle<=theta_y;angle+=0.01f)
		{
			glVertex3f((Fi_dis+0.05)*cos(angle),(Fi_dis+0.05)*sin(angle),0.0f);
		}
		glEnd();
		}
		else
		{
			glBegin(GL_LINE_STRIP);
		for(angle=theta_d-2*pi;angle<=theta_y;angle+=0.01f)
		{
			glVertex3f((Fi_dis+0.05)*cos(angle),(Fi_dis+0.05)*sin(angle),0.0f);
		}
		glEnd();
		}

	}
////////////////////////////////////////////////ͨ��C�㣬���ȵ翹Բ�뵥λԲ�Ľ��㼴ΪF��
	glColor3f(1.0f,0.0f,0.0f);
	double Xc,Yc;
	Xc=Fi_dis*Fi_dis;
	Yc=Fi_dis*sin(acos(Fi_dis));
	if(f_show==1.0f)
	{
		glBegin(GL_LINE_STRIP);
				k=(2*Yc)/((Xc-1)*(Xc-1)+Yc*Yc);
				theta=acos((1-k*k)/(1+k*k));
				for(angle=3*pi/2-theta;angle<3*pi/2;angle+=0.01)
				{
			
					K_x=1+(1/k)*cos(angle);
					K_y=(1/k)+(1/k)*sin(angle);
					glVertex3f(K_x,K_y,0.0f);
				}
		glEnd();
		
		glColor3f(0.2f,1.0f,0.8f);
		k=(2*Yc)/((Xc-1)*(Xc-1)+Yc*Yc);
		glBegin(GL_POINTS);
			K_x=1+(1/k)*cos(3*pi/2-theta);
			K_y=(1/k)+(1/k)*sin(3*pi/2-theta);
			glVertex3f(K_x,K_y,0.0f);
		glEnd();
	}
///////////////////////////////////////////////////////////////////////////////����F���Ӧ�Ƕ�theta_f
	theta_f=2*pi-acos(K_x/(sqrt(K_x*K_x+K_y*K_y)));

	if(f_show==1.0f)
	{
			glColor3f(0.0f,color_ff,color_ff);
		glBegin(GL_LINE_STRIP);
			for(angle=2*pi-theta_f;angle<=2*pi;angle+=0.01f)
			{
				glVertex3f(0.9*cos(angle),0.9*sin(angle),0.0f);
			}
			glEnd();
	}



//////////////////////////////////////////////ͨ��D�㣬���ȵ翹Բ�뵥λԪ�Ľ��㼴ΪF'��
	glColor3f(1.0f,0.0f,0.0f);
	double Xd,Yd;
	Xd=Fi_dis*Fi_dis;
	Yd=Fi_dis*sin(-acos(Fi_dis));

	if(ff_show==1.0f)
	{
		glBegin(GL_LINE_STRIP);
				k=(2*Yd)/((Xd-1)*(Xd-1)+Yd*Yd);
				theta=acos((1-k*k)/(1+k*k));
				for(angle=pi/2;angle<=pi/2+theta;angle+=0.01)
				{
			
					K_x=1+(-1/k)*cos(angle);
					K_y=(1/k)+(-1/k)*sin(angle);
					glVertex3f(K_x,K_y,0.0f);
				}
		glEnd();
		
		glColor3f(0.2f,1.0f,0.8f);
		glBegin(GL_POINTS);
			K_x=1+(-1/k)*cos(pi/2+theta);
			K_y=(1/k)+(-1/k)*sin(pi/2+theta);
			glVertex3f(K_x,K_y,0.0f);
		glEnd();
	}
//////////////////////////////////////////////////////////////////����F'���Ӧ�Ƕ�theta_ff
	theta_ff=acos(K_x/(sqrt(K_x*K_x+K_y*K_y)));
	if(ff_show==1.0f)
	{
		glColor3f(0.0f,color_fff,color_fff);
		glBegin(GL_LINE_STRIP);
			for(angle=theta_f;angle<=2*pi;angle+=0.01f)
			{
				glVertex3f(0.95*cos(angle),0.95*sin(angle),0.0f);
			}
			glEnd();
	}






    glFlush();
	SwapBuffers(hdc);
	
	// Do not call CWnd::OnPaint() for painting messages
}

void COpenGL::DrawColorBox(void)
{
}

void COpenGL::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(r_color==1.0f)
	{
		r_color=0.0f;
	}
	else
		r_color=1.0f;
	Invalidate(FALSE);
	
	CWnd::OnTimer(nIDEvent);
}
