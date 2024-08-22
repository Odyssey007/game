#pragma once
#include "../header/battle/partitions.h"
#include "../header/battle/collisionManager.h"
#include "../header/battle/enemies/enemy.h"
#include <unordered_set>
class GridSystem {
private:
    sf::FloatRect gridBounds;
    sf::FloatRect bufferZone;
    sf::FloatRect visibleGrid;

    std::vector<int> gridNum;
    std::vector<Grid> totalGrids;
    std::vector<QuadTree> activeCells;
    std::vector<float> bufferDistFromGrid;

    Grid newGrid;
    float cellWidth;
    float cellHeight;
    static const sf::Vector2f offsets[9];


    std::vector<std::reference_wrapper<Entity>> entities;
    
    CollisionManager collisionManager;
public:
    void addEntity(Entity& entity);
    void removeDeadEntities();

    GridSystem();
    GridSystem(sf::FloatRect bounds);
 
    void createGrids(); 
    void updateGrids(); 
    void checkCollision();
    void findActiveCells(); 
    void populateQuadTree();
    void draw(sf::RenderWindow &window);
    void bufferRegion(sf::Vector2f playerPosition);
    std::vector<int> activeGrids(sf::FloatRect player);
    std::vector<sf::FloatRect> getCellsInGrid(int gridIndex); 
    bool entityCell(sf::FloatRect cell, sf::FloatRect entity);

    std::vector<std::vector<std::reference_wrapper<Entity>>> gridEntities;
    void getNeighbors();
};