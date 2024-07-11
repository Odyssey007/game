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

    std::cout << "Splitting root node." << std::endl;

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
    // Draw the boundary of the QuadTree node
    sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
    rect.setPosition(bounds.left, bounds.top);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(1);
    window.draw(rect);

    // Draw all objects within the node
    for (const auto& object : objects) {
        sf::RectangleShape objRect(sf::Vector2f(object.width, object.height));
        objRect.setPosition(object.left, object.top);
        objRect.setFillColor(sf::Color::Transparent);
        objRect.setOutlineColor(sf::Color::Red);
        objRect.setOutlineThickness(1);
        window.draw(objRect);
    }

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