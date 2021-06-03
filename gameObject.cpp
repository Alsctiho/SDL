#include "game.h"
#include <iostream>
using namespace std;

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
    mpx = 0.0f;
    mpy = 0.0f;

    mVel.x = 0.0f;
    mVel.y = 0.0f;

    mRadius = 10.0f;
    mRect = new SDL_Rect;
    mRect->x = 0;
    mRect->y = 0;
    mRect->h = static_cast<int>(2 * mRadius);
    mRect->w = static_cast<int>(2 * mRadius);
}

Ball::Ball(float px, float py, float vx, float vy)
{ 
    setPos(px, py);
    setVel(vx, vy);
    mRadius = 10.0f;
    mRect = new SDL_Rect;
    mRect->x = 0;
    mRect->y = 0;
    mRect->h = static_cast<int>(2 * mRadius);
    mRect->w = static_cast<int>(2 * mRadius);
}

Ball::~Ball()
{
    delete mRect;
    mRect = nullptr;
}

float Ball::getPosX() const{ return mpx; }
float Ball::getPosY() const{ return mpy; }

Vector2 Ball::getVel() const{ return mVel; }
float Ball::getVelX() const{ return mVel.x; }
float Ball::getVelY() const{ return mVel.y; }
SDL_Rect* Ball::getRenderObject() const{ return mRect;}

void Ball::setPos(float x, float y){ mpx = x; mpy = y; }
void Ball::setVel(float x, float y){ mVel = {x , y}; }
void Ball::setVelX(float x){ setVel(x, mVel.y); }
void Ball::setVelY(float y){ setVel(mVel.x, y); }

void Ball::updateRenderObject()
{
    mRect->x = static_cast<int>(mpx - mRadius);
    mRect->y = static_cast<int>(mpy - mRadius);
}

void Ball::renderBall(SDL_Renderer* renderer)
{
    updateRenderObject();
    SDL_RenderFillRect(renderer, mRect);
}
