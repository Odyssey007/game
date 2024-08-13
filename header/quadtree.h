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
    std::vector<sf::FloatRect> objects; 

    //private functions
    void splitRoot(); 
    int getPrimaryNode(const sf::FloatRect& rect) const;
public: 

    //constructor
    QuadTree(sf::FloatRect bounds, int level);

    //public functions
    void clear(); 
    sf::FloatRect getBounds() const;
    void draw(sf::RenderWindow& window);
    void insertObject(const sf::FloatRect& object); 
    bool intersects(const sf::FloatRect& other) const;
    void getNodeElements(std::vector<std::vector<sf::FloatRect>>& elements); 
};


struct Grid {
    sf::FloatRect bounds;
    std::vector<sf::FloatRect> cells;

    void makeCells();
    void setBounds(const sf::FloatRect& newBounds);
}; 


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
public: 
    std::vector<std::vector<sf::FloatRect>> cellObjects;

    GridSystem();
    GridSystem(sf::FloatRect bounds);
 
    void createGrids(); 
    void updateGrids(); 
    void findActiveCells(); 
    void getNeighbors(); 
    void draw(sf::RenderWindow &window);
    void populateQuadTree(sf::Vector2f position);
    void bufferRegion(sf::Vector2f playerPosition);
    std::vector<int> activeGrids(sf::FloatRect player);
    std::vector<sf::FloatRect> getCellsInGrid(int gridIndex); 
    void getInstances(std::shared_ptr<EnemyPool> a, std::shared_ptr<ObjectPool> b, std::shared_ptr<Player> c);
};
