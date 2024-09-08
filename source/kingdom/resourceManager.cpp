#include "../header/kingdom/resourceManager.h"

ResourceManager::ResourceManager() {
    //? This will be loaded from the saved data
    //Starting resources
    resources[ResourceType::Gold] = 1000;
    resources[ResourceType::Wood] = 500;
    resources[ResourceType::Food] = 500;
    resources[ResourceType::Stone] = 200;
    resources[ResourceType::Population] = 10;
}

bool ResourceManager::canAfford() const {
    //logic
}

void ResourceManager::deductResources() {
    //logic
}

void ResourceManager::addResources() {
    //logic
}

int ResourceManager::getAmount(ResourceType type) const {
    //logic
}