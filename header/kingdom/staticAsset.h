#include "../header/utility.h"

class StaticAsset {
private: 
    //Pool
    std::vector<sf::FloatRect> civilianPool; 

    //Size for pool 
    unsigned int civilianPoolSize;
public: 
    //Type of objects.
    std::vector<sf::FloatRect> staticObject; 

    //Constructor
    StaticAsset(); 

    //Static Assets
    void kingdomWall();
    void riverFlow();
    void trees();
    void civilians();
    void backForest();
    void shops(); 
    void render(sf::RenderWindow& window); 
};