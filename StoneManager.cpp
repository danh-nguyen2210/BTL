#include "StoneManager.h"
#include "Variables.h"

StoneManager::StoneManager() {
    srand(time(0)); 
    addStone();  
}

void StoneManager::updateStones() {
    for (int i = 0; i < stones.size(); i++) {
        stones[i].UpdateStonePos();
    }

    if (!stones.empty() && stones[0].getStonePos().first + Stone::STONE_WIDTH < 0) {
        stones.erase(stones.begin()); 
    }

    if (stones.empty() || stones.back().getStonePos().first < SCREEN_WIDTH && stones.size()<2) {
        addStone();
    }
}

void StoneManager::renderStones() {
    for (int i = 0; i < stones.size(); i++) {
        stones[i].renderStone();
    }
}

void StoneManager::addStone() {
    int new_x;
    
    if (stones.empty()) 
    {
        new_x = SCREEN_WIDTH+5; 
    } 
    else 
    {
        int distance = distanceArray[rand()%5];
        new_x = stones.back().getStonePos().first + distance;
    }
    
    // Đảm bảo viên đá mới xuất hiện bên ngoài màn hình
    if (new_x < SCREEN_WIDTH + SPAWN_OFFSET) {
        new_x = SCREEN_WIDTH + (rand() % SPAWN_OFFSET);
    }
    

    stones.push_back(Stone(new_x));
}

std::vector<Stone> StoneManager::getStones(){
    return stones;
}