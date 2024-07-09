#include "../header/quadtree.h"

QuadTree::QuadTree(sf::FloatRect bounds, int rootCapacity):
    bounds(bounds), rootCapacity(rootCapacity),
    split(false)
{} 

void QuadTree::insertObject(sf::FloatRect object) {
    if(!bounds.intersects(object))  return; 

    if(objects.size() < rootCapacity) {
        objects.push_back(object); 
    }
    else {
        if (!split) {
            splitRoot(); 
        }
        for (auto& child : children) {
            child->insertObject(object); 
        }
    }
}

void QuadTree::splitRoot() {
    if(children[0] != 0) return; 

    float x = bounds.left;
    float y = bounds.top;
    float subWidth = bounds.width / 2;
    float subHeight = bounds.height / 2;

    children[0] = std::make_unique<QuadTree>(sf::FloatRect(x, y, subWidth, subHeight), rootCapacity);
    children[1] = std::make_unique<QuadTree>(sf::FloatRect(x + subWidth, y, subWidth, subHeight), rootCapacity);
    children[2] = std::make_unique<QuadTree>(sf::FloatRect(x, y + subHeight, subWidth, subHeight), rootCapacity);
    children[3] = std::make_unique<QuadTree>(sf::FloatRect(x + subWidth, y + subHeight, subWidth, subHeight), rootCapacity);

    split = true;
}

std::vector<sf::FloatRect> QuadTree::query(sf::FloatRect range) {
    std::vector<sf::FloatRect> found;
    if (!bounds.intersects(range)) {
        return found;
    }

    for (auto& object : objects) {
        if (range.intersects(object)) {
            found.push_back(object);
        }
    }

    if (split) {
        for (auto& child : children) {
            auto childFound = child->query(range);
            found.insert(found.end(), childFound.begin(), childFound.end());
        }
    }

    return found;
}