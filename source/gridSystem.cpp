#include "../header/gridSystem.h"

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

// void GridSystem::getInstances(std::shared_ptr<EnemyPool> a, std::shared_ptr<ObjectPool> b, std::shared_ptr<Player> c) {
//     enemyPool = a; 
//     objectPool = b; 
//     player = c; 
// }

void GridSystem::addEntity(std::shared_ptr<Entity> entity) {
    entities.push_back(entity);
}

bool GridSystem::entityCell(sf::FloatRect cell, sf::FloatRect entity) {
    float midpointX = entity.left + entity.width / 2;
    float midpointY = entity.top + entity.height / 2;

    if(containsWithTolerance(cell, midpointX, midpointY)) {
        return true; 
    } else {
        return false; 
    }
}

void GridSystem::populateQuadTree() {
    for (QuadTree& quadTree : activeCells) {
        quadTree.clear();

        for (const auto& entity : entities) {
            if (quadTree.intersects(entity->getBounds())) {
                quadTree.insertObject(entity);
            }
        }


        // if(quadTree.intersects(player->getBounds())) {
        //     // if(entityCell(quadTree.getBounds(), player->getBounds())) {
        //     // }
        //     quadTree.insertObject(player);
 
        // }
        // for (const auto& enemy : enemyPool->activeEnemies) {
        //     if(quadTree.intersects(enemy->getBounds())) {
        //         // if(entityCell(quadTree.getBounds(), player->getBounds())){
        //         // }
        //         quadTree.insertObject(enemy); 
        //     }
        // }
        // for (const auto& objects : objectPool->activeObjects) {
        //     if(quadTree.intersects(objects->getBounds())) {
        //         quadTree.insertObject(objects); 
        //     }
        // }
    }
}

#include <unordered_set>

void GridSystem::checkCollision() {
    for (QuadTree& grid : activeCells) {
        grid.getNodeElements(gridEntities);
        getNeighbors(); //gets the neighbors within a grid
        for (const auto& quadEntities : gridEntities) {
            collisionManager.update(quadEntities);
        }
        gridEntities.clear();
    }
}

void GridSystem::getNeighbors() {
    std::unordered_set<Entity*> uniqueEntities;
    std::vector<std::shared_ptr<Entity>> enemyNeighbors;

    for (const auto& quadEntities : gridEntities) {
        for (const auto& entity : quadEntities) {
            if (entity->entityType == ENEMY) {
                if (uniqueEntities.insert(entity.get()).second) {
                    enemyNeighbors.push_back(entity);
                }
            }
        }
    }
    for (const auto& entity : enemyNeighbors) {
        Enemy* enemy = dynamic_cast<Enemy*>(entity.get());
        if (enemy) {
            enemy->neighbors.clear();
            for (const auto& neighbor : enemyNeighbors) {
                if (entity != neighbor) {
                    enemy->neighbors.push_back(neighbor);
                }
            }
        }
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