#ifndef BOMB_H
#define BOMB_H
#include "boundaries.h"
#include <math.h>
class Bomb 
{
public:
    Texture bombtex;
    Sprite bomb;
    float speed = 0.3;
    float angle;
    int x_ax, y_ax;
    
    Bomb(std::string png_path)  //para const reciving path to texture
    {
        bombtex.loadFromFile(png_path);
        bomb.setTexture(bombtex);
    }
    
    void Position(const Sprite &player) //Position fn 
    {
        x_ax = player.getPosition().x;
        y_ax = player.getPosition().y;
        bomb.setPosition(x_ax + player.getGlobalBounds().width / 2, y_ax + player.getGlobalBounds().height / 2);
    }
    
    void movebomb()  // moves bomb sprite
    {
        // Calculate the movement in the x and y directions based on the rotation angle
        bomb.move(0, speed);
        x_ax = bomb.getPosition().x;
        y_ax = bomb.getPosition().y;
    }
    Boundary getBoundary() //stores boundary values , alt to FloatRect
	{
		Boundary temp;
		return temp.getBoundaries(bomb);
	}
};
#endif