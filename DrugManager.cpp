#include "DrugManager.h"


DrugManager::DrugManager() {
    srand(time(0)); // Khởi tạo random đơn giản   
}

void DrugManager::updateDrugs() {
        for (int i = 0; i < drugs.size(); i++) {
            drugs[i].UpdateDrugPos();
        }
    
        if (!drugs.empty() && drugs[0].getDrugPos().first + Drug::DRUG_WIDTH < 0) {
            drugs.erase(drugs.begin()); 
        }
        // Điều kiện sinh mới
        if ((drugs.empty() || drugs.back().getDrugPos().first < SCREEN_WIDTH) && drugs.size() < 1) {
            if (spawnCooldown <= 0) {
                addDrug();
                spawnCooldown = 1000 + rand() % 600; // Delay từ 300 đến 600 frame
            } 
            else {
                spawnCooldown--; // Đếm ngược mỗi frame
            }
        }
}

void DrugManager::renderDrugs() {
    for (int i = 0; i < drugs.size(); i++) {
        drugs[i].renderDrug();
    }
}

void DrugManager::addDrug() {
    int new_x;
    
    if (drugs.empty()) 
    {
        new_x = SCREEN_WIDTH+100; 
    } 
    else 
    {
        int distance = distanceArray[rand()%5];
        new_x = drugs.back().getDrugPos().first + distance;
    }
    
    if (new_x < SCREEN_WIDTH + SPAWN_OFFSET) {
        new_x = SCREEN_WIDTH + (rand() % SPAWN_OFFSET);
    }
    
    drugs.push_back(Drug(new_x));
}

std::vector<Drug>& DrugManager::getDrugs(){
    return drugs;
}
void DrugManager::reset()
{
    drugs.clear();    // Xóa hết các drug cũ
    addDrug();        // Thêm viên drug đầu tiên như constructor
}