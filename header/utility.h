#pragma once
#include <SFML/Graphics.hpp>
#include <iostream> 
#include <cmath>
#include <string>
#include <memory>

float magnitude(const sf::Vector2f& vector);
sf::Vector2f normalize(const sf::Vector2f& one);
float distance(const sf::Vector2f& point1, const sf::Vector2f& point2);
float dotProduct(const sf::Vector2f& one, const sf::Vector2f& two);



class DeltaTime {
private:
    sf::Clock clock;
    float deltaTime;
    static DeltaTime* instance;
    DeltaTime() : deltaTime(0.0f) {}
public:
    static DeltaTime* getInstace();
    void restart();
    float getDeltaTime() const;
};