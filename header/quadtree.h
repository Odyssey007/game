#pragma once
#include "../header/pool.h"
#include "../header/utility.h"
#include "../header/enemies/slime.h"
#include "../header/player/player.h"
#include "../header/obstacles/object.h"

class QuadTree {
private: 
    sf::FloatRect bounds; 
    unsigned int maxObjects;  
    int maxLevels; 
    int level; 
    std::unique_ptr<QuadTree> node[4]; 
    void splitRoot(); 
public: 
    std::vector<sf::FloatRect> objects; 
    //constructor
    //QuadTree() = default; 
    QuadTree(sf::FloatRect bounds, int level);
    int getPrimaryNode(const sf::FloatRect& rect) const;
    void insertObject(sf::FloatRect object); 
    bool intersects(const sf::FloatRect& other) const;
    void clear(); 
    void draw(sf::RenderWindow& window);
};


struct Grid {
    sf::FloatRect bounds;
    std::vector<sf::FloatRect> cells;

    void setBounds(const sf::FloatRect& newBounds);
    void makeCells();
}; 


class GridSystem {
private:
    sf::FloatRect gridBounds;
    sf::FloatRect bufferZone;
    sf::FloatRect visibleGrid;

    std::vector<sf::FloatRect> entities;
    std::unordered_map<std::string, std::vector<sf::FloatRect>::iterator> hashEntities;

    std::vector<QuadTree> activeCells;
    std::vector<float> bufferDistFromGrid;
    std::vector<Grid> totalGrids;
    std::vector<int> gridNum;

    float cellWidth;
    float cellHeight;
    Grid newGrid;
    static const sf::Vector2f offsets[9];

    std::shared_ptr<EnemyPool> enemyPool;
    std::shared_ptr<ObjectPool> objectPool;  
    std::shared_ptr<Player> player;  
public:
    GridSystem();
    GridSystem(sf::FloatRect bounds);
 
    void createGrids(); 
    void bufferRegion(sf::Vector2f playerPosition);
    std::vector<int> activeGrids(sf::FloatRect player);
    std::vector<sf::FloatRect> getCellsInGrid(int gridIndex); 
    void findActiveCells(); 
    void updateGrids(); 
    void populateQuadTree();
    void getInstances(std::shared_ptr<EnemyPool> a, std::shared_ptr<ObjectPool> b, std::shared_ptr<Player> c);
    void draw(sf::RenderWindow &window);
};
