#pragma once
#include "../header/utility.h"

enum class ResourceType {
    Gold,
    Wood,
    Food,
    Stone,
    Population,
};

class ResourceManager {
private:
    std::map<ResourceType, int> resources; 

public:
    //Constructor; 
    ResourceManager();

    //Function
    bool canAfford() const; 
    void deductResources(); 
    void addResources(); 
    int getAmount(ResourceType type) const; 
};