#include"GL/glut.h"
#include"iostream"
#include"math.h"
#include"stdlib.h"
using namespace std;

GLfloat pointsize = 1.0f;//�������ص��С
double pi = acos(-1.0);//����pi�Ĵ�С
float RGB[8][3] = //������ɫ����
{
	{0.5,0.5,0.5},//��ɫ0-45��
	{0,0,1},//��ɫ45-90��
	{0,0.5,0},//��ɫ90-135��
	{0,1,1},//����135-180��
	{1,0,0},//��ɫ180-225��
	{1,0,1},//��ɫ225-270��
	{1,1,0},//��ɫ270-315��
	{1,1,1}//��ɫ315-360��
};

void drawOneLine(GLint x1, GLint y1, GLint x2, GLint y2)//����Bresenham�㷨
{
	int x = x1;//��ʼx����
	int y = y1;//��ʼy����
	int dx = abs(x1 - x2);//��ʼ�����곤��
	int dy = abs(y1 - y2);//��ʼ�����곤��
	int sx = x2 - x1 > 0 ? 1 : -1;//�ж�x��������
	int sy = y2 - y1 > 0 ? 1 : -1;//�ж�y��������
	int flag = 0;
	int error = 2 * dy - dx;
	if (dy > dx)//Ҫʹ��dx��dy��
	{
		swap(dx, dy);//���򣬽���dx��dy
		flag = 1;
	}
	glPointSize(pointsize);//ָ��դ�����ص��ֱ��
	for (int i = 1; i < dx; i++)
	{
		glVertex2i(x, y);//ָ�����Ƹõ�
		if (error >= 0)
		{
			if (flag == 1)
				x = x + sx;
			else
				y = y + sy;
			error -= 2 * dx;
		}
		if (flag == 1)
			y = y + sy;
		else
			x = x + sx;
		error += 2 * dy;
	}

}

void display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);//�Ѵ������Ϊ��ǰ��ɫ
	glColor3f(1.0f, 1.0f, 1.0f);//������ɫΪ��ɫ
	glBegin(GL_POINTS);//��ʼ��ͼ����ӦglEnd()
	for (int n = 0; n < 360; n = n + 5) //ÿ��5�Ȼ���һ��ֱ��
	{
		int i = n / 45;//��Ϊ8����ɫ��ÿ��45��
		glColor3f(RGB[i][0], RGB[i][1], RGB[i][2]);//����ɫ������ѡȡ��ɫ
		drawOneLine(0, 0, (GLint)(10000 * cos(n / 180.0 * pi)), (GLint)(10000 * sin(n / 180.0 * pi)));
	}
	glEnd();//������ͼ����ӦglBegin()
	glFlush();//ǿ��ˢ�»��壬��֤��ͼ��ִ��
}

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);//��ʼ��GLUT��
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//����ͼ����ʾģʽ
	glutInitWindowPosition(100, 100);//�����ڴ��ڵ�����λ��
	glutInitWindowSize(600, 600);//���ô��ڴ�С
	glutCreateWindow("Bresenhamֱ�߹�դ���㷨"); //��������
	glClearColor(0.0, 0.0, 0.0, 0.0);//�����ɫ����
	glMatrixMode(GL_PROJECTION);//����͸��
	glLoadIdentity();//�ָ���ʼ����ϵ
	gluOrtho2D(-10000.0, 10000.0, -10000.0, 10000.0);//������ʾ����
	glutDisplayFunc(display);//����һ������
	glutMainLoop();//����GLUT�¼�����ѭ��
	system("pause");
	return 0;
}