#include "StoneManager.h"
#include "Variables.h"

StoneManager::StoneManager() {
    srand(time(0)); 
    addStone();  
}

void StoneManager::updateStones() {

    if (stoneSpeed < maxStoneSpeed) {
        stoneSpeed += speedIncrement;
    }

    for (int i = 0; i < stones.size(); i++) {
        stones[i].UpdateStonePos(stoneSpeed);
    }

    if (!stones.empty() && stones[0].getStonePos().first + Stone::STONE_WIDTH < 0) {
        stones.erase(stones.begin()); 
    }

    if (stones.empty() || (SCREEN_WIDTH - stones.back().getStonePos().first > nextStoneDistance)&& stones.size() < rand()%3 ){
        addStone();
        nextStoneDistance = distanceArray[rand()%5];
    }
}

void StoneManager::renderStones(const string& map) {
    for (int i = 0; i < stones.size(); i++) {
        stones[i].renderStone(map);
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

void StoneManager::reset()
{
    stones.clear();    // Xóa hết các viên đá cũ
    addStone();        // Thêm viên đá đầu tiên như constructor
}