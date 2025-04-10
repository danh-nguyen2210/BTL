#include "BatManager.h"


BatManager::BatManager() {
    srand(time(0)); // Khởi tạo random đơn giản
    addBat();     
}

void BatManager::updateBats() {
    for (int i = 0; i < bats.size(); i++) {
        bats[i].UpdateBatPos();
    }

    if (!bats.empty() && bats[0].getBatPos().first + Bat::BAT_WIDTH < 0) {
        bats.erase(bats.begin()); 
    }

    if (bats.empty() || bats.back().getBatPos().first < SCREEN_WIDTH && bats.size()<2) {
        addBat();
    }
}

void BatManager::renderBats() {
    for (int i = 0; i < bats.size(); i++) {
        bats[i].renderBat();
    }
}

void BatManager::addBat() {
    int new_x;
    
    if (bats.empty()) 
    {
        new_x = SCREEN_WIDTH+100; 
    } 
    else 
    {
        int distance = distanceArray[rand()%5];
        new_x = bats.back().getBatPos().first + distance;
    }
    
    // Đảm bảo dơi mới xuất hiện bên ngoài màn hình
    if (new_x < SCREEN_WIDTH + SPAWN_OFFSET) {
        new_x = SCREEN_WIDTH + (rand() % SPAWN_OFFSET);
    }
    
    bats.push_back(Bat(new_x));
}

std::vector<Bat>& BatManager::getBats(){
    return bats;
}