#pragma once
#include <SFML/Graphics.hpp>
#include <iostream> 
#include <cmath>
#include <memory>
#include <random>
#include "deltaTime.h"

float magnitude(const sf::Vector2f& vector);
sf::Vector2f normalize(const sf::Vector2f& one);
float distance(const sf::Vector2f& point1, const sf::Vector2f& point2);
float dotProduct(const sf::Vector2f& one, const sf::Vector2f& two);
sf::IntRect calcImageBounds(const sf::Image& image);
float rotationAngle(float centerX, float centerY, float mouseX, float mouseY);
float radianToDegrees(float radians);

sf::Vector2i randomGenerator(const std::pair<int, int>& xRange, const std::pair<int, int>& yRange);
