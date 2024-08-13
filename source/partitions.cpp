#include "../header/partitions.h"

//Methods for QuadTree
QuadTree::QuadTree(sf::FloatRect bounds, int level)
    : level(level), maxLevels(7), bounds(bounds), maxObjects(7)
{}

int QuadTree::getPrimaryNode(const std::shared_ptr<Entity>& entity) const {
    sf::FloatRect rect = entity->getBounds();
    
    float midpointX = rect.left + rect.width / 2;
    float midpointY = rect.top + rect.height / 2;

    for (int i = 0; i < 4; ++i) {
        if (containsWithTolerance(node[i]->bounds, midpointX, midpointY)) {
            return i;
        }
    }

    return -1; // If no child node contains the midpoint, return -1
}

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

void QuadTree::insertObject(std::shared_ptr<Entity> entity) {
    sf::FloatRect object = entity->getBounds();
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
                node[i]->insertObject(entity);
                inserted = true;
            }
        }
        // Only add to current node if it doesn't fit cleanly into any child
        if (!inserted) {
            objects.push_back(entity);
        }
    } else {
        objects.push_back(entity);
    }
}

void QuadTree::getNodeElements(std::vector<std::vector<std::shared_ptr<Entity>>>& elements) {
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