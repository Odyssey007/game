#pragma once
#include <SFML/Graphics.hpp>

class DeltaTime {
private:
    sf::Clock clock;
    float deltaTime;
    static DeltaTime* instance;
    DeltaTime() : deltaTime(0.0f) {}
public:
    static DeltaTime* getInstance();
    void restart();
    float getDeltaTime() const;
};