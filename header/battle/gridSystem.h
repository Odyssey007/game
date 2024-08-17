#pragma once
#include "../header/battle/partitions.h"

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

    std::shared_ptr<Player> player;  
    std::shared_ptr<EnemyPool> enemyPool;
    std::shared_ptr<ObjectPool> objectPool;  
    
    
    CollisionManager collisionManager;
public:

    GridSystem();
    GridSystem(sf::FloatRect bounds);
 
    void createGrids(); 
    void updateGrids(); 
    void getNeighbors();
    void findActiveCells(); 
    void populateQuadTree();
    void draw(sf::RenderWindow &window);
    void bufferRegion(sf::Vector2f playerPosition);
    std::vector<int> activeGrids(sf::FloatRect player);
    std::vector<sf::FloatRect> getCellsInGrid(int gridIndex); 
    bool entityCell(sf::FloatRect cell, sf::FloatRect entity);
    void getInstances(std::shared_ptr<EnemyPool> a, std::shared_ptr<ObjectPool> b, std::shared_ptr<Player> c);
};