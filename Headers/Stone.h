#ifndef STONE_H
#define STONE_H

#include <SDL.h>
#include <utility> 
#include "Variables.h"
#include "LTexture.h"

class Stone {
public: 
    static const int STONE_WIDTH = 35;
    static const int STONE_HEIGHT = 42;
   

    Stone(int startX = SCREEN_WIDTH);
    void UpdateStonePos(float speed);
    std::pair<int,int> getStonePos();
    SDL_Rect getStoneCollider();
    void renderStone(const string& map);
    void setStone(string CurrentMapStone );
    string getStone();

private:
    std::pair<int,int> StonePos;
    SDL_Rect StoneCollider;
    int stoneFrame = 0;
    string currentStone;
};

#endif