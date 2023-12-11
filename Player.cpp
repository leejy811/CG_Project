#include "Player.h"
#include "GL/freeglut.h"

Player::Player()
{
	
}

Player::Player(const char* filename)
{
    LoadObject(filename);
    position = Vec3(0, 0, 0);
    rotation = Vec3(0, 0, 0);
    scale = Vec3(1, 1, 1);

    _weapon = new Weapon();
    _childObjects.push_back(_weapon);
}

Player::Player(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, double rad, double h, double ms)
{
    LoadObject(filename);
    Init(pos, ro, s, rad, h, ms);
    _weapon = new Weapon();
    _childObjects.push_back(_weapon);
}

Player::~Player()
{
	
}

void Player::Init(Vec3 pos, Vec3 ro, Vec3 s, double rad, double h, double ms) {
    Character::Init(pos, ro, s, rad, h, ms);
}

void Player::Update(double dt)
{
    if (!isActive) return;
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
}

void Player::OnCollision(CollisonLayer layer, bool isEnter)
{
    if (!isActive) return;
    Character::OnCollision(layer, isEnter);
}

void Player::HandleInput(unsigned char key, int state)
{
    if (state == KEY_DOWN)     //Down
    {
        switch (key)
        {
        case 'A':
        case 'a':
            if ((_moveDirection + Vec3(-2, 0, 0)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(-2, 0, 0);
            break;
        case 'D':
        case 'd':
            if ((_moveDirection + Vec3(2, 0, 0)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(2, 0, 0);
            break;
        case 'W':
        case 'w':
            if ((_moveDirection + Vec3(0, 0, -2)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(0, 0, -2);
            break;
        case 'S':
        case 's':
            if ((_moveDirection + Vec3(0, 0, 2)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(0, 0, 2);
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
            break;
        case 'S':
        case 's':
        case 'W':
        case 'w':
            _moveDirection = Vec3(_moveDirection.x(), 0, 0);
            break;
        }
    }
}

void Player::HandleSpecialInput(int  key, int state)
{
    if (state == KEY_DOWN)     //Down
    {
        printf("%d Key Down\n", key);
        switch (key)
        {
        case GLUT_KEY_LEFT:
            if ((_moveDirection + Vec3(-1, 0, 0)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(-1, 0, 0);
            break;
        case GLUT_KEY_RIGHT:
            if ((_moveDirection + Vec3(1, 0, 0)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(1, 0, 0);
            break;
        case GLUT_KEY_DOWN:
            if ((_moveDirection + Vec3(0, 0, -1)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(0, 0, -1);
            break;
        case GLUT_KEY_UP:
            if ((_moveDirection + Vec3(0, 0, 1)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(0, 0, 1);
            break;
        }
    }
    else if (state == KEY_UP)    //Up
    {
        printf("%d Key Up\n", key);
        switch (key)
        {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            _moveDirection = Vec3(0, 0, _moveDirection.z());
            break;
        case GLUT_KEY_DOWN:
        case GLUT_KEY_UP:
            _moveDirection = Vec3(_moveDirection.x(), 0, 0);
            break;
        }
    }
    glutPostRedisplay();
}

void Player::HandleMouseInput(int x, int y, int state, int clickState)
{
    rotation = Vec3(0, (atan2(y, x) / 3.141592) * 180 + 90, 0);
    if (state == MOUSE_MOTION)
    {
        
    }
    else if (state == MOUSE_CLICK)
    {
        if (clickState == GLUT_DOWN)
        {
            Vec3 aim = Vec3(cos(((atan2(y, x) / 3.141592) * 180) * -1 * (3.141592 / 180)), 0, sin(((atan2(y, x) / 3.141592) * 180) * -1 * (3.141592 / 180)));
            _weapon->Shoot(position, aim);
        }
    }
}