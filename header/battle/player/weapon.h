#pragma once
#include "../header/utility.h"
#include "../header/animation.h"

class Sword {
    private: 
        sf::Texture texture;
        sf::Sprite sprite;
        Animation animation;

        bool facingRight;
    public: 
        //constructor
        Sword();
        //function
        void updateSword(sf::Vector2f playerPosition);
};