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
	DrawStringInfo();
	DrawHealthBar(WIDTH / 20, HEIGHT / 60);

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
	glPushMatrix();
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
	glPopMatrix();
}

void UIManager::DrawStringInfo()
{
	glPushMatrix();

	glColor3f(1, 1, 1);
	glRasterPos3f(WIDTH / 3, HEIGHT * -0.4, 0);
	char str[50];
	sprintf(str, "Ammo : %d", GameManager::GetInstance()->GetPlayer()->_weapon->ammo);
	for (unsigned int i = 0; i < strlen(str); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}

	glPopMatrix();
}

void UIManager::DrawHealthBar(int width, int height)
{
	glPushMatrix();
	glTranslatef(-width / 2, HEIGHT / 8, 0);

	double healthRatio = GameManager::GetInstance()->GetPlayer()->_curHealth / GameManager::GetInstance()->GetPlayer()->_maxHealth;
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(0, -height);
	glVertex2f(0, 0);
	glVertex2f(width * healthRatio, 0);
	glVertex2f(width * healthRatio, -height);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex2f(0, -height);
	glVertex2f(0, 0);
	glVertex2f(width, 0);
	glVertex2f(width, -height);
	glEnd();

	glPopMatrix();
}