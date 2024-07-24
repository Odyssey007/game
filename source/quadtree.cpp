#include "../header/quadtree.h"

QuadTree::QuadTree(sf::FloatRect bounds, unsigned int rootCapacity):
    bounds(bounds), rootCapacity(rootCapacity), level(0),
    split(false)
{} 

//? need to figure out level for query 
void QuadTree::insertObject(sf::FloatRect object) {
    if (!bounds.intersects(object)) {
        return; // Object is out of bounds
    }

    if (objects.size() < rootCapacity) {
        if (split) {
            for (auto& child : children) {
                if (child->bounds.intersects(object)) {
                    child->insertObject(object);
                }
            }
        } 
        else {
            objects.push_back(object);
        }
    } 
    else {
        if (!split) {
            if(level < 8) {
                splitRoot();
            }
        }
        for (auto& child : children) {
            if (child->bounds.intersects(object)) {
                child->insertObject(object);
            }
        }
    }
}

void QuadTree::splitRoot() {
    if (split) return; // Already split

    float x = bounds.left;
    float y = bounds.top;
    float subWidth = bounds.width / 2;
    float subHeight = bounds.height / 2;

    children[0] = std::make_unique<QuadTree>(sf::FloatRect(x, y, subWidth, subHeight), rootCapacity);
    children[1] = std::make_unique<QuadTree>(sf::FloatRect(x + subWidth, y, subWidth, subHeight), rootCapacity);
    children[2] = std::make_unique<QuadTree>(sf::FloatRect(x, y + subHeight, subWidth, subHeight), rootCapacity);
    children[3] = std::make_unique<QuadTree>(sf::FloatRect(x + subWidth, y + subHeight, subWidth, subHeight), rootCapacity);

    // Move existing objects to the appropriate child nodes
    for (const auto& object : objects) {
        for (auto& child : children) {
            if (child->bounds.intersects(object)) {
                child->insertObject(object);
            }
        }
    }

    split = true;
    objects.clear(); 
}

void QuadTree::draw(sf::RenderWindow& window) {
    //std::cout << "bounds: " << bounds.left << ", " << bounds.top << ", " << bounds.width << ", " << bounds.height << std::endl;
    //std::cout << "windowBounds: " << windowBounds.left << ", " << windowBounds.top << ", " << windowBounds.width << ", " << windowBounds.height << std::endl;
    //Draw the boundary of the QuadTree node
    sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
    rect.setPosition(bounds.left, bounds.top);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(1);
    window.draw(rect);

    // Draw all objects within the node
    // for (const auto& object : objects) {
    //     sf::RectangleShape objRect(sf::Vector2f(object.width, object.height));
    //     objRect.setPosition(object.left, object.top);
    //     objRect.setFillColor(sf::Color::Transparent);
    //     objRect.setOutlineColor(sf::Color::Red);
    //     objRect.setOutlineThickness(1);
    //     window.draw(objRect);
    // }

    // Recursively draw children
    if (split) {
        for (auto& child : children) {
            child->draw(window);
        }
    }
}

// std::vector<sf::FloatRect> QuadTree::query(sf::FloatRect range) {
//     std::vector<sf::FloatRect> found;
//     if (!bounds.intersects(range)) {
//         return found;
//     }

//     for (auto& object : objects) {
//         if (range.intersects(object)) {
//             found.push_back(object);
//         }
//     }

//     if (split) {
//         for (auto& child : children) {
//             auto childFound = child->query(range);
//             found.insert(found.end(), childFound.begin(), childFound.end());
//         }
//     }

//     return found;
// }

void QuadTree::clear() {
    objects.clear();
    split = false;

    for (auto& child : children) {
        if (child) {
            child->clear();
            child.reset();
        }
    }
}

void QuadTree::updateBounds(sf::Vector2f center) {
    float halfWidth = bounds.width/2;
    float halfHeight = bounds.height/2;
    bounds.left = center.x - halfWidth;
    bounds.top = center.y - halfHeight;
    windowBounds = sf::FloatRect((bounds.left + bounds.width/4), (bounds.top + bounds.height/4), bounds.width/2, bounds.height/2); 
}


//Class for grid
Grid::Grid() :
    gridBounds(0, 0, 0, 0), bufferZone(0, 0, 0, 0), visibleGrid(0, 0, 0, 0),
    cellWidth(0), cellHeight(0)
{}

Grid::Grid(sf::FloatRect bounds) :
    gridBounds(bounds)
{
    // Centering initial grid based on the player
    gridBounds.left = -gridBounds.width/4;
    gridBounds.top = -gridBounds.height/4;
    std::cout << "bufferZone: " << gridBounds.left << ", " << gridBounds.top << ", " << gridBounds.width << ", " << gridBounds.height << std::endl;
    static const sf::Vector2f offsets[9] = {
        { 0.0f,  0.0f}, {-1.0f,  0.0f}, {-1.0f, -1.0f}, // Center, Left, Top-left
        { 0.0f, -1.0f}, { 1.0f, -1.0f}, { 1.0f,  0.0f}, // Top, Top-right, right
        { 1.0f,  1.0f}, { 0.0f,  1.0f}, {-1.0f,  1.0f}, // Bottom-right, bottom, bottom-left
    };

    // Creating grids around the center grid
    for(int i = 0; i < 9; i++){
        sf::FloatRect newGrid = gridBounds;
        newGrid.left += offsets[i].x * gridBounds.width; 
        newGrid.top += offsets[i].y * gridBounds.height;
        totalGrids.push_back(newGrid); 
        hashGrid[i] = std::prev(totalGrids.end()); // Unique key for each grid
        makeCell(newGrid); // Create cells for each grid
    }
    
}

// void Grid::gridExpansion() {
//     int key = 0; 
//     if(firstGrid) {
//         key = dequeSize(); 
//         totalGrids.push_back(gridBounds); 
//         hashMap[key] = std::prev(totalGrids.end()); 
//         firstGrid = false;  
//     }

//     // if(bufferZone.intersects(totalGrids[0])) {
//     //     if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

//     //     }
//     // }
// }


void Grid::makeCell(sf::FloatRect grid) {
    int numCellsPerRow = 4;  // Defines how many cells are in a row, assumes a square grid so the same applies for columns
    cellWidth = grid.width/numCellsPerRow; 
    cellHeight = grid.height/numCellsPerRow; 

    for (int i = 0; i < 16; ++i) {  // Assumes a total of 16 cells (4x4 grid)
        int col = i % numCellsPerRow;  // Column index (0 to 3)
        int row = i / numCellsPerRow;  // Row index (0 to 3)
        float x = grid.left + col * cellWidth;  // Calculate the horizontal starting position of the cell
        float y = grid.top + row * cellHeight;  // Calculate the vertical starting position of the cell
        cells.emplace_back(x, y, cellWidth, cellHeight);
    }
}

// void Grid::insertObject(sf::FloatRect objects) {
//     if(bufferZone.intersects(objects)) {
//         entities.push_back(objects); 
//     }
//     else {
//         return; 
//     }
// } 

void Grid::bufferRegion(sf::View visible) { 
    bufferZone.left = -(visible.getCenter().x)/2;
    bufferZone.top = -(visible.getCenter().y)/2;
    bufferZone.width = visible.getSize().x + visible.getCenter().x;
    bufferZone.height = visible.getSize().y + visible.getCenter().y;
}






void Grid::draw(sf::RenderWindow& window) {

    // Draw the cells
    for (const auto& cellRect : cells) {
        sf::RectangleShape cell;
        cell.setPosition(cellRect.left, cellRect.top);
        cell.setSize(sf::Vector2f(cellRect.width, cellRect.height));
        cell.setOutlineColor(sf::Color::Green);
        cell.setOutlineThickness(0.5f);
        cell.setFillColor(sf::Color::Transparent);
        window.draw(cell);
    }
    // Draw the grids
    for (const auto& gridRect : totalGrids) {
        sf::RectangleShape rectangle;
        rectangle.setPosition(gridRect.left, gridRect.top);
        rectangle.setSize(sf::Vector2f(gridRect.width, gridRect.height));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(1.0f);
        rectangle.setFillColor(sf::Color::Transparent);
        window.draw(rectangle);
    }
}