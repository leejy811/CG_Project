#include "Character.h"
#include "GL/freeglut.h"

Character::Character()
{
	
}

Character::Character(const char* filename)
{
	LoadObject(filename);
	position = Vec3(0, 0, 0);
	rotation = Vec3(0, 0, 0);
	scale = Vec3(1, 1, 1);

	_weapon = new Weapon();
}

Character::Character(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, double rad, double h, double ms)
{
	LoadObject(filename);
	Init(pos, ro, s, rad, h, ms);

	_weapon = new Weapon();
	_childObjects.push_back(_weapon);
}

Character::~Character()
{

}

void Character::Init(Vec3 pos, Vec3 ro, Vec3 s, double rad, double h, double ms) {
	Object::Init(pos, ro, s, rad);
	_moveSpeed = ms;
	_curHealth = h;
	_maxHealth = h;
}

void Character::Update(double dt)
{
	Move(dt);
	_weapon->Update(dt);
}

void Character::Render()
{
	Object::Render();

	for (auto b : _weapon->_bullets)
	{
		b->Render();
	}
}

void Character::MinimapRender(float red, float green, float blue, float size)
{
	glPushMatrix();

	SetTransform();

	GLfloat emission[] = { red, green, blue, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);

	glColor3f(1, 1, 1);
	glTranslatef(0, size, 0);

	double rad = size;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) 
	{ 
		double angle = i * 3.141592 / 180;
		double x = rad * cos(angle);
		double y = rad * sin(angle);
		glVertex3f(x, 0, y); 
	}
	glEnd();

	GLfloat clearEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, clearEmission);

	glPopMatrix();
}

void Character::OnCollision(CollisonLayer layer, bool isEnter)
{
	if (layer == BULLET)
		OnDamage();
}

void Character::Move(double dt)
{
	position += _moveDirection * dt;
}

void Character::OnDamage()
{
	_curHealth -= 1;

	if (_curHealth <= 0)
	{
		OnDie();
	}
}

void Character::OnDie()
{
	isActive = false;
}