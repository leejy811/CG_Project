#include "Enemy.h"
#include <GL/freeglut.h>

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

Enemy::Enemy(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, Character& tar, double rad, double h, double ms)
{
	LoadObject(filename);
	Init(pos, ro, s, tar, rad, h, ms);
	_weapon = new Weapon();
	_childObjects.push_back(_weapon);
}

Enemy::~Enemy()
{

}

void Enemy::Init(Vec3 pos, Vec3 ro, Vec3 s, Character& tar, double rad, double h, double ms) {
	Character::Init(pos, ro, s, rad, h, ms);
	isActive = false;
	_target = &tar;
}

void Enemy::Update()
{
	if (!isActive) return;

	UpdateMove();
	AutoShoot();

	Character::Update();
}

void Enemy::Render()
{
	if (!isActive) return;

	Character::Render();
}

void Enemy::OnCollision(CollisonLayer layer, bool isEnter)
{
	if (!isActive) return;
	Character::OnCollision(layer, isEnter);

	if (layer == CHARACTER) {
		_moveDirection = Vec3(0, 0, 0);
		_isMove = !isEnter;
	}
}

void Enemy::UpdateMove()
{
	Vec3 tarDir = _target->position - position;
	double angle = (atan2(tarDir.x(), tarDir.z()) / 3.141592) * 180;
	rotation = Vec3(0, angle, 0);

	if (!_isMove) return;
	_moveDirection = tarDir;
	_moveDirection.normalize();
	_moveDirection *= _moveSpeed;
}

void Enemy::AutoShoot()
{
	int time = glutGet(GLUT_ELAPSED_TIME);

	if (time - _curShootTime > _shootCoolTime)
	{
		_curShootTime = time;
		_weapon->Shoot(position, _target->position - position);
	}
}