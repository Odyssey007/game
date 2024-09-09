#pragma once
#include "../header/utility.h"
#include "../header/kingdom/buildings/dynamic/huts.h"
#include "../header/kingdom/buildings/dynamic/farm.h"
#include "../header/kingdom/buildings/dynamic/castle.h"
#include "../header/kingdom/buildings/dynamic/storage.h"
#include "../header/kingdom/buildings/dynamic/carpenter.h"
#include "../header/kingdom/buildings/dynamic/animalFarm.h"
#include "../header/kingdom/buildings/dynamic/dynamicAsset.h"

class BuildingManager {
private: 
    int hutCounter; 
    int farmCounter;
    int animalFarmCounter;
public: 
    //std::vector<std::unique_ptr<DynamicAssets>> dynamicBuildings;
    //std::map<std::string, std::vector<std::unique_ptr<DynamicAssets>>> dynamicBuildings; 
    std::vector<std::pair<std::string, std::unique_ptr<DynamicAssets>>> dynamicBuildings;
    //Constructor; 
    BuildingManager(); 

    //Functions 
    void renderBuildings(sf::RenderWindow& window);
    void upgradeBuildings(); 
    void addDynamicBuildings(); 
    void addHuts(); 
    void addFarms(); 
    void addAnimalFarms(); 
    void allBuilding();
};