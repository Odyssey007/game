#pragma once
#include "../header/pool.h"
#include "../header/utility.h"
#include "../header/enemies/slime.h"
#include "../header/player/player.h"
#include "../header/obstacles/object.h"

class QuadTree {
private: 
    int level; 
    int maxLevels; 
    sf::FloatRect bounds; 
    unsigned int maxObjects;  
    std::unique_ptr<QuadTree> node[4]; 
    std::vector<std::shared_ptr<Entity>> objects; //!needs to be entity

    //private functions
    void splitRoot(); 
    int getPrimaryNode(const std::shared_ptr<Entity>& entity) const; //!!
public: 
    //constructor
    QuadTree(sf::FloatRect bounds, int level);

    //public functions
    void clear(); 
    sf::FloatRect getBounds() const;
    void draw(sf::RenderWindow& window);
    void insertObject(std::shared_ptr<Entity> entity);  //!!
    bool intersects(const sf::FloatRect& other) const;
    void getNodeElements(std::vector<std::vector<std::shared_ptr<Entity>>>& elements);
    
};

struct Grid {
    sf::FloatRect bounds;
    std::vector<sf::FloatRect> cells; //grid cell

    void makeCells();
    void setBounds(const sf::FloatRect& newBounds);
}; 