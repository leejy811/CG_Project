#include "Player.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "GL/freeglut.h"

Player::Player()
{
    position = Vec3(0, 0, 0);
    rotation = Vec3(0, 0, 0);
    scale = Vec3(1, 1, 1);

    _weapon = new Weapon();
    _weapon->ammo = 30;
    _childObjects.push_back(_weapon);
}

Player::Player(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, double rad, double h, double ms)
{
    Init(filename, pos, ro, s, rad, h, ms);
    _weapon->ammo = 50;
}

Player::~Player()
{
	
}

void Player::Init(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, double rad, double h, double ms) {
    Character::Init(filename, pos, ro, s, rad, h, ms);
}

void Player::Update(double dt)
{
    if (!isActive)
    {
        GameManager::GetInstance()->ResetGame();
    }
    Character::Update(dt);
}

void Player::Render()
{
    if (!isActive) return;
	Character::Render();
}

void Player::MinimapRender(float red, float green, float blue, float size)
{
    Character::MinimapRender(red, green, blue, size);

    glPushMatrix();

    SetTransform();

    glTranslatef(0, 1.6, 0);

    GLfloat emission[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(-1000.0f, 0.0f, -1000.0f);
    glVertex3f(-1000.0f, 0.0f, 1000.0f);
    glVertex3f(1000.0f, 0.0f, 1000.0f);
    glVertex3f(1000.0f, 0.0f, -1000.0f);
    glEnd();

    GLfloat clearEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_EMISSION, clearEmission);

    glPopMatrix();
}

void Player::OnCollision(CollisonLayer layer, bool isEnter)
{
    if (!isActive) return;
    Character::OnCollision(layer, isEnter);
}

void Player::HandleInput(unsigned char key, int state)
{
    if (_isDie) return;

    if (state == KEY_DOWN)     //Down
    {
        switch (key)
        {
        case 'A':
        case 'a':
            if ((_moveDirection + Vec3(-1, 0, 0)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(-1, 0, 0);
            _animator->ChangeState(MOVE);
            SoundManager::GetInstance()->PlaySoundToEnum(WALK_E);
            break;
        case 'D':
        case 'd':
            if ((_moveDirection + Vec3(1, 0, 0)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(1, 0, 0);
            _animator->ChangeState(MOVE);
            SoundManager::GetInstance()->PlaySoundToEnum(WALK_E);
            break;
        case 'W':
        case 'w':
            if ((_moveDirection + Vec3(0, 0, -1)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(0, 0, -1);
            _animator->ChangeState(MOVE);
            SoundManager::GetInstance()->PlaySoundToEnum(WALK_E);
            break;
        case 'S':
        case 's':
            if ((_moveDirection + Vec3(0, 0, 1)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(0, 0, 1);
            _animator->ChangeState(MOVE);
            SoundManager::GetInstance()->PlaySoundToEnum(WALK_E);
            break;
        }
    }
    else if (state == KEY_UP)    //Up
    {
        switch (key)
        {
        case 'A':
        case 'a':
        case 'D':
        case 'd':
            _moveDirection = Vec3(0, 0, _moveDirection.z());
            _animator->ChangeState(IDLE);
            break;
        case 'S':
        case 's':
        case 'W':
        case 'w':
            _moveDirection = Vec3(_moveDirection.x(), 0, 0);
            _animator->ChangeState(IDLE);
            break;
        }
    }
}

void Player::HandleSpecialInput(int  key, int state)
{
    if (_isDie) return;

    if (state == KEY_DOWN)     //Down
    {
        switch (key)
        {
        case GLUT_KEY_LEFT:
            if ((_moveDirection + Vec3(-1, 0, 0)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(-1, 0, 0);
            _animator->ChangeState(MOVE);
            SoundManager::GetInstance()->PlaySoundToEnum(WALK_E);
            break;
        case GLUT_KEY_RIGHT:
            if ((_moveDirection + Vec3(1, 0, 0)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(1, 0, 0);
            _animator->ChangeState(MOVE);
            SoundManager::GetInstance()->PlaySoundToEnum(WALK_E);
            break;
        case GLUT_KEY_DOWN:
            if ((_moveDirection + Vec3(0, 0, -1)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(0, 0, -1);
            _animator->ChangeState(MOVE);
            SoundManager::GetInstance()->PlaySoundToEnum(WALK_E);
            break;
        case GLUT_KEY_UP:
            if ((_moveDirection + Vec3(0, 0, 1)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(0, 0, 1);
            _animator->ChangeState(MOVE);
            SoundManager::GetInstance()->PlaySoundToEnum(WALK_E);
            break;
        }
    }
    else if (state == KEY_UP)    //Up
    {
        switch (key)
        {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            _moveDirection = Vec3(0, 0, _moveDirection.z());
            _animator->ChangeState(IDLE);
            break;
        case GLUT_KEY_DOWN:
        case GLUT_KEY_UP:
            _moveDirection = Vec3(_moveDirection.x(), 0, 0);
            _animator->ChangeState(IDLE);
            break;
        }
    }
    glutPostRedisplay();
}

void Player::HandleMouseInput(int x, int y, int state, int clickState)
{
    if (_isDie) return;

    rotation = Vec3(0, (atan2(y, x) / 3.141592) * 180 + 90, 0);
    if (state == MOUSE_MOTION)
    {
        
    }
    else if (state == MOUSE_CLICK)
    {
        if (clickState == GLUT_DOWN)
        {
            Vec3 aim = Vec3(cos(((atan2(y, x) / 3.141592) * 180) * -1 * (3.141592 / 180)), 0, sin(((atan2(y, x) / 3.141592) * 180) * -1 * (3.141592 / 180)));
            _weapon->Shoot(position, aim, false);
            SoundManager::GetInstance()->PlaySoundToEnum(SHOOT_E);
        }
    }
}