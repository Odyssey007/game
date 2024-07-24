#pragma once
#include "../header/utility.h"
#include "../header/enemies/slime.h"
#include "../header/player/player.h"
#include "../header/obstacles/object.h"

class QuadTree {
private: 
    sf::FloatRect bounds; 
    unsigned int rootCapacity; 
    int level; 
    bool split; 
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

class Grid {
private: 
    sf::FloatRect gridBounds; 
    sf::FloatRect bufferZone; 
    sf::FloatRect visibleGrid; 
    std::vector <sf::FloatRect> entities;
    std::unordered_map<std::string, std::vector<sf::FloatRect>::iterator> hashEntities; 

    std::deque<sf::FloatRect> totalGrids;  
    std::unordered_map<int, std::deque<sf::FloatRect>::iterator> hashGrid; 
    std::vector<sf::FloatRect> cells; 
    float cellWidth; 
    float cellHeight;  

public:
    Grid(); 
    Grid(sf::FloatRect bounds); 

    //void gridExpansion();
    void makeCell(sf::FloatRect grid); 
    void bufferRegion(sf::View visible);
    void insertObject(sf::FloatRect objects);
    void draw(sf::RenderWindow &window); 
}; 