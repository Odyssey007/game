#pragma once
#include "utility.h"

class QuadTree {
private: 
    sf::FloatRect bounds; 
    int rootCapacity; 
    bool split; 
    std::vector <sf::FloatRect> objects; 
    std::unique_ptr <QuadTree> children[4]; 
public:

    //constructor
    QuadTree(sf::FloatRect bounds, int rootCapacity);
    void insertObject(sf::FloatRect object); 
    void splitRoot(); 
    std::vector <sf::FloatRect> query(sf::FloatRect range);
};