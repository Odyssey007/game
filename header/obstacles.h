#include "utility.h"
#include "entity.h"

class Obstacle : public Entity {
private:

public:
    Obstacle();
    //functions
    virtual void initialPosition() override;
    virtual void handleCollisions(Entity& other) override;
    virtual void render(sf::RenderWindow& window) override;
    //fetchers
    virtual size_t getState() override;
    virtual sf::Shape& getShape() override;
};