#include "../header/utility.h"

class DynamicAsset {
private:
    //Pool
    std::vector<sf::FloatRect> hutPool; 
    std::vector<sf::FloatRect> farmPool;
    std::vector<sf::FloatRect> animalFarmPool; 

    //Size for pool 
    unsigned int hutPoolSize;
    unsigned int farmPoolSize;
    unsigned int animalFarmSize;
public: 
    //Type of objects.
    std::vector<sf::FloatRect> dynamicObject;

    //Constructor
    DynamicAsset(); 

    //Dynamic Assets 
    void kingCastle(); 
    void huts();
    void multipurpose(); //Contains storage, kitchen, mason, carpenter
    void scienceTech(); 
    void blacksmithWeapon(); 
    void farms(); 
    void paths();
    void animalFarms();
    void render(sf::RenderWindow& window); 
}; 