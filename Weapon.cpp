#include "Weapon.h"

Weapon::Weapon()
{
	position = Vec3(0, 50, 0);
	rotation = Vec3(0, 0, 0);
	scale = Vec3(1, 1, 1);
	_bulletOffset = Vec3(0, 0, 0);
}

Weapon::Weapon(const char* filename)
{
	LoadObject(filename);
	position = Vec3(0, 0, 0);
	rotation = Vec3(0, 0, 0);
	scale = Vec3(1, 1, 1);
}

Weapon::Weapon(const char* filename, Vec3 pos, Vec3 ro, Vec3 s)
{
	LoadObject(filename);
	position = pos;
	rotation = ro;
	scale = s;
}

Weapon::~Weapon()
{

}

void Weapon::Update()
{
	for (auto b : _bullets)
	{
		b->Update();
	}
}

void Weapon::Render()
{
	Object::Render();
}

void Weapon::Shoot(Vec3 playerPos, Vec3 aim)
{
	_bullets.push_back(new Bullet(playerPos + position + _bulletOffset, Vec3(0, 0, 0), Vec3(1, 1, 1), aim));
}