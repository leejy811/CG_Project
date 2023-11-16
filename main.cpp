#include <gl/glut.h>
#include <stdio.h>

void init(void)
{
	/* ȭ���� �⺻������ dark blue ���� */
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

void draw(void)
{
	/* Teapot 1���� �׸��� �ӽ� ��ƾ */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f); /* ���ڸ� �ٲٸ� ���� ��ȭ */
	glutWireTeapot(0.5f); /* �����ڸ� �ϳ� �׸� */
	glFlush();
}

int main(int argc, char** argv)
{
	/* Window �ʱ�ȭ */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("My First GL Program");
	init(); // -> ����� �ʱ�ȭ �Լ�
	/* Callback �Լ� ���� */
	glutDisplayFunc(draw); /* draw() -> ���� �׸��� �Լ� */
	/* Looping ���� */
	glutMainLoop();
	return 0;
}