#include "../header/utility.h"

float magnitude(const sf::Vector2f& vector) {
    return sqrt(vector.x*vector.x + vector.y*vector.y);
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

float distance(const sf::Vector2f& point1, const sf::Vector2f& point2) {
    return std::sqrt(std::pow(point1.x - point2.x, 2) + std::pow(point1.y - point2.y, 2));
}

float dotProduct(const sf::Vector2f& one, const sf::Vector2f& two) {
    return one.x*two.x + one.y*two.y;
}

//creates a box around the furthest pixels in x && y directions
sf::IntRect calcImageBounds(const sf::Image& image) {
    unsigned int left = image.getSize().x, right = 0;
    unsigned int top = image.getSize().y, bottom = 0;

    for (unsigned int x = 0; x < image.getSize().x; ++x) {
        for (unsigned int y = 0; y < image.getSize().y; ++y) {
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
sf::Vector2u randomGenerator(const std::pair <int, int>& range) {
    //static std::random_device rand;
    static std::mt19937 gen(std::random_device{}());

    std::uniform_int_distribution <> distribute (range.first, range.second); 
    unsigned int x = static_cast<unsigned int>(distribute(gen));
    unsigned int y = static_cast<unsigned int>(distribute(gen));

    return {x, y}; 
}

float rotationAngle(float centerX, float centerY, float mouseX, float mouseY) {
    return atan2(mouseY - centerY, mouseX - centerX); 
}

float radianToDegrees(float radians) {
    return radians * 180 / M_PI; 
}