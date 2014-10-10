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
	//给成员变量赋初值
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
	/////////////////////////////////表示单分支匹配时的变量初始化
	y_normalized_show=0.0f;///显示归一化导纳所在位置
	y_reflectcircle_show=0.0f;////显示归一化导纳点所在反射系数圆
	g_unit_show=0.0f;///显示G=1对应的圆
	c_show=0.0f;///显示反射系数圆与G=1圆交点C
	d_show=0.0f;///显示反射系数圆与G=1圆交点D
	f_show=0.0f;//显示F点
	ff_show=0.0f;//显示F'点
	color_cc=1.0f;
	color_dd=1.0f;
	color_ff=1.0f;
	color_fff=1.0f;
}

COpenGL::~COpenGL()
{
	wglMakeCurrent(NULL, NULL) ; 
	wglDeleteContext(hglrc);	//删除渲染描述表
	::ReleaseDC (m_hWnd, hdc) ; //释放设备描述表

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
// 设置像素格式函数
int COpenGL::MySetPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd = { 
	    sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
	    1,                                // 版本号 
	    PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图 
	    PFD_SUPPORT_OPENGL |              // 支持 OpenGL 
	    PFD_DOUBLEBUFFER,                 // 双缓存模式 
	    PFD_TYPE_RGBA,                    // RGBA 颜色模式 
	    24,                               // 24 位颜色深度 
	    0, 0, 0, 0, 0, 0,                 // 忽略颜色位 
	    0,                                // 没有非透明度缓存 
	    0,                                // 忽略移位位 
	    0,                                // 无累加缓存 
	    0, 0, 0, 0,                       // 忽略累加位 
	    32,                               // 32 位深度缓存     
	    0,                                // 无模板缓存 
	    0,                                // 无辅助缓存 
	    PFD_MAIN_PLANE,                   // 主层 
	    0,                                // 保留 
	    0, 0, 0                           // 忽略层,可见性和损毁掩模 
	}; 
	
	int  iPixelFormat; 
 
	// 为设备描述表得到最匹配的像素格式 
	if((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
	{
		MessageBox("ChoosePixelFormat Failed", NULL, MB_OK);
		return 0;
	}
	 
	// 设置最匹配的像素格式为当前的像素格式 
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
	// 设置当前的绘图像素格式
	MySetPixelFormat(::GetDC(m_hWnd));

	// 获得绘图描述表
	hdc = ::GetDC(m_hWnd);
	// 创建渲染描述表
	hglrc = wglCreateContext(hdc);
	// 使绘图描述表为当前调用现程的当前绘图描述表 
	wglMakeCurrent(hdc, hglrc);	
	return 0;
}

void COpenGL::OnPaint() 
{
	//CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// TODO: Add your message handler code here
	SetTimer(1,20,NULL);
	//调用OpenGL绘图函数进行图形绘制
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//清除颜色缓存和深度缓存

	float unit_x,unit_y;////////////////////////////////////////存储单位圆X,Y坐标
	float R_x,R_y;///////////////////////////////////////////////存储等r圆X，Y坐标
	float K_x,K_y;/////////////////////////////////////////////////存储等电抗x圆的X，Y坐标
	float r=0.2;////////画等r圆

	double r_normalized;////////////////定义归一化电阻值
	double x_normalized;////////////////定义归一化电抗值
	float angle_normalized;///////////////计算过程中用到角度
	float x_angle;

	extern double num1;//////////////////////全局变量引用对话框输入的数据
	extern double num2;
	extern double num3;

	////////////////////////////////////绘制 等电抗圆用到的参数
	float theta;
	float k;//////////画等电抗x圆

	/////////////////////////////////////////////////绘制归一化电阻用到参数计算
	r_normalized=num2/num1;///////////计算归一化电阻值
	x_normalized=num3/num1;//////////计算归一化电抗值
	angle_normalized=acos((x_normalized*x_normalized-(1+r_normalized)*(1+r_normalized))/(x_normalized*x_normalized+(1+r_normalized)*(1+r_normalized)));
	x_angle=acos((1-x_normalized*x_normalized)/(1+x_normalized*x_normalized));

	/////////////////////////////////////////////////////////////////绘制X，Y轴
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
/////////////////////////////////////////////////////////////////绘制最外面的单位圆
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
/////////////////////////////////////////////////////////////////绘制等电阻r圆
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
	/////////////////////////////////////绘制等电抗x圆

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

	///////////////////////////////////////////////下半部分等电抗x圆
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
	/////////////////////////////////////////////////////////画等反射系数圆
	float reflect_r=0.0;////////////////////////////////////等反射系数圆半径
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
	/////////////////////////////////////////////////根据输入数据计算目的数据

	glColor3f(1.0f,0.0,1.0f);///////////////////////////颜色统一设置为紫色
	//////////////////////////////等电阻圆
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
	/////////////////////////////等电抗圆

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
	//////////////////////////////////显示出等电阻圆与等电抗圆的交点，用紫色表示
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
	////////////////////////////////////////////////////将交点与圆心连接起来，与单位圆的交点得到相角Fi
	//double Fi_x,Fi_y,Fi_dis,Fi;////////////////////////////////定义变量画相角线
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
	/////////////////////////////////反射系数圆
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
//////////////////////////////////////////////////////////////////////单支节匹配

	double y_y,y_dis;/////////////////归一化导纳点对应的X,Y 坐标
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
//////////////////////////////////////////////////////////////////////////////计算归一化对应角度theta_y
	y_dis=sqrt(y_x*y_x+y_y*y_y);
/////////////////////////////////////////////////////////////////////归一化导纳位置显示	
	glColor3f(0.2f,1.0f,0.8f);
	if(y_normalized_show==1.0f)
	{
		glPointSize(8.0f);
		glBegin(GL_POINTS);
			glVertex3f(y_x,y_y,0.0f);
		glEnd();
	}
	//////////////////////////////////////////////////////////////////////////////计算归一化对应角度theta_y
	if(y_y>=0)
	{
		theta_y=acos((y_x/y_dis));
	}
	else
	{
		theta_y=2*pi-acos((y_x/y_dis));
	}
	//////////////////////////////归一化导纳所在点反射系数圆显示
	if(tor2_normalized_show==1.0f)
	{
			glBegin(GL_LINE_STRIP);
			for(angle=0.0f;angle<=2*pi;angle+=0.01f)
			{
				glVertex3f(Fi_dis*cos(angle),Fi_dis*sin(angle),0.0f);
			}
			glEnd();						
	}
//////////////////////////////////////////G=1圆显示
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
	//////////////////////////////////////////////计算C点对应角度theta_c,上半部
	 c_x=Fi_dis*Fi_dis;
	double c_y=Fi_dis*sin(acos(Fi_dis));
	double c_dis=sqrt(c_x*c_x+c_y*c_y);
	theta_c=acos(c_x/(c_dis));
///////////////////////////////////////////////交点C显示
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

	/////////////////////////////////////////////计算D点对应角度theta_d
	theta_d=2*pi-theta_c;
////////////////////////////////////////////////交点D显示
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
////////////////////////////////////////////////通过C点，画等电抗圆与单位圆的交点即为F点
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
///////////////////////////////////////////////////////////////////////////////计算F点对应角度theta_f
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



//////////////////////////////////////////////通过D点，画等电抗圆与单位元的交点即为F'点
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
//////////////////////////////////////////////////////////////////计算F'点对应角度theta_ff
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
