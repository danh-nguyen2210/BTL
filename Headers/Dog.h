#ifndef DOG_H
#define DOG_H

#include <SDL.h>
#include <utility> 

class Dog {
public:
    static const int DOG_WIDTH = 30;
    static const int DOG_HEIGHT = 30;
    static const int JUMP_VEL = -15;
    static const int GRAVITY = 1;

    Dog();
    void jump();
    void ApplyGravitationalForce();
    std::pair<int,int> getDogPos();
    void setDogPos(int NewDogPosY);
    SDL_Rect getDogCollider();
    void renderDog();

private:
    std::pair<int,int> DogPos;
    float velocityY;
    bool isJumping;
    SDL_Rect DogCollider;
};

#endif