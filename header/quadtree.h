#pragma once
#include "utility.h"
#include "slime.h"
#include "player.h"
#include "obstacles.h"

class QuadTree {
private: 
    sf::FloatRect bounds; 
    unsigned int rootCapacity; 
    int level; 
    bool split; 
    std::vector <sf::FloatRect> allObjects; 
    std::vector <sf::FloatRect> objects; 
    std::unique_ptr <QuadTree> children[4]; 
    // std::__shared_ptr<Slime> slimes; 
    // std::__shared_ptr<Player> player; 
    // std::__shared_ptr<Object> obstacles; 
    void splitRoot(); 
public:
    sf::FloatRect windowBounds; 

    //constructor
    //QuadTree() = default; 
    QuadTree(sf::FloatRect bounds,unsigned int rootCapacity);
    void insertObject(sf::FloatRect object); 
    //std::vector <sf::FloatRect> query(sf::FloatRect range);
    void draw(sf::RenderWindow& window); 
    void updateBounds(sf::Vector2f center);
    void clear(); 
};