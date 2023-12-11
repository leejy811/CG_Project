#include "Bullet.h"
#include <GL/freeglut.h>

Bullet::Bullet()
{
	position = Vec3(0, 0, 0);
	rotation = Vec3(0, 0, 0);
	scale = Vec3(1, 1, 1);
}

Bullet::Bullet(Vec3 pos, Vec3 ro, Vec3 s, Vec3 target, double rad)
{
	Init(pos, ro, s, target, rad);
}

Bullet::~Bullet()
{

}

void Bullet::Init(Vec3 pos, Vec3 ro, Vec3 s, Vec3 target, double rad) {
	Object::Init(pos, ro, s, rad);
	targetVec = target;
}

void Bullet::Update(double dt)
{
	if (!isActive) return;

	position += targetVec * bulletSpeed * dt;
}

void Bullet::Render()
{
	if (!isActive) return;

	glPushMatrix();

	SetTransform();
	glutSolidSphere(5, 10, 10);

	glPopMatrix();
}

void Bullet::OnCollision(CollisonLayer layer, bool isEnter)
{
	if (!isActive) return;

	if (layer == CHARACTER)
	{
		isActive = false;
	}
}