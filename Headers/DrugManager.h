#ifndef DRUGMANAGER_H
#define DRUGMANAGER_H

#include "Variables.h"
#include "Drug.h"
#include <vector>

class DrugManager {
public:
    DrugManager();
    void updateDrugs();
    void renderDrugs();
    std::vector<Drug>& getDrugs();
    void reset();
    
private:
    int spawnCooldown=600;
    std::vector<Drug> drugs; 
    void addDrug();
    
    const int MIN_DISTANCE = 75;
    const int MAX_DISTANCE = 150;
    const int SPAWN_OFFSET = 50; 
    const int distanceArray[2] = {1000,2000};
    
};

#endif