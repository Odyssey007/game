#include "../header/kingdom/buildings/dynamic/dynamicAsset.h"

DynamicAssets::DynamicAssets() :
level(0), cost(4)
{}

void DynamicAssets::calculateCost(unsigned int baseCost,unsigned int increment,unsigned int resourceIndex) {
    if (resourceIndex >= 0 && resourceIndex < cost.size()) {
        cost[resourceIndex] = baseCost + increment * level;
    }else {
        std::cerr << "Invalid resource index: " << resourceIndex << std::endl;
    }
}