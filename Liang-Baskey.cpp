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

GLdouble X1, Y1, X2, Y2;//���ڼ�¼�ü���Ķ˵�����


void display_rectangle(GLdouble wxl, GLdouble wxr, GLdouble wyb, GLdouble wyt, GLdouble X1, GLdouble Y1, GLdouble X2, GLdouble Y2)//���볤�����ĸ���������
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5.0f);//���õ�Ĵ�С
	glLineWidth(5.0f);//�����ߵĿ��
	
	//���ƿ����ı���
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//ֻ��ʾ����εı��߶���������ڲ�
	glBegin(GL_POLYGON);
	glColor3f(255, 255, 255);
	glVertex2f(wxl, wyb); //��P1,���½�
	glVertex2f(wxl, wyt);  //��P2,���Ͻ�
	glVertex2f(wxr, wyt);   //��P3,���Ͻ�            
	glVertex2f(wxr, wyb); //��P4,���½�
	glEnd();


	glBegin(GL_LINES);
	glColor3f(255, 255, 255);
	glVertex2f(X1, Y1);
	glVertex2f(X2, Y2);
	glEnd();
	
	glFlush();
}

//����Baskey�ü��㷨
void L_B(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2, GLdouble wxl, GLdouble wxr, GLdouble wyb, GLdouble wyt)//����ֱ�������˵�(x1,y1)��(x2,y2)���Լ����������߽�����wxl,wxr,wyb,wyt
{
	glClear(GL_COLOR_BUFFER_BIT);//�����ɫ
	glPointSize(5.0f);//���õ�Ĵ�С

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

	//cout << p1 << " " << p2 << " " << p3 << " " << p4 << endl;//������

	if (_x == 0)
	{
		if (q1 < 0 || q2 < 0)
		{
			cout << "��ֱ�߶β��ڴ�����!" << endl;
			return;
		}
	}

	if (_y == 0)
	{
		if (q3 < 0 || q4 < 0)
		{
			cout << "��ֱ�߶β��ڴ�����!" << endl;
			return;
		}
	}

	double fmin[3];//�����
	fmin[0] = 0;

	double fmax[3];//�����
	fmax[0] = 1;

	GLdouble u1 = 0;
	GLdouble u2 = 0;
	GLdouble u3 = 0;
	GLdouble u4 = 0;

	if (_x != 0)//��������
	{
		u1 = q1 / p1;
		u2 = q2 / p2;
	}

	if (_y != 0)//��������
	{
		u3 = q3 / p3;
		u4 = q4 / p4;
	}

	//cout << u1 << " " << u2 << " " << u3 << " " << u4 << endl;//�����

	if (_x > 0)//������߼����Ӧ����
	{
		fmin[1] = u1;
		fmax[1] = u2;
	}
	if (_x == 0)//�������ж�
	{
		fmin[1] = 0;
		fmax[1] = 1;
	}
	if (_x < 0)//������߼����Ӧ����
	{
		fmin[1] = u2;
		fmax[1] = u1;
	}

	if (_y > 0)//������߼����Ӧ����
	{
		fmin[2] = u3;
		fmax[2] = u4;
	}
	if (_y == 0)//�������ж�
	{
		fmin[2] = 0;
		fmax[2] = 1;
	}
	if (_y < 0)//������߼����Ӧ����
	{
		fmin[2] = u4;
		fmax[2] = u3;
	}


	sort(fmin, fmin + 3);
	sort(fmax, fmax + 3);

	////��֤��
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
	
	//��֤��
	//cout << k1 << endl;
	//cout << k2 << endl;

	//�ü�������
	X1 = x1 + k1 * _x;
	Y1 = y1 + k1 * _y;
	//�ü���ĳ���
	X2 = x1 + k2 * _x;
	Y2 = y1 + k2 * _y;

	//��֤��
	//cout << X1 << " " << Y1 << endl;
	//cout << X2 << " " << Y2 << endl;
	cout << "��ֱ�߶οɲü���" << endl;
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);//��ʼ��
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//������ʾ��ʽ������GLUT_RGB��ʾʹ��RGB��ɫ����֮��Ӧ�Ļ���GLUT_INDEX����ʾʹ��������ɫ����LUT_SINGLE��ʾʹ�õ����壬��֮��Ӧ�Ļ���GLUT_DOUBLE��ʹ��˫���壩��
	glutInitWindowPosition(200, 10);//ָ������λ��
	glutInitWindowSize(800, 800);//ָ�����ڴ�С
	glutCreateWindow("��-Baskeyֱ�߲ü��㷨");//ָ�����ڱ���
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 600.0, 0.0, 600.0);

	//L_B�ü��㷨(�����˵����꣬������磬�ҽ磬�½磬�Ͻ�)
	L_B(100, 300, 500, 300, 200, 400, 200, 400);//�ɹ��������ɲü�
	//L_B(100, 100, 500, 100, 200, 400, 200, 400);//ʧ�ܰ��������ɲü�

	//��ӡ���ڱ߿����£����ϣ����ϣ����£��Ͳü�����߶�
	display_rectangle(200, 400, 200, 400, X1, Y1, X2, Y2);
	
	glutMainLoop();
	return 0;
}