#pragma once
#include "../header/utility.h"
#include "../header/battle/entity.h"

class QuadTree {
private: 
    int level; 
    int maxLevels; 
    sf::FloatRect bounds; 
    unsigned int maxObjects;  
    std::unique_ptr<QuadTree> node[4]; 
    std::vector<std::reference_wrapper<Entity>> objects;

    //private functions
    void splitRoot(); 
    int getPrimaryNode(const Entity& weakEntity) const;
public: 
    //constructor
    QuadTree(sf::FloatRect bounds, int level);

    //public functions
    void clear(); 
    sf::FloatRect getBounds() const;
    void draw(sf::RenderWindow& window);
    void insertObject(Entity& entity);
    bool intersects(const sf::FloatRect& other) const;
    void getNodeElements(std::vector<std::vector<std::reference_wrapper<Entity>>>& elements);
};

struct Grid {
    sf::FloatRect bounds;
    std::vector<sf::FloatRect> cells; //grid cell

    void makeCells();
    void setBounds(const sf::FloatRect& newBounds);
}; 