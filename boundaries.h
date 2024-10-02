#ifndef BOUNDARIES_H
#define BOUNDARIES_H
#include <SFML\Graphics.hpp>
using namespace sf;
struct Boundary{ // this acts as an alternative fot sf::FloatRect
    float top;
    float left;
    float width;
    float height;
    Boundary getBoundaries(sf::Sprite & sprite)
    {
        Boundary bounds;
        bounds.top=sprite.getGlobalBounds().top;
        bounds.left=sprite.getGlobalBounds().left;
        bounds.width=sprite.getGlobalBounds().width;
        bounds.height=sprite.getGlobalBounds().height;
        return bounds;
    }
    
};
#endif