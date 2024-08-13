#include "../header/quadtree.h"

//Methods for QuadTree
QuadTree::QuadTree(sf::FloatRect bounds, int level)
    : level(level), maxLevels(7), bounds(bounds), maxObjects(7)
{}

void QuadTree::splitRoot() {
    float x = bounds.left;
    float y = bounds.top;
    float subWidth = bounds.width / 2;
    float subHeight = bounds.height / 2;

    node[0] = std::make_unique<QuadTree>(sf::FloatRect(x + subWidth, y, subWidth, subHeight), level + 1);
    node[1] = std::make_unique<QuadTree>(sf::FloatRect(x, y, subWidth, subHeight), level + 1);
    node[2] = std::make_unique<QuadTree>(sf::FloatRect(x, y + subHeight, subWidth, subHeight), level + 1);
    node[3] = std::make_unique<QuadTree>(sf::FloatRect(x + subWidth, y + subHeight, subWidth, subHeight), level + 1);

    for (const auto& object : objects) {
        for (int i = 0; i < 4; i++) {
            node[i]->insertObject(object);
        }
    }
    objects.clear();
}

void QuadTree::insertObject(const sf::FloatRect& object) {
    if (!bounds.intersects(object)) {
        return;
    }

    if (!node[0] && (objects.size() >= maxObjects && level < maxLevels)) {
        splitRoot();
    }

    if (node[0]) {
        bool inserted = false;
        for (int i = 0; i < 4; i++) {
            if (node[i]->bounds.intersects(object)) {
                node[i]->insertObject(object);
                inserted = true;
            }
        }
        // Only add to current node if it doesn't fit cleanly into any child
        if (!inserted) {
            objects.push_back(object);
        }
    } else {
        objects.push_back(object);
    }
}

void QuadTree::getNodeElements(std::vector<std::vector<sf::FloatRect>>& elements) {
    if(!objects.empty()) {
        elements.push_back(objects); 
    }
    
    if(node[0]) {
        for (int i = 0; i < 4; i++) {
            if (node[i]) {
                node[i]->getNodeElements(elements);
            }
        }
    }
}



bool QuadTree::intersects(const sf::FloatRect& other) const {
        return bounds.intersects(other);
}

sf::FloatRect QuadTree::getBounds() const {
    return bounds;
}

void QuadTree::clear() {
    objects.clear();

    for (auto& child : node) {
        if (child) {
            child->clear();
            child.reset();
        }
    }
}

void QuadTree::draw(sf::RenderWindow& window) {
    sf::RectangleShape rectangle(sf::Vector2f(bounds.width, bounds.height));
    rectangle.setPosition(bounds.left, bounds.top);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(1.0f);

    window.draw(rectangle);

    // Recursively draw child nodes
    for (auto& n : node) {
        if (n) {
            n->draw(window);
        }
    }
}


//Methods for Grid
void Grid::setBounds(const sf::FloatRect& newBounds) {
    bounds = newBounds;
    makeCells();
}

void Grid::makeCells() {
    cells.clear(); // Clear existing cells
    int numCellsPerRow = 4; 
    float cellWidth = bounds.width / numCellsPerRow;
    float cellHeight = bounds.height / numCellsPerRow;

    for (int i = 0; i < 16; ++i) {
        int col = i % numCellsPerRow;
        int row = i / numCellsPerRow;
        float x = bounds.left + col * cellWidth;
        float y = bounds.top + row * cellHeight;
        cells.push_back(sf::FloatRect(x, y, cellWidth, cellHeight));
    }
}


//Methods for GridSystem
GridSystem::GridSystem() :
    gridBounds(0, 0, 0, 0), bufferZone(0, 0, 0, 0), visibleGrid(0, 0, 0, 0),
    cellWidth(0), cellHeight(0)
{}

GridSystem::GridSystem(sf::FloatRect bounds) :
    gridBounds(bounds)
{
    createGrids(); 
}

const sf::Vector2f GridSystem::offsets[9] = {
    { 0.0f,  0.0f}, {-1.0f,  0.0f}, {-1.0f, -1.0f},  // Center, Left, Top-left
    { 0.0f, -1.0f}, { 1.0f, -1.0f}, { 1.0f,  0.0f},  // Top, Top-right, right
    { 1.0f,  1.0f}, { 0.0f,  1.0f}, {-1.0f,  1.0f}   // Bottom-right, bottom, bottom-left
};

void GridSystem::createGrids() {
    // Centering initial grid based on the player
    gridBounds.left = -gridBounds.width / 4;
    gridBounds.top = -gridBounds.height / 4;

    // Creating grids around the center grid
    for (int i = 0; i < 9; i++) {
        sf::FloatRect newGridBounds = gridBounds;
        newGridBounds.left += offsets[i].x * gridBounds.width;
        newGridBounds.top += offsets[i].y * gridBounds.height;

        newGrid.setBounds(newGridBounds); // Use the setter to set bounds and update cells
        totalGrids.push_back(newGrid);
    }
}

void GridSystem::bufferRegion(sf::Vector2f playerPosition) {
    bufferZone.width = (3 * gridBounds.width) / 4;
    bufferZone.height = (3 * gridBounds.height) / 4;
    bufferZone.left = playerPosition.x - bufferZone.width / 2;
    bufferZone.top = playerPosition.y - bufferZone.height / 2;
}

std::vector<int> GridSystem::activeGrids(sf::FloatRect player) {
    gridNum.clear();
    activeCells.clear(); 
    bufferDistFromGrid.clear(); 
    gridNum.push_back(-1);

    for (unsigned int i = 0; i < totalGrids.size(); i++) {
        if (totalGrids[i].bounds.intersects(player)) {
            gridNum[0] = i;
        }
        if (totalGrids[i].bounds.intersects(bufferZone)) {
            gridNum.push_back(i);
        }

        float x = bufferZone.left - totalGrids[i].bounds.left; 
        float y = bufferZone.top - totalGrids[i].bounds.top; 
        bufferDistFromGrid.push_back(std::sqrt(x * x + y * y)); 
    }

    findActiveCells(); 
    return gridNum;
}

std::vector<sf::FloatRect> GridSystem::getCellsInGrid(int gridIndex) {
    if(gridIndex >= 0 && gridIndex < 9) { 
        return totalGrids[gridIndex].cells; 
    } else {
        return std::vector<sf::FloatRect>();
    }
}

void GridSystem::findActiveCells() {
    activeCells.clear(); // Clear previous active cells

    for (unsigned int i = 0; i < gridNum.size(); i++) {
        if (i > 0) { 
            std::vector<sf::FloatRect> tempCells = getCellsInGrid(gridNum[i]);
            for (const auto& cell : tempCells) {
                if (cell.intersects(bufferZone)) {
                    activeCells.emplace_back(cell, 0);
                    //std::cout << "Active cells: " << cell.left << ", " << cell.top << ", " << cell.width << ", " << cell.height << std::endl;
                }
            }
        }
    }
}

void GridSystem::updateGrids() {
   if(activeCells.size() < 16) {
        int key = 1; 
        for (int i = 0; i < 9; i++) {
            sf::FloatRect newGridBounds = totalGrids[gridNum[0]].bounds;
            if(i == gridNum[0]) {
                newGridBounds.left += offsets[0].x * gridBounds.width;
                newGridBounds.top += offsets[0].y * gridBounds.height; 
            }
            else {
                newGridBounds.left += offsets[key].x * gridBounds.width;
                newGridBounds.top += offsets[key].y * gridBounds.height;
                key++; 
                //std::cout <<"its working" << std::endl;
            }
            totalGrids[i].bounds.left = newGridBounds.left; 
            totalGrids[i].bounds.top = newGridBounds.top; 
            totalGrids[i].setBounds(newGridBounds);
            //std::cout << "grids: " << totalGrids[i].bounds.left << ", " << totalGrids[i].bounds.top << ", " << totalGrids[i].bounds.width << ", " << totalGrids[i].bounds.height << std::endl;
        }
    } 
}

void GridSystem::getInstances(std::shared_ptr<EnemyPool> a, std::shared_ptr<ObjectPool> b, std::shared_ptr<Player> c) {
    enemyPool = a; 
    objectPool = b; 
    player = c; 
}

void GridSystem::populateQuadTree(sf::Vector2f position) {
    for (QuadTree& quadTree : activeCells) {
        quadTree.clear(); 
        if(quadTree.intersects(player->getBounds())) {
            quadTree.insertObject(player->getBounds()); 
        }
        for (const auto& enemy : enemyPool->activeEnemies) {
            if(quadTree.intersects(enemy->getBounds())) {
                quadTree.insertObject(enemy->getBounds()); 
            }
        }
        for (const auto& objects : objectPool->activeObjects) {
            quadTree.insertObject(objects->getBounds()); 
        }
    }
}

void GridSystem::getNeighbors() {
    for (QuadTree& quadTree : activeCells) {
        quadTree.getNodeElements(cellObjects); 
        std::cout << "size: " << cellObjects.size() << std::endl; 
        // for(unsigned int i = 0; i < cellObjects.size(); i++){
        //     std::cout << "object " << i << ": " << cellObjects[i].size() <<std::endl; 
        // }
        cellObjects.clear();  
    }
}

void GridSystem::draw(sf::RenderWindow& window) {
    for (const auto& grid : totalGrids) {
        sf::RectangleShape gridShape;
        gridShape.setPosition(grid.bounds.left, grid.bounds.top);
        gridShape.setSize(sf::Vector2f(grid.bounds.width, grid.bounds.height));
        gridShape.setOutlineColor(sf::Color::Red);
        gridShape.setOutlineThickness(1.0f);
        gridShape.setFillColor(sf::Color::Transparent);
        window.draw(gridShape);

        for (const auto& cell : grid.cells) {
            sf::RectangleShape cellShape;
            cellShape.setPosition(cell.left, cell.top);
            cellShape.setSize(sf::Vector2f(cell.width, cell.height));
            cellShape.setOutlineColor(sf::Color::Green);
            cellShape.setOutlineThickness(0.5f);
            cellShape.setFillColor(sf::Color::Transparent);
            window.draw(cellShape);
        }
    }

    sf::RectangleShape bufferShape;
    bufferShape.setPosition(bufferZone.left, bufferZone.top);
    bufferShape.setSize(sf::Vector2f(bufferZone.width, bufferZone.height));
    bufferShape.setOutlineColor(sf::Color::Blue);
    bufferShape.setOutlineThickness(1.0f);
    bufferShape.setFillColor(sf::Color::Transparent);
    window.draw(bufferShape);

    for (QuadTree& quadTree : activeCells) {
        quadTree.draw(window);
    }
}
