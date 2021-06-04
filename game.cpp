#include "game.h"
#include <iostream>


Game::Game()
{
    mWindow = nullptr;
    mIsRunning = true;
}


bool Game::initialize()
{
    //std::cout << "initialization start" << std::endl;
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if(sdlResult)
    {
        //The SDL_GetError function returns an error message as a C-style string
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());

        return false;
    }

    windowWidth = 1024.0f;
    windowHeight = 768.0f;
    
    mWindow = SDL_CreateWindow
    (
        "Game Programming in C++ (Chapter 1)",  //The title of the window, in UTF-8 encoding.
        100,      //The x position of the window
        100,      //The y position of the window
        static_cast<int>(windowWidth),   //The width of the window, in screen coordinates.
        static_cast<int>(windowHeight),    //The height of the window, in screen coordinates.
        0       //The flags for the window
    );

    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    mTicksCount = 0;

    mBall.setPos(windowWidth/2, windowHeight/2);
    mPaddle.setPos(10.0f, windowHeight/2);

    //Initialize mBallVel to (-200.0f, 235.0f)
    mBall.setVel(-200.0f, 235.0f);
    
    //std::cout << "initialization end" << std::endl;
    return true;
}


void Game::shutdown()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}


void Game::runLoop()
{
    while(mIsRunning)
    {
        processInput();

        updateGame();
        
        generateOutput();
    }
}

void Game::processInput()
{
    //std::cout << "processInput start" << std::endl;
    SDL_Event event;

    // While there are still events in the queue
    while(SDL_PollEvent(&event))
    {
        //std::cout << SDL_PollEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }

    //get state of keyboard, Uint8 is unsigned char
    const Uint8* state = SDL_GetKeyboardState(nullptr);

    //if escape is pressed, also end loop
    if(state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }

    //reset direction
    mPaddle.setDirection(0);

    //-1 if the paddle moves up (negative y)
    if(state[SDL_SCANCODE_W])
    {
        mPaddle.setDirection(-1);
    }
    //1 if the paddle moves down (positive y)
    if(state[SDL_SCANCODE_S])
    {
        mPaddle.setDirection(1);
    }
    //if W,S are both pressed or neither is pressed, dir is still 0
    if(state[SDL_SCANCODE_W] && state[SDL_SCANCODE_S])
    {
        mPaddle.setDirection(0);
    }

    //std::cout << "processInput end" << std::endl;
    return;
}

void Game::updateGame()
{
    //std::cout << "updateGame start" << std::endl;
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    // Delta time is the difference in ticks from last frame
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    //update tick counts for next frame
    mTicksCount = SDL_GetTicks();
    
    mPaddle.setY(mPaddle.getPosY()  + mPaddle.getDirection() * 300.0f * deltaTime);

    Vector2 nextBallPosition;
    nextBallPosition.x = mBall.getPosX() + mBall.getVelX() * deltaTime;
    nextBallPosition.y = mBall.getPosY() + mBall.getVelY() * deltaTime;
    mBall.setPos(nextBallPosition.x, nextBallPosition.y);

    //collision detection
    if((mBall.getPosY() < thickness && mBall.getVelY() < 0.0f) || 
    (mBall.getPosY() > windowHeight - thickness && mBall.getVelY() > 0.0f))
        mBall.invertVelY();

    if(mBall.getPosX() > windowWidth - thickness)
        mBall.invertVelX();

    float diff = abs(mBall.getPosY() - mPaddle.getPosY());
    if
    (
        // Our y-difference is small enough
        diff <= mPaddle.getPaddleH()/2.0f &&
        // Ball is at the correct x-position
        mBall.getPosX() <= 25.0f && mBall.getPosX() >= 20.0f &&
        // The ball is moving to the left
        mBall.getVelX() < 0.0f
    )
        mBall.invertVelX();
    //std::cout << "updateGame end" << std::endl;
    return;
}

void Game::generateOutput()
{
    //std::cout << "GenerateOutput start" << std::endl;
    SDL_SetRenderDrawColor(mRenderer, 75, 75, 255, 255); //RGBA
    
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    
    SDL_Rect wall[3];
    //the top wall
    wall[0] = 
    {
        0, 0,               // the x/y coordinates of the top-left corner of the rectangle on screen
        static_cast<int>(windowWidth), thickness     // the width/height of the rectangle
    };
    
    //the bottom wall
    wall[1] = {0, static_cast<int>(windowHeight) - thickness, static_cast<int>(windowWidth), thickness};

    //the right wall
    wall[2] = {static_cast<int>(windowWidth) - thickness, 0, thickness, static_cast<int>(windowHeight)};

    SDL_RenderFillRect(mRenderer, wall);
    SDL_RenderFillRect(mRenderer, wall + 1);
    SDL_RenderFillRect(mRenderer, wall + 2);

    //draw ball
    mBall.renderBall(mRenderer);
    
    //draw paddle
    mPaddle.renderPaddle(mRenderer);

    SDL_RenderPresent(mRenderer);

    //std::cout << "GenerateOuput end" << std::endl;
    return;
}