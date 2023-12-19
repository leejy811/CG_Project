#include "Weapon.h"

Weapon::Weapon()
{
	position = Vec3(0, 0, 0);
	rotation = Vec3(0, 0, 0);
	scale = Vec3(1, 1, 1);
	_bulletOffset = Vec3(0, 0, 0);
}

Weapon::Weapon(Vec3 pos, Vec3 ro, Vec3 s, Vec3 off)
{
	position = pos;
	rotation = ro;
	scale = s;
	_bulletOffset = off;
}

Weapon::~Weapon()
{
	_bullets.clear();
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
		if (!b->isActive) {
			b->Init(playerPos + position + aim * _bulletOffset.x(), Vec3(0, 0, 0), Vec3(0.1, 0.1, 0.1), aim, 0.5);
			b->isActive = true;
			return;
		}
	}
	_bullets.push_back(new Bullet(playerPos + position + aim * _bulletOffset.x(), Vec3(0, 0, 0), Vec3(0.1, 0.1, 0.1),  aim, 0.5));
}