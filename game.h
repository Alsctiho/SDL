#pragma once
#include "include/SDL2/SDL.h"

const int thickness = 15;
const float paddleH = 100.0f;

struct Vector2
{
    float x;
    float y;
};

class Paddle
{
private:
    float mx;
    float my;
    int direction;

public:
    Paddle();
    Paddle(float x, float y);

    float getX() const;
    float getY() const;
    int getDirection() const;

    void setPos(float x, float y);
    void setY(float y);
    void setDirection(int dir);
};

class Ball
{
private:
    float mx;
    float my;
    Vector2 mVel;

    float radius;
    SDL_Rect* render;

public:
    Ball();
    Ball(float px, float py, float vx, float vy);

    ~Ball();

    float getPosX() const;
    float getPosY() const;

    Vector2 getVel() const;
    float getVelX() const;
    float getVelY() const;
    SDL_Rect* getRenderObject() const;


    void setPos(float x, float y);
    void setVel(float x, float y);
    void setVelX(float x);
    void setVelY(float y);

    //render the object
    void renderBall(SDL_Renderer* mRenderer);
};

class Game
{
private:
    //Helper functions for the game loop
    void processInput();

    void updateGame();

    void generateOutput();

    //window created by SDL
    SDL_Window* mWindow;
    
    bool mIsRunning;

    SDL_Renderer* mRenderer;

    Uint32 mTicksCount;

    Ball mBall;
    Paddle mPaddle;

    float windowWidth;
    float windowHeight;

public:
    Game();    
    
    // Initialize the game
    bool initialize();

     // Runs the game loop until the game is over
    void runLoop();

    // Shutdown the game
    void shutdown();

};