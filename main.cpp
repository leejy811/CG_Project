#include <gl/glut.h>
#include <stdio.h>

void init(void)
{
	/* 화면의 기본색으로 dark blue 설정 */
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

void draw(void)
{
	/* Teapot 1개를 그리는 임시 루틴 */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f); /* 인자를 바꾸면 색이 변화 */
	glutWireTeapot(0.5f); /* 주전자를 하나 그림 */
	glFlush();
}

int main(int argc, char** argv)
{
	/* Window 초기화 */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("My First GL Program");
	init(); // -> 사용자 초기화 함수
	/* Callback 함수 정의 */
	glutDisplayFunc(draw); /* draw() -> 실제 그리기 함수 */
	/* Looping 시작 */
	glutMainLoop();
	return 0;
}