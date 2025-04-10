#ifndef STONE_H
#define STONE_H

#include <SDL.h>
#include <utility> 
#include "Variables.h"

class Stone {
public: 
    static const int STONE_WIDTH = 35;
    static const int STONE_HEIGHT = 42;
    static const int STONE_VEL = 6;

    Stone(int startX = SCREEN_WIDTH);
    void UpdateStonePos();
    std::pair<int,int> getStonePos();
    SDL_Rect getStoneCollider();
    void renderStone();

private:
    std::pair<int,int> StonePos;
    SDL_Rect StoneCollider;
    int stoneFrame = 0;
};

#endif