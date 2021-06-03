#include "game.h"
#include <iostream>
using namespace std;

//class Paddle
Paddle::Paddle(float x, float y)
{
    setPos(x, y);
    direction = 0;
    mThickness = 15;
    mPaddleH = 100.0f;
    mRect = new SDL_Rect;
    mRect->x = static_cast<int>(mThickness);
    mRect->y = 0;
    mRect->w = mThickness;
    mRect->h = static_cast<int>(mPaddleH);
}

Paddle::~Paddle()
{
    delete mRect;
    mRect = nullptr;
}

float Paddle::getX() const{ return mpx; }
float Paddle::getY() const{ return mpy; }
int Paddle::getDirection() const{ return direction; }

void Paddle::setPos(float x, float y)
{
    mpx = x;
    mpy = y;
}

void Paddle::setY(float y)
{
    if(y < 65.0f)
        mpy = 65.0f;
    else if(y > 703.0f)
        mpy = 703.0f;
    else
        mpy = y;
}

void Paddle::setDirection(int dir){ direction = dir; }

void Paddle::updateRenderObject()
{
    mRect->y = static_cast<int>(mpy - mPaddleH/2);
}

void Paddle::renderPaddle(SDL_Renderer* renderer)
{
    updateRenderObject();
    SDL_RenderFillRect(renderer, mRect);
}

//--------------------------------------------------------------
//class Ball
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
