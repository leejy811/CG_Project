#include "Enemy.h"
#include "GameManager.h"
#include <GL/freeglut.h>

Enemy::Enemy()
{
	position = Vec3(0, 0, 0);
	rotation = Vec3(0, 0, 0);
	scale = Vec3(1, 1, 1);

	_weapon = new Weapon();
	_childObjects.push_back(_weapon);
}

Enemy::Enemy(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, Character& tar, double rad, double h, double ms)
{
	Init(filename, pos, ro, s, tar, rad, h, ms);
}

Enemy::~Enemy()
{

}

void Enemy::Init(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, Character& tar, double rad, double h, double ms) {
	Character::Init(filename, pos, ro, s, rad, h, ms);
	isActive = false;
	_target = &tar;
}

void Enemy::Update(double dt)
{
	if (!isActive) return;

	UpdateMove();
	AutoShoot(dt);

	Character::Update(dt);
}

void Enemy::Render()
{
	if (!isActive) return;

	Character::Render();
}

void Enemy::MinimapRender(float red, float green, float blue, float size)
{
	Character::MinimapRender(red, green, blue, size);
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

void Enemy::OnDamage()
{
	Character::OnDamage();
}

void Enemy::OnDie()
{
	Character::OnDie();
	GameManager::GetInstance()->SetCurEnemyCount();
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

void Enemy::AutoShoot(double dt)
{
	int time = glutGet(GLUT_ELAPSED_TIME);

	if (time - _curShootTime > _shootCoolTime * (1.0 / dt) * DELTA_TIME)
	{
		_curShootTime = time;
		_weapon->Shoot(position, _target->position - position, true);
	}
}