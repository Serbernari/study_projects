#define _USE_MATH_DEFINES
#include <math.h>
#include <windows.h>
#include <glut.h> 
//#include <glaux.h>
#include <vector>
#include <gl\gl.h>
#include <iostream>
#include <sstream>

//#pragma comment(lib,"glaux.lib")
using namespace std;

GLint width, height;		//������ � ������ ����
GLfloat zoom = 1;			//����������� ��������������� �����������
int ind = 60;				//���������� ����� ������������� ���������
bool moving = false;		//����������� � ������� ����
bool movingPoint = false;	//����������� ����� � ������� ����
bool visibleWeight = true;	//����� ����� ������
int m = 3;					//������� �������� �-�
int n = 0;					//����� ����������� �����
int activePoint = -1;		//����� �������� �����

//����� ����� � �������� �����������
class point
{
public:
	GLint x, y;
	point()
	{
	}
	point(GLint _x, GLint _y)
	{
		x = _x;
		y = _y;
	}
};

point p;					//������� ���� ��� �� ��� ���������� �����������
point Shift = point(0, 0);	//����� ����� �����������
point Shift2;	//����� ��� ��������
point curP;		//����� �� ���������

//����� ����� � �������� �����������
class realPoint
{
public:
	double x, y;	//���������� �����
	double weight;	//��� �����
	realPoint()
	{
	}
	realPoint(double _x, double _y)
	{
		x = _x;
		y = _y;
		weight = 1.;
	}
	//�������������� �������� ��������� � ��������
	realPoint(point _point)
	{
		x = _point.x;
		y = _point.y;

		//�������������� �������� ��������� � ��������
		//���� ������
		x -= Shift.x;
		y -= Shift.y;
		//���� ��������� ������ ���������
		x = x - width / 2.;
		y = y - height / 2.;
		//���� ����� �������� �� ���� �������
		x /= double(ind);
		y /= double(ind);
		//���� ���������������
		x *= zoom;
		y *= zoom;

		weight = 1.;
	}
	point getPoint();
};

//�������������� �������� ��������� � ��������
point realPoint::getPoint()
{
	double _x = x;
	double _y = y;

	//���� ���������������
	_x /= zoom;
	_y /= zoom;
	//���� ����� �������� �� ���� �������
	_x *= double(ind);
	_y *= double(ind);
	//���� ��������� ������ ���������
	_x = _x + width / 2.;
	_y = _y + height / 2.;
	//���� ������
	_x += Shift.x;
	_y += Shift.y;

	return point(_x, _y);
}

//vector <point> vecPoint;
vector <realPoint> vecRealPoint;	//������ ����������� �����
vector <double> vecParameter;		//������ ����������
vector <realPoint> NURBS;			//������ ����� ��� ���������� �������

unsigned int names_tex[10];//����� �������
//�������� ��������
void loadTexture()
{
	//��������� ��������
	//AUX_RGBImageRec *image1 = auxDIBImageLoad(L"1.bmp");
	glGenTextures(10, names_tex); //�������� ���� �������

	glBindTexture(GL_TEXTURE_2D, names_tex[0]); //������� ������� ��������
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image1->sizeX, image1->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
}
//��������� �����
void DrawMesh()
{
	glBindTexture(GL_TEXTURE_2D, names_tex[0]);	//������� ��������
	glEnable(GL_TEXTURE_2D);					//��������� ���������������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//��������� ������ ������ 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	//�� ����� �����������
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);		//�� ��������� ���� �������
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);		glVertex2d(-5000, -5000);
	glTexCoord2d(0, 50);		glVertex2d(-5000, 5000);
	glTexCoord2d(50, 50);	glVertex2d(5000, 5000);
	glTexCoord2d(50, 0);		glVertex2d(5000, -5000);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
//��������� ������������ ����
void DrawAxis()
{
	int len = 5;			//����� ������
	int cenOx = width / 2.0;	//����� ��� �� ��
	int cenOy = height / 2.0;	//����� ��� �� ��
	int lineShiftX = 14;	//����� ������� � ��
	int sepShiftX = 2;		//����� ������� �� ����� ����������
	int lineShiftY = 7;		//����� ������� � ��
	int sepShiftY = 3;		//����� ������� �� ����� ����������

	//���������� ������������ �������
	for (int i = 0; i < 100; i++)
	{
		glLineWidth(1);
		glColor3ub(255, 0, 0);
		//�� ��
		glBegin(GL_LINES);
		glVertex2i(cenOx + i * ind, cenOy - len);
		glVertex2i(cenOx + i * ind, cenOy + len);
		glEnd();
		glBegin(GL_LINES);
		glVertex2i(cenOx - i * ind, cenOy - len);
		glVertex2i(cenOx - i * ind, cenOy + len);
		glEnd();

		//�� ��
		glBegin(GL_LINES);
		glVertex2i(cenOx - len, cenOy + i * ind);
		glVertex2i(cenOx + len, cenOy + i * ind);
		glEnd();
		glBegin(GL_LINES);
		glVertex2i(cenOx - len, cenOy - i * ind);
		glVertex2i(cenOx + len, cenOy - i * ind);
		glEnd();


		//������� ������� � ������������ ����
		glColor3ub(0, 0, 0);
		char dest[10];
		double num = (double)i * zoom;

		//�������������� ����� � ������
		sprintf_s(dest, "%0.2lf", num);
		string out = string(dest);

		//�� ��� ��
		glRasterPos2i(cenOx + i * ind + sepShiftX, cenOy - lineShiftX);
		for (auto a : out)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, a);
		glRasterPos2i(cenOx - i * ind + sepShiftX, cenOy - lineShiftX);
		for (auto a : out)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, a);

		//�� ��� ��
		if (i != 0)
		{
			glRasterPos2i(cenOx + lineShiftY, cenOy + i * ind - sepShiftY);
			for (auto a : out)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, a);
			glRasterPos2i(cenOx + lineShiftY, cenOy - i * ind - sepShiftY);
			for (auto a : out)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, a);
		}
	}

	//���������� ������������ ���
	glLineWidth(2);
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(-5000, cenOy);
	glVertex2i(5000, cenOy);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(cenOx, -5000);
	glVertex2i(cenOx, 5000);
	glEnd();
}
//������ ��������� ��������� �������
void PrintCoord(point pos)
{
	//������� ������� � ��������� �������
	char destX[10];
	char destY[10];
	realPoint rlPt = realPoint(pos);

	//�������������� ����� � ������
	sprintf_s(destX, "%0.2lf", rlPt.x);
	sprintf_s(destY, "%0.2lf", rlPt.y);
	string outX = "x = " + string(destX);
	string outY = "y = " + string(destY);

	//����� ���������
	glColor3ub(0, 0, 0);
	glRasterPos2i(pos.x + 12, pos.y + 2);
	for (auto a : outX)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, a);
	glRasterPos2i(pos.x + 12, pos.y - 10);
	for (auto a : outY)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, a);
	glutPostRedisplay();
}
//������ ������� �������� �������
void PrintM()
{
	//������ ������� �������� �������
	char dest[10];
	sprintf_s(dest, "%i", m);
	string out = "m = " + string(dest);
	glRasterPos2i(10, height - 10);
	for (auto a : out)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, a);
}
//������������ ������� ����������(true - ���� ������ ���������� �����������;
//								  false - ���� ������������ ����� ��� ����������)
bool SetParameters()
{
	//���� ����� ����������� ����� ������ ���������� ������� ������
	if (n < m + 1)
		return false;

	//�������� ������ ����������
	vecParameter.clear();

	//������������ ������ ����������
	for (int i = 0; i < m + 1; i++)
		vecParameter.push_back(0);
	for (int i = 0; i < n - (m + 1); i++)
		vecParameter.push_back(i + 1);
	for (int i = n - m; i < n + 1; i++)
		vecParameter.push_back(n - m);
}
//���������� �������� �������
double OneBasicFunc(int i, double u)
{
	double N[30];
	int p = vecParameter.size() - 1;
	if ((i == 0 && u == vecParameter[0]) ||
		(i == p - m - 1 && u == vecParameter[p]))
		return 1.;

	if (u < vecParameter[i] || u >= vecParameter[i + m + 1])
		return 0.;

	for (int j = 0; j <= m; j++)
		if (u >= vecParameter[i + j] && u < vecParameter[i + j + 1])
			N[j] = 1.;
		else
			N[j] = 0.;

	for (int k = 1; k <= m; k++)
	{
		double saved;
		if (N[0] == 0.)
			saved = 0.;
		else
			saved = ((u - vecParameter[i])*N[0]) / (vecParameter[i + k] - vecParameter[i]);

		for (int j = 0; j < m - k + 1; j++)
		{
			double Uleft = vecParameter[i + j + 1];
			double Uright = vecParameter[i + j + k + 1];
			if (N[j + 1] == 0.)
			{
				N[j] = saved;
				saved = 0.;
			}
			else
			{
				double temp = N[j + 1] / (Uright - Uleft);
				N[j] = saved + (Uright - u)*temp;
				saved = (u - Uleft)*temp;
			}
		}
	}
	return N[0];
}
//���������� NURBS �������
void NURBSspline()
{
	//���� ������������ ����������� ��������� �����
	if (SetParameters())
	{
		//�������� ���������� ����� ��������
		NURBS.clear();

		//����� ����� � ���������� �������
		int num = n * 20;

		//��� �� ������� ����������
		double h = abs(vecParameter[0] - vecParameter[n + m - 1]) / (double)num;
		//��������� ���������� �������
		for (int k = 0; k < num + 1; k++)
		{
			double u = vecParameter[0] + k * h;
			double x = 0.;
			double y = 0.;
			double w = 0.;
			if (k == num)
				u = vecParameter[vecParameter.size() - 1];

			//���������� ��������� �������
			for (int i = 0; i < n; i++)
			{
				//���������� ������� �������
				double Nim = OneBasicFunc(i, u);
				w += vecRealPoint[i].weight * Nim;
				x += vecRealPoint[i].weight * vecRealPoint[i].x * Nim;
				y += vecRealPoint[i].weight * vecRealPoint[i].y * Nim;
			}
			NURBS.push_back(realPoint(x / w, y / w));
		}
	}
}
//��������� NURBS �������
void DrawNURBSspline()
{
	point pt;

	//��������� �������
	glColor3ub(255, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < NURBS.size(); i++)
	{
		//������������� ���������� �������� ����� � ��������
		pt = NURBS[i].getPoint();
		//����������
		glVertex2i(pt.x, pt.y);
	}
	glEnd();
}
//��������� ����� � ������
void AddPoint(point _point)
{
	//�������� � ������ ���������� �������� �����
	vecRealPoint.push_back(realPoint(_point));

	//��������� ����� ������
	n++;

	//����������� ������
	NURBSspline();
}
//��������� ����������� �������
void DrawScrap()
{
	point pt;

	//��������� �������
	glColor3ub(226, 192, 226);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < vecRealPoint.size(); i++)
	{
		//������������� ���������� �������� ����� � ��������
		pt = vecRealPoint[i].getPoint();
		//����������
		glVertex2i(pt.x, pt.y);
	}
	glEnd();

	//��������� ����������� �����
	for (int i = 0; i < vecRealPoint.size(); i++)
	{
		glPointSize(5);
		glColor3ub(98, 0, 226);
		glBegin(GL_POINTS);
		//������������� ���������� �������� ����� � ��������
		pt = vecRealPoint[i].getPoint();
		//����������
		glVertex2i(pt.x, pt.y);
		glEnd();

		//���������� ��� �����
		if (visibleWeight)
		{
			char dest[10];
			sprintf_s(dest, "%0.2lf", vecRealPoint[i].weight);
			string out = "w = " + string(dest);
			glColor3ub(0, 0, 0);
			glRasterPos2i(pt.x - 10, pt.y + 5);
			for (auto a : out)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, a);
		}
	}

	//���� ���������� �������� �����
	//�������� �� ������ ������
	if (activePoint != -1)
	{
		glPointSize(6);
		glColor3ub(255, 201, 14);
		glBegin(GL_POINTS);
		//������������� ���������� �������� ����� � ��������
		pt = vecRealPoint[activePoint].getPoint();
		//����������
		glVertex2i(pt.x, pt.y);
		glEnd();
	}
}
//������� �������� �����
bool LightPoint(point pos)
{
	point ptCrd;
	int area = 7;
	for (int i = 0; i < vecRealPoint.size(); i++)
	{
		ptCrd = vecRealPoint[i].getPoint();
		//���� ���������� ������� �������� � ������� ���������� �����-������ �����
		if (pos.y < ptCrd.y + area && pos.y > ptCrd.y - area &&
			pos.x < ptCrd.x + area && pos.x > ptCrd.x - area)
		{
			activePoint = i;
			return true;
		}
	}
	//�������� ����� ���
	activePoint = -1;
	return false;
}
//�������� ���������� �����
void ChangePoint(point _point)
{
	//���� ���������� �������� �����
	if (activePoint != -1)
	{
		//�������� ���������� �����
		double weight = vecRealPoint[activePoint].weight;
		vecRealPoint[activePoint] = realPoint(_point);
		vecRealPoint[activePoint].weight = weight;
	}
	//����������� ������
	NURBSspline();
}
