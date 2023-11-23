#include "Bullet.h"
#include <GL/freeglut.h>

Bullet::Bullet()
{
	position = Vec3(0, 0, 0);
	rotation = Vec3(0, 0, 0);
	scale = Vec3(1, 1, 1);
}

Bullet::Bullet(Vec3 pos, Vec3 ro, Vec3 s, Vec3 target)
{
	position = pos;
	rotation = ro;
	scale = s;
	targetVec = target;
}

Bullet::~Bullet()
{

}

void Bullet::Update()
{
	position += targetVec * bulletSpeed;
}

void Bullet::Render()
{
	glPushMatrix();

	SetTransform();
	glutSolidSphere(5, 10, 10);

	glPopMatrix();
}