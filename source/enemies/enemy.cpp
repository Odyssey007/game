#include "../header/enemies/enemy.h"

Enemy::Enemy() {
    //preliminaries
    entityType = ENEMY; alive = true; currentAbility = 0;
    loadTexture("slime", "assets/slime.png"); //load up slime into textures
    //movement set up
    movementSpeed = 200.0f; baseDamage = 5.0f;
    bestDirection = sf::Vector2f(0.0f, 0.0f);
    generateDirections();
}

void Enemy::loadTexture(const std::string& name, const std::string& filePath) {
    sf::Texture texture;
    if (texture.loadFromFile(filePath)) {
        textures[name] = texture;
    } else {
        throw std::runtime_error ("Failed to load enemy texture");
    }
}

//generates all the directions of possible movement
void Enemy::generateDirections(int numDirections) {
    const float zeroThreshold = 1e-6; //to stop floating point precision error
    directions.clear();
    for (int i = 0; i < numDirections; i++) {
        float angle = 2 * M_PI * i / numDirections;
        float x = std::cos(angle);
        float y = std::sin(angle);
        if (std::abs(x) < zeroThreshold) x = 0;
        if (std::abs(y) < zeroThreshold) y = 0;
        directions.push_back(sf::Vector2f(x, y));
    }
}

void Enemy::meleeMovement(const sf::Vector2f& target) {
    sf::Vector2f toTarget = target - sprite.getPosition();
    toTarget = normalize(toTarget);
    //finds the optimal direction toward target 
    float maxDot = -1.0f;
    for (int i = 0; i < 32; i++) {
        float dot = dotProduct(directions[i], toTarget);
        if (dot > maxDot) {
            maxDot = dot;
            bestDirection = directions[i];
        }
    }
    //separation force from neighbors
    
    //move
    moveDistance = bestDirection*movementSpeed*DeltaTime::getInstance()->getDeltaTime();
    //sprite.move(moveDistance);
}

//ENTITY FUNCTIONS

void Enemy::setInitialPosition(const sf::View& view) {
    //pick the side of the screen to spawn in
    sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.0f, view.getSize());
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> distribute(1, 4);

    std::pair<int, int> rangeX, rangeY;
    switch (distribute(gen)) {
        case 1: //top
            std::cout << "1\n";
            rangeX = {static_cast<int>(viewBounds.left), static_cast<int>(viewBounds.left + viewBounds.width)};
            rangeY = {static_cast<int>(viewBounds.top) - 150, static_cast<int>(viewBounds.top) - 100};
            break;
        case 2: //bottom
            std::cout << "2\n";
            rangeX = {static_cast<int>(viewBounds.left), static_cast<int>(viewBounds.left + viewBounds.width)};
            rangeY = {static_cast<int>(viewBounds.top + viewBounds.height) + 100, static_cast<int>(viewBounds.top + viewBounds.height) + 150};
            break;
        case 3: //left 
            std::cout << "3\n";
            rangeX = {static_cast<int>(viewBounds.left) - 150*(1.71), static_cast<int>(viewBounds.left) - 100*(1.71)};
            rangeY = {static_cast<int>(viewBounds.top), static_cast<int>(viewBounds.top + viewBounds.height)};
            break;
        case 4: //right
            std::cout << "4\n";
            rangeX = {static_cast<int>(viewBounds.left + viewBounds.width) + 100*(1.71), static_cast<int>(viewBounds.left + viewBounds.width) + 150*(1.71)};
            rangeY = {static_cast<int>(viewBounds.top), static_cast<int>(viewBounds.top + viewBounds.height)};
            break;
    }


    sf::Vector2i spawnPosition = randomGenerator(rangeX, rangeY);

    // std::cout << rangeX.first << ", " << rangeX.second << std::endl;
    // std::cout << rangeY.first << ", " << rangeY.second << std::endl;
    // std::cout << "||||||||\n";
    // std::cout << spawnPosition.x << ", " << spawnPosition.y << std::endl;

    sprite.setPosition(spawnPosition.x, spawnPosition.y);
}

//ENTITY FUNCTIONS

bool Enemy::isAlive() const {
    return alive;
}

int Enemy::getState() const {
    return currentAbility; 
}

const sf::Vector2f& Enemy::getVelocity() const {
    return moveDistance;
}

void Enemy::setVelocity(const sf::Vector2f& velocity) {
    moveDistance = velocity;
}


void Enemy::applyMovement() {
    sprite.move(moveDistance);
    moveDistance = sf::Vector2f(0.0f, 0.0f);
}

void Enemy::handleCollision(Entity& entity) {
    //set up
    sf::Vector2f position1 = this->getPosition();
    sf::Vector2f position2 = entity.getPosition();
    float radius1 = this->getBounds().width / 2.0f;
    float radius2 = entity.getBounds().width / 2.0f;
    //
    float minDistance = radius1 + radius2;
    float dist = distance(position1, position2);

    if (dist < minDistance) {
        float overlap = minDistance - dist;
        sf::Vector2f direction = normalize(position2 - position1);
        sf::Vector2f correction = direction * (overlap / 2.0f);
        //apply a separation force
        this->setVelocity(this->getVelocity() - correction);
        entity.setVelocity(entity.getVelocity() + correction);
    }
}