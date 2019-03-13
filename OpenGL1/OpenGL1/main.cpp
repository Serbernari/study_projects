#include "header.h"

void Reshape(GLint w, GLint h)
{
	//�������� ������� ����
	width = w;
	height = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluOrtho2D(0.0, width, 0.0, height);
}
void Process_Mouse_Move(int x, int y)
{
	//��������� �������
	p = point((GLint)x, height - (GLint)y);

	//���������� ������������� �������� �����
	LightPoint(p);

	//���� ��������� �����������
	if (moving)
	{
		//��������� �����
		Shift = point(Shift.x + Shift2.x - p.x, Shift.y + Shift2.y - p.y);
		Shift2 = p;
	}

	//���� ��������� �������������� �����
	if (movingPoint)
	{
		//�������� �����
		ChangePoint(p);
	}
	glutPostRedisplay();
}
void Process_Mouse(int button, int state, int x, int y)
{
	if (state != GLUT_DOWN) return;

	//���������/���������� ����������� � ������� ����
	if (button == GLUT_RIGHT_BUTTON)
	{
		Shift2 = point((GLint)x, height - (GLint)y);
		moving = !moving;
	}
	//���������� ����� �����
	if (button == GLUT_LEFT_BUTTON)
	{
		curP = point((GLint)x, height - (GLint)y);
		AddPoint(curP);
	}
	//��������� ���������� �������������� �����
	if (button == GLUT_MIDDLE_BUTTON)
	{
		movingPoint = !movingPoint;
	}
}
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//���������� �����
	glPushMatrix();
	glTranslatef((GLfloat)Shift.x, (GLfloat)Shift.y, 0);
	DrawMesh();
	glPopMatrix();

	//���������� �������
	DrawScrap();

	//���������� ������
	DrawNURBSspline();

	//���������� ������������ ���
	glPushMatrix();
	glTranslatef((GLfloat)Shift.x, (GLfloat)Shift.y, 0);
	DrawAxis();
	glPopMatrix();

	//������ ������� �������� �������
	PrintM();

	//�������� ���������� ��������� �������
	PrintCoord(p);
	glutSwapBuffers();
}
void Process_Normal_Keys(unsigned char key, int x, int y)
{
	//��������� �������
	if (key == '+')
		if (zoom - 0.25 > 0)
			zoom -= 0.25;
	//��������� �������
	if (key == '-')
		zoom += 0.25;
	//��������� ������� �������� �������
	if (key == '8')
	{
		if (m < 25)
		{
			m++;
			//����������� ������
			NURBSspline();
		}
	}
	//��������� ������� �������� �������
	if (key == '2')
	{
		if (m > 1)
		{
			m--;
			//����������� ������
			NURBSspline();
		}
	}
	//����������� ����� ����������� �����
	if (key == 'w')
		visibleWeight = !visibleWeight;
	//���������� ���� �������� �����
	if (key == '7')
		if (activePoint != 0 && activePoint != -1)
		{
			vecRealPoint[activePoint].weight += 0.5;
			//����������� ������
			NURBSspline();
		}
	//���������� ���� �������� �����
	if (key == '1')
		if (activePoint != 0 && activePoint != -1)
		{
			vecRealPoint[activePoint].weight -= 0.5;
			//����������� ������
			NURBSspline();
		}

	glutPostRedisplay();
}
void Process_Special_Keys(int key, int x, int y)
{
	int localShift = 3;
	if (key == GLUT_KEY_UP)
		Shift.y -= localShift;
	if (key == GLUT_KEY_DOWN)
		Shift.y += localShift;
	if (key == GLUT_KEY_LEFT)
		Shift.x += localShift;
	if (key == GLUT_KEY_RIGHT)
		Shift.x -= localShift;
	glutPostRedisplay();
}
void Initialize()
{
	glClearColor(1.0, 1.0, 1.0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluOrtho2D(0.0, width, 0.0, height);

	//�������� ��������
	loadTexture();
}
void main(int argc, char *argv[])
{
	width = 800;
	height = 500;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("CG_RGR NURBS");
	Initialize();								//��������� ���������

	glutKeyboardFunc(Process_Normal_Keys);		//��������� ������ � ������ ascii
	glutSpecialFunc(Process_Special_Keys);		//��������� ��-ascii ������
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutMouseFunc(Process_Mouse);
	glutPassiveMotionFunc(Process_Mouse_Move);
	glutMainLoop();
}