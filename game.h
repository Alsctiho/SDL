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
    float mpx;
    float mpy;
    int direction;

    int mThickness;
    float mPaddleH;
    SDL_Rect* mRect;

public:
    Paddle(float x = 0.0f, float y = 0.0f);

    ~Paddle();

    float getPosX() const;
    float getPosY() const;
    int getDirection() const;
    float getPaddleH() const;

    void setPos(float x, float y);
    void setY(float y);
    void setDirection(int dir);

    void updateRenderObject();
    //render the object
    void renderPaddle(SDL_Renderer* renderer);
};

class Ball
{
private:
    float mpx;
    float mpy;
    Vector2 mVel;

    float mRadius;
    SDL_Rect* mRect;

public:
    Ball(float px = 0.0f, float py = 0.0f, float vx = 0.0f, float vy = 0.0f);

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

    void invertVel();
    void invertVelX();
    void invertVelY();

    void updateRenderObject();
    //render the object
    void renderBall(SDL_Renderer* renderer);
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