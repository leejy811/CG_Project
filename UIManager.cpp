#include "UIManager.h"
#include "GameManager.h"
#include "GL/freeglut.h"

UIManager::UIManager()
{

}

UIManager::~UIManager()
{

}

void UIManager::Render()
{
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	DrawMouse(20);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

void UIManager::SetMousePositon(int x, int y)
{
	_mousePos = Vec3(x, y, 0);
}

void UIManager::DrawMouse(int mouseSize)
{
	glColor3f(1, 1, 1);
	glTranslatef(_mousePos.x(), _mousePos.y(), 0);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; ++i)
	{
		glVertex2f(mouseSize * cos(i * (3.14152 / 180)), mouseSize * sin(i * (3.14152 / 180)));
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; ++i)
	{
		glVertex2f(mouseSize * 0.2 * cos(i * (3.14152 / 180)), mouseSize * 0.2 * sin(i * (3.14152 / 180)));
	}
	glEnd();

	glColor3f(1, 1, 1);
	for (int i = 0; i < 4; i++)
	{
		glBegin(GL_LINES);
		glVertex2f((mouseSize - mouseSize / 3) * cos(90 * i * (3.14152 / 180)), (mouseSize - mouseSize / 3) * sin(90 * i * (3.14152 / 180)));
		glVertex2f((mouseSize + mouseSize / 3) * cos(90 * i * (3.14152 / 180)), (mouseSize + mouseSize / 3) * sin(90 * i * (3.14152 / 180)));
		glEnd();
	}
}