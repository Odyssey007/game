#include "../header/utility.h"

float magnitude(const sf::Vector2f& vector) {
    return sqrt(vector.x*vector.x + vector.y*vector.y);
}

sf::Vector2f normalize(const sf::Vector2f& one) {    
    float normal = magnitude(one);
    sf::Vector2f normalized;
    if (normal != 0) {
        normalized = one / normal;
    }
    return normalized;
}

float distance(const sf::Vector2f& point1, const sf::Vector2f& point2) {
    return std::sqrt(std::pow(point1.x - point2.x, 2) + std::pow(point1.y - point2.y, 2));
}

float dotProduct(const sf::Vector2f& one, const sf::Vector2f& two) {
    return one.x*two.x + one.y*two.y;
}

DeltaTime* DeltaTime::instance = nullptr;

float DeltaTime::getDeltaTime() const {
    return deltaTime;
}

void DeltaTime::restart() {
    deltaTime = clock.restart().asSeconds();
}

DeltaTime* DeltaTime::getInstace() {
    if (instance == nullptr)  {
        instance = new DeltaTime();
    }    
    return instance;
}