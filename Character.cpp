#include "Character.h"
#include "GL/freeglut.h"
#include "bmpfuncs.h"

Character::Character()
{
	position = Vec3(0, 0, 0);
	rotation = Vec3(0, 0, 0);
	scale = Vec3(1, 1, 1);

	_weapon = new Weapon(Vec3(0, 5, -1), Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(6, 0, 0));
}

Character::Character(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, double rad, double h, double ms)
{
	Init(filename, pos, ro, s, rad, h, ms);
}

Character::~Character()
{

}

void Character::Init(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, double rad, double h, double ms) {
	Object::Init(pos, ro, s, rad);
	_moveSpeed = ms;
	_curHealth = h;
	_maxHealth = h;

	_weapon = new Weapon(Vec3(0, 1, -0.2), ro, Vec3(0, 0, 0), Vec3(1.3, 0, 0));
	_childObjects.push_back(_weapon);

	_animator = new Animator(IDLE);
	InitAnimation();

	InitTexture(filename);
}

void Character::Update(double dt)
{
	Move(dt);
	_weapon->Update(dt);
	PlayAnimation(dt);
}

void Character::Render()
{
	Object::Render();

	for (auto b : _weapon->_bullets)
	{
		b->Render();
	}
}

void Character::MinimapRender(float red, float green, float blue, float size)
{
	glPushMatrix();

	SetTransform();

	GLfloat emission[] = { red, green, blue, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);

	glColor3f(1, 1, 1);
	glTranslatef(0, 1.6 + size, 0);

	double rad = size;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) 
	{ 
		double angle = i * 3.141592 / 180;
		double x = rad * cos(angle);
		double y = rad * sin(angle);
		glVertex3f(x, 0, y); 
	}
	glEnd();

	GLfloat clearEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, clearEmission);

	glPopMatrix();
}

void Character::OnCollision(CollisonLayer layer, bool isEnter)
{
	if (layer == BULLET)
		OnDamage();
}

void Character::Move(double dt)
{
	position += _moveDirection * dt;
}

void Character::OnDamage()
{
	_curHealth -= 1;

	if (_curHealth <= 0)
	{
		OnDie();
	}
}

void Character::OnDie()
{
	isActive = false;
}

void Character::PlayAnimation(double dt)
{
	AnimationState* curAnim = _animator->_states[_animator->_curState];

	if (curAnim->frames.size() == curAnim->_curFrame && !curAnim->_isLoop) return;

	int idx = curAnim->_curFrame % curAnim->frames.size();
	_animator->_lerpAlpha += dt * curAnim->_speed * curAnim->frames[idx]->_duration;
	double alpha = sin(_animator->_lerpAlpha) * 0.5 + 0.5;

	for (int i = 0; i <_faces.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_faces[i]->_vertNormals[j] = curAnim->frames[idx]->_faces[i]->_vertNormals[j] * (1.0 - alpha) + curAnim->frames[(idx + 1) % curAnim->frames.size()]->_faces[i]->_vertNormals[j] * alpha;
			_faces[i]->_vertices[j] = curAnim->frames[idx]->_faces[i]->_vertices[j] * (1.0 - alpha) + curAnim->frames[(idx + 1) % curAnim->frames.size()]->_faces[i]->_vertices[j] * alpha;
		}
	}

	if (_animator->_lerpAlpha >= 90 * 3.14 / 180)
	{
		curAnim->_curFrame++;
		_animator->_lerpAlpha = -90 * 3.14 / 180;
	}
}

void Character::InitAnimation()
{
	Frame* curFrame = _animator->_states[_animator->_curState]->frames[0];
	int index = 0;

	for (auto f : curFrame->_faces)
	{
		_faces.push_back(new Face(index++, f->_vertices[0], f->_vertices[1], f->_vertices[2], f->_uvs[0], f->_uvs[1], f->_uvs[2], f->_vertNormals[0], f->_vertNormals[1], f->_vertNormals[2]));
	}
	ComputeNormal();
}

void Character::InitTexture(const char* filename)
{
	useTexture = true;
	_texName = new GLuint();
	int imgWidth, imgHeight, channels;
	glGenTextures(1, _texName);
	glBindTexture(GL_TEXTURE_2D, *_texName);

	uchar* img = readImageData(filename, &imgWidth, &imgHeight, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}