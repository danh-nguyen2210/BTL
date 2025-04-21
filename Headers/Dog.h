#ifndef DOG_H
#define DOG_H

#include <SDL.h>
#include <utility> 
#include "Timer.h"

class Dog {
public:
    static const int DOG_WIDTH = 30;
    static const int DOG_HEIGHT = 30;
    static const int JUMP_VEL = -15;
    static const int GRAVITY = 1;
    static const int MAX_FLY_DURATION = 5000; //5000 ms = 5 giây

    Dog();
    void jump();
    void HandleFlyLogic(bool isFPressedNow);
    void ApplyGravitationalForce();
    std::pair<int,int> getDogPos();
    void setDogPos(int NewDogPosY);
    SDL_Rect getDogCollider();
    void renderDog();
    void renderFlyTimeBar();
    void reset();
    bool isDogFlying();
private:
    std::pair<int,int> DogPos;
    float velocityY;
    bool isJumping;
    bool isFlying;
    bool isFalling;
    bool hasFlown;
    SDL_Rect DogCollider;
    LTimer flyTimer; 
};

#endif