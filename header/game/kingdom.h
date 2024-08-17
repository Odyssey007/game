#pragma once 
#include "../header/battle/utility.h"
#include "../header/battle/player/player.h"
#include "../header/game/states.h"
#include "../header/kingdom/dynamicAsset.h"
#include "../header/kingdom/staticAsset.h"

class KingdomState : public States {
private: 
    sf::Vector2u resolution; 
    sf::Vector2f mousePos; 
    sf::View view; 

    //Entity instance 
    std::shared_ptr<Player> player; 
    DynamicAsset dynamicAsset;
    StaticAsset staticAsset;  
public:
    //Constructor 
    KingdomState(); 

    //Inherited functions 
    virtual void handleEvents(sf::RenderWindow& window, sf::Event& event) override;
    virtual void update(sf::RenderWindow& window, sf::Event& event) override;
    virtual void render(sf::RenderWindow& window) override;
    virtual void enter(sf::RenderWindow& window) override; 
    virtual StateMode getStateType() override; 
    virtual void exit() override; 

    //Functions
};