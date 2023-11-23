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
}

Player::Player(const char* filename, Vec3 pos, Vec3 ro, Vec3 s)
{
    LoadObject(filename);
    position = pos;
    rotation = ro;
    scale = s;

    _weapon = new Weapon();
}

Player::~Player()
{
	
}

void Player::Update()
{
    Move();
    _weapon->Update();
}

void Player::Render()
{
	Character::Render();
    _weapon->Render();
}

void Player::HandleInput(unsigned char key, int state)
{
    if (state == KEY_DOWN)     //Down
    {
        
    }
    else if (state == KEY_UP)    //Up
    {

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
            _weapon->Shoot(aim);
        }
    }
}