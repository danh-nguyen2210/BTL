#include "BatManager.h"
#include "Bat.h"


BatManager::BatManager() {
    srand(time(0)); // Khởi tạo random đơn giản
    addBat();     
}

void BatManager::updateBats() {
   
    if (batSpeed < maxBatSpeed) {
        batSpeed += speedIncrement;
    }

    for (int i = 0; i < bats.size(); i++) {
        bats[i].UpdateBatPos(batSpeed);
    }

    if (!bats.empty() && bats[0].getBatPos().first + Bat::BAT_WIDTH < 0) {
        bats.erase(bats.begin());
    }

    // Sinh Bat mới khi khoảng cách đủ lớn
    if (bats.empty() || ((SCREEN_WIDTH - bats.back().getBatPos().first) > nextBatDistance)&& bats.size()< rand()%3) {
        addBat();
        nextBatDistance = distanceArray[rand() % 5]; // cập nhật lại khoảng cách mới
    }
}

void BatManager::renderBats(const string& map) {
    for (int i = 0; i < bats.size(); i++) {
        bats[i].renderBat(map);
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
void BatManager::reset()
{
    bats.clear();    // Xóa hết các viên đá cũ
    addBat();        // Thêm viên đá đầu tiên như constructor
}