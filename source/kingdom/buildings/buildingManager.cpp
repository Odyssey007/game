#include "../header/kingdom/buildings/buildingManager.h"

BuildingManager::BuildingManager() :
    hutCounter(1), farmCounter(1), animalFarmCounter(1)
{}

void BuildingManager::addDynamicBuildings() {
    dynamicBuildings.emplace_back("Castle", std::make_unique<Castle>());
    dynamicBuildings.emplace_back("Storage", std::make_unique<Storage>());
    dynamicBuildings.emplace_back("Carpenter", std::make_unique<Carpenter>());
    dynamicBuildings.emplace_back("Hut" + std::to_string(hutCounter), std::make_unique<Huts>());
    dynamicBuildings.emplace_back("Farm" + std::to_string(farmCounter), std::make_unique<Farms>());
    dynamicBuildings.emplace_back("AnimalFarm" + std::to_string(animalFarmCounter), std::make_unique<AnimalFarms>());
}

void BuildingManager::addHuts() {
    hutCounter++; 
    if (hutCounter < 11) {
        dynamicBuildings.emplace_back("Huts" + std::to_string(hutCounter), std::make_unique<Huts>());
        std::cout << "Hut counter: " << hutCounter << std::endl;
        std::cout << "Building size: " << dynamicBuildings.size() << std::endl;
    } else {
        std::cout << "Max hut number reached." << std::endl;
        std::cout << dynamicBuildings.size() << std::endl;
        std::cout << hutCounter << std::endl;
    }
}

void BuildingManager::addFarms() {
    farmCounter++; 
    if (farmCounter < 9) {
        dynamicBuildings.emplace_back("Farm" + std::to_string(farmCounter), std::make_unique<Farms>());
        std::cout << "Farm counter: " << farmCounter << std::endl;
        std::cout << "Building size: " << dynamicBuildings.size() << std::endl;
    } else {
        std::cout << "Max hut number reached." << std::endl;
        std::cout << dynamicBuildings.size() << std::endl;
        std::cout << "Farm counter: " << farmCounter << std::endl;
    }
}
void BuildingManager::addAnimalFarms() {
    animalFarmCounter++; 
    if (animalFarmCounter < 6) {
        dynamicBuildings.emplace_back("AnimalFarm" + std::to_string(animalFarmCounter), std::make_unique<AnimalFarms>());
        std::cout << "AnimalFarm counter: " << animalFarmCounter << std::endl;
        std::cout << "Building size: " << dynamicBuildings.size() << std::endl;
    } else {
        std::cout << "Max hut number reached." << std::endl;
        std::cout << dynamicBuildings.size() << std::endl;
        std::cout << "AnimalFarm counter: " << animalFarmCounter << std::endl;
    }
}

void BuildingManager::upgradeBuildings() {
    for (auto& dynamicBuildingPair : dynamicBuildings) {
        auto& dynamicBuilding = dynamicBuildingPair.second;
        dynamicBuilding->upgrade();
    }
}

void BuildingManager::renderBuildings(sf::RenderWindow& window) {
    for (auto& dynamicBuildingPair : dynamicBuildings) {
        auto& dynamicBuilding = dynamicBuildingPair.second;
        dynamicBuilding->render(window);
    }
}

void BuildingManager::allBuilding() {
    for (auto& [key, dynamicBuilding] : dynamicBuildings) {
        //std::cout << "Key: " << key << ", Building Name: " << dynamicBuilding->getName() << std::endl;
        std::cout << "Building key: " << key << std::endl; 
    }
    std::cout << std::endl; 
}
