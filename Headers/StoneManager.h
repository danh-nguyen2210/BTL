#ifndef STONEMANAGER_H
#define STONEMANAGER_H

#include "Stone.h"
#include <vector>

class StoneManager {
public:
    StoneManager();
    void updateStones();
    void renderStones(const string& map);
    std::vector<Stone> getStones();
    void reset();
    
private:
    std::vector<Stone> stones; 
    void addStone();
    
    const int MIN_DISTANCE = 75;
    const int MAX_DISTANCE = 150;
    const int SPAWN_OFFSET = 10; 
    const int distanceArray[5] = {200,240,280,320,380};
    int nextStoneDistance = distanceArray[rand() % 5];

    float stoneSpeed = 5.0f;
    float speedIncrement = 0.0000005f;
    float maxStoneSpeed = 6.0f;
};

#endif