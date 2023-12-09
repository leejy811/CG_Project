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

Enemy::Enemy(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, Character& tar, double rad, double h)
{
	LoadObject(filename);
	position = pos;
	rotation = ro;
	scale = s;
	collisionRad = rad;
	isActive = false;

	_target = &tar;
	_health = h;

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

	Character::Update();
}

void Enemy::Render()
{
	if (!isActive) return;

	Character::Render();
}

void Enemy::OnCollision(CollisonLayer layer)
{
	if (!isActive) return;
	Character::OnCollision(layer);
}

void Enemy::UpdateMove()
{
	_moveDirection = _target->position - position;
	_moveDirection.normalize();
	_moveDirection *= _moveSpeed;

	double angle = (atan2(_moveDirection.x(), _moveDirection.z()) / 3.141592) * 180;
	rotation = Vec3(0, angle, 0);
}