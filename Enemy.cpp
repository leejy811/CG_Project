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
	_childObjects.push_back(_weapon);
}

Enemy::Enemy(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, Character& tar)
{
	LoadObject(filename);
	position = pos;
	rotation = ro;
	scale = s;
	_target = &tar;

	_moveSpeed = 1;
	_weapon = new Weapon();
	_childObjects.push_back(_weapon);
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	if (!isActive) return;

	UpdateMove();
	Move();
	_weapon->Update();
}

void Enemy::Render()
{
	if (!isActive) return;

	Character::Render();

	for (auto b : _weapon->_bullets)
	{
		b->Render();
	}
}

void Enemy::UpdateMove()
{
	_moveDirection = _target->position - position;
	_moveDirection.normalize();
	_moveDirection *= _moveSpeed;

	double angle = (atan2(_moveDirection.x(), _moveDirection.z()) / 3.141592) * 180;
	rotation = Vec3(0, angle, 0);
}