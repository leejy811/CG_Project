#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(const char* filename)
{
	LoadObject(filename);
	position = Vec3(0, 0, 0);
	rotation = Vec3(0, 0, 0);
	scale = Vec3(1, 1, 1);

	_weapon = new Weapon();
}

Enemy::Enemy(const char* filename, Vec3 pos, Vec3 ro, Vec3 s)
{
	LoadObject(filename);
	position = pos;
	rotation = ro;
	scale = s;

	_weapon = new Weapon();
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{

}

void Enemy::Render()
{
	Object::Render();
}