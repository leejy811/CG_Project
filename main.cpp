#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "GameManager.h"
#include "bmpfuncs.h"

GameManager* GM = new GameManager();
float zoom = 15.0f;
float rotx = 0;
float roty = 0.001f;
float tx = 0;
float ty = 0;
int lastx = 0;
int lasty = 0;
unsigned char Buttons[3] = { 0 };

double curTime;
double prevTime;
double frameTime = 20;
double slowDeltaTime = 1;
double fastDeltaTime = 5;

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

	curTime = glutGet(GLUT_ELAPSED_TIME);
	if (curTime - prevTime > frameTime)
	{
		int dt = isMove ? fastDeltaTime : slowDeltaTime;
		prevTime = curTime;

		GM->Update(dt);
		glutPostRedisplay();
	}
}

void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)width / (float)height, 1, 2000);
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

	int diffx = x - lastx;
	int diffy = y - lasty;
	lastx = x;
	lasty = y;

	if (Buttons[2])
	{
		zoom -= (float)0.05f * diffx;
	}
	else if (Buttons[0])
	{
		rotx += (float)0.5f * diffy;
		roty += (float)0.5f * diffx;
	}
	else if (Buttons[1])
	{
		tx += (float)0.05f * diffx;
		ty -= (float)0.05f * diffy;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	int mouseX = x - WIDTH / 2;
	int mouseY = (HEIGHT - y) - HEIGHT / 2;
	if (button == GLUT_LEFT_BUTTON)
		GM->HandleMouseInput(mouseX, mouseY, MOUSE_CLICK, state);

	lastx = x;
	lasty = y;
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		Buttons[0] = ((GLUT_DOWN == state) ? 1 : 0);
		break;
	case GLUT_MIDDLE_BUTTON:
		Buttons[1] = ((GLUT_DOWN == state) ? 1 : 0);
		break;
	case GLUT_RIGHT_BUTTON:
		Buttons[2] = ((GLUT_DOWN == state) ? 1 : 0);
		break;
	default:
		break;
	}
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
	glutCreateWindow("My First GL Program");
 
	//glutGameModeString("800x600:32");

	//if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
	//	glutEnterGameMode();
	//else
	//{
	//	printf("The select mode is not available\n");
	//	exit(1);
	//}

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