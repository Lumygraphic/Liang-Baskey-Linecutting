#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<windows.h>  
#include<GL/gl.h>  
#include<GL/glu.h>  
#include<GL/glut.h>  
//#include"bresenham.h"
//#include"circle_bre.h"

using namespace std;

GLdouble X1, Y1, X2, Y2;//用于记录裁剪后的端点坐标


void display_rectangle(GLdouble wxl, GLdouble wxr, GLdouble wyb, GLdouble wyt, GLdouble X1, GLdouble Y1, GLdouble X2, GLdouble Y2)//输入长方形四个顶点坐标
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5.0f);//设置点的大小
	glLineWidth(5.0f);//设置线的宽度
	
	//绘制空心四边形
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//只显示多边形的边线而不填充其内部
	glBegin(GL_POLYGON);
	glColor3f(255, 255, 255);
	glVertex2f(wxl, wyb); //点P1,左下角
	glVertex2f(wxl, wyt);  //点P2,左上角
	glVertex2f(wxr, wyt);   //点P3,右上角            
	glVertex2f(wxr, wyb); //点P4,右下角
	glEnd();


	glBegin(GL_LINES);
	glColor3f(255, 255, 255);
	glVertex2f(X1, Y1);
	glVertex2f(X2, Y2);
	glEnd();
	
	glFlush();
}

//梁—Baskey裁剪算法
void L_B(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2, GLdouble wxl, GLdouble wxr, GLdouble wyb, GLdouble wyt)//输入直线两个端点(x1,y1)和(x2,y2)，以及窗口四条边界坐标wxl,wxr,wyb,wyt
{
	glClear(GL_COLOR_BUFFER_BIT);//清除颜色
	glPointSize(5.0f);//设置点的大小

	//(100,300),(500,300)
	//(200,400,200,400)
	GLdouble _x = x2 - x1;//400
	GLdouble _y = y2 - y1;//0

	//cout << _x << " " << _y << endl;

	GLdouble p1 = -_x;//-400
	GLdouble q1 = x1 - wxl;//-100

	GLdouble p2 = _x;//400
	GLdouble q2 = wxr - x1;//300

	GLdouble p3 = -_y;//0
	GLdouble q3 = y1 - wyb;//100

	GLdouble p4 = _y;//0
	GLdouble q4 = wyt - y1;//100

	//cout << p1 << " " << p2 << " " << p3 << " " << p4 << endl;//测试用

	if (_x == 0)
	{
		if (q1 < 0 || q2 < 0)
		{
			cout << "该直线段不在窗口内!" << endl;
			return;
		}
	}

	if (_y == 0)
	{
		if (q3 < 0 || q4 < 0)
		{
			cout << "该直线段不在窗口内!" << endl;
			return;
		}
	}

	double fmin[3];//存入边
	fmin[0] = 0;

	double fmax[3];//存出边
	fmax[0] = 1;

	GLdouble u1 = 0;
	GLdouble u2 = 0;
	GLdouble u3 = 0;
	GLdouble u4 = 0;

	if (_x != 0)//计算出入边
	{
		u1 = q1 / p1;
		u2 = q2 / p2;
	}

	if (_y != 0)//计算出入边
	{
		u3 = q3 / p3;
		u4 = q4 / p4;
	}

	//cout << u1 << " " << u2 << " " << u3 << " " << u4 << endl;//检测用

	if (_x > 0)//将出入边加入对应数组
	{
		fmin[1] = u1;
		fmax[1] = u2;
	}
	if (_x == 0)//不参与判断
	{
		fmin[1] = 0;
		fmax[1] = 1;
	}
	if (_x < 0)//将出入边加入对应数组
	{
		fmin[1] = u2;
		fmax[1] = u1;
	}

	if (_y > 0)//将出入边加入对应数组
	{
		fmin[2] = u3;
		fmax[2] = u4;
	}
	if (_y == 0)//不参与判断
	{
		fmin[2] = 0;
		fmax[2] = 1;
	}
	if (_y < 0)//将出入边加入对应数组
	{
		fmin[2] = u4;
		fmax[2] = u3;
	}


	sort(fmin, fmin + 3);
	sort(fmax, fmax + 3);

	////验证用
	//for (int i = 0; i < 3; i++)
	//{
	//	cout << fmin[i] << " ";
	//}
	//cout << endl;

	//for (int i = 0; i < 3; i++)
	//{
	//	cout << fmax[i] << " ";
	//}
	//cout << endl;

	GLdouble k1 = fmin[2];
	GLdouble k2 = fmax[0];
	
	//验证用
	//cout << k1 << endl;
	//cout << k2 << endl;

	//裁剪后的入点
	X1 = x1 + k1 * _x;
	Y1 = y1 + k1 * _y;
	//裁剪后的出点
	X2 = x1 + k2 * _x;
	Y2 = y1 + k2 * _y;

	//验证用
	//cout << X1 << " " << Y1 << endl;
	//cout << X2 << " " << Y2 << endl;
	cout << "该直线段可裁剪。" << endl;
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);//初始化
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//设置显示方式，其中GLUT_RGB表示使用RGB颜色，与之对应的还有GLUT_INDEX（表示使用索引颜色）。LUT_SINGLE表示使用单缓冲，与之对应的还有GLUT_DOUBLE（使用双缓冲）。
	glutInitWindowPosition(200, 10);//指定窗口位置
	glutInitWindowSize(800, 800);//指定窗口大小
	glutCreateWindow("梁-Baskey直线裁剪算法");//指定窗口标题
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 600.0, 0.0, 600.0);

	//L_B裁剪算法(两个端点坐标，窗口左界，右界，下界，上界)
	L_B(100, 300, 500, 300, 200, 400, 200, 400);//成功案例，可裁剪
	//L_B(100, 100, 500, 100, 200, 400, 200, 400);//失败案例，不可裁剪

	//打印窗口边框（左下，左上，右上，右下）和裁剪后的线段
	display_rectangle(200, 400, 200, 400, X1, Y1, X2, Y2);
	
	glutMainLoop();
	return 0;
}