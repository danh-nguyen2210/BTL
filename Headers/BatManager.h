#ifndef BATMANAGER_H
#define BATMANAGER_H

#include "Variables.h"
#include "Bat.h"
#include <vector>

class BatManager {
public:
    BatManager();
    void updateBats();
    void renderBats(const string& map);
    std::vector<Bat>& getBats();
    void reset();
    
private:
    std::vector<Bat> bats; 
    void addBat();
    
    const int MIN_DISTANCE = 75;
    const int MAX_DISTANCE = 150;
    const int SPAWN_OFFSET = 50; 
    const int distanceArray[5] = {200,300,400,500,600};
    int nextBatDistance = distanceArray[rand() % 5];

    float batSpeed = 5.0f;
    float speedIncrement = 0.0000005f;
    float maxBatSpeed = 6.0f;
};

#endif