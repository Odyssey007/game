#include "../header/utility.h"

float magnitude(const sf::Vector2f& vector) {
    return std::sqrt(vector.x*vector.x + vector.y*vector.y);
}

//unit vec
sf::Vector2f normalize(const sf::Vector2f& one) {    
    float normal = magnitude(one);
    sf::Vector2f normalized;
    if (normal != 0) {
        normalized = one / normal;
    }
    return normalized;
}

float distance(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

float dotProduct(const sf::Vector2f& one, const sf::Vector2f& two) {
    return one.x*two.x + one.y*two.y;
}

//creates a box around the furthest pixels in x && y directions
sf::IntRect calcImageBounds(const sf::Image& image) {
    size_t left = image.getSize().x, right = 0;
    size_t top = image.getSize().y, bottom = 0;

    for (size_t x = 0; x < image.getSize().x; ++x) {
        for (size_t y = 0; y < image.getSize().y; ++y) {
            if (image.getPixel(x, y).a != 0) {
                if (x <= left) left = x;
                if (x >= right) right = x;
                if (y <= top) top = y;
                if (y >= bottom) bottom = y;
            }
        }
    }

    return sf::IntRect(left, top, right-left, bottom-top);
}

//returns an signed int between range
sf::Vector2i randomGenerator(const std::pair<int, int>& xRange, const std::pair<int, int>& yRange) {
    //static std::random_device rand;
    static std::mt19937 gen(std::random_device{}());

    std::uniform_int_distribution<> distributeX(xRange.first, xRange.second);
    std::uniform_int_distribution<> distributeY(yRange.first, yRange.second);

    int x = distributeX(gen);
    int y = distributeY(gen);
    
    return {x, y}; 
}

float rotationAngle(float centerX, float centerY, float mouseX, float mouseY) {
    return atan2(mouseY - centerY, mouseX - centerX); 
}

float radianToDegrees(float radians) {
    return radians * 180 / M_PI; 
}