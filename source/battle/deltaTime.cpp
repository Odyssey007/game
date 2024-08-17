#include "../header/battle/deltaTime.h"

DeltaTime* DeltaTime::instance = nullptr;

float DeltaTime::getDeltaTime() const {
    return deltaTime;
}

void DeltaTime::restart() {
    deltaTime = clock.restart().asSeconds();
}

DeltaTime* DeltaTime::getInstance() {
    if (instance == nullptr)  {
        instance = new DeltaTime();
    }    
    return instance;
}