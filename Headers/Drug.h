#ifndef DRUG_H
#define DRUG_H

#include <SDL.h>
#include <utility> 
#include "Variables.h"


class Drug {
public: 
    static const int DRUG_WIDTH = 16;
    static const int DRUG_HEIGHT = 16;
    static const int DRUG_VEL = 5;

    Drug(int startX = SCREEN_WIDTH);
    void UpdateDrugPos();
    std::pair<int,int> getDrugPos();
    SDL_Rect getDrugCollider();
    void renderDrug();

private:
    std::pair<int,int> DrugPos;
    SDL_Rect DrugCollider;
    int drugFrame = 0;
};

#endif