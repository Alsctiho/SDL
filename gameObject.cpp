#include "game.h"


//class Paddle
Paddle::Paddle()
{
    mx = 0.0f;
    my = 0.0f;
    direction = 0;
}

Paddle::Paddle(float x, float y)
{
    setPos(x, y);
    direction = 0;
}

float Paddle::getX() const
{
    return mx;
}

float Paddle::getY() const
{
    return my;
}

int Paddle::getDirection() const
{
    return direction;
}

void Paddle::setPos(float x, float y)
{
    mx = x;
    my = y;
}

void Paddle::setY(float y)
{
    if(y < 65.0f)
        my = 65.0f;
    else if(y > 703.0f)
        my = 703.0f;
    else
        my = y;
}

void Paddle::setDirection(int dir)
{
    direction = dir;
}

//class Ball
Ball::Ball()
{
    mx = 0.0f;
    my = 0.0f;
    mVel.x = 0.0f;
    mVel.y = 0.0f;
    render = new SDL_Rect;
}

Ball::Ball(float px, float py, float vx, float vy)
{ 
    setPos(px, py);
    setVel(vx, vy);
    render = new SDL_Rect;
}

Ball::~Ball()
{
    delete render;
    render = nullptr;
}

float Ball::getPosX() const{ return mx; }
float Ball::getPosY() const{ return my; }

Vector2 Ball::getVel() const{ return mVel; }
float Ball::getVelX() const{ return mVel.x; }
float Ball::getVelY() const{ return mVel.y; }
SDL_Rect* Ball::getRenderObject() const{ return render;}

void Ball::setPos(float x, float y){ mx = x; my = y; }
void Ball::setVel(float x, float y){ mVel = {x , y}; }
void Ball::setVelX(float x){ setVel(x, mVel.y); }
void Ball::setVelY(float y){ setVel(mVel.x, y); }

void Ball::renderBall(SDL_Renderer* mRenderer)
{
    SDL_RenderFillRect(mRenderer, getRenderObject());
}
