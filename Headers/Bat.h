#ifndef BAT_H
#define BAT_H

#include <SDL.h>
#include <utility> 
#include "Variables.h"




class Bat {
public: 
    static const int BAT_WIDTH = 30;
    static const int BAT_HEIGHT = 30;

    
    Bat(int startX = SCREEN_WIDTH-150);
    void UpdateBatPos();
    std::pair<int,int> getBatPos();
    SDL_Rect getBatCollider();
    void renderBat(const string& map);

private:
    std::pair<int,int> BatPos;
    SDL_Rect BatCollider;
    int batFrame = 0;
    int BAT_VEL = 5;
};

#endif