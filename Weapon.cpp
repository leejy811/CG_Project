#include "Weapon.h"

Weapon::Weapon()
{
	position = Vec3(0, 0, 0);
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
	_bulletOffset = Vec3(0, 0, 0);
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

void Weapon::Update(double dt)
{
	for (auto b : _bullets)
	{
		b->Update(dt);
	}
}

void Weapon::Render()
{
	Object::Render();
}

void Weapon::Shoot(Vec3 playerPos, Vec3 aim, bool isAuto)
{
	if (!isAuto && ammo <= 0) return;

	ammo--;

	aim.normalize();
	for (auto b : _bullets) {
		if (b->isActive == false) {
			b->Init(playerPos + position + _bulletOffset, Vec3(0, 0, 0), Vec3(1, 1, 1), aim, 5);
			b->isActive = true;
			return;
		}
	}
	_bullets.push_back(new Bullet(playerPos + position + _bulletOffset, Vec3(0, 0, 0), Vec3(1, 1, 1), aim, 5));
}