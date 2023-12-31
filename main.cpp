﻿#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "GameManager.h"
#include "bmpfuncs.h"

GameManager* GM = GameManager::GetInstance();

double prevTime;
double slowDeltaTime = DELTA_TIME;
double fastDeltaTime = DELTA_TIME * 3;

bool isMove = false;

void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	GLfloat ambient_Sun[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuse_Sun[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular_Sun[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_Sun);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_Sun);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_Sun);
	glMaterialf(GL_FRONT, GL_SHININESS, 64);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	printf("----------------------------------------------------------------\n");
	printf("-------------12191806 이주용 컴퓨터 그래픽스 프로젝트-----------\n");
	printf("조작법 - WASD, 방향키 : 이동 / 좌클릭 : 발사 / 마우스 위치 : 조준\n");
	printf("-----------------------------------------------------------------\n");
	GM->Init();
}

void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GM->Render();

	glFlush();
	glutSwapBuffers();
}

void idle(void) 
{
	ShowCursor(false);

	double curTime = glutGet(GLUT_ELAPSED_TIME);
	if (curTime - prevTime > DELTA_TIME * 1000)
	{
		prevTime = curTime;

		double dt = isMove ? fastDeltaTime : slowDeltaTime;
		GM->Update(dt);
		glutPostRedisplay();
	}
}

void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)width / (float)height, 1, 500);
	glMatrixMode(GL_MODELVIEW);
}

void keyboardDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'A':
	case 'a':
	case 'D':
	case 'd':
	case 'W':
	case 'w':
	case 'S':
	case 's':
		isMove = true;
		break;
	}

	GM->HandleKeyInput(key, KEY_DOWN);
}

void keyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'A':
	case 'a':
	case 'D':
	case 'd':
	case 'W':
	case 'w':
	case 'S':
	case 's':
		isMove = false;
		break;
	}

	GM->HandleKeyInput(key, KEY_UP);
}

void specialKeyboardDown(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT:
	case GLUT_KEY_DOWN:
	case GLUT_KEY_UP:
		isMove = true;
		break;
	}

	GM->HandleSpecialInput(key, KEY_DOWN);
}

void specialKeyboardUp(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT:
	case GLUT_KEY_DOWN:
	case GLUT_KEY_UP:
		isMove = false;
		break;
	}

	GM->HandleSpecialInput(key, KEY_UP);
}


void Motion(int x, int y)
{
	int mouseX = x - WIDTH / 2;
	int mouseY = (HEIGHT - y) - HEIGHT / 2;
	GM->HandleMouseInput(mouseX, mouseY, MOUSE_MOTION, -1);
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	int mouseX = x - WIDTH / 2;
	int mouseY = (HEIGHT - y) - HEIGHT / 2;
	if (button == GLUT_LEFT_BUTTON)
		GM->HandleMouseInput(mouseX, mouseY, MOUSE_CLICK, state);
	glutPostRedisplay();
}

void PassiveMotion(int x, int y)
{
	int mouseX = x - WIDTH / 2;
	int mouseY = (HEIGHT - y) - HEIGHT / 2;
	GM->HandleMouseInput(mouseX, mouseY, MOUSE_MOTION, -1);
}

int main(int argc, char** argv)
{
	// init Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12191806 CG Project");

	init();
	
	//Callback
	glutReshapeFunc(resize);
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(specialKeyboardDown);
	glutSpecialUpFunc(specialKeyboardUp);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutPassiveMotionFunc(PassiveMotion);
	glutIdleFunc(idle);

	//Main Loop
	glutMainLoop();
	return 0;
}